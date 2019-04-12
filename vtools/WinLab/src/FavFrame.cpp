/* FavFrame.cpp */
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

//#include <CCore/inc/video/FavFrame.h>
#include <inc/FavFrame.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class FavListShape */

Point FavListShape::getMinSize() const
 {
  return Point(100,100);
 }

void FavListShape::layout() // TODO
 {
 }

void FavListShape::draw(const DrawBuf &buf,DrawParam) const // TODO
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;

  const Font &font=cfg.font.get();

  // lines

  {
   Point space=+cfg.space;
   Pane inner=pane.shrink(space);

   if( +inner )
     {
      VColor gray=+cfg.gray;
      VColor text=+cfg.text;

      FontSize fs=font->getSize();

      Coord h=fs.dy+space.y;
      MCoord H=Fraction(h);

      ulen count=inner.dy/h;

      MPoint A=MPointTopLeft(inner.getBase());
      MPoint B=MPointTopLeft(inner.addDX());

      art.path(width,gray,A,B);

      Point base=inner.getBase().addY(fs.by)+space/2;

      auto drawItem = [&] (StrLen title,StrLen path,bool section,bool open)
                          {
                           font->textOn(art,pane,TextPlace(base),title,text);

                           Used(path);
                           Used(section);
                           Used(open);

                           A=A.addY(H);
                           B=B.addY(H);
                           base=base.addY(h);

                           art.path(width,gray,A,B);
                          } ;

      fav_list.apply(count,drawItem);
     }
  }

  // border

  {
   VColor border = focus? +cfg.focus : +cfg.border ;

   FigureBox fig(p);

   fig.loop(art,HalfPos,width,border);
  }
 }

} // namespace Video
} // namespace CCore

