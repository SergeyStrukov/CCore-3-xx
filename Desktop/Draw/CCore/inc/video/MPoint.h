/* MPoint.h */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_MPoint_h
#define CCore_inc_video_MPoint_h

#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {

/* types */

using MCoord = sint32 ;

using uMCoord = uint32 ;

using DCoord = sint64 ;

using uDCoord = uint64 ;

/* consts */

inline constexpr MCoord MaxMCoord = 2'147'483'647 ;

/* functions */

template <OneOfTypes<Coord,MCoord> T>
T Sup(T a,T b) { return Max(a,b); }

template <OneOfTypes<Coord,MCoord> T>
T Inf(T a,T b) { return Min(a,b); }

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

/* classes */

struct MPoint;

struct Ratio;

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

/* struct Ratio */

struct Ratio
 {
  // consts

  static constexpr unsigned Precision = 16 ;

  // data

  sint32 value;

  // constructors

  Ratio() noexcept : value(0) {}

  explicit Ratio(sint32 value_) : value(value_) {}

  Ratio(sint32 value_,unsigned prec) : value( IntLShift(value_,Precision-prec) ) {} // prec <= Precision

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
    return Ratio( sint32( IntRShift(sint64(a.value)*b.value,Precision) ) );
   }

  friend Ratio operator / (Ratio a,Ratio b)
   {
    IntGuard( b.value!=0 );

    return Ratio( sint32( IntLShift(sint64(a.value),Precision)/b.value ) );
   }

  // multiplicators

  friend Coord operator * (Ratio a,Coord b)
   {
    return To16( IntRShift(sint64(a.value)*b,Precision) );
   }

  friend sint32 operator * (Ratio a,sint32 b)
   {
    return sint32( IntRShift(sint64(a.value)*b,Precision) );
   }
 };

inline Coordinate operator * (Ratio a,Coordinate c)
 {
  return a*c.x;
 }

inline Point operator * (Ratio a,Point point)
 {
  return Point(a*point.x,a*point.y);
 }

inline MPoint operator * (Ratio a,MPoint point)
 {
  return MPoint(a*point.x,a*point.y);
 }

inline Ratio Div(sint32 a,sint32 b) { return Ratio(a)/Ratio(b); }

inline Ratio XdivY(Point size) { return Div(size.x,size.y); }

inline Ratio YdivX(Point size) { return Div(size.y,size.x); }

/* Prod() */

inline DCoord Length(MPoint a) { return Length(a.x,a.y); }

inline DCoord Prod(MCoord a,MCoord b,MCoord x,MCoord y) { return DCoord(a)*x+DCoord(b)*y; }

inline DCoord Prod(MCoord a,MCoord b,MPoint point) { return Prod(a,b,point.x,point.y); }

inline DCoord Prod(MPoint a,MPoint b) { return Prod(a.x,a.y,b.x,b.y); }

/* functions */

inline Ratio XdivY(MPoint size) { return Div(size.x,size.y); }

inline Ratio YdivX(MPoint size) { return Div(size.y,size.x); }

} // namespace Video
} // namespace CCore

#endif

