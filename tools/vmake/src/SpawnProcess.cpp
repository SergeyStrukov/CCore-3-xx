/* SpawnProcess.cpp */
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

#include <inc/SpawnProcess.h>

#include <CCore/inc/CharProp.h>

#include <CCore/inc/algon/SortUnique.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/Print.h>

/* sys functions */

static void * mem_alloc(size_t len);

static void mem_free(void *ptr);

static char ** get_environ();

static int ext_spawn(int *pid,char *wdir,char *path,char **argv,char **envp);

static int wait_child(int pid);

namespace App {

namespace VMake {

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
  Place<void> ptr=PlaceAt(mem_alloc(alloc_len));

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
  while( Node *node=list.del() ) mem_free(node);
 }

/* class SpawnProcess */

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
  char **arglist=pool.alloc<char *>(LenAdd(args.getLen(),1u));

  {
   auto out=arglist;

   for(char *arg : args ) *(out++)=arg;

   *(out++)=0;
  }

  char **envlist;

  {
   for(auto e=get_environ(); const char *zstr=(*e) ;e++) addEnv(zstr);

   auto list=Range(envs);

   envlist=pool.alloc<char *>(LenAdd(list.len,1u));

   auto out=envlist;

   Algon::SortThenApplyUnique(list, [&] (EnvRec &env) { *(out++)=env.str; } );

   *(out++)=0;
  }

  if( ext_spawn(&pid,wdir,exe_name,arglist,envlist) )
    {
     Printf(Exception,"vmake : failed to spawn a process");
    }
 }

int SpawnProcess::wait()
 {
  return wait_child(pid);
 }

} // namespace VMake

} // namespace App

/* sys functions */

#define _GNU_SOURCE
#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void * mem_alloc(size_t len) { return malloc(len); }

static void mem_free(void *ptr) { free(ptr); }

static char ** get_environ() { return environ; }

static int ext_spawn(int *pid,char *wdir,char *path,char **argv,char **envp)
 {
  volatile int error=0;

  switch( int p=vfork() )
    {
     case -1 : return errno;

     case 0 :
      {
       if( wdir ) chdir(wdir);

       execvpe(path,argv,envp);

       error=errno;

       _exit(127);
      }

     default:
      {
       if( error )
         waitpid(p,0,WNOHANG);
       else
         *pid=p;

       return error;
      }
    }
 }

static int wait_child(int pid)
 {
  int result=0;

  int ret=waitpid(pid,&result,0);

  if( ret==-1 || ret!=pid ) return 1000;

  return result;
 }
