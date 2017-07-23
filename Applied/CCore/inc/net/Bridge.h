/* Bridge.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_net_Bridge_h
#define CCore_inc_net_Bridge_h

#include <CCore/inc/net/PacketEndpointDevice.h>

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/StartStop.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/AttachmentHost.h>
#include <CCore/inc/PlatformRandom.h>

namespace CCore {
namespace Net {

/* classes */

class Bridge;

/* class Bridge */

class Bridge : NoCopy
 {
   class Server : public ObjBase , public PacketMultipointDevice , public PortManager
    {
      Bridge &bridge;
      AttachmentHost<InboundProc> host;

      using Hook = AttachmentHost<InboundProc>::Hook ;

     public:

      explicit Server(Bridge &bridge);

      virtual ~Server();

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

      // methods

      void inbound(XPoint point,Packet<uint8> packet);

      void tick();
    };

   class Client : public ObjBase , public PacketEndpointDevice , public PortManager
    {
      Bridge &bridge;
      XPoint point;
      AttachmentHost<InboundProc> host;

      using Hook = AttachmentHost<InboundProc>::Hook ;

     public:

      Client(Bridge &bridge,XPoint point);

      virtual ~Client();

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

      // methods

      void inbound(Packet<uint8> packet);

      void tick();
    };

   PacketFormat to_server_format;
   PacketFormat to_client_format;

   Server server;
   DynArray<Client,ArrayAlgo_mini<Client> > clients;

   DynArray<ObjMaster,ArrayAlgo_mini<ObjMaster> > masters;

   enum Events
    {
     Event_Timeout,

     Event_Stop,
     Event_ToServer,
     Event_ToClient,

     EventLim
    };

   MultiSem<EventLim-1> msem;

   PlatformRandom random;
   uint32 drop_rate;
   uint32 drop_den;

   Mutex mutex;

   PacketList to_server;
   PacketList to_client;
   bool running;

  private:

   bool drop();

   void set(bool running);

   void put_to_server(XPoint point,Packet<uint8> packet);

   void put_to_client(XPoint point,Packet<uint8> packet);

   void send_to_client(XPoint point,Packet<uint8> packet);

   void send_to_server(XPoint point,Packet<uint8> packet);

   void handle_to_server();

   void handle_to_client();

   void handle_tick();

   // object run

   void prepareRun() {}

   void objRun();

   void completeRun() noexcept { set(true); }

   void signalStop();

   void completeStop();

   void complete(PacketList &list);

  public:

   explicit Bridge(ulen num_clients);

   Bridge(ulen num_clients,PacketFormat to_server_format,PacketFormat to_client_format);

   ~Bridge();

   // methods

   void setDropRate(uint32 drop_rate_,uint32 drop_den_)
    {
     drop_rate=drop_rate_;
     drop_den=drop_den_;
    }

   static StrLen ServerName() { return "BridgeServer"; }

   struct ClientName
    {
     char buf[TextBufLen];
     StrLen str;

     explicit ClientName(ulen number);
    };

   // start/stop

   friend class StartStopObject<Bridge>;

   using StartStop = StartStopObject<Bridge> ;
 };

} // namespace Net
} // namespace CCore

#endif


