/* ColorListWindow.cpp */
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

#include <CCore/inc/video/pref/ColorListWindow.h>

#include <CCore/inc/ForLoop.h>

#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/Print.h>

namespace CCore {
namespace Video {

namespace Private_ColorListWindow {

class DefList : public ColorInfoBase
 {
  public:

   DefList() {}

   virtual ~DefList() {}

   // AbstractColorInfo

   virtual ulen getLineCount() const { return 0; }

   virtual NamedColor getLine(ulen) const { return {}; }
 };

DefList Object CCORE_INITPRI_3 ;

} // namespace Private_ColorListWindow

using namespace Private_ColorListWindow;

/* GetNullColorInfoPtr() */

ColorInfoBase * GetNullColorInfoPtr() { return &Object; }

/* class ColorSet */

class ColorSet::Base : public ColorInfoBase
 {
   static NamedColor Table[141];

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

ColorSet::ColorSet()
 : ColorInfo(new Base())
 {
 }

ColorSet::~ColorSet()
 {
 }

/* class ColorListShape */

StrLen ColorListShape::SampleLine()
 {
  return "Sample color"_c;
 }

Point ColorListShape::LineSize(Font font,Point space,const ColorInfo &info)
 {
  FontSize fs=font->getSize();

  Coord max_dx=0;

  for(ulen index : IndLim(info->getLineCount()) )
    {
     Coord dx=font->text(Range(info->getLine(index).name)).full_dx;

     Replace_max(max_dx,dx);
    }

  Coord dy=fs.dy+space.y;

  return Point(max_dx+space.x+2*dy,dy);
 }

Point ColorListShape::ExtSpace(const Config &cfg)
 {
  Point space=+cfg.space;
  MCoord width=+cfg.width;

  Coord ext=RoundUpLen(width);

  return space.addXY(ext);
 }

void ColorListShape::Cache::operator () (const Config &cfg,const ColorInfo &info)
 {
  if( !ok )
    {
     const Font &font=cfg.font.get();

     FontSize fs=font->getSize();

     Point space=+cfg.space;

     med_dx=fs.medDX();

     line=LineSize(font,space,info);

     ok=true;
    }
 }

Point ColorListShape::getMinSize(Point cap) const
 {
  cache(cfg,info);

  Point space=ExtSpace(cfg);

  Point line=cache.line;

  Coord dy=MulSize(info->getLineCount(),line.y);

  return 2*space+Inf(Point(line.x,dy),cap-2*space);
 }

Point ColorListShape::getMinSize(unsigned lines) const
 {
  const Font &font=cfg.font.get();

  Point space=+cfg.space;
  MCoord width=+cfg.width;

  Coord ext=RoundUpLen(width);

  Point ts=font->text(SampleLine()).getSize();

  Coord dy=ts.y+space.y;
  Coord dx=ts.x+space.x+2*dy;

  return 2*space.addXY(ext)+Point(dx,MulSize(lines,dy));
 }

void ColorListShape::layout()
 {
  cache(cfg,info);

  Pane inner=pane.shrink(ExtSpace(cfg));

  if( +inner )
    {
     xoff_max=PlusSub(cache.line.x,inner.dx);

     dxoff=cache.med_dx;

     page=ulen(inner.dy/cache.line.y);

     yoff_max=PlusSub(info->getLineCount(),page);
    }
  else
    {
     xoff_max=0;
     dxoff=0;
     page=0;
     yoff_max=0;
    }
 }

void ColorListShape::initSelect()
 {
  select=MaxULen;

  setSelectDown(0);
 }

bool ColorListShape::setSelectDown(ulen pos)
 {
  ulen count=info->getLineCount();

  if( !count ) return false;

  Replace_min(pos,count-1);

  return Change(select,pos);
 }

bool ColorListShape::setSelectUp(ulen pos)
 {
  ulen count=info->getLineCount();

  if( !count ) return false;

  Replace_min(pos,count-1);

  return Change(select,pos);
 }

bool ColorListShape::showSelect()
 {
  if( select==MaxULen ) return false;

  if( select<yoff )
    {
     yoff=select;

     return true;
    }
  else
    {
     ulen i=select-yoff;

     if( i>=page && page>0 )
       {
        yoff=Min_cast(yoff_max,select-page+1);

        return true;
       }
    }

  return false;
 }

ulen ColorListShape::getPosition(Point point) const
 {
  Point space=+cfg.space;

  Pane inner=pane.shrink(space);

  if( !inner ) return 0;

  MCoord width=+cfg.width;

  Coord ext=RoundUpLen(width);

  Coord y=point.y-inner.y-ext;

  if( y<0 ) return yoff?yoff-1:0;

  if( y>=inner.dy ) return yoff+page;

  FontSize fs=cfg.font->getSize();

  Coord dy=fs.dy+space.y;

  Printf(Con,"#; #; #; #;\n",space,ext,y,dy);

  return yoff+ulen(y/dy);
 }

void ColorListShape::draw(const DrawBuf &buf,DrawParam draw_param) const
 {
  if( !pane ) return;

  cache(cfg,info);

  SmoothDrawArt art(buf.cut(pane));

  draw_param.erase(buf,pane,+cfg.back);

  VColor text = enable? +cfg.text : +cfg.inactive ;
  VColor gray=+cfg.gray;
  VColor snow=+cfg.snow;

  Point space=+cfg.space;

  // decor

  {
   MPane p(pane);

   MCoord width=+cfg.width;

   MPoint s(space);

   FigureTopBorder fig_top(p,width);

   fig_top.solid(art,gray);

   FigureBottomBorder fig_bottom(p,width);

   fig_bottom.solid(art,snow);

   if( focus )
     {
      FigureBox fig(p.shrink(s/2));

      fig.loop(art,width,+cfg.focus);
     }

   MCoord dx=s.x-width;
   MCoord dy=s.y-width;

   if( xoff>0 )
     {
      FigureLeftMark fig(p,dx);

      fig.solid(art,text);
     }

   if( xoff<xoff_max )
     {
      FigureRightMark fig(p,dx);

      fig.solid(art,text);
     }

   if( yoff>0 )
     {
      FigureUpMark fig(p,dy);

      fig.solid(art,text);
     }

   if( yoff<yoff_max )
     {
      FigureDownMark fig(p,dy);

      fig.solid(art,text);
     }
  }

  // table

  {
   Pane inner=pane.shrink(space);

   if( !inner ) return;

   ulen count=info->getLineCount();
   ulen index=yoff;

   if( !count ) return;

   const Font &font=cfg.font.get();

   Point line=cache.line;

   if( line.y>inner.dy ) return;

   DrawBuf tbuf=buf.cut(inner);

   SmoothDrawArt tart(tbuf);

   MCoord width=+cfg.width;
   VColor net=+cfg.net;

   Coord ext=RoundUpLen(width);

   Pane cell(inner.x-xoff+ext,inner.y+ext,line.x,line.y);

   Coord lim=cell.y+(inner.dy-line.y);
   Coord tx=line.x-2*line.y;

   auto hline = [&] (Point p)
                    {
                     MPoint a=p;

                     a=a.subXY(MPoint::Half);

                     MPoint b=a.addX(Fraction(cell.dx));

                     tart.path(width,net,a,b);

                     return a;

                    } ;

   MPoint A=hline(cell.getBase());
   MPoint B=A;

   for(; index<count && cell.y<=lim ;index++,cell.y+=line.y)
     {
      if( enable && index==select )
        {
         Pane pane=cell;

         pane.dx=tx;

         tart.block(pane.shrink(ext),+cfg.select);
        }

      NamedColor item=info->getLine(index);

      font->text(tbuf,cell.pushLeft(space.x/2),TextPlace(AlignX_Left,AlignY_Center),Range(item.name),text);

      {
       Pane pane=cell.pushLeft(tx);

       tart.block(pane.shrink(ext),item.vc);
      }

      B=hline(cell.addDY());
     }

   tart.path(width,net,A,B);

   auto vline = [&] (Coord dx)
                    {
                     MCoord mx=Fraction(dx);

                     tart.path(width,net,A.addX(mx),B.addX(mx));

                    } ;

   vline(tx);

   vline(cell.dx);
  }
 }

/* class ColorSet */

NamedColor ColorSet::Base::Table[141]=
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

  {"DimGray"_str,VColor(0x696969)},
  {"DodgerBlue"_str,VColor(0x1E90FF)},
  {"FireBrick"_str,VColor(0xB22222)},
  {"FloralWhite"_str,VColor(0xFFFAF0)},
  {"ForestGreen"_str,VColor(0x228B22)},
  {"Fuchsia"_str,VColor(0xFF00FF)},
  {"Gainsboro"_str,VColor(0xDCDCDC)},
  {"GhostWhite"_str,VColor(0xF8F8FF)},
  {"Gold"_str,VColor(0xFFD700)},
  {"GoldenRod"_str,VColor(0xDAA520)},

  {"Gray"_str,VColor(0x808080)},
  {"Green"_str,VColor(0x008000)},
  {"GreenYellow"_str,VColor(0xADFF2F)},
  {"HoneyDew"_str,VColor(0xF0FFF0)},
  {"HotPink"_str,VColor(0xFF69B4)},
  {"IndianRed"_str,VColor(0xCD5C5C)},
  {"Indigo"_str,VColor(0x4B0082)},
  {"Ivory"_str,VColor(0xFFFFF0)},
  {"Khaki"_str,VColor(0xF0E68C)},
  {"Lavender"_str,VColor(0xE6E6FA)},

  {"LavenderBlush"_str,VColor(0xFFF0F5)},
  {"LawnGreen"_str,VColor(0x7CFC00)},
  {"LemonChiffon"_str,VColor(0xFFFACD)},
  {"LightBlue"_str,VColor(0xADD8E6)},
  {"LightCoral"_str,VColor(0xF08080)},
  {"LightCyan"_str,VColor(0xE0FFFF)},
  {"LightGoldenRodYellow"_str,VColor(0xFAFAD2)},
  {"LightGray"_str,VColor(0xD3D3D3)},
  {"LightGreen"_str,VColor(0x90EE90)},
  {"LightPink"_str,VColor(0xFFB6C1)},

  {"LightSalmon"_str,VColor(0xFFA07A)},
  {"LightSeaGreen"_str,VColor(0x20B2AA)},
  {"LightSkyBlue"_str,VColor(0x87CEFA)},
  {"LightSlateGray"_str,VColor(0x778899)},
  {"LightSteelBlue"_str,VColor(0xB0C4DE)},
  {"LightYellow"_str,VColor(0xFFFFE0)},
  {"Lime"_str,VColor(0x00FF00)},
  {"LimeGreen"_str,VColor(0x32CD32)},
  {"Linen"_str,VColor(0xFAF0E6)},
  {"Magenta"_str,VColor(0xFF00FF)},

  {"Maroon"_str,VColor(0x800000)},
  {"MediumAquaMarine"_str,VColor(0x66CDAA)},
  {"MediumBlue"_str,VColor(0x0000CD)},
  {"MediumOrchid"_str,VColor(0xBA55D3)},
  {"MediumPurple"_str,VColor(0x9370DB)},
  {"MediumSeaGreen"_str,VColor(0x3CB371)},
  {"MediumSlateBlue"_str,VColor(0x7B68EE)},
  {"MediumSpringGreen"_str,VColor(0x00FA9A)},
  {"MediumTurquoise"_str,VColor(0x48D1CC)},
  {"MediumVioletRed"_str,VColor(0xC71585)},

  {"MidnightBlue"_str,VColor(0x191970)},
  {"MintCream"_str,VColor(0xF5FFFA)},
  {"MistyRose"_str,VColor(0xFFE4E1)},
  {"Moccasin"_str,VColor(0xFFE4B5)},
  {"NavajoWhite"_str,VColor(0xFFDEAD)},
  {"Navy"_str,VColor(0x000080)},
  {"OldLace"_str,VColor(0xFDF5E6)},
  {"Olive"_str,VColor(0x808000)},
  {"OliveDrab"_str,VColor(0x6B8E23)},
  {"Orange"_str,VColor(0xFFA500)},

  {"OrangeRed"_str,VColor(0xFF4500)},
  {"Orchid"_str,VColor(0xDA70D6)},
  {"PaleGoldenRod"_str,VColor(0xEEE8AA)},
  {"PaleGreen"_str,VColor(0x98FB98)},
  {"PaleTurquoise"_str,VColor(0xAFEEEE)},
  {"PaleVioletRed"_str,VColor(0xDB7093)},
  {"PapayaWhip"_str,VColor(0xFFEFD5)},
  {"PeachPuff"_str,VColor(0xFFDAB9)},
  {"Peru"_str,VColor(0xCD853F)},
  {"Pink"_str,VColor(0xFFC0CB)},

  {"Plum"_str,VColor(0xDDA0DD)},
  {"PowderBlue"_str,VColor(0xB0E0E6)},
  {"Purple"_str,VColor(0x800080)},
  {"RebeccaPurple"_str,VColor(0x663399)},
  {"Red"_str,VColor(0xFF0000)},
  {"RosyBrown"_str,VColor(0xBC8F8F)},
  {"RoyalBlue"_str,VColor(0x4169E1)},
  {"SaddleBrown"_str,VColor(0x8B4513)},
  {"Salmon"_str,VColor(0xFA8072)},
  {"SandyBrown"_str,VColor(0xF4A460)},

  {"SeaGreen"_str,VColor(0x2E8B57)},
  {"SeaShell"_str,VColor(0xFFF5EE)},
  {"Sienna"_str,VColor(0xA0522D)},
  {"Silver"_str,VColor(0xC0C0C0)},
  {"SkyBlue"_str,VColor(0x87CEEB)},
  {"SlateBlue"_str,VColor(0x6A5ACD)},
  {"SlateGray"_str,VColor(0x708090)},
  {"Snow"_str,VColor(0xFFFAFA)},
  {"SpringGreen"_str,VColor(0x00FF7F)},
  {"SteelBlue"_str,VColor(0x4682B4)},

  {"Tan"_str,VColor(0xD2B48C)},
  {"Teal"_str,VColor(0x008080)},
  {"Thistle"_str,VColor(0xD8BFD8)},
  {"Tomato"_str,VColor(0xFF6347)},
  {"Turquoise"_str,VColor(0x40E0D0)},
  {"Violet"_str,VColor(0xEE82EE)},
  {"Wheat"_str,VColor(0xF5DEB3)},
  {"White"_str,VColor(0xFFFFFF)},
  {"WhiteSmoke"_str,VColor(0xF5F5F5)},
  {"Yellow"_str,VColor(0xFFFF00)},

  {"YellowGreen"_str,VColor(0x9ACD32)}
 };

} // namespace Video
} // namespace CCore

