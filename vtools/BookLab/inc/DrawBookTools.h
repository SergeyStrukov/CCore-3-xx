/* DrawBookTools.h */
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

#ifndef DrawBookTools_h
#define DrawBookTools_h

#include <inc/Book.h>

#include <CCore/inc/ForLoop.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/ElementPool.h>

#include <CCore/inc/video/FontLookup.h>
#include <CCore/inc/video/Bitmap.h>

namespace App {
namespace DrawBook {

/* types */

using Effect = Book::TypeDef::Format::Effect ;

using RefType = AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page,Book::TypeDef::Collapse> ;

/* Cast() */

inline VColor CastColor(Book::TypeDef::VColor vc) { return (VColor)vc; }

inline Coord CastCoord(Book::TypeDef::Coord x) { return (Coord)x; }

inline Point Cast(Book::TypeDef::Point p) { return {CastCoord(p.x),CastCoord(p.y)}; }

inline Ratio Cast(Book::TypeDef::Ratio r) { return Div(CastCoord(r.a),CastCoord(r.b)); }

/* functions */

template <class T>
void SetArrayLen(DynArray<T> &obj,ulen len)
 {
  ulen cur=obj.getLen();

  if( cur<len )
    {
     obj.extend_default(len-cur);
    }
  else if( cur>len )
    {
     obj.shrink(cur-len);
    }
 }

template <class T>
void SetExactArrayLen(DynArray<T> &obj,ulen len)
 {
  SetArrayLen(obj,len);

  obj.shrink_extra();
 }

inline VColor Combine(Book::TypeDef::VColor vc_,VColor fallback)
 {
  VColor vc=CastColor(vc_);

  if( vc!=Book::NoColor ) return vc;

  return fallback;
 }

bool InsSpace(StrLen text);

inline Pane TextPane(Point base,TextSize ts) { return Pane(base.x,base.y-ts.by,ts.dx,ts.dy); }

/* ForTable() */

template <FuncArgType<ulen,ulen,Book::TypeDef::Cell *> Func>
void ForTable(Book::TypeDef::Table *obj,Func func)
 {
  auto width=obj->width.getRange();

  auto rows=obj->rows.getRange();

  for(ulen j : IndLim(rows.len) )
    {
     auto row=rows[j].getRange();

     for(ulen i : IndLim( Min(row.len,width.len) ) )
       {
        if( auto *cell=row[i].getPtr() ) func(i,j,cell);
       }
    }
 }

/* classes */

template <class T> struct MatrixSpan;

struct Config;

class FontMap;

class BitmapMap;

struct FrameExt;

struct FrameExt_OneLine;

struct FrameExt_MultiLine;

struct FrameExt_TextList;

struct FrameExt_Collapse;

struct TableDesc;

struct FrameExt_Table;

class FrameMap;

class ExtMap;

struct RefList;

struct RefPane;

/* struct MatrixSpan<T> */

template <class T>
struct MatrixSpan
 {
  T *base;
  ulen lenI;

  MatrixSpan(T *base_,ulen lenI_) : base(base_),lenI(lenI_) {}

  T & operator () (ulen i,ulen j) const { return base[i+j*lenI]; }
 };

/* struct Config */

struct Config
 {
  // user

  RefVal<Fraction> width = Fraction(6,2) ;

  RefVal<VColor> line =  Gray ;
  RefVal<VColor> gray =  Gray ;
  RefVal<VColor> snow =  Snow ;
  RefVal<VColor> face = Black ;

  // app

  RefVal<Font> font;
  RefVal<Font> codefont;

  Config() noexcept {}
 };

/* class FontMap */

class FontMap : NoCopy
 {
   struct Rec
    {
     Font font;
     bool ok = false ;
     bool fallback = false ;
    };

   DynArray<Rec> map;

   Ratio scale = Ratio(1,0) ;

   FontLookup lookup;

  private:

   Rec find(StrLen face,Coord size,int strength,bool bold,bool italic,Font fallback);

   Rec find(Book::TypeDef::Font *obj,Font fallback);

   static void SetSize(Font &font,Coord size);

  public:

   FontMap() : lookup(FontLookup::None) {}

   ~FontMap() {}

   void cache(FontLookup::Incremental &inc,bool use_cache=true) { lookup.cache(inc,use_cache); }

   void erase()
    {
     map.erase();

     scale=Ratio(1,0);
    }

   void setScale(Ratio scale);

   Font operator () (Book::TypeDef::Font *obj,Font fallback);
 };

/* class BitmapMap */

class BitmapMap : NoCopy
 {
   DynArray<Bitmap> map;

   String root;

  public:

   BitmapMap() {}

   ~BitmapMap() {}

   void erase() { map.erase(); root=Null; }

   void setRoot(StrLen file_name);

   const Bitmap * operator () (Book::TypeDef::Bitmap *obj); // may return 0
 };

/* struct FrameExt */

struct FrameExt
 {
  Point outer;
  Point inner;
  Point size;

  unsigned lock = 1 ;

  DynArray<Coord> downs;

  virtual ~FrameExt() {}
 };

/* struct FrameExt_OneLine */

struct FrameExt_OneLine : FrameExt
 {
  Coord offx = 0 ;
 };

/* struct FrameExt_MultiLine */

struct FrameExt_MultiLine : FrameExt
 {
  Coord first_dx = 0 ;
  Coord dy       = 0 ;
  DynArray<ulen> split;
 };

/* struct ListItemSize */

struct ListItemSize
 {
  Coord by1 = 0 ;
  Coord dy1 = 0 ;
  Coord by2 = 0 ;

  Coord down = 0 ;
 };

/* struct FrameExt_TextList */

struct FrameExt_TextList : FrameExt
 {
  Coord bullet_len   = 0 ;
  Coord bullet_space = 0 ;
  Coord item_space   = 0 ;

  DynArray<ListItemSize> size_list;
 };

/* struct FrameExt_Collapse */

struct FrameExt_Collapse : FrameExt
 {
  Coord len = 0 ;
 };

/* struct TableDesc */

struct TableDesc
 {
  PtrLen<const Coord> tdx;
  PtrLen<const Coord> tdy;
  Coord space;

  struct Cell
   {
    Point base;
    bool top  = false ;
    bool left = false ;

    void set(ulen i,ulen j)
     {
      left=(i>0);
      top=(j>0);
     }
   };

  MatrixSpan<Cell> span;

  void setBase();

  static Coord Size(PtrLen<const Coord> tdx,Coord space);

  Point getSize() const { return {Size(tdx,space),Size(tdy,space)}; }
 };

/* struct FrameExt_Table */

struct FrameExt_Table : FrameExt
 {
  DynArray<Coord> tdx;
  DynArray<Coord> tdy;
  Coord space = 0 ;

  DynArray<TableDesc::Cell> table;
  ulen lenI = 0 ;

  void alloc(ulen lenI_,ulen lenJ)
   {
    SetExactArrayLen(table,LenOf(lenI_,lenJ));

    lenI=lenI_;
   }

  void erase()
   {
    tdx.erase();
    tdy.erase();
    table.erase();
    lenI=0;
   }

  TableDesc getDesc() { return {Range(tdx),Range(tdy),space,MatrixSpan(table.getPtr(),lenI)}; }
 };

/* class FrameMap */

class FrameMap : NoCopy
 {
   MemPool pool;
   DynArray<FrameExt *> buf;

  private:

   template <class T>
   FrameExt * createType();

   FrameExt * create(Book::TypeDef::OneLine *placement);

   FrameExt * create(Book::TypeDef::MultiLine *placement);

   FrameExt * create(Book::TypeDef::Text *obj);

   FrameExt * create(Book::TypeDef::FixedText *obj);

   FrameExt * create(Book::TypeDef::Bitmap *obj);

   FrameExt * create(Book::TypeDef::TextList *obj);

   FrameExt * create(Book::TypeDef::Collapse *obj);

   FrameExt * create(Book::TypeDef::Table *obj);

   FrameExt * create(Book::TypeDef::Frame *obj);

  public:

   FrameMap() : pool(4_KByte) {}

   ~FrameMap() { erase(); }

   void erase();

   FrameExt * operator () (Book::TypeDef::Frame *obj);
 };

/* class ExtMap */

class ExtMap : NoCopy
 {
   FontMap font;
   BitmapMap bmp;
   FrameMap frame;

  public:

   ExtMap() {}

   ~ExtMap() {}

   void cache(FontLookup::Incremental &inc,bool use_cache=true) { font.cache(inc,use_cache); }

   void blank()
    {
     font.erase();
     bmp.erase();
     frame.erase();
    }

   void setScale(Ratio scale)
    {
     font.setScale(scale);
    }

   void setRoot(StrLen file_name)
    {
     bmp.setRoot(file_name);
    }

   Font operator () (Book::TypeDef::Font *obj,Font fallback) { return font(obj,fallback); }

   const Bitmap * operator () (Book::TypeDef::Bitmap *obj) { return bmp(obj); }

   FrameExt * operator () (Book::TypeDef::Frame *obj) { return frame(obj); }
 };

/* struct RefList */

struct RefList
 {
  RefType ref;
  RefArray<ulen> index_list;
 };

/* struct RefPane */

struct RefPane
 {
  Pane pane;
  RefType ref;
  RefArray<ulen> index_list;

  operator RefList() const { return {ref,index_list}; }
 };

} // namespace DrawBook
} // namespace App

#endif

