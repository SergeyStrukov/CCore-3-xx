/* FrameWindow.h */
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

#ifndef CCore_inc_video_FrameWindow_h
#define CCore_inc_video_FrameWindow_h

#include <CCore/inc/video/UserAction.h>
#include <CCore/inc/video/FrameBuf.h>

#include <CCore/inc/MemBase.h>
#include <CCore/inc/TimeScope.h>
#include <CCore/inc/Signal.h>

namespace CCore {
namespace Video {

/* classes */

//enum CmdDisplay;

struct CopyFunction;

struct Desktop;

class InterruptFunction;

class WindowHost;

class FrameWindow;

/* enum CmdDisplay */

enum CmdDisplay : unsigned
 {
  CmdDisplay_Normal,
  CmdDisplay_Minimized,
  CmdDisplay_Maximized,
  CmdDisplay_Restore
 };

const char * GetTextDesc(CmdDisplay cmd_display);

/* struct CopyFunction */

struct CopyFunction : public Funchor
 {
  PtrLen<char> buf;

  // constructors

  explicit CopyFunction(PtrLen<char> buf_) : buf(buf_) {}

  CopyFunction(char *ptr,ulen len) : buf(ptr,len) {}

  // methods

  void copy(StrLen text);

  void cutEOL();

  // functions

  Function<void (StrLen)> function_copy() { return FunctionOf(this,&CopyFunction::copy); }
 };

/* struct Desktop */

struct Desktop
 {
  virtual WindowHost * createHost()=0;

  virtual Point getScreenSize()=0;

  virtual Pane getMaxPane()=0;

  static const unsigned DefaultLim = 100 ;

  virtual bool pump(unsigned lim=DefaultLim)=0;

  virtual void wait(TimeScope time_scope)=0;

  virtual void interrupt()=0; // async
 };

/* class InterruptFunction */

class InterruptFunction : public Function<void (void)>
 {
   static void Call(Handle handle);

  public:

   explicit InterruptFunction(Desktop *desktop) : Function<void (void)>(Call,Handle((void *)desktop)) {}
 };

/* class WindowHost */

class WindowHost : public MemBase_nocopy
 {
  protected:

   FrameWindow *frame = 0 ;
   Point max_size = Null ;
   bool is_alive = false ;
   unsigned token = 0 ;

   friend class FrameWindow;

  public:

   WindowHost() {}

   virtual ~WindowHost() {}

   // props

   bool isAlive() const { return is_alive; }

   bool isDead() const { return !is_alive; }

   Point getMaxSize() const { return max_size; }

   unsigned getToken() const { return token; }

   // create/destroy

   virtual void createMain(Point max_size)=0;

   virtual void createMain(Pane pane,Point max_size)=0; // screen

   virtual void create(Pane pane,Point max_size)=0; // screen

   virtual void create(WindowHost *parent,Pane pane,Point max_size)=0; // screen

   virtual void destroy()=0;

   // operations

   virtual void setTitle(StrLen title)=0;

   virtual void setMaxSize(Point max_size)=0;

   virtual bool enableUserInput(bool en)=0; // return previous

   virtual void display(CmdDisplay cmd_display)=0;

   virtual void show()=0;

   virtual void hide()=0;

   // drawing

   virtual void update()=0;

   virtual void invalidate(Pane pane,unsigned token=0)=0;

   virtual void invalidate(unsigned token=0)=0;

   virtual ColorPlane getDrawPlane()=0;

   // keyboard

   virtual void setFocus()=0;

   // mouse

   virtual Point getMousePos()=0;

   virtual void captureMouse()=0;

   virtual void releaseMouse()=0;

   virtual void trackMouseHover()=0;

   virtual void trackMouseHover(MSec time)=0;

   virtual void untrackMouseHover()=0;

   virtual void trackMouseLeave()=0;

   virtual void untrackMouseLeave()=0;

   virtual void setMouseShape(MouseShape mshape)=0;

   // place

   virtual Pane getPlace()=0; // screen

   virtual void setPlace(Pane pane)=0; // screen

   // clipboard

   virtual void textToClipboard(StrLen text)=0;

   virtual void textFromClipboard(Function<void (StrLen)> func)=0;
 };

/* class FrameWindow */

class FrameWindow : public NoCopyBase<MemBase,UserInput>
 {
  protected:

   Desktop *const desktop;

   WindowHost *const host;

  public:

   explicit FrameWindow(Desktop *desktop_) : desktop(desktop_),host(desktop_->createHost()) { host->frame=this; }

   virtual ~FrameWindow() { delete host; }

   // props

   Desktop * getDesktop() const { return desktop; }

   WindowHost * getHost() const { return host; }

   bool isAlive() const { return host->isAlive(); }

   bool isDead() const { return host->isDead(); }

   Point getScreenSize() const { return desktop->getScreenSize(); }

   // focus

   void grabFocus() { host->setFocus(); }

   // move/resize

   void setMaxSize(Point size)
    {
     host->setMaxSize(size);
    }

   void move(Point delta)
    {
     host->setPlace(host->getPlace()+delta);
    }

   void resize(Point size)
    {
     host->setPlace(Pane(host->getPlace().getBase(),size));
    }

   // destroy

   void destroy()
    {
     dying();

     host->destroy();

     destroyed.assert();
    }

   // base

   virtual void alive()
    {
     // do nothing
    }

   virtual void dying()
    {
     // do nothing
    }

   virtual void dead()
    {
     // do nothing
    }

   virtual void askClose()
    {
     // do nothing
    }

   virtual void setSize(Point size,bool buf_dirty)
    {
     Used(size);
     Used(buf_dirty);

     // do nothing
    }

   virtual void paintDone(unsigned token)
    {
     Used(token);

     // do nothing
    }

   // keyboard

   virtual void gainFocus()
    {
     // do nothing
    }

   virtual void looseFocus()
    {
     // do nothing
    }

   // mouse

   virtual void looseCapture()
    {
     // do nothing
    }

   virtual void setMouseShape(Point point,KeyMod kmod)
    {
     Used(point);
     Used(kmod);

     host->setMouseShape(Mouse_Arrow);
    }

   // signals

   Signal<Point> moved;

   Signal<> destroyed;
 };

} // namespace Video
} // namespace CCore

#endif


