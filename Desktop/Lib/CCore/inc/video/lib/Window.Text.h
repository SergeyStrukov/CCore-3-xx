/* Window.Text.h */
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

#ifndef CCore_inc_video_lib_Window_Text_h
#define CCore_inc_video_lib_Window_Text_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Label.h>
#include <CCore/inc/video/lib/Shape.Text.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class TextWindowOf;

/* class TextWindowOf<Shape> */

template <class Shape>
class TextWindowOf : public SubWindow
 {
   Shape shape;

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   TextWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~TextWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   Point getMinSize(StrLen text) const { return shape.getMinSize(text); }

   bool isEnabled() const { return shape.enable; }

   bool isAlerted() const { return shape.alert; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   void alert(bool on=true)
    {
     if( Change(shape.alert,on) ) redraw();
    }

   String getText() const requires( IsType<decltype(shape.text),String> ) { return shape.text; }

   void setText(const String &text) requires( IsType<decltype(shape.text),String> )
    {
     shape.text=text;

     redraw();
    }

   void setAlign(AlignX align_x)
    {
     shape.align_x=align_x;

     redraw();
    }

   void setAlign(AlignY align_y)
    {
     shape.align_y=align_y;

     redraw();
    }

   void setAlign(AlignX align_x,AlignY align_y)
    {
     shape.align_x=align_x;
     shape.align_y=align_y;

     redraw();
    }

   template <class ... TT>
   void printf(const char *format,const TT & ... tt)
    {
     setText( Stringf(format,tt...) );
    }

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

/* type TextWindow */

using TextWindow = TextWindowOf<TextShape> ;

/* type LabelWindow */

using LabelWindow = TextWindowOf<LabelShape> ;

/* type RefLabelWindow */

using RefLabelWindow = TextWindowOf<RefLabelShape> ;

} // namespace Video
} // namespace CCore

#endif

