/* PTPServerDevice.cpp */
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

#include <CCore/inc/net/PTPServerDevice.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {
namespace PTP {

/* enum ServerEvent */

const char * GetTextDesc(ServerEvent ev)
 {
  static const char *const Table[]=
   {
    "Trans",                     // ServerEvent_Trans
    "Trans done",                // ServerEvent_TransDone

    "Trans timeout",             // ServerEvent_Timeout
    "Trans cancelled",           // ServerEvent_Cancel
    "Trans cancelled by client", // ServerEvent_ClientCancel
    "Trans aborted",             // ServerEvent_Abort

    "<- CALL",                   // ServerEvent_CALL
    "<- RECALL",                 // ServerEvent_RECALL
    "<- SENDRET",                // ServerEvent_SENDRET
    "<- ACK",                    // ServerEvent_ACK

    "-> RET",                    // ServerEvent_RET
    "-> CANCEL",                 // ServerEvent_CANCEL
    "-> NOINFO",                 // ServerEvent_NOINFO
    "-> RERET",                  // ServerEvent_RERET

    "Bad TransId",               // ServerEvent_BadTransId

    "No slot",                   // ServerEvent_NoSlot
    "No slot cancel",            // ServerEvent_NoSlotCancel
    "No free slot",              // ServerEvent_NoFreeSlot
    "No packet",                 // ServerEvent_NoPacket

    "Bad inbound",               // ServerEvent_BadInbound
    "Bad outbound",              // ServerEvent_BadOutbound

    ""
   };

  return Table[ev];
 }

/* struct ServerEventRegType */

EventIdType ServerEventRegType::Register(EventMetaInfo &info)
 {
  return info.addEnum_uint8("PTPServer")

             .addValueName(ServerEvent_Trans,"Trans",EventMarker_Push)
             .addValueName(ServerEvent_TransDone,"Trans done",EventMarker_Stop)

             .addValueName(ServerEvent_Timeout,"Timeout",EventMarker_Pass)
             .addValueName(ServerEvent_Cancel,"Cancel",EventMarker_Pass)
             .addValueName(ServerEvent_ClientCancel,"Client cancel",EventMarker_Pass)
             .addValueName(ServerEvent_Abort,"Abort",EventMarker_Pass)

             .addValueName(ServerEvent_CALL,"<- CALL",EventMarker_Down)
             .addValueName(ServerEvent_RECALL,"<- RECALL",EventMarker_Down)
             .addValueName(ServerEvent_SENDRET,"<- SENDRET",EventMarker_Down)
             .addValueName(ServerEvent_ACK,"<- ACK",EventMarker_Down)

             .addValueName(ServerEvent_RET,"-> RET",EventMarker_Up)
             .addValueName(ServerEvent_CANCEL,"-> CANCEL",EventMarker_Up)
             .addValueName(ServerEvent_NOINFO,"-> NOINFO",EventMarker_Up)
             .addValueName(ServerEvent_RERET,"-> RERET",EventMarker_Up)

             .addValueName(ServerEvent_BadTransId,"Bad TransId",EventMarker_Error)

             .addValueName(ServerEvent_NoSlot,"No slot",EventMarker_Error)
             .addValueName(ServerEvent_NoSlotCancel,"No slot cancel",EventMarker_Error)
             .addValueName(ServerEvent_NoFreeSlot,"No free slot",EventMarker_DownBlock)
             .addValueName(ServerEvent_NoPacket,"No packet",EventMarker_Error)

             .addValueName(ServerEvent_BadInbound,"Bad inbound",EventMarker_Error)
             .addValueName(ServerEvent_BadOutbound,"Bad outbound",EventMarker_Error)

             .getId();
 }

/* struct ServerProtoEvent */

void ServerProtoEvent::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id=info.addStruct("PTPServerEvent")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint8(EventTypeId<ServerEventRegType>::GetId(),"event",Offset_ev)
              .getId();

  desc.setStructId(info,id);
 }

/* struct ServerProtoEvent_slot */

void ServerProtoEvent_slot::Register(EventMetaInfo &info,EventMetaInfo::EventDesc &desc)
 {
  auto id=info.addStruct("PTPServerEventSlot")
              .addField_uint32("time",Offset_time)
              .addField_uint16("id",Offset_id)
              .addField_enum_uint8(EventTypeId<ServerEventRegType>::GetId(),"event",Offset_ev)
              .addField_uint32("slot",Offset_slot)
              .getId();

  desc.classId<ServerProtoEvent>();

  desc.setStructId(info,id);
 }

/* class ServerEngine::Slot */

void ServerEngine::ProcExt::Complete(PacketHeader *packet_)
 {
  Packet<uint8,Hook,ProcExt> packet=packet_;

  ProcExt ext=*packet.getExt();

  ext(packet.popExt());
 }

void ServerEngine::Slot::send_RET(PacketList &complete_list)
 {
  engine->stat.count(server_slot,ServerEvent_RET);

  PacketPrefix4 prefix(PacketType_RET,trans_id,client_slot,server_slot);
  Packet_RET4 ret(server_info.len);

  engine->send(complete_list,point,prefix,ret,server_info,engine->getDataPacket(plist));
 }

void ServerEngine::Slot::send_CANCEL(PacketList &complete_list)
 {
  engine->stat.count(server_slot,ServerEvent_CANCEL);

  PacketPrefix4 prefix(PacketType_CANCEL,trans_id,client_slot,server_slot);

  engine->send(complete_list,point,prefix,engine->getDataPacket(plist));
 }

void ServerEngine::Slot::send_RERET(PacketList &complete_list)
 {
  engine->stat.count(server_slot,ServerEvent_RERET);

  PacketPrefix4 prefix(PacketType_RERET,trans_id,client_slot,server_slot);

  engine->send(complete_list,point,prefix,engine->getDataPacket(plist));
 }

void ServerEngine::Slot::send_NOINFO(PacketList &complete_list)
 {
  engine->stat.count(server_slot,ServerEvent_NOINFO);

  PacketPrefix4 prefix(PacketType_NOINFO,trans_id,client_slot,server_slot);

  engine->send(complete_list,point,prefix,engine->getDataPacket(plist));
 }

void ServerEngine::Slot::start(PacketList &complete_list,XPoint point_,const TransId &trans_id_,SlotId client_slot_,Packet<uint8> packet,PtrLen<const uint8> client_info,RecallNumber recall_number_)
 {
  engine->stat.count(server_slot,ServerEvent_Trans);

  point=point_;
  trans_id=trans_id_;
  client_slot=client_slot_;
  recall_number=recall_number_;
  timeout_msec=0;
  retry_count=MaxRetries;

  state=State_pending;
  index++;

  Hook hook(engine->host);

  if( +hook )
    {
     auto packet2=engine->pset.enlist(plist,packet);

     auto packet3=packet2.pushExt<Hook>(std::move(hook)).pushExt<ProcExt>(point_,TransIndex(server_slot,index),client_info);

     packet3.pushCompleteFunction(ProcExt::Complete);

     complete_list.put(packet3);
    }
  else
    {
     complete_list.put(packet);

     send_cancel(complete_list);
    }
 }

void ServerEngine::Slot::send_info(PacketList &complete_list,Packet<uint8> proc_packet,PtrLen<const uint8> server_info_)
 {
  state=State_ready;

  proc_packet.detach(pbuf);

  server_info=server_info_;

  setTick();

  complete_list.put(proc_packet);

  send_RET(complete_list);
 }

void ServerEngine::Slot::send_cancel(PacketList &complete_list)
 {
  state=State_cancelled;

  setTick();

  send_CANCEL(complete_list);
 }

void ServerEngine::Slot::inbound_CALL(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,Packet<uint8> packet,PtrLen<const uint8> client_info)
 {
  engine->stat.count(server_slot,ServerEvent_CALL);

  start(complete_list,point,trans_id,client_slot,packet,client_info);
 }

void ServerEngine::Slot::inbound_RECALL(PacketList &complete_list,SlotId client_slot_,RecallNumber recall_number_)
 {
  engine->stat.count(server_slot,ServerEvent_RECALL);

  if( client_slot_!=client_slot ) return;

  recall_number=recall_number_;

  switch( state )
    {
     case State_pending   : send_NOINFO(complete_list); break;

     case State_ready     : send_RET(complete_list);    break;

     case State_cancelled : send_CANCEL(complete_list); break;
    }
 }

void ServerEngine::Slot::inbound_RECALL_first(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,Packet<uint8> packet,PtrLen<const uint8> client_info,RecallNumber recall_number)
 {
  engine->stat.count(server_slot,ServerEvent_RECALL);

  start(complete_list,point,trans_id,client_slot,packet,client_info,recall_number);
 }

void ServerEngine::Slot::inbound_ACK(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list)
 {
  engine->stat.count(server_slot,ServerEvent_ACK);

  switch( state )
    {
     case State_pending   : engine->stat.count(server_slot,ServerEvent_ClientCancel); break;
     case State_ready     : engine->stat.count(server_slot,ServerEvent_TransDone);    break;
     case State_cancelled : engine->stat.count(server_slot,ServerEvent_Cancel);       break;
    }

  finish(cancel,complete_list);
 }

void ServerEngine::Slot::inbound_SENDRET(PacketList &complete_list)
 {
  engine->stat.count(server_slot,ServerEvent_SENDRET);

  switch( state )
    {
     case State_ready     : send_RET(complete_list);    break;

     case State_cancelled : send_CANCEL(complete_list); break;
    }
 }

bool ServerEngine::Slot::tick(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list)
 {
  if( timeout_msec )
    {
     if( tick_count )
       {
        tick_count--;

        return true;
       }
     else
       {
        if( retry_count )
          {
           retry_count--;
          }
        else
          {
           engine->stat.count(server_slot,ServerEvent_Timeout);

           finish(cancel,complete_list);

           return false;
          }

        send_RERET(complete_list);

        setTick();

        return true;
       }
    }

  return true;
 }

void ServerEngine::Slot::finish(PacketSet<uint8>::Cancel &cancel,PacketList &)
 {
  server_info=Nothing;

  pbuf.detach();

  cancel.build(plist);
 }

/* struct ServerProc */

const Unid ServerProc::TypeUnid={{0x60D1'7480,0xD323'DCC0,0x01AB'1C7C,0x36D5'F6AD,0x9393'B175,0x9D66'258F,0x2DD2'0918,0x30E9'388F}};

/* class ServerEngine */

ServerEngine::Slot * ServerEngine::find(XPoint point,SlotId server_slot,const TransId &trans_id)
 {
  if( server_slot>=slots.getLen() ) return 0;

  Slot *slot=slots.getPtr()+server_slot;

  if( slot->active && slot->trans_id==trans_id && slot->point==point ) return slot;

  return 0;
 }

void ServerEngine::activate(Slot *slot)
 {
  slots_asem.inc();

  slot->active=true;

  avail_list.del(slot);

  active_list.ins_last(slot);
 }

void ServerEngine::deactivate(Slot *slot)
 {
  slots_asem.dec();

  slot->active=false;

  active_list.del(slot);

  avail_list.ins_last(slot);

  active_tree.del(slot);
 }

void ServerEngine::deactivate_nodel(Slot *slot)
 {
  slots_asem.dec();

  slot->active=false;

  avail_list.ins_last(slot);

  active_tree.del(slot);
 }

void ServerEngine::inbound_CALL(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,Packet<uint8> packet,PtrLen<const uint8> client_info)
 {
  TreeAlgo::PrepareIns prepare(active_tree,Key(point,trans_id));

  if( prepare.found )
    {
     stat.count(ServerEvent_CALL);
     stat.count(ServerEvent_BadTransId);

     complete_list.put(packet);
    }
  else if( Slot *slot=avail_list.top )
    {
     slot->inbound_CALL(complete_list,point,trans_id,client_slot,packet,client_info);

     activate(slot);

     prepare.complete(slot);
    }
  else
    {
     stat.count(ServerEvent_CALL);
     stat.count(ServerEvent_NoFreeSlot);

     complete_list.put(packet);
    }
 }

void ServerEngine::inbound_RECALL(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,RecallNumber recall_number,Packet<uint8> packet,PtrLen<const uint8> client_info)
 {
  TreeAlgo::PrepareIns prepare(active_tree,Key(point,trans_id));

  if( Slot *slot=prepare.found )
    {
     complete_list.put(packet);

     slot->inbound_RECALL(complete_list,client_slot,recall_number);
    }
  else if( Slot *slot=avail_list.top )
    {
     slot->inbound_RECALL_first(complete_list,point,trans_id,client_slot,packet,client_info,recall_number);

     activate(slot);

     prepare.complete(slot);
    }
  else
    {
     stat.count(ServerEvent_RECALL);
     stat.count(ServerEvent_NoFreeSlot);

     complete_list.put(packet);
    }
 }

void ServerEngine::inbound_ACK(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId,SlotId server_slot,Packet<uint8> packet)
 {
  if( Slot *slot=find(point,server_slot,trans_id) )
    {
     slot->inbound_ACK(cancel,complete_list);

     deactivate(slot);
    }
  else
    {
     stat.count(ServerEvent_ACK);

     stat.count(ServerEvent_NoSlot);
    }

  complete_list.put(packet);
 }

void ServerEngine::inbound_SENDRET(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,SlotId server_slot,Packet<uint8> packet)
 {
  if( Slot *slot=find(point,server_slot,trans_id) )
    {
     slot->inbound_SENDRET(complete_list);
    }
  else
    {
     stat.count(ServerEvent_SENDRET);

     send_CANCEL(complete_list,point,trans_id,client_slot,server_slot);
    }

  complete_list.put(packet);
 }

void ServerEngine::send_CANCEL(PacketList &complete_list,XPoint point,const TransId &trans_id,SlotId client_slot,SlotId server_slot)
 {
  stat.count(ServerEvent_NoSlotCancel);
  stat.count(ServerEvent_CANCEL);

  PacketPrefix4 prefix(PacketType_CANCEL,trans_id,client_slot,server_slot);

  send(complete_list,point,prefix,getDataPacket());
 }

Packet<uint8> ServerEngine::getDataPacket()
 {
  Packet<uint8> packet=pset.try_get();

  if( !packet ) stat.count(ServerEvent_NoPacket);

  return packet;
 }

Packet<uint8> ServerEngine::getDataPacket(PacketSet<uint8>::ExtTop &plist)
 {
  Packet<uint8> packet=pset.try_get(plist);

  if( !packet ) stat.count(ServerEvent_NoPacket);

  return packet;
 }

void ServerEngine::send(PacketList &complete_list,XPoint point,Packet<uint8> data_packet)
 {
  data_packet.pushCompleteFunction(function_send());

  complete_list.put(data_packet.pushExt<XPoint>(point));
 }

void ServerEngine::inbound_locked(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list,XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
 {
  Mutex::Lock lock(mutex);

  RangeGetDev dev(data);

  PacketPrefix3 prefix;

  dev(prefix);

  if( !dev ) return bad_inbound(complete_list,packet);

  switch( prefix.type )
    {
     case PacketType_CALL :
      {
       Packet_CALL3 suffix;

       dev(suffix);

       if( suffix.len>max_inbound_info_len ) return bad_inbound(complete_list,packet);

       PtrLen<const uint8> client_info=dev.getFinalRange(suffix.len);

       if( !dev.finish() ) return bad_inbound(complete_list,packet);

       inbound_CALL(complete_list,point,prefix.trans_id,prefix.client_slot,packet,client_info);
      }
     break;

     case PacketType_RECALL :
      {
       Packet_RECALL3 suffix;

       dev(suffix);

       if( suffix.len>max_inbound_info_len ) return bad_inbound(complete_list,packet);

       PtrLen<const uint8> client_info=dev.getFinalRange(suffix.len);

       if( !dev.finish() ) bad_inbound(complete_list,packet);

       inbound_RECALL(complete_list,point,prefix.trans_id,prefix.client_slot,suffix.recall_number,packet,client_info);
      }
     break;

     case PacketType_ACK :
      {
       Packet_control3 suffix;

       dev(suffix);

       if( !dev.finish() ) return bad_inbound(complete_list,packet);

       inbound_ACK(cancel,complete_list,point,prefix.trans_id,prefix.client_slot,suffix.server_slot,packet);
      }
     break;

     case PacketType_SENDRET :
      {
       Packet_control3 suffix;

       dev(suffix);

       if( !dev.finish() ) return bad_inbound(complete_list,packet);

       inbound_SENDRET(complete_list,point,prefix.trans_id,prefix.client_slot,suffix.server_slot,packet);
      }
     break;

     default: return bad_inbound(complete_list,packet);
    }
 }

void ServerEngine::tick_locked(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list)
 {
  Mutex::Lock lock(mutex);

  auto cur=active_list.start();

  while( +cur )
    {
     if( cur->tick(cancel,complete_list) )
       {
        ++cur;
       }
     else
       {
        Slot *slot=active_list.del_and_move(cur);

        deactivate_nodel(slot);
       }
    }
 }

void ServerEngine::cancelAll_locked(PacketSet<uint8>::Cancel &cancel,PacketList &complete_list)
 {
  Mutex::Lock lock(mutex);

  while( Slot *slot=active_list.top )
    {
     stat.count(slot->server_slot,ServerEvent_Abort);

     slot->finish(cancel,complete_list);

     deactivate(slot);
    }
 }

void ServerEngine::cancelFrom_locked(XPoint point,PacketSet<uint8>::Cancel &cancel,PacketList &complete_list)
 {
  Mutex::Lock lock(mutex);

  auto cur=active_list.start();

  while( +cur )
    {
     if( cur->point!=point )
       {
        ++cur;
       }
     else
       {
        Slot *slot=active_list.del_and_move(cur);

        stat.count(slot->server_slot,ServerEvent_Abort);

        slot->finish(cancel,complete_list);

        deactivate_nodel(slot);
       }
    }
 }

void ServerEngine::send_info_locked(PacketList &complete_list,TransIndex idx,Packet<uint8> proc_packet,PtrLen<const uint8> server_info)
 {
  Mutex::Lock lock(mutex);

  if( idx.slot<slots.getLen() )
    {
     Slot *slot=slots.getPtr()+idx.slot;

     if( slot->active && slot->index==idx.index && slot->state==Slot::State_pending )
       {
        slot->send_info(complete_list,proc_packet,server_info);

        return;
       }
    }

  complete_list.put(proc_packet);
 }

void ServerEngine::send_cancel_locked(PacketList &complete_list,TransIndex idx)
 {
  Mutex::Lock lock(mutex);

  if( idx.slot<slots.getLen() )
    {
     Slot *slot=slots.getPtr()+idx.slot;

     if( slot->active && slot->index==idx.index && slot->state==Slot::State_pending )
       {
        slot->send_cancel(complete_list);
       }
    }
 }

void ServerEngine::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
 {
  PacketSet<uint8>::Cancel cancel(pset);

  PacketList complete_list;

  inbound_locked(cancel,complete_list,point,packet,data);

  complete_list.complete();

  cancel.cancel();
 }

void ServerEngine::tick()
 {
  PacketSet<uint8>::Cancel cancel(pset);

  PacketList complete_list;

  tick_locked(cancel,complete_list);

  complete_list.complete();

  cancel.cancel();

  Hook hook(host);

  if( +hook ) hook->tick();
 }

void ServerEngine::connection_open(XPoint point)
 {
  cancelFrom(point);

  Hook hook(host);

  if( +hook )
    {
     if( PacketMultipointDevice::ConnectionProc *proc=hook->pickInterface<PacketMultipointDevice::ConnectionProc>() ) proc->connection_open(point);
    }
 }

void ServerEngine::connection_lost(XPoint point)
 {
  cancelFrom(point);

  Hook hook(host);

  if( +hook )
    {
     if( PacketMultipointDevice::ConnectionProc *proc=hook->pickInterface<PacketMultipointDevice::ConnectionProc>() ) proc->connection_lost(point);
    }
 }

void ServerEngine::connection_close(XPoint point)
 {
  cancelFrom(point);

  Hook hook(host);

  if( +hook )
    {
     if( PacketMultipointDevice::ConnectionProc *proc=hook->pickInterface<PacketMultipointDevice::ConnectionProc>() ) proc->connection_close(point);
    }
 }

void ServerEngine::do_send(PacketHeader *packet_)
 {
  Packet<uint8,XPoint> data_packet=packet_;

  XPoint point=*data_packet.getExt();

  mp->outbound(point,data_packet.popExt());
 }

ServerEngine::ServerEngine(ulen max_slots)
 : mutex("PTP::ServerEngine.mutex"),
   host("PTP::ServerEngine","PTP::ServerEngine.host"),
   slots(max_slots),
   pset("PTP::ServerEngine.pset",2*max_slots),
   slots_asem("PTP::ServerEngine.slots_asem")
 {
  mp=0;

  max_outbound_info_len=MaxInfoLen;
  max_inbound_info_len=MaxInfoLen;

  for(SlotId server_slot=0; server_slot<max_slots ;server_slot++)
    {
     Slot *slot=slots.getPtr()+server_slot;

     slot->init(this,server_slot);

     avail_list.ins_last(slot);
    }
 }

ServerEngine::~ServerEngine()
 {
  if( mp ) mp->detach();

  cancelAll();
 }

void ServerEngine::attach_to(PacketMultipointDevice *mp_)
 {
  outbound_format=mp_->getOutboundFormat();

  const char *name="CCore::Net::PTP::ServerEngine::attach_to(...)";

  max_outbound_info_len=LenSub(name,Min(outbound_format.max_data,MaxPacketLen),DeltaInfoLen);

  max_inbound_info_len=LenSub(name,Min(mp_->getMaxInboundLen(),MaxPacketLen),DeltaInfoLen);

  mp_->attach(this);

  mp=mp_;
 }

void ServerEngine::cancelAll()
 {
  PacketSet<uint8>::Cancel cancel(pset);

  PacketList complete_list;

  cancelAll_locked(cancel,complete_list);

  complete_list.complete();

  cancel.cancel();
 }

void ServerEngine::cancelFrom(XPoint point)
 {
  PacketSet<uint8>::Cancel cancel(pset);

  PacketList complete_list;

  cancelFrom_locked(point,cancel,complete_list);

  complete_list.complete();

  cancel.cancel();
 }

void ServerEngine::getStat(ServerStatInfo &ret)
 {
  Mutex::Lock lock(mutex);

  ret=stat;
 }

void ServerEngine::send_info(TransIndex idx,Packet<uint8> proc_packet,PtrLen<const uint8> server_info)
 {
  PacketList complete_list;

  send_info_locked(complete_list,idx,proc_packet,server_info);

  complete_list.complete();
 }

void ServerEngine::send_cancel(TransIndex idx)
 {
  PacketList complete_list;

  send_cancel_locked(complete_list,idx);

  complete_list.complete();
 }

void ServerEngine::attach(ServerProc *proc)
 {
  host.attach(proc);
 }

void ServerEngine::detach()
 {
  host.detach();
 }

/* class ServerDevice */

const Unid ServerDevice::TypeUnid={{0xBA6F'AFCD,0x1DCA'110E,0xB952'D7DB,0xF419'5C26,0xF793'014B,0xD06F'E096,0xCA9C'9D62,0xF4F2'1910}};

ServerDevice::ServerDevice(StrLen mp_dev_name,ulen max_slots)
 : hook(mp_dev_name),
   engine(max_slots)
 {
  PacketMultipointDevice *mp=hook;

  engine.attach_to(mp);
 }

ServerDevice::~ServerDevice()
 {
 }

void ServerDevice::getStat(ServerStatInfo &ret)
 {
  engine.getStat(ret);
 }

void ServerDevice::send_info(TransIndex idx,Packet<uint8> proc_packet,PtrLen<const uint8> server_info)
 {
  engine.send_info(idx,proc_packet,server_info);
 }

void ServerDevice::send_cancel(TransIndex idx)
 {
  engine.send_cancel(idx);
 }

void ServerDevice::attach(ServerProc *proc)
 {
  engine.attach(proc);
 }

void ServerDevice::detach()
 {
  engine.detach();
 }

} // namespace PTP
} // namespace Net
} // namespace CCore


