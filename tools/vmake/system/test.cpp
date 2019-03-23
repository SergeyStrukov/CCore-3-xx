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

#include <CCore/inc/MemBase.h>

#include "SpawnProcess.h"

#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

#include <string.h>
#include <stdlib.h>

using namespace App;

/* test1() */

void test1()
 {
  int pid;

  const char * args[]={"sh",0};

  char *temp=(char *)MemAlloc(80);

  strcpy(temp,"/bin/sh");

  if( posix_spawnp(&pid,temp,0,0,(char *const *)args,environ) ) // "/bin/sh"
    {
     Printf(Con,"spawn failed\n");
    }
  else
    {
     int result=0;

     int ret=waitpid(pid,&result,0);

     Printf(Con,"pid = #; result = #;\n",ret,result);
    }

  MemFree(temp);
 }

/* test2() */

void test2()
 {
  FileSystem fs;
  VMake::SpawnProcess spawn(fs,""_c,"/bin/sh"_c);

  spawn.addArg("sh"_c);

  spawn.spawn();

  spawn.wait();
 }

/* main() */

int main()
 {
  try
    {
     ReportException report;

     test1();

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

