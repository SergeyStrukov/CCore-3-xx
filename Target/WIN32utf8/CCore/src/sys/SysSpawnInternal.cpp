/* SysSpawnInternal.cpp */
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

#include <CCore/inc/sys/SysSpawnInternal.h>

#include <CCore/inc/GenFile.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* class ProcessSetup */

class ProcessSetup::BuildStr : NoCopy
 {
   Collector<WChar> out;

  public:

   BuildStr() {}

   ~BuildStr() {}

   void put(WChar ch) { out.append_copy(ch); }

   void putStr(StrLen str)
    {
     while( +str )
       {
        Unicode sym=CutUtf8_unicode(str);

        if( sym==Unicode(-1) ) throw Error_BrokenUtf8;

        if( IsSurrogate(sym) )
          {
           SurrogateCouple couple(sym);

           put(couple.hi);
           put(couple.lo);
          }
        else
          { // may insert forbidden symbol
           put(WChar(sym));
          }
       }
    }

   void putArg(StrLen str)
    {
     put('"');

     while( +str )
       {
        Unicode sym=CutUtf8_unicode(str);

        if( sym==Unicode(-1) ) throw Error_BrokenUtf8;

        if( IsSurrogate(sym) )
          {
           SurrogateCouple couple(sym);

           put(couple.hi);
           put(couple.lo);
          }
        else
          { // may insert forbidden symbol

           switch( sym )
             {
              case '"' : put('\\'); put('"'); break;

              case '\\' : put('\\'); put('\\'); break;

              default: put(WChar(sym));
             }
          }
       }

     put('"');
    }

   void extractTo(DynArray<WChar> &ret) { out.extractTo(ret); }
 };

/* class ProcessSetup */

void ProcessSetup::makeDir(char *wdir)
 {
  if( wdir )
    {
     BuildStr out;

     out.putStr(wdir);
     out.put(0);

     out.extractTo(dir);

     WChar temp[MaxPathLen+1];

     ulen len=Win32::GetFullPathNameW(dir.getPtr(),MaxPathLen+1,temp,0);

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
  error=ErrorType(Win32::ErrorNotEnoughMemory);

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

ErrorType ProcessSetup::create(Win32::handle_t &handle) noexcept
 {
  if( error ) return error;

  Win32::flags_t flags=Win32::UnicodeEnvironment;

  Win32::StartupInfo info{};

  info.cb=sizeof info;

  Win32::ProcessInfo pinfo;

  const WChar *wdir=0;

  if( has_dir ) wdir=dir.getPtr();

  if( Win32::CreateProcessW(0,cmdline.getPtr(),0,0,false,flags,envblock.getPtr(),wdir,&info,&pinfo) )
    {
     Win32::CloseHandle(pinfo.h_thread);

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

