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

/* functions */

template <class T,class ... SS>
void Create(IntObjPtr<T> &ptr,ObjectDomain &domain,SS && ... ss)
 {
  ptr=IntObjPtr<T>(&domain, std::forward<SS>(ss)... );
 }

template <class T,class ... SS>
void Create(ExtObjPtr<T> &ptr,ObjectDomain &domain,SS && ... ss)
 {
  ptr=ExtObjPtr<T>(&domain, std::forward<SS>(ss)... );
 }

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

struct Defaults;

struct Scope;

struct Section;

struct Doc;


struct Bitmap;

struct Collapse;

struct ListItem;

struct TextList;

struct Border;

struct Cell;

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

  String face;        // no default
  Coord size   = 20 ; // no default
  bool bold    = false ;
  bool italic  = false ;
  int strength = 0 ;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

 //
 // IntObjPtr<Type> obj;
 // String obj_name;
 //
 // obj_name is empty
 // obj is null             obj is default
 //
 // obj_name is empty
 // obj is not null         obj is anonym
 //
 // obj_name is not empty
 // obj is null             obj is not resolved by obj_name
 //
 // obj_name is not empty
 // obj is not null         obj is resolved by obj_name
 //

/* struct Format */

struct Format
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  IntObjPtr<Font> font; // default is null
  String font_name;

  VColor back   = NoColor ;
  VColor fore   = NoColor ;
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
  bool ok_inner = false ;
  bool has_inner = false ; // ?DefaultInner

  Point outer;
  bool ok_outer = false ;
  bool has_outer = false ; // ?DefaultOuter

  VColor col = NoColor ;

  IntAnyObjPtr<SingleLine,DoubleLine> line; // default is null
  String line_name;

  IntAnyObjPtr<Bitmap,Collapse,TextList,Table,Text,FixedText> body; // no default
  String body_name;

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

  String title; // no default
  VColor back = NoColor ;
  VColor fore = NoColor ;

  IntObjPtr<Page> up; // default is null , no anonym
  String up_name;

  IntObjPtr<Page> prev; // default is null , no anonym
  String prev_name;

  IntObjPtr<Page> next; // default is null , no anonym
  String next_name;

  FrameList list;

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

/* struct Defaults */

struct Defaults
 {
  // data

  Point inner;
  bool has_inner = false ;

  Point outer;
  bool has_outer = false ;

  Coord bulletSpace = 5 ;
  bool has_bulletSpace = false ;

  Coord itemSpace = 0 ;
  bool has_itemSpace = false ;

  IntObjPtr<SingleLine> singleLine;

  IntObjPtr<DoubleLine> doubleLine;

  IntObjPtr<Format> collapseFormat;

  IntObjPtr<Format> bulletFormat;

  IntObjPtr<Border> border;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(singleLine,doubleLine,collapseFormat,bulletFormat,border);
   }
 };

/* struct Scope */

struct Scope
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  Defaults defs;

  ElementList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);

    defs.keepAlive(keeper);
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

  String text; // no default

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
  // data

  String title; // no default
  VColor back = NoColor ;
  VColor fore = NoColor ;

  IntObjPtr<Page> start; // no default
  String start_name;

  Defaults lastdefs;
  Defaults defs;

  ElementList list;

  explicit Doc(ObjectDomain &domain);

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(start);

    lastdefs.keepAlive(keeper);
    defs.keepAlive(keeper);
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

/* struct ListItem */

struct ListItem;

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

/* struct Border */

struct Border
 {
  // obj

  IntObjPtr<Scope> scope;

  String name;
  bool open = true ;

  // data

  Coord space = 0 ;
  Ratio width = {1} ;
  VColor line = NoColor ;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct Cell */

struct Cell;

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

  private:

   void startDoc();

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

