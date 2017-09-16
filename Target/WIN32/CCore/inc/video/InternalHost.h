/* InternalHost.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_InternalHost_h
#define CCore_inc_video_InternalHost_h

#include <CCore/inc/PlatformRandom.h>

#include <CCore/inc/video/Picture.h>

#include <CCore/inc/video/InternalUtils.h>

namespace CCore {
namespace Video {
namespace Internal {

/* classes */

class WindowClass;

class WindowPaint;

class WindowsHost;

/* class WindowClass */

class WindowClass : NoCopy
 {
   Win32::Atom atom;
   Sys::ErrorType error;

   Win32::HIcon hIcon;
   Win32::HIcon hIconSm;

  private:

   void regClass();

   static Win32::HIcon CreateIcon(Picture pict,Coord dx,Coord dy);

  public:

   WindowClass();

   ~WindowClass();

   void setIcon(Picture pict);

   Win32::Atom getAtom(const char *format);
 };

/* class WindowPaint */

class WindowPaint : NoCopy
 {
   Win32::HWindow hWnd;
   Win32::PaintData pd;
   Win32::HGDevice hGD;

  public:

   explicit WindowPaint(Win32::HWindow hWnd);

   ~WindowPaint();

   Win32::HGDevice getGD() const { return hGD; }

   Pane getPane() const { return ToPane(pd.rect); }

   bool getEraseFlag() const { return pd.erase_flag; }
 };

/* class WindowsHost */

class WindowsHost : public WindowHost
 {
   Win32::HWindow hWnd = 0 ;
   bool is_main = false ;

   Point origin;

   WindowBuf buf;
   bool buf_dirty = true ;

   unsigned track_flags = 0 ;
   bool track_on = false ;
   unsigned hover_time = 0 ;

   Pane restore;
   bool max_flag = false ;

  private:

   void guardAlive(const char *format);

   void guardDead(const char *format);

   static void GuardMaxSize(const char *format,Point max_size);

   static void GuardPane(const char *format,Pane pane,Point max_size);

   void guardCreate(const char *format,Point max_size);

   void guardCreate(const char *format,Pane pane,Point max_size);

   static Win32::HCursor CursorTable[];

   static Win32::HCursor GetCursor(MouseShape mshape)
    {
     return CursorTable[mshape];
    }

   static WindowClass WindowClassObject;

   static Win32::HWindow HMainWindow;

   static PlatformRandom Random;

  private:

   static VKey ToVKey(Win32::MsgWParam wParam);

   static KeyMod GetKeyMod(bool ext);

   static KeyMod GetKeyMod();

   static MouseKey ToMouseKey(Win32::MsgWParam wParam);

   static Point ToPoint(Win32::MsgLParam lParam);

   static Point ToSize(Win32::MsgLParam lParam);

   static Coord RandomLen(Coord len);

   static Coord RandomPos(Coord len);

   void setTrack();

   void mouseShape(VKey vkey,KeyMod kmod);

   Win32::MsgResult msgProc(Win32::HWindow hWnd_,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam);

   static Win32::MsgResult ObjWndProc(WindowsHost *obj,Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam);

   static Win32::MsgResult WIN32_CALLTYPE WndProc(Win32::HWindow hWnd,Win32::MsgCode message,Win32::MsgWParam wParam,Win32::MsgLParam lParam);

   void reset();

   void do_move(Pane pane);

   friend class WindowClass;

  public:

   WindowsHost();

   virtual ~WindowsHost();

   // msg boxes

   static void AbortMsgBox(StrLen text);

   static void ErrorMsgBox(StrLen text,StrLen title);

   // icons

   static void SetAppIcon(Picture pict);

   // WinControl
   // create/destroy

   virtual void createMain(Point max_size);

   virtual void createMain(Pane pane,Point max_size);

   virtual void create(Pane pane,Point max_size);

   virtual void create(WindowHost *parent,Pane pane,Point max_size);

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

