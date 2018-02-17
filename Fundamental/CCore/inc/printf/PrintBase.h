/* PrintBase.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_printf_PrintBase_h
#define CCore_inc_printf_PrintBase_h

#include <CCore/inc/SymCount.h>

namespace CCore {

/* word NoPrint */

enum NoPrintType { NoPrint };

/* classes */

template <class P> struct PrintOutAdapter;

class PrintBase;

class PrintBuf;

template <class P> class PrintCount;

/* struct PrintOutAdapter<P> */

template <class P> requires ( PrinterType<Meta::UnRef<typename P::PrintOutType> > )
struct PrintOutAdapter<P>
 {
  using PrintOutType = typename P::PrintOutType ;
 };

template <>
struct PrintOutAdapter<NoPrintType>
 {
  using PrintOutType = void ;
 };

/* type PrintOutType<P> */

template <class P>
using PrintOutType = typename PrintOutAdapter<P>::PrintOutType ;

/* class PrintBase */

class PrintBase : NoCopy
 {
   char *ptr;
   char *cur;
   char *lim;

   bool overflow;

  private:

   void clear() { ptr=cur=lim=0; }

   bool provide(ulen hint_len);

   bool flush_and_provide(ulen hint_len);

   virtual PtrLen<char> do_provide(ulen hint_len)=0;

   virtual void do_flush(char *ptr,ulen len)=0;

   static void PrintBaseOverflow();

  protected:

   void clearOverflowFlag() { overflow=false; }

  public:

   using PrintOutType = PrintBase & ;

   PrintOutType printRef() { return *this; }

   // constructors

   PrintBase() { clear(); clearOverflowFlag(); }

   ~PrintBase() {} // flush() in derived class

   // methods

   bool getOverflowFlag() const { return overflow; }

   PrintBase & guardOverflow() { if( overflow ) PrintBaseOverflow(); return *this; }

   // put

   void put(char ch)
    {
     if( cur<lim || flush_and_provide(1) ) *(cur++)=ch;
    }

   void put(char ch,ulen len);

   void put(const char *str,ulen len);

   void flush();
 };

/* class PrintBuf */

class PrintBuf : public PrintBase
 {
   PtrLen<char> buf;
   ulen off;

  private:

   void initbuf(PtrLen<char> buf);

   virtual PtrLen<char> do_provide(ulen hint_len);

   virtual void do_flush(char *ptr,ulen len);

  public:

   explicit PrintBuf(PtrLen<char> buf=Empty) { initbuf(buf); }

   ~PrintBuf();

   void init(PtrLen<char> buf);

   PrintBuf & guardOverflow() { PrintBase::guardOverflow(); return *this; }

   StrLen close();

   const char * closeZStr() { return close().ptr; }
 };

/* class PrintCount<P> */

template <class P>
class PrintCount : NoCopy
 {
   P &out;
   SymCounter counter;

  public:

   using PrintOutType = PrintCount<P> & ;

   PrintOutType printRef() { return *this; }

   // constructors

   explicit PrintCount(P &out_) : out(out_) {}

   ulen getCount() const { return counter; }

   // put

   void put(char ch)
    {
     counter.put(ch);
     out.put(ch);
    }

   void put(char ch,ulen len)
    {
     counter.put(ch,len);
     out.put(ch,len);
    }

   void put(const char *str,ulen len)
    {
     counter.put(str,len);
     out.put(str,len);
    }

   void flush()
    {
     out.flush();
    }
 };

/* class PrintCount<void> */

template <>
class PrintCount<void> : NoCopy
 {
   SymCounter counter;

  public:

   using PrintOutType = PrintCount<void> & ;

   PrintOutType printRef() { return *this; }

   // constructors

   PrintCount() {}

   // methods

   ulen getCount() const { return counter; }

   // put

   void put(char ch)
    {
     counter.put(ch);
    }

   void put(char ch,ulen len)
    {
     counter.put(ch,len);
    }

   void put(const char *str,ulen len)
    {
     counter.put(str,len);
    }

   void flush()
    {
    }
 };

} // namespace CCore

#endif


