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

  public:

   Pipe()
    {
     Win32::SecurityAttributes sa{};

     sa.inherit=true;

     if( !Win32::CreatePipe(&h_read,&h_write,&sa,0) )
       {
        Printf(Exception,"App : cannot create pipe");
       }
    }

   ~Pipe()
    {
     Win32::CloseHandle(h_read);
     Win32::CloseHandle(h_write);
    }

   Win32::handle_t getHRead() const { return h_read; }

   Win32::handle_t getHWrite() const { return h_write; }
 };

/* class PipeToBuf */

class PipeToBuf : NoCopy
 {
   Pipe pipe;
   PtrLen<char> buf;
   PtrLen<char> next;

   ulen bad_count = 0 ;

  public:

   explicit PipeToBuf(PtrLen<char> buf_)
    : buf(buf_)
    {
     next=buf;
    }

   Pipe & getPipe() { return pipe; }

   PtrLen<char> getData()
    {
     return buf.prefix(next);
    }

   ulen pump()
    {
     Win32::ulen_t avail_len;

     if( !Win32::PeekNamedPipe(pipe.getHRead(),0,0,0,&avail_len,0) )
       {
        Printf(Exception,"App : read pipe failed");
       }

     if( !avail_len )
       {
        Win32::Sleep(1);

        bad_count++;

        return 0;
       }

     Printf(Con,"pump() bad_count = #;",Replace_null(bad_count));

     if( !next.len )
       {
        Printf(Exception,"App : read pipe overflow");
       }

     Win32::ulen_t ret_len;

     if( !Win32::ReadFile(pipe.getHRead(),next.ptr,next.len,&ret_len,0) )
       {
        Printf(Exception,"App : read pipe failed");
       }

     if( ret_len>next.len )
       {
        Printf(Exception,"App : read pipe bad len");
       }

     next+=ret_len;

     Printf(Con," : #;\n",ret_len);

     return ret_len;
    }

   void pumpRest()
    {
     Printf(Con,"pumpRest()");

     while( pump() );

     Printf(Con," bad_count = #;\n",Replace_null(bad_count));
    }
 };

/* struct FromProgram */

struct FromProgram
 {
  StrLen str;
  bool ok = false ;

  static DynArray<Sys::WChar> MakeCmdline(StrLen str)
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

    DynArray<Sys::WChar> ret;

    out.extractTo(ret);

    return ret;
   }

  static void Pump(Win32::handle_t h_process,PipeToBuf &dev)
   {
    Win32::handle_t temp[2]={h_process,dev.getPipe().getHRead()};

    for(;;)
      {
       switch( Win32::WaitForMultipleObjects(2,temp,false,Win32::NoTimeout) )
         {
          case Win32::WaitObject_0 :
           {
            dev.pumpRest();

            return;
           }
          break;

          case Win32::WaitObject_0+1 :
           {
            dev.pump();
           }
          break;

          default:
           {
            Printf(Exception,"App : pump failed");
           }
         }
      }
   }

  static Win32::handle_t Run(Win32::wchar *wcmd,Win32::handle_t h_write)
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

       return pinfo.h_process;
      }
    else
      {
       Printf(Exception,"App : failed to create a process");

       return 0;
      }
   }

  FromProgram(StrLen cmdline,PtrLen<char> result)
   {
    DynArray<Sys::WChar> temp=MakeCmdline(cmdline);

    PipeToBuf dev(result);

    Win32::handle_t h_process=Run(temp.getPtr(),dev.getPipe().getHWrite());

    ScopeGuard guard( [=] () { Win32::CloseHandle(h_process); } );

    Pump(h_process,dev);

    unsigned exit_code;

    if( !Win32::GetExitCodeProcess(h_process,&exit_code) )
      {
       Printf(Exception,"App : failed to get exit code");
      }

    if( exit_code )
      {
       Printf(Exception,"App : exit code is nonzero");
      }

    str=dev.getData();

    ok=true;
   }
 };

} // namespace Private_Utils

using namespace Private_Utils;

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

