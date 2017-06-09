/* NetFork.cpp */
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

#include <CCore/inc/net/NetFork.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {

/* class EndpointNetFork */

void EndpointNetFork::Engine::work(Item item)
 {
  Hook hook(host);

  if( +hook )
    {
     hook->inbound(item.packet,item.data);
    }
  else
    {
     item.packet.complete();
    }
 }

void EndpointNetFork::Engine::work()
 {
  for(;;)
    {
     sem.take();

     if( stop_flag )
       {
        sem.give();

        return;
       }

     Item item;

     {
      Mutex::Lock lock(mutex);

      item=queue.get();
     }

     work(item);
    }
 }

EndpointNetFork::Engine::Engine(PacketEndpointDevice *ep_,ulen queue_len)
 : ep(ep_),
   host("EndpointNetFork","EndpointNetFork.host"),
   sem("EndpointNetFork.sem"),
   mutex("EndpointNetFork.mutex"),
   queue(queue_len),
   asem("EndpointNetFork.asem")
 {
  ep->attach(this);
 }

EndpointNetFork::Engine::~Engine()
 {
  ep->detach();

  stop_flag=1;

  sem.give();

  asem.wait();

  while( +queue ) work(queue.get());
 }

void EndpointNetFork::Engine::attach(InboundProc *proc)
 {
  host.attach(proc);
 }

void EndpointNetFork::Engine::detach()
 {
  host.detach();
 }

void EndpointNetFork::Engine::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  Item item(packet,data);

  bool ok;

  {
   Mutex::Lock lock(mutex);

   ok=queue.put(item);
  }

  if( ok )
    sem.give();
  else
    work(item);
 }

void EndpointNetFork::Engine::tick()
 {
  Hook hook(host);

  if( +hook ) hook->tick();
 }

void EndpointNetFork::Engine::connection_lost()
 {
  Hook hook(host);

  if( +hook )
    {
     if( ConnectionProc *proc=hook->pickInterface<ConnectionProc>() ) proc->connection_lost();
    }
 }

void EndpointNetFork::Engine::connection_close()
 {
  Hook hook(host);

  if( +hook )
    {
     if( ConnectionProc *proc=hook->pickInterface<ConnectionProc>() ) proc->connection_close();
    }
 }

EndpointNetFork::EndpointNetFork(StrLen ep_dev_name,ulen queue_len)
 : hook(ep_dev_name),
   engine(hook,queue_len)
 {
 }

EndpointNetFork::~EndpointNetFork()
 {
 }

void EndpointNetFork::requestInterface(InterfaceCaster &caster)
 {
  if( caster.getTypeNumber().oneOf<PacketEndpointDevice>() )
    {
     caster.cast(this);
    }
  else
    {
     hook.requestInterface(caster);
    }
 }

PacketFormat EndpointNetFork::getOutboundFormat() const
 {
  return engine.getEPDevice()->getOutboundFormat();
 }

void EndpointNetFork::outbound(Packet<uint8> packet)
 {
  engine.getEPDevice()->outbound(packet);
 }

ulen EndpointNetFork::getMaxInboundLen() const
 {
  return engine.getEPDevice()->getMaxInboundLen();
 }

void EndpointNetFork::attach(InboundProc *proc)
 {
  engine.attach(proc);
 }

void EndpointNetFork::detach()
 {
  engine.detach();
 }

/* class MultipointNetFork */

void MultipointNetFork::Engine::work(Item item)
 {
  Hook hook(host);

  if( +hook )
    {
     hook->inbound(item.point,item.packet,item.data);
    }
  else
    {
     item.packet.complete();
    }
 }

void MultipointNetFork::Engine::work()
 {
  for(;;)
    {
     sem.take();

     if( stop_flag )
       {
        sem.give();

        return;
       }

     Item item;

     {
      Mutex::Lock lock(mutex);

      item=queue.get();
     }

     work(item);
    }
 }

MultipointNetFork::Engine::Engine(PacketMultipointDevice *mp_,ulen queue_len)
 : mp(mp_),
   host("MultipointNetFork","MultipointNetFork.host"),
   sem("MultipointNetFork.sem"),
   mutex("MultipointNetFork.mutex"),
   queue(queue_len),
   asem("MultipointNetFork.asem")
 {
  mp->attach(this);
 }

MultipointNetFork::Engine::~Engine()
 {
  mp->detach();

  stop_flag=1;

  sem.give();

  asem.wait();

  while( +queue ) work(queue.get());
 }

void MultipointNetFork::Engine::attach(InboundProc *proc)
 {
  host.attach(proc);
 }

void MultipointNetFork::Engine::detach()
 {
  host.detach();
 }

void MultipointNetFork::Engine::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
 {
  Item item(point,packet,data);

  bool ok;

  {
   Mutex::Lock lock(mutex);

   ok=queue.put(item);
  }

  if( ok )
    sem.give();
  else
    work(item);
 }

void MultipointNetFork::Engine::tick()
 {
  Hook hook(host);

  if( +hook ) hook->tick();
 }

void MultipointNetFork::Engine::connection_open(XPoint point)
 {
  Hook hook(host);

  if( +hook )
    {
     if( ConnectionProc *proc=hook->pickInterface<ConnectionProc>() ) proc->connection_open(point);
    }
 }

void MultipointNetFork::Engine::connection_lost(XPoint point)
 {
  Hook hook(host);

  if( +hook )
    {
     if( ConnectionProc *proc=hook->pickInterface<ConnectionProc>() ) proc->connection_lost(point);
    }
 }

void MultipointNetFork::Engine::connection_close(XPoint point)
 {
  Hook hook(host);

  if( +hook )
    {
     if( ConnectionProc *proc=hook->pickInterface<ConnectionProc>() ) proc->connection_close(point);
    }
 }

MultipointNetFork::MultipointNetFork(StrLen mp_dev_name,ulen queue_len)
 : hook(mp_dev_name),
   engine(hook,queue_len)
 {
 }

MultipointNetFork::~MultipointNetFork()
 {
 }

void MultipointNetFork::requestInterface(InterfaceCaster &caster)
 {
  if( caster.getTypeNumber().oneOf<PacketMultipointDevice>() )
    {
     caster.cast(this);
    }
  else
    {
     hook.requestInterface(caster);
    }
 }

StrLen MultipointNetFork::toText(XPoint point,PtrLen<char> buf) const
 {
  return engine.getMPDevice()->toText(point,buf);
 }

PacketFormat MultipointNetFork::getOutboundFormat() const
 {
  return engine.getMPDevice()->getOutboundFormat();
 }

void MultipointNetFork::outbound(XPoint point,Packet<uint8> packet)
 {
  engine.getMPDevice()->outbound(point,packet);
 }

ulen MultipointNetFork::getMaxInboundLen() const
 {
  return engine.getMPDevice()->getMaxInboundLen();
 }

void MultipointNetFork::attach(InboundProc *proc)
 {
  engine.attach(proc);
 }

void MultipointNetFork::detach()
 {
  engine.detach();
 }

} // namespace Net
} // namespace CCore


