/* struct TypeDefCore */

struct TypeDefCore
 {
  // types

  struct S1; // #Label 
  struct S2; // #Pad 
  struct S3; // #Formula 
  struct S4; // #Contour 
  struct S5; // #SolidOf 
  struct S6; // #BLoopOf 
  struct S7; // #LoopOf 
  struct S8; // #BPathOf 
  struct S9; // #PathOf 
  struct S10; // #StepOf 
  struct S11; // #Right 
  struct S12; // #Left 
  struct S13; // #Down 
  struct S14; // #Up 
  struct S15; // #Second 
  struct S16; // #First 
  struct S17; // #Mirror 
  struct S18; // #MoveLen 
  struct S19; // #Move 
  struct S20; // #RotateOrt 
  struct S21; // #Rotate 
  struct S22; // #MeetCircles 
  struct S23; // #MeetCircle 
  struct S24; // #Meet 
  struct S25; // #AngleC 
  struct S26; // #Proj 
  struct S27; // #CircleOuter 
  struct S28; // #CircleOf 
  struct S29; // #MidOrt 
  struct S30; // #Part 
  struct S31; // #Middle 
  struct S32; // #LineOf 
  struct S33; // #AngleOf 
  struct S34; // #LengthOf 
  struct S35; // #Div 
  struct S36; // #Mul 
  struct S37; // #Sub 
  struct S38; // #Add 
  struct S39; // #Neg 
  struct S40; // #Real 
  struct S41; // #Point 
  struct S42; // #Dot 
  struct S43; // #Solid 
  struct S44; // #Loop 
  struct S45; // #Path 
  struct S46; // #Step 
  struct S47; // #Couple 
  struct S48; // #Length 
  struct S49; // #Circle 
  struct S50; // #Line 
  struct S51; // #Angle 
  struct S52; // #Ratio 

  using A1 = DDL::MapPolyPtr< S52 , S48 , S51 , S41 , S2 , S3 , S39 , S38 , S37 , S36 , S35 , S34 , S33 , S32 , S31 , S30 , S29 , S28 , S27 , S26 , S25 , S24 , S23 , S22 , S21 , S20 , S19 , S18 , S17 , S16 , S15 , S14 , S13 , S12 , S11 , S10 , S9 , S8 , S7 , S6 , S5 > ; // #Arg
  using A2 = uint8 ; // #Exception
  using A3 = uint8 ; // #Bool


  using XXX8226D906_9898_43AA_B1BE_D60B0A6E31C8 = TypeDefCore ;

  // structures

  struct S1
   {
    DDL::MapText name;
    A3 show;
    A3 gray;
    A3 show_name;

    struct Ext;
   };

  struct S2
   {
    S1 label;
    DDL::ulen_type index;
    DDL::MapPolyPtr< S52 , S48 , S51 , S41 > object;

    struct Ext;
   };

  struct S3
   {
    S1 label;
    DDL::ulen_type index;
    A1 object;

    struct Ext;
   };

  struct S4
   {
    DDL::MapRange< S2 > pads;
    DDL::MapRange< S3 > formulas;

    struct Ext;
   };

  struct S5
   {
    A1 a;

    struct Ext;
   };

  struct S6
   {
    DDL::MapRange< A1 > args;

    struct Ext;
   };

  struct S7
   {
    DDL::MapRange< A1 > args;

    struct Ext;
   };

  struct S8
   {
    DDL::MapRange< A1 > args;

    struct Ext;
   };

  struct S9
   {
    DDL::MapRange< A1 > args;

    struct Ext;
   };

  struct S10
   {
    DDL::MapRange< A1 > args;

    struct Ext;
   };

  struct S11
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S12
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S13
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S14
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S15
   {
    A1 a;

    struct Ext;
   };

  struct S16
   {
    A1 a;

    struct Ext;
   };

  struct S17
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S18
   {
    A1 a;
    A1 b;
    A1 c;

    struct Ext;
   };

  struct S19
   {
    A1 a;
    A1 b;
    A1 c;

    struct Ext;
   };

  struct S20
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S21
   {
    A1 a;
    A1 b;
    A1 c;

    struct Ext;
   };

  struct S22
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S23
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S24
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S25
   {
    A1 a;
    A1 b;
    A1 c;

    struct Ext;
   };

  struct S26
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S27
   {
    A1 a;
    A1 b;
    A1 c;

    struct Ext;
   };

  struct S28
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S29
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S30
   {
    A1 a;
    A1 b;
    A1 c;

    struct Ext;
   };

  struct S31
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S32
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S33
   {
    A1 a;
    A1 b;
    A1 c;

    struct Ext;
   };

  struct S34
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S35
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S36
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S37
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S38
   {
    A1 a;
    A1 b;

    struct Ext;
   };

  struct S39
   {
    A1 a;

    struct Ext;
   };

  struct S40
   {
    sint64 mantissa;
    sint16 exp;

    struct Ext;
   };

  struct S41
   {
    S40 x;
    S40 y;
    A2 rex;

    struct Ext;
   };

  struct S42
   {
    S41 point;
    A3 break_flag;

    struct Ext;
   };

  struct S43
   {
    DDL::MapRange< S42 > dots;
    A2 rex;

    struct Ext;
   };

  struct S44
   {
    DDL::MapRange< S42 > dots;
    A2 rex;

    struct Ext;
   };

  struct S45
   {
    DDL::MapRange< S42 > dots;
    A2 rex;

    struct Ext;
   };

  struct S46
   {
    DDL::MapRange< S41 > points;
    A2 rex;

    struct Ext;
   };

  struct S47
   {
    S41 a;
    S41 b;
    A2 rex;

    struct Ext;
   };

  struct S48
   {
    S40 val;
    A2 rex;

    struct Ext;
   };

  struct S49
   {
    S41 center;
    S48 radius;
    A2 rex;

    struct Ext;
   };

  struct S50
   {
    S41 a;
    S41 ort;
    A2 rex;

    struct Ext;
   };

  struct S51
   {
    S40 val;
    A2 rex;

    struct Ext;
   };

  struct S52
   {
    S40 val;
    A2 rex;

    struct Ext;
   };

  // extra

 };

using XXX212CD757_09B3_4D89_BE20_65C1E4E5A819 = TypeDefCore ;

namespace TypeDef {

    using Arg = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A1 ;
    using Bool = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A3 ;
    using Exception = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::A2 ;
    using Up = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S14 ;
    using Add = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S38 ;
    using Div = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S35 ;
    using Dot = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S42 ;
    using Mul = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S36 ;
    using Neg = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S39 ;
    using Pad = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S2 ;
    using Sub = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S37 ;
    using MeetCircles = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S22 ;
    using MoveLen = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S18 ;
    using PathOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S9 ;
    using SolidOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S5 ;
    using Middle = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S31 ;
    using MidOrt = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S29 ;
    using Mirror = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S17 ;
    using Down = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S13 ;
    using Left = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S12 ;
    using Line = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S50 ;
    using Loop = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S44 ;
    using Meet = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S24 ;
    using Move = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S19 ;
    using Part = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S30 ;
    using Path = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S45 ;
    using Proj = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S26 ;
    using Real = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S40 ;
    using Step = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S46 ;
    using Rotate = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S21 ;
    using BLoopOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S6 ;
    using LoopOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S7 ;
    using LineOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S32 ;
    using Length = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S48 ;
    using AngleC = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S25 ;
    using CircleOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S28 ;
    using MeetCircle = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S23 ;
    using Formula = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S3 ;
    using Contour = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S4 ;
    using LengthOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S34 ;
    using RotateOrt = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S20 ;
    using Ratio = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S52 ;
    using AngleOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S33 ;
    using First = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S16 ;
    using BPathOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S8 ;
    using Second = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S15 ;
    using Angle = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S51 ;
    using Right = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S11 ;
    using StepOf = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S10 ;
    using Solid = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S43 ;
    using Point = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S41 ;
    using CircleOuter = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S27 ;
    using Label = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S1 ;
    using Couple = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S47 ;
    using Circle = XXX212CD757_09B3_4D89_BE20_65C1E4E5A819::S49 ;

} // namespace TypeDef

