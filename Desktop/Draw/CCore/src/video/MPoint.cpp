/* MPoint.cpp */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/MPoint.h>

namespace CCore {
namespace Video {

/* struct Ratio */

Ratio Ratio::pow(unsigned deg) const
 {
  if( !deg ) return Ratio(1,0);

  BitScanner<unsigned> scanner(deg);

  Ratio ret(*this);

  for(++scanner; +scanner ;++scanner)
    if( *scanner )
      {
       ret=Sq(ret)*(*this);
      }
    else
      {
       ret=Sq(ret);
      }

  return ret;
 }

/* AdjustAspect() */

Pane AdjustAspect(Point aspect,Pane pane)
 {
  Coord dy=YdivX(aspect)*pane.dx;

  if( pane.dy>dy ) return AlignCenterY(pane,dy);

  return AlignCenterX(pane,XdivY(aspect)*pane.dy);
 }

/* Length() */

DCoord Length(MCoord a,MCoord b)
 {
  uMCoord A=IntAbs(a);
  uMCoord B=IntAbs(b);

  uMCoord x=Max(A,B);

  if( x==0 ) return 0;

  return UIntFunc<uDCoord>::SqRoot(UDMul(A,A)+UDMul(B,B),x);
 }

} // namespace Video
} // namespace CCore

