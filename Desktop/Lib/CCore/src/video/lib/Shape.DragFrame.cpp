/* Shape.DragFrame.cpp */
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

#include <CCore/inc/video/lib/Shape.DragFrame.h>

namespace CCore {
namespace Video {

/* class DragShape */

VColor DragFrameShape::dragColor(DragType zone) const
 {
  if( drag_type==zone ) return +cfg.dragActive;

  if( hilight==zone ) return +cfg.dragHilight;

  return +cfg.drag;
 }

void DragFrameShape::draw_Frame(const DrawBuf &buf,Pane part) const
 {
  VColor frame=+cfg.frame;
  VColor small=+cfg.dragSmall;
  VColor frameSmall = has_good_size? frame : small ;

  drawFrame(buf,Pane(Null,size),client,frame,frameSmall,part);
 }

void DragFrameShape::draw_Frame(const DrawBuf &buf) const
 {
  draw_Frame(buf,Pane(Null,size));
 }

void DragFrameShape::draw_Frame(const DrawBuf &buf,DragType drag_type) const
 {
  Pane part=getPane(drag_type);

  draw_Frame(buf.cut(part),part);
 }

void DragFrameShape::draw_TopLeft(const DrawBuf &buf) const
 {
  drawTopLeft(buf,dragTopLeft,dragColor(DragType_TopLeft));
 }

void DragFrameShape::draw_Left(const DrawBuf &buf) const
 {
  drawLeft(buf,dragLeft,dragColor(DragType_Left));
 }

void DragFrameShape::draw_BottomLeft(const DrawBuf &buf) const
 {
  drawBottomLeft(buf,dragBottomLeft,dragColor(DragType_BottomLeft));
 }

void DragFrameShape::draw_Bottom(const DrawBuf &buf) const
 {
  drawBottom(buf,dragBottom,dragColor(DragType_Bottom));
 }

void DragFrameShape::draw_BottomRight(const DrawBuf &buf) const
 {
  drawBottomRight(buf,dragBottomRight,dragColor(DragType_BottomRight));
 }

void DragFrameShape::draw_Right(const DrawBuf &buf) const
 {
  drawRight(buf,dragRight,dragColor(DragType_Right));
 }

void DragFrameShape::draw_TopRight(const DrawBuf &buf) const
 {
  drawTopRight(buf,dragTopRight,dragColor(DragType_TopRight));
 }

void DragFrameShape::draw_Bar(const DrawBuf &buf) const
 {
  drawBar(buf,titleBar);
 }

void DragFrameShape::draw_Alert(const DrawBuf &buf) const
 {
  drawAlert(buf,btnAlert);
 }

void DragFrameShape::draw_Help(const DrawBuf &buf) const
 {
  drawHelp(buf,btnHelp);
 }

void DragFrameShape::draw_Min(const DrawBuf &buf) const
 {
  drawMin(buf,btnMin);
 }

void DragFrameShape::draw_Max(const DrawBuf &buf) const
 {
  drawMax(buf,btnMax,max_button);
 }

void DragFrameShape::draw_Close(const DrawBuf &buf) const
 {
  drawClose(buf,btnClose);
 }

void DragFrameShape::reset(const String &title_,bool is_main_,bool max_button_)
 {
  FrameShapeBase::reset(title_,is_main_);

  max_button=max_button_;
 }

void DragFrameShape::layout(Point size_)
 {
  size=size_;

  Coord dxy=+cfg.frame_dxy;
  Coord tdy=+cfg.title_dy;
  Coord bdx=+cfg.btn_dx;
  Coord bdy=+cfg.btn_dy;

  Coord btn_len = is_main? 6*bdx+bdx/8 : 4*bdx ;

  if( size>=Point( 2*dxy+btn_len+bdx/2+Max(tdy,dxy) , dxy+Max(tdy,dxy) ) )
    {
     Pane pane=Pane(Null,size);

     Pane left=SplitX(dxy,pane);
     Pane right=SplitX(pane,dxy);

     dragTopLeft=SplitY(dxy,left);
     dragBottomLeft=SplitY(left,dxy);
     dragLeft=left;

     dragTopRight=SplitY(dxy,right);
     dragBottomRight=SplitY(right,dxy);
     dragRight=right;

     dragBar=SplitY(tdy,pane);
     dragBottom=SplitY(pane,dxy);

     client=pane;

     Coord yb=(tdy-bdy)/2;

     Coord tx=dragBar.dx-btn_len;

     if( is_main )
       {
        Coord xb0=dragBar.x+tx;
        Coord xb1=xb0+bdx+bdx/8;
        Coord xb2=xb1+bdx+bdx/8;
        Coord xb3=xb2+bdx+bdx/8;
        Coord xb4=xb3+bdx+bdx/2;

        btnAlert=Pane(xb0,yb,bdx,bdy);
        btnHelp=Pane(xb1,yb,bdx,bdy);
        btnMin=Pane(xb2,yb,bdx,bdy);
        btnMax=Pane(xb3,yb,bdx,bdy);
        btnClose=Pane(xb4,yb,bdx,bdy);
       }
     else
       {
        Coord xb0=dragBar.x+tx;
        Coord xb1=xb0+bdx+bdx/8;
        Coord xb2=xb1+bdx+bdx/2;

        btnAlert=Empty;
        btnMin=Empty;
        btnHelp=Pane(xb0,yb,bdx,bdy);
        btnMax=Pane(xb1,yb,bdx,bdy);
        btnClose=Pane(xb2,yb,bdx,bdy);
       }

     Coord w=cfg.width.get().roundUp();

     titleBar=Pane(dragBar.x+bdx/4,w,tx-bdx/2,tdy-2*w);
    }
  else
    {
     dragTopLeft=Empty;
     dragBottomLeft=Empty;
     dragLeft=Empty;

     dragTopRight=Empty;
     dragBottomRight=Pane(Null,size);
     dragRight=Empty;

     dragBar=Empty;
     dragBottom=Empty;

     client=Empty;

     btnAlert=Empty;
     btnHelp=Empty;
     btnMin=Empty;
     btnMax=Empty;
     btnClose=Empty;

     titleBar=Empty;
    }
 }

Point DragFrameShape::getDeltaSize() const
 {
  Coord dxy=+cfg.frame_dxy;
  Coord tdy=+cfg.title_dy;

  return Point(dxy,tdy)+Point(dxy,dxy);
 }

Coord DragFrameShape::getMinDX(bool is_main,StrLen title) const
 {
  Coord width=cfg.width.get().roundUp();
  Coord tdy=+cfg.title_dy;

  Coord dxy=+cfg.frame_dxy;
  Coord bdx=+cfg.btn_dx;

  Coord btn_len = is_main? 6*bdx+bdx/8 : 4*bdx ;

  Coord dx=getMinTitleDX(title,tdy-2*width);

  Replace_max(dx,Max(tdy,dxy));

  dx += 2*dxy+btn_len+bdx/2 ;

  return dx;
 }

DragType DragFrameShape::dragTest(Point point) const
 {
  if( dragTopLeft.contains(point) ) return DragType_TopLeft;

  if( dragLeft.contains(point) ) return DragType_Left;

  if( dragBottomLeft.contains(point) ) return DragType_BottomLeft;

  if( dragBottom.contains(point) ) return DragType_Bottom;

  if( dragBottomRight.contains(point) ) return DragType_BottomRight;

  if( dragRight.contains(point) ) return DragType_Right;

  if( dragTopRight.contains(point) ) return DragType_TopRight;

  if( dragBar.contains(point) )
    {
     if( btnAlert.contains(point) ) return DragType_Alert;

     if( btnHelp.contains(point) ) return DragType_Help;

     if( btnMin.contains(point) ) return DragType_Min;

     if( btnMax.contains(point) ) return DragType_Max;

     if( btnClose.contains(point) ) return DragType_Close;

     return DragType_Bar;
    }

  return DragType_None;
 }

Pane DragFrameShape::getPane(DragType drag_type) const
 {
  switch( drag_type )
    {
     case DragType_TopLeft     : return dragTopLeft;
     case DragType_Left        : return dragLeft;
     case DragType_BottomLeft  : return dragBottomLeft;
     case DragType_Bottom      : return dragBottom;
     case DragType_BottomRight : return dragBottomRight;
     case DragType_Right       : return dragRight;
     case DragType_TopRight    : return dragTopRight;

     case DragType_Alert       : return btnAlert;
     case DragType_Help        : return btnHelp;
     case DragType_Min         : return btnMin;
     case DragType_Max         : return btnMax;
     case DragType_Close       : return btnClose;

     default: return Empty;
    }
 }

Hint DragFrameShape::getHint(Point point) const
 {
  switch( dragTest(point) )
    {
     case DragType_TopLeft     : return {dragTopLeft,+cfg.hint_ResizeTopLeft};
     case DragType_Left        : return {dragLeft,+cfg.hint_ResizeLeft};
     case DragType_BottomLeft  : return {dragBottomLeft,+cfg.hint_ResizeBottomLeft};
     case DragType_Bottom      : return {dragBottom,+cfg.hint_ResizeBottom};
     case DragType_BottomRight : return {dragBottomRight,+cfg.hint_ResizeBottomRight};
     case DragType_Right       : return {dragRight,+cfg.hint_ResizeRight};
     case DragType_TopRight    : return {dragTopRight,+cfg.hint_ResizeTopRight};

     case DragType_Alert       : return {btnAlert,+cfg.hint_Alert};
     case DragType_Help        : return {btnHelp,+cfg.hint_Help};
     case DragType_Min         : return {btnMin,+cfg.hint_Minimize};
     case DragType_Max         : return {btnMax, max_button? +cfg.hint_Maximize : +cfg.hint_Restore };
     case DragType_Close       : return {btnClose,+cfg.hint_Close};

     default: return Null;
    }
 }

void DragFrameShape::draw(const DrawBuf &buf) const
 {
  draw_Frame(buf);

  draw_TopLeft(buf);
  draw_Left(buf);
  draw_BottomLeft(buf);
  draw_Bottom(buf);
  draw_BottomRight(buf);
  draw_Right(buf);
  draw_TopRight(buf);

  draw_Bar(buf);

  draw_Alert(buf);
  draw_Help(buf);
  draw_Min(buf);
  draw_Max(buf);
  draw_Close(buf);
 }

void DragFrameShape::draw(const DrawBuf &buf,DragType drag_type) const
 {
  draw_Frame(buf,drag_type);

  switch( drag_type )
    {
     case DragType_TopLeft     : draw_TopLeft(buf); break;
     case DragType_Left        : draw_Left(buf); break;
     case DragType_BottomLeft  : draw_BottomLeft(buf); break;
     case DragType_Bottom      : draw_Bottom(buf); break;
     case DragType_BottomRight : draw_BottomRight(buf); break;
     case DragType_Right       : draw_Right(buf); break;
     case DragType_TopRight    : draw_TopRight(buf); break;

     case DragType_Alert       : draw_Alert(buf); break;
     case DragType_Help        : draw_Help(buf); break;
     case DragType_Min         : draw_Min(buf); break;
     case DragType_Max         : draw_Max(buf); break;
     case DragType_Close       : draw_Close(buf); break;
    }
 }

void DragFrameShape::drawHint(const DrawBuf &buf,Hint hint) const
 {
  FrameShapeBase::drawHint(buf,titleBar,hint);
 }

} // namespace Video
} // namespace CCore

