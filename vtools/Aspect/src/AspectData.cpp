/* AspectData.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.01
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/AspectData.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/DirTreeRun.h>
#include <CCore/inc/ElementPool.h>

#include <CCore/inc/Cmp.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/video/FileNameCmp.h>
#include <CCore/inc/algon/SortUnique.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/PrintStem.h>

#include <CCore/inc/video/PrintDDL.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/FileSystem.h>

namespace App {

/* functions */

bool IsRelPath(StrLen path)
 {
  if( !path ) return false;

  SplitDev split(path);

  if( !split )
    {
     if( PathBase::IsSlash(path[0]) ) return false;

     return true;
    }

  return false;
 }

bool SkipDir(StrLen name)
 {
  return name.len && name[0]=='.' ;
 }

bool SkipFile(StrLen name)
 {
  return name.len && name[0]=='.' ;
 }

/* struct DiffPath */

DiffPath::DiffPath(StrLen a,StrLen b)
 {
  SplitPath split_a(a);
  SplitPath split_b(b);

  if( !split_a )
    {
     if( !split_b )
       {
        // continue;
       }
     else
       {
        return;
       }
    }
  else
    {
     if( !split_b )
       {
        return;
       }
     else
       {
        if( !split_a.dev.equal(split_b.dev) ) return;

        // continue;
       }
    }

  a=split_a.path;
  b=split_b.path;

  while( +a && +b )
    {
     SplitDir split_a(a);
     SplitDir split_b(b);

     if( !split_a )
       {
        if( !split_b )
          {
           if( a.equal(b) )
             {
              a=Null;
              b=Null;
             }
          }
        else
          {
           if( a.equal(split_b.dir.inner(0,1)) )
             {
              a=Null;
              b=split_b.path;
             }
          }

        break;
       }
     else
       {
        if( !split_b )
          {
           if( b.equal(split_a.dir.inner(0,1)) )
             {
              a=split_a.path;
              b=Null;
             }

           break;
          }
        else
          {
           if( !split_a.dir.equal(split_b.dir) ) break;

           a=split_a.path;
           b=split_b.path;
          }
       }
    }

  this->a=a;
  this->b=b;
  ok=true;
 }

/* class RelPath */

ulen RelPath::Down(StrLen path)
 {
  if( +path && PathBase::IsSlash(path[0]) ) return MaxULen;

  ulen ret=0;

  while( +path )
    {
     SplitDir split(path);

     if( !split )
       {
        if( PathBase::IsDot(path) )
          {
           // continue;
          }
        else if( PathBase::IsDotDot(path) )
          {
           if( ret ) ret--; else return MaxULen;
          }
        else
          {
           ret++;
          }

        break;
       }
     else
       {
        if( PathBase::IsDot(split.dir) )
          {
           // continue;
          }
        else if( PathBase::IsDotDot(split.dir) )
          {
           if( ret ) ret--; else return MaxULen;
          }
        else
          {
           ret++;
          }

        path=split.path;
       }
    }

  return ret;
 }

void RelPath::relPath(ulen down,StrLen path)
 {
  if( +path )
    {
     if( PathBase::IsSlash(path[0]) ) return;

     for(; down ;down--) out.add("../"_c);

     out.add(path);
    }
  else
    {
     if( down )
       {
        for(down--; down ;down--) out.add("../"_c);

        out.add(".."_c);
       }
     else
       {
        out.add("."_c);
       }
    }

  ok=+out;
 }

RelPath::RelPath(StrLen base_path,StrLen path)
 {
  DiffPath diff(base_path,path);

  if( !diff ) return;

  ulen down=Down(diff.a);

  if( down!=MaxULen ) relPath(down,diff.b);
 }

/* class NormalPath */

NormalPath::NormalPath(StrLen path_)
 {
  FileSystem fs;

  path=fs.pathOf(path_,buf);
 }

/* enum ItemStatus */

const char * GetTextDesc(ItemStatus status)
 {
  switch( status )
    {
     case Item_New    : return "New";
     case Item_Ignore : return "Ignore";
     case Item_Red    : return "Red";
     case Item_Yellow : return "Yellow";
     case Item_Green  : return "Green";

     default: return "???";
    }
 }

/* struct FileData */

FileData::FileData() noexcept
 {
 }

FileData::~FileData()
 {
 }

/* struct DirData */

DirData::DirData() noexcept
 {
 }

DirData::~DirData()
 {
 }

void DirData::erase()
 {
  name=Null;
  status=Item_New;

  files.erase();
  dirs.erase();
 }

/* class AspectData */

void AspectData::Collect(ItemStatus &result,ItemStatus status)
 {
  if( status!=Item_Ignore ) Replace_min(result,status);
 }

void AspectData::Collect(DirData &dir)
 {
  ItemStatus result=ItemStatusLim;

  for(DirData &d : dir.dirs )
    {
     Collect(d);

     Collect(result,d.status);
    }

  for(const FileData &f : dir.files )
    {
     Collect(result,f.status);
    }

  if( result==ItemStatusLim ) result=Item_Ignore;

  dir.status=result;
 }

template <OneOfTypes<FileData,DirData> T>
void AspectData::SortData(PtrLen<T> data)
 {
  IncrSort(data, [] (const T &a,const T &b) { return ExtNameLess(Range(a.name),Range(b.name)); } );
 }

class AspectData::DirProc : NoCopy
 {
  public:

   struct FileNode : NoCopy
    {
     FileNode *next;
     StrLen name;

     FileNode(FileNode *next_,StrLen name_) : next(next_),name(name_) {}
    };

   struct DirNode;

   struct Final
    {
     SimpleArray<DirData> dirs;
     SimpleArray<FileData> files;
    };

   struct DataType : NoCopy
    {
     DirNode *dirs = 0 ;
     FileNode *files = 0 ;

     Final *final;

     explicit DataType(Final *final_) : final(final_) {}

     void finish()
      {
       {
        ulen count=0;

        for(auto *node=dirs; node ;node=node->next) count++;

        SimpleArray<DirData> temp(count);

        auto *ptr=temp.getPtr();

        for(auto *node=dirs; node ;node=node->next,ptr++)
          {
           ptr->name=String(node->name);

           Swap(ptr->dirs,node->data.final->dirs);
           Swap(ptr->files,node->data.final->files);
          }

        Swap(final->dirs,temp);
       }

       {
        ulen count=0;

        for(auto *node=files; node ;node=node->next) count++;

        SimpleArray<FileData> temp(count);

        auto *ptr=temp.getPtr();

        for(auto *node=files; node ;node=node->next,ptr++) ptr->name=String(node->name);

        Swap(final->files,temp);
       }

       SortData(Range(final->dirs));
       SortData(Range(final->files));
      }
    };

   struct DirNode : NoCopy
    {
     DirNode *next;
     StrLen name;
     DataType data;

     DirNode(DirNode *next_,StrLen name_,Final *final) : next(next_),name(name_),data(final) {}
    };

  private:

   ElementPool pool;
   Collector<Final> finals;

   DataType *root = 0 ;

  private:

   Final * createFinal()
    {
     return finals.append_default();
    }

   FileNode * create(FileNode *top,StrLen name)
    {
     return pool.create<FileNode>(top,pool.dup(name));
    }

   DirNode * create(DirNode *top,StrLen name)
    {
     return pool.create<DirNode>(top,pool.dup(name),createFinal());
    }

  public:

   DirProc() {}

   ~DirProc() {}

   void finish(DirData &dir)
    {
     if( !root ) return;

     Swap(dir.dirs,root->final->dirs);
     Swap(dir.files,root->final->files);
    }

   DataType * dir(StrLen)
    {
     return root=pool.create<DataType>(createFinal());
    }

   DataType * dir(StrLen,StrLen name,DataType *parent_data)
    {
     if( !parent_data || SkipDir(name) ) return 0;

     DirNode *node=create(parent_data->dirs,name);

     parent_data->dirs=node;

     return &node->data;
    }

   void file(StrLen,StrLen name,DataType *parent_data)
    {
     if( parent_data && !SkipFile(name) ) parent_data->files=create(parent_data->files,name);
    }

   void enddir(StrLen,StrLen,DataType *data)
    {
     if( data ) data->finish();
    }
 };

void AspectData::Build(DirData &root,StrLen path)
 {
  DirTreeRun run(path);

  DirProc proc;

  run.apply(proc);

  proc.finish(root);
 }

template <class T,class Func>
bool AspectData::CopyByName(PtrLen<T> dst,PtrLen<const T> src,Func copy)
 {
  struct Item
   {
    union
     {
      T *dst;
      const T *src;
     };

    bool is_dst;

    void setDst(T &dst_)
     {
      is_dst=true;
      dst=&dst_;
     }

    void setSrc(const T &src_)
     {
      is_dst=false;
      src=&src_;
     }

    StrLen getName() const { return is_dst?Range(dst->name):Range(src->name); }
   };

  SimpleArray<Item> temp(LenAdd(dst.len,src.len));

  Item *ptr=temp.getPtr();

  for(; +dst ;++dst,ptr++) ptr->setDst(*dst);

  for(; +src ;++src,ptr++) ptr->setSrc(*src);

  bool ret=false;

  Algon::IncrSortThenApplyUniqueRangeBy(Range(temp), [] (const Item &item) { return CmpAsStr(item.getName()); } ,
                                                     [copy,&ret] (PtrLen<Item> r)
                                                                 {
                                                                  const T *src=0;

                                                                  for(auto s=r; +s ;++s)
                                                                    if( !s->is_dst )
                                                                      {
                                                                       if( src )
                                                                         {
                                                                          ret=true;

                                                                          return;
                                                                         }

                                                                       src=s->src;
                                                                      }

                                                                  if( !src )
                                                                    {
                                                                     ret=true;

                                                                     return;
                                                                    }

                                                                  ulen count=0;

                                                                  for(auto s=r; +s ;++s)
                                                                    if( s->is_dst )
                                                                      {
                                                                       if( copy(*(s->dst),*src) ) ret=true;

                                                                       count++;
                                                                      }

                                                                  if( count!=1 ) ret=true;

                                                                 } );

  return ret;
 }

bool AspectData::CopyFiles(SimpleArray<FileData> &dst,const SimpleArray<FileData> &src)
 {
  return CopyByName(Range(dst),Range(src), [] (FileData &dst,const FileData &src) { dst.status=src.status; return false; } );
 }

bool AspectData::CopyDirs(SimpleArray<DirData> &dst,const SimpleArray<DirData> &src)
 {
  return CopyByName(Range(dst),Range(src),Copy);
 }

bool AspectData::Copy(DirData &root,const DirData &dir)
 {
  root.status=dir.status;

  bool f1=CopyDirs(root.dirs,dir.dirs);
  bool f2=CopyFiles(root.files,dir.files);

  return f1 || f2 ;
 }

void AspectData::Fill(DynArray<ItemData> &items,const DirData &dir,ulen depth)
 {
  ulen ind=items.getLen();

  items.append_fill(&dir,depth);

  for(const DirData &d : dir.dirs ) Fill(items,d,depth+1);

  for(const FileData &f : dir.files ) items.append_fill(&f,depth+1);

  items[ind].next_index=items.getLen();
 }

void AspectData::buildItems()
 {
  items.erase();

  Fill(items,root);

  visible.erase();

  visible.extend_default(items.getLen());
 }

bool AspectData::sync()
 {
  DirData temp;

  Build(temp,Range(path));

  bool ret=Copy(temp,root);

  Swap(temp,root);

  buildItems();

  ok=true;

  return ret;
 }

AspectData::AspectData() noexcept
 {
 }

AspectData::~AspectData()
 {
 }

void AspectData::erase()
 {
  path=Null;
  root.erase();
  items.erase();
  visible.erase();
  ok=false;
 }

Counts AspectData::getCounts() const
 {
  Counts ret;

  for(const ItemData &item : items )
    if( !item.is_dir )
      {
       ItemStatus status=item.ptr->status;

       if( status<ItemStatusLim ) ret.count[status]++;
      }

  return ret;
 }

void AspectData::collect()
 {
  Collect(root);
 }

 // save/load

void AspectData::blank(StrLen path_)
 {
  erase();

  try
    {
     path=String(path_);
     root.erase();

     sync();
    }
  catch(CatchType)
    {
     erase();
    }
 }

void AspectData::PrintDir(PrinterType &out,ulen &index,const DirData &dir)
 {
  Printf(out,"  {\n");

  Printf(out,"   #;,\n",DDLPrintableString(dir.name));

  Printf(out,"   #;,\n",dir.status);

  {
   Printf(out,"   {");

   PrintFirst stem("\n",",\n");

   for(const DirData &sub : dir.dirs )
     {
      sub.index=index;

      Printf(out,"#;    &Dir#;",stem,index++);
     }

   Printf(out,"\n   },\n");
  }

  {
   Printf(out,"   {");

   PrintFirst stem("\n",",\n");

   for(const FileData &file : dir.files )
     {
      Printf(out,"#;    { #; , #; }",stem,DDLPrintableString(file.name),file.status);
     }

   Printf(out,"\n   }\n");
  }

  Printf(out,"  }");
 }

void AspectData::PrintSub(PrinterType &out,ulen &index,const DirData &dir)
 {
  for(const DirData &sub : dir.dirs )
    {
     Printf(out,"Dir Dir#;=\n",sub.index);

     PrintDir(out,index,sub);

     Printf(out,";\n\n");
    }

  for(const DirData &sub : dir.dirs )
    {
     PrintSub(out,index,sub);
    }
 }

void AspectData::save(StrLen file_name,ErrorText &etext) const
 {
  PrintBuf eout(etext.getBuf());

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     PrintFile out(file_name);

     Printf(out,"//##include <Aspect.ddl>\n\n");

     Printf(out,"Aspect Data=\n {\n");

     {
      StrLen abspath=Range(path);

      RelPath rel(PrefixPath(file_name),abspath);

      if( +rel )
        Printf(out,"  #;,\n",DDLPrintableString(rel.get()));
      else
        Printf(out,"  #;,\n",DDLPrintableString(abspath));
     }

     ulen index=0;

     PrintDir(out,index,root);

     Printf(out,"\n };\n\n");

     PrintSub(out,index,root);
    }
  catch(CatchType)
    {
     Printf(eout,"\n@ #.q;",file_name);

     etext.setTextLen(eout.close().len);
    }
 }

#include "Aspect.TypeDef.gen.h"
#include "Aspect.TypeSet.gen.h"

StrLen AspectData::Pretext()
 {
  return
"type Status = uint8 ;"

"Status New    = 0 ;"
"Status Ignore = 1 ;"
"Status Red    = 2 ;"
"Status Yellow = 3 ;"
"Status Green  = 4 ;"

"struct File"
" {"
"  text name;"
"  Status status;"
" };"

"struct Dir"
" {"
"  text name;"
"  Status status;"

"  Dir * [] dirs;"
"  File[] files;"
" };"

"struct Aspect"
" {"
"  text path;"

"  Dir root;"
" };"_c;
 }

template <class Dir>
void AspectData::Load(DirData &dst,Dir src)
 {
  dst.name=String(src.name.getStr());
  dst.status=ItemStatus(src.status);

  {
   SimpleArray<FileData> temp(src.files.len);

   FileData *ptr=temp.getPtr();

   for(const TypeDef::File &f : src.files.getRange() )
     {
      ptr->name=String(f.name.getStr());
      ptr->status=ItemStatus(f.status);

      ptr++;
     }

   Swap(dst.files,temp);
  }

  {
   SimpleArray<DirData> temp(src.dirs.len);

   DirData *ptr=temp.getPtr();

   for(auto d : src.dirs.getRange() )
     {
      Load(*ptr,*d);

      ptr++;
     }

   Swap(dst.dirs,temp);
  }
 }

void AspectData::toAbs(StrLen file_name)
 {
  StrLen str=Range(path);

  if( IsRelPath(str) )
    {
     MakeFileName temp(PrefixPath(file_name),str);

     NormalPath normal(temp.get());

     path=String(normal.get());
    }
 }

bool AspectData::load(StrLen file_name,ErrorText &etext)
 {
  erase();

  PrintBuf eout(etext.getBuf());

  ReportExceptionTo<PrintBuf> report(eout);

  try
    {
     DDL::FileEngine<FileName,FileToMem> engine(eout);

     auto result=engine.process(file_name,Pretext());

     if( !result )
       {
        Printf(eout,"\n@ #.q;",file_name);

        etext.setTextLen(eout.close().len);

        return false;
       }
     else
       {
        DDL::TypedMap<TypeSet> map(result);
        MemAllocGuard guard(map.getLen());

        map(guard);

        // populate

        TypeDef::Aspect data=map.takeConst<TypeDef::Aspect>("Data");

        path=String(data.path.getStr());

        Load(root,data.root);

        toAbs(file_name);

        return sync();
       }
    }
  catch(CatchType)
    {
     erase();

     Printf(eout,"\n@ #.q;",file_name);

     etext.setTextLen(eout.close().len);

     return false;
    }
 }

} // namespace App

