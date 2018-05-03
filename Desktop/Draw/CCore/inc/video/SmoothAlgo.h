/* SmoothAlgo.h */
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

#ifndef CCore_inc_video_SmoothAlgo_h
#define CCore_inc_video_SmoothAlgo_h

#include <CCore/inc/video/DrawTools.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/TaskMemStack.h>
#include <CCore/inc/FunctorType.h>

#include <CCore/inc/algon/BaseRangeAlgo.h>
#include <CCore/inc/algon/SortUnique.h>

namespace CCore {
namespace Video {
namespace Smooth {

/* concept MPointRangeType<R> */

template <Algon::RangeType R>
concept bool MPointRangeType = requires(R &obj,ulen ind)
 {
  { *obj } -> MPoint ;

  obj+=ind;

  { obj[ind] } -> MPoint ;
 } ;

/* concept MPointMapType<Map,R> */

template <class Map,Algon::RangeType R>
concept bool MPointMapType = requires(R &obj,Map &map,ulen ind)
 {
  { map(*obj) } -> MPoint ;

  obj+=ind;

  { map(obj[ind]) } -> MPoint ;
 } ;

/* concept PlotType<Plot> */

template <NothrowCopyCtorType Plot>
concept bool PlotType = requires(Plot &obj,MPoint p,unsigned alpha)
 {
  obj(p);

  obj(p,alpha);
 } ;

/* consts */

inline constexpr unsigned MaxCapFineness = 1 ;

inline constexpr unsigned MaxFineness = 2 ;

inline constexpr unsigned AlphaBits = 8 ;

/* functions */

inline MPoint Rotate90(MPoint point) { return MPoint(-point.y,point.x); } // clockwise

/* classes */

template <SIntType SInt> struct Rational;

class Rotate;

class ArcDriver;

struct LineRound;

struct LineArc;

struct SolidBox;

template <PlotType Plot> class SolidRow;

class SolidDriver;

/* struct Rational<SInt> */

template <SIntType SInt>
struct Rational
 {
  MCoord a;
  SInt b;

  Rational(MCoord a_,SInt b_) : a(a_),b(b_) { IntGuard( b!=0 ); }

  MCoord mul(MCoord x) const { return MCoord( (DCoord(a)*x)/b ); }

  MCoord operator * (MCoord x) const { return mul(x); }

  MPoint operator * (MPoint a) const { return MPoint(mul(a.x),mul(a.y)); }
 };

/* class Rotate */

class Rotate
 {
   MCoord a;
   MCoord b;
   DCoord c;

  public:

   explicit Rotate(MPoint A) // (1,0) -> A/Length(A)
    {
     a=A.x;
     b=A.y;
     c=Length(a,b);

     IntGuard( c!=0 );
    }

   MPoint mul(MCoord x,MCoord y) const
    {
     return MPoint(MCoord(Prod(a,-b,x,y)/c),MCoord(Prod(b,a,x,y)/c));
    }

   MPoint operator () (MCoord x,MCoord y) const { return mul(x,y); }

   MPoint operator () (MPoint point) const { return mul(point.x,point.y); }
 };

/* class ArcDriver */

class ArcDriver : NoCopy
 {
   static constexpr unsigned MaxLevel = 10 ;

   static constexpr unsigned Len = Pow2(MaxLevel) ;

  private:

   MPoint buf[Len+1];
   unsigned level = 0 ;

  public:

   ArcDriver() {}

   void arc(MPoint a,MPoint b,MPoint c,MCoord radius,unsigned fineness); // c center, a,b ends , angle < 180

   PtrStepLen<const MPoint> getArc() const { return {buf,Pow2(MaxLevel-level),Pow2(level)+1}; }
 };

/* struct LineRound */

struct LineRound
 {
  MPoint buf[12];

  LineRound(MPoint a,MCoord radius); // clockwise

  PtrLen<const MPoint> get() const { return Range(buf); }
 };

/* struct LineArc */

struct LineArc
 {
  MPoint p;
  MPoint q;
  MPoint r;

  enum ArcType
   {
    OnePoint,
    TwoPoint,
    Arc
   };

  ArcType type;

  // internal

  static DCoord Sigma(MPoint a,MPoint b);

  static DCoord Sigma(MPoint a,MPoint b,MPoint c);

  static MPoint Bisect(MPoint a,MPoint b,MCoord radius);

  static unsigned SBits(DCoord a);

  static MPoint Sect(DCoord A,DCoord B,MPoint p);

  void intersect(MPoint a,MPoint b,MPoint c,MPoint d,MPoint base);

  // constructor

  LineArc(MPoint a,MPoint b,MPoint c,MCoord radius);
 };

/* PutWithoutFirst() */

void PutWithoutFirst(CursorOverType<MPoint> r,FuncArgType<MPoint> &func)
 {
  for(++r; +r ;++r) func(*r);
 }

/* AddLineRound() */

template <FuncInitArgType<MPoint> FuncInit>
void AddLineRound(MPoint a,MCoord radius,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  MPoint p=a+MPoint(0,radius);
  MPoint q=a+MPoint(-radius,0);
  MPoint r=a+MPoint(0,-radius);
  MPoint s=a+MPoint(radius,0);

  StackObject<ArcDriver> driver;

  driver->arc(p,q,a,radius,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);

  driver->arc(q,r,a,radius,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);

  driver->arc(r,s,a,radius,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);

  driver->arc(s,p,a,radius,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);
 }

/* AddLineCap() */

template <FuncInitArgType<MPoint> FuncInit>
void AddLineCap(MPoint a,MPoint b,MCoord radius,FuncInit func_init) // a != b
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Rotate rotate(b-a);

  MPoint d=rotate(0,radius);

  MPoint p=a+d;
  MPoint q=a+Rotate90(d);
  MPoint r=a-d;

  func(p);

  StackObject<ArcDriver> driver;

  driver->arc(p,q,a,radius,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);

  driver->arc(q,r,a,radius,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);
 }

/* AddLineInCap() */

template <FuncInitArgType<MPoint> FuncInit>
void AddLineInCap(MPoint a,MPoint b,MCoord radius,FuncInit func_init) // a != b
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Rotate rotate(b-a);

  MPoint d=rotate(0,radius);
  MPoint d2=d/2;

  MPoint p=a+d;
  MPoint c=a+d2;
  MPoint q=c+Rotate90(d2);
  MPoint r=a;

  func(p);

  StackObject<ArcDriver> driver;

  driver->arc(p,q,c,radius/2,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);

  driver->arc(q,r,c,radius/2,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);
 }

/* AddLineOutCap() */

template <FuncInitArgType<MPoint> FuncInit>
void AddLineOutCap(MPoint a,MPoint b,MCoord radius,FuncInit func_init) // a != b
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Rotate rotate(b-a);

  MPoint d=rotate(0,-radius);
  MPoint d2=d/2;

  MPoint p=a;
  MPoint c=a+d2;
  MPoint q=c-Rotate90(d2);
  MPoint r=a+d;

  func(p);

  StackObject<ArcDriver> driver;

  driver->arc(p,q,c,radius/2,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);

  driver->arc(q,r,c,radius/2,MaxCapFineness);

  PutWithoutFirst(driver->getArc(),func);
 }

/* AddLineArc() */

template <FuncInitArgType<MPoint> FuncInit>
void AddLineArc(MPoint a,MPoint b,MPoint c,MCoord radius,FuncInit func_init) // a != b , b != c
 {
  FunctorTypeOf<FuncInit> func(func_init);

  LineArc obj(a,b,c,radius);

  switch( obj.type )
    {
     case LineArc::OnePoint :
      {
       func(obj.p);
      }
     break;

     case LineArc::TwoPoint :
      {
       func(obj.p);
       func(obj.q);
      }
     break;

     case LineArc::Arc :
      {
       func(obj.p);

       StackObject<ArcDriver> driver;

       driver->arc(obj.p,obj.q,b,radius,MaxCapFineness);

       PutWithoutFirst(driver->getArc(),func);

       driver->arc(obj.q,obj.r,b,radius,MaxCapFineness);

       PutWithoutFirst(driver->getArc(),func);
      }
     break;
    }
 }

/* Intersect() */

inline uMCoord uIntersect(uMCoord x,uMCoord y,uMCoord Y)
 {
  uDCoord p=uDCoord(x)*y;
  uMCoord q=uMCoord( p/Y );
  uMCoord r=uMCoord( p%Y );

  return (r>Y/2)?q+1:q;
 }

inline MCoord Intersect(MCoord a,MCoord b,uMCoord y,uMCoord Y)
 {
  if( y<=0 ) return a;

  if( y>=Y ) return b;

  if( a<b )
    {
     return IntMovePos(a,uIntersect(IntDist(a,b),y,Y));
    }
  else
    {
     return IntMoveNeg(a,uIntersect(IntDist(b,a),y,Y));
    }
 }

inline MCoord Intersect(MPoint a,MPoint b,MCoord y)
 {
  return Intersect(a.x,b.x,IntDist(a.y,y),IntDist(a.y,b.y));
 }

/* struct SolidBox */

struct SolidBox
 {
  MPoint base; // whole
  MCoord dx;   // in whole pixels
  MCoord dy;   // in whole pixels

  static MCoord Len(MCoord len) { return IntRShift(len,MPoint::Precision)+1; }

  template <class R>
  SolidBox(R dots,MPointMapType<R> map)
   {
    if( +dots )
      {
       MPoint a=map(*dots);
       MPoint b=a;

       for(++dots; +dots ;++dots)
         {
          MPoint c=map(*dots);

          a=Inf(a,c);
          b=Sup(b,c);
         }

       base=a.round();

       MPoint p=b.round()-base;

       dx=Len(p.x);
       dy=Len(p.y);
      }
    else
      {
       dx=0;
       dy=0;
      }
   }
 };

/* class SolidRow<Plot> */

template <PlotType Plot>
class SolidRow : NoCopy
 {
   using Area = uint32 ;

   static constexpr Area FullArea = Area(1)<<(2*MPoint::Precision) ;

   static unsigned ToAlpha(Area s)
    {
     const unsigned Bits=2*MPoint::Precision-AlphaBits;
     const Area Half = Area(1)<<(Bits-1) ;

     return (s+Half)>>Bits;
    }

   static Area PixelArea(MCoord c,MCoord e)
    {
     if( c>=MPoint::Half ) return 0;

     if( e<=-MPoint::Half ) return FullArea;

     if( c>=-MPoint::Half )
       {
        if( e>MPoint::Half )
          {
           Area E=Area(e-MPoint::Half);
           Area C=Area(MPoint::Half-c);

           return (C*((C<<MPoint::Precision)/(C+E)))/2;
          }
        else
          {
           Area H=Area(MPoint::Half-(e+c)/2);

           return H<<MPoint::Precision;
          }
       }
     else
       {
        if( e>MPoint::Half )
          {
           Area C=Area(-c);
           Area E=Area(e);
           Area H=(C<<MPoint::Precision)/(C+E);

           return H<<MPoint::Precision;
          }
        else
          {
           Area E=Area(e+MPoint::Half);
           Area C=Area(-MPoint::Half-c);

           return FullArea-(E*((E<<MPoint::Precision)/(C+E)))/2;
          }
       }
    }

   static Area PixelArea(MCoord c,MCoord e,MCoord d,MCoord f,MCoord x)
    {
     return PosSub(FullArea,PixelArea(x-e,x-c),PixelArea(d-x,f-x));
    }

   static Area PixelArea(MCoord H,MCoord c,MCoord e,MCoord d,MCoord f,MCoord x)
    {
     return (PixelArea(c,e,d,f,x)*Area(H))>>MPoint::Precision;
    }

   class Part : NoCopy
    {
      MPoint base;
      MCoord a = 0 ;
      MCoord b = 0 ;

      StackArray<Area> line;
      ulen off = 0 ;
      ulen lim = 0 ;

     private:

      void add(ulen ind,Area s)
       {
        if( ind>=line.getLen() ) return;

        if( off<lim )
          {
           while( ind<off ) line[--off]=0;

           while( ind>=lim ) line[lim++]=0;

           line[ind]+=s;
          }
        else
          {
           off=ind;
           lim=ind+1;

           line[ind]=s;
          }
       }

      void pixel(MCoord x,Area s)
       {
        if( x<base.x ) return;

        ulen ind=(ulen)IntRShift(x-base.x,MPoint::Precision);

        add(ind,s);
       }

     public:

      explicit Part(SolidBox box) : base(box.base),line(box.dx) {}

      void start(MCoord y)
       {
        base.y=y;
        a=y-MPoint::Half;
        b=y+MPoint::Half;

        off=0;
        lim=0;
       }

      void next(MCoord bottom,MCoord top,MCoord bottom_start,MCoord bottom_end,MCoord top_start,MCoord top_end)
       {
        if( bottom>=b || top<=a ) return;

        MCoord A,c,d;

        if( bottom<a )
          {
           c=Intersect(MPoint(bottom_start,bottom),MPoint(top_start,top),a);
           d=Intersect(MPoint(bottom_end,bottom),MPoint(top_end,top),a);

           A=a;
          }
        else
          {
           c=bottom_start;
           d=bottom_end;

           A=bottom;
          }

        MCoord B,e,f;

        if( top>b )
          {
           e=Intersect(MPoint(bottom_start,bottom),MPoint(top_start,top),b);
           f=Intersect(MPoint(bottom_end,bottom),MPoint(top_end,top),b);

           B=b;
          }
        else
          {
           e=top_start;
           f=top_end;

           B=top;
          }

        if( c>e ) Swap(c,e);
        if( d>f ) Swap(d,f);

        MCoord x=MPoint::Round(c);
        MCoord x1=MPoint::Round(e+MPoint::One-1);

        MCoord x2=MPoint::Round(d);
        MCoord x3=MPoint::Round(f+MPoint::One-1);

        MCoord H=B-A;
        Area S=Area(H)<<MPoint::Precision;

        for(; x<x1 ;x+=MPoint::One) pixel(x,PixelArea(H,c,e,d,f,x));

        for(; x<x2 ;x+=MPoint::One) pixel(x,S);

        for(; x<x3 ;x+=MPoint::One) pixel(x,PixelArea(H,c,e,d,f,x));
       }

      void complete(Plot &plot)
       {
        auto *ptr=line.getPtr()+off;

        MPoint p=base;

        p.x+=MCoord(off)*MPoint::One;

        for(ulen cnt=lim-off; cnt ;cnt--,ptr++,p.x+=MPoint::One) plot(p,ToAlpha(*ptr));
       }
    };

   class Full : NoCopy
    {
      MPoint base;
      MCoord a = 0 ;
      MCoord b = 0 ;

      static constexpr ulen Len = 10 ;

      TempArray<Area,Len> buf;
      ulen count = 0 ;

     private:

      static ulen ExtLen(ulen len)
       {
        if( len<=Len ) return Len;

        return Max<ulen>(len,len+Len+len/2);
       }

      static bool PushLen(ulen delta,ulen count)
       {
        return delta>=Len && delta>=count/3 ;
       }

      void push(MCoord x,PlotType &plot)
       {
        if( count )
          {
           if( x<base.x ) return;

           ulen delta=(ulen)IntRShift(x-base.x,MPoint::Precision);

           if( delta>=count )
             {
              complete(plot);

              return;
             }

           if( PushLen(delta,count) )
             {
              {
               for(Area s : Range(buf.getPtr(),delta) )
                 {
                  plot(base,ToAlpha(s));

                  base.x+=MPoint::One;
                 }
              }

              count-=delta;

              {
               auto *ptr=buf.getPtr();

               for(ulen i=0,len=count; i<len ;i++) ptr[i]=ptr[i+delta];
              }
             }
          }
       }

      void first(MCoord x,Area s)
       {
        base.x=x;

        buf.provide(ExtLen(1));

        buf[count++]=s;
       }

      void add(ulen ind,Area s)
       {
        if( ind<count )
          {
           buf[ind]+=s;
          }
        else
          {
           buf.extend(ExtLen(ind+1));

           while( count<ind ) buf[count++]=0;

           buf[count++]=s;
          }
       }

      void pixel(MCoord x,Area s)
       {
        if( count )
          {
           if( x<base.x ) return;

           ulen ind=(ulen)IntRShift(x-base.x,MPoint::Precision);

           add(ind,s);
          }
        else
          {
           first(x,s);
          }
       }

      void pixel(MCoord x,PlotType &plot)
       {
        plot(MPoint(x,base.y));
       }

     public:

      Full() noexcept {}

      ~Full() {}

      void start(MCoord y)
       {
        base.y=y;
        a=y-MPoint::Half;
        b=y+MPoint::Half;

        count=0;
       }

      void next(MCoord bottom,MCoord top,MCoord bottom_start,MCoord bottom_end,MCoord top_start,MCoord top_end,Plot &plot)
       {
        MCoord c=Intersect(MPoint(bottom_start,bottom),MPoint(top_start,top),a);
        MCoord e=Intersect(MPoint(bottom_start,bottom),MPoint(top_start,top),b);
        MCoord d=Intersect(MPoint(bottom_end,bottom),MPoint(top_end,top),a);
        MCoord f=Intersect(MPoint(bottom_end,bottom),MPoint(top_end,top),b);

        if( c>e ) Swap(c,e);
        if( d>f ) Swap(d,f);

        MCoord x=MPoint::Round(c);
        MCoord x1=MPoint::Round(e+MPoint::One-1);

        MCoord x2=MPoint::Round(d);
        MCoord x3=MPoint::Round(f+MPoint::One-1);

        push(x,plot);

        for(; x<x1 ;x+=MPoint::One) pixel(x,PixelArea(c,e,d,f,x));

        if( x<x2 )
          {
           complete(plot);

           for(; x<x2 ;x+=MPoint::One) pixel(x,plot);
          }

        for(; x<x3 ;x+=MPoint::One) pixel(x,PixelArea(c,e,d,f,x));
       }

      void complete(Plot &plot)
       {
        if( count )
          {
           for(Area s : Range(buf.getPtr(),count) )
             {
              plot(base,ToAlpha(s));

              base.x+=MPoint::One;
             }

           count=0;

           buf.erase();
          }
       }
    };

   Part part1;
   Part part2;

   MCoord bottom = 0 ;
   MCoord top = 0 ;

   Part *bottom_part;
   Part *top_part;
   StackArray<Full> fulls;
   ulen count = 0 ;
   bool top_on = false ;
   bool bottom_on = false ;

   Plot plot;

  private:

   PtrLen<Full> getFulls() { return Range(fulls.getPtr(),count); }

   void startFulls(MCoord y)
    {
     if( count )
       {
        Replace_min(count,fulls.getLen());

        for(Full &f : getFulls() )
          {
           f.start(y);

           y+=MPoint::One;
          }
       }
    }

  public:

   SolidRow(SolidBox box,const PlotType &plot_)
    : part1(box),
      part2(box),
      fulls(box.dy),
      plot(plot_)
    {
     bottom_part=&part1;
     top_part=&part2;
    }

   void start(MCoord bottom_,MCoord top_)
    {
     bottom=bottom_;
     top=top_;

     MCoord a=MPoint::Round(bottom_);
     MCoord b=MPoint::Round(top_);

     if( bottom_==a-MPoint::Half )
       {
        bottom_on=false;

        count=IntRShift(b-a,MPoint::Precision);

        if( top_==b-MPoint::Half )
          {
           top_on=false;
          }
        else
          {
           top_on=true;

           top_part->start(b);
          }

        startFulls(a);
       }
     else
       {
        if( top_==b-MPoint::Half )
          {
           count=IntRShift(b-a,MPoint::Precision)-1;

           bottom_on=true;

           if( top_on )
             {
              Swap(top_part,bottom_part);
             }
           else
             {
              bottom_part->start(a);
             }

           top_on=false;
          }
        else
          {
           if( a==b )
             {
              if( !top_on )
                {
                 top_on=true;

                 top_part->start(b);
                }

              count=0;

              bottom_on=false;
             }
           else
             {
              if( top_on )
                {
                 Swap(top_part,bottom_part);
                }
              else
                {
                 top_on=true;

                 bottom_part->start(a);
                }

              top_part->start(b);

              bottom_on=true;

              count=IntRShift(b-a,MPoint::Precision)-1;
             }
          }

        startFulls(a+MPoint::One);
       }
    }

   void next(MCoord bottom_start,MCoord bottom_end,MCoord top_start,MCoord top_end)
    {
     if( top_on ) top_part->next(bottom,top,bottom_start,bottom_end,top_start,top_end);

     if( bottom_on ) bottom_part->next(bottom,top,bottom_start,bottom_end,top_start,top_end);

     for(Full &f : getFulls() ) f.next(bottom,top,bottom_start,bottom_end,top_start,top_end,plot);
    }

   void end()
    {
     if( bottom_on ) bottom_part->complete(plot);

     for(Full &f : getFulls() ) f.complete(plot);
    }

   void complete()
    {
     if( top_on ) top_part->complete(plot);
    }
 };

/* class SolidDriver */

class SolidDriver : NoCopy
 {
   struct Dot
    {
     MPoint point;
     ulen sect = 0 ;

     Dot() noexcept {}
    };

   struct Sect
    {
     MCoord y = 0 ;
     ulen dot = 0 ;

     Sect() noexcept {}

     void set(MCoord y_,ulen dot_) { y=y_; dot=dot_; }

     bool operator < (Sect obj) const { return y<obj.y; }

     bool operator != (Sect obj) const { return y!=obj.y; }
    };

   using IndexType = int ;

   struct Line : CmpComparable<Line>
    {
     MPoint a;
     MPoint b;
     IndexType delta_index = 0 ;
     ulen bottom = 0 ;
     ulen top = 0 ;

     MCoord x_bottom = 0 ;
     MCoord x_cur = 0 ;
     MCoord x_top = 0 ;

     Line() noexcept {}

     Line(Dot a_,Dot b_)
      {
       if( a_.sect<b_.sect )
         {
          delta_index=-1;
          bottom=a_.sect;
          top=b_.sect;

          a=a_.point;
          b=b_.point;
          x_bottom=a.x;
         }
       else if( a_.sect>b_.sect )
         {
          delta_index=+1;
          bottom=b_.sect;
          top=a_.sect;

          a=b_.point;
          b=a_.point;
          x_bottom=a.x;
         }
       else
         {
          delta_index=0;
          bottom=b_.sect;
          top=a_.sect;
         }
      }

     static uMCoord Cross(uMCoord y,uMCoord db,uMCoord dt)
      {
       return uMCoord( (uDCoord(y)*db)/(uDCoord(db)+dt) + 1 );
      }

     void setCur(MCoord y) { x_cur=Intersect(a,b,y); }

     void setCurTop() { x_cur=x_top; }

     void setTop(MCoord y) { x_top=Intersect(a,b,y); }

     void copyX() { x_bottom=x_cur; }

     bool cross(const Line *obj) const { return x_bottom<obj->x_bottom && x_top>obj->x_top ; }

     MCoord crossY(const Line *obj,MCoord bottom,MCoord top) const
      {
       MCoord xa=x_bottom;
       MCoord xb=obj->x_bottom;

       uMCoord dt=IntDist(obj->x_top,x_top);

       for(;;)
         {
          MCoord y=IntMovePos(bottom,Cross(IntDist(bottom,top),IntDist(xa,xb),dt));

          if( y==top ) return y;

          xa=Intersect(a,b,y);
          xb=Intersect(obj->a,obj->b,y);

          if( xa>=xb ) return y;

          bottom=y;
         }
      }

     // cmp objects

     CmpResult objCmp(const Line &obj) const { return AlphaCmp(x_bottom,obj.x_bottom,x_top,obj.x_top); }
    };

   ulen dot_count;

   StackArray<Dot> path;
   StackArray<Sect> sect;
   StackArray<Line> line_buf;
   StackArray<Line *> lines;

   ulen sect_count = 0 ;

   SolidBox box;

  private:

   void substep(MCoord bottom,MCoord top,PtrLen<Line *> set,SolidFlag solid_flag,AnyType &row)
    {
     row.start(bottom,top);

     if( solid_flag==SolidAll )
       {
        Line *start=0;
        IndexType index=0;

        for(Line *line : set )
          {
           if( index==0 ) start=line;

           index+=line->delta_index;

           if( index==0 ) row.next(start->x_bottom,line->x_bottom,start->x_cur,line->x_cur);
          }
       }
     else
       {
        Line *start=0;
        bool odd=false;

        for(Line *line : set )
          {
           if( !odd ) start=line;

           odd=!odd;

           if( !odd ) row.next(start->x_bottom,line->x_bottom,start->x_cur,line->x_cur);
          }
       }

     row.end();

     for(Line *line : set ) line->copyX();
    }

   void step(MCoord bottom,MCoord top,PtrLen<Line *> set,SolidFlag solid_flag,AnyType &row)
    {
     for(Line *line : set ) line->setTop(top);

     for(;;)
       {
        IncrSort(set, [] (const Line *a,const Line *b) { return *a < *b ; } );

        MCoord best_y=top;

        for(ulen i=0; i+1<set.len ;i++)
          {
           if( set[i]->cross(set[i+1]) )
             {
              MCoord y=set[i]->crossY(set[i+1],bottom,top);

              Replace_min(best_y,y);
             }
          }

        if( best_y==top )
          {
           for(Line *line : set ) line->setCurTop();

           substep(bottom,top,set,solid_flag,row);

           return;
          }

        for(Line *line : set ) line->setCur(best_y);

        substep(bottom,best_y,set,solid_flag,row);

        bottom=best_y;
       }
    }

  public:

   template <class R>
   SolidDriver(R dots,MPointMapType<R> map)
    : dot_count( Algon::BaseRangeAlgo<R>::GetLen(dots) ),
      path(dot_count),
      sect(dot_count),
      line_buf(dot_count),
      lines(dot_count),
      box(dots,map)
    {
     if( !dot_count ) return;

     for(ulen i=0; i<dot_count ;i++)
       {
        MPoint d=map(dots[i]);

        path[i].point=d;
        sect[i].set(d.y,i);
       }

     Algon::SortThenApplyUniqueRange(Range(sect), [&] (PtrLen<Sect> r)
                                                      {
                                                       ulen i=sect_count++;

                                                       for(Sect s : r ) path[s.dot].sect=i;

                                                       sect[i]=r[0];

                                                      } );

     ulen i=0;

     for(; i<dot_count-1 ;i++) line_buf[i]=Line(path[i],path[i+1]);

     line_buf[i]=Line(path[i],path[0]);

     for(ulen i=0; i<dot_count ;i++) lines[i]=&(line_buf[i]);

     IncrSort(Range(lines), [] (const Line *a,const Line *b) { return a->bottom<b->bottom; } );
    }

   explicit SolidDriver(MPointRangeType dots) : SolidDriver(dots, [] (MPoint point) { return point; } ) {}

   ~SolidDriver() {}

   template <PlotType Plot>
   void operator () (SolidFlag solid_flag,const Plot &plot)
    {
     if( !dot_count ) return;

     SolidRow<Plot> row(box,plot);

     ulen off=0;
     ulen lim=0;

     MCoord bottom=sect[0].y;

     for(ulen s=1; s<sect_count ;s++)
       {
        MCoord top=sect[s].y;

        for(; lim<lines.getLen() && lines[lim]->bottom<s ;lim++);

        ulen ind=lim;

        while( ind>off )
          {
           if( lines[--ind]->top<s )
             {
              ulen i=ind;

              while( i>off )
                {
                 if( lines[--i]->top>=s )
                   {
                    lines[ind--]=lines[i];
                   }
                }

              ind++;

              break;
             }
          }

        off=ind;

        // [off,lim) : bottom < s && top >= s

        step(bottom,top,Range(lines).part(off,lim-off),solid_flag,row);

        bottom=top;
       }

     row.complete();
    }
 };

} // namespace Smooth
} // namespace Video
} // namespace CCore

#endif


