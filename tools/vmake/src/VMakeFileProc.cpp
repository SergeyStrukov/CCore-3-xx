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
#include <CCore/inc/Path.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {

namespace VMake {

/* class FileProc::BuildFileName */

class FileProc::BuildFileName : NoCopy
 {
   MakeFileName buf;

   StrLen result;

  private:

   static bool IsRooted(StrLen name)
    {
     return name.len && PathBase::IsSlash(name[0]) ;
    }

   static bool IsRel(StrLen file)
    {
     SplitDev split_dev(file);

     return !split_dev && !IsRooted(file) ;
    }

  public:

   BuildFileName(StrLen wdir,StrLen file)
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

   StrLen get() const { return result; }
 };

/* class FileProc */

 // check

bool FileProc::checkExist(StrLen wdir,StrLen dst)
 {
  BuildFileName dst1(wdir,dst);

  return fs.getFileType(dst1.get())==FileType_file;
 }

bool FileProc::checkOlder(StrLen wdir,StrLen dst,StrLen src)
 {
  BuildFileName dst1(wdir,dst);
  BuildFileName src1(wdir,src);

  auto dst_time=fs.getFileUpdateTime(dst1.get());
  auto src_time=fs.getFileUpdateTime(src1.get());

  return dst_time<src_time;
 }

 // exe

int FileProc::exeCmd(StrLen wdir,TypeDef::Exe *cmd)
 {
  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen exe_file=cmd->exe;
  StrLen cmdline=cmd->cmdline;
  StrLen new_wdir=cmd->wdir;
  PtrLen<TypeDef::Env> env=cmd->env;

  if( +new_wdir )
    {
     try
       {
        BuildFileName wdir1(wdir,new_wdir);

        return execute(exe_file,wdir1.get(),cmdline,env);
       }
     catch(CatchType)
       {
        return 1000;
       }
    }
  else
    {
     return execute(exe_file,wdir,cmdline,env);
    }
 }

int FileProc::exeCmd(StrLen wdir,TypeDef::Cmd *cmd)
 {
  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen cmdline=cmd->cmdline;
  StrLen new_wdir=cmd->wdir;
  PtrLen<TypeDef::Env> env=cmd->env;

  if( +new_wdir )
    {
     try
       {
        BuildFileName wdir1(wdir,new_wdir);

        return command(wdir1.get(),cmdline,env);
       }
     catch(CatchType)
       {
        return 1000;
       }
    }
  else
    {
     return command(wdir,cmdline,env);
    }
 }

int FileProc::exeCmd(StrLen wdir,TypeDef::VMake *cmd)
 {
  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen file_name=cmd->file;
  StrLen target=cmd->target;
  StrLen new_wdir=cmd->wdir;

  if( +new_wdir )
    {
     try
       {
        LockUse lock(level);

        BuildFileName wdir1(wdir,new_wdir);

        DataProc proc(*this,file_name,target,wdir1.get());

        return proc.make();
       }
     catch(CatchType)
       {
        return 1000;
       }
    }
  else
    {
     try
       {
        LockUse lock(level);

        DataProc proc(*this,file_name,target,wdir);

        return proc.make();
       }
     catch(CatchType)
       {
        return 1000;
       }
    }
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

 // pexe

void FileProc::startCmd(StrLen wdir,TypeDef::Exe *cmd,CompleteExe complete)
 {
  Slot *slot=waitFree(complete.complete);

  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen exe_file=cmd->exe;
  StrLen cmdline=cmd->cmdline;
  StrLen new_wdir=cmd->wdir;
  PtrLen<TypeDef::Env> env=cmd->env;

  if( +new_wdir )
    {
     try
       {
        BuildFileName wdir1(wdir,new_wdir);

        execute(slot,exe_file,wdir1.get(),cmdline,env,complete);
       }
     catch(CatchType)
       {
        complete(1000);
       }
    }
  else
    {
     execute(slot,exe_file,wdir,cmdline,env,complete);
    }
 }

void FileProc::startCmd(StrLen wdir,TypeDef::Cmd *cmd,CompleteExe complete)
 {
  Slot *slot=waitFree(complete.complete);

  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen cmdline=cmd->cmdline;
  StrLen new_wdir=cmd->wdir;
  PtrLen<TypeDef::Env> env=cmd->env;

  if( +new_wdir )
    {
     try
       {
        BuildFileName wdir1(wdir,new_wdir);

        return command(slot,wdir1.get(),cmdline,env,complete);
       }
     catch(CatchType)
       {
        complete(1000);
       }
    }
  else
    {
     command(slot,wdir,cmdline,env,complete);
    }
 }

void FileProc::CompleteExe::operator () (int status) // TODO
 {
 }

void FileProc::exeRuleList(StrLen wdir,PtrLen<ExeRule> list,CompleteFunction complete) // TODO
 {
  if( !list ) return;

  Printf(Con,"vmake : start #; rules\n",list.len);

  for(auto &obj : list )
    {
     int status=exeRule(wdir,obj.rule);

     complete(obj.rule,status);
    }
 }

} // namespace VMake

} // namespace App

