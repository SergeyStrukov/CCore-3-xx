/* SmoothDrawArt.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
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

#ifndef CCore_inc_video_SmoothDrawArt_h
#define CCore_inc_video_SmoothDrawArt_h

#include <CCore/inc/video/DrawBuf.h>
#include <CCore/inc/video/ColorField.h>

#include <CCore/inc/video/CurveDriver.h>
#include <CCore/inc/video/SmoothAlgo.h>

namespace CCore {
namespace Video {
namespace Smooth {

/* PrefixPlus() */

template <Algon::RangeType R>
R PrefixPlus(R r,R suffix)
 {
  using Algo=Algon::BaseRangeAlgo<R>;

  auto len=Algo::GetLen(r)-Algo::GetLen(suffix)+1;

  return Algo::GetPrefix(r,len);
 }

/* classes */

//enum DotType;

struct Dot;

struct BreakDot;

/* enum DotType */

enum DotType
 {
  DotBreak,

  DotSimple
 };

const char * GetTextDesc(DotType type);

/* struct Dot */

struct Dot
 {
  MPoint point;
  DotType type = DotSimple ;

  Dot() noexcept {}

  Dot(const MPoint &point_) : point(point_) {}

  Dot(MCoord x,MCoord y) : point(x,y) {}

  Dot(const MPoint &point_,DotType type_) : point(point_),type(type_) {}

  Dot(Dot dot,FuncType<MPoint,MPoint> func) : point(func(dot.point)),type(dot.type) {}

  Dot operator + (MPoint p) const { return Dot(point+p,type); }
 };

/* struct BreakDot */

struct BreakDot : Dot
 {
  BreakDot() noexcept { type=DotBreak; }

  BreakDot(const MPoint &point) : Dot(point,DotBreak) {}

  BreakDot(MCoord x,MCoord y) : BreakDot(MPoint(x,y)) {}
 };

/* concept DotRangeType<R> */

template <Algon::RangeType R>
concept bool DotRangeType = requires(R &obj,ulen ind)
 {
  { *obj } -> Dot ;

  obj+=ind;

  { obj[ind] } -> Dot ;
 } ;

/* concept DotMapType<Map,R> */

template <class Map,Algon::RangeType R>
concept bool DotMapType = requires(R &obj,Map &map,ulen ind)
 {
  { map(*obj) } -> Dot ;

  obj+=ind;

  { map(obj[ind]) } -> Dot ;
 } ;

//----------------------------------------------------------------------------------------

/* classes */

class DotShift;

template <DotRangeType R> class DotBreaker;

class FieldPlotBase;

template <class Field> struct RefOrCopyCtor;

template <ColorFieldType Field> class FieldPlot;

template <class R,MPointMapType<R> Map> class NextLine;

class DotsBase;

class PathDots;

class LoopDots;

class HalfPathDots;

class HalfLoopDots;

class CurveBase;

class CurvePath;

class CurveLoop;

class CurveBreakPath;

class CurveBreakLoop;

class GenDrawArt;

class DrawArt;

/* class DotShift */

class DotShift
 {
   MPoint shift;

  public:

   explicit DotShift(const MPoint &shift_) : shift(shift_) {}

   Dot operator () (Dot dot) const { return dot+shift; }

   MPoint operator () (MPoint point) const { return point+shift; }
 };

/* class DotBreaker<R> */

template <DotRangeType R>
class DotBreaker
 {
   R dots;

  public:

   explicit DotBreaker(const R &dots_) : dots(dots_) {}

   R next()
    {
     R r=dots;

     if( !r ) return r;

     for(++r; +r ;++r)
       if( r->type==DotBreak )
         {
          R ret=PrefixPlus(dots,r);

          dots=r;

          return ret;
         }

     return Replace_null(dots);
    }
 };

/* class FieldPlotBase */

class FieldPlotBase : public DrawBuf
 {
  public:

   explicit FieldPlotBase(const DrawBuf &buf) : DrawBuf(buf) {}

   // VColor

   void plot(Point p,VColor vc)
    {
     buf.pixel_unsafe(p,vc);
    }

   void plot(Point p,VColor vc,unsigned alpha)
    {
     DesktopColor::BlendTo(Blender(Clr(alpha),vc),buf.place(p));
    }

   // AlphaColor

   void plot_cap(Point p,VColor vc,unsigned alpha)
    {
     if( alpha>=AlphaLim )
       plot(p,vc);
     else if( alpha )
       plot(p,vc,alpha);
    }

   void plot(Point p,AlphaColor ac)
    {
     plot_cap(p,ac.vc,ac.alpha);
    }

   void plot(Point p,AlphaColor ac,unsigned alpha)
    {
     plot_cap(p,ac.vc,(Min(ac.alpha,AlphaLim)*alpha)>>ClrBits);
    }
 };

/* struct RefOrCopyCtor<Field> */

template <class Field>
struct RefOrCopyCtor
 {
  using Ret = const Field & ;
 };

template <CopyCtorType Field>
struct RefOrCopyCtor<Field>
 {
  using Ret = Field ;
 };

/* type RefOrCopy<Field> */

template <class Field>
using RefOrCopy = typename RefOrCopyCtor<Field>::Ret ;

/* class FieldPlot<Field> */

template <ColorFieldType Field>
class FieldPlot : FieldPlotBase
 {
   RefOrCopy<Field> field;
   MPoint size;

  private:

   static Coord Shift(MCoord a) { return Coord( IntRShift(a,MPoint::Precision) ); }

   static Point ToPoint(MPoint p) { return Point(Shift(p.x),Shift(p.y)); }

  public:

   FieldPlot(const DrawBuf &buf_,const Field &field_) : FieldPlotBase(buf_),field(field_) { size=buf.getSize(); }

   void operator () (MPoint point)
    {
     MPoint biased=map(point).addXY(MPoint::Half);

     if( biased>=Null && biased<size )
       {
        plot(ToPoint(biased),field(point));
       }
    }

   void operator () (MPoint point,unsigned alpha)
    {
     if( !alpha ) return;

     if( alpha>=AlphaLim )
       {
        (*this)(point);
       }
     else
       {
        MPoint biased=map(point).addXY(MPoint::Half);

        if( biased>=Null && biased<size )
          {
           plot(ToPoint(biased),field(point),alpha);
          }
       }
    }
 };

/* class NextLine<R,Map> */

template <class R,MPointMapType<R> Map>
class NextLine
 {
   R dots;
   Map map;

  public:

   MPoint a;
   MPoint b;
   MPoint c;

   NextLine(const R &dots_,const Map &map_) : dots(dots_),map(map_) {}

   bool first() // sets b -> c , b != c
    {
     if( !dots ) return false;

     b=map(*dots);

     ++dots;

     while( +dots )
       {
        auto d=map(*dots);

        ++dots;

        if( d!=b )
          {
           c=d;

           return true;
          }
       }

     return false;
    }

   bool next() // sets b -> c , b != c , a <- b , a != b
    {
     while( +dots )
       {
        auto d=map(*dots);

        ++dots;

        if( d!=c )
          {
           a=b;
           b=c;
           c=d;

           return true;
          }
       }

     return false;
    }

   bool next(MPoint d)
    {
     if( d!=c )
       {
        a=b;
        b=c;
        c=d;

        return true;
       }

     return false;
    }
 };

/* class DotsBase */

class DotsBase : NoCopy
 {
   Collector<MPoint> buf;

  protected:

   struct AddBuf
    {
     Collector<MPoint> &buf;

     void operator () (MPoint point) { buf.append_copy(point); }
    };

   AddBuf getAdd() { return {buf}; }

   void addPoint(MPoint point) { buf.append_copy(point); }

   void addWithoutFirst(CursorOverType<MPoint> r)
    {
     for(++r; +r ;++r) addPoint(*r);
    }

   // path/loop elements

   void addRound(MPoint a,MCoord width)
    {
     AddLineRound(a,width,getAdd());
    }

   void addCap(MPoint a,MPoint b,MCoord width)
    {
     AddLineCap(a,b,width,getAdd());
    }

   void addArc(MPoint a,MPoint b,MPoint c,MCoord width)
    {
     AddLineArc(a,b,c,width,getAdd());
    }

   void addInCap(MPoint a,MPoint b,MCoord width)
    {
     AddLineInCap(a,b,width,getAdd());
    }

   void addOutCap(MPoint a,MPoint b,MCoord width)
    {
     AddLineOutCap(a,b,width,getAdd());
    }

  public:

   DotsBase() {}

   ~DotsBase() {}

   PtrLen<const MPoint> complete() { return Range_const(buf.flat()); }
 };

/* class PathDots */

class PathDots : public DotsBase
 {
   template <class R,MPointMapType<R> Map>
   bool addDirect(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);

     if( line.first() )
       {
        addCap(line.b,line.c,width);

        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }

        return true;
       }
     else
       {
        addRound(line.b,width);

        return false;
       }
    }

   template <class R,MPointMapType<R> Map>
   void addBack(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);

     if( line.first() )
       {
        addCap(line.b,line.c,width);

        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }
       }
    }

  public:

   template <class R>
   PathDots(R dots,MPointMapType<R> map,MCoord width)
    {
     if( !dots ) return;

     width/=2;

     if( addDirect(dots,map,width) )
       {
        addBack(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width);
       }
    }

   PathDots(MPointRangeType dots,MCoord width) : PathDots(dots, [] (MPoint point) { return point; } ,width) {}

   ~PathDots() {}
 };

/* class LoopDots */

class LoopDots : public DotsBase
 {
   template <class R,MPointMapType<R> Map>
   bool addDirect(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);

     if( line.first() )
       {
        MPoint o=line.b;

        addCap(line.b,line.c,width);

        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }

        if( line.next(o) )
          {
           addArc(line.a,line.b,line.c,width);

           addCap(line.c,line.b,width);

           addArc(line.c,line.b,line.a,width);
          }
        else
          {
           addCap(line.c,line.b,width);
          }

        return true;
       }
     else
       {
        addRound(line.b,width);

        return false;
       }
    }

   template <class R,MPointMapType<R> Map>
   void addBack(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);

     if( line.first() )
       {
        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }
       }
    }

  public:

   template <class R>
   LoopDots(R dots,MPointMapType<R> map,MCoord width)
    {
     if( !dots ) return;

     width/=2;

     if( addDirect(dots,map,width) )
       {
        addBack(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width);
       }
    }

   LoopDots(MPointRangeType dots,MCoord width) : LoopDots(dots, [] (MPoint point) { return point; } ,width) {}

   ~LoopDots() {}
 };

/* class HalfPathDots */

class HalfPathDots : public DotsBase
 {
   template <class R,MPointMapType<R> Map>
   bool addDirect(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);

     if( line.first() )
       {
        addInCap(line.b,line.c,width);

        while( line.next() ) addPoint(line.b);

        return true;
       }
     else
       {
        return false;
       }
    }

   template <class R,MPointMapType<R> Map>
   void addBack(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);

     if( line.first() )
       {
        addOutCap(line.b,line.c,width);

        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }
       }
    }

  public:

   template <class R>
   HalfPathDots(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width)
    {
     if( !dots ) return;

     if( half_flag==HalfNeg )
       {
        if( addDirect(dots,map,width) )
          {
           addBack(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width);
          }
       }
     else
       {
        if( addDirect(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width) )
          {
           addBack(dots,map,width);
          }
       }
    }

   HalfPathDots(MPointRangeType dots,HalfFlag half_flag,MCoord width) : HalfPathDots(dots, [] (MPoint point) { return point; } ,half_flag,width) {}

   ~HalfPathDots() {}
 };

/* class HalfLoopDots */

class HalfLoopDots : public DotsBase
 {
   MPoint last_a;
   MPoint last_b;
   MPoint last_c;

  private:

   template <class R,MPointMapType<R> Map>
   bool addDirect(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);

     if( line.first() )
       {
        MPoint o=line.b;
        MPoint s=line.c;

        addPoint(o);

        while( line.next() ) addPoint(line.b);

        if( line.next(o) )
          {
           addPoint(line.b);

           addPoint(line.c);

           addArc(s,line.c,line.b,width);

           last_a=s;
           last_b=line.c;
           last_c=line.b;

           addArc(line.c,line.b,line.a,width);
          }
        else
          {
           addPoint(line.c);

           addArc(s,line.c,line.b,width);

           last_a=s;
           last_b=line.c;
           last_c=line.b;
          }

        return true;
       }
     else
       {
        return false;
       }
    }

   template <class R,MPointMapType<R> Map>
   void addBack(R dots,Map map,MCoord width)
    {
     NextLine<R,Map> line(dots,map);

     if( line.first() )
       {
        while( line.next() )
          {
           addArc(line.a,line.b,line.c,width);
          }

        addArc(last_a,last_b,last_c,width);
       }
    }

  public:

   template <class R>
   HalfLoopDots(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width)
    {
     if( !dots ) return;

     if( half_flag==HalfNeg )
       {
        if( addDirect(dots,map,width) )
          {
           addBack(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width);
          }
       }
     else
       {
        if( addDirect(Algon::BaseRangeAlgo<R>::Reverse(dots),map,width) )
          {
           addBack(dots,map,width);
          }
       }
    }

   HalfLoopDots(MPointRangeType dots,HalfFlag half_flag,MCoord width) : HalfLoopDots(dots, [] (MPoint point) { return point; } ,half_flag,width) {}

   ~HalfLoopDots() {}
 };

/* class CurveBase */

class CurveBase : public DotsBase
 {
  protected:

   CurveBase() {}

   ~CurveBase() {}

   template <class R>
   void buildLoop(R dots,MPointMapType<R> map)
    {
     switch( Algon::BaseRangeAlgo<R>::GetLen(dots) )
       {
        case 0 :
         {
          // do nothing
         }
        break;

        case 1 :
         {
          addPoint(map(dots[0]));
         }
        break;

        case 2 :
         {
          StackObject<CurveDriver> driver(MaxFineness);

          auto a=map(dots[0]);
          auto b=map(dots[1]);

          driver->spline(a,b,a,b,a,b);

          addWithoutFirst(driver->getCurve());

          driver->shift(a);

          addWithoutFirst(driver->getCurve());
         }
        break;

        case 3 :
         {
          StackObject<CurveDriver> driver(MaxFineness);

          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);

          driver->spline(a,b,c,a,b,c);

          addWithoutFirst(driver->getCurve());

          driver->shift(a);

          addWithoutFirst(driver->getCurve());

          driver->shift(b);

          addWithoutFirst(driver->getCurve());
         }
        break;

        case 4 :
         {
          StackObject<CurveDriver> driver(MaxFineness);

          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);
          auto d=map(dots[3]);

          driver->spline(a,b,c,d,a,b);

          addWithoutFirst(driver->getCurve());

          driver->shift(c);

          addWithoutFirst(driver->getCurve());

          driver->shift(d);

          addWithoutFirst(driver->getCurve());

          driver->shift(a);

          addWithoutFirst(driver->getCurve());
         }
        break;

        case 5 :
         {
          StackObject<CurveDriver> driver(MaxFineness);

          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);
          auto d=map(dots[3]);
          auto e=map(dots[4]);

          driver->spline(a,b,c,d,e,a);

          addWithoutFirst(driver->getCurve());

          driver->shift(b);

          addWithoutFirst(driver->getCurve());

          driver->shift(c);

          addWithoutFirst(driver->getCurve());

          driver->shift(d);

          addWithoutFirst(driver->getCurve());

          driver->shift(e);

          addWithoutFirst(driver->getCurve());
         }
        break;

        default: // >=6
         {
          StackObject<CurveDriver> driver(MaxFineness);

          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);
          auto d=map(dots[3]);
          auto e=map(dots[4]);
          auto f=map(dots[5]);

          driver->spline(a,b,c,d,e,f);

          addWithoutFirst(driver->getCurve());

          for(dots+=6; +dots ;++dots)
            {
             driver->shift(map(dots[0]));

             addWithoutFirst(driver->getCurve());
            }

          driver->shift(a);

          addWithoutFirst(driver->getCurve());

          driver->shift(b);

          addWithoutFirst(driver->getCurve());

          driver->shift(c);

          addWithoutFirst(driver->getCurve());

          driver->shift(d);

          addWithoutFirst(driver->getCurve());

          driver->shift(e);

          addWithoutFirst(driver->getCurve());
         }
       }
    }

   template <class R>
   void extPath(R dots,MPointMapType<R> map,CurveDriver &driver)
    {
     switch( Algon::BaseRangeAlgo<R>::GetLen(dots) )
       {
        case 0 :
        case 1 :
         {
          // do nothing
         }
        break;

        case 2 :
         {
          addPoint(map(dots[1]));
         }
        break;

        case 3 :
         {
          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);

          driver.spline(a,b,c,c);

          addWithoutFirst(driver.getCurve());

          driver.shift();

          addWithoutFirst(driver.getCurve());
         }
        break;

        default: // >=4
         {
          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);
          auto d=map(dots[3]);

          driver.spline(a,b,c,d);

          addWithoutFirst(driver.getCurve());

          for(dots+=4; +dots ;++dots)
            {
             driver.shift(map(dots[0]));

             addWithoutFirst(driver.getCurve());
            }

          driver.shift();

          addWithoutFirst(driver.getCurve());

          driver.shift();

          addWithoutFirst(driver.getCurve());
         }
       }
    }

   template <class R>
   void extPath(R dots,R ext,MPointMapType<R> map,CurveDriver &driver)
    {
     switch( Algon::BaseRangeAlgo<R>::GetLen(dots) )
       {
        case 0 :
         {
          extPath(ext,map,driver);
         }
        break;

        case 1 :
         {
          auto a=map(dots[0]);

          switch( Algon::BaseRangeAlgo<R>::GetLen(ext) )
            {
             case 0 :
              {
               // do nothing
              }
             break;

             case 1 :
              {
               auto b=map(ext[0]);

               addPoint(b);
              }
             break;

             case 2 :
              {
               auto b=map(ext[0]);
               auto c=map(ext[1]);

               driver.spline(a,b,c,c);

               addWithoutFirst(driver.getCurve());

               driver.shift();

               addWithoutFirst(driver.getCurve());
              }
             break;

             default: // >=3
              {
               auto b=map(ext[0]);
               auto c=map(ext[1]);
               auto d=map(ext[2]);

               driver.spline(a,b,c,d);

               addWithoutFirst(driver.getCurve());

               for(ext+=3; +ext ;++ext)
                 {
                  driver.shift(map(ext[0]));

                  addWithoutFirst(driver.getCurve());
                 }

               driver.shift();

               addWithoutFirst(driver.getCurve());

               driver.shift();

               addWithoutFirst(driver.getCurve());
              }
            }
         }
        break;

        case 2 :
         {
          auto a=map(dots[0]);
          auto b=map(dots[1]);

          switch( Algon::BaseRangeAlgo<R>::GetLen(ext) )
            {
             case 0 :
              {
               addPoint(b);
              }
             break;

             case 1 :
              {
               auto c=map(ext[0]);

               driver.spline(a,b,c,c);

               addWithoutFirst(driver.getCurve());

               driver.shift();

               addWithoutFirst(driver.getCurve());
              }
             break;

             default: // >=2
              {
               auto c=map(ext[0]);
               auto d=map(ext[1]);

               driver.spline(a,b,c,d);

               addWithoutFirst(driver.getCurve());

               for(ext+=2; +ext ;++ext)
                 {
                  driver.shift(map(ext[0]));

                  addWithoutFirst(driver.getCurve());
                 }

               driver.shift();

               addWithoutFirst(driver.getCurve());

               driver.shift();

               addWithoutFirst(driver.getCurve());
              }
            }
         }
        break;

        case 3 :
         {
          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);

          switch( Algon::BaseRangeAlgo<R>::GetLen(ext) )
            {
             case 0 :
              {
               driver.spline(a,b,c,c);

               addWithoutFirst(driver.getCurve());

               driver.shift();

               addWithoutFirst(driver.getCurve());
              }
             break;

             default: // >=1
              {
               auto d=map(ext[0]);

               driver.spline(a,b,c,d);

               addWithoutFirst(driver.getCurve());

               for(ext+=1; +ext ;++ext)
                 {
                  driver.shift(map(ext[0]));

                  addWithoutFirst(driver.getCurve());
                 }

               driver.shift();

               addWithoutFirst(driver.getCurve());

               driver.shift();

               addWithoutFirst(driver.getCurve());
              }
            }
         }
        break;

        default: // >=4
         {
          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);
          auto d=map(dots[3]);

          driver.spline(a,b,c,d);

          addWithoutFirst(driver.getCurve());

          for(dots+=4; +dots ;++dots)
            {
             driver.shift(map(dots[0]));

             addWithoutFirst(driver.getCurve());
            }

          for(; +ext ;++ext)
            {
             driver.shift(map(ext[0]));

             addWithoutFirst(driver.getCurve());
            }

          driver.shift();

          addWithoutFirst(driver.getCurve());

          driver.shift();

          addWithoutFirst(driver.getCurve());
         }
       }
    }
 };

/* class CurvePath */

class CurvePath : public DotsBase
 {
  public:

   template <class R>
   CurvePath(R dots,MPointMapType<R> map)
    {
     switch( Algon::BaseRangeAlgo<R>::GetLen(dots) )
       {
        case 0 :
         {
          // do nothing
         }
        break;

        case 1 :
         {
          addPoint(map(dots[0]));
         }
        break;

        case 2 :
         {
          addPoint(map(dots[0]));
          addPoint(map(dots[1]));
         }
        break;

        case 3 :
         {
          StackObject<CurveDriver> driver(MaxFineness);

          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);

          addPoint(a);

          driver->spline(a,b,c,c);

          addWithoutFirst(driver->getCurve());

          driver->shift();

          addWithoutFirst(driver->getCurve());
         }
        break;

        default:
         {
          StackObject<CurveDriver> driver(MaxFineness);

          auto a=map(dots[0]);
          auto b=map(dots[1]);
          auto c=map(dots[2]);
          auto d=map(dots[3]);

          addPoint(a);

          driver->spline(a,b,c,d);

          addWithoutFirst(driver->getCurve());

          for(dots+=4; +dots ;++dots)
            {
             driver->shift(map(dots[0]));

             addWithoutFirst(driver->getCurve());
            }

          driver->shift();

          addWithoutFirst(driver->getCurve());

          driver->shift();

          addWithoutFirst(driver->getCurve());
         }
       }
    }

   explicit CurvePath(MPointRangeType dots) : CurvePath(dots, [] (MPoint point) { return point; } ) {}

   ~CurvePath() {}
 };

/* class CurveLoop */

class CurveLoop : public CurveBase
 {
  public:

   template <class R>
   CurveLoop(R dots,MPointMapType<R> map)
    {
     buildLoop(dots,map);
    }

   explicit CurveLoop(MPointRangeType dots) : CurveLoop(dots, [] (MPoint point) { return point; } ) {}

   ~CurveLoop() {}
 };

/* class CurveBreakPath */

class CurveBreakPath : public CurveBase
 {
  public:

   template <DotRangeType R>
   CurveBreakPath(R dots,MPointMapType<R> map)
    {
     if( !dots ) return;

     addPoint(map(dots[0]));

     StackObject<CurveDriver> driver(MaxFineness);

     for(DotBreaker<R> breaker(dots);;)
       {
        R r=breaker.next();

        if( !r ) return;

        extPath(r,map,*driver);
       }
    }

   explicit CurveBreakPath(DotRangeType dots) : CurveBreakPath(dots, [] (Dot dot) { return dot.point; } ) {}

   ~CurveBreakPath() {}
 };

/* class CurveBreakLoop */

class CurveBreakLoop : public CurveBase
 {
   template <DotRangeType R>
   void buildPath(R dots,R ext,MPointMapType<R> map)
    {
     StackObject<CurveDriver> driver(MaxFineness);

     DotBreaker<R> breaker(dots);

     R cur=breaker.next();

     for(;;)
       {
        R next=breaker.next();

        if( !next )
          {
           extPath(cur,ext,map,*driver);

           return;
          }

        extPath(cur,map,*driver);

        cur=next;
       }
    }

  public:

   template <DotRangeType R>
   CurveBreakLoop(R dots,MPointMapType<R> map)
    {
     if( !dots ) return;

     for(R r=dots; +r ;++r)
       {
        if( r->type==DotBreak )
          {
           buildPath(r,PrefixPlus(dots,r),map);

           return;
          }
       }

     buildLoop(dots,map);
    }

   explicit CurveBreakLoop(DotRangeType dots) : CurveBreakLoop(dots, [] (Dot dot) { return dot.point; } ) {}

   ~CurveBreakLoop() {}
 };

/* class GenDrawArt */

class GenDrawArt
 {
   DrawBuf buf;

  public:

   explicit GenDrawArt(const DrawBuf &buf_) : buf(buf_) {}

   const DrawBuf & getBuf() const { return buf; }

  protected:

   // generic line

   void path_gen(MPointRangeType dots,MCoord width,VColor vc)
    {
     path_gen(dots,width,ConstantField(vc));
    }

   void loop_gen(MPointRangeType dots,MCoord width,VColor vc)
    {
     loop_gen(dots,width,ConstantField(vc));
    }

   void path_gen(MPointRangeType dots,MCoord width,const ColorFieldType &field)
    {
     PathDots path(dots,width);

     solid_gen(path.complete(),SolidAll,field);
    }

   void loop_gen(MPointRangeType dots,MCoord width,const ColorFieldType &field)
    {
     LoopDots loop(dots,width);

     solid_gen(loop.complete(),SolidAll,field);
    }


   template <class R>
   void path_gen(R dots,MPointMapType<R> map,MCoord width,VColor vc)
    {
     path_gen(dots,map,width,ConstantField(vc));
    }

   template <class R>
   void loop_gen(R dots,MPointMapType<R> map,MCoord width,VColor vc)
    {
     loop_gen(dots,map,width,ConstantField(vc));
    }

   template <class R>
   void path_gen(R dots,MPointMapType<R> map,MCoord width,const ColorFieldType &field)
    {
     PathDots path(dots,map,width);

     solid_gen(path.complete(),SolidAll,field);
    }

   template <class R>
   void loop_gen(R dots,MPointMapType<R> map,MCoord width,const ColorFieldType &field)
    {
     LoopDots loop(dots,map,width);

     solid_gen(loop.complete(),SolidAll,field);
    }

   // half line

   void path_gen(MPointRangeType dots,HalfFlag half_flag,MCoord width,VColor vc)
    {
     path_gen(dots,half_flag,width,ConstantField(vc));
    }

   void loop_gen(MPointRangeType dots,HalfFlag half_flag,MCoord width,VColor vc)
    {
     loop_gen(dots,half_flag,width,ConstantField(vc));
    }

   void path_gen(MPointRangeType dots,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     HalfPathDots path(dots,half_flag,width);

     solid_gen(path.complete(),SolidAll,field);
    }

   void loop_gen(MPointRangeType dots,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     HalfLoopDots loop(dots,half_flag,width);

     solid_gen(loop.complete(),SolidAll,field);
    }


   template <class R>
   void path_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,VColor vc)
    {
     path_gen(dots,map,half_flag,width,ConstantField(vc));
    }

   template <class R>
   void loop_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,VColor vc)
    {
     loop_gen(dots,map,half_flag,width,ConstantField(vc));
    }

   template <class R>
   void path_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     HalfPathDots path(dots,map,half_flag,width);

     solid_gen(path.complete(),SolidAll,field);
    }

   template <class R>
   void loop_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     HalfLoopDots loop(dots,map,half_flag,width);

     solid_gen(loop.complete(),SolidAll,field);
    }

   // generic curve

   void curvePath_gen(MPointRangeType dots,MCoord width,VColor vc)
    {
     curvePath_gen(dots,width,ConstantField(vc));
    }

   void curveBreakPath_gen(DotRangeType dots,MCoord width,VColor vc)
    {
     curveBreakPath_gen(dots,width,ConstantField(vc));
    }

   void curveLoop_gen(MPointRangeType dots,MCoord width,VColor vc)
    {
     curveLoop_gen(dots,width,ConstantField(vc));
    }

   void curveBreakLoop_gen(DotRangeType dots,MCoord width,VColor vc)
    {
     curveBreakLoop_gen(dots,width,ConstantField(vc));
    }

   void curvePath_gen(MPointRangeType dots,MCoord width,const ColorFieldType &field)
    {
     CurvePath path(dots);

     path_gen(path.complete(),width,field);
    }

   void curveBreakPath_gen(DotRangeType dots,MCoord width,const ColorFieldType &field)
    {
     CurveBreakPath path(dots);

     path_gen(path.complete(),width,field);
    }

   void curveLoop_gen(MPointRangeType dots,MCoord width,const ColorFieldType &field)
    {
     CurveLoop loop(dots);

     loop_gen(loop.complete(),width,field);
    }

   void curveBreakLoop_gen(DotRangeType dots,MCoord width,const ColorFieldType &field)
    {
     CurveBreakLoop loop(dots);

     loop_gen(loop.complete(),width,field);
    }


   template <class R>
   void curvePath_gen(R dots,MPointMapType<R> map,MCoord width,VColor vc)
    {
     curvePath_gen(dots,map,width,ConstantField(vc));
    }

   template <DotRangeType R>
   void curveBreakPath_gen(R dots,MPointMapType<R> map,MCoord width,VColor vc)
    {
     curveBreakPath_gen(dots,map,width,ConstantField(vc));
    }

   template <class R>
   void curveLoop_gen(R dots,MPointMapType<R> map,MCoord width,VColor vc)
    {
     curveLoop_gen(dots,map,width,ConstantField(vc));
    }

   template <DotRangeType R>
   void curveBreakLoop_gen(R dots,MPointMapType<R> map,MCoord width,VColor vc)
    {
     curveBreakLoop_gen(dots,map,width,ConstantField(vc));
    }

   template <class R>
   void curvePath_gen(R dots,MPointMapType<R> map,MCoord width,const ColorFieldType &field)
    {
     CurvePath path(dots,map);

     path_gen(path.complete(),width,field);
    }

   template <DotRangeType R>
   void curveBreakPath_gen(R dots,MPointMapType<R> map,MCoord width,const ColorFieldType &field)
    {
     CurveBreakPath path(dots,map);

     path_gen(path.complete(),width,field);
    }

   template <class R>
   void curveLoop_gen(R dots,MPointMapType<R> map,MCoord width,const ColorFieldType &field)
    {
     CurveLoop loop(dots,map);

     loop_gen(loop.complete(),width,field);
    }

   template <DotRangeType R>
   void curveBreakLoop_gen(R dots,MPointMapType<R> map,MCoord width,const ColorFieldType &field)
    {
     CurveBreakLoop loop(dots,map);

     loop_gen(loop.complete(),width,field);
    }

   // generic half curve

   void curvePath_gen(MPointRangeType dots,HalfFlag half_flag,MCoord width,VColor vc)
    {
     curvePath_gen(dots,half_flag,width,ConstantField(vc));
    }

   void curveBreakPath_gen(DotRangeType dots,HalfFlag half_flag,MCoord width,VColor vc)
    {
     curveBreakPath_gen(dots,half_flag,width,ConstantField(vc));
    }

   void curveLoop_gen(MPointRangeType dots,HalfFlag half_flag,MCoord width,VColor vc)
    {
     curveLoop_gen(dots,half_flag,width,ConstantField(vc));
    }

   void curveBreakLoop_gen(DotRangeType dots,HalfFlag half_flag,MCoord width,VColor vc)
    {
     curveBreakLoop_gen(dots,half_flag,width,ConstantField(vc));
    }

   void curvePath_gen(MPointRangeType dots,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     CurvePath path(dots);

     path_gen(path.complete(),half_flag,width,field);
    }

   void curveBreakPath_gen(DotRangeType dots,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     CurveBreakPath path(dots);

     path_gen(path.complete(),half_flag,width,field);
    }

   void curveLoop_gen(MPointRangeType dots,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     CurveLoop loop(dots);

     loop_gen(loop.complete(),half_flag,width,field);
    }

   void curveBreakLoop_gen(DotRangeType dots,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     CurveBreakLoop loop(dots);

     loop_gen(loop.complete(),half_flag,width,field);
    }


   template <class R>
   void curvePath_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,VColor vc)
    {
     curvePath_gen(dots,map,half_flag,width,ConstantField(vc));
    }

   template <DotRangeType R>
   void curveBreakPath_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,VColor vc)
    {
     curveBreakPath_gen(dots,map,half_flag,width,ConstantField(vc));
    }

   template <class R>
   void curveLoop_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,VColor vc)
    {
     curveLoop_gen(dots,map,half_flag,width,ConstantField(vc));
    }

   template <DotRangeType R>
   void curveBreakLoop_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,VColor vc)
    {
     curveBreakLoop_gen(dots,map,half_flag,width,ConstantField(vc));
    }

   template <class R>
   void curvePath_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     CurvePath path(dots,map);

     path_gen(path.complete(),half_flag,width,field);
    }

   template <DotRangeType R>
   void curveBreakPath_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     CurveBreakPath path(dots,map);

     path_gen(path.complete(),half_flag,width,field);
    }

   template <class R>
   void curveLoop_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     CurveLoop loop(dots,map);

     loop_gen(loop.complete(),half_flag,width,field);
    }

   template <DotRangeType R>
   void curveBreakLoop_gen(R dots,MPointMapType<R> map,HalfFlag half_flag,MCoord width,const ColorFieldType &field)
    {
     CurveBreakLoop loop(dots,map);

     loop_gen(loop.complete(),half_flag,width,field);
    }

   // generic solid

   void solid_gen(MPointRangeType dots,SolidFlag solid_flag,VColor vc)
    {
     solid_gen(dots,solid_flag,ConstantField(vc));
    }

   template <ColorFieldType Field>
   void solid_gen(MPointRangeType dots,SolidFlag solid_flag,const Field &field)
    {
     SolidDriver driver(dots);

     driver(solid_flag,FieldPlot<Field>(buf,field));
    }


   template <class R>
   void solid_gen(R dots,MPointMapType<R> map,SolidFlag solid_flag,VColor vc)
    {
     solid_gen(dots,map,solid_flag,ConstantField(vc));
    }

   template <class R,ColorFieldType Field>
   void solid_gen(R dots,MPointMapType<R> map,SolidFlag solid_flag,const Field &field)
    {
     SolidDriver driver(dots,map);

     driver(solid_flag,FieldPlot<Field>(buf,field));
    }

   // generic curve solid

   void curveSolid_gen(MPointRangeType dots,SolidFlag solid_flag,VColor vc)
    {
     curveSolid_gen(dots,solid_flag,ConstantField(vc));
    }

   void curveBreakSolid_gen(DotRangeType dots,SolidFlag solid_flag,VColor vc)
    {
     curveBreakSolid_gen(dots,solid_flag,ConstantField(vc));
    }

   void curveSolid_gen(MPointRangeType dots,SolidFlag solid_flag,const ColorFieldType &field)
    {
     CurveLoop loop(dots);

     solid_gen(loop.complete(),solid_flag,field);
    }

   void curveBreakSolid_gen(DotRangeType dots,SolidFlag solid_flag,const ColorFieldType &field)
    {
     CurveBreakLoop loop(dots);

     solid_gen(loop.complete(),solid_flag,field);
    }


   template <class R>
   void curveSolid_gen(R dots,MPointMapType<R> map,SolidFlag solid_flag,VColor vc)
    {
     curveSolid_gen(dots,map,solid_flag,ConstantField(vc));
    }

   template <DotRangeType R>
   void curveBreakSolid_gen(R dots,MPointMapType<R> map,SolidFlag solid_flag,VColor vc)
    {
     curveBreakSolid_gen(dots,map,solid_flag,ConstantField(vc));
    }

   template <class R>
   void curveSolid_gen(R dots,MPointMapType<R> map,SolidFlag solid_flag,const ColorFieldType &field)
    {
     CurveLoop loop(dots,map);

     solid_gen(loop.complete(),solid_flag,field);
    }

   template <DotRangeType R>
   void curveBreakSolid_gen(R dots,MPointMapType<R> map,SolidFlag solid_flag,const ColorFieldType &field)
    {
     CurveBreakLoop loop(dots,map);

     solid_gen(loop.complete(),solid_flag,field);
    }

   // generic special

   void knob_gen(MPoint center,MCoord len,const ColorFieldType &field)
    {
     MPoint temp[]=
      {
       center+MPoint(-len,-len),
       center+MPoint(len,-len),
       center+MPoint(len,len),
       center+MPoint(-len,len)
      };

     solid_gen(Range_const(temp),SolidAll,field);
    }

   void ball_gen(MPoint center,MCoord radius,const ColorFieldType &field)
    {
     LineRound obj(center,radius);

     curveSolid_gen(obj.get(),SolidAll,field);
    }

   void circle_gen(MPoint center,MCoord radius,MCoord width,const ColorFieldType &field)
    {
     LineRound obj(center,radius);

     curveLoop_gen(obj.get(),width,field);
    }
 };

/* class DrawArt */

class DrawArt : public GenDrawArt
 {
  public:

   explicit DrawArt(const DrawBuf &buf) : GenDrawArt(buf) {}

   // simple

   void pixel(Point p,DesktopColor color);

   void erase(DesktopColor color);

   void erase(VColor vc,Clr alpha);

   void block(Pane pane,DesktopColor color);

   void block(Pane pane,VColor vc,Clr alpha);

   // special

   void knob(MPoint center,MCoord len,VColor vc);

   void ball(MPoint center,MCoord radius,VColor vc);

   void ball(MPoint center,MCoord radius,const TwoField &field);

   void ball(MPoint center,MCoord radius,const RadioField &field);

   void ball(MPoint center,MCoord radius,const AbstractField &field);

   void ball(MPoint center,MCoord radius,const AbstractAlphaField &field);

   void circle(MPoint center,MCoord radius,MCoord width,VColor vc);

   template <class ... TT>
   void path(MCoord width,VColor vc,TT ... tt) requires ( MPointSetTypes<TT...> )
    {
     MPoint temp[sizeof ... (TT)]={ tt... };

     path(Range_const(temp),width,vc);
    }

   template <class ... TT>
   void loop(MCoord width,VColor vc,TT ... tt) requires ( MPointSetTypes<TT...> )
    {
     MPoint temp[sizeof ... (TT)]={ tt... };

     loop(Range_const(temp),width,vc);
    }

   template <class ... TT>
   void path(HalfFlag half_flag,MCoord width,VColor vc,TT ... tt) requires ( MPointSetTypes<TT...> )
    {
     MPoint temp[sizeof ... (TT)]={ tt... };

     path(Range_const(temp),half_flag,width,vc);
    }

   template <class ... TT>
   void loop(HalfFlag half_flag,MCoord width,VColor vc,TT ... tt) requires ( MPointSetTypes<TT...> )
    {
     MPoint temp[sizeof ... (TT)]={ tt... };

     loop(Range_const(temp),half_flag,width,vc);
    }

   // special line

   void path(PtrLen<const MPoint> dots,MCoord width,VColor vc);

   void loop(PtrLen<const MPoint> dots,MCoord width,VColor vc);

   // special half line

   void path(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc);

   void loop(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc);

   // special curve

   void curvePath(PtrLen<const MPoint> dots,MCoord width,VColor vc);

   void curveLoop(PtrLen<const MPoint> dots,MCoord width,VColor vc);

   void curvePath(PtrLen<const Dot> dots,MCoord width,VColor vc);

   void curveLoop(PtrLen<const Dot> dots,MCoord width,VColor vc);

   // special half curve

   void curvePath(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc);

   void curveLoop(PtrLen<const MPoint> dots,HalfFlag half_flag,MCoord width,VColor vc);

   void curvePath(PtrLen<const Dot> dots,HalfFlag half_flag,MCoord width,VColor vc);

   void curveLoop(PtrLen<const Dot> dots,HalfFlag half_flag,MCoord width,VColor vc);

   // special solid

   void solid(PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor vc);

   void solid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const TwoField &field);

   void solid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const RadioField &field);

   void solid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractField &field);

   void solid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractAlphaField &field);

   // special curve solid

   void curveSolid(PtrLen<const MPoint> dots,SolidFlag solid_flag,VColor vc);

   void curveSolid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const TwoField &field);

   void curveSolid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const RadioField &field);

   void curveSolid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractField &field);

   void curveSolid(PtrLen<const MPoint> dots,SolidFlag solid_flag,const AbstractAlphaField &field);

   void curveSolid(PtrLen<const Dot> dots,SolidFlag solid_flag,VColor vc);

   void curveSolid(PtrLen<const Dot> dots,SolidFlag solid_flag,const TwoField &field);

   void curveSolid(PtrLen<const Dot> dots,SolidFlag solid_flag,const RadioField &field);

   void curveSolid(PtrLen<const Dot> dots,SolidFlag solid_flag,const AbstractField &field);

   void curveSolid(PtrLen<const Dot> dots,SolidFlag solid_flag,const AbstractAlphaField &field);
 };

} // namespace Smooth

/* type SmoothDot */

using SmoothDot = Smooth::Dot ;

/* type SmoothBreakDot */

using SmoothBreakDot = Smooth::BreakDot ;

/* type SmoothDotShift */

using SmoothDotShift = Smooth::DotShift ;

/* type SmoothDrawArt */

using SmoothDrawArt = Smooth::DrawArt ;

} // namespace Video
} // namespace CCore

#endif


