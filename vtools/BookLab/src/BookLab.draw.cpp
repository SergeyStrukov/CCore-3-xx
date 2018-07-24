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

/* class Book::ShowData */

class Book::ShowData : NoCopy
 {
   char buf[TextBufLen];
   PrintBuf out;
   StrLen str;

  private:

   void show(Point data)
    {
     Putobj(out,data);
    }

   void show(Coord data)
    {
     Putobj(out,data);
    }

  public:

   template <class T>
   ShowData(T data)
    : out(Range(buf))
    {
     show(data);

     str=out.close();
    }

   StrLen get() const { return str; }
 };

/* class Book::PrepareContext */

class Book::PrepareContext : NoCopy
 {
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
   Point size(TableLayout<RowCount> &layout,PtrLen<const Row> table)
    {
     layout={};

     Point cell[RowCount][3];

     Point min_size=Point::Diag(fs.dy);

     for(ulen i : IndLim(RowCount) )
       {
        cell[i][0]=size(table[i].type);
        cell[i][1]=size(table[i].name);
        cell[i][2]=Sup(table[i].place.size(this),min_size);
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

     Coord dy=table_dxy;

     for(ulen i : IndLim(RowCount) )
       {
        dy=AddSize(dy,layout.row[i].dy,table_dxy);
       }

     Point size(AddSize(dx0,dx1,dx2,MulSize(4u,table_dxy)),dy);

     layout.size=size;

     return size;
    }

   template <ulen RowCount>
   void place(TableLayout<RowCount> &layout,Point base,PtrLen<const Row> table)
    {
     Coord dx0=layout.col[0].dx;
     Coord dx1=layout.col[1].dx;

     Coord dx=dx0+dx1+3*table_dxy;
     Coord dy=table_dxy;

     for(ulen i : IndLim(RowCount) )
       {
        table[i].place.place(this,base+Point(dx,dy));

        dy+=layout.row[i].dy+table_dxy;
       }
    }

   template <ulen RowCount>
   Point prepare(TableLayout<RowCount> &layout,Point base,PtrLen<const Row> table)
    {
     Point ret=size(layout,table);

     place(layout,base,table);

     return ret;
    }

   template <class T>
   Point prepareTable(Point base,T *ptr)
    {
     Point ret;

     ptr->template apply<Row,PlaceOf>( [&] (auto table,auto &layout) { ret=prepare(layout,base,table); } );

     return ret;
    }

   Point prepare(Point base,ElementList &list)
    {
     Point ret;

     for(Element &elem : ForIntList(list) )
       {
        base=base.addY(element_space);

        ret=StackYSize_guarded(ret,Point(0,element_space));

        Point s=prepare(base,elem.ptr.getPtr());

        base=base.addY(s.y);

        ret=StackYSize_guarded(ret,s);
       }

     return ret;
    }

   Point prepare(Point base,Defaults &obj)
    {
     Point s=prepareTable(base.addY(element_space),&obj);

     return StackYSize_guarded(s,Point(0,element_space));
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

   Point size(VColor)
    {
     Coord dy=fs.dy;

     return Point(2*dy,dy);
    }

   template <OneOfTypes<Point,Coord> T>
   Point size(T data)
    {
     ShowData show(data);

     return size(show.get());
    }

   template <class T,auto Def>
   Point size(const OptData<T,Def> &obj)
    {
     if( obj.def )
       {
        return Null;
       }
     else
       {
        return size(obj.data);
       }
    }

   template <class T,auto Def>
   void place(Point,OptData<T,Def> &) {}

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

   template <class T>
   Point size(const IntObjPtr<T> &obj)
    {
     if( +obj ) return size(obj.getPtr());

     return Null;
    }

   template <class T>
   void place(Point base,const IntObjPtr<T> &obj)
    {
     if( +obj ) place(base,obj.getPtr());
    }

   template <class ... TT>
   Point size(const IntAnyObjPtr<TT...> &obj)
    {
     if( +obj ) return size(obj.getPtr());

     return Null;
    }

   template <class ... TT>
   void place(Point base,const IntAnyObjPtr<TT...> &obj)
    {
     if( +obj ) place(base,obj.getPtr());
    }

  private:

   template <class ... TT>
   Point size(AnyPtr<TT...> anyptr)
    {
     Point ret;

     anyptr.apply( [&] (auto *ptr) { if( ptr ) ret=size(ptr); } );

     return ret;
    }

   template <class ... TT>
   void place(Point base,AnyPtr<TT...> anyptr)
    {
     anyptr.apply( [&] (auto *ptr) { if( ptr ) place(base,ptr); } );
    }

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

   Point size(Page *ptr) // TODO
    {
     Point ret;

     ptr->apply<Row,PlaceOf>( [&] (auto table,auto &layout) { ret=size(layout,table); } );

     return ret;
    }

   void place(Point base,Page *ptr) // TODO
    {
     ptr->apply<Row,PlaceOf>( [&] (auto table,auto &layout) { place(layout,base,table); } );
    }

  private:

   template <class ... TT>
   Point prepare(Point base,AnyPtr<TT...> anyptr)
    {
     Point ret;

     anyptr.apply( [&] (auto *ptr) { if( ptr ) ret=prepare(base,ptr); } );

     return ret;
    }

   // TODO

   template <class T>
   Point prepare(Point base,T *ptr)
    {
     Used(base);
     Used(ptr);

     return Null;
    }

   Point prepare(Point base,Page *ptr) // TODO
    {
     return prepareTable(base,ptr);
    }

  public:

   explicit PrepareContext(const Config &cfg)
    {
     table_dxy=+cfg.table_dxy;
     element_space=+cfg.element_space;
     text_font=+cfg.text_font;

     fs=text_font->getSize();
    }

   Point place(Doc *doc)
    {
     Point s1=prepareTable(Null,doc);

     Coord dy=s1.y;

     Point s2=prepare(Point(0,dy),doc->defs);

     dy+=s2.y;

     Point s3=prepare(Point(0,dy),doc->list);

     return StackYSize_guarded(StackYSize_guarded(s1,s2),s3);
    }
 };

/* class Book::DrawContext */

class Book::DrawContext : NoCopy
 {
   DrawBuf buf;

   Fraction line_width;

   Coord table_dxy;
   Coord element_space;

   VColor gray;
   VColor alert;
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

      {
       MPoint O=A;
       MCoord fdx=Fraction(layout.size.x-table_dxy);

       art.path(line_width,vc,O,O.addX(fdx));

       for(ulen i : IndLim(RowCount) )
         {
          Coord dy=layout.row[i].dy;

          O=O.addY(Fraction(dy+table_dxy));

          art.path(line_width,vc,O,O.addX(fdx));
         }
      }

      {
       MPoint O=A;
       MCoord fdy=Fraction(layout.size.y-table_dxy);

       art.path(line_width,vc,O,O.addY(fdy));

       O=O.addX(Fraction(dx0+table_dxy));

       art.path(line_width,vc,O,O.addY(fdy));

       O=O.addX(Fraction(dx1+table_dxy));

       art.path(line_width,vc,O,O.addY(fdy));

       O=O.addX(Fraction(dx2+table_dxy));

       art.path(line_width,vc,O,O.addY(fdy));
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

   template <class T>
   Coord drawTable(Point base,T *ptr)
    {
     Coord ret=0;

     ptr->template apply<Row,DrawOf>( [&] (auto table,auto &layout) { draw(base,table,layout); ret=layout.size.y; } );

     return ret;
    }

   Coord draw(Point base,ElementList &list)
    {
     Coord start=base.y;

     for(Element &elem : ForIntList(list) )
       {
        base=base.addY(element_space);

        Coord dy=draw(base,elem.ptr.getPtr());

        base=base.addY(dy);
       }

     return base.y-start;
    }

   Coord draw(Point base,Defaults &obj)
    {
     return drawTable(base.addY(element_space),&obj)+element_space;
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

   void draw(Pane cell,Coord offy,const String &obj,bool alert_flag)
    {
     if( alert_flag ) buf.erase(cell,alert);

     draw(cell,offy,Range(obj));
    }

   void draw(Pane cell,Coord offy,VColor data)
    {
     SmoothDrawArt art(buf);

     Coord dy=fs.dy;

     Pane pane(cell.x,cell.y+offy-fs.by,2*dy,dy);

     MPane p(pane);

     if( !p ) return;

     FigureRoundBox fig(p,p.dy/4);

     fig.curveSolid(art,data);
    }

   template <OneOfTypes<Point,Coord> T>
   void draw(Pane cell,Coord offy,T data)
    {
     ShowData show(data);

     draw(cell,offy,show.get());
    }

   template <class T,auto Def>
   void draw(Pane cell,Coord offy,const OptData<T,Def> &obj)
    {
     if( obj.def )
       {
        buf.erase(cell,gray);
       }
     else
       {
        draw(cell,offy,obj.data);
       }
    }

   template <class T>
   void draw(Pane cell,Coord offy,const NamedPtr<T> &obj)
    {
     if( obj.hasName() ) return draw(cell,offy,obj.name,obj.notResolved());

     if( obj.hasObj() ) return draw(cell,offy,obj.ptr.getPtr());

     buf.erase(cell,gray);
    }

   template <class T>
   void draw(Pane cell,Coord offy,const IntObjPtr<T> &obj)
    {
     if( !obj )
       {
        buf.erase(cell,gray);
       }
     else
       {
        draw(cell,offy,obj.getPtr());
       }
    }

   template <class ... TT>
   void draw(Pane cell,Coord offy,const IntAnyObjPtr<TT...> &obj)
    {
     if( !obj )
       {
        buf.erase(cell,gray);
       }
     else
       {
        draw(cell,offy,obj.getPtr());
       }
    }

  private:

   template <class ... TT>
   void draw(Pane cell,Coord offy,AnyPtr<TT...> anyptr)
    {
     anyptr.apply( [&] (auto *ptr) { if( ptr ) draw(cell,offy,ptr); } );
    }

   // TODO

   template <class T>
   void draw(Pane cell,Coord offy,T *ptr)
    {
     Used(cell);
     Used(offy);
     Used(ptr);
    }

   void draw(Pane cell,Coord,Page *ptr) // TODO
    {
     drawTable(cell.getBase(),ptr);
    }

  private:

   template <class ... TT>
   Coord draw(Point base,AnyPtr<TT...> anyptr)
    {
     Coord ret=0;

     anyptr.apply( [&] (auto *ptr) { if( ptr ) ret=draw(base,ptr); } );

     return ret;
    }

   // TODO

   template <class T>
   Coord draw(Point base,T *ptr)
    {
     Used(base);
     Used(ptr);

     return 0;
    }

   Coord draw(Point base,Page *ptr) // TODO
    {
     return drawTable(base,ptr);
    }

  public:

   DrawContext(const DrawBuf &buf_,const Config &cfg)
    : buf(buf_)
    {
     line_width=+cfg.line_width;
     table_dxy=+cfg.table_dxy;
     element_space=+cfg.element_space;
     gray=+cfg.gray;
     alert=+cfg.alert;
     table=+cfg.table;
     text=+cfg.text;
     text_font=+cfg.text_font;

     fs=text_font->getSize();
    }

   void draw(Doc *doc)
    {
     Coord dy=drawTable(Null,doc);

     dy+=draw(Point(0,dy),doc->defs);

     draw(Point(0,dy),doc->list);
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
