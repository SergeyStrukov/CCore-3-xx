/* test.h */
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

#ifndef CCore_test_test_h
#define CCore_test_test_h

#include <CCore/test/testPrint.h>

#include <CCore/inc/Exception.h>

namespace App {

/* classes */

template <int XXXX> class Testit;

 //
 // 1001 - 1999  Simple
 // 2001 - 2999  Fundamental
 // 3001 - 3999  Applied
 // 4001 - 4999  HCore
 // 5001 - 5999  XCore
 // 6001 - 6499  Target
 // 6500 - 6999  Target extra
 // 7000 - 7999  Desktop
 //

class ShowInitExit;

template <UIntType UInt,UIntType SumUInt=uint64> class TimeStat;

/* class Testit<int XXXX> */

template <int XXXX>
class Testit
 {
   static const char *const Name;

   static bool Main();

  private:

   bool result;

  public:

   Testit()
    : result(false)
    {
     Printf(Con,"#;\n\n",Title(Name));
    }

   ~Testit()
    {
     Printf(Con,"\n#;\n\n",Title(result?"passed":"failed"));
    }

   void run()
    {
     ReportException report;

     try
       {
        result=Main();

        report.guard();
       }
     catch(CatchType)
       {
        result=false;
       }
    }
 };

/* class ShowInitExit */

class ShowInitExit : NoCopy
 {
   const char *text;

  public:

   explicit ShowInitExit(const char *text_) : text(text_) { Printf(Con,"Init(#;)\n",text); }

   ~ShowInitExit() { Printf(Con,"Exit(#;)\n",text); }
 };

/* class TimeStat<UInt,SumUInt> */

template <UIntType UInt,UIntType SumUInt>
class TimeStat
 {
   UInt minval;
   UInt maxval;
   SumUInt sumval;
   ulen count;

  public:

   TimeStat() { reset(); }

   // methods

   void reset()
    {
     minval=MaxUInt<UInt>;
     maxval=0;
     sumval=0;
     count=0;
    }

   void add(UInt value)
    {
     Replace_min(minval,value);
     Replace_max(maxval,value);
     sumval+=value;
     count++;
    }

   template <class T>
   void div(T den)
    {
     minval/=den;
     maxval/=den;
     sumval/=den;
    }

   UInt getMin() const { return minval; }

   // print object

   using PrintOptType = IntPrintOpt ;

   template <class P>
   void print(P &out,PrintOptType opt) const
    {
     SumUInt average;

     if( count )
       average=sumval/count;
     else
       average=0;

     Printf(out,"count = #; minval = #; maxval = #; average = #;",count,BindOpt(opt,minval),
                                                                        BindOpt(opt,maxval),
                                                                        BindOpt(opt,average));
    }
 };

} // namespace App

#endif

