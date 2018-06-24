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
#include <CCore/inc/PretextFileToMem.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/Volume.h>
#include <CCore/inc/RawFileToRead.h>

namespace App {
namespace Book {

#include "Book1.TypeSet.gen.h"

/* class BookMap::Pretext */

class BookMap::Pretext : public PretextMap
 {
  private:

   static StrLen Pretext1()
    {
     return

#include "Book1.gen.cpp"

     ""_c;
    }

   virtual void prepare()
    {
     add("pretext:/Book1.ddl"_c,Pretext1());
    }

  public:

   Pretext() noexcept {}

   ~Pretext() {}

   static Pretext Object;
 };

BookMap::Pretext BookMap::Pretext::Object;

/* class BookMap */

ErrorText BookMap::loadFS(StrLen file_name,PtrLen<char> ebuf)
 {
  PrintBuf eout(ebuf);

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     using FileType = PretextFileToMem<FileToMem,Pretext::Object> ;

     DDL::FileEngine<FileName,FileType> engine(eout);

     auto result=engine.process(file_name);

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

           return Success;
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

ErrorText BookMap::loadVolume(StrLen file_name,PtrLen<char> ebuf)
 {
  PrintBuf eout(ebuf);

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     using VolType = Volume<AltFileToRead> ;
     using FileType = PretextFileToMem<VolumeFileToMem<AltFileToRead>,Pretext::Object> ;

     VolType vol(file_name);

     DDL::FileEngine<FileName,FileType,VolType &> engine(vol,eout);

     auto result=engine.process("/main.book.ddl"_c);

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

           return Success;
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

ErrorText BookMap::load(StrLen file_name,PtrLen<char> ebuf)
 {
  blank();

  if( SuffixExt(file_name).equal(".vol"_c) ) return loadVolume(file_name,ebuf);

  return loadFS(file_name,ebuf);
 }

} // namespace Book
} // namespace App
