/* Shape.Switch.cpp */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/lib/Shape.Switch.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class SwitchShape */

struct SwitchShape::Face : public FigurePoints<6>
 {
  Face(MPoint a,MCoord radius,MCoord len,bool check) CCORE_NOINLINE // compiler bug workaround
   {
    MCoord d1=len/20;
    MCoord d2=len/8;

    if( check )
      {
       buf[0]={radius+d1,0};
       buf[1]={radius-d1,0};
       buf[2]={radius-d2,radius};
       buf[3]={radius-d1,len};
       buf[4]={radius+d1,len};
       buf[5]={radius+d2,radius};
      }
    else
      {
       buf[0]={0,radius+d1};
       buf[1]={0,radius-d1};
       buf[2]={radius,radius-d2};
       buf[3]={len,radius-d1};
       buf[4]={len,radius+d1};
       buf[5]={radius,radius+d2};
      }

    shift(a);
   }
 };

SizeBox SwitchShape::getMinSize() const
 {
  return +cfg.dxy;
 }

void SwitchShape::draw(const DrawBuf &buf,DrawParam) const
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
   Face fig(a,radius,len,check);

   VColor face = enable? ( mover? +cfg.faceUp : +cfg.face ) : gray ;

   fig.solid(art,face);
  }
 }

} // namespace Video
} // namespace CCore

