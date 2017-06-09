/* Bridge.cpp */
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

#include <CCore/inc/net/Bridge.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {

/* class Bridge::Server */

Bridge::Server::Server(Bridge &bridge_)
 : bridge(bridge_),
   host("Bridge::Server","Bridge::Server")
 {
 }

Bridge::Server::~Server()
 {
 }

StrLen Bridge::Server::toText(XPoint point,PtrLen<char> buf) const
 {
  PrintBuf out(buf);

  Putobj(out,point);

  return out.close();
 }

PacketFormat Bridge::Server::getOutboundFormat() const
 {
  return bridge.to_client_format;
 }

void Bridge::Server::outbound(XPoint point,Packet<uint8> packet)
 {
  bridge.put_to_client(point,packet);
 }

ulen Bridge::Server::getMaxInboundLen() const
 {
  return bridge.to_server_format.max_data;
 }

void Bridge::Server::attach(InboundProc *proc)
 {
  host.attach(proc);
 }

void Bridge::Server::detach()
 {
  host.detach();
 }

XPoint Bridge::Server::getDevicePort() const
 {
  return 0;
 }

XPoint Bridge::Server::getPort(XPoint) const
 {
  return 0;
 }

XPoint Bridge::Server::changePort(XPoint point,XPoint) const
 {
  return point;
 }

void Bridge::Server::inbound(XPoint point,Packet<uint8> packet)
 {
  Hook hook(host);

  if( +hook )
    {
     PacketFormat format=bridge.to_server_format;

     if( packet.checkRange(format) )
       {
        hook->inbound(point,packet,Range_const(packet.getRange(format)));
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

void Bridge::Server::tick()
 {
  Hook hook(host);

  if( +hook ) hook->tick();
 }

/* class Bridge::Client */

Bridge::Client::Client(Bridge &bridge_,XPoint point_)
 : bridge(bridge_),
   point(point_),
   host("Bridge::Client","Bridge::Client")
 {
 }

Bridge::Client::~Client()
 {
 }

PacketFormat Bridge::Client::getOutboundFormat() const
 {
  return bridge.to_server_format;
 }

void Bridge::Client::outbound(Packet<uint8> packet)
 {
  bridge.put_to_server(point,packet);
 }

ulen Bridge::Client::getMaxInboundLen() const
 {
  return bridge.to_client_format.max_data;
 }

void Bridge::Client::attach(InboundProc *proc)
 {
  host.attach(proc);
 }

void Bridge::Client::detach()
 {
  host.detach();
 }

XPoint Bridge::Client::getDevicePort() const
 {
  return 0;
 }

XPoint Bridge::Client::getPort(XPoint) const
 {
  return 0;
 }

XPoint Bridge::Client::changePort(XPoint point,XPoint) const
 {
  return point;
 }

void Bridge::Client::inbound(Packet<uint8> packet)
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

void Bridge::Client::tick()
 {
  Hook hook(host);

  if( +hook ) hook->tick();
 }

/* class Bridge */

bool Bridge::drop()
 {
  return random.select(drop_den)<drop_rate;
 }

void Bridge::set(bool running_)
 {
  Mutex::Lock lock(mutex);

  running=running_;
 }

void Bridge::put_to_server(XPoint point,Packet<uint8> packet)
 {
  bool flag;

  {
   Mutex::Lock lock(mutex);

   flag=running;

   if( flag ) to_server.put(packet.pushExt<XPoint>(point));
  }

  if( flag )
    msem.give(Event_ToServer);
  else
    packet.complete();
 }

void Bridge::put_to_client(XPoint point,Packet<uint8> packet)
 {
  bool flag;

  {
   Mutex::Lock lock(mutex);

   flag=running;

   if( flag ) to_client.put(packet.pushExt<XPoint>(point));
  }

  if( flag )
    msem.give(Event_ToClient);
  else
    packet.complete();
 }

void Bridge::send_to_client(XPoint point,Packet<uint8> packet)
 {
  if( point==0 || point>clients.getLen() )
    {
     packet.complete();
    }
  else
    {
     ulen i=ulen(point-1);

     if( drop() )
       packet.complete();
     else
       clients[i].inbound(packet);
    }
 }

void Bridge::send_to_server(XPoint point,Packet<uint8> packet)
 {
  if( drop() )
    packet.complete();
  else
    server.inbound(point,packet);
 }

void Bridge::handle_to_server()
 {
  Packet<uint8,XPoint> packet;

  {
   Mutex::Lock lock(mutex);

   packet=to_server.get();
  }

  XPoint point=*packet.getExt();

  send_to_server(point,packet.popExt());
 }

void Bridge::handle_to_client()
 {
  Packet<uint8,XPoint> packet;

  {
   Mutex::Lock lock(mutex);

   packet=to_client.get();
  }

  XPoint point=*packet.getExt();

  send_to_client(point,packet.popExt());
 }

void Bridge::handle_tick()
 {
  server.tick();

  for(auto cur=Range(clients); +cur ;++cur) cur->tick();
 }

void Bridge::objRun()
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

void Bridge::signalStop()
 {
  msem.give(Event_Stop);
 }

void Bridge::completeStop()
 {
  set(false);

  complete(to_server);
  complete(to_client);
 }

void Bridge::complete(PacketList &list)
 {
  while( PacketHeader *packet_=list.get() )
    {
     Packet<uint8,XPoint> packet=packet_;

     packet.popExt().complete();
    }
 }

Bridge::ClientName::ClientName(ulen number)
 {
  PrintBuf out(Range(buf));

  Printf(out,"BridgeClient[#;]",number);

  str=out.guardOverflow().close();
 }

Bridge::Bridge(ulen num_clients)
 : server(*this),
   clients(DoReserve,num_clients),
   masters(DoReserve,num_clients+1),
   msem("Bridge"),
   mutex("Bridge"),
   running(false)
 {
  masters.append_fill(server,ServerName());

  for(ulen i=0; i<num_clients ;i++)
    {
     Client *client=clients.append_fill(*this,i+1);

     masters.append_fill(*client,ClientName(i+1).str);
    }

  drop_rate=0;
  drop_den=1;

  to_server_format.prefix=11;
  to_server_format.max_data=1100;
  to_server_format.suffix=10;

  to_client_format.prefix=13;
  to_client_format.max_data=1000;
  to_client_format.suffix=15;
 }

Bridge::Bridge(ulen num_clients,PacketFormat to_server_format_,PacketFormat to_client_format_)
 : Bridge(num_clients)
 {
  to_server_format=to_server_format_;
  to_client_format=to_client_format_;
 }

Bridge::~Bridge()
 {
  Mutex::Lock lock(mutex);

  if( running ) Abort("Fatal error : CCore::Net::Bridge is running on exit");
 }

} // namespace Net
} // namespace CCore


