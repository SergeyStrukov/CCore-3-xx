/* VMakeList.h */
//----------------------------------------------------------------------------------------
//
//  Project: VMakeList 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_VMakeList_h
#define App_VMakeList_h

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

#include "VMakeList.TypeDef.gen.h"

/* functions */

StrLen Pretext();

/* classes */

class DataFile;

class ToolFile;

class TargetFile;

/* class DataFile */

class DataFile : NoCopy
 {
   void *mem = 0 ;

   TypeDef::Param * param = 0 ;

  public:

   explicit DataFile(StrLen file_name);

   ~DataFile();

   TypeDef::Param * getParam() const { return param; }
 };

/* class ToolFile */

class ToolFile : NoCopy
 {
   void *mem = 0 ;

   TypeDef::Tools * tools = 0 ;

  public:

   explicit ToolFile(StrLen file_name);

   ~ToolFile();

   TypeDef::Tools * getTools() const { return tools; }
 };

/* class TargetFile */

class TargetFile : NoCopy
 {
   void *mem = 0 ;

   StrLen target;

  public:

   explicit TargetFile(StrLen file_name);

   ~TargetFile();

   StrLen getTarget() const { return target; }
 };

} // namespace App

#endif


