/* test4001.Mutex.cpp */
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

#include <CCore/inc/Random.h>

namespace App {

namespace Private_4001 {

/* ShowSemCount() */

template <class Mutex>
void ShowSemCount(Mutex &) {}

void ShowSemCount(Mutex &mutex) { Printf(Con,"sem_count = #;\n",mutex.getSemCount()); }

/* class Data<Mutex> */

template <class Mutex>
class Data : public Funchor_nocopy
 {
   static const ulen TaskCount =      10 ;
   static const ulen Rep       = 100'000 ;

   static const unsigned MaxDelay = 10000 ;

  private:

   Mutex mutex;
   volatile ulen shared;

  private:

   static void DelayLoop(ulen count_)
    {
     for(volatile ulen count=count_; count ; count--);
    }

   void inc()
    {
     typename Mutex::Lock lock(mutex);

     shared++;
    }

   void loop()
    {
     Random random;

     for(ulen count=Rep; count ;count--)
       {
        inc();

        DelayLoop(random.select(MaxDelay));

        //Task::Sleep(1_msec);
       }
    }

   Function<void (void)> function_loop() { return FunctionOf(this,&Data::loop); }

  public:

   Data()
    {
     shared=0;
    }

   void run()
    {
     RunTask run_task;

     run_task(TaskCount,function_loop());
    }

   void show(StrLen name)
    {
     Printf(Con,"#; : shared = #; expected = #;\n\n",name,shared,TaskCount*Rep);

     ShowSemCount(mutex);
    }
 };

} // namespace Private_4001

using namespace Private_4001;

/* Testit<4001> */

template<>
const char *const Testit<4001>::Name="Test4001 Mutex";

template<>
bool Testit<4001>::Main()
 {
  {
   Data<NoMutex> data;

   data.run();

   data.show("NoMutex");
  }

  {
   Data<FastMutex> data;

   data.run();

   data.show("FastMutex");
  }

  {
   Data<Mutex> data;

   data.run();

   data.show("Mutex");
  }

  return true;
 }

} // namespace App

