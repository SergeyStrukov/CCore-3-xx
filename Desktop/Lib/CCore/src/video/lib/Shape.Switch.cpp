/* Shape.Switch.cpp */
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

#include <CCore/inc/video/lib/Shape.Switch.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class SwitchShape */

SizeBox SwitchShape::getMinSize() const
 {
  return +cfg.dxy;
 }

void SwitchShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  p.square();

  SmoothDrawArt art(buf.cut(pane));

  MCoord len=p.dx;
  MCoord radius=len/2;
  MCoord width=len/16;

  MPoint a=p.getTopLeft();
  MPoint center=p.getCenter();

  VColor snow=+cfg.snow;
  VColor gray=+cfg.gray;

  // body

  if( check )
    {
     art.ball(center,radius,TwoField(a,snow,p.getTopRight(),gray));

     art.ball(center,radius/2, enable? +cfg.on : gray );
    }
  else
    {
     art.ball(center,radius,TwoField(a,snow,p.getBottomLeft(),gray));

     art.ball(center,radius/2, enable? +cfg.off : gray );
    }

  // border

  {
   VColor border = focus? +cfg.focus : ( enable? +cfg.border : gray ) ;

   art.circle(center,radius-width/2,width,border);
  }

  // face

  {
   MCoord d1=len/20;
   MCoord d2=len/8;

   FigurePoints<6> fig;

   if( check )
     {
      fig[0]={radius+d1,0};
      fig[1]={radius-d1,0};
      fig[2]={radius-d2,radius};
      fig[3]={radius-d1,len};
      fig[4]={radius+d1,len};
      fig[5]={radius+d2,radius};
     }
   else
     {
      fig[0]={0,radius+d1};
      fig[1]={0,radius-d1};
      fig[2]={radius,radius-d2};
      fig[3]={len,radius-d1};
      fig[4]={len,radius+d1};
      fig[5]={radius,radius+d2};
     }

   fig.shift(a);

   VColor face = enable? ( mover? +cfg.faceUp : +cfg.face ) : gray ;

   fig.solid(art,face);
  }
 }

} // namespace Video
} // namespace CCore

