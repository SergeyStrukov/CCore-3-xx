/* Utils.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: VMakeList 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Utils.h>

#include <CCore/inc/sys/SysUtf8.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/CharProp.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/win32/Win32.h>

namespace App {

namespace Private_Utils {

/* class Pipe */

class Pipe : NoCopy
 {
   Win32::handle_t h_read;
   Win32::handle_t h_write;

   bool has_read = true ;
   bool has_write = true ;

  public:

   Pipe()
    {
     if( !Win32::CreatePipe(&h_read,&h_write,0,0) )
       {
        Printf(Exception,"App : cannot create pipe");
       }

     if( !Win32::SetHandleInformation(h_write,Win32::HandleInherit,Win32::HandleInherit) )
       {
        Printf(Exception,"App : cannot set inherit");
       }
    }

   ~Pipe()
    {
     if( has_read ) Win32::CloseHandle(h_read);
     if( has_write ) Win32::CloseHandle(h_write);
    }

   Win32::handle_t getHRead() const { return h_read; }

   Win32::handle_t getHWrite() const { return h_write; }

   void closeHRead()
    {
     if( Change(has_read,false) ) Win32::CloseHandle(h_read);
    }

   void closeHWrite()
    {
     if( Change(has_write,false) ) Win32::CloseHandle(h_write);
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
           Printf(Exception,"App : read pipe overflow");
          }

        Win32::ulen_t ret_len;

        if( !Win32::ReadFile(getHRead(),next.ptr,next.len,&ret_len,0) )
          {
           auto error=Sys::NonNullError();

           if( error==Win32::ErrorBrokenPipe ) return;

           Printf(Exception,"App : read pipe failed");
          }

        if( ret_len>next.len )
          {
           Printf(Exception,"App : read pipe bad len");
          }

        next+=ret_len;
       }
    }
 };

/* class RunProcess */

class RunProcess : NoCopy
 {
   Win32::handle_t h_process = 0 ;

  public:

   RunProcess(Win32::wchar *wcmd,Win32::handle_t h_write)
    {
     Win32::flags_t flags=0;

     Win32::StartupInfo info{};

     info.cb=sizeof info;

     info.flags=Win32::StartupInfo_std_handles;

     info.h_stdin=Win32::InvalidFileHandle;
     info.h_stdout=h_write;
     info.h_stderr=Win32::InvalidFileHandle;

     Win32::ProcessInfo pinfo;

     if( Win32::CreateProcessW(0,wcmd,0,0,true,flags,0,0,&info,&pinfo) )
       {
        Win32::CloseHandle(pinfo.h_thread);

        h_process=pinfo.h_process;
       }
     else
       {
        Printf(Exception,"App : failed to create a process");
       }
    }

   ~RunProcess()
    {
     Win32::CloseHandle(h_process);
    }

   void wait()
    {
     if( Win32::WaitForSingleObject(h_process,Win32::NoTimeout)!=Win32::WaitObject_0 )
       {
        Printf(Exception,"App : wait process failed");
       }
    }

   unsigned getExitCode()
    {
     unsigned exit_code;

     if( !Win32::GetExitCodeProcess(h_process,&exit_code) )
       {
        Printf(Exception,"App : failed to get exit code");
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
           Printf(Exception,"App : broken utf8");
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

} // namespace Private_Utils

using namespace Private_Utils;

/* struct FromProgram */

FromProgram::FromProgram(StrLen cmdline_,PtrLen<char> result_buf)
 {
  MakeCmdLine cmdline(cmdline_);

  PipeToBuf dev(result_buf);

  RunProcess proc(cmdline.getPtr(),dev.getHWrite());

  dev.closeHWrite();

  dev.pump();

  dev.closeHRead();

  proc.wait();

  if( proc.getExitCode()!=0 )
    {
     Printf(Exception,"App : exit code is nonzero");
    }

  str=dev.getData();

  ok=true;
 }

/* class RootDir */

void RootDir::make()
 {
  FromProgram result("cygpath -m -a --codepage UTF8 /"_c,Range(buf));

  if( result.ok )
    {
     str=CutLine(result.str);
    }
  else
    {
     Printf(Exception,"App : cannot find root path");
    }
 }

/* class HomeDir */

void HomeDir::make()
 {
  FromProgram result("cygpath -m -a --codepage UTF8 ~"_c,Range(buf));

  if( result.ok )
    {
     str=CutLine(result.str);
    }
  else
    {
     Printf(Exception,"App : cannot find home path");
    }
 }

} // namespace App

