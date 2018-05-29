/* InternalUtils.h */
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

#ifndef CCore_inc_video_InternalUtils_h
#define CCore_inc_video_InternalUtils_h

#include <CCore/inc/video/FrameWindow.h>
#include <CCore/inc/video/Picture.h>

#include <CCore/inc/Tree.h>
#include <CCore/inc/Array.h>

#include <CCore/inc/sys/SysError.h>

#include <CCore/inc/task/TaskEvent.h>

#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <X11/Xcursor/Xcursor.h>
#include <X11/Xutil.h>

#include <locale>

namespace CCore {
namespace Video {
namespace Internal {

/* global Locale */

extern std::locale Locale;

/* SysGuard() */

void SysGuardFailed(const char *format,Sys::ErrorType error=Sys::NonNullError());

inline void SysGuard(const char *format,bool ok)
 {
  if( !ok ) SysGuardFailed(format);
 }

/* SetFuncName() */

void SetFuncName(const char *name);

const char * GetFuncName();

/* Point_cast() */

template <class T1,class T2>
Point Point_cast(T1 x,T2 y) { return Point((Coord)x,(Coord)y); }

/* Pane_cast() */

template <class T1,class T2,class T3,class T4>
Pane Pane_cast(T1 x,T2 y,T3 dx,T4 dy) { return Pane((Coord)x,(Coord)y,(Coord)dx,(Coord)dy); }

/* classes */

struct PrintXStatus;

struct TickEvent;

struct MsgEvent;

class X11KeyMap;

class WindowBuf;

class WindowDispatcher;

class HiddenWindowHost;

class MsgBoxHost;

/* struct PrintXStatus */

struct PrintXStatus
 {
  Display *display;
  Status status;

  PrintXStatus(Display *display_,Status status_) : display(display_),status(status_) {}

  void print(PrinterType &out) const
   {
    char temp[TextBufLen];

    XGetErrorText(display,status,temp,TextBufLen);

    Putobj(out,temp);
   }
 };

/* struct TickEvent */

struct TickEvent
 {
  EventTimeType time;
  EventIdType id;

  uint8 flag;

  enum FlagType
   {
    Entry,
    Leave
   };

  void init(EventTimeType time_,EventIdType id_,FlagType flag_)
   {
    time=time_;
    id=id_;

    flag=flag_;
   }

  static void * Offset_time(void *ptr) { return &(static_cast<TickEvent *>(ptr)->time); }

  static void * Offset_id(void *ptr) { return &(static_cast<TickEvent *>(ptr)->id); }

  static void * Offset_flag(void *ptr) { return &(static_cast<TickEvent *>(ptr)->flag); }

  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* struct MsgEvent */

struct MsgEvent
 {
  EventTimeType time;
  EventIdType id;

  uint32 type;
  uint8 flag;

  enum FlagType
   {
    Entry,
    Leave,
    Stop
   };

  void init(EventTimeType time_,EventIdType id_,int type_,FlagType flag_)
   {
    time=time_;
    id=id_;

    type=type_;
    flag=flag_;
   }

  static void * Offset_time(void *ptr) { return &(static_cast<MsgEvent *>(ptr)->time); }

  static void * Offset_id(void *ptr) { return &(static_cast<MsgEvent *>(ptr)->id); }

  static void * Offset_type(void *ptr) { return &(static_cast<MsgEvent *>(ptr)->type); }

  static void * Offset_flag(void *ptr) { return &(static_cast<MsgEvent *>(ptr)->flag); }

  static void Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc);
 };

/* class X11KeyMap */

class X11KeyMap : NoCopy
 {
   bool ok = false ;

   int keycode_min = 0 ;
   int keycode_max = 0 ;

   int page_count = 0 ;
   KeySym *table = 0 ;

  public:

   explicit X11KeyMap(Display *display);

   ~X11KeyMap();

   bool noMap() const { return !ok; }

   void updateMap(Display *display);

   // get

   MouseKey getMKey(unsigned state) const;

   KeyMod getKMod(unsigned state) const;

   // mapToVKey

   static bool IsKP(KeySym ksym);

   KeySym map(unsigned state,unsigned keycode) const;

   struct VKeyExt
    {
     VKey vkey;
     bool ext;

     VKeyExt(VKey vkey_,bool ext_=false) : vkey(vkey_),ext(ext_) {}
    };

   struct Ext : VKeyExt
    {
     Ext(VKey vkey) : VKeyExt(vkey,true) {}
    };

   static VKeyExt MapToVKey(KeySym ksym);

   VKeyExt mapToVKey(unsigned state,unsigned keycode) const;

   // mapToChar

   struct VKeyExtChar : VKeyExt
    {
     Char ch;

     VKeyExtChar(VKeyExt vkeyext,Char ch_) : VKeyExt(vkeyext),ch(ch_) {}
    };

   static uint32 MapToUnicode(KeySym ksym);

   static Char MapToChar(KeySym ksym);

   static bool IsChar(KeySym ksym);

   VKeyExtChar mapToChar(unsigned state,unsigned keycode) const;
 };

/* class WindowBuf */

class WindowBuf : NoCopy
 {
   void *mem = 0 ;
   Point size;
   XImage image;

  public:

   WindowBuf();

   ~WindowBuf();

   Point getSize() const { return size; }

   void * getMem() const { return mem; }

   ColorPlane getPlane() const { return ColorPlane(mem,size.x,size.y,size.x*4u); }

   void setSize(Point new_size);

   void draw(Display *display,Window window,GC gc,Pane pane);
 };

/* class WindowDispatcher */

class WindowDispatcher : NoCopy
 {
   TreeLink<WindowDispatcher,Window> link;

   using Algo = TreeLink<WindowDispatcher,Window>::RadixAlgo<&WindowDispatcher::link> ;

  private:

   virtual void handle(XEvent &event)=0;

   virtual void ping()=0;

  private:

   static bool StopEventFlag;

   static Algo::Root MapRoot;

   static WindowDispatcher * Find(Window window);

   static void Ping(WindowDispatcher *obj);

  public:

   WindowDispatcher();

   ~WindowDispatcher();

   static void Stop() { StopEventFlag=true; }

   static void AddToMap(Window window,WindowDispatcher *obj);

   static void DelFromMap(WindowDispatcher *obj);

   static bool DispatchEvent(XEvent &event);

   static bool Ping();
 };

/* class HiddenWindowHost */

class HiddenWindowHost : WindowDispatcher
 {
   Display *disp;
   int screen;

   Window window = None ;

   DynArray<uint32> icon;

   Atom net_wm_icon = None ;
   Atom net_wm_state = None ;
   Atom net_wm_state_hidden = None ;
   Atom wm_protocols = None ;
   Atom wm_delete_window = None ;

  private:

   void testState(const long *data,unsigned long count);

   void testState();

   virtual void handle(XEvent &event);

   virtual void ping();

   Point getIconSize();

   void setIcon();

   void setProtocols();

  public:

   HiddenWindowHost();

   ~HiddenWindowHost();

   void create();

   void destroy();

   void setTitle(StrLen str);

   void setIcon(Picture pict);

   void iconify();
 };

/* global HiddenWindow */

extern HiddenWindowHost HiddenWindow;

/* class MsgBoxHost */

class MsgBoxHost : NoCopy
 {
   Display *display = 0 ;
   int screen = 0 ;

   Atom wm_protocols = None ;
   Atom wm_delete_window = None ;
   KeyCode esc_keycode = 0 ;

   XFontStruct *font = 0 ;

   bool run_flag = true ;
   Window window = None ;
   GC gc = None ;

   StrLen text;
   bool has_focus = false ;

  private:

   Point getSize();

   void setTitle(StrLen str);

   void setProtocols();

   void setIcon(const long *icon,ulen icon_len);

   void setIcon();

   unsigned long getColor(const char *name);

   bool create(StrLen title);

   void drawText(int x,int y,StrLen str);

   void draw(XFontStruct *font);

   void draw();

   void redraw();

   void handle(XEvent &event);

   void run();

   void destroy();

  public:

   MsgBoxHost();

   ~MsgBoxHost();

   void show(StrLen title,StrLen text);
 };

} // namespace Internal
} // namespace Video
} // namespace CCore

#endif

