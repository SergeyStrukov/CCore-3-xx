/* PTPSupportBase.h */
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

#ifndef CCore_inc_net_PTPSupportBase_h
#define CCore_inc_net_PTPSupportBase_h

#include <CCore/inc/net/PTPExtra.h>

namespace CCore {
namespace Net {
namespace PTPSupport {

/* using */

using namespace PTP;

/* consts */

inline constexpr ServiceIdType ServiceId = 1 ;

inline constexpr FunctionIdType FunctionId_Len       = 1 ;
inline constexpr FunctionIdType FunctionId_Seed      = 2 ;
inline constexpr FunctionIdType FunctionId_Session   = 3 ;
inline constexpr FunctionIdType FunctionId_Echo      = 4 ;
inline constexpr FunctionIdType FunctionId_ErrorDesc = 5 ;
inline constexpr FunctionIdType FunctionId_Exist     = 6 ;

inline constexpr uint32 MaxDelay = 1000*60*60 ; // 1 hour

/* classes */

struct LenInput;
struct LenOutput;

using SeedInput = Empty ;
struct SeedOutput;

using SessionInput = Empty ;
using SessionOutput = Empty ;

struct EchoInput;
struct EchoOutput;

struct ErrorDescInput;
struct ErrorDescOutput;

struct ExistInput;
struct ExistOutput;

/* struct LenInput */

struct LenInput
 {
  LenType to_server_info_len;
  LenType to_client_info_len;

  // constructors

  LenInput() : to_server_info_len(),to_client_info_len() {}

  LenInput(LenType to_server_info_len_,LenType to_client_info_len_)
   : to_server_info_len(to_server_info_len_),to_client_info_len(to_client_info_len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<LenType,LenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(to_server_info_len,to_client_info_len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(to_server_info_len,to_client_info_len);
   }
 };

/* struct LenOutput */

struct LenOutput
 {
  LenType to_server_info_len;
  LenType to_client_info_len;

  // constructors

  LenOutput() : to_server_info_len(),to_client_info_len() {}

  LenOutput(LenType to_server_info_len_,LenType to_client_info_len_)
   : to_server_info_len(to_server_info_len_),to_client_info_len(to_client_info_len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<LenType,LenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(to_server_info_len,to_client_info_len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(to_server_info_len,to_client_info_len);
   }
 };

/* struct SeedOutput */

struct SeedOutput
 {
  uint64 seed1;
  uint64 seed2;

  // constructors

  SeedOutput() : seed1(),seed2() {}

  SeedOutput(uint64 seed1_,uint64 seed2_) : seed1(seed1_),seed2(seed2_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint64,uint64>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(seed1,seed2);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(seed1,seed2);
   }
 };

/* struct EchoInput */

struct EchoInput // + uint8 data[len];
 {
  static constexpr ulen MaxLen = 255 ;

  uint32 delay_msec;
  uint8 len;

  // constructors

  EchoInput() : delay_msec(),len() {}

  EchoInput(uint32 delay_msec_,uint8 len_) : delay_msec(delay_msec_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint32,uint8>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(delay_msec,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(delay_msec,len);
   }
 };

/* struct EchoOutput */

struct EchoOutput // + uint8 data[len];
 {
  static constexpr ulen MaxLen = 255 ;

  uint8 len;

  // constructors

  EchoOutput() : len() {}

  explicit EchoOutput(uint8 len_) : len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint8>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(len);
   }
 };

/* struct ErrorDescInput */

struct ErrorDescInput
 {
  ServiceIdType service_id;
  FunctionIdType function_id;
  ErrorIdType error_id;

  // constructors

  ErrorDescInput() : service_id(),function_id(),error_id() {}

  ErrorDescInput(ServiceIdType service_id_,FunctionIdType function_id_,ErrorIdType error_id_)
   : service_id(service_id_),function_id(function_id_),error_id(error_id_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<ServiceIdType,FunctionIdType,ErrorIdType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(service_id,function_id,error_id);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(service_id,function_id,error_id);
   }
 };

/* struct ErrorDescOutput */

struct ErrorDescOutput // + uint8 str[len];
 {
  static constexpr ulen MaxLen = 255 ;

  uint8 len;

  // constructors

  ErrorDescOutput() : len() {}

  explicit ErrorDescOutput(uint8 len_) : len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint8>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(len);
   }
 };

/* struct ExistInput */

struct ExistInput
 {
  ServiceIdType service_id;
  FunctionIdType function_id;

  // constructors

  ExistInput() : service_id(),function_id() {}

  ExistInput(ServiceIdType service_id_,FunctionIdType function_id_)
   : service_id(service_id_),function_id(function_id_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<ServiceIdType,FunctionIdType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(service_id,function_id);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(service_id,function_id);
   }
 };

/* struct ExistOutput */

struct ExistOutput
 {
  ServiceIdType service_id;
  FunctionIdType function_id;
  ErrorIdType error_id;

  // constructors

  ExistOutput() : service_id(),function_id(),error_id() {}

  ExistOutput(ExistInput input,ErrorIdType error_id_)
   : service_id(input.service_id),function_id(input.function_id),error_id(error_id_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<ServiceIdType,FunctionIdType,ErrorIdType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(service_id,function_id,error_id);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(service_id,function_id,error_id);
   }
 };

} // namespace PTPSupport
} // namespace Net
} // namespace CCore

#endif


