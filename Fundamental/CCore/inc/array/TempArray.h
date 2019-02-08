/* TempArray.h */
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

#ifndef CCore_inc_array_TempArray_h
#define CCore_inc_array_TempArray_h

#include <CCore/inc/MemBase.h>

#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* classes */

template <PODType T,ulen StackLen> class TempArray;

/* class TempArray<T,ulen StackLen> */

template <PODType T,ulen StackLen>
class TempArray : NoCopy
 {
   T *ptr; // always at least StackLen items
   ulen len;

   T buf[StackLen];

  private:

   void init(ulen len_) // len_ <= StackLen
    {
     ptr=buf;
     len=len_;
    }

   void alloc(ulen len_) // len_ > StackLen
    {
     ptr=static_cast<T *>(MemAlloc(LenOf(len_,sizeof (T))));

     len=len_;
    }

   void free()
    {
     if( ptr!=buf ) MemFree(ptr);
    }

   void recreate(ulen len_)
    {
     if( len_<=StackLen )
       {
        free();

        init(len_);
       }
     else
       {
        T *old_ptr=ptr;

        alloc(len_);

        if( old_ptr!=buf ) MemFree(old_ptr);
       }
    }

  public:

   // constructors

   TempArray() noexcept { init(0); }

   explicit TempArray(ulen len_)
    {
     if( len_<=StackLen )
       {
        init(len_);
       }
     else
       {
        alloc(len_);
       }
    }

   ~TempArray() { free(); }

   // methods

   bool isEmpty() const { return getLen()==0; }

   bool notEmpty() const { return getLen()!=0; }

   void provide(ulen len_)
    {
     if( len_ > len )
       {
        recreate(len_);
       }
    }

   void reset(ulen len_)
    {
     if( len_ > len )
       {
        recreate(len_);
       }
     else
       {
        len=len_;
       }
    }

   bool extend(ulen len_)
    {
     if( len_<=len ) return false;

     if( len_<=StackLen )
       {
        len=len_;
       }
     else
       {
        T *old_ptr=ptr;
        ulen old_len=len;

        alloc(len_);

        Range(ptr,old_len).copy(old_ptr);

        if( old_ptr!=buf ) MemFree(old_ptr);
       }

     return true;
    }

   void erase()
    {
     free();
     init(0);
    }

   // range access

   T * getPtr() { return ptr; }

   const T * getPtr() const { return ptr; }

   const T * getPtr_const() const { return ptr; }

   ulen getLen() const { return len; }

   // index access

   T & operator [] (ulen index)
    {
     return ptr[index];
    }

   const T & operator [] (ulen index) const
    {
     return ptr[index];
    }

   T & at(ulen index)
    {
     GuardIndex(index,len);

     return ptr[index];
    }

   const T & at(ulen index) const
    {
     GuardIndex(index,len);

     return ptr[index];
    }

   // apply

   auto apply(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(Range(*this),func_init); }

   auto apply(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(Range(*this),func_init); }

   auto apply_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(Range(*this),func_init); }

   auto applyReverse(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(RangeReverse(*this),func_init); }

   auto applyReverse(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(RangeReverse(*this),func_init); }

   auto applyReverse_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(RangeReverse(*this),func_init); }
 };

} // namespace CCore

#endif


