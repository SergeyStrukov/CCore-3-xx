/* test2021.GCD.cpp */
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

#include <CCore/inc/algon/CommonIntAlgo.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_2021 {

/* class RandomGen */

class RandomGen : NoCopy
 {
   Random random;

  public:

   RandomGen() {}

   operator unsigned()
    {
     const unsigned Bits = Meta::UIntBits<unsigned>/2-1 ;
     const unsigned Mask = (1u<<Bits)-1 ;

     return random.next_uint<unsigned>()&Mask;
    }
 };

/* functions */

unsigned GCD(unsigned a,unsigned b) { return Algon::GCD(a,b); }

void test1(unsigned a,unsigned b)
 {
  Printf(Con,"a = #; b = #; GCD = #;\n",a,b,GCD(a,b));
 }

void test2(unsigned a,unsigned b,unsigned d)
 {
  if( GCD(a,b)!=GCD(b,a) ) Printf(Exception,"1");

  if( GCD(a*d,b*d)!=GCD(a,b)*d ) Printf(Exception,"2");

  if( GCD(a,b)!=GCD(a+b*d,b) ) Printf(Exception,"3");
 }

} // namespace Private_2021

using namespace Private_2021;

/* Testit<2021> */

template<>
const char *const Testit<2021>::Name="Test2021 GCD";

template<>
bool Testit<2021>::Main()
 {
  {
   test1(2,4);
   test1(16,32);
   test1(3,5);
  }

  {
   const ulen Rep = 1'000'000 ;

   RandomGen gen;

   for(ulen count=Rep; count ;count--)
     {
      unsigned a=gen;
      unsigned b=gen;
      unsigned d=gen;

      test2(a,b,d);
     }
  }

  return true;
 }

} // namespace App

