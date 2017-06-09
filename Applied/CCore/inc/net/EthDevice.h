/* EthDevice.h */
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

#ifndef CCore_inc_net_EthDevice_h
#define CCore_inc_net_EthDevice_h

#include <CCore/inc/Counters.h>

#include <CCore/inc/net/NetBase.h>
#include <CCore/inc/net/PacketEndpointDevice.h>

namespace CCore {
namespace Net {

/* classes */

//enum EthEvent;

struct EthTxExt;

struct EthRxExt;

struct EthProc;

struct EthDevice;

/* enum EthEvent */

enum EthEvent
 {
  EthLink_Up,
  EthLink_Down,

  EthTx_Done,
  EthRx_Done,

  EthTx_BadPacketLen,
  EthTx_Error,

  EthRx_BadPacketLen,
  EthRx_Drop,
  EthRx_Broadcast,
  EthRx_Error,

  EthEventLim
 };

const char * GetTextDesc(EthEvent ev);

using EthStatInfo = Counters<EthEvent,EthEventLim> ;

/* struct EthTxExt */

struct EthTxExt
 {
  MACAddress dst;
  EthType type;

  // constructors

  EthTxExt() : dst(),type() {}

  EthTxExt(MACAddress dst_,EthType type_) : dst(dst_),type(type_) {}

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"-> #; #;",dst,type);
   }
 };

/* struct EthRxExt */

struct EthRxExt
 {
  MACAddress src;
  MACAddress dst;
  EthType type;

  // constructors

  EthRxExt() : src(),dst(),type() {}

  EthRxExt(MACAddress src_,MACAddress dst_,EthType type_) : src(src_),dst(dst_),type(type_) {}

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"#; <- #; #;",dst,src,type);
   }
 };

/* struct EthProc */

struct EthProc
 {
  // serialized

  virtual void start()=0;

  virtual void linkUp()=0;

  virtual void linkDown()=0;

  virtual void tick()=0; // InboundTicksPerSec

  virtual void inbound(Packet<uint8,EthRxExt> packet)=0;

  virtual void prepareOutbound()=0;

  virtual Packet<uint8,EthTxExt> outbound()=0;

  virtual void stop()=0;
 };

/* struct EthDevice */

struct EthDevice
 {
  static const Unid TypeUnid;

  // static properties

  virtual MACAddress getAddress() const =0;

  virtual PacketFormat getTxFormat() const =0; // max_data <= MaxUInt<IPLen>

  virtual PacketFormat getRxFormat() const =0; // max_data <= MaxUInt<IPLen>

  // attach/detach

  virtual void attach(EthProc *proc)=0;

  virtual void detach()=0;

  // dynamic properties

  using StatInfo = EthStatInfo ;

  virtual void getStat(StatInfo &ret)=0;

  virtual bool getPromiscMode()=0;

  virtual void setPromiscMode(bool enable)=0;

  // outbound

  virtual void signalOutbound()=0;
 };

} // namespace Net
} // namespace CCore

#endif


