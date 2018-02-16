/* ErrorId.cpp */
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

#include <inc/ErrorId.h>

namespace App {

/* class ErrorId */

StrLen ErrorId::BoolFunc(int code)
 {
  return code?"Error"_c:"Ok"_c;
 }

} // namespace App

