/* test1037.MemberFold.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/MemberFold.h>

namespace App {

namespace Private_1037 {

/* struct Test1 */

struct Test1
 {
  int a;
  int b[10];
  double c;

  template <template <class ...> class Ret,class T>
  static constexpr auto Fold()
   {
    return Ret(&T::a,&T::b,&T::c);
   }
 };

void SetNull(int &a) { a=0; }

void SetNull(double &a) { a=0; }

void SetNull(int (&a)[10]) { a[0]=0; }

struct SumSizeof
 {
  template <class ... TT>
  constexpr ulen operator () ()
   {
    return ( ... + sizeof (TT) );
   }
 };

} // namespace Private_1037

using namespace Private_1037;

/* Testit<1037> */

template<>
const char *const Testit<1037>::Name="Test1037 MemberFold";

template<>
bool Testit<1037>::Main()
 {
  constexpr auto members=Members<Test1>;

  Test1 obj1{};

  members(&obj1, [] (auto & ... x) { ( ... , SetNull(x) ); } );

  ulen len1=members(&obj1, [] (auto & ... x) { return ( ... + sizeof x ); } );

  Printf(Con,"sum sizeof = #;\n",len1);

  constexpr ulen len2=Members<Test1>(SumSizeof());

  Printf(Con,"sum sizeof = #;\n",len2);

  return true;
 }

} // namespace App

