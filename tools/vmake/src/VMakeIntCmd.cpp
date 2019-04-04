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

#include <CCore/inc/ForLoop.h>
#include <CCore/inc/Path.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {
namespace VMake {

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
  Used(wdir);
  Used(str);
  Used(outfile);

  return 1;
 }

int IntCmdProc::cat(StrLen wdir,PtrLen<DDL::MapText> files,StrLen outfile)
 {
  Used(wdir);
  Used(files);
  Used(outfile);

  return 1;
 }

int IntCmdProc::rm(StrLen wdir,PtrLen<DDL::MapText> files)
 {
  Used(wdir);
  Used(files);

  return 1;
 }

int IntCmdProc::mkdir(StrLen wdir,StrLen path)
 {
  Used(wdir);
  Used(path);

  return 1;
 }

} // namespace VMake
} // namespace App
