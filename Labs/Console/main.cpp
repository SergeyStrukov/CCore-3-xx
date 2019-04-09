/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/Console
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

#include <CCore/inc/SpawnProcess.h>

namespace App {

/* using */

using namespace CCore;

/* Main() */

void Main()
 {
  SpawnSlot slot1;
  SpawnSlot slot2;

  {
   SpawnProcess spawn("./test1/test.exe"_c);

   spawn.addArg("test.exe"_c);
   spawn.addArg("t1"_c);

   spawn.spawn(slot1);
  }

  {
   SpawnProcess spawn("./test1/test.exe"_c);

   spawn.addArg("test.exe"_c);
   spawn.addArg("t2"_c);

   spawn.spawn(slot2);
  }

  SpawnSet set(2);

  set.add(&slot1);
  set.add(&slot2);

  for(unsigned count=2; count ;)
    {
     auto result=set.wait();

     if( result.slot ) count--;
    }

  Printf(Con,"main stop\n\n");
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  try
    {
     ReportException report;

     Main();

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

