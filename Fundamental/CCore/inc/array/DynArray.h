/* DynArray.h */
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

#ifndef CCore_inc_array_DynArray_h
#define CCore_inc_array_DynArray_h

#include <CCore/inc/array/ArrayBase.h>

#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* classes */

struct DynArrayHeader;

class DefaultDynArrayHeader;

template <class T,class Algo> class DynArrayBase;

template <class T,class Algo=ArrayAlgo<T> > class DynArray;

/* struct DynArrayHeader */

struct DynArrayHeader
 {
  ulen len;
  ulen maxlen;

  void init(ulen maxlen_)
   {
    len=0;
    maxlen=maxlen_;
   }

  void exit()
   {
   }
 };

/* class DefaultDynArrayHeader */

class DefaultDynArrayHeader
 {
   static DynArrayHeader DefaultObject;

   template <class T,class Algo> friend class DynArrayBase;
 };

/* class DynArrayBase<T,Algo> */

template <class T,class Algo>
class DynArrayBase : NoCopy
 {
   friend class DynArray<T,Algo>;

   using Base = ArrayBase<T,DynArrayHeader,Algo> ;

   // data

   DynArrayHeader *ptr;

   // constructors

   DynArrayBase()
    {
     ptr=&DefaultDynArrayHeader::DefaultObject;
    }

   explicit DynArrayBase(DynArrayHeader *&ptr_)
    {
     ptr=Replace(ptr_,&DefaultDynArrayHeader::DefaultObject);
    }

   explicit DynArrayBase(ulen maxlen)
    {
     ptr=Base::Create(maxlen);
    }

   ~DynArrayBase()
    {
     Base::Destroy(ptr);
    }

   // std move

   DynArrayBase(DynArrayBase<T,Algo> &&obj) noexcept
     : DynArrayBase<T,Algo>(obj.ptr)
     {
     }

   DynArrayBase<T,Algo> & operator = (DynArrayBase<T,Algo> &&obj) noexcept
    {
     if( this!=&obj )
       {
        Base::Destroy(Replace(ptr,Replace(obj.ptr,&DefaultDynArrayHeader::DefaultObject)));
       }

     return *this;
    }
 };

/* class DynArray<T,Algo> */

template <class T,class Algo>
class DynArray : DynArrayBase<T,Algo>
 {
   using Base = typename DynArrayBase<T,Algo>::Base ;

   using DynArrayBase<T,Algo>::ptr;

  private:

   DynArrayHeader * provide() // provides not default ptr with room for 1 element
    {
     return ptr=Base::Provide_one(ptr);
    }

   DynArrayHeader * provide(ulen extra_len) // provides not default ptr with room for extra_len elements
    {
     return ptr=Base::Provide(ptr,extra_len);
    }

  public:

   // constructors

   DynArray() noexcept {}

   template <class S>
   explicit DynArray(std::initializer_list<S> il)
    : DynArrayBase<T,Algo>(il.size())
    {
     Base::Extend_cast(ptr,il.size(),il.begin());
    }

   explicit DynArray(ulen len)
    : DynArrayBase<T,Algo>(len)
    {
     Base::Extend_default(ptr,len);
    }

   DynArray(ulen len,ulen maxlen)
    : DynArrayBase<T,Algo>(maxlen)
    {
     GuardLen(len,maxlen);

     Base::Extend_default(ptr,len);
    }

   DynArray(DoReserveType,ulen maxlen)
    : DynArrayBase<T,Algo>(maxlen)
    {
    }

   explicit DynArray(DoRaw dotype)
    : DynArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_raw(ptr,dotype.getLen());
    }

   template <class ... SS>
   explicit DynArray(DoFill dotype,SS && ... ss)
    : DynArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_fill(ptr,dotype.getLen(), std::forward<SS>(ss)... );
    }

   DynArray(DoCopy dotype,const T src[])
    : DynArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_copy(ptr,dotype.getLen(),src);
    }

   template <class S>
   DynArray(DoCast dotype,const S src[])
    : DynArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_cast(ptr,dotype.getLen(),src);
    }

   DynArray(DoSwap dotype,T objs[])
    : DynArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend_swap(ptr,dotype.getLen(),objs);
    }

   DynArray(DoCreate dotype,CreatorType<T> creator)
    : DynArrayBase<T,Algo>(dotype.getMaxLen())
    {
     Base::Extend(ptr,dotype.getLen(),creator);
    }

   DynArray(DoBuildType,BuilderType<T> builder)
    : DynArrayBase<T,Algo>(builder.getLen())
    {
     Base::Extend(ptr,builder);
    }

   ~DynArray() {}

   // std move

   DynArray(DynArray<T,Algo> &&obj) noexcept = default ;

   DynArray<T,Algo> & operator = (DynArray<T,Algo> &&obj) noexcept = default ;

   // range access

   T * getPtr() { return Base::GetSafePtr(ptr); }

   const T * getPtr() const { return Base::GetSafePtr(ptr); }

   const T * getPtr_const() const { return Base::GetSafePtr(ptr); }

   ulen getLen() const { return ptr->len; }

   ulen getMaxLen() const { return ptr->maxlen; }

   ulen getExtraLen() const { return Base::GetExtraLen(ptr); }

   // index access

   T & operator [] (ulen index)
    {
     return Base::GetPtr(ptr)[index];
    }

   const T & operator [] (ulen index) const
    {
     return Base::GetPtr(ptr)[index];
    }

   T & at(ulen index)
    {
     GuardIndex(index,getLen());

     return Base::GetPtr(ptr)[index];
    }

   const T & at(ulen index) const
    {
     GuardIndex(index,getLen());

     return Base::GetPtr(ptr)[index];
    }

   // methods

   void cloneTo(DynArray<T,Algo> &ret) const
    {
     DynArray<T,Algo> temp(DoCopy(getLen(),getMaxLen()),getPtr());

     Swap(ret,temp);
    }

   void reserve(ulen extra_len)
    {
     provide(extra_len);
    }

   void erase()
    {
     DynArray<T,Algo> temp;

     Swap(*this,temp);
    }

   // shrink

   ulen shrink(ulen delta_len)
    {
     return Base::Shrink(ptr,delta_len);
    }

   bool shrink_one()
    {
     return Base::Shrink_one(ptr);
    }

   ulen shrink_all()
    {
     return Base::Shrink_all(ptr);
    }

   void shrink_extra()
    {
     Base::Shrink_extra(ptr);
    }

   void shrink_reserve(ulen maxlen)
    {
     Base::Shrink_reserve(ptr,maxlen);
    }

   void shrink_reserve()
    {
     Base::Shrink_reserve(ptr);
    }

   // extend

   PtrLen<T> extend_raw(ulen delta_len)
    {
     return Base::Extend_raw(provide(delta_len),delta_len);
    }

   PtrLen<T> extend_default(ulen delta_len)
    {
     return Base::Extend_default(provide(delta_len),delta_len);
    }

   template <class ... SS>
   PtrLen<T> extend_fill(ulen delta_len,SS && ... ss)
    {
     return Base::Extend_fill(provide(delta_len),delta_len, std::forward<SS>(ss)... );
    }

   PtrLen<T> extend_copy(ulen delta_len,const T src[])
    {
     return Base::Extend_copy(provide(delta_len),delta_len,src);
    }

   PtrLen<T> extend_copy(PtrLen<const T> src)
    {
     return extend_copy(src.len,src.ptr);
    }

   template <class S>
   PtrLen<T> extend_cast(ulen delta_len,const S src[])
    {
     return Base::Extend_cast(provide(delta_len),delta_len,src);
    }

   template <class S>
   PtrLen<T> extend_cast(PtrLen<const S> src)
    {
     return extend_cast(src.len,src.ptr);
    }

   PtrLen<T> extend_swap(ulen delta_len,T objs[])
    {
     return Base::Extend_swap(provide(delta_len),delta_len,objs);
    }

   PtrLen<T> extend_swap(PtrLen<T> objs)
    {
     return extend_swap(objs.len,objs.ptr);
    }

   PtrLen<T> extend(ulen delta_len,CreatorType<T> creator)
    {
     return Base::Extend(provide(delta_len),delta_len,creator);
    }

   PtrLen<T> extend(BuilderType<T> builder)
    {
     return Base::Extend(provide(builder.getLen()),builder);
    }

   // append

   T * append_raw()
    {
     return Base::Append_raw(provide());
    }

   T * append_default()
    {
     return Base::Append_default(provide());
    }

   template <class ... SS>
   T * append_fill(SS && ... ss)
    {
     return Base::Append_fill(provide(), std::forward<SS>(ss)... );
    }

   T * append_copy(const T &src)
    {
     return Base::Append_copy(provide(),src);
    }

   T * append_swap(T &obj)
    {
     return Base::Append_swap(provide(),obj);
    }

   T * append(CreatorType<T> creator)
    {
     return Base::Append(provide(),creator);
    }

   // apply

   auto apply(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(Range(*this),func_init); }

   auto apply(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(Range(*this),func_init); }

   auto apply_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(Range(*this),func_init); }

   auto applyReverse(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(RangeReverse(*this),func_init); }

   auto applyReverse(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(RangeReverse(*this),func_init); }

   auto applyReverse_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(RangeReverse(*this),func_init); }

   // swap/move objects

   void objSwap(DynArray<T,Algo> &obj)
    {
     Swap(ptr,obj.ptr);
    }

   explicit DynArray(ToMoveCtor<DynArray<T,Algo> > obj)
    : DynArrayBase<T,Algo>(obj->ptr)
    {
    }
 };

/* type MiniDynArray<T> */

template <class T>
using MiniDynArray = DynArray<T,ArrayAlgo_mini<T> > ;

} // namespace CCore

#endif


