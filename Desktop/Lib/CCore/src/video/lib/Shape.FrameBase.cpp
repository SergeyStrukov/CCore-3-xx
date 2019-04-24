/* Shape.FrameBase.cpp */
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

#include <CCore/inc/video/lib/Shape.FrameBase.h>

#include <CCore/inc/video/FigureLib.h>

namespace CCore {
namespace Video {

/* class FrameShapeBase */

void FrameShapeBase::drawFrame(const DrawBuf &buf,Pane all,Pane client,VColor frame,VColor frameSmall,Pane part) const
 {
  SmoothDrawArt art(buf);

  VColor gray=+cfg.gray;

  if( !client )
    {
     art.block(all,frame);

     return;
    }

  PaneSub sub(all,client);

  MPane outer(all);
  MPane inner(client);

  // top

  Pane top=Inf(sub.top,part);

  if( +top )
    {
     MCoord y0=outer.y;
     MCoord y1=inner.y;

     FigureBox fig{MPane(top)};

     fig.solid(art,YField(y0,frame,y1,gray));
    }

  // bottom

  Pane bottom=Inf(sub.bottom,part);

  if( +bottom )
    {
     MCoord y0=inner.ey;
     MCoord y1=outer.ey;

     FigureBox fig{MPane(bottom)};

     fig.solid(art,YField(y0,frameSmall,y1,gray));
    }

  // left

  Pane left=Inf(sub.left,part);

  if( +left )
    {
     MCoord x0=outer.x;
     MCoord x1=inner.x;

     FigureBox fig{MPane(left)};

     fig.solid(art,XField(x0,frame,x1,gray));
    }

  {
   MCoord x0=outer.x;
   MCoord x1=inner.x;

   MCoord y0=outer.y;
   MCoord y1=inner.y;
   MCoord y2=inner.ey;
   MCoord y3=outer.ey;

   FigureBottomLeftArrow fig1(x0,x1,y0,y1);
   FigureTopLeftArrow fig2(x0,x1,y2,y3);

   XField field(x0,frame,x1,gray);

   fig1.solid(art,field);
   fig2.solid(art,field);
  }

  // right

  Pane right=Inf(sub.right,part);

  if( +right )
    {
     MCoord x0=inner.ex;
     MCoord x1=outer.ex;

     FigureBox fig{MPane(right)};

     fig.solid(art,XField(x0,frameSmall,x1,gray));
    }

  {
   MCoord x0=inner.ex;
   MCoord x1=outer.ex;

   MCoord y0=outer.y;
   MCoord y1=inner.y;
   MCoord y2=inner.ey;
   MCoord y3=outer.ey;

   FigureBottomRightArrow fig1(x0,x1,y0,y1);
   FigureTopRightArrow fig2(x0,x1,y2,y3);

   XField field(x0,frameSmall,x1,gray);

   fig1.solid(art,field);
   fig2.solid(art,field);
  }
 }

void FrameShapeBase::drawTopLeft(const DrawBuf &buf,Pane pane,VColor vc) const
 {
  if( +pane )
    {
     SmoothDrawArt art(buf);

     MPane p(pane);

     MCoord width=+cfg.width;

     FigureTopLeftArrow fig(p.shrink(width));

     fig.solid(art,vc);
    }
 }

void FrameShapeBase::drawLeft(const DrawBuf &buf,Pane pane,VColor vc) const
 {
  if( +pane )
    {
     SmoothDrawArt art(buf);

     MPane p(pane);

     MCoord d=p.dx/2;
     MCoord x0=p.x+d;

     MCoord y0=p.y+d;
     MCoord y1=p.ey-d;

     MCoord w=p.dx/4;

     art.path(w,vc,MPoint(x0,y0),MPoint(x0,y1));
    }
 }

void FrameShapeBase::drawBottomLeft(const DrawBuf &buf,Pane pane,VColor vc) const
 {
  if( +pane )
    {
     SmoothDrawArt art(buf);

     MPane p(pane);

     MCoord width=+cfg.width;

     FigureBottomLeftArrow fig(p.shrink(width));

     fig.solid(art,vc);
    }
 }

void FrameShapeBase::drawBottom(const DrawBuf &buf,Pane pane,VColor vc) const
 {
  if( +pane )
    {
     SmoothDrawArt art(buf);

     MPane p(pane);

     MCoord d=p.dy/2;
     MCoord y0=p.y+d;

     MCoord x0=p.x+d;
     MCoord x1=p.ex-d;

     MCoord w=p.dy/4;

     art.path(w,vc,MPoint(x0,y0),MPoint(x1,y0));
    }
 }

void FrameShapeBase::drawBottomRight(const DrawBuf &buf,Pane pane,VColor vc) const
 {
  if( +pane )
    {
     SmoothDrawArt art(buf);

     MPane p(pane);

     MCoord width=+cfg.width;

     FigureBottomRightArrow fig(p.shrink(width));

     fig.solid(art,vc);
    }
 }

void FrameShapeBase::drawRight(const DrawBuf &buf,Pane pane,VColor vc) const
 {
  if( +pane )
    {
     SmoothDrawArt art(buf);

     MPane p(pane);

     MCoord d=p.dx/2;
     MCoord x0=p.x+d;

     MCoord y0=p.y+d;
     MCoord y1=p.ey-d;

     MCoord w=p.dx/4;

     art.path(w,vc,MPoint(x0,y0),MPoint(x0,y1));
    }
 }

void FrameShapeBase::drawTopRight(const DrawBuf &buf,Pane pane,VColor vc) const
 {
  if( +pane )
    {
     SmoothDrawArt art(buf);

     MPane p(pane);

     MCoord width=+cfg.width;

     FigureTopRightArrow fig(p.shrink(width));

     fig.solid(art,vc);
    }
 }

void FrameShapeBase::drawBar(const DrawBuf &buf,Pane pane) const
 {
  if( +pane )
    {
     SmoothDrawArt art(buf);

     MPane p(pane);

     MCoord width=+cfg.width;

     MCoord ex=p.dy/4;

     VColor gray=+cfg.gray;
     VColor snow=+cfg.snow;

     FigureButton fig(p,ex);

     fig.curveSolid(art, has_focus? +cfg.active : +cfg.inactive );

     fig.getTop().curvePath(art,HalfPos,width,gray);
     fig.getBottom().curvePath(art,HalfPos,width,snow);

     Pane tpane=pane.shrink(RoundUpLen(ex),RoundUpLen(width));

     cfg.font->textOn(art,tpane,TextPlace(AlignX_Left,AlignY_Center),Range(title),+cfg.title);
    }
 }

auto FrameShapeBase::drawBtn(const DrawBuf &buf,Pane btn,DragType zone) const
 {
  SmoothDrawArt art(buf);

  MPane p(btn);

  MCoord width=+cfg.width;

  MCoord ex=p.dx/8;

  FigureButton fig(p,ex);

  MPane ret=p.shrink(p.dx/5,p.dy/5);

  VColor gray=+cfg.gray;

  if( btn_type==zone )
    {
     fig.curveSolid(art,gray);

     ret+=MPoint::Diag(width);
    }
  else
    {
     VColor face = (hilight==zone)? +cfg.btnFaceHilight : +cfg.btnFace ;

     VColor snow=+cfg.snow;

     fig.curveSolid(art,face);

     fig.getTop().curvePath(art,HalfPos,width,gray);
     fig.getBottom().curvePath(art,HalfPos,width,snow);
    }

  return ret;
 }

void FrameShapeBase::drawAlert(const DrawBuf &buf,Pane btn) const
 {
  if( +btn )
    {
     SmoothDrawArt art(buf);

     MPane p(btn);

     MCoord width=+cfg.width;

     MCoord ex=p.dx/8;

     FigureButton fig(p,ex);

     MPane q=p.shrink(p.dx/5,p.dy/5);

     VColor gray=+cfg.gray;

     VColor alert;

     if( alert_type==AlertType_No )
       {
        fig.curveLoop(art,HalfPos,width,gray);

        alert=+cfg.btnPictNoAlert;
       }
     else
       {
        if( btn_type==DragType_Alert )
          {
           fig.curveSolid(art,gray);

           q+=MPoint::Diag(width);
          }
        else
          {
           VColor face = (hilight==DragType_Alert)? +cfg.btnFaceHilight : +cfg.btnFace ;

           VColor snow=+cfg.snow;

           fig.curveSolid(art,face);

           fig.getTop().curvePath(art,HalfPos,width,gray);
           fig.getBottom().curvePath(art,HalfPos,width,snow);
          }

        alert = (alert_type==AlertType_Closed)? +cfg.btnPictAlert : +cfg.btnPictCloseAlert ;
       }

     if( !alert_blink )
       {
        PolyFigureExclamation fig(q.x+q.dx/2,q.y,q.dy);

        fig.solid(art,alert);
       }
    }
 }

void FrameShapeBase::drawHelp(const DrawBuf &buf,Pane btn) const
 {
  if( +btn )
    {
     MPane p=drawBtn(buf,btn,DragType_Help);

     SmoothDrawArt art(buf);

     PolyFigureQuestion fig(p.x+p.dx/2,p.y,p.dy);

     if( help )
       {
        fig.solid(art,+cfg.btnPictAlert);
       }
     else
       {
        fig.solid(art,+cfg.btnPict);
       }
    }
 }

void FrameShapeBase::drawMin(const DrawBuf &buf,Pane btn) const
 {
  if( +btn )
    {
     MPane p=drawBtn(buf,btn,DragType_Min);

     SmoothDrawArt art(buf);

     FigureBox fig_pict(p.x,p.ex,p.ey-p.dy/4,p.ey);

     fig_pict.solid(art,+cfg.btnPict);
    }
 }

void FrameShapeBase::drawMax(const DrawBuf &buf,Pane btn,bool max_button) const
 {
  if( +btn )
    {
     MPane p=drawBtn(buf,btn,DragType_Max);

     SmoothDrawArt art(buf);

     VColor pict=+cfg.btnPict;

     if( max_button )
       {
        FigureBox fig_pict(p);

        fig_pict.solid(art,pict);
       }
     else
       {
        MCoord e=p.dy/5;

        FigureBox fig_pict(p.x,p.ex-p.dx/3,p.y+e,p.ey-e);

        fig_pict.solid(art,pict);
       }
    }
 }

void FrameShapeBase::drawClose(const DrawBuf &buf,Pane btn) const
 {
  if( +btn )
    {
     MPane p=drawBtn(buf,btn,DragType_Close);

     SmoothDrawArt art(buf);

     MCoord w=p.dx/6;

     VColor pict=+cfg.btnPictClose;

     art.path(w,pict,p.getTopLeft(),p.getBottomRight());
     art.path(w,pict,p.getTopRight(),p.getBottomLeft());
    }
 }

void FrameShapeBase::drawHint(const DrawBuf &buf,Pane title,Hint hint) const
 {
  if( +title )
    {
     // 1

     MPane bar(title);

     MCoord width=+cfg.width;

     Coord dxy=RoundUpLen(width);

     MCoord ex=bar.dy/4;

     Pane pane=title.shrink(RoundUpLen(ex)+2*dxy,2*dxy);

     // 2

     SmoothDrawArt art(buf);

     MCoord topY;
     MCoord minX;
     MCoord maxX;

     {
      MPane p(pane);

      topY=p.ey;
      minX=p.x;
      maxX=p.ex;

      FigureBox fig(p);

      VColor snow=+cfg.snow;
      VColor gray=+cfg.gray;
      VColor hintBack=+cfg.hintBack;
      VColor hintText=+cfg.hintText;

      fig.solid(art,hintBack);

      FigureTopBorder fig_top(p,width);
      FigureBottomBorder fig_bottom(p,width);

      fig_top.solid(art,snow);
      fig_bottom.solid(art,gray);

      StrLen text;

      if( +hint )
        {
         text=Range(hint.text);
        }
      else
        {
         text=Range(cfg.text_No_hint.get());
        }

      cfg.fontHint->textOn(art,pane,TextPlace(AlignX_Left,AlignY_Center),text,hintText);
     }

     // 3

     if( +hint )
       {
        MCoord width=+cfg.hintWidth;

        VColor border=+cfg.hintBorder;

        Coord dxy=RoundUpLen(width);

        MPane p(hint.pane.expand(dxy));

        FigureBox fig(p);

        fig.loop(art,HalfNeg,width,border);

        MPoint a=p.getTopMid().subY(width/2);
        MPoint b(a.x,topY);

        if( a.y>b.y )
          {
           art.path(width,border,a,b);

           if( b.x<minX )
             {
              MPoint c(minX,b.y);

              art.path(width,border,b,c);

              art.ball(c,2*width,border);
             }
           else if( b.x>maxX )
             {
              MPoint c(maxX,b.y);

              art.path(width,border,b,c);

              art.ball(c,2*width,border);
             }
           else
             {
              art.ball(b,2*width,border);
             }
          }
        else
          {
           if( p.x-width/2>maxX )
             {
              MPoint a=p.getLeftMid().subX(width/2);
              MPoint b(maxX,a.y);

              art.path(width,border,a,b);

              if( b.y<=topY )
                {
                 art.ball(b,2*width,border);
                }
              else
                {
                 MPoint c(b.x,topY);

                 art.path(width,border,b,c);

                 art.ball(c,2*width,border);
                }
             }
           else if( p.ex+width/2<minX )
             {
              MPoint a=p.getRightMid().addX(width/2);
              MPoint b(minX,a.y);

              art.path(width,border,a,b);

              if( b.y<=topY )
                {
                 art.ball(b,2*width,border);
                }
              else
                {
                 MPoint c(b.x,topY);

                 art.path(width,border,b,c);

                 art.ball(c,2*width,border);
                }
             }
          }
       }
    }
 }

Coord FrameShapeBase::getMinTitleDX(StrLen title,Coord dy) const
 {
  MCoord ex=Fraction(Max_cast(dy,0))/4;

  TextSize ts=cfg.font->text(title);

  Coord dx=ts.full_dx;

  dx+=2*RoundUpLen(ex);

  return dx;
 }

void FrameShapeBase::reset(const String &title_,bool is_main_)
 {
  has_focus=false;
  is_main=is_main_;

  drag_type=DragType_None;
  hilight=DragType_None;
  btn_type=DragType_None;
  alert_type=AlertType_No;
  alert_blink=false;
  help=false;
  has_good_size=true;

  title=title_;

  time=0;
 }

} // namespace Video
} // namespace CCore

