/* test5016.TickCount.cpp */
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

#include <CCore/inc/Task.h>

namespace App {

namespace Private_5016 {

/* test1() */

void test1()
 {
  TickCount_gen<51> tcnt;

  Printf(Con,"test1()\n");

  for(unsigned msec=1; msec<=10000 ;msec++)
    {
     tcnt.set(msec);

     unsigned n=0;

     while( !tcnt.tick() ) n++;

     if( n!=(msec*51-1)/1000 )
       Printf(Con,"#; #; #;\n",n,msec,(msec*51-1)/1000);
    }
 }

/* test2() */

void test2()
 {
  TickCount_gen<1550> tcnt;

  Printf(Con,"test2()\n");

  for(unsigned msec=1; msec<=10000 ;msec++)
    {
     tcnt.set(msec);

     unsigned n=0;

     while( !tcnt.tick() ) n++;

     if( n!=(msec*1550-1)/1000 )
       Printf(Con,"#; #; #;\n",n,msec,(msec*1550-1)/1000);
    }
 }

} // namespace Private_5016

using namespace Private_5016;

/* Testit<5016> */

template<>
const char *const Testit<5016>::Name="Test5016 TickCount";

template<>
bool Testit<5016>::Main()
 {
  test1();
  test2();

  return true;
 }

} // namespace App

