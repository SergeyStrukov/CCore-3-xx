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

#include <inc/DrawBookTools.h>

namespace App {
namespace DrawBook {

/* classes */

class Prepare;

struct DrawOut;

class Draw;

class Shape;

/* class Prepare */

class Prepare : NoCopy
 {
   const Config &cfg;
   ExtMap &map;
   Ratio scale;
   DynArray<RefPane> &refs;

   unsigned level = 25 ;

  private:

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

    Coord sizeLine(Font font,Book::TypeDef::Line line,Point base);

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

    Point sizeItem(FontSize fs,Book::TypeDef::ListItem item,ListItemSize &item_size,Coord bullet_dx,Coord wdx,Point base);

   Point size(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,Coord wdx,Point base);

   Point size(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,Coord wdx,Point base);

    template <class T>
    static void CorrectSpanLen(T &span,ulen cap);

   Point size(Book::TypeDef::Table *obj,FrameExt_Table *ext,Coord wdx,Point base);

   template <class T>
   Point sizeAny(T body,FrameExt *ext,Coord wdx,Point base);

   // frame

   Point operator () (PtrLen<Book::TypeDef::Frame> list,Coord wdx,Point base);

  public:

   Prepare(const Config &cfg_,ExtMap &map_,Ratio scale_,DynArray<RefPane> &refs_) : cfg(cfg_),map(map_),scale(scale_),refs(refs_) {}

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

  DrawOut add(Point p) const { return {buf,pane,base+p}; }

  void back(TextSize ts,VColor back);

  void effect(TextSize ts,Effect effect,VColor fore,MCoord width);

  void text(Font font,StrLen text,VColor fore);

  void bitmap(const Bitmap *bitmap);

  void drawPlus(const Config &cfg,Coord len);

  void drawMinus(const Config &cfg,Coord len);

  static Coord Sum(PtrLen<const Coord> tdx,Coord space,ulen i,ulen k);

  template <class F1,class F2,class F3>
  static void DrawLine(F1 path,MPoint A,PtrLen<const Coord> tdx,Coord space,Coord maxlen,F2 skip,F3 add);

  void table(TableDesc desc,VColor line,MCoord width);
 };

/* class Draw */

class Draw : NoCopy
 {
   const Config &cfg;
   ExtMap &map;
   VColor fore;

  private:

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
    };

   Format use(const Book::TypeDef::Format *fmt);

   Format useFixed(const Book::TypeDef::Format *fmt);

   Format useBack(const Book::TypeDef::Format *fmt);

   Format over(Format format,const Book::TypeDef::Format *fmt);

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

    Coord drawItem(Format format,Book::TypeDef::ListItem item,ListItemSize item_size,Coord bullet_len,Coord bullet_space,DrawOut out);

   void draw(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,DrawOut out);

   void draw(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,DrawOut out);

   void draw(Book::TypeDef::Table *obj,FrameExt_Table *ext,DrawOut out);

   template <class T>
   void drawAny(T body,FrameExt *ext,DrawOut out);

   // frame

   Point operator () (Book::TypeDef::Frame *frame,DrawOut out);

   Point operator () (PtrLen<Book::TypeDef::Frame> list,DrawOut out);

  public:

   Draw(const Config &cfg_,ExtMap &map_,VColor fore_) : cfg(cfg_),map(map_),fore(fore_) {}

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

   void draw(const Config &cfg,ExtMap &map,VColor fore,DrawBuf buf,Coord pos_x,Coord pos_y) const; // set() first

   bool hit(Point point,Coord pos_x,Coord pos_y) const;

   RefType getRef(Point point,Coord pos_x,Coord pos_y) const;
 };

} // namespace DrawBook
} // namespace App

#endif

