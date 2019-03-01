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
#include <CCore/inc/video/Layout.h>

namespace App {
namespace BookLab {

/* functions */

inline Point SizeListBtn(Coord dxy)
 {
  return Point(BoxExt(dxy),5*dxy);
 }

inline StrLen LinkDesc(Link &link) { return (+link.frame)? "frame ..."_c : "null"_c ; }

inline bool LinkAlert(Link &link) { return !link.page; }

/* class Book::ShowData */

class Book::ShowData : NoCopy
 {
   char buf[TextBufLen];
   PrintBuf out;
   StrLen str;

  private:

   template <OneOfTypes<Point,Ratio,Coord,Strength,bool,ulen> T>
   void show(T data)
    {
     Putobj(out,data);
    }

   void show(Effect data)
    {
     switch( data )
       {
        case Underline : Putobj(out,"underline"_c); break;
        case Strikeout : Putobj(out,"strikeout"_c); break;

        default: Putobj(out,"none"_c); break;
       }
    }

   void show(Align data)
    {
     switch( data )
       {
        case Right : Putobj(out,"right"_c); break;
        case Center : Putobj(out,"center"_c); break;

        default: Putobj(out,"left"_c); break;
       }
    }

  public:

   template <class T>
   explicit ShowData(T data)
    : out(Range(buf))
    {
     show(data);

     str=out.close();
    }

   StrLen get() const { return str; }
 };

/* class Book::ShowName */

class Book::ShowName : NoCopy
 {
   char buf[TextBufLen];
   PrintBuf out;
   StrLen str;

  private:

   void show(Font *ptr)
    {
     Printf(out,"Font #; = ",ptr->name);
    }

   void show(Format *ptr)
    {
     Printf(out,"Format #; = ",ptr->name);
    }

   void show(SingleLine *ptr)
    {
     Printf(out,"SingleLine #; = ",ptr->name);
    }

   void show(DoubleLine *ptr)
    {
     Printf(out,"DoubleLine #; = ",ptr->name);
    }

   void show(Page *ptr)
    {
     Printf(out,"Page #; = ",ptr->name);
    }

   void show(Scope *ptr)
    {
     Printf(out,"Scope #; = ",ptr->name);
    }

   void show(Bitmap *ptr)
    {
     Printf(out,"Bitmap #; = ",ptr->name);
    }

   void show(Collapse *ptr)
    {
     Printf(out,"Collapse #; = ",ptr->name);
    }

   void show(TextList *ptr)
    {
     Printf(out,"TextList #; = ",ptr->name);
    }

   void show(Border *ptr)
    {
     Printf(out,"Border #; = ",ptr->name);
    }

   void show(Cell *ptr)
    {
     Printf(out,"Cell #; = ",ptr->name);
    }

   void show(Table *ptr)
    {
     Printf(out,"Table #; = ",ptr->name);
    }

   void show(Link *ptr)
    {
     Printf(out,"Link #; = ",ptr->name);
    }

   void show(FixedText *ptr)
    {
     Printf(out,"FixedText #; = ",ptr->name);
    }

   void show(OneLine *ptr)
    {
     Printf(out,"OneLine #; = ",ptr->name);
    }

   void show(MultiLine *ptr)
    {
     Printf(out,"MultiLine #; = ",ptr->name);
    }

   void show(Text *ptr)
    {
     Printf(out,"Text #; = ",ptr->name);
    }

  public:

   template <class T>
   explicit ShowName(T *ptr)
    : out(Range(buf))
    {
     show(ptr);

     str=out.close();
    }

   StrLen get() const { return str; }
 };

/* class Book::PrepareContext */

class Book::PrepareContext : NoCopy
 {
   Coord table_dxy;
   Coord element_space;
   Coord knob_dxy;

   CCore::Video::Font text_font;
   FontSize fs;

   CCore::Video::Font element_font;
   FontSize efs;

   CCore::Video::Font comment_font;
   FontSize cfs;

   DynArray<PaneRef> &refs;
   PaneRef &cursor;
   bool erase_cursor = true ;

  private:

   void addRef(Pane pane,Ref ref)
    {
     refs.append_copy({pane,ref});

     if( cursor.is(ref) )
       {
        cursor.pane=pane;
        erase_cursor=false;
       }
    }

   template <class T>
   void addPad(Pane pad,T *ptr)
    {
     addRef(pad,Ref(Nothing,ptr));
    }

   template <class T,auto Def>
   void addPad(Pane pad,OptData<T,Def> *ptr)
    {
     addPad(pad,(OptDataBase<T> *)ptr);
    }

   void addPad(Pane,StrLen *) {}

   void addOpenFlag(Pane pane,OpenFlag *ptr)
    {
     addRef(pane,ptr);
    }

   template <class T>
   void addListRef(Pane pane,T *ptr)
    {
     addRef(pane,ptr);
    }

  private:

   Coord tableLen(PtrLen<const Coord> tdx)
    {
     Coord ret=table_dxy;

     for(Coord dx : tdx ) ret=AddSize(ret,dx,table_dxy);

     return ret;
    }

   Point sizeListBtn() { return SizeListBtn(knob_dxy); }

  private:

   struct Place
    {
     void *data;
     void *datapad;

     Point (*size_func)(PrepareContext *ctx,void *data);

     void (*place_func)(PrepareContext *ctx,Point base,Pane pad,void *data,void *datapad);

     Point size(PrepareContext *ctx) const { return size_func(ctx,data); }

     void place(PrepareContext *ctx,Point base,Pane pad) const { place_func(ctx,base,pad,data,datapad); }
    };

   template <class T,class S=int>
   struct PlaceOf : Place
    {
     static Point SizeFunc(PrepareContext *ctx,void *data)
      {
       return ctx->size(*static_cast<T *>(data));
      }

     static void PlaceFunc(PrepareContext *ctx,Point base,Pane pad,void *data,void *datapad)
      {
       T *ptr=static_cast<T *>(data);

       if( datapad )
         ctx->addPad(pad,static_cast<S *>(datapad));
       else
         ctx->addPad(pad,ptr);

       ctx->place(base,*ptr);
      }

     explicit PlaceOf(T &obj)
      {
       data=&obj;
       datapad=0;
       size_func=SizeFunc;
       place_func=PlaceFunc;
      }

     PlaceOf(S &obj,T &desc,bool)
      {
       data=&desc;
       datapad=&obj;
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
   Point sizeTable(TableLayout<RowCount> &layout,PtrLen<const Row> table)
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
   void placeTable(TableLayout<RowCount> &layout,Point base,PtrLen<const Row> table)
    {
     Coord dx0=layout.col[0].dx;
     Coord dx1=layout.col[1].dx;

     Coord dx=dx0+dx1+3*table_dxy;
     Coord dy=0;

     for(ulen i : IndLim(RowCount) )
       {
        Coord tdy=layout.row[i].dy;

        table[i].place.place(this,base+Point(dx,dy+table_dxy),Pane(base.x,base.y+dy,dx,tdy+2*table_dxy));

        dy+=tdy+table_dxy;
       }
    }

   template <ulen RowCount>
   Point prepareTable(TableLayout<RowCount> &layout,Point base,PtrLen<const Row> table)
    {
     Point ret=sizeTable(layout,table);

     placeTable(layout,base,table);

     return ret;
    }

   template <class T>
   Point sizeTable(T *ptr)
    {
     Point ret;

     ptr->template apply<Row,PlaceOf>( [&] (auto table,auto &layout) { ret=sizeTable(layout,table); } );

     return ret;
    }

   template <class T>
   void placeTable(Point base,T *ptr)
    {
     ptr->template apply<Row,PlaceOf>( [&] (auto table,auto &layout) { placeTable(layout,base,table); } );
    }

   template <class T>
   Point prepareTable(Point base,T *ptr)
    {
     Point ret;

     ptr->template apply<Row,PlaceOf>( [&] (auto table,auto &layout) { ret=prepareTable(layout,base,table); } );

     return ret;
    }

   Point size(ElementList &list)
    {
     Point ret;

     for(Element &elem : ForIntList(list) )
       {
        ret=StackYSize_guarded(ret,Point(0,element_space));

        Point s=sizeElement(elem.ptr.getPtr());

        elem.pane.dx=s.x;
        elem.pane.dy=s.y;

        ret=StackYSize_guarded(ret,s);
       }

     list.size=ret;

     return ret;
    }

   void place(Point base,ElementList &list)
    {
     for(Element &elem : ForIntList(list) )
       {
        base=base.addY(element_space);

        elem.pane.x=base.x;
        elem.pane.y=base.y;

        placeElement(base,elem.ptr.getPtr(),Ref(list,elem));

        base=base.addY(elem.pane.dy);
       }
    }

   Point prepare(Point base,ElementList &list)
    {
     Point ret=size(list);

     place(base,list);

     return ret;
    }

   Point size(Defaults &obj)
    {
     Point s=sizeTable(&obj);

     return StackYSize_guarded(s,Point(0,element_space));
    }

   void place(Point base,Defaults &obj)
    {
     placeTable(base.addY(element_space),&obj);
    }

   Point prepare(Point base,Defaults &obj)
    {
     Point ret=size(obj);

     place(base,obj);

     return ret;
    }

  private:

   Point size(StrLen text)
    {
     return text_font->text(text).getSize();
    }

   void place(Point,StrLen) {}

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

   template <OneOfTypes<Point,Ratio,Coord,Strength,bool,Effect,Align,ulen> T>
   Point size(T data)
    {
     ShowData show(data);

     return size(show.get());
    }

   template <OneOfTypes<VColor,Point,Ratio,Coord,int,bool,Effect,Align,ulen> T>
   void place(Point,T &) {}

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

   template <class ... TT>
   Point size(NamedPtr<TT...> &obj)
    {
     if( obj.hasName() ) return size(obj.name);

     if( obj.hasObj() ) return size(obj.ptr.getPtr());

     return Null;
    }

   template <class ... TT>
   void place(Point base,NamedPtr<TT...> &obj)
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

   template <class T>
   Point size(T *ptr)
    {
     return sizeBody(ptr);
    }

   template <class T>
   void place(Point base,T *ptr)
    {
     placeBody(base,ptr);
    }

  private:

   template <class ... TT>
   Point sizeElement(AnyPtr<TT...> anyptr)
    {
     Point ret;

     anyptr.apply( [&] (auto *ptr) { if( ptr ) ret=sizeElement(ptr); } );

     return ret;
    }

   template <class ... TT>
   void placeElement(Point base,AnyPtr<TT...> anyptr,Ref eref)
    {
     anyptr.apply( [&] (auto *ptr) { if( ptr ) placeElement(base,ptr,eref); } );
    }

   template <class T>
   Point sizeElement(T *ptr)
    {
     ShowName show(ptr);

     TextSize ts=element_font->text(show.get());

     Coord dy=BoxExt(efs.dy);

     Point s=sizeBody(ptr);

     return StackYSize(s,Point(ts.full_dx,dy));
    }

   template <class T>
   void placeElement(Point base,T *ptr,Ref eref)
    {
     ShowName show(ptr);

     Point size=element_font->text(show.get()).getSize();

     addRef(Pane(base,size),eref);

     Coord dy=BoxExt(efs.dy);

     placeBody(base.addY(dy),ptr);
    }

   Point sizeElement(Scope *ptr)
    {
     ShowName show(ptr);

     TextSize ts=element_font->text(show.get());

     Coord dy=BoxExt(efs.dy)+efs.dy;

     Point s=sizeBody(ptr);

     return StackYSize(s,Point(ts.full_dx,dy));
    }

   Point sizeElement(Section *ptr)
    {
     Coord dxy=cfs.dy;
     Coord edxy=BoxExt(dxy);

     TextSize ts=comment_font->text(Range(ptr->comment));

     Coord tx=AddSize(edxy,ts.full_dx);

     if( ptr->open )
       {
        Point s1(tx,edxy+dxy);

        Point s2=size(ptr->list);

        return StackYSize_guarded(s1,s2);
       }
     else
       {
        return Point(tx,2*dxy);
       }
    }

   void placeElement(Point base,Section *ptr,Ref eref)
    {
     Coord dxy=cfs.dy;

     addOpenFlag(Pane(base,dxy),ptr);

     Point size=comment_font->text(Range(ptr->comment)).getSize();

     addRef(Pane(base.addX(BoxExt(dxy)),Sup(size,Point::Diag(dxy))),eref);

     if( ptr->open )
       {
        place(base.addY(BoxExt(dxy)),ptr->list);
       }
     else
       {
       }
    }

   template <class T>
   Point sizeBody(T *ptr)
    {
     if( ptr->open )
       {
        Point s=sizeTableExt(ptr);

        return StackXSize_guarded(s,Point(BoxExt(knob_dxy),knob_dxy));
       }
     else
       {
        return Point::Diag(knob_dxy);
       }
    }

   template <class T>
   void placeBody(Point base,T *ptr)
    {
     addOpenFlag(Pane(base,knob_dxy),ptr);

     if( ptr->open )
       {
        placeTableExt(base.addX(BoxExt(knob_dxy)),ptr);
       }
    }

   Point sizeBody(Bitmap *ptr)
    {
     return sizeTable(ptr);
    }

   void placeBody(Point base,Bitmap *ptr)
    {
     placeTable(base,ptr);
    }

  private:

   Point size(Link &link)
    {
     return size(LinkDesc(link));
    }

   void place(Point,Link &) {}

   Point size(Table::Data &obj)
    {
     obj.cellsize.erase();

     auto width=Range(obj.width);
     auto cells=Range(obj.cells);

     ulen nx=width.len;

     if( !nx ) return Null;

     ulen ny=cells.len/nx+(cells.len%nx!=0)+1;

     Coord *tdx=obj.cellsize.extend_default(LenAdd(nx,ny)).ptr;
     Coord *tdy=tdx+nx;

     for(ulen i : IndLim(nx) )
       {
        ShowData show(width[i]);

        Point s=size(show.get());

        tdx[i]=s.x;

        Replace_max(tdy[0],s.y);
       }

     for(ulen k : IndLim(cells.len) )
       {
        Point s=size(cells[k]);

        ulen i=k%nx;
        ulen j=k/nx+1;

        Replace_max(tdx[i],s.x);
        Replace_max(tdy[j],s.y);
       }

     Coord dx=tableLen(Range(tdx,nx));
     Coord dy=tableLen(Range(tdy,ny));

     return Point(dx,dy);
    }

   void place(Point base,Table::Data &obj)
    {
     auto width=Range(obj.width);
     auto cells=Range(obj.cells);

     ulen nx=width.len;

     if( !nx ) return;

     Coord *tdx=obj.cellsize.getPtr();
     Coord *tdy=tdx+nx;

     Coord dx=table_dxy;
     Coord dy=2*table_dxy+tdy[0];

     for(ulen k : IndLim(cells.len) )
       {
        ulen i=k%nx;
        ulen j=k/nx+1;

        place(base.addX(dx).addY(dy),cells[k]);

        if( i<nx-1 )
          {
           dx+=tdx[i]+table_dxy;
          }
        else
          {
           dx=table_dxy;
           dy+=tdy[j]+table_dxy;
          }
       }
    }

   template <OneOfTypes<FrameList,ItemList> T>
   Point size(T &obj)
    {
     if( !obj.cur ) return Null;

     return sizeList(&obj);
    }

   template <OneOfTypes<FrameList,ItemList> T>
   void place(Point base,T &obj)
    {
     if( +obj.cur ) placeList(base,&obj);
    }

  private:

   template <class T>
   Point sizeTableExt(T *ptr)
    {
     return sizeTable(ptr);
    }

   template <class T>
   void placeTableExt(Point base,T *ptr)
    {
     placeTable(base,ptr);
    }

   Point sizeTableExt(Scope *ptr)
    {
     Point s1=size(ptr->defs);

     Point s2=size(ptr->list);

     Point s=StackYSize_guarded(s1,s2,Point(0,element_space));

     ptr->size=s;

     return s;
    }

   void placeTableExt(Point base,Scope *ptr)
    {
     place(base,ptr->defs);

     Coord dy=ptr->defs.layout.size.y+element_space;

     place(base.addY(dy),ptr->list);
    }

   template <class T>
   Point sizeList(T *ptr)
    {
     Point s1=sizeListBtn();
     Point s2=sizeTable(ptr);

     return StackXSize_guarded(s1,s2);
    }

   template <class T>
   void placeList(Point base,T *ptr)
    {
     Point s1=sizeListBtn();
     Point s2=ptr->layout.size;

     if( s1.y<s2.y )
       {
#if 0

        Coord delta=s2.y-s1.y;

        addListRef(Pane(base.addY(delta/2),s1),ptr);

#else

        addListRef(Pane(base,s1),ptr);

#endif

        placeTable(base.addX(s1.x),ptr);
       }
     else
       {
        Coord delta=s1.y-s2.y;

        addListRef(Pane(base,s1),ptr);

        placeTable(base.addX(s1.x).addY(delta/2),ptr);
       }
    }

  public:

   PrepareContext(const Config &cfg,DynArray<PaneRef> &refs_,PaneRef &cursor_)
    : refs(refs_),
      cursor(cursor_)
    {
     table_dxy=+cfg.table_dxy;
     element_space=+cfg.element_space;
     knob_dxy=+cfg.knob_dxy;
     text_font=+cfg.text_font;
     element_font=+cfg.element_font;
     comment_font=+cfg.comment_font;

     fs=text_font->getSize();
     efs=element_font->getSize();
     cfs=comment_font->getSize();
    }

   PrepareResult place(Doc *doc)
    {
     Point s1=prepareTable(Null,doc);

     Coord dy=s1.y;

     Point s2=prepare(Point(0,dy),doc->defs);

     dy+=s2.y;

     Point s3=prepare(Point(0,dy),doc->list);

     return {StackYSize_guarded(s1,s2,s3),erase_cursor};
    }
 };

/* class Book::DrawContext */

class Book::DrawContext : NoCopy
 {
   DrawBuf buf;

   Fraction line_width;

   Coord table_dxy;
   Coord element_space;
   Coord knob_dxy;

   VColor gray;
   VColor snow;
   VColor face;
   VColor top;
   VColor alert;
   VColor table;
   VColor text;
   VColor element;
   VColor comment;

   CCore::Video::Font text_font;
   FontSize fs;

   CCore::Video::Font element_font;
   FontSize efs;

   CCore::Video::Font comment_font;
   FontSize cfs;

  private:

   Coord tableLen(PtrLen<const Coord> tdx)
    {
     Coord ret=table_dxy;

     for(Coord dx : tdx ) ret+=dx+table_dxy;

     return ret;
    }

   void drawTable(Point base,PtrLen<const Coord> tdx,PtrLen<const Coord> tdy)
    {
     Coord lenx=tableLen(tdx);
     Coord leny=tableLen(tdy);

     DrawBuf buf1=buf;

     buf1.shift(base);

     SmoothDrawArt art(buf1);

     MPoint A=Point::Diag(table_dxy-1);

     A=A/2;

     {
      MPoint O=A;
      MCoord fdx=Fraction(lenx-table_dxy);

      art.path(line_width,table,O,O.addX(fdx));

      for(Coord dy : tdy )
        {
         O=O.addY(Fraction(dy+table_dxy));

         art.path(line_width,table,O,O.addX(fdx));
        }
     }

     {
      MPoint O=A;
      MCoord fdy=Fraction(leny-table_dxy);

      art.path(line_width,table,O,O.addY(fdy));

      for(Coord dx : tdx )
        {
         O=O.addX(Fraction(dx+table_dxy));

         art.path(line_width,table,O,O.addY(fdy));
        }
     }
    }

   void drawPlus(Point base,Coord dxy)
    {
     MPane p(Pane(base,dxy));

     if( !p ) return;

     SmoothDrawArt art(buf);

     // center and radius

     MCoord len=p.dx;
     MCoord radius=len/2;

     MPoint center=p.getCenter();

     // body

     art.ball(center,radius,YField(p.y,snow,p.ey,gray));

     // face

     MCoord a=radius/2;
     MCoord w=radius/3;

     art.path(w,face,center.subX(a),center.addX(a));
     art.path(w,face,center.subY(a),center.addY(a));
    }

   void drawMinus(Point base,Coord dxy)
    {
     MPane p(Pane(base,dxy));

     if( !p ) return;

     SmoothDrawArt art(buf);

     // center and radius

     MCoord len=p.dx;
     MCoord radius=len/2;

     MPoint center=p.getCenter();

     // body

     art.ball(center,radius,YField(p.y,snow,p.ey,gray));

     // face

     MCoord a=radius/2;
     MCoord w=radius/3;

     art.path(w,face,center.subX(a),center.addX(a));
    }

   void drawPlus(Point base) { drawPlus(base,knob_dxy); }

   void drawMinus(Point base) { drawMinus(base,knob_dxy); }

   void drawBegBtn(SmoothDrawArt &art,Pane pane,bool enable)
    {
     MPane p(pane);

     if( !p ) return;

     MCoord delta=p.dx/10;
     VColor fc=enable?face:gray;

     FigureBox fig1(p);

     fig1.solid(art,YField(p.y,snow,p.ey,gray));

     MPane q=p.shrink(delta);

     FigureUpArrow fig2(q);

     fig2.curveSolid(art,fc);

     FigureBox fig3(q.x,q.ex,q.y-delta/2,q.y+delta/2);

     fig3.solid(art,fc);
    }

   void drawPrevBtn(SmoothDrawArt &art,Pane pane,bool enable)
    {
     MPane p(pane);

     if( !p ) return;

     MCoord delta=p.dx/10;
     VColor fc=enable?face:gray;

     FigureBox fig1(p);

     fig1.solid(art,YField(p.y,snow,p.ey,gray));

     FigureUpArrow fig2(p.shrink(delta));

     fig2.curveSolid(art,fc);
    }

   void drawWheelPad(SmoothDrawArt &art,Pane pane)
    {
     MPane p(pane);

     if( !p ) return;

     MPoint center=p.getCenter();
     MCoord radius=Div(2,5)*p.dx;

     art.ball(center,radius,face);
    }

   void drawNextBtn(SmoothDrawArt &art,Pane pane,bool enable)
    {
     MPane p(pane);

     if( !p ) return;

     MCoord delta=p.dx/10;
     VColor fc=enable?face:gray;

     FigureBox fig1(p);

     fig1.solid(art,YField(p.y,snow,p.ey,gray));

     FigureDownArrow fig2(p.shrink(delta));

     fig2.curveSolid(art,fc);
    }

   void drawEndBtn(SmoothDrawArt &art,Pane pane,bool enable)
    {
     MPane p(pane);

     if( !p ) return;

     MCoord delta=p.dx/10;
     VColor fc=enable?face:gray;

     FigureBox fig1(p);

     fig1.solid(art,YField(p.y,snow,p.ey,gray));

     MPane q=p.shrink(delta);

     FigureDownArrow fig2(q);

     fig2.curveSolid(art,fc);

     FigureBox fig3(q.x,q.ex,q.ey-delta/2,q.ey+delta/2);

     fig3.solid(art,fc);
    }

   template <class T>
   void drawListBtn(Point base,Coord dxy,T *ptr)
    {
     SmoothDrawArt art(buf);

     Pane pane1(base,dxy); base.y+=dxy;
     Pane pane2(base,dxy); base.y+=dxy;
     Pane pane3(base,dxy); base.y+=dxy;
     Pane pane4(base,dxy); base.y+=dxy;
     Pane pane5(base,dxy);

     drawBegBtn(art,pane1,ptr->canBeg());
     drawPrevBtn(art,pane2,ptr->canPrev());
     drawWheelPad(art,pane3);
     drawNextBtn(art,pane4,ptr->canNext());
     drawEndBtn(art,pane5,ptr->canEnd());
    }

   Point sizeListBtn() { return SizeListBtn(knob_dxy); }

   void drawScopeLine(Point base,Point size)
    {
     DrawBuf buf1=buf;

     buf1.shift(base.subX(BoxExt(knob_dxy)).addY(knob_dxy));

     SmoothDrawArt art(buf1);

     MPoint A=Point(knob_dxy-1,0);

     A=A/2;

     MPoint B=A.addY(Fraction(size.y-knob_dxy)+Fraction(element_space,1));

     MPoint C=B.addX(Fraction(size.x+knob_dxy));

     art.path(line_width,table,A,B,C);
    }

  private:

   struct Draw
    {
     void *data;
     bool alert;

     void (*draw_func)(DrawContext *ctx,Pane cell,Coord offy,void *data,bool alert);

     void draw(DrawContext *ctx,Pane cell,Coord offy) const { draw_func(ctx,cell,offy,data,alert); }
    };

   template <class T>
   struct DrawOf : Draw
    {
     static void DrawFunc(DrawContext *ctx,Pane cell,Coord offy,void *data,bool)
      {
       ctx->draw(cell,offy,*static_cast<T *>(data));
      }

     static void AlertDrawFunc(DrawContext *ctx,Pane cell,Coord offy,void *data,bool alert)
      {
       ctx->draw(cell,offy,*static_cast<T *>(data),alert);
      }

     explicit DrawOf(T &obj)
      {
       data=&obj;
       alert=false;
       draw_func=DrawFunc;
      }

     explicit DrawOf(auto &,T &desc,bool alert_)
      {
       data=&desc;
       alert=alert_;
       draw_func=AlertDrawFunc;
      }
    };

   struct Row
    {
     StrLen type;
     StrLen name;
     Draw draw;
    };

   template <ulen RowCount>
   void drawTable(Point base,PtrLen<const Row> table,const TableLayout<RowCount> &layout)
    {
     Coord dx0=layout.col[0].dx;
     Coord dx1=layout.col[1].dx;
     Coord dx2=layout.col[2].dx;

     {
      VColor vc=this->table;

      DrawBuf buf1=buf;

      buf1.shift(base);

      SmoothDrawArt art(buf1);

      MPoint A=Point::Diag(table_dxy-1);

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

     ptr->template apply<Row,DrawOf>( [&] (auto table,auto &layout) { drawTable(base,table,layout); ret=layout.size.y; } );

     return ret;
    }

   Coord draw(Point base,ElementList &list)
    {
     Pane clip=buf.getClip();

     if( !clip ) return list.size.y;

     Coord lim=clip.y+clip.dy;

     for(Element &elem : ForIntList(list) )
       {
        base=base.addY(element_space);

        if( base.y>=lim ) break;

        if( base.y+elem.pane.dy>clip.y ) drawElement(base,elem.ptr.getPtr());

        base=base.addY(elem.pane.dy);
       }

     return list.size.y;
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

     fig.curveLoop(art,HalfPos,line_width,table);
    }

   template <OneOfTypes<Point,Ratio,Coord,Strength,bool,Effect,Align,ulen> T>
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

   template <class ... TT>
   void draw(Pane cell,Coord offy,const NamedPtr<TT...> &obj)
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

   void draw(Pane cell,Coord offy,Link &link)
    {
     draw(cell,offy,LinkDesc(link),LinkAlert(link));
    }

   void draw(Pane cell,Coord,Table::Data &obj)
    {
     auto width=Range(obj.width);
     auto cells=Range(obj.cells);

     ulen nx=width.len;

     if( !nx ) return;

     Point base=cell.getBase();
     Coord offy=fs.by;

     Coord *tdx=obj.cellsize.getPtr();
     Coord *tdy=tdx+nx;

     ulen ny=cells.len/nx+(cells.len%nx!=0)+1;

     drawTable(base,Range(tdx,nx),Range(tdy,ny));

     Coord dx=table_dxy;
     Coord dy=table_dxy;

     for(ulen i : IndLim(nx) )
       {
        ShowData show(width[i]);

        draw(Pane(base.addX(dx).addY(dy),tdx[i],tdy[0]),offy,show.get());

        dx+=tdx[i]+table_dxy;
       }

     dx=table_dxy;
     dy=2*table_dxy+tdy[0];

     for(ulen k : IndLim(cells.len) )
       {
        ulen i=k%nx;
        ulen j=k/nx+1;

        draw(Pane(base.addX(dx).addY(dy),tdx[i],tdy[j]),offy,cells[k]);

        if( i<nx-1 )
          {
           dx+=tdx[i]+table_dxy;
          }
        else
          {
           dx=table_dxy;
           dy+=tdy[j]+table_dxy;
          }
       }
    }

   template <OneOfTypes<FrameList,ItemList> T>
   void draw(Pane cell,Coord,T &obj)
    {
     if( !obj.cur )
       {
        buf.erase(cell,gray);
       }
     else
       {
        drawList(cell.getBase(),&obj);
       }
    }

  private:

   template <class ... TT>
   void draw(Pane cell,Coord offy,AnyPtr<TT...> anyptr)
    {
     anyptr.apply( [&] (auto *ptr) { if( ptr ) draw(cell,offy,ptr); } );
    }

   template <class T>
   void draw(Pane cell,Coord,T *ptr)
    {
     drawBody(cell.getBase(),ptr);
    }

  private:

   template <class ... TT>
   void drawElement(Point base,AnyPtr<TT...> anyptr)
    {
     anyptr.apply( [&] (auto *ptr) { if( ptr ) drawElement(base,ptr); } );
    }

   template <class T>
   void drawElement(Point base,T *ptr)
    {
     ShowName show(ptr);

     element_font->text(buf,Pane(base,MaxCoord,MaxCoord),TextPlace(AlignX_Left,AlignY_Top),show.get(),element);

     Coord dy=BoxExt(efs.dy);

     drawBody(base.addY(dy),ptr);
    }

   void drawElement(Point base,Section *ptr)
    {
     Coord dxy=cfs.dy;

     if( ptr->open )
       {
        drawMinus(base,dxy);

        comment_font->text(buf,Pane(base.addX(BoxExt(dxy)),MaxCoord,MaxCoord),TextPlace(AlignX_Left,AlignY_Top),Range(ptr->comment),comment);

        draw(base.addY(BoxExt(dxy)),ptr->list);
       }
     else
       {
        drawPlus(base,dxy);

        comment_font->text(buf,Pane(base.addX(BoxExt(dxy)),MaxCoord,MaxCoord),TextPlace(AlignX_Left,AlignY_Top),Range(ptr->comment),comment);
       }
    }

   template <class T>
   void drawBody(Point base,T *ptr)
    {
     if( ptr->open )
       {
        drawMinus(base);

        drawTableExt(base.addX(BoxExt(knob_dxy)),ptr);
       }
     else
       {
        drawPlus(base);
       }
    }

   void drawBody(Point base,Bitmap *ptr)
    {
     drawTable(base,ptr);
    }

  private:

   template <class T>
   void drawTableExt(Point base,T *ptr)
    {
     drawTable(base,ptr);
    }

   void drawTableExt(Point base,Scope *ptr)
    {
     Coord dy=draw(base,ptr->defs);

     draw(base.addY(dy),ptr->list);

     drawScopeLine(base,ptr->size);
    }

   template <class T>
   void drawListBtn(Point base,T *ptr) { drawListBtn(base,knob_dxy,ptr); }

   template <class T>
   void drawList(Point base,T *ptr)
    {
     Point s1=sizeListBtn();
     Point s2=ptr->layout.size;

     if( s1.y<s2.y )
       {
#if 0

        Coord delta=s2.y-s1.y;

        drawListBtn(base.addY(delta/2),ptr);

#else

        drawListBtn(base,ptr);

#endif

        drawTable(base.addX(s1.x),ptr);
       }
     else
       {
        Coord delta=s1.y-s2.y;

        drawListBtn(base,ptr);

        drawTable(base.addX(s1.x).addY(delta/2),ptr);
       }
    }

  public:

   DrawContext(const DrawBuf &buf_,const Config &cfg)
    : buf(buf_)
    {
     line_width=+cfg.line_width;
     table_dxy=+cfg.table_dxy;
     element_space=+cfg.element_space;
     knob_dxy=+cfg.knob_dxy;
     gray=+cfg.gray;
     snow=+cfg.snow;
     face=+cfg.face;
     alert=+cfg.alert;
     table=+cfg.table;
     text=+cfg.text;
     element=+cfg.element;
     comment=+cfg.comment;
     text_font=+cfg.text_font;
     element_font=+cfg.element_font;
     comment_font=+cfg.comment_font;

     fs=text_font->getSize();
     efs=element_font->getSize();
     cfs=comment_font->getSize();
    }

   void draw(Doc *doc)
    {
     Coord dy=drawTable(Null,doc);

     dy+=draw(Point(0,dy),doc->defs);

     draw(Point(0,dy),doc->list);
    }
 };

/* class Book */

auto Book::prepare(const Config &cfg,DynArray<PaneRef> &refs,PaneRef &cursor) const -> PrepareResult
 {
  if( !doc ) return {Point(100,100),true};

  PrepareContext ctx(cfg,refs,cursor);

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
