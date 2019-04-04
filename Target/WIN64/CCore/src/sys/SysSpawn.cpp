/* SysSpawn.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysSpawn.h>

#include <CCore/inc/sys/SysSpawnInternal.h>

#include <CCore/inc/MemBase.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/win64/Win64.h>

#include <cstdlib>

namespace CCore {
namespace Sys {

/* GetShell() */

StrLen GetShell(char buf[MaxPathLen+1]) noexcept
 {
  if( const char *str=std::getenv("UNIXSHELL") )
    {
     StrLen text(str);

     if( text.len<=MaxPathLen )
       {
        text.copyTo(buf);

        return StrLen(buf,text.len);
       }
    }

  return "sh.exe"_c;
 }

/* struct GetEnviron */

static_assert( Meta::IsSame<GetEnviron::WChar,Win64::unicode_t> ,"CCore::Sys::GetEnviron : bad WChar");

auto GetEnviron::ZScan(const WChar *ztext) -> const WChar *
 {
  for(; *ztext ;ztext++);

  return ztext;
 }

auto GetEnviron::transform(PtrLen<const WChar> text) noexcept -> TransformResult
 {
  if( !str )
    {
     str=small;
     len=DimOf(small);
    }

  if( !text ) return {0,NoError};

  if( text.len>0x7FFF'FFFFu ) return {0,Error_TooLong};

  int result=Win64::WideCharToMultiByte(Win64::CodePageActive,0,text.ptr,(int)text.len,0,0,0,0);

  if( result==0 ) return {0,NonNullError()};

  if( result<0 ) return {0,Error_SysErrorFault};

  ulen buflen=(ulen)result;

  if( buflen>len )
    {
     if( char *new_str=PlaceAt(TryMemAlloc(buflen)) )
       {
        if( str!=small ) MemFree(str);

        str=new_str;
        len=buflen;
       }
     else
       {
        return {0,ErrorType(Win64::ErrorNotEnoughMemory)};
       }
    }

  Win64::WideCharToMultiByte(Win64::CodePageActive,0,text.ptr,(int)text.len,str,result,0,0);

  return {buflen,NoError};
 }

ErrorType GetEnviron::init() noexcept
 {
  envblock=Win64::GetEnvironmentStringsW();

  if( !envblock ) return NonNullError();

  ptr=envblock;
  str=0;

  return NoError;
 }

ErrorType GetEnviron::exit() noexcept
 {
  if( str && str!=small ) MemFree(Replace_null(str));

  if( !Win64::FreeEnvironmentStringsW(Replace_null(envblock)) ) return NonNullError();

  return NoError;
 }

auto GetEnviron::next() noexcept -> NextResult
 {
  const WChar *wstr=ptr;

  if( *wstr )
    {
     const WChar *lim=ZScan(wstr);

     ptr=lim+1;

     auto result=transform(Range(wstr,lim));

     if( result.error ) return {Empty,result.error,false};

     return {StrLen(str,result.len),NoError,false};
    }
  else
    {
     return {Empty,NoError,true};
    }
 }

/* struct SpawnChild */

static_assert( Meta::IsSame<Win64::handle_t,SpawnChild::Type> ,"CCore::Sys::SpawnChild : bad Type");

ErrorType SpawnChild::spawn(char *wdir,char *path,char **argv,char **envp) noexcept
 {
  ProcessSetup setup(wdir,path,argv,envp);

  return setup.create(handle);
 }

auto SpawnChild::wait() noexcept -> WaitResult
 {
  WaitResult ret;

  switch( Win64::WaitForSingleObject(handle,Win64::NoTimeout) )
    {
     case Win64::WaitObject_0 :
      {
       unsigned exit_code;

       if( Win64::GetExitCodeProcess(handle,&exit_code) )
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

     case Win64::WaitFailed :
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

  Win64::CloseHandle(handle);

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

     if( Win64::GetExitCodeProcess(handle,&exit_code) )
       {
        ret.status=(int)exit_code;
        ret.error=NoError;
       }
     else
       {
        ret.status=1000;
        ret.error=NonNullError();
       }

     Win64::CloseHandle(handle);

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
     auto result=Win64::WaitForMultipleObjects(list.len,list.ptr,false,Win64::NoTimeout);

     if( result==Win64::WaitFailed )
       {
        return {0,NonNullError()};
       }

     if( result>=Win64::WaitObject_0 && ulen(result-Win64::WaitObject_0)<list.len )
       {
        return {ulen(result-Win64::WaitObject_0),NoError};
       }

     return {0,Error_Spawn};
    }
 };

/* struct SpawnWaitList */

ErrorType SpawnWaitList::init(ulen reserve) noexcept
 {
  SilentReportException report;

  try
    {
     engine=new Engine(reserve);

     return NoError;
    }
  catch(CatchType)
    {
     return ErrorType(Win64::ErrorNotEnoughMemory);
    }
 }

ErrorType SpawnWaitList::exit() noexcept
 {
  bool nok=engine->notEmpty();

  delete Replace_null(engine);

  return nok?Error_Running:NoError;
 }

ErrorType SpawnWaitList::add(SpawnChild *spawn,void *arg) noexcept
 {
  SilentReportException report;

  try
    {
     engine->add(spawn->handle,arg);

     return NoError;
    }
  catch(CatchType)
    {
     return ErrorType(Win64::ErrorNotEnoughMemory);
    }
 }

auto SpawnWaitList::wait() noexcept -> WaitResult
 {
  return engine->wait();
 }

} // namespace Sys
} // namespace CCore

