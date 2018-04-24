/* Bitmap.cpp */
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

#include <CCore/inc/video/Bitmap.h>

#include <CCore/inc/DecodeFile.h>
#include <CCore/inc/BinaryFile.h>
#include <CCore/inc/Deflate.h>

#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/FeedBuf.h>
#include <CCore/inc/algon/GCDConst.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* struct BitmapData */

 // internal

void BitmapData::Diff(uint8 *base,ulen dx,ulen dy)
 {
  if( dx<=1 || dy<=1 ) return;

  uint8 *ptr=base+(dx*dy-1);

  for(dy--; dy-- ;)
    {
     for(ulen cnt=dx-1; cnt-- ;ptr--)
       {
        (*ptr) += *(ptr-dx-1) - *(ptr-1) - *(ptr-dx) ;
       }

     ptr--;
    }
 }

void BitmapData::Undiff(uint8 *base,ulen dx,ulen dy)
 {
  if( dx<=1 || dy<=1 ) return;

  uint8 *ptr=base+(dx+1);

  for(dy--; dy-- ;)
    {
     for(ulen cnt=dx-1; cnt-- ;ptr++)
       {
        (*ptr) -= *(ptr-dx-1) - *(ptr-1) - *(ptr-dx) ;
       }

     ptr++;
    }
 }

void BitmapData::GetPlane(uint8 *plane,PtrLen<const uint32> map,unsigned shift)
 {
  for(uint32 x : map ) *(plane++)=uint8(x>>shift);
 }

void BitmapData::AddPlane(PtrLen<uint32> map,const uint8 *plane,unsigned shift)
 {
  for(uint32 &x : map ) x|=(uint32(*(plane++))<<shift);
 }

 // load/save

void BitmapData::loadBitmap(StrLen file_name)
 {
  DecodeFile file(file_name);

  file.use<BeOrder>(dx,dy);

  ulen len=LenOf(dy,dx);

  map.erase();
  map.extend_raw(len);

  for(uint32 &x : map ) file.use<BeOrder>(x);
 }

void BitmapData::saveBitmap(StrLen file_name) const
 {
  BinaryFile file(file_name);

  file.use<BeOrder>(dx,dy);

  for(uint32 x : map ) file.use<BeOrder>(x);
 }

void BitmapData::loadZipmap(StrLen file_name)
 {
  DecodeFile file(file_name);

  file.use<BeOrder>(dx,dy);

  ulen len=LenOf(dy,dx);

  map.erase();
  map.extend_default(len);

  DynArray<uint8> plane(DoRaw{len});

  uint8 *base=plane.getPtr();

  PtrLen<uint8> cur=Range(plane);
  unsigned shift=0;

  auto temp1=ToFunction<void (PtrLen<const uint8>)>( [&] (PtrLen<const uint8> data)
                                                   {
                                                    if( data.len>cur.len )
                                                      {
                                                       Printf(Exception,"CCore::Video::BitmapData::loadZipmap(...) : plane data overflow");
                                                      }

                                                    if( shift>=32u )
                                                      {
                                                       Printf(Exception,"CCore::Video::BitmapData::loadZipmap(...) : extra plane");
                                                      }

                                                    data.copyTo(cur.ptr);

                                                    cur+=data.len;

                                                   } );

  auto temp2=ToFunction<void (void)>( [&] ()
                                          {
                                           if( cur.len )
                                             {
                                              Printf(Exception,"CCore::Video::BitmapData::loadZipmap(...) : plane data underflow");
                                             }

                                           if( shift>=32u )
                                             {
                                              Printf(Exception,"CCore::Video::BitmapData::loadZipmap(...) : extra plane");
                                             }

                                           Undiff(base,dx,dy);

                                           AddPlane(Range(map),base,shift);

                                           cur=Range(plane);
                                           shift+=8;

                                          } );

  Deflate::Inflator unzip(temp1.function(),true);

  unzip.setTrigger(temp2.function());

  while( file.more() ) unzip.put(file.pump());

  unzip.complete();
 }

void BitmapData::saveZipmap(StrLen file_name) const
 {
  BinaryFile file(file_name);

  file.use<BeOrder>(dx,dy);

  auto temp=ToFunction<void (PtrLen<const uint8>)>( [&] (PtrLen<const uint8> data) { file.put(data); } );

  Deflate::Param param;

  param.level=Deflate::MaxLevel;

  Deflate::Deflator zip(temp.function(),param);

  ulen len=map.getLen();

  DynArray<uint8> plane(DoRaw{len});

  uint8 *base=plane.getPtr();

  for(unsigned shift=0; shift<32u ;shift+=8)
    {
     GetPlane(base,Range(map),shift);

     Diff(base,dx,dy);

     zip.put(base,len);

     zip.complete();
    }
 }

/* struct Bitmap::Fill */

struct Bitmap::Fill
 {
  ulen dx;
  ulen dy;
  ulen dline;
  const Raw *src;

  PtrLen<const Raw> line(ulen y) const { return Range(src+y*dline,dx*RawCount); }

  static void Line(PtrLen<const Raw> line,ulen x,ulen dx,Raw *dst)
   {
    line.safe_part(x*RawCount,dx*RawCount).copyTo(dst);
   }

  void operator () (ulen x,ulen y,ulen dx,Raw *dst) const
   {
    if( y>=dy ) return;

    Line(line(y),x,dx,dst);
   }
 };

/* class Bitmap */

template <class Dev>
uint32 Bitmap::Next(Dev &dev)
 {
  uint32 ret;

  dev.template use<BeOrder>(ret);

  return ret;
 }

void Bitmap::fill(FuncType<uint32> next)
 {
  dline=LenOf(dx,RawCount);

  const ulen Align = MaxAlign/Algon::GCDConst<ulen,MaxAlign,sizeof (Raw)>  ;

  if constexpr ( Align>1 ) TryAlign(dline,Align);

  Raw *ptr=buf.extend_raw( LenOf(dline,dy) ).ptr;

  for(ulen count=dy; count ;count--,ptr+=dline)
    {
     Raw *line=ptr;

     for(ulen count=dx; count ;count--,line+=RawCount)
       {
        DesktopColor col( (VColor)next() );

        col.copyTo(line);
       }
    }
 }

void Bitmap::load(const BitmapData &data)
 {
  dx=data.dx;
  dy=data.dy;

  struct Src
   {
    const uint32 *ptr;

    uint32 operator () () { return *(ptr++); }
   };

  fill(Src{data.map.getPtr()});
 }

void Bitmap::load(StrLen file_name)
 {
  if( file_name.hasSuffix(".zipmap"_c) )
    {
     BitmapData data;

     data.loadZipmap(file_name);

     load(data);
    }
  else
    {
     DecodeFile file(file_name);

     dx=Next(file);
     dy=Next(file);

     fill( [&file] () { return Next(file); } );
    }
 }

Bitmap::Bitmap(StrLen file_name)
 {
  load(file_name);
 }

Bitmap::Bitmap(StrLen dir,StrLen file_name)
 {
  MakeFileName temp(dir,file_name);

  load(temp.get());
 }

void Bitmap::draw(DrawBuf buf,Pane pane) const
 {
  buf.fill(pane,Fill{dx,dy,dline,getPtr()});
 }

} // namespace Video
} // namespace CCore

