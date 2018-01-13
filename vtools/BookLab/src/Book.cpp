/* Book.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Book.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

namespace App {
namespace Book {

#include "Book.TypeSet.gen.h"

/* class BookMap */

StrLen BookMap::Pretext()
 {
  return ""_c;
 }

BookMap::BookMap()
 {
  mem=0;
  book=0;
 }

BookMap::~BookMap()
 {
  blank();
 }

void BookMap::blank()
 {
  book=0;

  MemFree(Replace_null(mem));
 }

auto BookMap::load(StrLen file_name,PtrLen<char> ebuf) -> Result
 {
  blank();

  PrintBuf eout(ebuf);

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     DDL::FileEngine<FileName,FileToMem> engine(eout);

     auto result=engine.process(file_name,Pretext());

     if( !result )
       {
        Printf(eout,"\n@ #.q;",file_name);

        return eout.close();
       }
     else
       {
        DDL::TypedMap<TypeSet> map(result);
        MemAllocGuard guard(map.getLen());

        map(guard);

        if( TypeDef::Book *data=map.findConst<TypeDef::Book>("Data"_c) )
          {
           mem=guard.disarm();
           book=data;

           return {};
          }
        else
          {
           Printf(eout,"Error : No Data\n@ #.q;",file_name);

           return eout.close();
          }
       }
    }
  catch(CatchType)
    {
     Printf(eout,"\n@ #.q;",file_name);

     return eout.close();
    }
 }

} // namespace Book
} // namespace App
