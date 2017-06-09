/* test4006.MultiEvent.cpp */
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

namespace App {

namespace Private_4006 {

/* Wait...() */

ulen Wait(MultiEventBase &mev) { return mev.wait(); }

ulen WaitTimed(MultiEventBase &mev) { return mev.wait(1_msec); }

/* class Data<WaitFunc> */

template <ulen WaitFunc(MultiEventBase &)>
class Data : public Funchor_nocopy
 {
   static const ulen TaskCount =       5 ;
   static const ulen Rep       = 100'000 ;

  private:

   MultiEvent<TaskCount+1> mev;
   AntiSem asem;
   ulen total[TaskCount];
   bool wait_flag;

  private:

   void wait()
    {
     ulen count[TaskCount]={};

     ulen timeout_count=0;

     for(;;)
       {
        ulen index=WaitFunc(mev);

        if( index==0 )
          {
           timeout_count++;

           continue;
          }

        index--;

        if( index<TaskCount )
          {
           count[index]++;

           asem.dec();
          }
        else
          {
           for(ulen i=0; i<TaskCount ;i++) total[i]+=count[i];

           mev.trigger(TaskCount+1);

           if( timeout_count ) Printf(Con,"timeout = #;\n",timeout_count);

           return;
          }
       }
    }

   void trigger_loop(ulen index)
    {
     for(ulen count=Rep; count ;count--)
       {
        asem.inc();

        if( !mev.trigger(index+1) ) asem.dec();

        Task::Sleep(1_msec);
       }
    }

   Function<void (void)> function_wait() { return FunctionOf(this,&Data::wait); }

   void stop()
    {
     if( wait_flag ) asem.wait();

     mev.trigger(TaskCount+1);
    }

   Function<void (void)> function_stop() { return FunctionOf(this,&Data::stop); }

  public:

   Data() : mev("TestMev"),total() {}

   void run()
    {
     Data *data=this;

     wait_flag=false;

     RunTask run_wait(function_stop());

     run_wait(TaskCount,function_wait());

     RunTask run_trigger;

     for(ulen index=0; index<TaskCount ;index++) run_trigger( [=] () -> void { data->trigger_loop(index); } );

     wait_flag=true;
    }

   void show(StrLen name)
    {
     Printf(Con,"#; give #;\n\n",name,TaskCount*Rep);

     for(ulen i=0; i<TaskCount ;i++) Printf(Con,"total[#;] = #;\n",i,total[i]);

     Printf(Con,"\n\n");
    }
 };

} // namespace Private_4006

using namespace Private_4006;

/* Testit<4006> */

template<>
const char *const Testit<4006>::Name="Test4006 MultiEvent";

template<>
bool Testit<4006>::Main()
 {
  {
   Data<Wait> data;

   data.run();

   data.show("Wait");
  }

  {
   Data<WaitTimed> data;

   data.run();

   data.show("WaitTimed");
  }

  return true;
 }

} // namespace App

