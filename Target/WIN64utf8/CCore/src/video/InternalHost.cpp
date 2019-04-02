/* InternalHost.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/InternalHost.h>

#include <CCore/inc/sys/SysUtf8.h>

#include <CCore/inc/sys/SysFileInternal.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {
namespace Internal {

/* class WindowClass */

void WindowClass::regClass()
 {
  Win64::HModule hModule=(Win64::HModule)Win64::GetModuleHandleW(0);

  if( hModule==0 )
    {
     error=Sys::NonNullError();

     return;
    }

  Win64::WindowClass wndcls;

  wndcls.cb=sizeof wndcls;
  wndcls.class_extra=0;
  wndcls.window_extra=sizeof (Win64::UPtrType);

  wndcls.hModule=hModule;

  wndcls.style=Win64::ClassStyle_VRedraw|Win64::ClassStyle_HRedraw|Win64::ClassStyle_DClick;

  wndcls.hCursor=WindowsHost::GetCursor(Mouse_Arrow);

  wndcls.hBrush=0;
  wndcls.hIcon=hIcon;
  wndcls.hIconSm=hIconSm;
  wndcls.menu_res=0;

  Sys::WCharString<> temp("9613CA28BE7A78F0-2DD3FC07C7330F49-WindowsHost"_c);

  wndcls.class_name=temp;
  wndcls.wnd_proc=WindowsHost::WndProc;

  atom=Win64::RegisterClassExW(&wndcls);

  if( atom==0 )
    {
     error=Sys::NonNullError();
    }
  else
    {
     error=Sys::NoError;
    }
 }

Win64::HIcon WindowClass::CreateIcon(Picture pict,Coord dx,Coord dy)
 {
  const char *format="CCore::Video::Internal::WindowsHost::WindowClass::CreateIcon(...) : #;";

  Win64::IconInfo info{};

  WindowBitmap mask_bmp({dx,dy});
  WindowBitmap bmp({dx,dy});
  DesktopColor ground=pict->defaultGround();

  DrawBuf color_buf(bmp.getPlane());

  color_buf.erase(ground);

  pict->draw(color_buf,dx,dy);

  DrawBuf mask_buf(mask_bmp.getPlane());

  mask_buf.erase(Black);

  info.icon_flag=true;
  info.bmpMask=mask_bmp.getHandle();
  info.bmpColor=bmp.getHandle();

  auto ret=Win64::CreateIconIndirect(&info);

  SysGuard(format,ret!=0);

  return ret;
 }

WindowClass::WindowClass()
 : atom(0),error(Sys::NoError),hIcon(0),hIconSm(0)
 {
 }

WindowClass::~WindowClass()
 {
  if( hIcon ) Win64::DestroyIcon(hIcon);
  if( hIconSm ) Win64::DestroyIcon(hIconSm);
 }

void WindowClass::setIcon(Picture pict)
 {
  if( !hIcon )
    {
     Coord dx=Coord(Win64::GetSystemMetrics(Win64::SysMetric_DXIcon));
     Coord dy=Coord(Win64::GetSystemMetrics(Win64::SysMetric_DYIcon));

     hIcon=CreateIcon(pict,dx,dy);
    }

  if( !hIconSm )
    {
     Coord dx=Coord(Win64::GetSystemMetrics(Win64::SysMetric_DXIconSm));
     Coord dy=Coord(Win64::GetSystemMetrics(Win64::SysMetric_DYIconSm));

     hIconSm=CreateIcon(pict,dx,dy);
    }
 }

Win64::Atom WindowClass::getAtom(const char *format)
 {
  if( error ) SysGuardFailed(format,error);

  if( atom!=0 ) return atom;

  regClass();

  if( error ) SysGuardFailed(format,error);

  return atom;
 }

/* class WindowPaint */

WindowPaint::WindowPaint(Win64::HWindow hWnd_)
 {
  const char *format="CCore::Video::Internal::WindowsHost::WindowPaint::WindowPaint(...) : #;";

  if( hWnd_==0 )
    {
     Printf(Exception,format,"null hWnd");
    }

  hWnd=hWnd_;

  hGD=Win64::BeginPaint(hWnd_,&pd);

  SysGuard(format,hGD!=0);
 }

WindowPaint::~WindowPaint()
 {
  Win64::EndPaint(hWnd,&pd);
 }

/* class WindowsHost */

Win64::HCursor WindowsHost::CursorTable[]=
 {
  0,
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_Arrow)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_IBeam)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_Wait)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_Cross)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_Hand)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_No)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_Help)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_SizeLeftRight)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_SizeUpDown)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_SizeUpLeft)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_SizeUpRight)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_SizeAll)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_UpArrow)),
  Win64::LoadCursorW(0,Win64::MakeIntResource(Win64::SysCursor_AppStarting))
 };

WindowClass WindowsHost::WindowClassObject CCORE_INITPRI_3 ;

Win64::HWindow WindowsHost::HMainWindow=0;

PlatformRandom WindowsHost::Random CCORE_INITPRI_3 ;

void WindowsHost::guardAlive(const char *format)
 {
  if( hWnd==0 )
    {
     Printf(Exception,format,"window is dead");
    }
 }

void WindowsHost::guardDead(const char *format)
 {
  if( hWnd!=0 )
    {
     Printf(Exception,format,"window is alive");
    }
 }

void WindowsHost::GuardMaxSize(const char *format,Point max_size)
 {
  if( max_size<=Null )
    {
     Printf(Exception,format,"bad max_size");
    }
 }

void WindowsHost::GuardPane(const char *format,Pane pane,Point max_size)
 {
  if( !(pane.getSize()<=max_size) )
    {
     Printf(Exception,format,"bad pane size");
    }
 }

void WindowsHost::guardCreate(const char *format,Point max_size)
 {
  guardDead(format);

  GuardMaxSize(format,max_size);
 }

void WindowsHost::guardCreate(const char *format,Pane pane,Point max_size)
 {
  guardDead(format);

  GuardMaxSize(format,max_size);

  GuardPane(format,pane,max_size);
 }

VKey WindowsHost::ToVKey(Win64::MsgWParam wParam)
 {
  switch( wParam )
    {
     case Win64::VK_Escape    : return VKey_Esc;
     case Win64::VK_F1        : return VKey_F1;
     case Win64::VK_F2        : return VKey_F2;
     case Win64::VK_F3        : return VKey_F3;
     case Win64::VK_F4        : return VKey_F4;
     case Win64::VK_F5        : return VKey_F5;
     case Win64::VK_F6        : return VKey_F6;
     case Win64::VK_F7        : return VKey_F7;
     case Win64::VK_F8        : return VKey_F8;
     case Win64::VK_F9        : return VKey_F9;
     case Win64::VK_F10       : return VKey_F10;
     case Win64::VK_F11       : return VKey_F11;
     case Win64::VK_F12       : return VKey_F12;

     case Win64::VK_Tilda     : return VKey_Tilda;

     case '1'                 : return VKey_1;
     case '2'                 : return VKey_2;
     case '3'                 : return VKey_3;
     case '4'                 : return VKey_4;
     case '5'                 : return VKey_5;
     case '6'                 : return VKey_6;
     case '7'                 : return VKey_7;
     case '8'                 : return VKey_8;
     case '9'                 : return VKey_9;
     case '0'                 : return VKey_0;

     case Win64::VK_Minus     : return VKey_Minus;
     case Win64::VK_Plus      : return VKey_Equal;
     case Win64::VK_BackSlash : return VKey_BackSlash;
     case Win64::VK_Back      : return VKey_BackSpace;
     case Win64::VK_Tab       : return VKey_Tab;

     case 'Q'                 : return VKey_q;
     case 'W'                 : return VKey_w;
     case 'E'                 : return VKey_e;
     case 'R'                 : return VKey_r;
     case 'T'                 : return VKey_t;
     case 'Y'                 : return VKey_y;
     case 'U'                 : return VKey_u;
     case 'I'                 : return VKey_i;
     case 'O'                 : return VKey_o;
     case 'P'                 : return VKey_p;

     case Win64::VK_OBracket  : return VKey_OpenBracket;
     case Win64::VK_CBracket  : return VKey_CloseBracket;
     case Win64::VK_Return    : return VKey_Enter;

     case Win64::VK_CapsLock  : return VKey_CapsLock;

     case 'A'                 : return VKey_a;
     case 'S'                 : return VKey_s;
     case 'D'                 : return VKey_d;
     case 'F'                 : return VKey_f;
     case 'G'                 : return VKey_g;
     case 'H'                 : return VKey_h;
     case 'J'                 : return VKey_j;
     case 'K'                 : return VKey_k;
     case 'L'                 : return VKey_l;

     case Win64::VK_Colon     : return VKey_Semicolon;
     case Win64::VK_Quote     : return VKey_Quote;

     case Win64::VK_Shift     : return VKey_Shift;

     case 'Z'                 : return VKey_z;
     case 'X'                 : return VKey_x;
     case 'C'                 : return VKey_c;
     case 'V'                 : return VKey_v;
     case 'B'                 : return VKey_b;
     case 'N'                 : return VKey_n;
     case 'M'                 : return VKey_m;

     case Win64::VK_Comma     : return VKey_Comma;
     case Win64::VK_Period    : return VKey_Period;
     case Win64::VK_Slash     : return VKey_Slash;

     case Win64::VK_Control   : return VKey_Ctrl;
     case Win64::VK_Alt       : return VKey_Alt;

     case Win64::VK_Space     : return VKey_Space;

     case Win64::VK_Scroll    : return VKey_ScrollLock;
     case Win64::VK_Pause     : return VKey_Pause;

     case Win64::VK_Insert    : return VKey_Insert;
     case Win64::VK_Home      : return VKey_Home;
     case Win64::VK_PgUp      : return VKey_PageUp;
     case Win64::VK_Delete    : return VKey_Delete;
     case Win64::VK_End       : return VKey_End;
     case Win64::VK_PgDown    : return VKey_PageDown;

     case Win64::VK_Up        : return VKey_Up;
     case Win64::VK_Left      : return VKey_Left;
     case Win64::VK_Down      : return VKey_Down;
     case Win64::VK_Right     : return VKey_Right;

     case Win64::VK_NumLock   : return VKey_NumLock;
     case Win64::VK_Div       : return VKey_NumSlash;
     case Win64::VK_Mul       : return VKey_NumAsterisk;
     case Win64::VK_Sub       : return VKey_NumMinus;
     case Win64::VK_Add       : return VKey_NumPlus;

     case Win64::VK_Numpad7   : return VKey_Num7;
     case Win64::VK_Numpad8   : return VKey_Num8;
     case Win64::VK_Numpad9   : return VKey_Num9;
     case Win64::VK_Numpad4   : return VKey_Num4;
     case Win64::VK_Numpad5   : return VKey_Num5;
     case Win64::VK_Numpad6   : return VKey_Num6;
     case Win64::VK_Numpad1   : return VKey_Num1;
     case Win64::VK_Numpad2   : return VKey_Num2;
     case Win64::VK_Numpad3   : return VKey_Num3;

     case Win64::VK_Numpad0   : return VKey_NumIns;
     case Win64::VK_Decimal   : return VKey_NumDel;

     default: return VKey_Null;
    }
 }

KeyMod WindowsHost::GetKeyMod(bool ext)
 {
  KeyMod kmod=KeyMod_Null;

  if( ext ) kmod|=KeyMod_Ext;

  if( Win64::GetKeyState(Win64::VK_Shift)&Win64::KeyStateDown ) kmod|=KeyMod_Shift;

  if( Win64::GetKeyState(Win64::VK_Control)&Win64::KeyStateDown ) kmod|=KeyMod_Ctrl;

  if( Win64::GetKeyState(Win64::VK_CapsLock)&Win64::KeyStateToggle ) kmod|=KeyMod_CapsLock;

  if( Win64::GetKeyState(Win64::VK_NumLock)&Win64::KeyStateToggle ) kmod|=KeyMod_NumLock;

  if( Win64::GetKeyState(Win64::VK_Scroll)&Win64::KeyStateToggle ) kmod|=KeyMod_ScrollLock;

  return kmod;
 }

KeyMod WindowsHost::GetKeyMod()
 {
  KeyMod kmod=KeyMod_Null;

  if( Win64::GetKeyState(Win64::VK_Shift)&Win64::KeyStateDown ) kmod|=KeyMod_Shift;

  if( Win64::GetKeyState(Win64::VK_Control)&Win64::KeyStateDown ) kmod|=KeyMod_Ctrl;

  if( Win64::GetKeyState(Win64::VK_Alt)&Win64::KeyStateDown ) kmod|=KeyMod_Alt;

  if( Win64::GetKeyState(Win64::VK_CapsLock)&Win64::KeyStateToggle ) kmod|=KeyMod_CapsLock;

  if( Win64::GetKeyState(Win64::VK_NumLock)&Win64::KeyStateToggle ) kmod|=KeyMod_NumLock;

  if( Win64::GetKeyState(Win64::VK_Scroll)&Win64::KeyStateToggle ) kmod|=KeyMod_ScrollLock;

  return kmod;
 }

MouseKey WindowsHost::ToMouseKey(Win64::MsgWParam wParam)
 {
  MouseKey mkey=MouseKey_Null;

  if( wParam&Win64::MouseKey_Left ) mkey|=MouseKey_Left;

  if( wParam&Win64::MouseKey_Right ) mkey|=MouseKey_Right;

  if( wParam&Win64::MouseKey_Shift ) mkey|=MouseKey_Shift;

  if( wParam&Win64::MouseKey_Control ) mkey|=MouseKey_Ctrl;

  if( Win64::GetKeyState(Win64::VK_Alt)&Win64::KeyStateDown ) mkey|=MouseKey_Alt;

  return mkey;
 }

Point WindowsHost::ToPoint(Win64::MsgLParam lParam)
 {
  return Point((Coord)Win64::SLoWord(lParam),(Coord)Win64::SHiWord(lParam));
 }

Point WindowsHost::ToSize(Win64::MsgLParam lParam)
 {
  return Point((Coord)Win64::LoWord(lParam),(Coord)Win64::HiWord(lParam));
 }

Coord WindowsHost::RandomLen(Coord len)
 {
  int percent=Random.select(128);

  return Coord( (len/2)+((len/4)*percent)/128 );
 }

Coord WindowsHost::RandomPos(Coord len)
 {
  int percent=Random.select(128);

  return Coord( (len*percent)/128 );
 }

void WindowsHost::setTrack()
 {
  const char *format="CCore::Video::Internal::WindowsHost::setTrack() : #;";

  Win64::TrackMouseDesc desc;

  desc.cb=sizeof desc;
  desc.flags=track_flags;
  desc.hWnd=hWnd;
  desc.hover_time=hover_time;

  SysGuard(format, Win64::TrackMouseEvent(&desc) );
 }

void WindowsHost::mouseShape(VKey vkey,KeyMod kmod)
 {
  if( vkey==VKey_Shift || vkey==VKey_Ctrl || vkey==VKey_Alt )
    {
     frame->setMouseShape(getMousePos(),kmod);
    }
 }

Win64::MsgResult WindowsHost::msgProc(Win64::HWindow hWnd_,Win64::MsgCode message,Win64::MsgWParam wParam,Win64::MsgLParam lParam)
 {
  switch( message )
    {
     case Win64::WM_GetMinMaxInfo :
      {
       Win64::MinMaxInfo *info=(Win64::MinMaxInfo *)lParam;

       Replace_min<int>(info->max_size.x,max_size.x);
       Replace_min<int>(info->max_size.y,max_size.y);
      }
     return 0;

     case Win64::WM_NcCreate :
      {
       hWnd=hWnd_;
       is_alive=true;

       if( is_main ) HMainWindow=hWnd_;

       auto ret=Win64::DefWindowProcW(hWnd_,message,wParam,lParam);

       try { frame->alive(); } catch(...) {}

       return ret;
      }

     case Win64::WM_NcDestroy :
      {
       try { frame->dead(); } catch(...) {}

       hWnd=0;
       is_alive=false;

       if( is_main )
         {
          HMainWindow=0;

          Win64::PostQuitMessage(0);
         }

       return Win64::DefWindowProcW(hWnd_,message,wParam,lParam);
      }

     case Win64::WM_Paint :
      {
       WindowPaint wp(hWnd);

       if( !buf_dirty ) buf.draw(wp.getGD(),wp.getPane());

       frame->paintDone(Replace_null(token));
      }
     return 0;

     case Win64::WM_Move :
      {
       origin=ToPoint(lParam);
      }
     return 0;

     case Win64::WM_Size :
      {
       frame->setSize(ToSize(lParam),buf_dirty);
      }
     return 0;

     case Win64::WM_SetFocus :
      {
       frame->gainFocus();
      }
     return 0;

     case Win64::WM_KillFocus :
      {
       frame->looseFocus();
      }
     return 0;

     case Win64::WM_CaptureChanged :
      {
       frame->looseCapture();
      }
     return 0;

     case Win64::WM_KeyDown :
      {
       unsigned repeat=lParam&0xFFFFu;
       bool ext=(lParam>>24)&1u;

       VKey vkey=ToVKey(wParam);
       KeyMod kmod=GetKeyMod(ext);

       mouseShape(vkey,kmod);

       if( repeat>1 )
         frame->put_Key(vkey,kmod,repeat);
       else
         frame->put_Key(vkey,kmod);
      }
     return 0;

     case Win64::WM_SysKeyDown :
      {
       unsigned repeat=lParam&0xFFFFu;
       bool ext=(lParam>>24)&1u;
       bool alt=(lParam>>29)&1u;

       VKey vkey=ToVKey(wParam);
       KeyMod kmod=GetKeyMod(ext);

       if( alt ) kmod|=KeyMod_Alt;

       mouseShape(vkey,kmod);

       if( repeat>1 )
         frame->put_Key(vkey,kmod,repeat);
       else
         frame->put_Key(vkey,kmod);
      }
     return 0;

     case Win64::WM_KeyUp :
      {
       unsigned repeat=lParam&0xFFFFu;
       bool ext=(lParam>>24)&1u;

       VKey vkey=ToVKey(wParam);
       KeyMod kmod=GetKeyMod(ext);

       mouseShape(vkey,kmod);

       if( repeat>1 )
         frame->put_KeyUp(vkey,kmod,repeat);
       else
         frame->put_KeyUp(vkey,kmod);
      }
     return 0;

     case Win64::WM_SysKeyUp :
      {
       unsigned repeat=lParam&0xFFFFu;
       bool ext=(lParam>>24)&1u;
       bool alt=(lParam>>29)&1u;

       VKey vkey=ToVKey(wParam);
       KeyMod kmod=GetKeyMod(ext);

       if( alt ) kmod|=KeyMod_Alt;

       mouseShape(vkey,kmod);

       if( repeat>1 )
         frame->put_KeyUp(vkey,kmod,repeat);
       else
         frame->put_KeyUp(vkey,kmod);
      }
     return 0;

     case Win64::WM_Char :
      {
       Sys::WChar ch=(Sys::WChar)wParam;

       if( hi )
         {
          if( Sys::IsLoSurrogate(ch) )
            {
             Unicode uch=Sys::Surrogate(Replace_null(hi),ch);
             unsigned repeat=lParam&0xFFFFu;

             if( repeat>1 )
               frame->put_Char(uch,repeat);
             else
               frame->put_Char(uch);
            }
          else if( Sys::IsHiSurrogate(ch) )
            {
             // broken, skip

             hi=ch;
            }
          else
            {
             // broken, skip

             hi=0;
            }
         }
       else
         {
          if( Sys::IsHiSurrogate(ch) )
            {
             hi=ch;
            }
          else if( Sys::IsLoSurrogate(ch) )
            {
             // broken, skip
            }
          else
            {
             unsigned repeat=lParam&0xFFFFu;

             if( repeat>1 )
               frame->put_Char(ch,repeat);
             else
               frame->put_Char(ch);
            }
         }
      }
     return 0;

     case Win64::WM_SysChar :
      {
       Sys::WChar ch=(Sys::WChar)wParam;

       if( syshi )
         {
          if( Sys::IsLoSurrogate(ch) )
            {
             Unicode uch=Sys::Surrogate(Replace_null(syshi),ch);
             unsigned repeat=lParam&0xFFFFu;

             if( repeat>1 )
               frame->put_AltChar(uch,repeat);
             else
               frame->put_AltChar(uch);
            }
          else if( Sys::IsHiSurrogate(ch) )
            {
             // broken, skip

             syshi=ch;
            }
          else
            {
             // broken, skip

             syshi=0;
            }
         }
       else
         {
          if( Sys::IsHiSurrogate(ch) )
            {
             syshi=ch;
            }
          else if( Sys::IsLoSurrogate(ch) )
            {
             // broken, skip
            }
          else
            {
             unsigned repeat=lParam&0xFFFFu;

             if( repeat>1 )
               frame->put_AltChar(ch,repeat);
             else
               frame->put_AltChar(ch);
            }
         }
      }
     return 0;

     case Win64::WM_LButtonDown :
      {
       MouseKey mkey=ToMouseKey(wParam);
       Point point=ToPoint(lParam);

       frame->put_LeftClick(point,mkey);
      }
     return 0;

     case Win64::WM_LButtonUp :
      {
       MouseKey mkey=ToMouseKey(wParam);
       Point point=ToPoint(lParam);

       frame->put_LeftUp(point,mkey);
      }
     return 0;

     case Win64::WM_LButtonDClick :
      {
       MouseKey mkey=ToMouseKey(wParam);
       Point point=ToPoint(lParam);

       frame->put_LeftDClick(point,mkey);
      }
     return 0;

     case Win64::WM_RButtonDown :
      {
       MouseKey mkey=ToMouseKey(wParam);
       Point point=ToPoint(lParam);

       frame->put_RightClick(point,mkey);
      }
     return 0;

     case Win64::WM_RButtonUp :
      {
       MouseKey mkey=ToMouseKey(wParam);
       Point point=ToPoint(lParam);

       frame->put_RightUp(point,mkey);
      }
     return 0;

     case Win64::WM_RButtonDClick :
      {
       MouseKey mkey=ToMouseKey(wParam);
       Point point=ToPoint(lParam);

       frame->put_RightDClick(point,mkey);
      }
     return 0;

     case Win64::WM_MouseMove :
      {
       if( track_flags )
         {
          if( !track_on )
            {
             setTrack();

             track_on=true;
            }
         }

       MouseKey mkey=ToMouseKey(wParam);
       Point point=ToPoint(lParam);

       frame->put_Move(point,mkey);
      }
     return 0;

     case Win64::WM_MouseWheel :
      {
       MouseKey mkey=ToMouseKey(Win64::LoWord(wParam));
       Coord delta=Win64::SHiWord(wParam)/Win64::WheelDelta;
       Point point=ToPoint(lParam)-origin;

       frame->put_Wheel(point,mkey,delta);
      }
     return 0;

     case Win64::WM_MouseHover :
      {
       MouseKey mkey=ToMouseKey(wParam);
       Point point=ToPoint(lParam);

       track_on=false;

       frame->put_Hover(point,mkey);
      }
     return 0;

     case Win64::WM_MouseLeave :
      {
       track_on=false;

       frame->put_Leave();
      }
     return 0;

     case Win64::WM_NcHitTest :
      {
       Point point=ToPoint(lParam);

       frame->setMouseShape(point-origin,GetKeyMod());
      }
     return Win64::HitCode_Client;

     case Win64::WM_SetCursor :
      {
       // do nothing
      }
     return true;

     case Win64::WM_Close :
      {
       frame->askClose();
      }
     return 0;

     default: return Win64::DefWindowProcW(hWnd_,message,wParam,lParam);
    }
 }

Win64::MsgResult WindowsHost::ObjWndProc(WindowsHost *obj,Win64::HWindow hWnd,Win64::MsgCode message,Win64::MsgWParam wParam,Win64::MsgLParam lParam)
 {
  try
    {
     return obj->msgProc(hWnd,message,wParam,lParam);
    }
  catch(...)
    {
     return 0;
    }
 }

Win64::MsgResult WindowsHost::WndProc(Win64::HWindow hWnd,Win64::MsgCode message,Win64::MsgWParam wParam,Win64::MsgLParam lParam)
 {
  TaskEventHost.add<MsgEvent>(message,MsgEvent::Entry);

  if( message==Win64::WM_NcCreate )
    {
     Win64::CreateData *ctx=(Win64::CreateData *)lParam;

     Win64::SetWindowLongW(hWnd,0,(Win64::UPtrType)(ctx->arg));
    }

  void *arg=(void *)Win64::GetWindowLongW(hWnd,0);

  Win64::MsgResult ret;

  if( !arg )
    {
     // WM_GetMinMaxInfo comes before WM_NcCreate

     ret=Win64::DefWindowProcW(hWnd,message,wParam,lParam);
    }
  else
    {
     ret=ObjWndProc(static_cast<WindowsHost *>(arg),hWnd,message,wParam,lParam);
    }

  TaskEventHost.add<MsgEvent>(message,MsgEvent::Leave);

  return ret;
 }

void WindowsHost::reset()
 {
  origin=Null;
  buf_dirty=true;
  track_flags=0;
  track_on=false;
  max_flag=false;
  hi=0;
  syshi=0;
 }

void WindowsHost::do_move(Pane pane)
 {
  const char *format="CCore::Video::Internal::WindowsHost::do_move(...) : #;";

  guardAlive(format);

  GuardPane(format,pane,max_size);

  unsigned pos_flags=Win64::WindowPos_NoZOrder|Win64::WindowPos_NoCopyBits|Win64::WindowPos_NoRedraw|Win64::WindowPos_DeferErase;

  SysGuard(format, Win64::SetWindowPos(hWnd,(Win64::HWindow)0,pane.x,pane.y,pane.dx,pane.dy,pos_flags) );
 }

WindowsHost::WindowsHost()
 {
 }

WindowsHost::~WindowsHost()
 {
  if( is_alive )
    {
     Win64::DestroyWindow(hWnd);
    }
 }

 // msg boxes

void WindowsHost::AbortMsgBox(StrLen text)
 {
  ErrorMsgBox(text,"Abort"_c);
 }

void WindowsHost::ErrorMsgBox(StrLen text,StrLen title)
 {
  Sys::WCharString<> cap(text);
  Sys::WCharString<> cap_title(title);

  Win64::MessageBoxW(HMainWindow,cap,cap_title,Win64::MessageBox_Ok|Win64::MessageBox_IconError);
 }

 // icons

void WindowsHost::SetAppIcon(Picture pict)
 {
  WindowClassObject.setIcon(pict);
 }

 // WinControl
 // create/destroy

void WindowsHost::createMain(Point max_size)
 {
  Pane work=GetWorkPane();

  Point size;

  size.x=RandomLen(work.dx);
  size.y=RandomLen(work.dy);

  size=Inf(size,max_size);

  Point base;

  base.x=RandomPos(work.dx-size.x);
  base.y=RandomPos(work.dy-size.y);

  Pane pane=Pane(work.getBase()+base,size);

  createMain(pane,max_size);
 }

void WindowsHost::createMain(Pane pane,Point max_size_)
 {
  const char *format="CCore::Video::Internal::WindowsHost::createMain(...) : #;";

  guardCreate(format,pane,max_size_);

  if( HMainWindow!=0 )
    {
     Printf(Exception,format,"main window is already created");
    }

  is_main=true;
  max_size=max_size_;

  reset();

  buf.setSize(max_size_);

  Sys::WCharString<16> temp(""_c);

  Win64::HWindow hWnd=Win64::CreateWindowExW(0,
                                             Win64::MakeIntAtom(WindowClassObject.getAtom(format)),
                                             temp,
                                             Win64::WindowStyle_Popup,
                                             pane.x,pane.y,pane.dx,pane.dy,
                                             0,0,0,
                                             (void *)this);

  SysGuard(format,hWnd!=0);
 }

void WindowsHost::create(Pane pane,Point max_size)
 {
  create(0,pane,max_size);
 }

void WindowsHost::create(WindowHost *parent,Pane pane,Point max_size_)
 {
  const char *format="CCore::Video::Internal::WindowsHost::create(...) : #;";

  guardCreate(format,pane,max_size_);

  is_main=false;
  max_size=max_size_;

  reset();

  buf.setSize(max_size_);

  Win64::HWindow hParent;

  if( parent )
    {
     WindowsHost *ptr=dynamic_cast<WindowsHost *>(parent);

     if( !ptr )
       {
        Printf(Exception,format,"bad parent");
       }

     hParent=ptr->hWnd;

     if( hParent==0 )
       {
        Printf(Exception,format,"dead parent");
       }
    }
  else
    {
     hParent=HMainWindow;
    }

  Sys::WCharString<16> temp(""_c);

  Win64::HWindow hWnd=Win64::CreateWindowExW(0,
                                             Win64::MakeIntAtom(WindowClassObject.getAtom(format)),
                                             temp,
                                             Win64::WindowStyle_Popup,
                                             pane.x,pane.y,pane.dx,pane.dy,
                                             hParent,0,0,
                                             (void *)this);

  SysGuard(format,hWnd!=0);
 }

void WindowsHost::destroy()
 {
  const char *format="CCore::Video::Internal::WindowsHost::destroy() : #;";

  guardAlive(format);

  SysGuard(format, Win64::DestroyWindow(hWnd) );
 }

 // operations

void WindowsHost::setTitle(StrLen title)
 {
  Sys::WCharString<> cap(title);

  const char *format="CCore::Video::Internal::WindowsHost::setTitle(...) : #;";

  guardAlive(format);

  if( is_main )
    SysGuard(format, Win64::SetWindowTextW(hWnd,cap) );
 }

void WindowsHost::setMaxSize(Point max_size_)
 {
  const char *format="CCore::Video::Internal::WindowsHost::setMaxSize(...) : #;";

  GuardMaxSize(format,max_size_);

  buf.setSize(max_size_);

  max_size=max_size_;

  buf_dirty=true;
 }

bool WindowsHost::enableUserInput(bool en)
 {
  const char *format="CCore::Video::Internal::WindowsHost::enableUserInput(...) : #;";

  guardAlive(format);

  return !Win64::EnableWindow(hWnd,en);
 }

void WindowsHost::display(CmdDisplay cmd_display)
 {
  const char *format="CCore::Video::Internal::WindowsHost::display(...) : #;";

  guardAlive(format);

  switch( cmd_display )
    {
     default:
     case CmdDisplay_Normal :
      {
       Win64::ShowWindow(hWnd,Win64::CmdShow_Normal); // error unavailable
      }
     break;

     case CmdDisplay_Minimized :
      {
       if( is_main )
         Win64::ShowWindow(hWnd,Win64::CmdShow_Minimized); // error unavailable
      }
     break;

     case CmdDisplay_Maximized :
      {
       if( !max_flag )
         {
          max_flag=true;

          restore=getPlace();

          Pane pane=GetWorkPane(restore);

          Replace_min(pane.dx,max_size.x);
          Replace_min(pane.dy,max_size.y);

          do_move(pane);

          Win64::InvalidateRect(hWnd,0,true); // ignore error
         }

       Win64::ShowWindow(hWnd,Win64::CmdShow_Normal); // error unavailable
      }
     break;

     case CmdDisplay_Restore :
      {
       if( max_flag )
         {
          max_flag=false;

          do_move(restore);

          Win64::InvalidateRect(hWnd,0,true); // ignore error
         }

       Win64::ShowWindow(hWnd,Win64::CmdShow_Normal); // error unavailable
      }
     break;
    }
 }

void WindowsHost::show()
 {
  const char *format="CCore::Video::Internal::WindowsHost::show() : #;";

  guardAlive(format);

  Win64::ShowWindow(hWnd,Win64::CmdShow_Show); // error unavailable
 }

void WindowsHost::hide()
 {
  const char *format="CCore::Video::Internal::WindowsHost::hide() : #;";

  guardAlive(format);

  Win64::ShowWindow(hWnd,Win64::CmdShow_Hide); // error unavailable
 }

 // drawing

void WindowsHost::update()
 {
  const char *format="CCore::Video::Internal::WindowsHost::update() : #;";

  guardAlive(format);

  SysGuard(format, Win64::UpdateWindow(hWnd) );

  buf_dirty=false;
 }

void WindowsHost::invalidate(Pane pane,unsigned token_)
 {
  if( !pane ) return;

  token|=token_;

  Win64::Rectangle rect;

  rect.left=pane.x;
  rect.right=pane.x+pane.dx;

  rect.top=pane.y;
  rect.bottom=pane.y+pane.dy;

  Win64::InvalidateRect(hWnd,&rect,true); // ignore error

  buf_dirty=false;
 }

void WindowsHost::invalidate(unsigned token_)
 {
  token|=token_;

  Win64::InvalidateRect(hWnd,0,true); // ignore error

  buf_dirty=false;
 }

ColorPlane WindowsHost::getDrawPlane()
 {
  return buf.getPlane();
 }

 // keyboard

void WindowsHost::setFocus()
 {
  const char *format="CCore::Video::Internal::WindowsHost::setFocus() : #;";

  guardAlive(format);

  Win64::SetFocus(hWnd); // error unavailable
 }

 // mouse

Point WindowsHost::getMousePos()
 {
  Win64::Point point_;

  if( Win64::GetCursorPos(&point_) )
    {
     Point point(point_.x,point_.y);

     return point-origin;
    }

  return Null;
 }

void WindowsHost::captureMouse()
 {
  const char *format="CCore::Video::Internal::WindowsHost::captureMouse() : #;";

  guardAlive(format);

  Win64::SetCapture(hWnd); // error unavailable
 }

void WindowsHost::releaseMouse()
 {
  const char *format="CCore::Video::Internal::WindowsHost::releaseMouse() : #;";

  guardAlive(format);

  SysGuard(format, Win64::ReleaseCapture() );
 }

void WindowsHost::trackMouseHover()
 {
  BitSet(track_flags,Win64::MouseTrack_Hover);

  hover_time=Win64::HoverTimeDefault;

  setTrack();
 }

void WindowsHost::trackMouseHover(MSec time)
 {
  BitSet(track_flags,Win64::MouseTrack_Hover);

  hover_time=+time;

  setTrack();
 }

void WindowsHost::untrackMouseHover()
 {
  BitClear(track_flags,Win64::MouseTrack_Hover);
 }

void WindowsHost::trackMouseLeave()
 {
  BitSet(track_flags,Win64::MouseTrack_Leave);

  setTrack();
 }

void WindowsHost::untrackMouseLeave()
 {
  BitClear(track_flags,Win64::MouseTrack_Leave);
 }

void WindowsHost::setMouseShape(MouseShape mshape)
 {
  Win64::SetCursor(GetCursor(mshape)); // error unavailable
 }

 // place

Pane WindowsHost::getPlace()
 {
  const char *format="CCore::Video::Internal::WindowsHost::getPlace() : #;";

  guardAlive(format);

  Win64::Rectangle rect;

  SysGuard(format, Win64::GetWindowRect(hWnd,&rect) );

  return ToPane(rect);
 }

void WindowsHost::setPlace(Pane pane)
 {
  max_flag=false;

  do_move(pane);
 }

 // clipboard

void WindowsHost::textToClipboard(PtrLen<const Char> text)
 {
  TextToClipboard obj(text);

  Clipboard cbd(hWnd);

  ulen len=obj.getLen();

  PutToClipboard put(len);

  obj.fill(put.getMem());

  put.commit(Win64::ClipboardFormat_UnicodeText);
 }

void WindowsHost::textFromClipboard(Function<void (PtrLen<const Char>)> func)
 {
  Clipboard cbd(hWnd);
  GetFromClipboard get(Win64::ClipboardFormat_UnicodeText);

  const Sys::WChar *ptr=static_cast<const Sys::WChar *>(get.getMem());
  ulen len=get.getLen()/sizeof (Sys::WChar);

  auto text=Range(ptr,len);

  for(auto r=text; +r ;++r)
    {
     if( !*r )
       {
        text=text.prefix(r);

        break;
       }
    }

  ULenSat outlen;

  Sys::FeedUnicode(text, [&outlen] (Char) { outlen+=1u; } );

  if( !outlen )
    {
     Printf(Exception,"CCore::Video::Internal::WindowsHost::textFromClipboard(...) : overflow");
    }

  Sys::TempBuf<Char> temp(outlen.value);

  Char *dst=temp;

  if( !dst )
    {
     Printf(Exception,"CCore::Video::Internal::WindowsHost::textFromClipboard(...) : no memory");
    }

  Sys::FeedUnicode(text, [&dst] (Char ch) { *(dst++)=ch; } );

  func(Range(+temp,outlen.value));
 }

} // namespace Internal
} // namespace Video
} // namespace CCore

