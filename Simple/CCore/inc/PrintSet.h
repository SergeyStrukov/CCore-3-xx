/* PrintSet.h */
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

#ifndef CCore_inc_PrintSet_h
#define CCore_inc_PrintSet_h

#include <CCore/inc/Printf.h>

namespace CCore {

/* classes */

template <CursorType R,class T=Meta::PtrObjType<R> > requires ( CursorOverType<R,T> ) class PrintSet;

/* class PrintSet<R,T> */

template <CursorType R,class T> requires ( CursorOverType<R,T> )
class PrintSet : public PrintOptAdapter<T>
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
        Putobj(out,"{ ",Cast(*r));

        for(++r; +r ;++r) Putobj(out," , ",Cast(*r));

        Putobj(out," }");
       }
     else
       {
        Putobj(out,"{ }");
       }
    }

   void print(PrinterType &out,const AnyType &opt) const
    {
     R r=range;

     if( +r )
       {
        Putobj(out,"{ ",BindOpt(opt,Cast(*r)));

        for(++r; +r ;++r) Putobj(out," , ",BindOpt(opt,Cast(*r)));

        Putobj(out," }");
       }
     else
       {
        Putobj(out,"{ }");
       }
    }
 };

} // namespace CCore

#endif


