/* DDLMapBase.h */
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

#ifndef CCore_inc_ddl_DDLMapBase_h
#define CCore_inc_ddl_DDLMapBase_h

#include <CCore/inc/MemBase.h>

namespace CCore {
namespace DDL {

/* classes */

class MapBase;

/* class MapBase */

class MapBase : NoCopy
 {
   class MemHook : NoCopy
    {
      void *mem;

     public:

      explicit MemHook(ulen len) { mem=MemAlloc(len); }

      ~MemHook() { MemFree(mem); }

      void * getMem() const { return mem; }
    };

   MemHook hook;

  public:

   template <class Map>
   explicit MapBase(Map &map)
    : hook(map.getLen())
    {
     map(hook.getMem());
    }

   ~MapBase()
    {
    }
 };

} // namespace DDL
} // namespace CCore

#endif


