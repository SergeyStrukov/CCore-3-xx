/* VMakeData.h */
//----------------------------------------------------------------------------------------
//
//  Project: vmake 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_VMakeData_h
#define App_VMakeData_h

#include <CCore/inc/Array.h>

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

namespace VMake {

#ifndef App_vmaketypedef_h
#define App_vmaketypedef_h

#include "vmake.TypeDef.gen.h"

#endif

/* classes */

class DataFile;

/* class DataFile */

class DataFile : NoCopy
 {
   void *mem = 0 ;

   TypeDef::Target *target = 0 ;

   DynArray<TypeDef::Rule *> rules;
   DynArray<TypeDef::Dep *> deps;

  private:

   static StrLen Pretext();

  public:

   DataFile(StrLen file_name,StrLen target_name);

   ~DataFile();

   TypeDef::Target * getTarget() const { return target; }

   PtrLen<TypeDef::Rule *const> getRules() const { return Range(rules); }

   PtrLen<TypeDef::Dep *const> getDeps() const { return Range(deps); }
 };

} // namespace VMake
} // namespace App

#endif


