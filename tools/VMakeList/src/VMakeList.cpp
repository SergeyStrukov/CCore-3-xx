/* VMakeList.cpp */
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

#include <inc/VMakeList.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

namespace App {

#include "VMakeList.TypeSet.gen.h"

/* class DataFile */

StrLen DataFile::Pretext()
 {
  return

#include "VMakeList.Pretext.gen.h"

  ""_c;
 }

DataFile::DataFile(StrLen file_name)
 {
  // process

  PrintCon eout;

  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(Range(file_name),Pretext());

  eout.flush();

  if( !result )
    {
     Printf(Exception,"VMakeList file #.q; : load failed",file_name);
    }

  // map

  DDL::TypedMap<TypeSet> map(result);
  MemAllocGuard guard(map.getLen());

  map(guard);

  param=map.findConst<TypeDef::Param>("Data");

  if( !param )
    {
     Printf(Exception,"VMakeList file #.q; : no data",file_name);
    }

  mem=guard.disarm();
 }

DataFile::~DataFile()
 {
  MemFree(Replace_null(mem));
 }

} // namespace App

