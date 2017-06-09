/* ScopeGuard.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_ScopeGuard_h
#define CCore_inc_gadget_ScopeGuard_h

#include <CCore/inc/gadget/NoCopy.h>
#include <CCore/inc/gadget/Classification.h>

namespace CCore {

/* classes */

template <class T> requires ( NothrowDefaultCtorType<T> && NothrowCopyableType<T> ) class DefaultGuard;

template <FuncArgType<> Func> class ScopeGuard;

/* class DefaultGuard<T> */

template <class T> requires ( NothrowDefaultCtorType<T> && NothrowCopyableType<T> )
class DefaultGuard : NoCopy
 {
   T &obj;

  public:

   explicit DefaultGuard(T &obj_) : obj(obj_) {}

   ~DefaultGuard()
    {
     obj=T();
    }
 };

/* class ScopeGuard<Func> */

template <FuncArgType<> Func>
class ScopeGuard : NoCopy
 {
   Func func;

  public:

   explicit ScopeGuard(const Func &func_) : func(func_) {}

   ~ScopeGuard()
    {
     func();
    }
 };

} // namespace CCore

#endif

