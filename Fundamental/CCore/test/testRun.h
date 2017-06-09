/* testRun.h */
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

#ifndef CCore_test_testRun_h
#define CCore_test_testRun_h

#include <CCore/inc/Task.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

class RunTask;

/* class RunTask */

class RunTask : NoCopy
 {
   AntiSem asem;
   Function<void (void)> stop_func;

  public:

   explicit RunTask(Function<void (void)> stop_func_=Nothing)
    : asem("RunTask"),
      stop_func(stop_func_)
    {
    }

   ~RunTask()
    {
     stop_func();

     asem.wait();
    }

   template <class FuncInit,class ... TT>
   void operator () (FuncInit func_init,TT ... tt)
    {
     asem.inc();

     RunFuncTask(func_init,asem.function_dec(),tt...);
    }

   template <class FuncInit,class ... TT>
   void operator () (ulen count,FuncInit func_init,TT ... tt)
    {
     for(ulen cnt=count; cnt ;cnt--) (*this)(func_init,tt...);
    }
 };

} // namespace App

#endif

