/* test1025.PtrLenReverse.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>

namespace App {

namespace Private_1025 {

template <class R>
void Show(R r)
 {
  for(; +r ;++r) Printf(Con,"#; ",*r);

  Putch(Con,'\n');
 }

void test1()
 {
  int buf[]={1,2,3,4,5};

  Show(RangeReverse(buf));
 }

void test2()
 {
  int buf[]={1,2,3,4,5};

  for(int obj : RangeReverse(buf) ) Printf(Con,"#; ",obj);

  Putch(Con,'\n');
 }

void test3()
 {
  DynArray<int> buf{1,2,3,4,5};

  Show(RangeReverse(buf));
 }

void test4()
 {
  DynArray<int> buf{1,2,3,4,5};

  Show(Range(buf));
  Show(RangeReverse(buf));
 }

void test5()
 {
  int buf[]={1,2,3,4,5};

  auto r=RangeReverse(buf);

  Show(r.prefix(3));
  Show(r.suffix(3));
  Show(r.prefix(r.suffix(3)));
  Show(r.part(1,2));
  Show(r.part(1));
  Show(r.inner(1,1));
 }

void test6()
 {
  int buf[]={1,2,3,4,5};

  auto r=RangeReverse(buf);

  for(ulen i=0; i<r.len ;i++) Printf(Con,"#; ",r[i]);

  Putch(Con,'\n');

  for(ulen i=1; i<=r.len ;i++) Printf(Con,"#; ",r.back(i));

  Putch(Con,'\n');
 }

void test7()
 {
  int buf[]={1,2,3,4,5};

  auto r=RangeReverse(buf);

  Show(r+=3);
  Show(r);
 }

} // namespace Private_1025

using namespace Private_1025;

/* Testit<1025> */

template<>
const char *const Testit<1025>::Name="Test1025 PtrLenReverse";

template<>
bool Testit<1025>::Main()
 {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();

  return true;
 }

} // namespace App

