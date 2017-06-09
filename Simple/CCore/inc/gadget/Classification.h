/* Classification.h */
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

#ifndef CCore_inc_gadget_Classification_h
#define CCore_inc_gadget_Classification_h

#include <CCore/inc/gadget/Meta.h>

namespace CCore {

/* simple concepts */

template <class T>
concept bool AnyType = true ;

template <class T>
concept bool NoType = false ;


template <class T>
concept bool UIntType = Meta::IsUInt<T> ;

template <class T>
concept bool SIntType = Meta::IsSInt<T> ;

template <class T>
concept bool S2sIntType = SIntType<T> && Is2sComplementArithmetic ;

template <class T>
concept bool SUIntType = SIntType<T> || UIntType<T> ;


template <class T>
concept bool VoidType = Meta::OneOf<T,void,const void> ;

template <class T>
concept bool ConstCharType = Meta::OneOf<T,const char,const unsigned char> ;

template <class T>
concept bool CharType = ConstCharType<T> || Meta::OneOf<T,char,unsigned char> ;

template <class T>
concept bool ULenType = Meta::IsSame<T,ulen> ;

template <class T,class S>
concept bool IsType = Meta::IsSame<T,S> ;

template <class T,class ... TT>
concept bool OneOfTypes = Meta::OneOf<T,TT...> ;

template <class T,class S>
concept bool IsDerivedFrom = Meta::IsBaseOf<S,T> ;


template <class T>
concept bool EnumType = Meta::IsEnum<T> ;

template <class T>
concept bool ClassType = Meta::IsClass<T> ;

template <class T>
concept bool PODType = Meta::IsPOD<T> ;


template <class T>
concept bool NothrowDtorType = Meta::HasNothrowDtor<T> ;

template <class T>
concept bool TrivDtorType = NothrowDtorType<T> && Meta::HasTrivDtor<T> ;

template <class T>
concept bool DefaultCtorType = Meta::HasDefaultCtor<T> ;

template <class T>
concept bool NothrowDefaultCtorType = DefaultCtorType<T> && Meta::HasNothrowDefaultCtor<T> ;

template <class T>
concept bool MoveCtorType = Meta::HasMoveCtor<T> ;

template <class T>
concept bool CopyCtorType = Meta::HasCopyCtor<T> ;

template <class T>
concept bool NothrowCopyCtorType = CopyCtorType<T> && Meta::HasNothrowCopyCtor<T> ;

template <class T>
concept bool MovableType = Meta::IsMovable<T> ;

template <class T>
concept bool CopyableType = Meta::IsCopyable<T> ;

template <class T>
concept bool NothrowCopyableType = CopyableType<T> && Meta::IsNothrowCopyable<T> ;

/* complex concepts */

/* concept ConstructibleType<T,SS> */

template <class T,class ... SS>
concept bool ConstructibleType = requires(SS && ... ss) { T( std::forward<SS>(ss)... ); } ;

/* concept FuncArgType<Func,AA> */

template <class Func,class ... AA>
concept bool FuncArgType = requires(Func func,AA && ... aa) { func( std::forward<AA>(aa)... ); } ;

/* concept FuncType<Func,R,AA> */

template <class Func,class R,class ... AA>
concept bool FuncType = FuncArgType<Func,AA...> && requires(Func func,AA && ... aa) { { func( std::forward<AA>(aa)... ) } -> R ; } ;

/* concept OpLessType<T> */

template <class T> // ref extended
concept bool OpLessType = requires(Meta::ToConst<T> &a,Meta::ToConst<T> &b) { { a < b } -> bool ; } ;

/* concept OpEqualType<T> */

template <class T> // ref extended
concept bool OpEqualType = requires(Meta::ToConst<T> &a,Meta::ToConst<T> &b) { { a == b } -> bool ; } ;

/* concept OpNotEqualType<T> */

template <class T> // ref extended
concept bool OpNotEqualType = requires(Meta::ToConst<T> &a,Meta::ToConst<T> &b) { { a != b } -> bool ; } ;

/* concept OpCmpType<T> */

template <class T> // ref extended
concept bool OpCmpType = requires(Meta::ToConst<T> &a,Meta::ToConst<T> &b)
 {
  { a <  b } -> bool ;
  { a <= b } -> bool ;
  { a >  b } -> bool ;
  { a >= b } -> bool ;
  { a == b } -> bool ;
  { a != b } -> bool ;
 } ;

/* concept OpLessTypes<T,S> */

template <class T,class S> // ref extended
concept bool OpLessTypes = requires(Meta::ToConst<T> &a,Meta::ToConst<S> &b) { { a < b } -> bool ; } ;

/* concept OpLessEqualTypes<T,S> */

template <class T,class S> // ref extended
concept bool OpLessEqualTypes = requires(Meta::ToConst<T> &a,Meta::ToConst<S> &b) { { a <= b } -> bool ; } ;

/* concept OpGreaterTypes<T,S> */

template <class T,class S> // ref extended
concept bool OpGreaterTypes = requires(Meta::ToConst<T> &a,Meta::ToConst<S> &b) { { a > b } -> bool ; } ;

/* concept OpGreaterEqualTypes<T,S> */

template <class T,class S> // ref extended
concept bool OpGreaterEqualTypes = requires(Meta::ToConst<T> &a,Meta::ToConst<S> &b) { { a >= b } -> bool ; } ;

/* concept NullableType<T> */

template <NothrowDefaultCtorType T> // ref extended
concept bool NullableType = requires(Meta::ToConst<T> &cobj)
 {
  { +cobj } -> bool ;

  { !cobj } -> bool ;
 } ;

/* concept IndirectOverType<P,T> */

template <class P,class T> // P ref extended
concept bool IndirectOverType = requires(Meta::ToConst<P> &cobj)
 {
  { *cobj } -> T ;
 } ;

/* concept IndirectCastType<P,T> */

template <class P,class T> // P ref extended
concept bool IndirectCastType = requires(Meta::ToConst<P> &cobj)
 {
  T(*cobj);
 } ;

/* concept RangeAccessType<T> */

template <class T,class T1,class T2> requires ( Meta::IsSame<T1,T2> && Meta::OneOf<T1,T,const T> )
void RangeAccessHelper(T *,T1 *,T2 *,ULenType) {}

template <class T> // ref extended
concept bool RangeAccessType = requires(T &obj,Meta::ToConst<T> &cobj)
 {
  RangeAccessHelper(obj.getPtr(),cobj.getPtr_const(),cobj.getPtr(),cobj.getLen());
 } ;

/* concept CursorType<R> */

template <NothrowCopyableType R>
concept bool CursorType = NullableType<R> && requires(R &obj,Meta::ToConst<R> &cobj)
 {
  *cobj;

  cobj.operator -> () ;

  ++obj;
 } ;

/* concept CursorOverType<R,T> */

template <CursorType R,class T>
concept bool CursorOverType = IndirectOverType<R,T> ;

/* concept CursorCastType<R,T> */

template <CursorType R,class T>
concept bool CursorCastType = IndirectCastType<R,T> ;

/* concept RecursorType<R> */

template <NothrowCopyableType R>
concept bool RecursorType = NullableType<R> && requires(Meta::ToConst<R> &cobj)
 {
  *cobj;

  cobj.operator -> () ;

  { cobj.prev() } -> R ;

  { cobj.next() } -> R ;
 } ;

/* concept RecursorOverType<R,T> */

template <RecursorType R,class T>
concept bool RecursorOverType = IndirectOverType<R,T> ;

/* concept RecursorOverType<R,T> */

template <RecursorType R,class T>
concept bool RecursorCastType = IndirectCastType<R,T> ;

/* concept RanType<Ran> */

template <NothrowCopyableType Ran>
concept bool RanType = NothrowDefaultCtorType<Ran> && OpCmpType<Ran> && requires(Ran ptr,ulen len)
 {
  *ptr;

  ptr++;
  ptr--;

  ++ptr;
  --ptr;

  { ptr+len } -> Ran ;

  ptr+=len;

  { ptr-len } -> Ran ;

  ptr-=len;

  { ptr-ptr } -> ulen ;

  ptr[len];
 } ;

/* concept ToOpNotEqualFuncType<Func,T> */

template <class Func,class T>
concept bool ToOpNotEqualFuncType = requires(Func func,Meta::ToConst<T> &a,Meta::ToConst<T> &b)
 {
  { func(a)!=func(b) } -> bool ;
 } ;

/* concept ToOpLessFuncType<Func,T> */

template <class Func,class T>
concept bool ToOpLessFuncType = requires(Func func,Meta::ToConst<T> &a,Meta::ToConst<T> &b)
 {
  { func(a)<func(b) } -> bool ;
 } ;

/* concept PtrToOpLessFuncType<Func,Ptr> */

template <class Func,class Ptr>
concept bool PtrToOpLessFuncType = ToOpLessFuncType<Func,Meta::PtrObjType<Ptr> > ;

/* concept PrinterType<P> */

template <class P>
concept bool PrinterType = requires(P &out,char ch,ulen len,const char *str)
 {
  typename P::PrintOutType;

  { out.printRef() } -> typename P::PrintOutType ;

  out.put(ch);

  out.put(ch,len);

  out.put(str,len);

  out.flush();
 } ;

/* concept ScannerType<S> */

template <class S>
concept bool ScannerType = requires(S &obj,const S &cobj)
 {
  typename S::ScanInpType;

  { obj.scanRef() } -> typename S::ScanInpType ;

  { +cobj } -> bool ;

  { !cobj } -> bool ;

  { *cobj } -> char ;

  ++obj;

  { cobj.isOk() } -> bool ;

  { cobj.isFailed() } -> bool ;

  obj.fail();
 } ;

} // namespace CCore

#endif

