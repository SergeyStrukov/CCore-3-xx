/* Book.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/book/Book.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToRead.h>
#include <CCore/inc/PretextFileToMem.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {
namespace Book {

#include "Book1.TypeSet.gen.h"

/* class BookMap::Pretext */

class BookMap::Pretext : public PretextMap
 {
  private:

   static StrLen Pretext1()
    {
     return

#include "Book1.Pretext.gen.h"

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

BookMap::Pretext BookMap::Pretext::Object CCORE_INITPRI_3 ;

/* class BookMap */

void BookMap::prepare(StrLen book_file_name)
 {
  if( SuffixExt(book_file_name).equal(".vol"_c) )
    {
     file=VolumeBinFileToRead(book_file_name);
     file_name="/main.book.ddl"_c;
    }
  else
    {
     file=DefBinFileToRead();
     file_name=book_file_name;
    }
 }

BookMap::BookMap()
 {
  mem=0;
  book=0;
 }

BookMap::~BookMap()
 {
  MemFree(Replace_null(mem));
 }

void BookMap::blank()
 {
  book=0;
  file={};
  file_name=Empty;

  MemFree(Replace_null(mem));
 }

ErrorText BookMap::load(StrLen book_file_name,PtrLen<char> ebuf)
 {
  blank();

  PrintBuf eout(ebuf);

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     prepare(book_file_name);

     using FileType = PretextFileToMem<BinFileToMem,Pretext::Object> ;

     DDL::FileEngine<FileName,FileType,BinFileToRead> engine(file,eout);

     auto result=engine.process(Range(file_name));

     if( !result )
       {
        Printf(eout,"\n@ #.q;",book_file_name);

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
           Printf(eout,"Error : No Data\n@ #.q;",book_file_name);

           return eout.close();
          }
       }
    }
  catch(CatchType)
    {
     Printf(eout,"\n@ #.q;",book_file_name);

     return eout.close();
    }
 }

} // namespace Book
} // namespace Video
} // namespace CCore
