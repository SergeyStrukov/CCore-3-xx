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
#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/FeedBuf.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/algon/GCDConst.h>

namespace CCore {
namespace Video {

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

void Bitmap::load(StrLen file_name)
 {
  DecodeFile file(file_name);

  dx=Next(file);
  dy=Next(file);

  dline=LenOf(dx,RawCount);

  const ulen Align = MaxAlign/Algon::GCDConst<ulen,MaxAlign,sizeof (Raw)>  ;

  if constexpr ( Align>1 ) TryAlign(dline,Align);

  Raw *ptr=buf.extend_raw( LenOf(dline,dy) ).ptr;

  for(ulen count=dy; count ;count--,ptr+=dline)
    {
     Raw *line=ptr;

     for(ulen count=dx; count ;count--,line+=RawCount)
       {
        DesktopColor col( (VColor)Next(file) );

        col.copyTo(line);
       }
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

