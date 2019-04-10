/* ProcessUtils.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ProcessUtils.h>

#include <CCore/inc/sys/SysError.h>
#include <CCore/inc/sys/SysUtf8.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/CharProp.h>

#include <CCore/inc/PrintError.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/win64/Win64.h>

namespace CCore {

namespace Private_ProcessUtils {

/* class Pipe */

class Pipe : NoCopy
 {
   Win64::handle_t h_read;
   Win64::handle_t h_write;

   bool has_read = true ;
   bool has_write = true ;

  public:

   Pipe()
    {
     if( !Win64::CreatePipe(&h_read,&h_write,0,0) )
       {
        Printf(Exception,"CCore::Private_ProcessUtils::Pipe::Pipe() : #;",PrintError(Sys::NonNullError()));
       }

     if( !Win64::SetHandleInformation(h_write,Win64::HandleInherit,Win64::HandleInherit) )
       {
        Printf(Exception,"CCore::Private_ProcessUtils::Pipe::Pipe() : #;",PrintError(Sys::NonNullError()));
       }
    }

   ~Pipe()
    {
     closeHRead();
     closeHWrite();
    }

   Win64::handle_t getHRead() const { return h_read; }

   Win64::handle_t getHWrite() const { return h_write; }

   void closeHRead()
    {
     if( Change(has_read,false) ) Win64::CloseHandle(h_read);
    }

   void closeHWrite()
    {
     if( Change(has_write,false) ) Win64::CloseHandle(h_write);
    }
 };

/* class PipeToBuf */

class PipeToBuf : public Pipe
 {
   PtrLen<char> buf;
   PtrLen<char> next;

  public:

   explicit PipeToBuf(PtrLen<char> buf_)
    : buf(buf_)
    {
     next=buf;
    }

   ~PipeToBuf()
    {
    }

   PtrLen<char> getData()
    {
     return buf.prefix(next);
    }

   void pump()
    {
     for(;;)
       {
        if( !next.len )
          {
           Printf(Exception,"CCore::Private_ProcessUtils::PipeToBuf::pump() : read pipe overflow");
          }

        Win64::ulen_t ret_len;

        if( !Win64::ExtReadFile(getHRead(),next.ptr,next.len,&ret_len) )
          {
           auto error=Sys::NonNullError();

           if( error==Win64::ErrorBrokenPipe ) return;

           Printf(Exception,"CCore::Private_ProcessUtils::PipeToBuf::pump() : #;",PrintError(error));
          }

        if( ret_len>next.len )
          {
           Printf(Exception,"CCore::Private_ProcessUtils::PipeToBuf::pump() : read pipe bad len");
          }

        next+=ret_len;
       }
    }
 };

/* class RunProcess */

class RunProcess : NoCopy
 {
   Win64::handle_t h_process = 0 ;

  public:

   RunProcess(Win64::wchar *wcmd,Win64::handle_t h_write)
    {
     Win64::flags_t flags=0;

     Win64::StartupInfo info{};

     info.cb=sizeof info;

     info.flags=Win64::StartupInfo_std_handles;

     info.h_stdin=Win64::InvalidFileHandle;
     info.h_stdout=h_write;
     info.h_stderr=Win64::InvalidFileHandle;

     Win64::ProcessInfo pinfo;

     if( Win64::CreateProcessW(0,wcmd,0,0,true,flags,0,0,&info,&pinfo) )
       {
        Win64::CloseHandle(pinfo.h_thread);

        h_process=pinfo.h_process;
       }
     else
       {
        Printf(Exception,"CCore::Private_ProcessUtils::RunProcess::RunProcess() : #;",PrintError(Sys::NonNullError()));
       }
    }

   ~RunProcess()
    {
     Win64::CloseHandle(h_process);
    }

   void wait()
    {
     if( Win64::WaitForSingleObject(h_process,Win64::NoTimeout)!=Win64::WaitObject_0 )
       {
        Printf(Exception,"CCore::Private_ProcessUtils::RunProcess::wait() : #;",PrintError(Sys::NonNullError()));
       }
    }

   unsigned getExitCode()
    {
     unsigned exit_code;

     if( !Win64::GetExitCodeProcess(h_process,&exit_code) )
       {
        Printf(Exception,"CCore::Private_ProcessUtils::RunProcess::getExitCode() : #;",PrintError(Sys::NonNullError()));
       }

     return exit_code;
    }
 };

/* class MakeCmdLine */

class MakeCmdLine : NoCopy
 {
   DynArray<Sys::WChar> buf;

  public:

   explicit MakeCmdLine(StrLen str)
    {
     Collector<Sys::WChar> out;

     auto put = [&] (Sys::WChar ch) { out.append_copy(ch); } ;

     while( +str )
       {
        Unicode sym=CutUtf8_unicode(str);

        if( sym==Unicode(-1) )
          {
           Printf(Exception,"CCore::Private_ProcessUtils::MakeCmdLine::MakeCmdLine(...) : broken utf8");
          }

        if( Sys::IsSurrogate(sym) )
          {
           Sys::SurrogateCouple couple(sym);

           put(couple.hi);
           put(couple.lo);
          }
        else
          { // may insert forbidden symbol
           put(Sys::WChar(sym));
          }
       }

     put(0);

     out.extractTo(buf);
    }

   ~MakeCmdLine()
    {
    }

   Sys::WChar * getPtr() { return buf.getPtr(); }
 };

} // namespace Private_ProcessUtils

using namespace Private_ProcessUtils;

/* FromProgram() */

StrLen FromProgram(StrLen cmdline_,PtrLen<char> result_buf)
 {
  MakeCmdLine cmdline(cmdline_);

  PipeToBuf dev(result_buf);

  RunProcess proc(cmdline.getPtr(),dev.getHWrite());

  dev.closeHWrite();

  dev.pump();

  dev.closeHRead();

  proc.wait();

  if( auto exit_code=proc.getExitCode() )
    {
     Printf(Exception,"CCore::FromProgram(#.q;,...) : exit code is nonzero #;",cmdline_,exit_code);
    }

  return dev.getData();
 }

/* class UnixRootDir */

void UnixRootDir::make()
 {
  StrLen result=FromProgram("cygpath -m -a --codepage UTF8 /"_c,Range(buf));

  str=CutLine(result);
 }

/* class UnixHomeDir */

void UnixHomeDir::make()
 {
  StrLen result=FromProgram("cygpath -m -a --codepage UTF8 ~"_c,Range(buf));

  str=CutLine(result);
 }

} // namespace CCore

