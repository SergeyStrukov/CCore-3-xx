/* Color.h */
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

#ifndef CCore_inc_video_Color_h
#define CCore_inc_video_Color_h

#include <CCore/inc/video/Gamma.h>

namespace CCore {
namespace Video {

/* types */

using Clr = uint8 ;

/* consts */

const unsigned ClrBits = 8 ;

const unsigned AlphaLim = 256 ;

const Clr MinClr =   0 ;

const Clr MedClr = 128 ;

const Clr MaxClr = 255 ;

/* functions */

inline Clr Blend(Clr dst,Clr alpha,Clr src)
 {
  uint16 Dst=GammaCorrect::Direct(dst);
  uint16 Src=GammaCorrect::Direct(src);

  return GammaCorrect::Inverse( (Dst*uint32(256-alpha)+Src*uint32(alpha))>>8 );
 }

inline Clr Blend(Clr dst,Clr alpha,Clr src,GammaFunc gamma)
 {
  uint16 Dst=gamma.direct[dst];
  uint16 Src=gamma.direct[src];

  return gamma.inverse[ (Dst*uint32(256-alpha)+Src*uint32(alpha))>>8 ];
 }

inline uint16 BlendBeta(Clr alpha) { return uint16(256-alpha); }

inline uint32 BlendSrc(Clr alpha,Clr src)
 {
  uint16 Src=GammaCorrect::Direct(src);

  return Src*uint32(alpha);
 }

inline Clr PreparedBlend(Clr dst,uint16 beta,uint32 src)
 {
  uint16 Dst=GammaCorrect::Direct(dst);

  return GammaCorrect::Inverse( (Dst*uint32(beta)+src)>>8 );
 }

inline uint32 BlendSrc(Clr alpha,Clr src,GammaFunc gamma)
 {
  uint16 Src=gamma.direct[src];

  return Src*uint32(alpha);
 }

inline Clr PreparedBlend(Clr dst,uint16 beta,uint32 src,GammaFunc gamma)
 {
  uint16 Dst=gamma.direct[dst];

  return gamma.inverse[ (Dst*uint32(beta)+src)>>8 ];
 }

/* classes */

//enum VColor;

class Blender;

class GammaBlender;

class TripleBlender;

class RawColor16;

class RawColor24;

class RawColor24Inv;

class RawColor32;

class RawColor32Inv;

/* enum VColor */

enum VColor : uint32
 {
  Black       = 0x000000,
  Gray        = 0x808080,
  Silver      = 0xC0C0C0,
  White       = 0xFFFFFF,

  Red         = 0xFF0000,
  Green       = 0x00FF00,
  Blue        = 0x0000FF,

  Cyan        = 0x00FFFF,
  Fuchsia     = 0xFF00FF,
  Yellow      = 0xFFFF00,

  Teal        = 0x008080,
  Purple      = 0x800080,
  Olive       = 0x808000,

  // extra

  Aqua        = 0x00FFFF,
  Maroon      = 0x800000,
  Navy        = 0x000080,
  Orange      = 0xFFA500,
  Crimson     = 0xDC143C,
  DarkGray    = 0xA9A9A9,
  DarkGreen   = 0x006400,
  DarkOrange  = 0xFF8C00,
  DarkOrchid  = 0x9932CC,
  DarkRed     = 0x8B0000,
  DarkViolet  = 0x9400D3,
  DimGray     = 0x696969,
  ForestGreen = 0x228B22,
  GhostWhite  = 0xF8F8FF,
  Gold        = 0xFFD700,
  GoldenRod   = 0xDAA520,
  Indigo      = 0x4B0082,
  Ivory       = 0xFFFFF0,
  Lavender    = 0xE6E6FA,
  LightGray   = 0xD3D3D3,
  MediumBlue  = 0x0000CD,
  OrangeRed   = 0xFF4500,
  Orchid      = 0xDA70D6,
  SeaGreen    = 0x2E8B57,
  SkyBlue     = 0x87CEEB,
  Snow        = 0xFFFAFA,
  SteelBlue   = 0x4682B4,
  Violet      = 0xEE82EE,
  Wheat       = 0xF5DEB3,
  RoyalBlue   = 0x4169E1,
  DeepSkyBlue = 0x00BFFF,
  Pink        = 0xFFC0CB,
  PaleGreen   = 0x98FB98
 };

inline constexpr Clr RedOf(VColor vc) { return Clr(vc>>16); }

inline constexpr Clr GreenOf(VColor vc) { return Clr(vc>>8); }

inline constexpr Clr BlueOf(VColor vc) { return Clr(vc); }

inline constexpr VColor RGBColor(Clr r,Clr g,Clr b) { return VColor(b|(uint32(g)<<8)|(uint32(r)<<16)); }

inline constexpr VColor GrayColor(Clr rgb) { return RGBColor(rgb,rgb,rgb); }

/* class Blender */

class Blender
 {
   uint16 beta;

   uint32 src_r;
   uint32 src_g;
   uint32 src_b;

  public:

   Blender(Clr alpha,VColor vc)
    {
     beta=BlendBeta(alpha);

     src_r=BlendSrc(alpha,RedOf(vc));
     src_g=BlendSrc(alpha,GreenOf(vc));
     src_b=BlendSrc(alpha,BlueOf(vc));
    }

   Clr blendR(Clr r) const { return PreparedBlend(r,beta,src_r); }

   Clr blendG(Clr g) const { return PreparedBlend(g,beta,src_g); }

   Clr blendB(Clr b) const { return PreparedBlend(b,beta,src_b); }
 };

/* class GammaBlender */

class GammaBlender
 {
   uint16 beta;

   uint32 src_r;
   uint32 src_g;
   uint32 src_b;

   GammaFunc gamma;

  public:

   GammaBlender(Clr alpha,VColor vc,GammaFunc gamma_)
    : gamma(gamma_)
    {
     beta=BlendBeta(alpha);

     src_r=BlendSrc(alpha,RedOf(vc),gamma_);
     src_g=BlendSrc(alpha,GreenOf(vc),gamma_);
     src_b=BlendSrc(alpha,BlueOf(vc),gamma_);
    }

   Clr blendR(Clr r) const { return PreparedBlend(r,beta,src_r,gamma); }

   Clr blendG(Clr g) const { return PreparedBlend(g,beta,src_g,gamma); }

   Clr blendB(Clr b) const { return PreparedBlend(b,beta,src_b,gamma); }
 };

/* class TripleBlender */

class TripleBlender
 {
   Clr alpha_r,alpha_g,alpha_b;
   Clr src_r,src_g,src_b;
   GammaFunc gamma;

  public:

   TripleBlender(Clr alpha_r_,Clr alpha_g_,Clr alpha_b_,VColor vc,GammaFunc gamma_)
    : alpha_r(alpha_r_),
      alpha_g(alpha_g_),
      alpha_b(alpha_b_),
      gamma(gamma_)
    {
     src_r=RedOf(vc);
     src_g=GreenOf(vc);
     src_b=BlueOf(vc);
    }

   Clr blendR(Clr r) const { return (alpha_r<MaxClr)?Blend(r,alpha_r,src_r,gamma):src_r; }

   Clr blendG(Clr g) const { return (alpha_g<MaxClr)?Blend(g,alpha_g,src_g,gamma):src_g; }

   Clr blendB(Clr b) const { return (alpha_b<MaxClr)?Blend(b,alpha_b,src_b,gamma):src_b; }
 };

/* concept BlenderType<Blender> */

template <NothrowCopyableType Blender>
concept bool BlenderType = requires(Blender &obj,Clr c)
 {
  { obj.blendR(c) } -> Clr ;
  { obj.blendG(c) } -> Clr ;
  { obj.blendB(c) } -> Clr ;
 } ;

/* class RawColor16 */

class RawColor16
 {
  public:

   using Raw = uint16 ;

   static const unsigned RawCount = 1 ;

  private:

   Raw color[RawCount];

  private:

   static uint16 Pack565(uint16 r,uint16 g,uint16 b) { return (r<<11)|(g<<5)|b; }

  public:

   RawColor16(VColor vc=Black) { set(vc); }

   // methods

   Clr getR() const { return Clr( (color[0]>>11)<<3 ); }

   Clr getG() const { return Clr( (color[0]>>5)<<2 ); }

   Clr getB() const { return Clr( color[0]<<3 ); }

   VColor get() const { Raw raw=color[0]; return RGBColor(Clr( (raw>>11)<<3 ),Clr( (raw>>5)<<2 ),Clr( raw<<3 )); }

   void set(VColor vc) { set(RedOf(vc),GreenOf(vc),BlueOf(vc)); }

   void set(Clr r,Clr g,Clr b) { color[0]=Pack565(r>>3,g>>2,b>>3); }

   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }

   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; }

   static void BlendTo(BlenderType blender,Raw dst[RawCount])
    {
     Raw raw=dst[0];

     Clr r=Clr( (raw>>11)<<3 );
     Clr g=Clr( (raw>>5)<<2 );
     Clr b=Clr( raw<<3 );

     dst[0]=Pack565(blender.blendR(r),blender.blendG(g),blender.blendB(b));
    }

   void blend(BlenderType blender) { BlendTo(blender,color); }

   void blend(Clr alpha,VColor vc) { blend(Blender(alpha,vc)); }
 };

/* class RawColor24 */

class RawColor24
 {
  public:

   using Raw = uint8 ;

   static const unsigned RawCount = 3 ;

  private:

   Raw color[RawCount];

  public:

   RawColor24(VColor vc=Black) { set(vc); }

   // methods

   Clr getR() const { return color[0]; }

   Clr getG() const { return color[1]; }

   Clr getB() const { return color[2]; }

   VColor get() const { return RGBColor(color[0],color[1],color[2]); }

   void set(VColor vc) { set(RedOf(vc),GreenOf(vc),BlueOf(vc)); }

   void set(Clr r,Clr g,Clr b) { color[0]=r; color[1]=g; color[2]=b; }

   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; dst[1]=color[1]; dst[2]=color[2]; }

   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; color[1]=src[1]; color[2]=src[2]; }

   static void BlendTo(BlenderType blender,Raw dst[RawCount])
    {
     dst[0]=blender.blendR(dst[0]);
     dst[1]=blender.blendG(dst[1]);
     dst[2]=blender.blendB(dst[2]);
    }

   void blend(BlenderType blender) { BlendTo(blender,color); }

   void blend(Clr alpha,VColor vc) { blend(Blender(alpha,vc)); }
 };

/* class RawColor24Inv */

class RawColor24Inv
 {
  public:

   using Raw = uint8 ;

   static const unsigned RawCount = 3 ;

  private:

   Raw color[RawCount];

  public:

   RawColor24Inv(VColor vc=Black) { set(vc); }

   // methods

   Clr getR() const { return color[2]; }

   Clr getG() const { return color[1]; }

   Clr getB() const { return color[0]; }

   VColor get() const { return RGBColor(color[2],color[1],color[0]); }

   void set(VColor vc) { set(RedOf(vc),GreenOf(vc),BlueOf(vc)); }

   void set(Clr r,Clr g,Clr b) { color[0]=b; color[1]=g; color[2]=r; }

   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; dst[1]=color[1]; dst[2]=color[2]; }

   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; color[1]=src[1]; color[2]=src[2]; }

   static void BlendTo(BlenderType blender,Raw dst[RawCount])
    {
     dst[0]=blender.blendB(dst[0]);
     dst[1]=blender.blendG(dst[1]);
     dst[2]=blender.blendR(dst[2]);
    }

   void blend(BlenderType blender) { BlendTo(blender,color); }

   void blend(Clr alpha,VColor vc) { blend(Blender(alpha,vc)); }
 };

/* class RawColor32 */

class RawColor32
 {
  public:

   using Raw = uint32 ;

   static const unsigned RawCount = 1 ;

  private:

   Raw color[RawCount];

   static uint32 Pack888(uint32 r,uint32 g,uint32 b) { return b|(g<<8)|(r<<16); }

  public:

   RawColor32(VColor vc=Black) { set(vc); }

   // methods

   Clr getR() const { return Clr(color[0]>>16); }

   Clr getG() const { return Clr(color[0]>>8); }

   Clr getB() const { return Clr(color[0]); }

   VColor get() const { Raw raw=color[0]; return RGBColor(Clr(raw>>16),Clr(raw>>8),Clr(raw)); }

   void set(VColor vc) { color[0]=vc; }

   void set(Clr r,Clr g,Clr b) { color[0]=Pack888(r,g,b); }

   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }

   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; }

   static void BlendTo(BlenderType blender,Raw dst[RawCount])
    {
     Raw raw=dst[0];

     Clr r=Clr(raw>>16);
     Clr g=Clr(raw>> 8);
     Clr b=Clr(raw    );

     dst[0]=Pack888(blender.blendR(r),blender.blendG(g),blender.blendB(b));
    }

   void blend(BlenderType blender) { BlendTo(blender,color); }

   void blend(Clr alpha,VColor vc) { blend(Blender(alpha,vc)); }
 };

/* class RawColor32Inv */

class RawColor32Inv
 {
  public:

   using Raw = uint32 ;

   static const unsigned RawCount = 1 ;

  private:

   Raw color[RawCount];

   static uint32 Pack888(uint32 r,uint32 g,uint32 b) { return r|(g<<8)|(b<<16); }

  public:

   RawColor32Inv(VColor vc=Black) { set(vc); }

   // methods

   Clr getR() const { return Clr(color[0]); }

   Clr getG() const { return Clr(color[0]>>8); }

   Clr getB() const { return Clr(color[0]>>16); }

   VColor get() const { Raw raw=color[0]; return RGBColor(Clr(raw),Clr(raw>>8),Clr(raw>>16)); }

   void set(VColor vc) { set(RedOf(vc),GreenOf(vc),BlueOf(vc)); }

   void set(Clr r,Clr g,Clr b) { color[0]=Pack888(r,g,b); }

   void copyTo(Raw dst[RawCount]) const { dst[0]=color[0]; }

   void copyFrom(const Raw src[RawCount]) { color[0]=src[0]; }

   static void BlendTo(BlenderType blender,Raw dst[RawCount])
    {
     Raw raw=dst[0];

     Clr r=Clr(raw    );
     Clr g=Clr(raw>> 8);
     Clr b=Clr(raw>>16);

     dst[0]=Pack888(blender.blendR(r),blender.blendG(g),blender.blendB(b));
    }

   void blend(BlenderType blender) { BlendTo(blender,color); }

   void blend(Clr alpha,VColor vc) { blend(Blender(alpha,vc)); }
 };

/* concept RawColorType<RawColor> */

template <class RawColor,class Raw>
concept bool RawColorType2 = requires(RawColor &obj,const RawColor &cobj,Raw *dst,const Raw *src,Blender blender)
 {
  cobj.copyTo(dst);

  obj.copyFrom(src);

  RawColor::BlendTo(blender,dst);
 } ;

template <NothrowCopyableType RawColor>
concept bool RawColorType = requires(RawColor &obj,const RawColor &cobj,Clr alpha,VColor vc,Clr r,Clr g,Clr b,Blender blender)
 {
  typename RawColor::Raw;

  { RawColor::RawCount } -> unsigned ;

  RawColor();

  RawColor(vc);

  { cobj.getR() } -> Clr ;

  { cobj.getG() } -> Clr ;

  { cobj.getB() } -> Clr ;

  { cobj.get() } -> VColor ;

  obj.set(vc);

  obj.set(r,g,b);

  obj.blend(alpha,vc);

  obj.blend(blender);

  requires ( RawColorType2<RawColor,typename RawColor::Raw> );
 } ;

} // namespace Video
} // namespace CCore

#endif


