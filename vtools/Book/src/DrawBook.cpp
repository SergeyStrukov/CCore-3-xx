/* DrawBook.cpp */
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

#include <inc/DrawBook.h>
#include <inc/SpanLenEngine.h>
#include <inc/SelectFrames.h>

#include <CCore/inc/video/FigureLib.h>

namespace App {
namespace DrawBook {

/* struct Prepare */

 // refs

void Prepare::addRef(RefType ref,Pane pane)
 {
  auto list=Range(stack);

  if( +ref ) refs.append_copy({pane,ref,RefArray<ulen>(DoCopy(list.len),list.ptr)});
 }

void Prepare::addRef(AnyPtr<Book::TypeDef::Link,Book::TypeDef::Page> ref,Pane pane)
 {
  if( +ref ) addRef(CastAnyPtr<RefType>(ref),pane);
 }

 // common

Font Prepare::use(const Book::TypeDef::Format *fmt)
 {
  if( fmt )
    {
     return map(fmt->font,+cfg.font);
    }
  else
    {
     return +cfg.font;
    }
 }

Font Prepare::useFixed(const Book::TypeDef::Format *fmt)
 {
  if( fmt )
    {
     return map(fmt->font,+cfg.codefont);
    }
  else
    {
     return +cfg.codefont;
    }
 }

Font Prepare::over(Font font,const Book::TypeDef::Format *fmt)
 {
  if( fmt )
    {
     return map(fmt->font,font);
    }
  else
    {
     return font;
    }
 }

TextSize Prepare::SizeSpan(Font font,StrLen text)
 {
  return font->text(text);
 }

Coord Prepare::SizeSpace(Font font)
 {
  return SizeSpan(font," "_c).dx;
 }

 // size(Book::TypeDef::Text *)

void Prepare::correctRefs(ulen refs_len,Coord delta_x,Coord delta_y)
 {
  for(RefPane &ref : Range(refs).part(refs_len) )
    {
     ref.pane+=Point(delta_x,delta_y);
    }
 }

Coord Prepare::sizeSpan(Font font,Book::TypeDef::Span span,Point base)
 {
  TextSize ts=SizeSpan(over(font,span.fmt),span.body);

  addRef(span.ref,TextPane(base,ts));

  return ts.dx;
 }

auto Prepare::sizeSpan(const Book::TypeDef::Format *prev_fmt,Font font,Coord space_dx,Book::TypeDef::Span span,Point base) -> LineSize
 {
  Font span_font=over(font,span.fmt);

  Coord sdx=0;

  if( InsSpace(span.body) )
    {
     if( span.fmt && prev_fmt==span.fmt )
       {
        sdx=SizeSpace(span_font);
       }
     else
       {
        sdx=space_dx;
       }
    }

  TextSize ts=SizeSpan(span_font,span.body);

  addRef(span.ref,TextPane(base.addX(sdx),ts));

  return {ts.dx,ts.dx+sdx};
 }

Coord Prepare::sizeLine(Font font,Coord space_dx,PtrLen<const Book::TypeDef::Span> line,Point base)
 {
  Coord tdx=0;

  if( +line )
    {
     tdx=sizeSpan(font,*line,base);

     const Book::TypeDef::Format *fmt=line->fmt;

     base.x+=tdx;

     for(++line; +line ;++line)
       {
        Coord dx=sizeSpan(fmt,font,space_dx,*line,base).edx;

        tdx=AddSize(tdx,dx);

        base.x+=dx;

        fmt=line->fmt;
       }
    }

  return tdx;
 }

Point Prepare::size(Font font,Coord space_dx,PtrLen<const Book::TypeDef::Span> range,Book::TypeDef::OneLine *placement,FrameExt_OneLine *ext,Coord wdx,Point base)
 {
  if( !placement ) return Null;

  FontSize fs=font->getSize();

  ulen refs_len=refs.getLen();

  Coord dx=sizeLine(font,space_dx,range,base.addY(fs.by));

  switch( placement->align )
    {
     case Book::LineRight :
      {
       Coord extra=PlusSub(wdx,dx);

       Coord offx=extra;

       ext->offx=offx;

       correctRefs(refs_len,offx);
      }
     break;

     case Book::LineCenter :
      {
       Coord extra=PlusSub(wdx,dx);

       Coord offx=extra/2;

       ext->offx=offx;

       correctRefs(refs_len,offx);
      }
     break;

     default: // case Book::LineLeft :
      {
       ext->offx=0;
      }
    }

  return Point(Max(dx,wdx),fs.dy);
 }

Point Prepare::size(Font font,Coord space_dx,PtrLen<const Book::TypeDef::Span> range,Book::TypeDef::MultiLine *placement,FrameExt_MultiLine *ext,Coord wdx,Point base)
 {
  ext->split.erase();

  if( !placement ) return Null;

  FontSize fs=font->getSize();

  Coord first_dx=Cast(placement->first_line_space)*fs.dy;
  Coord dy=Cast(placement->line_space)*fs.dy;

  ext->first_dx=first_dx;
  ext->dy=dy;

  Coord tdx=fs.dy;
  Coord tdy=fs.dy;

  if( +range )
    {
     base.y+=fs.by;

     Coord dx=AddSize( sizeSpan(font,*range,base.addX(first_dx)) ,first_dx);

     const Book::TypeDef::Format *fmt=range->fmt;

     Point p=base;

     p.x+=dx;

     while( +range )
       {
        ulen len=1;

        for(++range; +range ;++range,len++)
          {
           ulen refs_len=refs.getLen();

           LineSize delta=sizeSpan(fmt,font,space_dx,*range,p);

           fmt=range->fmt;

           if( delta.edx<=wdx-dx )
             {
              dx=AddSize(dx,delta.edx);

              p.x+=delta.edx;
             }
           else
             {
              correctRefs(refs_len,-dx,dy);

              Replace_max(tdx,dx);

              tdy=AddSize(tdy,dy);

              dx=delta.dx;

              base.y+=dy;

              p=base;

              p.x+=dx;

              break;
             }
          }

        ext->split.append_copy(len);
       }

     Replace_max(tdx,dx);
    }

  return Point(tdx,tdy);
 }

Point Prepare::size(Book::TypeDef::Text *obj,FrameExt *ext,Coord wdx,Point base)
 {
  if( !obj ) return Null;

  Font font=use(obj->fmt);

  Coord space_dx=SizeSpace(font);

  auto range=obj->list.getRange();

  Point ret;

  obj->placement.getPtr().apply( [&] (auto *placement) { ret=size(font,space_dx,range,placement,AutoCast(ext),wdx,base); } );

  return ret;
 }

 // size(Book::TypeDef::FixedText *)

Coord Prepare::sizeLine(Font font,Book::TypeDef::Line line,Point base)
 {
  Coord tdx=0;

  for(Book::TypeDef::Span span : line.getRange() )
    {
     TextSize ts=SizeSpan(over(font,span.fmt),span.body);

     addRef(span.ref,TextPane(base,ts));

     tdx=AddSize(tdx,ts.dx);

     base.x+=ts.dx;
    }

  return tdx;
 }

Point Prepare::size(Book::TypeDef::FixedText *obj,FrameExt *,Coord,Point base)
 {
  if( !obj ) return Null;

  Font font=useFixed(obj->fmt);

  FontSize fs=font->getSize();

  Coord dy=fs.dy;

  auto range=obj->list.getRange();

  base.y+=fs.by;

  Coord dx=0;

  for(const Book::TypeDef::Line line : range )
    {
     Replace_max(dx,sizeLine(font,line,base));

     base.y+=dy;
    }

  return Point(dx,MulSize(range.len,dy));
 }

 // size(Book::TypeDef::Bitmap *)

Point Prepare::size(Book::TypeDef::Bitmap *obj,FrameExt *,Coord,Point)
 {
  const Bitmap *bitmap=map(obj);

  if( !bitmap ) return Null;

  return {CountToCoord(bitmap->dX()),CountToCoord(bitmap->dY())};
 }

 // size(Book::TypeDef::TextList *)

Coord Prepare::SizeBullet(Font font,StrLen text)
 {
  return SizeSpan(font,text).dx;
 }

auto Prepare::getBase(Book::TypeDef::Text *obj) -> ItemBase
 {
  if( obj ) return {use(obj->fmt)->getSize().by,true};

  return {};
 }

auto Prepare::getBase(Book::TypeDef::FixedText *obj) -> ItemBase
 {
  if( obj ) return {useFixed(obj->fmt)->getSize().by,true};

  return {};
 }

auto Prepare::getBase(Book::TypeDef::Bitmap *) -> ItemBase { return {}; }

auto Prepare::getBase(Book::TypeDef::TextList *obj) -> ItemBase
 {
  if( obj )
    {
     auto list=obj->list.getRange();

     if( !list.len ) return {};

     FontSize fs=use(obj->bullet_fmt)->getSize();

     auto item=list[0];

     {
      auto list=item.list.getRange();

      Coord by1=fs.by;

      if( +list )
        {
         ItemBase base=getBase(list.ptr);

         if( base.ok )
           {
            if( base.by>by1 )
              {
               by1=base.by;
              }
           }
        }

      return {by1,true};
     }
    }

  return {};
 }

auto Prepare::getBase(Book::TypeDef::Collapse *obj) -> ItemBase
 {
  if( obj ) return {use(obj->collapse_fmt)->getSize().by,true};

  return {};
 }

auto Prepare::getBase(Book::TypeDef::Table *) -> ItemBase { return {}; }

auto Prepare::getBase(Book::TypeDef::Frame *frame) -> ItemBase
 {
  LockUse lock(level);

  ItemBase ret;

  frame->body.getPtr().apply( [&] (auto *obj) { ret=getBase(obj); } );

  if( ret.ok ) ret.by+=scale*CastCoord(frame->inner.y)+scale*CastCoord(frame->outer.y);

  return ret;
 }

Point Prepare::sizeItem(FontSize fs,Book::TypeDef::ListItem item,ListItemSize &item_size,Coord bullet_dx,Coord wdx,Point base)
 {
  auto list=item.list.getRange();

  Coord by1=fs.by;
  Coord dy1=fs.dy;
  Coord by2=0;

  if( +list )
    {
     ItemBase base=getBase(list.ptr);

     if( base.ok )
       {
        if( base.by>by1 )
          {
           dy1+=(base.by-by1);
           by1=base.by;
          }
        else
          {
           by2=by1-base.by;
          }
       }
    }

  item_size.by1=by1;
  item_size.dy1=dy1;
  item_size.by2=by2;

  Point s=(*this)(list,wdx,base+Point(bullet_dx,by2));

  return {AddSize(bullet_dx,s.x),Max(dy1,AddSize(by2,s.y))};
 }

Point Prepare::size(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,Coord wdx,Point base)
 {
  if( !obj )
    {
     ext->size_list.erase();

     return Null;
    }

  auto list=obj->list.getRange();

  if( !list.len )
    {
     ext->size_list.erase();

     return Null;
    }

  SetExactArrayLen(ext->size_list,list.len);

  Font font=use(obj->bullet_fmt);

  Coord bullet_len = 0 ;

  for(auto &item : list ) Replace_max(bullet_len,SizeBullet(font,item.bullet));

  Coord bullet_space=scale*Coord(obj->bullet_space);

  Coord item_space=scale*Coord(obj->item_space);

  ext->bullet_len=bullet_len;
  ext->bullet_space=bullet_space;
  ext->item_space=item_space;

  Point ret(0,MulSize(list.len-1,item_space));

  ListItemSize *size_list=ext->size_list.getPtr();

  Coord bullet_dx=AddSize(bullet_len,bullet_space);

  wdx-=bullet_dx;

  FontSize fs=font->getSize();

  Coord down=0;

  for(ulen i=0; i<list.len ;i++)
    {
     push(i);

     Point s=sizeItem(fs,list[i],size_list[i],bullet_dx,wdx,base);

     pop();

     down+=s.y;

     if( i ) down+=item_space;

     size_list[i].down=down;

     ret=StackYSize_guarded(ret,s);

     base.y+=(s.y+item_space);
    }

  return ret;
 }

 // size(Book::TypeDef::Collapse *)

Point Prepare::size(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,Coord wdx,Point base)
 {
  if( !obj ) return Null;

  Font font=use(obj->collapse_fmt);

  Coord len=font->getSize().dy;
  Coord elen=BoxExt(len);

  ext->len=len;

  addRef(RefType(obj),Pane(base,len));

  if( obj->open )
    {
     Point ret;

     if( obj->hide )
       {
        ret={len,elen};
       }
     else
       {
        Coord tx=SizeSpan(font,obj->title).dx;

        ret={AddSize(elen,tx),elen};
       }

     Point s=(*this)(obj->list,wdx,base.addY(elen));

     return StackYSize_guarded(ret,s);
    }
  else
    {
     Coord tx=SizeSpan(font,obj->title).dx;

     return {AddSize(elen,tx),elen};
    }
 }

 // size(Book::TypeDef::Table *)

template <class T>
void Prepare::CorrectSpanLen(T &span,ulen cap)
 {
  if( !span ) span=1;

  if( span>cap ) span=(T)cap;
 }

Point Prepare::size(Book::TypeDef::Table *obj,FrameExt_Table *ext,Coord wdx,Point base)
 {
  if( !obj )
    {
     ext->erase();

     return Null;
    }

  // 1

  Coord space=0;

  if( auto *border=obj->border.getPtr() )
    {
     space=scale*Coord(border->space);
    }

  ext->space=space;

  auto width=obj->width.getRange();

  TempArray<Coord,50> cdx(width.len);

  {
   Coord dx=wdx-MulSize(width.len+1,space);

   if( dx<0 ) dx=0;

   for(ulen i : IndLim(width.len) ) cdx[i]=Div(width[i],100)*dx;
  }

  // 2

  auto rows=obj->rows.getRange();

  for(ulen j : IndLim(rows.len) )
    {
     auto row=rows[j].getRange();

     for(ulen i : IndLim( Min(row.len,width.len) ) )
       {
        if( auto *cell=row[i].getPtr() )
          {
           CorrectSpanLen(cell->span_x,width.len-i);
           CorrectSpanLen(cell->span_y,rows.len-j);

           for(ulen j1 : IndLim(cell->span_y) )
             {
              auto row1=rows[j+j1].getRange();

              if( i<row1.len )
                for(ulen i1 : IndLim( Min<ulen>(cell->span_x,row1.len-i) ) )
                  {
                   if( i1 || j1 ) row1[i+i1]={};
                  }
             }
          }
       }
    }

  // 3

  SpanLenEngine engx(width.len);
  SpanLenEngine engy(rows.len);

  DynArray<ulen> ref_lens(DoReserve,width.len*rows.len+1);

  ref_lens.append_copy(refs.getLen());

  ForTable(obj, [&] (ulen i,ulen j,Book::TypeDef::Cell *cell)
                    {
                     push(i,j);

                     Point size=(*this)(cell->list,cdx[i],base);

                     pop2();

                     ref_lens.append_copy(refs.getLen());

                     engx.add(i,cell->span_x,size.x);
                     engy.add(j,cell->span_y,size.y);

                    } );

  ext->tdx=engx.complete();
  ext->tdy=engy.complete();

  if( obj->hard )
    {
     Coord dx=0;

     for(ulen i : IndLim(width.len) )
       {
        if( Coord p=width[i] ; p>0 )
          {
           Replace_max(dx,Div(100,p)*ext->tdx[i]);
          }
       }

     for(ulen i : IndLim(width.len) )
       {
        ext->tdx[i]=Div(width[i],100)*dx;
       }
    }

  // 4

  ext->alloc(width.len,rows.len);

  TableDesc desc=ext->getDesc();

  desc.setBase();

  // 5

  ulen *ptrLen=ref_lens.getPtr();

  ulen off=*(ptrLen++);

  ForTable(obj, [&] (ulen i,ulen j,Book::TypeDef::Cell *cell)
                    {
                     // 1

                     ulen lim=*(ptrLen++);

                     auto part=Range(refs).part(off,lim-off);

                     off=lim;

                     // 2

                     Point rebase=desc.span(i,j).base;

                     for(RefPane &ref : part ) ref.pane+=rebase;

                     // 3

                     for(ulen j1 : IndLim(cell->span_y) )
                       for(ulen i1 : IndLim(cell->span_x) )
                         {
                          desc.span(i+i1,j+j1).set(i1,j1);
                         }

                    } );

  return desc.getSize();
 }

 // sizeAny()

template <class T>
Point Prepare::sizeAny(T body,FrameExt *ext,Coord wdx,Point base)
 {
  Point ret=Null;

  body.apply( [&] (auto *obj) { ret=size(obj,AutoCast(ext),wdx,base); } );

  return ret;
 }

 // frame

Point Prepare::operator () (PtrLen<Book::TypeDef::Frame> list,Coord wdx,Point base)
 {
  Point ret=Null;

  if( +list )
    {
     FrameExt *ext=map(list.ptr);

     SetExactArrayLen(ext->downs,list.len);

     Coord *downPtr=ext->downs.getPtr();

     Coord down=0;

     for(ulen i : IndLim(list.len) )
       {
        Point s=(*this)(&list[i],i,wdx,base);

        ret=StackYSize_guarded(ret,s);

        base.y+=s.y;

        down+=s.y;

        *(downPtr++)=down;
       }
    }

  return ret;
 }

 // public

Prepare::Prepare(const Config &cfg_,ExtMap &map_,Ratio scale_,DynArray<RefPane> &refs_)
 : cfg(cfg_),map(map_),scale(scale_),refs(refs_),
   stack(DoReserve,100)
 {
 }

Point Prepare::operator () (Book::TypeDef::Frame *frame,ulen frame_index,Coord wdx,Point base)
 {
  push(frame_index);

  FrameExt *ext=map(frame);

  LockUse lock1(ext->lock);
  LockUse lock2(level);

  Point outer=scale*Cast(frame->outer);
  Point inner=scale*Cast(frame->inner);

  ext->outer=outer;
  ext->inner=inner;

  Point off=outer+inner;
  Point delta=2*off;

  Point size=sizeAny(frame->body.getPtr(),ext,wdx-delta.x,base+off)+delta;

  ext->size=size;

  pop();

  return size;
 }

/* struct DrawOut */

void DrawOut::back(TextSize ts,VColor back)
 {
  SmoothDrawArt art(buf.cutRebase(pane));

  MCoord skew=Fraction(ts.skew);

  MPane p(TextPane(base,ts));

  if( skew )
    {
     MCoord delta=Div(ts.dy-ts.by,ts.dy)*skew;

     p+=MPoint(-delta,0);
    }

  FigureSkew fig(p,skew);

  fig.solid(art,back);
 }

void DrawOut::effect(TextSize ts,Effect effect,VColor fore,MCoord width)
 {
  switch( effect )
    {
     case Book::Underline :
      {
       SmoothDrawArt art(buf.cutRebase(pane));

       Coord delta=(ts.dy-ts.by)/2;

       MPoint a=MPoint(base.addY(delta));
       MPoint b=a.addX(Fraction(ts.dx));

       art.path(width,fore,a,b);
      }
     break;

     case Book::Strikeout :
      {
       SmoothDrawArt art(buf.cutRebase(pane));

       Coord delta=ts.by-ts.dy/2;

       MPoint a=MPoint(base.subY(delta));
       MPoint b=a.addX(Fraction(ts.dx));

       art.path(width,fore,a,b);
      }
     break;
    }
 }

void DrawOut::text(Font font,StrLen text,VColor fore)
 {
  font->text(buf,pane,base,text,fore);
 }

void DrawOut::bitmap(const Bitmap *bitmap)
 {
  if( !bitmap ) return;

  bitmap->draw(buf,pane.shrink(base));
 }

void DrawOut::drawPlus(const Config &cfg,Coord len_)
 {
  MPane p(Pane(base,len_));

  if( !p ) return;

  SmoothDrawArt art(buf.cutRebase(pane));

  // center and radius

  MCoord len=p.dx;
  MCoord radius=len/2;

  MPoint center=p.getCenter();

  VColor gray=+cfg.gray;

  // body

  VColor top=+cfg.snow;

  art.ball(center,radius,YField(p.y,top,p.ey,gray));

  // face

  VColor fc=+cfg.face;

  MCoord a=radius/2;
  MCoord w=radius/3;

  art.path(w,fc,center.subX(a),center.addX(a));
  art.path(w,fc,center.subY(a),center.addY(a));
 }

void DrawOut::drawMinus(const Config &cfg,Coord len_)
 {
  MPane p(Pane(base,len_));

  if( !p ) return;

  SmoothDrawArt art(buf.cutRebase(pane));

  // center and radius

  MCoord len=p.dx;
  MCoord radius=len/2;

  MPoint center=p.getCenter();

  VColor gray=+cfg.gray;

  // body

  VColor top=+cfg.snow;

  art.ball(center,radius,YField(p.y,top,p.ey,gray));

  // face

  VColor fc=+cfg.face;

  MCoord a=radius/2;
  MCoord w=radius/3;

  art.path(w,fc,center.subX(a),center.addX(a));
 }

Coord DrawOut::Sum(PtrLen<const Coord> tdx,Coord space,ulen i,ulen k)
 {
  Coord ret=0;

  for(; i<k ;i++) ret+=tdx[i]+space;

  return ret;
 }

template <class F1,class F2,class F3>
void DrawOut::DrawLine(F1 path,MPoint A,PtrLen<const Coord> tdx,Coord space,Coord maxlen,F2 skip,F3 add)
 {
  for(ulen i=0; i<tdx.len ;i++)
    {
     if( skip(i) )
       {
        if( i>0 )
          {
           MPoint B=add(A, Sum(tdx,space,0,i) );

           path(A,B);

           A=B;
          }

        while( i<tdx.len )
          {
           ulen k=i+1;

           for(; k<tdx.len && skip(k) ;k++);

           if( k<tdx.len )
             {
              A=add(A, Sum(tdx,space,i,k) );

              i=k;

              for(k=i+1; k<tdx.len && !skip(k) ;k++);

              MPoint B=add(A, Sum(tdx,space,i,k) );

              i=k;

              path(A,B);

              A=B;
             }
           else
             {
              return;
             }
          }

        return;
       }
    }

  path(A,add(A,maxlen));
 }

void DrawOut::table(TableDesc desc,VColor line,MCoord width)
 {
  auto span=desc.span;

  SmoothDrawArt art(buf.cutRebase(pane));

  auto path = [&art,line,width] (MPoint A,MPoint B) { art.path(width,line,A,B); } ;

  // 1

  MPoint A=base;
  MPoint S=Point::Diag(desc.space);

  A+=S/2;

  // 2

  Coord dy=0;

  for(Coord y : desc.tdy ) dy+=y+desc.space;

  // 3

  Coord dx=0;

  for(Coord x : desc.tdx ) dx+=x+desc.space;

  // 4

  {
   auto add = [] (MPoint A,Coord delta) { return A.addY(MPoint::LShift(delta)); } ;

   MPoint P=A;

   for(ulen i : IndLim(desc.tdx.len) )
     {
      auto skip = [i,span] (ulen j) { return span(i,j).left; } ;

      DrawLine(path,P,desc.tdy,desc.space,dy,skip,add);

      Coord x=desc.tdx[i];

      P=P.addX(MPoint::LShift(x+desc.space));
     }

   path(P,add(P,dy));
  }

  // 5

  {
   auto add = [] (MPoint A,Coord delta) { return A.addX(MPoint::LShift(delta)); } ;

   MPoint P=A;

   for(ulen j : IndLim(desc.tdy.len) )
     {
      auto skip = [j,span] (ulen i) { return span(i,j).top; } ;

      DrawLine(path,P,desc.tdx,desc.space,dx,skip,add);

      Coord y=desc.tdy[j];

      P=P.addY(MPoint::LShift(y+desc.space));
     }

   path(P,add(P,dx));
  }
 }

/* class Draw */

 // GetAnyBack()

VColor Draw::GetBack(const Book::TypeDef::Format *fmt)
 {
  if( fmt ) return CastColor(fmt->back);

  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::Text *obj)
 {
  if( obj ) return GetBack(obj->fmt.getPtr());

  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::FixedText *obj)
 {
  if( obj ) return GetBack(obj->fmt.getPtr());

  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::Bitmap *)
 {
  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::TextList *)
 {
  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::Collapse *)
 {
  return Book::NoColor;
 }

VColor Draw::GetBack(const Book::TypeDef::Table *)
 {
  return Book::NoColor;
 }

template <class T>
VColor Draw::GetAnyBack(T body)
 {
  VColor ret=Book::NoColor;

  body.apply( [&] (auto *obj) { ret=GetBack(obj); } );

  return ret;
 }

 // drawAnyLine()

void Draw::drawLine(const Book::TypeDef::SingleLine *obj,Pane pane,DrawBuf buf)
 {
  if( !obj ) return;

  MPane p(pane);

  if( !p ) return;

  VColor line=Combine(obj->line,+cfg.line);

  MCoord width=Cast(obj->width)*(+cfg.width);

  SmoothDrawArt art(buf);

  FigureBox fig(p);

  fig.loop(art,width,line);
 }

void Draw::drawLine(const Book::TypeDef::DoubleLine *obj,Pane pane,DrawBuf buf)
 {
  if( !obj ) return;

  MPane p(pane);

  if( !p ) return;

  VColor gray=Combine(obj->gray,+cfg.gray);
  VColor snow=Combine(obj->snow,+cfg.snow);

  MCoord width=Cast(obj->width)*(+cfg.width);

  SmoothDrawArt art(buf);

  FigureBox fig(p);

  fig.loop(art,HalfPos,width,gray);
  fig.loop(art,HalfNeg,width,snow);
 }

template <class T>
void Draw::drawAnyLine(T line,Pane pane,DrawBuf buf)
 {
  line.apply( [&] (auto *obj) { drawLine(obj,pane,buf); } );
 }

 // common

auto Draw::use(const Book::TypeDef::Format *fmt) -> Format
 {
  Format ret;

  if( fmt )
    {
     ret.font=map(fmt->font,+cfg.font);

     ret.fore=Combine(fmt->fore,fore);

     ret.effect=fmt->effect;
    }
  else
    {
     ret.font=+cfg.font;

     ret.fore=fore;

     ret.effect=Book::NoEffect;
    }

  ret.back=Book::NoColor;

  return ret;
 }

auto Draw::useFixed(const Book::TypeDef::Format *fmt) -> Format
 {
  Format ret;

  if( fmt )
    {
     ret.font=map(fmt->font,+cfg.codefont);

     ret.fore=Combine(fmt->fore,fore);

     ret.effect=fmt->effect;
    }
  else
    {
     ret.font=+cfg.codefont;

     ret.fore=fore;

     ret.effect=Book::NoEffect;
    }

  ret.back=Book::NoColor;

  return ret;
 }

auto Draw::useBack(const Book::TypeDef::Format *fmt) -> Format
 {
  Format ret;

  if( fmt )
    {
     ret.font=map(fmt->font,+cfg.font);

     ret.back=CastColor(fmt->back);
     ret.fore=Combine(fmt->fore,fore);

     ret.effect=fmt->effect;
    }
  else
    {
     ret.font=+cfg.font;

     ret.back=Book::NoColor;
     ret.fore=fore;

     ret.effect=Book::NoEffect;
    }

  return ret;
 }

auto Draw::over(Format format,const Book::TypeDef::Format *fmt) -> Format
 {
  if( fmt )
    {
     Format ret;

     ret.font=map(fmt->font,format.font);

     ret.back=Combine(fmt->back,format.back);
     ret.fore=Combine(fmt->fore,format.fore);

     ret.effect=fmt->effect;

     return ret;
    }

  return format;
 }

Point Draw::drawSpan(Format format,StrLen text,DrawOut out)
 {
  TextSize ts=format.font->text(text);

  if( format.back!=Book::NoColor ) out.back(ts,format.back);

  if( format.effect ) out.effect(ts,format.effect,format.fore,+cfg.width);

  out.text(format.font,text,format.fore);

  return out.base.addX(ts.dx);
 }

Point Draw::drawSpace(Format format,DrawOut out)
 {
  return drawSpan(format," "_c,out);
 }

 // draw(Book::TypeDef::Text *)

Point Draw::drawSpan(Format format,Book::TypeDef::Span span,DrawOut out)
 {
  return drawSpan(over(format,span.fmt),span.body,out);
 }

Point Draw::drawSpan(const Book::TypeDef::Format *prev_fmt,Format format,Book::TypeDef::Span span,DrawOut out)
 {
  Format span_format=over(format,span.fmt);

  if( InsSpace(span.body) )
    {
     if( prev_fmt==span.fmt )
       {
        out.base=drawSpace(span_format,out);
       }
     else
       {
        out.base=drawSpace(format,out);
       }
    }

  return drawSpan(span_format,span.body,out);
 }

void Draw::drawLine(Format format,PtrLen<const Book::TypeDef::Span> line,DrawOut out)
 {
  if( +line )
    {
     out.base=drawSpan(format,*line,out);

     const Book::TypeDef::Format *fmt=line->fmt;

     for(++line; +line ;++line)
       {
        out.base=drawSpan(fmt,format,*line,out);

        fmt=line->fmt;
       }
    }
 }

void Draw::draw(Format format,PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::OneLine *placement,FrameExt_OneLine *ext,DrawOut out)
 {
  if( !placement ) return;

  FontSize fs=format.font->getSize();

  drawLine(format,range,out.add(ext->offx,fs.by));
 }

void Draw::draw(Format format,PtrLen<const Book::TypeDef::Span> range,const Book::TypeDef::MultiLine *placement,FrameExt_MultiLine *ext,DrawOut out)
 {
  if( !placement ) return;

  FontSize fs=format.font->getSize();

  out.base.y+=fs.by;

  Coord first_dx=ext->first_dx;
  Coord dy=ext->dy;

  PtrLen<ulen> split=Range(ext->split);

  ulen off=0;

  if( +split )
    {
     {
      ulen len=*split;

      auto part=range.safe_part(off,len);

      off+=len;

      drawLine(format,part,out.addX(first_dx));

      out.base.y+=dy;
     }

     for(ulen len : split.part(1) )
       {
        auto part=range.safe_part(off,len);

        off+=len;

        drawLine(format,part,out);

        out.base.y+=dy;
       }
    }
 }

void Draw::draw(Book::TypeDef::Text *obj,FrameExt *ext,DrawOut out)
 {
  if( !obj ) return;

  Format format=use(obj->fmt);

  auto range=obj->list.getRange();

  obj->placement.getPtr().apply( [&] (auto *placement) { draw(format,range,placement,AutoCast(ext),out); } );
 }

 // draw(Book::TypeDef::FixedText *)

void Draw::drawFixedLine(Format format,PtrLen<const Book::TypeDef::Span> line,DrawOut out)
 {
  for(Book::TypeDef::Span span : line )
    {
     out.base=drawSpan(over(format,span.fmt),span.body,out);
    }
 }

void Draw::draw(Book::TypeDef::FixedText *obj,FrameExt *,DrawOut out)
 {
  if( !obj ) return;

  Format format=useFixed(obj->fmt);

  FontSize fs=format.font->getSize();

  out.base.y+=fs.by;

  Coord dy=fs.dy;

  for(Book::TypeDef::Line line : obj->list.getRange() )
    {
     drawFixedLine(format,line.getRange(),out);

     out.base.y+=dy;
    }
 }

 // draw(Book::TypeDef::Bitmap *)

void Draw::draw(Book::TypeDef::Bitmap *obj,FrameExt *,DrawOut out)
 {
  out.bitmap(map(obj));
 }

 // draw(Book::TypeDef::TextList *)

void Draw::drawBullet(Format format,StrLen text,Coord bullet_len,DrawOut out)
 {
  TextSize ts=format.font->text(text);

  out.base.x+=bullet_len-ts.dx;

  if( format.back!=Book::NoColor ) out.back(ts,format.back);

  if( format.effect ) out.effect(ts,format.effect,format.fore,+cfg.width);

  out.text(format.font,text,format.fore);
 }

Coord Draw::drawItem(Format format,Book::TypeDef::ListItem item,ListItemSize item_size,Coord bullet_len,Coord bullet_space,DrawOut out)
 {
  drawBullet(format,item.bullet,bullet_len,out.addY(item_size.by1));

  Point ebase=(*this)(item.list,out.add(bullet_len+bullet_space,item_size.by2));

  return Max_cast(item_size.dy1,ebase.y-out.base.y);
 }

void Draw::draw(Book::TypeDef::TextList *obj,FrameExt_TextList *ext,DrawOut out)
 {
  if( !obj ) return;

  Coord bullet_len=ext->bullet_len;
  Coord bullet_space=ext->bullet_space;
  Coord item_space=ext->item_space;

  ListItemSize *size_list=ext->size_list.getPtr();

  Format format=useBack(obj->bullet_fmt);

  auto list=obj->list.getRange();

  for(ulen i=0; i<list.len ;i++)
    {
     Coord dy=drawItem(format,list[i],size_list[i],bullet_len,bullet_space,out);

     out.base.y+=(dy+item_space);
    }
 }

 // draw(Book::TypeDef::Collapse *)

void Draw::draw(Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext,DrawOut out)
 {
  if( !obj ) return;

  Coord len=ext->len;
  Coord elen=BoxExt(len);

  Format format=useBack(obj->collapse_fmt);

  if( obj->open )
    {
     out.drawMinus(cfg,len);

     if( !obj->hide )
       {
        Coord by=format.font->getSize().by;

        drawSpan(format,obj->title,out.add(elen,by));
       }

     (*this)(obj->list,out.addY(elen));
    }
  else
    {
     out.drawPlus(cfg,len);

     Coord by=format.font->getSize().by;

     drawSpan(format,obj->title,out.add(elen,by));
    }
 }

 // draw(Book::TypeDef::Table *)

void Draw::draw(Book::TypeDef::Table *obj,FrameExt_Table *ext,DrawOut out)
 {
  if( !obj ) return;

  TableDesc desc=ext->getDesc();

  if( auto *border=obj->border.getPtr() ; border && border->space>0 )
    {
     VColor line=Combine(border->line,+cfg.line);

     if( line!=Book::NoColor )
       {
        MCoord width=Cast(border->width)*(+cfg.width);

        out.table(desc,line,width);
       }
    }

  ForTable(obj, [&] (ulen i,ulen j,Book::TypeDef::Cell *cell)
                    {
                     (*this)(cell->list,out.add(desc.span(i,j).base));

                    } );
 }

 // drawAny()

template <class T>
void Draw::drawAny(T body,FrameExt *ext,DrawOut out)
 {
  body.apply( [&] (auto *obj) { draw(obj,AutoCast(ext),out); } );
 }

 // frame

Point Draw::operator () (Book::TypeDef::Frame *frame,DrawOut out)
 {
  Coord dy=(*this)(frame,out.buf,out.fullBase());

  return out.base.addY(dy);
 }

Point Draw::operator () (PtrLen<Book::TypeDef::Frame> list,DrawOut out)
 {
  if( +list )
    {
     FrameExt *ext=map(list.ptr);

     PtrLen<const Coord> downs=Range(ext->downs);

     Point ret=out.base.addY(downs[list.len-1]);

     Pane clip=out.buf.getClip();

     Point base=out.fullBase();

     SelectFrames select(downs,base.y,clip.y,clip.dy);

     if( select.ind<select.lim )
       {
        if( select.ind ) out.base.y+=downs[select.ind-1];

        for(ulen i : IndLim(select.ind,select.lim) )
          {
           Book::TypeDef::Frame &frame=list[i];

           out.base=(*this)(&frame,out);
          }
       }

     return ret;
    }

#if 0

  for(Book::TypeDef::Frame &frame : list )
    {
     out.base=(*this)(&frame,out);
    }

#endif

  return out.base;
 }

 // public

Coord Draw::operator () (Book::TypeDef::Frame *frame,DrawBuf buf,Point base)
 {
  FrameExt *ext=map(frame);

  Pane pane(base,ext->size);

  Pane inner=pane.shrink(ext->outer);

  if( VColor col=CastColor(frame->col) ; col!=Book::NoColor )
    {
     PaneSub sub(pane,inner);

     buf.erase(sub.top,col);
     buf.erase(sub.bottom,col);
     buf.erase(sub.left,col);
     buf.erase(sub.right,col);
    }

  if( VColor back=GetAnyBack(frame->body.getPtr()) ; back!=Book::NoColor )
    {
     buf.erase(inner,back);
    }

  drawAnyLine(frame->line.getPtr(),inner,buf);

  drawAny(frame->body.getPtr(),ext,{buf.cut(inner),inner,ext->inner});

  return ext->size.y;
 }

/* class GotoBase */

void GotoBase::frameDown(PtrLen<Book::TypeDef::Frame> list,ulen index)
 {
  if( !index ) return;

  FrameExt *ext=map(list.ptr);

  down+=ext->downs[index-1];
 }

void GotoBase::frameDown(PtrLen<Book::TypeDef::Frame> list)
 {
  if( !list ) return;

  FrameExt *ext=map(list.ptr);

  down+=ext->downs[list.len-1];
 }

void GotoBase::border(FrameExt *ext)
 {
  down+=ext->outer.y+ext->inner.y;
 }

Book::TypeDef::Frame * GotoBase::step(ulen item_index,ulen frame_index,Book::TypeDef::TextList *obj,FrameExt_TextList *ext)
 {
  if( !obj ) return 0;

  auto items=obj->list.getRange();

  if( item_index>=items.len ) return 0;

  Book::TypeDef::ListItem item=items[item_index];

  auto frames=item.list.getRange();

  if( frame_index>=frames.len ) return 0;

  ListItemSize *size_list=ext->size_list.getPtr();

  if( item_index ) down+=size_list[item_index-1].down+ext->item_space;

  down+=size_list[item_index].by2;

  frameDown(frames,frame_index);

  return &frames[frame_index];
 }

Book::TypeDef::Frame * GotoBase::step(ulen index,Book::TypeDef::Collapse *obj,FrameExt_Collapse *ext)
 {
  if( !obj || !obj->open ) return 0;

  auto list=obj->list.getRange();

  if( index>=list.len ) return 0;

  down+=BoxExt(ext->len);

  frameDown(list,index);

  return &list[index];
 }

Book::TypeDef::Frame * GotoBase::step(ulen col,ulen row,ulen index,Book::TypeDef::Table *obj,FrameExt_Table *ext)
 {
  if( !obj ) return 0;

  auto rows=obj->rows.getRange();

  if( row>=rows.len ) return 0;

  auto line=rows[row].getRange();

  if( col>=line.len ) return 0;

  auto *cell=line[col].getPtr();

  if( !cell ) return 0;

  auto list=cell->list.getRange();

  if( index>=list.len ) return 0;

  TableDesc desc=ext->getDesc();

  down+=desc.span(col,row).base.y;

  frameDown(list,index);

  return &list[index];
 }

/* class OpenBase */

Book::TypeDef::Frame * OpenBase::step(ulen item_index,ulen frame_index,Book::TypeDef::TextList *obj)
 {
  if( !obj ) return 0;

  auto items=obj->list.getRange();

  if( item_index>=items.len ) return 0;

  Book::TypeDef::ListItem item=items[item_index];

  auto frames=item.list.getRange();

  if( frame_index>=frames.len ) return 0;

  return &frames[frame_index];
 }

Book::TypeDef::Frame * OpenBase::step(ulen index,Book::TypeDef::Collapse *obj)
 {
  if( !obj ) return 0;

  auto list=obj->list.getRange();

  if( index>=list.len ) return 0;

  if( !obj->open )
    {
     obj->open=true;

     flag=true;
    }

  return &list[index];
 }

Book::TypeDef::Frame * OpenBase::step(ulen col,ulen row,ulen index,Book::TypeDef::Table *obj)
 {
  if( !obj ) return 0;

  auto rows=obj->rows.getRange();

  if( row>=rows.len ) return 0;

  auto line=rows[row].getRange();

  if( col>=line.len ) return 0;

  auto *cell=line[col].getPtr();

  if( !cell ) return 0;

  auto list=cell->list.getRange();

  if( index>=list.len ) return 0;

  return &list[index];
 }

/* class Shape */

void Shape::prepare(const Config &cfg,ExtMap &map,Ratio scale,ulen frame_index,Coord wdx)
 {
  Prepare ctx(cfg,map,scale,refs);

  size=ctx(frame,frame_index,wdx,Null);
 }

void Shape::draw(const Config &cfg,ExtMap &map,VColor fore,DrawBuf buf,Point base) const
 {
  Draw ctx(cfg,map,fore);

  ctx(frame,buf,base);
 }

bool Shape::hit(Point point) const
 {
  return point>=Null && point<size ;
 }

RefList Shape::getRef(Point point) const
 {
  const RefPane *ptr=refs.getPtr();

  RefList ret;

  tree.find(point.y, [ptr,point,&ret] (ulen index)
                                      {
                                       auto &obj=ptr[index];

                                       if( obj.pane.contains(point) )
                                        {
                                         ret=obj;

                                         return false;
                                        }

                                       return true;

                                      } );

  return ret;
 }

Point Shape::set(const Config &cfg,ExtMap &map,Ratio scale,Book::TypeDef::Frame &frame_,ulen frame_index,Coord wdx,Coord down_)
 {
  frame=&frame_;
  down=down_;

  refs.erase();
  tree={};

  prepare(cfg,map,scale,frame_index,wdx);

  struct Span
   {
    Coord a;
    Coord b;

    explicit Span(const RefPane &ref)
     {
      Coord y=ref.pane.y;
      Coord dy=ref.pane.dy;

      a=y;
      b=y+dy;
     }
   };

  tree=IntervalTree<Coord>(Range(refs), [] (const RefPane &ref) { return Span(ref); } );

  return size;
 }

void Shape::draw(const Config &cfg,ExtMap &map,VColor fore,DrawBuf buf,Coord pos_x,Coord pos_y) const
 {
  draw(cfg,map,fore,buf,Point(pos_x,pos_y));
 }

bool Shape::hit(Point point,Coord pos_x,Coord pos_y) const
 {
  return hit(point-Point(pos_x,pos_y));
 }

RefList Shape::getRef(Point point,Coord pos_x,Coord pos_y) const
 {
  return getRef(point-Point(pos_x,pos_y));
 }

} // namespace DrawBook
} // namespace App

