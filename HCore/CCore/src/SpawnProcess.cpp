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

/* class CmdLineParser */

StrLen CmdLineParser::next()
 {
  for(; +text && CharIsSpace(*text) ;++text);

  if( !text ) return Empty;

  switch( char ch=*text )
    {
     case '"' :
     case '\'' :
      {
       ++text;

       StrLen line=text;

       for(; +text && *text!=ch ;++text);

       StrLen ret=line.prefix(text);

       if( +text ) ++text;

       return ret;
      }
     break;

     default:
      {
       StrLen line=text;

       for(; +text && !CharIsSpace(*text) ;++text);

       return line.prefix(text);
      }
    }
 }

/* class SpawnProcess::Pool */

Place<void> SpawnProcess::Pool::allocBlock(ulen alloc_len)
 {
  Place<void> ptr=PlaceAt(Sys::SpawnChild::MemAlloc(alloc_len));

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
  if( state==2 )
    {
     Printf(NoException,"CCore::SpawnProcess::~SpawnProcess() : not waited");
    }
 }

void SpawnProcess::addArg(StrLen str)
 {
  args.append_copy(pool.cat(str));
 }

void SpawnProcess::addCmdline(StrLen cmdline)
 {
  CmdLineParser parser(cmdline);

  for(;;)
    {
     StrLen str=parser.next();

     if( !str ) break;

     addArg(str);
    }
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

void SpawnProcess::spawn()
 {
  if( state!=0 )
    {
     Printf(Exception,"CCore::SpawnProcess::spawn() : already spawned");
    }

  state=1;

  char **argv=buildArgv();

  char **envp=buildEnvp();

  if( auto error=sys_spawn.spawn(wdir,exe_name,argv,envp) )
    {
     Printf(Exception,"CCore::SpawnProcess::spawn() : #;",PrintError(error));
    }

  state=2;
 }

int SpawnProcess::wait()
 {
  if( state!=2 )
    {
     Printf(Exception,"CCore::SpawnProcess::wait() : not spawned");
    }

  state=3;

  auto result=sys_spawn.wait();

  if( result.error )
    {
     Printf(Exception,"CCore::SpawnProcess::wait() : #;",PrintError(result.error));
    }

  return result.status;
 }

} // namespace CCore

