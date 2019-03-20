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

#include <CCore/inc/Timer.h>
#include <CCore/inc/PrintTime.h>
#include <CCore/inc/Exception.h>

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

void PrimeBuilder::setStatusCancel()
 {
  setStatus(BuilderDoneReject,"Cancelled!"_str);
 }

void PrimeBuilder::setException(StrLen text) noexcept
 {
  try
    {
     PrintString out;

     Printf(out,"Exception: #;",text);

     setStatus(BuilderDoneReject,out.close());
    }
  catch(...)
    {
     setStatus(BuilderDoneReject,"Exception: no memory"_str);
    }
 }

class PrimeBuilder::Report : NoCopy
 {
   PrimeBuilder *obj;

   static constexpr unsigned Count = 1000 ;

   unsigned count = 0 ;

   unsigned P = 0 ;

  private:

   void testStop()
    {
     if( obj->stop_flag ) throw Cancel;
    }

  public:

   enum CancelType { Cancel };

   explicit Report(PrimeBuilder *obj_) : obj(obj_) {}

   template <class Integer>
   void start(const Integer &) {}

   void sanity(const char *) {}

   void isSmallPrime() {}

   void testP(unsigned prime_p)
    {
     testStop();

     P=prime_p;

     PrintString out;

     Printf(out,"Test P = #;",prime_p);

     obj->setStatus(BuilderRunning,out.close());
    }

   void testQ(Math::APRTest::QType prime_q)
    {
     testStop();

     PrintString out;

     Printf(out,"Test P = #;\n  Q = #;",P,prime_q);

     obj->setStatus(BuilderRunning,out.close());
    }

   template <class Integer>
   void cappa(PtrLen<const Integer>,const Integer &)
    {
     testStop();
    }

   template <class Integer>
   void cappa2(const Integer &,const Integer &)
    {
     testStop();
    }

   void startProbe()
    {
     testStop();

     obj->setStatus(BuilderRunning,"Start probe"_str);
    }

   template <class Integer>
   void probe(const Integer &cnt)
    {
     testStop();

     if( count )
       {
        count--;
       }
     else
       {
        count=Count;

        PrintString out;

        Printf(out,"Probe #;",cnt);

        obj->setStatus(BuilderRunning,out.close());
       }
    }

   template <class Integer>
   void div(const Integer &) {}

   void hard() {}

   void isPrime() {}

   void noPrime() {}
 };

void PrimeBuilder::work1(PtrLen<const uint8> number_)
 {
  using Int = Math::Integer<Math::IntegerFastAlgo> ;

  Math::OctetInteger<Int> number(number_);

  SecTimer timer;

  setStatus(BuilderRunning,"No-prime test is being performed ..."_str);

  if( Math::NoPrimeTest<Int>::RandomTest(number,100,random) )
    {
     setStatus(BuilderRunning,"Probable prime ..."_str);

     if( stop_flag ) return setStatusCancel();

     try
       {
        Math::APRTest::TestEngine<Int> test;
        Report report(this);

        auto result=test(number,report);

        PrintString out;

        if( result )
          Printf(out,"Rejected: #;!",result);
        else
          Printf(out,"Prime. Time = #;.",PrintTime(timer.get()));

        setStatus((result?BuilderDoneReject:BuilderDoneIsPrime),out.close());
       }
     catch(Report::CancelType)
       {
        return setStatusCancel();
       }
    }
  else
    {
     setStatus(BuilderDoneReject,"Not a prime!"_str);
    }
 }

void PrimeBuilder::work(PtrLen<const uint8> number)
 {
  SimpleArray<char> buf(4_KByte);
  PrintBuf out(Range(buf));
  ReportExceptionTo report(out);

  try
    {
     work1(number);

     report.guard();

     async_interrupt();
    }
  catch(CatchType)
    {
     setException(out.close());
    }
  catch(...)
    {
     setException("Unknown exception"_c);
    }
 }

void PrimeBuilder::exit()
 {
  stopping=true;

  stop_sem.give();
 }

class PrimeBuilder::Work : public Task
 {
   PrimeBuilder *obj;

   DynArray<uint8> number;

  private:

   virtual void entry()
    {
     obj->work(Range(number));
    }

   virtual void exit()
    {
     PrimeBuilder *temp=obj;

     delete this;

     temp->exit();
    }

  public:

   explicit Work(PrimeBuilder *obj_)
    {
     obj=obj_;

     number.extend_copy(Range(obj->buf));
    }

   virtual ~Work() {}
 };

PrimeBuilder::PrimeBuilder(Function<void (void)> async_interrupt_)
 : async_interrupt(async_interrupt_)
 {
 }

PrimeBuilder::~PrimeBuilder()
 {
  if( running )
    {
     stop_flag=true;

     stop_sem.take();
    }
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

String PrimeBuilder::getOctBuf() const
 {
  if( !buf_ok ) return Empty;

  PrintString out;

  auto r=Range(buf);

  Printf(out,"\n {\n");

  ulen ind=0;

  for(uint8 octet : r )
    {
     if( ind&15 )
       {
        Putobj(out,", "_c);

        if( (ind&3)==0 ) Putch(out,' ');
       }
     else
       {
        if( ind==0 )
          Putobj(out,"  "_c);
        else
          Putobj(out,",\n  "_c);
       }

     Printf(out,"#4.xi;",octet);

     ind++;
    }

  Printf(out,"\n }");

  return out.close();
 }

 // methods

void PrimeBuilder::gen()
 {
  if( !buf_ok ) return;

  fill();

  mask();
 }

void PrimeBuilder::runTest()
 {
  if( running ) return;

  using Int = Math::Integer<Math::IntegerFastAlgo> ;

  Int number=getInteger<Int>();

  stop_flag=false;
  stopping=false;

  Work *ptr=new Work(this);

  running=true;

  if( !ptr->run_or_exit() )
    {
     Printf(Exception,"App::PrimeBuilder::runTest() : cannot start a task");
    }
 }

void PrimeBuilder::cancelTest()
 {
  stop_flag=true;
 }

auto PrimeBuilder::getStatus() -> Status
 {
  if( running && stopping )
    {
     if( stop_sem.take(1_sec) ) running=false;
    }

  Mutex::Lock lock(mutex);

  return Status{state,text,running,Replace_null(status_ok)};
 }

} // namespace App

