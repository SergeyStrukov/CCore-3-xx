/* PrintSet.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_PrintSet_h
#define CCore_inc_PrintSet_h

#include <CCore/inc/Printf.h>

namespace CCore {

/* classes */

template <CursorType R,class T=Meta::PtrObjType<R> > requires ( CursorOverType<R,T> ) class PrintSet;

/* class PrintSet<R,T> */

template <CursorType R,class T> requires ( CursorOverType<R,T> )
class PrintSet : public PrintOptAdapter< Meta::UnConst<T> >
 {
   R range;

  private:

   template <class S>
   static const T & Cast(const S &obj) { return obj; }

  public:

   explicit PrintSet(const R &range_) : range(range_) {}

   void print(PrinterType &out) const
    {
     R r=range;

     if( +r )
       {
        Putobj(out,"{ "_c,Cast(*r));

        for(++r; +r ;++r) Putobj(out," , "_c,Cast(*r));

        Putobj(out," }"_c);
       }
     else
       {
        Putobj(out,"{ }"_c);
       }
    }

   void print(PrinterType &out,const AnyType &opt) const
    {
     R r=range;

     if( +r )
       {
        Putobj(out,"{ "_c,BindOpt(opt,Cast(*r)));

        for(++r; +r ;++r) Putobj(out," , "_c,BindOpt(opt,Cast(*r)));

        Putobj(out," }"_c);
       }
     else
       {
        Putobj(out,"{ }"_c);
       }
    }
 };

} // namespace CCore

#endif


