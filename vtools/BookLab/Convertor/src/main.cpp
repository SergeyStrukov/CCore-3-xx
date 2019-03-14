/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Source.h>
#include <inc/Convert.h>
#include <inc/DomConvert.h>
#include <inc/TagTest.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/FileSystem.h>
#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/ForLoop.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/Array.h>

namespace App {

/* class FileList */

class FileList : NoCopy
 {
  public:

   struct Rec
    {
     String file_name;
     String path;
     String page_name;

     Rec(StrLen dir,StrLen file)
      {
       file_name=file;

       MakeFileName temp(dir,file);

       path=temp.get();

       SplitFullExt split(file);

       page_name=split.name;
      }
    };

  private:

   Collector<Rec> list;

   PtrLen<const Rec> range;

  public:

   explicit FileList(StrLen dir)
    {
     FileSystem fs;
     FileSystem::DirCursor cur(fs,dir);

     cur.apply( [&] (StrLen file_name,FileType file_type)
                    {
                     if( file_type==FileType_file && file_name.hasSuffix(".html"_c) )
                       {
                        list.append_fill(dir,file_name);
                       }

                    } );

     range=list.flat();
    }

   ~FileList()
    {
    }

   auto getRange() const { return range; }
 };

/* Index() */

int Index(PrintBase &out,StrLen input_dir_name)
 {
  StrLen file_name="../index.html"_c;

  MakeFileName temp(input_dir_name,file_name);

  Source src(temp.get());

  DomConvert convert;

  if( !src.run(convert) )
    {
     Printf(Con,"@ #;\n",file_name);

     return 1;
    }

  return 0;
 }

/* Main() */

StrLen CutTitle(const String &title)
 {
  StrLen str=Range(title);

  StrLen prefix="CCore -> "_c;

  if( str.hasPrefix(prefix) ) return str.part(prefix.len);

  return str;
 }

int Main(StrLen input_dir_name,StrLen output_file_name)
 {
  PrintFile out(output_file_name);

  return Index(out,input_dir_name);

  FileList file_list(input_dir_name);
  auto list=file_list.getRange();

  DynArray<String> title(list.len);

  // 1

  for(ulen i : IndLim(list.len) )
    {
     auto &rec=list[i];

     Source src(Range(rec.path));

     PageParam param;

     param.name=rec.page_name;

     param.up="content"_str;

     if( i>0 ) param.prev=list[i-1].page_name+"#page"_c;

     if( i+1<list.len ) param.next=list[i+1].page_name+"#page"_c;

     Convert convert(out,param);

     if( !src.run(convert) )
       {
        Printf(Con,"@ #;\n",rec.file_name);

        return 1;
       }

     title[i]=convert.getTitle();
    }

  // 2

  for(ulen i : IndLim(list.len) )
    {
     auto &rec=list[i];
     ulen ind=i+1;

     Printf(out,"Text item#; = { { { #.q; , null , &link#; } } , null , & align_item } ;\n\n",ind,CutTitle(title[i]),ind);

     Printf(out,"Link link#; = { &#;##page } ;\n\n",ind,rec.page_name);
    }

  // 3

  Putobj(out,"TextList list = { {\n"_c);

  for(ulen i : IndLim(list.len) )
    {
     ulen ind=i+1;

     out.put(' ');

     if( i ) out.put(',');

     Printf(out,"{ '#;.' , { { & item#; , null , { 0 , 0 } , { 0 , 0 } } } }",ind,ind);
    }

  Putobj(out,"} } ;\n\n"_c);

  return 0;
 }

/* Test() */

bool Test(StrLen dir,StrLen file_name)
 {
  MakeFileName path(dir,file_name);

  Source src(path.get());

  TagTest convert;

  return src.run(convert);
 }

/* Main() */

int Main()
 {
  FileSystem fs;

  StrLen dir="../../../html"_c;

  FileSystem::DirCursor cur(fs,dir);

  int ret=0;

  cur.apply( [&] (StrLen file_name,FileType file_type)
                 {
                  if( file_type==FileType_file && file_name.hasSuffix(".html"_c) )
                    {
                     if( !Test(dir,file_name) )
                       {
                        Printf(Con,"@ #;\n",file_name);

                        ret=1;
                       }
                    }

                 } );

  return ret;
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     int ret;

     {
      Putobj(Con,"--- Book Convertor 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc==1 )
        {
         ret=Main();
        }
      else if( argc==3 )
        {
         ret=Main(argv[1],argv[2]);
        }
      else
        {
         Putobj(Con,"Usage: Convertor <input-dir-name> <output-file-name>\n");

         return 1;
        }
     }

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

