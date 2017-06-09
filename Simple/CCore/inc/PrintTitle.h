/* PrintTitle.h */
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

#ifndef CCore_inc_PrintTitle_h
#define CCore_inc_PrintTitle_h

#include <CCore/inc/Printf.h>

namespace CCore {

/* classes */

template <class T> class PrintTitle;

/* class PrintTitle<T> */

template <class T>
class PrintTitle
 {
   const T &obj;

  public:

   explicit PrintTitle(const T &obj_) : obj(obj_) {}

   using PrintOptType = TitlePrintOpt ;

   template <PrinterType P>
   void print(P &out,PrintOptType opt) const
    {
     out.put(opt.border,opt.off);
     out.put(' ');

     PrintCount<P> out_count(out);

     Putobj(out_count,obj);

     out.put(' ');
     out.put(opt.border,PosSub(opt.width,opt.off,out_count.getCount(),2u));
    }
 };

} // namespace CCore

#endif


