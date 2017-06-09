/* InterfaceHost.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_InterfaceHost_h
#define CCore_inc_InterfaceHost_h

#include <CCore/inc/TypeNumber.h>

namespace CCore {

/* functions */

void GuardNoInterface(StrLen from,StrLen name);

/* classes */

template <class T> struct GetInterfaceName;

struct InterfaceCaster;

struct InterfaceHost;

template <UnidType T> class InterfaceCasterTo;

/* concept Has_InterfaceName<T> */

template <class T>
concept bool Has_InterfaceName = requires() { { T::InterfaceName } -> StrLen ; } ;

/* concept No_InterfaceName<T> */

template <class T>
concept bool No_InterfaceName = !Has_InterfaceName<T> ;

/* struct GetInterfaceName<T> */

template <Has_InterfaceName T>
struct GetInterfaceName<T> : StrLen
 {
  GetInterfaceName() : StrLen(T::InterfaceName) {}
 };

template <No_InterfaceName T>
struct GetInterfaceName<T> : StrLen
 {
  GetInterfaceName() : StrLen("<Unknown interface>"_c) {}
 };

/* struct InterfaceCaster */

struct InterfaceCaster
 {
  virtual void cast(InterfaceHost *obj)=0;

  virtual TypeNumber getTypeNumber()=0;
 };

/* struct InterfaceHost */

struct InterfaceHost
 {
  virtual void requestInterface(InterfaceCaster &caster) { caster.cast(this); }

  template <UnidType T>
  T * pickInterface()
   {
    InterfaceCasterTo<T> caster;

    requestInterface(caster);

    return caster;
   }

  template <UnidType T>
  T * takeInterface(StrLen from)
   {
    T *ret=pickInterface<T>();

    if( !ret ) GuardNoInterface(from,GetInterfaceName<T>());

    return ret;
   }
 };

/* class InterfaceCasterTo<T> */

template <UnidType T>
class InterfaceCasterTo : public InterfaceCaster
 {
   T *ret;

  private:

   virtual void cast(InterfaceHost *obj) { ret=dynamic_cast<T *>(obj); }

   virtual TypeNumber getTypeNumber() { return TypeNumberOf<T>(); }

  public:

   InterfaceCasterTo() : ret(0) {}

   operator T * () const { return ret; }
 };

} // namespace CCore

#endif


