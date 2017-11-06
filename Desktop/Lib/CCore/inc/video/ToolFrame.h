/* ToolFrame.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_video_ToolFrame_h
#define CCore_inc_video_ToolFrame_h

#include <CCore/inc/video/SubWindow.h>
#include <CCore/inc/video/FrameBase.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/DeferCall.h>

namespace CCore {
namespace Video {

/* classes */

class ToolFrame;

/* class ToolFrame */

class ToolFrame : public FrameWindow , public SubWindowHost
 {
  public:

   struct Config
    {
     RefVal<VColor> shadeColor = Violet ;
     RefVal<Clr>    shadeAlpha =     64 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       shadeColor.bind(bag.shadeColor);
       shadeAlpha.bind(bag.shadeAlpha);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   SubWindow *client = 0 ;

   AliveControl *client_ac = &AliveControl::Default ;

   Point size;

   bool has_focus = false ;
   bool client_enter = false ;
   bool client_capture = false ;
   bool delay_draw = false ;
   bool enable_react = true ;

   RedrawSet redraw_set;

  private:

   void guardClient();

   void guardDead();

   void reset();

   SubWindow & getClient();

   void shade(FrameBuf<DesktopColor> &buf);

   void shade(FrameBuf<DesktopColor> &buf,Pane pane);

   void redrawBuf(FuncArgType<FrameBuf<DesktopColor> &> func);

   void redrawAll(bool do_layout=false);

   void redrawSet();

  public:

   ToolFrame(Desktop *desktop,const Config &cfg);

   ToolFrame(Desktop *desktop,const Config &cfg,Signal<> &update);

   virtual ~ToolFrame();

   // methods

   void bindClient(SubWindow &client);

   void connectUpdate(Signal<> &update);

   void createMain(Pane pane,const DefString &title);

   void create(Pane pane);

   void create(FrameWindow *parent,Pane pane);

   // SubWindowHost

   virtual FrameWindow * getFrame() noexcept;

   virtual Point getScreenOrigin() noexcept;

   virtual void redraw(Pane pane) noexcept;

   virtual void setFocus(SubWindow *) noexcept;

   virtual void captureMouse(SubWindow *) noexcept;

   virtual void releaseMouse(SubWindow *) noexcept;

   // base

   virtual void alive();

   virtual void dying();

   virtual void dead();

   virtual void askClose();

   virtual void setSize(Point size_,bool buf_dirty);

   virtual void paintDone(unsigned);

   // keyboard

   virtual void gainFocus();

   virtual void looseFocus();

   // mouse

   virtual void looseCapture();

   virtual void setMouseShape(Point point,KeyMod kmod);

   // user input

   virtual void disableReact();

   virtual void enableReact();

   virtual void react(UserAction action);

   void react_other(UserAction action);

   void react_Move(Point point,MouseKey mkey);

   void react_Leave();

   // DeferInput

   class Input : DeferInput<ToolFrame>
    {
      friend class ToolFrame;

      explicit Input(ToolFrame *window) : DeferInput<ToolFrame>(window) {}

      ~Input() {}

      using DeferInput<ToolFrame>::try_post;

     public:

      void redrawAll(bool do_layout=false) { try_post(&ToolFrame::redrawAll,do_layout); }

      void redrawSet() { try_post(&ToolFrame::redrawSet); }
    };

   Input input;

  private:

   void update();

   SignalConnector<ToolFrame> connector_update;
 };

} // namespace Video
} // namespace CCore

#endif

