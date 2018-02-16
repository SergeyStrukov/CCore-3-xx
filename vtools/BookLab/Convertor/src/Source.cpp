/* Source.cpp */
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

#include <inc/Source.h>

namespace App {

/* class SourceErrorId */

StrLen SourceErrorId::Func(int code)
 {
  switch( code )
    {
     case UnknownTag : return "Unknown tag"_c;

     case BadTagText : return "Bad tag text"_c;

     default: return "???"_c;
    }
 }

} // namespace App

