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

#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

using namespace CCore;

/* test() */

void test()
 {
  int pid;

  const char * args[]={"sh",0};

  if( posix_spawnp(&pid,"/bin/sh",0,0,(char *const *)args,environ) )
    {
     Printf(Con,"spawn failed\n");

     return;
    }

  int result=0;

  int ret=waitpid(pid,&result,0);

  Printf(Con,"pid = #; result = #;\n",ret,result);
 }

/* main() */

int main()
 {
  try
    {
     ReportException report;

     test();

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

