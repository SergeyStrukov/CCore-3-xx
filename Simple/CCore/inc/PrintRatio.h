/* PrintRatio.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_PrintRatio_h
#define CCore_inc_PrintRatio_h

#include <CCore/inc/Printf.h>

namespace CCore {

/* consts */

inline constexpr unsigned DefaultRatioFract = 5 ;

/* classes */

struct RatioPrintOpt;

template <UIntType A,UIntType B> class PrintRatio;

/* struct RatioPrintOpt */

struct RatioPrintOpt
 {
  ulen width;
  unsigned fract;
  IntAlign align;
  IntShowSign show_sign;

  void setDefault()
   {
    width=0;
    fract=DefaultRatioFract;
    align=IntAlignDefault;
    show_sign=IntShowSignDefault;
   }

  RatioPrintOpt() { setDefault(); }

  RatioPrintOpt(const char *ptr,const char *lim);

  //
  // [+][width=0][.<fract>=.5][l|L|r|R|i|I=R]
  //
 };

/* class PrintRatio<A,B> */

template <UIntType A,UIntType B>
class PrintRatio
 {
   A a;
   B b;

  private:

   static A Split(A &a,B b)
    {
     A t=a/b;

     a%=b;

     return t;
    }

  public:

   PrintRatio(A a_,B b_) : a(a_),b(b_) {}

   // print object

   using PrintOptType = RatioPrintOpt ;

   static ulen CountLen(PrintRatio obj,PrintOptType opt)
    {
     PrintCount<void> out;

     opt.width=0;

     Putobj(out,BindOpt(opt,obj));

     return out.getCount();
    }

   void print(PrinterType &out,PrintOptType opt) const
    {
     ulen extra=0;

     if( opt.width )
       {
        ulen len=CountLen(*this,opt);

        extra=PosSub(opt.width,len);
       }

     if( extra && opt.align==IntAlignRight ) out.put(' ',extra);

     if( a!=0 && opt.show_sign ) out.put('+');

     if( extra && opt.align==IntAlignInternal ) out.put('0',extra);

     A x=a;

     Printf(out,"#;.",Split(x,b));

     for(unsigned f=opt.fract; a && f ;f--)
       {
        x*=10;

        Printf(out,"#;",Split(x,b));
       }

     if( x ) Putobj(out,"..."_c);

     if( extra && opt.align==IntAlignLeft ) out.put(' ',extra);
    }
 };

} // namespace CCore

#endif

