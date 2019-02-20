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

#include <inc/ColorListWindow.h>

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

/* class ColorListShape */

Point ColorListShape::getMinSize(Point cap) const // TODO
 {
 }

Point ColorListShape::getMinSize(unsigned lines) const // TODO
 {
 }

void ColorListShape::layout() // TODO
 {
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

ulen ColorListShape::getPosition(Point point) const // TODO
 {
  Pane inner=pane.shrink(+cfg.space);

  if( !inner ) return 0;

  if( point.y<inner.y ) return yoff?yoff-1:0;

  if( point.y>=inner.y+inner.dy ) return yoff+page;

  FontSize fs=cfg.font->getSize();

  return yoff+ulen((point.y-inner.y)/fs.dy);
 }

void ColorListShape::draw(const DrawBuf &buf) const // TODO
 {
 }

} // namespace Video
} // namespace CCore

