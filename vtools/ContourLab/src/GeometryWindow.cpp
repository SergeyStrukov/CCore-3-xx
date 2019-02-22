/* GeometryWindow.cpp */
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

#include <inc/GeometryWindow.h>

#include <CCore/inc/video/FigureLib.h>

namespace App {

/* class GeometryWindow */

void GeometryWindow::pin(Point point_)
 {
  if( point )
    {
     *point=GPoint(point_);

     redraw();

     changed.assert();
    }
 }

void GeometryWindow::shift_x(Coord delta)
 {
  if( point )
    {
     point->x=point->x+Geometry::Real(delta);

     redraw();

     changed.assert();
    }
 }

void GeometryWindow::shift_y(Coord delta)
 {
  if( point )
    {
     point->y=point->y+Geometry::Real(delta);

     redraw();

     changed.assert();
    }
 }

class GeometryWindow::DrawItem : Geometry
 {
   SmoothDrawArt art;

   Coord dx;
   Coord dy;

   MCoord width;

   VColor face;
   VColor gray;

   // work

   Real cap_radius;

   Point A,B,C,D;

   static constexpr Coord Guard = 2 ;

   Point P1,P2;
   Point P3,P4;
   Point Q1,Q2;
   Point Q3,Q4;

  private:

   bool test(Point p)
    {
     return p.x>=-dx && p.y>=-dy && p.x<=2*dx && p.y<=2*dy ;
    }

   // line

   static Point SafeMeet(Line a,Point b,Point c)
    {
     try
       {
        return MeetIn(a,b,c);
       }
     catch(RealException rex)
       {
        return rex;
       }
    }

   void drawLine(Point a,Point b,bool selected,const Label &label)
    {
     MPoint beg=Map(a);
     MPoint end=Map(b);

     if( label.gray && !selected )
       art.path(width/2,gray,beg,end);
     else
       art.path(width,face,beg,end);

     label.setPos(end);
    }

   // circle

   static Couple SafeMeet(Circle C,Point a,Point b)
    {
     try
       {
        return MeetCircleIn(C,a,b);
       }
     catch(RealException rex)
       {
        return rex;
       }
    }

   static void SetPos(const Label &label,Couple C)
    {
     if( C.a.rex )
       label.setPos(Map(C.b));
     else
       label.setPos(Map(C.a));
    }

   static Point ArcMid(Point c,Real r,Point a,Point b)
    {
     Point p=(a+b)/2;

     Point e=Point::Ort(p-c);

     Real x=Point::Norm(p-a);
     Real x2=Sq(x);
     Real r2=Sq(r);

     Real t;

     if( r2<x2 )
       t=x2/r;
     else
       t=x2/(r+Real::Sqrt(r2-x2));

     return p+t*e;
    }

   void drawArc(const Label &label,bool selected,Point c,Real r,Point a,Point b)
    {
     if( a.rex || b.rex ) return;

     label.setPos(Map(b));

     try
       {
        Point p4=ArcMid(c,r,a,b);
        Point p2=ArcMid(c,r,a,p4);
        Point p6=ArcMid(c,r,p4,b);

        Point p1=ArcMid(c,r,a,p2);
        Point p3=ArcMid(c,r,p2,p4);
        Point p5=ArcMid(c,r,p4,p6);
        Point p7=ArcMid(c,r,p6,b);

        MPoint temp[9];

        temp[0]=Map(a);

        temp[1]=Map(p1);
        temp[2]=Map(p2);
        temp[3]=Map(p3);

        temp[4]=Map(p4);

        temp[5]=Map(p5);
        temp[6]=Map(p6);
        temp[7]=Map(p7);

        temp[8]=Map(b);

        if( label.gray && !selected )
          art.curvePath(Range(temp),width/2,gray);
        else
          art.curvePath(Range(temp),width,face);
       }
     catch(RealException)
       {
       }
    }

   void drawArc(const Label &label,bool selected,Point c,Real r,Couple A,Couple B)
    {
     if( A.rex ) return drawArc(label,selected,c,r,B);

     if( B.rex ) return drawArc(label,selected,c,r,A);

     drawArc(label,selected,c,r,A.a,B.a);
    }

   void drawArc(const Label &label,bool selected,Point c,Real r,Couple A)
    {
     if( A.rex ) return;

     drawArc(label,selected,c,r,A.a,A.b);
    }

   void testPoint(Point a)
    {
     if( a.rex ) return;

     art.ball(Map(a),Fraction(5),Red);
    }

   void testPoint(Couple C)
    {
     if( C.rex ) return;

     testPoint(C.a);
     testPoint(C.b);
    }

   // path

   struct TempPath
    {
     DynArray<SmoothDot> temp;
     bool ok=true;

     TempPath(DrawItem *obj,const Label &label,bool selected,PtrLen<const Dot> dots)
      : temp(dots.len)
      {
       for(ulen i=0; i<dots.len ;i++)
         {
          Dot dot=dots[i];

          if( !obj->test(dot.point) ) { ok=false; return; }

          MPoint p=Map(dot.point);

          if( i==0 ) label.setPos(p);

          if( label.gray && !selected )
            obj->art.ball(p,obj->width,obj->gray);
          else
            obj->art.ball(p,2*obj->width,obj->face);

          temp[i]=SmoothDot(p,dot.break_flag?Smooth::DotBreak:Smooth::DotSimple);
         }
      }

     auto get() const { return Range(temp); }
    };

  public:

   DrawItem(const SmoothDrawArt &art_,Coord dx_,Coord dy_,const Config &cfg)
    : art(art_),
      dx(dx_),
      dy(dy_),
      width(+cfg.width),
      face(+cfg.face),
      gray(+cfg.gray),

      cap_radius( 3*Max(dx,dy) ),

      A(0,0),
      B(0,dy),
      C(dx,dy),
      D(dx,0),

      P1(0,-Guard),
      P2(0,dy+Guard),
      P3(dx,-Guard),
      P4(dx,dy+Guard),

      Q1(-Guard,dy),
      Q2(dx+Guard,dy),
      Q3(-Guard,0),
      Q4(dx+Guard,0)
    {
    }

   void operator () (const Label &,bool,auto)
    {
     // do nothing
    }

   void operator () (const Label &label,bool selected,Point s)
    {
     if( !label.test() ) return;

     if( s.rex ) return;

     if( test(s) )
       {
        MPoint p=Map(s);

        if( label.gray && !selected )
          art.ball(p,width,gray);
        else
          art.ball(p,2*width,face);

        label.setPos(p);
       }
    }

   void operator () (const Label &label,bool selected,Line s)
    {
     if( !label.test() ) return;

     if( s.rex ) return;

     Point p1=SafeMeet(s,P1,P2);
     Point q1=SafeMeet(s,Q1,Q2);
     Point p2=SafeMeet(s,P3,P4);
     Point q2=SafeMeet(s,Q3,Q4);

     if( p1.rex )
       {
        if( q1.rex )
          {
           if( !p2.rex && !q2.rex ) // p2 , q2
             {
              drawLine(p2,q2,selected,label);
             }
          }
        else // q1
          {
           if( q2.rex )
             {
              if( !p2.rex ) // p2 , q1
                {
                 drawLine(p2,q1,selected,label);
                }
             }
           else // q1 , q2
             {
              drawLine(q1,q2,selected,label);
             }
          }
       }
     else // p1
       {
        if( p2.rex )
          {
           if( q1.rex )
             {
              if( !q2.rex ) // p1 , q2
                {
                 drawLine(p1,q2,selected,label);
                }
             }
           else // p1 , q1
             {
              if( q2.rex )
                {
                 drawLine(p1,q1,selected,label);
                }
              else // p1 , q1 , q2
                {
                 drawLine(q1,q2,selected,label);
                }
             }
          }
        else // p1 , p2
          {
           drawLine(p1,p2,selected,label);
          }
       }
    }

   void operator () (const Label &label,bool selected,Circle s)
    {
     if( !label.test() ) return;

     if( s.rex ) return;

     Point c=s.center;
     Real r=Real::Abs(s.radius.val);

     if( test(c) )
       {
        if( r<cap_radius )
          {
           if( label.gray && !selected )
             art.circle(Map(c),Map(r),width/2,gray);
           else
             art.circle(Map(c),Map(r),width,face);

           Couple q1=SafeMeet(s,Q1,Q2);

           if( q1.rex )
             {
              Couple q2=SafeMeet(s,Q3,Q4);

              if( q2.rex )
                {
                 Couple p1=SafeMeet(s,P1,P2);

                 if( p1.rex )
                   {
                    Couple p2=SafeMeet(s,P3,P4);

                    if( p2.rex )
                      {
                       label.setPos(Map(c+Point(0,r)));
                      }
                    else
                      {
                       SetPos(label,p2);
                      }
                   }
                 else
                   {
                    SetPos(label,p1);
                   }
                }
              else
                {
                 SetPos(label,q2);
                }
             }
           else
             {
              SetPos(label,q1);
             }
          }
       }
     else
       {
        Couple p1=SafeMeet(s,P1,P2);

        if( p1.rex )
          {
           Couple q1=SafeMeet(s,Q1,Q2);
           Couple q2=SafeMeet(s,Q3,Q4);

           if( q1.rex )
             {
              Couple p2=SafeMeet(s,P3,P4);

              drawArc(label,selected,c,r,p2,q2);
             }
           else
             {
              if( q2.rex )
                {
                 Couple p2=SafeMeet(s,P3,P4);

                 drawArc(label,selected,c,r,p2,q1);
                }
              else // q1 AND q2
                {
                 drawArc(label,selected,c,r,q1.a,q2.a);
                }
             }
          }
        else
          {
           Couple p2=SafeMeet(s,P3,P4);

           if( p2.rex )
             {
              Couple q1=SafeMeet(s,Q1,Q2);
              Couple q2=SafeMeet(s,Q3,Q4);

              if( q1.rex )
                {
                 drawArc(label,selected,c,r,p1,q2);
                }
              else
                {
                 if( q2.rex )
                   {
                    drawArc(label,selected,c,r,p1,q1);
                   }
                 else // q1 AND q2
                   {
                    drawArc(label,selected,c,r,q1.a,q2.a);
                   }
                }
             }
           else // p1 AND p2
             {
              drawArc(label,selected,c,r,p1.a,p2.a);
             }
          }
       }
    }

   void operator () (const Label &label,bool selected,Path s)
    {
     if( !label.test() ) return;

     if( s.rex ) return;

     TempPath temp(this,label,selected,Range(s.dots));

     if( !temp.ok ) return;

     if( label.gray && !selected )
       art.curvePath(temp.get(),width/2,gray);
     else
       art.curvePath(temp.get(),width,face);
    }

   void operator () (const Label &label,bool selected,Loop s)
    {
     if( !label.test() ) return;

     if( s.rex ) return;

     TempPath temp(this,label,selected,Range(s.dots));

     if( !temp.ok ) return;

     if( label.gray && !selected )
       art.curveLoop(temp.get(),width/2,gray);
     else
       art.curveLoop(temp.get(),width,face);
    }

   void operator () (const Label &label,bool selected,Solid s)
    {
     if( !label.test() ) return;

     if( s.rex ) return;

     TempPath temp(this,label,selected,Range(s.dots));

     if( !temp.ok ) return;

     if( label.gray && !selected )
       art.curveSolid(temp.get(),SolidAll,gray);
     else
       art.curveSolid(temp.get(),SolidAll,face);
    }
 };

class GeometryWindow::DrawName
 {
   SmoothDrawArt art;

   Coord dx;
   Coord dy;

   MCoord width;

   VColor text;

   Font font;

   // work

   Coord shift;

  private:

   void drawName(MPoint p,const String &name)
    {
     Point base=p.toPoint();

     if( base.x<dx/2 )
       {
        if( base.y<dy/2 )
          {
           base.addXY(shift);

           Pane pane(base.x,base.y,dx-base.x,dy-base.y);

           font->text(art.getBuf(),pane,TextPlace(AlignX_Left,AlignY_Top),Range(name),text);
          }
        else
          {
           base.addXsubY(shift);

           Pane pane(base.x,0,dx-base.x,base.y);

           font->text(art.getBuf(),pane,TextPlace(AlignX_Left,AlignY_Bottom),Range(name),text);
          }
       }
     else
       {
        if( base.y<dy/2 )
          {
           base.subXaddY(shift);

           Pane pane(0,base.y,base.x,dy-base.y);

           font->text(art.getBuf(),pane,TextPlace(AlignX_Right,AlignY_Top),Range(name),text);
          }
        else
          {
           base.subXY(shift);

           Pane pane(0,0,base.x,base.y);

           font->text(art.getBuf(),pane,TextPlace(AlignX_Right,AlignY_Bottom),Range(name),text);
          }
       }
    }

  public:

   DrawName(const SmoothDrawArt &art_,Coord dx_,Coord dy_,const Config &cfg)
    : art(art_),
      dx(dx_),
      dy(dy_),
      width(+cfg.width),
      text(+cfg.text),
      font(+cfg.font)
    {
     shift=RoundUpLen(6*width);
    }

   void operator () (const Label &,bool,auto)
    {
     // do nothing
    }

   void operator () (const Label &label,bool selected,OneOfTypes<Geometry::Point,Geometry::Line,Geometry::Circle,Geometry::Path,Geometry::Loop,Geometry::Solid>)
    {
     if( ( label.show_name || selected ) && label.pos_ok ) drawName(label.pos,label.name);
    }
 };

GeometryWindow::GeometryWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
 }

GeometryWindow::~GeometryWindow()
 {
 }

 // methods

Point GeometryWindow::getMinSize() const
 {
  return Point::Diag(+cfg.dxy);
 }

 // drawing

bool GeometryWindow::isGoodSize(Point size) const
 {
  return size>=getMinSize();
 }

void GeometryWindow::layout()
 {
  Coord s=+cfg.shade_dxy;

  Point size=getSize().subXY(s);

  pane=Pane(Null,size.x,size.y);
  shade1=Pane(s,size.y,size.x,s);
  shade2=Pane(size.x,s,s,size.y-s);
 }

void GeometryWindow::draw(DrawBuf buf,DrawParam) const
 {
  if( pane.dx<10 || pane.dy<10 ) return;

  MCoord width=+cfg.width;

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

  contour.apply(pad_ind,formula_ind,DrawItem(art,pane.dx,pane.dy,cfg));

  contour.apply(pad_ind,formula_ind,DrawName(art,pane.dx,pane.dy,cfg));

  // border

  {
   VColor vc = focus? +cfg.focus : ( hilight? +cfg.hilight : +cfg.border ) ;

   fig.loop(art,HalfPos,width,vc);
  }
 }

 // base

void GeometryWindow::open()
 {
  focus=false;
  hilight=false;
 }

 // keyboard

FocusType GeometryWindow::askFocus() const
 {
  return FocusOk;
 }

void GeometryWindow::gainFocus()
 {
  if( Change(focus,true) ) redraw();
 }

void GeometryWindow::looseFocus()
 {
  if( Change(focus,false) ) redraw();
 }

 // mouse

MouseShape GeometryWindow::getMouseShape(Point,KeyMod) const
 {
  return Mouse_Arrow;
 }

 // user input

void GeometryWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void GeometryWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_Left :
      {
       if( kmod&KeyMod_Shift )
         shift_x(-10*CountToCoord(repeat));
       else
         shift_x(-CountToCoord(repeat));
      }
     break;

     case VKey_Right :
      {
       if( kmod&KeyMod_Shift )
         shift_x(10*CountToCoord(repeat));
       else
         shift_x(CountToCoord(repeat));
      }
     break;

     case VKey_Up :
      {
       if( kmod&KeyMod_Shift )
         shift_y(-10*CountToCoord(repeat));
       else
         shift_y(-CountToCoord(repeat));
      }
     break;

     case VKey_Down :
      {
       if( kmod&KeyMod_Shift )
         shift_y(10*CountToCoord(repeat));
       else
         shift_y(CountToCoord(repeat));
      }
     break;
    }
 }

void GeometryWindow::react_LeftClick(Point point,MouseKey)
 {
  if( pane.contains(point) ) pin(point);
 }

void GeometryWindow::react_Move(Point point,MouseKey mkey)
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

void GeometryWindow::react_Leave()
 {
  if( Change(hilight,false) ) redraw();
 }

void GeometryWindow::react_Wheel(Point,MouseKey mkey,Coord delta)
 {
  if( mkey&MouseKey_Shift )
    {
     shift_x(delta);
    }
  else
    {
     shift_y(-delta);
    }
 }

} // namespace App
