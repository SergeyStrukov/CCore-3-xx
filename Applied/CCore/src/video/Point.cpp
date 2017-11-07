/* Point.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {

/* functions */

DCoord Length(MCoord a,MCoord b)
 {
  uMCoord A=IntAbs(a);
  uMCoord B=IntAbs(b);

  uMCoord x=Max(A,B);

  if( x==0 ) return 0;

  return UIntFunc<uDCoord>::SqRoot(uDCoord(A)*A+uDCoord(B)*B,x);
 }

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

/* struct PaneSub */

PaneSub::PaneSub(Pane outer,Pane inner)
 {
  if( !outer ) return;

  if( !inner )
    {
     top=outer;

     return;
    }

  inner=Inf_nonempty(outer,inner);

  if( !inner )
    {
     top=outer;

     return;
    }

  top.x=outer.x;
  top.y=outer.y;
  top.dx=outer.dx;
  top.dy=inner.y-outer.y;

  left.x=outer.x;
  left.y=inner.y;
  left.dx=inner.x-outer.x;
  left.dy=inner.dy;

  right.x=inner.x+inner.dx;
  right.y=inner.y;
  right.dx=outer.x+outer.dx-right.x;
  right.dy=inner.dy;

  bottom.x=outer.x;
  bottom.y=inner.y+inner.dy;
  bottom.dx=outer.dx;
  bottom.dy=outer.y+outer.dy-bottom.y;
 }

} // namespace Video
} // namespace CCore


