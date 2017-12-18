/* FrameBase.cpp */
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

#include <CCore/inc/video/FrameBase.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* functions */

void GuardNoClient()
 {
  Printf(Exception,"CCore::Video::GuardNoClient() : no client is attached to a frame window");
 }

void GuardNotDead()
 {
  Printf(Exception,"CCore::Video::GuardNotDead() : frame window is alive");
 }

/* DragPane() */

void DragPane(Pane &place,Point delta,DragType drag_type)
 {
  switch( drag_type )
    {
     case DragType_Top :
      {
       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;

     case DragType_TopLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;

       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;

     case DragType_Left :
      {
       place.x+=delta.x;
       place.dx-=delta.x;
      }
     break;

     case DragType_BottomLeft :
      {
       place.x+=delta.x;
       place.dx-=delta.x;

       place.dy+=delta.y;
      }
     break;

     case DragType_Bottom :
      {
       place.dy+=delta.y;
      }
     break;

     case DragType_BottomRight :
      {
       place.dx+=delta.x;

       place.dy+=delta.y;
      }
     break;

     case DragType_Right :
      {
       place.dx+=delta.x;
      }
     break;

     case DragType_TopRight :
      {
       place.dx+=delta.x;

       place.y+=delta.y;
       place.dy-=delta.y;
      }
     break;

     case DragType_Bar :
      {
       place.x+=delta.x;

       place.y+=delta.y;
      }
     break;
    }
 }

/* class RedrawSet */

AreaType RedrawSet::Excess(Pane a,Pane b,Pane c)
 {
  Pane d=Inf(a,b);

  return c.getArea()+d.getArea()-a.getArea()-b.getArea();
 }

void RedrawSet::compress(Pane pane)
 {
  Pane *dst=0;
  Pane src;
  AreaType best_e=0;

  for(Pane &p : set )
    {
     Pane q=Sup_nonempty(p,pane);
     AreaType e=Excess(p,pane,q);

     if( !dst || e<best_e )
       {
        dst=&p;
        src=q;
        best_e=e;

        if( !e ) break;
       }
    }

  *dst=src;
 }

bool RedrawSet::add(Pane pane)
 {
  if( +pane )
    {
     bool ret=!count;

     if( count<Len )
       {
        set[count++]=pane;
       }
     else
       {
        compress(pane);
       }

     return ret;
    }

  return false;
 }

PtrLen<Pane> RedrawSet::pop()
 {
  return Range(set,Replace_null(count));
 }

} // namespace Video
} // namespace CCore

