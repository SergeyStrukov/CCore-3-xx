/* BookLab.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef BookLab_h
#define BookLab_h

#include <inc/App.h>

#include <CCore/inc/MemPageHeap.h>
#include <CCore/inc/ObjectDomain.h>
#include <CCore/inc/String.h>
#include <CCore/inc/Array.h>

namespace App {
namespace BookLab {

/* consts */

inline constexpr VColor NoColor = (VColor)0xFFFF'FFFF ;

enum Effect
 {
  NoEffect,
  Underline,
  Strikeout
 };

/* classes */

struct Ratio;

struct Font;

struct Format;


struct SingleLine;

struct DoubleLine;

struct Frame;

struct Page;

struct Scope;

struct Section;

struct Doc;


class Book;

/* struct Ratio */

struct Ratio
 {
  Coord a = 1 ;
  Coord b = 1 ;

  operator Video::Ratio() const { return Div(a,b); }
 };

/* struct Font */

struct Font
 {
  // obj

  String name;
  bool open = true ;

  // data

  String face;
  Coord size = 20 ;
  bool bold = false ;
  bool italic = false ;
  int strength = 0 ;
 };

/* struct Format */

struct Format
 {
  // obj

  String name;
  bool open = true ;

  // data

  IntObjPtr<Font> font;

  VColor back = NoColor ;
  VColor fore = NoColor ;
  Effect effect = NoEffect ;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(font);
   }
 };

/* class Book */

class Book : NoCopy
 {
   class Domain : public ObjectDomain
    {
      static constexpr ulen MemCap = 100_MByte ;

      PageHeap heap;

     private:

      virtual void * try_alloc(ulen len) { return heap.alloc(len); }

      virtual void free(void *mem) { heap.free(mem); }

     public:

      Domain() : ObjectDomain(MemCap) {}

      ~Domain() { cleanup(); }
    };

   Domain domain;

  public:

   Book();

   ~Book();

   void blank();

   void load(StrLen file_name);

   void save(StrLen file_name) const;
 };

} // namespace BookLab
} // namespace App

#endif

