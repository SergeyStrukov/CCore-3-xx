/* Shape.FixedFrame.cpp */
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

#include <CCore/inc/video/lib/Shape.FixedFrame.h>

namespace CCore {
namespace Video {

/* class FixedFrameShape */

void FixedFrameShape::draw_Frame(const DrawBuf &buf,Pane part) const
 {
  VColor frame=+cfg.frame;
  VColor small=+cfg.dragSmall;
  VColor frameSmall = has_good_size? frame : small ;

  if( hilight==DragType_Bar ) frameSmall=frame=+cfg.frameHilight;

  if( drag_type==DragType_Bar ) frameSmall=frame=+cfg.frameDrag;

  drawFrame(buf,Pane(Null,size),client,frame,frameSmall,part);
 }

void FixedFrameShape::draw_Frame(const DrawBuf &buf) const
 {
  draw_Frame(buf,Pane(Null,size));
 }

void FixedFrameShape::draw_Frame(const DrawBuf &buf,DragType drag_type) const
 {
  Pane part=getPane(drag_type);

  draw_Frame(buf.cut(part),part);
 }

void FixedFrameShape::draw_Bar(const DrawBuf &buf) const
 {
  drawBar(buf,titleBar);
 }

void FixedFrameShape::draw_Alert(const DrawBuf &buf) const
 {
  drawAlert(buf,btnAlert);
 }

void FixedFrameShape::draw_Help(const DrawBuf &buf) const
 {
  drawHelp(buf,btnHelp);
 }

void FixedFrameShape::draw_Min(const DrawBuf &buf) const
 {
  drawMin(buf,btnMin);
 }

void FixedFrameShape::draw_Close(const DrawBuf &buf) const
 {
  drawClose(buf,btnClose);
 }

void FixedFrameShape::layout(Point size_)
 {
  size=size_;

  Coord dxy=+cfg.frame_dxy;
  Coord tdy=+cfg.title_dy;
  Coord bdx=+cfg.btn_dx;
  Coord bdy=+cfg.btn_dy;

  Coord btn_len = is_main? 5*bdx : 3*bdx ;

  if( size>Point( 2*dxy+btn_len+bdx/2+Max(tdy,dxy) , dxy+Max(tdy,dxy) ) )
    {
     Pane pane=Pane(Null,size);

     SplitX(dxy,pane);
     SplitX(pane,dxy);

     Pane top=SplitY(tdy,pane);

     SplitY(pane,dxy);

     client=pane;

     Coord yb=(tdy-bdy)/2;

     Coord tx=top.dx-btn_len;

     if( is_main )
       {
        Coord xb0=top.x+tx;
        Coord xb1=xb0+bdx+bdx/8;
        Coord xb2=xb1+bdx+bdx/8;
        Coord xb3=xb2+bdx+bdx/2;

        btnAlert=Pane(xb0,yb,bdx,bdy);
        btnHelp=Pane(xb1,yb,bdx,bdy);
        btnMin=Pane(xb2,yb,bdx,bdy);
        btnClose=Pane(xb3,yb,bdx,bdy);
       }
     else
       {
        Coord xb0=top.x+tx;
        Coord xb1=xb0+bdx+bdx/2;

        btnAlert=Empty;
        btnMin=Empty;
        btnHelp=Pane(xb0,yb,bdx,bdy);
        btnClose=Pane(xb1,yb,bdx,bdy);
       }

     Coord w=cfg.width.get().roundUp();

     titleBar=Pane(top.x+bdx/4,w,tx-bdx/2,tdy-2*w);
    }
  else
    {
     client=Empty;

     btnAlert=Empty;
     btnHelp=Empty;
     btnMin=Empty;
     btnClose=Pane(Null,bdx,bdy);

     titleBar=Empty;
    }
 }

Point FixedFrameShape::getDeltaSize() const
 {
  Coord dxy=+cfg.frame_dxy;
  Coord tdy=+cfg.title_dy;

  return Point(dxy,tdy)+Point(dxy,dxy);
 }

Coord FixedFrameShape::getMinDX(bool is_main,StrLen title) const
 {
  Coord width=cfg.width.get().roundUp();
  Coord tdy=+cfg.title_dy;

  Coord dxy=+cfg.frame_dxy;
  Coord bdx=+cfg.btn_dx;

  Coord btn_len = is_main? 5*bdx : 3*bdx ;

  Coord dx=getMinTitleDX(title,tdy-2*width);

  Replace_max(dx,Max(tdy,dxy));

  dx += 2*dxy+btn_len+bdx/2 ;

  return dx;
 }

DragType FixedFrameShape::dragTest(Point point) const
 {
  if( btnAlert.contains(point) ) return DragType_Alert;

  if( btnHelp.contains(point) ) return DragType_Help;

  if( btnMin.contains(point) ) return DragType_Min;

  if( btnClose.contains(point) ) return DragType_Close;

  return client.contains(point)?DragType_None:DragType_Bar;
 }

Pane FixedFrameShape::getPane(DragType drag_type) const
 {
  switch( drag_type )
    {
     case DragType_Bar : return Pane(Null,size);

     case DragType_Alert       : return btnAlert;
     case DragType_Help        : return btnHelp;
     case DragType_Min         : return btnMin;
     case DragType_Close       : return btnClose;

     default: return Empty;
    }
 }

Hint FixedFrameShape::getHint(Point point) const
 {
  switch( dragTest(point) )
    {
     case DragType_Alert       : return {btnAlert,+cfg.hint_Alert};
     case DragType_Help        : return {btnHelp,+cfg.hint_Help};
     case DragType_Min         : return {btnMin,+cfg.hint_Minimize};
     case DragType_Close       : return {btnClose,+cfg.hint_Close};

     default: return Null;
    }
 }

void FixedFrameShape::draw(const DrawBuf &buf) const
 {
  draw_Frame(buf);

  draw_Bar(buf);

  draw_Alert(buf);
  draw_Help(buf);
  draw_Min(buf);
  draw_Close(buf);
 }

void FixedFrameShape::draw(const DrawBuf &buf,DragType drag_type) const
 {
  if( drag_type==DragType_Bar )
    {
     draw_Frame(buf);

     draw_Bar(buf);

     draw_Alert(buf);
     draw_Help(buf);
     draw_Min(buf);
     draw_Close(buf);
    }
  else
    {
     draw_Frame(buf,drag_type);

     switch( drag_type )
       {
        case DragType_Alert       : draw_Alert(buf); break;
        case DragType_Help        : draw_Help(buf); break;
        case DragType_Min         : draw_Min(buf); break;
        case DragType_Close       : draw_Close(buf); break;
       }
    }
 }

void FixedFrameShape::drawHint(const DrawBuf &buf,Hint hint) const
 {
  FrameShapeBase::drawHint(buf,titleBar,hint);
 }

} // namespace Video
} // namespace CCore

