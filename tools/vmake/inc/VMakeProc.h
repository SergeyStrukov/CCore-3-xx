/* VMakeProc.h */
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

#ifndef App_VMakeProc_h
#define App_VMakeProc_h

#include <CCore/inc/String.h>
#include <CCore/inc/Array.h>

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

namespace VMake {

#include "vmake.TypeDef.gen.h"

/* classes */

class DataFile;

class DataProc;

/* class DataFile */

class DataFile : NoCopy
 {
   void *mem = 0 ;

   DynArray<TypeDef::Rule *> rules;
   DynArray<TypeDef::Dep *> deps;

   TypeDef::Target *target;

  private:

   static StrLen Pretext();

  public:

   DataFile(StrLen file_name,StrLen target_name);

   ~DataFile();

   TypeDef::Target * getTarget() const { return target; }

   PtrLen<TypeDef::Rule *const> getRules() const { return Range(rules); }

   PtrLen<TypeDef::Dep *const> getDeps() const { return Range(deps); }
 };

/* class DataProc */

class DataProc : NoCopy
 {
  public:

   DataProc(StrLen file_name,StrLen target);

   DataProc(StrLen file_name,StrLen target,StrLen wdir);

   ~DataProc();

   int make();
 };

} // namespace VMake

} // namespace App

#endif

