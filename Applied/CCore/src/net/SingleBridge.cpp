/* SingleBridge.cpp */
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

#include <CCore/inc/net/SingleBridge.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {

/* class SingleBridge::Server */

SingleBridge::Server::Server(SingleBridge &bridge_)
 : bridge(bridge_),
   host("SingleBridge::Server","SingleBridge::Server")
 {
 }

SingleBridge::Server::~Server()
 {
 }

PacketFormat SingleBridge::Server::getOutboundFormat() const
 {
  return bridge.to_client_format;
 }

void SingleBridge::Server::outbound(Packet<uint8> packet)
 {
  bridge.put_to_client(packet);
 }

ulen SingleBridge::Server::getMaxInboundLen() const
 {
  return bridge.to_server_format.max_data;
 }

void SingleBridge::Server::attach(InboundProc *proc)
 {
  host.attach(proc);
 }

void SingleBridge::Server::detach()
 {
  host.detach();
 }

XPoint SingleBridge::Server::getDevicePort() const
 {
  return 0;
 }

XPoint SingleBridge::Server::getPort(XPoint) const
 {
  return 0;
 }

XPoint SingleBridge::Server::changePort(XPoint point,XPoint) const
 {
  return point;
 }

void SingleBridge::Server::inbound(Packet<uint8> packet)
 {
  Hook hook(host);

  if( +hook )
    {
     PacketFormat format=bridge.to_server_format;

     if( packet.checkRange(format) )
       {
        hook->inbound(packet,Range_const(packet.getRange(format)));
       }
     else
       {
        packet.complete();
       }
    }
  else
    {
     packet.complete();
    }
 }

void SingleBridge::Server::tick()
 {
  Hook hook(host);

  if( +hook ) hook->tick();
 }

/* class SingleBridge::Client */

SingleBridge::Client::Client(SingleBridge &bridge_)
 : bridge(bridge_),
   host("SingleBridge::Client","SingleBridge::Client")
 {
 }

SingleBridge::Client::~Client()
 {
 }

PacketFormat SingleBridge::Client::getOutboundFormat() const
 {
  return bridge.to_server_format;
 }

void SingleBridge::Client::outbound(Packet<uint8> packet)
 {
  bridge.put_to_server(packet);
 }

ulen SingleBridge::Client::getMaxInboundLen() const
 {
  return bridge.to_client_format.max_data;
 }

void SingleBridge::Client::attach(InboundProc *proc)
 {
  host.attach(proc);
 }

void SingleBridge::Client::detach()
 {
  host.detach();
 }

XPoint SingleBridge::Client::getDevicePort() const
 {
  return 0;
 }

XPoint SingleBridge::Client::getPort(XPoint) const
 {
  return 0;
 }

XPoint SingleBridge::Client::changePort(XPoint point,XPoint) const
 {
  return point;
 }

void SingleBridge::Client::inbound(Packet<uint8> packet)
 {
  Hook hook(host);

  if( +hook )
    {
     PacketFormat format=bridge.to_client_format;

     if( packet.checkRange(format) )
       {
        hook->inbound(packet,Range_const(packet.getRange(format)));
       }
     else
       {
        packet.complete();
       }
    }
  else
    {
     packet.complete();
    }
 }

void SingleBridge::Client::tick()
 {
  Hook hook(host);

  if( +hook ) hook->tick();
 }

/* class SingleBridge */

bool SingleBridge::drop()
 {
  return random.select(drop_den)<drop_rate;
 }

void SingleBridge::set(bool running_)
 {
  Mutex::Lock lock(mutex);

  running=running_;
 }

void SingleBridge::put_to_server(Packet<uint8> packet)
 {
  bool flag;

  {
   Mutex::Lock lock(mutex);

   flag=running;

   if( flag ) to_server.put(packet);
  }

  if( flag )
    msem.give(Event_ToServer);
  else
    packet.complete();
 }

void SingleBridge::put_to_client(Packet<uint8> packet)
 {
  bool flag;

  {
   Mutex::Lock lock(mutex);

   flag=running;

   if( flag ) to_client.put(packet);
  }

  if( flag )
    msem.give(Event_ToClient);
  else
    packet.complete();
 }

void SingleBridge::send_to_client(Packet<uint8> packet)
 {
  if( drop() )
    packet.complete();
  else
    client.inbound(packet);
 }

void SingleBridge::send_to_server(Packet<uint8> packet)
 {
  if( drop() )
    packet.complete();
  else
    server.inbound(packet);
 }

void SingleBridge::handle_to_server()
 {
  Packet<uint8> packet;

  {
   Mutex::Lock lock(mutex);

   packet=to_server.get();
  }

  send_to_server(packet);
 }

void SingleBridge::handle_to_client()
 {
  Packet<uint8> packet;

  {
   Mutex::Lock lock(mutex);

   packet=to_client.get();
  }

  send_to_client(packet);
 }

void SingleBridge::handle_tick()
 {
  server.tick();
  client.tick();
 }

void SingleBridge::objRun()
 {
  set(true);

  TimeScope time_scope(100_msec);

  for(;;)
    switch( msem.take(time_scope) )
      {
       case Event_Timeout  : if( time_scope.nextScope_skip() ) handle_tick(); break;

       case Event_Stop     : return;

       case Event_ToServer : handle_to_server(); break;
       case Event_ToClient : handle_to_client(); break;
      }
 }

void SingleBridge::signalStop()
 {
  msem.give(Event_Stop);
 }

void SingleBridge::completeStop()
 {
  set(false);

  complete(to_server);
  complete(to_client);
 }

void SingleBridge::complete(PacketList &list)
 {
  list.complete();
 }

SingleBridge::SingleBridge()
 : server(*this),
   client(*this),
   msem("SingleBridge"),
   mutex("SingleBridge"),
   running(false),
   server_master(server,ServerName()),
   client_master(client,ClientName())
 {
  drop_rate=0;
  drop_den=1;

  to_server_format.prefix=11;
  to_server_format.max_data=1100;
  to_server_format.suffix=10;

  to_client_format.prefix=13;
  to_client_format.max_data=1000;
  to_client_format.suffix=15;
 }

SingleBridge::SingleBridge(PacketFormat to_server_format_,PacketFormat to_client_format_)
 : SingleBridge()
 {
  to_server_format=to_server_format_;
  to_client_format=to_client_format_;
 }

SingleBridge::~SingleBridge()
 {
  Mutex::Lock lock(mutex);

  if( running ) Abort("Fatal error : CCore::Net::SingleBridge is running on exit");
 }

} // namespace Net
} // namespace CCore


