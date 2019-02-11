/* Book.h */
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

#ifndef CCore_inc_video_book_Book_h
#define CCore_inc_video_book_Book_h

#include <CCore/inc/ddl/DDLMapTypes.h>

#include <CCore/inc/video/Color.h>

#include <CCore/inc/ErrorText.h>

namespace CCore {
namespace Video {
namespace Book {

/* namespace TypeDef */

#include "Book1.TypeDef.gen.h"

/* consts */

inline constexpr VColor NoColor = (VColor)0xFFFF'FFFFu ;


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

   class Pretext;

   class FromFS;

   class FromVolume;

   template <class Engine>
   ErrorText loadFrom(StrLen file_name,PtrLen<char> ebuf);

  public:

   BookMap();

   ~BookMap();

   void blank();

   ErrorText load(StrLen file_name,PtrLen<char> ebuf);

   TypeDef::Book * get() const { return book; } // null on blank, non-null on successful load
 };

} // namespace Book
} // namespace Video
} // namespace CCore

#endif
