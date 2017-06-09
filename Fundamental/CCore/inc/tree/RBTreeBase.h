/* RBTreeBase.h */
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

#ifndef CCore_inc_tree_RBTreeBase_h
#define CCore_inc_tree_RBTreeBase_h

#include <CCore/inc/Cmp.h>

namespace CCore {

/* concept RBTreeKeyTypes<K,KRef> */

template <CmpableType K,NothrowCopyCtorType KRef>
concept bool RBTreeKeyTypes = requires(const K &cobj,KRef a)
 {
  { Cmp(a,cobj) } -> CmpResult ;
 } ;

/* concept CopyKeyTypes<K,KRef> */

template <class K,class KRef>
concept bool CopyKeyTypes = requires(K &key,KRef ref)
 {
  { key=ref } noexcept ;
 } ;

/* functions */

void GuardRBTreeCheckFailed(const char *text);

inline void GuardRBTreeCheck(bool cond,const char *text)
 {
  if( !cond ) GuardRBTreeCheckFailed(text);
 }

template <class K,class KRef>
void DoCopyKey(K &key,KRef ref) requires ( CopyKeyTypes<K,KRef> ) { key=ref; }

template <class K,class KRef>
void NoCopyKey(K &,KRef) {}

/* classes */

//enum RBFlag;

/* enum RBFlag */

enum RBFlag
 {
  RBFlag_BlackBlack,
  RBFlag_HiRed,
  RBFlag_LoRed,
  RBFlag_RedRed
 };

inline RBFlag operator | (RBFlag a,RBFlag b) { return RBFlag(unsigned(a)|unsigned(b)); }

inline RBFlag operator |= (RBFlag &a,RBFlag b) { return a=(a|b); }

inline RBFlag operator ^ (RBFlag a,RBFlag b) { return RBFlag(unsigned(a)^unsigned(b)); }

inline RBFlag operator ^= (RBFlag &a,RBFlag b) { return a=(a^b); }

const char * GetTextDesc(RBFlag flag);

} // namespace CCore

#endif


