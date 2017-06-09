/* PTPBase.h */
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

#ifndef CCore_inc_net_PTPBase_h
#define CCore_inc_net_PTPBase_h

#include <CCore/inc/SaveLoad.h>

namespace CCore {
namespace Net {
namespace PTP {

/* types */

using PacketType = uint32 ;

using SlotId = uint32 ;

using RecallNumber = uint32 ;

using InfoLenType = uint32 ;

/* consts */

inline constexpr ulen MaxPacketLen = 1472 ;
inline constexpr ulen DeltaInfoLen =   32 ;
inline constexpr ulen MaxInfoLen   = 1440 ;

inline constexpr unsigned MinTimeout   =   300 ; // msec
inline constexpr unsigned MaxTimeout   = 10000 ; // msec
inline constexpr unsigned DeltaTimeout =   100 ; // msec

inline constexpr PacketType PacketType_CALL    = 1 ; // toServer , info
inline constexpr PacketType PacketType_RET     = 2 ; // toClient , info
inline constexpr PacketType PacketType_RECALL  = 3 ; // toServer , info
inline constexpr PacketType PacketType_ACK     = 4 ; // toServer
inline constexpr PacketType PacketType_NOINFO  = 5 ; // toClient
inline constexpr PacketType PacketType_RERET   = 6 ; // toClient
inline constexpr PacketType PacketType_SENDRET = 7 ; // toServer
inline constexpr PacketType PacketType_CANCEL  = 8 ; // toClient

/* classes */

struct TransId;

struct PacketPrefix3;

struct PacketPrefix4;

struct Packet_CALL3;

struct Packet_RET3;

struct Packet_RET4;

struct Packet_RECALL3;

struct Packet_control3; // ACK, NOINFO, RERET, SENDRET, CANCEL

/* struct TransId */

struct TransId
 {
  uint64 number;
  uint64 clock;

  // constructors

  TransId() : number(),clock() {}

  // methods

  friend bool operator == (const TransId &a,const TransId &b)
   {
    return a.number==b.number && a.clock==b.clock ;
   }

  friend bool operator != (const TransId &a,const TransId &b) { return !(a==b); }

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint64,uint64>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(number,clock);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(number,clock);
   }
 };

/* struct PacketPrefix3 */

struct PacketPrefix3
 {
  PacketType type;
  TransId trans_id;
  SlotId client_slot;

  // constructors

  PacketPrefix3() : type(),trans_id(),client_slot() {}

  PacketPrefix3(PacketType type_,const TransId &trans_id_,SlotId client_slot_)
   : type(type_),trans_id(trans_id_),client_slot(client_slot_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<PacketType,TransId,SlotId>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(type,trans_id,client_slot);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(type,trans_id,client_slot);
   }
 };

/* struct PacketPrefix4 */

struct PacketPrefix4
 {
  PacketType type;
  TransId trans_id;
  SlotId client_slot;
  SlotId server_slot;

  // constructors

  PacketPrefix4() : type(),trans_id(),client_slot(),server_slot() {}

  PacketPrefix4(PacketType type_,const TransId &trans_id_,SlotId client_slot_,SlotId server_slot_)
   : type(type_),trans_id(trans_id_),client_slot(client_slot_),server_slot(server_slot_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<PacketType,TransId,SlotId,SlotId>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(type,trans_id,client_slot,server_slot);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(type,trans_id,client_slot,server_slot);
   }
 };

/* struct Packet_CALL3 */

struct Packet_CALL3 // + uint8 info[len];
 {
  InfoLenType len;

  // constructors

  Packet_CALL3() : len() {}

  explicit Packet_CALL3(InfoLenType len_) : len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<InfoLenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(len);
   }
 };

/* struct Packet_RET3 */

struct Packet_RET3 // + uint8 info[len];
 {
  SlotId server_slot;
  InfoLenType len;

  // constructors

  Packet_RET3() : server_slot(),len() {}

  Packet_RET3(SlotId server_slot_,InfoLenType len_) : server_slot(server_slot_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<SlotId,InfoLenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(server_slot,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(server_slot,len);
   }
 };

/* struct Packet_RET4 */

struct Packet_RET4 // + uint8 info[len];
 {
  InfoLenType len;

  // constructors

  Packet_RET4() : len() {}

  explicit Packet_RET4(InfoLenType len_) : len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<InfoLenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(len);
   }
 };

/* struct Packet_RECALL3 */

struct Packet_RECALL3 // + uint8 info[len];
 {
  RecallNumber recall_number;
  InfoLenType len;

  // constructors

  Packet_RECALL3() : recall_number(),len() {}

  Packet_RECALL3(RecallNumber recall_number_,InfoLenType len_) : recall_number(recall_number_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<RecallNumber,InfoLenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(recall_number,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(recall_number,len);
   }
 };

/* struct Packet_control3 */

struct Packet_control3
 {
  SlotId server_slot;

  // constructors

  Packet_control3() : server_slot() {}

  explicit Packet_control3(SlotId server_slot_) : server_slot(server_slot_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<SlotId>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(server_slot);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(server_slot);
   }
 };

} // namespace PTP
} // namespace Net
} // namespace CCore

#endif


