/* VMakeIntCmd.h */
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

#ifndef App_VMakeIntCmd_h
#define App_VMakeIntCmd_h

#include <CCore/inc/ExpandWildcard.h>

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

namespace VMake {

/* classes */

class IntCmdProc;

/* class IntCmdProc */

class IntCmdProc : NoCopy
 {
   FileSystem fs;

  public:

   IntCmdProc();

   ~IntCmdProc();

   // check

   bool checkExist(StrLen wdir,StrLen dst);

   CmpFileTimeType getFileTime(StrLen wdir,StrLen file);

   bool checkOlder(StrLen wdir,StrLen dst,StrLen src); // dst.noexist OR dst.time < src.time

   // commands

   int echo(StrLen wdir,PtrLen<DDL::MapText> strs,StrLen outfile);

   int cat(StrLen wdir,PtrLen<DDL::MapText> files,StrLen outfile);

   int rm(StrLen wdir,PtrLen<DDL::MapText> files);

   int mkdir(StrLen wdir,PtrLen<DDL::MapText> paths);
 };

} // namespace VMake
} // namespace App

#endif


