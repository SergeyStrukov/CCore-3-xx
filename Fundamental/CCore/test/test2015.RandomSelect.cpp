/* test2015.RandomSelect.cpp */
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

#include <CCore/inc/Random.h>

namespace App {

namespace Private_2015 {

uint32 BitReverse(uint32 a)
 {
  uint32 ret=0;

  for(uint32 bit=UIntBit<uint32>(31); a ;a>>=1,bit>>=1)
    {
     if( a&1 ) ret|=bit;
    }

  return ret;
 }

} // namespace Private_2015

using namespace Private_2015;

/* Testit<2015> */

template<>
const char *const Testit<2015>::Name="Test2015 RandomSelect";

template<>
bool Testit<2015>::Main()
 {
  Random random;

  for(ulen count=100; count ;count--)
    {
     Printf(Con,"#;\n",random.select_uint<uint64>(1,1000));
    }

  for(ulen count=10'000'000; count ;count--)
    {
     uint8 a=random.next8();
     uint32 b=random.next32();
     uint8 lim=random.next8();

     if( !lim ) continue;

     uint8 res1=RandomSelect<uint8>::Do(a,b,lim);
     uint8 res2=uint8( ((uint64(a)<<32)|BitReverse(b))%lim );

     if( res1!=res2 )
       {
        Printf(Exception,"Fault a = #; b = #; lim = #;",a,b,lim);
       }
    }

  return true;
 }

} // namespace App

