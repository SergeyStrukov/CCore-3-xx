/* ApplyToRange.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_algon_ApplyToRange_h
#define CCore_inc_algon_ApplyToRange_h

#include <CCore/inc/FunctorType.h>

namespace CCore {
namespace Algon {

/* concept Has_getResult<T> */

template <class T>
concept bool Has_getResult = requires(T &obj) { obj.getResult(); } ;

/* concept No_getResult<T> */

template <class T>
concept bool No_getResult = !Has_getResult<T> ;

/* GetResult() */

auto GetResult(Has_getResult &obj) { return obj.getResult(); }

void GetResult(No_getResult &) {}

/* ApplyToRange() */

template <CursorType R,FuncInitArgType<Meta::PtrObjType<R> &> FuncInit>
auto ApplyToRange(R r,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  for(; +r ;++r) func(*r);

  return GetResult(func);
 }

template <CursorType R,FuncInitType<bool,Meta::PtrObjType<R> &> FuncInit>
auto ApplyToRange(R r,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  for(; +r ;++r) if( !func(*r) ) break;

  return GetResult(func);
 }

template <class R,class Func>
void ApplyToRange_rec(R r,Func &func)
 {
  if( +r )
    {
     ApplyToRange_rec(r.prev(),func);

     func(*r);

     ApplyToRange_rec(r.next(),func);
    }
 }

template <RecursorType R,FuncInitArgType<Meta::PtrObjType<R> &> FuncInit>
auto ApplyToRange(R r,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  ApplyToRange_rec(r,func);

  return GetResult(func);
 }

template <class R,class Func>
bool CondApplyToRange_rec(R r,Func &func)
 {
  if( +r )
    {
     if( !CondApplyToRange_rec(r.prev(),func) ) return false;

     if( !func(*r) ) return false;

     if( !CondApplyToRange_rec(r.next(),func) ) return false;
    }

  return true;
 }

template <RecursorType R,FuncInitType<bool,Meta::PtrObjType<R> &> FuncInit>
auto ApplyToRange(R r,FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  CondApplyToRange_rec(r,func);

  return GetResult(func);
 }

} // namespace Algon
} // namespace CCore

#endif


