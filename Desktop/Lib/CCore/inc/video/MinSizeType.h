/* MinSizeType.h */
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

#ifndef CCore_inc_video_MinSizeType_h
#define CCore_inc_video_MinSizeType_h

#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {

/* concept MinSizeType<T> */

template <class T> // ref extended
concept bool MinSizeType = requires(Meta::ToConst<T> &cobj)
 {
  { cobj.toSizePoint() } -> Point ;
 } ;

/* Box...() */

inline Coordinate BoxSpace(Coordinate dxy) { return dxy/5; }

inline Coord BoxSpace(Coord dxy) { return dxy/5; }

inline Coordinate BoxExt(Coordinate dxy) { return dxy+BoxSpace(dxy); }

inline Coord BoxExt(Coord dxy) { return +BoxExt(Coordinate(dxy)); }

/* classes */

struct SizeBox;

struct SizeBoxSpace;

struct SizeX;

struct SizeY;

struct SizeXSpace;

struct SizeYSpace;

/* struct SizeBox */

struct SizeBox
 {
  Coord dxy;

  SizeBox(Coord dxy_=0) : dxy(dxy_) {}

  SizeBox(Coordinate dxy_) : dxy(+dxy_) {}

  Point toSizePoint() const { return {dxy,dxy}; }
 };

/* struct SizeBoxSpace */

struct SizeBoxSpace
 {
  Coord dxy;
  Coord space;

  SizeBoxSpace(Coord dxy_=0) : dxy(dxy_),space(BoxSpace(dxy_)) {}

  SizeBoxSpace(Coordinate dxy_) : dxy(+dxy_),space(+BoxSpace(dxy_)) {}

  SizeBoxSpace(Coord dxy_,Coord space_) : dxy(dxy_),space(space_) {}

  SizeBoxSpace(Coordinate dxy_,Coordinate space_) : dxy(+dxy_),space(+space_) {}

  Point toSizePoint() const { return {dxy,dxy}; }
 };

/* struct SizeX */

struct SizeX
 {
  Coord dx;

  SizeX(Coord dx_=0) : dx(dx_) {}

  SizeX(Coordinate dx_) : dx(+dx_) {}

  Point toSizePoint() const { return {dx,0}; }
 };

/* struct SizeY */

struct SizeY
 {
  Coord dy;

  SizeY(Coord dy_=0) : dy(dy_) {}

  SizeY(Coordinate dy_) : dy(+dy_) {}

  Point toSizePoint() const { return {0,dy}; }
 };

/* struct SizeXSpace */

struct SizeXSpace
 {
  Coord dx;
  Coord space;

  SizeXSpace(Coord dx_=0,Coord space_=0) : dx(dx_),space(space_) {}

  SizeXSpace(Coordinate dx_,Coordinate space_=0) : dx(+dx_),space(+space_) {}

  Point toSizePoint() const { return {dx,0}; }
 };

/* struct SizeYSpace */

struct SizeYSpace
 {
  Coord dy;
  Coord space;

  SizeYSpace(Coord dy_=0,Coord space_=0) : dy(dy_),space(space_) {}

  SizeYSpace(Coordinate dy_,Coordinate space_=0) : dy(+dy_),space(+space_) {}

  Point toSizePoint() const { return {0,dy}; }
 };

/* operator >= */

bool operator >= (Point a,MinSizeType b) { return a>=b.toSizePoint(); }

/* ToSizePoint() */

inline Point ToSizePoint(Point size) { return size; }

Point ToSizePoint(MinSizeType size) { return size.toSizePoint(); }

} // namespace Video
} // namespace CCore

#endif

