/* SpecialDrawArt.h */
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

#ifndef CCore_test_SpecialDrawArt_h
#define CCore_test_SpecialDrawArt_h

#include <CCore/inc/video/CommonDrawArt.h>

namespace App {

/* using */

using namespace CCore;
using namespace Video;

/* classes */

class SpecialDrawArt;

/* class SpecialDrawArt */

class SpecialDrawArt
 {
   DrawBuf buf;
   Point size;

   class HPlot
    {
      SpecialDrawArt *obj;
      DesktopColor color;
      Coord magnify;

     public:

      HPlot(SpecialDrawArt *obj_,DesktopColor color_,Coord magnify_) : obj(obj_),color(color_),magnify(magnify_) {}

      void operator () (Point p)
       {
        obj->gridCell(p,color,magnify);
       }
    };

   class SPlot
    {
      SpecialDrawArt *obj;
      VColor vc;
      Coord magnify;

     public:

      SPlot(SpecialDrawArt *obj_,VColor vc_,Coord magnify_) : obj(obj_),vc(vc_),magnify(magnify_) {}

      void operator () (Point p)
       {
        obj->gridCell(p,vc,magnify);
       }

      void operator () (Point p,unsigned alpha)
       {
        if( !alpha ) return;

        if( alpha>=AlphaLim )
          obj->gridCell(p,vc,magnify);
        else
          obj->gridCell(p,Blender(Clr(alpha),vc),magnify);
       }
    };

  public:

   SpecialDrawArt(const DrawBuf &buf_,Point size_) : buf(buf_),size(size_) {}

   // simple

   void erase(DesktopColor color);

   void block(Pane pane,DesktopColor color);

   void block(Pane pane,Blender blender);

   void knob(Point p,Coord len,DesktopColor color)
    {
     Coord d=Coord( 2*len+1 );

     block(Pane(p.x-len,p.y-len,d,d),color);
    }

   void knob(Point p,Coord len,Blender blender)
    {
     Coord d=Coord( 2*len+1 );

     block(Pane(p.x-len,p.y-len,d,d),blender);
    }

   void lineX(Coord x,Coord y,Coord len,DesktopColor line);

   void lineY(Coord x,Coord y,Coord len,DesktopColor line);

   // special

   void grid(Coord cell,DesktopColor back,DesktopColor line);

   void gridCell(Point p,DesktopColor color,Coord magnify);

   void gridCell(Point p,Blender blender,Coord magnify);

   void circle_micro(Point center,Coord radius,DesktopColor color,Point focus,Coord magnify);

   void curvePath_micro(PtrLen<const Point> dots,DesktopColor color,Point focus,Coord magnify);

   void path_smooth_micro(PtrLen<const Point> dots,VColor vc,Point focus,Coord magnify);

   void curvePath_smooth_micro(PtrLen<const Point> dots,VColor vc,Point focus,Coord magnify);
 };

} // namespace App

#endif
