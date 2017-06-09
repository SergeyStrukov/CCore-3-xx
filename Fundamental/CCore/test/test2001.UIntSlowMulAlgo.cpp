/* test2001.UIntSlowMulAlgo.cpp */
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

#include <CCore/inc/math/UIntSlowMulAlgo.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_2001 {

class Engine : NoCopy
 {
   Random random;

   using UInt = uint16 ;
   using EUInt = uint32 ;

   using Algo = Math::UIntSlowMulAlgo<UInt> ;

  private:

   static EUInt Combine(UInt hi,UInt lo) { return (EUInt(hi)<<16)|lo; }

  public:

   Engine() {}

   void test1()
    {
     UInt a=random.next_uint<UInt>();
     UInt b=random.next_uint<UInt>();

     Algo::DoubleUMul mul(a,b);

     if( Combine(mul.hi,mul.lo) != EUInt(a)*b )
       {
        Printf(Exception,"test1 failed");
       }
    }

   void test2()
    {
     UInt hi=random.next_uint<UInt>();
     UInt lo=random.next_uint<UInt>();
     UInt den=random.next_uint<UInt>();

     if( hi>=den ) return;

     if( Algo::DoubleUDiv(hi,lo,den) != Combine(hi,lo)/den )
       {
        Printf(Exception,"test2 failed");
       }
    }

   void step()
    {
     test1();
     test2();
    }

   void run(ulen count=1'000'000'000)
    {
     for(; count ;count--)
       {
        if( (count%1'000'000)==0 ) Printf(Con,"#;\n",count);

        step();
       }
    }
 };

} // namespace Private_2001

using namespace Private_2001;

/* Testit<2001> */

template<>
const char *const Testit<2001>::Name="Test2001 UIntSlowMulAlgo";

template<>
bool Testit<2001>::Main()
 {
  Engine engine;

  engine.run();

  return true;
 }

} // namespace App

