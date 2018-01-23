/* PtrLen.h */
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

#ifndef CCore_inc_gadget_PtrLen_h
#define CCore_inc_gadget_PtrLen_h

#include <CCore/inc/gadget/Len.h>
#include <CCore/inc/gadget/Nothing.h>
#include <CCore/inc/gadget/UtilFunc.h>
#include <CCore/inc/gadget/Classification.h>

namespace CCore {

/* functions */

template <class T,class S>
void RangeCopy(T *restrict dst,const S *restrict src,ulen count)
 {
  for(; count ;count--) *(dst++)=*(src++);
 }

template <class T>
void RangeSet(T *restrict dst,T src,ulen count)
 {
  for(; count ;count--) *(dst++)=src;
 }

template <class T>
void RangeSet_null(T *restrict dst,ulen count)
 {
  for(; count ;count--) *(dst++)=T();
 }

template <class T,class S>
ulen RangeMatch(const T *dst,const S *src,ulen count)
 {
  for(ulen cnt=count; cnt ;cnt--)
    if( *(dst++)!=*(src++) )
      return count-cnt;

  return count;
 }

/* classes */

template <class T> struct PtrLen;

struct StrLen;

/* struct PtrLen<T> */

template <class T>
struct PtrLen
 {
  T *ptr;
  ulen len;

  // constructors

  PtrLen() noexcept : ptr(0),len(0) {}

  PtrLen(NothingType) : PtrLen() {}

  PtrLen(T *ptr_,ulen len_) : ptr(ptr_),len(len_) {}

  operator PtrLen<const T>() const { return {ptr,len}; }

  // cursor

  ulen operator + () const { return len; }

  bool operator ! () const { return !len; }

  T & operator * () const { return *ptr; }

  T * operator -> () const { return ptr; }

  void operator ++ () { ptr++; len--; }

  void operator -- () { ptr--; len++; }

  PtrLen<T> operator += (ulen delta) // assume fit(delta)
   {
    PtrLen<T> ret(ptr,delta);

    ptr+=delta;
    len-=delta;

    return ret;
   }

  PtrLen<T> takeup(ulen delta) { return (*this)+=Min(delta,len); }

  T & take()
   {
    T &ret=*ptr;

    ptr++;
    len--;

    return ret;
   }

  PtrLen<T> getFinal() const { return {ptr+len,0}; }

  // fit

  bool fit(ulen length) const { return length<=len; }

  bool fit(ulen off,ulen length) const { return off<=len && length<=(len-off) ; }

  // parts

  PtrLen<T> prefix(ulen length) const { return {ptr,length}; }                     // assume fit(length)

  PtrLen<T> prefix(PtrLen<T> suffix) const { return {ptr,len-suffix.len}; }

  PtrLen<T> suffix(ulen length) const { return {ptr+(len-length),length}; }        // assume fit(length)

  PtrLen<T> part(ulen off,ulen length) const { return {ptr+off,length}; }          // assume fit(off,length)

  PtrLen<T> part(ulen off) const { return {ptr+off,len-off}; }                     // assume fit(off)

  PtrLen<T> inner(ulen off,ulen endoff) const { return {ptr+off,len-off-endoff}; } // assume fit(off,endoff)

  PtrLen<T> safe_part(ulen off,ulen length) const
   {
    if( off>len ) return Null;

    return part(off,Min_cast(length,len-off));
   }

  PtrLen<T> safe_part(ulen off) const
   {
    if( off>len ) return Null;

    return part(off);
   }

  // index access

  T & operator [] (ulen index) const
   {
    return ptr[index];
   }

  T & at(ulen index) const
   {
    GuardIndex(index,len);

    return ptr[index];
   }

  T & back(ulen index) const // 1 is the last
   {
    return ptr[len-index];
   }

  // methods

  template <class S>
  void copyTo(S dst[/* len */]) const { RangeCopy<S,T>(dst,ptr,len); }

  template <class S>
  void copyFrom(const S src[/* len */]) const { RangeCopy<T,S>(ptr,src,len); }

  void copy(const T src[/* len */]) const { RangeCopy<T,T>(ptr,src,len); }

  void set(T src) const { RangeSet<T>(ptr,src,len); }

  void set_null() const { RangeSet_null<T>(ptr,len); }

  template <class S>
  ulen match(const S src[/* len */]) const { return RangeMatch<T,S>(ptr,src,len); }

  template <class S>
  bool equal(const S src[/* len */]) const { return match(src)==len; }

  template <class S>
  bool equal(PtrLen<S> src) const { return len==src.len && equal(src.ptr) ; }

  template <class S>
  bool hasPrefix(PtrLen<S> src) const { return len>=src.len && src.equal(ptr) ; }

  template <class S>
  bool hasSuffix(PtrLen<S> src) const { return len>=src.len && src.equal(ptr+(len-src.len)) ; }

  // begin()/end() support

  bool operator != (ulen end_len) const { return len!=end_len; }
 };

/* struct StrLen */

struct StrLen : PtrLen<const char>
 {
  // constructors

  StrLen() noexcept {}

  StrLen(NothingType) {}

  StrLen(const char *zstr);

  StrLen(PtrLen<const char> str) : PtrLen<const char>(str) {}

  StrLen(PtrLen<char> str) : PtrLen<const char>(str.ptr,str.len) {}

  StrLen(const char *str,ulen len) : PtrLen<const char>(str,len) {}
 };

/* StrLen literal */

inline StrLen operator "" _c (const char *str,ulen len) { return StrLen(str,len); }

/* Range...() */

template <class T>
PtrLen<T> Range(PtrLen<T> a) { return a; }

template <class T,ulen Len>
PtrLen<T> Range(T (&buf)[Len]) { return {buf,Len}; }

template <class T>
PtrLen<T> Range(T *ptr,ulen len) { return {ptr,len}; }

template <class T>
PtrLen<T> Range(T *ptr,T *lim) { return {ptr,Dist(ptr,lim)}; }

template <class T>
PtrLen<const T> Range_const(PtrLen<T> a) { return a; }

template <class T,ulen Len>
PtrLen<const T> Range_const(T (&buf)[Len]) { return {buf,Len}; }

template <class T>
PtrLen<const T> Range_const(T *ptr,ulen len) { return {ptr,len}; }

template <class T>
PtrLen<const T> Range_const(T *ptr,T *lim) { return {ptr,Dist(ptr,lim)}; }

/* Single() */

template <class T>
PtrLen<T> Single(T &obj) { return {&obj,1}; }

/* container Range...() */

auto Range(RangeAccessType &&obj) { return Range(obj.getPtr(),obj.getLen()); }

auto Range_const(const RangeAccessType &obj) { return Range_const(obj.getPtr_const(),obj.getLen()); }

/* const IsPtrLen<R> */

template <class R>
const bool IsPtrLen = false ;

template <class T>
const bool IsPtrLen<PtrLen<T> > = true ;

/* concept RangeableType<T> */

template <class T> // ref extended
concept bool RangeableType = requires(T &obj) { Range(obj); } ;

/* concept TypeRangeableType<T,S> */

template <class T,class S> // T ref extended
concept bool TypeRangeableType = RangeableType<T> && requires(T &obj) { { Range(obj) } -> PtrLen<S> ; } ;

/* concept ConstRangeableType<T> */

template <class T> // ref extended
concept bool ConstRangeableType = requires(Meta::ToConst<T> &cobj) { Range_const(cobj); } ;

/* concept TypeRangeableType<T,S> */

template <class T,class S> // T ref extended
concept bool ConstTypeRangeableType = ConstRangeableType<T> && requires(Meta::ToConst<T> &cobj) { { Range_const(cobj) } -> PtrLen<const S> ; } ;

/* begin()/end() */

auto begin(RangeAccessType &&obj) { return Range(obj.getPtr(),obj.getLen()); }

ulen end(RangeAccessType &&) { return 0; }

template <class T>
PtrLen<T> begin(PtrLen<T> a) { return a; }

template <class T>
ulen end(PtrLen<T>) { return 0; }

/* Mutate...() */

template <CharType T>
T * MutatePtr(void *ptr) { return static_cast<T *>(ptr); }

template <ConstCharType T>
T * MutatePtr(const void *ptr) { return static_cast<T *>(ptr); }

template <class T,class S>
PtrLen<T> Mutate(PtrLen<S> a) { return {MutatePtr<T>(a.ptr),a.len*sizeof (S)}; }

} // namespace CCore

#endif


