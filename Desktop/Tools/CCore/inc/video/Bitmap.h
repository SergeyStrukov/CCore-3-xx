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

struct BitmapData;

class Bitmap;

/* struct BitmapData */

struct BitmapData
 {
  uint32 dx;
  uint32 dy;

  DynArray<uint32> map; // dx*dy

  // load/save

  void loadBitmap(StrLen file_name);

  void saveBitmap(StrLen file_name) const;

  void loadZipmap(StrLen file_name);

  void saveZipmap(StrLen file_name) const;

  // internal

  static void Diff(uint8 *base,ulen dx,ulen dy);

  static void Undiff(uint8 *base,ulen dx,ulen dy);

  static void GetPlane(uint8 *plane,PtrLen<const uint32> map,unsigned shift);

  static void AddPlane(PtrLen<uint32> map,const uint8 *plane,unsigned shift);
 };

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

   template <class Dev>
   static uint32 Next(Dev &dev);

   struct Fill;

   void fill(FuncType<uint32> next);

   void load(const BitmapData &data);

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

