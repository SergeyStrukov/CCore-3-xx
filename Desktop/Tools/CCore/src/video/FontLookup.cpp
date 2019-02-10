/* FontLookup.cpp */
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

#include <CCore/inc/video/FontLookup.h>

namespace CCore {
namespace Video {

/* class FontLookup::Step */

StepResult FontLookup::Step::finish(FontLookup &obj,StepResult result)
 {
  if( result==StepFinalOk ) obj.buildIndex();

  return result;
 }

FontLookup::Step::Step()
 {
 }

FontLookup::Step::~Step()
 {
 }

StepResult FontLookup::Step::start(FontLookup &obj,bool use_cache)
 {
  return finish(obj,dbstep.start(obj.fdb,use_cache));
 }

StepResult FontLookup::Step::step(IncrementalProgress &progress,FontLookup &obj)
 {
  return finish(obj,dbstep.step(progress,obj.fdb));
 }

void FontLookup::Step::erase() noexcept
 {
  dbstep.erase();
 }

/* class FontLookup */

FontCouple FontLookup::Build(const FontInfo *info,Coord font_size,const AbstractExtFont::Config &font_config)
 {
  try
    {
     FontCouple ret;

     ret.param.engine_type=FontParam::EngineFreeType;
     ret.param.file_name=info->file_name;
     ret.param.size_type=FontParam::SizeXY;
     ret.param.set_size.size_xy=font_size;
     ret.param.cfg=font_config;

     ret.create();

     return ret;
    }
  catch(...)
    {
     return FontCouple();
    }
 }

void FontLookup::buildIndex()
 {
  index.build(fdb, [] (const FontInfo &obj) { return obj.scalable; } ,
                   [] (const FontInfo &a,const FontInfo &b) { return AlphaCmp(CmpAsStr(a.family),CmpAsStr(b.family),
                                                                              a.bold,b.bold,
                                                                              a.italic,b.italic); } );
 }

FontLookup::FontLookup(InitType type)
 {
  switch( type )
    {
     case Populate :
      {
       fdb.populate();
       buildIndex();
      }
     break;

     case Cache :
      {
       fdb.cache();
       buildIndex();
      }
     break;
    }
 }

FontLookup::~FontLookup()
 {
 }

const FontInfo * FontLookup::find(StrLen family,bool bold,bool italic) const
 {
  return index.find( [=] (const FontInfo &obj) { return AlphaCmp(CmpAsStr(obj.family),CmpAsStr(family),
                                                                 obj.bold,bold,
                                                                 obj.italic,italic); } );
 }

FontCouple FontLookup::build(StrLen family,bool bold,bool italic,Coord font_size,const AbstractExtFont::Config &font_config) const
 {
  const FontInfo *info=find(family,bold,italic);

  if( !info ) return FontCouple();

  return Build(info,font_size,font_config);
 }

} // namespace Video
} // namespace CCore

//----------------------------------------------------------------------------------------

#include <CCore/inc/video/UserPreference.h>
#include <CCore/inc/video/ApplicationBase.h>
#include <CCore/inc/video/Layout.h>

namespace CCore {
namespace Video {

/* class DialogFontLookup::Window */

class DialogFontLookup::Window : public ComboWindow
 {
   FontLookup &lookup;

   ArrowProgressWindow::ConfigType cfg;

   VColor back = Silver ;

   Coord space = 30 ;
   Coord len = 300 ;

   ArrowProgressWindow progress;

   ProgressTo<ArrowProgressWindow> progress_control;

   FontLookup::Incremental font_inc;

  private:

   void complete(bool)
    {
     askFrameClose();
    }

   SignalConnector<Window,bool> connector_complete;

  public:

   Window(SubWindowHost &host,FontLookup &lookup_)
    : ComboWindow(host),
      lookup(lookup_),

      progress(wlist,cfg),
      progress_control(progress),
      font_inc(progress_control),

      connector_complete(this,&Window::complete,font_inc.completed)
    {
     wlist.insTop(progress);
    }

   virtual ~Window() {}

   // methods

   Point getMinSize() const
    {
     return Point(2*space+len,2*space+len/10);
    }

   void start() { lookup.cache(font_inc); }

   // drawing

   virtual void layout()
    {
     Pane pane=getPane();

     progress.setPlace(pane.shrink(space));
    }

   virtual void drawBack(DrawBuf buf,bool) const
    {
     buf.erase(back);
    }
 };

/* class DialogFontLookup::Frame */

class DialogFontLookup::Frame : public FixedFrame
 {
   Window client;

   String title = "Font lookup in progress, please, standby ! "_str ;

  public:

   Frame(Desktop *desktop,const FixedFrame::ConfigType &cfg,FontLookup &lookup)
    : FixedFrame(desktop,cfg),
      client(*this,lookup)
    {
     bindClient(client);
    }

   virtual ~Frame() {}

   void create()
    {
     Point size=getMinSize(true,Range(title),client.getMinSize());

     Pane pane=GetWindowPlace(desktop,Div(5,12),size);

     createMain(pane,title);
    }

   void start() { client.start(); }
 };

/* class DialogFontLookup::App */

class DialogFontLookup::App : public ApplicationBase
 {
   FixedFrame::ConfigType cfg;

   Frame frame;

  private:

   virtual void clearException() noexcept
    {
    }

   virtual void guardException()
    {
    }

   virtual void showException() noexcept
    {
    }

   virtual void prepare()
    {
     frame.create();

     frame.start();
    }

   virtual void beforeLoop() noexcept
    {
    }

   virtual void afterLoop() noexcept
    {
    }

   virtual void final()
    {
     // do nothing
    }

  public:

   App(Desktop *desktop,FontLookup &lookup)
    : ApplicationBase(desktop,DeferCallQueue::DefaultTickPeriod),
      frame(desktop,cfg,lookup)
    {
    }

   ~App() {}
 };

/* class DialogFontLookup */

DialogFontLookup::DialogFontLookup()
 : FontLookup(None)
 {
  App app(DefaultDesktop,*this);

  app.run();
 }

} // namespace Video
} // namespace CCore

