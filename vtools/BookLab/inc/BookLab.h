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
#include <CCore/inc/ErrorText.h>

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

enum Align
 {
  Left,
  Right,
  Center
 };

/* functions */

template <class T>
T DefNull() { return Null; }

inline VColor DefNoColor() { return NoColor; }

inline Effect DefNoEffect() { return NoEffect; }

template <class Ptr>
auto SafePtr(Ptr &ptr)
 {
  return !ptr ? 0 : ptr.getPtr() ;
 }

/* classes */

template <class Ctx,class T> struct BindCtx;

struct Ratio;

template <class T,T Def()=DefNull> struct OptData;

struct NamedObj;

template <class ... TT> struct NamedPtr;

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

struct LastDefaults;

struct Scope;

struct Section;

struct Doc;

struct Bitmap;

struct Collapse;

struct Item;

struct ItemList;

struct TextList;

struct Border;

struct Cell;

struct Table;

struct Link;

struct Span;

struct TextLine;

struct FixedText;

struct OneLine;

struct MultiLine;

struct Text;


class Book;

/* struct BindCtx<Ctx,T> */

template <class Ctx,class T>
struct BindCtx
 {
  Ctx *ctx;
  const T &obj;

  BindCtx(Ctx *ctx_,const T &obj_) : ctx(ctx_),obj(obj_) {}
 };

/* struct Ratio */

struct Ratio
 {
  Coord a = 1 ;
  Coord b = 1 ;

  operator Video::Ratio() const { return Div(a,b); }
 };

inline Ratio DefRatioOne() { return {1}; }

inline Ratio DefRatioTwo() { return {2}; }

/* struct OptData<T,T Def()> */

template <class T,T Def()>
struct OptData
 {
  T data = Def() ;
  bool def = true ;

  T get() const { return def? Def() : data ; }

  void set(T data_) { data=data_; def=false; }

  void clear() { def=true; }
 };

/* struct NamedObj */

struct NamedObj
 {
  IntAnyObjPtr<Scope,Doc> scope;

  String name;
  bool open = true ;

  NamedObj & getBase() { return *this; }

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope);
   }
 };

/* struct NamedPtr<TT> */

template <class ... TT> requires ( sizeof ... (TT) > 1 )
struct NamedPtr<TT...>
 {
  String name;
  IntAnyObjPtr<TT...> ptr;

  //
  // !name && !ptr => default
  //
  // !name && +ptr => anonym
  //
  // +name && !ptr => name is not resolved
  //
  // +name && +ptr => name is resolved to ptr
  //

  bool isDef() const { return !Range(name) && !ptr ; }

  bool isAnonym() const { return !Range(name) && +ptr ; }

  bool hasName() const { return +Range(name); }

  bool hasObj() const { return +ptr; }

  bool notResolved() const { return +Range(name) && !ptr ; }

  bool isResolved() const { return +Range(name) && +ptr ; }

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(ptr);
   }
 };

template <class T>
struct NamedPtr<T>
 {
  String name;
  IntObjPtr<T> ptr;

  //
  // !name && !ptr => default
  //
  // !name && +ptr => anonym
  //
  // +name && !ptr => name is not resolved
  //
  // +name && +ptr => name is resolved to ptr
  //

  bool isDef() const { return !Range(name) && !ptr ; }

  bool isAnonym() const { return !Range(name) && +ptr ; }

  bool hasName() const { return +Range(name); }

  bool hasObj() const { return +ptr; }

  bool notResolved() const { return +Range(name) && !ptr ; }

  bool isResolved() const { return +Range(name) && +ptr ; }

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(ptr);
   }
 };

/* struct Font */

struct Font : NamedObj
 {
  String face;
  Coord size = 20 ;

  OptData<bool> bold;
  OptData<bool> italic;
  OptData<int> strength;
 };

/* struct Format */

struct Format : NamedObj
 {
  NamedPtr<Font> font; // default: null

  OptData<VColor,DefNoColor> back;
  OptData<VColor,DefNoColor> fore;
  OptData<Effect,DefNoEffect> effect;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),font);
   }
 };

/* struct SingleLine */

struct SingleLine : NamedObj
 {
  OptData<Ratio,DefRatioOne> width;
  OptData<VColor,DefNoColor> line;
 };

/* struct DoubleLine */

struct DoubleLine : NamedObj
 {
  OptData<Ratio,DefRatioOne> width;
  OptData<VColor,DefNoColor> gray;
  OptData<VColor,DefNoColor> snow;
 };

/* struct Frame */

struct Frame
 {
  // links

  IntObjPtr<Frame> prev;
  IntObjPtr<Frame> next;

  // data

  OptData<Point> inner; // default: ?DefaultInner
  OptData<Point> outer; // default: ?DefaultOuter

  OptData<VColor,DefNoColor> col;

  NamedPtr<SingleLine,DoubleLine> line; // default: null

  NamedPtr<Bitmap,Collapse,TextList,Table,Text,FixedText> body; // default: none

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

struct Page : NamedObj
 {
  String title;
  OptData<VColor,DefNoColor> back;
  OptData<VColor,DefNoColor> fore;

  NamedPtr<Page> up;   // default: null , no anonym
  NamedPtr<Page> prev; // default: null , no anonym
  NamedPtr<Page> next; // default: null , no anonym

  FrameList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),up,prev,next,list);
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
  OptData<Point> inner;
  OptData<Point> outer;
  OptData<Coord> bulletSpace;
  OptData<Coord> itemSpace;

  IntObjPtr<SingleLine> singleLine;
  IntObjPtr<DoubleLine> doubleLine;
  IntObjPtr<Format> collapseFormat;
  IntObjPtr<Format> bulletFormat;
  IntObjPtr<Border> border;
  IntObjPtr<Format> textFormat;
  IntObjPtr<Format> fixedFormat;
  IntAnyObjPtr<OneLine,MultiLine> placement;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(singleLine,doubleLine,collapseFormat,bulletFormat,border,textFormat,fixedFormat,placement);
   }
 };

/* struct LastDefaults */

struct LastDefaults
 {
  Point inner = Null ;                       // DefaultInner
  Point outer = Null ;                       // DefaultOuter
  Coord bulletSpace = 5 ;                    // DefaultBulletSpace
  Coord itemSpace = 0 ;                      // DefaultItemSpace

  IntObjPtr<SingleLine> singleLine;          // DefaultSingleLine
  IntObjPtr<DoubleLine> doubleLine;          // DefalutDoubleLine
  IntObjPtr<Format> collapseFormat;          // DefaultCollapseFormat
  IntObjPtr<Format> bulletFormat;            // DefaultBulletFormat
  IntObjPtr<Border> border;                  // DefaultBorder
  IntObjPtr<Format> textFormat;              // DefaultFormat
  IntObjPtr<Format> fixedFormat;             // DefaultFixedFormat
  IntAnyObjPtr<OneLine,MultiLine> placement; // Placement

  explicit LastDefaults(ObjectDomain &domain);

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(singleLine,doubleLine,collapseFormat,bulletFormat,border,textFormat,fixedFormat,placement);
   }
 };

/* struct Scope */

struct Scope : NamedObj
 {
  Defaults defs;

  ElementList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),defs,list);
   }
 };

/* struct Section */

struct Section
 {
  // obj

  IntAnyObjPtr<Scope,Doc> scope;

  bool open = true ;

  // data

  String comment;

  ElementList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(scope,list);
   }
 };

/* struct Doc */

struct Doc
 {
  String title;
  OptData<VColor,DefNoColor> back;
  OptData<VColor,DefNoColor> fore;

  NamedPtr<Page> start; // default: none

  Defaults defs;
  LastDefaults lastdefs;

  ElementList list;

  explicit Doc(ObjectDomain &domain);

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(start,defs,lastdefs,list);
   }
 };

/* struct Bitmap */

struct Bitmap
 {
  // obj

  IntAnyObjPtr<Scope,Doc> scope;

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

struct Collapse : NamedObj
 {
  static bool DefTrue() { return true; }

  String title;
  NamedPtr<Format> format; // default: ?DefaultCollapseFormat
  bool openlist = true ;
  OptData<bool,DefTrue> hide;

  FrameList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),format,list);
   }
 };

/* struct Item */

struct Item
 {
  // links

  IntObjPtr<Item> prev;
  IntObjPtr<Item> next;

  // data

  String bullet;

  FrameList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(prev,next,list);
   }
 };

/* struct ItemList */

struct ItemList
 {
  IntObjPtr<Item> beg;
  IntObjPtr<Item> cur;
  IntObjPtr<Item> end;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(beg,cur,end);
   }
 };

/* struct TextList */

struct TextList : NamedObj
 {
  NamedPtr<Format> format;     // default: ?DefaultBulletFormat

  OptData<Coord> bullet_space; // default: ?DefaultBulletSpace
  OptData<Coord> item_space;   // default: ?DefaultItemSpace

  ItemList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),format,list);
   }
 };

/* struct Border */

struct Border : NamedObj
 {
  OptData<Coord> space;
  OptData<Ratio,DefRatioOne> width;
  OptData<VColor,DefNoColor> line;
 };

/* struct Cell */

struct Cell : NamedObj
 {
  static ulen DefOne() { return 1; }

  OptData<ulen,DefOne> span_x;
  OptData<ulen,DefOne> span_y;

  FrameList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),list);
   }
 };

/* struct Table */

struct Table : NamedObj
 {
  NamedPtr<Border> border;         // default: ?DefaultBorder

  OptData<bool> hard;

  DynArray<Coord> width;

  DynArray<NamedPtr<Cell> > table; // default: null

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),border);

    table.apply(keeper);
   }
 };

/* struct Link */

struct Link : NamedObj
 {
  NamedPtr<Page> page; // default: none

  DynArray<ulen> index_list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),page);
   }
 };

/* struct Span */

struct Span
 {
  String body;

  NamedPtr<Format> format; // default: null

  NamedPtr<Link,Page> ref; // default: null

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(format,ref);
   }
 };

/* struct TextLine */

struct TextLine
 {
  DynArray<Span> list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    list.apply(keeper);
   }
 };

/* struct FixedText */

struct FixedText : NamedObj
 {
  NamedPtr<Format> format; // default: ?DefaultFixedFormat

  DynArray<TextLine> list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),format);

    list.apply(keeper);
   }
 };

/* struct OneLine */

struct OneLine : NamedObj
 {
  static Align DefLeft() { return Left; }

  OptData<Align,DefLeft> align;
 };

/* struct MultiLine */

struct MultiLine : NamedObj
 {
  OptData<Ratio,DefRatioOne> line_space;
  OptData<Ratio,DefRatioTwo> first_line_space;
 };

/* struct Text */

struct Text : NamedObj
 {
  NamedPtr<OneLine,MultiLine> placement; // default: ?DefaultPlacement

  NamedPtr<Format> format;               // default: ?DefaultFormat

  DynArray<Span> list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),placement,format);

    list.apply(keeper);
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

   bool linked = true ;

  private:

   void startDoc();

   class SaveContext;

   class BookContext;

  public:

   Book();

   ~Book();

   void blank();

   ErrorText load(StrLen file_name,PtrLen<char> ebuf);

   ErrorText save(StrLen file_name,PtrLen<char> ebuf) const;

   bool isLinked() const { return linked; }

   ErrorText link(PtrLen<char> ebuf);

   ErrorText book(StrLen file_name,PtrLen<char> ebuf) const;
 };

} // namespace BookLab
} // namespace App

#endif

