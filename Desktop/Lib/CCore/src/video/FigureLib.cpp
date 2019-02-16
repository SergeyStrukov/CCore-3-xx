/* FigureLib.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/video/DrawTools.h>

namespace CCore {
namespace Video {

/* struct DrawPoints */

void DrawPoints::Path(SmoothDrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  art.path(dots,width,vc);
 }

void DrawPoints::Loop(SmoothDrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  art.loop(dots,width,vc);
 }

void DrawPoints::Path(SmoothDrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  art.path(dots,half_flag,width,vc);
 }

void DrawPoints::Loop(SmoothDrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  art.loop(dots,half_flag,width,vc);
 }

void DrawPoints::Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor vc)
 {
  art.solid(dots,solid_flag,vc);
 }

void DrawPoints::Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const TwoField &field)
 {
  art.solid(dots,solid_flag,field);
 }

void DrawPoints::Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const RadioField &field)
 {
  art.solid(dots,solid_flag,field);
 }

void DrawPoints::Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractField &field)
 {
  art.solid(dots,solid_flag,field);
 }

void DrawPoints::Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractAlphaField &field)
 {
  art.solid(dots,solid_flag,field);
 }

void DrawPoints::CurvePath(SmoothDrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  art.curvePath(dots,width,vc);
 }

void DrawPoints::CurveLoop(SmoothDrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor vc)
 {
  art.curveLoop(dots,width,vc);
 }

void DrawPoints::CurvePath(SmoothDrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  art.curvePath(dots,half_flag,width,vc);
 }

void DrawPoints::CurveLoop(SmoothDrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  art.curveLoop(dots,half_flag,width,vc);
 }

void DrawPoints::CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor vc)
 {
  art.curveSolid(dots,solid_flag,vc);
 }

void DrawPoints::CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const TwoField &field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

void DrawPoints::CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const RadioField &field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

void DrawPoints::CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractField &field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

void DrawPoints::CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractAlphaField &field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

/* struct DrawDots */

void DrawDots::CurvePath(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,MCoord width,VColor vc)
 {
  art.curvePath(dots,width,vc);
 }

void DrawDots::CurveLoop(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,MCoord width,VColor vc)
 {
  art.curveLoop(dots,width,vc);
 }

void DrawDots::CurvePath(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  art.curvePath(dots,half_flag,width,vc);
 }

void DrawDots::CurveLoop(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,HalfFlag half_flag,MCoord width,VColor vc)
 {
  art.curveLoop(dots,half_flag,width,vc);
 }

void DrawDots::CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,VColor vc)
 {
  art.curveSolid(dots,solid_flag,vc);
 }

void DrawDots::CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,const TwoField &field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

void DrawDots::CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,const RadioField &field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

void DrawDots::CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,const AbstractField &field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

void DrawDots::CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,const AbstractAlphaField &field)
 {
  art.curveSolid(dots,solid_flag,field);
 }

/* struct FigureBox */

FigureBox::FigureBox(MCoord x0,MCoord x1,MCoord y0,MCoord y1)
 {
  buf[0]={x0,y0};
  buf[1]={x0,y1};
  buf[2]={x1,y1};
  buf[3]={x1,y0};
 }

/* struct FigureSkew */

FigureSkew::FigureSkew(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord skew)
 {
  buf[0]={x0+skew,y0};
  buf[1]={x0,y1};
  buf[2]={x1,y1};
  buf[3]={x1+skew,y0};
 }

/* struct FigureTopLeftArrow */

FigureTopLeftArrow::FigureTopLeftArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1)
 {
  buf[0]={x0,y0};
  buf[1]={x0,y1};
  buf[2]={x1,y0};
 }

/* struct FigureBottomLeftArrow */

FigureBottomLeftArrow::FigureBottomLeftArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1)
 {
  buf[0]={x0,y1};
  buf[1]={x1,y1};
  buf[2]={x0,y0};
 }

/* struct FigureTopRightArrow */

FigureTopRightArrow::FigureTopRightArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1)
 {
  buf[0]={x1,y0};
  buf[1]={x0,y0};
  buf[2]={x1,y1};
 }

/* struct FigureBottomRightArrow */

FigureBottomRightArrow::FigureBottomRightArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1)
 {
  buf[0]={x1,y1};
  buf[1]={x1,y0};
  buf[2]={x0,y1};
 }

/* struct FigureTopBorder */

FigureTopBorder::FigureTopBorder(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord w)
 {
  buf[0]={x0,y0};
  buf[1]={x0,y1};
  buf[2]={x0+w,y1-w};
  buf[3]={x0+w,y0+w};
  buf[4]={x1-w,y0+w};
  buf[5]={x1,y0};
 }

FigurePoints<6> FigureTopBorder::getLeftCut(MCoord t) const
 {
  FigurePoints<6> ret(buf,0,1,2,3,4,5);

  ret.buf[4].x=t;
  ret.buf[5].x=t;

  return ret;
 }

FigurePoints<4> FigureTopBorder::getRightCut(MCoord t) const
 {
  FigurePoints<4> ret(buf,4,5,5,4);

  ret.buf[2].x=t;
  ret.buf[3].x=t;

  return ret;
 }

/* struct FigureBottomBorder */

FigureBottomBorder::FigureBottomBorder(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord w)
 {
  buf[0]={x0,y1};
  buf[1]={x1,y1};
  buf[2]={x1,y0};
  buf[3]={x1-w,y0+w};
  buf[4]={x1-w,y1-w};
  buf[5]={x0+w,y1-w};
 }

/* struct FigureButton */

FigureButton::FigureButton(MCoord x0,MCoord x5,MCoord y0,MCoord y4,MCoord ex)
 {
  MCoord dy=y4-y0;

  MCoord ey=Ratio(200,10)*dy;

  MCoord y1=y0+ey;
  MCoord y2=y0+dy/2;
  MCoord y3=y4-ey;

  MCoord fx=ex/3;

  MCoord x1=x0+fx;
  MCoord x2=x0+ex;
  MCoord x3=x5-ex;
  MCoord x4=x5-fx;

  buf[0]=SmoothBreakDot{x2,y0};
  buf[1]={x1,y1};
  buf[2]={x0,y2};
  buf[3]={x1,y3};
  buf[4]=SmoothBreakDot{x2,y4};

  buf[5]=SmoothBreakDot{x3,y4};
  buf[6]={x4,y3};
  buf[7]={x5,y2};
  buf[8]={x4,y1};
  buf[9]=SmoothBreakDot{x3,y0};
 }

FigureDots<6> FigureButton::getTop() const
 {
  FigureDots<6> ret(buf,9,0,1,2,3,4);

  return ret;
 }

FigureDots<6> FigureButton::getBottom() const
 {
  FigureDots<6> ret(buf,4,5,6,7,8,9);

  return ret;
 }

/* struct FigureAsterisk */

FigureAsterisk::FigureAsterisk(MPoint center,MCoord radius)
 {
  MCoord a=radius/14;
  MCoord b=3*a;
  MCoord c=11*a;
  MCoord d=radius;

  buf[0]={-a,b};
  buf[1]={-b,c};
  buf[2]={0,d};
  buf[3]={b,c};
  buf[4]={a,b};

  Smooth::Rotate rotate(MPoint(1024,-1774));

  for(unsigned i=0; i<25 ;i++) buf[i+5]=rotate(buf[i]);

  for(unsigned i=0; i<30 ;i++) buf[i]+=center;
 }

/* struct ShrinkArrowDelta */

ShrinkArrowDelta::ShrinkArrowDelta(MCoord h,MCoord l,MCoord width)
 {
  DCoord L=Length(h,l);

  if( h>0 && l>0 )
    {
     a=MulDiv(L,width,h);
     b=MulDiv(h+l/2,width,h);
     c=h-MulDiv(l-a-b,h,l);
    }
  else
    {
     a=0;
     b=0;
     c=0;
    }
 }

/* struct FigureLeftArrow */

FigureLeftArrow::FigureLeftArrow(MCoord x0,MCoord x2,MCoord y0,MCoord y2)
 {
  MCoord x1=x2-(x2-x0)/6;
  MCoord y1=y0+(y2-y0)/2;

  buf[0]=SmoothBreakDot{x2,y0};
  buf[1]=SmoothBreakDot{x0,y1};
  buf[2]=SmoothBreakDot{x2,y2};
  buf[3]={x1,y1};
 }

FigureLeftArrow FigureLeftArrow::shrink(MCoord width) const
 {
  FigureLeftArrow ret(*this);

  MCoord h=(buf[2].point.y-buf[0].point.y)/2;
  MCoord l=buf[0].point.x-buf[1].point.x;

  ShrinkArrowDelta delta(h,l,width);

  ret[1].point.x+=delta.a;
  ret[3].point.x-=width;

  ret[0].point.x-=delta.b;
  ret[2].point.x-=delta.b;

  ret[0].point.y+=delta.c;
  ret[2].point.y-=delta.c;

  return ret;
 }

FigureDots<10> FigureLeftArrow::border(MCoord width) const
 {
  FigureLeftArrow inner=shrink(width);

  FigureDots<10> ret(buf,1,2,3,0,1);

  ret.set(5,inner,1,0,3,2,1);

  return ret;
 }

/* struct FigureRightArrow */

FigureRightArrow::FigureRightArrow(MCoord x0,MCoord x2,MCoord y0,MCoord y2)
 {
  MCoord x1=x0+(x2-x0)/6;
  MCoord y1=y0+(y2-y0)/2;

  buf[0]=SmoothBreakDot{x0,y2};
  buf[1]=SmoothBreakDot{x2,y1};
  buf[2]=SmoothBreakDot{x0,y0};
  buf[3]={x1,y1};
 }

FigureRightArrow FigureRightArrow::shrink(MCoord width) const
 {
  FigureRightArrow ret(*this);

  MCoord h=(buf[0].point.y-buf[2].point.y)/2;
  MCoord l=buf[1].point.x-buf[0].point.x;

  ShrinkArrowDelta delta(h,l,width);

  ret[1].point.x-=delta.a;
  ret[3].point.x+=width;

  ret[0].point.x+=delta.b;
  ret[2].point.x+=delta.b;

  ret[0].point.y-=delta.c;
  ret[2].point.y+=delta.c;

  return ret;
 }

FigureDots<10> FigureRightArrow::border(MCoord width) const
 {
  FigureRightArrow inner=shrink(width);

  FigureDots<10> ret(buf,1,2,3,0,1);

  ret.set(5,inner,1,0,3,2,1);

  return ret;
 }

/* struct FigureUpArrow */

FigureUpArrow::FigureUpArrow(MCoord x0,MCoord x2,MCoord y0,MCoord y2)
 {
  MCoord x1=x0+(x2-x0)/2;
  MCoord y1=y2-(y2-y0)/6;

  buf[0]=SmoothBreakDot{x2,y2};
  buf[1]=SmoothBreakDot{x1,y0};
  buf[2]=SmoothBreakDot{x0,y2};
  buf[3]={x1,y1};
 }

FigureUpArrow FigureUpArrow::shrink(MCoord width) const
 {
  FigureUpArrow ret(*this);

  MCoord h=(buf[0].point.x-buf[2].point.x)/2;
  MCoord l=buf[0].point.y-buf[1].point.y;

  ShrinkArrowDelta delta(h,l,width);

  ret[1].point.y+=delta.a;
  ret[3].point.y-=width;

  ret[0].point.y-=delta.b;
  ret[2].point.y-=delta.b;

  ret[0].point.x-=delta.c;
  ret[2].point.x+=delta.c;

  return ret;
 }

FigureDots<10> FigureUpArrow::border(MCoord width) const
 {
  FigureUpArrow inner=shrink(width);

  FigureDots<10> ret(buf,1,2,3,0,1);

  ret.set(5,inner,1,0,3,2,1);

  return ret;
 }

/* struct FigureDownArrow */

FigureDownArrow::FigureDownArrow(MCoord x0,MCoord x2,MCoord y0,MCoord y2)
 {
  MCoord x1=x0+(x2-x0)/2;
  MCoord y1=y0+(y2-y0)/6;

  buf[0]=SmoothBreakDot{x0,y0};
  buf[1]=SmoothBreakDot{x1,y2};
  buf[2]=SmoothBreakDot{x2,y0};
  buf[3]={x1,y1};
 }

FigureDownArrow FigureDownArrow::shrink(MCoord width) const
 {
  FigureDownArrow ret(*this);

  MCoord h=(buf[2].point.x-buf[0].point.x)/2;
  MCoord l=buf[1].point.y-buf[0].point.y;

  ShrinkArrowDelta delta(h,l,width);

  ret[1].point.y-=delta.a;
  ret[3].point.y+=width;

  ret[0].point.y+=delta.b;
  ret[2].point.y+=delta.b;

  ret[0].point.x+=delta.c;
  ret[2].point.x-=delta.c;

  return ret;
 }

FigureDots<10> FigureDownArrow::border(MCoord width) const
 {
  FigureDownArrow inner=shrink(width);

  FigureDots<10> ret(buf,1,2,3,0,1);

  ret.set(5,inner,1,0,3,2,1);

  return ret;
 }

/* struct FigureLeftMark */

FigureLeftMark::FigureLeftMark(MCoord x,MCoord y,MCoord len)
 {
  buf[0]={x,y};
  buf[1]={x+len,y+len};
  buf[2]={x+len,y-len};
 }

/* struct FigureRightMark */

FigureRightMark::FigureRightMark(MCoord x,MCoord y,MCoord len)
 {
  buf[0]={x,y};
  buf[1]={x-len,y-len};
  buf[2]={x-len,y+len};
 }

/* struct FigureUpMark */

FigureUpMark::FigureUpMark(MCoord x,MCoord y,MCoord len)
 {
  buf[0]={x,y};
  buf[1]={x-len,y+len};
  buf[2]={x+len,y+len};
 }

/* struct FigureDownMark */

FigureDownMark::FigureDownMark(MCoord x,MCoord y,MCoord len)
 {
  buf[0]={x,y};
  buf[1]={x+len,y-len};
  buf[2]={x-len,y-len};
 }

/* struct FigureRoundBox */

FigureRoundBox::FigureRoundBox(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord r)
 {
  MCoord dx1=Ratio(16962,16)*r;
  MCoord dy1=Ratio(63303,16)*r;

  MCoord dx2=r/2;
  MCoord dy2=Ratio(56756,16)*r;

  MCoord dx3=Ratio(46341,16)*r;
  MCoord dy3=dx3;

  MCoord dx4=dy2;
  MCoord dy4=dx2;

  MCoord dx5=dy1;
  MCoord dy5=dx1;

  buf[0]=SmoothBreakDot{x0,y0+r};
  buf[1]=SmoothBreakDot{x0,y1-r};

  MCoord cx=x0+r;
  MCoord cy=y1-r;

  buf[2]={cx-dy1,cy+dx1};
  buf[3]={cx-dy2,cy+dx2};
  buf[4]={cx-dy3,cy+dx3};
  buf[5]={cx-dy4,cy+dx4};
  buf[6]={cx-dy5,cy+dx5};

  buf[7]=SmoothBreakDot{x0+r,y1};
  buf[8]=SmoothBreakDot{x1-r,y1};

  cx=x1-r;
  cy=y1-r;

  buf[9]={cx+dx1,cy+dy1};
  buf[10]={cx+dx2,cy+dy2};
  buf[11]={cx+dx3,cy+dy3};
  buf[12]={cx+dx4,cy+dy4};
  buf[13]={cx+dx5,cy+dy5};

  buf[14]=SmoothBreakDot{x1,y1-r};
  buf[15]=SmoothBreakDot{x1,y0+r};

  cx=x1-r;
  cy=y0+r;

  buf[16]={cx+dy1,cy-dx1};
  buf[17]={cx+dy2,cy-dx2};
  buf[18]={cx+dy3,cy-dx3};
  buf[19]={cx+dy4,cy-dx4};
  buf[20]={cx+dy5,cy-dx5};

  buf[21]=SmoothBreakDot{x1-r,y0};
  buf[22]=SmoothBreakDot{x0+r,y0};

  cx=x0+r;
  cy=y0+r;

  buf[23]={cx-dx1,cy-dy1};
  buf[24]={cx-dx2,cy-dy2};
  buf[25]={cx-dx3,cy-dy3};
  buf[26]={cx-dx4,cy-dy4};
  buf[27]={cx-dx5,cy-dy5};
 }

/* struct FigureCursor */

FigureCursor::FigureCursor(MCoord x0,MCoord y0,MCoord y1,MCoord width,MCoord skew)
 {
  MCoord b0=x0;
  MCoord b1=b0+width;

  MCoord a0=b0+skew;
  MCoord a1=a0+width;

  buf[0]={a1,y0};
  buf[1]={a1+width,y0};
  buf[2]={a1+width,y0-width};
  buf[3]={a0-width,y0-width};
  buf[4]={a0-width,y0};
  buf[5]={a0,y0};

  buf[6]={b0,y1};
  buf[7]={b0-width,y1};
  buf[8]={b0-width,y1+width};
  buf[9]={b1+width,y1+width};
  buf[10]={b1+width,y1};
  buf[11]={b1,y1};
 }

/* class PolyFigureExclamation */

PolyFigureExclamation::PolyFigureExclamation(MCoord x,MCoord y,MCoord h)
 {
  MCoord c=h/6;
  MCoord b=4*c+c/2;

  r=Ratio(3,2)*c;

  o={x,y+b+r};

  fig[0]={x-c,y+c};
  fig[1]={x,y};
  fig[2]={x+c,y+c};
  fig[3]=SmoothBreakDot{x,y+b};
 }

/* class PolyFigureQuestion */

PolyFigureQuestion::PolyFigureQuestion(MCoord x,MCoord y,MCoord h)
 {
  MCoord c=h/6;
  MCoord b=4*c+c/2;

  r=Ratio(3,2)*c;

  o={x,y+b+r};

  MPoint E(x,y+b);

  static const SmoothDot Contour[30]=
   {
    {{284672,523264},Smooth::DotBreak},
    {{293888,468992},Smooth::DotSimple},
    {{339968,432128},Smooth::DotSimple},
    {{419840,391168},Smooth::DotSimple},
    {{473088,334848},Smooth::DotSimple},
    {{492544,254976},Smooth::DotSimple},
    {{477184,182272},Smooth::DotSimple},
    {{432128,120832},Smooth::DotSimple},
    {{379904,86016},Smooth::DotSimple},
    {{332800,67584},Smooth::DotSimple},
    {{284672,63488},Smooth::DotSimple},
    {{214016,73728},Smooth::DotSimple},
    {{139264,119808},Smooth::DotSimple},
    {{94208,179200},Smooth::DotSimple},
    {{84992,224256},Smooth::DotSimple},
    {{100352,256000},Smooth::DotSimple},
    {{131072,269312},Smooth::DotSimple},
    {{163840,262144},Smooth::DotSimple},
    {{182272,239616},Smooth::DotSimple},
    {{195584,207872},Smooth::DotSimple},
    {{216064,184320},Smooth::DotSimple},
    {{250880,166912},Smooth::DotSimple},
    {{303104,162816},Smooth::DotSimple},
    {{359424,189440},Smooth::DotSimple},
    {{393216,237568},Smooth::DotSimple},
    {{399360,299008},Smooth::DotSimple},
    {{369664,356352},Smooth::DotSimple},
    {{323584,388096},Smooth::DotSimple},
    {{278528,422912},Smooth::DotSimple},
    {{267264,472064},Smooth::DotSimple}
   };

  Ratio A=Div(h,Fraction(600));

  MPoint B=E-A*Contour[0].point;

  fig.copy(Contour);

  fig.transformPoint( [A,B] (MPoint point) -> MPoint { return A*point+B; } );
 }

/* class FigureReload */

FigureReload::FigureReload(MCoord x,MCoord y,MCoord h)
 {
  static const SmoothDot Contour[37]=
   {
    { { 450560 , 325632 } , Smooth::DotBreak },
    { { 447253 , 347926 } , Smooth::DotSimple },
    { { 437617 , 368300 } , Smooth::DotSimple },
    { { 422481 , 384999 } , Smooth::DotSimple },
    { { 403150 , 396586 } , Smooth::DotSimple },
    { { 381288 , 402062 } , Smooth::DotSimple },
    { { 358777 , 400956 } , Smooth::DotSimple },
    { { 337557 , 393364 } , Smooth::DotSimple },
    { { 319454 , 379938 } , Smooth::DotSimple },
    { { 306028 , 361835 } , Smooth::DotSimple },
    { { 298436 , 340615 } , Smooth::DotSimple },
    { { 297330 , 318104 } , Smooth::DotSimple },
    { { 302806 , 296242 } , Smooth::DotSimple },
    { { 314393 , 276911 } , Smooth::DotSimple },
    { { 331092 , 261775 } , Smooth::DotSimple },
    { { 351466 , 252139 } , Smooth::DotSimple },
    { { 373760 , 248832 } , Smooth::DotBreak },
    { { 373760 , 293205 } , Smooth::DotBreak },
    { { 451413 , 215552 } , Smooth::DotBreak },
    { { 373760 , 137899 } , Smooth::DotBreak },
    { { 373760 , 182272 } , Smooth::DotBreak },
    { { 332145 , 188445 } , Smooth::DotSimple },
    { { 294113 , 206433 } , Smooth::DotSimple },
    { { 262941 , 234685 } , Smooth::DotSimple },
    { { 241313 , 270771 } , Smooth::DotSimple },
    { { 231090 , 311580 } , Smooth::DotSimple },
    { { 233155 , 353600 } , Smooth::DotSimple },
    { { 247328 , 393211 } , Smooth::DotSimple },
    { { 272389 , 427003 } , Smooth::DotSimple },
    { { 306181 , 452064 } , Smooth::DotSimple },
    { { 345792 , 466237 } , Smooth::DotSimple },
    { { 387812 , 468302 } , Smooth::DotSimple },
    { { 428621 , 458079 } , Smooth::DotSimple },
    { { 464707 , 436451 } , Smooth::DotSimple },
    { { 492959 , 405279 } , Smooth::DotSimple },
    { { 510947 , 367247 } , Smooth::DotSimple },
    { { 517120 , 325632 } , Smooth::DotBreak }
   };

  copy(Contour);

  Anchor from({373760,325632},{0,137899});
  Anchor to({x,y},h);

  transformPoint(AnchorMap(from,to));
 }

/* class FigureLove */

FigureLove::FigureLove(MCoord x,MCoord y,MCoord h)
 {
  static const SmoothDot Contour[14]=
   {
    { { 490496 , 192512 } , Smooth::DotBreak },
    { { 436224 , 156672 } , Smooth::DotSimple },
    { { 350208 , 165888 } , Smooth::DotSimple },
    { { 303104 , 226304 } , Smooth::DotSimple },
    { { 307200 , 309248 } , Smooth::DotSimple },
    { { 367616 , 392192 } , Smooth::DotSimple },
    { { 431104 , 451584 } , Smooth::DotSimple },
    { { 490496 , 537600 } , Smooth::DotBreak },
    { { 549888 , 451584 } , Smooth::DotSimple },
    { { 613376 , 392192 } , Smooth::DotSimple },
    { { 673792 , 309248 } , Smooth::DotSimple },
    { { 677888 , 226304 } , Smooth::DotSimple },
    { { 630784 , 165888 } , Smooth::DotSimple },
    { { 544768 , 156672 } , Smooth::DotSimple }
   };

  copy(Contour);

  Anchor from({490496,340992},{490496,105984});
  Anchor to({x,y},h);

  transformPoint(AnchorMap(from,to));
 }

} // namespace Video
} // namespace CCore


