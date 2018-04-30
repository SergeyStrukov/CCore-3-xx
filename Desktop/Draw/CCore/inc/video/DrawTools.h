/* DrawTools.h */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_DragTools_h
#define CCore_inc_video_DragTools_h

#include <CCore/inc/video/MPoint.h>

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

} // namespace Video
} // namespace CCore

#endif


