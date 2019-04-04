/* VMakeIntCmd.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: vmake 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/VMakeIntCmd.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/ScanRange.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/DecodeFile.h>

namespace App {
namespace VMake {

/* struct CheckWildcard */

CheckWildcard::CheckWildcard(StrLen path)
 {
  SplitPath split1(path);

  SplitName split2(split1.path);

  ScanStr scan(split2.name, [] (char ch) { return ch=='*' || ch=='?' ; } );

  if( +scan.next )
    {
     dir=path.prefix(split1.dev.len+split2.path.len);

     file=split2.name;

     ok=true;
    }
  else
    {
     ok=false;
    }
 }

/* class WildcardCursor */

WildcardCursor::WildcardCursor(FileSystem &fs,StrLen dir_,StrLen file)
 : dir(dir_),
   str(dir,"."_c),
   cur(fs,str.get()),
   filter(file)
 {
 }

WildcardCursor::~WildcardCursor()
 {
 }

bool WildcardCursor::next()
 {
  while( cur.next() )
    {
     StrLen file=cur.getFileName();

     if( cur.getFileType()==FileType_file && filter(file) )
       {
        str(dir,file);

        return true;
       }
    }

  return false;
 }

/* class BuildFileName */

bool BuildFileName::IsRooted(StrLen name)
 {
  return name.len && PathBase::IsSlash(name[0]) ;
 }

bool BuildFileName::IsRel(StrLen file)
 {
  SplitDev split_dev(file);

  return !split_dev && !IsRooted(file) ;
 }

BuildFileName::BuildFileName(StrLen wdir,StrLen file)
 {
  if( !wdir )
    {
     result=file;
    }
  else
    {
     if( IsRel(file) )
       {
        result=buf(wdir,file);
       }
     else
       {
        result=file;
       }
    }
 }

/* class IntCmdProc */

IntCmdProc::IntCmdProc()
 {
 }

IntCmdProc::~IntCmdProc()
 {
 }

 // check

bool IntCmdProc::checkExist(StrLen wdir,StrLen dst)
 {
  BuildFileName dst1(wdir,dst);

  return fs.getFileType(dst1.get())==FileType_file;
 }

bool IntCmdProc::checkOlder(StrLen wdir,StrLen dst,StrLen src)
 {
  BuildFileName dst1(wdir,dst);
  BuildFileName src1(wdir,src);

  auto dst_time=fs.getFileUpdateTime(dst1.get());
  auto src_time=fs.getFileUpdateTime(src1.get());

  return dst_time<src_time;
 }

 // commands

int IntCmdProc::echo(StrLen wdir,StrLen str,StrLen outfile)
 {
  try
    {
     if( !outfile )
       {
        Printf(Con,"#;\n",str);
       }
     else
       {
        BuildFileName outfile1(wdir,outfile);

        PrintFile out(outfile1.get());

        Putobj(out,str);
       }

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

int IntCmdProc::cat(StrLen wdir,PtrLen<DDL::MapText> files,StrLen outfile)
 {
  try
    {
     BuildFileName outfile1(wdir,outfile);

     PrintFile out(outfile1.get());

     for(StrLen file : files )
       {
        BuildFileName file1(wdir,file);

        DecodeFile inp(file1.get());

        while( inp.more() )
          {
           auto r=Mutate<const char>(inp.pump());

           out.put(r.ptr,r.len);
          }
       }

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

int IntCmdProc::rm(StrLen wdir,PtrLen<DDL::MapText> files)
 {
  try
    {
     for(StrLen file : files )
       {
        BuildFileName file1(wdir,file);

        ExpandWildcard(fs,file1.get(), [&] (StrLen f)
                                           {
                                            fs.deleteFile(f);

                                           } );

       }

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

int IntCmdProc::mkdir(StrLen wdir,StrLen path)
 {
  try
    {
     BuildFileName path1(wdir,path);

     WalkPath(path1.get(), [&] (StrLen dir)
                               {
                                if( fs.getFileType(dir)!=FileType_dir ) fs.createDir(dir);

                               } );

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

} // namespace VMake
} // namespace App
