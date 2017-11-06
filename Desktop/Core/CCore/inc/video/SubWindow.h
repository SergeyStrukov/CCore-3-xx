/* SubWindow.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
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

#ifndef CCore_inc_video_SubWindow_h
#define CCore_inc_video_SubWindow_h

#include <CCore/inc/video/FrameWindow.h>
#include <CCore/inc/video/DrawBuf.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/InterfaceHost.h>
#include <CCore/inc/List.h>

namespace CCore {
namespace Video {

/* consts */

enum FocusType
 {
  NoFocus = 0,
  FocusOk,
  FocusTab
 };

/* classes */

struct SubWindowHost;

struct AliveControl;

class SubWindow;

class WindowList;

class ComboWindow;

/* struct SubWindowHost */

struct SubWindowHost
 {
  // abstract

  virtual FrameWindow * getFrame()=0;

  virtual Point getScreenOrigin()=0;

  virtual void redraw(Pane pane)=0; // relative host coords

  virtual void setFocus(SubWindow *sub_win)=0;

  virtual void captureMouse(SubWindow *sub_win)=0;

  virtual void releaseMouse(SubWindow *sub_win)=0;

  // helpers

  Desktop * getFrameDesktop() { return getFrame()->getDesktop(); }

  WindowHost * getFrameHost() { return getFrame()->getHost(); }
 };

/* struct AliveControl */

struct AliveControl
 {
  static const Unid TypeUnid;

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

  virtual bool askDestroy()
   {
    return true;
   }

  static AliveControl Default;
 };

/* class SubWindow */

class SubWindow : public NoCopyBase<MemBase,UserInput,InterfaceHost>
 {
   DLink<SubWindow> link;
   WindowList *list = 0 ;

   Pane place; // relative host coords

   SubWindowHost &host;

   const RefVal<DefString> * hint_text = 0 ;

   friend class SubWindowHost;
   friend class WindowList;

  public:

   static const Unid TypeUnid;

   explicit SubWindow(SubWindowHost &host_) : host(host_) {}

   virtual ~SubWindow();

   AliveControl * getAliveControl(); // non-null

   // methods

   bool isListed() const { return list!=0; }

   Pane getPlace() const { return place; }

   Point getSize() const { return place.getSize(); }

   FrameWindow * getFrame() const { return host.getFrame(); }

   WindowHost * getFrameHost() const { return host.getFrameHost(); }

   Desktop * getFrameDesktop() const { return host.getFrameDesktop(); }

   Point getScreenOrigin() const { return host.getScreenOrigin()+place.getBase(); }

   template <class T>
   T toScreen(T obj) const { return obj+getScreenOrigin(); }

   template <class T>
   T fromScreen(T obj) const { return obj-getScreenOrigin(); }

   void setPlace(Pane place_)
    {
     place=place_;

     layout();
    }

   void redraw() { host.redraw(place); }

   void redraw(Pane pane) { host.redraw(Inner(place,pane)); }

   void setFocus() { host.setFocus(this); }

   void captureMouse() { host.captureMouse(this); }

   void releaseMouse() { host.releaseMouse(this); }

   void disableFrameReact() { getFrame()->disableReact(); }

   void enableFrameReact() { getFrame()->enableReact(); }

   void askFrameClose() { getFrame()->askClose(); }

   void destroyFrame() { getFrame()->destroy(); }

   // hint

   void bindHint(const RefVal<DefString> &str)
    {
     hint_text=&str;
    }

   virtual Hint getHint(Point point) const // relative host coords
    {
     if( hint_text && place.contains(point) ) return Hint(place,hint_text->get());

     return Nothing;
    }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     Used(size);

     return true;
    }

   virtual bool hasGoodSize() const
    {
     return isGoodSize(getSize());
    }

   virtual void layout()
    {
     // do nothing
    }

   virtual void draw(DrawBuf buf,bool drag_active) const
    {
     buf.erase(drag_active?Gray:Black);
    }

   virtual void draw(DrawBuf buf,Pane pane,bool drag_active) const
    {
     Used(pane);

     draw(buf,drag_active);
    }

   // base

   virtual void open()
    {
     // do nothing
    }

   virtual void close()
    {
     // do nothing
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return FocusOk;
    }

   virtual void gainFocus()
    {
     // do nothing
    }

   virtual void looseFocus()
    {
     // do nothing
    }

   // tab focus

   virtual void topTabFocus()
    {
     // do nothing
    }

   virtual bool nextTabFocus()
    {
     return false;
    }

   virtual void bottomTabFocus()
    {
     // do nothing
    }

   virtual bool prevTabFocus()
    {
     return false;
    }

   // mouse

   virtual void looseCapture()
    {
     // do nothing
    }

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const
    {
     Used(point);
     Used(kmod);

     return Mouse_Arrow;
    }

   // forward

   void forward_draw(const DrawBuf &buf,bool drag_active) const
    {
     DrawBuf sub_buf=buf.cutRebase(place);

     if( +sub_buf ) try { draw(sub_buf,drag_active); } catch(...) {}
    }

   void forward_draw(const DrawBuf &buf,Pane pane,bool drag_active) const
    {
     DrawBuf sub_buf=buf.cutRebase(place);

     pane=Inf(place,pane);

     if( +sub_buf && +pane ) try { draw(sub_buf,pane-place.getBase(),drag_active); } catch(...) {}
    }

   void forward_react(UserAction action)
    {
     action.rebase(place.getBase());

     react(action);
    }

   struct Forwarder : UserInput
    {
     SubWindow *obj;

     explicit Forwarder(SubWindow *obj_) : obj(obj_) {}

     virtual void react(UserAction action) final
      {
       obj->forward_react(action);
      }
    };

   Forwarder forward()
    {
     return Forwarder(this);
    }

   MouseShape forward_getMouseShape(Point point,KeyMod kmod) const { return getMouseShape(point-place.getBase(),kmod); }
 };

/* class WindowList */

class WindowList : public NoCopyBase<SubWindowHost,UserInput>
 {
   SubWindow &parent;

   SubWindow *focus = 0 ;
   SubWindow *capture = 0 ;
   SubWindow *enter = 0 ;

   bool has_focus = false ;
   bool is_opened = false ;

   bool enable_tab = false ;
   bool enable_click = false ;

   using Algo = DLink<SubWindow>::LinearAlgo<&SubWindow::link> ;

   Algo::FirstLast list;

  private:

   SubWindow * find(Point point) const;

   SubWindow * pick(Point point) const;

   SubWindow * next(SubWindow *sub_win);

   SubWindow * prev(SubWindow *sub_win);

  public:

   explicit WindowList(SubWindow &parent_) : parent(parent_) {}

   ~WindowList();

   // methods

   bool insTop(SubWindow *sub_win);

   bool insBottom(SubWindow *sub_win);

   bool del(SubWindow *sub_win);

   void moveTop(SubWindow *sub_win);

   void moveBottom(SubWindow *sub_win);

   void insAfter(SubWindow *that,SubWindow *sub_win);

   void insBefore(SubWindow *that,SubWindow *sub_win);


   bool insTop(SubWindow &sub_win) { return insTop(&sub_win); }

   bool insBottom(SubWindow &sub_win) { return insBottom(&sub_win); }

   bool del(SubWindow &sub_win) { return del(&sub_win); }

   void moveTop(SubWindow &sub_win) { moveTop(&sub_win); }

   void moveBottom(SubWindow &sub_win) { moveBottom(&sub_win); }

   void insAfter(SubWindow &that,SubWindow &sub_win) { insAfter(&that,&sub_win); }

   void insBefore(SubWindow &that,SubWindow &sub_win) { insBefore(&that,&sub_win); }


   void delAll();

   // multiple insert

   template <class ... TT>
   void insTop(SubWindow *sub_win,TT * ... tt)
    {
     insTop(tt...);

     insTop(sub_win);
    }

   template <class ... TT>
   void insTop(SubWindow &sub_win,TT & ... tt)
    {
     insTop(&sub_win,&tt...);
    }

   template <class ... TT>
   void insBottom(SubWindow *sub_win,TT * ... tt)
    {
     insBottom(sub_win);

     insBottom(tt...);
    }

   template <class ... TT>
   void insBottom(SubWindow &sub_win,TT & ... tt)
    {
     insBottom(&sub_win,&tt...);
    }

   template <class ... TT>
   void insAfter(SubWindow *that,SubWindow *sub_win,TT * ... tt)
    {
     insAfter(that,sub_win);

     insAfter(sub_win,tt...);
    }

   template <class ... TT>
   void insAfter(SubWindow &that,TT & ... tt)
    {
     insAfter(&that,&tt...);
    }

   template <class ... TT>
   void insBefore(SubWindow *that,SubWindow *sub_win1,SubWindow *sub_win2,TT * ... tt)
    {
     insBefore(that,sub_win2,tt...);

     insBefore(sub_win2,sub_win1);
    }

   template <class ... TT>
   void insBefore(SubWindow &that,TT & ... tt)
    {
     insBefore(&that,&tt...);
    }

   // multiple delete

   template <class ... TT>
   void del(TT * ... tt) requires( sizeof ... (TT) > 1 )
    {
     ( del(tt) , ... );
    }

   template <class ... TT>
   void del(TT & ... tt) requires( sizeof ... (TT) > 1 )
    {
     ( del(tt) , ... );
    }

   // focus

   SubWindow * getFocus() const { return has_focus?focus:0; }

   void focusTop();

   void focusBottom();

   void focusNext();

   void focusPrev();

   void focusOn(Point point);

   void enableTabFocus(bool enable_tab_=true) { enable_tab=enable_tab_; }

   void enableClickFocus(bool enable_click_=true) { enable_click=enable_click_; }

   // hint

   Hint getHint(Point point) const;

   // draw

   bool hasGoodSize() const;

   void draw(const DrawBuf &buf,bool drag_active) const;

   void draw(const DrawBuf &buf,Pane pane,bool drag_active) const;

   // SubWindowHost

   virtual FrameWindow * getFrame();

   virtual Point getScreenOrigin();

   virtual void redraw(Pane pane);

   virtual void setFocus(SubWindow *sub_win);

   virtual void captureMouse(SubWindow *sub_win);

   virtual void releaseMouse(SubWindow *sub_win);

   // base

   void open() noexcept;

   void close() noexcept;

   // keyboard

   void gainFocus();

   void looseFocus();

   // tab focus

   void topTabFocus();

   bool nextTabFocus();

   void bottomTabFocus();

   bool prevTabFocus();

   // mouse

   void looseCapture();

   MouseShape getMouseShape(Point point,KeyMod kmod,MouseShape def_shape=Mouse_Arrow) const;

   // user input

   void react(UserAction action,FuncArgType<UserAction> func);

   bool react_Keyboard(UserAction action);

   void react_Keyboard(UserAction action,FuncArgType<UserAction> func);

   bool react_Mouse(UserAction action);

   void react_Mouse(UserAction action,FuncArgType<UserAction> func);

   bool react_Move(Point point,MouseKey mkey);

   void react_Move(Point point,MouseKey mkey,FuncArgType<UserAction> func);

   void react_Leave(FuncArgType<UserAction> func);

   virtual void react(UserAction action);
 };

template <FuncArgType<UserAction> Func>
void WindowList::react(UserAction action,Func func)
 {
  if( action.fromKeyboard() )
    {
     react_Keyboard(action,func);
    }
  else
    {
     struct React
      {
       WindowList *list;
       const Func &func;

       void react_Move(Point point,MouseKey mkey)
        {
         list->react_Move(point,mkey,func);
        }

       void react_Leave()
        {
         list->react_Leave(func);
        }

       void react_other(UserAction action)
        {
         list->react_Mouse(action,func);
        }
      };

     React obj{this,func};

     action.dispatch(obj);
    }
 }

void WindowList::react_Keyboard(UserAction action,FuncArgType<UserAction> func)
 {
  if( !react_Keyboard(action) ) func(action);
 }

void WindowList::react_Mouse(UserAction action,FuncArgType<UserAction> func)
 {
  if( !react_Mouse(action) ) func(action);
 }

void WindowList::react_Move(Point point,MouseKey mkey,FuncArgType<UserAction> func)
 {
  if( !react_Move(point,mkey) ) UserInputFunc(func).put_Move(point,mkey);
 }

void WindowList::react_Leave(FuncArgType<UserAction> func)
 {
  if( enter )
    {
     Replace_null(enter)->put_Leave();
    }
  else
    {
     UserInputFunc(func).put_Leave();
    }
 }

/* class SomeWindow */

#if 0

class SomeWindow : public SubWindow
 {
   WindowList wlist;

  public:

   explicit SomeWindow(SubWindowHost &host);

   virtual ~SomeWindow();

   // hint

   virtual Hint getHint(Point point) const;

   // drawing

   virtual bool hasGoodSize() const;

   virtual void layout();

   virtual void draw(DrawBuf buf,bool drag_active) const;

   virtual void draw(DrawBuf buf,Pane pane,bool drag_active) const;

   // base

   virtual void open();

   virtual void close();

   // keyboard

   virtual FocusType askFocus() const;

   virtual void gainFocus();

   virtual void looseFocus();

   // tab focus

   virtual void topTabFocus();

   virtual bool nextTabFocus();

   virtual void bottomTabFocus();

   virtual bool prevTabFocus();

   // mouse

   virtual void looseCapture();

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const;

   // user input

   virtual void react(UserAction action);
 };

SomeWindow::SomeWindow(SubWindowHost &host)
 : SubWindow(host),
   wlist(*this)
 {
  // TODO
 }

SomeWindow::~SomeWindow()
 {
 }

 // hint

Hint SomeWindow::getHint(Point point) const
 {
  return wlist.getHint(point);
 }

 // drawing

bool SomeWindow::hasGoodSize() const
 {
  // TODO

  return wlist.hasGoodSize();
 }

void SomeWindow::layout()
 {
  // TODO
 }

void SomeWindow::draw(DrawBuf buf,bool drag_active) const
 {
  // TODO

  wlist.draw(buf,drag_active);
 }

void SomeWindow::draw(DrawBuf buf,Pane pane,bool drag_active) const
 {
  // TODO

  wlist.draw(buf,pane,drag_active);
 }

 // base

void SomeWindow::open()
 {
  // TODO

  wlist.open();
 }

void SomeWindow::close()
 {
  // TODO

  wlist.close();
 }

 // keyboard

FocusType SomeWindow::askFocus() const
 {
  return FocusTab;
 }

void SomeWindow::gainFocus()
 {
  // TODO

  wlist.gainFocus();
 }

void SomeWindow::looseFocus()
 {
  // TODO

  wlist.looseFocus();
 }

 // tab focus

void SomeWindow::topTabFocus()
 {
  wlist.topTabFocus();
 }

bool SomeWindow::nextTabFocus()
 {
  return wlist.nextTabFocus();
 }

void SomeWindow::bottomTabFocus()
 {
  wlist.bottomTabFocus();
 }

bool SomeWindow::prevTabFocus()
 {
  return wlist.prevTabFocus();
 }

 // mouse

void SomeWindow::looseCapture()
 {
  // TODO

  wlist.looseCapture();
 }

MouseShape SomeWindow::getMouseShape(Point point,KeyMod kmod) const
 {
  // TODO

  return wlist.getMouseShape(point,kmod,Mouse_Arrow);
 }

 // user input

void SomeWindow::react(UserAction action)
 {
  action.dispatch(*this, [this] (UserAction action) { wlist.react(action); } );

  /* OR */

  wlist.react(action, [this] (UserAction action) { action.dispatch(*this); } );
 }

#endif

/* class ComboWindow */

class ComboWindow : public SubWindow
 {
  protected:

   WindowList wlist;

  protected:

   explicit ComboWindow(SubWindowHost &host)
    : SubWindow(host),
      wlist(*this)
    {
     wlist.enableTabFocus();
     wlist.enableClickFocus();
    }

   virtual ~ComboWindow()
    {
    }

  public:

   // hint

   virtual Hint getHint(Point point) const
    {
     return wlist.getHint(point);
    }

   // drawing

   virtual bool hasGoodSize() const
    {
     return wlist.hasGoodSize();
    }

   virtual void drawBack(DrawBuf buf,bool drag_active) const
    {
     Used(buf);
     Used(drag_active);
    }

   virtual void drawBack(DrawBuf buf,Pane pane,bool drag_active) const
    {
     Used(pane);

     drawBack(buf,drag_active);
    }

   virtual void draw(DrawBuf buf,bool drag_active) const
    {
     drawBack(buf,drag_active);

     wlist.draw(buf,drag_active);
    }

   virtual void draw(DrawBuf buf,Pane pane,bool drag_active) const
    {
     drawBack(buf,pane,drag_active);

     wlist.draw(buf,pane,drag_active);
    }

   // base

   virtual void open()
    {
     wlist.open();

     wlist.focusTop();
    }

   virtual void close()
    {
     wlist.close();
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return FocusTab;
    }

   virtual void gainFocus()
    {
     wlist.gainFocus();
    }

   virtual void looseFocus()
    {
     wlist.looseFocus();
    }

   // tab focus

   virtual void topTabFocus()
    {
     wlist.topTabFocus();
    }

   virtual bool nextTabFocus()
    {
     return wlist.nextTabFocus();
    }

   virtual void bottomTabFocus()
    {
     wlist.bottomTabFocus();
    }

   virtual bool prevTabFocus()
    {
     return wlist.prevTabFocus();
    }

   // mouse

   virtual void looseCapture()
    {
     wlist.looseCapture();
    }

   virtual MouseShape getMouseShape(Point point,KeyMod kmod) const
    {
     return wlist.getMouseShape(point,kmod);
    }

   // user input

   virtual void react(UserAction action)
    {
     wlist.react(action);
    }
 };

} // namespace Video
} // namespace CCore

#endif



