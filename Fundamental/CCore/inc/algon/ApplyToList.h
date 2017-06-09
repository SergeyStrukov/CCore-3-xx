/* ApplyToList.h */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_algon_ApplyToList_h
#define CCore_inc_algon_ApplyToList_h

#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {
namespace Algon {

/* ApplyToList() */

template <class FuncInit,class ... TT>
auto ApplyToList(FuncInit func_init,TT && ... tt)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  ( (void)func( std::forward<TT>(tt) ) , ... );

  return GetResult(func);
 }

} // namespace Algon
} // namespace CCore

#endif

