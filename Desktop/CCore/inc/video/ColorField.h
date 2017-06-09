/* ColorField.h */
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

#ifndef CCore_inc_video_ColorField_h
#define CCore_inc_video_ColorField_h

#include <CCore/inc/video/Point.h>
#include <CCore/inc/video/Color.h>

namespace CCore {
namespace Video {

/* functions */

inline Clr Linear(Clr a,Clr b,uint16 c,uint16 d)
 {
  if( a<b ) return Clr( a+(uint32(b-a)*c)/d );

  if( a==b ) return a;

  return Clr( a-(uint32(a-b)*c)/d );
 }

inline VColor Linear(VColor a,VColor b,uint16 c,uint16 d)
 {
  return RGBColor(Linear(RedOf(a),RedOf(b),c,d),Linear(GreenOf(a),GreenOf(b),c,d),Linear(BlueOf(a),BlueOf(b),c,d));
 }

/* classes */

struct AlphaColor;

class ConstantField;

class ConstantAlphaField;

class TwoField;

class XField;

class YField;

class RadioField;

struct AbstractField;

struct AbstractAlphaField;

/* struct AlphaColor */

struct AlphaColor
 {
  VColor vc;
  unsigned alpha;
 };

/* class ConstantField */

class ConstantField
 {
   VColor vc;

  public:

   explicit ConstantField(VColor vc_) : vc(vc_) {}

   VColor operator () (MPoint) const { return vc; }
 };

/* class ConstantAlphaField */

class ConstantAlphaField
 {
   AlphaColor ac;

  public:

   explicit ConstantAlphaField(VColor vc,unsigned alpha) : ac{vc,alpha} {}

   AlphaColor operator () (MPoint) const { return ac; }
 };

/* class TwoField */

class TwoField
 {
   MPoint a;
   VColor va;
   MPoint b;
   VColor vb;

   DCoord D;
   DownBits<uint16> d;

  public:

   TwoField(MPoint a,VColor va,MPoint b,VColor vb);

   VColor operator () (MPoint point) const;
 };

/* class XField */

class XField : public TwoField
 {
  public:

   XField(MCoord a,VColor va,MCoord b,VColor vb) : TwoField({a,0},va,{b,0},vb) {}
 };

/* class YField */

class YField : public TwoField
 {
  public:

   YField(MCoord a,VColor va,MCoord b,VColor vb) : TwoField({0,a},va,{0,b},vb) {}
 };

/* class RadioField */

class RadioField
 {
   MPoint center;
   MCoord radius;
   VColor vc;
   VColor va;

   DownBits<uint16> d;

  public:

   RadioField(MPoint center,MCoord radius,VColor vc,VColor va);

   VColor operator () (MPoint point) const;
 };

/* struct AbstractField */

struct AbstractField
 {
  virtual VColor operator () (MPoint) const =0;
 };

/* struct AbstractAlphaField */

struct AbstractAlphaField
 {
  virtual AlphaColor operator () (MPoint) const =0;
 };

/* concept VColorFieldType<Field> */

template <class Field> // ref extended
concept bool VColorFieldType = requires(Meta::ToConst<Field> &field,MPoint p)
 {
  { field(p) } -> VColor ;
 } ;

/* concept AlphaColorFieldType<Field> */

template <class Field> // ref extended
concept bool AlphaColorFieldType = requires(Meta::ToConst<Field> &field,MPoint p)
 {
  { field(p) } -> AlphaColor ;
 } ;

/* concept ColorFieldType<Field> */

template <class Field> // ref extended
concept bool ColorFieldType = VColorFieldType<Field> || AlphaColorFieldType<Field> ;

} // namespace Video
} // namespace CCore

#endif


