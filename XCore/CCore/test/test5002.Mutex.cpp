/* test5002.Mutex.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

#include <CCore/inc/sys/SysLog.h>

namespace App {

namespace Private_5002 {

/* class Data<Mutex> */

template <class Mutex>
class Data : public Funchor_nocopy
 {
   static const ulen Num = 50     ;
   static const ulen Rep = 100000 ;

  private:

   Mutex mutex;
   volatile ulen shared;

  private:

   void inc()
    {
     typename Mutex::Lock lock(mutex);

     shared++;
    }

   void loop()
    {
     for(ulen rep=Rep; rep ;rep--) inc();
    }

   Function<void (void)> function_loop() { return FunctionOf(this,&Data::loop); }

  public:

   Data()
    : mutex("TestMutex")
    {
     shared=0;
    }

   ~Data() {}

   void run()
    {
     RunTask run_task;

     run_task(Num,function_loop());
    }

   void show(const char *name)
    {
     Printf(Con,"#; : shared = #; expected = #;\n",name,shared,Num*Rep);
    }
 };

} // namespace Private_5002

using namespace Private_5002;

/* Testit<5002> */

template<>
const char *const Testit<5002>::Name="Test5002 Mutex";

template<>
bool Testit<5002>::Main()
 {
  {
   Data<NoMutex> data;

   data.run();

   data.show("NoMutex");
  }

  {
   Data<Mutex> data;

   data.run();

   data.show("Mutex");
  }

  Printf(Con,"\n\n#;\n",Sys::PrintLog(1000));

  return true;
 }

} // namespace App

