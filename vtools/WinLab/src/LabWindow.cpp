/* LabWindow.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: WinLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/LabWindow.h>

namespace App {

/* class ColorSet */

class ColorSet::Base : public ColorInfoBase
 {
   static NamedColor Table[140];

  public:

   Base() {}

   virtual ~Base() {}

   // AbstractColorInfo

   virtual ulen getLineCount() const
    {
     return DimOf(Table);
    }

   virtual NamedColor getLine(ulen index) const
    {
     GuardIndex(index,DimOf(Table));

     return Table[index];
    }
 };

NamedColor ColorSet::Base::Table[140]=
 {
  {"AliceBlue"_str,VColor(0xF0F8FF)},
  {"AntiqueWhite"_str,VColor(0xFAEBD7)},
  {"Aqua"_str,VColor(0x00FFFF)},
  {"Aquamarine"_str,VColor(0x7FFFD4)},
  {"Azure"_str,VColor(0xF0FFFF)},
  {"Beige"_str,VColor(0xF5F5DC)},
  {"Bisque"_str,VColor(0xFFE4C4)},
  {"Black"_str,VColor(0x000000)},
  {"BlanchedAlmond"_str,VColor(0xFFEBCD)},
  {"Blue"_str,VColor(0x0000FF)},

  {"BlueViolet"_str,VColor(0x8A2BE2)},
  {"Brown"_str,VColor(0xA52A2A)},
  {"BurlyWood"_str,VColor(0xDEB887)},
  {"CadetBlue"_str,VColor(0x5F9EA0)},
  {"Chartreuse"_str,VColor(0x7FFF00)},
  {"Chocolate"_str,VColor(0xD2691E)},
  {"Coral"_str,VColor(0xFF7F50)},
  {"CornflowerBlue"_str,VColor(0x6495ED)},
  {"Cornsilk"_str,VColor(0xFFF8DC)},
  {"Crimson"_str,VColor(0xDC143C)},

  {"Cyan"_str,VColor(0x00FFFF)},
  {"DarkBlue"_str,VColor(0x00008B)},
  {"DarkCyan"_str,VColor(0x008B8B)},
  {"DarkGoldenRod"_str,VColor(0xB8860B)},
  {"DarkGray"_str,VColor(0xA9A9A9)},
  {"DarkGreen"_str,VColor(0x006400)},
  {"DarkKhaki"_str,VColor(0xBDB76B)},
  {"DarkMagenta"_str,VColor(0x8B008B)},
  {"DarkOliveGreen"_str,VColor(0x556B2F)},
  {"DarkOrange"_str,VColor(0xFF8C00)},

  {"DarkOrchid"_str,VColor(0x9932CC)},
  {"DarkRed"_str,VColor(0x8B0000)},
  {"DarkSalmon"_str,VColor(0xE9967A)},
  {"DarkSeaGreen"_str,VColor(0x8FBC8F)},
  {"DarkSlateBlue"_str,VColor(0x483D8B)},
  {"DarkSlateGray"_str,VColor(0x2F4F4F)},
  {"DarkTurquoise"_str,VColor(0x00CED1)},
  {"DarkViolet"_str,VColor(0x9400D3)},
  {"DeepPink"_str,VColor(0xFF1493)},
  {"DeepSkyBlue"_str,VColor(0x00BFFF)},

#if 0

  {""_str,VColor(0x)},
  {""_str,VColor(0x)},
  {""_str,VColor(0x)},
  {""_str,VColor(0x)},
  {""_str,VColor(0x)},
  {""_str,VColor(0x)},
  {""_str,VColor(0x)},
  {""_str,VColor(0x)},
  {""_str,VColor(0x)},
  {""_str,VColor(0x)},

#endif
 };

#if 0

DimGray     #696969     Shades  Mix
DimGrey     #696969     Shades  Mix
DodgerBlue  #1E90FF     Shades  Mix
FireBrick   #B22222     Shades  Mix
FloralWhite     #FFFAF0     Shades  Mix
ForestGreen     #228B22     Shades  Mix
Fuchsia     #FF00FF     Shades  Mix
Gainsboro   #DCDCDC     Shades  Mix
GhostWhite  #F8F8FF     Shades  Mix
Gold    #FFD700     Shades  Mix
GoldenRod   #DAA520     Shades  Mix
Gray    #808080     Shades  Mix
Grey    #808080     Shades  Mix
Green   #008000     Shades  Mix
GreenYellow     #ADFF2F     Shades  Mix
HoneyDew    #F0FFF0     Shades  Mix
HotPink     #FF69B4     Shades  Mix
IndianRed   #CD5C5C     Shades  Mix
Indigo      #4B0082     Shades  Mix
Ivory   #FFFFF0     Shades  Mix
Khaki   #F0E68C     Shades  Mix
Lavender    #E6E6FA     Shades  Mix
LavenderBlush   #FFF0F5     Shades  Mix
LawnGreen   #7CFC00     Shades  Mix
LemonChiffon    #FFFACD     Shades  Mix
LightBlue   #ADD8E6     Shades  Mix
LightCoral  #F08080     Shades  Mix
LightCyan   #E0FFFF     Shades  Mix
LightGoldenRodYellow    #FAFAD2     Shades  Mix
LightGray   #D3D3D3     Shades  Mix
LightGrey   #D3D3D3     Shades  Mix
LightGreen  #90EE90     Shades  Mix
LightPink   #FFB6C1     Shades  Mix
LightSalmon     #FFA07A     Shades  Mix
LightSeaGreen   #20B2AA     Shades  Mix
LightSkyBlue    #87CEFA     Shades  Mix
LightSlateGray  #778899     Shades  Mix
LightSlateGrey  #778899     Shades  Mix
LightSteelBlue  #B0C4DE     Shades  Mix
LightYellow     #FFFFE0     Shades  Mix
Lime    #00FF00     Shades  Mix
LimeGreen   #32CD32     Shades  Mix
Linen   #FAF0E6     Shades  Mix
Magenta     #FF00FF     Shades  Mix
Maroon  #800000     Shades  Mix
MediumAquaMarine    #66CDAA     Shades  Mix
MediumBlue  #0000CD     Shades  Mix
MediumOrchid    #BA55D3     Shades  Mix
MediumPurple    #9370DB     Shades  Mix
MediumSeaGreen  #3CB371     Shades  Mix
MediumSlateBlue     #7B68EE     Shades  Mix
MediumSpringGreen   #00FA9A     Shades  Mix
MediumTurquoise     #48D1CC     Shades  Mix
MediumVioletRed     #C71585     Shades  Mix
MidnightBlue    #191970     Shades  Mix
MintCream   #F5FFFA     Shades  Mix
MistyRose   #FFE4E1     Shades  Mix
Moccasin    #FFE4B5     Shades  Mix
NavajoWhite     #FFDEAD     Shades  Mix
Navy    #000080     Shades  Mix
OldLace     #FDF5E6     Shades  Mix
Olive   #808000     Shades  Mix
OliveDrab   #6B8E23     Shades  Mix
Orange  #FFA500     Shades  Mix
OrangeRed   #FF4500     Shades  Mix
Orchid  #DA70D6     Shades  Mix
PaleGoldenRod   #EEE8AA     Shades  Mix
PaleGreen   #98FB98     Shades  Mix
PaleTurquoise   #AFEEEE     Shades  Mix
PaleVioletRed   #DB7093     Shades  Mix
PapayaWhip  #FFEFD5     Shades  Mix
PeachPuff   #FFDAB9     Shades  Mix
Peru    #CD853F     Shades  Mix
Pink    #FFC0CB     Shades  Mix
Plum    #DDA0DD     Shades  Mix
PowderBlue  #B0E0E6     Shades  Mix
Purple  #800080     Shades  Mix
RebeccaPurple   #663399     Shades  Mix
Red     #FF0000     Shades  Mix
RosyBrown   #BC8F8F     Shades  Mix
RoyalBlue   #4169E1     Shades  Mix
SaddleBrown     #8B4513     Shades  Mix
Salmon  #FA8072     Shades  Mix
SandyBrown  #F4A460     Shades  Mix
SeaGreen    #2E8B57     Shades  Mix
SeaShell    #FFF5EE     Shades  Mix
Sienna  #A0522D     Shades  Mix
Silver  #C0C0C0     Shades  Mix
SkyBlue     #87CEEB     Shades  Mix
SlateBlue   #6A5ACD     Shades  Mix
SlateGray   #708090     Shades  Mix
SlateGrey   #708090     Shades  Mix
Snow    #FFFAFA     Shades  Mix
SpringGreen     #00FF7F     Shades  Mix
SteelBlue   #4682B4     Shades  Mix
Tan     #D2B48C     Shades  Mix
Teal    #008080     Shades  Mix
Thistle     #D8BFD8     Shades  Mix
Tomato  #FF6347     Shades  Mix
Turquoise   #40E0D0     Shades  Mix
Violet  #EE82EE     Shades  Mix
Wheat   #F5DEB3     Shades  Mix
White   #FFFFFF     Shades  Mix
WhiteSmoke  #F5F5F5     Shades  Mix
Yellow  #FFFF00     Shades  Mix
YellowGreen     #9ACD32

#endif

ColorSet::ColorSet()
 : ColorInfo(new Base())
 {
 }

ColorSet::~ColorSet()
 {
 }

/* class LabWindow */

LabWindow::LabWindow(SubWindowHost &host,const Config &cfg)
 : ColorListWindow(host,cfg,ColorSet())
 {
 }

LabWindow::~LabWindow()
 {
 }

} // namespace App

