/* Shape.h */
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

#ifndef Shape_h
#define Shape_h

#include <inc/Book.h>

#include <CCore/inc/video/FontLookup.h>
#include <CCore/inc/video/Bitmap.h>

namespace App {

/* using */

using Effect = Book::TypeDef::Format::Effect ;

using RefType = AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page,Book::TypeDef::Collapse> ;

/* Cast() */

inline VColor CastColor(Book::TypeDef::VColor vc) { return (VColor)vc; }

inline Coord CastCoord(Book::TypeDef::Coord x) { return (Coord)x; }

inline Point Cast(Book::TypeDef::Point p) { return {CastCoord(p.x),CastCoord(p.y)}; }

inline Ratio Cast(Book::TypeDef::Ratio r) { return Div(CastCoord(r.a),CastCoord(r.b)); }

/* functions */

inline VColor Combine(Book::TypeDef::VColor vc_,VColor fallback)
 {
  VColor vc=CastColor(vc_);

  if( vc!=Book::NoColor ) return vc;

  return fallback;
 }

inline void Combine(VColor &dst,Book::TypeDef::VColor vc_)
 {
  VColor vc=CastColor(vc_);

  if( vc!=Book::NoColor ) dst=vc;
 }

Point StackY(Point a,Point b);

void FillBack(DrawBuf buf,Pane pane,Point base,TextSize ts,VColor back);

void MakeEffect(DrawBuf buf,Pane pane,Point base,TextSize ts,Effect effect,VColor fore,MCoord width);

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

/* classes */

class FontMap;

class BitmapMap;

struct ExtMap;

class Shape;

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

   Rec find(Book::TypeDef::Font *font,Font fallback);

   static void SetSize(Font &font,Coord size);

  public:

   FontMap() : lookup(FontLookup::None) {}

   ~FontMap() {}

   void cache(FontLookup::Incremental &inc,bool use_cache=true) { lookup.cache(inc,use_cache); }

   void erase() { map.erase(); scale=Ratio(1,0); }

   void setScale(Ratio scale);

   Font operator () (Book::TypeDef::Font *font,Font fallback);
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

   const Bitmap * operator () (Book::TypeDef::Bitmap *bmp);
 };

/* struct ExtMap */

struct ExtMap
 {
  FontMap font;
  BitmapMap bmp;

  void blank()
   {
    font.erase();
    bmp.erase();
   }

  void setScale(Ratio scale)
   {
    font.setScale(scale);
   }
 };

/* class Shape */

class Shape
 {
  public:

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

  private:

   const Book::TypeDef::Frame *frame = 0 ;

   // base

   Coord down = 0 ;
   Point size;
   DynArray<Shape> subshapes;

   struct RefPane
    {
     Pane pane;
     RefType ref;
    };

   DynArray<RefPane> refs;

   Point rebase;

   // extra

   Coord len = 0 ;
   DynArray<ulen> split;
   DynArray<Coord> tdx;
   DynArray<Coord> tdy;

  private:

   static bool SkipSpace(StrLen text);

   static Coord GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Format *fmt);

   static Coord GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Text *obj);

   static Coord GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::FixedText *obj);

   static Coord GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Bitmap *obj);

   static Coord GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::TextList *obj);

   static Coord GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Collapse *obj);

   static Coord GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Table *obj);

   static Coord GetBY(const Config &cfg,FontMap &font_map,const Book::TypeDef::Frame &frame,Ratio scale);

   struct SizeContext;

   Point setBase(const Config &cfg,ExtMap &map,Ratio scale,const Book::TypeDef::Frame &frame,Coord dx,Point base);

   struct DrawContext;

   static VColor GetBack(const Book::TypeDef::Format *fmt);

   static VColor GetBack(const Book::TypeDef::Text *obj);

   static VColor GetBack(const Book::TypeDef::FixedText *obj);

   static VColor GetBack(const Book::TypeDef::Bitmap *obj);

   static VColor GetBack(const Book::TypeDef::TextList *obj);

   static VColor GetBack(const Book::TypeDef::Collapse *obj);

   static VColor GetBack(const Book::TypeDef::Table *obj);

   template <class T>
   static VColor GetAnyBack(T body);

   static void DrawLine(const Config &cfg,DrawBuf buf,const Book::TypeDef::SingleLine *obj,Pane pane);

   static void DrawLine(const Config &cfg,DrawBuf buf,const Book::TypeDef::DoubleLine *obj,Pane pane);

   template <class T>
   static void DrawAnyLine(const Config &cfg,DrawBuf buf,T line,Pane pane);

   void draw(const Config &cfg,ExtMap &map,Ratio scale,VColor fore,DrawBuf buf,Point base) const;

   Coord drawSub(const Config &cfg,ExtMap &map,Ratio scale,VColor fore,DrawBuf buf,Pane parent,Point base) const;

   bool hit(Point point) const;

   RefType getRef(Point point) const;

  public:

   Shape() noexcept {}

   Coord getDown() const { return down; }

   Point getSize() const { return size; }

   Point set(const Config &cfg,ExtMap &map,Ratio scale,const Book::TypeDef::Frame &frame,Coord dx,Coord down);

   void draw(const Config &cfg,ExtMap &map,Ratio scale,VColor fore,DrawBuf buf,Coord pos_x,Coord pos_y) const;

   bool hit(Point point,Coord pos_x,Coord pos_y) const;

   RefType getRef(Point point,Coord pos_x,Coord pos_y) const;
 };

} // namespace App

#endif
