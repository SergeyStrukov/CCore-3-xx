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

using Coord = sint16 ;

using uCoord = uint16 ;

using MCoord = sint32 ;

using uMCoord = uint32 ;

using DCoord = sint64 ;

using uDCoord = uint64 ;

using AreaType = uint32 ;

/* consts */

inline constexpr Coord MaxCoord = 32'767 ;

inline constexpr Coord MinCoord = -32'768 ;

inline constexpr MCoord MaxMCoord = 2'147'483'647 ;

/* functions */

template <OneOfTypes<Coord,MCoord> T>
T Sup(T a,T b) { return Max(a,b); }

template <OneOfTypes<Coord,MCoord> T>
T Inf(T a,T b) { return Min(a,b); }

inline constexpr AreaType Area(Coord dx,Coord dy) { return AreaType(dx)*AreaType(dy); }

DCoord Length(MCoord a,MCoord b);

inline MCoord MulDiv(DCoord a,MCoord b,MCoord c) { IntGuard( c!=0 ); return MCoord( (a*b)/c ); }

inline uMCoord UMulDiv(uDCoord a,uMCoord b,uMCoord c) { IntGuard( c!=0 ); return uMCoord( (a*b)/c ); }

template <UIntType UInt>
MCoord Position(UInt P,UInt Q,MCoord a,MCoord b)
 {
  if( P>=Q ) return b;

  DownBits<uMCoord> q(Q);

  uMCoord p=q(P);

  if( a<b )
    return IntMovePos(a,UMulDiv(p,IntDist(a,b),q));
  else
    return IntMoveNeg(a,UMulDiv(p,IntDist(b,a),q));
 }

inline Coord AddSat(Coord a,Coord b)
 {
  MCoord ret=MCoord(a)+b;

  if( ret>MaxCoord ) return MaxCoord;

  return (Coord)ret;
 }

/* classes */

struct Coordinate;

template <class T,class Int> struct BasePoint;

struct Point;

struct MPoint;

struct Ratio;

struct Pane;

struct PaneSub;

class PointMap;

struct CoordAcc;

/* struct Coordinate */

struct Coordinate
 {
  Coord x;

  // constructors

  Coordinate() noexcept : x(0) {}

  Coordinate(NothingType) : Coordinate() {}

  Coordinate(Coord x_) : x(x_) {}

  // methods

  Coord operator + () const { return x; }

  static Coordinate Max() { return Coordinate(MaxCoord); }

  static Coordinate Min() { return Coordinate(MinCoord); }

  // unsafe operations

  friend Coordinate operator - (Coordinate a) { return Coordinate()-a; }

  friend Coordinate operator + (Coordinate a,Coordinate b) { return Coordinate(IntAdd(a.x,b.x)); }

  friend Coordinate operator - (Coordinate a,Coordinate b) { return Coordinate(IntSub(a.x,b.x)); }

  friend Coordinate operator * (Coordinate a,Coordinate b) { return Coordinate(IntMul(a.x,b.x)); }

  friend Coordinate operator / (Coordinate a,Coordinate b) { return Coordinate(IntDiv(a.x,b.x)); }

  friend Coordinate operator << (Coordinate a,unsigned s) { return Coordinate(IntLShift(a.x,s)); }

  friend Coordinate operator >> (Coordinate a,unsigned s) { return Coordinate(IntRShift(a.x,s)); }

  // derived operations

  friend Coordinate operator += (Coordinate &a,Coordinate b) { return a=a+b; }

  friend Coordinate operator -= (Coordinate &a,Coordinate b) { return a=a-b; }

  friend Coordinate operator *= (Coordinate &a,Coordinate b) { return a=a*b; }

  friend Coordinate operator /= (Coordinate &a,Coordinate b) { return a=a/b; }

  friend Coordinate operator <<= (Coordinate &a,unsigned s) { return a=a<<s; }

  friend Coordinate operator >>= (Coordinate &a,unsigned s) { return a=a>>s; }

  // safe operations

  friend bool operator == (Coordinate a,Coordinate b) { return a.x==b.x ; }

  friend bool operator != (Coordinate a,Coordinate b) { return a.x!=b.x ; }

  friend bool operator < (Coordinate a,Coordinate b) { return a.x<b.x ; }

  friend bool operator <= (Coordinate a,Coordinate b) { return a.x<=b.x ; }

  friend bool operator > (Coordinate a,Coordinate b) { return a.x>b.x ; }

  friend bool operator >= (Coordinate a,Coordinate b) { return a.x>=b.x ; }

  // print object

  void print(PrinterType &out) const
   {
    Putobj(out,x);
   }
 };

inline Coordinate Sup(Coordinate a,Coordinate b) { return Coordinate(Max(a.x,b.x)); }

inline Coordinate Inf(Coordinate a,Coordinate b) { return Coordinate(Min(a.x,b.x)); }

/* CountToCoordinate() */

Coordinate CountToCoordinate(UIntType count) { IntGuard( count<=MaxCoord ); return Coord(count); }

/* struct BasePoint<T,Int> */

template <class T,class Int>
struct BasePoint
 {
  Int x;
  Int y;

  // constructors

  BasePoint() noexcept : x(0),y(0) {}

  BasePoint(NothingType) : BasePoint() {}

  BasePoint(Int x_,Int y_) : x(x_),y(y_) {}

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

  static Point Min() { return Point(MinCoord,MinCoord); }

  using BasePoint<Point,Coord>::Diag;

  static Point Diag(Coordinate xy) { return Diag(+xy); }

  // constructors

  using BasePoint<Point,Coord>::BasePoint;

  Point() noexcept {}

  Point(Coordinate x,Coordinate y) : Point(+x,+y) {}
 };

/* struct MPoint */

struct MPoint : BasePoint<MPoint,MCoord>
 {
  // consts

  static constexpr unsigned Precision = 10 ;

  static constexpr MCoord One = MCoord(1)<<Precision ;

  static constexpr MCoord Half = MCoord(1)<<(Precision-1) ;

  // LShift

  static MCoord LShift(Coord a) { return IntLShift(MCoord(a),Precision); }

  static MCoord LShift_ext(MCoord a) { return IntLShift(a,Precision); }

  // RShift

  static Coord RShift(MCoord a) { return To16( IntRShift(IntAdd(a,Half),Precision) ); }

  static MCoord RShift_ext(MCoord a) { return IntRShift(IntAdd(a,Half),Precision); }

  // Round

  static constexpr uMCoord RoundMask = uMCoord(-1)<<Precision ;

  static MCoord Round(MCoord a) { return IntMask(IntAdd(a,Half),RoundMask); }

  // constructors

  using BasePoint<MPoint,MCoord>::BasePoint;

  MPoint() noexcept {}

  MPoint(Point p) : BasePoint<MPoint,MCoord>(LShift(p.x),LShift(p.y)) {}

  // methods

  Point toPoint() const { return Point(RShift(x),RShift(y)); }

  MPoint round() const { return MPoint(Round(x),Round(y)); }
 };

inline MCoord Fraction(MCoord value,unsigned prec=0) // prec <= MPoint::Precision
 {
  return IntLShift(value,MPoint::Precision-prec);
 }

inline MCoord Fraction(Coordinate x) { return Fraction(+x); }

inline Coord RoundUpLen(MCoord dx)
 {
  return To16( IntRShift(dx+MPoint::One-1,MPoint::Precision) );
 }

/* Prod() */

inline DCoord Length(MPoint a) { return Length(a.x,a.y); }

inline DCoord Prod(MCoord a,MCoord b,MCoord x,MCoord y) { return DCoord(a)*x+DCoord(b)*y; }

inline DCoord Prod(MCoord a,MCoord b,MPoint point) { return Prod(a,b,point.x,point.y); }

inline DCoord Prod(MPoint a,MPoint b) { return Prod(a.x,a.y,b.x,b.y); }

/* struct Ratio */

struct Ratio
 {
  // consts

  static constexpr unsigned Precision = 16 ;

  // data

  MCoord value;

  // constructors

  Ratio() noexcept : value(0) {}

  explicit Ratio(MCoord value_) : value(value_) {}

  Ratio(MCoord value_,unsigned prec) : value( IntLShift(value_,Precision-prec) ) {} // prec <= Precision

  // methods

  Ratio pow(unsigned deg) const;

  // operators

  friend Ratio operator - (Ratio a)
   {
    return Ratio(-a.value);
   }

  friend Ratio operator + (Ratio a,Ratio b)
   {
    return Ratio(a.value+b.value);
   }

  friend Ratio operator - (Ratio a,Ratio b)
   {
    return Ratio(a.value-b.value);
   }

  friend Ratio operator * (Ratio a,Ratio b)
   {
    return Ratio( MCoord( IntRShift(DCoord(a.value)*b.value,Precision) ) );
   }

  friend Ratio operator / (Ratio a,Ratio b)
   {
    IntGuard( b.value!=0 );

    return Ratio( MCoord( IntLShift(DCoord(a.value),Precision)/b.value ) );
   }

  // multiplicators

  friend MCoord operator * (Ratio a,MCoord b)
   {
    return MCoord( IntRShift(DCoord(a.value)*b,Precision) );
   }

  friend MPoint operator * (Ratio a,MPoint point)
   {
    return MPoint(a*point.x,a*point.y);
   }

  friend Coord operator * (Ratio a,Coord b)
   {
    return To16( IntRShift(DCoord(a.value)*b,Precision) );
   }

  friend Coordinate operator * (Ratio a,Coordinate c)
   {
    return a*c.x;
   }

  friend Point operator * (Ratio a,Point point)
   {
    return Point(a*point.x,a*point.y);
   }
 };

inline Ratio Div(MCoord a,MCoord b) { return Ratio(a)/Ratio(b); }

inline Ratio XdivY(Point size) { return Div(size.x,size.y); }

inline Ratio YdivX(Point size) { return Div(size.y,size.x); }

inline Ratio XdivY(MPoint size) { return Div(size.x,size.y); }

inline Ratio YdivX(MPoint size) { return Div(size.y,size.x); }

/* struct Pane */

struct Pane
 {
  Coord x;
  Coord y;
  Coord dx; // >=0
  Coord dy; // >=0

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

       IntAdd(x_,dx_);
       IntAdd(y_,dy_);
      }
    else
      {
       x=0;
       y=0;
       dx=0;
       dy=0;
      }
   }

  Pane(Coordinate x,Coordinate y,Coordinate dx,Coordinate dy) : Pane(+x,+y,+dx,+dy) {}

  Pane(Point base,Coord dx,Coord dy) : Pane(base.x,base.y,dx,dy) {}

  Pane(Point base,Coordinate dx,Coordinate dy) : Pane(base,+dx,+dy) {}

  Pane(Point base,Point size) : Pane(base.x,base.y,size.x,size.y) {}

  Pane(Point base,Coord dxy) : Pane(base.x,base.y,dxy,dxy) {}

  Pane(Point base,Coordinate dxy) : Pane(base,+dxy) {}

  // methods

  bool operator + () const { return dx>0 && dy>0 ; }

  bool operator ! () const { return dx<=0 || dy<=0 ; }

  Point getBase() const { return Point(x,y); }

  Point addDX() const { return Point(x+dx,y); }

  Point addDY() const { return Point(x,y+dy); }

  Point getSize() const { return Point(dx,dy); }

  Point getLim() const { return Point(x+dx,y+dy); }

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

  Pane pullLeft(Coordinate delta) const { return Pane(x-delta,y,dx+delta,dy); }

  Pane pullTop(Coordinate delta) const { return Pane(x,y-delta,dx,dy+delta); }

  Pane pullRight(Coordinate delta) const { return Pane(x,y,dx+delta,dy); }

  Pane pullBottom(Coordinate delta) const { return Pane(x,y,dx,dy+delta); }

  // shrink

  Pane shrink(Point delta) const { return Pane(getBase()+delta,getSize()-2*delta); }

  Pane shrink(Coordinate delta_x,Coordinate delta_y) const { return shrink(Point(delta_x,delta_y)); }

  Pane shrink(Coordinate delta_xy) const { return shrink(Point(delta_xy,delta_xy)); }

  // expand

  Pane expand(Point delta) const { return shrink(-delta); }

  Pane expand(Coordinate delta_x,Coordinate delta_y) const { return expand(Point(delta_x,delta_y)); }

  Pane expand(Coordinate delta_xy) const { return expand(Point(delta_xy,delta_xy)); }

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

inline Pane SplitX(Coordinate delta,Pane &pane)
 {
  Pane ret=Pane(pane.x,pane.y,delta,pane.dy);

  pane=Pane(pane.x+delta,pane.y,pane.dx-delta,pane.dy);

  return ret;
 }

inline Pane SplitX(Pane &pane,Coordinate delta)
 {
  auto dx=pane.dx-delta;

  Pane ret=Pane(pane.x+dx,pane.y,delta,pane.dy);

  pane=Pane(pane.x,pane.y,dx,pane.dy);

  return ret;
 }

inline Pane SplitY(Coordinate delta,Pane &pane)
 {
  Pane ret=Pane(pane.x,pane.y,pane.dx,delta);

  pane=Pane(pane.x,pane.y+delta,pane.dx,pane.dy-delta);

  return ret;
 }

inline Pane SplitY(Pane &pane,Coordinate delta)
 {
  auto dy=pane.dy-delta;

  Pane ret=Pane(pane.x,pane.y+dy,pane.dx,delta);

  pane=Pane(pane.x,pane.y,pane.dx,dy);

  return ret;
 }


inline Pane TrySplitX(Coordinate delta,Pane &pane)
 {
  if( delta<=pane.dx ) return SplitX(delta,pane);

  return Empty;
 }

inline Pane TrySplitX(Pane &pane,Coordinate delta)
 {
  if( delta<=pane.dx ) return SplitX(pane,delta);

  return Empty;
 }

inline Pane TrySplitY(Coordinate delta,Pane &pane)
 {
  if( delta<=pane.dy ) return SplitY(delta,pane);

  return Empty;
 }

inline Pane TrySplitY(Pane &pane,Coordinate delta)
 {
  if( delta<=pane.dy ) return SplitY(pane,delta);

  return Empty;
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

/* struct CoordAcc */

struct CoordAcc
 {
  Coord value = 0 ;
  bool overflow = false ;

  CoordAcc() {}

  void add(Coord dx) // >= 0
   {
    MCoord s=(MCoord)value+dx;

    if( s>MaxCoord )
      {
       value=MaxCoord;
       overflow=true;
      }
    else
      {
       value=Coord(s);
      }
   }
 };

} // namespace Video
} // namespace CCore

#endif


