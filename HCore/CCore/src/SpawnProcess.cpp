/* SpawnProcess.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/SpawnProcess.h>

#include <CCore/inc/algon/SortUnique.h>
#include <CCore/inc/PrintError.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class SpawnSlot */

SpawnSlot::SpawnSlot() noexcept
 {
 }

SpawnSlot::~SpawnSlot()
 {
  if( state==SpawnSlot_Running )
    {
     Printf(NoException,"CCore::SpawnSlot::~SpawnSlot() : not waited");
    }
 }

int SpawnSlot::wait()
 {
  if( state!=SpawnSlot_Running )
    {
     Printf(Exception,"CCore::SpawnSlot::wait() : not spawned");
    }

  state=SpawnSlot_Stopped;

  auto result=sys_spawn.wait();

  if( result.error )
    {
     Printf(Exception,"CCore::SpawnSlot::wait() : #; status = #;",PrintError(result.error),result.status);
    }

  return result.status;
 }

/* class SpawnSet */

SpawnSet::SpawnSet(ulen reserve)
 {
  if( auto error=list.init(reserve) )
    {
     Printf(Exception,"CCore::SpawnSet::SpawnSet(#;) : #;",reserve,PrintError(error));
    }
 }

SpawnSet::~SpawnSet()
 {
  if( auto error=list.exit() )
    {
     Printf(NoException,"CCore::SpawnSet::~SpawnSet() : #;",PrintError(error));
    }
 }

void SpawnSet::add(SpawnSlot *slot)
 {
  if( slot->state!=SpawnSlot_Running )
    {
     Printf(Exception,"CCore::SpawnSet::add(...) : not spawned");
    }

  if( auto error=list.add(&slot->sys_spawn,slot) )
    {
     Printf(Exception,"CCore::SpawnSet::add(...) : #;",PrintError(error));
    }
 }

auto SpawnSet::wait() -> WaitResult
 {
  auto result=list.wait();

  SpawnSlot *slot=static_cast<SpawnSlot *>(result.arg);

  if( slot ) slot->state=SpawnSlot_Stopped;

  if( result.error )
    {
     Printf(Exception,"CCore::SpawnSet::wait() : #; status = #;",PrintError(result.error),result.status);
    }

  return {slot,result.status};
 }

/* class SpawnProcess */

template <class ... TT>
char * SpawnProcess::cat(TT ... tt)
 {
  StrLen str=pool.cat(tt...,"\0"_c);

  return const_cast<char *>(str.ptr);
 }

char ** SpawnProcess::alloc(ulen len)
 {
  return pool.createArray_raw<char *>(LenAdd(len,1)).ptr;
 }

char * SpawnProcess::allocBuf(ulen len)
 {
  return pool.createArray_raw<char>(LenAdd(len,1)).ptr;
 }

char ** SpawnProcess::buildArgv()
 {
  char **ret=alloc(args.getLen());

  auto out=ret;

  for(char *arg : args ) *(out++)=arg;

  *(out++)=0;

  return ret;
 }

char ** SpawnProcess::buildEnvp()
 {
  auto temp=ToFunction<void (StrLen)>( [&] (StrLen env) { addEnv(env); } );

  Sys::GetEnviron(temp.function());

  auto list=Range(envs);

  char **ret=alloc(list.len);

  auto out=ret;

  Algon::SortThenApplyUnique(list, [&] (EnvRec &env) { *(out++)=env.str; } );

  *(out++)=0;

  return ret;
 }

SpawnProcess::SpawnProcess(StrLen wdir_,StrLen exe_name_)
 : pool(4_KByte),
   args(DoReserve,100),
   envs(DoReserve,100)
 {
  if( +wdir_ ) wdir=cat(wdir_);

  exe_name=cat(exe_name_);
 }

SpawnProcess::~SpawnProcess()
 {
 }

void SpawnProcess::addArg(StrLen str)
 {
  args.append_copy(cat(str));
 }

void SpawnProcess::addEnv(StrLen name,StrLen value)
 {
  ulen ind=envs.getLen();

  envs.append_fill(cat(name,"="_c,value),name.len,ind);
 }

void SpawnProcess::addEnv(StrLen str)
 {
  for(StrLen t=str; +t ;++t)
    if( *t=='=' )
      {
       ulen name_len=str.len-t.len;
       ulen ind=envs.getLen();

       envs.append_fill(cat(str),name_len,ind);

       break;
      }
 }

void SpawnProcess::spawn(SpawnSlot &slot)
 {
  if( slot.state!=SpawnSlot_Ready )
    {
     Printf(Exception,"CCore::SpawnProcess::spawn() : slot is already spawned");
    }

  if( used )
    {
     Printf(Exception,"CCore::SpawnProcess::spawn() : used");
    }

  used=true;

  slot.state=SpawnSlot_Broken;

  char **argv=buildArgv();

  char **envp=buildEnvp();

  if( auto error=slot.sys_spawn.spawn(wdir,exe_name,argv,envp) )
    {
     Printf(Exception,"CCore::SpawnProcess::spawn() : #;",PrintError(error));
    }

  slot.state=SpawnSlot_Running;
 }

} // namespace CCore

