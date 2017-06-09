/* test2038.AtomicRefArray.cpp */
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

#include <CCore/inc/Array.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_2038 {

/* class Engine */

class Engine : public Funchor_nocopy
 {
   static const ulen TaskCount = 10 ;
   static const ulen Rep = 1'000'000 ;

   using Array = AtomicRefArray<unsigned> ;

   Mutex mutex;

   Array shared;

   PrintFile out;

  private:

   Array get()
    {
     Mutex::Lock lock(mutex);

     return shared;
    }

   void put(const Array &a)
    {
     Mutex::Lock lock(mutex);

     shared=a;

     Printf(out,"#;\n",a.getLen());
    }

   void task()
    {
     Random random;

     for(ulen count=Rep; count ;count--)
       switch( random.select(10) )
         {
          case 0 :
           {
            auto a=get();

            a.extend_fill(100,666);

            if( a.getLen()<10000 )
              {
               put(a);
              }
            else
              {
               Array a(500);

               put(a);
              }
           }
          break;

          case 1 :
           {
            auto a=get();

            a.shrink(10);

            put(a);
           }
          break;

          default:
           {
            auto a=get();

            unsigned sum=0;

            for(unsigned x : a) sum+=x;

            a.append_copy(sum);

            put(a);
           }
         }
    }

   Function<void (void)> function_task() { return FunctionOf(this,&Engine::task); }

  public:

   Engine() : out("test2038.txt") {}

   ~Engine() {}

   void run()
    {
     RunTask run_task;

     run_task(TaskCount,function_task());
    }
 };

} // namespace Private_2038

using namespace Private_2038;

/* Testit<2038> */

template<>
const char *const Testit<2038>::Name="Test2038 AtomicRefArray";

template<>
bool Testit<2038>::Main()
 {
  Engine engine;

  engine.run();

  return true;
 }

} // namespace App

