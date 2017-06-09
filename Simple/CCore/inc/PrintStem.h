/* PrintStem.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_PrintStem_h
#define CCore_inc_PrintStem_h

#include <CCore/inc/Printf.h>

namespace CCore {

/* classes */

class PrintFirst;

class PrintPeriod;

/* class PrintFirst */

class PrintFirst : NoCopy
 {
   mutable bool flag = true ;

   StrLen first;
   StrLen other;

  public:

   PrintFirst(StrLen first_,StrLen other_) : first(first_),other(other_) {}

   void reset() { flag=true; }

   StrLen end(StrLen non_empty,StrLen empty) const { return flag?empty:non_empty; }

   // print object

   void print(PrinterType &out) const
    {
     if( flag )
       {
        flag=false;

        Putobj(out,first);
       }
     else
       {
        Putobj(out,other);
       }
    }
 };

/* class PrintPeriod */

class PrintPeriod : NoCopy
 {
   mutable bool flag = true ;
   mutable unsigned count = 0 ;

   unsigned period; // > 0
   StrLen first;
   StrLen next;
   StrLen line;

  public:

   PrintPeriod(unsigned period_,StrLen first_,StrLen next_,StrLen line_) : period(period_),first(first_),next(next_),line(line_) {}

   void reset() { flag=true; }

   StrLen end(StrLen non_empty,StrLen empty) const { return flag?empty:non_empty; }

   // print object

   void print(PrinterType &out) const
    {
     if( flag )
       {
        flag=false;
        count=1;

        Putobj(out,first);
       }
     else
       {
        if( count<period )
          {
           count++;

           Putobj(out,next);
          }
        else
          {
           count=1;

           Putobj(out,line);
          }
       }
    }
 };

} // namespace CCore

#endif

