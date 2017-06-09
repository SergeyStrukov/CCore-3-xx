/* NetFork.h */
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

#ifndef CCore_inc_net_NetFork_h
#define CCore_inc_net_NetFork_h

#include <CCore/inc/net/PacketEndpointDevice.h>

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/AttachmentHost.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/Fifo.h>
#include <CCore/inc/Array.h>

namespace CCore {
namespace Net {

/* classes */

template <class T> class NetForkQueue;

class EndpointNetFork;

class MultipointNetFork;

/* class NetForkQueue<T> */

template <class T>
class NetForkQueue
 {
   DynArray<T> buf;
   Fifo<T> fifo;

  public:

   explicit NetForkQueue(ulen queue_len)
    : buf(queue_len),
      fifo(Range(buf))
    {
    }

   ~NetForkQueue() {}

   bool operator + () const { return !fifo.isEmpty(); }

   bool operator ! () const { return fifo.isEmpty(); }

   bool put(const T &item) { return fifo.put(item); }

   T get() // non-empty
    {
     T ret;

     fifo.get_swap(ret);

     return ret;
    }
 };

/* class EndpointNetFork */

class EndpointNetFork : public ObjBase , public PacketEndpointDevice
 {
   ObjHook hook;

   struct Item
    {
     Packet<uint8> packet;
     PtrLen<const uint8> data;

     Item() noexcept {}

     Item(Packet<uint8> packet_,PtrLen<const uint8> data_) : packet(packet_),data(data_) {}
    };

   using Queue = NetForkQueue<Item> ;

   class Engine : NoCopy , public InboundProc , public ConnectionProc
    {
      PacketEndpointDevice *ep;

      AttachmentHost<InboundProc> host;

      Sem sem;
      Mutex mutex;
      Atomic stop_flag;

      Queue queue;

      AntiSem asem;

     private:

      using Hook = AttachmentHost<InboundProc>::Hook ;

      void work(Item item);

      void work();

     public:

      Engine(PacketEndpointDevice *ep,ulen queue_len);

      ~Engine();

      PacketEndpointDevice * getEPDevice() const { return ep; }

      void attach(InboundProc *proc);

      void detach();

      template <class ... TT>
      void run(ulen task_count,TT ... tt)
       {
        while( task_count-- )
          {
           asem.inc();

           RunFuncTask( [this] () { work(); } ,asem.function_dec(),tt...);
          }
       }

      // InboundProc

      virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);

      virtual void tick();

      // ConnectionProc

      virtual void connection_lost();

      virtual void connection_close();
    };

   Engine engine;

  private:

   EndpointNetFork(StrLen ep_dev_name,ulen queue_len);

  public:

   template <class ... TT>
   EndpointNetFork(StrLen ep_dev_name,ulen task_count,ulen queue_len,TT ... tt)
    : EndpointNetFork(ep_dev_name,queue_len)
    {
     engine.run(task_count,tt...);
    }

   virtual ~EndpointNetFork();

   // InterfaceHost

   virtual void requestInterface(InterfaceCaster &caster);

   // PacketEndpointDevice

   virtual PacketFormat getOutboundFormat() const;

   virtual void outbound(Packet<uint8> packet);

   virtual ulen getMaxInboundLen() const;

   virtual void attach(InboundProc *proc);

   virtual void detach();
 };

/* class MultipointNetFork */

class MultipointNetFork : public ObjBase , public PacketMultipointDevice
 {
   ObjHook hook;

   struct Item
    {
     XPoint point;
     Packet<uint8> packet;
     PtrLen<const uint8> data;

     Item() noexcept {}

     Item(XPoint point_,Packet<uint8> packet_,PtrLen<const uint8> data_) : point(point_),packet(packet_),data(data_) {}
    };

   using Queue = NetForkQueue<Item> ;

   class Engine : NoCopy , public InboundProc , public ConnectionProc
    {
      PacketMultipointDevice *mp;

      AttachmentHost<InboundProc> host;

      Sem sem;
      Mutex mutex;
      Atomic stop_flag;

      Queue queue;

      AntiSem asem;

     private:

      using Hook = AttachmentHost<InboundProc>::Hook ;

      void work(Item item);

      void work();

     public:

      Engine(PacketMultipointDevice *mp,ulen queue_len);

      ~Engine();

      PacketMultipointDevice * getMPDevice() const { return mp; }

      void attach(InboundProc *proc);

      void detach();

      template <class ... TT>
      void run(ulen task_count,TT ... tt)
       {
        while( task_count-- )
          {
           asem.inc();

           RunFuncTask( [this] () { work(); } ,asem.function_dec(),tt...);
          }
       }

      // InboundProc

      virtual void inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data);

      virtual void tick();

      // ConnectionProc

      virtual void connection_open(XPoint point);

      virtual void connection_lost(XPoint point);

      virtual void connection_close(XPoint point);
    };

   Engine engine;

  private:

   MultipointNetFork(StrLen mp_dev_name,ulen queue_len);

  public:

   template <class ... TT>
   MultipointNetFork(StrLen mp_dev_name,ulen task_count,ulen queue_len,TT ... tt)
    : MultipointNetFork(mp_dev_name,queue_len)
    {
     engine.run(task_count,tt...);
    }

   virtual ~MultipointNetFork();

   // InterfaceHost

   virtual void requestInterface(InterfaceCaster &caster);

   // PacketMultipointDevice

   virtual StrLen toText(XPoint point,PtrLen<char> buf) const;

   virtual PacketFormat getOutboundFormat() const;

   virtual void outbound(XPoint point,Packet<uint8> packet);

   virtual ulen getMaxInboundLen() const;

   virtual void attach(InboundProc *proc);

   virtual void detach();
 };

} // namespace Net
} // namespace CCore

#endif


