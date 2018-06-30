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

struct Config;

struct FrameExt;

struct ExtMap;

struct Draw;

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

/* struct FrameExt */

struct FrameExt
 {
  Point size;
 };

/* struct ExtMap */

struct ExtMap
 {
  void blank()
   {
   }

  void setScale(Ratio scale)
   {
    Used(scale);
   }

  FrameExt * operator () (const Book::TypeDef::Frame *frame);
 };

/* struct Draw */

struct Draw
 {
  const Config &cfg;
  ExtMap &map;
  Ratio scale;
  VColor fore;
  Point base;

  DrawBuf buf;

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

  void drawLine(const Book::TypeDef::SingleLine *obj,Pane pane);

  void drawLine(const Book::TypeDef::DoubleLine *obj,Pane pane);

  template <class T>
  void drawAnyLine(T line,Pane pane);

   // draw()

  void draw(const Book::TypeDef::Text *obj,Pane inner,Point pad);

  void draw(const Book::TypeDef::FixedText *obj,Pane inner,Point pad);

  void draw(const Book::TypeDef::Bitmap *obj,Pane inner,Point pad);

  void draw(const Book::TypeDef::TextList *obj,Pane inner,Point pad);

  void draw(const Book::TypeDef::Collapse *obj,Pane inner,Point pad);

  void draw(const Book::TypeDef::Table *obj,Pane inner,Point pad);

  template <class T>
  void drawAny(T body,Pane inner,Point pad);

  // public

  void operator () (const Book::TypeDef::Frame *frame);
 };

} // namespace DrawBook
} // namespace App

#endif

