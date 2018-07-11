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

struct FrameList;

struct Page;

struct Element;

struct ElementList;

struct Scope;

struct Section;

struct Doc;


struct Bitmap;

struct Collapse;

struct TextList;

struct Table;

struct Text;

struct FixedText;


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

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  String face;      // not default
  Coord size = 20 ; // not default
  bool bold = false ;
  bool italic = false ;
  int strength = 0 ;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct Format */

struct Format
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  IntObjPtr<Font> font;
  String font_name;

  VColor back = NoColor ;
  VColor fore = NoColor ;
  Effect effect = NoEffect ;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope,font);
   }
 };

/* struct SingleLine */

struct SingleLine
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  Ratio width = {1} ;
  VColor line = NoColor ;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct DoubleLine */

struct DoubleLine
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  Ratio width = {1} ;
  VColor gray = NoColor ;
  VColor snow = NoColor ;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct Frame */

struct Frame
 {
  // links

  IntObjPtr<Frame> prev;
  IntObjPtr<Frame> next;

  // data

  Point inner;
  bool has_inner = false ; // ?DefaultInner

  Point outer;
  bool has_outer = false ;

  VColor col = NoColor ;

  IntAnyObjPtr<SingleLine,DoubleLine> line;

  IntAnyObjPtr<Bitmap,Collapse,TextList,Table,Text,FixedText> body; // not default

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(prev,next,line,body);
   }
 };

/* struct FrameList */

struct FrameList
 {
  IntObjPtr<Frame> beg;
  IntObjPtr<Frame> cur;
  IntObjPtr<Frame> end;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(beg,cur,end);
   }
 };

/* struct Page */

struct Page
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  String title; // not default
  VColor back = NoColor ;
  VColor fore = NoColor ;

  IntObjPtr<Page> up;
  IntObjPtr<Page> prev;
  IntObjPtr<Page> next;

  FrameList list; // not default

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope,up,prev,next);

    list.keepAlive(keeper);
   }
 };

/* struct Element */

struct Element
 {
  // links

  IntObjPtr<Element> prev;
  IntObjPtr<Element> next;

  // data

  IntAnyObjPtr<Font,Format,SingleLine,DoubleLine,Page,Scope,Section,Bitmap,Collapse,TextList,Table,Text,FixedText> ptr;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(prev,next,ptr);
   }
 };

/* struct ElementList */

struct ElementList
 {
  IntObjPtr<Element> beg;
  IntObjPtr<Element> end;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(beg,end);
   }
 };

/* struct Scope */

struct Scope
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  ElementList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);

    list.keepAlive(keeper);
   }
 };

/* struct Section */

struct Section
 {
  // obj

  IntObjPtr<Scope> scope;

  bool open = true ;

  // data

  String text; // not default

  ElementList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);

    list.keepAlive(keeper);
   }
 };

/* struct Doc */

struct Doc
 {
  String title; // not default
  VColor back = NoColor ;
  VColor fore = NoColor ;
  IntObjPtr<Page> start; // not default

  ElementList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(start);

    list.keepAlive(keeper);
   }
 };

/* struct Bitmap */

struct Bitmap
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;

  // data

  String file_name;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct Collapse */

struct Collapse // TODO
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct TextList */

struct TextList // TODO
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct Table */

struct Table // TODO
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct Text */

struct Text // TODO
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct FixedText */

struct FixedText // TODO
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
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

   ExtObjPtr<Doc> doc;

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

