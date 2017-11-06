/* DrawTools.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_video_DragTools_h
#define CCore_inc_video_DragTools_h

#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {

/* concept PointSetTypes<TT> */

template <class ... TT>
concept bool PointSetTypes = ( ... && IsType<TT,Point> ) ;

/* concept MPointSetTypes<TT> */

template <class ... TT>
concept bool MPointSetTypes = ( ... && OneOfTypes<TT,Point,MPoint> ) ;

/* concept PlotType<Plot> */

template <NothrowCopyCtorType Plot> // ref extended
concept bool PlotType = requires(Plot &obj,Point p)
 {
  obj(p);
 } ;

/* concept SmoothPlotType<SPlot> */

template <class SPlot> // ref extended
concept bool SmoothPlotType = PlotType<SPlot> && requires(SPlot &obj,Point p,unsigned alpha)
 {
  obj(p,alpha);
 } ;

/* concept HPlotType<HPlot> */

template <class HPlot> // ref extended
concept bool HPlotType = PlotType<HPlot> && requires(HPlot &obj,Coord y,Coord a,Coord b)
 {
  obj(y,a,b);
 } ;

/* concept MapType<Map> */

template <NothrowCopyCtorType Map> // ref extended
concept bool MapType = requires(Meta::ToConst<Map> &cobj,Point p)
 {
  { cobj(p) } -> Point ;
 } ;

/* enum SolidFlag */

enum SolidFlag
 {
  SolidOdd,
  SolidAll
 };

/* enum HalfFlag */

enum HalfFlag // contraclockwise
 {
  HalfPos,
  HalfNeg,
 };

/* functions */

DCoord Length(MCoord a,MCoord b);

inline DCoord Length(MPoint a) { return Length(a.x,a.y); }

inline MCoord MulDiv(DCoord a,MCoord b,MCoord c) { IntGuard( c!=0 ); return MCoord( (a*b)/c ); }

/* classes */

struct CircleSpline;

struct PaneBorder;

/* struct CircleSpline */

struct CircleSpline
 {
  Point buf[12]; // contraclockwise

  CircleSpline(Point center,Coord radius); // radius > 0

  PtrLen<const Point> get() const { return Range(buf); }
 };

/* struct PaneBorder */

struct PaneBorder
 {
  Point buf[4]; // contraclockwise

  explicit PaneBorder(Pane pane); // +pane

  Point topLeft() const { return buf[0]; }

  Point bottomLeft() const { return buf[1]; }

  Point bottomRight() const { return buf[2]; }

  Point topRight() const { return buf[3]; }

  PtrLen<const Point> get() const { return Range(buf); }
 };

} // namespace Video
} // namespace CCore

#endif


