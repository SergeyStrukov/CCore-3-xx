/* Bitmap.h */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_Bitmap_h
#define CCore_inc_video_Bitmap_h

#include <CCore/inc/Array.h>

#include <CCore/inc/video/DrawBuf.h>

namespace CCore {
namespace Video {

/* classes */

class Bitmap;

/* class Bitmap */

class Bitmap
 {
   using Raw = DesktopColor::Raw ;

   static constexpr unsigned RawCount = DesktopColor::RawCount ;

  private:

   DynArray<Raw> buf;
   ulen dx;
   ulen dy;
   ulen dline;

  private:

   class File;

   struct Fill;

   void load(StrLen file_name);

   const Raw * getPtr() const { return buf.getPtr(); }

  public:

   explicit Bitmap(StrLen file_name);

   Bitmap(StrLen dir,StrLen file_name);

   ulen dX() const { return dx; }

   ulen dY() const { return dy; }

   void draw(DrawBuf buf,Pane pane) const;
 };


} // namespace Video
} // namespace CCore

#endif

