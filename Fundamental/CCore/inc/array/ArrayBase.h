/* ArrayBase.h */
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

#ifndef CCore_inc_array_ArrayBase_h
#define CCore_inc_array_ArrayBase_h

#include <CCore/inc/array/ArrayAlgo.h>

namespace CCore {

/* words */

enum DoBuildType { DoBuild };

enum DoReserveType { DoReserve };

/* concept ArrayHeaderType<H> */

template <PODType H>
concept bool ArrayHeaderType = requires(H obj,ulen len)
 {
  { &H::len } -> ulen H::* ;

  { &H::maxlen } -> ulen H::* ;

  obj.init(len);

  obj.exit();
 } ;

/* concept BuilderType<Builder,T> */

template <class Builder,class T>
concept bool BuilderType = requires(Meta::ToConst<Builder> &cobj)
 {
  { cobj.getLen() } -> ulen ;

  requires ( FuncInitType<Builder,PtrLen<T>,Place<void> > ) ;
 } ;

/* classes */

template <int Sw> class DoSomething;

template <class T,ArrayHeaderType H,class Algo> struct ArrayBase;

/* class DoSomething<int Sw> */

template <int Sw>
class DoSomething
 {
   ulen len;
   ulen maxlen;

  public:

   explicit DoSomething(ulen len_) : len(len_),maxlen(len_) {}

   DoSomething(ulen len_,ulen maxlen_) : len(len_),maxlen(maxlen_) { GuardLen(len_,maxlen_); }

   ulen getLen() const { return len; }

   ulen getMaxLen() const { return maxlen; }
 };

using DoRaw = DoSomething<1> ;

using DoFill = DoSomething<2> ;

using DoCopy = DoSomething<3> ;

using DoCast = DoSomething<4> ;

using DoSwap = DoSomething<5> ;

using DoCreate = DoSomething<6> ;

/* struct ArrayBase<T,H,Algo> */

template <class T,ArrayHeaderType H,class Algo>
struct ArrayBase
 {
  // placement

  static constexpr ulen Delta = Align(sizeof (H)) ;

  static T * GetPtr(H *ptr) { return PlaceAt(ptr)+Delta; }

  static T * GetSafePtr(H *ptr)
   {
    if( ptr->len ) return PlaceAt(ptr)+Delta;

    return 0;
   }

  static Place<void> GetExtra(H *ptr) { return PlaceAt(ptr)+(Delta+ptr->len*sizeof (T)); }

  static ulen GetExtraLen(H *ptr) { return ptr->maxlen - ptr->len; }

  // basic

  template <ulen MaxLen> requires ( MaxLen>0 )
  static constexpr ulen StaticMemLen = UIntConstAdd<ulen, Delta , UIntConstMul<ulen,MaxLen,sizeof (T)> > ;

  static H * Create(void *mem,ulen maxlen) requires ( ArrayAlgo_core<Algo,T> ) // mem is aligned , maxlen > 0
   {
    H *ret=PlaceAt(mem); // POD

    ret->init(maxlen);

    return ret;
   }

  static H * Alloc(ulen maxlen,ulen mem_len) requires ( ArrayAlgo_core<Algo,T> )
   {
    H *ret=PlaceAt(Algo::MemAlloc(mem_len)); // POD

    ret->init(maxlen);

    return ret;
   }

  static H * Alloc(ulen maxlen) requires ( ArrayAlgo_core<Algo,T> )
   {
    ulen mem_len=LenOf(maxlen,sizeof (T),Delta);

    return Alloc(maxlen,mem_len);
   }

  static void Free(H *ptr) requires ( ArrayAlgo_core<Algo,T> )
   {
    ptr->exit();

    Algo::MemFree(ptr); // POD
   }

  static H * Create(ulen maxlen) requires ( ArrayAlgo_core<Algo,T> )
   {
    if( !maxlen ) maxlen=1;

    return Alloc(maxlen);
   }

  static void Destroy(H *ptr) requires ( NothrowDtorType<T> && ArrayAlgo_core<Algo,T> )
   {
    if( ptr->maxlen )
      {
       Algo::Destroy(GetPtr(ptr),ptr->len);

       Free(ptr);
      }
   }

  static Place<void> MoveAndDestroy(H *ptr,Place<void> place) requires ( ArrayAlgo_move<Algo,T> )
   {
    if( ptr->maxlen )
      {
       ulen len=ptr->len;

       Algo::MoveTo(GetPtr(ptr),len,place);

       Free(ptr);

       return place+len*sizeof(T);
      }

    return place;
   }

  // provide

  static H * Provide_do(H *ptr,ulen extra_len) requires ( ArrayAlgo_core<Algo,T> && (bool)Algo::MoveTo_exist )
   {
    ulen maxlen=Algo::ProvideLen(ptr->len,ptr->maxlen,extra_len);

    ulen mem_len=LenOf(maxlen,sizeof (T),Delta);

    if( Algo::MemExtend(ptr,mem_len) )
      {
       ptr->maxlen=maxlen;

       return ptr;
      }

    H *ret=Alloc(maxlen,mem_len);

    ulen len=ptr->len;

    Algo::MoveTo(GetPtr(ptr),len,PlaceAt(ret)+Delta);

    ret->len=len;

    Free(ptr);

    return ret;
   }

  static H * Provide_do(H *ptr,ulen extra_len) requires ( ArrayAlgo_core<Algo,T> && !Algo::MoveTo_exist )
   {
    GuardArrayOverflow(ptr->len,ptr->maxlen,extra_len);

    return 0;
   }

  static H * Provide_one(H *ptr) requires ( ArrayAlgo_core<Algo,T> ) // provides not default ptr with room for 1 element
   {
    if( GetExtraLen(ptr) ) return ptr;

    if( ptr->maxlen==0 ) return Create(1);

    return Provide_do(ptr,1);
   }

  static H * Provide(H *ptr,ulen extra_len) requires ( ArrayAlgo_core<Algo,T> ) // provides not default ptr with room for extra_len elements
   {
    if( ptr->maxlen==0 ) return Create(extra_len);

    if( extra_len<=GetExtraLen(ptr) ) return ptr;

    return Provide_do(ptr,extra_len);
   }

  // shrink

  static ulen Shrink(H *ptr,ulen delta_len) requires ( NothrowDtorType<T> && ArrayAlgo_core<Algo,T> )
   {
    ulen len=ptr->len;

    if( delta_len>len ) delta_len=len;

    if( delta_len )
      {
       len-=delta_len;

       ptr->len=len;

       Algo::Destroy(GetPtr(ptr)+len,delta_len);
      }

    return delta_len;
   }

  static bool Shrink_one(H *ptr) requires ( NothrowDtorType<T> && ArrayAlgo_core<Algo,T> )
   {
    if( ulen len=ptr->len )
      {
       len--;

       ptr->len=len;

       Algo::Destroy(GetPtr(ptr)+len);

       return true;
      }

    return false;
   }

  static ulen Shrink_all(H *ptr) requires ( NothrowDtorType<T> && ArrayAlgo_core<Algo,T> )
   {
    ulen len=ptr->len;

    if( len )
      {
       ptr->len=0;

       Algo::Destroy(GetPtr(ptr),len);
      }

    return len;
   }

  static void Shrink_extra(H *ptr) requires ( ArrayAlgo_core<Algo,T> )
   {
    ulen maxlen=ptr->len;

    if( !maxlen ) maxlen=1;

    if( maxlen<ptr->maxlen )
      {
       ptr->maxlen=maxlen;

       Algo::MemShrink(ptr,Delta+maxlen*sizeof (T));
      }
   }

  static void Shrink_reserve(H *ptr,ulen maxlen) requires ( ArrayAlgo_core<Algo,T> )
   {
    if( !maxlen ) maxlen=1;

    if( maxlen>=ptr->len && maxlen<ptr->maxlen )
      {
       ptr->maxlen=maxlen;

       Algo::MemShrink(ptr,Delta+maxlen*sizeof (T));
      }
   }

  static void Shrink_reserve(H *ptr) requires ( ArrayAlgo_core<Algo,T> )
   {
    Shrink_reserve(ptr,2*ptr->len+100u);
   }

  // extend : ptr is not default and has enough room for delta_len elements

  static PtrLen<T> Extend_raw(H *ptr,ulen delta_len) requires ( DefaultCtorType<T> && ArrayAlgo_raw<Algo,T> )
   {
    PtrLen<T> ret=Algo::Create_raw(GetExtra(ptr),delta_len);

    ptr->len+=delta_len;

    return ret;
   }

  static PtrLen<T> Extend_default(H *ptr,ulen delta_len) requires ( DefaultCtorType<T> && ArrayAlgo_default<Algo,T> )
   {
    PtrLen<T> ret=Algo::Create_default(GetExtra(ptr),delta_len);

    ptr->len+=delta_len;

    return ret;
   }

  template <class ... SS>
  static PtrLen<T> Extend_fill(H *ptr,ulen delta_len,SS && ... ss) requires ( ConstructibleType<T,SS...> && ArrayAlgo_fill<Algo,T,SS...> )
   {
    PtrLen<T> ret=Algo::Create_fill(GetExtra(ptr),delta_len, std::forward<SS>(ss)... );

    ptr->len+=delta_len;

    return ret;
   }

  static PtrLen<T> Extend_copy(H *ptr,ulen delta_len,const T src[]) requires ( CopyCtorType<T> && ArrayAlgo_copy<Algo,T> )
   {
    PtrLen<T> ret=Algo::Create_copy(GetExtra(ptr),delta_len,src);

    ptr->len+=delta_len;

    return ret;
   }

  template <class S>
  static PtrLen<T> Extend_cast(H *ptr,ulen delta_len,const S src[]) requires ( ConstructibleType<T,const S> && ArrayAlgo_cast<Algo,T,S> )
   {
    PtrLen<T> ret=Algo::Create_cast(GetExtra(ptr),delta_len,src);

    ptr->len+=delta_len;

    return ret;
   }

  static PtrLen<T> Extend_swap(H *ptr,ulen delta_len,T objs[]) requires ( DefaultCtorType<T> && ArrayAlgo_swap<Algo,T> )
   {
    PtrLen<T> ret=Algo::Create_swap(GetExtra(ptr),delta_len,objs);

    ptr->len+=delta_len;

    return ret;
   }

  template <CreatorType<T> Creator>
  static PtrLen<T> Extend(H *ptr,ulen delta_len,Creator creator) requires ( ArrayAlgo_creator<Algo,T,Creator> )
   {
    PtrLen<T> ret=Algo::Create(GetExtra(ptr),delta_len,creator);

    ptr->len+=delta_len;

    return ret;
   }

  template <BuilderType<T> Builder>
  static PtrLen<T> Extend(H *ptr,Builder builder)
   {
    FunctorTypeOf<Builder> func(builder);

    PtrLen<T> ret=func(GetExtra(ptr));

    ptr->len+=ret.len;

    return ret;
   }

  // append : ptr is not default and has enough room for 1 element

  static T * Append_raw(H *ptr) requires ( DefaultCtorType<T> )
   {
    T *ret=new(GetExtra(ptr)) T;

    ptr->len++;

    return ret;
   }

  static T * Append_default(H *ptr) requires ( DefaultCtorType<T> )
   {
    T *ret=new(GetExtra(ptr)) T();

    ptr->len++;

    return ret;
   }

  template <class ... SS>
  static T * Append_fill(H *ptr,SS && ... ss) requires ( ConstructibleType<T,SS...> )
   {
    T *ret=new(GetExtra(ptr)) T( std::forward<SS>(ss)... );

    ptr->len++;

    return ret;
   }

  static T * Append_copy(H *ptr,const T &src) requires ( CopyCtorType<T> )
   {
    T *ret=new(GetExtra(ptr)) T(src);

    ptr->len++;

    return ret;
   }

  static T * Append_swap(H *ptr,T &obj) requires ( DefaultCtorType<T> && ArrayAlgo_swap<Algo,T> )
   {
    T *ret=Algo::Create_swap(GetExtra(ptr),obj);

    ptr->len++;

    return ret;
   }

  template <CreatorType<T> Creator>
  static T * Append(H *ptr,Creator creator)
   {
    FunctorTypeOf<Creator> func(creator);

    T *ret=func(GetExtra(ptr));

    ptr->len++;

    return ret;
   }
 };

} // namespace CCore

#endif


