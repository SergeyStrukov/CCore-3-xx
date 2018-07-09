/* DrawBook.h */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
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

#include <CCore/inc/IntervalTree.h>

namespace App {
namespace DrawBook {

/* classes */

class Prepare;

struct DrawOut;

class Draw;

class GotoBase;

template <UIntType UInt> class Goto;

class OpenBase;

template <UIntType UInt> class Open;

class Shape;

/* class Prepare */

class Prepare : NoCopy
 {
   const Config &cfg;
   ExtMap &map;
   Ratio scale;
   DynArray<RefPane> &refs;

   DynArray<ulen> stack;

   unsigned level = 25 ;

  private:

   // refs

   void addRef(RefType ref,Pane pane);

   static RefType CastRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref);

   void addRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref,Pane pane);

   void push(ulen index) { stack.append_copy(index); }

   void pop() { stack.shrink_one(); }

   void push(ulen i1,ulen i2) { auto r=stack.extend_raw(2); r[0]=i1; r[1]=i2; }

   void pop2() { stack.shrink(2); }

   // common

   Font use(const Book::TypeDef::Format *fmt);

   Font useFixed(const Book::TypeDef::Format *fmt);

   Font over(Font font,const Book::TypeDef::Format *fmt);

   static TextSize SizeSpan(Font font,StrLen text);

   static Coord SizeSpace(Font font);

   // size()

    void correctRefs(ulen refs_len,Coord delta_x,Coord delta_y=0);

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

    static Coord SizeBullet(Font font,StrLen text);

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

   Prepare(const Config &cfg,ExtMap &map,Ratio scale,DynArray<RefPane> &refs);

   ~Prepare() {}

   Point operator () (Book::TypeDef::Frame *frame,ulen frame_index,Coord wdx,Point base);
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

/* class GotoBase */

class GotoBase : NoCopy
 {
   ExtMap &map;
   Coord down;

  private:

   void frameDown(PtrLen<Book::TypeDef::Frame> list,ulen index);

   void frameDown(PtrLen<Book::TypeDef::Frame> list);

  public:

   GotoBase(ExtMap &map_,Coord down_) : map(map_),down(down_) {}

   Coord getDown() const { return down; }

   void border(FrameExt *ext);

   Book::TypeDef::Frame * step(ulen item_index,ulen frame_index,Book::TypeDef::TextList *obj,FrameExt_TextList *ext);

   Book::TypeDef::Frame * step(ulen index,Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext);

   Book::TypeDef::Frame * step(ulen col,ulen row,ulen index,Book::TypeDef::Table *obj,FrameExt_Table *ext);
 };

/* class Goto<UInt> */

template <UIntType UInt>
class Goto : GotoBase
 {
   PtrLen<const UInt> index_list;

  private:

   using GotoBase::step;

   Book::TypeDef::Frame * step(Book::TypeDef::Text *,FrameExt *) { return 0; }

   Book::TypeDef::Frame * step(Book::TypeDef::FixedText *,FrameExt *) { return 0; }

   Book::TypeDef::Frame * step(Book::TypeDef::Bitmap *,FrameExt *) { return 0; }

   Book::TypeDef::Frame * step(Book::TypeDef::TextList *obj,FrameExt *ext)
    {
     if( index_list.len<2 ) return 0;

     ulen index1=index_list[0];
     ulen index2=index_list[1];

     index_list+=2;

     return step(index1,index2,obj,AutoCast(ext));
    }

   Book::TypeDef::Frame * step(Book::TypeDef::Collapse *obj,FrameExt *ext)
    {
     if( !index_list ) return 0;

     ulen index=index_list[0];

     ++index_list;

     return step(index,obj,AutoCast(ext));
    }

   Book::TypeDef::Frame * step(Book::TypeDef::Table *obj,FrameExt *ext)
    {
     if( index_list.len<3 ) return 0;

     ulen index1=index_list[0];
     ulen index2=index_list[1];
     ulen index3=index_list[2];

     index_list+=3;

     return step(index1,index2,index3,obj,AutoCast(ext));
    }

   template <class T>
   Book::TypeDef::Frame * stepAny(T body,FrameExt *ext)
    {
     Book::TypeDef::Frame *ret=0;

     body.apply( [&] (auto *obj) { ret=step(obj,ext); } );

     if( ret ) border(ext);

     return ret;
    }

  public:

   Goto(ExtMap &map,Coord down,PtrLen<const UInt> index_list_) : GotoBase(map,down),index_list(index_list_) {}

   Coord operator () (Book::TypeDef::Frame *frame)
    {
     while( +index_list && frame )
       {
        FrameExt *ext=map(frame);

        frame=stepAny(frame->body.getPtr(),ext);
       }

     return getDown();
    }
 };

/* class OpenBase */

class OpenBase : NoCopy
 {
   bool flag = false ;

  public:

   bool getFlag() const { return flag; }

   Book::TypeDef::Frame * step(ulen item_index,ulen frame_index,Book::TypeDef::TextList *obj);

   Book::TypeDef::Frame * step(ulen index,Book::TypeDef::Collapse *obj);

   Book::TypeDef::Frame * step(ulen col,ulen row,ulen index,Book::TypeDef::Table *obj);
 };

/* class Open<UInt> */

template <UIntType UInt>
class Open : OpenBase
 {
   PtrLen<const UInt> index_list;

  private:

   using OpenBase::step;

   Book::TypeDef::Frame * step(Book::TypeDef::Text *) { return 0; }

   Book::TypeDef::Frame * step(Book::TypeDef::FixedText *) { return 0; }

   Book::TypeDef::Frame * step(Book::TypeDef::Bitmap *) { return 0; }

   Book::TypeDef::Frame * step(Book::TypeDef::TextList *obj)
    {
     if( index_list.len<2 ) return 0;

     ulen index1=index_list[0];
     ulen index2=index_list[1];

     index_list+=2;

     return step(index1,index2,obj);
    }

   Book::TypeDef::Frame * step(Book::TypeDef::Collapse *obj)
    {
     if( !index_list ) return 0;

     ulen index=index_list[0];

     ++index_list;

     return step(index,obj);
    }

   Book::TypeDef::Frame * step(Book::TypeDef::Table *obj)
    {
     if( index_list.len<3 ) return 0;

     ulen index1=index_list[0];
     ulen index2=index_list[1];
     ulen index3=index_list[2];

     index_list+=3;

     return step(index1,index2,index3,obj);
    }

   template <class T>
   Book::TypeDef::Frame * stepAny(T body)
    {
     Book::TypeDef::Frame *ret=0;

     body.apply( [&] (auto *obj) { ret=step(obj); } );

     return ret;
    }

  private:

   explicit Open(PtrLen<const UInt> index_list_) : index_list(index_list_) {}

   bool operator () (Book::TypeDef::Frame *frame)
    {
     while( +index_list && frame )
       {
        frame=stepAny(frame->body.getPtr());
       }

     return getFlag();
    }
 };

/* class Shape */

class Shape
 {
   Book::TypeDef::Frame *frame = 0 ;

   Coord down = 0 ;
   Point size;

   DynArray<RefPane> refs;

   IntervalTree<Coord> tree;

  private:

   void prepare(const Config &cfg,ExtMap &map,Ratio scale,ulen frame_index,Coord wdx);

   void draw(const Config &cfg,ExtMap &map,VColor fore,DrawBuf buf,Point base) const;

   bool hit(Point point) const;

   RefList getRef(Point point) const;

  public:

   Shape() noexcept {}

   Coord getDown() const { return down; }

   Coord getDown(ExtMap &map,PtrLen<const UIntType> index_list) const;

   bool open(PtrLen<const UIntType> index_list) const;

   Point getSize() const { return size; }

   Point set(const Config &cfg,ExtMap &map,Ratio scale,Book::TypeDef::Frame &frame,ulen frame_index,Coord wdx,Coord down);

   void draw(const Config &cfg,ExtMap &map,VColor fore,DrawBuf buf,Coord pos_x,Coord pos_y) const; // set() first

   bool hit(Point point,Coord pos_x,Coord pos_y) const;

   RefList getRef(Point point,Coord pos_x,Coord pos_y) const;
 };

Coord Shape::getDown(ExtMap &map,PtrLen<const UIntType> index_list) const
 {
  Goto ctx(map,down,index_list);

  return ctx(frame);
 }

bool Shape::open(PtrLen<const UIntType> index_list) const
 {
  Open ctx(index_list);

  return ctx(frame);
 }

} // namespace DrawBook
} // namespace App

#endif

