/* BestSearch.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_algon_BestSearch_h
#define CCore_inc_algon_BestSearch_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Algon {

/* functions */

template <CursorType R,FuncType<bool,const Meta::PtrObjType<R> &,const Meta::PtrObjType<R> &> Pred>
R BestSearch(R r,Pred better)
 {
  R best=r;

  if( +r )
    for(++r; +r ;++r)
      {
       if( better(*r,*best) ) best=r;
      }

  return best;
 }

template <CursorType R,PtrToOpLessFuncType<R> Func>
R BestSearchGreaterBy(R r,Func by)
 {
  using T = Meta::PtrObjType<R> ;

  return BestSearch(r, [=] (const T &a,const T &b) -> bool { return by(b) < by(a) ; } );
 }

template <CursorType R,PtrToOpLessFuncType<R> Func>
R BestSearchLessBy(R r,Func by)
 {
  using T = Meta::PtrObjType<R> ;

  return BestSearch(r, [=] (const T &a,const T &b) -> bool { return by(a) < by(b) ; } );
 }

} // namespace Algon
} // namespace CCore

#endif

