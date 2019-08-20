/* test2033.DynArray.cpp */
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

namespace Private_2033 {

/* test1() */

template <class FuncInit>
auto trans(const int *src,FuncInit func_init)
 {
  return Creator_transform<int,const int,FuncInit>(src,func_init);
 }

void test1()
 {
  const int buf[]={1,2,3,4,5};

  auto r=Range(buf);

  DynArray<int> a(DoCreate(r.len),trans(r.ptr, [] (int a) { return 2*a; } ));

  a.extend_transform(Range(buf), [] (int a) { return 3*a; } );

  a.extend_transform_nothrow(Range(buf), [] (int a) { return 5*a; } );

  Show(a);
 }

} // namespace Private_2033

using namespace Private_2033;

/* Testit<2033> */

template<>
const char *const Testit<2033>::Name="Test2033 DynArray";

template<>
bool Testit<2033>::Main()
 {
  ReportException report;

  test1();

  return true;

  const int buf[]={1,2,3,4,5};

  DynArray<int> a;

  Printf(Con,"#; #;\n",a.isEmpty(),a.notEmpty());

  Show(a);

  Printf(Con,"#;\n",PrintSet(a.extend_default(2)));

  Printf(Con,"#; #;\n",a.isEmpty(),a.notEmpty());

  Show(a);

  a.extend_fill(5,23);

  Show(a);

  Printf(Con,"#;\n",PrintSet(a.extend_copy(5,buf)));

  Show(a);
  ShowReverse(a);

  DynArray<int> b(DoCopy(6,50),a.getPtr_const());

  Show(b);

  b.append_fill(13);

  Show(b);

  b.shrink_reserve();

  Show(b);

  b.shrink_reserve(10);

  Show(b);

  b.shrink_extra();

  Show(b);

  Printf(Con,"delta = #;\n",b.shrink_one());

  Show(b);

  Printf(Con,"delta = #;\n",b.shrink(3));

  Show(b);

  Printf(Con,"delta = #;\n",b.shrink_all());

  Show(b);

  b.shrink_extra();

  Show(b);

  DynArray<int> c{'0','1','2'};

  Show(c);

  {
   c.apply( [] (int &obj) { obj+=100; } );

   Show(c);
  }

  {
   int k=0;

   c.apply( [&k] (int &obj) { obj+=k++; } );

   Show(c);
  }

  {
   int k=0;

   c.applyReverse( [&k] (int &obj) { obj+=k++; } );

   Show(c);
  }

  DynArray<int> x(std::move(c));

  Show(c);
  Show(x);

  c=std::move(x);

  Show(c);
  Show(x);

  try
    {
     DynArray<X> a;

     a.extend_default(5);
    }
  catch(CatchType) {}

  try
    {
     DynArray<X> a(10);
    }
  catch(CatchType) {}

  DynArray<DynArray<int> > d{3,3,3};

  ulen dn[10];

  Range(dn).set(100);

  d.extend_cast(10,dn);

  for(auto r=Range(d); +r ;++r) Printf(Con,"#;\n",r->getLen());

  DynArray<RefArray<int> > e{3,3,3};

  ulen en[10];

  Range(en).set(100);

  e.extend_cast(10,en);

  for(auto r=Range(e); +r ;++r) Printf(Con,"#;\n",r->getLen());

  return true;
 }

} // namespace App

