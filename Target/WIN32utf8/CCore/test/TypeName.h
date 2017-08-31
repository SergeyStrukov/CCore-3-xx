/* TypeName.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_test_TypeName_h
#define CCore_test_TypeName_h

#include <CCore/inc/String.h>

#include <typeinfo>

#include <cxxabi.h>
#include <stdlib.h>

namespace App {

/* TypeName<T>() */

template <class T>
String TypeName()
 {
  const char *name=typeid (T).name();

  int status;

  char *result=__cxxabiv1::__cxa_demangle(name,0,0,&status);

  if( result )
    {
     String ret(result);

     free(result);

     return ret;
    }

  return String("<error>");
 }

} // namespace App

#endif
