/* test1034.PrintStem.cpp */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/PrintStem.h>

namespace App {

namespace Private_1034 {

class PrintPeriod : NoCopy
 {
   mutable bool flag = true ;
   mutable unsigned count = 0 ;

   unsigned period; // > 0
   StrLen first;
   StrLen next;
   StrLen line;

  public:

   PrintPeriod(unsigned period_,StrLen first_,StrLen next_,StrLen line_) : period(period_),first(first_),next(next_),line(line_) {}

   void reset() { flag=true; }

   StrLen end(StrLen non_empty,StrLen empty) const { return flag?empty:non_empty; }

   // print object

   template <class P>
   void print(P &out) const
    {
     if( flag )
       {
        flag=false;
        count=1;

        Putobj(out,first);
       }
     else
       {
        if( count<period )
          {
           count++;

           Putobj(out,next);
          }
        else
          {
           count=1;

           Putobj(out,line);
          }
       }
    }
 };

void test1()
 {
  PrintFirst stem(" "," , ");

  Putobj(Con,"{",stem,1,stem,2,stem,3);

  Putobj(Con,stem.end(" }\n\n","}\n\n"));
 }

void test2(ulen count)
 {
  PrintPeriod stem(10,"\n  "," , "," ,\n  ");

  Putobj(Con," {");

  for(ulen i=0; i<count ;i++) Putobj(Con,stem,i);

  Putobj(Con,stem.end("\n }\n\n","}\n\n"));
 }

} // namespace Private_1034

using namespace Private_1034;

/* Testit<1034> */

template<>
const char *const Testit<1034>::Name="Test1034 PrintStem";

template<>
bool Testit<1034>::Main()
 {
  test1();

  test2(0);
  test2(1);
  test2(5);
  test2(10);
  test2(11);
  test2(15);
  test2(20);
  test2(21);
  test2(25);

  return true;
 }

} // namespace App

