/* test4002.Sem.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

#include <CCore/inc/Abort.h>

namespace App {

namespace Private_4002 {

/* Take...() */

template <class TestSem>
bool Take(TestSem &sem)
 {
  sem.take();

  return true;
 }

template <class TestSem>
bool TakeTimed(TestSem &sem)
 {
  return sem.take(1_msec);
 }

/* class Data<TestSem,Take> */

template <class TestSem,bool Take(TestSem &sem)>
class Data : public Funchor_nocopy
 {
   static const ulen TaskCount =         5 ;
   static const ulen Rep       = 1'000'000 ;

  private:

   TestSem sem;

   Atomic total_give;
   Atomic total_take;
   Atomic shared;
   Atomic take_flag;

  private:

   void give()
    {
     total_give++;
     shared++;

     sem.give();
    }

   bool take()
    {
     if( Take(sem) )
       {
        if( (shared--)==0 ) Abort("test failed");

        total_take++;

        return true;
       }

     return false;
    }

   void give_loop()
    {
     for(ulen count=Rep; count ;count--) give();
    }

   void take_loop()
    {
     ulen count=0;

     while( take_flag ) count+=take();

     while( total_take<total_give ) count+=take();

     give();

     Printf(Con,"count = #;\n",count);
    }

   Function<void (void)> function_give_loop() { return FunctionOf(this,&Data::give_loop); }

   Function<void (void)> function_take_loop() { return FunctionOf(this,&Data::take_loop); }

   void stop()
    {
     take_flag=0;

     give();
    }

   Function<void (void)> function_stop() { return FunctionOf(this,&Data::stop); }

  public:

   Data() : sem("TestSem") { take_flag=1; }

   ~Data() {}

   void run()
    {
     RunTask run_take(function_stop());

     run_take(TaskCount,function_take_loop());

     RunTask run_give;

     run_give(TaskCount,function_give_loop());
    }

   void show(StrLen name)
    {
     Printf(Con,"#; : total_give = #; total_take = #;\n\n",name,total_give,total_take);
    }
 };

} // namespace Private_4002

using namespace Private_4002;

/* Testit<4002> */

template<>
const char *const Testit<4002>::Name="Test4002 Sem";

template<>
bool Testit<4002>::Main()
 {
  {
   Data<SlowSem,Take<SlowSem> > data;

   data.run();

   data.show("SlowSem");
  }

  {
   Data<SlowSem,TakeTimed<SlowSem> > data;

   data.run();

   data.show("SlowSem timed");
  }

  {
   Data<Sem,Take<Sem> > data;

   data.run();

   data.show("Sem");
  }

  {
   Data<Sem,TakeTimed<Sem> > data;

   data.run();

   data.show("Sem timed");
  }

  return true;
 }

} // namespace App

