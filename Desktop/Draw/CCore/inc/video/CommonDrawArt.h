/* CommonDrawArt.h */
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

#ifndef CCore_inc_video_CommonDrawArt_h
#define CCore_inc_video_CommonDrawArt_h

#include <CCore/inc/video/DrawTools.h>
#include <CCore/inc/video/DrawBuf.h>

#include <CCore/inc/Swap.h>

namespace CCore {
namespace Video {

/* concept RawPlotType<Plot> */

template <NothrowCopyableType Plot> // ref extended
concept bool RawPlotType = requires(Plot &obj,DesktopColor::Raw *ptr)
 {
  obj(ptr);
 } ;

/* classes */

class CommonDrawArt;

/* class CommonDrawArt */

class CommonDrawArt
 {
   class SPlot : public FrameBuf<DesktopColor>
    {
      VColor vc;

     public:

      SPlot(const FrameBuf<DesktopColor> &buf,VColor vc_) : FrameBuf<DesktopColor>(buf),vc(vc_) {}

      void operator () (Point p) { pixel_safe(p,vc); }

      void operator () (Point p,unsigned alpha)
       {
        if( !alpha ) return;

        if( p>=Null && p<getSize() )
          {
           if( alpha>=AlphaLim )
             pixel_unsafe(p,vc);
           else
             DesktopColor::BlendTo(Blender(Clr(alpha),vc),place(p));
          }
       }
    };

   class HPlot : public FrameBuf<DesktopColor>
    {
      DesktopColor color;

     public:

      HPlot(const FrameBuf<DesktopColor> &buf,DesktopColor color_) : FrameBuf<DesktopColor>(buf),color(color_) {}

      void operator () (Point p) { pixel_safe(p,color); }

      void operator () (Coord y,Coord a,Coord b) // [a,b] unordered
       {
        if( y<0 || y>=dy ) return;

        if( a>b ) Swap(a,b);

        if( a<0 ) a=0;

        if( b>=dx ) b=dx-1;

        if( a>b ) return;

        Raw *ptr=place(Point(a,y));

        for(; a<b ;a++,ptr=NextX(ptr)) color.copyTo(ptr);

        color.copyTo(ptr);
       }
    };

   class WorkBuf : public FrameBuf<DesktopColor>
    {
      static void Prepare(Coord &a,Coord &b,Coord d);

     public:

      explicit WorkBuf(const FrameBuf<DesktopColor> &buf) : FrameBuf<DesktopColor>(buf) {}

      void lineY(Coord abx,Coord ay,Coord by,RawPlotType plot); // [a,b) , plot(Raw *ptr)

      void lineX(Coord aby,Coord ax,Coord bx,RawPlotType plot); // [a,b) , plot(Raw *ptr)

      void line(Point a,Point b,RawPlotType plot); // [a,b) , plot(Raw *ptr)

      void lineY(Coord abx,Coord ay,Coord by,DesktopColor color); // [a,b)

      void lineX(Coord aby,Coord ax,Coord bx,DesktopColor color); // [a,b)

      void line(Point a,Point b,DesktopColor color); // [a,b)

      void line_smooth(Point a,Point b,VColor vc); // [a,b)
    };

   WorkBuf buf;
   PointMap map;

  public:

   explicit CommonDrawArt(const DrawBuf &buf);

   DrawBuf getBuf() const { return DrawBuf(buf,map.getOrigin()); }

   // simple

   void pixel(Point p,DesktopColor color);

   void erase(DesktopColor color);

   void block(Pane pane,DesktopColor color);

   void knob(Point p,Coord len,DesktopColor color)
    {
     IntGuard( len<=(MaxCoord-1)/2 );

     Coord d=Coord( 2*len+1 );

     block(Pane(p.subXY(len),d),color);
    }

   // path

   void path(PtrLen<const Point> dots,DesktopColor color);

   template <class ... TT>
   void path(DesktopColor color,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     path(Range_const(temp),color);
    }

   void loop(PtrLen<const Point> dots,DesktopColor color);

   template <class ... TT>
   void loop(DesktopColor color,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     loop(Range_const(temp),color);
    }

   void curvePath(PtrLen<const Point> dots,DesktopColor color);

   template <class ... TT>
   void curvePath(DesktopColor color,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     curvePath(Range_const(temp),color);
    }

   void curveLoop(PtrLen<const Point> dots,DesktopColor color);

   template <class ... TT>
   void curveLoop(DesktopColor color,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     curveLoop(Range_const(temp),color);
    }

   // path smooth

   void path_smooth(PtrLen<const Point> dots,VColor vc);

   template <class ... TT>
   void path_smooth(VColor vc,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     path_smooth(Range_const(temp),vc);
    }

   void loop_smooth(PtrLen<const Point> dots,VColor vc);

   template <class ... TT>
   void loop_smooth(VColor vc,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     loop_smooth(Range_const(temp),vc);
    }

   void curvePath_smooth(PtrLen<const Point> dots,VColor vc);

   template <class ... TT>
   void curvePath_smooth(VColor vc,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     curvePath_smooth(Range_const(temp),vc);
    }

   void curveLoop_smooth(PtrLen<const Point> dots,VColor vc);

   template <class ... TT>
   void curveLoop_smooth(VColor vc,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     curveLoop_smooth(Range_const(temp),vc);
    }

   // solid

   void solid(PtrLen<const Point> dots,SolidFlag flag,DesktopColor color);

   template <class ... TT>
   void solid(SolidFlag flag,DesktopColor color,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     solid(Range_const(temp),flag,color);
    }

   void curveSolid(PtrLen<const Point> dots,SolidFlag flag,DesktopColor color);

   template <class ... TT>
   void curveSolid(SolidFlag flag,DesktopColor color,TT ... tt) requires ( PointSetTypes<TT...> )
    {
     Point temp[sizeof ... (TT)]={ tt... };

     curveSolid(Range_const(temp),flag,color);
    }

   // circle

   void ball(Point center,Coord radius,DesktopColor color);

   void ballSpline(Point center,Coord radius,DesktopColor color);

   void circle(Point center,Coord radius,DesktopColor color);

   void circleSpline(Point center,Coord radius,DesktopColor color);

   void circleSpline_smooth(Point center,Coord radius,VColor vc);
 };

} // namespace Video
} // namespace CCore

#endif


