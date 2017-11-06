/* SpecialDrawArt.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/test/SpecialDrawArt.h>

#include <CCore/inc/video/DrawAlgo.h>

namespace App {

/* class SpecialDrawArt */

 // simple

void SpecialDrawArt::erase(DesktopColor color)
 {
  buf.erase(color);
 }

void SpecialDrawArt::block(Pane pane,DesktopColor color)
 {
  buf.erase(pane,color);
 }

void SpecialDrawArt::block(Pane pane,Blender blender)
 {
  buf.erase(pane,blender);
 }

void SpecialDrawArt::lineX(Coord x,Coord y,Coord len,DesktopColor line)
 {
  block(Pane(x,y,len,1),line);
 }

void SpecialDrawArt::lineY(Coord x,Coord y,Coord len,DesktopColor line)
 {
  block(Pane(x,y,1,len),line);
 }

 // special

void SpecialDrawArt::grid(Coord cell,DesktopColor back,DesktopColor line)
 {
  erase(back);

  for(Coord x=cell/2; x<size.x ;x+=cell) lineY(x,0,size.y,line);

  for(Coord y=cell/2; y<size.y ;y+=cell) lineX(0,y,size.x,line);
 }

void SpecialDrawArt::gridCell(Point p,DesktopColor color,Coord magnify)
 {
  if( p>=Null && p<size/magnify )
    knob(p*magnify,magnify/2-1,color);
 }

void SpecialDrawArt::gridCell(Point p,Blender blender,Coord magnify)
 {
  if( p>=Null && p<size/magnify )
    knob(p*magnify,magnify/2-1,blender);
 }

void SpecialDrawArt::circle_micro(Point center,Coord radius,DesktopColor color,Point focus,Coord magnify)
 {
  focus.y-=size.y/magnify;

  DrawAlgo::Circle(center-focus,radius,HPlot(this,color,magnify));
 }

void SpecialDrawArt::curvePath_micro(PtrLen<const Point> dots,DesktopColor color,Point focus,Coord magnify)
 {
  focus.y-=size.y/magnify;

  if( dots.len>=3 )
    {
     DrawAlgo::CurvePath(dots,PointMap(-focus),HPlot(this,color,magnify));
    }
  else
    {
     // skip
    }
 }

void SpecialDrawArt::path_smooth_micro(PtrLen<const Point> dots,VColor vc,Point focus,Coord magnify)
 {
  focus.y-=size.y/magnify;

  SPlot plot(this,vc,magnify);

  if( +dots )
    {
     Point a=(*dots)-focus;

     for(++dots; +dots ;++dots)
       {
        Point b=(*dots)-focus;

        DrawAlgo::LineSmooth(a,b,plot);

        a=b;
       }

     plot(a);
    }
 }

void SpecialDrawArt::curvePath_smooth_micro(PtrLen<const Point> dots,VColor vc,Point focus,Coord magnify)
 {
  focus.y-=size.y/magnify;

  if( dots.len>=3 )
    {
     DrawAlgo::CurvePathSmooth(dots,PointMap(-focus),SPlot(this,vc,magnify));
    }
  else
    {
     // skip
    }
 }

} // namespace App

