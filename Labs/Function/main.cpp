/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/Function
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

#include <CCore/inc/Tuple.h>

namespace App {

/* using */

using namespace CCore;

/* class FunctionClass<> */

template <class T,class R,class ... AA> class BindMethod;

template <class S,class F> class FunctionClass;

template <class R,class Box> struct BindArgs;

template <class T,class R,class ... AA>
class BindMethod
 {
   T &obj;
   R (T::*method)(AA...);

  public:

   BindMethod(T &obj_,R (T::*method_)(AA...)) : obj(obj_),method(method_) {}

   template <class ... SS> requires ( sizeof ... (SS) == sizeof ... (AA) )
   R operator () (SS && ... ss) const { return (obj.*method)( std::forward<SS>(ss)... ); }
 };

template <class R,class F,class ... AA>
class FunctionClass<R(AA...),F>
 {
   F func;

  public:

   explicit FunctionClass(const F &func_) : func(func_) {}

   template <class ... SS> requires ( sizeof ... (SS) == sizeof ... (AA) )
   R operator () (SS && ... ss) const { return func( std::forward<SS>(ss)... ); }

   template <class ... TT>
   auto operator () (const TT & ... tt) const requires( sizeof ... (TT) < sizeof ... (AA) )
    {
     using Box=typename Meta::SplitTypeList<sizeof ... (TT),AA...>::Last;

     return BindArgs<R,Box>::Bind(func, tt... );
    }
 };

template <class S,class F>
auto Function(const F &func) { return FunctionClass<S,F>(func); }

template <class S>
auto Function(S *func) { return FunctionClass<S,S *>(func); }

template <class S,class T>
auto Function(T &obj,S T::* method) { return Function<S>( BindMethod(obj,method) ); }

template <class R,class ... AA>
struct BindArgs<R,Meta::TypeListBox<AA...> >
 {
  template <class F,class ... TT>
  static auto Bind(const F &func,const TT & ... tt)
   {
    return Function<R(AA...)>( [=] (auto && ... ss) { return func( tt... , std::forward<decltype(ss)>(ss)... ); } );
   }
 };

/* Main() */

int Sum(int a,int b,int c) { return a+b+c; }

struct Test
 {
  int base = 100 ;

  int sum(int a,int b,int c) { return base+a+b+c; }
 };

void Main()
 {
  // 1

  {
   auto sum=Function(Sum);

   Printf(Con,"#;\n",sum(1,2,3));

   Printf(Con,"#;\n",sum(1,2)(3));
  }

  // 2

  {
   Test test;

   auto sum=Function(test,&Test::sum);

   Printf(Con,"#;\n",sum(1,2,3));

   Printf(Con,"#;\n",sum(1,2)(3));
  }
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

