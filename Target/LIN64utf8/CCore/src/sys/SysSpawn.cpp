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

#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

namespace CCore {
namespace Sys {

/* GetShell() */

StrLen GetShell()
 {
  const char *shell=getenv("SHELL");

  if( !shell ) return "/bin/sh"_c;

  return shell;
 }

/* GetEnviron() */

char ** GetEnviron()
 {
  return environ;
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
       if( wdir )
         {
          if( chdir(wdir) )
            {
             error=NonNullError();

             _exit(125);
            }
         }

       execvpe(path,argv,envp);

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
     ret.error=ErrorType(EFAULT);
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
        ret.error=ErrorType(EFAULT);
       }
    }

  return ret;
 }

} // namespace Sys
} // namespace CCore

