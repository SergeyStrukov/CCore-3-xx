/* test2040.ElementPool.cpp */
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

#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_2040 {

/* functions */

void test1(ulen rep,ulen maxlen)
 {
  Random random;
  ElementPool pool(2_KByte);

  SecTimer timer;

  for(ulen count=rep; count ;count--)
    {
     ulen len=random.select(1,maxlen);

     pool.createArray<int>(len);
    }

  Printf(Con,"#; sec\n",timer.get());
 }

void test2(ulen rep)
 {
  Random random;
  ElementPool pool(2_KByte);

  SecTimer timer;

  for(ulen count=rep; count ;count--)
    {
     pool.create<int>(0);
    }

  Printf(Con,"#; sec\n",timer.get());
 }

void test3()
 {
  ElementPool pool;

  auto str1=pool.cat("prefix","12345","suffix");
  pool.shrink_extra();
  auto str2=pool.cat("prefix","12345","suffix");
  pool.shrink_extra();

  Printf(Con,"#;\n#;\n",str1,str2);
 }

} // namespace Private_2040

using namespace Private_2040;

/* Testit<2040> */

template<>
const char *const Testit<2040>::Name="Test2040 ElementPool";

template<>
bool Testit<2040>::Main()
 {
  test1(100'000,1000);
  test1(1'000'000,100);

  test2(1'000'000);
  test2(10'000'000);
  test2(100'000'000);

  test3();

  return true;
 }

} // namespace App

