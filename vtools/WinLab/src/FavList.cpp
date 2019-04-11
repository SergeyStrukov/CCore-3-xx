/* FavList.cpp */
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

//#include <CCore/inc/video/FavList.h>
#include <inc/FavList.h>

#include <CCore/inc/video/HomeFile.h>
#include <CCore/inc/video/PrintDDL.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/PrintStem.h>
#include <CCore/inc/ForLoop.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

namespace Private_FavList {

#include "FavData.TypeDef.gen.h"
#include "FavData.TypeSet.gen.h"

} // namespace Private_FavList

using namespace Private_FavList;

/* class FavList */

StrLen FavList::Pretext()
 {
  return

"type Bool = uint8 ;\r\n"
"\r\n"
"Bool True = 1 ;\r\n"
"Bool False = 0 ;\r\n"
"\r\n"
"struct FavElement\r\n"
" {\r\n"
"  text title;\r\n"
"  text path;\r\n"
"  Bool section = False ;\r\n"
"  Bool open = True ;\r\n"
" };\r\n"
"\r\n"
"struct FavData\r\n"
" {\r\n"
"  FavElement[] list;\r\n"
"  \r\n"
"  ulen off = 0 ;\r\n"
"  ulen cur = 0 ;  \r\n"
" };\r\n"
" \r\n"
""_c;
 }

FavList::FavList()
 {
 }

FavList::~FavList()
 {
 }

 // methods

void FavList::erase()
 {
  list.erase();
  off=0;
  cur=0;
 }

 // load/save

bool FavList::load(StrLen file_name)
 {
  erase();

  char buf[TextBufLen];
  PrintBuf eout(Range(buf));

  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(file_name,Pretext());

  if( !result )
    {
     return false;
    }
  else
    {
     DDL::TypedMap<TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     // populate

     TypeDef::FavData data=map.takeConst<TypeDef::FavData>("Data"_c);

     auto r=data.list.getRange();

     DynArray<FavRec> new_list(r.len);

     for(ulen i : IndLim(r.len) )
       {
        auto &dst=new_list[i];
        auto &src=r[i];

        dst.title=src.title.getStr();
        dst.path=src.path.getStr();
        dst.section=src.section;
        dst.open=src.open;
       }

     list=std::move(new_list);

     off=data.off;
     cur=data.cur;

     Replace_min(off,r.len);
     Replace_min(cur,r.len);

     return true;
    }

  return false;
 }

void FavList::save(StrLen file_name) const
 {
  PrintFile out(file_name);

  Putobj(out,"//include <FavData.ddl>\n\n"_c);

  Putobj(out,"FavData Data =\n {\n\n"_c);

  Putobj(out,"  {"_c);

  PrintFirst stem("\n"_c,",\n"_c);

  for(auto &rec : list )
    {
     Printf(out,"#;   { #; , #; , #; , #; }",stem,DDLString(rec.title),
                                                  DDLPrintableString(rec.path),
                                                  DDLBool(rec.section),
                                                  DDLBool(rec.open));
    }

  Putobj(out,"\n  },\n\n"_c);

  Printf(out,"  #;,\n",off);
  Printf(out,"  #;\n",cur);

  Putobj(out," };\n\n"_c);
 }

bool FavList::load(StrLen key,StrLen file) noexcept
 {
  try
    {
     HomeFile home_file(key,file);

     return load(home_file.get());
    }
  catch(...)
    {
     erase();

     return false;
    }
 }

void FavList::save(StrLen key,StrLen file) const noexcept
 {
  try
    {
     HomeFile home_file(key,file);

     home_file.createDir();

     save(home_file.get());
    }
  catch(...)
    {
    }
 }

} // namespace Video
} // namespace CCore


