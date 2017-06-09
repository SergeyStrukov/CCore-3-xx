/* TreeBase.h */
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

#ifndef CCore_inc_tree_TreeBase_h
#define CCore_inc_tree_TreeBase_h

#include <CCore/inc/Cmp.h>

namespace CCore {

/* functions */

void RadixTreeBrokenAbort();

/* concept TreeKeyTypes<K,KRef> */

template <CmpableType K,NothrowCopyCtorType KRef>
concept bool TreeKeyTypes = requires(const K &cobj,KRef a)
 {
  { Cmp(a,cobj) } -> CmpResult ;
 } ;

} // namespace CCore

#endif


