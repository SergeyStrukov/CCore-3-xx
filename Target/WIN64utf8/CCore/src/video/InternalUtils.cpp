/* InternalUtils.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/WIN64
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
  Win64::Rectangle rect;

  rect.left=pane.x;
  rect.top=pane.y;
  rect.right=pane.x+pane.dx;
  rect.bottom=pane.y+pane.dy;

  SysGuard("CCore::Video::Internal::GetWorkPane() : #;", Win64::SystemParametersInfoA(Win64::SPA_getWorkArea,0,&rect,0) );

  return ToPane(rect);
 }

/* struct MsgEvent */

void MsgEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id_Code=info.addEnum_uint32("WinMsgCode")
                   .addValueName(Win64::WM_Create,"WM_Create")
                   .addValueName(Win64::WM_Destroy,"WM_Destroy")
                   .addValueName(Win64::WM_Move,"WM_Move")
                   .addValueName(Win64::WM_Size,"WM_Size")
                   .addValueName(Win64::WM_Activate,"WM_Activate")
                   .addValueName(Win64::WM_SetFocus,"WM_SetFocus")
                   .addValueName(Win64::WM_KillFocus,"WM_KillFocus")
                   .addValueName(Win64::WM_Enable,"WM_Enable")
                   .addValueName(Win64::WM_Paint,"WM_Paint")
                   .addValueName(Win64::WM_Close,"WM_Close")
                   .addValueName(Win64::WM_Quit,"WM_Quit")
                   .addValueName(Win64::WM_QueryOpen,"WM_QueryOpen")
                   .addValueName(Win64::WM_EraseBackground,"WM_EraseBackground")
                   .addValueName(Win64::WM_EndSession,"WM_EndSession")
                   .addValueName(Win64::WM_ShowWindow,"WM_ShowWindow")
                   .addValueName(Win64::WM_ActivateApp,"WM_ActivateApp")
                   .addValueName(Win64::WM_CancelMode,"WM_CancelMode")
                   .addValueName(Win64::WM_SetCursor,"WM_SetCursor")
                   .addValueName(Win64::WM_MouseActivate,"WM_MouseActivate")
                   .addValueName(Win64::WM_GetMinMaxInfo,"WM_GetMinMaxInfo")
                   .addValueName(Win64::WM_WindowPosChanging,"WM_WindowPosChanging")
                   .addValueName(Win64::WM_WindowPosChanged,"WM_WindowPosChanged")
                   .addValueName(Win64::WM_ContextMenu,"WM_ContextMenu")
                   .addValueName(Win64::WM_NcCreate,"WM_NcCreate")
                   .addValueName(Win64::WM_NcDestroy,"WM_NcDestroy")
                   .addValueName(Win64::WM_NcHitTest,"WM_NcHitTest")
                   .addValueName(Win64::WM_NcPaint,"WM_NcPaint")
                   .addValueName(Win64::WM_NcActivate,"WM_NcActivate")
                   .addValueName(Win64::WM_SyncPaint,"WM_SyncPaint")
                   .addValueName(Win64::WM_NcMouseMove,"WM_NcMouseMove")
                   .addValueName(Win64::WM_NcLButtonDown,"WM_NcLButtonDown")
                   .addValueName(Win64::WM_NcLButtonUp,"WM_NcLButtonUp")
                   .addValueName(Win64::WM_NcLButtonDClick,"WM_NcLButtonDClick")
                   .addValueName(Win64::WM_NcRButtonDown,"WM_NcRButtonDown")
                   .addValueName(Win64::WM_NcRButtonUp,"WM_NcRButtonUp")
                   .addValueName(Win64::WM_NcRButtonDClick,"WM_NcRButtonDClick")
                   .addValueName(Win64::WM_NcMButtonDown,"WM_NcMButtonDown")
                   .addValueName(Win64::WM_NcMButtonUp,"WM_NcMButtonUp")
                   .addValueName(Win64::WM_NcMButtonDClick,"WM_NcMButtonDClick")
                   .addValueName(Win64::WM_KeyDown,"WM_KeyDown")
                   .addValueName(Win64::WM_KeyUp,"WM_KeyUp")
                   .addValueName(Win64::WM_Char,"WM_Char")
                   .addValueName(Win64::WM_DeadChar,"WM_DeadChar")
                   .addValueName(Win64::WM_SysKeyDown,"WM_SysKeyDown")
                   .addValueName(Win64::WM_SysKeyUp,"WM_SysKeyUp")
                   .addValueName(Win64::WM_SysChar,"WM_SysChar")
                   .addValueName(Win64::WM_SysDeadChar,"WM_SysDeadChar")
                   .addValueName(Win64::WM_InitDialog,"WM_InitDialog")
                   .addValueName(Win64::WM_Command,"WM_Command")
                   .addValueName(Win64::WM_SysCommand,"WM_SysCommand")
                   .addValueName(Win64::WM_InitMenu,"WM_InitMenu")
                   .addValueName(Win64::WM_InitMenuPopup,"WM_InitMenuPopup")
                   .addValueName(Win64::WM_MenuSelect,"WM_MenuSelect")
                   .addValueName(Win64::WM_EnterIdle,"WM_EnterIdle")
                   .addValueName(Win64::WM_UninitMenuPopup,"WM_UninitMenuPopup")
                   .addValueName(Win64::WM_MouseMove,"WM_MouseMove")
                   .addValueName(Win64::WM_LButtonDown,"WM_LButtonDown")
                   .addValueName(Win64::WM_LButtonUp,"WM_LButtonUp")
                   .addValueName(Win64::WM_LButtonDClick,"WM_LButtonDClick")
                   .addValueName(Win64::WM_RButtonDown,"WM_RButtonDown")
                   .addValueName(Win64::WM_RButtonUp,"WM_RButtonUp")
                   .addValueName(Win64::WM_RButtonDClick,"WM_RButtonDClick")
                   .addValueName(Win64::WM_MButtonDown,"WM_MButtonDown")
                   .addValueName(Win64::WM_MButtonUp,"WM_MButtonUp")
                   .addValueName(Win64::WM_MButtonDClick,"WM_MButtonDClick")
                   .addValueName(Win64::WM_MouseWheel,"WM_MouseWheel")
                   .addValueName(Win64::WM_EnterMenuLoop,"WM_EnterMenuLoop")
                   .addValueName(Win64::WM_ExitMenuLoop,"WM_ExitMenuLoop")
                   .addValueName(Win64::WM_Sizing,"WM_Sizing")
                   .addValueName(Win64::WM_CaptureChanged,"WM_CaptureChanged")
                   .addValueName(Win64::WM_Moving,"WM_Moving")
                   .addValueName(Win64::WM_EnterSizeMove,"WM_EnterSizeMove")
                   .addValueName(Win64::WM_ExitSizeMove,"WM_ExitSizeMove")
                   .addValueName(Win64::WM_NcMouseHover,"WM_NcMouseHover")
                   .addValueName(Win64::WM_MouseHover,"WM_MouseHover")
                   .addValueName(Win64::WM_NcMouseLeave,"WM_NcMouseLeave")
                   .addValueName(Win64::WM_MouseLeave,"WM_MouseLeave")
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

  Win64::BitmapInfo info;

  info.header.cb=sizeof (Win64::BitmapInfoHeader);
  info.header.dx=size.x;
  info.header.dy=-size.y;
  info.header.planes=1;
  info.header.bpp=32;
  info.header.compression=Win64::Bitmap_RGB;

  info.header.image_size=0;
  info.header.x_ppm=0;
  info.header.y_ppm=0;
  info.header.colors_used=1;
  info.header.colors_important=0;

  info.colors[0].blue=0;
  info.colors[0].green=0;
  info.colors[0].red=0;
  info.colors[0].alpha=0;

  hBitmap=Win64::CreateDIBSection(0,&info,Win64::DIB_RGBColors,&mem,0,0);

  SysGuard(format,hBitmap!=0);
 }

WindowBitmap::~WindowBitmap()
 {
  if( hBitmap ) Win64::DeleteObject(Win64::ToGDObject(hBitmap));
 }

/* class WindowBuf */

void WindowBuf::setSize(Point new_size,bool first_time)
 {
  const char *format="CCore::Video::Internal::WindowBuf::setSize(...) : #;";

  if( new_size<=Null )
    {
     Printf(Exception,format,"bad size");
    }

  Win64::BitmapInfo info;

  info.header.cb=sizeof (Win64::BitmapInfoHeader);
  info.header.dx=new_size.x;
  info.header.dy=-new_size.y;
  info.header.planes=1;
  info.header.bpp=32;
  info.header.compression=Win64::Bitmap_RGB;

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

  Win64::HGDObject new_bmp=Win64::ToGDObject(Win64::CreateDIBSection(0,&info,Win64::DIB_RGBColors,&new_mem,0,0));

  SysGuard(format,new_bmp!=0);

  if( first_time )
    {
     old_bmp=Win64::SelectObject(hGD,new_bmp);
    }
  else
    {
     Win64::SelectObject(hGD,new_bmp);

     Win64::DeleteObject(bmp);
    }

  bmp=new_bmp;
  mem=new_mem;
  size=new_size;
 }

WindowBuf::WindowBuf()
 {
  const char *format="CCore::Video::Internal::WindowBuf::WindowBuf(...) : #;";

  hGD=Win64::CreateCompatibleDC(0);

  SysGuard(format,hGD!=0);
 }

WindowBuf::~WindowBuf()
 {
  if( mem )
    {
     Win64::SelectObject(hGD,old_bmp);

     Win64::DeleteObject(bmp);
    }

  Win64::DeleteDC(hGD);
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

void WindowBuf::draw(Win64::HGDevice dstGD,Pane pane)
 {
  const char *format="CCore::Video::Internal::WindowBuf::draw(...) : #;";

  if( !mem )
    {
     Printf(Exception,format,"no buf");
    }

  SysGuard(format, Win64::BitBlt(dstGD,pane.x,pane.y,pane.dx,pane.dy,hGD,pane.x,pane.y,Win64::RasterOp_Copy) );
 }

/* class Clipboard */

Clipboard::Clipboard(Win64::HWindow hWnd)
 {
  const char *format="CCore::Video::Internal::Clipboard::Clipboard(...) : #;";

  SysGuard(format, Win64::OpenClipboard(hWnd) );
 }

Clipboard::~Clipboard()
 {
  Win64::CloseClipboard();
 }

/* class PutToClipboard */

PutToClipboard::PutToClipboard(ulen len)
 {
  const char *format="CCore::Video::Internal::PutToClipboard::PutToClipboard(...) : #;";

  SysGuard(format, Win64::EmptyClipboard() );

  h_mem=Win64::GlobalAlloc(Win64::GMemMovable,len);

  SysGuard(format,h_mem!=0);

  mem=Win64::GlobalLock(h_mem);
 }

PutToClipboard::~PutToClipboard()
 {
  if( h_mem )
    {
     Win64::GlobalUnlock(h_mem);

     Win64::GlobalFree(h_mem);
    }
 }

void PutToClipboard::commit(unsigned cbd_format)
 {
  const char *format="CCore::Video::Internal::PutToClipboard::commit(...) : #;";

  if( h_mem )
    {
     Win64::GlobalUnlock(h_mem);

     mem=0;

     if( !Win64::SetClipboardData(cbd_format,h_mem) )
       {
        Sys::ErrorType error=Sys::NonNullError();

        mem=Win64::GlobalLock(h_mem);

        SysGuardFailed(format,error);
       }

     h_mem=0;
    }
 }

/* class GetFromClipboard */

GetFromClipboard::GetFromClipboard(unsigned cbd_format)
 {
  const char *format="CCore::Video::Internal::GetFromClipboard::GetFromClipboard(...) : #;";

  h_mem=Win64::GetClipboardData(cbd_format);

  SysGuard(format,h_mem!=0);

  mem=Win64::GlobalLock(h_mem);
  len=Win64::GlobalSize(h_mem);
 }

GetFromClipboard::~GetFromClipboard()
 {
  Win64::GlobalUnlock(h_mem);
 }

/* class TextToClipboard */

ulen TextToClipboard::getLen() const
 {
  ULenSat len=1u;

  StrLen temp=text;

  while( +temp )
    {
     StrLen line=CutLine(temp);

     len+=line.len;

     if( +temp ) len+=2u;
    }

  if( !len )
    {
     Printf(Exception,"CCore::Video::Internal::TextToClipboard::getLen() : overflow");
    }

  return len.value;
 }

void TextToClipboard::fill(void *mem) const
 {
  char *dst=static_cast<char *>(mem);

  StrLen temp=text;

  while( +temp )
    {
     StrLen line=CutLine(temp);

     line.copyTo(dst);

     dst+=line.len;

     if( +temp )
       {
        dst[0]='\r';
        dst[1]='\n';

        dst+=2;
       }
    }

  dst[0]=0;
 }

} // namespace Internal
} // namespace Video
} // namespace CCore

