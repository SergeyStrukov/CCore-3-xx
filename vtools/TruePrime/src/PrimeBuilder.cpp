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

namespace App {

/* class PrimeBuilder */

void PrimeBuilder::clean() // TODO
 {
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

 // get (digits only)

String PrimeBuilder::getBin() const // TODO
 {
  return Empty;
 }

String PrimeBuilder::getDec() const // TODO
 {
  return Empty;
 }

String PrimeBuilder::getHex() const // TODO
 {
  return Empty;
 }

 // methods

void PrimeBuilder::gen() // TODO
 {
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

