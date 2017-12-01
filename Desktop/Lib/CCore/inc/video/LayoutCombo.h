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

/* classes */

template <class ... LL> class LaySet;

template <class ... LL> class LayToTop;

template <class ... LL> class LayToBottom;

template <class ... LL> class LayToLeft;

template <class ... LL> class LayToRight;

template <class L> class ExtLayY;

template <class L> class ExtLayX;

template <class ... LL> class LaySupCenterXExt;

template <class ... LL> class LaySupCenterYExt;

class LayNull;

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

/* class LayToTop<LL> */

template <class ... LL>
class LayToTop : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;

  private:

   static Pane Split(Pane &pane,Coord dy,Coord space)
    {
     Pane ret;

     if( dy<=pane.dy )
       {
        ret=SplitY(pane,dy);

        SplitY(pane,space);
       }
     else
       {
        ret=Replace_null(pane);
       }

     return ret;
    }

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(Coord space) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [space,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space);

                             dy+=s.y;
                             dy+=space;

                             dx=Sup(dx,s.x);

                            } ,

            [space,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space);

                             dy+=s.y;

                             dx=Sup(dx,s.x);

                            } );

     return {dx,dy};
    }

   Point getMinSize(Coord space,Point cap) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [space,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space);

                             dy+=s.y;
                             dy+=space;

                             dx=Sup(dx,s.x);

                            } ,

            [space,cap,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space,cap.subY(+dy));

                             dy+=s.y;

                             dx=Sup(dx,s.x);

                            } );

     return {dx,dy};
    }

   void setPlace(Pane pane,Coord space) const
    {
     apply( [&pane,space] (auto &obj)
                          {
                           Coord dy=obj.getMinSize(space).y;

                           obj.setPlace(Split(pane,dy,space),space);
                          } ,

            [&pane,space] (auto &obj)
                          {
                           obj.setPlace(pane,space);

                          } );
    }
 };

template <class ... LL>
LayToTop(const LL & ...) -> LayToTop<LL...> ;

/* class LayToBottom<LL> */

template <class ... LL>
class LayToBottom : protected LaySet<LL...>
 {
  using LaySet<LL...>::apply;

 private:

  static Pane Split(Pane &pane,Coord dy,Coord space)
   {
    Pane ret;

    if( dy<=pane.dy )
      {
       ret=SplitY(dy,pane);

       SplitY(space,pane);
      }
    else
      {
       ret=Replace_null(pane);
      }

    return ret;
   }

 public:

  using LaySet<LL...>::LaySet;

  Point getMinSize(Coord space) const
   {
    Coordinate dx;
    Coordinate dy;

    apply( [space,&dx,&dy] (auto &obj)
                           {
                            Point s=obj.getMinSize(space);

                            dy+=s.y;
                            dy+=space;

                            dx=Sup(dx,s.x);

                           } ,

           [space,&dx,&dy] (auto &obj)
                           {
                            Point s=obj.getMinSize(space);

                            dy+=s.y;

                            dx=Sup(dx,s.x);

                           } );

    return {dx,dy};
   }

  Point getMinSize(Coord space,Point cap) const
   {
    Coordinate dx;
    Coordinate dy;

    apply( [space,&dx,&dy] (auto &obj)
                           {
                            Point s=obj.getMinSize(space);

                            dy+=s.y;
                            dy+=space;

                            dx=Sup(dx,s.x);

                           } ,

           [space,cap,&dx,&dy] (auto &obj)
                           {
                            Point s=obj.getMinSize(space,cap.subY(+dy));

                            dy+=s.y;

                            dx=Sup(dx,s.x);

                           } );

    return {dx,dy};
   }

  void setPlace(Pane pane,Coord space) const
   {
    apply( [&pane,space] (auto &obj)
                         {
                          Coord dy=obj.getMinSize(space).y;

                          obj.setPlace(Split(pane,dy,space),space);
                         } ,

           [&pane,space] (auto &obj)
                         {
                          obj.setPlace(pane,space);

                         } );
   }
 };

template <class ... LL>
LayToBottom(const LL & ...) -> LayToBottom<LL...> ;

/* class LayToLeft<LL> */

template <class ... LL>
class LayToLeft : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;

  private:

   static Pane Split(Pane &pane,Coord dx,Coord space)
    {
     Pane ret;

     if( dx<=pane.dx )
       {
        ret=SplitY(pane,dx);

        SplitY(pane,space);
       }
     else
       {
        ret=Replace_null(pane);
       }

     return ret;
    }

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(Coord space) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [space,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space);

                             dx+=s.x;
                             dx+=space;

                             dy=Sup(dy,s.y);

                            } ,

            [space,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space);

                             dx+=s.x;

                             dy=Sup(dy,s.y);

                            } );

     return {dx,dy};
    }

   Point getMinSize(Coord space,Point cap) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [space,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space);

                             dx+=s.x;
                             dx+=space;

                             dy=Sup(dy,s.y);

                            } ,

            [space,cap,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space,cap.subX(+dx));

                             dx+=s.x;

                             dy=Sup(dy,s.y);

                            } );

     return {dx,dy};
    }

   void setPlace(Pane pane,Coord space) const
    {
     apply( [&pane,space] (auto &obj)
                          {
                           Coord dx=obj.getMinSize(space).x;

                           obj.setPlace(Split(pane,dx,space),space);
                          } ,

            [&pane,space] (auto &obj)
                          {
                           obj.setPlace(pane,space);

                          } );
    }
 };

template <class ... LL>
LayToLeft(const LL & ...) -> LayToLeft<LL...> ;

/* class LayToRight<LL> */

template <class ... LL>
class LayToRight : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;

  private:

   static Pane Split(Pane &pane,Coord dx,Coord space)
    {
     Pane ret;

     if( dx<=pane.dx )
       {
        ret=SplitY(dx,pane);

        SplitY(space,pane);
       }
     else
       {
        ret=Replace_null(pane);
       }

     return ret;
    }

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(Coord space) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [space,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space);

                             dx+=s.x;
                             dx+=space;

                             dy=Sup(dy,s.y);

                            } ,

            [space,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space);

                             dx+=s.x;

                             dy=Sup(dy,s.y);

                            } );

     return {dx,dy};
    }

   Point getMinSize(Coord space,Point cap) const
    {
     Coordinate dx;
     Coordinate dy;

     apply( [space,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space);

                             dx+=s.x;
                             dx+=space;

                             dy=Sup(dy,s.y);

                            } ,

            [space,cap,&dx,&dy] (auto &obj)
                            {
                             Point s=obj.getMinSize(space,cap.subX(+dx));

                             dx+=s.x;

                             dy=Sup(dy,s.y);

                            } );

     return {dx,dy};
    }

   void setPlace(Pane pane,Coord space) const
    {
     apply( [&pane,space] (auto &obj)
                          {
                           Coord dx=obj.getMinSize(space).x;

                           obj.setPlace(Split(pane,dx,space),space);
                          } ,

            [&pane,space] (auto &obj)
                          {
                           obj.setPlace(pane,space);

                          } );
    }
 };

template <class ... LL>
LayToRight(const LL & ...) -> LayToRight<LL...> ;

/* class ExtLayY<L> */

template <class L>
class ExtLayY
 {
   L lay;

  private:

   static Point Ext(Coord space) { return Point(0,space); }

  public:

   explicit ExtLayY(const L &lay_) : lay(lay_) {}

   Point getMinSize(Coord space) const
    {
     Point s=lay.getMinSize(space);

     return s+2*Ext(space);
    }

   Point getMinSize(Coord space,Point cap) const
    {
     Point delta=2*Ext(space);
     Point s=lay.getMinSize(space,cap-delta);

     return s+delta;
    }

   void setPlace(Pane pane,Coord space) const
    {
     lay.setPlace(pane.shrink(Ext(space)),space);
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

   Point getMinSize(Coord space) const
    {
     Point s=lay.getMinSize(space);

     return s+2*Ext(space);
    }

   Point getMinSize(Coord space,Point cap) const
    {
     Point delta=2*Ext(space);
     Point s=lay.getMinSize(space,cap-delta);

     return s+delta;
    }

   void setPlace(Pane pane,Coord space) const
    {
     lay.setPlace(pane.shrink(Ext(space)),space);
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
   mutable Coord size_space;

  private:

   Point getSize(Coord space) const
    {
     if( has_size && space==size_space ) return size;

     Point s;

     apply( [&s,space] (auto &obj) { s=Sup(s,obj.getMinSize(space)); } );

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

   Point getMinSize(Coord space) const
    {
     Point size=getSize(space);

     auto count=CountToCoordinate(getCount());

     return {count*size.x+(count+1)*space,size.y};
    }

   void setPlace(Pane pane,Coord space) const
    {
     Point size=getSize(space);

     ulen count=getCount();
     Coord dx=size.x;

     Coord off=PosSubMul(pane.dx,count,dx);

     if( count>1 ) off=PosSubMul(off,count-1,space);

     off/=2;

     SplitX(off,pane);

     apply( [&pane,space,dx] (auto &obj)
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

                              obj.setPlace(p,space);
                             } ,

            [&pane,space,dx] (auto &obj)
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

                              obj.setPlace(p,space);

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
   mutable Coord size_space;

  private:

   Point getSize(Coord space) const
    {
     if( has_size && space==size_space ) return size;

     Point s;

     apply( [&s,space] (auto &obj) { s=Sup(s,obj.getMinSize(space)); } );

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

   Point getMinSize(Coord space) const
    {
     Point size=getSize(space);

     auto count=CountToCoordinate(getCount());

     return {size.x,count*size.y+(count+1)*space};
    }

   void setPlace(Pane pane,Coord space) const
    {
     Point size=getSize(space);

     ulen count=getCount();
     Coord dy=size.y;

     Coord off=PosSubMul(pane.dy,count,dy);

     if( count>1 ) off=PosSubMul(off,count-1,space);

     off/=2;

     SplitY(off,pane);

     apply( [&pane,space,dy] (auto &obj)
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

                              obj.setPlace(p,space);
                             } ,

            [&pane,space,dy] (auto &obj)
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

                              obj.setPlace(p,space);

                             } );
    }
 };

/* class LayNull */

class LayNull
 {
  public:

   LayNull() {}

   Point getMinSize(Coord) const { return Null; }

   void setPlace(Pane,Coord) const {}
 };

/* class LayAll<W> */

template <class W>
class LayAll
 {
   W &obj;
   Point s;

  public:

   explicit LayAll(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord) const { return s; }

   void setPlace(Pane pane,Coord) const { obj.setPlace(pane); }
 };

/* class LayExtX<W> */

template <class W>
class LayExtX
 {
   W &obj;
   Point s;

  private:

   static Point Ext(Coord space) { return Point(space,0); }

  public:

   explicit LayExtX(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord space) const { return s+2*Ext(space); }

   void setPlace(Pane pane,Coord space) const { obj.setPlace(pane.shrink(Ext(space))); }
 };

/* class LayExtY<W> */

template <class W>
class LayExtY
 {
   W &obj;
   Point s;

  private:

   static Point Ext(Coord space) { return Point(0,space); }

  public:

   explicit LayExtY(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord space) const { return s+2*Ext(space); }

   void setPlace(Pane pane,Coord space) const { obj.setPlace(pane.shrink(Ext(space))); }
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

   Point getMinSize(Coord space,Point cap) const
    {
     Point delta=2*Ext(space);

     return obj.getMinSize(cap-delta)+delta;
    }

   void setPlace(Pane pane,Coord space) const { obj.setPlace(pane.shrink(Ext(space))); }
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

   Point getMinSize(Coord space,Point cap) const
    {
     Point delta=2*Ext(space);

     return obj.getMinSize(cap-delta)+delta;
    }

   void setPlace(Pane pane,Coord space) const { obj.setPlace(pane.shrink(Ext(space))); }
 };

/* class LayLeft<W> */

template <class W>
class LayLeft
 {
   W &obj;
   Point s;

  public:

   explicit LayLeft(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord) const { return s; }

   void setPlace(Pane pane,Coord) const { obj.setPlace(AlignLeft(pane,s.x)); }
 };

/* class LayCenterX<W> */

template <class W>
class LayCenterX
 {
   W &obj;
   Point s;

  public:

   explicit LayCenterX(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord) const { return s; }

   void setPlace(Pane pane,Coord) const { obj.setPlace(AlignCenterX(pane,s.x)); }
 };

/* class LayRight<W> */

template <class W>
class LayRight
 {
   W &obj;
   Point s;

  public:

   explicit LayRight(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord) const { return s; }

   void setPlace(Pane pane,Coord) const { obj.setPlace(AlignRight(pane,s.x)); }
 };

/* class LayTop<W> */

template <class W>
class LayTop
 {
   W &obj;
   Point s;

  public:

   explicit LayTop(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord) const { return s; }

   void setPlace(Pane pane,Coord) const { obj.setPlace(AlignTop(pane,s.y)); }
 };

/* class LayCenterY<W> */

template <class W>
class LayCenterY
 {
   W &obj;
   Point s;

  public:

   explicit LayCenterY(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord) const { return s; }

   void setPlace(Pane pane,Coord) const { obj.setPlace(AlignCenterY(pane,s.y)); }
 };

/* class LayBottom<W> */

template <class W>
class LayBottom
 {
   W &obj;
   Point s;

  public:

   explicit LayBottom(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord) const { return s; }

   void setPlace(Pane pane,Coord) const { obj.setPlace(AlignBottom(pane,s.y)); }
 };

/* class LayCenterXExt<W> */

template <class W>
class LayCenterXExt
 {
   W &obj;
   Point s;

  public:

   explicit LayCenterXExt(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord space) const { return s+2*Point(space,0); }

   void setPlace(Pane pane,Coord) const { obj.setPlace(AlignCenterX(pane,s.x)); }
 };

/* class LayCenterYExt<W> */

template <class W>
class LayCenterYExt
 {
   W &obj;
   Point s;

  public:

   explicit LayCenterYExt(W &obj_) : obj(obj_) { s=GetMinSize(obj); }

   Point getMinSize(Coord space) const { return s+2*Point(0,space); }

   void setPlace(Pane pane,Coord) const { obj.setPlace(AlignCenterY(pane,s.y)); }
 };

} // namespace Video
} // namespace CCore

#endif

