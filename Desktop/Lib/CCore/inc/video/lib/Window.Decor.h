/* Window.Decor.h */
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

#ifndef CCore_inc_video_lib_Decor_h
#define CCore_inc_video_lib_Decor_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Line.h>
#include <CCore/inc/video/lib/Shape.Contour.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class DecorWindowOf;

/* class DecorWindowOf<Shape> */

template <class Shape>
class DecorWindowOf : public SubWindow
 {
   Shape shape;

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   DecorWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~DecorWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   Point getMinSize(Point inner_size) const { return shape.getMinSize(inner_size); }

   Pane getInner() const { return shape.getInner()+getPlace().getBase(); } // owner coordinates

   Point getCap(Point cap) const { return shape.getCap(cap); }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout()
    {
     shape.pane=getPane();
    }

   virtual void draw(DrawBuf buf,DrawParam draw_param) const
    {
     shape.draw(buf,draw_param);
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return NoFocus;
    }
 };

/* type XSingleLineWindow */

using XSingleLineWindow = DecorWindowOf<XSingleLineShape> ;

/* type YSingleLineWindow */

using YSingleLineWindow = DecorWindowOf<YSingleLineShape> ;

/* type XDoubleLineWindow */

using XDoubleLineWindow = DecorWindowOf<XDoubleLineShape> ;

/* type YDoubleLineWindow */

using YDoubleLineWindow = DecorWindowOf<YDoubleLineShape> ;

/* type ContourWindow */

using ContourWindow = DecorWindowOf<ContourShape> ;

/* type TextContourWindow */

using TextContourWindow = DecorWindowOf<TextContourShape> ;

/* type RefTextContourWindow */

using RefTextContourWindow = DecorWindowOf<RefTextContourShape> ;

} // namespace Video
} // namespace CCore

#endif

