/* PTPBoot.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#ifndef CCore_inc_net_PTPBoot_h
#define CCore_inc_net_PTPBoot_h

#include <CCore/inc/net/PTPSupport.h>

#include <CCore/inc/net/PTPBootBase.h>

namespace CCore {
namespace Net {
namespace PTPBoot {

/* classes */

struct AllocExt;

struct WriteExt;

struct BootExt;

class BootClient;

class BootInfo;

/* struct AllocExt */

struct AllocExt : ExtBase<ServiceId,FunctionId_Alloc>
 {
  using InputType = AllocInput ;
  using OutputType = AllocOutput ;

  IndexType index;

  void done(const OutputType &output)
   {
    index=output.index;
   }
 };

/* struct WriteExt */

struct WriteExt : ExtBase<ServiceId,FunctionId_Write>
 {
  using InputType = WriteInput ;
  using OutputType = WriteOutput ;

  void done(const OutputType &)
   {
   }
 };

/* struct BootExt */

struct BootExt : ExtBase<ServiceId,FunctionId_Boot>
 {
  using InputType = BootInput ;
  using OutputType = BootOutput ;

  void done(const OutputType &)
   {
   }
 };

/* class BootClient */

class BootClient : public Funchor_nocopy
 {
   ObjHook hook;

   ClientDevice *ptp;

   PacketSet<uint8> pset;
   MSec timeout;

   PacketFormat write_format;

   Atomic status_flag;
   TransStatus status;

   IndexType index;

  private:

   void complete_alloc(PacketHeader *packet);

   PacketFunction function_complete_alloc() { return FunctionOf(this,&BootClient::complete_alloc); }

   void complete_write(PacketHeader *packet);

   PacketFunction function_complete_write() { return FunctionOf(this,&BootClient::complete_write); }

   void complete_boot(PacketHeader *packet);

   PacketFunction function_complete_boot() { return FunctionOf(this,&BootClient::complete_boot); }

  public:

   // constructors

   explicit BootClient(StrLen ptp_dev_name,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);

   ~BootClient();

   // methods

   IndexType alloc(AddressType address,AddressType len);

   void write(IndexType index,AddressType off,PtrLen<const uint8> data);

   void boot(AddressType entry_point,FlagType flags);
 };

/* class BootInfo */

class BootInfo : NoCopy
 {
  protected:

   class Sect : NoCopy
    {
      AddressType address;
      AddressType len;
      DynArray<uint8> data;

     public:

      // constructors

      Sect(AddressType address,AddressType len);

      ~Sect();

      // methods

      AddressType getAddress() const { return address; }

      AddressType getLen() const { return len; }

      PtrLen<const uint8> getData() const { return Range_const(data); }

      void write(AddressType off,PtrLen<const uint8> frame);

      // move object

      explicit Sect(ToMoveCtor<Sect> obj)
       : address(obj->address),
         len(obj->len),
         data(ToMoveCtor(obj->data))
       {
       }
    };

   DynArray<Sect> table;

   AddressType entry_point;
   FlagType flags;

  private:

   IndexType alloc(AddressType address,AddressType len);

   void write(IndexType index,AddressType off,PtrLen<const uint8> data);

   void boot(AddressType entry_point_,FlagType flags_)
    {
     entry_point=entry_point_;
     flags=flags_;
    }

  private:

   virtual void signal_complete()=0;

   virtual void wait_complete()=0;

  public:

   BootInfo();

   ~BootInfo();

   void get(StrLen ptp_server_name,MSec timeout=DefaultTimeout);

   class PTPServerProc;
 };

} // namespace PTPBoot
} // namespace Net
} // namespace CCore

#endif


