/* Cmp.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Cmp_h
#define CCore_inc_Cmp_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* enum CmpResult */

enum CmpResult
 {
  CmpLess    = -1,
  CmpEqual   =  0,
  CmpGreater =  1
 };

inline CmpResult operator - (CmpResult cmp) { return CmpResult(-int(cmp)); }

const char * GetTextDesc(CmpResult cmp);

/* concept Has_objCmp<T> */

template <class T>
concept bool Has_objCmp = requires() { { &T::objCmp } -> CmpResult (T::*)(const T &) const ; } ||
                          requires() { { &T::objCmp } -> CmpResult (T::*)(T) const ; } ;

/* concept No_objCmp<T> */

template <class T>
concept bool No_objCmp = !Has_objCmp<T> ;

/* LessCmp() */

template <OpLessType T>
CmpResult LessCmp(const T &a,const T &b)
 {
  return (a<b)?CmpLess:( (b<a)?CmpGreater:CmpEqual );
 }

/* Str...() */

inline CmpResult CharCmp(char a,char b) { return LessCmp((unsigned char)a,(unsigned char)b); }

inline bool CharLess(char a,char b) { return (unsigned char)a<(unsigned char)b; }

CmpResult StrCmp(StrLen a,StrLen b);

bool StrLess(StrLen a,StrLen b);

template <class T>
CmpResult StrCmpOf(const T &a,const T &b) requires( TypeRangeableType<const T,const char> ) { return StrCmp(Range(a),Range(b)); }

template <class T>
bool StrLessOf(const T &a,const T &b) requires( TypeRangeableType<const T,const char> ) { return StrLess(Range(a),Range(b)); }

/* classes */

class CmpAsStr;

template <class T> struct LessComparable;

template <class T> struct CmpComparable;

template <class T> struct CmpAdapter;

/* class CmpAsStr */

class CmpAsStr
 {
   StrLen str;

  public:

   explicit CmpAsStr(StrLen str_) : str(str_) {}

   template <class T>
   explicit CmpAsStr(const T &obj) requires( TypeRangeableType<const T,const char> ) : str(Range(obj)) {}

   // cmp objects

   CmpResult objCmp(CmpAsStr obj) const { return StrCmp(str,obj.str); }

   friend bool operator < (const CmpAsStr &a,const CmpAsStr &b) { return StrLess(a.str,b.str); }

   friend bool operator > (const CmpAsStr &a,const CmpAsStr &b) { return StrLess(b.str,a.str); }

   friend bool operator <= (const CmpAsStr &a,const CmpAsStr &b) { return !StrLess(b.str,a.str); }

   friend bool operator >= (const CmpAsStr &a,const CmpAsStr &b) { return !StrLess(a.str,b.str); }

   friend bool operator == (const CmpAsStr &a,const CmpAsStr &b) { return StrCmp(a.str,b.str)==0; }

   friend bool operator != (const CmpAsStr &a,const CmpAsStr &b) { return StrCmp(a.str,b.str)!=0; }
 };

/* struct LessComparable<T> */

template <class T>
struct LessComparable
 {
  friend bool operator > (const T &a,const T &b) requires ( OpLessType<T> ) { return b<a; }

  friend bool operator <= (const T &a,const T &b) requires ( OpLessType<T> ) { return !(b<a); }

  friend bool operator >= (const T &a,const T &b) requires ( OpLessType<T> ) { return !(a<b); }

  friend bool operator == (const T &a,const T &b) requires ( OpLessType<T> && !OpEqualType<T> ) { return !( a<b || b<a ); }

  friend bool operator != (const T &a,const T &b) requires ( OpLessType<T> && !OpNotEqualType<T> ) { return ( a<b || b<a ); }
 };

/* struct CmpComparable<T> */

template <class T>
struct CmpComparable
 {
  friend bool operator < (const T &a,const T &b) requires ( Has_objCmp<T> ) { return a.objCmp(b)<0; }

  friend bool operator > (const T &a,const T &b) requires ( Has_objCmp<T> ) { return a.objCmp(b)>0; }

  friend bool operator <= (const T &a,const T &b) requires ( Has_objCmp<T> ) { return a.objCmp(b)<=0; }

  friend bool operator >= (const T &a,const T &b) requires ( Has_objCmp<T> ) { return a.objCmp(b)>=0; }

  friend bool operator == (const T &a,const T &b) requires ( Has_objCmp<T> ) { return a.objCmp(b)==0; }

  friend bool operator != (const T &a,const T &b) requires ( Has_objCmp<T> ) { return a.objCmp(b)!=0; }
 };

/* struct CmpAdapter<T> */

template <Has_objCmp T>
struct CmpAdapter<T>
 {
  static CmpResult Cmp(const T &a,const T &b) { return a.objCmp(b); }
 };

template <No_objCmp T> requires ( OpLessType<T> )
struct CmpAdapter<T>
 {
  static CmpResult Cmp(const T &a,const T &b) { return LessCmp(a,b); }
 };

/* Cmp() */

template <class T>
CmpResult Cmp(const T &a,const T &b) requires( Has_objCmp<T> || OpLessType<T> ) { return CmpAdapter<T>::Cmp(a,b); }

/* concept CmpableType<T> */

template <class T> // ref extended
concept bool CmpableType = requires(Meta::ToConst<T> &a,Meta::ToConst<T> &b) { { Cmp(a,b) } -> CmpResult ; } ;

/* AlphaCmp() */

template <class ... TT>
CmpResult AlphaCmpAny(const TT & ... tt);

inline CmpResult AlphaCmp(CmpResult cmp)
 {
  return cmp;
 }

inline CmpResult AlphaCmp(CmpResult cmp1,CmpResult cmp2)
 {
  if( cmp1 ) return cmp1;

  return cmp2;
 }

template <class ... TT>
CmpResult AlphaCmp(CmpResult cmp,const TT & ... tt)
 {
  if( cmp ) return cmp;

  return AlphaCmpAny(tt...);
 }

template <class ... TT>
CmpResult AlphaCmp(CmpResult cmp1,CmpResult cmp2,const TT & ... tt)
 {
  if( cmp1 ) return cmp1;

  if( cmp2 ) return cmp2;

  return AlphaCmpAny(tt...);
 }

template <CmpableType T>
CmpResult AlphaCmp(const T &a,const T &b)
 {
  return Cmp(a,b);
 }

template <CmpableType T,class ... TT>
CmpResult AlphaCmp(const T &a,const T &b,const TT & ... tt)
 {
  if( CmpResult ret=Cmp(a,b) ) return ret;

  return AlphaCmp(tt...);
 }

template <class ... TT>
CmpResult AlphaCmpAny(const TT & ... tt)
 {
  return AlphaCmp(tt...);
 }

/* Range...() */

template <CmpableType T>
CmpResult RangeCmp(const T *a,const T *b,ulen count)
 {
  for(; count ;count--)
    if( CmpResult ret=Cmp(*(a++),*(b++)) )
      return ret;

  return CmpEqual;
 }

template <CmpableType T>
CmpResult RangeCmp(PtrLen<T> a,PtrLen<T> b)
 {
  if( a.len<b.len )
    {
     if( CmpResult ret=RangeCmp(a.ptr,b.ptr,a.len) ) return ret;

     return CmpLess;
    }
  else if( a.len>b.len )
    {
     if( CmpResult ret=RangeCmp(a.ptr,b.ptr,b.len) ) return ret;

     return CmpGreater;
    }
  else
    {
     return RangeCmp(a.ptr,b.ptr,b.len);
    }
 }

template <CmpableType T>
bool RangeLess(PtrLen<T> a,PtrLen<T> b)
 {
  if( a.len<b.len )
    {
     return RangeCmp(a.ptr,b.ptr,a.len) <= 0 ;
    }
  else
    {
     return RangeCmp(a.ptr,b.ptr,b.len) < 0 ;
    }
 }

template <class T>
CmpResult RangeCmpOf(const T &a,const T &b) requires ( RangeableType<const T> ) { return RangeCmp(Range(a),Range(b)); }

template <class T>
bool RangeLessOf(const T &a,const T &b) requires ( RangeableType<const T> ) { return RangeLess(Range(a),Range(b)); }

/* concept ToCmpableFuncType<Func,T> */

template <class Func,class T> // T ref extended
concept bool ToCmpableFuncType = requires(Func func,Meta::ToConst<T> &a,Meta::ToConst<T> &b) { { Cmp(func(a),func(b)) } -> CmpResult ; } ;

/* Range...By() */

template <class T,ToCmpableFuncType<T> Func>
CmpResult RangeCmpBy(const T *a,const T *b,ulen count,Func by)
 {
  for(; count ;count--)
    if( CmpResult ret=Cmp(by(*(a++)),by(*(b++))) )
      return ret;

  return CmpEqual;
 }

template <class T,ToCmpableFuncType<T> Func>
CmpResult RangeCmpBy(PtrLen<T> a,PtrLen<T> b,Func by)
 {
  if( a.len<b.len )
    {
     if( CmpResult ret=RangeCmpBy(a.ptr,b.ptr,a.len,by) ) return ret;

     return CmpLess;
    }
  else if( a.len>b.len )
    {
     if( CmpResult ret=RangeCmpBy(a.ptr,b.ptr,b.len,by) ) return ret;

     return CmpGreater;
    }
  else
    {
     return RangeCmpBy(a.ptr,b.ptr,b.len,by);
    }
 }

template <class T,ToCmpableFuncType<T> Func>
bool RangeLessBy(PtrLen<T> a,PtrLen<T> b,Func by)
 {
  if( a.len<b.len )
    {
     return RangeCmpBy(a.ptr,b.ptr,a.len,by) <= 0 ;
    }
  else
    {
     return RangeCmpBy(a.ptr,b.ptr,b.len,by) < 0 ;
    }
 }

template <class T,class Func> requires ( RangeableType<const T> )
CmpResult RangeCmpOfBy(const T &a,const T &b,Func by) { return RangeCmpBy(Range(a),Range(b),by); }

template <class T,class Func> requires ( RangeableType<const T> )
bool RangeLessOfBy(const T &a,const T &b,Func by) { return RangeLessBy(Range(a),Range(b),by); }

} // namespace CCore

#endif


