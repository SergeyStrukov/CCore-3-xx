/* Len.h */
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
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_Len_h
#define CCore_inc_gadget_Len_h

#include <CCore/inc/gadget/OpAddHelper.h>

namespace CCore {

/* consts */

inline constexpr ulen TextBufLen = 256 ;

inline constexpr ulen MaxULen = ulen(-1) ;

/* unit functions */

inline constexpr ulen operator "" _KByte (unsigned long long len) { return len*1024u; }

inline constexpr ulen operator "" _MByte (unsigned long long len) { return len*1024u*1024u; }

/* functions */

void GuardLenAddOverflow(ulen len,ulen extra_len);

inline ulen CheckedLenAdd(ulen len,ulen extra_len)
 {
  ulen ret=len+extra_len;

  if( ret<len ) GuardLenAddOverflow(len,extra_len);

  return ret;
 }

ulen LenAdd(AnyType ... args)
 {
  return ( ... + OpAddHelper<ulen,CheckedLenAdd>(args) ).val;
 }

void GuardLenFailed(ulen len,ulen maxlen);

inline void GuardLen(ulen len,ulen maxlen)
 {
  if( len>maxlen ) GuardLenFailed(len,maxlen);
 }

void GuardLenOfOverflow(ulen count,ulen size_of,ulen extra);

inline ulen LenOf(ulen count,ulen size_of,ulen extra=0)
 {
  if( size_of )
    {
     if( count>(MaxULen-extra)/size_of ) GuardLenOfOverflow(count,size_of,extra);

     return count*size_of+extra;
    }

  return extra;
 }

void GuardIndexOutOfRange(ulen index,ulen len);

inline void GuardIndex(ulen index,ulen len)
 {
  if( index>=len ) GuardIndexOutOfRange(index,len);
 }

/* functions */

inline constexpr bool NotAligned(ulen len,ulen A=MaxAlign) { return (len%A)!=0; }

inline constexpr ulen Align(ulen len,ulen A=MaxAlign) { return ((len+A-1)/A)*A; }

inline constexpr ulen AlignDown(ulen len,ulen A=MaxAlign) { return (len/A)*A; }

inline bool TryAlign(ulen &len,ulen A=MaxAlign)
 {
  ulen result=Align(len,A);

  if( len<=result )
    {
     len=result;

     return true;
    }
  else
    {
     return false;
    }
 }

/* functions */

template <class T,ulen Len>
ulen DimOf(T (&)[Len]) { return Len; }

template <class T>
ulen Dist(const T *from,const T *to) { return ulen(to-from); }

} // namespace CCore

#endif


