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

/* SplitBox() */

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

/* SplitBoxRight() */

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

