/* PTPEchoTest.h */
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

#ifndef CCore_inc_net_PTPEchoTest_h
#define CCore_inc_net_PTPEchoTest_h

#include <CCore/inc/net/PTPClientDevice.h>
#include <CCore/inc/net/PTPServerDevice.h>

#include <CCore/inc/PlatformRandom.h>

namespace CCore {
namespace Net {
namespace PTP {

/* classes */

class EchoTest;

/* class EchoTest */

class EchoTest : public NoCopyBase<ServerProc>
 {
   ObjHook hook;

   ServerDevice *ptp;

   PlatformRandom random;

  private:

   void cancel(TransIndex idx,Packet<uint8> packet);

   template <class T>
   void result(TransIndex idx,Packet<uint8> packet,ServiceFunction serv_func,const T &output);

   // ServerProc

   virtual void inbound(XPoint point,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info);

   virtual void tick();

  public:

   static constexpr ServiceIdType ServiceId = 10000 ;
   static constexpr FunctionIdType FunctionId = 1 ;

   static constexpr ulen DeltaLen = 12 ;

   struct Ext;

   explicit EchoTest(StrLen ptp_server_name);

   ~EchoTest();

   PacketMultipointDevice * getMPDevice() const { return ptp->getMPDevice(); }
 };

/* struct EchoTest::Ext */

struct EchoTest::Ext : ExtBase<EchoTest::ServiceId,EchoTest::FunctionId,MovePacketBuf>
 {
  struct InputType // + uint8 info[len];
   {
    static constexpr uint32 MaxLen = MaxInfoLen ;

    uint32 len;

    explicit InputType(ulen len_) : len(len_) {}

    // save object

    enum { SaveLoadLen = SaveLenCounter<uint32>::SaveLoadLen };

    void save(SaveDevType &dev) const
     {
      dev.template use<BeOrder>(len);
     }
   };

  struct OutputType
   {
    PtrLen<const uint8> info;

    // load object

    void load(ExtraLoadDevType &dev)
     {
      info=dev.getFinalRange();
     }
   };

  PtrLen<const uint8> info;

  void done(const OutputType &output)
   {
    info=output.info;
   }
 };

} // namespace PTP
} // namespace Net
} // namespace CCore

#endif


