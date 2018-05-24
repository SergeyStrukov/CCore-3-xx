/* EditAngleWindow.cpp */
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

#include <inc/EditAngleWindow.h>

#include <CCore/inc/video/FigureLib.h>

namespace App {

/* class EditAngleWindow */

void EditAngleWindow::newValue(Geometry::Angle value_)
 {
  value=value_;

  redraw();

  changed.assert(value);
 }

void EditAngleWindow::pin(Point point)
 {
  if( point!=base )
    {
     newValue( Geometry::Point::Arg(GPoint(point-base)) );
    }
 }

void EditAngleWindow::rotate(Coord delta)
 {
  newValue( value+GradToRadian(delta) );
 }

EditAngleWindow::EditAngleWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   value(0)
 {
 }

EditAngleWindow::~EditAngleWindow()
 {
 }

 // methods

SizeBox EditAngleWindow::getMinSize() const
 {
  return +cfg.dxy;
 }

 // drawing

bool EditAngleWindow::isGoodSize(Point size) const
 {
  return size>=getMinSize();
 }

void EditAngleWindow::layout()
 {
  Point size=getSize();
  Coord s=+cfg.shade_dxy;

  len=Min(size.x,size.y)-s;

  pane=Pane(Null,len);
  shade1=Pane(s,len,len,s);
  shade2=Pane(len,s,s,len-s);

  base=Point::Diag(len/2);

  text_plus=Pane(0,len/2+len/12,len,len/3);

  text_minus=Pane(0,len/12,len,len/3);
 }

void EditAngleWindow::draw(DrawBuf buf,bool) const
 {
  if( len<10 ) return;

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

  // angle

  {
   Geometry::Real radius(len*0.4);
   Geometry::Real radius2(len*0.45);
   Geometry::Real radius3(len*0.35);

   MPoint line_x=Geometry::Map(Geometry::Point(radius2,0));
   MPoint line_y=Geometry::Map(Geometry::Point(0,radius2));

   MPoint line=Geometry::Map(Geometry::Point::Polar(radius,value));

   MPoint end_x=base+line_x;
   MPoint end_y=base-line_y;

   art.path(width/2,gray,base-line_x,end_x);
   art.path(width/2,gray,end_y,base+line_y);

   MCoord arrow_size=+cfg.arrow_size;

   FigureRightArrow fig1(MBox(end_x,arrow_size));

   fig1.curveSolid(art,gray);

   FigureUpArrow fig2(MBox(end_y,arrow_size));

   fig2.curveSolid(art,gray);

   for(int y : {0,90,180,180+90} )
     for(int x : {15,30,45,60,75} )
       {
        Geometry::Angle a=GradToRadian(x+y);

        art.path(width/2,gray,base+Geometry::Map(Geometry::Point::Polar(radius3,a)),base+Geometry::Map(Geometry::Point::Polar(radius2,a)));
       }

   art.path(width,face,base,base+line);

   art.ball(base,2*width,face);
  }

  // text

  {
   char temp[TextBufLen];
   PrintBuf out(Range(temp));

   Putobj(out,value);

   if( value.val>=0 )
     cfg.font->text(buf,text_plus,TextPlace(AlignX_Center,AlignY_Top),out.close(),+cfg.text);
   else
     cfg.font->text(buf,text_minus,TextPlace(AlignX_Center,AlignY_Bottom),out.close(),+cfg.text);
  }

  // border

  {
   VColor vc = focus? +cfg.focus : ( hilight? +cfg.hilight : +cfg.border ) ;

   fig.loop(art,HalfPos,width,vc);
  }
 }

 // base

void EditAngleWindow::open()
 {
  focus=false;
  hilight=false;
 }

 // keyboard

FocusType EditAngleWindow::askFocus() const
 {
  return FocusOk;
 }

void EditAngleWindow::gainFocus()
 {
  if( Change(focus,true) ) redraw();
 }

void EditAngleWindow::looseFocus()
 {
  if( Change(focus,false) ) redraw();
 }

 // mouse

MouseShape EditAngleWindow::getMouseShape(Point,KeyMod) const
 {
  return Mouse_Arrow;
 }

 // user input

void EditAngleWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void EditAngleWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_Up :
     case VKey_Left :
     case VKey_NumPlus :
      {
       if( kmod&KeyMod_Shift )
         rotate(10*CountToCoord(repeat));
       else
         rotate(CountToCoord(repeat));
      }
     break;

     case VKey_Down :
     case VKey_Right :
     case VKey_NumMinus :
      {
       if( kmod&KeyMod_Shift )
         rotate(-10*CountToCoord(repeat));
       else
         rotate(-CountToCoord(repeat));
      }
     break;
    }
 }

void EditAngleWindow::react_LeftClick(Point point,MouseKey)
 {
  if( pane.contains(point) ) pin(point);
 }

void EditAngleWindow::react_Move(Point point,MouseKey mkey)
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

void EditAngleWindow::react_Leave()
 {
  if( Change(hilight,false) ) redraw();
 }

void EditAngleWindow::react_Wheel(Point,MouseKey mkey,Coord delta)
 {
  if( mkey&MouseKey_Shift )
    {
     rotate(10*delta);
    }
  else
    {
     rotate(delta);
    }
 }

} // namespace App


