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

#include <CCore/inc/RawFileToRead.h>
#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/FeedBuf.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/algon/GCDConst.h>

namespace CCore {
namespace Video {

/* class Bitmap::File */

class Bitmap::File : NoCopy
 {
   RawFileToRead file;
   DynArray<uint8> buf;

   PtrLen<const uint8> cur;

  private:

   void provide()
    {
     uint8 *ptr=buf.getPtr();

     ulen len=file.read(ptr,buf.getLen());

     cur=Range(ptr,len);

     if( !len )
       {
        Printf(Exception,"CCore::Video::Bitmap::File::provide() : no more data");
       }
    }

   void next(PtrLen<uint8> range)
    {
     while( Pumpup(range,cur) ) provide();
    }

  public:

   explicit File(StrLen file_name)
    : file(file_name),
      buf(64_KByte)
    {
    }

   ~File()
    {
    }

   uint32 next()
    {
     uint8 temp[4];

     next(Range(temp));

     BufGetDev dev(temp);

     uint32 ret;

     dev.use<BeOrder>(ret);

     return ret;
    }
 };

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

void Bitmap::load(StrLen file_name)
 {
  File file(file_name);

  dx=file.next();
  dy=file.next();

  dline=LenOf(dx,RawCount);

  const ulen Align = MaxAlign/Algon::GCDConst<ulen,MaxAlign,sizeof (Raw)>  ;

  if constexpr ( Align>1 ) TryAlign(dline,Align);

  Raw *ptr=buf.extend_raw( LenOf(dline,dy) ).ptr;

  for(ulen count=dy; count ;count--,ptr+=dline)
    {
     Raw *line=ptr;

     for(ulen count=dx; count ;count--,line+=RawCount)
       {
        DesktopColor col( (VColor)file.next() );

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

