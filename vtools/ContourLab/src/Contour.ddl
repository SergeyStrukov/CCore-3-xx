/* Contour.ddl */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

/* --- Common ------------------------------------------------------------------------- */

type Bool = uint8 ;

Bool True = 1 ;

Bool False = 0 ;

struct Label
 {
  text name;

  Bool show;
  Bool gray;
  Bool show_name;
 };

type Exception = uint8 ;

/* --- Geometry ----------------------------------------------------------------------- */

struct Real
 {
  sint64 mantissa;
  sint16 exp;
 };
 
struct Ratio
 {
  Real val;
  Exception rex;
 };
  
struct Length
 {
  Real val;
  Exception rex;
 }; 
 
struct Angle
 {
  Real val;
  Exception rex;
 };
  
struct Point
 {
  Real x;
  Real y;
  Exception rex;
 }; 
 
struct Line
 {
  Point a;
  Point ort;
  Exception rex;
 };
 
struct Circle 
 {
  Point center;
  Length radius;
  Exception rex;
 };
 
struct Couple
 {
  Point a;
  Point b;
  Exception rex;
 };
 
struct Dot 
 {
  Point point;
  Bool break_flag;
 };
 
struct Step 
 {
  Point[] points;
  Exception rex;
 };
 
struct Path
 {
  Dot[] dots;
  Exception rex;
 };
 
struct Loop
 {
  Dot[] dots;
  Exception rex;
 };
  
struct Solid
 {
  Dot[] dots;
  Exception rex;
 };

/* --- Pad ---------------------------------------------------------------------------- */ 

struct Pad
 {
  Label label;
  ulen index;
  
  {Ratio,Length,Angle,Point} *object;
 };

/* --- Formula ------------------------------------------------------------------------ */

struct Neg
 {
  Arg a;
 };
 
struct Add
 {
  Arg a;
  Arg b;  
 };
 
struct Sub
 {
  Arg a;
  Arg b;  
 };
 
struct Mul
 {
  Arg a;
  Arg b;  
 };
 
struct Div
 {
  Arg a;
  Arg b;  
 };

struct LengthOf
 {
  Arg a;
  Arg b;  
 };
 
struct AngleOf
 {
  Arg a;
  Arg b;
  Arg c;  
 };
 
struct LineOf
 {
  Arg a;
  Arg b;  
 };  
 
struct Middle
 {
  Arg a;
  Arg b;  
 };
   
struct Part
 {
  Arg a;
  Arg b;  
  Arg c;  
 };
 
struct MidOrt 
 {
  Arg a;
  Arg b;  
 };
 
struct CircleOf 
 {
  Arg a;
  Arg b;  
 };
 
struct CircleOuter 
 {
  Arg a;
  Arg b;  
  Arg c;  
 };
 
struct Proj 
 {
  Arg a;
  Arg b;  
 };
 
struct AngleC 
 {
  Arg a;
  Arg b;  
  Arg c;  
 };
 
struct Meet 
 {
  Arg a;
  Arg b;  
 };
 
struct MeetCircle
 {
  Arg a;
  Arg b;  
 };
 
struct MeetCircles
 {
  Arg a;
  Arg b;  
 };
 
struct Rotate 
 {
  Arg a;
  Arg b;  
  Arg c;  
 };

struct RotateOrt
 {
  Arg a;
  Arg b;  
 };

struct Move
 {
  Arg a;
  Arg b;  
  Arg c;  
 };
 
struct MoveLen
 {
  Arg a;
  Arg b;  
  Arg c;  
 };
 
struct Mirror 
 {
  Arg a;
  Arg b;  
 };
 
struct First
 {
  Arg a;
 };
  
struct Second
 {
  Arg a;
 }; 
 
struct Up 
 {
  Arg a;
  Arg b;  
 };
 
struct Down 
 {
  Arg a;
  Arg b;  
 };
 
struct Left 
 {
  Arg a;
  Arg b;  
 };
 
struct Right 
 {
  Arg a;
  Arg b;  
 };
 
struct StepOf
 {
  Arg[] args;
 }; 
 
struct PathOf
 {
  Arg[] args;
 };
 
struct BPathOf
 {
  Arg[] args;
 };
  
struct LoopOf
 {
  Arg[] args;
 };
 
struct BLoopOf
 {
  Arg[] args;
 };
 
struct SolidOf 
 {
  Arg a;
 }; 
 
type Arg = {
            Ratio,Length,Angle,Point,Pad,Formula,
            Neg,Add,Sub,Mul,Div, 
            LengthOf,AngleOf,LineOf,Middle,Part,MidOrt,CircleOf,CircleOuter,
            Proj,AngleC,Meet,MeetCircle,MeetCircles,Rotate,RotateOrt,Move,MoveLen,
            Mirror,First,Second,Up,Down,Left,Right,
            StepOf,PathOf,BPathOf,LoopOf,BLoopOf,SolidOf
           } * ;

struct Formula
 {
  Label label;
  ulen index;
  
  Arg object;
 };

/* --- Contour ------------------------------------------------------------------------ */
 
struct Contour
 {
  Pad[] pads;
  Formula[] formulas;
 };


   