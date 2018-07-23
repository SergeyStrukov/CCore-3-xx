/* DrawBookLab.cpp */
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

#include <inc/BookLab.h>

namespace App {
namespace BookLab {

/* class Book::PrepareContext */

class Book::PrepareContext : NoCopy
 {
   const Config &cfg;

  private:

   struct Place
    {
     void *data;

     Point (*size)(PrepareContext *ctx,void *data);

     void (*place)(PrepareContext *ctx,Point base,void *data);
    };

   template <class T>
   struct PlaceOf : Place
    {
     static Point SizeFunc(PrepareContext *ctx,void *data)
      {
       return ctx->size(*static_cast<T *>(data));
      }

     static void PlaceFunc(PrepareContext *ctx,Point base,void *data)
      {
       ctx->place(base,*static_cast<T *>(data));
      }

     explicit PlaceOf(T &obj)
      {
       data=&obj;
       size=SizeFunc;
       place=PlaceFunc;
      }
    };

   struct Row
    {
     StrLen type;
     StrLen name;
     Place place;
    };

   template <ulen RowCount>
   Point place(TableLayout<RowCount> &layout,Point base,PtrLen<const Row> table) // TODO
    {
     Used(base);
     Used(table);
     Used(layout);

     return Null;
    }

  private:

   Point size(const String &obj)
    {
     Used(obj);

     return Null;
    }

   void place(Point,String &) {}

   template <auto Def>
   Point size(const OptData<VColor,Def> &obj)
    {
     Used(obj);

     return Null;
    }

   template <auto Def>
   void place(Point,OptData<VColor,Def> &) {}

   template <class T>
   Point size(NamedPtr<T> &obj)
    {
     Used(obj);

     return Null;
    }

   template <class T>
   void place(Point base,NamedPtr<T> &obj)
    {
     Used(base);
     Used(obj);
    }

  public:

   explicit PrepareContext(const Config &cfg_) : cfg(cfg_) {}

   Point place(Doc *doc) // TODO
    {
     Row table[4]=
      {
       {"text"_c,"title"_c,PlaceOf(doc->title)},
       {"Color"_c,"back"_c,PlaceOf(doc->back)},
       {"Color"_c,"fore"_c,PlaceOf(doc->fore)},
       {"Page"_c,"start"_c,PlaceOf(doc->start)}
      };

     place(doc->layout,Null,Range(table));

     return Point(3000,3000);
    }
 };

/* class Book::DrawContext */

class Book::DrawContext : NoCopy
 {
   const Config &cfg;

  private:

   struct Draw
    {
     const void *data;

     void (*draw)(DrawContext *ctx,DrawBuf buf,Point base,Coord offy,const void *data);
    };

   template <class T>
   struct DrawOf : Draw
    {
     static void DrawFunc(DrawContext *ctx,DrawBuf buf,Point base,Coord offy,const void *data)
      {
       ctx->draw(buf,base,offy,*static_cast<const T *>(data));
      }

     explicit DrawOf(const T &obj)
      {
       data=&obj;
       draw=DrawFunc;
      }
    };

   struct Row
    {
     StrLen type;
     StrLen name;
     Draw draw;
    };

   template <ulen RowCount>
   void draw(DrawBuf buf,Point base,PtrLen<const Row> table,const TableLayout<RowCount> &layout) // TODO
    {
     Used(buf);
     Used(base);
     Used(table);
     Used(layout);
    }

  private:

   void draw(DrawBuf buf,Point base,Coord offy,const String &obj)
    {
     Used(buf);
     Used(base);
     Used(offy);
     Used(obj);
    }

   template <auto Def>
   void draw(DrawBuf buf,Point base,Coord offy,const OptData<VColor,Def> &obj)
    {
     Used(buf);
     Used(base);
     Used(offy);
     Used(obj);
    }

   template <class T>
   void draw(DrawBuf buf,Point base,Coord offy,const NamedPtr<T> &obj)
    {
     Used(buf);
     Used(base);
     Used(offy);
     Used(obj);
    }

  public:

   explicit DrawContext(const Config &cfg_) : cfg(cfg_) {}

   void draw(DrawBuf buf,Doc *doc) // TODO
    {
     Row table[4]=
      {
       {"text"_c,"title"_c,DrawOf(doc->title)},
       {"Color"_c,"back"_c,DrawOf(doc->back)},
       {"Color"_c,"fore"_c,DrawOf(doc->fore)},
       {"Page"_c,"start"_c,DrawOf(doc->start)}
      };

     draw(buf,Null,Range(table),doc->layout);

    }
 };

/* class Book */

Point Book::prepare(const Config &cfg) const
 {
  if( !doc ) return Point(100,100);

  PrepareContext ctx(cfg);

  return ctx.place(doc.getPtr());
 }

void Book::draw(const Config &cfg,DrawBuf buf,Point base) const
 {
  if( !doc ) return;

  buf.shift(base);

  DrawContext ctx(cfg);

  ctx.draw(buf,doc.getPtr());
 }

} // namespace BookLab
} // namespace App
