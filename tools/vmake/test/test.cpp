/* test.cpp */
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

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/sys/SysUtf8.h>
#include <CCore/inc/win32/Win32.h>

namespace Win32 {
extern "C" {

wchar * WIN32_API GetEnvironmentStringsW(void);

} // extern "C"
} // namespace Win32

#include <unistd.h>
#include <stdlib.h>

/* main() */

using namespace CCore;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     {
      Printf(Con,"self = #.q;\n",argv[0]);

      PrintFile out("args.txt");

      for(int i=0; i<argc ;i++) Printf(out,"argv[#;] = #.q;\n",i,argv[i]);

      Putch(out,'\n');

      for(ulen i=0; const char *str=environ[i] ;i++) Printf(out,"env[#;] = #.q;\n",i,str);

      Putch(out,'\n');

      {
       Win32::wchar *base=Win32::GetEnvironmentStringsW();

       if( base )
         {
          while( *base )
            {
             Win32::wchar *str=base;
             Win32::wchar *lim=(Win32::wchar *)Sys::ZScan(str);

             base=lim+1;

             char temp[TextBufLen];

             ulen len=Sys::Truncate(Range(str,lim),Range(temp));

             Printf(out,"#.q;\n",StrLen(temp,len));
            }
         }
      }

      if( argc>1 )
        {
         int t=atoi(argv[1]);

         if( t ) sleep(t);
        }
     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }


