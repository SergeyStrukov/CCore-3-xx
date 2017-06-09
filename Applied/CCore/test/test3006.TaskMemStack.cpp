/* test3006.TaskMemStack.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/TaskMemStack.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_3006 {

class Test : NoCopy
 {
   static const ulen MaxLevel = 1000 ;
   static const uint32 MaxLen = 100 ;

   Random random;

   ulen level = 0 ;
   ulen count = 0 ;

  private:

   void fill(unsigned seed,PtrLen<unsigned> r)
    {
     for(; +r ;++r,++seed) *r=seed;
    }

   void check(unsigned seed,PtrLen<const unsigned> r)
    {
     for(; +r ;++r,++seed)
       if( *r!=seed )
         {
          Printf(Exception,"test failed");
         }
    }

  public:

   Test() {}

   ~Test() {}

   void test()
    {
     if( !count ) return;

     count--;
     level++;

     if( level<MaxLevel )
       {
        StackArray<unsigned> temp(random.select(MaxLen));
        unsigned seed=random.next_uint<unsigned>();

        fill(seed,Range(temp));

        if( random.select(20)<19 ) test();

        check(seed,Range_const(temp));
       }

     level--;
    }

   void run(ulen count_)
    {
     count=count_;

     while( count ) test();
    }
 };

} // namespace Private_3006

using namespace Private_3006;

/* Testit<3006> */

template<>
const char *const Testit<3006>::Name="Test3006 TaskMemStack";

template<>
bool Testit<3006>::Main()
 {
  TaskMemStack task_stack;

  Test test;

  test.run(10'000'000);

  return true;
 }

} // namespace App

