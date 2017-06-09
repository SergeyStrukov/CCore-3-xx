/* NanoPacket.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_NanoPacket_h
#define CCore_inc_NanoPacket_h

#include <CCore/inc/List.h>
#include <CCore/inc/Move.h>

#include <CCore/inc/task/FastMutex.h>

namespace CCore {

/* functions */

void NanoPacketListExitAbort();

void NanoPacketPoolExitAbort();

/* classes */

template <PODType POD> class NanoPacket;

template <PODType POD> class NanoPacketList;

template <PODType POD> class NanoPacketPool;

/* class NanoPacket<POD> */

template <PODType POD>
class NanoPacket
 {
   using NanoPacketFunction = Function<void (NanoPacket<POD> packet)> ;

   struct Header
    {
     ulen data_len;
     ulen max_data_len;

     NanoPacketFunction free_function;

     DLink<Header> link;

     Header(ulen max_data_len_,NanoPacketFunction free_function_)
      : data_len(0),
        max_data_len(max_data_len_),
        free_function(free_function_)
      {
      }
    };

   static constexpr ulen Delta = Align(sizeof (Header)) ;

   using Algo = typename DLink<Header>::template CircularAlgo<&Header::link> ;

  private:

   Header *ptr;

  private:

   NanoPacket(Header *ptr_) : ptr(ptr_) {}

   friend class NanoPacketList<POD>;

  public:

   // constructors

   static constexpr ulen AllocLen(ulen max_data_len) { return Align(Delta+max_data_len*sizeof (POD)); }

   NanoPacket() noexcept : ptr(0) {}

   NanoPacket(NothingType) : ptr(0) {}

   NanoPacket(Place<void> place,ulen max_data_len,NanoPacketFunction free_function)
    {
     ptr=new(place) Header(max_data_len,free_function);
    }

   // methods

   bool operator + () const { return ptr!=0; }

   bool operator ! () const { return ptr==0; }

   void free()
    {
     auto func=ptr->free_function;

     func(Replace_null(*this));
    }

   // data

   POD * getData() const { return PlaceAt(ptr)+Delta; }

   ulen getDataLen() const { return ptr->data_len; }

   ulen getMaxDataLen() const { return ptr->max_data_len; }

   PtrLen<POD> getRange() const { return Range(getData(),ptr->data_len); }

   PtrLen<POD> getMaxRange() const { return Range(getData(),ptr->max_data_len); }

   PtrLen<POD> setDataLen(ulen len) { ptr->data_len=len; return Range(getData(),len); }
 };

/* class NanoPacketList<POD> */

template <PODType POD>
class NanoPacketList : NoCopy
 {
   typename NanoPacket<POD>::Algo::Top list;

  private:

   void destroy()
    {
     if( +list ) NanoPacketListExitAbort();
    }

  public:

   NanoPacketList() noexcept {}

   ~NanoPacketList() { destroy(); }

   // std move

   NanoPacketList(NanoPacketList<POD> &&obj) noexcept
    : list(Replace_null(obj.list))
    {
    }

   NanoPacketList<POD> & operator = (NanoPacketList<POD> &&obj) noexcept
    {
     if( this!=&obj )
       {
        destroy();

        list=Replace_null(obj.list);
       }

     return *this;
    }

   // methods

   bool operator + () const { return +list; }

   bool operator ! () const { return !list; }

   void put(NanoPacket<POD> packet)
    {
     list.ins_last(packet.ptr);
    }

   void put_first(NanoPacket<POD> packet)
    {
     list.ins_first(packet.ptr);
    }

   NanoPacket<POD> get()
    {
     return list.del_first();
    }

   void freeAll()
    {
     for(;;)
       {
        NanoPacket<POD> packet=get();

        if( !packet ) break;

        packet.free();
       }
    }

   void cleanAll() { list.init(); }

   // swap/move object

   void objSwap(NanoPacketList<POD> &obj)
    {
     Swap(list,obj.list);
    }

   explicit NanoPacketList(ToMoveCtor<NanoPacketList<POD> > obj)
    : list(Replace_null(obj->list))
    {
    }
 };

/* class NanoPacketPool<POD> */

template <PODType POD>
class NanoPacketPool : FastMutexBase , public Funchor
 {
   NanoPacketList<POD> list;

   ulen use_count;

  private:

   virtual void post_free() {}

   void free(NanoPacket<POD> packet)
    {
     packet.setDataLen(0);

     {
      Lock lock(*this);

      list.put_first(packet);

      use_count--;
     }

     post_free();
    }

   Function<void (NanoPacket<POD> packet)> function_free() { return FunctionOf(this,&NanoPacketPool::free); }

  public:

   NanoPacketPool(void *mem,ulen max_data_len,ulen count) // aligned mem,
                                                          // NanoPacket<POD>::AllocLen(max_data_len)*count length
    : use_count(0)
    {
     Place<void> place(mem);

     ulen alloc_len=NanoPacket<POD>::AllocLen(max_data_len);

     auto func=function_free();

     for(ulen cnt=count; cnt ;cnt--,place+=alloc_len)
       {
        NanoPacket<POD> packet(place,max_data_len,func);

        list.put(packet);
       }
    }

   ~NanoPacketPool()
    {
     {
      Lock lock(*this);

      if( use_count ) NanoPacketPoolExitAbort();
     }

     list.cleanAll();
    }

   NanoPacket<POD> try_get()
    {
     Lock lock(*this);

     NanoPacket<POD> ret=list.get();

     if( +ret ) use_count++;

     return ret;
    }
 };

} // namespace CCore

#endif


