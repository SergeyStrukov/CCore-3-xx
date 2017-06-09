/* test6007.FPU.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>

namespace App {

namespace Private_6007 {

class Data : NoCopy
 {
   const ulen Len = 1000000 ;

   DynArray<double> buf;

  private:

   static double Func(const double *a,ulen len)
    {
     double ret=0;

     for(double val : Range(a,len) ) ret+=val*val;

     return ret;
    }

   static double Func(double a,double b)
    {
     if( a<b ) return a/b; else return b/a;
    }

  public:

   Data()
    : buf(Len)
    {
     double x=1;

     for(double &val : buf )
       {
        val=x;

        x+=1;
       }
    }

   ~Data() {}

   double operator () () const
    {
     Printf(Con,"start\n");

     MSecTimer timer;

     // 1

     DynArray<double> temp1(Len/10);

     for(ulen i=0,len=temp1.getLen(); i<len ;i++) temp1[i]=Func(buf.getPtr()+10*i,10);

     // 2

     DynArray<double> temp2(Len/20);

     for(ulen i=0,len=temp2.getLen(); i<len ;i++) temp2[i]=Func(temp1[2*i],temp1[2*i+1]);

     // 3

     double ret=0;

     for(double val : temp2 ) ret+=val;

     Printf(Con,"stop #; msec\n",timer.get());

     return ret;
    }
 };

} // namespace Private_6007

using namespace Private_6007;

/* Testit<6007> */

template<>
const char *const Testit<6007>::Name="Test6007 FPU";

template<>
bool Testit<6007>::Main()
 {
  const ulen Len = 10 ;

  Data data;
  double buf[Len];

  {
   RunTask run_task;

   for(ulen index=0; index<Len ;index++) run_task( [&buf,&data,index] () { buf[index]=data(); } );
  }

  for(ulen index=1; index<Len ;index++)
    if( buf[index]!=buf[0] )
      {
       Printf(Con,"Failed\n");

       return false;
      }

  return true;
 }

} // namespace App

