/* test1026.PtrStepLen.cpp */
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

namespace App {

namespace Private_1026 {

template <class R>
void Show(R r)
 {
  for(; +r ;++r) Printf(Con,"#; ",*r);

  Putch(Con,'\n');
 }

void test1(PtrStepLen<int> r)
 {
  Show(r);
 }

void test2(PtrStepLen<int> r)
 {
  for(int obj : r ) Printf(Con,"#; ",obj);

  Putch(Con,'\n');
 }

void test3(PtrStepLen<int> r)
 {
  Show(r.prefix(3));
  Show(r.suffix(3));
  Show(r.prefix(r.suffix(3)));
  Show(r.part(1,2));
  Show(r.part(1));
  Show(r.inner(1,1));
 }

void test4(PtrStepLen<int> r)
 {
  for(ulen i=0; i<r.len ;i++) Printf(Con,"#; ",r[i]);

  Putch(Con,'\n');

  for(ulen i=1; i<=r.len ;i++) Printf(Con,"#; ",r.back(i));

  Putch(Con,'\n');
 }

void test5(PtrStepLen<int> r)
 {
  Show(r+=3);
  Show(r);
 }

} // namespace Private_1026

using namespace Private_1026;

/* Testit<1026> */

template<>
const char *const Testit<1026>::Name="Test1026 PtrStepLen";

template<>
bool Testit<1026>::Main()
 {
  int buf[]={1,0,2,0,3,0,4,0,5};

  PtrStepLen<int> r(buf,2,5);

  test1(r);
  test2(r);
  test3(r);
  test4(r);
  test5(r);

  return true;
 }

} // namespace App

