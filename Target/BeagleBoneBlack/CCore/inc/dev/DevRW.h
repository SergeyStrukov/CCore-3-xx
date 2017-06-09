/* DevRW.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_dev_DevRW_h
#define CCore_inc_dev_DevRW_h

#include <CCore/inc/Gadget.h>

namespace CCore {
namespace Dev {

/* types */

using AddressType = uint32 ;

/* concept RegType */

template <class UInt>
concept bool RegisterType = OneOfTypes<UInt,uint8,uint16,uint32> ;

/* functions */

template <RegisterType UInt>
UInt VarGet(const void *ptr) noexcept;

template <RegisterType UInt>
void VarSet(void *ptr,UInt value) noexcept;

template <RegisterType UInt>
UInt VarGet(AddressType address) { return VarGet<UInt>((const void *)address); }

template <RegisterType UInt>
void VarSet(AddressType address,UInt value) { VarSet<UInt>((void *)address,value); }

/* classes */

class RegRW;

/* class RegRW */

class RegRW
 {
  public:

   using AddressType = uint32 ;

  private:

   AddressType base_address;

  public:

   explicit RegRW(AddressType base_address_) : base_address(base_address_) {}

   template <RegisterType UInt>
   UInt get(AddressType address) { return VarGet<UInt>(base_address+address); }

   template <RegisterType UInt>
   void set(AddressType address,UInt value) { VarSet<UInt>(base_address+address,value); }
 };

} // namespace Dev
} // namespace CCore

#endif


