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

/* functions */

StrLen Pretext()
 {
  return

#include "VMakeList.Pretext.gen.h"

  ""_c;
 }

/* class DataFile */

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

  param=map.findConst<TypeDef::Param>("Data"_c);

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

/* class ToolFile */

ToolFile::ToolFile(StrLen file_name)
 {
  // process

  PrintCon eout;

  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(Range(file_name),Pretext());

  eout.flush();

  if( !result )
    {
     Printf(Exception,"VMakeList tools file #.q; : load failed",file_name);
    }

  // map

  DDL::TypedMap<TypeSet> map(result);
  MemAllocGuard guard(map.getLen());

  map(guard);

  tools=map.findConst<TypeDef::Tools>("Data"_c);

  if( !tools )
    {
     Printf(Exception,"VMakeList tools file #.q; : no data",file_name);
    }

  mem=guard.disarm();
 }

ToolFile::~ToolFile()
 {
  MemFree(Replace_null(mem));
 }

/* class TargetFile */

TargetFile::TargetFile(StrLen file_name)
 {
  // process

  PrintCon eout;

  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(Range(file_name));

  eout.flush();

  if( !result )
    {
     Printf(Exception,"VMakeList target file #.q; : load failed",file_name);
    }

  // map

  DDL::TypedMap<DDL::EmptyTypeSet> map(result);
  MemAllocGuard guard(map.getLen());

  map(guard);

  DDL::MapText *ptr=map.findConst<DDL::MapText>("CCORE_TARGET"_c);

  if( !ptr )
    {
     Printf(Exception,"VMakeList target file #.q; : no target",file_name);
    }

  target=*ptr;

  mem=guard.disarm();
 }

TargetFile::~TargetFile()
 {
  MemFree(Replace_null(mem));
 }

} // namespace App

