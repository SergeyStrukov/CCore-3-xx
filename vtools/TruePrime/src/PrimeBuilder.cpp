/* PrimeBuilder.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: TruePrime 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/PrimeBuilder.h>

#include <CCore/inc/math/NoPrimeTest.h>
#include <CCore/inc/math/APRTest.h>
#include <CCore/inc/math/IntegerFastAlgo.h>
#include <CCore/inc/math/IntegerOctetBuilder.h>

namespace App {

/* class PrimeBuilder */

void PrimeBuilder::SetLSB(PtrLen<uint8> r,ulen lsbits)
 {
  if( lsbits/8<r.len )
    {
     for(; lsbits>=8 ;++r,lsbits-=8) *r=0xFF;

     if( lsbits ) BitSet(*r,MaskLo(lsbits));
    }
  else
    {
     r.set(0xFF);
    }
 }

void PrimeBuilder::SetMSB(PtrLen<uint8> r_,ulen msbits)
 {
  if( msbits/8<r_.len )
    {
     auto r=RangeReverse(r_);

     for(; msbits>=8 ;++r,msbits-=8) *r=0xFF;

     if( msbits ) BitSet(*r,MaskHi(msbits));
    }
  else
    {
     r_.set(0xFF);
    }
 }

void PrimeBuilder::fill()
 {
  random.fill(Range(buf));
 }

void PrimeBuilder::mask()
 {
  auto r=Range(buf);

  SetLSB(r,lsbits);

  ulen n=nbits%8;

  if( n )
    {
     SetMSB(r,msbits+(8-n));

     BitClear(r.back(1),MaskHi(8-n));
    }
  else
    {
     SetMSB(r,msbits);
    }
 }

void PrimeBuilder::clean()
 {
  ulen len=RoundUpCount<ulen>(nbits,8);

  if( len!=buf.getLen() )
    {
     buf.erase();

     buf_ok=false;

     buf=SimpleArray<uint8>(len);

     buf_ok=true;
    }
  else
    {
     Range(buf).set_null();
    }

  mask();
 }

template <class Int>
auto PrimeBuilder::getInteger() const
 {
  return Math::OctetInteger<Int>(Range(buf));
 }

void PrimeBuilder::setStatus(BuilderState state_,const String &text_)
 {
  {
   Mutex::Lock lock(mutex);

   state=state_;
   text=text_;

   status_ok=true;
  }

  async_interrupt();
 }

PrimeBuilder::PrimeBuilder(Function<void (void)> async_interrupt_)
 : async_interrupt(async_interrupt_)
 {
 }

PrimeBuilder::~PrimeBuilder()
 {
 }

 // set

void PrimeBuilder::setBits(ulen value)
 {
  nbits=Cap<ulen>(MinNBits,value,MaxNBits);

  clean();
 }

void PrimeBuilder::setMSBits(ulen value)
 {
  msbits=Cap<ulen>(MinGuardBits,value,MaxGuardBits);

  clean();
 }

void PrimeBuilder::setLSBits(ulen value)
 {
  lsbits=Cap<ulen>(MinGuardBits,value,MaxGuardBits);

  clean();
 }

void PrimeBuilder::setBits(ulen nbits_,ulen msbits_,ulen lsbits_)
 {
  nbits=Cap<ulen>(MinNBits,nbits_,MaxNBits);
  msbits=Cap<ulen>(MinGuardBits,msbits_,MaxGuardBits);
  lsbits=Cap<ulen>(MinGuardBits,lsbits_,MaxGuardBits);

  clean();
 }

 // get (digits only)

String PrimeBuilder::getBin() const
 {
  if( !buf_ok ) return Empty;

  PrintString out;

  auto r=RangeReverse(buf);

  if( +r )
    {
     Printf(out,"#.2;",*r);

     for(++r; +r ;++r)
       {
        Printf(out,"#8.2i;",*r);
       }
    }
  else
    {
     Putobj(out,"0"_c);
    }

  return out.close();
 }

String PrimeBuilder::getDec() const
 {
  if( !buf_ok ) return Empty;

  using Int = Math::Integer<Math::IntegerFastAlgo> ;

  PrintString out;

  Putobj(out,getInteger<Int>());

  return out.close();
 }

String PrimeBuilder::getHex() const
 {
  if( !buf_ok ) return Empty;

  PrintString out;

  auto r=RangeReverse(buf);

  if( +r )
    {
     Printf(out,"#.16;",*r);

     for(++r; +r ;++r)
       {
        Printf(out,"#2.16i;",*r);
       }
    }
  else
    {
     Putobj(out,"0"_c);
    }

  return out.close();
 }

 // methods

void PrimeBuilder::gen()
 {
  if( !buf_ok ) return;

  fill();

  mask();
 }

void PrimeBuilder::runTest() // TODO
 {
 }

void PrimeBuilder::cancelTest() // TODO
 {
 }

auto PrimeBuilder::getStatus() -> Status
 {
  Mutex::Lock lock(mutex);

  return Status{state,text,Replace_null(status_ok)};
 }

} // namespace App

