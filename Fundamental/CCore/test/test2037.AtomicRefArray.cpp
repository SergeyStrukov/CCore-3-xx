/* test2037.AtomicRefArray.cpp */
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
#include <CCore/test/testArray.h>

namespace App {

namespace Private_2037 {

/* struct Test */

struct Test
 {
  int val;

  explicit Test(int val_)
   : val(val_)
   {
    Printf(Con,"Test(#;)\n",val);
   }

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"#;",val);
   }
 };

/* testStatic() */

void testStatic()
 {
  using Array = AtomicRefArray<Test> ;

  static Meta::AlignedStorage<Array::StaticMemLen<5> > mem;

  Array a(&mem,5,{1,2,3,4,5});

  Show(a);
 }

} // namespace Private_2037

using namespace Private_2037;

/* Testit<2037> */

template<>
const char *const Testit<2037>::Name="Test2037 AtomicRefArray";

template<>
bool Testit<2037>::Main()
 {
  testStatic();

  const int buf[]={1,2,3,4,5};

  AtomicRefArray<int> a;
  AtomicRefArray<int> b(a);

  Show(a);

  a.extend_default(2);

  Show(a);

  a.extend_fill(5,23);

  Show(a);

  a.extend_copy(5,buf);

  Show(a);

  Show(b);

  b=a;

  a.extend_default(5);

  Show(a);
  Show(b);

  b=a;

  a.shrink(12);

  Show(a);
  Show(b);

  b=a;

  a.modify().set(13);

  Show(a);
  Show(b);

  return true;
 }

} // namespace App

