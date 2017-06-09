/* test2055.ArrayInsDel.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/PrintSet.h>

namespace App {

namespace Private_2055 {


} // namespace Private_2055

using namespace Private_2055;

/* Testit<2055> */

template<>
const char *const Testit<2055>::Name="Test2055 ArrayInsDel";

template<>
bool Testit<2055>::Main()
 {
  DynArray<int> a;

  ArraySwapIns(a,0,1);
  ArraySwapIns(a,1,2);
  ArraySwapIns(a,2,3);
  ArraySwapIns(a,3,4);
  ArraySwapIns_guarded(a,4,5);

  ArrayCopyIns(a,0,100);
  ArrayCopyIns(a,1,101);
  ArrayCopyIns(a,2,102);
  ArrayCopyIns_guarded(a,3,103);

  Printf(Con,"#;\n",PrintSet(Range(a)));

  ArrayCopyDel(a,0);
  ArrayCopyDel_guarded(a,1);

  Printf(Con,"#;\n",PrintSet(Range(a)));

  ArraySwapDel(a,2);
  ArraySwapDel_guarded(a,3);

  Printf(Con,"#;\n",PrintSet(Range(a)));

  return true;
 }

} // namespace App

