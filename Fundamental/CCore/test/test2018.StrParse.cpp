/* test2018.StrParse.cpp */
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

#include <CCore/test/test.h>

#include <CCore/inc/Random.h>

namespace App {

namespace Private_2018 {

/* class Engine */

class Engine : NoCopy
 {
   Random random;

  private:

   void fail(unsigned num)
    {
     Printf(Exception,"fail #;",num);
    }

  public:

   Engine() {}

   ~Engine() {}

   void test1()
    {
     const uint16 minval=5000u;
     const uint16 maxval=20000u;

     uint16 val=random.next16();
     char buf[32];
     PrintBuf out(Range(buf));

     Putobj(out,val);

     StrLen str=out.close();

     //Printf(Con,"str = #;\n",str);

     StrParse dev(str);

     uint16 ret;

     ParseUInt(dev,ret,minval,maxval);

     if( val>=minval && val<=maxval )
       {
        if( !dev ) fail(1);

        if( ret!=val ) fail(2);
       }
     else
       {
        if( !!dev ) fail(3);
       }
    }

   void test2()
    {
     const uint16 minval=5000u;
     const uint16 maxval=20000u;

     uint16 val=random.next16();
     char buf[32];
     PrintBuf out(Range(buf));

     Putobj(out,val);

     StrLen str=out.close();

     //Printf(Con,"str = #;\n",str);

     StrParse dev(str);

     uint16 ret;

     ParseUInt_empty(dev,ret,0u,minval,maxval);

     if( val>=minval && val<=maxval )
       {
        if( !dev ) fail(4);

        if( ret!=val ) fail(5);
       }
     else
       {
        if( !!dev ) fail(6);
       }
    }
 };

} // namespace Private_2018

using namespace Private_2018;

/* Testit<2018> */

template<>
const char *const Testit<2018>::Name="Test2018 StrParse";

template<>
bool Testit<2018>::Main()
 {
  const ulen Rep =100'000 ;

  Engine engine;

  for(ulen count=Rep; count ;count--) engine.test1();

  for(ulen count=Rep; count ;count--) engine.test2();

  return true;
 }

} // namespace App

