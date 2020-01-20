/* Point.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_Point_h
#define CCore_inc_video_Point_h

#include <CCore/inc/algon/ApplyToRange.h>

#include <CCore/inc/video/IntOp.h>

namespace CCore {
namespace Video {

/* types */

using Coord = sint32 ;

using uCoord = uint32 ;

using AreaType = ulen ;

/* consts */

inline constexpr Coord MaxCoord = 32'767 ;

inline constexpr Coord MinCoord = -32'768 ;

/* functions */

template <SUIntType SUInt>
inline constexpr SUInt Sup(SUInt a,SUInt b) { return Max(a,b); }

template <SUIntType SUInt>
inline constexpr SUInt Inf(SUInt a,SUInt b) { return Min(a,b); }

inline AreaType Area(Coord dx,Coord dy) { return LenOf(dx,dy); } // dx >= 0 , dy >= 0

/* size functions */

void GuardSizeOverflow(const char *name);

inline Coord AddSize(Coord a,Coord b)
 {
  Coord ret=a+b;

  if( ret<0 ) GuardSizeOverflow("CCore::Video::AddSize");

  return ret;
 }

Coord AddSize(Coord a,auto ... args) requires ( sizeof ... (args) > 1 )
 {
  using Helper = OpAddHelper<Coord,AddSize> ;

  return ( Helper(a) + ... + Helper(args) ).val;
 }

Coord MulSize(UIntType count,Coord x)
 {
  if( x>0 && count>SIntFunc<Coord>::UInt(SIntFunc<Coord>::MaxPositive/x) ) GuardSizeOverflow("CCore::Video::MulSize");

  return Coord(count)*x;
 }

/* Multi Sup() & Inf() */

template <class T,class ... TT>
T Sup(T a,TT ... tt) requires ( sizeof ... (TT) >= 2 )
 {
  return Sup(a,Sup(tt...));
 }

template <class T,class ... TT>
T Inf(T a,TT ... tt) requires ( sizeof ... (TT) >= 2 )
 {
  return Inf(a,Inf(tt...));
 }

/* CountToCoord() */

Coord CountToCoord(UIntType count) { return Coord(count); }

/* CoordMulDiv() */

inline Coord CoordMulDiv(sint64 a,Coord b,Coord c) { IntGuard( c!=0 ); return Coord( (a*b)/c ); }

/* classes */

template <class T,class Int> struct BasePoint;

struct Point;

struct Pane;

struct PaneSub;

class PointMap;

/* struct BasePoint<T,Int> */

template <class T,class Int>
struct BasePoint
 {
  Int x;
  Int y;

  // constructors

  BasePoint() noexcept : x(0),y(0) {}

  BasePoint(NothingType) : BasePoint() {}

  constexpr BasePoint(Int x_,Int y_) : x(x_),y(y_) {}

  // unsafe operations

  friend T operator - (T a) { return T()-a; }

  friend T operator + (T a,T b) { return T(IntAdd(a.x,b.x),IntAdd(a.y,b.y)); }

  friend T operator - (T a,T b) { return T(IntSub(a.x,b.x),IntSub(a.y,b.y)); }

  friend T operator * (Int a,T p) { return T(IntMul(a,p.x),IntMul(a,p.y)); }

  friend T operator * (T p,Int a) { return T(IntMul(p.x,a),IntMul(p.y,a)); }

  friend T operator / (T p,Int a) { return T(IntDiv(p.x,a),IntDiv(p.y,a)); }

  friend T operator << (T p,unsigned s) { return T(IntLShift(p.x,s),IntLShift(p.y,s)); }

  friend T operator >> (T p,unsigned s) { return T(IntRShift(p.x,s),IntRShift(p.y,s)); }


  T addX(Int dx) const { return T(IntAdd(x,dx),y); }

  T addY(Int dy) const { return T(x,IntAdd(y,dy)); }

  T addXY(Int dxy) const { return T(IntAdd(x,dxy),IntAdd(y,dxy)); }

  T addXsubY(Int dxy) const { return T(IntAdd(x,dxy),IntSub(y,dxy)); }


  T subX(Int dx) const { return T(IntSub(x,dx),y); }

  T subY(Int dy) const { return T(x,IntSub(y,dy)); }

  T subXY(Int dxy) const { return T(IntSub(x,dxy),IntSub(y,dxy)); }

  T subXaddY(Int dxy) const { return T(IntSub(x,dxy),IntAdd(y,dxy)); }

  // derived operations

  friend T operator += (T &a,T b) { return a=a+b; }

  friend T operator -= (T &a,T b) { return a=a-b; }

  friend T operator *= (T &p,Int a) { return p=p*a; }

  friend T operator /= (T &p,Int a) { return p=p/a; }

  friend T operator <<= (T &p,unsigned s) { return p=p<<s; }

  friend T operator >>= (T &p,unsigned s) { return p=p>>s; }

  // safe operations

  friend bool operator == (T a,T b) { return a.x==b.x && a.y==b.y ; }

  friend bool operator != (T a,T b) { return a.x!=b.x || a.y!=b.y ; }

  friend bool operator < (T a,T b) { return a.x<b.x && a.y<b.y ; }

  friend bool operator <= (T a,T b) { return a.x<=b.x && a.y<=b.y ; }

  friend bool operator > (T a,T b) { return a.x>b.x && a.y>b.y ; }

  friend bool operator >= (T a,T b) { return a.x>=b.x && a.y>=b.y ; }

  friend T Sup(T a,T b) { return T(Max(a.x,b.x),Max(a.y,b.y)); }

  friend T Inf(T a,T b) { return T(Min(a.x,b.x),Min(a.y,b.y)); }

  static T Diag(Int xy) { return T(xy,xy); }

  T supX(Int sx) const { return Point(Max(x,sx),y); }

  T supY(Int sy) const { return Point(x,Max(y,sy)); }

  T sup(Int sx,Int sy) const { return Point(Max(x,sx),Max(y,sy)); }

  T sup(T s) const { return sup(s.x,s.y); }

  T infX(Int sx) const { return Point(Min(x,sx),y); }

  T infY(Int sy) const { return Point(x,Min(y,sy)); }

  T inf(Int sx,Int sy) const { return Point(Min(x,sx),Min(y,sy)); }

  T inf(T s) const { return inf(s.x,s.y); }

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"(#;,#;)",x,y);
   }
 };

/* struct Point */

struct Point : BasePoint<Point,Coord>
 {
  static Point Max() { return Point(MaxCoord,MaxCoord); }

  // constructors

  using BasePoint<Point,Coord>::BasePoint;

  Point() noexcept {}
 };

/* Stack...Size() */

inline Point StackXSize(Point a,Point b)
 {
  return Point( a.x+b.x , Sup(a.y,b.y) );
 }

inline Point StackYSize(Point a,Point b)
 {
  return Point( Sup(a.x,b.x) , a.y+b.y );
 }

inline Point StackXSize_guarded(Point a,Point b)
 {
  return Point( AddSize(a.x,b.x) , Sup(a.y,b.y) );
 }

inline Point StackYSize_guarded(Point a,Point b)
 {
  return Point( Sup(a.x,b.x) , AddSize(a.y,b.y) );
 }


template <class ... TT>
Point StackXSize(Point a,Point b,TT ... tt) requires ( sizeof ... (TT) > 0 )
 {
  return StackXSize(StackXSize(a,b),tt...);
 }

template <class ... TT>
Point StackYSize(Point a,Point b,TT ... tt) requires ( sizeof ... (TT) > 0 )
 {
  return StackYSize(StackYSize(a,b),tt...);
 }

template <class ... TT>
Point StackXSize_guarded(Point a,Point b,TT ... tt) requires ( sizeof ... (TT) > 0 )
 {
  return StackXSize_guarded(StackXSize_guarded(a,b),tt...);
 }

template <class ... TT>
Point StackYSize_guarded(Point a,Point b,TT ... tt) requires ( sizeof ... (TT) > 0 )
 {
  return StackYSize_guarded(StackYSize_guarded(a,b),tt...);
 }

/* struct Pane */

struct Pane
 {
  Coord x;
  Coord y;
  Coord dx; // >= 0
  Coord dy; // >= 0

  // constructors

  Pane() noexcept : x(0),y(0),dx(0),dy(0) {}

  Pane(NothingType) : Pane() {}

  Pane(Coord x_,Coord y_,Coord dx_,Coord dy_) // empty if dx_ <= 0 OR dy_ <= 0
   {
    if( dx_>0 && dy_>0 )
      {
       x=x_;
       y=y_;
       dx=dx_;
       dy=dy_;

       IntGuard( x<IntAdd(x,dx) && y<IntAdd(y,dy) );
      }
    else
      {
       x=0;
       y=0;
       dx=0;
       dy=0;
      }
   }

  Pane(Point base,Coord dx,Coord dy) : Pane(base.x,base.y,dx,dy) {}

  Pane(Point base,Point size) : Pane(base.x,base.y,size.x,size.y) {}

  Pane(Point base,Coord dxy) : Pane(base.x,base.y,dxy,dxy) {}

  // methods

  bool operator + () const { return dx>0 && dy>0 ; }

  bool operator ! () const { return dx<=0 || dy<=0 ; }

  Point getBase() const { return Point(x,y); }

  Point addDX() const { return Point(x+dx,y); }

  Point addDY() const { return Point(x,y+dy); }

  Point getSize() const { return Point(dx,dy); }

  Point getLim() const { return Point(x+dx,y+dy); }

  Coord getLimX() const { return x+dx; }

  Coord getLimY() const { return y+dy; }

  AreaType getArea() const { return Area(dx,dy); }

  bool contains(Point point) const
   {
    return point>=getBase() && point<getLim() ;
   }

  bool contains_nonempty(Pane pane) const // +pane
   {
    return pane.getBase()>=getBase() && pane.getLim()<=getLim() ;
   }

  bool contains(Pane pane) const
   {
    if( !pane ) return true;

    return contains_nonempty(pane);
   }

  // operators

  friend Pane operator + (Pane pane,Point point) { return Pane(pane.getBase()+point,pane.dx,pane.dy); }

  friend Pane operator += (Pane &pane,Point point) { return pane=pane+point; }

  friend Pane operator - (Pane pane,Point point) { return Pane(pane.getBase()-point,pane.dx,pane.dy); }

  friend Pane operator -= (Pane &pane,Point point) { return pane=pane-point; }

  friend bool operator == (Pane a,Pane b) { return a.getBase()==b.getBase() && a.getSize()==b.getSize() ; }

  friend bool operator != (Pane a,Pane b) { return !( a==b ); }

  // pull

  Pane pullLeft(Coord delta) const { return Pane(IntSub(x,delta),y,IntAdd(dx,delta),dy); }

  Pane pullTop(Coord delta) const { return Pane(x,IntSub(y,delta),dx,IntAdd(dy,delta)); }

  Pane pullRight(Coord delta) const { return Pane(x,y,IntAdd(dx,delta),dy); }

  Pane pullBottom(Coord delta) const { return Pane(x,y,dx,IntAdd(dy,delta)); }

  // push

  Pane pushLeft(Coord delta) const { return Pane(IntAdd(x,delta),y,IntSub(dx,delta),dy); }

  Pane pushTop(Coord delta) const { return Pane(x,IntAdd(y,delta),dx,IntSub(dy,delta)); }

  Pane pushRight(Coord delta) const { return Pane(x,y,IntSub(dx,delta),dy); }

  Pane pushBottom(Coord delta) const { return Pane(x,y,dx,IntSub(dy,delta)); }

  // shrink

  Pane shrink(Point delta) const { return Pane(getBase()+delta,getSize()-2*delta); }

  Pane shrink(Coord delta_x,Coord delta_y) const { return shrink(Point(delta_x,delta_y)); }

  Pane shrink(Coord delta_xy) const { return shrink(Point(delta_xy,delta_xy)); }

  // expand

  Pane expand(Point delta) const { return shrink(-delta); }

  Pane expand(Coord delta_x,Coord delta_y) const { return expand(Point(delta_x,delta_y)); }

  Pane expand(Coord delta_xy) const { return expand(Point(delta_xy,delta_xy)); }

  // apply

  template <FuncInitArgType<Point> FuncInit>
  auto apply(FuncInit func_init) const
   {
    FunctorTypeOf<FuncInit> func(func_init);

    Coord sBeg=x;
    Coord sLim=sBeg+dx;

    for(Coord t=y,tLim=t+dy; t<tLim ;t++)
      for(Coord s=sBeg; s<sLim ;s++)
        {
         func(Point(s,t));
        }

    return Algon::GetResult(func);
   }

  template <FuncInitArgType<Coord,Coord> FuncInit>
  auto apply(FuncInit func_init) const
   {
    FunctorTypeOf<FuncInit> func(func_init);

    Coord sBeg=x;
    Coord sLim=sBeg+dx;

    for(Coord t=y,tLim=t+dy; t<tLim ;t++)
      for(Coord s=sBeg; s<sLim ;s++)
        {
         func(s,t);
        }

    return Algon::GetResult(func);
   }

  template <FuncInitType<bool,Point> FuncInit>
  auto apply(FuncInit func_init) const
   {
    FunctorTypeOf<FuncInit> func(func_init);

    Coord sBeg=x;
    Coord sLim=sBeg+dx;

    for(Coord t=y,tLim=t+dy; t<tLim ;t++)
      for(Coord s=sBeg; s<sLim ;s++)
        {
         if( !func(Point(s,t)) ) goto stop;
        }

    stop: return Algon::GetResult(func);
   }

  template <FuncInitType<bool,Coord,Coord> FuncInit>
  auto apply(FuncInit func_init) const
   {
    FunctorTypeOf<FuncInit> func(func_init);

    Coord sBeg=x;
    Coord sLim=sBeg+dx;

    for(Coord t=y,tLim=t+dy; t<tLim ;t++)
      for(Coord s=sBeg; s<sLim ;s++)
        {
         if( !func(s,t) ) goto stop;
        }

    stop: return Algon::GetResult(func);
   }

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"(#; +#;,#; +#;)",x,dx,y,dy);
   }
 };

/* functions */

inline Pane Square(Pane pane) { return Pane(pane.getBase(),Min(pane.dx,pane.dy)); }

inline Pane PaneBaseLim(Point base,Point lim) // base <= lim OR empty
 {
  return Pane(base,lim-base);
 }


inline Pane Sup_nonempty(Pane a,Pane b) // +a && +b
 {
  Point base=Inf(a.getBase(),b.getBase());
  Point lim=Sup(a.getLim(),b.getLim());

  return PaneBaseLim(base,lim);
 }

inline Pane Sup(Pane a,Pane b)
 {
  if( !a ) return b;

  if( !b ) return a;

  return Sup_nonempty(a,b);
 }

inline Pane Inf_nonempty(Pane a,Pane b) // +a && +b
 {
  Point base=Sup(a.getBase(),b.getBase());
  Point lim=Inf(a.getLim(),b.getLim());

  if( base<lim ) return PaneBaseLim(base,lim);

  return Empty;
 }

inline Pane Inf(Pane a,Pane b)
 {
  if( !a ) return a;

  if( !b ) return b;

  return Inf_nonempty(a,b);
 }


inline Pane Envelope(Point a,Point b) { return PaneBaseLim(Inf(a,b),Sup(a,b).addXY(1)); }

inline Pane Inner(Pane pane,Pane subpane) { return Inf(subpane+pane.getBase(),pane); }

/* Split...() */

inline Pane SplitX(Coord delta,Pane &pane)
 {
  Pane ret=Pane(pane.x,pane.y,delta,pane.dy);

  pane=pane.pushLeft(delta);

  return ret;
 }

inline Pane SplitX(Pane &pane,Coord delta)
 {
  Coord dx=IntSub(pane.dx,delta);

  Pane ret=Pane(IntAdd(pane.x,dx),pane.y,delta,pane.dy);

  pane=Pane(pane.x,pane.y,dx,pane.dy);

  return ret;
 }

inline Pane SplitY(Coord delta,Pane &pane)
 {
  Pane ret=Pane(pane.x,pane.y,pane.dx,delta);

  pane=pane.pushTop(delta);

  return ret;
 }

inline Pane SplitY(Pane &pane,Coord delta)
 {
  Coord dy=IntSub(pane.dy,delta);

  Pane ret=Pane(pane.x,IntAdd(pane.y,dy),pane.dx,delta);

  pane=Pane(pane.x,pane.y,pane.dx,dy);

  return ret;
 }


inline Pane TrySplitX(Coord delta,Pane &pane)
 {
  if( delta<=pane.dx ) return SplitX(delta,pane);

  return Empty;
 }

inline Pane TrySplitX(Pane &pane,Coord delta)
 {
  if( delta<=pane.dx ) return SplitX(pane,delta);

  return Empty;
 }

inline Pane TrySplitY(Coord delta,Pane &pane)
 {
  if( delta<=pane.dy ) return SplitY(delta,pane);

  return Empty;
 }

inline Pane TrySplitY(Pane &pane,Coord delta)
 {
  if( delta<=pane.dy ) return SplitY(pane,delta);

  return Empty;
 }

/* Align...() */

Pane AlignLeft(Pane pane,Coord dx);

Pane AlignCenterX(Pane pane,Coord dx);

Pane AlignRight(Pane pane,Coord dx);

Pane AlignTop(Pane pane,Coord dy);

Pane AlignCenterY(Pane pane,Coord dy);

Pane AlignBottom(Pane pane,Coord dy);

Pane AlignCenter(Pane pane,Coord dx,Coord dy);

inline Pane AlignCenter(Pane pane,Point size) { return AlignCenter(pane,size.x,size.y); }

/* struct PaneSub */

struct PaneSub
 {
  Pane top;    // full width
  Pane bottom; // full width

  Pane left;
  Pane right;

  PaneSub(Pane outer,Pane inner);
 };

/* class PointMap */

class PointMap
 {
   Point origin;

  public:

   explicit PointMap(Point origin_) : origin(origin_) {}

   Point getOrigin() const { return origin; }

   PointMap operator - () const { return PointMap(-origin); }

   template <class T>
   T operator () (T obj) const { return obj+origin; }
 };

} // namespace Video
} // namespace CCore

#endif


