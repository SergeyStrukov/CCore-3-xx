/* Shape.Button.h */
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

#ifndef CCore_inc_video_lib_Shape_Button_h
#define CCore_inc_video_lib_Shape_Button_h

#include <CCore/inc/video/MinSizeType.h>
#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Font.h>
#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* classes */

struct ButtonState;

class ButtonShape;

class RefButtonShape;

class KnobShape;

/* struct ButtonState */

struct ButtonState
 {
  bool enable =  true ;
  bool focus  = false ;
  bool mover  = false ;
  bool down   = false ;

  bool mouse  = false ;

  ButtonState() {}
 };

/* class ButtonShape */

class ButtonShape : public ButtonState
 {
   static MCoord FigEX(Coord fdy,MCoord width);

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

   ButtonShape(const Config &cfg_,const FaceType &face_) : cfg(cfg_),face(face_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf) const;
 };

/* class RefButtonShape */

class RefButtonShape : public ButtonState
 {
  public:

   using Config = ButtonShape::Config ;

   // parameters

   using FaceType = const RefVal<DefString> & ;

   const Config &cfg;
   FaceType face;
   Pane pane;

   // methods

   RefButtonShape(const Config &cfg_,FaceType face_) : cfg(cfg_),face(face_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf) const;
 };

/* class KnobShape */

class KnobShape : public ButtonState
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
     RefVal<VColor> face   =     Black ;

     RefVal<Coord> dxy = 30 ;

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

       dxy.bind(bag.knob_dxy);
      }
    };

   // parameters

   enum FaceType
    {
     FaceOk,
     FacePlus,
     FaceMinus,
     FaceList,
     FaceCross,
     FaceAsterisk,
     FaceExclamation,
     FaceQuestion,
     FaceLeft,
     FaceRight,
     FaceUp,
     FaceDown,
     FaceStop,
     FaceRightRight,
     FaceLeftLeft,

     FaceLim
    };

   const Config &cfg;
   FaceType face;
   Pane pane;

   // methods

   KnobShape(const Config &cfg_,const FaceType &face_) : cfg(cfg_),face(face_) {}

   SizeBox getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf) const;
 };

} // namespace Video
} // namespace CCore

#endif

