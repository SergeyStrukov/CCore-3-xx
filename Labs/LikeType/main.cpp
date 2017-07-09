/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/LikeType
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

namespace App {

/* using */

using namespace CCore;

/* struct GetSig<T> */

template <class T> struct GetSig;

template <class S,class T>
struct GetSig<S T::*>
 {
  using Ret = S ;
 };

/* struct SigList<TT> */

template <class ... TT>
struct SigList
 {
  SigList(TT ...) {}

  using Ret = Meta::TypeListBox< typename GetSig<TT>::Ret ... > ;
 };

/* struct Model */

template <class T>
concept bool ModelFoldType = requires()
 {
  &T::add1;
  &T::add2;
  &T::add3;
 } ;

struct Model
 {
  int add1(int a) { Used(a); throw 0; }

  int add2(int a,int b) { Used(a); Used(b); throw 0; }

  int add3(int a,int b,int c) { Used(a); Used(b); Used(c); throw 0; }

  template <template <class ...> class Ret,ModelFoldType T>
  static auto Fold()
   {
    return Ret(
               &T::add1,
               &T::add2,
               &T::add3
              );
   }
 };

/* struct Test */

struct Test
 {
  int add1(int a) { return a; }

  int add2(int a,int b) { return a+b; }

  int add3(int a,int b,int c) { return a+b+c; }
 };

/* concept LikeType<T,Model> */

template <class T,class Model>
concept bool LikeType = IsType< typename decltype(Model::template Fold<SigList,Model>())::Ret ,
                                typename decltype(Model::template Fold<SigList,T>())::Ret > ;

/* Main() */

void Main()
 {
  Printf(Con,"#;\n",LikeType<Test,Model>);
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  try
    {
     ReportException report;

     Main();

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

