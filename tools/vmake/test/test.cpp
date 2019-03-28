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

#include <CCore/inc/sys/SysSpawn.h>

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

      for(ulen i=0; const char *str=environ[i] ;i++) Printf(out,"#;\n",str);

      Putch(out,'\n');

      auto temp=ToFunction<void (StrLen)>( [&] (StrLen env) { Printf(out,"#;\n",env); } );

      Sys::GetEnviron(temp.function());

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


