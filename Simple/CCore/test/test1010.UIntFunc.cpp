/* test1010.UIntFunc.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#include <CCore/inc/Random.h>

namespace App {

namespace Private_1010 {

/* consts */

const ulen Rep = 10'000'000 ;

/* functions */

template <class UInt>
void Show(UInt value)
 {
  using Func = UIntFunc<UInt> ;

  Printf(Con,"\nvalue = #.h;\n",value);
  Printf(Con,"Neg(value) = #.h;\n",Func::Neg(value));
  Printf(Con,"IsNegative(value) = #.h;\n",Func::IsNegative(value));
  Printf(Con,"NotNegative(value) = #.h;\n",Func::NotNegative(value));
  Printf(Con,"IsPositive(value) = #.h;\n",Func::IsPositive(value));
  Printf(Con,"NotPositive(value) = #.h;\n",Func::NotPositive(value));
 }

template <class UInt>
void test(const char *name)
 {
  using Func = UIntFunc<UInt> ;

  Printf(Con,"#;\n\n",Title(name));

  Printf(Con,"MSBit = #.h;\n",+Func::MSBit);
  Printf(Con,"MaxPositive = #.h;\n",+Func::MaxPositive);
  Printf(Con,"MinNegative = #.h;\n",+Func::MinNegative);

  Show<UInt>(Func::MinNegative);
  Show<UInt>(Func::MinNegative+Func::MaxPositive/2);
  Show<UInt>(0);
  Show<UInt>(Func::MaxPositive/2);
  Show<UInt>(Func::MaxPositive);

  Printf(Con,"\n#;\n\n",TextDivider());
 }

/* testSqRoot() */

template <class UInt>
void testSqRoot(ulen rep=Rep)
 {
  Random random;

  ulen count1=0;
  ulen count2=0;
  ulen count3=0;

  for(auto count=rep; count ;count--)
    {
     UInt S=random.next_uint<UInt>();

     if( !S ) continue;

     UInt x=UIntFunc<UInt>::SqRoot(S);

     UInt y=S/x;
     UInt z=S%x;

     if( y!=x )
       {
        if( y==x-1 )
          {
           if( z==0 ) Printf(Exception,"fail 1");

           count2++;
          }
        else if( y==x+1 )
          {
           if( z!=0 ) Printf(Exception,"fail 2");

           count3++;
          }
        else
          {
           Printf(Exception,"fail 3");
          }
       }
     else
       {
        count1++;
       }
    }

  for(auto count=rep; count ;count--)
    {
     UInt S=random.next_uint<UInt>();
     UInt t=random.next_uint<UInt>();

     if( !S || !t ) continue;

     UInt x=UIntFunc<UInt>::SqRoot(S,t);

     UInt y=S/x;
     UInt z=S%x;

     if( y!=x )
       {
        if( y==x-1 )
          {
           if( z==0 ) Printf(Exception,"fail 4");

           count2++;
          }
        else if( y==x+1 )
          {
           if( z!=0 ) Printf(Exception,"fail 5");

           count3++;
          }
        else
          {
           Printf(Exception,"fail 6");
          }
       }
     else
       {
        count1++;
       }
    }

  Printf(Con,"#; #; #;\n",count1,count2,count3);

  Printf(Con,"SqRoot ok\n");

  Printf(Con,"\n#;\n\n",TextDivider());
 }

/* testBits() */

template <class UInt>
void testBits(ulen rep=Rep)
 {
  Random random;

  for(auto count=rep; count ;count--)
    {
     UInt a=random.next_uint<UInt>()|UIntBitFunc_gen<UInt>::MSBit;

     unsigned s=random.select(UIntBitFunc_gen<UInt>::Bits);

     a>>=s;

     unsigned n=UIntBitFunc_gen<UInt>::CountZeroMSB(a);

     if( n!=s ) Printf(Exception,"fail 7");

     if( UIntBitFunc_gen<UInt>::BitsOf(a)!=UIntBitFunc_gen<UInt>::Bits-n ) Printf(Exception,"fail 8");
    }

  for(auto count=rep; count ;count--)
    {
     UInt a=random.next_uint<UInt>()|1u;

     unsigned s=random.select(UIntBitFunc_gen<UInt>::Bits);

     a<<=s;

     unsigned n=UIntBitFunc_gen<UInt>::CountZeroLSB(a);

     if( n!=s ) Printf(Exception,"fail 8");
    }

  Printf(Con,"Bits ok\n");

  Printf(Con,"\n#;\n\n",TextDivider());
 }

} // namespace Private_1010

using namespace Private_1010;

/* Testit<1010> */

template<>
const char *const Testit<1010>::Name="Test1010 UIntFunc";

template<>
bool Testit<1010>::Main()
 {
  test<unsigned short>("unsigned short");
  test<unsigned>("unsigned");
  test<unsigned long long>("unsigned long long");

  testSqRoot<unsigned>();
  testSqRoot<uint32>();

  testBits<unsigned>();
  testBits<unsigned long long>();

  return true;
 }

} // namespace App

