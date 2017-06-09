/* AsyncUDPDevice.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_net_AsyncUDPDevice_h
#define CCore_inc_net_AsyncUDPDevice_h

#include <CCore/inc/List.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/StartStop.h>
#include <CCore/inc/Counters.h>
#include <CCore/inc/PacketPool.h>
#include <CCore/inc/AttachmentHost.h>

#include <CCore/inc/sys/SysNet.h>

#include <CCore/inc/net/PacketEndpointDevice.h>

namespace CCore {
namespace Net {

/* functions */

void AsyncUDPDeviceExitRunningAbort();

void AsyncUDPDeviceWaitAbort();

void GuardAsyncUDPDeviceMaxPackets();

/* classes */

class AsyncUDPSocket;

class AsyncUDPSocketWait;

template <class T> class AsyncUDPDevice;

struct AsyncUDPEndpointDeviceBase;

class AsyncUDPEndpointDevice;

struct AsyncUDPMultipointDeviceBase;

class AsyncUDPMultipointDevice;

/* class AsyncUDPSocket */

class AsyncUDPSocket : NoCopy
 {
   Sys::AsyncUDPSocket sys_sock;

  public:

   explicit AsyncUDPSocket(UDPort udport);

   ~AsyncUDPSocket();

   Sys::AsyncUDPSocket::OutResult startOutbound(Sys::AsyncUDPSocket::Async async,UDPoint dst,PtrLen<const uint8> data)
    {
     return sys_sock.startOutbound(async,dst,data);
    }

   Sys::ErrorType completeOutbound(Sys::AsyncUDPSocket::Async async)
    {
     return sys_sock.completeOutbound(async);
    }

   Sys::AsyncUDPSocket::StartInResult startInbound(Sys::AsyncUDPSocket::Async async,PtrLen<uint8> buf)
    {
     return sys_sock.startInbound(async,buf);
    }

   Sys::AsyncUDPSocket::InResult completeInbound(Sys::AsyncUDPSocket::Async async)
    {
     return sys_sock.completeInbound(async);
    }
 };

/* class AsyncUDPSocketWait */

class AsyncUDPSocketWait : NoCopy
 {
   Sys::AsyncUDPSocketWait sys_wait;
   Function<void (void)> finish;

  public:

   explicit AsyncUDPSocketWait(Function<void (void)> finish);

   ~AsyncUDPSocketWait();

   enum WaitIndex
    {
     OutboundIndex = 0,
     InboundIndex  = 1
    };

   Sys::AsyncUDPSocket::Async getAsync(WaitIndex ind) { return sys_wait.getAsync(ind); }

   bool addWait(WaitIndex ind) { return sys_wait.addWait(ind); }

   bool delWait(WaitIndex ind) { return sys_wait.delWait(ind); }

   Sys::WaitResult wait(TimeScope time_scope) { return sys_wait.wait(time_scope); }

   void interrupt() { sys_wait.interrupt(); }
 };

/* class AsyncUDPDevice<T> */

template <class T>
class AsyncUDPDevice : public Funchor_nocopy
 {
   using InboundProc = typename T::ProcType ;
   using Event = typename T::Event ;
   using StatInfo = typename T::StatInfo ;
   using Extra = typename T::Extra ;

  private:

   struct Ext : PacketCanceller
    {
     DLink<Ext> link;
     DLink<Ext> ext_link;

     explicit Ext(PacketHeader *packet) : PacketCanceller(packet) {}
    };

   using Top = typename DLink<Ext>::template LinearAlgo<&Ext::link>::Top ;
   using ExtTop = typename DLink<Ext>::template LinearAlgo<&Ext::ext_link>::Top ;

  private:

   UDPort udport;

   Packet<uint8> in_packet;

   Sem exit_sem;
   Mutex mutex;

   PacketList out_list;
   Top in_list;

   AttachmentHost<InboundProc> host;
   StatInfo stat;
   bool running;
   bool stop_flag;

   Packet<uint8> out_packet;

   ulen max_packets;
   ulen use_count;
   bool interrupt_flag;
   ulen exit_count;
   bool exit_flag;

   AsyncUDPSocketWait wait;
   AsyncUDPSocket sock;

  private:

   using Hook = typename AttachmentHost<InboundProc>::Hook ;

   void count(Event ev)
    {
     Mutex::Lock lock(mutex);

     stat.count(ev);
    }

   void set(bool running_)
    {
     Mutex::Lock lock(mutex);

     running=running_;
    }

   void tick()
    {
     Hook hook(host);

     if( +hook ) hook->tick();
    }

   template <class Result>
   Event inbound_ok(Packet<uint8> packet,Result result)
    {
     Hook hook(host);

     if( +hook )
       {
        return extra.inbound(hook.getPtr(),packet,result.len,result.src);
       }
     else
       {
        packet.complete();

        return T::Event_noread;
       }
    }

   // outbound

   void cancel(PacketHeader *packet);

   PacketFunction function_cancel() { return FunctionOf(this,&AsyncUDPDevice::cancel); }

   bool put(UDPoint dst,Packet<uint8> packet);

   struct GetResult
    {
     Packet<uint8,UDPoint> packet;
     bool stop_flag;

     GetResult(bool stop_flag_) : stop_flag(stop_flag_) {}

     GetResult(Packet<uint8,UDPoint> packet_) : packet(packet_),stop_flag(false) {}
    };

   GetResult get();

   bool start_out(Packet<uint8,UDPoint> packet);

   void complete_out();

   bool/* stop_flag */ push_out();

   // inbound

   void complete(PacketHeader *packet);

   PacketFunction function_complete() { return FunctionOf(this,&AsyncUDPDevice::complete); }

   Packet<uint8> get_in();

   void buildCancel(ExtTop &cancel_list);

   static void DoCancel(ExtTop &cancel_list);

   void cancel_inbound();

   void cancel_and_wait();

   bool start_in();

   void complete_in();

   void push_in();

   void inbound(Packet<uint8> packet,Sys::AsyncUDPSocket::InResult result);

   // finish

   void finish();

   Function<void (void)> function_finish() { return FunctionOf(this,&AsyncUDPDevice::finish); }

  public:

   Extra extra;

   // constructors

   template <class ... TT>
   AsyncUDPDevice(UDPort udport_,ulen max_packets_,TT ... tt)
    : udport(udport_),
      exit_sem("AsyncUDPDevice.exit_sem"),
      mutex("AsyncUDPDevice.mutex"),
      host("AsyncUDPDevice","AsyncUDPDevice.host"),
      running(false),
      stop_flag(false),
      max_packets(max_packets_),
      use_count(0),
      interrupt_flag(false),
      exit_count(0),
      exit_flag(false),
      wait(function_finish()),
      sock(udport_),
      extra(tt...)
    {
     if( !max_packets_ ) GuardAsyncUDPDeviceMaxPackets();
    }

   ~AsyncUDPDevice()
    {
     Mutex::Lock lock(mutex);

     if( running ) AsyncUDPDeviceExitRunningAbort();
    }

   // methods

   UDPort getPort() const { return udport; }

   void getStat(StatInfo &ret)
    {
     Mutex::Lock lock(mutex);

     ret=stat;
    }

   // object run

   void prepareRun()
    {
     Mutex::Lock lock(mutex);

     stop_flag=false;
    }

   void objRun();

   void completeRun() noexcept { set(true); }

   void signalStop()
    {
     {
      Mutex::Lock lock(mutex);

      stop_flag=true;
     }

     wait.interrupt();
    }

   void completeStop() { set(false); }

   // device

   PacketFormat getOutboundFormat() const
    {
     PacketFormat ret;

     ret.prefix=0;
     ret.max_data=MaxUDPDataLen;
     ret.suffix=0;

     return ret;
    }

   void outbound(UDPoint dst,Packet<uint8> packet)
    {
     if( put(dst,packet) ) wait.interrupt();
    }

   ulen getMaxInboundLen() const
    {
     return MaxUDPDataLen;
    }

   void attach(InboundProc *proc)
    {
     host.attach(proc);
    }

   void detach()
    {
     host.detach();
    }
 };

template <class T>
void AsyncUDPDevice<T>::cancel(PacketHeader *packet_)
 {
  Packet<uint8,UDPoint,bool> packet=packet_;

  {
   Mutex::Lock lock(mutex);

   if( *packet.getExt() )
     {
      out_list.del(packet);

      stat.count(T::Event_cancel);
     }
  }

  packet.popExt().popExt().complete();
 }

template <class T>
bool AsyncUDPDevice<T>::put(UDPoint dst,Packet<uint8> packet)
 {
  {
   Mutex::Lock lock(mutex);

   if( packet.setCancelFunction(function_cancel())!=Packet_Cancelled )
     {
      auto packet2=packet.pushExt<UDPoint>(dst).pushExt<bool>(true);

      out_list.put(packet2);

      return !out_packet;
     }
   else
     {
      stat.count(T::Event_cancel_on_put);
     }
  }

  packet.complete();

  return false;
 }

template <class T>
auto AsyncUDPDevice<T>::get() -> GetResult
 {
  {
   Mutex::Lock lock(mutex);

   if( +out_packet ) return false;

   if( stop_flag ) return true;

   Packet<uint8,UDPoint,bool> packet=out_list.get();

   if( !packet ) return false;

   if( packet.clearCancelFunction()!=Packet_Cancelled ) return packet.popExt();

   *packet.getExt()=false;

   stat.count(T::Event_cancel_on_get);
  }

  for(;;)
    {
     Mutex::Lock lock(mutex);

     if( stop_flag ) return true;

     Packet<uint8,UDPoint,bool> packet=out_list.get();

     if( !packet ) return false;

     if( packet.clearCancelFunction()!=Packet_Cancelled ) return packet.popExt();

     *packet.getExt()=false;

     stat.count(T::Event_cancel_on_get);
    }
 }

template <class T>
bool AsyncUDPDevice<T>::start_out(Packet<uint8,UDPoint> packet2)
 {
  UDPoint dst=*packet2.getExt();
  Packet<uint8> packet=packet2.popExt();

  PtrLen<const uint8> data=packet.getRange();

  if( data.len>MaxUDPDataLen )
    {
     packet.complete();

     count(T::Event_nosent);

     return false;
    }

  auto result=sock.startOutbound(wait.getAsync(AsyncUDPSocketWait::OutboundIndex),dst,data);

  if( result.pending )
    {
     wait.addWait(AsyncUDPSocketWait::OutboundIndex);

     Mutex::Lock lock(mutex);

     out_packet=packet;

     return true;
    }
  else
    {
     packet.complete();

     if( result.error )
       count(T::Event_nosent);
     else
       count(T::Event_sent);

     return false;
    }
 }

template <class T>
void AsyncUDPDevice<T>::complete_out()
 {
  if( sock.completeOutbound(wait.getAsync(AsyncUDPSocketWait::OutboundIndex)) )
    count(T::Event_nosent);
  else
    count(T::Event_sent);

  wait.delWait(AsyncUDPSocketWait::OutboundIndex);

  Packet<uint8> packet;

  {
   Mutex::Lock lock(mutex);

   packet=Replace_null(out_packet);
  }

  packet.complete();
 }

template <class T>
bool AsyncUDPDevice<T>::push_out()
 {
  for(ulen cnt=100; cnt ;cnt--)
    {
     auto result=get();

     if( result.stop_flag ) return true;

     if( !result.packet ) return false;

     if( start_out(result.packet) ) return false;
    }

  wait.interrupt();

  return false;
 }

template <class T>
void AsyncUDPDevice<T>::complete(PacketHeader *packet_)
 {
  Packet<uint8,Ext> packet=packet_;

  {
   Mutex::Lock lock(mutex);

   in_list.del(packet.getExt());
  }

  packet.popExt().complete();

  bool i_flag=false;
  bool e_flag=false;

  {
   Mutex::Lock lock(mutex);

   use_count--;

   if( interrupt_flag )
     {
      interrupt_flag=false;

      i_flag=true;
     }
   else
     {
      exit_count--;

      if( exit_flag && !exit_count ) e_flag=true;
     }
  }

  if( i_flag )
    {
     wait.interrupt();

     {
      Mutex::Lock lock(mutex);

      exit_count--;

      if( exit_flag && !exit_count ) e_flag=true;
     }
    }

  if( e_flag ) exit_sem.give();
 }

template <class T>
Packet<uint8> AsyncUDPDevice<T>::get_in()
 {
  {
   Mutex::Lock lock(mutex);

   if( use_count<max_packets )
     {
      use_count++;
      exit_count++;
     }
   else
     {
      interrupt_flag=true;

      return Nothing;
     }
  }

  Packet<uint8> packet=TryAllocPacket<uint8>();

  if( !packet )
    {
     Mutex::Lock lock(mutex);

     use_count--;
     exit_count--;

     stat.count(T::Event_nopacket);

     return Nothing;
    }

  PacketHeader *packet_=packet.getPtr();

  auto packet2=packet.pushExt<Ext>(packet_);

  packet2.pushCompleteFunction(function_complete());

  {
   Mutex::Lock lock(mutex);

   in_list.ins(packet2.getExt());
  }

  return packet2.template forgetExt<1>();
 }

template <class T>
void AsyncUDPDevice<T>::buildCancel(ExtTop &cancel_list)
 {
  Mutex::Lock lock(mutex);

  for(auto cur=in_list.start(); +cur ;++cur)
    {
     if( cur->getCancelFunction() ) cancel_list.ins(cur.ptr);
    }
 }

template <class T>
void AsyncUDPDevice<T>::DoCancel(ExtTop &cancel_list)
 {
  while( Ext *ext=cancel_list.del() ) ext->cancel();
 }

template <class T>
void AsyncUDPDevice<T>::cancel_inbound()
 {
  ExtTop cancel_list;

  buildCancel(cancel_list);

  DoCancel(cancel_list);
 }

template <class T>
void AsyncUDPDevice<T>::cancel_and_wait()
 {
  cancel_inbound();

  bool flag;

  {
   Mutex::Lock lock(mutex);

   exit_flag=true;
   interrupt_flag=false;

   flag=exit_count;
  }

  if( flag ) exit_sem.take();
 }

template <class T>
bool AsyncUDPDevice<T>::start_in()
 {
  Packet<uint8> packet=get_in();

  if( !packet ) return true;

  auto result=sock.startInbound(wait.getAsync(AsyncUDPSocketWait::InboundIndex),packet.getMaxRange());

  if( result.pending )
    {
     wait.addWait(AsyncUDPSocketWait::InboundIndex);

     in_packet=packet;

     return true;
    }

  inbound(packet,result.result);

  return false;
 }

template <class T>
void AsyncUDPDevice<T>::complete_in()
 {
  auto result=sock.completeInbound(wait.getAsync(AsyncUDPSocketWait::InboundIndex));

  wait.delWait(AsyncUDPSocketWait::InboundIndex);

  inbound(Replace_null(in_packet),result);
 }

template <class T>
void AsyncUDPDevice<T>::push_in()
 {
  if( +in_packet ) return;

  for(ulen cnt=100; cnt ;cnt--) if( start_in() ) return;

  wait.interrupt();
 }

template <class T>
void AsyncUDPDevice<T>::inbound(Packet<uint8> packet,Sys::AsyncUDPSocket::InResult result)
 {
  if( result.error )
    {
     count(T::Event_noread);

     packet.complete();
    }
  else
    {
     count(inbound_ok(packet,result));
    }
 }

template <class T>
void AsyncUDPDevice<T>::finish()
 {
  if( +out_packet )
    {
     Replace_null(out_packet).complete();
    }

  if( +in_packet )
    {
     Replace_null(in_packet).complete();
    }

  cancel_and_wait();
 }

template <class T>
void AsyncUDPDevice<T>::objRun()
 {
  set(true);

  TimeScope time_scope( (1000/InboundTicksPerSec)*1_msec );

  push_in();

  for(;;)
    switch( wait.wait(time_scope) )
      {
       case Sys::Wait_error :
        {
         AsyncUDPDeviceWaitAbort();
        }
       break;

       case Sys::Wait_timeout :
        {
         if( time_scope.nextScope_skip() )
           {
            tick();

            count(T::Event_tick);

            push_in();
           }
         else
           {
            count(T::Event_extra_timeout);
           }
        }
       break;

       case AsyncUDPSocketWait::OutboundIndex :
        {
         complete_out();

         if( push_out() ) return;
        }
       break;

       case Sys::Wait_interrupt :
        {
         if( push_out() ) return;

         push_in();
        }
       break;

       case AsyncUDPSocketWait::InboundIndex :
        {
         complete_in();

         push_in();
        }
       break;
      }
 }

/* struct AsyncUDPEndpointDeviceBase */

struct AsyncUDPEndpointDeviceBase
 {
  using ProcType = PacketEndpointDevice::InboundProc ;

  enum Event
   {
    Event_read,
    Event_sent,
    Event_tick,

    Event_extra_timeout,

    Event_cancel_on_put,
    Event_cancel_on_get,
    Event_cancel,
    Event_nosent,
    Event_nopacket,
    Event_noread,
    Event_nodst,

    EventLim
   };

  friend const char * GetTextDesc(Event ev);

  using StatInfo = Counters<Event,EventLim> ;

  struct Extra
   {
    UDPoint dst;

    explicit Extra(UDPoint dst_) : dst(dst_) {}

    Event inbound(ProcType *proc,Packet<uint8> packet,ulen len,UDPoint src)
     {
      if( src==dst )
        {
         PtrLen<uint8> data=packet.setDataLen(len);

         proc->inbound(packet,data);

         return Event_read;
        }
      else
        {
         packet.complete();

         return Event_nodst;
        }
     }
   };
 };

/* class AsyncUDPEndpointDevice */

class AsyncUDPEndpointDevice : public ObjBase , public PacketEndpointDevice , public AsyncUDPEndpointDeviceBase , public PortManager
 {
   AsyncUDPDevice<AsyncUDPEndpointDeviceBase> dev;

   using StartStopDev = StartStopObject<AsyncUDPDevice<AsyncUDPEndpointDeviceBase> > ;

  public:

   // constructors

   static constexpr ulen DefaultMaxPackets = 500 ;

   AsyncUDPEndpointDevice(UDPort udport,UDPoint dst,ulen max_packets=DefaultMaxPackets);

   virtual ~AsyncUDPEndpointDevice();

   // methods

   UDPort getPort() const { return dev.getPort(); }

   UDPoint getDst() const { return dev.extra.dst; }

   void getStat(StatInfo &ret) { dev.getStat(ret); }

   // PacketEndpointDevice

   virtual PacketFormat getOutboundFormat() const;

   virtual void outbound(Packet<uint8> packet);

   virtual ulen getMaxInboundLen() const;

   virtual void attach(InboundProc *proc);

   virtual void detach();

   // PortManager

   virtual XPoint getDevicePort() const;

   virtual XPoint getPort(XPoint point) const;

   virtual XPoint changePort(XPoint point,XPoint port) const;

   // start/stop

   class StartStop : public StartStopDev
    {
     public:

      template <class ... TT>
      StartStop(AsyncUDPEndpointDevice &obj,TT ... tt) : StartStopDev(obj.dev,tt...) {}

      ~StartStop() {}
    };
 };

/* struct AsyncUDPMultipointDeviceBase */

struct AsyncUDPMultipointDeviceBase
 {
  using ProcType = PacketMultipointDevice::InboundProc ;

  enum Event
   {
    Event_read,
    Event_sent,
    Event_tick,

    Event_extra_timeout,

    Event_cancel_on_put,
    Event_cancel_on_get,
    Event_cancel,
    Event_nosent,
    Event_nopacket,
    Event_noread,

    EventLim
   };

  friend const char * GetTextDesc(Event ev);

  using StatInfo = Counters<Event,EventLim> ;

  struct Extra
   {
    Extra() {}

    Event inbound(ProcType *proc,Packet<uint8> packet,ulen len,UDPoint src)
     {
      PtrLen<uint8> data=packet.setDataLen(len);

      proc->inbound(src.get(),packet,data);

      return Event_read;
     }
   };
 };

/* class AsyncUDPMultipointDevice */

class AsyncUDPMultipointDevice : public ObjBase , public PacketMultipointDevice , public AsyncUDPMultipointDeviceBase , public PortManager
 {
   AsyncUDPDevice<AsyncUDPMultipointDeviceBase> dev;

   using StartStopDev = StartStopObject<AsyncUDPDevice<AsyncUDPMultipointDeviceBase> > ;

  public:

   // constructors

   static constexpr ulen DefaultMaxPackets = 500 ;

   explicit AsyncUDPMultipointDevice(UDPort udport,ulen max_packets=DefaultMaxPackets);

   virtual ~AsyncUDPMultipointDevice();

   // methods

   UDPort getPort() const { return dev.getPort(); }

   void getStat(StatInfo &ret) { dev.getStat(ret); }

   // PacketMultipointDevice

   virtual StrLen toText(XPoint point,PtrLen<char> buf) const;

   virtual PacketFormat getOutboundFormat() const;

   virtual void outbound(XPoint point,Packet<uint8> packet);

   virtual ulen getMaxInboundLen() const;

   virtual void attach(InboundProc *proc);

   virtual void detach();

   // PortManager

   virtual XPoint getDevicePort() const;

   virtual XPoint getPort(XPoint point) const;

   virtual XPoint changePort(XPoint point,XPoint port) const;

   // start/stop

   class StartStop : public StartStopDev
    {
     public:

      template <class ... TT>
      StartStop(AsyncUDPMultipointDevice &obj,TT ... tt) : StartStopDev(obj.dev,tt...) {}

      ~StartStop() {}
    };
 };

} // namespace Net
} // namespace CCore

#endif


