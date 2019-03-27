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

#include <CCore/inc/CharProp.h>

#include <CCore/inc/algon/SortUnique.h>

#include <CCore/inc/PrintError.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class SpawnProcess::Pool */

Place<void> SpawnProcess::Pool::allocBlock(ulen alloc_len)
 {
  void *mem=Sys::SpawnChild::MemAlloc(alloc_len);

  if( !mem ) GuardNoMem(alloc_len);

  Place<void> ptr=PlaceAt(mem);

  list.ins(new(ptr) Node);

  return ptr;
 }

void SpawnProcess::Pool::newBlock()
 {
  Place<void> new_block=allocBlock(block_len);

  block=new_block;
  cur=new_block+Delta;
  avail=block_len-Delta;
 }

void * SpawnProcess::Pool::allocMem(ulen len)
 {
  if( len>MaxLen ) GuardNoMem(len);

  len=Align(len);

  if( !len ) len=MaxAlign;

  if( avail<len )
    {
     if( avail>block_len/2 || len+Delta>block_len )
       {
        auto ret=allocBlock(len+Delta)+Delta;

        return ret;
       }

     newBlock();
    }

  avail-=len;

  return cur+=len;
 }

SpawnProcess::Pool::Pool()
 : block(0),
   cur(0),
   avail(0)
 {
  constexpr ulen BLen=AlignDown(4_KByte);

  static_assert( BLen>Delta );

  block_len=BLen;
 }

SpawnProcess::Pool::~Pool()
 {
  while( Node *node=list.del() ) Sys::SpawnChild::MemFree(node);
 }

/* class SpawnSlot */

SpawnSlot::SpawnSlot() noexcept
 {
 }

SpawnSlot::~SpawnSlot()
 {
  if( state==2 )
    {
     Printf(NoException,"CCore::SpawnSlot::~SpawnSlot() : not waited");
    }
 }

int SpawnSlot::wait()
 {
  if( state!=2 )
    {
     Printf(Exception,"CCore::SpawnSlot::wait() : not spawned");
    }

  state=3;

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
  if( slot->state!=2 )
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

  if( slot ) slot->state=3;

  if( result.error )
    {
     Printf(Exception,"CCore::SpawnSet::wait() : #; status = #;",PrintError(result.error),result.status);
    }

  return {slot,result.status};
 }

/* class SpawnProcess */

char ** SpawnProcess::buildArgv()
 {
  char **ret=pool.alloc<char *>(LenAdd(args.getLen(),1u));

  auto out=ret;

  for(char *arg : args ) *(out++)=arg;

  *(out++)=0;

  return ret;
 }

char ** SpawnProcess::buildEnvp()
 {
  for(auto e=Sys::GetEnviron(); const char *zstr=(*e) ;e++) addEnv(zstr);

  auto list=Range(envs);

  char **ret=pool.alloc<char *>(LenAdd(list.len,1u));

  auto out=ret;

  Algon::SortThenApplyUnique(list, [&] (EnvRec &env) { *(out++)=env.str; } );

  *(out++)=0;

  return ret;
 }

SpawnProcess::SpawnProcess(StrLen wdir_,StrLen exe_name_)
 : args(DoReserve,100),
   envs(DoReserve,100)
 {
  if( +wdir_ ) wdir=pool.cat(wdir_);

  exe_name=pool.cat(exe_name_);
 }

SpawnProcess::~SpawnProcess()
 {
 }

void SpawnProcess::addArg(StrLen str)
 {
  args.append_copy(pool.cat(str));
 }

void SpawnProcess::addEnv(StrLen name,StrLen value)
 {
  ulen ind=envs.getLen();

  envs.append_fill(pool.cat(name,"="_c,value),name.len,ind);
 }

void SpawnProcess::addEnv(StrLen str)
 {
  for(StrLen t=str; +t ;++t)
    if( *t=='=' )
      {
       ulen name_len=str.len-t.len;
       ulen ind=envs.getLen();

       envs.append_fill(pool.cat(str),name_len,ind);

       break;
      }
 }

void SpawnProcess::spawn(SpawnSlot &slot)
 {
  if( slot.state!=0 )
    {
     Printf(Exception,"CCore::SpawnProcess::spawn() : slot is already spawned");
    }

  if( used )
    {
     Printf(Exception,"CCore::SpawnProcess::spawn() : used");
    }

  used=true;

  slot.state=1;

  char **argv=buildArgv();

  char **envp=buildEnvp();

  if( auto error=slot.sys_spawn.spawn(wdir,exe_name,argv,envp) )
    {
     Printf(Exception,"CCore::SpawnProcess::spawn() : #;",PrintError(error));
    }

  slot.state=2;
 }

} // namespace CCore

