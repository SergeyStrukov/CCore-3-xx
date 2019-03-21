/* PrimeBuilder.h */
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

#ifndef PrimeBuilder_h
#define PrimeBuilder_h

#include <CCore/inc/Task.h>
#include <CCore/inc/String.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/PlatformRandom.h>

namespace App {

/* using */

using namespace CCore;

/* consts */

enum BuilderLimits
 {
  MinNBits =  100,
  MaxNBits = 9020,

  MinGuardBits =  2,
  MaxGuardBits = 32
 };

/* classes */

//enum BuilderState;

class PrimeBuilder;

/* enum BuilderState */

enum BuilderState
 {
  BuilderReady,

  BuilderRunning,

  BuilderDoneIsPrime,
  BuilderDoneReject
 };

/* class PrimeBuilder */

class PrimeBuilder : NoCopy
 {
   PlatformRandom random;

   SimpleArray<uint8> buf;

   ulen nbits = MinNBits ;
   ulen msbits = MinGuardBits ;
   ulen lsbits = MinGuardBits ;

   bool buf_ok = false ;

  private:

   static auto MaskLo(ulen n) { return (1u<<n)-1; }

   static auto MaskHi(ulen n) { return 0xFF00u >> n ; }

   static void SetLSB(PtrLen<uint8> r,ulen lsbits);

   static void SetMSB(PtrLen<uint8> r,ulen msbits);

   void fill();

   void mask();

   void clean();

   template <class Int>
   auto getInteger() const;

  private:

   Function<void (void)> async_interrupt;

   Mutex mutex;

   BuilderState state = BuilderReady ;
   String text;
   bool status_ok = false ;

  private:

   void setStatus(BuilderState state,const String &text);

   void setStatusCancel();

   void setException(StrLen text) noexcept;

  private:

   bool running=false;

   Atomic stop_flag;
   Atomic stopping;

   Sem stop_sem;

  private:

   class Report;

   template <class Int,class Engine>
   void work_engine(PtrLen<const uint8> number);

   void work_single(PtrLen<const uint8> number);

   void work_para(PtrLen<const uint8> number);

   void work(PtrLen<const uint8> number,bool para);

   void exit();

   class Work;

  public:

   explicit PrimeBuilder(Function<void (void)> async_interrupt);

   ~PrimeBuilder();

   // set

   void setBits(ulen nbits);

   void setMSBits(ulen nbits);

   void setLSBits(ulen nbits);

   void setBits(ulen nbits,ulen msbits,ulen lsbits);

   // get (digits only)

   String getBin() const;

   String getDec() const;

   String getHex() const;

   String getOctBuf() const;

   // methods

   void gen();

   void runTest(bool para);

   void cancelTest();

   struct Status
    {
     BuilderState state;
     String text;
     bool running;
     bool ok;
    };

   Status getStatus();
 };

} // namespace App

#endif

