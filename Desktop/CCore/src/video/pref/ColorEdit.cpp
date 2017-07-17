/* ColorEdit.cpp */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/pref/ColorEdit.h>

#include <CCore/inc/video/FigureLib.h>
#include <CCore/inc/video/Layout.h>

#include <CCore/inc/Scanf.h>

namespace CCore {
namespace Video {

/* class ColorEditWindow */

void ColorEditWindow::preparePalette()
 {
  ulen size=len*len;

  ulen plen=palette.getLen();

  if( plen<size )
    {
     palette.extend_fill(size-plen,White);
    }
 }

class ColorEditWindow::Art : public SmoothDrawArt
 {
  public:

   explicit Art(const DrawBuf &buf) : SmoothDrawArt(buf) {}
 };

void ColorEditWindow::drawCap(Art &art,MPoint center,VColor color,bool select) const
 {
  MCoord radius=Fraction(+cfg.radius);
  MCoord radius2=Div(8,10)*radius;

  MCoord delta=Ratio(724,10)*radius;

  art.ball(center,radius,TwoField(center.subXY(delta),+cfg.gray,center.addXY(delta),+cfg.snow));

  art.ball(center,radius2,color);

  if( select )
    {
     MCoord radius3=Div(7,10)*radius;

     FigureAsterisk fig(center,radius3);

     fig.curveSolid(art,RadioField(center,radius3,White,Black));
    }
 }

class ColorEditWindow::WhiteField : public TwoField
 {
  public:

   static VColor Whiten(VColor vc)
    {
     Clr r=RedOf(vc);
     Clr g=GreenOf(vc);
     Clr b=BlueOf(vc);

     Clr d=MaxClr-Max_cast(r,g,b);

     return RGBColor(r+d,g+d,b+d);
    }

   WhiteField(MPoint a,VColor va,MPoint b) : TwoField(a,va,b,Whiten(va)) {}
 };

auto ColorEditWindow::getItem(Point point) const -> ItemIndex
 {
  Coord radius=+cfg.radius;
  Coord space_dxy=+cfg.space_dxy;

  if( Dist(point,value_center)<=radius ) return Item_value;

  if( Dist(point,back_center)<=radius ) return Item_back;

  if( Dist(point,fore_center)<=radius ) return Item_fore;

  if( Dist(point,left_center)<=radius ) return Item_left;

  if( Dist(point,right_center)<=radius ) return Item_right;

  if( Dist(point,top_center)<=radius ) return Item_top;

  if( mixUp_place.contains(point) ) return Item_mix;

  if( whiteUp_place.contains(point) ) return Item_white;

  Coord grid=2*radius+space_dxy;

  for(unsigned i=0; i<len ;i++)
    for(unsigned j=0; j<len ;j++)
      {
       unsigned k=i+j*len;

       if( Dist(point,palette_base_center+Point(i,j)*grid)<=radius ) return ItemIndex(Item_palette_base+k);
      }

  return Item_none;
 }

VColor ColorEditWindow::getColor(ItemIndex item) const
 {
  switch( item )
    {
     case Item_value : return value;

     case Item_back : return back;

     case Item_fore : return fore;

     case Item_left : return left;

     case Item_right : return right;

     case Item_mix :
      {
       Coord mix_width=+cfg.mix_width;

       Point base=mix_place.getBase();

       TwoField field(base.addX(mix_width/2),left,base.addX(mix_place.dx-mix_width/2),right);

       return field(base.addX(mix_pos+mix_width/2));
      }

     case Item_top : return top;

     case Item_white :
      {
       Coord mix_width=+cfg.mix_width;

       Point base=white_place.getBase();

       WhiteField field(base.addY(mix_width/2),top,base.addY(white_place.dy-mix_width/2));

       return field(base.addY(white_pos+mix_width/2));
      }

     default:
      {
       if( item>=Item_palette_base )
         {
          unsigned ind=item-Item_palette_base;

          return pal(ind);
         }

       return Black;
      }
    }
 }

void ColorEditWindow::setColor(ItemIndex item,VColor vc)
 {
  switch( item )
    {
     case Item_value :
      {
       value=vc;

       changed.assert(vc);

       redraw();
      }
     break;

     case Item_back :
      {
       back=vc;

       redraw();
      }
     break;

     case Item_fore :
      {
       fore=vc;

       redraw();
      }
     break;

     case Item_left :
      {
       left=vc;

       redraw();
      }
     break;

     case Item_right :
      {
       right=vc;

       redraw();
      }
     break;

     case Item_top :
      {
       top=vc;

       redraw();
      }
     break;

     default:
      {
       if( item>=Item_palette_base )
         {
          unsigned ind=item-Item_palette_base;

          if( ind>=45 && ind<palette.getLen() )
            {
             palette[ind]=vc;

             redraw();
            }
         }
      }
    }
 }

void ColorEditWindow::copy(VColor vc)
 {
  char temp[TextBufLen];
  PrintBuf out(Range(temp));

  Printf(out,"###6.16i;",vc);

  getFrameHost()->textToClipboard(out.close());
 }

class ColorEditWindow::TextToColor : public Funchor
 {
   VColor vc = Black ;
   bool ok = false ;

  public:

   bool get(VColor &ret) const
    {
     if( ok )
       {
        ret=vc;

        return true;
       }

     return false;
    }

   void text(StrLen str)
    {
     ScanString inp(str);

     uint32 val;

     Scanf(inp,"###.16;",val);

     if( inp.isOk() && val<=0xFFFFFF )
       {
        vc=VColor(val);

        ok=true;
       }
    }

   Function<void (StrLen)> function_text() { return FunctionOf(this,&TextToColor::text); }
 };

bool ColorEditWindow::past(VColor &ret)
 {
  TextToColor temp;

  getFrameHost()->textFromClipboard(temp.function_text());

  return temp.get(ret);
 }

ColorEditWindow::ColorEditWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_),

   palette{Black,Gray,Silver,White,Red,Green,Blue,Cyan,Fuchsia,Yellow,Teal,Purple,Olive,
           Maroon,Navy,Orange,Crimson,DarkGray,DarkGreen,DarkOrange,DarkOrchid,
           DarkRed,DarkViolet,DimGray,ForestGreen,GhostWhite,Gold,GoldenRod,Indigo,
           Ivory,Lavender,LightGray,MediumBlue,OrangeRed,Orchid,SeaGreen,SkyBlue,
           Snow,SteelBlue,Violet,Wheat,RoyalBlue,DeepSkyBlue,Pink,PaleGreen}
 {
  bindHint(cfg.hint_color);
 }

ColorEditWindow::~ColorEditWindow()
 {
 }

 // methods

Point ColorEditWindow::getMinSize() const
 {
  Coordinate radius=+cfg.radius;
  Coordinate space_dxy=+cfg.space_dxy;
  Coordinate len=+cfg.len;

  Coordinate contour_len=len*(2*radius)+(len+1)*space_dxy;

  return Point(contour_len+space_dxy+2*radius,contour_len+2*space_dxy+4*radius);
 }

void ColorEditWindow::setColor(VColor value_)
 {
  value=value_;

  redraw();
 }

 // drawing

bool ColorEditWindow::isGoodSize(Point size) const
 {
  return size>=getMinSize();
 }

void ColorEditWindow::layout()
 {
  Coord radius=+cfg.radius;
  Coord space_dxy=+cfg.space_dxy;
  Coord mix_len=+cfg.mix_len;
  Coord white_len=+cfg.white_len;

  // value

  value_center=Point(radius,radius);

  // palette

  len=+cfg.len;

  Coord contour_len=len*(2*radius)+(len+1)*space_dxy;

  palette_contour=Pane(0,2*radius+space_dxy,contour_len,contour_len);

  palette_base_center=palette_contour.getBase().addXY(space_dxy+radius);

  preparePalette();

  // mixer

  left_center=Point(radius,palette_contour.getLim().y+space_dxy+radius);

  right_center=left_center.addX(2*radius+mix_len);

  {
   Point base=left_center.addX(radius);

   mix_place=EnvelopeY(base,mix_len,Div(2,3)*radius);
   mixUp_place=EnvelopeY(base,mix_len,radius);
  }

  // text

  text_place=Pane(4*radius,0,12*radius,2*radius);

  back_center=Point(text_place.getLim().x+space_dxy+radius,radius);
  fore_center=back_center.addX(2*radius);

  // white

  top_center=Point(palette_contour.x+palette_contour.dx+space_dxy+radius,palette_contour.y+radius);

  {
   Point base=top_center.addY(radius);

   white_place=EnvelopeX(base,white_len,Div(2,3)*radius);
   whiteUp_place=EnvelopeX(base,white_len,radius);
  }
 }

void ColorEditWindow::draw(DrawBuf buf,bool) const
 {
  MCoord width=+cfg.width;
  Coord radius=+cfg.radius;
  Coord space_dxy=+cfg.space_dxy;
  Coord mix_width=+cfg.mix_width;

  VColor gray=+cfg.gray;
  VColor snow=+cfg.snow;

  Art art(buf);

  // value

  drawCap(art,value_center,value,item==Item_value);

  if( focus )
    {
     art.circle(value_center,Fraction(radius),width,+cfg.focus);
    }

  // palette

  {
   Coord grid=2*radius+space_dxy;

   FigureTopBorder fig_top(palette_contour,width);
   FigureBottomBorder fig_bottom(palette_contour,width);

   fig_top.solid(art,gray);
   fig_bottom.solid(art,snow);

   for(unsigned i=0; i<len ;i++)
     for(unsigned j=0; j<len ;j++)
       {
        unsigned k=i+j*len;

        drawCap(art,palette_base_center+Point(i,j)*grid,pal(k),item==(Item_palette_base+k));
       }
  }

  // mixer

  {
   drawCap(art,left_center,left,item==Item_left);
   drawCap(art,right_center,right,item==Item_right);

   Point base=mix_place.getBase();

   TwoField field(base.addX(mix_width/2),left,base.addX(mix_place.dx-mix_width/2),right);

   FigureBox(mix_place).solid(art,field);

   Pane box_mix(base.x+mix_pos,mixUp_place.y,mix_width,mixUp_place.dy);

   FigureBox(box_mix).solid(art,field(base.addX(mix_pos+mix_width/2)));

   if( item==Item_mix )
     {
      MPoint pos(box_mix.getBase()+box_mix.getSize()/2);

      MCoord radius2=Div(1,3)*Fraction(mix_width);

      FigureAsterisk fig(pos,radius2);

      fig.curveSolid(art,RadioField(pos,radius2,White,Black));
     }
  }

  // text

  {
   art.block(text_place,back);

   cfg.font.get()->text(buf,text_place,TextPlace(AlignX_Center,AlignY_Center),"Sample text"_c,fore);

   drawCap(art,back_center,back,item==Item_back);
   drawCap(art,fore_center,fore,item==Item_fore);
  }

  // white

  {
   drawCap(art,top_center,top,item==Item_top);

   Point base=white_place.getBase();

   WhiteField field(base.addY(mix_width/2),top,base.addY(white_place.dy-mix_width/2));

   FigureBox(white_place).solid(art,field);

   Pane box_white(whiteUp_place.x,base.y+white_pos,whiteUp_place.dx,mix_width);

   FigureBox(box_white).solid(art,field(base.addY(white_pos+mix_width/2)));

   if( item==Item_white )
     {
      MPoint pos(box_white.getBase()+box_white.getSize()/2);

      MCoord radius2=Div(1,3)*Fraction(mix_width);

      FigureAsterisk fig(pos,radius2);

      fig.curveSolid(art,RadioField(pos,radius2,White,Black));
     }
  }
 }

 // base

void ColorEditWindow::open()
 {
  item=Item_value;
 }

void ColorEditWindow::close()
 {
 }

 // keyboard

FocusType ColorEditWindow::askFocus() const
 {
  return FocusOk;
 }

void ColorEditWindow::gainFocus()
 {
  if( Change(focus,true) ) redraw();
 }

void ColorEditWindow::looseFocus()
 {
  if( Change(focus,false) ) redraw();
 }

 // mouse

void ColorEditWindow::looseCapture()
 {
 }

MouseShape ColorEditWindow::getMouseShape(Point,KeyMod) const
 {
  return Mouse_Arrow;
 }

 // user input

void ColorEditWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void ColorEditWindow::react_Key(VKey vkey,KeyMod kmod)
 {
  if( kmod&KeyMod_Ctrl )
    {
     switch( vkey )
       {
        case VKey_c :
         {
          copy(getColor(item));
         }
        break;

        case VKey_v :
         {
          VColor vc;

          if( past(vc) ) setColor(item,vc);
         }
        break;
       }
    }
 }

void ColorEditWindow::react_LeftClick(Point point,MouseKey mkey)
 {
  if( auto item_=getItem(point) )
    {
     item=item_;

     if( item==Item_mix )
       {
        Coord mix_len=+cfg.mix_len;
        Coord mix_width=+cfg.mix_width;

        Coord pos=point.x-mix_place.x-mix_width/2;

        mix_pos=Cap<Coord>(0,pos,mix_len-mix_width);
       }

     if( item==Item_white )
       {
        Coord white_len=+cfg.white_len;
        Coord mix_width=+cfg.mix_width;

        Coord pos=point.y-white_place.y-mix_width/2;

        white_pos=Cap<Coord>(0,pos,white_len-mix_width);
       }

     if( mkey&MouseKey_Shift ) copy(getColor(item));

     redraw();
    }
 }

void ColorEditWindow::react_RightClick(Point point,MouseKey mkey)
 {
  if( auto item_=getItem(point) )
    {
     if( mkey&MouseKey_Shift )
       {
        VColor vc;

        if( past(vc) ) setColor(item_,vc);
       }
     else
       {
        setColor(item_,getColor(item));
       }
    }
 }

void ColorEditWindow::react_Move(Point point,MouseKey mkey)
 {
  if( mkey&MouseKey_Left )
    {
     if( mixUp_place.contains(point) )
       {
        Coord mix_len=+cfg.mix_len;
        Coord mix_width=+cfg.mix_width;

        Coord pos=point.x-mix_place.x-mix_width/2;

        pos=Cap<Coord>(0,pos,mix_len-mix_width);

        if( Change(mix_pos,pos) ) redraw();
       }

     if( whiteUp_place.contains(point) )
       {
        Coord white_len=+cfg.white_len;
        Coord mix_width=+cfg.mix_width;

        Coord pos=point.y-white_place.y-mix_width/2;

        pos=Cap<Coord>(0,pos,white_len-mix_width);

        if( Change(white_pos,pos) ) redraw();
       }
    }
 }

void ColorEditWindow::react_Wheel(Point point,MouseKey,Coord delta)
 {
  if( mixUp_place.contains(point) )
    {
     Coord mix_len=+cfg.mix_len;
     Coord mix_width=+cfg.mix_width;

     mix_pos=Cap<Coord>(0,mix_pos-delta,mix_len-mix_width);

     redraw();
    }

  if( whiteUp_place.contains(point) )
    {
     Coord white_len=+cfg.white_len;
     Coord mix_width=+cfg.mix_width;

     white_pos=Cap<Coord>(0,white_pos-delta,white_len-mix_width);

     redraw();
    }
 }

} // namespace Video
} // namespace CCore

