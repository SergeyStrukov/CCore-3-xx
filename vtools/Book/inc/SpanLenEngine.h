/* SpanLenEngine.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef SpanLenEngine_h
#define SpanLenEngine_h

#include <inc/App.h>

namespace App {

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

} // namespace App

#endif

