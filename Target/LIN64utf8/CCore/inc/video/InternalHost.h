/* InternalHost.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/LIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_InternalHost_h
#define CCore_inc_video_InternalHost_h

#include <CCore/inc/video/InternalUtils.h>

#include <CCore/inc/List.h>
#include <CCore/inc/Timer.h>
#include <CCore/inc/PlatformRandom.h>

namespace CCore {
namespace Video {
namespace Internal {

/* classes */

class DClickDetector;

class HoverDetector;

class X11Host;

/* class DClickDetector */

class DClickDetector : NoCopy
 {
   bool flag = false ;
   Point point;
   MSecTimer timer;

  public:

   DClickDetector() {}

   void reset() { flag=false; }

   bool detect(Point point_,MSec timeout);

   void ping(MSec timeout);

   void stop() { flag=false; }
 };

/* class HoverDetector */

class HoverDetector : NoCopy
 {
   MSec timeout = Null ;
   bool enable = false ;

   bool flag = false ;
   Point point;
   MouseKey mkey = MouseKey_Null ;
   MSecTimer timer;

  public:

   HoverDetector() {}

   void reset()
    {
     flag=false;
     enable=false;
    }

   void track(MSec timeout_)
    {
     timeout=timeout_;
     enable=true;
    }

   void untrack() { enable=false; }

   void start(Point point_,MouseKey mkey_);

   void stop() { flag=false; }

   void test(FrameWindow *frame);
 };

/* class X11Host */

class X11Host : public WindowHost , WindowDispatcher
 {
   Display *disp;
   int screen;

   Window window = None ;
   GC gc = None ;
   bool window_ok = false ;
   bool is_main = false ;
   bool expose_flag = true ;
   bool show_flag = false ;
   bool parent_show = true ;

   MouseShape mouse_shape = Mouse_Null ;

   bool user_flag = true ;
   bool leave_flag = false ;
   bool motion_flag = true ;

   bool stack_changed = true ;

   Point origin;
   Point size;

   WindowBuf buf;
   bool buf_dirty = true ;

   Pane restore;
   bool max_flag = false ;

   HoverDetector hover;

   MSec dclick_timeout = 500_msec ;

   DClickDetector left_dclick;
   DClickDetector right_dclick;

   DLink<X11Host> dlink;

   using DAlgo = DLink<X11Host>::LinearAlgo<&X11Host::dlink> ;

   X11Host *dparent = 0 ;
   DAlgo::Top dlist;

   DynArray<uint8> clipboard;

  private:

   // reset()

   void reset();

   // utils

   void guardAlive(const char *format);

   void guardDead(const char *format);

   static void GuardMaxSize(const char *format,Point max_size);

   static void GuardPane(const char *format,Pane pane,Point max_size);

   void guardCreate(const char *format,Point max_size);

   void guardCreate(const char *format,Pane pane,Point max_size);

   static PlatformRandom Random;

   static Coord RandomLen(Coord len);

   static Coord RandomPos(Coord len);

   static Bool MatchSelection(Display *,XEvent *event,XPointer);

   void setClipboard(PtrLen<const Char> text);

   static void Translate(Function<void (PtrLen<const Char>)> func,PtrLen<const uint8> text);

   // cursor

   static Cursor CursorTable[];

   static Cursor GetCursor(Display *display,MouseShape mshape);

   // event mask

   static unsigned EventMask(bool user_flag,bool leave_flag);

   void setEventMask();

   void disableMotionNotify();

   void enableMotionNotify();

   // MainWindow

   static X11Host *MainWindow;

   // descendants

   void addDescendant(X11Host *host);

   void delAsDescendant();

   // postDestroy()

   void postDestroy();

   // message handle

   static MouseKey GetMKey(unsigned state);

   static KeyMod GetKMod(unsigned state);

   static auto MapToVKey(unsigned state,unsigned keycode);

   static auto MapToChar(unsigned state,unsigned keycode);

   void mouseShape(VKey vkey,KeyMod kmod);

   virtual void handle(XEvent &event);

   virtual void ping();

   // group actions

   void destroyAll();

   void clearStackChanged();

   void raiseAll(bool force=false);

   void parentShowOn();

   void parentShowOff();

   void showAll();

   void hideAll();

   void do_move(Pane pane);

  public:

   X11Host(Display *display,int screen);

   virtual ~X11Host();

   // msg boxes

   static void CloseApp();

   static void RestoreApp();

   static void AbortMsgBox(StrLen text);

   static void ErrorMsgBox(StrLen text,StrLen title);

   // WinControl
   // create/destroy

   virtual void createMain(Point max_size);

   virtual void createMain(Pane pane,Point max_size);

   virtual void create(Pane pane,Point max_size);

   virtual void create(WindowHost *parent_,Pane pane,Point max_size);

   virtual void destroy();

   // operations

   virtual void setTitle(StrLen title);

   virtual void setMaxSize(Point max_size);

   virtual bool enableUserInput(bool en);

   virtual void display(CmdDisplay cmd_display);

   virtual void show();

   virtual void hide();

   // drawing

   virtual void update();

   virtual void invalidate(Pane pane,unsigned token);

   virtual void invalidate(unsigned token);

   virtual ColorPlane getDrawPlane();

   // keyboard

   virtual void setFocus();

   // mouse

   virtual Point getMousePos();

   virtual void captureMouse();

   virtual void releaseMouse();

   virtual void trackMouseHover();

   virtual void trackMouseHover(MSec time);

   virtual void untrackMouseHover();

   virtual void trackMouseLeave();

   virtual void untrackMouseLeave();

   virtual void setMouseShape(MouseShape mshape);

   // place

   virtual Pane getPlace();

   virtual void setPlace(Pane pane);

   // clipboard

   virtual void textToClipboard(PtrLen<const Char> text);

   virtual void textFromClipboard(Function<void (PtrLen<const Char>)> func);
 };

} // namespace Internal
} // namespace Video
} // namespace CCore

#endif

