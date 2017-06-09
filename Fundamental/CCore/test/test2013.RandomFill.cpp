/* test2013.RandomFill.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#include <CCore/inc/Random.h>

namespace App {

namespace Private_2013 {

/* class Gen */

class Gen
 {
   unsigned count;

  public:

   Gen() { count=0; }

   unsigned getCount() const { return count; }

   using UnitType = uint8 ;

   UnitType next() { count++; return 0xFF; }

   uint8 next8() { return 0; }

   uint16 next16() { return 0; }

   uint32 next32() { return 0; }

   uint64 next64() { return 0; }
 };

/* functions */

template <class UInt>
unsigned Fill(UInt &ret)
 {
  Gen gen;

  ret=RandomFill_gen<UInt>::Do(gen);

  return gen.getCount();
 }

template <class UInt>
void test()
 {
  UInt a;
  unsigned count=Fill(a);

  Printf(Con,"a = #.h; count = #;\n",a,count);
 }

} // namespace Private_2013

using namespace Private_2013;

/* Testit<2013> */

template<>
const char *const Testit<2013>::Name="Test2013 RandomFill";

template<>
bool Testit<2013>::Main()
 {
  test<uint8>();
  test<uint16>();
  test<uint32>();
  test<uint64>();

  return true;
 }

} // namespace App

