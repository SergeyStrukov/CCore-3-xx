/* TextEditor.cpp */
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

#include <inc/TextEditor.h>

#include <CCore/inc/CharUtils.h>
#include <CCore/inc/SymCount.h>
#include <CCore/inc/SymPart.h>

#include <CCore/inc/video/LayoutCombo.h>
#include <CCore/inc/video/FigureLib.h>
#include <CCore/inc/video/PrintDDL.h>

#include <CCore/inc/algon/EuclidRotate.h>

#include <CCore/inc/Exception.h>

namespace App {

/* InsAt() */

template <class A>
auto InsAt(A &array,ulen ind,ulen count)
 {
  ulen len=array.getLen();

  if( ind<len )
    {
     array.extend_default(count);

     auto r=Range(array).part(ind);

     Algon::EuclidRotate_suffix(r,count);

     return r.prefix(count);
    }
  else
    {
     return array.extend_default(count);
    }
 }

/* DelRange() */

template <class A>
void DelRange(A &array,ulen ind,ulen lim)
 {
  ulen len=array.getLen();

  Replace_min(lim,len);

  if( ind>=lim ) return;

  ulen delta=lim-ind;

  if( ulen count=len-lim )
    {
     auto *base=array.getPtr();

     for(ulen i : IndLim(ind,ind+count) ) Swap(base[i],base[i+delta]);
    }

  array.shrink(delta);
 }

/* DelPrefix() */

template <class A>
void DelPrefix(A &array,ulen delta)
 {
  DelRange(array,0,delta);
 }

/* class TextBuf */

void TextBuf::GuardNoObject()
 {
  Printf(Exception,"App::TextBuf::guard() : no pad");
 }

TextBuf::TextBuf()
 {
 }

TextBuf::~TextBuf()
 {
 }

BookLab::TextLine * TextBuf::insLine(ulen index)
 {
  guard();

  return ArraySwapIns_guarded(*pad,index);
 }

PtrLen<BookLab::TextLine> TextBuf::insLines(ulen index,ulen count)
 {
  guard();

  return InsAt(*pad,index,count);
 }

void TextBuf::delLine(ulen index)
 {
  guard();

  ArraySwapDel_guarded(*pad,index);
 }

void TextBuf::delRange(ulen ind,ulen lim)
 {
  guard();

  DelRange(*pad,ind,lim);
 }

void TextBuf::blank()
 {
  pad=0;
 }

void TextBuf::load(DynArray<BookLab::TextLine> *pad_)
 {
  pad=pad_;
 }

void TextBuf::save() const
 {
 }

/* class TextWindow */

void TextWindow::SizeData::prepare(const Font &font)
 {
  fs=font->getSize();

  space_dx=font->text(" "_c).dx;

  text_dx=0;
 }

void TextWindow::SizeData::update(const Font &font,BookLab::TextLine &line)
 {
  Replace_max(text_dx,Cache(font,line,space_dx));
 }

void TextWindow::SizeData::update(const Font &font,BookLab::TextLine &line,ulen spanind,PtrLen<const Char> curspan)
 {
  Replace_max(text_dx,Cache(font,line,space_dx,spanind,curspan));
 }

void TextWindow::SizeData::update(BookLab::TextLine &line)
 {
  Replace_max(text_dx,Cache(line,space_dx));
 }

Coord TextWindow::Cache(const Font &font,BookLab::Span &span)
 {
  Coord ret=font->text(Range(span.body)).dx;

  span.dx=ret;

  return ret;
 }

Coord TextWindow::Cache(const Font &font,PtrLen<const Char> curspan)
 {
  return font->text(curspan).dx;
 }

Coord TextWindow::Cache(const Font &font,BookLab::TextLine &line,Coord space_dx)
 {
  if( ulen count=line.list.getLen() )
    {
     Coord dx=MulSize(count-1,space_dx);

     for(BookLab::Span &span : line.list )
       {
        dx=AddSize(dx,Cache(font,span));
       }

     line.dx=dx;

     return dx;
    }
  else
    {
     line.dx=0;

     return 0;
    }
 }

Coord TextWindow::Cache(const Font &font,BookLab::TextLine &line,Coord space_dx,ulen spanind,PtrLen<const Char> curspan)
 {
  if( ulen count=line.list.getLen() )
    {
     Coord dx=MulSize(count-1,space_dx);

     for(ulen ind : IndLim(count) )
       if( ind==spanind )
         {
          dx=AddSize(dx,Cache(font,curspan));
         }
       else
         {
          dx=AddSize(dx,Cache(font,line.list[ind]));
         }

     line.dx=dx;

     return dx;
    }
  else
    {
     line.dx=0;

     return 0;
    }
 }

Coord TextWindow::Cache(BookLab::TextLine &line,Coord space_dx)
 {
  if( ulen count=line.list.getLen() )
    {
     Coord dx=MulSize(count-1,space_dx);

     for(BookLab::Span &span : line.list )
       {
        dx=AddSize(dx,span.dx);
       }

     line.dx=dx;

     return dx;
    }
  else
    {
     line.dx=0;

     return 0;
    }
 }

void TextWindow::addSXPos(ulen delta)
 {
  sx.add(delta);

  scroll_x.assert(sx.pos);

  redraw();
 }

void TextWindow::subSXPos(ulen delta)
 {
  sx.sub(delta);

  scroll_x.assert(sx.pos);

  redraw();
 }

void TextWindow::addSYPos(ulen delta)
 {
  sy.add(delta);

  scroll_y.assert(sy.pos);

  redraw();
 }

void TextWindow::subSYPos(ulen delta)
 {
  sy.sub(delta);

  scroll_y.assert(sy.pos);

  redraw();
 }

void TextWindow::clean()
 {
  block_cache=false;
  ok=false;

  sx.beg();
  sy.beg();

  cursor={};

  selection_on=false;

  spanlen=0;
 }

[[nodiscard]] bool TextWindow::cache() const
 {
  if( block_cache )
    {
     return false;
    }

  try
    {
     if( !ok )
       {
        const Font &font=cfg.font.get();

        data.prepare(font);

        ulen count=text.getLineCount();

        for(ulen i : IndLim(count) )
          {
           if( i==cursor.y )
             data.update(font,text.getLine(i),cursor.span,getCurSpan());
           else
             data.update(font,text.getLine(i));
          }

        ok=true;
       }

     return true;
    }
  catch(...)
    {
     block_cache=true;

     return false;
    }
 }

void TextWindow::posSX(ulen pos)
 {
  sx.setPos(pos);

  redraw();
 }

void TextWindow::posSY(ulen pos)
 {
  sy.setPos(pos);

  redraw();
 }

void TextWindow::updated(unsigned flags)
 {
  if( flags&LayoutUpdate ) ok=false;
 }

void TextWindow::tick()
 {
  if( tick_count )
    {
     tick_count--;
    }
  else
    {
     tick_count=PosSub(+cfg.period,1u);

     cursor_on=!cursor_on;

     redraw();
    }
 }

void TextWindow::tickStart()
 {
  cursor_on=true;

  defer_tick.start();
 }

void TextWindow::tickStop()
 {
  cursor_on=false;

  defer_tick.stop();
 }

template <class Func>
bool TextWindow::applyToSpan(Func func)
 {
  if( cursor.y<text.getLineCount() )
    {
     BookLab::TextLine &line=text.getLine(cursor.y);

     if( cursor.span<line.list.getLen() )
       {
        func(line.list[cursor.span]);

        return true;
       }
    }

  return false;
 }

template <class Func>
bool TextWindow::applyToSpan(Func func) const
 {
  if( cursor.y<text.getLineCount() )
    {
     BookLab::TextLine &line=text.getLine(cursor.y);

     if( cursor.span<line.list.getLen() )
       {
        func(line.list[cursor.span]);

        return true;
       }
    }

  return false;
 }

void TextWindow::fill(StrLen str)
 {
  FillCharBuf result(Range(spanbuf),str);

  if( result.overflow )
    {
     Printf(Exception,"App::TextWindow::fill() : overflow, too long span");
    }
  else
    {
     spanlen=result.len;
    }
 }

ulen TextWindow::extend(StrLen str)
 {
  FillCharBuf result(Range(spanbuf).part(spanlen),str);

  if( result.overflow )
    {
     Printf(Exception,"App::TextWindow::extend() : overflow, too long span");
    }
  else
    {
     spanlen+=result.len;
    }

  return result.len;
 }

void TextWindow::insert(StrLen str)
 {
  ulen off=Min(cursor.x,spanlen);
  ulen delta=extend(str);

  auto r=Range(spanbuf.getPtr(),spanlen).part(off);

  Algon::EuclidRotate_suffix(r,delta);

  cursor.x=off+delta;
 }

void TextWindow::cleanNames()
 {
  showFormat.assert(Null,false);
  showLink.assert(Null,false);
 }

void TextWindow::fill()
 {
  spanlen=0;

  if( !applyToSpan( [&] (BookLab::Span &span)
                  {
                   fill(Range(span.body));

                   showFormat.assert(span.format.name,span.format.notResolved());
                   showLink.assert(span.ref.name,span.ref.notResolved());

                  } ) )
    {
     cleanNames();
    }
 }

void TextWindow::setSXPos(ulen x)
 {
  sx.setPos(x);

  scroll_x.assert(sx.pos);

  redraw();
 }

void TextWindow::setSYPos(ulen y)
 {
  sy.setPos(y);

  scroll_y.assert(sy.pos);

  redraw();
 }

void TextWindow::setSXYPos(ulen x,ulen y)
 {
  sx.setPos(x);
  sy.setPos(y);

  scroll_x.assert(sx.pos);
  scroll_y.assert(sy.pos);

  redraw();
 }

ulen TextWindow::getSpanCount() const
 {
  if( cursor.y>=text.getLineCount() ) return 0;

  BookLab::TextLine &line=text.getLine(cursor.y);

  return line.list.getLen();
 }

struct TextWindow::Split
 {
  PtrLen<const Char> str1;
  PtrLen<const Char> str2;

  Split(PtrLen<const Char> str,ulen pos)
   {
    ulen split=Min(pos,str.len);

    str1=str.prefix(split);
    str2=str.part(split);
   }
 };

void TextWindow::changeSpan(ulen span)
 {
  applyToSpan( [&] (BookLab::Span &span)
                   {
                    span.body=String(getCurSpan());

                    if( ok )
                      {
                       const Font &font=cfg.font.get();

                       Cache(font,span);
                      }

                   } );

  cursor.span=span;

  fill();
 }

void TextWindow::showCursor()
 {
  if( cursor.y<sy.pos )
    {
     setSYPos(cursor.y);
    }
  else if( cursor.y-sy.pos>=sy.page )
    {
     setSYPos(cursor.y-sy.page+1);
    }

  if( !cache() ) return;

  const Font &font=cfg.font.get();

  Coord x=data.fs.dx0;

  if( cursor.y<text.getLineCount() )
    {
     BookLab::TextLine &line=text.getLine(cursor.y);

     for(ulen j : IndLim(line.list.getLen()) )
       if( j==cursor.span )
         {
          Split split(getCurSpan(),cursor.x);

          x+=font->text(split.str1).dx;

          break;
         }
       else
         {
          BookLab::Span &span=line.list[j];

          x+=span.dx+data.space_dx;
         }
    }

  ulen X=(ulen)x;

  if( X<sx.pos )
    {
     setSXPos(X);
    }
  else
    {
     X-=sx.pos;

     Coord dxc=+cfg.cursor_dx;

     X+=ulen(3*dxc+data.fs.dx1+data.space_dx);

     if( X>sx.page ) addSXPos(X-sx.page);
    }
 }

void TextWindow::keySelect(bool on)
 {
  if( selection_on )
    {
     if( !on )
       {
        selection_on=false;
       }
    }
  else
    {
     if( on )
       {
        selection_on=true;
        selection=cursor;
       }
    }
 }

void TextWindow::moveLeft(ulen delta)
 {
  if( delta==0 || ( cursor.span==0 && cursor.x==0 ) ) return;

  while( delta )
    {
     if( cursor.x>=delta )
       {
        cursor.x-=delta;
        delta=0;
       }
     else
       {
        if( cursor.span )
          {
           delta-=cursor.x+1;

           changeSpan(cursor.span-1);

           cursor.x=spanlen;
          }
        else
          {
           cursor.x=0;
           delta=0;
          }
       }
    }

  showCursor();

  redraw();
 }

bool TextWindow::moveRight(ulen delta)
 {
  if( delta==0 ) return false;

  ulen count=getSpanCount();

  if( count==0 || ( cursor.span==count-1 && cursor.x==spanlen ) ) return false;

  while( delta )
    {
     ulen len=PosSub(spanlen,cursor.x);

     if( delta<=len )
       {
        cursor.x+=delta;
        delta=0;
       }
     else
       {
        if( cursor.span<count-1 )
          {
           delta-=len+1;

           changeSpan(cursor.span+1);

           cursor.x=0;
          }
        else
          {
           cursor.x=spanlen;
           delta=0;
          }
       }
    }

  showCursor();

  redraw();

  return true;
 }

void TextWindow::moveHome()
 {
  if( cursor.span )
    {
     changeSpan(0);
    }
  else
    {
     if( cursor.x==0 ) return;
    }

  cursor.x=0;

  showCursor();

  redraw();
 }

void TextWindow::moveEnd()
 {
  ulen count=getSpanCount();

  if( count==0 ) return;

  if( cursor.span<count-1 )
    {
     changeSpan(count-1);
    }
  else
    {
     if( cursor.x==spanlen ) return;
    }

  cursor.x=spanlen;

  showCursor();

  redraw();
 }

void TextWindow::moveTab()
 {
  ulen count=getSpanCount();

  if( count==0 || cursor.span>=count-1 )
    {
     cursor.x=spanlen;
    }
  else
    {
     changeSpan(cursor.span+1);

     cursor.x=0;
    }

  showCursor();

  redraw();
 }

ulen TextWindow::getPosX() const
 {
  if( cursor.y<text.getLineCount() )
    {
     BookLab::TextLine &line=text.getLine(cursor.y);

     ulen ind=cursor.span;

     if( ind>=line.list.getLen() ) return 0;

     ulen len=0;

     while( ind-- )
       {
        len+=1+SymLen(Range(line.list[ind].body));
       }

     return cursor.x+len;
    }
  else
    {
     return 0;
    }
 }

void TextWindow::flushDX()
 {
  ulen count=text.getLineCount();

  if( cursor.y<count )
    {
     BookLab::TextLine &line=text.getLine(cursor.y);

     if( cursor.span<line.list.getLen() )
       {
        BookLab::Span &span=line.list[cursor.span];

        span.body=String(getCurSpan());

        if( ok )
          {
           const Font &font=cfg.font.get();

           Cache(font,span);

           Cache(line,data.space_dx);
          }
       }
    }
 }

void TextWindow::setPos(ulen x,ulen y)
 {
  flushDX();

  cursor.y=y;
  cursor.span=0;
  cursor.x=0;

  fill();

  if( moveRight(x) ) return;

  showCursor();

  redraw();
 }

void TextWindow::moveUp(ulen delta)
 {
  if( delta==0 || cursor.y==0 ) return;

  setPos(getPosX(),PosSub(cursor.y,delta));
 }

void TextWindow::moveDown(ulen delta)
 {
  if( delta==0 ) return;

  ulen lim=text.getLineCount();

  if( lim==0 || cursor.y==lim-1 ) return;

  setPos(getPosX(),AddToCap(cursor.y,delta,lim-1));
 }

void TextWindow::moveTop()
 {
  moveUp(cursor.y);
 }

void TextWindow::moveBottom()
 {
  ulen lim=text.getLineCount();

  if( cursor.y<lim ) moveDown(lim-1-cursor.y);
 }

void TextWindow::startDrag(Point point)
 {
  if( Change(drag,true) )
    {
     captureMouse();

     if( mouse_pos )
       {
        startPosCursor(point);
       }
     else
       {
        startPosWindow(point);
       }
    }
 }

void TextWindow::dragTo(Point point)
 {
  if( mouse_pos )
    {
     posCursor(point);
    }
  else
    {
     posWindow(point);
    }
 }

void TextWindow::endDrag()
 {
  drag=false;

  releaseMouse();
 }

void TextWindow::endDrag(Point point)
 {
  endDrag();

  dragTo(point);
 }

Coord TextWindow::Div(Coord a,Coord b)
 {
  if( a>0 ) return a/b;

  return a/b-1;
 }

ulen TextWindow::DragPos(ulen pos,Coord from,Coord to,ulen cap)
 {
  if( to>from )
    return PosSub(pos,(ulen)to-(ulen)from) ;
  else
    return AddToCap(pos,(ulen)from-(ulen)to,cap);
 }

void TextWindow::startPosWindow(Point point)
 {
  drag_base=point;

  posx_base=sx.pos;
  posy_base=sy.pos;
 }

void TextWindow::posWindow(Point point)
 {
  Coord dxc=+cfg.cursor_dx;
  Coord div=data.fs.dy;

  setSXYPos(DragPos(posx_base,drag_base.x,point.x,sx.getMaxPos()),
            DragPos(posy_base,Div(drag_base.y-dxc,div),Div(point.y-dxc,div),sy.getMaxPos()));
 }

auto TextWindow::toCursor(Point point) -> Cursor
 {
  if( !cache() ) return {};

  ulen count=text.getLineCount();

  if( !count ) return {};

  Coord dxc=+cfg.cursor_dx;

  point=point.subXY(dxc);

  // y

  Coord py=Div(point.y,data.fs.dy);
  ulen y;

  if( py>0 )
    {
     y=AddMin<ulen>(sy.pos,(ulen)py,count-1);
    }
  else
    {
     y=Min<ulen>(PosSub(sy.pos,UIntNeg((ulen)py)),count-1);
    }

  // x

  ulen span=0;
  ulen x=0;

  BookLab::TextLine &line=text.getLine(y);

  const Font &font=cfg.font.get();

  if( ulen spancount=line.list.getLen() )
    {
     Coord px=Coord(sx.pos)+point.x;

     if( px<0 ) px=0;

     for(; span<spancount ;span++)
       {
        if( y==cursor.y && span==cursor.span )
          {
           Coord dxc=+cfg.cursor_dx;
           Coord dx=font->text(getCurSpan()).dx+dxc;

           if( px>=dx )
             {
              px-=dx;

              if( px>=data.space_dx )
                {
                 px-=data.space_dx;
                }
              else
                {
                 x=spanlen;

                 break;
                }
             }
           else
             {
              x=font->position(getCurSpan(),{px,0});

              x=Cap<ulen>(1,x,spanlen+1)-1;

              break;
             }
          }
        else
          {
           BookLab::Span &obj=line.list[span];

           if( px>=obj.dx )
             {
              px-=obj.dx;

              if( px>=data.space_dx )
                {
                 px-=data.space_dx;
                }
              else
                {
                 x=SymLen(Range(obj.body));

                 break;
                }
             }
           else
             {
              x=font->position(Range(obj.body),{px,0});

              x=Cap<ulen>(1,x,SymLen(Range(obj.body))+1)-1;

              break;
             }
          }
       }

     if( span==spancount )
       {
        span=spancount-1;

        if( y==cursor.y && span==cursor.span )
          {
           x=spanlen;
          }
        else
          {
           BookLab::Span &obj=line.list[span];

           x=SymLen(Range(obj.body));
          }
       }
    }

  return {y,span,x};
 }

void TextWindow::posCursor(Cursor cur)
 {
  if( cur.y!=cursor.y || cur.span!=cursor.span )
    {
     flushDX();

     cursor=cur;

     fill();
    }
  else
    {
     cursor=cur;
    }

  redraw();

  showCursor();
 }

void TextWindow::startPosCursor(Point point)
 {
  Cursor cur=toCursor(point);

  selection_on=true;
  selection=cur;

  posCursor(cur);
 }

void TextWindow::posCursor(Point point)
 {
  posCursor(toCursor(point));
 }

void TextWindow::makeNonEmpty()
 {
  if( !text.getLineCount() ) text.addLine();
 }

Coord TextWindow::updateCache(BookLab::TextLine &line)
 {
  ulen count=line.list.getLen();

  Coord dx=MulSize(count-1,data.space_dx);

  for(ulen i : IndLim(count) )
    {
     BookLab::Span &span=line.list[i];

     if( i==cursor.span )
       {
        const Font &font=cfg.font.get();

        TextSize ts=font->text(getCurSpan());

        span.dx=ts.dx;
       }

     dx=AddSize(dx,span.dx);
    }

  line.dx=dx;

  return dx;
 }

void TextWindow::updateData()
 {
  data.text_dx=0;

  ulen count=text.getLineCount();

  for(ulen i : IndLim(count) ) Replace_max(data.text_dx,text.getLine(i).dx);
 }

void TextWindow::updateData(BookLab::TextLine &line)
 {
  updateCache(line);

  updateData();
 }

void TextWindow::insSpanChar(BookLab::TextLine &line,Char ch)
 {
  if( spanlen<spanbuf.getLen() )
    {
     InsChar(spanbuf.getPtr(),spanlen,Min(cursor.x,spanlen),ch);

     spanlen++;
     cursor.x++;

     Replace_max(data.text_dx,updateCache(line));
    }
 }

void TextWindow::insChar(Char ch)
 {
  if( !SymCharIsPrintable(ch) ) return;

  if( selection_on ) delSel();

  makeNonEmpty();

  if( ulen count=text.getLineCount() )
    {
     if( cursor.y<count )
       {
        BookLab::TextLine &line=text.getLine(cursor.y);

        if( !line.list.getLen() )
          {
           line.list.append_default();

           cursor.span=0;
           cursor.x=0;

           spanlen=0;

           cleanNames();
          }

        insSpanChar(line,ch);
       }
    }

  changed.assert();

  showCursor();
 }

void TextWindow::delSpanChar(BookLab::TextLine &line)
 {
  DelCharRange(spanbuf.getPtr(),spanlen,cursor.x,1);

  spanlen--;

  updateData(line);

  changed.assert();

  showCursor();
 }

void TextWindow::joinLine()
 {
  ulen count=text.getLineCount();

  if( count<2 || cursor.y>=count-1 ) return;

  BookLab::TextLine &line1=text.getLine(cursor.y);
  BookLab::TextLine &line2=text.getLine(cursor.y+1);

  line1.list.extend_copy(Range(line2.list));

  text.delLine(cursor.y+1);

  Replace_max(data.text_dx,Cache(line1,data.space_dx));

  changed.assert();

  showCursor();
 }

void TextWindow::delEmptyLine(bool prev)
 {
  text.delLine(cursor.y);

  bool toend=false;

  ulen count=text.getLineCount();

  if( prev || cursor.y>=count )
    {
     if( cursor.y==0 )
       {
        cursor.span=0;
        cursor.x=0;
       }
     else
       {
        cursor.y--;

        BookLab::TextLine &line=text.getLine(cursor.y);

        if( ulen spancount=line.list.getLen() )
          {
           cursor.span=spancount-1;
           toend=true;
          }
        else
          {
           cursor.span=0;
           cursor.x=0;
          }
       }
    }
  else
    {
     cursor.span=0;
     cursor.x=0;
    }

  fill();

  if( toend ) cursor.x=spanlen;

  changed.assert();

  showCursor();
 }

void TextWindow::joinSpan(BookLab::TextLine &line,bool prev)
 {
  if( prev )
    {
     if( cursor.span )
       {
        changeSpan(cursor.span-1);

        cursor.x=spanlen;
       }
     else
       {
        if( cursor.y )
          {
           flushDX();

           cursor.y--;

           if( ulen count=text.getLine(cursor.y).list.getLen() )
             {
              cursor.span=count-1;

              fill();

              cursor.x=spanlen;

              joinLine();
             }
           else
             {
              cursor.span=0;
              cursor.x=0;

              delEmptyLine(false);
             }
          }

        return;
       }
    }

  ulen count=line.list.getLen();

  if( cursor.span<count-1 )
    {
     BookLab::Span &span2=line.list[cursor.span+1];

     extend(Range(span2.body));

     ArraySwapDel_guarded(line.list,cursor.span+1);

     updateData(line);

     changed.assert();

     showCursor();
    }
  else
    {
     flushDX();

     joinLine();
    }
 }

void TextWindow::delChar(bool prev)
 {
  selection_on=false;

  if( ulen count=text.getLineCount() )
    {
     if( cursor.y<count )
       {
        BookLab::TextLine &line=text.getLine(cursor.y);

        if( ulen spancount=line.list.getLen() )
          {
           if( cursor.span<spancount )
             {
              if( prev )
                {
                 if( cursor.x==0 )
                   {
                    joinSpan(line,true);

                    return;
                   }

                 cursor.x--;
                }

               if( cursor.x<spanlen )
                 {
                  delSpanChar(line);
                 }
               else
                 {
                  joinSpan(line,false);
                 }
             }
          }
        else
          {
           delEmptyLine(prev);
          }
       }
    }
 }

void TextWindow::splitSpan()
 {
  if( selection_on )
    {
     selection_on=false;

     redraw();
    }

  makeNonEmpty();

  if( ulen count=text.getLineCount() )
    {
     if( cursor.y<count )
       {
        BookLab::TextLine &line=text.getLine(cursor.y);

        if( ulen spancount=line.list.getLen() )
          {
           if( cursor.span>=spancount ) return;

           BookLab::Span *span=ArraySwapIns_guarded(line.list,cursor.span);

           Split split(getCurSpan(),cursor.x);

           span[0].body=String(split.str1);
           span[1].body=String(split.str2);

           span[0].format=span[1].format;
           span[0].ref=span[1].ref;

           cursor.span++;
           cursor.x=0;

           fill();

           const Font &font=cfg.font.get();

           Cache(font,span[0]);
           Cache(font,span[1]);

           data.update(line);
          }
        else
          {
           line.list.append_default();

           cursor.span=0;
           cursor.x=0;

           spanlen=0;

           cleanNames();
          }

        changed.assert();

        showCursor();
       }
    }
 }

void TextWindow::splitLine()
 {
  if( selection_on )
    {
     selection_on=false;

     redraw();
    }

  makeNonEmpty();

  if( ulen count=text.getLineCount() )
    {
     if( cursor.y<count )
       {
        BookLab::TextLine &line=text.getLine(cursor.y);

        if( ulen spancount=line.list.getLen() )
          {
           if( cursor.span>=spancount ) return;

           BookLab::TextLine *lineptr=text.insLine(cursor.y);

           cursor.y++;

           BookLab::TextLine &line1=lineptr[0];
           BookLab::TextLine &line2=lineptr[1];

           Split split(getCurSpan(),cursor.x);

           String str1=split.str1;
           String str2=split.str2;

           BookLab::Span &old=line2.list[cursor.span];

           if( cursor.span>0 )
             {
              line1.list.reserve(cursor.span+1);

              line1.list.extend_copy(cursor.span,line2.list.getPtr());
             }

           BookLab::Span *span=line1.list.append_default();

           span->body=str1;
           span->format=old.format;
           span->ref=old.ref;

           old.body=str2;

           const Font &font=cfg.font.get();

           Cache(font,line1.list[cursor.span]);
           Cache(font,line2.list[cursor.span]);

           if( cursor.span>0 )
             {
              DelPrefix(line2.list,cursor.span);

              cursor.span=0;
             }

           cursor.x=0;

           fill();

           Cache(line1,data.space_dx);
           Cache(line2,data.space_dx);

           updateData();
          }
        else
          {
           text.insLine(cursor.y);

           cursor.y++;

           cursor.span=0;
           cursor.x=0;

           spanlen=0;

           cleanNames();
          }

        changed.assert();

        showCursor();
       }
    }
 }

StrLen TextWindow::Part(StrLen str,ulen from,ulen to)
 {
  if( from>=to ) return Null;

  return SymPart(str,from,to-from);
 }

void TextWindow::Del(String &str,ulen from,ulen to)
 {
  auto text=Range(str);

  str=StringSum(SymPrefix(text,from),SymPart(text,to));
 }

void TextWindow::Del(String &str,ulen from)
 {
  str=SymPrefix(Range(str),from);
 }

void TextWindow::Del(const Font &font,BookLab::Span &span,ulen from,ulen to)
 {
  Del(span.body,from,to);

  Cache(font,span);
 }

void TextWindow::Del(const Font &font,BookLab::Span &span,ulen from)
 {
  Del(span.body,from);

  Cache(font,span);
 }

void TextWindow::Del(const Font &font,Coord space_dx,BookLab::TextLine &line,ulen from,ulen from_x,ulen to,ulen to_x)
 {
  ulen count=line.list.getLen();

  if( from<count )
    {
     if( from<to )
       {
        Del(font,line.list[from],from_x);

        if( to<count )
          {
           Del(font,line.list[to],0,to_x);
          }

        DelRange(line.list,from+1,to);
       }
     else
       {
        Del(font,line.list[from],from_x,to_x);
       }

     Cache(line,space_dx);
    }
 }

void TextWindow::Del(const Font &font,Coord space_dx,BookLab::TextLine &line,ulen from,ulen from_x)
 {
  ulen count=line.list.getLen();

  if( from<count )
    {
     Del(font,line.list[from],from_x);

     DelRange(line.list,from+1,count);

     Cache(line,space_dx);
    }
 }

void TextWindow::delSel()
 {
  selection_on=false;

  if( cursor==selection ) return;

  flushDX();

  Cursor from=cursor;
  Cursor to=selection;

  if( from>to )
    {
     Swap(from,to);

     cursor=selection;
    }

  ulen count=text.getLineCount();

  if( to.y<count )
    {
     const Font &font=cfg.font.get();

     if( from.y<to.y )
       {
        Del(font,data.space_dx,text.getLine(from.y),from.span,from.x);

        Del(font,data.space_dx,text.getLine(to.y),0,0,to.span,to.x);

        text.delRange(from.y+1,to.y);
       }
     else
       {
        Del(font,data.space_dx,text.getLine(to.y),from.span,from.x,to.span,to.x);
       }

     updateData();
    }

  fill();
 }

void TextWindow::delSelection()
 {
  delSel();

  changed.assert();

  showCursor();
 }

void TextWindow::copy()
 {
  if( selection_on && selection!=cursor )
    {
     Cursor from=selection;
     Cursor to=cursor;

     if( from>to ) Swap(from,to);

     ulen count=text.getLineCount();

     if( to.y<count )
       {
        struct Builder
         {
          PrintString out;
          bool first = true ;

          Builder()
           {
            Putobj(out,"{"_c);
           }

          void add(StrLen format,StrLen ref,StrLen text)
           {
            if( !Change(first,false) ) Putch(out,',');

            Printf(out,"{#;,#;,#;}",DDLPrintableString(text),DDLPrintableString(format),DDLPrintableString(ref));
           }

          void add(BookLab::Span &span,ulen from)
           {
            add(Range(span.format.name),Range(span.ref.name),SymPart(Range(span.body),from));
           }

          void add(BookLab::Span &span,ulen from,ulen to)
           {
            add(Range(span.format.name),Range(span.ref.name),Part(Range(span.body),from,to));
           }

          void eol()
           {
            Putobj(out,"},{"_c);

            first=true;
           }

          String complete()
           {
            Putobj(out,"}"_c);

            return out.close();
           }
         };

        Builder builder;

        flush();

        BookLab::TextLine *line=&text.getLine(from.y);
        ulen spancount=line->list.getLen();

        for(;;)
          {
           if( from.y<to.y )
             {
              if( from.span<spancount )
                {
                 builder.add(line->list[from.span],from.x);

                 from.span++;
                 from.x=0;
                }
              else
                {
                 builder.eol();

                 from.y++;
                 from.span=0;
                 from.x=0;

                 line=&text.getLine(from.y);
                 spancount=line->list.getLen();
                }
             }
           else if( from.span<spancount )
             {
              if( from.span<to.span )
               {
                builder.add(line->list[from.span],from.x);

                from.span++;
                from.x=0;
               }
             else
               {
                builder.add(line->list[from.span],from.x,to.x);

                break;
               }
             }
           else
             {
              break;
             }
          }

        String frame=builder.complete();

        getFrameHost()->textToClipboard(Range(frame));
       }
    }
 }

struct TextWindow::PastData : Funchor
 {
  struct Span
   {
    String body;
    String format;
    String ref;

    BookLab::Span build() const
     {
      BookLab::Span ret;

      ret.body=body;
      ret.format.name=format;
      ret.ref.name=ref;

      return ret;
     }
   };

  struct Line
   {
    DynArray<Span> list;

    BookLab::TextLine build() const
     {
      BookLab::TextLine ret;

      extend(ret);

      return ret;
     }

    void extend(BookLab::TextLine &line) const
     {
      ulen len=list.getLen();

      auto r=line.list.extend_default(len);

      for(ulen i : IndLim(len) )
        {
         r[i]=list[i].build();
        }
     }
   };

  DynArray<Line> list;

  PastData() {}

  ~PastData() {}

  bool operator ! () const { return !list.getLen(); }

  bool isSimple() const
   {
    return list.getLen()==1 && list[0].list.getLen()==1 ;
   }

  StrLen getSimple() const { return Range(list[0].list[0].body); }

  bool parseChar(StrLen &text,char ch)
   {
    if( !text || *text!=ch ) return false;

    ++text;

    return true;
   }

  bool parseString(StrLen &text,String &ret)
   {
    PrintString out;

    if( !parseChar(text,'"') ) return false;

    while( +text )
      {
       char ch=*text;

       ++text;

       if( ch=='\\' )
         {
          if( !text ) return false;

          ch=*text;

          ++text;

          out.put(ch);
         }
       else if( ch=='"' )
         {
          ret=out.close();

          return true;
         }
       else
         {
          out.put(ch);
         }
      }

    return false;
   }

  bool parseSpan(StrLen &text,Span &ret)
   {
    if( !parseChar(text,'{') ) return false;

    if( !parseString(text,ret.body) ) return false;

    if( !parseChar(text,',') ) return false;

    if( !parseString(text,ret.format) ) return false;

    if( !parseChar(text,',') ) return false;

    if( !parseString(text,ret.ref) ) return false;

    if( !parseChar(text,'}') ) return false;

    return true;
   }

  bool parseSpan(StrLen &text,Collector<Span> &buf)
   {
    Span obj;

    if( !parseSpan(text,obj) ) return false;

    buf.append_fill(std::move(obj));

    return true;
   }

  bool parseLine(StrLen &text,Line &ret)
   {
    if( !parseChar(text,'{') ) return false;

    if( !text ) return false;

    if( *text=='}' )
      {
       ++text;

       return true;
      }

    Collector<Span> buf;

    if( !parseSpan(text,buf) ) return false;

    while( +text )
      {
       char ch=*text;

       if( ch=='}' )
         {
          ++text;

          buf.extractTo(ret.list);

          return true;
         }
       else if( ch==',' )
         {
          ++text;

          if( !parseSpan(text,buf) ) return false;
         }
       else
         {
          return false;
         }
      }

    return false;
   }

  bool parseLine(StrLen &text,Collector<Line> &buf)
   {
    Line obj;

    if( !parseLine(text,obj) ) return false;

    buf.append_fill(std::move(obj));

    return true;
   }

  bool parseCombo(StrLen text)
   {
    if( !text ) return true;

    Collector<Line> buf;

    if( !parseLine(text,buf) ) return false;

    while( +text )
      {
       char ch=*text;

       if( ch==',' )
         {
          ++text;

          if( !parseLine(text,buf) ) return false;
         }
       else
         {
          return false;
         }
      }

    buf.extractTo(list);

    return true;
   }

  void parseSimple(StrLen text) // TODO
   {
    Used(text);
   }

  void load(StrLen text)
   {
    if( !parseCombo(text) ) parseSimple(text);
   }

  Function<void (StrLen)> function_load() { return FunctionOf(this,&PastData::load); }
 };

void TextWindow::past(BookLab::TextLine &line,PastData &data)
 {
  if( ulen dlen=data.list.getLen() ; dlen==1 )
    {
     auto &src=data.list[0];

     ulen delta=src.list.getLen();

     auto dst=InsAt(line.list,cursor.span,delta);

     for(ulen i : IndLim(dst.len) ) dst[i]=src.list[i].build();

     cursor.span+=delta;
    }
  else
    {
     auto dst=text.insLines(cursor.y+1,dlen-1);

     for(ulen i : IndLim(dlen-1) ) dst[i]=data.list[i+1].build();

     BookLab::TextLine &line1=text.getLine(cursor.y);

     cursor.y+=dlen-1;

     BookLab::TextLine &line2=text.getLine(cursor.y);

     auto r=Range(line1.list).part(cursor.span);

     ulen new_span=line2.list.getLen();

     cursor.span=0;

     line2.list.extend_copy(r);
     line1.list.shrink(r.len);

     cursor.span=new_span;

     data.list[0].extend(line1);
    }
 }

void TextWindow::pastEnd()
 {
  BookLab::TextLine &line=text.getLine(cursor.y);

  ulen spancount=line.list.getLen();

  cursor.span=PosSub(spancount,1u);

  fill();

  cursor.x=spanlen;

  ok=false;
 }

void TextWindow::past()
 {
  PastData data;

  getFrameHost()->textFromClipboard(data.function_load());

  if( !data ) return;

  if( selection_on ) delSel();

  if( ulen count=text.getLineCount() )
    {
     if( cursor.y<count )
       {
        BookLab::TextLine &line=text.getLine(cursor.y);

        ulen spancount=line.list.getLen();

        if( cursor.span<spancount )
          {
           if( data.isSimple() )
             {
              insert(data.getSimple());

              Replace_max(this->data.text_dx,updateCache(line));
             }
           else
             {
              BookLab::Span *span=ArraySwapIns_guarded(line.list,cursor.span);

              Split split(getCurSpan(),cursor.x);

              span[0].body=String(split.str1);
              span[1].body=String(split.str2);

              span[0].format=span[1].format;
              span[0].ref=span[1].ref;

              cursor.span++;
              cursor.x=0;

              fill();

              past(line,data);

              ok=false;
             }
          }
        else
          {
           ulen delta=data.list.getLen();

           data.list[0].extend(line);

           if( delta>1 )
             {
              auto dst=text.insLines(cursor.y+1,delta-1);

              for(ulen i : IndLim(dst.len) ) dst[i]=data.list[i+1].build();

              cursor.y+=delta-1;
             }

           pastEnd();
          }
       }
    }
  else
    {
     auto dst=text.addLines(data.list.getLen());

     for(ulen i : IndLim(dst.len) ) dst[i]=data.list[i].build();

     cursor.y=dst.len-1;

     pastEnd();
    }

  changed.assert();

  showCursor();
 }

TextWindow::TextWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   spanbuf(1_KByte),

   connector_posX(this,&TextWindow::posSX),
   connector_posY(this,&TextWindow::posSY),

   connector_updated(this,&TextWindow::updated,host.getFrame()->updated),

   input(this)
 {
  defer_tick=input.create(&TextWindow::tick);
 }

TextWindow::~TextWindow()
 {
 }

 // methods

Point TextWindow::getMinSize(Point) const
 {
  FontSize fs=cfg.font->getSize();

  Coord dy=10*fs.dy;

  return Point(2*dy,dy);
 }

void TextWindow::blank()
 {
  flush();

  clean();

  text.blank();
 }

void TextWindow::load(DynArray<BookLab::TextLine> *pad)
 {
  flush();

  clean();

  text.load(pad);

  fill();
 }

void TextWindow::flush()
 {
  applyToSpan( [&] (BookLab::Span &span) { span.body=String(getCurSpan()); } );
 }

void TextWindow::setFormat(String name)
 {
  applyToSpan( [&] (BookLab::Span &span) { span.format.setName(name); } );
 }

void TextWindow::setLink(String name)
 {
  applyToSpan( [&] (BookLab::Span &span) { span.ref.setName(name); } );
 }

void TextWindow::link()
 {
  applyToSpan( [&] (BookLab::Span &span)
                   {
                    showFormat.assert(span.format.name,span.format.notResolved());
                    showLink.assert(span.ref.name,span.ref.notResolved());

                   } );

  redraw();
 }

 // drawing

void TextWindow::layout()
 {
  if( !cache() )
    {
     sx.pos=0;
     sx.total=1;
     sx.page=1;

     sy.pos=0;
     sy.total=1;
     sy.page=1;

     return;
    }

  Point size=getSize();

  Coord dxc=+cfg.cursor_dx;

  size.subXY(2*dxc);

  if( size.x>0 )
    {
     sx.page=(ulen)size.x;
    }
  else
    {
     sx.page=1;
    }

  if( size.y>=data.fs.dy )
    {
     sy.page=ulen(size.y/data.fs.dy);
    }
  else
    {
     sy.page=1;
    }

  sx.total=(ulen)AddSize(data.text_dx,3*dxc+data.fs.dx0+data.fs.dx1);
  sy.total=text.getLineCount();

  sx.total+=sx.page/8;
  sy.total+=sy.page/4;

  sx.adjustPos();
  sy.adjustPos();
 }

bool TextWindow::HasSpec(BookLab::Span &span)
 {
  return span.format.name.getLen() || span.ref.name.getLen() ;
 }

bool TextWindow::Alert(BookLab::Span &span)
 {
  return span.format.notResolved() || span.ref.notResolved() ;
 }

class TextWindow::Draw : SizeData , NoCopy
 {
   SmoothDrawArt art;

   Pane pane;

   const Font &font;

   Coord dxc;

   MCoord width;
   MCoord skew;
   MCoord delta;

   VColor vc_cursor;
   VColor vc_end;
   VColor vc_text;
   VColor vc_line;
   VColor vc_alert;
   VColor vc_select;

  public:

   Draw(const DrawBuf &buf,Pane pane_,const Config &cfg,const SizeData &data)
    : SizeData(data),

      art(buf),
      pane(pane_),
      font(cfg.font.get())
    {
     dxc=+cfg.cursor_dx;

     width=+cfg.width;

     skew=Fraction(fs.skew);
     delta=MulDiv(skew,fs.dy-fs.by,fs.dy);

     vc_cursor=+cfg.cursor;
     vc_end=+cfg.endspan;
     vc_text=+cfg.text;
     vc_line=+cfg.line;
     vc_alert=+cfg.alert;
     vc_select=+cfg.select;
    }

   Point getBase() const
    {
     Point base(fs.dx0,fs.by);

     return base.addXY(dxc);
    }

   Point getBase(Coord shift_x) const
    {
     return getBase().subX(shift_x);
    }

   Coord dY() const { return fs.dy; }

   void cursor(Point base,bool on)
    {
     MCoord width=Fraction(dxc);
     MCoord dy=Fraction(fs.dy);

     MCoord x=Fraction(base.x)-delta;
     MCoord y=Fraction(base.y-fs.by);

     FigureCursor fig(x,y,y+dy,width,skew);

     if( on )
       {
        fig.solid(art,vc_cursor);
       }
     else
       {
        fig.loop(art,HalfPos,width/3,vc_cursor);
       }
    }

   void end(Point base)
    {
     MCoord dx=Fraction(space_dx);
     MCoord dy=Fraction(fs.dy);

     MCoord x=Fraction(base.x)-delta;
     MCoord y=Fraction(base.y-fs.by);

     FigureSkew fig(x,x+dx,y,y+dy,skew);

     fig.solid(art,vc_end);
    }

   template <class T>
   void text(Point base,T str)
    {
     font->text(art.getBuf(),pane,base,str,vc_text);
    }

   template <class T>
   Coord text(T str)
    {
     return font->text(str).dx;
    }

   void under(Point base,Coord len,bool alert)
    {
     VColor vc = alert? vc_alert : vc_line ;

     art.path(width,vc,base,base.addX(len-1));
    }

   Point span(Point base,BookLab::Span &span)
    {
     text(base,Range(span.body));

     if( HasSpec(span) ) under(base,span.dx,Alert(span));

     base.x+=span.dx;

     end(base);

     base.x+=space_dx;

     return base;
    }

   Point text(Point base,PtrLen<const Char> str,ulen pos,bool on)
    {
     Split split(str,pos);

     Coord dx1=text(split.str1);
     Coord dx2=text(split.str2);

     text(base,split.str1);

     base.x+=dx1;

     cursor(base,on);

     base.x+=dxc;

     text(base,split.str2);

     base.x+=dx2;

     return base;
    }

   Point span(Point base,BookLab::Span &span,PtrLen<const Char> str,ulen pos,bool on)
    {
     Point p=text(base,str,pos,on);

     if( HasSpec(span) ) under(base,p.x-base.x,Alert(span));

     end(p);

     p.x+=space_dx;

     return p;
    }

   Coord getPosX(Coord base,BookLab::TextLine &line,ulen span,ulen x,ulen curind,PtrLen<const Char> curspan,bool flag=false)
    {
     if( span<line.list.getLen() )
       {
        for(ulen i=0; i<span ;i++)
          if( i!=curind )
            {
             base+=line.list[i].dx+space_dx;
            }
          else
            {
             base+=text(curspan)+space_dx;
            }

        if( span!=curind )
          {
           base+=font->text(Range(line.list[span].body),x).dx;
          }
        else
          {
           base+=font->text(curspan,x).dx;
          }
       }
     else
       {
        for(ulen i : IndLim(line.list.getLen()) )
          if( i!=curind )
            {
             base+=line.list[i].dx+space_dx;
            }
          else
            {
             base+=text(curspan)+space_dx;
            }
       }

     if( flag ) base+=dxc;

     return base;
    }

   Coord getPosX(Coord base,BookLab::TextLine &line,ulen curind,PtrLen<const Char> curspan,bool flag)
    {
     for(ulen i : IndLim(line.list.getLen()) )
       if( i!=curind )
         {
          base+=line.list[i].dx+space_dx;
         }
       else
         {
          base+=text(curspan)+space_dx;
         }

     if( flag ) base+=dxc;

     return base;
    }

   Point getPos(Point base,ulen y,BookLab::TextLine &line,ulen span,ulen x,ulen curind,PtrLen<const Char> curspan,bool flag)
    {
     return Point(getPosX(base.x,line,span,x,curind,curspan,flag),base.y+Coord(y)*fs.dy);
    }

   Coord getPosX(Coord base,BookLab::TextLine &line,ulen span,ulen x,bool flag=false)
    {
     if( span<line.list.getLen() )
       {
        for(ulen i=0; i<span ;i++) base+=line.list[i].dx+space_dx;

        base+=font->text(Range(line.list[span].body),x).dx;
       }
     else
       {
        for(ulen i : IndLim(line.list.getLen()) ) base+=line.list[i].dx+space_dx;
       }

     if( flag ) base+=dxc;

     return base;
    }

   Point getPos(Point base,ulen y,BookLab::TextLine &line,ulen span,ulen x,bool flag)
    {
     return Point(getPosX(base.x,line,span,x,flag),base.y+Coord(y)*fs.dy);
    }

   Coord getPosX(Coord base,BookLab::TextLine &line,bool flag=false)
    {
     base+=line.dx+space_dx;

     if( flag ) base+=dxc;

     return base;
    }

   Point getPos(Point base,ulen y)
    {
     return Point(base.x,base.y+Coord(y)*fs.dy);
    }

   void select(Point base,Coord len)
    {
     MCoord dx=Fraction(len);
     MCoord dy=Fraction(fs.dy);

     MCoord x=Fraction(base.x)-delta;
     MCoord y=Fraction(base.y-fs.by);

     FigureSkew fig(x,x+dx,y,y+dy,skew);

     fig.solid(art,vc_select);
    }
 };

void TextWindow::draw(DrawBuf buf,bool) const
 {
  if( !cache() )
    {
     buf.erase(Black);

     return;
    }

  Draw draw(buf,getPane(),cfg,data);

  Coord shift_x=Coord(sx.pos);

  Point base=draw.getBase(shift_x);

  if( ulen count=text.getLineCount() )
    {
     ulen lim=AddMin(sy.pos,sy.page,count);

     if( selection_on )
       {
        Cursor from=selection;
        Cursor to=cursor;
        bool flag=false;

        if( from>to )
          {
           Swap(from,to);

           flag=true;
          }

        if( from<to )
          {
           if( from.y<to.y )
             {
              if( from.y>=sy.pos && from.y<lim )
                {
                 BookLab::TextLine &line=text.getLine(from.y);

                 if( from.y==cursor.y )
                   {
                    Point a=draw.getPos(base,from.y-sy.pos,line,from.span,from.x,cursor.span,getCurSpan(),flag);
                    Coord b=draw.getPosX(base.x,line,cursor.span,getCurSpan(),flag);

                    draw.select(a,b-a.x);
                   }
                 else
                   {
                    Point a=draw.getPos(base,from.y-sy.pos,line,from.span,from.x,flag);
                    Coord b=draw.getPosX(base.x,line,flag);

                    draw.select(a,b-a.x);
                   }
                }

              if( to.y>=sy.pos && to.y<lim )
                {
                 BookLab::TextLine &line=text.getLine(to.y);

                 if( to.y==cursor.y )
                   {
                    Point a=draw.getPos(base,to.y-sy.pos);
                    Coord b=draw.getPosX(base.x,line,to.span,to.x,cursor.span,getCurSpan());

                    draw.select(a,b-a.x);
                   }
                 else
                   {
                    Point a=draw.getPos(base,to.y-sy.pos);
                    Coord b=draw.getPosX(base.x,line,to.span,to.x);

                    draw.select(a,b-a.x);
                   }
                }

              for(ulen i : IndLim(Max_cast(sy.pos,from.y+1),Min(lim,to.y)) )
                {
                 BookLab::TextLine &line=text.getLine(i);

                 Point a=draw.getPos(base,i-sy.pos);
                 Coord b=draw.getPosX(base.x,line);

                 draw.select(a,b-a.x);
                }
             }
           else
             {
              if( from.y>=sy.pos && from.y<lim )
                {
                 BookLab::TextLine &line=text.getLine(from.y);

                 Point a=draw.getPos(base,from.y-sy.pos,line,from.span,from.x,cursor.span,getCurSpan(),flag);
                 Coord b=draw.getPosX(base.x,line,to.span,to.x,cursor.span,getCurSpan(),flag);

                 draw.select(a,b-a.x);
                }
             }
          }
       }

     for(ulen i : IndLim(sy.pos,lim) )
       {
        BookLab::TextLine &line=text.getLine(i);

        if( ulen spancount=line.list.getLen() )
          {
           Point p=base;

           for(ulen j : IndLim(spancount) )
             if( i==cursor.y && j==cursor.span )
               {
                p=draw.span(p,line.list[j],getCurSpan(),cursor.x,cursor_on);
               }
             else
               {
                p=draw.span(p,line.list[j]);
               }
          }
        else
          {
           if( i==cursor.y ) draw.cursor(base,cursor_on);
          }

        base.y+=draw.dY();
       }
    }
  else
    {
     draw.cursor(base,cursor_on);
    }
 }

 // base

void TextWindow::open()
 {
  focus=false;
  cursor_on=false;
  drag=false;
  mouse_pos=false;

  defer_tick.stop();
 }

void TextWindow::close()
 {
  defer_tick.stop();

  flush();
 }

 // keyboard

void TextWindow::gainFocus()
 {
  if( Change(focus,true) )
    {
     tickStart();

     redraw();
    }
 }

void TextWindow::looseFocus()
 {
  if( Change(focus,false) )
    {
     tickStop();

     redraw();
    }
 }

 // mouse

void TextWindow::looseCapture()
 {
  drag=false;
 }

MouseShape TextWindow::getMouseShape(Point,KeyMod) const
 {
  return Mouse_IBeem;
 }

 // user input

void TextWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void TextWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_Left :
      {
       keySelect(kmod&KeyMod_Shift);

       moveLeft(repeat);
      }
     break;

     case VKey_Right :
      {
       keySelect(kmod&KeyMod_Shift);

       moveRight(repeat);
      }
     break;

     case VKey_Home :
      {
       keySelect(kmod&KeyMod_Shift);

       moveHome();
      }
     break;

     case VKey_End :
      {
       keySelect(kmod&KeyMod_Shift);

       moveEnd();
      }
     break;

     case VKey_Tab :
      {
       keySelect(kmod&KeyMod_Shift);

       moveTab();
      }
     break;

     case VKey_Up :
      {
       keySelect(kmod&KeyMod_Shift);

       moveUp(repeat);
      }
     break;

     case VKey_Down :
      {
       keySelect(kmod&KeyMod_Shift);

       moveDown(repeat);
      }
     break;

     case VKey_PageUp :
      {
       keySelect(kmod&KeyMod_Shift);

       if( kmod&KeyMod_Ctrl )
         moveTop();
       else
         moveUp(repeat*sy.page);
      }
     break;

     case VKey_PageDown :
      {
       keySelect(kmod&KeyMod_Shift);

       if( kmod&KeyMod_Ctrl )
         moveBottom();
       else
         moveDown(repeat*sy.page);
      }
     break;

     case VKey_Enter :
      {
       splitLine();
      }
     break;

     case VKey_Space :
      {
       if( kmod&KeyMod_Shift )
         insChar(' ');
       else
         splitSpan();
      }
     break;

     case VKey_Delete :
      {
       if( selection_on && selection!=cursor )
         {
          if( kmod&KeyMod_Shift ) copy();

          delSelection();
         }
       else
         {
          delChar(false);
         }
      }
     break;

     case VKey_BackSpace :
      {
       if( selection_on && selection!=cursor )
         {
          delSelection();
         }
       else
         {
          delChar(true);
         }
      }
     break;

     case VKey_c :
      {
       if( kmod&KeyMod_Ctrl ) copy();
      }
     break;

     case VKey_v :
      {
       if( kmod&KeyMod_Ctrl ) past();
      }
     break;

     case VKey_Insert :
      {
       if( kmod&KeyMod_Ctrl )
         copy();
       else if( kmod&KeyMod_Shift )
         past();
      }
     break;
    }
 }

void TextWindow::react_Char(Char ch)
 {
  if( ch!=' ' ) insChar(ch);
 }

void TextWindow::react_LeftClick(Point point,MouseKey mkey)
 {
  mouse_pos = !(mkey&MouseKey_Ctrl) ;

  startDrag(point);
 }

void TextWindow::react_LeftUp(Point point,MouseKey)
 {
  if( drag )
    {
     endDrag(point);
    }
 }

void TextWindow::react_Move(Point point,MouseKey mkey)
 {
  if( drag )
    {
     if( mkey&MouseKey_Left )
       {
        dragTo(point);
       }
     else
       {
        endDrag();
       }
    }
 }

void TextWindow::react_Leave()
 {
  // do nothing
 }

void TextWindow::react_Wheel(Point,MouseKey mkey,Coord delta_)
 {
  unsigned delta=IntAbs(delta_);

  if( mkey&MouseKey_Shift )
    {
     delta*=data.fs.medDX();

     if( delta_>0 )
       subSXPos(delta);
     else
       addSXPos(delta);
    }
  else
    {
     if( delta_>0 )
       subSYPos(delta);
     else
       addSYPos(delta);
    }
 }

/* class ScrollTextWindow */

void ScrollTextWindow::changed()
 {
  layout();

  redraw();

  modified.assert();
 }

ScrollTextWindow::ScrollTextWindow(SubWindowHost &host,const ConfigType &cfg)
 : ScrollableWindow<TextWindow>(host,cfg),

   connector_changed(this,&ScrollTextWindow::changed,window.changed),

   showFormat(window.showFormat),
   showLink(window.showLink)
 {
  wlist.enableTabFocus(false);
 }

ScrollTextWindow::~ScrollTextWindow()
 {
 }

void ScrollTextWindow::blank()
 {
  window.blank();

  layout();

  redraw();
 }

void ScrollTextWindow::load(DynArray<BookLab::TextLine> *pad)
 {
  window.load(pad);

  layout();

  redraw();
 }

/* class TextEditor */

void TextEditor::format_pressed()
 {
  String name=edit_format.getString();

  edit_text.setFormat(name);

  edit_format.alert(name.getLen()!=0);

  modified.assert();
 }

void TextEditor::link_pressed()
 {
  String name=edit_link.getString();

  edit_text.setLink(name);

  edit_link.alert(name.getLen()!=0);

  modified.assert();
 }

void TextEditor::show_format(String name,bool alert)
 {
  edit_format.setText(Range(name));

  edit_format.alert(alert);
 }

void TextEditor::show_link(String name,bool alert)
 {
  edit_link.setText(Range(name));

  edit_link.alert(alert);
 }

TextEditor::TextEditor(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   btn_format(wlist,cfg.btn_cfg,"Format"_def),
   btn_link(wlist,cfg.btn_cfg,"Link"_def),

   edit_format(wlist,cfg.edit_cfg),
   edit_link(wlist,cfg.edit_cfg),
   cont(wlist,cfg.cont_cfg),

   edit_text(wlist,cfg.text_cfg),

   connector_format_pressed(this,&TextEditor::format_pressed,btn_format.pressed),
   connector_link_pressed(this,&TextEditor::link_pressed,btn_link.pressed),

   connector_show_format(this,&TextEditor::show_format,edit_text.showFormat),
   connector_show_link(this,&TextEditor::show_link,edit_text.showLink),

   modified(edit_text.modified)
 {
  wlist.insTop(btn_format,edit_format,btn_link,edit_link,edit_text,cont);

  edit_format.hideInactiveCursor();
  edit_link.hideInactiveCursor();

  wlist.enableTabFocus(false);
 }

TextEditor::~TextEditor()
 {
 }

 // methods

Point TextEditor::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(btn_format),Lay(edit_format)};

  LayToRightCenter lay2{Lay(btn_link),Lay(edit_link)};

  LayInner lay3{cont,Lay{edit_text}};

  LayToBottom lay{lay1,lay2,lay3};

  return lay.getMinSize(space);
 }

void TextEditor::load(DynArray<BookLab::TextLine> *pad)
 {
  show_format(Null,false);
  show_link(Null,false);

  edit_text.load(pad);
 }

 // base

void TextEditor::open()
 {
  ComboWindow::open();

  edit_text.setFocus();
 }

 // drawing

void TextEditor::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(btn_format),Lay(edit_format)};

  LayToRightCenter lay2{Lay(btn_link),Lay(edit_link)};

  LayInner lay3{cont,Lay{edit_text}};

  LayToBottom lay{lay1,lay2,lay3};

  lay.setPlace(getPane(),space);
 }

void TextEditor::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

} // namespace App

