/* test3014.AES-speed.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/crypton/AES.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Timer.h>

namespace App {

namespace Private_3014 {

/* class Test */

class Test : NoCopy
 {
   static const ulen BufLen = 100'000 ;

   Random random;
   DynArray<uint8> buf;

  public:

   Test() : buf(BufLen) {}

   ~Test() {}

   template <class C>
   static void Apply(C &cipher,PtrLen<uint8> r)
    {
     for(; r.len>=C::BlockLen ;r+=C::BlockLen) cipher.apply(r.ptr);
    }

   static uint8 Sum(PtrLen<const uint8> r)
    {
     uint8 ret=0;

     for(; +r ;++r) ret+=*r;

     return ret;
    }

   template <class C>
   void test(ulen rep)
    {
     uint8 key[C::KeyLen];

     random.fill(Range(key));

     C cipher(key);
     uint8 sum=0;

     SecTimer timer;

     for(ulen count=rep; count ;count--)
       {
        auto r=Range(buf);

        random.fill(r);
        Apply(cipher,r);
        sum+=Sum(Range_const(r));
       }

     auto t=timer.get();

     if( !t ) t=1;

     uint64 s=buf.getLen()*(uint64)rep;

     Printf(Con,"#; len = #; byte time = #; sec speed = #; Mbips\n",C::GetName(),s,t,((s*8)/t)/1'000'000,sum);
    }
 };

} // namespace Private_3014

using namespace Private_3014;

/* Testit<3014> */

template<>
const char *const Testit<3014>::Name="Test3014 AES speed";

template<>
bool Testit<3014>::Main()
 {
  const ulen Rep = 10'000 ;

  Test test;

  test.test<Crypton::AES128>(Rep);
  test.test<Crypton::AES192>(Rep);
  test.test<Crypton::AES256>(Rep);

  test.test<Crypton::AESInverse128>(Rep);
  test.test<Crypton::AESInverse192>(Rep);
  test.test<Crypton::AESInverse256>(Rep);

  return true;
 }

} // namespace App

