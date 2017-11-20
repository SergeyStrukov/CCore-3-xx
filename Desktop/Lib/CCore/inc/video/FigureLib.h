/* FigureLib.h */
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

#ifndef CCore_inc_video_FigureLib_h
#define CCore_inc_video_FigureLib_h

#include <CCore/inc/video/SmoothDrawArt.h>

namespace CCore {
namespace Video {

/* classes */

struct MPane;

template <class T,ulen Len> struct FigureBase;

struct DrawPoints;

template <ulen Len> struct FigurePoints;

struct DrawDots;

template <ulen Len> struct FigureDots;

struct FigureBox;

struct FigureSkew;

struct FigureTopLeftArrow;

struct FigureBottomLeftArrow;

struct FigureTopRightArrow;

struct FigureBottomRightArrow;

struct FigureTopBorder;

struct FigureBottomBorder;

struct FigureButton;

struct FigureAsterisk;

struct ShrinkArrowDelta;

struct FigureLeftArrow;

struct FigureRightArrow;

struct FigureUpArrow;

struct FigureDownArrow;

struct FigureLeftMark;

struct FigureRightMark;

struct FigureUpMark;

struct FigureDownMark;

struct FigureRoundBox;

struct FigureCursor;

class PolyFigureExclamation;

class PolyFigureQuestion;

/* struct MPane */

struct MPane
 {
  MCoord x;
  MCoord y;
  MCoord dx;
  MCoord dy;

  MCoord ex;
  MCoord ey;

  // constructors

  MPane() noexcept : x(0),y(0),dx(0),dy(0),ex(0),ey(0) {}

  MPane(NothingType) noexcept : MPane() {}

  MPane(const Pane &pane)
   {
    if( +pane )
      {
       x=MPoint::LShift(pane.x)-MPoint::Half;
       y=MPoint::LShift(pane.y)-MPoint::Half;
       dx=MPoint::LShift(pane.dx);
       dy=MPoint::LShift(pane.dy);

       ex=x+dx;
       ey=y+dy;
      }
    else
      {
       (*this)=Empty;
      }
   }

  MPane(MCoord x_,MCoord ex_,MCoord y_,MCoord ey_)
   {
    if( x_<ex_ && y_<ey_ )
      {
       x=x_;
       y=y_;
       ex=ex_;
       ey=ey_;

       dx=ex-x;
       dy=ey-y;
      }
    else
      {
       (*this)=Empty;
      }
   }

  // methods

  bool operator + () const { return dx>0 && dy>0 ; }

  bool operator ! () const { return dx<=0 && dy<=0 ; }

  void square()
   {
    if( dx>dy )
      {
       dx=dy;
       ex=x+dx;
      }
    else
      {
       dy=dx;
       ey=y+dy;
      }
   }

  // points

  MPoint getBase() const { return MPoint(x,y); }

  MPoint getSize() const { return MPoint(dx,dy); }

  MPoint getCenter() const { return getBase()+getSize()/2; }

  MPoint getTopLeft() const { return MPoint(x,y); }

  MPoint getTopRight() const { return MPoint(ex,y); }

  MPoint getBottomLeft() const { return MPoint(x,ey); }

  MPoint getBottomRight() const { return MPoint(ex,ey); }

  MPoint getLeftMid() const { return MPoint(x,y+dy/2); }

  MPoint getRightMid() const { return MPoint(ex,y+dy/2); }

  MPoint getTopMid() const { return MPoint(x+dx/2,y); }

  MPoint getBottomMid() const { return MPoint(x+dx/2,ey); }

  // shift

  MPane operator + (MPoint p) const
   {
    MPane ret(*this);

    ret+=p;

    return ret;
   }

  MPane operator += (MPoint p)
   {
    x+=p.x;
    y+=p.y;

    ex+=p.x;
    ey+=p.y;

    return *this;
   }

  // shrink

  MPane shrinkX(MCoord dleft,MCoord dright) const
   {
    return MPane(x+dleft,ex-dright,y,ey);
   }

  MPane shrinkX(MCoord dx) const
   {
    return MPane(x+dx,ex-dx,y,ey);
   }

  MPane shrinkY(MCoord dtop,MCoord dbottom) const
   {
    return MPane(x,ex,y+dtop,ey-dbottom);
   }

  MPane shrinkY(MCoord dy) const
   {
    return MPane(x,ex,y+dy,ey-dy);
   }

  MPane shrink(MCoord dx,MCoord dy) const
   {
    return MPane(x+dx,ex-dx,y+dy,ey-dy);
   }

  MPane shrink(MPoint delta) const
   {
    return shrink(delta.x,delta.y);
   }

  MPane shrink(MCoord dxy) const
   {
    return MPane(x+dxy,ex-dxy,y+dxy,ey-dxy);
   }

  // part

  MPane cutLeft(MCoord t) const { return MPane(x,t,y,ey); }

  MPane cutRight(MCoord t) const { return MPane(t,ex,y,ey); }

  MPane cutTop(MCoord t) const { return MPane(x,ex,y,t); }

  MPane cutBottom(MCoord t) const { return MPane(x,ex,t,ey); }
 };

/* MBox() */

inline MPane MBox(MPoint p,MCoord len)
 {
  return MPane(p.x-len,p.x+len,p.y-len,p.y+len);
 }

/* struct FigureBase<T,ulen Len> */

template <class T,ulen Len>
struct FigureBase
 {
  T buf[Len];

  struct Set
   {
    T *dst;

    explicit Set(T *dst_) : dst(dst_) {}

    void operator () (ulen) const {}

    template <class ... TT>
    void operator () (ulen ind,const T &t,const TT & ... tt) const
     {
      dst[ind]=t;

      (*this)(ind+1,tt...);
     }
   };

  // methods

  FigureBase() {}

  template <class B,class ... TT>
  FigureBase(const B &src,TT ... tt)
   {
    Set set(buf);

    set(0, src[tt]... );
   }

  template <class B,class ... TT>
  void set(ulen ind,const B &src,TT ... tt)
   {
    Set set(buf);

    set(ind, src[tt]... );
   }

  void copy(const T *src) { Range(buf).copy(src); }

  PtrLen<const T> get() const { return Range(buf); }

  T & operator [] (ulen ind) { return buf[ind]; }

  const T & operator [] (ulen ind) const { return buf[ind]; }
 };

/* struct DrawPoints */

struct DrawPoints
 {
  static void Path(SmoothDrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor vc);

  static void Loop(SmoothDrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor vc);


  static void Path(SmoothDrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc);

  static void Loop(SmoothDrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc);


  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor vc);

  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const TwoField &field);

  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const RadioField &field);

  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractField &field);

  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractAlphaField &field);


  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,VColor vc)
   {
    Solid(art,dots,SolidAll,vc);
   }

  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,const TwoField &field)
   {
    Solid(art,dots,SolidAll,field);
   }

  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,const RadioField &field)
   {
    Solid(art,dots,SolidAll,field);
   }

  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,const AbstractField &field)
   {
    Solid(art,dots,SolidAll,field);
   }

  static void Solid(SmoothDrawArt &art,PtrLen<const MPoint> dots,const AbstractAlphaField &field)
   {
    Solid(art,dots,SolidAll,field);
   }


  static void CurvePath(SmoothDrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor vc);

  static void CurveLoop(SmoothDrawArt &art,PtrLen<const MPoint> dots,MCoord width,VColor vc);


  static void CurvePath(SmoothDrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc);

  static void CurveLoop(SmoothDrawArt &art,PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc);


  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor vc);

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const TwoField &field);

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const RadioField &field);

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractField &field);

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractAlphaField &field);


  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,VColor vc)
   {
    CurveSolid(art,dots,SolidAll,vc);
   }

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,const TwoField &field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,const RadioField &field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,const AbstractField &field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const MPoint> dots,const AbstractAlphaField &field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }
 };

/* struct FigurePoints<ulen Len> */

template <ulen Len>
struct FigurePoints : FigureBase<MPoint,Len> , DrawPoints
 {
  using FigureBase<MPoint,Len>::FigureBase;

  using FigureBase<MPoint,Len>::buf;
  using FigureBase<MPoint,Len>::get;

  template <FuncInitType<MPoint,MPoint> FuncInit>
  void transform(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);

    for(MPoint &p : buf ) p=func(p);
   }

  void shift(MPoint delta) { transform(SmoothDotShift(delta)); }

  template <class ... TT>
  void path(SmoothDrawArt &art,TT && ... tt) const
   {
    Path(art,get(), std::forward<TT>(tt)... );
   }

  template <class ... TT>
  void loop(SmoothDrawArt &art,TT && ... tt) const
   {
    Loop(art,get(), std::forward<TT>(tt)... );
   }

  template <class ... TT>
  void solid(SmoothDrawArt &art,TT && ... tt) const
   {
    Solid(art,get(), std::forward<TT>(tt)... );
   }

  template <class ... TT>
  void curvePath(SmoothDrawArt &art,TT && ... tt) const
   {
    CurvePath(art,get(), std::forward<TT>(tt)... );
   }

  template <class ... TT>
  void curveLoop(SmoothDrawArt &art,TT && ... tt) const
   {
    CurveLoop(art,get(), std::forward<TT>(tt)... );
   }

  template <class ... TT>
  void curveSolid(SmoothDrawArt &art,TT && ... tt) const
   {
    CurveSolid(art,get(), std::forward<TT>(tt)... );
   }
 };

/* struct DrawDots */

struct DrawDots
 {
  static void CurvePath(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,MCoord width,VColor vc);

  static void CurveLoop(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,MCoord width,VColor vc);


  static void CurvePath(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,HalfFlag half_flag,MCoord width,VColor vc);

  static void CurveLoop(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,HalfFlag half_flag,MCoord width,VColor vc);


  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,VColor vc);

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,const TwoField &field);

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,const RadioField &field);

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,const AbstractField &field);

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,SolidFlag solid_flag,const AbstractAlphaField &field);


  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,VColor vc)
   {
    CurveSolid(art,dots,SolidAll,vc);
   }

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,const TwoField &field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,const RadioField &field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,const AbstractField &field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }

  static void CurveSolid(SmoothDrawArt &art,PtrLen<const SmoothDot> dots,const AbstractAlphaField &field)
   {
    CurveSolid(art,dots,SolidAll,field);
   }
 };

/* struct FigureDots<ulen Len> */

template <ulen Len>
struct FigureDots : FigureBase<SmoothDot,Len> , DrawDots
 {
  using FigureBase<SmoothDot,Len>::FigureBase;

  using FigureBase<SmoothDot,Len>::buf;
  using FigureBase<SmoothDot,Len>::get;

  template <FuncInitType<MPoint,MPoint> FuncInit>
  void transform(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);

    for(SmoothDot &p : buf ) p.point=func(p.point);
   }

  void shift(MPoint delta) { transform(SmoothDotShift(delta)); }

  template <class ... TT>
  void curvePath(SmoothDrawArt &art,TT && ... tt) const
   {
    CurvePath(art,get(), std::forward<TT>(tt)... );
   }

  template <class ... TT>
  void curveLoop(SmoothDrawArt &art,TT && ... tt) const
   {
    CurveLoop(art,get(), std::forward<TT>(tt)... );
   }

  template <class ... TT>
  void curveSolid(SmoothDrawArt &art,TT && ... tt) const
   {
    CurveSolid(art,get(), std::forward<TT>(tt)... );
   }
 };

 //
 // contraclockwise
 //

/* struct FigureBox */

struct FigureBox : FigurePoints<4>
 {
  FigureBox(MCoord x0,MCoord x1,MCoord y0,MCoord y1);

  explicit FigureBox(const MPane &p) : FigureBox(p.x,p.ex,p.y,p.ey) {}
 };

/* struct FigureSkew */

struct FigureSkew : FigurePoints<4>
 {
  FigureSkew(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord skew);

  FigureSkew(const MPane &p,MCoord skew) : FigureSkew(p.x,p.ex,p.y,p.ey,skew) {}
 };

/* struct FigureTopLeftArrow */

struct FigureTopLeftArrow : FigurePoints<3>
 {
  FigureTopLeftArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);

  explicit FigureTopLeftArrow(const MPane &p) : FigureTopLeftArrow(p.x,p.ex,p.y,p.ey) {}
 };

/* struct FigureBottomLeftArrow */

struct FigureBottomLeftArrow : FigurePoints<3>
 {
  FigureBottomLeftArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);

  explicit FigureBottomLeftArrow(const MPane &p) : FigureBottomLeftArrow(p.x,p.ex,p.y,p.ey) {}
 };

/* struct FigureTopRightArrow */

struct FigureTopRightArrow : FigurePoints<3>
 {
  FigureTopRightArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);

  explicit FigureTopRightArrow(const MPane &p) : FigureTopRightArrow(p.x,p.ex,p.y,p.ey) {}
 };

/* struct FigureBottomRightArrow */

struct FigureBottomRightArrow : FigurePoints<3>
 {
  FigureBottomRightArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);

  explicit FigureBottomRightArrow(const MPane &p) : FigureBottomRightArrow(p.x,p.ex,p.y,p.ey) {}
 };

/* struct FigureTopBorder */

struct FigureTopBorder : FigurePoints<6>
 {
  FigureTopBorder(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord w);

  FigureTopBorder(const MPane &p,MCoord w) : FigureTopBorder(p.x,p.ex,p.y,p.ey,w) {}

  FigurePoints<6> getLeftCut(MCoord t) const;

  FigurePoints<4> getRightCut(MCoord t) const;
 };

/* struct FigureBottomBorder */

struct FigureBottomBorder : FigurePoints<6>
 {
  FigureBottomBorder(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord w);

  FigureBottomBorder(const MPane &p,MCoord w) : FigureBottomBorder(p.x,p.ex,p.y,p.ey,w) {}
 };

/* struct FigureButton */

struct FigureButton : FigureDots<10>
 {
  FigureButton(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord ex);

  FigureButton(const MPane &p,MCoord ex) : FigureButton(p.x,p.ex,p.y,p.ey,ex) {}

  FigureDots<6> getTop() const;

  FigureDots<6> getBottom() const;
 };

/* struct FigureAsterisk */

struct FigureAsterisk : FigurePoints<30>
 {
  FigureAsterisk(MPoint center,MCoord radius);
 };

/* struct ShrinkArrowDelta */

struct ShrinkArrowDelta
 {
  MCoord a;
  MCoord b;
  MCoord c;

  ShrinkArrowDelta(MCoord h,MCoord l,MCoord width);
 };

/* struct FigureLeftArrow */

struct FigureLeftArrow : FigureDots<4>
 {
  FigureLeftArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);

  explicit FigureLeftArrow(const MPane &p) : FigureLeftArrow(p.x,p.ex,p.y,p.ey) {}

  MPoint getPoint() const { return buf[1].point; }

  FigureLeftArrow shrink(MCoord width) const;

  FigureDots<10> border(MCoord width) const;
 };

/* struct FigureRightArrow */

struct FigureRightArrow : FigureDots<4>
 {
  FigureRightArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);

  explicit FigureRightArrow(const MPane &p) : FigureRightArrow(p.x,p.ex,p.y,p.ey) {}

  MPoint getPoint() const { return buf[1].point; }

  FigureRightArrow shrink(MCoord width) const;

  FigureDots<10> border(MCoord width) const;
 };

/* struct FigureUpArrow */

struct FigureUpArrow : FigureDots<4>
 {
  FigureUpArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);

  explicit FigureUpArrow(const MPane &p) : FigureUpArrow(p.x,p.ex,p.y,p.ey) {}

  MPoint getPoint() const { return buf[1].point; }

  FigureUpArrow shrink(MCoord width) const;

  FigureDots<10> border(MCoord width) const;
 };

/* struct FigureDownArrow */

struct FigureDownArrow : FigureDots<4>
 {
  FigureDownArrow(MCoord x0,MCoord x1,MCoord y0,MCoord y1);

  explicit FigureDownArrow(const MPane &p) : FigureDownArrow(p.x,p.ex,p.y,p.ey) {}

  MPoint getPoint() const { return buf[1].point; }

  FigureDownArrow shrink(MCoord width) const;

  FigureDots<10> border(MCoord width) const;
 };

/* struct FigureLeftMark */

struct FigureLeftMark : FigurePoints<3>
 {
  FigureLeftMark(MCoord x,MCoord y,MCoord len);

  FigureLeftMark(MPoint point,MCoord len) : FigureLeftMark(point.x,point.y,len) {}

  FigureLeftMark(const MPane &p,MCoord len) : FigureLeftMark(p.getLeftMid(),len) {}
 };

/* struct FigureRightMark */

struct FigureRightMark : FigurePoints<3>
 {
  FigureRightMark(MCoord x,MCoord y,MCoord len);

  FigureRightMark(MPoint point,MCoord len) : FigureRightMark(point.x,point.y,len) {}

  FigureRightMark(const MPane &p,MCoord len) : FigureRightMark(p.getRightMid(),len) {}
 };

/* struct FigureUpMark */

struct FigureUpMark : FigurePoints<3>
 {
  FigureUpMark(MCoord x,MCoord y,MCoord len);

  FigureUpMark(MPoint point,MCoord len) : FigureUpMark(point.x,point.y,len) {}

  FigureUpMark(const MPane &p,MCoord len) : FigureUpMark(p.getTopMid(),len) {}
 };

/* struct FigureDownMark */

struct FigureDownMark : FigurePoints<3>
 {
  FigureDownMark(MCoord x,MCoord y,MCoord len);

  FigureDownMark(MPoint point,MCoord len) : FigureDownMark(point.x,point.y,len) {}

  FigureDownMark(const MPane &p,MCoord len) : FigureDownMark(p.getBottomMid(),len) {}
 };

/* struct FigureRoundBox */

struct FigureRoundBox : FigureDots<28>
 {
  FigureRoundBox(MCoord x0,MCoord x1,MCoord y0,MCoord y1,MCoord r);

  FigureRoundBox(const MPane &p,MCoord r) : FigureRoundBox(p.x,p.ex,p.y,p.ey,r) {}

  MPoint getLeftTop() const { return buf[0].point; }

  MPoint getLeftBottom() const { return buf[1].point; }

  MPoint getBottomLeft() const { return buf[7].point; }

  MPoint getBottomRight() const { return buf[8].point; }

  MPoint getRightTop() const { return buf[15].point; }

  MPoint getRightBottom() const { return buf[14].point; }

  MPoint getTopLeft() const { return buf[22].point; }

  MPoint getTopRight() const { return buf[21].point; }
 };

/* struct FigureCursor */

struct FigureCursor : FigurePoints<12>
 {
  FigureCursor(MCoord x0,MCoord y0,MCoord y1,MCoord width,MCoord skew);
 };

/* class PolyFigureExclamation */

class PolyFigureExclamation
 {
   MPoint o;
   MCoord r;

   FigureDots<4> fig;

  public:

   PolyFigureExclamation(MCoord x,MCoord y,MCoord h);

   void solid(SmoothDrawArt &art,VColor vc)
    {
     art.ball(o,r,vc);

     fig.curveSolid(art,vc);
    }
 };

/* class PolyFigureQuestion */

class PolyFigureQuestion
 {
   MPoint o;
   MCoord r;

   FigureDots<30> fig;

  public:

   PolyFigureQuestion(MCoord x,MCoord y,MCoord h);

   void solid(SmoothDrawArt &art,VColor vc)
    {
     art.ball(o,r,vc);

     fig.curveSolid(art,vc);
    }
 };

} // namespace Video
} // namespace CCore

#endif


