/* EditRatioWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/EditRatioWindow.h>

#include <CCore/inc/video/FigureLib.h>

namespace App {

/* class EditRatioWindow */

Coord EditRatioWindow::ToCoord(Geometry::Real x)
 {
  return (Coord)x.getVal();
 }

void EditRatioWindow::newValue()
 {
  value=Geometry::Real(a)/Geometry::Real(b);

  redraw();

  changed.assert(value);
 }

void EditRatioWindow::pin(Point point)
 {
  point-=base;

  if( point.y<0 )
    {
     a=point.x;
     b=-point.y;

     newValue();
    }
 }

void EditRatioWindow::shiftA(Coord delta)
 {
  a+=delta;

  newValue();
 }

void EditRatioWindow::shiftB(Coord delta)
 {
  Coord new_b=b+delta;

  if( new_b>0 )
    {
     b=new_b;

     newValue();
    }
  else if( b>1 )
    {
     b=1;

     newValue();
    }
 }

EditRatioWindow::EditRatioWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   value(0)
 {
 }

EditRatioWindow::~EditRatioWindow()
 {
 }

 // methods

Point EditRatioWindow::getMinSize() const
 {
  return {+cfg.dx,+cfg.dy};
 }

void EditRatioWindow::setValue(Geometry::Ratio value_)
 {
  if( value_.rex )
    {
     value=Geometry::Ratio(1);
     a=0;
     b=1;
    }
  else
    {
     value=value_;

     Geometry::Real x=value_.val;

     Geometry::Real d=Geometry::Real::Den(x,50);

     b=ToCoord(d);

     a=ToCoord(Geometry::Real::RoundMul(d,Cap<Geometry::Real>(MinCoord/d,x,MaxCoord/d)));
    }

  redraw();
 }

 // drawing

bool EditRatioWindow::isGoodSize(Point size) const
 {
  return size>=getMinSize();
 }

void EditRatioWindow::layout()
 {
  Coord s=+cfg.shade_dxy;

  Point size=getSize().subXY(s);

  pane=Pane(Null,size.x,size.y);
  shade1=Pane(s,size.y,size.x,s);
  shade2=Pane(size.x,s,s,size.y-s);

  base=size/2;

  text=Pane(0,base.y+size.y/12,size.x,size.y/3);
 }

void EditRatioWindow::draw(DrawBuf buf,DrawParam) const
 {
  if( pane.dx<10 || pane.dy<10 ) return;

  MCoord width=+cfg.width;

  VColor face=+cfg.face;
  VColor gray=+cfg.gray;

  SmoothDrawArt art(buf.cut(pane));

  MPane p(pane);
  FigureBox fig(p);

  // body

  {
   fig.solid(art,+cfg.back);

   buf.erase(shade1,gray);
   buf.erase(shade2,gray);
  }

  // length

  {
   Coord d=RoundUpLen(width);
   MPoint endA=base.addX(Cap<Coord>(-base.x+d,a,base.x+1+d));
   MPoint endB=base.subY(b);

   art.ball(base,2*width,face);
   art.ball(endA,2*width,face);
   art.ball(endB,2*width,face);

   art.path(width,face,base,endA);
   art.path(width,face,base,endB);
  }

  // text

  {
   char temp[TextBufLen];
   PrintBuf out(Range(temp));

   Printf(out,"#;/#;",a,b);

   cfg.font->text(buf,text,TextPlace(AlignX_Center,AlignY_Top),out.close(),+cfg.text);
  }

  // border

  {
   VColor vc = focus? +cfg.focus : ( hilight? +cfg.hilight : +cfg.border ) ;

   fig.loop(art,HalfPos,width,vc);
  }
 }

 // base

void EditRatioWindow::open()
 {
  focus=false;
  hilight=false;
 }

 // keyboard

FocusType EditRatioWindow::askFocus() const
 {
  return FocusOk;
 }

void EditRatioWindow::gainFocus()
 {
  if( Change(focus,true) ) redraw();
 }

void EditRatioWindow::looseFocus()
 {
  if( Change(focus,false) ) redraw();
 }

 // mouse

MouseShape EditRatioWindow::getMouseShape(Point,KeyMod) const
 {
  return Mouse_Arrow;
 }

 // user input

void EditRatioWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void EditRatioWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_Up :
      {
       if( kmod&KeyMod_Shift )
         shiftB(10*CountToCoord(repeat));
       else
         shiftB(CountToCoord(repeat));
      }
     break;

     case VKey_Down :
      {
       if( kmod&KeyMod_Shift )
         shiftB(-10*CountToCoord(repeat));
       else
         shiftB(-CountToCoord(repeat));
      }
     break;

     case VKey_Right :
     case VKey_NumPlus :
      {
       if( kmod&KeyMod_Shift )
         shiftA(10*CountToCoord(repeat));
       else
         shiftA(CountToCoord(repeat));
      }
     break;

     case VKey_Left :
     case VKey_NumMinus :
      {
       if( kmod&KeyMod_Shift )
         shiftA(-10*CountToCoord(repeat));
       else
         shiftA(-CountToCoord(repeat));
      }
     break;
    }
 }

void EditRatioWindow::react_LeftClick(Point point,MouseKey)
 {
  if( pane.contains(point) ) pin(point);
 }

void EditRatioWindow::react_Move(Point point,MouseKey mkey)
 {
  if( pane.contains(point) )
    {
     if( Change(hilight,true) ) redraw();

     if( mkey&MouseKey_Left ) pin(point);
    }
  else
    {
     if( Change(hilight,false) ) redraw();
    }
 }

void EditRatioWindow::react_Leave()
 {
  if( Change(hilight,false) ) redraw();
 }

void EditRatioWindow::react_Wheel(Point,MouseKey mkey,Coord delta)
 {
  if( mkey&MouseKey_Shift )
    {
     shiftB(delta);
    }
  else
    {
     shiftA(delta);
    }
 }

} // namespace App

