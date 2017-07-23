/* EchoDevice.h */
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

#ifndef CCore_inc_net_EchoDevice_h
#define CCore_inc_net_EchoDevice_h

#include <CCore/inc/net/PacketEndpointDevice.h>

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PacketSet.h>
#include <CCore/inc/Counters.h>

namespace CCore {
namespace Net {

/* classes */

class EchoDevice;

/* class EchoDevice */

class EchoDevice : public NoCopyBase<PacketMultipointDevice::InboundProc,PacketMultipointDevice::ConnectionProc>
 {
  public:

   enum Event
    {
     Event_inbound,

     Event_nopacket,
     Event_badformat,

     Event_open,
     Event_lost,
     Event_close,

     EventLim
    };

   friend const char * GetTextDesc(Event ev);

   using StatInfo = Counters<Event,EventLim> ;

  private:

   ObjHook hook;

   PacketMultipointDevice *mp;
   PacketFormat format;
   bool show_flag;

   PacketSet<uint8> pset;

   Mutex mutex;

   StatInfo stat;
   uint64 traffic;

  private:

   void count(Event ev);

   void echo(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data);

   // PacketMultipointDevice::InboundProc

   virtual void inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data);

   virtual void tick();

   // PacketMultipointDevice::ConnectionProc

   virtual void connection_open(XPoint point);

   virtual void connection_lost(XPoint point);

   virtual void connection_close(XPoint point);

  public:

   static constexpr ulen DefaultMaxPackets = 200 ;

   explicit EchoDevice(StrLen mp_dev_name,ulen max_packets=DefaultMaxPackets,bool show_flag=false);

   ~EchoDevice();

   void getStat(StatInfo &ret);

   uint64 getTraffic();
 };

} // namespace Net
} // namespace CCore

#endif


