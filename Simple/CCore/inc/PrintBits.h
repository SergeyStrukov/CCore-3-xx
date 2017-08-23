/* PrintBits.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_PrintBits_h
#define CCore_inc_PrintBits_h

#include <CCore/inc/Printf.h>

namespace CCore {

/* classes */

template <PrinterType P,UIntType UInt> class PrintBitsClass;

/* class PrintBitsClass<P,UInt> */

template <PrinterType P,UIntType UInt>
class PrintBitsClass
 {
   P &out;
   UInt value;
   bool empty;

  public:

   PrintBitsClass(P &out_,UInt value_) : out(out_),value(value_),empty(true) {}

   PrintBitsClass<P,UInt> & operator () (UInt flag,StrLen name)
    {
     if( value&flag )
       {
        BitClear(value,flag);

        if( !empty ) out.put('|');

        Putobj(out,name);

        empty=false;
       }

     return *this;
    }

   void complete()
    {
     if( empty ) out.put('0');
    }
 };

/* PrintBits() */

template <UIntType UInt,PrinterType P>
PrintBitsClass<P,UInt> PrintBits(P &out,UInt value) { return {out,value}; }

} // namespace CCore

#endif


