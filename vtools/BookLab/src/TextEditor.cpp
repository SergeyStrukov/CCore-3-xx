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

#include <CCore/inc/video/LayoutCombo.h>
#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/algon/SimpleRotate.h>

#include <CCore/inc/Exception.h>

namespace App {

/* InsAt() */

template <class A>
auto InsAt(A &array,ulen ind)
 {
  array.append_default();

  auto r=Range(array).part(ind);

  Algon::RangeRotateRight(r);

  return r.ptr;
 }

/* class TextBuf */

TextBuf::TextBuf()
 {
 }

TextBuf::~TextBuf()
 {
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

void TextWindow::clean()
 {
  block_cache=false;
  ok=false;

  sx.beg();
  sy.beg();

  cursor={};
  spanlen=0;
 }

Coord TextWindow::Cache(const Font &font,BookLab::Span &span)
 {
  TextSize ts=font->text(Range(span.body));

  Coord ret=ts.dx;

  span.dx=ret;

  return ret;
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

void TextWindow::SizeData::update(BookLab::TextLine &line)
 {
  Replace_max(text_dx,Cache(line,space_dx));
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

        for(ulen i : IndLim(count) ) data.update(font,text.getLine(i));

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

void TextWindow::posX(ulen pos)
 {
  sx.setPos(pos);

  redraw();
 }

void TextWindow::posY(ulen pos)
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

void TextWindow::flush() const
 {
  applyToSpan( [&] (BookLab::Span &span) { span.body=String(getCurSpan()); } );
 }

void TextWindow::setPosX(ulen x)
 {
  sx.setPos(x);

  scroll_x.assert(sx.pos);

  redraw();
 }

void TextWindow::setPosY(ulen y)
 {
  sy.setPos(y);

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
  flush();

  cursor.span=span;

  fill();
 }

void TextWindow::showCursor()
 {
  if( cursor.y<sy.pos )
    {
     setPosY(cursor.y);
    }
  else if( cursor.y>=sy.pos+sy.page )
    {
     setPosY(cursor.y-sy.page+1);
    }

  const Font &font=cfg.font.get();

  Coord dxc=+cfg.cursor_dx;

  Coord x=data.fs.dx0+dxc;

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
     setPosX(PosSub(X,(ulen)dxc));
    }
  else if( X>=sx.pos+sx.page )
    {
     setPosX(X-sx.page+1+(ulen)dxc+(ulen)data.space_dx);
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

void TextWindow::setPos(ulen x,ulen y)
 {
  flush();

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

void TextWindow::makeNonEmpty()
 {
  if( !text.getLineCount() ) text.addLine();
 }

void TextWindow::insSpanChar(BookLab::TextLine &line,Char ch)
 {
  ulen count=line.list.getLen();

  if( spanlen<spanbuf.getLen() )
    {
     InsChar(spanbuf.getPtr(),spanlen,Min(cursor.x,spanlen),ch);

     spanlen++;
     cursor.x++;

     Coord dx=MulSize(count-1,data.space_dx);

     for(ulen i : IndLim(count) )
       {
        BookLab::Span &span=line.list[i];

        if( i==cursor.span )
          {
           Cache(cfg.font.get(),span);
          }

        dx=AddSize(dx,span.dx);
       }

     line.dx=dx;

     Replace_max(data.text_dx,dx);

     changed.assert();

     showCursor();
    }
 }

void TextWindow::insChar(Char ch)
 {
  if( !SymCharIsPrintable(ch) ) return;

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
 }

void TextWindow::splitSpan()
 {
  makeNonEmpty();

  if( ulen count=text.getLineCount() )
    {
     if( cursor.y<count )
       {
        BookLab::TextLine &line=text.getLine(cursor.y);

        if( ulen spancount=line.list.getLen() )
          {
           if( cursor.span>=spancount ) return;

           BookLab::Span *span=InsAt(line.list,cursor.span);

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

void TextWindow::splitLine() // TODO
 {
  makeNonEmpty();


  changed.assert();

  showCursor();
 }

TextWindow::TextWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   spanbuf(1_KByte),

   connector_posX(this,&TextWindow::posX),
   connector_posY(this,&TextWindow::posY),

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
  save();

  clean();

  text.blank();

  changed.assert();
 }

void TextWindow::load(DynArray<BookLab::TextLine> *pad)
 {
  clean();

  text.load(pad);

  fill();

  changed.assert();
 }

void TextWindow::save() const
 {
  flush();

  text.save();
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

  sx.total=(ulen)AddSize(data.text_dx,data.fs.dx0+data.fs.dx1+2*dxc);
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

  SmoothDrawArt art(buf);

  if( ulen count=text.getLineCount() )
    {
     for(ulen i : IndLim(sy.pos,sy.pos+sy.page) )
       {
        if( i>=count ) break;

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

  defer_tick.stop();
 }

void TextWindow::close()
 {
  defer_tick.stop();
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

void TextWindow::looseCapture() // TODO
 {
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

void TextWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat) // TODO
 {
  switch( vkey )
    {
     case VKey_Left :
      {
       moveLeft(repeat);
      }
     break;

     case VKey_Right :
      {
       moveRight(repeat);
      }
     break;

     case VKey_Home :
      {
       moveHome();
      }
     break;

     case VKey_End :
      {
       moveEnd();
      }
     break;

     case VKey_Tab :
      {
       moveTab();
      }
     break;

     case VKey_Up :
      {
       moveUp(repeat);
      }
     break;

     case VKey_Down :
      {
       moveDown(repeat);
      }
     break;

     case VKey_PageUp :
      {
       if( kmod&KeyMod_Ctrl )
         moveTop();
       else
         moveUp(repeat*sy.page);
      }
     break;

     case VKey_PageDown :
      {
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
       // TODO
      }
     break;

     case VKey_BackSpace :
      {
       // TODO
      }
     break;
    }
 }

void TextWindow::react_Char(Char ch)
 {
  if( ch!=' ' ) insChar(ch);
 }

void TextWindow::react_LeftClick(Point point,MouseKey mkey) // TODO
 {
  Used(point);
  Used(mkey);
 }

void TextWindow::react_LeftUp(Point point,MouseKey mkey) // TODO
 {
  Used(point);
  Used(mkey);
 }

void TextWindow::react_Move(Point point,MouseKey mkey) // TODO
 {
  Used(point);
  Used(mkey);
 }

void TextWindow::react_Leave() // TODO
 {
 }

void TextWindow::react_Wheel(Point point,MouseKey mkey,Coord delta) // TODO
 {
  Used(point);
  Used(mkey);
  Used(delta);
 }

/* class ScrollTextWindow */

void ScrollTextWindow::changed()
 {
  layout();

  redraw();
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

/* class TextEditor */

void TextEditor::format_pressed()
 {
  String name=edit_format.getString();

  edit_text.setFormat(name);

  edit_format.alert(name.getLen()!=0);
 }

void TextEditor::link_pressed()
 {
  String name=edit_link.getString();

  edit_text.setLink(name);

  edit_link.alert(name.getLen()!=0);
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
   connector_show_link(this,&TextEditor::show_link,edit_text.showLink)
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

void TextEditor::blank()
 {
  edit_text.blank();
 }

void TextEditor::load(DynArray<BookLab::TextLine> *pad)
 {
  show_format(Null,false);
  show_link(Null,false);

  edit_text.load(pad);
 }

void TextEditor::save() const
 {
  edit_text.save();
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

