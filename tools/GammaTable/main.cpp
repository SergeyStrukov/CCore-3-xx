/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: GammaTable 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <cmath>
#include <cstdio>

#include <CCore/inc/Print.h>

using namespace std;
using namespace CCore;

/* Fill() */

template <UIntType UInt>
void Fill(PtrLen<UInt> table,double order)
 {
  double M=table.len-1;
  double V=MaxUInt<UInt>;

  for(ulen i=0; i<table.len ;i++)
    {
     double x=i/M;
     double y=pow(x,order);

     table[i]=UInt( round(V*y) );
    }
 }

/* FillLen() */

inline constexpr ulen DirectLen = ulen(1)<<8 ;

inline constexpr ulen InverseLen = ulen(1)<<16 ;

 // Fixed

using Fixed = uint32 ; // 8.24

inline constexpr int FixedPrec = 24 ;

Fixed ToFixed(double x)
 {
  return Fixed( round(ldexp(x,FixedPrec)) );
 }

double FromFixed(Fixed x)
 {
  return ldexp(x,-FixedPrec);
 }

 // NegLog

template <ulen Len>
Fixed NegLog(ulen i)
 {
  double M=Len-1;

  return ToFixed( -log(i/M) );
 }

 // NegLog_lut

template <ulen Len>
Fixed NegLog_lut(ulen i);

static Fixed LogTable8[DirectLen];

static Fixed LogTable16[InverseLen];

template <>
Fixed NegLog_lut<DirectLen>(ulen i) { return LogTable8[i]; }

template <>
Fixed NegLog_lut<InverseLen>(ulen i) { return LogTable16[i]; }

 // ExpNeg

template <UIntType UInt>
UInt ExpNeg(Fixed x)
 {
  double V=MaxUInt<UInt>;

  return UInt( round(V*exp(-FromFixed(x))) );
 }

 // ExpNeg_lut

inline constexpr unsigned ExpPrec = 17 ;

inline constexpr unsigned ExpShift = Meta::UIntBits<Fixed> - ExpPrec ;

inline constexpr ulen ExpTableLen = ulen(1)<<ExpPrec ;

template <UIntType UInt>
struct ExpNeg_lut_ab
 {
  UInt a;
  UInt b;

  ExpNeg_lut_ab(Fixed x);
 };

static uint8 ExpTable8[ExpTableLen+1];

static uint16 ExpTable16[ExpTableLen+1];

template <>
ExpNeg_lut_ab<uint8>::ExpNeg_lut_ab(Fixed x)
 {
  auto ind=x>>ExpShift;

  a=ExpTable8[ind];
  b=ExpTable8[ind+1];
 }

template <>
ExpNeg_lut_ab<uint16>::ExpNeg_lut_ab(Fixed x)
 {
  auto ind=x>>ExpShift;

  a=ExpTable16[ind];
  b=ExpTable16[ind+1];
 }

template <UIntType UInt>
UInt ExpNeg_lut(Fixed x)
 {
  ExpNeg_lut_ab<UInt> val(x);

  Fixed mask=(Fixed(1)<<ExpShift)-1;

  Fixed delta=x&mask;

  return UInt( val.a-(((val.a-val.b)*delta)>>ExpShift) );
 }

 // Mul

Fixed Mul(Fixed x,double order)
 {
  return Fixed( Min_cast( x*order+0.5 , Fixed(-1) ) );
 }

 // FillLen

template <ulen Len,UIntType UInt>
void FillLen(UInt table[Len],double order)
 {
  table[0]=0;

  for(ulen i=1; i<Len ;i++)
    {
     table[i]=ExpNeg_lut<UInt>( Mul( NegLog_lut<Len>(i) , order ) );
    }
 }

/* Dist() */

template <UIntType UInt>
UInt Dist(UInt a,UInt b)
 {
  return (a<b)?(b-a):(a-b);
 }

template <ulen Len,UIntType UInt>
UInt Dist(UInt table1[Len],UInt table2[Len])
 {
  UInt ret=0;

  for(ulen i=0; i<Len ;i++) Replace_max(ret,Dist(table1[i],table2[i]));

  return ret;
 }

/* test() */

static void test1(double order)
 {
  static uint16 direct1[DirectLen];
  static uint16 direct2[DirectLen];

  Fill(Range(direct1),order);
  FillLen<DirectLen>(direct2,order);

  printf("order = %f dist = %d\n",order,(int)Dist<DirectLen>(direct1,direct2));
 }

static void test2(double order)
 {
  static uint8 inverse1[InverseLen];
  static uint8 inverse2[InverseLen];

  Fill(Range(inverse1),order);
  FillLen<InverseLen>(inverse2,order);

  printf("order = %f dist = %d\n",order,(int)Dist<InverseLen>(inverse1,inverse2));
 }

static void test(double order)
 {
  test1(order);
  test2(1/order);
 }

/* main() */

int main()
 {
  for(ulen i=1; i<DirectLen ;i++) LogTable8[i]=NegLog<DirectLen>(i);

  for(ulen i=1; i<InverseLen ;i++) LogTable16[i]=NegLog<InverseLen>(i);

  for(ulen i=0; i<ExpTableLen ;i++) ExpTable8[i]=ExpNeg<uint8>(i<<ExpShift);

  ExpTable8[ExpTableLen]=ExpTable8[ExpTableLen-1];

  for(ulen i=0; i<ExpTableLen ;i++) ExpTable16[i]=ExpNeg<uint16>(i<<ExpShift);

  ExpTable16[ExpTableLen]=ExpTable16[ExpTableLen-1];

  PrintFile out("test.txt");

  for(double order=0.1; order<2.05 ;order+=0.1) test(order);

  return 0;
 }


