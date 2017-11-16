/* Shape.RunButton.h */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Shape_RunButton_h
#define CCore_inc_video_lib_Shape_RunButton_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

struct RunButtonState;

class RunButtonShape;

/* struct RunButtonState */

struct RunButtonState
 {
  bool enable =  true ;
  bool focus  = false ;
  bool mover  = false ;
  bool on     = false ;

  RunButtonState() {}
 };

/* class RunButtonShape */

class RunButtonShape : public RunButtonState
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(6,2) ;

     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> snowUp = PaleGreen ;
     RefVal<VColor> text   =     Black ;

     RefVal<Point> space = Point(6,4) ;

     RefVal<Font> font;

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

       text.bind(bag.button_text);
       space.bind(bag.button_space);
       font.bind(bag.button_font.font);
      }
    };

   // parameters

   using FaceType = DefString ;

   const Config &cfg;
   FaceType face;
   Pane pane;

   // methods

   RunButtonShape(const Config &cfg_,const FaceType &face_) : cfg(cfg_),face(face_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

