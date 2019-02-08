/* FontDatabase.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/FontDatabase.h>

#include <CCore/inc/video/DesktopKey.h>
#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/video/HomeFile.h>

#include <CCore/inc/PrintStem.h>
#include <CCore/inc/CharProp.h>

#include <CCore/inc/MakeString.h>
#include <CCore/inc/FileSystem.h>
#include <CCore/inc/DirTreeRun.h>
#include <CCore/inc/Print.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Path.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* struct FontInfo */

bool FontInfo::CheckName(StrLen name)
 {
  for(char ch : name ) if( !CharIsPrintable(ch) ) return false;

  return true;
 }

bool FontInfo::checkNames() const
 {
  return CheckName(file_name) && CheckName(family) && CheckName(style) ;
 }

template <class Font>
void FontInfo::fill(Font &font,bool &is_font)
 {
  if( is_font )
    {
     family=GetFontFamily(font);
     style=GetFontStyle(font);
     font_class=GetFontClass(font);

     auto flags=GetFontStyleFlags(font);

     scalable=flags.scalable;
     monospace=flags.monospace;
     italic=flags.italic;
     bold=flags.bold;

     if( !checkNames() ) is_font=false;
    }
 }

FontInfo::FontInfo(const String &file_name_,bool &is_font,bool use_probe)
 {
  file_name=file_name_;

  if( use_probe )
    {
     ProbeFreeTypeFont font(Range(file_name),is_font);

     fill(font,is_font);
    }
  else
    {
     FreeTypeFont font(Range(file_name),is_font);

     fill(font,is_font);
    }
 }

void FontInfo::turnSlash()
 {
  PathBase::TurnSlash(file_name.modify());
 }

/* class FontDatabase */

StrLen FontDatabase::CacheFile() { return "/FontCache.ddl"_c; }

StrLen FontDatabase::Pretext()
 {
  return
"type Bool = uint8 ;\r\n"
"\r\n"
"Bool True = 1 ;\r\n"
"Bool False = 0 ;\r\n"
"\r\n"
"struct FontInfo\r\n"
" {\r\n"
"  text file_name;\r\n"
"\r\n"
"  text family;\r\n"
"  text style;\r\n"
"  \r\n"
"  uint font_class;\r\n"
"\r\n"
"  Bool scalable;\r\n"
"  Bool monospace;\r\n"
"  Bool italic;\r\n"
"  Bool bold;\r\n"
" };\r\n"
"\r\n"
"type FontDatabase = FontInfo[] ;\r\n"_c;
 }

String FontDatabase::CatPath(StrLen path,StrLen name)
 {
  if( path.len>=2 && PathBase::IsSlash(path.back(2)) && PathBase::IsDot(path.back(1)) )
    {
     path.len--;

     return StringCat(path,name);
    }
  else
    {
     return StringCat(path,"/"_c,name);
    }
 }

void FontDatabase::Append(Collector<FontInfo> &obj,StrLen path,StrLen name)
 {
  String file_name=CatPath(path,name);

  bool is_font=false;
  FontInfo info(file_name,is_font,true);

  if( is_font ) obj.append_copy(info);
 }

void FontDatabase::Append(Collector<FontInfo> &obj,StrLen dir)
 {
  FileSystem fs;

  if( fs.getFileType(dir)!=FileType_dir ) return;

  struct Proc
   {
    Collector<FontInfo> &obj;

    using DataType = void ;

    DataType * dir(StrLen) { return 0; }

    DataType * dir(StrLen,StrLen,DataType *) { return 0; }

    void file(StrLen path,StrLen name,DataType *)
     {
      Append(obj,path,name);
     }

    void enddir(StrLen,StrLen,DataType *) {}
   };

  Proc proc{obj};

  DirTreeRun run(dir);

  run.apply(proc);
 }

void FontDatabase::tryCache(StrLen file_name)
 {
  FileSystem fs;

  auto cmp=fs.getFileUpdateTime(file_name);

  if( !cmp )
    {
     Printf(Exception,"CCore::Video::FontDatabase::tryCache(#.q;) : no cache file",file_name);
    }

  SystemFontDirs sysdirs;

  for(StrLen dir : sysdirs.getList() )
    if( fs.getFileUpdateTime(dir)>cmp )
      {
       Printf(Exception,"CCore::Video::FontDatabase::tryCache(...) : system fonts are updated");
      }

  loadDDL(file_name);
 }

FontDatabase::FontDatabase() noexcept
 {
 }

FontDatabase::~FontDatabase()
 {
 }

 // methods

void FontDatabase::populate()
 {
  Collector<FontInfo> temp;

  SystemFontDirs sysdirs;

  for(StrLen dir : sysdirs.getList() ) Append(temp,dir);

  temp.extractTo(list);

  turnSlash();
 }

void FontDatabase::turnSlash()
 {
  for(auto &obj : list ) obj.turnSlash();
 }

 // cache methods

namespace Private_FontDatabase {

#include "FontInfo.TypeDef.gen.h"
#include "FontInfo.TypeSet.gen.h"

} // namespace Private_FontDatabase

using namespace Private_FontDatabase;

void FontDatabase::loadDDL(StrLen file_name)
 {
  list.erase();

  SimpleArray<char> temp(4_KByte);
  PrintBuf eout(Range(temp));
  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(file_name,Pretext());

  if( !result )
    {
     Printf(Exception,"CCore::Video::FontDatabase::loadDDL(#.q;) : input file processing error\n#;",file_name,eout.close());
    }
  else
    {
     DDL::TypedMap<TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     // populate

     PtrLen<TypeDef::FontInfo> cache=map.takeConst<TypeDef::FontDatabase>("FontCache");

     list.reserve(cache.len);

     for(auto &info : cache )
       {
        FontInfo obj;

        obj.file_name=String(info.file_name);
        obj.family=String(info.family);
        obj.style=String(info.style);
        obj.font_class=Correct((FontClass)info.font_class);

        obj.scalable=info.scalable;
        obj.monospace=info.monospace;
        obj.italic=info.italic;
        obj.bold=info.bold;

        if( obj.checkNames() ) list.append_copy(obj);
       }

     list.shrink_extra();

     turnSlash();
    }
 }

void FontDatabase::saveDDL(StrLen file_name) const
 {
  PrintFile out(file_name);

  Putobj(out,"/* FontCache.ddl */\n\n");

  Putobj(out,"//include <FontInfo.ddl>\n\n");

  Putobj(out,"FontDatabase FontCache=\n {");

  PrintFirst stem("\n  ",",\n  ");

  for(auto &info : list )
    {
     Putobj(out,stem);

     info.printDDL(out);
    }

  Putobj(out,"\n };\n\n");
 }

void FontDatabase::cache()
 {
  try
    {
     tryCache();
    }
  catch(CatchType)
    {
     populate();

     try
       {
        saveCache();
       }
     catch(CatchType)
       {
       }
    }
 }

void FontDatabase::tryCache()
 {
  HomeFile home_file(HomeKey(),CacheFile());

  tryCache(home_file.get());
 }

void FontDatabase::saveCache() const
 {
  HomeFile home_file(HomeKey(),CacheFile());

  home_file.createDir();

  saveDDL(home_file.get());
 }

/* class FontDatabase::Step */

void FontDatabase::Step::append(StrLen dir)
 {
  FileSystem fs;

  if( fs.getFileType(dir)!=FileType_dir ) return;

  struct Proc
   {
    Collector<String> &obj;

    using DataType = void ;

    DataType * dir(StrLen) { return 0; }

    DataType * dir(StrLen,StrLen,DataType *) { return 0; }

    void file(StrLen path,StrLen name,DataType *)
     {
      obj.append_copy(CatPath(path,name));
     }

    void enddir(StrLen,StrLen,DataType *) {}
   };

  Proc proc{file_list};

  DirTreeRun run(dir);

  run.apply(proc);
 }

StepResult FontDatabase::Step::stepDir(IncrementalProgress &progress,FontDatabase &)
 {
  file_list.erase();
  info_list.erase();

  SystemFontDirs sysdirs;

  for(StrLen dir : sysdirs.getList() ) append(dir);

  cur_file=file_list.flat();
  pos=0;

  progress.setTotal(scale.set(cur_file.len));

  stage=&Step::stepInfo;

  return StepContinue;
 }

StepResult FontDatabase::Step::stepInfo(IncrementalProgress &progress,FontDatabase &obj)
 {
  if( +cur_file )
    {
     bool is_font=false;
     FontInfo info(*cur_file,is_font);

     if( is_font ) info_list.append_copy(info);

     ++cur_file;

     if( progress.setPos(scale(pos++)) ) return StepContinue;

     return StepFinalError;
    }
  else
    {
     info_list.extractTo(obj.list);

     obj.turnSlash();

     try
       {
        obj.saveCache();
       }
     catch(CatchType)
       {
       }

     return StepFinalOk;
    }
 }

FontDatabase::Step::Step()
 {
 }

FontDatabase::Step::~Step()
 {
 }

StepResult FontDatabase::Step::start(FontDatabase &obj,bool use_cache)
 {
  if( use_cache )
    try
      {
       obj.tryCache();

       return StepFinalOk;
      }
    catch(CatchType)
      {
      }

  stage=&Step::stepDir;

  return StepContinue;
 }

void FontDatabase::Step::erase() noexcept
 {
  file_list.erase();

  info_list.erase();

  cur_file=Null;
 }

/* class FontIndex */

FontIndex::FontIndex() noexcept
 {
 }

FontIndex::~FontIndex()
 {
 }

} // namespace Video
} // namespace CCore

