/* InternalUtils.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/InternalUtils.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintError.h>

namespace CCore {
namespace Video {
namespace Internal {

/* SysGuard() */

void SysGuardFailed(const char *format,Sys::ErrorType error)
 {
  Printf(Exception,format,PrintError(error));
 }

/* GetWorkPane() */

Pane GetWorkPane(Pane pane)
 {
  Win32::Rectangle rect;

  rect.left=pane.x;
  rect.top=pane.y;
  rect.right=pane.x+pane.dx;
  rect.bottom=pane.y+pane.dy;

  SysGuard("CCore::Video::Internal::GetWorkPane() : #;", Win32::SystemParametersInfoW(Win32::SPA_getWorkArea,0,&rect,0) );

  return ToPane(rect);
 }

/* struct MsgEvent */

void MsgEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Code=info.addEnum_uint32("WinMsgCode")
                   .addValueName(Win32::WM_Create,"WM_Create")
                   .addValueName(Win32::WM_Destroy,"WM_Destroy")
                   .addValueName(Win32::WM_Move,"WM_Move")
                   .addValueName(Win32::WM_Size,"WM_Size")
                   .addValueName(Win32::WM_Activate,"WM_Activate")
                   .addValueName(Win32::WM_SetFocus,"WM_SetFocus")
                   .addValueName(Win32::WM_KillFocus,"WM_KillFocus")
                   .addValueName(Win32::WM_Enable,"WM_Enable")
                   .addValueName(Win32::WM_Paint,"WM_Paint")
                   .addValueName(Win32::WM_Close,"WM_Close")
                   .addValueName(Win32::WM_Quit,"WM_Quit")
                   .addValueName(Win32::WM_QueryOpen,"WM_QueryOpen")
                   .addValueName(Win32::WM_EraseBackground,"WM_EraseBackground")
                   .addValueName(Win32::WM_EndSession,"WM_EndSession")
                   .addValueName(Win32::WM_ShowWindow,"WM_ShowWindow")
                   .addValueName(Win32::WM_ActivateApp,"WM_ActivateApp")
                   .addValueName(Win32::WM_CancelMode,"WM_CancelMode")
                   .addValueName(Win32::WM_SetCursor,"WM_SetCursor")
                   .addValueName(Win32::WM_MouseActivate,"WM_MouseActivate")
                   .addValueName(Win32::WM_GetMinMaxInfo,"WM_GetMinMaxInfo")
                   .addValueName(Win32::WM_WindowPosChanging,"WM_WindowPosChanging")
                   .addValueName(Win32::WM_WindowPosChanged,"WM_WindowPosChanged")
                   .addValueName(Win32::WM_ContextMenu,"WM_ContextMenu")
                   .addValueName(Win32::WM_NcCreate,"WM_NcCreate")
                   .addValueName(Win32::WM_NcDestroy,"WM_NcDestroy")
                   .addValueName(Win32::WM_NcHitTest,"WM_NcHitTest")
                   .addValueName(Win32::WM_NcPaint,"WM_NcPaint")
                   .addValueName(Win32::WM_NcActivate,"WM_NcActivate")
                   .addValueName(Win32::WM_SyncPaint,"WM_SyncPaint")
                   .addValueName(Win32::WM_NcMouseMove,"WM_NcMouseMove")
                   .addValueName(Win32::WM_NcLButtonDown,"WM_NcLButtonDown")
                   .addValueName(Win32::WM_NcLButtonUp,"WM_NcLButtonUp")
                   .addValueName(Win32::WM_NcLButtonDClick,"WM_NcLButtonDClick")
                   .addValueName(Win32::WM_NcRButtonDown,"WM_NcRButtonDown")
                   .addValueName(Win32::WM_NcRButtonUp,"WM_NcRButtonUp")
                   .addValueName(Win32::WM_NcRButtonDClick,"WM_NcRButtonDClick")
                   .addValueName(Win32::WM_NcMButtonDown,"WM_NcMButtonDown")
                   .addValueName(Win32::WM_NcMButtonUp,"WM_NcMButtonUp")
                   .addValueName(Win32::WM_NcMButtonDClick,"WM_NcMButtonDClick")
                   .addValueName(Win32::WM_KeyDown,"WM_KeyDown")
                   .addValueName(Win32::WM_KeyUp,"WM_KeyUp")
                   .addValueName(Win32::WM_Char,"WM_Char")
                   .addValueName(Win32::WM_DeadChar,"WM_DeadChar")
                   .addValueName(Win32::WM_SysKeyDown,"WM_SysKeyDown")
                   .addValueName(Win32::WM_SysKeyUp,"WM_SysKeyUp")
                   .addValueName(Win32::WM_SysChar,"WM_SysChar")
                   .addValueName(Win32::WM_SysDeadChar,"WM_SysDeadChar")
                   .addValueName(Win32::WM_InitDialog,"WM_InitDialog")
                   .addValueName(Win32::WM_Command,"WM_Command")
                   .addValueName(Win32::WM_SysCommand,"WM_SysCommand")
                   .addValueName(Win32::WM_InitMenu,"WM_InitMenu")
                   .addValueName(Win32::WM_InitMenuPopup,"WM_InitMenuPopup")
                   .addValueName(Win32::WM_MenuSelect,"WM_MenuSelect")
                   .addValueName(Win32::WM_EnterIdle,"WM_EnterIdle")
                   .addValueName(Win32::WM_UninitMenuPopup,"WM_UninitMenuPopup")
                   .addValueName(Win32::WM_MouseMove,"WM_MouseMove")
                   .addValueName(Win32::WM_LButtonDown,"WM_LButtonDown")
                   .addValueName(Win32::WM_LButtonUp,"WM_LButtonUp")
                   .addValueName(Win32::WM_LButtonDClick,"WM_LButtonDClick")
                   .addValueName(Win32::WM_RButtonDown,"WM_RButtonDown")
                   .addValueName(Win32::WM_RButtonUp,"WM_RButtonUp")
                   .addValueName(Win32::WM_RButtonDClick,"WM_RButtonDClick")
                   .addValueName(Win32::WM_MButtonDown,"WM_MButtonDown")
                   .addValueName(Win32::WM_MButtonUp,"WM_MButtonUp")
                   .addValueName(Win32::WM_MButtonDClick,"WM_MButtonDClick")
                   .addValueName(Win32::WM_MouseWheel,"WM_MouseWheel")
                   .addValueName(Win32::WM_EnterMenuLoop,"WM_EnterMenuLoop")
                   .addValueName(Win32::WM_ExitMenuLoop,"WM_ExitMenuLoop")
                   .addValueName(Win32::WM_Sizing,"WM_Sizing")
                   .addValueName(Win32::WM_CaptureChanged,"WM_CaptureChanged")
                   .addValueName(Win32::WM_Moving,"WM_Moving")
                   .addValueName(Win32::WM_EnterSizeMove,"WM_EnterSizeMove")
                   .addValueName(Win32::WM_ExitSizeMove,"WM_ExitSizeMove")
                   .addValueName(Win32::WM_NcMouseHover,"WM_NcMouseHover")
                   .addValueName(Win32::WM_MouseHover,"WM_MouseHover")
                   .addValueName(Win32::WM_NcMouseLeave,"WM_NcMouseLeave")
                   .addValueName(Win32::WM_MouseLeave,"WM_MouseLeave")
                   .getId();

  auto id_Flag=info.addEnum_uint8("WinMsgFlag")
                   .addValueName(Entry,"Entry",EventMarker_Up)
                   .addValueName(Leave,"Leave",EventMarker_Down)
                   .addValueName(Stop,"Stop",EventMarker_Stop)
                   .getId();

  auto id=info.addStruct("WinMsgEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint32(id_Code,"code",Offset_code)
              .addField_enum_uint8(id_Flag,"flag",Offset_flag)
              .getId();

  desc.setStructId(info,id);
 }

/* struct TickEvent */

void TickEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Flag=info.addEnum_uint8("WinTickFlag")
                   .addValueName(Entry,"Entry",EventMarker_Up)
                   .addValueName(Leave,"Leave",EventMarker_Down)
                   .getId();

  auto id=info.addStruct("WinTickEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint8(id_Flag,"flag",Offset_flag)
              .getId();

  desc.setStructId(info,id);
 }

/* class WindowBitmap */

WindowBitmap::WindowBitmap(Point size_)
 : size(size_)
 {
  const char *format="CCore::Video::Internal::WindowBitmap::WindowBitmap(...) : #;";

  if( size<=Null )
    {
     Printf(Exception,format,"bad size");
    }

  Win32::BitmapInfo info;

  info.header.cb=sizeof (Win32::BitmapInfoHeader);
  info.header.dx=size.x;
  info.header.dy=-size.y;
  info.header.planes=1;
  info.header.bpp=32;
  info.header.compression=Win32::Bitmap_RGB;

  info.header.image_size=0;
  info.header.x_ppm=0;
  info.header.y_ppm=0;
  info.header.colors_used=1;
  info.header.colors_important=0;

  info.colors[0].blue=0;
  info.colors[0].green=0;
  info.colors[0].red=0;
  info.colors[0].alpha=0;

  hBitmap=Win32::CreateDIBSection(0,&info,Win32::DIB_RGBColors,&mem,0,0);

  SysGuard(format,hBitmap!=0);
 }

WindowBitmap::~WindowBitmap()
 {
  if( hBitmap ) Win32::DeleteObject(Win32::ToGDObject(hBitmap));
 }

/* class WindowBuf */

void WindowBuf::setSize(Point new_size,bool first_time)
 {
  const char *format="CCore::Video::Internal::WindowBuf::setSize(...) : #;";

  if( new_size<=Null )
    {
     Printf(Exception,format,"bad size");
    }

  Win32::BitmapInfo info;

  info.header.cb=sizeof (Win32::BitmapInfoHeader);
  info.header.dx=new_size.x;
  info.header.dy=-new_size.y;
  info.header.planes=1;
  info.header.bpp=32;
  info.header.compression=Win32::Bitmap_RGB;

  info.header.image_size=0;
  info.header.x_ppm=0;
  info.header.y_ppm=0;
  info.header.colors_used=1;
  info.header.colors_important=0;

  info.colors[0].blue=0;
  info.colors[0].green=0;
  info.colors[0].red=0;
  info.colors[0].alpha=0;

  void *new_mem;

  Win32::HGDObject new_bmp=Win32::ToGDObject(Win32::CreateDIBSection(0,&info,Win32::DIB_RGBColors,&new_mem,0,0));

  SysGuard(format,new_bmp!=0);

  if( first_time )
    {
     old_bmp=Win32::SelectObject(hGD,new_bmp);
    }
  else
    {
     Win32::SelectObject(hGD,new_bmp);

     Win32::DeleteObject(bmp);
    }

  bmp=new_bmp;
  mem=new_mem;
  size=new_size;
 }

WindowBuf::WindowBuf()
 {
  const char *format="CCore::Video::Internal::WindowBuf::WindowBuf(...) : #;";

  hGD=Win32::CreateCompatibleDC(0);

  SysGuard(format,hGD!=0);
 }

WindowBuf::~WindowBuf()
 {
  if( mem )
    {
     Win32::SelectObject(hGD,old_bmp);

     Win32::DeleteObject(bmp);
    }

  Win32::DeleteDC(hGD);
 }

void WindowBuf::setSize(Point new_size)
 {
  if( mem )
    {
     if( new_size!=size ) setSize(new_size,false);
    }
  else
    {
     setSize(new_size,true);
    }
 }

void WindowBuf::draw(Win32::HGDevice dstGD,Pane pane)
 {
  const char *format="CCore::Video::Internal::WindowBuf::draw(...) : #;";

  if( !mem )
    {
     Printf(Exception,format,"no buf");
    }

  SysGuard(format, Win32::BitBlt(dstGD,pane.x,pane.y,pane.dx,pane.dy,hGD,pane.x,pane.y,Win32::RasterOp_Copy) );
 }

/* class Clipboard */

Clipboard::Clipboard(Win32::HWindow hWnd)
 {
  const char *format="CCore::Video::Internal::Clipboard::Clipboard(...) : #;";

  SysGuard(format, Win32::OpenClipboard(hWnd) );
 }

Clipboard::~Clipboard()
 {
  Win32::CloseClipboard();
 }

/* class PutToClipboard */

PutToClipboard::PutToClipboard(ulen len)
 {
  const char *format="CCore::Video::Internal::PutToClipboard::PutToClipboard(...) : #;";

  SysGuard(format, Win32::EmptyClipboard() );

  h_mem=Win32::GlobalAlloc(Win32::GMemMovable,len);

  SysGuard(format,h_mem!=0);

  mem=Win32::GlobalLock(h_mem);
 }

PutToClipboard::~PutToClipboard()
 {
  if( h_mem )
    {
     Win32::GlobalUnlock(h_mem);

     Win32::GlobalFree(h_mem);
    }
 }

void PutToClipboard::commit(unsigned cbd_format)
 {
  const char *format="CCore::Video::Internal::PutToClipboard::commit(...) : #;";

  if( h_mem )
    {
     Win32::GlobalUnlock(h_mem);

     mem=0;

     if( !Win32::SetClipboardData(cbd_format,h_mem) )
       {
        Sys::ErrorType error=Sys::NonNullError();

        mem=Win32::GlobalLock(h_mem);

        SysGuardFailed(format,error);
       }

     h_mem=0;
    }
 }

/* class GetFromClipboard */

GetFromClipboard::GetFromClipboard(unsigned cbd_format)
 {
  const char *format="CCore::Video::Internal::GetFromClipboard::GetFromClipboard(...) : #;";

  h_mem=Win32::GetClipboardData(cbd_format);

  SysGuard(format,h_mem!=0);

  mem=Win32::GlobalLock(h_mem);
  len=Win32::GlobalSize(h_mem);
 }

GetFromClipboard::~GetFromClipboard()
 {
  Win32::GlobalUnlock(h_mem);
 }

/* class TextToClipboard */

void TextToClipboard::Feed(PtrLen<const Char> text,FuncArgType<Sys::WChar> func)
 {
  while( +text )
    {
     Char ch=*text;

     if( ch=='\r' || ch=='\n' )
       {
        if( text.len>=2 && ch=='\r' && text[1]=='\n' )
          {
           text+=2;
          }
        else
          {
           ++text;
          }

        if( +text )
          {
           func('\r');
           func('\n');
          }
       }
     else
       {
        ++text;

        if( Sys::IsSurrogate(ch) )
          {
           Sys::SurrogateCouple couple(ch);

           func(couple.hi);
           func(couple.lo);
          }
        else
          {
           func((Sys::WChar)ch);
          }
       }
    }

  func(0);
 }

ulen TextToClipboard::getLen() const
 {
  ULenSat len;

  Feed(text, [&len] (Sys::WChar) { len+=sizeof (Sys::WChar); } );

  if( !len )
    {
     Printf(Exception,"CCore::Video::Internal::TextToClipboard::getLen() : overflow");
    }

  return len.value;
 }

void TextToClipboard::fill(void *mem) const
 {
  Sys::WChar *dst=static_cast<Sys::WChar *>(mem);

  Feed(text, [&dst] (Sys::WChar ch) { *(dst++)=ch; } );
 }

} // namespace Internal
} // namespace Video
} // namespace CCore

