/* test4007.Sem-speed.cpp */
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

#include <CCore/inc/Task.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_4007 {

/* class NoSem */

class NoSem : NoCopy
 {
  public:

   NoSem()
    {
    }

   ~NoSem()
    {
    }

   void give()
    {
    }

   void take()
    {
    }
 };

/* class AtomicNoSem */

class AtomicNoSem : NoCopy
 {
   Atomic count;

  public:

   AtomicNoSem()
    {
    }

   ~AtomicNoSem()
    {
    }

   void give()
    {
     count++;
    }

   void take()
    {
     count--;
    }
 };

/* test<Sem>() */

template <class Sem>
void test(StrLen name)
 {
  const unsigned Rep = 10'000 ;

  Sem sem;

  {
   TimeStat<ClockTimer::ValueType> stat;

   for(unsigned count=Rep; count ;count--)
     {
      ClockTimer timer;

      sem.give();

      stat.add(timer.get());
     }

   Printf(Con,"#; give: #;\n",name,stat);
  }

  {
   TimeStat<ClockTimer::ValueType> stat;

   for(unsigned count=Rep; count ;count--)
     {
      ClockTimer timer;

      sem.take();

      stat.add(timer.get());
     }

   Printf(Con,"#; take: #;\n\n",name,stat);
  }
 }

} // namespace Private_4007

using namespace Private_4007;

/* Testit<4007> */

template<>
const char *const Testit<4007>::Name="Test4007 Sem speed";

template<>
bool Testit<4007>::Main()
 {
  test<NoSem>("NoSem");
  test<AtomicNoSem>("AtomicNoSem");
  test<SlowSem>("SlowSem");
  test<Sem>("Sem");

  return true;
 }

} // namespace App

