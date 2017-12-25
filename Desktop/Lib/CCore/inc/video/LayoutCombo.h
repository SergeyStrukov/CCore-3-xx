/* LayoutCombo.h */
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

#ifndef CCore_inc_video_LayoutCombo_h
#define CCore_inc_video_LayoutCombo_h

#include <CCore/inc/video/Layout.h>

#include <CCore/inc/Tuple.h>

namespace CCore {
namespace Video {

/* concept LayRangeType<R> */

template <NothrowCopyCtorType R>
concept bool LayRangeType = requires(R r)
 {
  typename R::AdapterType;

  { r.getLen() } -> ulen ;

  +r;

  ++r;

  *r;

  (typename R::AdapterType)(*r);

 } ;

/* Split...() */

Pane SplitToTop(Pane &pane,Coord dy,Coord space);

Pane SplitToBottom(Pane &pane,Coord dy,Coord space);

Pane SplitToLeft(Pane &pane,Coord dx,Coord space);

Pane SplitToRight(Pane &pane,Coord dx,Coord space);

Pane SplitBox(Pane &pane,Coord dx);

Pane SplitBoxRight(Pane &pane,Coord dx);

/* classes */

template <class ... LL> class LaySet;

template <class ... LL> class LaySame;

template <class L,Pane Func(Pane pane,Coord dx)> class LayAlignX;

template <class L,Pane Func(Pane pane,Coord dy)> class LayAlignY;

template <class ... LL> class LayToTop;

template <class ... LL> class LayToTopCenter;

template <class ... LL> class LayToTopLeft;

template <class ... LL> class LayToTopRight;

template <class ... LL> class LayToBottom;

template <class ... LL> class LayToBottomCenter;

template <class ... LL> class LayToBottomLeft;

template <class ... LL> class LayToBottomRight;

template <class ... LL> class LayToLeft;

template <class ... LL> class LayToLeftCenter;

template <class ... LL> class LayToLeftTop;

template <class ... LL> class LayToLeftBottom;

template <class ... LL> class LayToRight;

template <class ... LL> class LayToRightCenter;

template <class ... LL> class LayToRightTop;

template <class ... LL> class LayToRightBottom;

template <class L> class ExtLayY;

template <class L> class ExtLayX;

template <class ... LL> class LaySupCenterXExt;

template <class ... LL> class LaySupCenterYExt;

class LayNull;

template <class W> class LayBase;

template <class W> class LayAll;

template <class W> class LayExtX;

template <class W> class LayExtY;

template <class W> class LayExtXCap;

template <class W> class LayExtYCap;

template <class W> class LayLeft;

template <class W> class LayCenterX;

template <class W> class LayRight;

template <class W> class LayTop;

template <class W> class LayCenterY;

template <class W> class LayBottom;

template <class W> class LayCenterXExt;

template <class W> class LayCenterYExt;

template <class WBox,class W> class LayBox;

template <class WBox,class L> class LayBoxLay;

template <class WBox,class W> class LayBoxRight;

template <class WBox,class L> class LayBoxRightLay;

template <class W,class L> class LayInner;

/* class LaySet<LL> */

template <class ... LL>
class LaySet
 {
   Tuple<LL...> list;

  private:

   template <class FirstFunc,class LastFunc>
   struct Call
    {
     FirstFunc first;
     LastFunc last;

     Call(const FirstFunc &first_,const LastFunc &last_) : first(first_),last(last_) {}

     template <class T>
     void operator () (const T &t)
      {
       last(t);
      }

     template <class T,class ... TT>
     void operator () (const T &t,const TT & ... tt)
      {
       first(t);

       (*this)(tt...);
      }
    };

   template <class Func>
   struct CallSame
    {
     Func func;

     explicit CallSame(const Func &func_) : func(func_) {}

     template <class T>
     void operator () (const T &t)
      {
       func(t);
      }

     template <class T,class ... TT>
     void operator () (const T &t,const TT & ... tt)
      {
       func(t);

       (*this)(tt...);
      }
    };

  public:

   explicit LaySet(const LL & ... list_) : list(list_...) {}

   ulen getCount() const { return sizeof ... (LL); }

   template <class FirstFunc,class LastFunc>
   void apply(FirstFunc first,LastFunc last) const
    {
     list.call( Call<FirstFunc,LastFunc>(first,last) );
    }

   template <class Func>
   void apply(Func func) const
    {
     list.call( CallSame<Func>(func) );
    }
 };

template <LayRangeType R>
class LaySet<R>
 {
   R range;

   using L = typename R::AdapterType ;

  public:

   explicit LaySet(const R &range_) : range(range_) {}

   ulen getCount() const { return range.getLen(); }

   template <class FirstFunc,class LastFunc>
   void apply(FirstFunc first,LastFunc last) const
    {
     if( auto len=range.getLen() ; len>0 )
       {
        R r(range);

        for(len--; len>0 ;len--,++r)
          {
           L obj(*r);

           first(obj);
          }

        {
         L obj(*r);

         last(obj);
        }
       }
    }

   template <class Func>
   void apply(Func func) const
    {
     R r(range);

     for(; +r ;++r)
       {
        L obj(*r);

        func(obj);
       }
    }
 };

/* class LaySame<LL> */

template <class ... LL>
class LaySame : protected LaySet<LL...>
 {
  protected:

   using LaySet<LL...>::apply;

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(unsigned flags,Coord space) const
    {
     Point ret;

     apply( [flags,space,&ret] (auto &obj)
                               {
                                Point s=obj.getMinSize(flags,space);

                                ret=Sup(ret,s);

                               } );

     return ret;
    }

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Point ret;

     apply( [flags,space,cap,&ret] (auto &obj)
                                   {
                                    Point s=obj.getMinSize(flags,space,cap);

                                    ret=Sup(ret,s);

                                   } );

     return ret;
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     apply( [&pane,flags,space] (auto &obj)
                                {
                                 obj.setPlace(pane,flags,space);

                                } );
    }
 };

template <class ... LL>
LaySame(const LL & ...) -> LaySame<LL...> ;

/* class LayAlignX<L,Func> */

template <class L,Pane Func(Pane pane,Coord dx)>
class LayAlignX
 {
   L lay;

  public:

   explicit LayAlignX(const L &lay_) : lay(lay_) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     return lay.getMinSize(flags,space);
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     Coord dx=lay.getMinSize(flags,space).x;

     lay.setPlace(Func(pane,dx),flags,space);
    }
 };

template <class L>
auto LayAlignLeft(const L &lay) { return LayAlignX<L,AlignLeft>(lay); }

template <class L>
auto LayAlignCenterX(const L &lay) { return LayAlignX<L,AlignCenterX>(lay); }

template <class L>
auto LayAlignRight(const L &lay) { return LayAlignX<L,AlignRight>(lay); }

/* class LayAlignY<L,Func> */

template <class L,Pane Func(Pane pane,Coord dy)>
class LayAlignY
 {
   L lay;

  public:

   explicit LayAlignY(const L &lay_) : lay(lay_) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     return lay.getMinSize(flags,space);
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     Coord dy=lay.getMinSize(flags,space).y;

     lay.setPlace(Func(pane,dy),flags,space);
    }
 };

template <class L>
auto LayAlignTop(const L &lay) { return LayAlignY<L,AlignTop>(lay); }

template <class L>
auto LayAlignCenterY(const L &lay) { return LayAlignY<L,AlignCenterY>(lay); }

template <class L>
auto LayAlignBottom(const L &lay) { return LayAlignY<L,AlignBottom>(lay); }

/* class LayToTop<LL> */

template <class ... LL>
class LayToTop : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(unsigned flags,Coord space) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dy+=s.y;
                                   dy+=space;

                                   dx=Sup(dx,s.x);

                                  } ,

            [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dy+=s.y;

                                   dx=Sup(dx,s.x);

                                  } );

     return {dx,dy};
    }

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dy+=s.y;
                                   dy+=space;

                                   dx=Sup(dx,s.x);

                                  } ,

            [flags,space,cap,&dx,&dy] (auto &obj)
                                      {
                                       Point s=obj.getMinSize(flags,space,cap.subY(+dy));

                                       dy+=s.y;

                                       dx=Sup(dx,s.x);

                                      } );

     return {dx,dy};
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     apply( [&pane,flags,space] (auto &obj)
                                {
                                 Coord dy=obj.getMinSize(flags,space).y;

                                 obj.setPlace(SplitToTop(pane,dy,space),flags,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 obj.setPlace(pane,flags,space);

                                } );
    }

   template <Pane Func(Pane pane,Coord dx)>
   void alignPlace(Pane pane,unsigned flags,Coord space) const
    {
     apply( [&pane,flags,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(SplitToTop(pane,s.y,space),s.x),flags,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(pane,s.x),flags,space);

                                } );
    }
 };

template <class ... LL>
LayToTop(const LL & ...) -> LayToTop<LL...> ;

/* class LayToTopCenter<LL> */

template <class ... LL>
class LayToTopCenter : public LayToTop<LL...>
 {
  public:

   using LayToTop<LL...>::LayToTop;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignCenterX>(pane,flags,space);
    }
 };

template <class ... LL>
LayToTopCenter(const LL & ...) -> LayToTopCenter<LL...> ;

/* class LayToTopLeft<LL> */

template <class ... LL>
class LayToTopLeft : public LayToTop<LL...>
 {
  public:

   using LayToTop<LL...>::LayToTop;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignLeft>(pane,flags,space);
    }
 };

template <class ... LL>
LayToTopLeft(const LL & ...) -> LayToTopLeft<LL...> ;

/* class LayToTopRight<LL> */

template <class ... LL>
class LayToTopRight : public LayToTop<LL...>
 {
  public:

   using LayToTop<LL...>::LayToTop;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignRight>(pane,flags,space);
    }
 };

template <class ... LL>
LayToTopRight(const LL & ...) -> LayToTopRight<LL...> ;

/* class LayToBottom<LL> */

template <class ... LL>
class LayToBottom : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(unsigned flags,Coord space) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dy+=s.y;
                                   dy+=space;

                                   dx=Sup(dx,s.x);

                                  } ,

            [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dy+=s.y;

                                   dx=Sup(dx,s.x);

                                  } );

     return {dx,dy};
    }

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dy+=s.y;
                                   dy+=space;

                                   dx=Sup(dx,s.x);

                                  } ,

            [flags,space,cap,&dx,&dy] (auto &obj)
                                      {
                                       Point s=obj.getMinSize(flags,space,cap.subY(+dy));

                                       dy+=s.y;

                                       dx=Sup(dx,s.x);

                                      } );

     return {dx,dy};
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     apply( [&pane,flags,space] (auto &obj)
                                {
                                 Coord dy=obj.getMinSize(flags,space).y;

                                 obj.setPlace(SplitToBottom(pane,dy,space),flags,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 obj.setPlace(pane,flags,space);

                                } );
    }

   template <Pane Func(Pane pane,Coord dx)>
   void alignPlace(Pane pane,unsigned flags,Coord space) const
    {
     apply( [&pane,flags,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(SplitToBottom(pane,s.y,space),s.x),flags,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(pane,s.x),flags,space);

                                } );
    }
 };

template <class ... LL>
LayToBottom(const LL & ...) -> LayToBottom<LL...> ;

/* class LayToBottomCenter<LL> */

template <class ... LL>
class LayToBottomCenter : public LayToBottom<LL...>
 {
  public:

   using LayToBottom<LL...>::LayToBottom;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignCenterX>(pane,flags,space);
    }
 };

template <class ... LL>
LayToBottomCenter(const LL & ...) -> LayToBottomCenter<LL...> ;

/* class LayToBottomLeft<LL> */

template <class ... LL>
class LayToBottomLeft : public LayToBottom<LL...>
 {
  public:

   using LayToBottom<LL...>::LayToBottom;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignLeft>(pane,flags,space);
    }
 };

template <class ... LL>
LayToBottomLeft(const LL & ...) -> LayToBottomLeft<LL...> ;

/* class LayToBottomRight<LL> */

template <class ... LL>
class LayToBottomRight : public LayToBottom<LL...>
 {
  public:

   using LayToBottom<LL...>::LayToBottom;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignRight>(pane,flags,space);
    }
 };

template <class ... LL>
LayToBottomRight(const LL & ...) -> LayToBottomRight<LL...> ;

/* class LayToLeft<LL> */

template <class ... LL>
class LayToLeft : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(unsigned flags,Coord space) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dx+=s.x;
                                   dx+=space;

                                   dy=Sup(dy,s.y);

                                  } ,

            [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dx+=s.x;

                                   dy=Sup(dy,s.y);

                                  } );

     return {dx,dy};
    }

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dx+=s.x;
                                   dx+=space;

                                   dy=Sup(dy,s.y);

                                  } ,

            [flags,space,cap,&dx,&dy] (auto &obj)
                                      {
                                       Point s=obj.getMinSize(flags,space,cap.subX(+dx));

                                       dx+=s.x;

                                       dy=Sup(dy,s.y);

                                      } );

     return {dx,dy};
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     apply( [&pane,flags,space] (auto &obj)
                                {
                                 Coord dx=obj.getMinSize(flags,space).x;

                                 obj.setPlace(SplitToLeft(pane,dx,space),flags,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 obj.setPlace(pane,flags,space);

                                } );
    }

   template <Pane Func(Pane pane,Coord dy)>
   void alignPlace(Pane pane,unsigned flags,Coord space) const
    {
     apply( [&pane,flags,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(SplitToLeft(pane,s.x,space),s.y),flags,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(pane,s.y),flags,space);

                                } );
    }
 };

template <class ... LL>
LayToLeft(const LL & ...) -> LayToLeft<LL...> ;

/* class LayToLeftCenter<LL> */

template <class ... LL>
class LayToLeftCenter : public LayToLeft<LL...>
 {
  public:

   using LayToLeft<LL...>::LayToLeft;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignCenterY>(pane,flags,space);
    }
 };

template <class ... LL>
LayToLeftCenter(const LL & ...) -> LayToLeftCenter<LL...> ;

/* class LayToLeftTop<LL> */

template <class ... LL>
class LayToLeftTop : public LayToLeft<LL...>
 {
  public:

   using LayToLeft<LL...>::LayToLeft;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignTop>(pane,flags,space);
    }
 };

template <class ... LL>
LayToLeftTop(const LL & ...) -> LayToLeftTop<LL...> ;

/* class LayToLeftBottom<LL> */

template <class ... LL>
class LayToLeftBottom : public LayToLeft<LL...>
 {
  public:

   using LayToLeft<LL...>::LayToLeft;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignBottom>(pane,flags,space);
    }
 };

template <class ... LL>
LayToLeftBottom(const LL & ...) -> LayToLeftBottom<LL...> ;

/* class LayToRight<LL> */

template <class ... LL>
class LayToRight : protected LaySet<LL...>
 {
  protected:

   using LaySet<LL...>::apply;

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(unsigned flags,Coord space) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dx+=s.x;
                                   dx+=space;

                                   dy=Sup(dy,s.y);

                                  } ,

            [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dx+=s.x;

                                   dy=Sup(dy,s.y);

                                  } );

     return {dx,dy};
    }

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [flags,space,&dx,&dy] (auto &obj)
                                  {
                                   Point s=obj.getMinSize(flags,space);

                                   dx+=s.x;
                                   dx+=space;

                                   dy=Sup(dy,s.y);

                                  } ,

            [flags,space,cap,&dx,&dy] (auto &obj)
                                      {
                                       Point s=obj.getMinSize(flags,space,cap.subX(+dx));

                                       dx+=s.x;

                                       dy=Sup(dy,s.y);

                                      } );

     return {dx,dy};
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     apply( [&pane,flags,space] (auto &obj)
                                {
                                 Coord dx=obj.getMinSize(flags,space).x;

                                 obj.setPlace(SplitToRight(pane,dx,space),flags,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 obj.setPlace(pane,flags,space);

                                } );
    }

   template <Pane Func(Pane pane,Coord dy)>
   void alignPlace(Pane pane,unsigned flags,Coord space) const
    {
     apply( [&pane,flags,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(SplitToRight(pane,s.x,space),s.y),flags,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(pane,s.y),flags,space);

                                } );
    }
 };

template <class ... LL>
LayToRight(const LL & ...) -> LayToRight<LL...> ;

/* class LayToRightCenter<LL> */

template <class ... LL>
class LayToRightCenter : public LayToRight<LL...>
 {
  public:

   using LayToRight<LL...>::LayToRight;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignCenterY>(pane,flags,space);
    }
 };

template <class ... LL>
LayToRightCenter(const LL & ...) -> LayToRightCenter<LL...> ;

/* class LayToRightTop<LL> */

template <class ... LL>
class LayToRightTop : public LayToRight<LL...>
 {
  public:

   using LayToRight<LL...>::LayToRight;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignTop>(pane,flags,space);
    }
 };

template <class ... LL>
LayToRightTop(const LL & ...) -> LayToRightTop<LL...> ;

/* class LayToRightBottom<LL> */

template <class ... LL>
class LayToRightBottom : public LayToRight<LL...>
 {
  public:

   using LayToRight<LL...>::LayToRight;

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     this->template alignPlace<AlignBottom>(pane,flags,space);
    }
 };

template <class ... LL>
LayToRightBottom(const LL & ...) -> LayToRightBottom<LL...> ;

/* class ExtLayY<L> */

template <class L>
class ExtLayY
 {
   L lay;

  private:

   static Point Ext(Coord space) { return Point(0,space); }

  public:

   explicit ExtLayY(const L &lay_) : lay(lay_) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     Point s=lay.getMinSize(flags,space);

     return s+2*Ext(space);
    }

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Point delta=2*Ext(space);
     Point s=lay.getMinSize(flags,space,cap-delta);

     return s+delta;
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     lay.setPlace(pane.shrink(Ext(space)),flags,space);
    }
 };

/* class ExtLayX<L> */

template <class L>
class ExtLayX
 {
   L lay;

  private:

   static Point Ext(Coord space) { return Point(space,0); }

  public:

   explicit ExtLayX(const L &lay_) : lay(lay_) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     Point s=lay.getMinSize(flags,space);

     return s+2*Ext(space);
    }

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Point delta=2*Ext(space);
     Point s=lay.getMinSize(flags,space,cap-delta);

     return s+delta;
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     lay.setPlace(pane.shrink(Ext(space)),flags,space);
    }
 };

/* class LaySupCenterXExt<LL> */

template <class ... LL>
class LaySupCenterXExt : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;
   using LaySet<LL...>::getCount;

   mutable bool has_size = false ;
   mutable Point size;
   mutable Coord size_space = 0 ;

  private:

   Point getSize(unsigned flags,Coord space) const
    {
     if( has_size && space==size_space ) return size;

     Point s;

     apply( [&s,flags,space] (auto &obj) { s=Sup(s,obj.getMinSize(flags,space)); } );

     has_size=true;
     size=s;
     size_space=space;

     return s;
    }

  public:

   explicit LaySupCenterXExt(const LL & ... list)
    : LaySet<LL...>(list...)
    {
    }

   Point getMinSize(unsigned flags,Coord space) const
    {
     Point size=getSize(flags,space);

     auto count=CountToCoordinate(getCount());

     return {count*size.x+(count+1)*space,size.y};
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     Point size=getSize(flags,space);

     ulen count=getCount();
     Coord dx=size.x;

     Coord off=PosSubMul(pane.dx,count,dx);

     if( count>1 ) off=PosSubMul(off,count-1,space);

     off/=2;

     SplitX(off,pane);

     apply( [&pane,flags,space,dx] (auto &obj)
                                   {
                                    Pane p;

                                    if( dx<=pane.dx )
                                      {
                                       p=SplitX(dx,pane);

                                       SplitX(space,pane);
                                      }
                                    else
                                      {
                                       p=Replace_null(pane);
                                      }

                                    obj.setPlace(p,flags,space);
                                   } ,

            [&pane,flags,space,dx] (auto &obj)
                                   {
                                    Pane p;

                                    if( dx<=pane.dx )
                                      {
                                       p=SplitX(dx,pane);
                                      }
                                    else
                                      {
                                       p=Replace_null(pane);
                                      }

                                    obj.setPlace(p,flags,space);

                                   } );
    }
 };

/* class LaySupCenterYExt<LL> */

template <class ... LL>
class LaySupCenterYExt : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;
   using LaySet<LL...>::getCount;

   mutable bool has_size = false ;
   mutable Point size;
   mutable Coord size_space = 0 ;

  private:

   Point getSize(unsigned flags,Coord space) const
    {
     if( has_size && space==size_space ) return size;

     Point s;

     apply( [&s,flags,space] (auto &obj) { s=Sup(s,obj.getMinSize(flags,space)); } );

     has_size=true;
     size=s;
     size_space=space;

     return s;
    }

  public:

   explicit LaySupCenterYExt(const LL & ... list)
    : LaySet<LL...>(list...)
    {
    }

   Point getMinSize(unsigned flags,Coord space) const
    {
     Point size=getSize(flags,space);

     auto count=CountToCoordinate(getCount());

     return {size.x,count*size.y+(count+1)*space};
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     Point size=getSize(flags,space);

     ulen count=getCount();
     Coord dy=size.y;

     Coord off=PosSubMul(pane.dy,count,dy);

     if( count>1 ) off=PosSubMul(off,count-1,space);

     off/=2;

     SplitY(off,pane);

     apply( [&pane,flags,space,dy] (auto &obj)
                                   {
                                    Pane p;

                                    if( dy<=pane.dy )
                                      {
                                       p=SplitY(dy,pane);

                                       SplitY(space,pane);
                                      }
                                    else
                                      {
                                       p=Replace_null(pane);
                                      }

                                    obj.setPlace(p,flags,space);
                                   } ,

            [&pane,flags,space,dy] (auto &obj)
                                   {
                                    Pane p;

                                    if( dy<=pane.dy )
                                      {
                                       p=SplitY(dy,pane);
                                      }
                                    else
                                      {
                                       p=Replace_null(pane);
                                      }

                                    obj.setPlace(p,flags,space);

                                   } );
    }
 };

/* class LayNull */

class LayNull
 {
  public:

   LayNull() {}

   Point getMinSize(unsigned,Coord) const { return Null; }

   void setPlace(Pane,unsigned,Coord) const {}
 };

/* class LayBase<W> */

template <class W>
class LayBase
 {
   W &obj;
   mutable unsigned flags = 0 ;
   mutable Point s;

  protected:

   Point get(unsigned flags_) const
    {
     if( Change(flags,flags_) ) s=GetMinSize(flags_,obj);

     return s;
    }

   void set(Pane pane,unsigned flags) const { obj.setPlace(pane,flags); }

  public:

   explicit LayBase(W &obj_) : obj(obj_) {}
 };

/* class LayAll<W> */

template <class W>
class LayAll : LayBase<W>
 {
  public:

   explicit LayAll(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { this->set(pane,flags); }
 };

template <class W>
auto Lay(W &obj) { return LayAll(obj); }

/* class LayExtX<W> */

template <class W>
class LayExtX : LayBase<W>
 {
   static Point Ext(Coord space) { return Point(space,0); }

  public:

   explicit LayExtX(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord space) const { return this->get(flags)+2*Ext(space); }

   void setPlace(Pane pane,unsigned flags,Coord space) const { this->set(pane.shrink(Ext(space)),flags); }
 };

/* class LayExtY<W> */

template <class W>
class LayExtY : LayBase<W>
 {
   static Point Ext(Coord space) { return Point(0,space); }

  public:

   explicit LayExtY(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord space) const { return this->get(flags)+2*Ext(space); }

   void setPlace(Pane pane,unsigned flags,Coord space) const { this->set(pane.shrink(Ext(space)),flags); }
 };

/* class LayExtXCap<W> */

template <class W>
class LayExtXCap
 {
   W &obj;

  private:

   static Point Ext(Coord space) { return Point(space,0); }

  public:

   explicit LayExtXCap(W &obj_) : obj(obj_) {}

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Point delta=2*Ext(space);

     return obj.getMinSize(flags,cap-delta)+delta;
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const { obj.setPlace(pane.shrink(Ext(space)),flags); }
 };

/* class LayExtYCap<W> */

template <class W>
class LayExtYCap
 {
   W &obj;

  private:

   static Point Ext(Coord space) { return Point(0,space); }

  public:

   explicit LayExtYCap(W &obj_) : obj(obj_) {}

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Point delta=2*Ext(space);

     return obj.getMinSize(flags,cap-delta)+delta;
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const { obj.setPlace(pane.shrink(Ext(space)),flags); }
 };

/* class LayLeft<W> */

template <class W>
class LayLeft : LayBase<W>
 {
  public:

   explicit LayLeft(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get(flags); this->set(AlignLeft(pane,s.x),flags); }
 };

/* class LayCenterX<W> */

template <class W>
class LayCenterX : LayBase<W>
 {
  public:

   explicit LayCenterX(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get(flags); this->set(AlignCenterX(pane,s.x),flags); }
 };

/* class LayRight<W> */

template <class W>
class LayRight : LayBase<W>
 {
  public:

   explicit LayRight(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get(flags); this->set(AlignRight(pane,s.x),flags); }
 };

/* class LayTop<W> */

template <class W>
class LayTop : LayBase<W>
 {
  public:

   explicit LayTop(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get(flags); this->set(AlignTop(pane,s.y),flags); }
 };

/* class LayCenterY<W> */

template <class W>
class LayCenterY : LayBase<W>
 {
  public:

   explicit LayCenterY(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get(flags); this->set(AlignCenterY(pane,s.y),flags); }
 };

/* class LayBottom<W> */

template <class W>
class LayBottom : LayBase<W>
 {
  public:

   explicit LayBottom(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get(flags); this->set(AlignBottom(pane,s.y),flags); }
 };

/* class LayCenterXExt<W> */

template <class W>
class LayCenterXExt : LayBase<W>
 {
  public:

   explicit LayCenterXExt(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord space) const { return this->get(flags)+2*Point(space,0); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get(flags); this->set(AlignCenterX(pane,s.x),flags); }
 };

/* class LayCenterYExt<W> */

template <class W>
class LayCenterYExt : LayBase<W>
 {
  public:

   explicit LayCenterYExt(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord space) const { return this->get(flags)+2*Point(0,space); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get(flags); this->set(AlignCenterY(pane,s.y),flags); }
 };

/* class LayBox<WBox,W> */

template <class WBox,class W>
class LayBox
 {
   WBox &box;
   W &obj;
   mutable unsigned flags = 0 ;
   mutable Coordinate dxy;
   mutable Point s;

  private:

   void cache(unsigned flags_) const
    {
     if( Change(flags,flags_) )
       {
        dxy=box.getMinSize(flags_).dxy;
        s=GetMinSize(flags_,obj);
       }
    }

  public:

   LayBox(WBox &box_,W &obj_) : box(box_),obj(obj_) {}

   Point getMinSize(unsigned flags,Coord) const
    {
     cache(flags);

     return Point( BoxExt(dxy)+s.x , Sup(dxy,s.y) );
    }

   void setPlace(Pane pane,unsigned flags,Coord) const
    {
     cache(flags);

     box.setPlace(AlignCenterY(SplitBox(pane,+dxy),+dxy),flags);

     obj.setPlace(AlignCenterY(pane,s.y),flags);
    }
 };

/* class LayBoxLay<WBox,L> */

template <class WBox,class L>
class LayBoxLay
 {
   WBox &box;
   L lay;
   mutable unsigned flags = 0 ;
   mutable Coordinate dxy;

  private:

   void cache(unsigned flags_) const
    {
     if( Change(flags,flags_) )
       {
        dxy=box.getMinSize(flags_).dxy;
       }
    }

  public:

   LayBoxLay(WBox &box_,const L &lay_) : box(box_),lay(lay_) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     cache(flags);

     Point s=lay.getMinSize(flags,space);

     return Point( BoxExt(dxy)+s.x , Sup(dxy,s.y) );
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     cache(flags);

     Point s=lay.getMinSize(flags,space);

     box.setPlace(AlignCenterY(SplitBox(pane,+dxy),+dxy),flags);

     lay.setPlace(AlignCenterY(pane,s.y),flags,space);
    }
 };

/* class LayBoxRight<WBox,W> */

template <class WBox,class W>
class LayBoxRight
 {
   WBox &box;
   W &obj;
   mutable unsigned flags = 0 ;
   mutable Coordinate dxy;
   mutable Point s;

  private:

   void cache(unsigned flags_) const
    {
     if( Change(flags,flags_) )
       {
        dxy=box.getMinSize(flags_).dxy;
        s=GetMinSize(flags_,obj);
       }
    }

  public:

   LayBoxRight(WBox &box_,W &obj_) : box(box_),obj(obj_) {}

   Point getMinSize(unsigned flags,Coord) const
    {
     cache(flags);

     return Point( BoxExt(dxy)+s.x , Sup(dxy,s.y) );
    }

   void setPlace(Pane pane,unsigned flags,Coord) const
    {
     cache(flags);

     box.setPlace(AlignCenterY(SplitBoxRight(pane,+dxy),+dxy),flags);

     obj.setPlace(AlignCenterY(pane,s.y),flags);
    }
 };

/* class LayBoxRightLay<WBox,L> */

template <class WBox,class L>
class LayBoxRightLay
 {
   WBox &box;
   L lay;
   mutable unsigned flags = 0 ;
   mutable Coordinate dxy;

  private:

   void cache(unsigned flags_) const
    {
     if( Change(flags,flags_) )
       {
        dxy=box.getMinSize(flags_).dxy;
       }
    }

  public:

   LayBoxRightLay(WBox &box_,const L &lay_) : box(box_),lay(lay_) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     cache(flags);

     Point s=lay.getMinSize(flags,space);

     return Point( BoxExt(dxy)+s.x , Sup(dxy,s.y) );
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     cache(flags);

     Point s=lay.getMinSize(flags,space);

     box.setPlace(AlignCenterY(SplitBoxRight(pane,+dxy),+dxy),flags);

     lay.setPlace(AlignCenterY(pane,s.y),flags,space);
    }
 };

/* class LayInner<W,L> */

template <class W,class L>
class LayInner
 {
   W &obj;
   L lay;

  public:

   LayInner(W &obj_,const L &lay_) : obj(obj_),lay(lay_) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     return obj.getMinSize(flags,lay.getMinSize(flags,space)+2*Point::Diag(space));
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     obj.setPlace(pane,flags);

     lay.setPlace(obj.getInner().shrink(space),flags,space);
    }
 };

} // namespace Video
} // namespace CCore

#endif

