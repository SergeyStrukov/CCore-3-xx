/* Deflate.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Deflate_h
#define CCore_inc_Deflate_h

#include <CCore/inc/Array.h>

namespace CCore {

/* classes */

class Deflate;

class Inflate;

/* class Deflate */

class Deflate : NoCopy
 {
  public:

   Deflate();

   ~Deflate();

   void step(uint8 sym,FuncArgType<uint8> out)
    {
    }
 };

} // namespace CCore

#endif

