/* Menu.cpp */
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

#include <CCore/inc/video/Menu.h>

#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/SymCount.h>
#include <CCore/inc/Symbol.h>

namespace CCore {
namespace Video {

/* struct MenuPoint */

void MenuPoint::pickhot()
 {
  if( type==MenuTextNoHot )
    {
     type=MenuText;

     hotindex=0;
     hotkey=0;
    }
  else
    {
     StrLen str=text.str();

     if( str.len )
       for(ulen i=0,lim=str.len-1; i<lim ;i++)
         {
          if( str[i]==Hot )
            {
             hotindex=i+1;

             hotkey=PeekChar(str.part(hotindex));

             return;
            }
         }

     hotindex=0;
     hotkey=0;
    }
 }

/* struct MenuData */

auto MenuData::find(Char ch) const -> FindResult
 {
  auto r=Range(list);

  for(ulen i=0; i<r.len ;i++) if( r[i].test(ch) ) return i;

  return Null;
 }

auto MenuData::find(Point point) const -> FindResult
 {
  auto r=Range(list);

  for(ulen i=0; i<r.len ;i++) if( r[i].test(point) ) return i;

  return Null;
 }

auto MenuData::findDown(ulen index) const -> FindResult
 {
  auto r=Range(list);

  Replace_min(index,r.len);

  while( index-- ) if( r[index].type==MenuText ) return index;

  return Null;
 }

auto MenuData::findUp(ulen index) const -> FindResult
 {
  auto r=Range(list);

  for(index++; index<r.len ;index++) if( r[index].type==MenuText ) return index;

  return Null;
 }

auto MenuData::findFirst() const -> FindResult
 {
  auto r=Range(list);

  for(ulen index=0; index<r.len ;index++) if( r[index].type==MenuText ) return index;

  return Null;
 }

/* class MenuShapeBase */

Coordinate MenuShapeBase::GetDX(const MenuPoint &point,const Font &font,Coordinate space)
 {
  switch( point.type )
    {
     case MenuText :
     case MenuDisabled :
      {
       StrLen str=point.text.str();

       if( ulen s=point.hotindex )
         {
          StrLen str1=str.prefix(s-1);
          StrLen str2=str.part(s);

          TextSize ts=font->text(str1,str2);

          return ts.full_dx+2*space;
         }
       else
         {
          TextSize ts=font->text(str);

          return ts.full_dx+2*space;
         }
      }
     break;

     default:
      {
       return 0;
      }
    }
 }

Coordinate MenuShapeBase::GetDX(const MenuPoint &point,const Font &font,Coordinate space,Coordinate dy)
 {
  if( point.type==MenuSeparator ) return dy/5;

  return GetDX(point,font,space);
 }

VColor MenuShapeBase::PlaceFunc::place(ulen index_,Char,Point base_,Point delta_)
 {
  if( index==index_ )
    {
     base=base_;
     delta=delta_;
    }

  return vc;
 }

VColor MenuShapeBase::HotFunc::hot(ulen index_,Char,Point,Point)
 {
  if( index==index_ ) return hotc;

  return vc;
 }

void MenuShapeBase::drawText(const DrawBuf &buf,const MenuPoint &point,Pane pane,const Font &font,AlignX align_x,VColor vc,bool showhot) const
 {
  StrLen str=point.text.str();

  if( ulen s=point.hotindex )
    {
     StrLen str1=str.prefix(s-1);
     StrLen str2=str.part(s);

     if( showhot )
       {
        if( +cfg.hotcolor )
          {
           HotFunc func(vc,SymLen(str1),+cfg.hot);

           font->text(buf,pane,{align_x,AlignY_Center},str1,str2,func.function_hot());
          }
        else
          {
           PlaceFunc func(vc,SymLen(str1));

           font->text(buf,pane,{align_x,AlignY_Center},str1,str2,func.function_place());

           Point base=pane.getBase()+func.base;

           MCoord width=+cfg.width;

           base=base.addY(RoundUpLen(width));

           SmoothDrawArt art(buf);

           art.path(HalfNeg,width,+cfg.select,base,base+func.delta);
          }
       }
     else
       {
        font->text(buf,pane,{align_x,AlignY_Center},str1,str2,vc);
       }
    }
  else
    {
     font->text(buf,pane,{align_x,AlignY_Center},str,vc);
    }
 }

void MenuShapeBase::drawX(const DrawBuf &buf,Pane pane) const
 {
  SmoothDrawArt art(buf);

  MPane p(pane);

  YField field(p.y,+cfg.snow,p.ey,+cfg.gray);

  FigureBox(p).solid(art,field);
 }

void MenuShapeBase::drawY(const DrawBuf &buf,Pane pane) const
 {
  SmoothDrawArt art(buf);

  MPane p(pane);

  XField field(p.x,+cfg.snow,p.ex,+cfg.gray);

  FigureBox(p).solid(art,field);
 }

/* class SimpleTopMenuShape */

SizeY SimpleTopMenuShape::getMinSize(unsigned) const
 {
  const Font &font=cfg.font.get();
  FontSize fs=font->getSize();
  Point space=+cfg.space;

  return fs.dy+2*Coordinate(space.y);
 }

bool SimpleTopMenuShape::isGoodSize(Point size) const
 {
  Point min_size(menu_dx,getMinSize(LayoutResize).dy);

  return size>=min_size;
 }

void SimpleTopMenuShape::layout(unsigned update_flag)
 {
  if( update_flag || !ok )
    {
     const Font &font=cfg.font.get();
     FontSize fs=font->getSize();
     Point space=+cfg.space;

     Coordinate dy=fs.dy+2*Coordinate(space.y);
     Coordinate x=0;

     for(MenuPoint &point : data.list )
       {
        Coordinate dx=GetDX(point,font,space.x,dy);

        point.place=Pane(x,0,dx,dy)+pane.getBase();

        x+=dx;
       }

     menu_dx=+x;

     xoffMax=PlusSub(menu_dx,pane.dx);

     Replace_min(xoff,xoffMax);

     dxoff=fs.medDX();

     ok=true;
    }
 }

void SimpleTopMenuShape::draw(const DrawBuf &buf) const
 {
  MCoord width=+cfg.width;

  VColor text=+cfg.text;
  VColor inactive=+cfg.inactive;
  VColor hilight=+cfg.hilight;
  VColor select=+cfg.select;

  const Font &font=cfg.font.get();

  SmoothDrawArt art(buf.cut(pane));

  // back

  {
   art.block(pane,+cfg.back);

   MPane p(pane);

   art.path(HalfPos,width,+cfg.gray,p.getBottomLeft(),p.getBottomRight());
  }

  // text

  auto r=Range(data.list);

  for(ulen i=0; i<r.len ;i++)
    {
     const MenuPoint &point=r[i];

     Pane pane=point.place-Point(xoff,0);

     switch( point.type )
       {
        case MenuText :
         {
          if( BitTest(state,MenuSelect) && select_index==i )
            {
             FigureBox(pane).loop(art,HalfPos,width,select);

             drawText(buf,point,pane,font,AlignX_Center,hilight,focus);
            }
          else if( BitTest(state,MenuHilight) && hilight_index==i )
            {
             MPane p(pane);

             art.path(HalfPos,width,hilight,p.getBottomLeft(),p.getBottomRight());

             drawText(buf,point,pane,font,AlignX_Center,hilight,focus);
            }
          else
            {
             drawText(buf,point,pane,font,AlignX_Center,text,focus);
            }
         }
        break;

        case MenuDisabled :
         {
          drawText(buf,point,pane,font,AlignX_Center,inactive);
         }
        break;

        case MenuHidden :
         {
          // do nothing
         }
        break;

        case MenuSeparator :
         {
          drawY(buf,pane);
         }
       }
    }

  // markers

  if( xoff>0 )
    {
     Coord len=pane.dy/3;

     Pane p(pane.x,pane.y+pane.dy-len,len,len);

     FigureLeftArrow(p).curveSolid(art,hilight);
    }

  if( xoff<xoffMax )
    {
     Coord len=pane.dy/3;

     Pane p(pane.x+pane.dx-len,pane.y+pane.dy-len,len,len);

     FigureRightArrow(p).curveSolid(art,hilight);
    }
 }

/* class SimpleCascadeMenuShape */

void SimpleCascadeMenuShape::drawFrame(const DrawBuf &buf) const
 {
  SmoothDrawArt art(buf);

  art.block(pane,+cfg.back);

  FigureTopBorder(pane,+cfg.width).solid(art,+cfg.snow);

  FigureBottomBorder(pane,+cfg.width).solid(art,+cfg.gray);
 }

void SimpleCascadeMenuShape::drawMenu(const DrawBuf &buf) const
 {
  if( !data ) return;

  MCoord width=+cfg.width;

  VColor text=+cfg.text;
  VColor inactive=+cfg.inactive;
  VColor hilight=+cfg.hilight;
  VColor select=+cfg.select;

  const Font &font=cfg.font.get();

  SmoothDrawArt art(buf);

  // text

  auto r=Range(data->list);

  for(ulen i=0; i<r.len ;i++)
    {
     const MenuPoint &point=r[i];

     Pane pane=point.place-Point(0,yoff);

     switch( point.type )
       {
        case MenuText :
         {
          if( BitTest(state,MenuSelect) && select_index==i )
            {
             FigureBox(pane).loop(art,HalfPos,width,select);

             drawText(buf,point,pane,font,AlignX_Left,hilight,focus);
            }
          else if( BitTest(state,MenuHilight) && hilight_index==i )
            {
             MPane p(pane);

             art.path(HalfPos,width,hilight,p.getBottomLeft(),p.getBottomRight());

             drawText(buf,point,pane,font,AlignX_Left,hilight,focus);
            }
          else
            {
             drawText(buf,point,pane,font,AlignX_Left,text,focus);
            }
         }
        break;

        case MenuDisabled :
         {
          drawText(buf,point,pane,font,AlignX_Left,inactive);
         }
        break;

        case MenuHidden :
         {
          // do nothing
         }
        break;

        case MenuSeparator :
         {
          drawX(buf,pane);
         }
       }
    }

  // markers

  if( yoff>0 )
    {
     Coord len=cell_dy/3;

     Pane p(pane.x+pane.dx-len,pane.y,len,len);

     FigureUpArrow(p).curveSolid(art,hilight);
    }

  if( yoff<yoffMax )
    {
     Coord len=cell_dy/3;

     Pane p(pane.x+pane.dx-len,pane.y+pane.dy-len,len,len);

     FigureDownArrow(p).curveSolid(art,hilight);
    }
 }

Point SimpleCascadeMenuShape::getMinSize(unsigned) const
 {
  const Font &font=cfg.font.get();
  FontSize fs=font->getSize();
  Point space=+cfg.space;

  Coordinate dy=fs.dy+2*Coordinate(space.y);
  Coordinate dx=dy;
  Coordinate y=0;

  if( !data ) return Point(dx,0);

  for(const MenuPoint &point : data->list )
    switch( point.type )
      {
       case MenuText :
       case MenuDisabled :
        {
         Coordinate tdx=GetDX(point,font,space.x);

         Replace_max(dx,tdx);

         y+=dy;
        }
       break;

       case MenuSeparator :
        {
         Coordinate sdy=dy/5;

         y+=sdy;
        }
       break;
      }

  Coord delta=RoundUpLen(+cfg.width);

  return Point(dx,y)+2*Point::Diag(delta);
 }

void SimpleCascadeMenuShape::layout(unsigned)
 {
  const Font &font=cfg.font.get();
  FontSize fs=font->getSize();
  Point space=+cfg.space;

  Coordinate dy=fs.dy+2*Coordinate(space.y);
  Coordinate y=0;

  cell_dy=+dy;

  if( !data )
    {
     yoff=0;
     yoffMax=0;

     return;
    }

  Coord delta=RoundUpLen(+cfg.width);

  Pane inner=pane.shrink(delta);

  for(MenuPoint &point : data->list )
    switch( point.type )
      {
       case MenuText :
       case MenuDisabled :
        {
         Pane pane=Pane(0,y,inner.dx,dy)+inner.getBase();

         point.place=pane.shrink(delta,0);

         y+=dy;
        }
       break;

       case MenuSeparator :
        {
         Coordinate sdy=dy/5;

         Pane pane=Pane(0,y,inner.dx,sdy)+inner.getBase();

         point.place=pane.shrink(delta,0);

         y+=sdy;
        }
       break;

       default:
        {
         point.place=Empty;
        }
      }

  yoffMax=PlusSub(+y,inner.dy);

  Replace_min(yoff,yoffMax);
 }

void SimpleCascadeMenuShape::draw(const DrawBuf &buf) const
 {
  drawFrame(buf.cut(pane));

  Coord delta=RoundUpLen(+cfg.width);

  drawMenu(buf.cut(pane.shrink(delta)));
 }

} // namespace Video
} // namespace CCore

