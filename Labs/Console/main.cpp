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

#include <CCore/inc/ReadCon.h>
#include <CCore/inc/Task.h>

namespace App {

/* using */

using namespace CCore;

/* class StopFlag */

class StopFlag : NoCopy
 {
   Atomic cancel_flag;

   ReadCon con;

   unsigned count = 0 ;

   Atomic stop_flag;

   Sem stop_sem;

  private:

   void input(Symbol sym);

   void objRun();

  public:

   StopFlag();

   ~StopFlag();

   void guard();
 };

void StopFlag::input(Symbol sym)
 {
  if( ToChar(sym)=='x' )
    {
     count++;

     if( count>=3 )
       {
        cancel_flag=true;
        stop_flag=true;
       }
    }
 }

void StopFlag::objRun()
 {
  try
    {
     while( !stop_flag )
       {
        Symbol sym;

        if( con.get(100_msec,sym) ) input(sym);
       }
    }
  catch(...)
    {
     cancel_flag=true;
    }
 }

StopFlag::StopFlag()
 {
  RunFuncTask( [&] () { objRun(); } ,stop_sem.function_give());
 }

StopFlag::~StopFlag()
 {
  //con.interrupt();

  stop_flag=true;

  stop_sem.take();
 }

void StopFlag::guard()
 {
  if( cancel_flag )
    {
     Printf(Exception,"App : cancel flag is set");
    }
 }

/* Main() */

void Step()
 {
  SpawnSlot slot1;
  SpawnSlot slot2;

  {
   SpawnProcess spawn("./test2/test.exe"_c);

   spawn.addArg("test.exe"_c);
   spawn.addArg("t1"_c);

   spawn.spawn(slot1);
  }

  {
   SpawnProcess spawn("./test2/test.exe"_c);

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
 }

void Main()
 {
  StopFlag stop_flag;

  for(unsigned count=10; count ;count--)
    {
     stop_flag.guard();

     Step();
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

