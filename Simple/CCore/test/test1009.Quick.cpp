/* test1009.Quick.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/base/Quick.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_1009 {

/* struct BitCur */

struct BitCur
 {
  Quick::ScanUInt value;
  unsigned bit;

  BitCur()
   {
    value=1;
    bit=0;
   }

  bool operator + () const { return value; }

  void operator ++ ()
   {
    value<<=1;
    bit++;
   }
 };

/* class Engine */

class Engine : NoCopy
 {
   Random random;

  private:

   Quick::ScanUInt get() { return random.next_uint<Quick::ScanUInt>(); }

   template <class UInt>
   void test_swap(UInt val,UInt ret)
    {
     for(unsigned cnt=Meta::UIntBits<UInt>/8,shift=8*(cnt-1); cnt ;cnt--,ret>>=8,val<<=8)
       {
        if( byte(ret)!=byte(val>>shift) )
          {
           Printf(Exception,"test_swap() failed");
          }
       }
    }

  public:

   Engine() {}

   static const ulen Rep = 10'000'000 ;

   void test1();

   void test2(ulen rep=Rep);

   void test3(ulen rep=Rep);

   void test4();

   void test5(ulen rep=Rep);

   void test6(ulen rep=Rep);

   void test7(ulen rep=Rep);
 };

void Engine::test1()
 {
  for(BitCur cur; +cur ;++cur)
    {
     unsigned msbit=Quick::ScanMSBit(cur.value);
     unsigned lsbit=Quick::ScanLSBit(cur.value);

     if( cur.bit!=msbit )
       {
        Printf(Exception,"Failed at value = #.h; msbit = #;",cur.value,msbit);
       }

     if( cur.bit!=lsbit )
       {
        Printf(Exception,"Failed at value = #.h; lsbit = #;",cur.value,lsbit);
       }

     Printf(Con,"ScanBit #; #; #;\n",cur.bit,msbit,lsbit);
    }
 }

void Engine::test2(ulen rep)
 {
  for(BitCur cur; +cur ;++cur)
    {
     for(auto count=rep; count ;count--)
       {
        Quick::ScanUInt val=(get()<<1)|1;

        val<<=cur.bit;

        unsigned lsbit=Quick::ScanLSBit(val);

        if( lsbit!=cur.bit )
          {
           Printf(Exception,"Failed at value = #.h; lsbit = #;\n",val,lsbit);
          }
       }
    }
 }

void Engine::test3(ulen rep)
 {
  const unsigned Bits = Meta::UIntBits<Quick::ScanUInt> ;

  for(BitCur cur; +cur ;++cur)
    {
     for(auto count=rep; count ;count--)
       {
        Quick::ScanUInt val=~(get()>>1);

        val>>=(Bits-1-cur.bit);

        unsigned msbit=Quick::ScanMSBit(val);

        if( msbit!=cur.bit )
          {
           Printf(Exception,"Failed at value = #.h; msbit = #;\n",val,msbit);
          }
       }
    }
 }

void Engine::test4()
 {
  {
   uint16 val=random.next16();
   uint16 ret=Quick::ByteSwap16(val);

   Printf(Con,"val = #5.hi; ret = #5.hi;\n",val,ret);
  }
  {
   uint32 val=random.next32();
   uint32 ret=Quick::ByteSwap32(val);

   Printf(Con,"val = #9.hi; ret = #9.hi;\n",val,ret);
  }
  {
   uint64 val=random.next64();
   uint64 ret=Quick::ByteSwap64(val);

   Printf(Con,"val = #17.hi; ret = #17.hi;\n",val,ret);
  }
 }

void Engine::test5(ulen rep)
 {
  for(auto count=rep; count ;count--)
    {
     uint16 val=random.next16();
     uint16 ret=Quick::ByteSwap16(val);

     test_swap(val,ret);
    }
 }

void Engine::test6(ulen rep)
 {
  for(auto count=rep; count ;count--)
    {
     uint32 val=random.next32();
     uint32 ret=Quick::ByteSwap32(val);

     test_swap(val,ret);
    }
 }

void Engine::test7(ulen rep)
 {
  for(auto count=rep; count ;count--)
    {
     uint64 val=random.next64();
     uint64 ret=Quick::ByteSwap64(val);

     test_swap(val,ret);
    }
 }

} // namespace Private_1009

using namespace Private_1009;

/* Testit<1009> */

template<>
const char *const Testit<1009>::Name="Test1009 Quick";

template<>
bool Testit<1009>::Main()
 {
  Engine engine;

  engine.test1();
  engine.test2();
  engine.test3();
  engine.test4();
  engine.test5();
  engine.test6();
  engine.test7();

  return true;
 }

} // namespace App

