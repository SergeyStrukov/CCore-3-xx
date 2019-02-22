/* Font.h */
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

#ifndef CCore_inc_video_Font_h
#define CCore_inc_video_Font_h

#include <CCore/inc/video/DrawBuf.h>

#include <CCore/inc/Symbol.h>
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

using CharFunction = Function<VColor (ulen index,Char ch,Point base,Point delta)> ; // base relative pane

/* classes */

struct FontSize;

struct TextSize;

struct TextPlace;

struct AbstractSparseString;

class SingleString;

class DoubleString;

#ifdef CCORE_UTF8

class CharString;

#endif

struct AbstractFont;

template <class FontShape> class DotFontBase;

/* enum FontClass */

enum FontClass
 {
  FontHasNoClass = 0,

  FontOldstyleSerif     =  1,
  FontTransitionalSerif =  2,
  FontModernSerif       =  3,
  FontClarendonSerif    =  4,
  FontSlabSerif         =  5,
  FontFreedomSerif      =  7,
  FontSansSerif         =  8,
  FontOrnamental        =  9,
  FontScript            = 10,
  FontSymbol            = 12,

  FontClassLim = 13
 };

FontClass Correct(FontClass fc);

const char * GetTextDesc(FontClass fc);

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
  Coord dx;
  Coord dy;
  Coord by;
  Coord dx0;
  Coord dx1;
  Coord skew;
  Coord full_dx; // dx+font_size.dx0+font_size.dx1

  Coord extDX() const { return dx+dx0+dx1; }

  Point getSize() const { return {full_dx,dy}; }
 };

/* struct TextPlace */

struct TextPlace
 {
  AlignX align_x;
  AlignY align_y;

  Coord x = 0 ; // relative pane
  Coord y = 0 ;

  TextPlace(AlignX align_x_,AlignY align_y_) : align_x(align_x_),align_y(align_y_) {}

  TextPlace(AlignX align_x_,Coord y_) : align_x(align_x_),align_y(AlignY_Given),y(y_) {}

  TextPlace(Coord x_,AlignY align_y_) : align_x(AlignX_Given),align_y(align_y_),x(x_) {}

  TextPlace(Coord x_,Coord y_) : align_x(AlignX_Given),align_y(AlignY_Given),x(x_),y(y_) {}

  TextPlace(Point pos) : TextPlace(pos.x,pos.y) {}
 };

/* struct AbstractSparseString */

struct AbstractSparseString
 {
  // abstract

   // props

  virtual ulen getLen() const =0;

   // cursor

  virtual void restart()=0;

  struct Result
   {
    Char ch;
    bool ok;
   };

  virtual Result next()=0;

  virtual ulen getCount() const =0;

   // self-modification

  virtual void cutPrefix(ulen len)=0;

  virtual void cutSuffix(ulen len)=0;

  virtual void cutSuffix(ulen len,ulen &index);

  virtual bool cutCenter(ulen len); // true if extra character is appended, len+1 result is returned

  virtual bool cutCenter(ulen len,ulen &index);

  // helper

  template <FuncInitArgType<Char> FuncInit>
  auto apply(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);

    restart();

    for(;;)
      {
       auto result=next();

       if( !result.ok ) break;

       func(result.ch);
      }

    return Algon::GetResult(func);
   }

  template <FuncInitType<bool,Char> FuncInit>
  auto apply(FuncInit func_init)
   {
    FunctorTypeOf<FuncInit> func(func_init);

    restart();

    for(;;)
      {
       auto result=next();

       if( !result.ok || !func(result.ch) ) break;
      }

    return Algon::GetResult(func);
   }
 };

/* class SingleString */

class SingleString : public AbstractSparseString
 {
   StrLen str;
   StrLen cur;

#ifdef CCORE_UTF8

   ulen total;
   ulen count;

#endif

  public:

   explicit SingleString(StrLen str);

   ~SingleString() {}

   // AbstractSparseString

    // props

   virtual ulen getLen() const;

    // cursor

   virtual void restart();

   virtual Result next();

   virtual ulen getCount() const;

    // self-modification

   virtual void cutPrefix(ulen len);

   virtual void cutSuffix(ulen len);
 };

/* class DoubleString */

class DoubleString : public AbstractSparseString
 {
   StrLen str1;
   StrLen str2;

#ifdef CCORE_UTF8

   ulen total1;
   ulen total2;
   ulen count;

#else

   ulen total;

#endif

   StrLen cur;
   bool first = true ;

  public:

   DoubleString(StrLen str1,StrLen str2);

   ~DoubleString() {}

   // AbstractSparseString

    // props

   virtual ulen getLen() const;

    // cursor

   virtual void restart();

   virtual Result next();

   virtual ulen getCount() const;

    // self-modification

   virtual void cutPrefix(ulen len);

   virtual void cutSuffix(ulen len);
 };

#ifdef CCORE_UTF8

/* class CharString */

class CharString : public AbstractSparseString
 {
   PtrLen<const Char> str;
   PtrLen<const Char> cur;

  public:

   explicit CharString(PtrLen<const Char> str);

   ~CharString() {}

   // AbstractSparseString

    // props

   virtual ulen getLen() const;

    // cursor

   virtual void restart();

   virtual Result next();

   virtual ulen getCount() const;

    // self-modification

   virtual void cutPrefix(ulen len);

   virtual void cutSuffix(ulen len);
 };

#endif

/* struct AbstractFont */

struct AbstractFont
 {
  // abstract

  virtual FontClass getFontClass() const =0;

  virtual FontSize getSize() const =0;

  virtual TextSize text(AbstractSparseString &str) const =0;

  virtual ulen fit(AbstractSparseString &str,Coord full_dx) const =0; // prefix length

  virtual ulen position(AbstractSparseString &str,Point point) const =0; // 1-based cell index, 0 -- before the first

  virtual void text(DrawBuf buf,Pane pane,TextPlace place,AbstractSparseString &str,VColor vc) const =0;

  virtual void text(DrawBuf buf,Pane pane,TextPlace place,AbstractSparseString &str,CharFunction func) const =0;

  // helpers

  TextSize text(AbstractSparseString &str,ulen len) const
   {
    str.cutPrefix(len);

    return text(str);
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

  ulen fit(StrLen str,Coord full_dx) const
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

  ulen fit(StrLen str1,StrLen str2,Coord full_dx) const
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

#ifdef CCORE_UTF8

  // Char

  TextSize text(PtrLen<const Char> str) const
   {
    CharString obj(str);

    return text(obj);
   }

  TextSize text(PtrLen<const Char> str,ulen len) const
   {
    CharString obj(str);

    return text(obj,len);
   }

  ulen fit(PtrLen<const Char> str,Coord full_dx) const
   {
    CharString obj(str);

    return fit(obj,+full_dx);
   }

  ulen position(PtrLen<const Char> str,Point point) const
   {
    CharString obj(str);

    return position(obj,point);
   }

  void text(DrawBuf buf,Pane pane,TextPlace place,PtrLen<const Char> str,VColor vc) const
   {
    CharString obj(str);

    text(buf,pane,place,obj,vc);
   }

  void text(DrawBuf buf,Pane pane,TextPlace place,PtrLen<const Char> str,CharFunction func) const
   {
    CharString obj(str);

    text(buf,pane,place,obj,func);
   }

#endif

  template <class T,class ... TT>
  void textOn(T &obj,TT && ... tt) const
   {
    text(obj.getBuf(), std::forward<TT>(tt)... );
   }
 };

/* type FontBase */

using FontBase = RefObjectBase<AbstractFont> ;

/* GetNullFontPtr() */

FontBase * GetNullFontPtr();

/* type Font */

using Font = RefObjectHook<FontBase,AbstractFont,GetNullFontPtr> ;

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
 //    BoolGlyph operator () (Char ch) const;
 //  };
 //

template <class FontShape>
class DotFontBase : public FontBase
 {
   FontShape shape;

  private:

   TextSize text(ulen len) const
    {
     TextSize ret;

     ret.dx=CountToCoord(len)*shape.dX();
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

      void text(Coord x,Coord y,Char ch,DesktopColor color)
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

           default: y=place.y-fby;
          }

        Coord x;

        switch( place.align_x )
          {
           case AlignX_Left : x=0; break;

           case AlignX_Right :
            {
             ulen len=str.getLen();
             ulen cap=ulen(px/fdx)+1;

             if( len<=cap )
               {
                x=px-CountToCoord(len)*fdx;
               }
             else
               {
                str.cutSuffix(cap);

                x=px-CountToCoord(cap)*fdx;
               }
            }
           break;

           case AlignX_Center :
            {
             ulen len=str.getLen();
             ulen cap=ulen(px/fdx)+1;

             if( len<=cap )
               {
                x=(px-CountToCoord(len)*fdx)/2;
               }
             else
               {
                ulen new_len=cap+str.cutCenter(cap);

                x=(px-CountToCoord(new_len)*fdx)/2;
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

           default: y=place.y-fby;
          }

        Coord x;

        switch( place.align_x )
          {
           case AlignX_Left : index=0; x=0; break;

           case AlignX_Right :
            {
             ulen len=str.getLen();
             ulen cap=ulen(px/fdx)+1;

             if( len<=cap )
               {
                index=0;

                x=px-CountToCoord(len)*fdx;
               }
             else
               {
                str.cutSuffix(cap,index);

                x=px-CountToCoord(cap)*fdx;
               }
            }
           break;

           case AlignX_Center :
            {
             ulen len=str.getLen();
             ulen cap=ulen(px/fdx)+1;

             if( len<=cap )
               {
                index=0;

                x=(px-CountToCoord(len)*fdx)/2;
               }
             else
               {
                ulen new_len=cap+str.cutCenter(cap,index);

                x=(px-CountToCoord(new_len)*fdx)/2;
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

        Coord x=p.x;
        Coord y=p.y;

        if( y>=dy || y<=-fdy ) return;

        str.apply( [&] (Char ch)
                       {
                        if( x>=dx ) return false;

                        text(x,y,ch,color);

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

        Coord x=p.x;
        Coord y=p.y;

        if( y>=dy || y<=-fdy ) return;

        point=point.addY(fby);

        str.apply( [&] (Char ch)
                       {
                        if( x>=dx ) return false;

                        VColor vc=func(index++,ch,point,Point(fdx,0));

                        text(x,y,ch,vc);

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
    }

   virtual ~DotFontBase() {}

   // AbstractFont

   virtual FontClass getFontClass() const { return FontHasNoClass; }

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
     ulen len=str.getLen();

     return text(len);
    }

   virtual ulen fit(AbstractSparseString &str,Coord full_dx) const
    {
     ulen len=str.getLen();
     ulen max_len=full_dx/shape.dX();

     return Min(len,max_len);
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


