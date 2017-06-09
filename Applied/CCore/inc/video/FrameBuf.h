/* FrameBuf.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FrameBuf_h
#define CCore_inc_video_FrameBuf_h

#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {

/* types */

using DLineType = unsigned ;

/* classes */

struct ColorPlane;

class MonoGlyph;

class GrayGlyph;

class RGBGlyph;

struct CutExtension;

template <RawColorType RawColor> class FrameBuf;

/* struct ColorPlane */

struct ColorPlane
 {
  void *raw;
  Coord dx; // >=0
  Coord dy; // >=0
  DLineType dline; // in chars

  ColorPlane() : raw(0),dx(0),dy(0),dline(0) {}

  ColorPlane(void *raw_,Coord dx_,Coord dy_,DLineType dline_) : raw(raw_),dx(dx_),dy(dy_),dline(dline_) {}
 };

/* class MonoGlyph */

class MonoGlyph : ColorPlane
 {
   unsigned bitoff = 0 ; // < 8

  private:

   struct BitPtr
    {
     uint8 *ptr;
     unsigned bitoff; // < 8

     void shift(unsigned delta) // < 8
      {
       delta+=bitoff;

       if( delta>=8 )
         {
          delta-=8;
          ptr++;
         }

       bitoff=delta;
      }
    };

   BitPtr place(Point p) const
    {
     DLineType x=DLineType(p.x);

     BitPtr ptr{getBase()+dline*ulen(p.y)+(x>>3),bitoff};

     ptr.shift(x&7u);

     return ptr;
    }

  public:

   MonoGlyph() {}

   MonoGlyph(const ColorPlane &plane) : ColorPlane(plane) {}

   MonoGlyph(const ColorPlane &plane,unsigned bitoff_) : ColorPlane(plane),bitoff(bitoff_) {}

   Coord dX() const { return dx; }

   Coord dY() const { return dy; }

   unsigned bitOff() const { return bitoff; }

   Pane getPane(Point p) const { return Pane(p,dx,dy); }

   // unsafe methods

   uint8 * getBase() const { return static_cast<uint8 *>(raw); }

   uint8 * nextY(uint8 *ptr) const { return ptr+dline; }

   MonoGlyph cut(Pane pane) const
    {
     BitPtr ptr=place(pane.getBase());

     return MonoGlyph(ColorPlane(ptr.ptr,pane.dx,pane.dy,dline),ptr.bitoff);
    }
 };

/* class GrayGlyph */

class GrayGlyph : ColorPlane
 {
  private:

   Clr * place(Point p) const { return getBase()+dline*ulen(p.y)+DLineType(p.x); }

  public:

   GrayGlyph() {}

   GrayGlyph(const ColorPlane &plane) : ColorPlane(plane) {}

   Coord dX() const { return dx; }

   Coord dY() const { return dy; }

   Pane getPane(Point p) const { return Pane(p,dx,dy); }

   // unsafe methods

   Clr * getBase() const { return static_cast<Clr *>(raw); }

   Clr * nextY(Clr *ptr) const { return ptr+dline; }

   GrayGlyph cut(Pane pane) const
    {
     return ColorPlane(place(pane.getBase()),pane.dx,pane.dy,dline);
    }
 };

/* class RGBGlyph */

class RGBGlyph : ColorPlane
 {
  private:

   Clr * place(Point p) const { return getBase()+dline*ulen(p.y)+3*DLineType(p.x); }

  public:

   RGBGlyph() {}

   RGBGlyph(const ColorPlane &plane) : ColorPlane(plane) {}

   Coord dX() const { return dx; }

   Coord dY() const { return dy; }

   Pane getPane(Point p) const { return Pane(p,dx,dy); }

   // unsafe methods

   Clr * getBase() const { return static_cast<Clr *>(raw); }

   Clr * nextY(Clr *ptr) const { return ptr+dline; }

   RGBGlyph cut(Pane pane) const
    {
     return ColorPlane(place(pane.getBase()),pane.dx,pane.dy,dline);
    }
 };

/* concept BoolPatternType<Pattern> */

template <NothrowCopyableType Pattern> // ref extended
concept bool BoolPatternType = requires(Meta::ToConst<Pattern> &cobj,Coord x)
 {
  { cobj.dX() } -> Coord ; // > 0

  { cobj[x] } -> bool ;
 } ;

/* concept BoolGlyphType<Glyph> */

template <NothrowCopyableType Glyph> // ref extended
concept bool BoolGlyphType = requires(Meta::ToConst<Glyph> &cobj,Coord y)
 {
  { cobj.dX() } -> Coord ; // > 0

  { cobj.dY() } -> Coord ; // > 0

  cobj[y];

  requires ( BoolPatternType<decltype( cobj[y] )> );
 } ;

/* struct CutExtension */

struct CutExtension
 {
  Coord pos;
  Coord ind;
  Coord lim;

  CutExtension(Coord len,Coord glen,Coord pos) // len >= 0 , glen >= 0
   {
    if( pos<0 )
      {
       this->pos=0;

       if( glen+pos>0 )
         {
          ind=-pos;
          lim=ind+Min_cast(len,glen-ind);
         }
       else
         {
          ind=0;
          lim=0;
         }
      }
    else
      {
       this->pos=pos;

       ind=0;

       if( pos<len )
         lim=Min_cast(glen,len-pos);
       else
         lim=0;
      }
   }

  bool operator + () const { return ind<lim; }

  bool operator ! () const { return ind>=lim; }
 };

/* class FrameBuf<RawColor> */

template <RawColorType RawColor>
class FrameBuf : protected ColorPlane
 {
  protected:

   using Raw = typename RawColor::Raw ;

   // unsafe methods

   Raw * place(Coord y) const { return static_cast<Raw *>(PtrAdd(raw,ulen(y)*dline)); }

   Raw * place(Point p) const { return place(p.y)+DLineType(p.x)*RawColor::RawCount; }

   static Raw * NextX(Raw *ptr) { return ptr+RawColor::RawCount; }

   static Raw * PrevX(Raw *ptr) { return ptr-RawColor::RawCount; }

   Raw * nextY(Raw *ptr) const { return static_cast<Raw *>(PtrAdd(ptr,dline)); }

   Raw * prevY(Raw *ptr) const { return static_cast<Raw *>(PtrSub(ptr,dline)); }

   Raw * nextXnextY(Raw *ptr) const { return NextX(nextY(ptr)); }

   Raw * nextXprevY(Raw *ptr) const { return NextX(prevY(ptr)); }

   Raw * prevXnextY(Raw *ptr) const { return PrevX(nextY(ptr)); }

   Raw * prevXprevY(Raw *ptr) const { return PrevX(prevY(ptr)); }

  private:

   // unsafe methods

   static void HLine(Raw *ptr,Coord len,RawColor color);

   static void HLine(Raw *ptr,Coord len,BlenderType blender);

   static void Save(Raw *ptr,Coord len,RawColor buf[/* len */]);

   static void Load(Raw *ptr,Coord len,const RawColor buf[/* len */]);

   static void HLine(Raw *ptr,BoolPatternType pat,RawColor back,RawColor fore);

   static void HLine(Raw *ptr,BoolPatternType pat,RawColor fore);

   static void HLine(Raw *ptr,BoolPatternType pat,Coord gx,Coord lim,RawColor fore); // gx < lim

   static void HLine_mono(Raw *ptr,const uint8 *base,unsigned bitoff,Coord dx,RawColor color);

   static void HLine(Raw *ptr,const Clr *base,Coord dx,VColor vc,GammaFunc gamma);

   static void HLine_rgb(Raw *ptr,const Clr *base,Coord dx,VColor vc,GammaFunc gamma);

   static void HLine_bgr(Raw *ptr,const Clr *base,Coord dx,VColor vc,GammaFunc gamma);

  public:

   FrameBuf() {}

   FrameBuf(const ColorPlane &plane) : ColorPlane(plane) {}

   FrameBuf(const FrameBuf<RawColor> &buf,Pane pane); // unsafe

   // properties

   bool operator + () const { return dx>0 && dy>0 ; }

   bool operator ! () const { return dx<=0 || dy<=0 ; }

   Coord dX() const { return dx; }

   Coord dY() const { return dy; }

   Pane getPane() const { return Pane(Null,dx,dy); }

   Point getSize() const { return Point(dx,dy); }

   AreaType getArea() const { return Area(dx,dy); }

   // unsafe methods

   FrameBuf<RawColor> cutFrame_unsafe(Pane pane) const { return FrameBuf<RawColor>(*this,pane); }

   RawColor pixel_unsafe(Point p) const;

   void pixel_unsafe(Point p,RawColor color);

   void block_unsafe(Pane pane,RawColor color);

   void block_unsafe(Pane pane,VColor vc) { block_unsafe(pane,RawColor(vc)); }

   void block_unsafe(Pane pane,BlenderType blender);

   void block_unsafe(Pane pane,VColor vc,Clr alpha);

   void save_unsafe(Pane pane,RawColor buf[/* pane.getArea() */]);

   void load_unsafe(Pane pane,const RawColor buf[/* pane.getArea() */]);

   void glyph_unsafe(Point p,BoolGlyphType gly,RawColor back,RawColor fore);

   void glyph_unsafe(Point p,BoolGlyphType gly,RawColor fore);

   void glyph_unsafe(Point p,MonoGlyph gly,RawColor color);

   void glyph_unsafe(Point p,GrayGlyph gly,VColor vc,GammaFunc gamma);

   void glyph_rgb_unsafe(Point p,RGBGlyph gly,VColor vc,GammaFunc gamma);

   void glyph_bgr_unsafe(Point p,RGBGlyph gly,VColor vc,GammaFunc gamma);

   // safe methods

   void test();

   void erase(RawColor color);

   void erase(VColor vc,Clr alpha);

   void pixel_safe(Point p,RawColor color);

   void block_safe(Pane pane,RawColor color);

   void block_safe(Pane pane,VColor vc) { block_safe(pane,RawColor(vc)); }

   void block_safe(Pane pane,BlenderType blender);

   void block_safe(Pane pane,VColor vc,Clr alpha);

   void glyph_safe(Point p,BoolGlyphType gly,RawColor fore);

   void glyph_safe(Point p,MonoGlyph gly,RawColor color);

   void glyph_safe(Point p,GrayGlyph gly,VColor vc,GammaFunc gamma);

   void glyph_safe(Point p,RGBGlyph gly,VColor vc,GammaFunc gamma,bool bgr);
 };

template <RawColorType RawColor>
void FrameBuf<RawColor>::HLine(Raw *ptr,Coord len,RawColor color)
 {
  for(; len>0 ;len--,ptr=NextX(ptr)) color.copyTo(ptr);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::HLine(Raw *ptr,Coord len,BlenderType blender)
 {
  for(; len>0 ;len--,ptr=NextX(ptr)) RawColor::BlendTo(blender,ptr);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::Save(Raw *ptr,Coord len,RawColor buf[])
 {
  for(; len>0 ;len--,ptr=NextX(ptr),buf++) buf->copyFrom(ptr);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::Load(Raw *ptr,Coord len,const RawColor buf[])
 {
  for(; len>0 ;len--,ptr=NextX(ptr),buf++) buf->copyTo(ptr);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::HLine(Raw *ptr,BoolPatternType pat,RawColor back,RawColor fore)
 {
  Coord bdx=pat.dX();

  for(Coord bx=0; bx<bdx ;bx++,ptr=NextX(ptr))
    if( pat[bx] )
      fore.copyTo(ptr);
    else
      back.copyTo(ptr);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::HLine(Raw *ptr,BoolPatternType pat,RawColor fore)
 {
  Coord bdx=pat.dX();

  for(Coord bx=0; bx<bdx ;bx++,ptr=NextX(ptr))
    if( pat[bx] )
      fore.copyTo(ptr);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::HLine(Raw *ptr,BoolPatternType pat,Coord gx,Coord lim,RawColor fore)
 {
  if( pat[gx] ) fore.copyTo(ptr);

  while( ++gx<lim )
    {
     ptr=NextX(ptr);

     if( pat[gx] ) fore.copyTo(ptr);
    }
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::HLine_mono(Raw *ptr,const uint8 *base,unsigned bitoff,Coord dx,RawColor color)
 {
  struct Bits
   {
    const uint8 *ptr;
    uint8 mask;
    uint8 bit;

    Bits(const uint8 *base,unsigned bitoff)
     {
      ptr=base;
      mask=*ptr;
      bit=uint8( 128u>>bitoff );
     }

    uint8 operator * ()
     {
      if( !bit )
        {
         mask=*(++ptr);
         bit=128u;
        }

      return mask&bit;
     }

    void operator ++ ()
     {
      bit>>=1;
     }
   };

  if( dx<=0 ) return;

  for(Bits bits(base,bitoff); dx>0 ;dx--,ptr=NextX(ptr),++bits)
    {
     if( *bits ) color.copyTo(ptr);
    }
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::HLine(Raw *ptr,const Clr *base,Coord dx,VColor vc,GammaFunc gamma)
 {
  RawColor color(vc);

  for(; dx>0 ;dx--,ptr=NextX(ptr),base++)
    {
     Clr alpha=*base;

     if( alpha<MaxClr )
       {
        GammaBlender blender(alpha,vc,gamma);

        RawColor::BlendTo(blender,ptr);
       }
     else
       {
        color.copyTo(ptr);
       }
    }
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::HLine_rgb(Raw *ptr,const Clr *base,Coord dx,VColor vc,GammaFunc gamma)
 {
  for(; dx>0 ;dx--,ptr=NextX(ptr),base+=3)
    {
     TripleBlender blender(base[0],base[1],base[2],vc,gamma);

     RawColor::BlendTo(blender,ptr);
    }
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::HLine_bgr(Raw *ptr,const Clr *base,Coord dx,VColor vc,GammaFunc gamma)
 {
  for(; dx>0 ;dx--,ptr=NextX(ptr),base+=3)
    {
     TripleBlender blender(base[2],base[1],base[0],vc,gamma);

     RawColor::BlendTo(blender,ptr);
    }
 }

template <RawColorType RawColor>
FrameBuf<RawColor>::FrameBuf(const FrameBuf<RawColor> &buf,Pane pane)
 {
  if( +pane )
    {
     raw=buf.place(pane.getBase());
     dx=pane.dx;
     dy=pane.dy;
     dline=buf.dline;
    }
 }

template <RawColorType RawColor>
RawColor FrameBuf<RawColor>::pixel_unsafe(Point p) const
 {
  RawColor ret;

  ret.copyFrom(place(p));

  return ret;
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::pixel_unsafe(Point p,RawColor color)
 {
  color.copyTo(place(p));
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::block_unsafe(Pane pane,RawColor color)
 {
  if( !pane ) return;

  Raw *ptr=place(pane.getBase());

  for(; pane.dy>1 ;pane.dy--,ptr=nextY(ptr))
    {
     HLine(ptr,pane.dx,color);
    }

  HLine(ptr,pane.dx,color);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::block_unsafe(Pane pane,BlenderType blender)
 {
  if( !pane ) return;

  Raw *ptr=place(pane.getBase());

  for(; pane.dy>1 ;pane.dy--,ptr=nextY(ptr))
    {
     HLine(ptr,pane.dx,blender);
    }

  HLine(ptr,pane.dx,blender);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::block_unsafe(Pane pane,VColor vc,Clr alpha)
 {
  if( !pane ) return;

  Blender blender(alpha,vc);

  Raw *ptr=place(pane.getBase());

  for(; pane.dy>1 ;pane.dy--,ptr=nextY(ptr))
    {
     HLine(ptr,pane.dx,blender);
    }

  HLine(ptr,pane.dx,blender);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::save_unsafe(Pane pane,RawColor buf[])
 {
  if( !pane ) return;

  Raw *ptr=place(pane.getBase());

  for(; pane.dy>1 ;pane.dy--,ptr=nextY(ptr),buf+=pane.dx)
    {
     Save(ptr,pane.dx,buf);
    }

  Save(ptr,pane.dx,buf);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::load_unsafe(Pane pane,const RawColor buf[])
 {
  if( !pane ) return;

  Raw *ptr=place(pane.getBase());

  for(; pane.dy>1 ;pane.dy--,ptr=nextY(ptr),buf+=pane.dx)
    {
     Load(ptr,pane.dx,buf);
    }

  Load(ptr,pane.dx,buf);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_unsafe(Point p,BoolGlyphType gly,RawColor back,RawColor fore)
 {
  Coord bdy=gly.dY();

  if( bdy<=0 ) return;

  Raw *ptr=place(p);
  Coord by=0;

  for(; by<bdy-1 ;by++,ptr=nextY(ptr))
    {
     HLine(ptr,gly[by],back,fore);
    }

  HLine(ptr,gly[by],back,fore);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_unsafe(Point p,BoolGlyphType gly,RawColor fore)
 {
  Coord bdy=gly.dY();

  if( bdy<=0 ) return;

  Raw *ptr=place(p);
  Coord by=0;

  for(; by<bdy-1 ;by++,ptr=nextY(ptr))
    {
     HLine(ptr,gly[by],fore);
    }

  HLine(ptr,gly[by],fore);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_unsafe(Point p,MonoGlyph gly,RawColor color)
 {
  Coord dy=gly.dY();

  if( dy<=0 ) return;

  Raw *ptr=place(p);
  Clr *base=gly.getBase();

  for(dy--; dy>0 ;dy--,ptr=nextY(ptr),base=gly.nextY(base))
    {
     HLine_mono(ptr,base,gly.bitOff(),gly.dX(),color);
    }

  HLine_mono(ptr,base,gly.bitOff(),gly.dX(),color);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_unsafe(Point p,GrayGlyph gly,VColor vc,GammaFunc gamma)
 {
  Coord dy=gly.dY();

  if( dy<=0 ) return;

  Raw *ptr=place(p);
  Clr *base=gly.getBase();

  for(dy--; dy>0 ;dy--,ptr=nextY(ptr),base=gly.nextY(base))
    {
     HLine(ptr,base,gly.dX(),vc,gamma);
    }

  HLine(ptr,base,gly.dX(),vc,gamma);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_rgb_unsafe(Point p,RGBGlyph gly,VColor vc,GammaFunc gamma)
 {
  Coord dy=gly.dY();

  if( dy<=0 ) return;

  Raw *ptr=place(p);
  Clr *base=gly.getBase();

  for(dy--; dy>0 ;dy--,ptr=nextY(ptr),base=gly.nextY(base))
    {
     HLine_rgb(ptr,base,gly.dX(),vc,gamma);
    }

  HLine_rgb(ptr,base,gly.dX(),vc,gamma);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_bgr_unsafe(Point p,RGBGlyph gly,VColor vc,GammaFunc gamma)
 {
  Coord dy=gly.dY();

  if( dy<=0 ) return;

  Raw *ptr=place(p);
  Clr *base=gly.getBase();

  for(dy--; dy>0 ;dy--,ptr=nextY(ptr),base=gly.nextY(base))
    {
     HLine_bgr(ptr,base,gly.dX(),vc,gamma);
    }

  HLine_bgr(ptr,base,gly.dX(),vc,gamma);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::test()
 {
  if( dx<=0 || dy<=0 ) return;

  {
   Coord x1=(1*dx)/4;
   Coord x2=(2*dx)/4;
   Coord x3=(3*dx)/4;

   block_unsafe(Pane(0,0,x1,dy),Black);
   block_unsafe(Pane(x1,0,x2-x1,dy),Gray);
   block_unsafe(Pane(x2,0,x3-x2,dy),Silver);
   block_unsafe(Pane(x3,0,dx-x3,dy),White);
  }

  {
   block_unsafe(Pane(0,0,1,dy),Red);
   block_unsafe(Pane(dx-1,0,1,dy),Red);
   block_unsafe(Pane(0,0,dx,1),Red);
   block_unsafe(Pane(0,dy-1,dx,1),Red);
  }

  {
   Coord bdy=(Min(dx,dy)*10)/36;
   Coord bdx=bdy;

   Coord gap=bdy/10;

   Coord x1=(dx-3*bdx-2*gap)/2;
   Coord x2=x1+bdx+gap;
   Coord x3=x2+bdx+gap;

   Coord y1=(dy-3*bdy-2*gap)/2;
   Coord y2=y1+bdy+gap;
   Coord y3=y2+bdy+gap;

   block_unsafe(Pane(x1,y1,bdx,bdy),Red);
   block_unsafe(Pane(x2,y1,bdx,bdy),Green);
   block_unsafe(Pane(x3,y1,bdx,bdy),Blue);

   block_unsafe(Pane(x1,y2,bdx,bdy),Cyan);
   block_unsafe(Pane(x2,y2,bdx,bdy),Fuchsia);
   block_unsafe(Pane(x3,y2,bdx,bdy),Yellow);

   block_unsafe(Pane(x1,y3,bdx,bdy),Teal);
   block_unsafe(Pane(x2,y3,bdx,bdy),Purple);
   block_unsafe(Pane(x3,y3,bdx,bdy),Olive);
  }
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::erase(RawColor color)
 {
  block_unsafe(getPane(),color);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::erase(VColor vc,Clr alpha)
 {
  block_unsafe(getPane(),vc,alpha);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::pixel_safe(Point p,RawColor color)
 {
  if( p>=Null && p<getSize() ) pixel_unsafe(p,color);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::block_safe(Pane pane,RawColor color)
 {
  block_unsafe(Inf(pane,getPane()),color);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::block_safe(Pane pane,BlenderType blender)
 {
  block_unsafe(Inf(pane,getPane()),blender);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::block_safe(Pane pane,VColor vc,Clr alpha)
 {
  block_unsafe(Inf(pane,getPane()),vc,alpha);
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_safe(Point p,BoolGlyphType gly,RawColor fore)
 {
  if( !*this ) return;

  CutExtension y(dy,gly.dY(),p.y);

  if( !y ) return;

  CutExtension x(dx,gly.dX(),p.x);

  if( !x ) return;

  Coord gy=y.ind;
  Coord lim=y.lim;

  Raw *ptr=place(Point(x.pos,y.pos));

  HLine(ptr,gly[gy],x.ind,x.lim,fore);

  while( ++gy<lim )
    {
     ptr=nextY(ptr);

     HLine(ptr,gly[gy],x.ind,x.lim,fore);
    }
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_safe(Point p,MonoGlyph gly,RawColor color)
 {
  Pane pane=Inf(getPane(),gly.getPane(p));

  if( +pane )
    {
     glyph_unsafe(pane.getBase(),gly.cut(pane-p),color);
    }
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_safe(Point p,GrayGlyph gly,VColor vc,GammaFunc gamma)
 {
  Pane pane=Inf(getPane(),gly.getPane(p));

  if( +pane )
    {
     glyph_unsafe(pane.getBase(),gly.cut(pane-p),vc,gamma);
    }
 }

template <RawColorType RawColor>
void FrameBuf<RawColor>::glyph_safe(Point p,RGBGlyph gly,VColor vc,GammaFunc gamma,bool bgr)
 {
  Pane pane=Inf(getPane(),gly.getPane(p));

  if( +pane )
    {
     if( bgr )
       glyph_bgr_unsafe(pane.getBase(),gly.cut(pane-p),vc,gamma);
     else
       glyph_rgb_unsafe(pane.getBase(),gly.cut(pane-p),vc,gamma);
    }
 }

} // namespace Video
} // namespace CCore

#endif


