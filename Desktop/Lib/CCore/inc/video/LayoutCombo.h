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

/* concept LaySpaceType<L> */

template <class L>
concept bool LaySpaceType = requires(const L &lay,unsigned flags,Coord space)
 {
  { lay.getSpace(flags,space) } -> Coord ;
 } ;

/* Split...() */

Pane SplitToTop(Pane &pane,Coord dy,Coord space);

Pane SplitToBottom(Pane &pane,Coord dy,Coord space);

Pane SplitToLeft(Pane &pane,Coord dx,Coord space);

Pane SplitToRight(Pane &pane,Coord dx,Coord space);

/* Stack...Size() */

inline Point StackXSize(Point s1,Point s2)
 {
  return Point( Coordinate(s1.x)+s2.x , Sup(s1.y,s2.y) );
 }

inline Point StackYSize(Point s1,Point s2)
 {
  return Point( Sup(s1.x,s2.x) , Coordinate(s1.y)+s2.y );
 }

/* GetLaySpace() */

template <class L>
Coord GetLaySpace(const L &,unsigned,Coord space)
 {
  return space;
 }

template <LaySpaceType L>
Coord GetLaySpace(const L &lay,unsigned flags,Coord space)
 {
  return lay.getSpace(flags,space);
 }

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

template <class L> class ExtLay;

template <class L> class ExtLayNoSpace;

template <class ... LL> class LaySupCenterXExt;

template <class ... LL> class LaySupCenterYExt;

class LayNull;

template <class W> class LayBase;

template <class W> class Lay;

template <class W> class LayNoSpace;

template <class W> class LayCap;

template <class W,class T> class LaySpecial;

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

template <class W> class LayBox;

template <class L1,class L2> class LayDivX;

template <class L1,class L2> class LayDivY;

template <class W,class L> class LayInner;

template <class W,class L> class LayInnerSpace;

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

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     return lay.getMinSize(flags,space,cap);
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     Coord dx=lay.getMinSize(flags,space).x;

     lay.setPlace(Func(pane,dx),ClearUpdate(flags),space);
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

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     return lay.getMinSize(flags,space,cap);
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     Coord dy=lay.getMinSize(flags,space).y;

     lay.setPlace(Func(pane,dy),ClearUpdate(flags),space);
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
                                   dy+=GetLaySpace(obj,flags,space);

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
                                   dy+=GetLaySpace(obj,flags,space);

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
     unsigned flags1=ClearUpdate(flags);

     apply( [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Coord dy=obj.getMinSize(flags,space).y;

                                 obj.setPlace(SplitToTop(pane,dy,GetLaySpace(obj,flags,space)),flags1,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 obj.setPlace(pane,flags,space);

                                } );
    }

   template <Pane Func(Pane pane,Coord dx)>
   void alignPlace(Pane pane,unsigned flags,Coord space) const
    {
     unsigned flags1=ClearUpdate(flags);

     apply( [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(SplitToTop(pane,s.y,GetLaySpace(obj,flags,space)),s.x),flags1,space);

                                } ,

            [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(pane,s.x),flags1,space);

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
                                   dy+=GetLaySpace(obj,flags,space);

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
                                   dy+=GetLaySpace(obj,flags,space);

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
     unsigned flags1=ClearUpdate(flags);

     apply( [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Coord dy=obj.getMinSize(flags,space).y;

                                 obj.setPlace(SplitToBottom(pane,dy,GetLaySpace(obj,flags,space)),flags1,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 obj.setPlace(pane,flags,space);

                                } );
    }

   template <Pane Func(Pane pane,Coord dx)>
   void alignPlace(Pane pane,unsigned flags,Coord space) const
    {
     unsigned flags1=ClearUpdate(flags);

     apply( [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(SplitToBottom(pane,s.y,GetLaySpace(obj,flags,space)),s.x),flags1,space);

                                } ,

            [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(pane,s.x),flags1,space);

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
                                   dx+=GetLaySpace(obj,flags,space);

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
                                   dx+=GetLaySpace(obj,flags,space);

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
     unsigned flags1=ClearUpdate(flags);

     apply( [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Coord dx=obj.getMinSize(flags,space).x;

                                 obj.setPlace(SplitToLeft(pane,dx,GetLaySpace(obj,flags,space)),flags1,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 obj.setPlace(pane,flags,space);

                                } );
    }

   template <Pane Func(Pane pane,Coord dy)>
   void alignPlace(Pane pane,unsigned flags,Coord space) const
    {
     unsigned flags1=ClearUpdate(flags);

     apply( [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(SplitToLeft(pane,s.x,GetLaySpace(obj,flags,space)),s.y),flags1,space);

                                } ,

            [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(pane,s.y),flags1,space);

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
                                   dx+=GetLaySpace(obj,flags,space);

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
                                   dx+=GetLaySpace(obj,flags,space);

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
     unsigned flags1=ClearUpdate(flags);

     apply( [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Coord dx=obj.getMinSize(flags,space).x;

                                 obj.setPlace(SplitToRight(pane,dx,GetLaySpace(obj,flags,space)),flags1,space);

                                } ,

            [&pane,flags,space] (auto &obj)
                                {
                                 obj.setPlace(pane,flags,space);

                                } );
    }

   template <Pane Func(Pane pane,Coord dy)>
   void alignPlace(Pane pane,unsigned flags,Coord space) const
    {
     unsigned flags1=ClearUpdate(flags);

     apply( [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(SplitToRight(pane,s.x,GetLaySpace(obj,flags,space)),s.y),flags1,space);

                                } ,

            [&pane,flags,flags1,space] (auto &obj)
                                {
                                 Point s=obj.getMinSize(flags,space);

                                 obj.setPlace(Func(pane,s.y),flags1,space);

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

/* class ExtLay<L> */

template <class L>
class ExtLay
 {
   L lay;

  private:

   static Point Ext(Coord space) { return Point::Diag(space); }

  public:

   explicit ExtLay(const L &lay_) : lay(lay_) {}

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

/* class ExtLayNoSpace<L> */

template <class L>
class ExtLayNoSpace
 {
   L lay;

  private:

   static Point Ext(Coord space) { return Point::Diag(space); }

  public:

   explicit ExtLayNoSpace(const L &lay_) : lay(lay_) {}

   Coord getSpace(unsigned,Coord) const { return 0; }

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

   Point getSize(unsigned &flags,Coord space) const
    {
     if( has_size && space==size_space ) return size;

     Point s;

     apply( [&s,flags,space] (auto &obj) { s=Sup(s,obj.getMinSize(flags,space)); } );

     has_size=true;
     size=s;
     size_space=space;

     flags=ClearUpdate(flags);

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

   Point getSize(unsigned &flags,Coord space) const
    {
     if( has_size && space==size_space ) return size;

     Point s;

     apply( [&s,flags,space] (auto &obj) { s=Sup(s,obj.getMinSize(flags,space)); } );

     has_size=true;
     size=s;
     size_space=space;

     flags=ClearUpdate(flags);

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
   mutable bool ok = false ;
   mutable Point size;

  protected:

   Point get(unsigned flags) const
    {
     if( Change(ok,true) ) size=GetMinSize(flags,obj);

     return size;
    }

   Point get_clear(unsigned &flags) const
    {
     if( Change(ok,true) )
       {
        size=GetMinSize(flags,obj);

        flags=ClearUpdate(flags);
       }

     return size;
    }

   void set(Pane pane,unsigned flags) const { obj.setPlace(pane,flags); }

  public:

   explicit LayBase(W &obj_) : obj(obj_) {}
 };

/* class Lay<W> */

template <class W>
class Lay : LayBase<W>
 {
  public:

   explicit Lay(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { this->set(pane,flags); }
 };

/* class LayNoSpace<W> */

template <class W>
class LayNoSpace : LayBase<W>
 {
  public:

   explicit LayNoSpace(W &obj) : LayBase<W>(obj) {}

   Coord getSpace(unsigned,Coord) const { return 0; }

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { this->set(pane,flags); }
 };

/* class LayCap<W> */

template <class W>
class LayCap
 {
   W &obj;

  public:

   explicit LayCap(W &obj_) : obj(obj_) {}

   Point getMinSize(unsigned flags,Coord,Point cap) const { return obj.getMinSize(flags,cap); }

   void setPlace(Pane pane,unsigned flags,Coord) const { obj.setPlace(pane,flags); }
 };

/* class LaySpecial<W,T> */

template <class W,class T>
class LaySpecial
 {
   W &obj;
   T arg;

  public:

   LaySpecial(W &obj_,T arg_) : obj(obj_),arg(arg_) {}

   Point getMinSize(unsigned flags,Coord) const { return obj.getMinSize(flags,arg); }

   void setPlace(Pane pane,unsigned flags,Coord) const { obj.setPlace(pane,flags); }
 };

/* class LayExtX<W> */

template <class W>
class LayExtX : LayBase<W>
 {
  private:

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
  private:

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

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get_clear(flags); this->set(AlignLeft(pane,s.x),flags); }
 };

/* class LayCenterX<W> */

template <class W>
class LayCenterX : LayBase<W>
 {
  public:

   explicit LayCenterX(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get_clear(flags); this->set(AlignCenterX(pane,s.x),flags); }
 };

/* class LayRight<W> */

template <class W>
class LayRight : LayBase<W>
 {
  public:

   explicit LayRight(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get_clear(flags); this->set(AlignRight(pane,s.x),flags); }
 };

/* class LayTop<W> */

template <class W>
class LayTop : LayBase<W>
 {
  public:

   explicit LayTop(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get_clear(flags); this->set(AlignTop(pane,s.y),flags); }
 };

/* class LayCenterY<W> */

template <class W>
class LayCenterY : LayBase<W>
 {
  public:

   explicit LayCenterY(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get_clear(flags); this->set(AlignCenterY(pane,s.y),flags); }
 };

/* class LayBottom<W> */

template <class W>
class LayBottom : LayBase<W>
 {
  public:

   explicit LayBottom(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord) const { return this->get(flags); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get_clear(flags); this->set(AlignBottom(pane,s.y),flags); }
 };

/* class LayCenterXExt<W> */

template <class W>
class LayCenterXExt : LayBase<W>
 {
  public:

   explicit LayCenterXExt(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord space) const { return this->get(flags)+2*Point(space,0); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get_clear(flags); this->set(AlignCenterX(pane,s.x),flags); }
 };

/* class LayCenterYExt<W> */

template <class W>
class LayCenterYExt : LayBase<W>
 {
  public:

   explicit LayCenterYExt(W &obj) : LayBase<W>(obj) {}

   Point getMinSize(unsigned flags,Coord space) const { return this->get(flags)+2*Point(0,space); }

   void setPlace(Pane pane,unsigned flags,Coord) const { Point s=this->get_clear(flags); this->set(AlignCenterY(pane,s.y),flags); }
 };

/* class LayBox<W> */

template <class W>
class LayBox
 {
   W &box;
   mutable bool ok = false ;
   mutable Coord dxy = 0 ;

  private:

   void cache(unsigned flags) const
    {
     if( Change(ok,true) )
       {
        dxy=box.getMinSize(flags).dxy;
       }
    }

  public:

   explicit LayBox(W &box_) : box(box_) {}

   Coord getSpace(unsigned flags,Coord) const
    {
     cache(flags);

     return BoxSpace(dxy);
    }

   Point getMinSize(unsigned flags,Coord) const
    {
     cache(flags);

     return Point::Diag(dxy);
    }

   void setPlace(Pane pane,unsigned flags,Coord) const { box.setPlace(pane,flags); }
 };

/* ...Boxed...() */

template <class W,class L>
auto BoxedLay(W &box,const L &lay) { return LayToRightCenter(LayBox(box),lay); }

template <class WBox,class W>
auto BoxedWindow(WBox &box,W &obj) { return BoxedLay(box,Lay(obj)); }

template <class L,class W>
auto LayBoxed(const L &lay,W &box) { return LayToLeftCenter(LayBox(box),lay); }

template <class W,class WBox>
auto WindowBoxed(W &obj,WBox &box) { return LayBoxed(Lay(obj),box); }

/* class LayDivX<L1,L2> */

template <class L1,class L2>
class LayDivX
 {
   L1 lay1;
   L2 lay2;
   Ratio div;

  public:

   LayDivX(const L1 &lay1_,const L2 &lay2_,const Ratio &div_) : lay1(lay1_),lay2(lay2_),div(div_) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     Point s1=lay1.getMinSize(flags,space);
     Point s2=lay2.getMinSize(flags,space);

     return StackXSize(s1,s2).addX(space);
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     Coord dx=div*pane.dx;

     lay1.setPlace(SplitToRight(pane,dx,space),flags,space);

     lay2.setPlace(pane,flags,space);
    }
 };

/* class LayDivY<L1,L2> */

template <class L1,class L2>
class LayDivY
 {
   L1 lay1;
   L2 lay2;
   Ratio div;

  public:

   LayDivY(const L1 &lay1_,const L2 &lay2_,const Ratio &div_) : lay1(lay1_),lay2(lay2_),div(div_) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     Point s1=lay1.getMinSize(flags,space);
     Point s2=lay2.getMinSize(flags,space);

     return StackYSize(s1,s2).addY(space);
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     Coord dy=div*pane.dy;

     lay1.setPlace(SplitToBottom(pane,dy,space),flags,space);

     lay2.setPlace(pane,flags,space);
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

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Point delta=obj.getDelta(flags);

     return obj.getMinSize(flags,lay.getMinSize(flags,space,cap-delta)+2*Point::Diag(space));
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     obj.setPlace(pane,flags);

     lay.setPlace(obj.getInner().shrink(space),flags,space);
    }
 };

/* class LayInnerSpace<W,L> */

template <class W,class L>
class LayInnerSpace
 {
   W &obj;
   L lay;
   Point inner_space;

  public:

   LayInnerSpace(W &obj_,const L &lay_,Point inner_space_) : obj(obj_),lay(lay_),inner_space(inner_space_) {}

   LayInnerSpace(W &obj_,const L &lay_,Coord inner_space_) : obj(obj_),lay(lay_),inner_space(Point::Diag(inner_space_)) {}

   Point getMinSize(unsigned flags,Coord space) const
    {
     return obj.getMinSize(flags,lay.getMinSize(flags,space)+2*inner_space);
    }

   Point getMinSize(unsigned flags,Coord space,Point cap) const
    {
     Point delta=obj.getDelta(flags);

     return obj.getMinSize(flags,lay.getMinSize(flags,space,cap-delta)+2*inner_space);
    }

   void setPlace(Pane pane,unsigned flags,Coord space) const
    {
     obj.setPlace(pane,flags);

     lay.setPlace(obj.getInner().shrink(inner_space),flags,space);
    }
 };

} // namespace Video
} // namespace CCore

#endif

