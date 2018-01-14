/* Book.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Application.h>

#include <CCore/inc/ddl/DDLMapTypes.h>

#ifndef Book_h
#define Book_h

namespace App {
namespace Book {

/* namespace TypeDef */

#include "Book.TypeDef.gen.h"

/* consts */

inline constexpr VColor NoColor = (VColor)0xFFFFFFFFu ;

inline constexpr TypeDef::Format::Effect NoEffect = 0 ;

inline constexpr TypeDef::Format::Effect Underline = 1 ;

inline constexpr TypeDef::Format::Effect Strikeout = 2 ;

inline constexpr TypeDef::OneLine::Align LineLeft   = 0 ;

inline constexpr TypeDef::OneLine::Align LineRight  = 1 ;

inline constexpr TypeDef::OneLine::Align LineCenter = 2 ;

/* classes */

class BookMap;

/* class BookMap */

class BookMap : NoCopy
 {
   void *mem;

   TypeDef::Book *book;

  private:

   static StrLen Pretext();

  public:

   BookMap();

   ~BookMap();

   void blank();

   struct Result
    {
     bool ok;
     StrLen etext;

     Result() : ok(true) {}

     Result(StrLen etext_) : ok(false),etext(TrimText(etext_)) {}
    };

   Result load(StrLen file_name,PtrLen<char> ebuf);

   TypeDef::Book * get() const { return book; }
 };

} // namespace Book
} // namespace App

#endif
