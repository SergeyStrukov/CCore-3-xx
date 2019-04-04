/* SysSpawnInternal.cpp */
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

#include <CCore/inc/sys/SysSpawnInternal.h>

#include <CCore/inc/GenFile.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/win64/Win64.h>

namespace CCore {
namespace Sys {

/* class ProcessSetup */

class ProcessSetup::BuildStr : NoCopy
 {
   Collector<char> out;

  public:

   BuildStr() {}

   ~BuildStr() {}

   void put(char ch) { out.append_copy(ch); }

   void putStr(StrLen str) { out.extend_copy(str); }

   void putArg(StrLen str)
    {
     put('"');

     for(char sym : str )
       {
        switch( sym )
          {
           case '"' : put('\\'); put('"'); break;

           case '\\' : put('\\'); put('\\'); break;

           default: put(sym);
          }
       }

     put('"');
    }

   void extractTo(DynArray<char> &ret) { out.extractTo(ret); }
 };

/* class ProcessSetup */

void ProcessSetup::makeDir(char *wdir)
 {
  if( wdir )
    {
     char temp[MaxPathLen+1];

     ulen len=Win64::GetFullPathNameA(wdir,MaxPathLen+1,temp,0);

     if( !len ) throw NonNullError();

     if( len>MaxPathLen ) throw Error_TooLong;

     dir.erase();

     dir.extend_copy(Range(temp,len+1));

     has_dir=true;
    }
  else
    {
     has_dir=false;
    }
 }

void ProcessSetup::makeCmdline(char *path,char **argv)
 {
  BuildStr out;

  out.putArg(path);

  if( *argv )
    {
     for(argv++; const char *str=*argv ;argv++)
       {
        out.put(' ');

        out.putArg(str);
       }
    }

  out.put(0);

  out.extractTo(cmdline);
 }

void ProcessSetup::makeEnvblock(char **envp)
 {
  BuildStr out;

  for(; const char *str=*envp ;envp++)
    {
     if( *str )
       {
        out.putStr(str);

        out.put(0);
       }
    }

  out.put(0);

  out.extractTo(envblock);
 }

ProcessSetup::ProcessSetup(char *wdir,char *path,char **argv,char **envp) noexcept
 {
  error=ErrorType(Win64::ErrorNotEnoughMemory);

  SilentReportException report;

  try
    {
     makeDir(wdir);

     makeCmdline(path,argv);

     makeEnvblock(envp);

     error=NoError;
    }
  catch(CatchType)
    {
    }
  catch(ErrorType e)
    {
     error=e;
    }
 }

ProcessSetup::~ProcessSetup()
 {
 }

ErrorType ProcessSetup::create(Win64::handle_t &handle) noexcept
 {
  if( error ) return error;

  Win64::flags_t flags=0;

  Win64::StartupInfo info{};

  info.cb=sizeof info;

  Win64::ProcessInfo pinfo;

  const char *wdir=0;

  if( has_dir ) wdir=dir.getPtr();

  if( Win64::CreateProcessA(0,cmdline.getPtr(),0,0,false,flags,envblock.getPtr(),wdir,&info,&pinfo) )
    {
     Win64::CloseHandle(pinfo.h_thread);

     handle=pinfo.h_process;

     return NoError;
    }
  else
    {
     return NonNullError();
    }
 }

} // namespace Sys
} // namespace CCore

