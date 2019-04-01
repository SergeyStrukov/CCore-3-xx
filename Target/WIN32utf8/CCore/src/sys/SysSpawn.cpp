/* SysSpawn.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysSpawn.h>

#include <CCore/inc/sys/SysEnv.h>
#include <CCore/inc/sys/SysSpawnInternal.h>

#include <CCore/inc/MemBase.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* GetShell() */

StrLen GetShell(char buf[MaxPathLen+1])
 {
  TryGetEnv<32,MaxPathLen> tryget(Range(buf,MaxPathLen),"UNIXSHELL");

  if( tryget.ok ) return tryget.str;

  return "sh.exe"_c;
 }

/* GetEnviron() */

void GetEnviron(Function<void (StrLen)> func)
 {
  EnvironHook hook;

  hook( [=] (PtrLen<const WChar> env)
            {
             WCharToUtf8Full temp(env);

             if( !temp ) GuardNoMem(temp.getLen());

             func(temp.get());

            } );
 }

/* struct SpawnChild */

static_assert( Meta::IsSame<Win32::handle_t,SpawnChild::Type> ,"CCore::Sys::SpawnChild : bad Type");

ErrorType SpawnChild::spawn(char *wdir,char *path,char **argv,char **envp)
 {
  ProcessSetup setup(wdir,path,argv,envp);

  return setup.create(handle);
 }

auto SpawnChild::wait() -> WaitResult
 {
  WaitResult ret;

  switch( Win32::WaitForSingleObject(handle,Win32::NoTimeout) )
    {
     case Win32::WaitObject_0 :
      {
       unsigned exit_code;

       if( Win32::GetExitCodeProcess(handle,&exit_code) )
         {
          ret.status=(int)exit_code;
          ret.error=NoError;
         }
       else
         {
          ret.status=1000;
          ret.error=NonNullError();
         }
      }
     break;

     case Win32::WaitFailed :
      {
       ret.status=1000;
       ret.error=NonNullError();
      }
     break;

     default:
      {
       ret.status=1000;
       ret.error=Error_Spawn;
      }
    }

  Win32::CloseHandle(handle);

  return ret;
 }

/* class SpawnWaitList::Engine */

class SpawnWaitList::Engine : MemBase_nocopy
 {
   DynArray<SpawnChild::Type> list;
   DynArray<void *> arglist;

  private:

   static WaitResult Finish(SpawnChild::Type handle,void *arg)
    {
     WaitResult ret;

     ret.arg=arg;

     unsigned exit_code;

     if( Win32::GetExitCodeProcess(handle,&exit_code) )
       {
        ret.status=(int)exit_code;
        ret.error=NoError;
       }
     else
       {
        ret.status=1000;
        ret.error=NonNullError();
       }

     Win32::CloseHandle(handle);

     return ret;
    }

   WaitResult finish(ulen ind)
    {
     auto handle=list[ind];
     auto arg=arglist[ind];

     ulen last=list.getLen()-1;

     if( ind<last )
       {
        list[ind]=list[last];
        arglist[ind]=arglist[last];
       }

     list.shrink_one();
     arglist.shrink_one();

     return Finish(handle,arg);
    }

  public:

   explicit Engine(ulen reserve) : list(DoReserve,reserve),arglist(DoReserve,reserve) {}

   ~Engine() {}

   bool notEmpty() const { return list.notEmpty(); }

   void add(SpawnChild::Type handle,void *arg)
    {
     arglist.reserve(1);

     list.append_copy(handle);
     arglist.append_copy(arg);
    }

   WaitResult wait()
    {
     if( list.isEmpty() ) return {0,0,NoError};

     auto result=WaitAny(Range(list));

     if( result.error ) return {0,0,result.error};

     return finish(result.ind);
    }

   struct WaitAnyResult
    {
     ulen ind;
     ErrorType error;
    };

   static WaitAnyResult WaitAny(PtrLen<SpawnChild::Type> list)
    {
     auto result=Win32::WaitForMultipleObjects(list.len,list.ptr,false,Win32::NoTimeout);

     if( result==Win32::WaitFailed )
       {
        return {0,NonNullError()};
       }

     if( result>=Win32::WaitObject_0 && ulen(result-Win32::WaitObject_0)<list.len )
       {
        return {ulen(result-Win32::WaitObject_0),NoError};
       }

     return {0,Error_Spawn};
    }
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
     return ErrorType(Win32::ErrorNotEnoughMemory);
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
     engine->add(spawn->handle,arg);

     return NoError;
    }
  catch(CatchType)
    {
     return ErrorType(Win32::ErrorNotEnoughMemory);
    }
 }

auto SpawnWaitList::wait() -> WaitResult
 {
  return engine->wait();
 }

} // namespace Sys
} // namespace CCore
