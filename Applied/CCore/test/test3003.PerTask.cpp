/* test3003.PerTask.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Fundamental Mini
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

#include <CCore/inc/PerTask.h>

namespace App {

namespace Private_3003 {

/* struct Acc */

struct Acc
 {
  static const Unid TypeUnid;

  class ObjectType : public MemBase_nocopy
   {
     unsigned acc;

    public:

     explicit ObjectType(unsigned start)
      : acc(start)
      {
       Printf(Con,"start acc = #;\n",acc);
      }

     ~ObjectType()
      {
       Printf(Con,"end acc = #;\n",acc);
      }

     void inc() { acc++; }

     void destroy() { delete this; }
   };

  class BuilderType
   {
     unsigned start;

    public:

     explicit BuilderType(unsigned start_) : start(start_) {}

     ObjectType * create() { return new ObjectType(start); }
   };
 };

const Unid Acc::TypeUnid={{0x3905'4602,0x14E2'5482,0x6E96'8E13,0x99E3'3A70,0xC7EE'DAE0,0x099F'3471,0xA88F'C37E,0x1F66'C070}};

/* test() */

void test()
 {
  PerTaskObjectScope<Acc> scope;

  const ulen Rep = 10'000'000 ;

  for(ulen count=Rep; count ;count--) GetTaskObject<Acc>()->inc();
 }

} // namespace Private_3003

using namespace Private_3003;

/* Testit<3003> */

template<>
const char *const Testit<3003>::Name="Test3003 PerTask";

template<>
bool Testit<3003>::Main()
 {
  const ulen TaskCount = 10 ;

  DestroyPerTask dpt;

  {
   TaskObjectBuild<Acc> task_object(100);

   RunTask run_task;

   run_task(TaskCount,test);
  }

  {
   TaskObjectBuild<Acc> task_object(200);

   RunTask run_task;

   run_task(TaskCount,test);

   test();
  }

  return true;
 }

} // namespace App

