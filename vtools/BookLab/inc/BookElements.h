/* BookElements.h */
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

#ifndef BookElements_h
#define BookElements_h

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

enum Align
 {
  Left,
  Right,
  Center
 };

enum Strength : int
 {
  NoStrength = 0
 };

/* functions */

template <class T>
T DefNull() { return Null; }

inline VColor DefNoColor() { return NoColor; }

inline Effect DefNoEffect() { return NoEffect; }

inline Align DefLeft() { return Left; }

inline Strength DefNoStrength() { return NoStrength; }

inline bool DefTrue() { return true; }

inline ulen DefOne() { return 1; }

/* classes */

struct Ratio;

template <class T> struct OptDataBase;

template <class T,T Def()=DefNull> struct OptData;

struct OpenFlag;

struct NamedObj;

template <class ... TT> struct NamedPtr;

template <ulen RowCount> struct TableLayout;

template <class T> struct CommonList;


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

/* struct OptDataBase<T> */

template <class T>
struct OptDataBase
 {
  T data;
  bool def;
 };

/* struct OptData<T,T Def()> */

template <class T,T Def()>
struct OptData : OptDataBase<T>
 {
  using OptDataBase<T>::data;
  using OptDataBase<T>::def;

  OptData() noexcept
   {
    data=Def();
    def=true;
   }

  T get() const { return def? Def() : data ; }

  void set(T data_) { data=data_; def=false; }

  void clear() { def=true; }
 };

/* struct OpenFlag */

struct OpenFlag : NoCopy
 {
  bool open = true ;

  void change() { open=!open; }
 };

/* struct NamedObj */

struct NamedObj : OpenFlag
 {
  IntAnyObjPtr<Scope,Doc> scope;

  String name;

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

  bool isDef() const { return !name.getLen() && !ptr ; }

  bool isAnonym() const { return !name.getLen() && +ptr ; }

  bool hasName() const { return +name.getLen(); }

  bool hasObj() const { return +ptr; }

  bool notResolved() const { return +name.getLen() && !ptr ; }

  bool isResolved() const { return +name.getLen() && +ptr ; }

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

  bool isDef() const { return !name.getLen() && !ptr ; }

  bool isAnonym() const { return !name.getLen() && +ptr ; }

  bool hasName() const { return +name.getLen(); }

  bool hasObj() const { return +ptr; }

  bool notResolved() const { return +name.getLen() && !ptr ; }

  bool isResolved() const { return +name.getLen() && +ptr ; }

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

/* struct CommonList<T> */

template <class T>
struct CommonList : NoCopy
 {
  IntObjPtr<T> beg;
  IntObjPtr<T> cur;
  IntObjPtr<T> end;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(beg,cur,end);
   }

  bool canBeg() { return canPrev(); }

  bool canEnd() { return canNext(); }

  bool canPrev() { return +cur && +cur->prev ; }

  bool canNext() { return +cur && +cur->next ; }

  bool gotoBeg() { if( canBeg() ) { cur=beg; return true; } return false; }

  bool gotoEnd() { if( canEnd() ) { cur=end; return true; } return false; }

  bool gotoPrev() { if( canPrev() ) { cur=cur->prev; return true; } return false; }

  bool gotoNext() { if( canNext() ) { cur=cur->next; return true; } return false; }

  bool movePrev()
   {
    if( canPrev() )
      {
       IntObjPtr<T> obj=cur;

       delPrev();

       insBefore(obj);

       return true;
      }

    return false;
   }

  bool delPrev()
   {
    if( +cur )
      {
       IntObjPtr<T> prev=cur->prev;
       IntObjPtr<T> next=cur->next;

       if( +prev ) prev->next=next; else beg=next;

       if( +next ) next->prev=prev; else end=prev;

       if( +prev ) cur=prev; else cur=next;

       return true;
      }

    return false;
   }

  void insBefore(IntObjPtr<T> elem)
   {
    if( +cur )
      {
       IntObjPtr<T> prev=cur->prev;

       cur->prev=elem;
       elem->prev=prev;
       elem->next=cur;

       if( +prev )
         {
          prev->next=elem;
         }
       else
         {
          beg=elem;
         }
      }
    else
      {
       elem->prev=Null;
       elem->next=Null;
       beg=elem;
       end=elem;
      }

    cur=elem;
   }

  bool moveNext()
   {
    if( canNext() )
      {
       IntObjPtr<T> obj=cur;

       del();

       insAfter(obj);

       return true;
      }

    return false;
   }

  bool del()
   {
    if( +cur )
      {
       IntObjPtr<T> prev=cur->prev;
       IntObjPtr<T> next=cur->next;

       if( +prev ) prev->next=next; else beg=next;

       if( +next ) next->prev=prev; else end=prev;

       if( +next ) cur=next; else cur=prev;

       return true;
      }

    return false;
   }

  void insAfter(IntObjPtr<T> elem)
   {
    if( +cur )
      {
       IntObjPtr<T> next=cur->next;

       cur->next=elem;
       elem->prev=cur;
       elem->next=next;

       if( +next )
         {
          next->prev=elem;
         }
       else
         {
          end=elem;
         }
      }
    else
      {
       elem->prev=Null;
       elem->next=Null;
       beg=elem;
       end=elem;
      }

    cur=elem;
   }

  void append(IntObjPtr<T> elem)
   {
    IntObjPtr<T> prev=end;

    if( +prev )
      {
       elem->prev=prev;
       prev->next=elem;

       end=elem;
      }
    else
      {
       beg=elem;
       end=elem;
      }
   }
 };

/* struct Font */

struct Font : NamedObj
 {
  String face;
  Coord size = 20 ;

  OptData<bool> bold;
  OptData<bool> italic;
  OptData<Strength,DefNoStrength> strength;

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

  // link

  ulen index = MaxULen ;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(prev,next,line,body);
   }
 };

/* struct FrameList */

struct FrameList : CommonList<Frame>
 {
  // layout

  TableLayout<5> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    if( +cur )
      {
       Row table[5]=
        {
         {"Point"_c,"inner = "_c,If(cur->inner)},
         {"Point"_c,"outer = "_c,If(cur->outer)},
         {"Color"_c,"col = "_c,If(cur->col)},
         {"{SingleLine,DoubleLine}"_c,"line = "_c,If(cur->line)},
         {"{...}"_c,"body = "_c,If(cur->body)}
        };

       func(Range(table),layout);
      }
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

  // link

  ulen index = MaxULen ;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),up,prev,next,list);
   }

  // layout

  TableLayout<7> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[7]=
     {
      {"text"_c,"title = "_c,If(title)},
      {"Color"_c,"back = "_c,If(back)},
      {"Color"_c,"fore = "_c,If(fore)},
      {"Page"_c,"up = "_c,If(up)},
      {"Page"_c,"prev = "_c,If(prev)},
      {"Page"_c,"next = "_c,If(next)},
      {"Frame[]"_c,"list = "_c,If(list)}
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

  // layout

  Pane pane;
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

  void insBefore(Element *ptr,ExtObjPtr<Element> obj);

  void insAfter(Element *ptr,ExtObjPtr<Element> obj);

  void insFirst(ExtObjPtr<Element> obj);

  Element * del(Element *ptr);

  void append(IntObjPtr<Element> elem)
   {
    IntObjPtr<Element> prev=end;

    if( +prev )
      {
       elem->prev=prev;
       prev->next=elem;

       end=elem;
      }
    else
      {
       beg=elem;
       end=elem;
      }
   }

  // layout

  Point size;
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

  // layout

  Point size;
 };

/* struct Section */

struct Section : OpenFlag
 {
  // obj

  IntAnyObjPtr<Scope,Doc> scope;

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

  TableLayout<5> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[5]=
     {
      {"text"_c,"title = "_c,If(title)},
      {"Format"_c,"format = "_c,If(format)},
      {"bool"_c,"openlist = "_c,If(openlist)},
      {"bool"_c,"hide = "_c,If(hide)},
      {"Frame[]"_c,"list = "_c,If(list)}
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

struct ItemList : CommonList<Item>
 {
  // layout

  TableLayout<2> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    if( +cur )
      {
       Row table[2]=
        {
         {"text"_c,"bullet = "_c,If(cur->bullet)},
         {"Frame[]"_c,"list = "_c,If(cur->list)}
        };

       func(Range(table),layout);
      }
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

  TableLayout<4> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[4]=
     {
      {"Format"_c,"format = "_c,If(format)},
      {"Coord"_c,"bullet_space = "_c,If(bullet_space)},
      {"Coord"_c,"item_space = "_c,If(item_space)},
      {"Item[]"_c,"list = "_c,If(list)}
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
  OptData<ulen,DefOne> span_x;
  OptData<ulen,DefOne> span_y;

  FrameList list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),list);
   }

  // layout

  TableLayout<3> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[3]=
     {
      {"ulen"_c,"span_x = "_c,If(span_x)},
      {"ulen"_c,"span_y = "_c,If(span_y)},
      {"Frame[]"_c,"list = "_c,If(list)}
     };

    func(Range(table),layout);
   }
 };

/* struct Table */

struct Table : NamedObj
 {
  NamedPtr<Border> border;         // default: ?DefaultBorder

  OptData<bool> hard;

  struct Data
   {
    DynArray<Coord> width;
    DynArray<NamedPtr<Cell> > cells; // default: null
    DynArray<Coord> cellsize;
   };

  Data table;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),border);

    table.cells.apply(keeper);
   }

  // layout

  TableLayout<3> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table_[3]=
     {
      {"Border"_c,"border = "_c,If(border)},
      {"bool"_c,"hard = "_c,If(hard)},
      {"Table"_c,"table = "_c,If(table)}
     };

    func(Range(table_),layout);
   }
 };

/* struct Link */

struct Link : NamedObj
 {
  IntObjPtr<Frame> frame;

  IntObjPtr<Page> page;
  RefArray<ulen> index_list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),frame,page);
   }

  void set(IntObjPtr<Frame> frame_)
   {
    frame=frame_;
    page=Null;
    index_list.erase();
   }

  // layout

  TableLayout<1> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[1]=
     {
      {"Link"_c,"link = "_c,If(*this)}
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

  // editor cache

  Coord dx = 0 ;

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

  // editor cache

  Coord dx = 0 ;

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

  TableLayout<2> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[2]=
     {
      {"Format"_c,"format = "_c,If(format)},
      {"FixedText"_c,"text = "_c,If(list)}
     };

    func(Range(table),layout);
   }
 };

/* struct OneLine */

struct OneLine : NamedObj
 {
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

  DynArray<TextLine> list;

  template <class Keeper>
  void keepAlive(Keeper keeper)
   {
    keeper(getBase(),placement,format);

    list.apply(keeper);
   }

  // layout

  TableLayout<3> layout;

  template <class Row,template <class T> class If,class Func>
  void apply(Func func)
   {
    Row table[3]=
     {
      {"{OneLine,MultiLine}"_c,"placement = "_c,If(placement)},
      {"Format"_c,"format = "_c,If(format)},
      {"Text"_c,"text = "_c,If(list)}
     };

    func(Range(table),layout);
   }
 };

} // namespace BookLab
} // namespace App

#endif

