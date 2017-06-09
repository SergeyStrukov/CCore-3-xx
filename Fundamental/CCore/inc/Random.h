/* Random.h */
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

#ifndef CCore_inc_Random_h
#define CCore_inc_Random_h

#include <CCore/inc/MersenneTwister.h>
#include <CCore/inc/UIntSplit.h>

namespace CCore {

/* concept RandomCoreType<T> */

template <class T,UIntType UnitType>
concept bool RandomCoreType2 = requires()
 {
  { &T::next } -> UnitType (T::*)() ;

  { &T::next8 } -> uint8 (T::*)() ;

  { &T::next16 } -> uint16 (T::*)() ;

  { &T::next32 } -> uint32 (T::*)() ;

  { &T::next64 } -> uint64 (T::*)() ;
 } ;

template <class T>
concept bool RandomCoreType = requires()
 {
  typename T::UnitType;

  requires ( RandomCoreType2<T,typename T::UnitType> );
 } ;

/* classes */

template <UIntType UInt> struct RandomFill_gen;

template <UIntType UInt> struct RandomFill;

template <UIntType UInt> struct RandomSelect;

template <class T> class RandomBase;

class Random;

/* struct RandomFill_gen<UInt> */

template <UIntType UInt>
struct RandomFill_gen
 {
  template <unsigned DstBit,unsigned SrcBit> struct Extra_loop;

  template <unsigned DstBit,unsigned SrcBit> struct Extra_last;

  template <unsigned DstBit,unsigned SrcBit>
  using Extra = Meta::Select<( DstBit>SrcBit ), Extra_loop<DstBit,SrcBit> , Extra_last<DstBit,SrcBit> > ;

  template <RandomCoreType T>
  static UInt Do(T &random);
 };

template <UIntType UInt>
template <unsigned DstBit,unsigned SrcBit>
struct RandomFill_gen<UInt>::Extra_loop
 {
  template <RandomCoreType T>
  static void Do(UInt &ret,T &random)
   {
    const unsigned Delta=Meta::UIntBits<typename T::UnitType>;

    ret=UInt( (ret<<Delta)^random.next() );

    Extra<DstBit,SrcBit+Delta>::Do(ret,random);
   }
 };

template <UIntType UInt>
template <unsigned DstBit,unsigned SrcBit>
struct RandomFill_gen<UInt>::Extra_last
 {
  template <RandomCoreType T>
  static void Do(UInt &,T &) {}
 };

template <UIntType UInt>
template <RandomCoreType T>
UInt RandomFill_gen<UInt>::Do(T &random)
 {
  UInt ret=UInt(random.next());

  Extra< Meta::UIntBits<UInt> , Meta::UIntBits<typename T::UnitType> >::Do(ret,random);

  return ret;
 }

/* struct RandomFill<UInt> */

template <UIntType UInt>
struct RandomFill : RandomFill_gen<UInt> {};

template <>
struct RandomFill<uint8>
 {
  static uint8 Do(RandomCoreType &random) { return random.next8(); }
 };

template <>
struct RandomFill<uint16>
 {
  static uint16 Do(RandomCoreType &random) { return random.next16(); }
 };

template <>
struct RandomFill<uint32>
 {
  static uint32 Do(RandomCoreType &random) { return random.next32(); }
 };

template <>
struct RandomFill<uint64>
 {
  static uint64 Do(RandomCoreType &random) { return random.next64(); }
 };

/* struct RandomSelect<UInt> */

template <UIntType UInt>
struct RandomSelect
 {
  static UInt Do(UInt a,uint32 b,UInt lim) // lim!=0
   {
    a%=lim;

    UInt lim2=lim/2;
    UInt lim3=(lim-1)/2;

    for(unsigned cnt=32; cnt ;cnt--,b>>=1)
      if( b&1u )
        {
         if( a+1<=lim2 )
           a=2*a+1;
         else
           a=2*a+1-lim;
        }
      else
        {
         if( a<=lim3 )
           a=2*a;
         else
           a=2*a-lim;
        }

    return a;
   }

  template <class T>
  static UInt Do(T &random,UInt lim) // lim!=0
   {
    if( lim<=MaxUInt<uint32> ) return (UInt)random.select((uint32)lim);

    UInt a=random.template next_uint<UInt>();
    uint32 b=random.next32();

    return Do(a,b,lim);
   }
 };

/* class RandomBase<T> */

template <class T>
class RandomBase : NoCopy
 {
  private:

   T & getObj() requires ( RandomCoreType<T> ) { return *static_cast<T *>(this); }

  public:

   template <UIntType UInt>
   UInt next_uint() { return RandomFill<UInt>::Do(getObj()); }

   uint32 select(uint32 lim) { return lim?uint32( getObj().next64()%lim ):getObj().next32(); }

   uint32 select(uint32 a,uint32 b) { return a+select(b-a+1); }

   template <UIntType UInt>
   UInt select_uint(UInt lim) { return lim?RandomSelect<UInt>::Do(getObj(),lim):next_uint<UInt>(); }

   template <UIntType UInt>
   UInt select_uint(UInt a,UInt b) { return a+select_uint<UInt>(b-a+1); }

   template <UIntType UInt>
   void fill(PtrLen<UInt> r)
    {
     for(; +r ;++r) *r=next_uint<UInt>();
    }

   template <UIntType UInt>
   void fill(UInt *ptr,ulen len)
    {
     fill(Range(ptr,len));
    }
 };

/* class Random */

class Random : public MersenneTwister::Gen<MersenneTwister::MT19937> , public RandomBase<Random>
 {
  public:

   Random();

   uint8  next8()  { return uint8 (next()); }

   uint16 next16() { return uint16(next()); }

   uint32 next32() { return uint32(next()); }

   uint64 next64()
    {
     UIntSplit<uint64,uint32> split;

     split[0]=next32();
     split[1]=next32();

     return split.get();
    }
 };

/* concept RandomType<T> */

template <class T>
concept bool RandomType = IsDerivedFrom<T,RandomBase<T> > && requires(T &obj,PtrLen<const uint8> data)
 {
  T();

  obj.warp(data);

  { obj.next8() } -> uint8 ;
  { obj.next16() } -> uint16 ;
  { obj.next32() } -> uint32 ;
  { obj.next64() } -> uint64 ;
 } ;

} // namespace CCore

#endif


