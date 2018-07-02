/* DrawBook.h */
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

#ifndef DrawBook_h
#define DrawBook_h

#include <inc/Book.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/ElementPool.h>

#include <CCore/inc/video/FontLookup.h>
#include <CCore/inc/video/Bitmap.h>

namespace App {
namespace DrawBook {

/* using */

using Effect = Book::TypeDef::Format::Effect ;

using RefType = AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page,Book::TypeDef::Collapse> ;

/* Cast() */

inline VColor CastColor(Book::TypeDef::VColor vc) { return (VColor)vc; }

inline Coord CastCoord(Book::TypeDef::Coord x) { return (Coord)x; }

inline Point Cast(Book::TypeDef::Point p) { return {CastCoord(p.x),CastCoord(p.y)}; }

inline Ratio Cast(Book::TypeDef::Ratio r) { return Div(CastCoord(r.a),CastCoord(r.b)); }

/* size functions */

void GuardSizeOverflow(const char *name);

Coord AddSize(Coord a,Coord b);

Coord MulSize(UIntType count,Coord x)
 {
  if( x>0 && count>SIntFunc<Coord>::UInt(SIntFunc<Coord>::MaxPositive/x) ) GuardSizeOverflow("App::DrawBook::MulSize");

  return Coord(count)*x;
 }

Point StackY(Point a,Point b);

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

template <class T,class S>
T CastAnyPtr(S obj)
 {
  T ret;

  obj.apply( [&ret] (auto *ptr) { ret=ptr; } );

  return ret;
 }

/* classes */

struct Config;

class BitmapMap;

class FontMap;

struct FrameExt;

struct FrameExt_OneLine;

struct FrameExt_MultiLine;

struct FrameExt_TextList;

struct FrameExt_Collapse;

struct FrameExt_Table;

class FrameMap;

class ExtMap;

template <class T> class AutoCast;

struct RefPane;

struct Prepare;

struct DrawOut;

struct Draw;

class Shape;

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

/* struct FrameExt_TextList */

struct FrameExt_TextList : FrameExt
 {
  Coord bullet_len   = 0 ;
  Coord bullet_space = 0 ;
  Coord item_space   = 0 ;

  struct Delta
   {
    Coord by1 = 0 ;
    Coord dy1 = 0 ;
    Coord by2 = 0 ;
   };

  DynArray<Delta> delta;
 };

/* struct FrameExt_Collapse */

struct FrameExt_Collapse : FrameExt
 {
  Coord len = 0 ;
 };

/* struct FrameExt_Table */

struct FrameExt_Table : FrameExt
 {
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

/* class AutoCast<T> */

template <class T>
class AutoCast
 {
   T *ptr;

  public:

   explicit AutoCast(T *ptr_) : ptr(ptr_) {}

   template <class S>
   operator S * () const { return static_cast<S *>(ptr); }
 };

/* struct RefPane */

struct RefPane
 {
  Pane pane;
  RefType ref;
 };

/* struct Prepare */

struct Prepare
 {
  const Config &cfg;
  ExtMap &map;
  Ratio scale;
  DynArray<RefPane> &refs;

  // private

  void addRef(RefType ref,Pane pane);

  static RefType CastRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref);

  void addRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref,Pane pane);

   // common

  Font use(const Book::TypeDef::Format *fmt);

  Font useFixed(const Book::TypeDef::Format *fmt);

  Font over(Font font,const Book::TypeDef::Format *fmt);

  static TextSize SizeSpan(Font font,StrLen text);

  static Coord SizeSpace(Font font);

   // size()

   void correctRefs(ulen refs_len,Coord delta_x);

   Coord sizeSpan(Font font,Book::TypeDef::Span span,Point base);

   struct LineSize
    {
     Coord dx;
     Coord edx;
    };

   LineSize sizeSpan(const Book::TypeDef::Format *prev_fmt,Font font,Coord space_dx,Book::TypeDef::Span span,Point base);

   Coord sizeLine(Font font,Coord space_dx,PtrLen<const Book::TypeDef::Span> range,Point base);

   Point size(Font font,Coord space_dx,PtrLen<const Book::TypeDef::Span> range,Book::TypeDef::OneLine *placement,FrameExt_OneLine *ext,Coord wdx,Point base);

   Point size(Font font,Coord space_dx,PtrLen<const Book::TypeDef::Span> range,Book::TypeDef::MultiLine *placement,FrameExt_MultiLine *ext,Coord wdx,Point base);

  Point size(Book::TypeDef::Text *obj,FrameExt *ext,Coord wdx,Point base);

   Coord sizeLine(Font font,const Book::TypeDef::Line &line,Point base);

  Point size(Book::TypeDef::FixedText *obj,FrameExt *ext,Coord wdx,Point base);

  Point size(Book::TypeDef::Bitmap *obj,FrameExt *ext,Coord wdx,Point base);

   Coord sizeBullet(Font font,StrLen text);

   struct ItemBase
    {
     Coord by = 0 ;
     bool ok = false ;
    };

   ItemBase getBase(Book::TypeDef::Text *obj);

   ItemBase getBase(Book::TypeDef::FixedText *obj);

   ItemBase getBase(Book::TypeDef::Bitmap *obj);

   ItemBase getBase(Book::TypeDef::TextList *obj);

   ItemBase getBase(Book::TypeDef::Collapse *obj);

   ItemBase getBase(Book::TypeDef::Table *obj);

   ItemBase getBase(Book::TypeDef::Frame *frame);

   Point sizeItem(FontSize fs,Book::TypeDef::ListItem item,FrameExt_TextList::Delta &delta,Coord bullet_dx,Coord wdx,Point base);

  Point size(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,Coord wdx,Point base);

  Point size(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,Coord wdx,Point base);

  Point size(Book::TypeDef::Table *obj,FrameExt_Table *ext,Coord wdx,Point base);

  template <class T>
  Point sizeAny(T body,FrameExt *ext,Coord wdx,Point base);

   // frame

  Point operator () (PtrLen<Book::TypeDef::Frame> list,Coord wdx,Point base);

  // public

  Point operator () (Book::TypeDef::Frame *frame,Coord wdx,Point base);
 };

/* struct DrawOut */

struct DrawOut
 {
  DrawBuf buf;
  Pane pane;
  Point base;

  Point fullBase() const { return pane.getBase()+base; }

  DrawOut addX(Coord dx) const { return {buf,pane,base.addX(dx)}; }

  DrawOut addY(Coord dy) const { return {buf,pane,base.addY(dy)}; }

  DrawOut add(Coord dx,Coord dy) const { return {buf,pane,base+Point(dx,dy)}; }

  void back(TextSize ts,VColor back);

  void effect(TextSize ts,Effect effect,VColor fore,MCoord width);

  void text(Font font,StrLen text,VColor fore);

  void bitmap(const Bitmap *bitmap);

  void drawPlus(const Config &cfg,Coord len);

  void drawMinus(const Config &cfg,Coord len);
 };

/* struct Draw */

struct Draw
 {
  const Config &cfg;
  ExtMap &map;
  VColor fore;

  // private

   // GetAnyBack()

  static VColor GetBack(const Book::TypeDef::Format *fmt);

  static VColor GetBack(const Book::TypeDef::Text *obj);

  static VColor GetBack(const Book::TypeDef::FixedText *obj);

  static VColor GetBack(const Book::TypeDef::Bitmap *obj);

  static VColor GetBack(const Book::TypeDef::TextList *obj);

  static VColor GetBack(const Book::TypeDef::Collapse *obj);

  static VColor GetBack(const Book::TypeDef::Table *obj);

  template <class T>
  static VColor GetAnyBack(T body);

   // drawAnyLine()

  void drawLine(const Book::TypeDef::SingleLine *obj,Pane pane,DrawBuf buf);

  void drawLine(const Book::TypeDef::DoubleLine *obj,Pane pane,DrawBuf buf);

  template <class T>
  void drawAnyLine(T line,Pane pane,DrawBuf buf);

   // common

  struct Format
   {
    Font font;
    VColor back;
    VColor fore;
    Effect effect;

    Format over(ExtMap &map,const Book::TypeDef::Format *fmt) const;
   };

  Format use(const Book::TypeDef::Format *fmt);

  Format useFixed(const Book::TypeDef::Format *fmt);

  Format useBack(const Book::TypeDef::Format *fmt);

  Point drawSpan(Format format,StrLen text,DrawOut out);

  Point drawSpace(Format format,DrawOut out);

   // draw()

   Point drawSpan(Format format,Book::TypeDef::Span span,DrawOut out);

   Point drawSpan(const Book::TypeDef::Format *prev_fmt,Format format,Book::TypeDef::Span span,DrawOut out);

   void drawLine(Format format,PtrLen<const Book::TypeDef::Span> line,DrawOut out);

   void draw(Format format,PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::OneLine *placement,FrameExt_OneLine *ext,DrawOut out);

   void draw(Format format,PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement,FrameExt_MultiLine *ext,DrawOut out);

  void draw(Book::TypeDef::Text *obj,FrameExt *ext,DrawOut out);

   void drawLine(Format format,PtrLen<const Book::TypeDef::FixedSpan> line,DrawOut out);

  void draw(Book::TypeDef::FixedText *obj,FrameExt *ext,DrawOut out);

  void draw(Book::TypeDef::Bitmap *obj,FrameExt *ext,DrawOut out);

   void drawBullet(Format format,StrLen text,Coord bullet_len,DrawOut out);

   Coord drawItem(Format format,Book::TypeDef::ListItem item,FrameExt_TextList::Delta delta,Coord bullet_len,Coord bullet_space,DrawOut out);

  void draw(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,DrawOut out);

  void draw(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,DrawOut out);

  void draw(Book::TypeDef::Table *obj,FrameExt_Table *ext,DrawOut out);

  template <class T>
  void drawAny(T body,FrameExt *ext,DrawOut out);

   // frame

  Point operator () (Book::TypeDef::Frame *frame,DrawOut out);

  Point operator () (PtrLen<Book::TypeDef::Frame> list,DrawOut out);

  // public

  Coord operator () (Book::TypeDef::Frame *frame,DrawBuf buf,Point base);
 };

/* class Shape */

class Shape
 {
   Book::TypeDef::Frame *frame = 0 ;

   Coord down = 0 ;
   Point size;

   DynArray<RefPane> refs;

  private:

   void prepare(const Config &cfg,ExtMap &map,Ratio scale,Coord wdx);

   void draw(const Config &cfg,ExtMap &map,VColor fore,DrawBuf buf,Point base) const;

   bool hit(Point point) const;

   RefType getRef(Point point) const;

  public:

   Shape() noexcept {}

   Coord getDown() const { return down; }

   Point getSize() const { return size; }

   Point set(const Config &cfg,ExtMap &map,Ratio scale,Book::TypeDef::Frame &frame,Coord wdx,Coord down);

   void draw(const Config &cfg,ExtMap &map,VColor fore,DrawBuf buf,Coord pos_x,Coord pos_y) const;

   bool hit(Point point,Coord pos_x,Coord pos_y) const;

   RefType getRef(Point point,Coord pos_x,Coord pos_y) const;
 };

} // namespace DrawBook
} // namespace App

#endif

