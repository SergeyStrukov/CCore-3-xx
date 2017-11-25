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
#include <CCore/inc/algon/BaseRangeAlgo.h>

namespace CCore {
namespace Video {

/* classes */

template <class ... LL> class LaySet;

template <class ... LL> class LayToTop;

template <class ... LL> class LayToTop_ext;

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
     void operator () (const T &t,const TT && ... tt)
      {
       first(t)

       (*this)(tt...);
      }
    };

  public:

   explicit LaySet(const LL & ... list_) : list(list_...) {}

   template <class FirstFunc,class LastFunc>
   void apply(FirstFunc first,LastFunc last) const
    {
     list.call( Call(first,last) );
    }
 };

template <Algon::RangeType R>
class LaySet<R> : Algon::BaseRangeAlgo<R>
 {
   R range;

  public:

   explicit LaySet(const R &range_) : range(range_) {}

   template <class FirstFunc,class LastFunc>
   void apply(FirstFunc first,LastFunc last) const
    {
     if( auto len=GetLen(range) ; len>0 )
       {
        R r=range;

        for(len--; len>0 ;len--,++r) first(*r);

        last(*r);
       }
    }
 };

/* class LayToTop<LL> */

template <class ... LL>
class LayToTop : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(Coord space) const
    {
    }

   void setPlace(Pane pane,Coord space) const
    {
    }
 };

template <class ... LL>
LayToTop(const LL & ...) -> LayToTop<LL...> ;

/* class LayToTop_ext<LL> */

template <class ... LL>
class LayToTop_ext : protected LaySet<LL...>
 {
   using LaySet<LL...>::apply;

  public:

   using LaySet<LL...>::LaySet;

   Point getMinSize(Coord space) const
    {
    }

   void setPlace(Pane pane,Coord space) const
    {
    }
 };

template <class ... LL>
LayToTop_ext(const LL & ...) -> LayToTop_ext<LL...> ;

} // namespace Video
} // namespace CCore

#endif

