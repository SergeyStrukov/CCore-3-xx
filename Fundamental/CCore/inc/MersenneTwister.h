/* MersenneTwister.h */
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

#ifndef CCore_inc_MersenneTwister_h
#define CCore_inc_MersenneTwister_h

#include <CCore/inc/Timer.h>
#include <CCore/inc/UIntSplit.h>

namespace CCore {
namespace MersenneTwister {

/* classes */

struct MT19937;

template <class P> class Gen;

/* struct MT19937 */

struct MT19937
 {
  // unit

  using UnitType = uint32 ;

  static constexpr ulen W = 32 ;

  // state

  static constexpr ulen N = 624 ;
  static constexpr ulen M = 397 ;
  static constexpr ulen R =  31 ;

  static constexpr UnitType A = 0x9908B0DF ;

  // output

  static constexpr ulen S1 = 11 ;
  static constexpr ulen S2 =  7 ;
  static constexpr ulen S3 = 15 ;
  static constexpr ulen S4 = 18 ;

  static constexpr UnitType B = 0x9D2C5680 ;
  static constexpr UnitType C = 0xEFC60000 ;

  // initialization

  static constexpr ulen ReMessCount =  100 ;
  static constexpr ulen MessCount   = 1000 ;

  static const UnitType HotBits[N];
 };

/* class Gen<P> */

template <class P>
class Gen : NoCopy
 {
  public:

   using UnitType = typename P::UnitType ;

  private:

   ulen remess_count;
   ulen ind;
   UnitType state[P::N];

  private:

   static UnitType Func(UnitType x0,UnitType x1);

   static UnitType Func(UnitType x0,UnitType x1,UnitType x2);

   void tick() { state[1]=UnitType( ClockTimer::Get() ); }

   void generate();

   static UnitType Output(UnitType x);

  protected:

   PtrLen<UnitType> getState() { return Range(state); }

   void hotbits();

   void messup();

   void pure_init() { ind=P::N; }

   UnitType pure_next();

  public:

   UnitType next();

   void warp(PtrLen<const uint8> data);
 };

template <class P>
auto Gen<P>::Func(UnitType x0,UnitType x1) -> UnitType
 {
  const UnitType MaskLow=(UnitType(1)<<P::R)-1;

  UnitType x=UnitType( ((x0^x1)&MaskLow)^x0 );
  UnitType y=UIntFunc<UnitType>::Neg(UnitType(x&1));

  return UnitType( (x>>1)^(y&P::A) );
 }

template <class P>
auto Gen<P>::Func(UnitType x0,UnitType x1,UnitType x2) -> UnitType
 {
  return UnitType( Func(x0,x1)^x2 );
 }

template <class P>
void Gen<P>::generate()
 {
  UnitType *ptr=state;

  for(ulen cnt=P::N-P::M; cnt ;cnt--,ptr++) *ptr=Func(*ptr,*(ptr+1),*(ptr+P::M));

  for(ulen cnt=P::M-1; cnt ;cnt--,ptr++) *ptr=Func(*ptr,*(ptr+1),*(ptr-(P::N-P::M)));

  *ptr=Func(*ptr,*state,*(ptr-(P::N-P::M)));
 }

template <class P>
auto Gen<P>::Output(UnitType x) -> UnitType
 {
  x=UnitType( x^(x>>P::S1) );
  x=UnitType( x^((x<<P::S2)&P::B) );
  x=UnitType( x^((x<<P::S3)&P::C) );
  x=UnitType( x^(x>>P::S4) );

  return x;
 }

template <class P>
void Gen<P>::hotbits()
 {
  getState().copy(P::HotBits);
 }

template <class P>
void Gen<P>::messup()
 {
  for(ulen cnt=P::MessCount; cnt ;cnt--)
    {
     tick();

     generate();
    }

  ind=0;
  remess_count=P::ReMessCount;
 }

template <class P>
auto Gen<P>::pure_next() -> UnitType
 {
  if( ind>=P::N )
    {
     generate();

     ind=0;
    }

  return Output(state[ind++]);
 }

template <class P>
auto Gen<P>::next() -> UnitType
 {
  if( ind>=P::N )
    {
     if( remess_count )
       {
        remess_count--;
       }
     else
       {
        remess_count=P::ReMessCount;

        tick();
       }

     generate();

     ind=0;
    }

  return Output(state[ind++]);
 }

template <class P>
void Gen<P>::warp(PtrLen<const uint8> data)
 {
  for(auto dst=Range(state+1,(P::N-1)/2); +dst ;++dst)
    {
     UIntSplit<UnitType,uint8> split;

     auto buf=split.ref();

     if( data.len<buf.len ) break;

     buf.copy(data.ptr);

     (*dst)^=split.get();

     data+=buf.len;
    }
 }

} // namespace MersenneTwister
} // namespace CCore

#endif


