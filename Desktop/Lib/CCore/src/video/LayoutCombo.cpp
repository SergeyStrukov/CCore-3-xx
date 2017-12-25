/* LayoutCombo.cpp */
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

#include <CCore/inc/video/LayoutCombo.h>

namespace CCore {
namespace Video {

/* Split...() */

Pane SplitToTop(Pane &pane,Coord dy,Coord space)
 {
  Pane ret;

  if( dy<=pane.dy )
    {
     ret=SplitY(pane,dy);

     SplitY(pane,space);
    }
  else
    {
     ret=Replace_null(pane);
    }

  return ret;
 }

Pane SplitToBottom(Pane &pane,Coord dy,Coord space)
 {
  Pane ret;

  if( dy<=pane.dy )
    {
     ret=SplitY(dy,pane);

     SplitY(space,pane);
    }
  else
    {
     ret=Replace_null(pane);
    }

  return ret;
 }

Pane SplitToLeft(Pane &pane,Coord dx,Coord space)
 {
  Pane ret;

  if( dx<=pane.dx )
    {
     ret=SplitX(pane,dx);

     SplitX(pane,space);
    }
  else
    {
     ret=Replace_null(pane);
    }

  return ret;
 }

Pane SplitToRight(Pane &pane,Coord dx,Coord space)
 {
  Pane ret;

  if( dx<=pane.dx )
    {
     ret=SplitX(dx,pane);

     SplitX(space,pane);
    }
  else
    {
     ret=Replace_null(pane);
    }

  return ret;
 }

Pane SplitBox(Pane &pane,Coord dx)
 {
  Coord space=BoxSpace(dx);

  Pane ret;

  if( dx<=pane.dx )
    {
     ret=SplitX(dx,pane);

     SplitX(space,pane);
    }
  else
    {
     ret=Replace_null(pane);
    }

  return ret;
 }

Pane SplitBoxRight(Pane &pane,Coord dx)
 {
  Coord space=BoxSpace(dx);

  Pane ret;

  if( dx<=pane.dx )
    {
     ret=SplitX(pane,dx);

     SplitX(pane,space);
    }
  else
    {
     ret=Replace_null(pane);
    }

  return ret;
 }

} // namespace Video
} // namespace CCore

