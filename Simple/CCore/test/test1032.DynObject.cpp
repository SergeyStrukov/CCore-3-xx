/* test1032.DynObject.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/DynObject.h>
#include <CCore/inc/Array.h>

namespace App {

/* Testit<1032> */

template<>
const char *const Testit<1032>::Name="Test1032 DynObject";

template<>
bool Testit<1032>::Main()
 {
  DynObject<int> a;
  DynObject<int> b(Null);
  DynObject<int> c(12345);

  DynObject<int> d( std::move(c) );

  Printf(Con,"#; #;\n",*b,*d);

  b=std::move(d);

  Printf(Con,"#;\n",*b);

  b.create(Null);

  Printf(Con,"#;\n",*b);

  b.create(6789);

  Printf(Con,"#;\n",*b);

  b.destroy();

  DynArray<DynObject<int> > temp(100);

  temp.extend_default(100);

  return true;
 }

} // namespace App

