/* RangeDel.h */
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

#ifndef CCore_inc_RangeDel_h
#define CCore_inc_RangeDel_h

#include <CCore/inc/Swap.h>

namespace CCore {

/* functions */

bool RangeCopyDel(NothrowCopyableType list[],ulen len,ulen ind)
 {
  if( ind>=len ) return false;

  for(len--; ind<len ;ind++) list[ind]=list[ind+1];

  return true;
 }

bool RangeCopyDel(PtrLen<NothrowCopyableType> range,ulen ind)
 {
  return RangeCopyDel(range.ptr,range.len,ind);
 }

bool RangeSwapDel(AnyType list[],ulen len,ulen ind)
 {
  if( ind>=len ) return false;

  for(len--; ind<len ;ind++) Swap(list[ind],list[ind+1]);

  return true;
 }

bool RangeSwapDel(PtrLen<AnyType> range,ulen ind)
 {
  return RangeSwapDel(range.ptr,range.len,ind);
 }

void RangeCopyDel_guarded(NothrowCopyableType list[],ulen len,ulen ind)
 {
  GuardIndex(ind,len);

  for(len--; ind<len ;ind++) list[ind]=list[ind+1];
 }

void RangeCopyDel_guarded(PtrLen<NothrowCopyableType> range,ulen ind)
 {
  RangeCopyDel_guarded(range.ptr,range.len,ind);
 }

void RangeSwapDel_guarded(AnyType list[],ulen len,ulen ind)
 {
  GuardIndex(ind,len);

  for(len--; ind<len ;ind++) Swap(list[ind],list[ind+1]);
 }

void RangeSwapDel_guarded(PtrLen<AnyType> range,ulen ind)
 {
  RangeSwapDel_guarded(range.ptr,range.len,ind);
 }

} // namespace CCore

#endif

