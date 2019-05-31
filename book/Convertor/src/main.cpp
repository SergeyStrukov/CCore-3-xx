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
#include <inc/DomConvert.h>
#include <inc/TagTest.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/FileSystem.h>
#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/ForLoop.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>

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

     Rec(StrLen dir,StrLen file,StrLen page_name_)
      {
       file_name=file;

       MakeFileName temp(dir,file);

       path=temp.get();

       page_name=page_name_;
      }
    };

  private:

   Collector<Rec> list;

   PtrLen<const Rec> range;

  public:

   explicit FileList(StrLen dir)
    {
     list.append_fill(dir,"../index.html"_c,"Index"_c);

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

/* struct Prop */

struct Prop
 {
  String title;
 };

/* class PageList */

class PageList : NoCopy
 {
   DynArray<String> list;

   struct Rec
    {
     StrLen page;
     ulen ind;

     void set(ulen ind_,const String &page_)
      {
       ind=ind_;
       page=Range(page_);
      }

     bool operator < (const Rec &obj) const { return StrLess(page,obj.page); }
    };

   DynArray<Rec> find_list;

  private:

   void prepare()
    {
     auto r=Range(list);

     find_list.erase();
     find_list.extend_default(r.len);

     for(ulen i : IndLim(r.len) ) find_list[i].set(i,r[i]);

     Sort(Range(find_list));
    }

   bool find(ulen &ind,StrLen page) const
    {
     auto r=Range(find_list);

     Algon::BinarySearch_if(r, [=] (const Rec &obj) { return !StrLess(obj.page,page); } );

     if( +r && r->page.equal(page) )
       {
        ind=r->ind;

        return true;
       }

     return false;
    }

  public:

   PageList() {}

   ~PageList() {}

   void setList(DynArray<String> &&list_)
    {
     list=std::move(list_);

     prepare();
    }

   void find(String &prev,String &next,const String &page)
    {
     ulen ind;

     if( find(ind,Range(page)) )
       {
        if( ind>0 ) prev=list[ind-1];

        if( ind+1<list.getLen() ) next=list[ind+1];
       }
    }
 };

/* CCoreBook() */

StrLen CutTitle(const String &title)
 {
  StrLen str=Range(title);

  SkipPrefix(str,"CCore -> "_c);

  return str;
 }

int CCoreBook(StrLen input_dir_name,StrLen output_file_name)
 {
  PrintFile out(output_file_name);

  FileList file_list(input_dir_name);

  auto list=file_list.getRange();

  DynArray<Prop> props(list.len);

  String up=list[0].page_name;

  PageList page_list;

  // 1

  for(ulen i : IndLim(list.len) )
    {
     auto &rec=list[i];

     Source src(Range(rec.path));

     PageParam param;

     param.name=rec.page_name;

     if( i>0 ) param.up=up;

     page_list.find(param.prev,param.next,param.name);

     DomConvert convert;

     if( !src.run(convert) )
       {
        Printf(Con,"@ #;\n",rec.file_name);

        return 1;
       }

     if( i==0 )
       {
        page_list.setList(convert.getPageList());
       }

     convert.print(out,param);

     props[i].title=convert.getTitle();
    }

  // 2

  for(ulen i : IndLim(list.len) )
    {
     auto &rec=list[i];
     ulen ind=i+1;

     Printf(out,"Text item#; = { { { #.q; , null , &link#; } } , null , & align_item } ;\n\n",ind,CutTitle(props[i].title),ind);

     Printf(out,"Link link#; = { &#;##page } ;\n\n",ind,rec.page_name);
    }

  // 3

  Putobj(out,"TextList list = { {\n"_c);

  for(ulen i : IndLim(list.len) )
    {
     ulen ind=i+1;

     out.put(' ');

     if( i ) out.put(',');

     Printf(out,"{ '#;.' , { { & item#; , null , { 0 , 0 } , { 0 , 0 } } } }\n",ind,ind);
    }

  Putobj(out,"} } ;\n\n"_c);

  Printf(out,"Page *start = #; ;\n\n",PrintPtr(up));

  return 0;
 }

/* Page() */

StrLen GetPageName(StrLen input_file_name)
 {
  SplitPath split1(input_file_name);
  SplitName split2(split1.path);
  SplitFullExt split3(split2.name);

  return split3.name;
 }

int Page(StrLen input_file_name,StrLen output_file_name)
 {
  PrintFile out(output_file_name);

  Source src(input_file_name);

  PageParam param;

  param.name=GetPageName(input_file_name);

  DomConvert convert;

  if( !src.run(convert) )
    {
     Printf(Con,"@ #;\n",input_file_name);

     return 1;
    }

  convert.print(out,param);

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

/* Test() */

bool Test(StrLen input_dir_name)
 {
  FileSystem fs;

  FileSystem::DirCursor cur(fs,input_dir_name);

  bool ret=true;

  cur.apply( [&] (StrLen file_name,FileType file_type)
                 {
                  if( file_type==FileType_file && file_name.hasSuffix(".html"_c) )
                    {
                     if( !Test(input_dir_name,file_name) )
                       {
                        Printf(Con,"@ #;\n",file_name);

                        ret=false;
                       }
                    }

                 } );

  return ret;
 }

/* Test() */

int Test()
 {
  if( Test("../../../html"_c) ) return 0;

  return 1;
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
         ret=CCoreBook("../../html"_c,"../files/CCore.bookinc.ddl"_c);
        }
      else if( argc==3 )
        {
         ret=Page(argv[1],argv[2]);
        }
      else
        {
         Putobj(Con,"Usage: Convertor <input-file-name> <output-file-name>\n");

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

