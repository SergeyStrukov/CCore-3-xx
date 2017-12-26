/* WindowReport.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/WindowReport.h>
#include <CCore/inc/video/SmoothDrawArt.h>

#include <CCore/inc/CharProp.h>
#include <CCore/inc/MemBase.h>

namespace CCore {
namespace Video {

/* class ExceptionStore */

auto ExceptionStore::try_alloc() -> Header *
 {
  if( !head ) return PlaceAt(mem);

  if( (void *)head<(void *)tail )
    {
     void *ret=GetNext(tail);

     if( PtrDist(ret,lim)>=Delta+MaxMsgLen ) return PlaceAt(ret);

     ret=mem;

     if( PtrDist(ret,head)>=Delta+MaxMsgLen ) return PlaceAt(ret);

     return 0;
    }
  else
    {
     void *ret=GetNext(tail);

     if( PtrDist(ret,head)>=Delta+MaxMsgLen ) return PlaceAt(ret);

     return 0;
    }
 }

auto ExceptionStore::alloc() -> Header *
 {
  for(;;)
    {
     if( Header *ret=try_alloc() ) return ret;

     free();
    }
 }

void ExceptionStore::free()
 {
  if( Header *ptr=head )
    {
     head=ptr->next;

     if( !head ) tail=0;
    }
 }

ExceptionStore::ExceptionStore()
 {
  ulen alloc_len=MaxMsgCount*(Delta+MaxMsgLen);

  mem=TryMemAlloc(alloc_len);

  if( !mem )
    {
     ErrorMsgBox("No memory for the exception store","Fatal error");

     throw CatchType();
    }

  lim=PtrAdd(mem,alloc_len);
  head=0;
  tail=0;
 }

ExceptionStore::~ExceptionStore()
 {
  MemFree(mem);
 }

PtrLen<char> ExceptionStore::startMsg()
 {
  Header *ptr=alloc();

  ptr->next=0;
  ptr->len=MaxMsgLen;
  ptr->done=false;
  ptr->divide=false;

  if( tail )
    {
     tail->next=ptr;
     tail=ptr;
    }
  else
    {
     head=ptr;
     tail=ptr;
    }

  return GetBuf(ptr);
 }

void ExceptionStore::endMsg(PtrLen<char> rest)
 {
  tail->index=index++;
  tail->len-=rest.len;
  tail->done=true;

#ifdef CCORE_UTF8

  StrLen text=GetStr(tail);

  TrimUtf8End(text);

  tail->len=text.len;

#endif
 }

void ExceptionStore::divide()
 {
  if( tail ) tail->divide=true;
 }

/* class ExceptionWindow */

ulen ExceptionWindow::CountLines(StrLen text)
 {
  if( !text ) return 1;

  ulen ret=0;

  for(bool first=true; +text ;first=false)
    {
     StrLen line=CutLine(text);

     if( !text && !line && !first ) break;

     ret++;
    }

  return ret;
 }

Coord ExceptionWindow::TotalDX(const Font &font,ulen index,StrLen text)
 {
  Coord ret=0;

  if( !text ) text="<empty>"_c;

  for(bool first=true; +text ;first=false)
    {
     StrLen line=CutLine(text);

     if( !text && !line && !first ) break;

     if( first )
       {
        char temp[TextBufLen];
        PrintBuf out(Range(temp));

        Printf(out,"#;) ",index);

        StrLen line1=out.close();

        TextSize ts=font->text(line1,line);

        Replace_max(ret,ts.full_dx);
       }
     else
       {
        TextSize ts=font->text(line);

        Replace_max(ret,ts.full_dx);
       }
    }

  return ret;
 }

void ExceptionWindow::setScrollPage()
 {
  xscroll.setRange(total_dx,ptext.dx);

  yscroll.setRange(lines+page-1,page);
 }

void ExceptionWindow::setLines()
 {
  ulen temp=0;
  Coord temp_dx=0;

  const Font &font=cfg.font.get();

  report.apply( [&] (ulen index,StrLen text,bool)
                    {
                     temp+=CountLines(text)+1;

                     Replace_max(temp_dx,TotalDX(font,index,text));

                    } );

  lines=temp;

  total_dx=Min_cast(temp_dx,MaxCoord-delta_dx)+delta_dx;

  setScrollPage();
 }

void ExceptionWindow::drawText(DrawBuf buf,Pane pane,Coord xoff) const
 {
  SmoothDrawArt art(buf);

  const Font &font=cfg.font.get();
  Coord y=text_by;
  ulen ind=0;
  ulen off=yscroll.getPos();

  FontSize fs=font->getSize();

  Coord xpos=fs.dx0-xoff;

  MCoord width=+cfg.width;

  MCoord x0=Fraction(pane.x);
  MCoord dx=Fraction(pane.dx);
  MCoord x1=x0+dx/2;
  MCoord x2=x0+dx;

  VColor vc=+cfg.text;
  VColor divider=+cfg.divider;

  report.apply( [&] (ulen index,StrLen text,bool divide)
                    {
                     if( ind>=off+page ) return;

                     if( !text ) text="<empty>"_c;

                     for(bool first=true; +text ;first=false)
                       {
                        StrLen line=CutLine(text);

                        if( !text && !line && !first ) break;

                        if( ind>=off )
                          {
                           if( ind>=off+page ) return;

                           if( first )
                             {
                              char temp[TextBufLen];
                              PrintBuf out(Range(temp));

                              Printf(out,"#;) ",index);

                              StrLen line1=out.close();

                              font->text(buf,pane,TextPlace(xpos,y),line1,line,vc);
                             }
                           else
                             {
                              font->text(buf,pane,TextPlace(xpos,y),line,vc);
                             }

                           y+=text_dy;
                          }

                        ind++;
                       }

                     if( ind>=off )
                       {
                        if( ind>=off+page ) return;

                        MCoord div_y=Fraction(pane.y)-MPoint::Half+Fraction(y-text_by)+Fraction(text_dy)/2;

                        if( divide )
                          {
                           art.path(2*width,divider,MPoint(x0,div_y),MPoint(x2,div_y));
                          }
                        else
                          {
                           art.path(width,divider,MPoint(x0,div_y),MPoint(x1,div_y));
                          }

                        y+=text_dy;
                       }

                     ind++;

                    } );
 }

void ExceptionWindow::subYPos(ulen delta)
 {
  if( ulen off=yscroll.getPos() )
    {
     yscroll.setPos(PosSub(off,delta));

     redraw();
    }
 }

void ExceptionWindow::addYPos(ulen delta)
 {
  ulen off=yscroll.getPos();

  yscroll.setPos(AddToCap<ulen>(off,delta,lines));

  redraw();
 }

void ExceptionWindow::subXPos(ulen delta)
 {
  if( ulen off=xscroll.getPos() )
    {
     delta*=delta_dx;

     xscroll.setPos(PosSub(off,delta));

     redraw();
    }
 }

void ExceptionWindow::addXPos(ulen delta)
 {
  ulen off=xscroll.getPos();

  delta*=delta_dx;

  xscroll.setPos(AddToCap<ulen>(off,delta,total_dx));

  redraw();
 }

void ExceptionWindow::update()
 {
  if( opened )
    {
     setLines();

     redraw();
    }
 }

void ExceptionWindow::setXPos(ulen)
 {
  redraw();
 }

void ExceptionWindow::setYPos(ulen)
 {
  redraw();
 }

ExceptionWindow::ExceptionWindow(SubWindowHost &host,const Config &cfg_,WindowReportBase &report_)
 : SubWindow(host),
   report(report_),
   cfg(cfg_),

   wlist(*this),

   xscroll(wlist,cfg.scroll_cfg),
   yscroll(wlist,cfg.scroll_cfg),

   connector_update(this,&ExceptionWindow::update,report.updated),
   connector_xscroll_changed(this,&ExceptionWindow::setXPos,xscroll.changed),
   connector_yscroll_changed(this,&ExceptionWindow::setYPos,yscroll.changed)
 {
  wlist.insTop(xscroll,yscroll);
 }

ExceptionWindow::~ExceptionWindow()
 {
 }

 // methods

void ExceptionWindow::reposition() noexcept
 {
  ulen temp=0;
  ulen off=0;

  report.apply( [&] (ulen,StrLen text,bool divide)
                    {
                     temp+=CountLines(text)+1;

                     if( divide ) off=temp;

                    } );

  yscroll.setPos(off);

  redraw();
 }

 // drawing

void ExceptionWindow::layout(unsigned flags)
 {
  FontSize fs=cfg.font->getSize();

  text_dy=fs.dy;
  text_by=fs.by;
  delta_dx=fs.medDX();

  Point size=getSize();

  Coord dxy=+cfg.scroll_cfg.get().dxy;

  if( size>Point::Diag(dxy) )
    {
     Pane xp=Pane(dxy,size.y-dxy,size.x-dxy,dxy);
     Pane yp=Pane(Null,dxy,size.y-dxy);

     if( xscroll.isGoodSize(xp.getSize()) ) xscroll.setPlace(xp,flags); else xscroll.setPlace(Empty,flags);
     if( yscroll.isGoodSize(yp.getSize()) ) yscroll.setPlace(yp,flags); else yscroll.setPlace(Empty,flags);

     Coord offx=dxy+delta_dx;

     ptext=Pane(offx,0,size.x-offx,size.y-dxy);
    }
  else
    {
     xscroll.setPlace(Empty,flags);
     yscroll.setPlace(Empty,flags);

     ptext=Pane(Null,size);
    }

  page=Max<ulen>(ptext.dy/text_dy,1);

  setLines();
 }

void ExceptionWindow::draw(DrawBuf buf,bool drag_active) const
 {
  buf.erase(+cfg.back);

  Coord xoff=Coord(xscroll.getPos());

  drawText(buf.cut(ptext),ptext,xoff);

  wlist.draw(buf,drag_active);
 }

 // base

void ExceptionWindow::open()
 {
  opened=true;

  setLines();
 }

void ExceptionWindow::close()
 {
  opened=false;
 }

 // user input

void ExceptionWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void ExceptionWindow::react_other(UserAction action)
 {
  wlist.react(action);
 }

void ExceptionWindow::react_Key(VKey vkey,KeyMod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_PageUp :
      {
       subYPos(repeat*page);
      }
     break;

     case VKey_Up :
      {
       subYPos(repeat);
      }
     break;

     case VKey_PageDown :
      {
       addYPos(repeat*page);
      }
     break;

     case VKey_Down :
      {
       addYPos(repeat);
      }
     break;

     case VKey_Left :
      {
       subXPos(repeat);
      }
     break;

     case VKey_Right :
      {
       addXPos(repeat);
      }
     break;

     case VKey_Home :
      {
       yscroll.setPos(0);

       redraw();
      }
     break;

     case VKey_End :
      {
       yscroll.setPos(lines);

       redraw();
      }
     break;
    }
 }

void ExceptionWindow::react_Wheel(Point,MouseKey mkey,Coord delta)
 {
  if( mkey&MouseKey_Shift )
    {
     if( delta<0 )
       {
        subXPos(IntAbs(delta));
       }
     else
       {
        addXPos(IntAbs(delta));
       }
    }
  else
    {
     if( delta<0 )
       {
        subYPos(IntAbs(delta));
       }
     else
       {
        addYPos(IntAbs(delta));
       }
    }
 }

/* class WindowReportBase */

void WindowReportBase::print(StrLen str)
 {
  if( !enable ) return;

  if( !msg )
    {
     buf=startMsg();

     msg=true;
    }

  Replace_min(str.len,buf.len);

  str.copyTo(buf.ptr);

  buf+=str.len;
 }

void WindowReportBase::end()
 {
  if( !enable ) return;

  if( msg )
    {
     endMsg(buf);

     msg=false;

     non_cleared=true;

     updated.assert();
    }
 }

void WindowReportBase::boxShow() noexcept
 {
  char buf[TextBufLen];

  PrintBuf out(Range(buf));

  ulen off=0;

  {
   ulen temp=0;

   apply( [&] (ulen,StrLen,bool divide)
              {
               temp++;

               if( divide ) off=temp;

              } );
  }

  {
   ulen temp=0;

   apply( [&] (ulen index,StrLen text,bool divide)
              {
               if( temp>=off )
                 {
                  Printf(out,"#;) #;\n",index,text);

                  if( divide )
                    Printf(out,"#16=;\n",TextDivider());
                  else
                    Printf(out,"#16;\n",TextDivider());
                 }

               temp++;

              } );
  }

  ErrorMsgBox(out.close(),getTitle().str());
 }

class WindowReportBase::TempQueue : DeferCallQueue
 {
   Desktop *desktop;

  private:

   virtual void forward(TimeScope time_scope)
    {
     try
       {
        desktop->wait(time_scope);

        if( !desktop->pump() ) stop();
       }
     catch(...)
       {
        // ignore
       }
    }

  public:

   explicit TempQueue(Desktop *desktop_,MSec tick_period)
    : DeferCallQueue(tick_period),
      desktop(desktop_)
    {
     activate();
    }

   ~TempQueue()
    {
     deactivate();
    }
 };

void WindowReportBase::lastShow()
 {
  if( non_cleared )
    {
     show();
    }
 }

WindowReportBase::WindowReportBase(Desktop *desktop_,MSec tick_period_,const ExceptionWindow::ConfigType &cfg_)
 : desktop(desktop_),
   tick_period(tick_period_),
   cfg(cfg_)
 {
 }

WindowReportBase::~WindowReportBase()
 {
 }

void WindowReportBase::clear() noexcept
 {
  ReportException::clear();

  non_cleared=false;

  divide();
 }

void WindowReportBase::show() noexcept
 {
  if( !enable ) return;

  enable=false;

  ReportException::clear();

#if 1

  try
    {
     if( DeferCallQueue::IsActive() )
       {
        modalLoop();
       }
     else
       {
        TempQueue queue(desktop,tick_period);

        modalLoop();
       }
    }
  catch(...)
    {
     boxShow();
    }

#else

  boxShow();

#endif

  enable=true;
 }

/* class ExceptionClient */

ExceptionClient::~ExceptionClient()
 {
 }

void ExceptionClient::clear() noexcept
 {
  report.clear();
 }

void ExceptionClient::guard()
 {
  report.guard();
 }

void ExceptionClient::show() noexcept
 {
  if( in_loop )
    {
     reposition();

     alert.assert();
    }
  else
    {
     report.show();
    }
 }

void ExceptionClient::beforeLoop() noexcept
 {
  in_loop=true;
 }

void ExceptionClient::afterLoop() noexcept
 {
  in_loop=false;
 }

void ExceptionClient::alive()
 {
  if( report.nonEmpty() && in_loop ) alert.assert();
 }

} // namespace Video
} // namespace CCore


