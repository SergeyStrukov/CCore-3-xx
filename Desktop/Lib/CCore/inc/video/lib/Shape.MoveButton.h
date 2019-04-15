/* Shape.MoveButton.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Shape_MoveButton_h
#define CCore_inc_video_lib_Shape_MoveButton_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

#include <CCore/inc/video/lib/Shape.ButtonState.h>

namespace CCore {
namespace Video {

/* classes */

class MoveButtonShape;

/* class MoveButtonShape */

class MoveButtonShape : public ButtonState
 {
   static constexpr Point Aspect = Point(37,20) ;

  public:

   struct Config
    {
     // user

     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> snowUp = PaleGreen ;
     RefVal<VColor> face   =     Black ;

     RefVal<Coord> dy = 30 ;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       snowUp.bind(bag.snowUp);
       face.bind(bag.face);

       dy.bind(bag.knob_dxy);
      }
    };

   // parameters

   enum FaceType
    {
     BackDir,
     ForeDir
    };

   const Config &cfg;
   FaceType face;
   Pane pane;

   // methods

   MoveButtonShape(const Config &cfg_,FaceType face_) : cfg(cfg_),face(face_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

} // namespace Video
} // namespace CCore

#endif

