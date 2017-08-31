/* test6001.Quick.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/base/Quick.h>
#include <CCore/inc/math/UIntSlowMulAlgo.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_6001 {

template <class UInt>
class Engine : NoCopy
 {
   Random random;

   using Algo1 = Quick::UIntMulFunc<UInt> ;
   using Algo2 = Math::UIntSlowMulFunc<UInt> ;

  private:

   UInt next() { return random.next_uint<UInt>(); }

  public:

   Engine() {}

   void test1()
    {
     UInt a=next();
     UInt b=next();

     typename Algo1::Mul mul1(a,b);
     typename Algo2::Mul mul2(a,b);

     if( mul1.hi!=mul2.hi || mul1.lo!=mul2.lo )
       {
        Printf(Exception,"test1 failed");
       }
    }

   void test2()
    {
     UInt hi=next();
     UInt lo=next();
     UInt den=next();

     if( hi>=den ) return;

     if( Algo1::Div(hi,lo,den) != Algo2::Div(hi,lo,den) )
       {
        Printf(Exception,"test2 failed");
       }
    }

   void test3()
    {
     UInt hi=next();
     UInt lo=next();
     UInt den=next();

     if( hi>=den ) return;

     if( Algo1::Mod(hi,lo,den) != Algo2::Mod(hi,lo,den) )
       {
        Printf(Exception,"test3 failed");
       }
    }

   void test4()
    {
     UInt a=next();
     UInt b=next();
     UInt den=next();

     typename Algo1::Mul mul(a,b);

     if( mul.hi>=den ) return;

     if( Algo1::MulDiv(a,b,den) != Algo2::MulDiv(a,b,den) )
       {
        Printf(Exception,"test4 failed");
       }
    }

   void test5()
    {
     UInt hi=next();
     UInt lo=next();
     UInt den=next();

     if( hi>=den ) return;

     typename Algo1::DivMod divmod1(hi,lo,den);
     typename Algo2::DivMod divmod2(hi,lo,den);

     if( divmod1.div!=divmod2.div || divmod1.mod!=divmod2.mod )
       {
        Printf(Exception,"test5 failed");
       }
    }

   void test6()
    {
     UInt a=next();
     UInt b=next();
     UInt mod=next();

     if( !mod ) return;

     a%=mod;
     b%=mod;

     if( Algo1::ModMul(a,b,mod) != Algo2::ModMul(a,b,mod) )
       {
        Printf(Exception,"test6 failed");
       }
    }

   void test7()
    {
     UInt s=next();
     UInt a=next();
     UInt b=next();
     UInt mod=next();

     if( !mod ) return;

     s%=mod;
     a%=mod;
     b%=mod;

     if( Algo1::ModMac(s,a,b,mod) != Algo2::ModMac(s,a,b,mod) )
       {
        Printf(Exception,"test7 failed");
       }
    }

   void step()
    {
     test1();
     test2();
     test3();
     test4();
     test5();
     test6();
     test7();
    }

   void run(ulen count=10'000'000)
    {
     for(; count ;count--)
       {
        if( (count%1'000'000)==0 ) Printf(Con,"#;\n",count);

        step();
       }
    }
 };

} // namespace Private_6001

using namespace Private_6001;

/* Testit<6001> */

template<>
const char *const Testit<6001>::Name="Test6001 Quick";

template<>
bool Testit<6001>::Main()
 {
  Engine<uint32> engine;

  engine.run();

  return true;
 }

} // namespace App

