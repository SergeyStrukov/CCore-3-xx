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

#include <CCore/inc/Exception.h>

namespace App {

namespace VMake {

/* class FileProc */

struct FileProc::Slot : NoCopy
 {
  SpawnSlot spawn_slot;

  CompleteArg arg;

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
     slotptrs=SimpleArray<Slot *>(pcap);

     auto out=slotptrs.getPtr();

     for(Slot &s : slots ) (*out++)=&s;

     free=pcap;
    }
 }

 // pexe

auto FileProc::Wait(PtrLen<Slot *> list) -> WaitResult // TODO
 {
  Used(list);

  return {0,0};
 }

void FileProc::movetoFree(ulen ind)
 {
  if( free<ind )
    {
     Swap(slotptrs[free],slotptrs[ind]);
    }

  free++;
 }

auto FileProc::waitOne() -> WaitOneResult
 {
  auto result=Wait(Range(slotptrs).part(free));

  ulen ind=free+result.ind;

  Slot *slot=slotptrs[ind];

  movetoFree(ind);

  return {slot,result.status};
 }

void FileProc::waitOne(CompleteCtx ctx)
 {
  auto result=waitOne();

  CompleteExe temp(Replace_null(result.slot->arg),ctx);

  temp(result.status);
 }

void FileProc::waitFree(CompleteCtx ctx)
 {
  if( !free ) waitOne(ctx);
 }

void FileProc::waitAll(CompleteCtx ctx)
 {
  while( free<pcap ) waitOne(ctx);
 }

void FileProc::waitAll() noexcept
 {
  while( free<pcap )
    {
     waitOne().slot->arg={};
    }
 }

void FileProc::setRunning(Slot *slot,CompleteExe complete)
 {
  slot->arg=complete.arg;

  free--;
 }

void FileProc::command(StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,CompleteExe complete)
 {
  if( !free )
    {
     Printf(Exception,"vmake internal : no free slot");
    }

  Slot *slot=slotptrs[free-1];

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

void FileProc::execute(StrLen exe_file,StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,CompleteExe complete)
 {
  if( !free )
    {
     Printf(Exception,"vmake internal : no free slot");
    }

  Slot *slot=slotptrs[free-1];

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

