/* VMakeFileProc.cpp */
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

#include <inc/VMakeProc.h>

#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/CapString.h>

#include <CCore/inc/Print.h>

#include <cstdlib>

namespace App {

namespace VMake {

/* class FileProc */

int FileProc::command(StrLen wdir,StrLen cmdline)
 {
  char buf[1024];
  PrintBuf out(Range(buf));

  if( +wdir )
    {
     Printf(out,"START /D '#;' '#;'",wdir,cmdline);
    }
  else
    {
     Putobj(out,cmdline);
    }

  return std::system(out.closeZStr());
 }

FileProc::FileProc()
 {
 }

FileProc::~FileProc()
 {
 }

 // check

bool FileProc::checkExist(StrLen wdir,StrLen dst)
 {
  MakeFileName dst1(wdir,dst);

  return fs.getFileType(dst1.get())==FileType_file;
 }

bool FileProc::checkOlder(StrLen wdir,StrLen dst,StrLen src)
 {
  MakeFileName dst1(wdir,dst);
  MakeFileName src1(wdir,src);

  auto dst_time=fs.getFileUpdateTime(dst1.get());
  auto src_time=fs.getFileUpdateTime(src1.get());

  return dst_time<src_time;
 }

 // exe

int FileProc::exeCmd(StrLen wdir,TypeDef::Exe *cmd)
 {
  Used(wdir);
  Used(cmd);

  return 1;
 }

int FileProc::exeCmd(StrLen wdir,TypeDef::Cmd *cmd)
 {
  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen cmdline=cmd->cmdline;

  // cmd->wdir cmd->env

  return command(wdir,cmdline);
 }

int FileProc::exeCmd(StrLen wdir,TypeDef::VMake *cmd)
 {
  Used(wdir);
  Used(cmd);

  return 1;
 }

int FileProc::exeRule(StrLen wdir,TypeDef::Rule *rule)
 {
  for(auto cmd : rule->cmd.getRange() )
    {
     int ret=0;

     cmd.getPtr().apply( [&] (auto *ptr) { if( ptr ) ret=exeCmd(wdir,ptr); } );

     if( ret ) return ret;
    }

  return 0;
 }

} // namespace VMake

} // namespace App

