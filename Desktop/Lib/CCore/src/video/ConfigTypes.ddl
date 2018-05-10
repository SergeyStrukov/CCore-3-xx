/* ConfigTypes.ddl */
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

type Bool = uint8 ;

Bool True = 1 ;

Bool False = 0 ;

type Coord = sint32 ;

type MCoord = sint32 ; 

type VColor = uint32 ;

type Clr = uint8 ;

struct Point
 {
  Coord x;
  Coord y;
 };
 
struct Ratio
 {
  sint32 ratio;
 }; 

struct Font
 {
  type EngineType = int ;

  const EngineType EngineDefault  = 0 ;
  const EngineType EngineFreeType = 1 ;

  EngineType engine_type;

  text file_name;

  type SizeType = int ;

  const SizeType SizeXY    = 0 ;
  const SizeType SizePoint = 1 ;
  const SizeType SizeIndex = 2 ;

  SizeType size_type;
  int dx;
  int dy;

  struct Config
   {
    type FontHintType = int ;

    const FontHintType FontHintNone   = 0 ;
    const FontHintType FontHintNative = 1 ;
    const FontHintType FontHintAuto   = 2 ;

    FontHintType fht;

    type FontSmoothType = int ;

    const FontSmoothType FontSmoothNone    = 0 ;
    const FontSmoothType FontSmooth        = 1 ;
    const FontSmoothType FontSmoothLCD_RGB = 2 ;
    const FontSmoothType FontSmoothLCD_BGR = 3 ;

    FontSmoothType fsm;

    Bool use_kerning;
    int strength;
    int gamma_order; // /1024
   };

  Config cfg;
 };


