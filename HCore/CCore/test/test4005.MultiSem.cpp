/* test4005.MultiSem.cpp */
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

namespace Private_4005 {

/* Take...() */

ulen Take(MultiSemBase &msem) { return msem.take(); }

ulen TakeTimed(MultiSemBase &msem) { return msem.take(1_msec); }

/* class Data<TakeFunc> */

template <ulen TakeFunc(MultiSemBase &)>
class Data : public Funchor_nocopy
 {
   static const ulen TaskCount =    5 ;
   static const ulen Rep       = 1000 ;

  private:

   MultiSem<TaskCount+1> msem;
   AntiSem asem;
   ulen total[TaskCount];
   bool wait_flag;

  private:

   void take()
    {
     ulen count[TaskCount]={};

     ulen timeout_count=0;

     for(;;)
       {
        ulen index=TakeFunc(msem);

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

           msem.give(TaskCount+1);

           if( timeout_count ) Printf(Con,"timeout = #;\n",timeout_count);

           return;
          }
       }
    }

   void give_loop(ulen index)
    {
     for(ulen count=Rep; count ;count--)
       {
        msem.give(index+1);

        //Task::Sleep(1_msec);
       }
    }

   Function<void (void)> function_take() { return FunctionOf(this,&Data::take); }

   void stop()
    {
     if( wait_flag ) asem.wait();

     msem.give(TaskCount+1);
    }

   Function<void (void)> function_stop() { return FunctionOf(this,&Data::stop); }

  public:

   Data() : msem("TestMSem"),total() { asem.add(TaskCount*Rep); }

   void run()
    {
     Data *data=this;

     wait_flag=false;

     RunTask run_task(function_stop());

     run_task(TaskCount,function_take());

     for(ulen index=0; index<TaskCount ;index++) run_task( [=] () -> void { data->give_loop(index); } );

     wait_flag=true;
    }

   void show(StrLen name)
    {
     Printf(Con,"#; give #;\n\n",name,TaskCount*Rep);

     for(ulen i=0; i<TaskCount ;i++) Printf(Con,"total[#;] = #;\n",i,total[i]);

     Printf(Con,"\n\n");
    }
 };

} // namespace Private_4005

using namespace Private_4005;

/* Testit<4005> */

template<>
const char *const Testit<4005>::Name="Test4005 MultiSem";

template<>
bool Testit<4005>::Main()
 {
  {
   Data<Take> data;

   data.run();

   data.show("Take");
  }

  {
   Data<TakeTimed> data;

   data.run();

   data.show("TakeTimed");
  }

  return true;
 }

} // namespace App

