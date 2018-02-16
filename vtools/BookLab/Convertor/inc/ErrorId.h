/* ErrorId.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_ErrorId_h
#define App_ErrorId_h

#include <CCore/inc/Printf.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

class ErrorId;

/* class ErrorId */

using ErrorFunc = StrLen (*) (int code) ;

class ErrorId
 {
   int code = 0 ;
   ErrorFunc func = 0 ;

  private:

   static StrLen BoolFunc(int code);

  public:

   ErrorId() {}

   ErrorId(int code_,ErrorFunc func_) : code(code_),func(func_) {}

   explicit ErrorId(bool ok) : ErrorId(!ok,BoolFunc) {}

   bool operator + () const { return code!=0; }

   bool operator ! () const { return code==0; }

   // print object

   void print(PrinterType &out) const
    {
     if( code )
       Putobj(out,func(code));
     else
       Putobj(out,"Ok"_c);
    }
 };

} // namespace App

#endif

