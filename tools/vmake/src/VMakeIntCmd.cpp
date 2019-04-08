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

#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/Path.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/DecodeFile.h>

namespace App {
namespace VMake {

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
  WDirFileName dst1(wdir,dst);

  return fs.getFileType(dst1.get())==FileType_file;
 }

CmpFileTimeType IntCmdProc::getFileTime(StrLen wdir,StrLen file)
 {
  WDirFileName file1(wdir,file);

  return fs.getFileUpdateTime(file1.get());
 }

bool IntCmdProc::checkOlder(StrLen wdir,StrLen dst,StrLen src)
 {
  return getFileTime(wdir,dst) < getFileTime(wdir,src) ;
 }

 // commands

int IntCmdProc::echo(StrLen wdir,PtrLen<DDL::MapText> strs,StrLen outfile)
 {
  try
    {
     if( !outfile )
       {
        for(StrLen str : strs ) Printf(Con,"#;\n",str);
       }
     else
       {
        WDirFileName outfile1(wdir,outfile);

        PrintFile out(outfile1.get(),Open_ToWrite|Open_AutoDelete);

        for(StrLen str : strs ) Putobj(out,str);

        out.preserveFile();
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
     WDirFileName outfile1(wdir,outfile);

     PrintFile out(outfile1.get(),Open_ToWrite|Open_AutoDelete);

     for(StrLen file : files )
       {
        WDirFileName file1(wdir,file);

        DecodeFile inp(file1.get());

        while( inp.more() )
          {
           auto r=Mutate<const char>(inp.pump());

           out.put(r.ptr,r.len);
          }
       }

     out.preserveFile();

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
        WDirFileName file1(wdir,file);

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

int IntCmdProc::mkdir(StrLen wdir,PtrLen<DDL::MapText> paths)
 {
  try
    {
     for(StrLen path : paths )
       {
        WDirFileName path1(wdir,path);

        WalkPath(path1.get(), [&] (StrLen dir)
                                  {
                                   if( fs.getFileType(dir)!=FileType_dir ) fs.createDir(dir);

                                  } );
       }

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

} // namespace VMake
} // namespace App
