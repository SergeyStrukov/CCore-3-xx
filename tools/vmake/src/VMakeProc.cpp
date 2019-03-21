/* VMakeProc.cpp */
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

#include <inc/VMakeProc.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/ForLoop.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

namespace App {

namespace VMake {

#include "vmake.TypeSet.gen.h"

/* class DataFile */

StrLen DataFile::Pretext()
 {
  return

#include "vmake.Pretext.gen.h"

  ""_c;
 }

DataFile::DataFile(StrLen file_name,StrLen target_name)
 {
  // process

  PrintCon eout;

  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(Range(file_name),Pretext());

  if( !result )
    {
     eout.flush();

     Printf(Exception,"App::VMake::DataFile::DataFile(#.q;) : load failed",file_name);
    }

  // map

  DDL::TypedMap<TypeSet> map(result);
  MemAllocGuard guard(map.getLen());

  map(guard);

  mem=guard.disarm();

  target=map.findConst<TypeDef::Target>(target_name);

  // extract

  Collector<TypeDef::Rule *> rule_list;
  Collector<TypeDef::Dep *> dep_list;

  auto list=Range(result.eval->const_table);

  for(ulen ind : IndLim(list.len) )
    {
     DDL::ConstResult &item=list[ind];

     if( DDL::StructNode *node=DDL::IsStructType(item.type) )
       {
        if( node->depth==0 )
          {
           StrLen name=node->name.name.str;

           if( name.equal("Rule"_c) )
             {
              StrLen objname=item.node->name.name.str;

              rule_list.append_copy(static_cast<TypeDef::Rule *>(map.constPlace(ind)));

              Printf(Con,"Rule #;\n",objname);
             }
           else if( name.equal("Dep"_c) )
             {
              StrLen objname=item.node->name.name.str;

              dep_list.append_copy(static_cast<TypeDef::Dep *>(map.constPlace(ind)));

              Printf(Con,"Dep #;\n",objname);
             }
          }
       }
    }

  // build tables

  rule_list.extractTo(rules);
  dep_list.extractTo(deps);
 }

DataFile::~DataFile()
 {
  MemFree(Replace_null(mem));
 }

/* class DataProc */

} // namespace VMake

} // namespace App

