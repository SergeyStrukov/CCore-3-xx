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

} // namespace CCore

#endif

