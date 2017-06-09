/* Font.h */
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

#ifndef CCore_inc_video_Font_h
#define CCore_inc_video_Font_h

#include <CCore/inc/video/DrawBuf.h>

#include <CCore/inc/RefObjectBase.h>
#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {
namespace Video {

/* consts */

enum AlignX
 {
  AlignX_Left,
  AlignX_Center,
  AlignX_Right,
  AlignX_Given
 };

enum AlignY
 {
  AlignY_Top,
  AlignY_Center,
  AlignY_Bottom,
  AlignY_Given
 };

/* types */

using CharFunction = Function<VColor (ulen index,char ch,Point base,Point delta)> ; // base relative pane

/* classes */

struct FontSize;

struct TextSize;

struct TextPlace;

struct AbstractSparseString;

class SingleString;

class DoubleString;

struct AbstractFont;

class Font;

template <class FontShape> class DotFontBase;

/* struct FontSize */

struct FontSize
 {
  Coord min_dx;
  Coord max_dx;
  Coord dy;
  Coord by;
  Coord dx0;
  Coord dx1;
  Coord skew;

  Coord medDX() const { return min_dx+(max_dx-min_dx)/2; }
 };

/* struct TextSize */

struct TextSize
 {
  Coord dx;      // MaxCoord if overflowed
  Coord dy;
  Coord by;
  Coord dx0;
  Coord dx1;
  Coord skew;
  Coord full_dx; // dx+font_size.dx0+font_size.dx1 , MaxCoord if overflowed
  bool overflow; // full_dx overflowed

  Coord extDX() const { return dx+dx0+dx1; }
 };

/* struct TextPlace */

struct TextPlace
 {
  AlignX align_x;
  AlignY align_y;

  Coord x = 0 ; // relative pane
  Coord y = 0 ;

  TextPlace(AlignX align_x_,AlignY align_y_) : align_x(align_x_),align_y(align_y_) {}

  TextPlace(AlignX align_x_,Coordinate y_) : align_x(align_x_),align_y(AlignY_Given),y(+y_) {}

  TextPlace(Coordinate x_,AlignY align_y_) : align_x(AlignX_Given),align_y(align_y_),x(+x_) {}

  TextPlace(Coordinate x_,Coordinate y_) : align_x(AlignX_Given),align_y(AlignY_Given),x(+x_),y(+y_) {}

  TextPlace(Point pos) : TextPlace(pos.x,pos.y) {}
 };

/* struct AbstractSparseString */

struct AbstractSparseString
 {
  // abstract

  virtual void restart()=0;

  virtual StrLen next()=0;

  virtual void cutPrefix(ulen len)=0;

  virtual void cutSuffix(ulen len)=0;

  virtual bool cutCenter(ulen len)=0; // true if extra character is appended, len+1 result is returned

  // helper

  template <FuncInitArgType<StrLen> FuncInit>
  auto apply(FuncInit func_init)
   {
    restart();

    FunctorTypeOf<FuncInit> func(func_init);

    for(;;)
      {
       StrLen r=next();

       if( !r ) break;

       func(r);
      }

    return Algon::GetResult(func);
   }

  template <FuncInitArgType<char> FuncInit>
  auto applyChar(FuncInit func_init)
   {
    restart();

    FunctorTypeOf<FuncInit> func(func_init);

    for(;;)
      {
       StrLen r=next();

       if( !r ) break;

       for(char ch : r ) func(ch);
      }

    return Algon::GetResult(func);
   }

  template <FuncInitType<bool,StrLen> FuncInit>
  auto apply(FuncInit func_init)
   {
    restart();

    FunctorTypeOf<FuncInit> func(func_init);

    for(;;)
      {
       StrLen r=next();

       if( !r ) break;

       if( !func(r) ) break;
      }

    return Algon::GetResult(func);
   }

  template <FuncInitType<bool,char> FuncInit>
  auto applyChar(FuncInit func_init)
   {
    restart();

    FunctorTypeOf<FuncInit> func(func_init);

    for(;;)
      {
       StrLen r=next();

       if( !r ) break;

       for(char ch : r ) if( !func(ch) ) return Algon::GetResult(func);
      }

    return Algon::GetResult(func);
   }

  ULenSat countLen(bool guard_overflow=false);

  void cutSuffix_index(ulen len,ulen &index)
   {
    index=countLen(true).value-len;

    cutSuffix(len);
   }

  bool cutCenter_index(ulen len,ulen &index)
   {
    index=(countLen(true).value-len)/2;

    return cutCenter(len);
   }
 };

/* class SingleString */

class SingleString : public AbstractSparseString
 {
   StrLen str;
   bool first = true ;

  public:

   explicit SingleString(StrLen str_) : str(str_) {}

   ~SingleString() {}

   // AbstractSparseString

   virtual void restart();

   virtual StrLen next();

   virtual void cutPrefix(ulen len);

   virtual void cutSuffix(ulen len);

   virtual bool cutCenter(ulen len);
 };

/* class DoubleString */

class DoubleString : public AbstractSparseString
 {
   StrLen str1;
   StrLen str2;
   unsigned ind = 1 ;

  public:

   DoubleString(StrLen str1_,StrLen str2_);

   ~DoubleString() {}

   // AbstractSparseString

   virtual void restart();

   virtual StrLen next();

   virtual void cutPrefix(ulen len);

   virtual void cutSuffix(ulen len);

   virtual bool cutCenter(ulen len);
 };

/* struct AbstractFont */

struct AbstractFont
 {
  // abstract

  virtual FontSize getSize() const =0;

  virtual TextSize text(AbstractSparseString &str) const =0;

  virtual ulen fit(AbstractSparseString &str,Coord full_dx) const =0; // prefix length

  virtual ulen position(AbstractSparseString &str,Point point) const =0; // 1-based cell index, 0 -- before the first

  virtual void text(DrawBuf buf,Pane pane,TextPlace place,AbstractSparseString &str,VColor vc) const =0;

  virtual void text(DrawBuf buf,Pane pane,TextPlace place,AbstractSparseString &str,CharFunction func) const =0;

  // helpers

  TextSize text_guarded(AbstractSparseString &str) const
   {
    TextSize ts=text(str);

    IntGuard( !ts.overflow );

    return ts;
   }

  TextSize text(AbstractSparseString &str,ulen len) const
   {
    str.cutPrefix(len);

    return text(str);
   }

  TextSize text_guarded(AbstractSparseString &str,ulen len) const
   {
    TextSize ts=text(str,len);

    IntGuard( !ts.overflow );

    return ts;
   }

  // single

  TextSize text(StrLen str) const
   {
    SingleString obj(str);

    return text(obj);
   }

  TextSize text(StrLen str,ulen len) const
   {
    SingleString obj(str);

    return text(obj,len);
   }

  TextSize text_guarded(StrLen str) const
   {
    SingleString obj(str);

    return text_guarded(obj);
   }

  TextSize text_guarded(StrLen str,ulen len) const
   {
    SingleString obj(str);

    return text_guarded(obj,len);
   }

  ulen fit(StrLen str,Coordinate full_dx) const
   {
    SingleString obj(str);

    return fit(obj,+full_dx);
   }

  ulen position(StrLen str,Point point) const
   {
    SingleString obj(str);

    return position(obj,point);
   }

  void text(DrawBuf buf,Pane pane,TextPlace place,StrLen str,VColor vc) const
   {
    SingleString obj(str);

    text(buf,pane,place,obj,vc);
   }

  void text(DrawBuf buf,Pane pane,TextPlace place,StrLen str,CharFunction func) const
   {
    SingleString obj(str);

    text(buf,pane,place,obj,func);
   }

  // double

  TextSize text(StrLen str1,StrLen str2) const
   {
    DoubleString obj(str1,str2);

    return text(obj);
   }

  TextSize text(StrLen str1,StrLen str2,ulen len) const
   {
    DoubleString obj(str1,str2);

    return text(obj,len);
   }

  TextSize text_guarded(StrLen str1,StrLen str2) const
   {
    DoubleString obj(str1,str2);

    return text_guarded(obj);
   }

  TextSize text_guarded(StrLen str1,StrLen str2,ulen len) const
   {
    DoubleString obj(str1,str2);

    return text_guarded(obj,len);
   }

  ulen fit(StrLen str1,StrLen str2,Coordinate full_dx) const
   {
    DoubleString obj(str1,str2);

    return fit(obj,+full_dx);
   }

  ulen position(StrLen str1,StrLen str2,Point point) const
   {
    DoubleString obj(str1,str2);

    return position(obj,point);
   }

  void text(DrawBuf buf,Pane pane,TextPlace place,StrLen str1,StrLen str2,VColor vc) const
   {
    DoubleString obj(str1,str2);

    text(buf,pane,place,obj,vc);
   }

  void text(DrawBuf buf,Pane pane,TextPlace place,StrLen str1,StrLen str2,CharFunction func) const
   {
    DoubleString obj(str1,str2);

    text(buf,pane,place,obj,func);
   }
 };

/* type FontBase */

using FontBase = RefObjectBase<AbstractFont> ;

/* class Font */

class Font
 {
   RefPtr<FontBase> ptr;

  protected:

   explicit Font(FontBase *font) : ptr(font) {}

   template <class T>
   T * castPtr() const { return dynamic_cast<T *>(ptr.getPtr()); }

  public:

   Font() noexcept; // default font

   ~Font() {}

   const AbstractFont * getPtr() const { return ptr.getPtr(); }

   const AbstractFont * operator -> () const { return ptr.getPtr(); }
 };

/* class DotFontBase<FontShape> */

 //
 // class FontShape
 //  {
 //    ...
 //
 //   public:
 //
 //    ...
 //
 //    Coord dX() const; // > 0
 //
 //    Coord dY() const; // > 0
 //
 //    Coord bY() const; // > 0
 //
 //    BoolGlyph operator () (char ch) const;
 //  };
 //

template <class FontShape>
class DotFontBase : public FontBase
 {
   FontShape shape;

   ulen max_len;

  private:

   TextSize text(ulen len,bool overflow) const
    {
     TextSize ret;

     if( overflow )
       {
        ret.dx=MaxCoord;
        ret.overflow=true;
       }
     else
       {
        ret.dx=Coord(len)*shape.dX();
        ret.overflow=false;
       }

     ret.full_dx=ret.dx;

     ret.dy=shape.dY();
     ret.by=shape.bY();
     ret.dx0=0;
     ret.dx1=0;
     ret.skew=0;

     return ret;
    }

   class WorkBuf : public DrawBuf
    {
      const FontShape &shape;

     public:

      WorkBuf(const DrawBuf &buf,const FontShape &shape_) : DrawBuf(buf),shape(shape_) {}

      // char

      void text(Coord x,Coord y,char ch,DesktopColor color)
       {
        buf.glyph_safe(Point(x,y),shape(ch),color);
       }

      // text

      Point prepare(Coord px,Coord py,TextPlace place,AbstractSparseString &str) const
       {
        Coord fdx=shape.dX();
        Coord fdy=shape.dY();
        Coord fby=shape.bY();

        Coord y;

        switch( place.align_y )
          {
           case AlignY_Top : y=0; break;

           case AlignY_Center : y=(py-fdy)/2; break;

           case AlignY_Bottom : y=py-fdy; break;

           default: y=IntSub(place.y,fby);
          }

        Coord x;

        switch( place.align_x )
          {
           case AlignX_Left : x=0; break;

           case AlignX_Right :
            {
             ULenSat len=str.countLen();

             ulen cap=ulen(px/fdx)+1;

             if( len<=cap )
               {
                x=Coord( px-MCoord(len.value)*fdx );
               }
             else
               {
                str.cutSuffix(cap);

                x=Coord( px-MCoord(cap)*fdx );
               }
            }
           break;

           case AlignX_Center :
            {
             ULenSat len=str.countLen();

             ulen cap=ulen(px/fdx)+1;

             if( len<=cap )
               {
                x=Coord( (px-MCoord(len.value)*fdx)/2 );
               }
             else
               {
                ulen new_len=cap+str.cutCenter(cap);

                x=Coord( (px-MCoord(new_len)*fdx)/2 );
               }
            }
           break;

           default: x=place.x;
          }

        return Point(x,y);
       }

      Point prepare(Coord px,Coord py,TextPlace place,AbstractSparseString &str,ulen &index) const
       {
        Coord fdx=shape.dX();
        Coord fdy=shape.dY();
        Coord fby=shape.bY();

        Coord y;

        switch( place.align_y )
          {
           case AlignY_Top : y=0; break;

           case AlignY_Center : y=(py-fdy)/2; break;

           case AlignY_Bottom : y=py-fdy; break;

           default: y=IntSub(place.y,fby);
          }

        Coord x;

        switch( place.align_x )
          {
           case AlignX_Left : index=0; x=0; break;

           case AlignX_Right :
            {
             ULenSat len=str.countLen();

             ulen cap=ulen(px/fdx)+1;

             if( len<=cap )
               {
                index=0;

                x=Coord( px-MCoord(len.value)*fdx );
               }
             else
               {
                str.cutSuffix_index(cap,index);

                x=Coord( px-MCoord(cap)*fdx );
               }
            }
           break;

           case AlignX_Center :
            {
             ULenSat len=str.countLen();

             ulen cap=ulen(px/fdx)+1;

             if( len<=cap )
               {
                index=0;

                x=Coord( (px-MCoord(len.value)*fdx)/2 );
               }
             else
               {
                ulen new_len=cap+str.cutCenter_index(cap,index);

                x=Coord( (px-MCoord(new_len)*fdx)/2 );
               }
            }
           break;

           default: index=0; x=place.x;
          }

        return Point(x,y);
       }

      void text(Point point,AbstractSparseString &str,DesktopColor color)
       {
        Coord dx=buf.dX();
        Coord dy=buf.dY();

        Coord fdx=shape.dX();
        Coord fdy=shape.dY();

        Point p=map(point);

        MCoord x=p.x;
        Coord y=p.y;

        if( y>=dy || y<=-fdy ) return;

        str.applyChar( [&] (char ch)
                           {
                            if( x>=dx ) return false;

                            text((Coord)x,y,ch,color);

                            x+=fdx;

                            return true;

                           } );
       }

      void text(Point point,AbstractSparseString &str,ulen index,CharFunction func)
       {
        Coord dx=buf.dX();
        Coord dy=buf.dY();

        Coord fdx=shape.dX();
        Coord fdy=shape.dY();
        Coord fby=shape.bY();

        Point p=map(point);

        MCoord x=p.x;
        Coord y=p.y;

        if( y>=dy || y<=-fdy ) return;

        point=point.addY(fby);

        str.applyChar( [&] (char ch)
                           {
                            if( x>=dx ) return false;

                            VColor vc=func(index++,ch,point,Point(fdx,0));

                            text((Coord)x,y,ch,vc);

                            x+=fdx;

                            point=point.addX(fdx);

                            return true;

                           } );
       }

      void text(Coord px,Coord py,TextPlace place,AbstractSparseString &str,DesktopColor color)
       {
        if( !*this ) return;

        Point point=prepare(px,py,place,str);

        text(point,str,color);
       }

      void text(Coord px,Coord py,TextPlace place,AbstractSparseString &str,CharFunction func)
       {
        if( !*this ) return;

        ulen index;
        Point point=prepare(px,py,place,str,index);

        text(point,str,index,func);
       }
    };

  public:

   template <class ... TT>
   explicit DotFontBase(TT && ... tt)
    : shape( std::forward<TT>(tt)... )
    {
     max_len=ulen(MaxCoord/shape.dX());
    }

   virtual ~DotFontBase() {}

   // AbstractFont

   virtual FontSize getSize() const
    {
     FontSize ret;

     ret.min_dx=shape.dX();
     ret.max_dx=shape.dX();
     ret.dy=shape.dY();
     ret.by=shape.bY();
     ret.dx0=0;
     ret.dx1=0;
     ret.skew=0;

     return ret;
    }

   virtual TextSize text(AbstractSparseString &str) const
    {
     ULenSat len=str.countLen();

     return text(len.value,len>max_len);
    }

   virtual ulen fit(AbstractSparseString &str,Coord full_dx) const
    {
     ULenSat len=str.countLen();

     ulen max_len=full_dx/shape.dX();

     if( len<=max_len ) return len.value;

     return max_len;
    }

   virtual ulen position(AbstractSparseString &,Point point) const
    {
     if( point.x<0 ) return 0;

     return 1+ulen(point.x/shape.dX());
    }

   virtual void text(DrawBuf buf,Pane pane,TextPlace place,AbstractSparseString &str,VColor vc) const
    {
     WorkBuf out(buf.cutRebase(pane),shape);

     out.text(pane.dx,pane.dy,place,str,vc);
    }

   virtual void text(DrawBuf buf,Pane pane,TextPlace place,AbstractSparseString &str,CharFunction func) const
    {
     WorkBuf out(buf.cutRebase(pane),shape);

     out.text(pane.dx,pane.dy,place,str,func);
    }
 };

} // namespace Video
} // namespace CCore

#endif


