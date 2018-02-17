/* ErrorText.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ErrorText_h
#define CCore_inc_ErrorText_h

#include <CCore/inc/Symbol.h>

namespace CCore {

/* word Success */

enum SuccessType { Success };

/* classes */

struct ErrorText;

template <class T> struct ObjErrorText;

/* struct ErrorText */

struct ErrorText
 {
  bool ok;
  StrLen etext;

  ErrorText() : ok(true) {}

  ErrorText(SuccessType) : ok(true) {}

  ErrorText(StrLen etext_) : ok(false),etext(TrimText(etext_)) {}
 };

/* struct ObjErrorText<T> */

template <class T>
struct ObjErrorText
 {
  bool ok;
  T obj;
  StrLen etext;

  ObjErrorText(const T &obj_) : ok(true),obj(obj_) {}

  ObjErrorText(StrLen etext_) : ok(false),obj{},etext(TrimText(etext_)) {}
 };

} // namespace CCore

#endif

