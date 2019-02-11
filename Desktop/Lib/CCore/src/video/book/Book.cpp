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

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/PretextFileToMem.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/Volume.h>
#include <CCore/inc/RawFileToRead.h>

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

/* class BookMap::FromFS */

class BookMap::FromFS : NoCopy
 {
   using FileType = PretextFileToMem<FileToMem,Pretext::Object> ;

   StrLen file_name;

   DDL::FileEngine<FileName,FileType> engine;

  public:

   FromFS(StrLen file_name_,PrintBase &eout)
    : file_name(file_name_),
      engine(eout)
    {
    }

   ~FromFS() {}

   auto operator () () { return engine.process(file_name); }
 };

/* class BookMap::FromVolume */

class BookMap::FromVolume : NoCopy
 {
   using VolType = Volume<AltFileToRead> ;
   using FileType = PretextFileToMem<VolumeFileToMem<AltFileToRead>,Pretext::Object> ;

   VolType vol;

   DDL::FileEngine<FileName,FileType,VolType &> engine;

  public:

   FromVolume(StrLen file_name,PrintBase &eout)
    : vol(file_name),
      engine(vol,eout)
    {
    }

   ~FromVolume() {}

   auto operator () () { return engine.process("/main.book.ddl"_c); }
 };

/* class BookMap */

template <class Engine>
ErrorText BookMap::loadFrom(StrLen file_name,PtrLen<char> ebuf)
 {
  PrintBuf eout(ebuf);

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     Engine engine(file_name,eout);

     auto result=engine();

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

  if( SuffixExt(file_name).equal(".vol"_c) ) return loadFrom<FromVolume>(file_name,ebuf);

  return loadFrom<FromFS>(file_name,ebuf);
 }

} // namespace Book
} // namespace Video
} // namespace CCore
