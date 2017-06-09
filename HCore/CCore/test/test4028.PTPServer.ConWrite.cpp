/* test4028.PTPServer.ConWrite.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/CmdInput.h>
#include <CCore/inc/ReadCon.h>
#include <CCore/inc/Scanf.h>

namespace App {

namespace Private_4028 {

/* functions */

inline uint32 ToTicks(uint32 time_msec)
 {
  Replace_min(time_msec,(MaxUInt<uint32>-999)/Net::InboundTicksPerSec);

  return (time_msec*Net::InboundTicksPerSec+999)/1000;
 }

/* class PTPConWrite */

class PTPConWrite : NoCopy
 {
   static const ulen BufLen = 8 ; // power of 2

   uint32 next_number;
   uint32 write_ticks;

   struct Frame
    {
     DynArray<char> text;
     uint32 write_ticks;
     bool ok;

     Frame() : ok(false) {}

     bool set(StrLen text,uint32 write_ticks);

     bool tick();

     bool print();
    };

   Frame buf[BufLen];
   ulen ind;
   bool ok;

  private:

   static ulen Next(ulen ind) { return (ind+1)%BufLen; }

   static void Print(StrLen text);

   bool shift();

   void set(uint32 n,StrLen text);

   void write(uint32 n,StrLen text); // n <= BufLen

   ulen skip();

  public:

   PTPConWrite();

   ~PTPConWrite();

   void open(uint32 write_timeout_msec);

   bool operator () (uint32 number,StrLen text);

   void tick();

   void close();
 };

bool PTPConWrite::Frame::set(StrLen text_,uint32 write_ticks_)
 {
  if( ok ) return false;

  write_ticks=write_ticks_;

  ok=true;

  try
    {
     text.extend_copy(text_);

     return true;
    }
  catch(CatchType)
    {
     return false;
    }
 }

bool PTPConWrite::Frame::tick()
 {
  if( !ok ) return false;

  if( write_ticks )
    {
     write_ticks--;

     return false;
    }

  return true;
 }

bool PTPConWrite::Frame::print()
 {
  if( !ok ) return false;

  Print(Range_const(text));

  text.erase();

  ok=false;

  return true;
 }

/* class PTPConWrite */

void PTPConWrite::Print(StrLen text)
 {
  PrintCon::Print(text);
 }

bool PTPConWrite::shift()
 {
  bool ret=buf[ind].print();

  next_number++;

  ind=Next(ind);

  return ret;
 }

void PTPConWrite::set(uint32 n,StrLen text)
 {
  ulen i=(ind+n-1)%BufLen;

  if( !buf[i].set(text,write_ticks) ) ok=false;
 }

void PTPConWrite::write(uint32 n,StrLen text)
 {
  if( n )
    {
     set(n,text);
    }
  else
    {
     Print(text);

     while( shift() );
    }
 }

ulen PTPConWrite::skip()
 {
  ulen ret=1;

  while( shift() ) ret++;

  return ret;
 }

PTPConWrite::PTPConWrite()
 : ind(0),
   ok(false)
 {
 }

PTPConWrite::~PTPConWrite()
 {
 }

void PTPConWrite::open(uint32 write_timeout_msec)
 {
  ind=0;
  ok=true;
  next_number=0;
  write_ticks=ToTicks(write_timeout_msec);
 }

bool PTPConWrite::operator () (uint32 number,StrLen text)
 {
  uint32 n=number-next_number;

  if( UIntFunc<uint32>::IsNegative(n) ) return ok=false;

  if( n>=2*BufLen )
    {
     close();

     next_number=number-BufLen;

     ind=0;

     set(BufLen,text);

     return ok=false;
    }
  else if( n>BufLen )
    {
     do
       {
        ulen delta=skip();

        if( n>=delta )
          {
           n-=delta;
          }
        else
          {
           // never happens

           return ok=false;
          }
       }
     while( n>BufLen );

     write(n,text);

     return ok=false;
    }
  else
    {
     write(n,text);

     return ok;
    }
 }

void PTPConWrite::tick()
 {
  ulen i=ind;
  ulen delta=0;

  for(ulen n=1; n<=BufLen ;n++,i=Next(i))
    {
     if( buf[i].tick() )
       {
        ok=false;

        while( delta<n ) delta+=skip();
       }
    }
 }

void PTPConWrite::close()
 {
  for(ulen cnt=BufLen; cnt ;cnt--,ind=Next(ind)) buf[ind].print();
 }

/* class Target */

class Target : public NoCopyBase<CmdInput::Target>
 {
   bool run_flag;

   PTPConWrite write;

  private:

   void empty(StrLen) {}

   void exit(StrLen) { run_flag=false; }

   void tick(StrLen)
    {
     write.tick();

     Putch(Con,'\n');
    }

   void add(StrLen arg)
    {
     ScanString inp(arg);

     uint32 n;
     String text;

     Scanf(inp,"#.10; #.s;",n,text);

     write(n,Range(text));

     Putch(Con,'\n');
    }

   virtual void buildCmdList(CmdInput &input)
    {
     addCommand(input,"",&Target::empty);
     addCommand(input,"exit",&Target::exit);

     addCommand(input,"tick",&Target::tick);
     addCommand(input,"add",&Target::add);
    }

  public:

   Target() : run_flag(true) { write.open(100); }

   ~Target() { write.close(); }

   bool operator + () const { return run_flag; }

   bool operator ! () const { return !run_flag; }
 };

} // namespace Private_4028

using namespace Private_4028;

/* Testit<4028> */

template<>
const char *const Testit<4028>::Name="Test4028 PTPServer ConWrite";

template<>
bool Testit<4028>::Main()
 {
  Target target;
  CmdInputCon<ReadCon> input(target,"test> ");

  while( +target ) input.command();

  return true;
 }

} // namespace App

