/* OpAddHelper.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_OpAddHelper_h
#define CCore_inc_gadget_OpAddHelper_h

#include <CCore/inc/gadget/Classification.h>

namespace CCore {

/* classes */

template <class T,T Add(T,T)> struct OpAddHelper;

/* struct OpAddHelper<T,T Add(T,T)> */

template <class T,T Add(T,T)>
struct OpAddHelper
 {
  T val;

  constexpr OpAddHelper(AnyType arg) : val(arg) {}

  constexpr OpAddHelper operator + (OpAddHelper obj) const { return Add(val,obj.val); }
 };

} // namespace CCore

#endif

