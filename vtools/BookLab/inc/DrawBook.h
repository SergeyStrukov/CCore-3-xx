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
#include <CCore/inc/CompactList.h>

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

class FontMap;

struct FrameExt;

template <class T,class E> class MapOf;

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

/* struct FrameExt */

struct FrameExt
 {
  Point size;
 };

/* MapOf<T,E> */

template <class T,class E>
class MapOf : NoCopy
 {
   CompactList<E> list;
   DynArray<E *> buf;

  public:

   MapOf() {}

   ~MapOf() {}

   void erase()
    {
     list.erase();
     buf.erase();
    }

   E * operator () (T *obj)
    {
     if( !obj ) return 0;

     if( ulen ext=obj->ext )
       {
        return buf.at(ext-1);
       }
     else
       {
        buf.reserve(1);

        E *ret=list.ins();

        buf.append_copy(ret);

        obj->ext=buf.getLen();

        return ret;
       }
    }
 };

/* struct ExtMap */

struct ExtMap : NoCopy
 {
  FontMap font;

  MapOf<Book::TypeDef::Frame,FrameExt> frame;

  void blank()
   {
    font.erase();
    frame.erase();
   }

  void setScale(Ratio scale)
   {
    font.setScale(scale);
   }

  Font operator () (Book::TypeDef::Font *obj,Font fallback) { return font(obj,fallback); }

  FrameExt * operator () (Book::TypeDef::Frame *obj) { return frame(obj); }
 };

/* struct Draw */

struct Draw
 {
  const Config &cfg;
  ExtMap &map;
  Ratio scale;
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

  Format useFixed(const Book::TypeDef::Format *fmt);

  Point drawSpan(Format fmt,StrLen text,Pane inner,Point base,DrawBuf buf);

   // draw()

  void draw(Book::TypeDef::Text *obj,Pane inner,Point pad,DrawBuf buf);

   void drawLine(PtrLen<const Book::TypeDef::FixedSpan> line,Format format,Pane inner,Point base,DrawBuf buf);

  void draw(Book::TypeDef::FixedText *obj,Pane inner,Point pad,DrawBuf buf);

  void draw(Book::TypeDef::Bitmap *obj,Pane inner,Point pad,DrawBuf buf);

  void draw(Book::TypeDef::TextList *obj,Pane inner,Point pad,DrawBuf buf);

  void draw(Book::TypeDef::Collapse *obj,Pane inner,Point pad,DrawBuf buf);

  void draw(Book::TypeDef::Table *obj,Pane inner,Point pad,DrawBuf buf);

  template <class T>
  void drawAny(T body,Pane inner,Point pad,DrawBuf buf);

  // public

  void operator () (Book::TypeDef::Frame *frame,DrawBuf buf,Point base);
 };

} // namespace DrawBook
} // namespace App

#endif

