/* SysSpawn.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/LIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysSpawn.h>

#include <CCore/inc/ForLoop.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Sys {

/* class SpawnWaitList::Engine */

class SpawnWaitList::Engine : MemBase_nocopy
 {
   struct Rec
    {
     SpawnChild::Type pid;
     void *arg;
    };

   DynArray<Rec> list;

  private:

   WaitResult finish(ulen ind,int status,ErrorType error)
    {
     WaitResult ret{list[ind].arg,status,error};

     ulen last=list.getLen()-1;

     if( ind<last ) list[ind]=list[last];

     list.shrink_one();

     return ret;
    }

  public:

   explicit Engine(ulen reserve) : list(DoReserve,reserve) {}

   ~Engine() {}

   bool notEmpty() const { return list.notEmpty(); }

   void add(SpawnChild::Type pid,void *arg) { list.append_copy({pid,arg}); }

   WaitResult wait()
    {
     if( list.isEmpty() ) return {0,0,NoError};

     auto result=WaitAny();

     if( result.pid==-1 )
       {
        return {0,result.status,result.error};
       }

     for(ulen ind : IndLim(list.getLen()) )
       if( list[ind].pid==result.pid )
         {
          return finish(ind,result.status,result.error);
         }

     return {0,0,NoError};
    }

   struct WaitAnyResult
    {
     SpawnChild::Type pid;
     int status;
     ErrorType error;
    };

   static WaitAnyResult WaitAny();
 };

/* struct SpawnWaitList */

ErrorType SpawnWaitList::init(ulen reserve)
 {
  SilentReportException report;

  try
    {
     engine=new Engine(reserve);

     return NoError;
    }
  catch(CatchType)
    {
     return Error_NoMem;
    }
 }

ErrorType SpawnWaitList::exit()
 {
  bool nok=engine->notEmpty();

  delete Replace_null(engine);

  return nok?Error_Running:NoError;
 }

ErrorType SpawnWaitList::add(SpawnChild *spawn,void *arg)
 {
  SilentReportException report;

  try
    {
     engine->add(spawn->pid,arg);

     return NoError;
    }
  catch(CatchType)
    {
     return Error_NoMem;
    }
 }

auto SpawnWaitList::wait() -> WaitResult
 {
  return engine->wait();
 }

} // namespace Sys
} // namespace CCore

#include <limits.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

namespace CCore {
namespace Sys {

/* GetShell() */

StrLen GetShell(char [MaxPathLen+1])
 {
  const char *shell=getenv("SHELL");

  if( !shell ) return "/bin/sh"_c;

  return shell;
 }

/* GetEnviron() */

void GetEnviron(Function<void (StrLen)> func)
 {
  char **envp=environ;

  if( envp )
    {
     for(; char *str=*envp ;envp++)
       {
        func(StrLen(str));
       }
    }
 }

/* struct SpawnChild */

static_assert( Meta::IsSame<pid_t,SpawnChild::Type> ,"CCore::Sys::SpawnChild : bad Type");

void * SpawnChild::MemAlloc(ulen len)
 {
  return malloc(len);
 }

void SpawnChild::MemFree(void *mem)
 {
  free(mem);
 }

ErrorType SpawnChild::spawn(char *wdir,char *path,char **argv,char **envp)
 {
  volatile ErrorType error=NoError;

  switch( Type child_pid=vfork() )
    {
     case -1 : return NonNullError();

     case 0 :
      {
       char temp[PATH_MAX+1];
       char *path1=path;

       if( *path!='/' && strchr(path,'/') )
         {
          if( char *result=realpath(path,temp) )
            {
             path1=result;
            }
          else
            {
             error=NonNullError();

             _exit(124);
            }
         }

       if( wdir )
         {
          if( chdir(wdir) )
            {
             error=NonNullError();

             _exit(125);
            }
         }

       execvpe(path1,argv,envp);

       error=NonNullError();

       _exit( ( error==ENOENT )? 126 : 127 );
      }

     default:
      {
       if( error )
         waitpid(child_pid,0,WNOHANG);
       else
         pid=child_pid;

       return error;
      }
    }
 }

auto SpawnChild::wait() -> WaitResult
 {
  WaitResult ret;

  int status;

  Type child_pid=waitpid(pid,&status,0);

  if( child_pid==-1 )
    {
     ret.status=1000;
     ret.error=NonNullError();
    }
  else if( child_pid!=pid )
    {
     ret.status=1000;
     ret.error=Error_Spawn;
    }
  else
    {
     if( WIFEXITED(status) )
       {
        ret.status=WEXITSTATUS(status);
        ret.error=NoError;
       }
     else
       {
        ret.status=status;
        ret.error=Error_Spawn;
       }
    }

  return ret;
 }

/* class SpawnWaitList::Engine */

auto SpawnWaitList::Engine::WaitAny() -> WaitAnyResult
 {
  WaitAnyResult ret;

  int status;

  SpawnChild::Type child_pid=waitpid(0,&status,0);

  if( child_pid==-1 )
    {
     ret.pid=-1;
     ret.status=1000;
     ret.error=NonNullError();
    }
  else
    {
     if( WIFEXITED(status) )
       {
        ret.pid=child_pid;
        ret.status=WEXITSTATUS(status);
        ret.error=NoError;
       }
     else
       {
        ret.pid=child_pid;
        ret.status=status;
        ret.error=Error_Spawn;
       }
    }

  return ret;
 }

} // namespace Sys
} // namespace CCore

