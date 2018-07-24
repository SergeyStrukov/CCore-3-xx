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
#include <CCore/inc/ForLoop.h>

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

struct Ratio;

template <class T,T Def()=DefNull> struct OptData;

struct NamedObj;

template <class ... TT> struct NamedPtr;

template <ulen RowCount> struct TableLayout;


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


template <class IntList> class IntListCur;

struct Index;

class NextIndex;

template <class Ctx,class T> struct BindCtx;

struct Config;

class Book;

/* struct Ratio */

struct Ratio
 {
  Coord a = 1 ;
  Coord b = 1 ;

  operator Video::Ratio() const { return Div(a,b); }

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"#;/#;",a,b);
   }
 };

inline Ratio DefRatioOne() { return {1}; }

inline Ratio DefRatioTwo() { return {2}; }

/* struct OptData<T,T Def()> */

template <class T,T Def()>
struct OptData : NoCopy
 {
  T data = Def() ;
  bool def = true ;

  T get() const { return def? Def() : data ; }

  void set(T data_) { data=data_; def=false; }

  void clear() { def=true; }
 };

/* struct NamedObj */

struct NamedObj : NoCopy
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

/* struct TableLayout<ulen RowCount> */

template <ulen RowCount>
struct TableLayout
 {
  struct Col
   {
    Coord dx = 0 ;

    Coord offx[RowCount] = {} ;
   };

  Col col[3];

  struct Row
   {
    Coord dy = 0 ;
    Coord offy = 0 ;
   };

  Row row[RowCount];

  Point size;
 };

/* struct Font */

struct Font : NamedObj
 {
  String face;
  Coord size = 20 ;

  OptData<bool> bold;
  OptData<bool> italic;
  OptData<int> strength;

  // layout

  TableLayout<5> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[5]=
     {
      {"text"_c,"face = "_c,If(face)},
      {"Coord"_c,"size = "_c,If(size)},
      {"bool"_c,"bold = "_c,If(bold)},
      {"bool"_c,"italic = "_c,If(italic)},
      {"int"_c,"strength = "_c,If(strength)}
     };

    func(Range(table),layout);
   }
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

  // layout

  TableLayout<4> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[4]=
     {
      {"Font"_c,"font = "_c,If(font)},
      {"Color"_c,"back = "_c,If(back)},
      {"Color"_c,"fore = "_c,If(fore)},
      {"Effect"_c,"effect = "_c,If(effect)}
     };

    func(Range(table),layout);
   }
 };

/* struct SingleLine */

struct SingleLine : NamedObj
 {
  OptData<Ratio,DefRatioOne> width;
  OptData<VColor,DefNoColor> line;

  // layout

  TableLayout<2> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[2]=
     {
      {"Ratio"_c,"width = "_c,If(width)},
      {"Color"_c,"line = "_c,If(line)}
     };

    func(Range(table),layout);
   }
 };

/* struct DoubleLine */

struct DoubleLine : NamedObj
 {
  OptData<Ratio,DefRatioOne> width;
  OptData<VColor,DefNoColor> gray;
  OptData<VColor,DefNoColor> snow;

  // layout

  TableLayout<3> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[3]=
     {
      {"Ratio"_c,"width = "_c,If(width)},
      {"Color"_c,"gray = "_c,If(gray)},
      {"Color"_c,"snow = "_c,If(snow)}
     };

    func(Range(table),layout);
   }
 };

/* struct Frame */

struct Frame : NoCopy
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

struct FrameList : NoCopy
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

  // layout

  TableLayout<6> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[6]=
     {
      {"text"_c,"title = "_c,If(title)},
      {"Color"_c,"back = "_c,If(back)},
      {"Color"_c,"fore = "_c,If(fore)},
      {"Page"_c,"up = "_c,If(up)},
      {"Page"_c,"prev = "_c,If(prev)},
      {"Page"_c,"next = "_c,If(next)},
     };

    func(Range(table),layout);
   }
 };

/* struct Element */

struct Element : NoCopy
 {
  // links

  IntObjPtr<Element> prev;
  IntObjPtr<Element> next;

  // data

  IntAnyObjPtr<Font,Format,SingleLine,DoubleLine,Page,Scope,Section,Bitmap,Collapse,TextList,
               Border,Cell,Table,Link,FixedText,OneLine,MultiLine,Text> ptr;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(prev,next,ptr);
   }
 };

/* struct ElementList */

struct ElementList : NoCopy
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

struct Defaults : NoCopy
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

  // layout

  TableLayout<12> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[12]=
     {
      {"Point"_c,"inner = "_c,If(inner)},
      {"Point"_c,"outer = "_c,If(outer)},
      {"Coord"_c,"bulletSpace = "_c,If(bulletSpace)},
      {"Coord"_c,"itemSpace = "_c,If(itemSpace)},

      {"SingleLine"_c,"singleLine = "_c,If(singleLine)},
      {"DoubleLine"_c,"doubleLine = "_c,If(doubleLine)},
      {"Format"_c,"collapseFormat = "_c,If(collapseFormat)},
      {"Format"_c,"bulletFormat = "_c,If(bulletFormat)},
      {"Border"_c,"border = "_c,If(border)},
      {"Format"_c,"textFormat = "_c,If(textFormat)},
      {"Format"_c,"fixedFormat = "_c,If(fixedFormat)},
      {"{OneLine,MultiLine}"_c,"placement = "_c,If(placement)},
     };

    func(Range(table),layout);
   }
 };

/* struct LastDefaults */

struct LastDefaults : NoCopy
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
  IntAnyObjPtr<OneLine,MultiLine> placement; // DefaultPlacement

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

struct Section : NoCopy
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

struct Doc : NoCopy
 {
  // data

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

  // layout

  TableLayout<4> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[4]=
     {
      {"text"_c,"title = "_c,If(title)},
      {"Color"_c,"back = "_c,If(back)},
      {"Color"_c,"fore = "_c,If(fore)},
      {"Page"_c,"start = "_c,If(start)}
     };

    func(Range(table),layout);
   }
 };

/* struct Bitmap */

struct Bitmap : NoCopy
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

  // layout

  TableLayout<1> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[1]=
     {
      {"text"_c,"file_name = "_c,If(file_name)}
     };

    func(Range(table),layout);
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

  // layout

  TableLayout<4> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[4]=
     {
      {"text"_c,"title = "_c,If(title)},
      {"Format"_c,"format = "_c,If(format)},
      {"bool"_c,"openlist = "_c,If(openlist)},
      {"bool"_c,"hide = "_c,If(hide)}
     };

    func(Range(table),layout);
   }
 };

/* struct Item */

struct Item : NoCopy
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

struct ItemList : NoCopy
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

  // layout

  TableLayout<3> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[3]=
     {
      {"Format"_c,"format = "_c,If(format)},
      {"Coord"_c,"bullet_space = "_c,If(bullet_space)},
      {"Coord"_c,"item_space = "_c,If(item_space)}
     };

    func(Range(table),layout);
   }
 };

/* struct Border */

struct Border : NamedObj
 {
  OptData<Coord> space;
  OptData<Ratio,DefRatioOne> width;
  OptData<VColor,DefNoColor> line;

  // layout

  TableLayout<3> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[3]=
     {
      {"Coord"_c,"space = "_c,If(space)},
      {"Ratio"_c,"width = "_c,If(width)},
      {"Color"_c,"line = "_c,If(line)}
     };

    func(Range(table),layout);
   }
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

  // layout

  TableLayout<2> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[2]=
     {
      {"ulen"_c,"span_x = "_c,If(span_x)},
      {"ulen"_c,"span_y = "_c,If(span_y)}
     };

    func(Range(table),layout);
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

  // layout

  TableLayout<2> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[2]=
     {
      {"Border"_c,"border = "_c,If(border)},
      {"bool"_c,"hard"_c,If(hard)}
     };

    func(Range(table),layout);
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

  // layout

  TableLayout<1> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[1]=
     {
      {"Page"_c,"page = "_c,If(page)}
     };

    func(Range(table),layout);
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

  // layout

  TableLayout<1> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[1]=
     {
      {"Format"_c,"format = "_c,If(format)}
     };

    func(Range(table),layout);
   }
 };

/* struct OneLine */

struct OneLine : NamedObj
 {
  static Align DefLeft() { return Left; }

  OptData<Align,DefLeft> align;

  // layout

  TableLayout<1> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[1]=
     {
      {"Align"_c,"align = "_c,If(align)}
     };

    func(Range(table),layout);
   }
 };

/* struct MultiLine */

struct MultiLine : NamedObj
 {
  OptData<Ratio,DefRatioOne> line_space;
  OptData<Ratio,DefRatioTwo> first_line_space;

  // layout

  TableLayout<2> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[2]=
     {
      {"Ratio"_c,"line_space = "_c,If(line_space)},
      {"Ratio"_c,"first_line_space = "_c,If(first_line_space)}
     };

    func(Range(table),layout);
   }
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

  // layout

  TableLayout<2> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[2]=
     {
      {"{OneLine,MultiLine}"_c,"placement = "_c,If(placement)},
      {"Format"_c,"format = "_c,If(format)}
     };

    func(Range(table),layout);
   }
 };

//----------------------------------------------------------------------------------------

/* class IntListCur<IntList> */

template <class IntList>
class IntListCur
 {
   using Ptr = decltype( SafePtr(Meta::TypeBox<IntList &>::Get().beg) ) ;

   Ptr ptr;

  public:

   explicit IntListCur(IntList &list) : ptr(SafePtr(list.beg)) {}

   bool operator + () const { return ptr; }

   auto & operator * () const { return *ptr; }

   void operator ++ () { ptr=SafePtr(ptr->next); }
 };

template <class IntList>
auto ForIntList(IntList &list) { return ForLoop(IntListCur(list)); }

/* struct Index */

struct Index
 {
  unsigned index;
 };

/* class NextIndex */

class NextIndex : NoCopy
 {
   unsigned next_index = 1 ;

  public:

   NextIndex() {}

   Index getIndex();
 };

/* struct BindCtx<Ctx,T> */

template <class Ctx,class T>
struct BindCtx
 {
  Ctx *ctx;
  const T &obj;

  BindCtx(Ctx *ctx_,const T &obj_) : ctx(ctx_),obj(obj_) {}
 };

/* struct Config */

struct Config
 {
  // user

  RefVal<VColor> gray  = Gray ;
  RefVal<VColor> snow  = Snow ;
  RefVal<VColor> face  = Black ;
  RefVal<VColor> alert = Pink ;

  // app

  RefVal<Fraction> line_width = Fraction(6,2) ;

  RefVal<Coord> table_dxy     = 3 ;
  RefVal<Coord> element_space = 5 ;
  RefVal<Coord> knob_dxy = 20 ;

  RefVal<VColor> table   = Black ;
  RefVal<VColor> element = Black ;
  RefVal<VColor> text    = Blue ;

  RefVal<CCore::Video::Font> text_font;
  RefVal<CCore::Video::Font> element_font;

  template <class AppPref>
  Config(const UserPreference &user_pref,const AppPref &app_pref) noexcept
   {
    bindUser(user_pref.get(),user_pref.getSmartConfig());
    bindApp(app_pref.get());
   }

  template <class Bag,class Proxy>
  void bindUser(const Bag &bag,Proxy proxy)
   {
    Used(proxy);

    gray.bind(bag.gray);
    snow.bind(bag.snow);
    face.bind(bag.face);
    alert.bind(bag.alert);
   }

  template <class Bag>
  void bindApp(const Bag &bag)
   {
    line_width.bind(bag.line_width);
    table_dxy.bind(bag.table_dxy);
    element_space.bind(bag.element_space);
    knob_dxy.bind(bag.knob_dxy);
    table.bind(bag.table);
    element.bind(bag.element);
    text.bind(bag.text);
    text_font.bind(bag.text_font.font);
    element_font.bind(bag.element_font.font);
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

   static StrLen Pretext();

   class SaveContext;

   template <class T> struct LoadType;

   class LoadContext;

   class BookContext;

   class ScopeContext;

   void setScope();

   class ShowData;

   class ShowName;

   class PrepareContext;

   class DrawContext;

  public:

   Book();

   ~Book();

   void collect() { domain.collect(); }

   void blank();

   ErrorText load(StrLen file_name,PtrLen<char> ebuf);

   ErrorText save(StrLen file_name,PtrLen<char> ebuf) const;

   bool isLinked() const { return linked; }

   ErrorText link(PtrLen<char> ebuf);

   ErrorText book(StrLen file_name,PtrLen<char> ebuf) const;

   Point prepare(const Config &cfg) const;

   void draw(const Config &cfg,DrawBuf buf,Point base) const;
 };

} // namespace BookLab
} // namespace App

#endif

