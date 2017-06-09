/* test2035.RefArray.cpp */
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
#include <CCore/test/testArray.h>

namespace App {

/* Testit<2035> */

template<>
const char *const Testit<2035>::Name="Test2035 RefArray";

template<>
bool Testit<2035>::Main()
 {
  ReportException report;

  const int buf[]={1,2,3,4,5};

  RefArray<int> a;

  Show(a);

  a.extend_default(2);

  Show(a);

  a.extend_fill(5,23);

  Show(a);

  a.extend_copy(5,buf);

  Show(a);

  RefArray<int> b(DoCopy(6,50),a.getPtr_const());

  Show(b);

  b.append_fill(13);

  Show(b);

  b.shrink_extra();

  Show(b);

  Printf(Con,"delta = #;\n",b.shrink_one());

  Show(b);

  Printf(Con,"delta = #;\n",b.shrink(3));

  Show(b);

  Printf(Con,"delta = #;\n",b.shrink_all());

  Show(b);

  b.shrink_reserve();
  b.shrink_reserve(10);
  b.shrink_extra();

  Show(b);

  RefArray<int> c{'0','1','2'};

  Show(c);

  {
   c.apply_modify( [] (int &obj) { obj+=100; } );

   Show(c);
  }

  {
   int k=0;

   c.apply_modify( [&k] (int &obj) { obj+=k++; } );

   Show(c);
  }

  {
   int k=0;

   c.applyReverse_modify( [&k] (int &obj) { obj+=k++; } );

   Show(c);
  }

  try
    {
     RefArray<X> a;

     a.extend_default(5);
    }
  catch(CatchType) {}

  try
    {
     RefArray<X> a(10);
    }
  catch(CatchType) {}

  return true;
 }

} // namespace App

