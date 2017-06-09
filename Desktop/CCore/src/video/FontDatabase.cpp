/* FontDatabase.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/FontDatabase.h>

#include <CCore/inc/video/DesktopKey.h>
#include <CCore/inc/video/Desktop.h>

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

struct FontInfo::MaxSizeFunction : public Funchor
 {
  ulen cur = 0 ;

  ulen index = 0 ;
  Coord dx = 0 ;
  Coord dy = 0 ;

  MaxSizeFunction() {}

  void next(Coord dx_,Coord dy_)
   {
    if( dy_ > dy )
      {
       index=cur;
       dx=dx_;
       dy=dy_;
      }

    cur++;
   }

  Function<void (Coord dx,Coord dy)> function_next() { return FunctionOf(this,&MaxSizeFunction::next); }
 };

FontInfo::FontInfo(const String &file_name_,bool &is_font)
 {
  file_name=file_name_;

  FreeTypeFont font(Range(file_name),is_font);

  if( is_font )
    {
     family=font.getFamily();
     style=font.getStyle();

     auto flags=font.getStyleFlags();

     scalable=flags.scalable;
     monospace=flags.monospace;
     italic=flags.italic;
     bold=flags.bold;

     if( scalable )
       {
        try
          {
           font.setSize(32);
          }
        catch(...)
          {
           Printf(NoException,"CCore::Video::FontInfo::FontInfo(#.q;,...) : cannot set size",file_name);
          }
       }
     else
       {
        MaxSizeFunction func;

        font.getSizeList(func.function_next());

        try
          {
           font.setFixedSize(func.index);
          }
        catch(...)
          {
           Printf(NoException,"CCore::Video::FontInfo::FontInfo(#.q;,...) : cannot set size",file_name);
          }
       }

     def_size=font->getSize();

     if( !checkNames() ) is_font=false;
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
"type Bool = uint8 ;"

"Bool True = 1 ;"
"Bool False = 0 ;"

"type Coord = sint16 ;"

"struct FontSize"
" {"
"  Coord min_dx;"
"  Coord max_dx;"
"  Coord dy;"
"  Coord by;"
"  Coord dx0;"
"  Coord dx1;"
"  Coord skew;"
" };"

"struct FontInfo"
" {"
"  text file_name;"

"  text family;"
"  text style;"

"  Bool scalable;"
"  Bool monospace;"
"  Bool italic;"
"  Bool bold;"

"  FontSize def_size;"
" };"

"type FontDatabase = FontInfo[] ;"_c;
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
     return StringCat(path,"/",name);
    }
 }

void FontDatabase::Append(Collector<FontInfo> &obj,StrLen path,StrLen name)
 {
  String file_name=CatPath(path,name);

  bool is_font=false;
  FontInfo info(file_name,is_font);

  if( is_font ) obj.append_copy(info);
 }

void FontDatabase::Append(Collector<FontInfo> &obj,StrLen dir)
 {
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

  char temp[512];
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

        obj.scalable=info.scalable;
        obj.monospace=info.monospace;
        obj.italic=info.italic;
        obj.bold=info.bold;

        obj.def_size.min_dx=info.def_size.min_dx;
        obj.def_size.max_dx=info.def_size.max_dx;
        obj.def_size.dy=info.def_size.dy;
        obj.def_size.by=info.def_size.by;
        obj.def_size.dx0=info.def_size.dx0;
        obj.def_size.dx1=info.def_size.dx1;
        obj.def_size.skew=info.def_size.skew;

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

  //Putobj(out,"include <FontInfo.ddl>\n\n");

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
  HomeDir home;

  MakeString<MaxPathLen> buf;

  buf.add(home.get(),HomeKey(),CacheFile());

  if( !buf )
    {
     Printf(Exception,"CCore::Video::FontDatabase::tryCache() : too long file name");
    }

  tryCache(buf.get());
 }

void FontDatabase::saveCache() const
 {
  HomeDir home;

  MakeString<MaxPathLen> buf;

  buf.add(home.get(),HomeKey());

  StrLen dir=buf.get();

  buf.add(CacheFile);

  if( !buf )
    {
     Printf(Exception,"CCore::Video::FontDatabase::saveCache() : too long file name");
    }

  FileSystem fs;

  if( fs.getFileType(dir)==FileType_none ) fs.createDir(dir);

  saveDDL(buf.get());
 }

/* class FontDatabase::Step */

void FontDatabase::Step::append(StrLen dir)
 {
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

/* class FontBuilder */

FreeTypeFont FontBuilder::Build(const FontInfo *info,Coord font_size,const FreeTypeFont::Config &font_config)
 {
  FreeTypeFont ret(Range(info->file_name));

  ret.setSize(font_size);

  ret.setConfig(font_config);

  return ret;
 }

void FontBuilder::buildIndex()
 {
  index.build(fdb, [] (const FontInfo &obj) { return obj.scalable; } ,
                   [] (const FontInfo &a,const FontInfo &b) { return AlphaCmp(CmpAsStr(a.family),CmpAsStr(b.family),
                                                                              a.bold,b.bold,
                                                                              a.italic,b.italic); } );
 }

FontBuilder::FontBuilder()
 {
 }

FontBuilder::~FontBuilder()
 {
 }

void FontBuilder::prepare()
 {
  fdb.cache();

  buildIndex();
 }

const FontInfo * FontBuilder::find(StrLen family,bool bold,bool italic) const
 {
  return index.find( [=] (const FontInfo &obj) { return AlphaCmp(CmpAsStr(obj.family),CmpAsStr(family),
                                                                 obj.bold,bold,
                                                                 obj.italic,italic); });
 }

FreeTypeFont FontBuilder::build(StrLen family,bool bold,bool italic,Coord font_size,const FreeTypeFont::Config &font_config) const
 {
  const FontInfo *info=find(family,bold,italic);

  if( !info )
    {
     Printf(Exception,"CCore::Video::FontBuilder::find(#.q;,bold=#;,italic=#;) : no such font",family,bold,italic);
    }

  return Build(info,font_size,font_config);
 }

Font FontBuilder::build_or_default(StrLen family,bool bold,bool italic,Coord font_size,const FreeTypeFont::Config &font_config) const
 {
  const FontInfo *info=find(family,bold,italic);

  if( !info ) return Font();

  return Build(info,font_size,font_config);
 }

/* class FontBuilder::Step */

StepResult FontBuilder::Step::finish(StepResult result,FontBuilder &obj)
 {
  if( result!=StepFinalOk ) return result;

  obj.buildIndex();

  return StepFinalOk;
 }

FontBuilder::Step::Step()
 {
 }

FontBuilder::Step::~Step()
 {
 }

StepResult FontBuilder::Step::start(FontBuilder &obj,bool use_cache)
 {
  return finish(step.start(obj.fdb,use_cache),obj);
 }

StepResult FontBuilder::Step::operator () (IncrementalProgress &progress,FontBuilder &obj)
 {
  return finish(step(progress,obj.fdb),obj);
 }

void FontBuilder::Step::erase() noexcept
 {
  step.erase();
 }

} // namespace Video
} // namespace CCore

