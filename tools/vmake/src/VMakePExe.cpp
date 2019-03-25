/* VMakePExe.cpp */
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

#include <CCore/inc/Path.h>
#include <CCore/inc/SpawnProcess.h>

namespace App {

namespace VMake {

/* class FileProc */

struct FileProc::Slot : NoCopy
 {
  SpawnSlot spawn_slot;

  ExeRule *obj = 0 ;

  Slot() noexcept {}
 };

FileProc::FileProc()
 {
 }

FileProc::~FileProc()
 {
 }

void FileProc::prepare(unsigned pcap_)
 {
  pcap=Cap<unsigned>(0,pcap_,100);

  if( usePExe() )
    {
     slots=SimpleArray<Slot>(pcap);
    }
 }

 // pexe

auto FileProc::waitFree(CompleteFunction complete) -> Slot * // TODO
 {
 }

void FileProc::waitAll(CompleteFunction complete) // TODO
 {
 }

void FileProc::setRunning(Slot *slot,CompleteExe complete) // TODO
 {
  slot->obj=complete.obj;


 }

void FileProc::command(Slot *slot,StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,CompleteExe complete)
 {
  try
    {
     StrLen exe_name=Sys::GetShell();

     SpawnProcess spawn(wdir,exe_name);

     SplitPath split1(exe_name);
     SplitName split2(split1.path);

     spawn.addArg(split2.name);
     spawn.addArg("-c"_c);
     spawn.addArg(cmdline);

     for(TypeDef::Env obj : env ) spawn.addEnv(obj.name,obj.value);

     spawn.spawn(slot->spawn_slot);

     setRunning(slot,complete);
    }
  catch(CatchType)
    {
     complete(1000);
    }
 }

void FileProc::execute(Slot *slot,StrLen exe_file,StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,CompleteExe complete)
 {
  try
    {
     SpawnProcess spawn(wdir,exe_file);

     spawn.addArg(exe_file);

     spawn.addCmdline(cmdline);

     for(TypeDef::Env obj : env ) spawn.addEnv(obj.name,obj.value);

     spawn.spawn(slot->spawn_slot);

     setRunning(slot,complete);
    }
  catch(CatchType)
    {
     return complete(1000);
    }
 }

} // namespace VMake

} // namespace App

