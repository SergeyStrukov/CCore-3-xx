/* RefObjectBase.h */
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

#ifndef CCore_inc_RefObjectBase_h
#define CCore_inc_RefObjectBase_h

#include <CCore/inc/RefPtr.h>
#include <CCore/inc/task/Atomic.h>
#include <CCore/inc/MemBase.h>

namespace CCore {

/* classes */

template <class ... TT> class RefObjectBase;

template <class Base,class F,Base * NullObjectPtr()> class RefObjectHook;

/* class RefObjectBase<TT> */

template <class ... TT>
class RefObjectBase : public NoCopyBase<MemBase,TT...>
 {
   Atomic refs;

  public:

   RefObjectBase() { refs=1; }

   virtual ~RefObjectBase() {}

   void incRef() { refs++; }

   bool decRef() { return (refs--)==1; }

   void destroy() noexcept { delete this; }
 };

/* class RefObjectHook<Base,F,Base * NullObjectPtr()> */

template <class Base,class F,Base * NullObjectPtr()>
class RefObjectHook
 {
   RefPtr<Base> ptr;

  protected:

   explicit RefObjectHook(Base *info) : ptr(info) {}

  public:

   RefObjectHook() noexcept
    : ptr(NullObjectPtr())
    {
     ptr->incRef();
    }

   ~RefObjectHook() {}

   F * getPtr() const { return ptr.getPtr(); }

   F * operator -> () const { return ptr.getPtr(); }

   // extra

   template <class T>
   T * castPtr() const { return dynamic_cast<T *>(ptr.getPtr()); }
 };

} // namespace CCore

#endif

