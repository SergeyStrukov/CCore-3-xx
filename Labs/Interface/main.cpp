/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/Interface
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include "ProxyModel.h"

#include <CCore/inc/Array.h>
#include <CCore/inc/PrintSet.h>

namespace App {

/* using */

using namespace CCore;

/* class ModelTest<T> */

template <class T>
class ModelTest : T
 {
  public:

   using T::T;

   int & ref0() { return T::template method<1>(); }

   int add1(int a) { return T::template method<2>(a); }

   int add2(int a,int b) const { return T::template method<3>(a,b); }

   int add3(int a,int b,int c) const { return T::template method<4>(a,b,c); }

   DynArray<int> list() const { return RetMove(T::template method<5>()); }

   template <template <class ...> class Ret,class S>
   static auto Fold()
    {
     return Ret(
                &S::ref0,
                &S::add1,
                &S::add2,
                &S::add3,
                &S::list
               );
    }
 };

/* struct Test */

struct Ins1
 {
  int ins = 0 ;
 };

struct Ins2
 {
  int ins = 0 ;
 };

struct Test : Ins1 , Funchor , Ins2
 {
  int base = 100 ;

  int & ref0() { return base; }

  int add1(int a) { return a+base; }

  int add2(int a,int b) const { return a+b+base; }

  int add3(int a,int b,int c) const { return a+b+c+base; }

  DynArray<int> list() const { return DynArray<int>{1,2,3,4,5}; }
 };

/* class ModelCTest<T> */

template <class T>
class ModelCTest : T
 {
  public:

   using T::T;

   int add1(int a) const { return T::template method<1>(a); }

   int add2(int a,int b) const { return T::template method<2>(a,b); }

   int add3(int a,int b,int c) const { return T::template method<3>(a,b,c); }

   template <template <class ...> class Ret,class S>
   static auto Fold()
    {
     return Ret(
                &S::add1,
                &S::add2,
                &S::add3
               );
    }
 };

/* struct CTest */

struct CTest : Funchor
 {
  int base = 100 ;

  int add1(int a) const { return a+base; }

  int add2(int a,int b) const { return a+b+base; }

  int add3(int a,int b,int c) const { return a+b+c+base; }
 };

/* Main1() */

void Main1()
 {
  Test test;

  ProxyModel<ModelTest> proxy(test);

  proxy.ref0()=1000;

  Printf(Con,"#;\n", proxy.add1(1) );
  Printf(Con,"#;\n", proxy.add2(1,10) );
  Printf(Con,"#;\n", proxy.add3(1,10,100) );

  Printf(Con,"#;\n", PrintSet(Range(proxy.list())) );
 }

/* Main2() */

void Main2()
 {
  const CTest test;

  ConstProxyModel<ModelCTest> proxy(test);

  Printf(Con,"#;\n", proxy.add1(1) );
  Printf(Con,"#;\n", proxy.add2(1,10) );
  Printf(Con,"#;\n", proxy.add3(1,10,100) );
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  try
    {
     ReportException report;

     Main2();

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

