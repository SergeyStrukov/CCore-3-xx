/* PTPBootBase.h */
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

#ifndef CCore_inc_net_PTPBootBase_h
#define CCore_inc_net_PTPBootBase_h

#include <CCore/inc/net/PTPExtra.h>

namespace CCore {
namespace Net {
namespace PTPBoot {

/* using */

using namespace PTP;

/* consts */

inline constexpr ulen DeltaWriteLen   =   24 ;
inline constexpr ulen MaxWriteDataLen = 1416 ; // MaxInfoLen-DeltaWriteLen

inline constexpr ServiceIdType ServiceId = 4 ;

inline constexpr FunctionIdType FunctionId_Alloc = 1 ;
inline constexpr FunctionIdType FunctionId_Write = 2 ;
inline constexpr FunctionIdType FunctionId_Boot  = 3 ;

/* types */

using AddressType = uint64 ;

using IndexType = uint32 ;

/* classes */

struct AllocInput;
struct AllocOutput;

struct WriteInput;
using WriteOutput = Empty ;

struct BootInput;
using BootOutput = Empty ;

/* struct AllocInput */

struct AllocInput
 {
  AddressType address;
  AddressType len;

  // constructors

  AllocInput() : address(),len() {}

  AllocInput(AddressType address_,AddressType len_) : address(address_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<AddressType,AddressType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(address,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(address,len);
   }
 };

/* struct AllocOutput */

struct AllocOutput
 {
  IndexType index;

  // constructors

  AllocOutput() : index() {}

  explicit AllocOutput(IndexType index_) : index(index_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<IndexType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(index);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(index);
   }
 };

/* struct WriteInput */

struct WriteInput // + uint8 data[len];
 {
  static constexpr ulen MaxLen = MaxWriteDataLen ;

  IndexType index;
  AddressType off;
  LenType len;

  // constructors

  WriteInput() : index(),off(),len() {}

  WriteInput(IndexType index_,AddressType off_,LenType len_) : index(index_),off(off_),len(len_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<IndexType,AddressType,LenType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(index,off,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(index,off,len);
   }
 };

/* struct BootInput */

struct BootInput
 {
  AddressType entry_point;
  FlagType flags;

  // constructors

  BootInput() : entry_point(),flags() {}

  BootInput(AddressType entry_point_,FlagType flags_) : entry_point(entry_point_),flags(flags_) {}

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<AddressType,FlagType>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(entry_point,flags);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(entry_point,flags);
   }
 };

} // namespace PTPBoot
} // namespace Net
} // namespace CCore

#endif


