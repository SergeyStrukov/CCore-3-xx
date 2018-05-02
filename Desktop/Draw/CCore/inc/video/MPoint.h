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

inline DCoord DMul(DCoord a,MCoord b) { return a*b; }

inline uDCoord UDMul(uDCoord a,uMCoord b) { return a*b; }

inline MCoord MulDiv(DCoord a,MCoord b,MCoord c) { IntGuard( c!=0 ); return MCoord( (a*b)/c ); }

inline uMCoord UMulDiv(uDCoord a,uMCoord b,uMCoord c) { IntGuard( c!=0 ); return uMCoord( (a*b)/c ); }

/* Position() */

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

struct Fraction;

struct MPoint;

struct Ratio;

/* struct Fraction */

struct Fraction
 {
  // consts

  static constexpr unsigned Precision = 10 ;

  static constexpr MCoord One = MCoord(1)<<Precision ;

  static constexpr MCoord Half = MCoord(1)<<(Precision-1) ;

  // value

  MCoord value;

  // constructors

  enum MaxPrecType { MaxPrec };

  Fraction(MCoord value_,MaxPrecType) : value(value_) {}

  Fraction(MCoord value_,unsigned prec) // prec <= Precision
   {
    value=IntLShift(value_,Precision-prec);
   }

  Fraction(Coord x) : Fraction(x,0) {}

  // methods

  using PrintProxyType = MCoord ;

  operator MCoord() const { return value; }

  MCoord operator + () const { return value; }

  static Coord RoundUp(MCoord value)
   {
    return IntRShift(value+One-1,Precision);
   }

  Coord roundUp() const { return RoundUp(value); }
 };

inline Coord RoundUpLen(MCoord dx) { return Fraction::RoundUp(dx); }

/* struct MPoint */

struct MPoint : BasePoint<MPoint,MCoord>
 {
  // consts

  static constexpr unsigned Precision = Fraction::Precision ;

  static constexpr MCoord One = Fraction::One ;

  static constexpr MCoord Half = Fraction::Half ;

  // LShift

  static MCoord LShift(Coord a) { return IntLShift(MCoord(a),Precision); }

  // RShift

  static Coord RShift(MCoord a) { return (Coord)IntRShift(IntAdd(a,Half),Precision); }

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

  Ratio(MCoord value_,unsigned prec) // prec <= Precision
   {
    value=IntLShift(value_,Precision-prec);
   }

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
    return Ratio( MCoord( IntRShift(DMul(a.value,b.value),Precision) ) );
   }

  friend Ratio operator / (Ratio a,Ratio b)
   {
    IntGuard( b.value!=0 );

    return Ratio( MCoord( IntLShift(DCoord(a.value),Precision)/b.value ) );
   }

  // multiplicators

  template <OneOfTypes<Coord,MCoord> Int>
  friend Int operator * (Ratio a,Int b)
   {
    return Int( IntRShift(DMul(a.value,b),Precision) );
   }
 };

inline Point operator * (Ratio a,Point point)
 {
  return Point(a*point.x,a*point.y);
 }

inline MCoord operator * (Ratio a,Fraction b)
 {
  return a*b.value;
 }

inline MPoint operator * (Ratio a,MPoint point)
 {
  return MPoint(a*point.x,a*point.y);
 }

inline Ratio Div(MCoord a,MCoord b) { return Ratio(a)/Ratio(b); }

inline Ratio XdivY(Point size) { return Div(size.x,size.y); }

inline Ratio YdivX(Point size) { return Div(size.y,size.x); }

inline Ratio XdivY(MPoint size) { return Div(size.x,size.y); }

inline Ratio YdivX(MPoint size) { return Div(size.y,size.x); }

/* AbsDist() */

inline uMCoord AbsDist(MPoint a,MPoint b)
 {
  return Max(IntAbs(a.x,b.x),IntAbs(a.y,b.y))>>MPoint::Precision;
 }

/* Length() */

DCoord Length(MCoord a,MCoord b);

inline DCoord Length(MPoint a) { return Length(a.x,a.y); }

/* Prod() */

inline DCoord Prod(MCoord a,MCoord b,MCoord x,MCoord y) { return DMul(a,x)+DMul(b,y); }

inline DCoord Prod(MCoord a,MCoord b,MPoint point) { return Prod(a,b,point.x,point.y); }

inline DCoord Prod(MPoint a,MPoint b) { return Prod(a.x,a.y,b.x,b.y); }

} // namespace Video
} // namespace CCore

#endif

