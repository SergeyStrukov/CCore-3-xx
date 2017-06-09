/* ErrorText.h */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef ErrorText_h
#define ErrorText_h

#include <inc/Application.h>

namespace App {

/* classes */

class ErrorText;

/* class ErrorText */

class ErrorText : NoCopy
 {
   SimpleArray<char> buf;
   ulen len = 0 ;

  public:

   ErrorText() : buf(64_KByte) {}

   // methods

   bool operator + () const { return len!=0; }

   bool operator ! () const { return len==0; }

   StrLen getText() const { return Range(buf.getPtr(),len); }

   PtrLen<char> getBuf() { return Range(buf); }

   void setTextLen(ulen len_)
    {
     len=Min(buf.getLen(),len_);
    }
 };

} // namespace App

#endif


