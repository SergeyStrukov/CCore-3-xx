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

class StopFlag;

class Activator;

//enum BuilderState;

class PrimeBuilder;

/* class StopFlag */

class StopFlag : NoCopy
 {
   Atomic flag;

   friend class Activator;

  public:

   StopFlag() {}

   operator bool() const { return flag; }
 };

/* class Activator */

class Activator : NoCopy
 {
   bool running = false ;

   StopFlag stop_flag;

   Atomic stopping;

   Sem stop_sem;

  private:

   void exit();

   template <class Work>
   class WorkTask : public Task
    {
      Activator *obj;
      Work work;

     private:

      virtual void entry()
       {
        work();
       }

      virtual void exit()
       {
        Activator *temp=obj;

        delete this;

        temp->exit();
       }

     public:

      template <class ... SS>
      explicit WorkTask(Activator *obj_,SS && ... ss) : obj(obj_),work(obj_->stop_flag, std::forward<SS>(ss)... ) {}

      virtual ~WorkTask() {}
    };

  public:

   Activator();

   ~Activator();

   // status

   bool isRunning() const { return running; }

   // start

   template <class Work,class ... SS>
   bool start(SS && ... ss)
    {
     if( running ) return false;

     auto *ptr=new WorkTask<Work>(this, std::forward<SS>(ss)... );

     stop_flag.flag=false;
     stopping=false;
     running=true;

     return ptr->run_or_exit();
    }

   // stop_flag

   void setStop() { stop_flag.flag=true; }

   // stop

   void stop(); // blocking, call in a destructor!

   bool waitStop(MSec timeout);
 };

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

   class Work;

   Activator activator;

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

