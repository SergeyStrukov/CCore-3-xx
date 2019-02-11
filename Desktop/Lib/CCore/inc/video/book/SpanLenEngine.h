/* SpanLenEngine.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_book_SpanLenEngine_h
#define CCore_inc_video_book_SpanLenEngine_h

#include <CCore/inc/Array.h>

#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {
namespace Book {
namespace DrawBook {

/* classes */

class SpanLenEngine;

/* class SpanLenEngine */

class SpanLenEngine : NoCopy
 {
   struct Cond
    {
     ulen k;
     ulen l;

     Coord a;
    };

   DynArray<Cond> list;

   ulen len;

  public:

   SpanLenEngine(ulen len);

   ~SpanLenEngine();

   void add(ulen i,ulen span,Coord ext); // span > 0 , i+span <= len

   DynArray<Coord> complete(); // [len]
 };

} // namespace DrawBook
} // namespace Book
} // namespace Video
} // namespace CCore

#endif

