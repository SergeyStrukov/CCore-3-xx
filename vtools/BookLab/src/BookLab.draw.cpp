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

#include <CCore/inc/video/FigureLib.h>

namespace App {
namespace BookLab {

/* class Book::PrepareContext */

class Book::PrepareContext : NoCopy
 {
   Fraction width;

   Coord table_dxy;
   Coord element_space;

   CCore::Video::Font text_font;
   FontSize fs;

  private:

   struct Place
    {
     void *data;

     Point (*size_func)(PrepareContext *ctx,void *data);

     void (*place_func)(PrepareContext *ctx,Point base,void *data);

     Point size(PrepareContext *ctx) const { return size_func(ctx,data); }

     void place(PrepareContext *ctx,Point base) const { place_func(ctx,base,data); }
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
       size_func=SizeFunc;
       place_func=PlaceFunc;
      }
    };

   struct Row
    {
     StrLen type;
     StrLen name;
     Place place;
    };

   template <ulen RowCount>
   Point place(TableLayout<RowCount> &layout,Point base,PtrLen<const Row> table)
    {
     layout={};

     Point cell[RowCount][3];

     for(ulen i : IndLim(RowCount) )
       {
        cell[i][0]=size(table[i].type);
        cell[i][1]=size(table[i].name);
        cell[i][2]=table[i].place.size(this);
       }

     Coord dx0=0;
     Coord dx1=0;
     Coord dx2=0;

     for(ulen i : IndLim(RowCount) )
       {
        Replace_max(dx0,cell[i][0].x);
        Replace_max(dx1,cell[i][1].x);
        Replace_max(dx2,cell[i][2].x);

        Coord dy=Sup(cell[i][0].y,cell[i][1].y,cell[i][2].y);

        layout.row[i].dy=dy;
        layout.row[i].offy=fs.by;
       }

     layout.col[0].dx=dx0;
     layout.col[1].dx=dx1;
     layout.col[2].dx=dx2;

     for(ulen i : IndLim(RowCount) )
       {
        layout.col[0].offx[i]=0;
        layout.col[1].offx[i]=dx1-cell[i][1].x;
        layout.col[2].offx[i]=0;
       }

     Coord dx=dx0+dx1+3*table_dxy;
     Coord dy=table_dxy;

     for(ulen i : IndLim(RowCount) )
       {
        table[i].place.place(this,base+Point(dx,dy));

        dy+=layout.row[i].dy+table_dxy;
       }

     return Point(dx+dx2+table_dxy,dy);
    }

  private:

   Point size(StrLen text)
    {
     return text_font->text(text).getSize();
    }

   Point size(const String &obj)
    {
     return size(Range(obj));
    }

   void place(Point,String &) {}

   template <auto Def>
   Point size(const OptData<VColor,Def> &)
    {
     Coord dy=fs.dy;

     return Point(2*dy,dy);
    }

   template <auto Def>
   void place(Point,OptData<VColor,Def> &) {}

   template <class T>
   Point size(NamedPtr<T> &obj)
    {
     if( obj.hasName() ) return size(obj.name);

     if( obj.hasObj() ) return size(obj.ptr.getPtr());

     return Null;
    }

   template <class T>
   void place(Point base,NamedPtr<T> &obj)
    {
     if( obj.hasName() ) return;

     if( obj.hasObj() ) place(base,obj.ptr.getPtr());
    }

  private:

   // TODO

   template <class T>
   Point size(T *ptr)
    {
     Used(ptr);

     return Null;
    }

   template <class T>
   void place(Point base,T *ptr)
    {
     Used(base);
     Used(ptr);
    }

  public:

   explicit PrepareContext(const Config &cfg)
    {
     width=+cfg.width;
     table_dxy=+cfg.table_dxy;
     element_space=+cfg.element_space;
     text_font=+cfg.text_font;

     fs=text_font->getSize();
    }

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
   DrawBuf buf;

   Fraction width;

   Coord table_dxy;
   Coord element_space;

   VColor gray;
   VColor table;
   VColor text;

   CCore::Video::Font text_font;
   FontSize fs;

  private:

   struct Draw
    {
     const void *data;

     void (*draw_func)(DrawContext *ctx,Pane cell,Coord offy,const void *data);

     void draw(DrawContext *ctx,Pane cell,Coord offy) const { draw_func(ctx,cell,offy,data); }
    };

   template <class T>
   struct DrawOf : Draw
    {
     static void DrawFunc(DrawContext *ctx,Pane cell,Coord offy,const void *data)
      {
       ctx->draw(cell,offy,*static_cast<const T *>(data));
      }

     explicit DrawOf(const T &obj)
      {
       data=&obj;
       draw_func=DrawFunc;
      }
    };

   struct Row
    {
     StrLen type;
     StrLen name;
     Draw draw;
    };

   template <ulen RowCount>
   void draw(Point base,PtrLen<const Row> table,const TableLayout<RowCount> &layout)
    {
     Coord dx0=layout.col[0].dx;
     Coord dx1=layout.col[1].dx;
     Coord dx2=layout.col[2].dx;

     {
      VColor vc=this->table;

      DrawBuf buf1=buf;

      buf1.shift(base);

      SmoothDrawArt art(buf1);

      MPoint A=Point::Diag(table_dxy);

      A=A/2;

      MCoord fdx=Fraction(dx0+dx1+dx2+3*table_dxy);

      Coord tdy=0;

      {
       MPoint O=A;

       art.path(width,vc,O,O.addX(fdx));

       for(ulen i : IndLim(RowCount) )
         {
          Coord dy=layout.row[i].dy;

          O=O.addY(Fraction(dy+table_dxy));

          art.path(width,vc,O,O.addX(fdx));

          tdy+=dy+table_dxy;
         }
      }

      {
       MPoint O=A;
       MCoord fdy=Fraction(tdy);

       art.path(width,vc,O,O.addY(fdy));

       O=O.addX(Fraction(dx0+table_dxy));

       art.path(width,vc,O,O.addY(fdy));

       O=O.addX(Fraction(dx1+table_dxy));

       art.path(width,vc,O,O.addY(fdy));

       O=O.addX(Fraction(dx2+table_dxy));

       art.path(width,vc,O,O.addY(fdy));
      }
     }

     Coord ox0=table_dxy;
     Coord ox1=dx0+2*table_dxy;
     Coord ox2=dx0+dx1+3*table_dxy;
     Coord oy=table_dxy;

     for(ulen i : IndLim(RowCount) )
       {
        Coord dy=layout.row[i].dy;
        Coord offy=layout.row[i].offy;

        Coord offx0=layout.col[0].offx[i];
        Coord offx1=layout.col[1].offx[i];
        Coord offx2=layout.col[2].offx[i];

        draw(Pane(base+Point(ox0+offx0,oy),dx0-offx0,dy),offy,table[i].type);

        draw(Pane(base+Point(ox1+offx1,oy),dx1-offx1,dy),offy,table[i].name);

        table[i].draw.draw(this,Pane(base+Point(ox2+offx2,oy),dx2-offx2,dy),offy);

        oy+=dy+table_dxy;
       }
    }

  private:

   void draw(Pane cell,Coord offy,StrLen str)
    {
     text_font->text(buf,cell,TextPlace(AlignX_Left,offy),str,text);
    }

   void draw(Pane cell,Coord offy,const String &obj)
    {
     draw(cell,offy,Range(obj));
    }

   template <auto Def>
   void draw(Pane cell,Coord offy,const OptData<VColor,Def> &obj)
    {
     if( obj.def )
       {
        buf.erase(cell,gray);
       }
     else
       {
        Coord dy=fs.dy;

        Pane pane(cell.x,cell.y+offy-fs.by,2*dy,dy);

        buf.erase(pane,obj.data);
       }
    }

   template <class T>
   void draw(Pane cell,Coord offy,const NamedPtr<T> &obj)
    {
     if( obj.hasName() ) return draw(cell,offy,obj.name);

     if( obj.hasObj() ) return draw(cell,offy,obj.ptr.getPtr());
    }

  private:

   // TODO

   template <class T>
   void draw(Pane cell,Coord offy,T *ptr)
    {
     Used(cell);
     Used(offy);
     Used(ptr);
    }

  public:

   DrawContext(const DrawBuf &buf_,const Config &cfg)
    : buf(buf_)
    {
     width=+cfg.width;
     table_dxy=+cfg.table_dxy;
     element_space=+cfg.element_space;
     gray=+cfg.gray;
     table=+cfg.table;
     text=+cfg.text;
     text_font=+cfg.text_font;

     fs=text_font->getSize();
    }

   void draw(Doc *doc) // TODO
    {
     Row table[4]=
      {
       {"text"_c,"title"_c,DrawOf(doc->title)},
       {"Color"_c,"back"_c,DrawOf(doc->back)},
       {"Color"_c,"fore"_c,DrawOf(doc->fore)},
       {"Page"_c,"start"_c,DrawOf(doc->start)}
      };

     draw(Null,Range(table),doc->layout);

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

  DrawContext ctx(buf,cfg);

  ctx.draw(doc.getPtr());
 }

} // namespace BookLab
} // namespace App
