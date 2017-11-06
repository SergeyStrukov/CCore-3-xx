/* wintest.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/wintest.h>

namespace App {

/* class ResultBuilder */

void ResultBuilder::entry()
 {
  BufReport report;

  try
    {
     work();
    }
  catch(CatchType)
    {
     setResult(String(report.close()));
    }
 }

void ResultBuilder::exit()
 {
  stop_sem.give();
 }

void ResultBuilder::setCurrent(unsigned current_)
 {
  {
   Mutex::Lock lock(mutex);

   current=current_;
  }

  interrupt();
 }

void ResultBuilder::setResult(const Info &result_)
 {
  {
   Mutex::Lock lock(mutex);

   result=result_;
   done=true;
  }

  interrupt();
 }

ResultBuilder::ResultBuilder(Function<void (void)> interrupt_,unsigned total_)
 : interrupt(interrupt_),
   total(total_)
 {
 }

ResultBuilder::~ResultBuilder()
 {
  stop();

  if( ready ) stop_sem.take();
 }

void ResultBuilder::start()
 {
  if( ready.trySet(0,1)==0 )
    {
     if( !run_or_exit() )
       {
        Printf(Exception,"App::ResultBuilder::start() : cannot start working task");
       }
    }
 }

void ResultBuilder::stop()
 {
  cancel=1;
 }

unsigned ResultBuilder::getTotal() const
 {
  Mutex::Lock lock(mutex);

  return total;
 }

unsigned ResultBuilder::getCurrent() const
 {
  Mutex::Lock lock(mutex);

  return current;
 }

bool ResultBuilder::getDone() const
 {
  Mutex::Lock lock(mutex);

  return done;
 }

Info ResultBuilder::getResult() const
 {
  Mutex::Lock lock(mutex);

  return result;
 }

/* class ResultWindow */

ResultWindow::ResultWindow(SubWindowHost &host,const ConfigType &cfg_,ResultBuilder &builder_)
 : ComboWindow(host),
   cfg(cfg_),
   builder(builder_),

   progress(wlist,cfg.progress_cfg.get()),
   info(wlist,cfg.info_cfg.get())
 {
  wlist.insTop(progress,info);

  progress.setTotal(builder.getTotal());
 }

ResultWindow::~ResultWindow()
 {
  builder.stop();
 }

void ResultWindow::ping()
 {
  progress.setPosPing(builder.getCurrent());

  if( builder.getDone() )
    {
     info.setInfo(builder.getResult());

     progress.stopPing();
    }
 }

 // drawing

void ResultWindow::layout()
 {
  Point size=getSize();

  Coord split_dy = +cfg.split_dy ;
  Coord delta_dx = +cfg.delta_dx ;
  Coord delta_dy = +cfg.delta_dy ;

  if( size.y>split_dy )
    {
     Pane pane(Null,size);

     Pane top=SplitY(split_dy,pane);

     progress.setPlace(top.shrink(delta_dx,delta_dy));

     info.setPlace(pane);
    }
  else
    {
     progress.setPlace(Empty);
     info.setPlace(Empty);
    }
 }

void ResultWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

 // base

void ResultWindow::open()
 {
  ComboWindow::open();

  builder.start();
 }

 // user input

void ResultWindow::react(UserAction action)
 {
  action.dispatch(*this);

  wlist.react(action);
 }

void ResultWindow::react_Key(VKey vkey,KeyMod)
 {
  if( vkey==VKey_Esc ) builder.stop();
 }

} // namespace App



