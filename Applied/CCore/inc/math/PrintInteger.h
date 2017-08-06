/* PrintInteger.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_math_PrintInteger_h
#define CCore_inc_math_PrintInteger_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/Cmp.h>

namespace CCore {
namespace Math {

/* classes */

struct IntegerPrintOpt;

template <class Integer> class PrintInteger;

/* struct IntegerPrintOpt */

struct IntegerPrintOpt
 {
  ulen width;
  IntShowSign show_sign;

  void setDefault()
   {
    width=0;
    show_sign=IntShowSignDefault;
   }

  IntegerPrintOpt() { setDefault(); }

  IntegerPrintOpt(const char *ptr,const char *lim);

  //
  // [+][width=0]
  //
 };

/* class PrintInteger<Integer> */

template <class Integer>
class PrintInteger : NoCopy
 {
   using Unit = typename Integer::Unit ;

  private:

   Integer pow10[Integer::UnitBits+Meta::UIntBits<ulen>]; // 10^(2^index) , [K+1]
   ulen K;

  private:

   struct Get_combine
    {
     static bool Do(PtrLen<const Unit> body,unsigned &ret);
    };

   struct Get_never
    {
     static bool Do(PtrLen<const Unit>,unsigned &) { return false; }
    };

   using Get = Meta::Select<( Integer::UnitBits<Meta::UIntBits<unsigned> ), Get_combine , Get_never > ;

   static bool GetUnsigned(PtrLen<const Unit> body,unsigned &ret);

   bool print_lo_short(PrinterType &out,PtrLen<const Unit> body,ulen k) const;

   bool print_short(PrinterType &out,ulen width,PtrLen<const Unit> body) const;

   void print_lo(PrinterType &out,ulen k) const;

   void print_lo(PrinterType &out,Integer a,ulen k) const;

   //
   // a < 10^(2^(k+1)) , k <= K
   //

   void print(PrinterType &out,ulen width,Integer a,ulen k) const;

  public:

   explicit PrintInteger(ulen max_body_len);

   ~PrintInteger() {}

   void operator () (PrinterType &out,IntegerPrintOpt opt,Integer a) const;
 };

template <class Integer>
bool PrintInteger<Integer>::Get_combine::Do(PtrLen<const Unit> body,unsigned &ret)
 {
  if( body.len>Meta::UIntBits<unsigned>/Integer::UnitBits ) return false;

  unsigned temp=0;

  for(unsigned elem : RangeReverse(body) )
    {
     temp<<=Integer::UnitBits;
     temp|=elem;
    }

  ret=temp;

  return true;
 }

template <class Integer>
bool PrintInteger<Integer>::GetUnsigned(PtrLen<const Unit> body,unsigned &ret)
 {
  if( body.len && body.back(1)==0 ) body.len--;

  if( body.len==0 )
    {
     ret=0;

     return true;
    }

  if( body.len==1 )
    {
     Unit u=body[0];

     if( u<=MaxUInt<unsigned> )
       {
        ret=u;

        return true;
       }

     return false;
    }

  return Get::Do(body,ret);
 }

template <class Integer>
bool PrintInteger<Integer>::print_lo_short(PrinterType &out,PtrLen<const Unit> body,ulen k) const
 {
  unsigned value;

  if( k+1<Meta::UIntBits<ulen> && GetUnsigned(body,value) )
    {
     IntPrintOpt opt;

     opt.width=ulen(1)<<(k+1);
     opt.align=IntAlignInternal;

     Putobj(out,BindOpt(opt,value));

     return true;
    }

  return false;
 }

template <class Integer>
bool PrintInteger<Integer>::print_short(PrinterType &out,ulen width,PtrLen<const Unit> body) const
 {
  unsigned value;

  if( GetUnsigned(body,value) )
    {
     IntPrintOpt opt;

     opt.align=IntAlignInternal;
     opt.width=width;

     Putobj(out,BindOpt(opt,value));

     return true;
    }

  return false;
 }

template <class Integer>
void PrintInteger<Integer>::print_lo(PrinterType &out,ulen k) const
 {
  if( k+1>=Meta::UIntBits<ulen> )
    { // huge output
     print_lo(out,k-1);
     print_lo(out,k-1);
    }
  else
    {
     out.put('0',ulen(1)<<(k+1));
    }
 }

template <class Integer>
void PrintInteger<Integer>::print_lo(PrinterType &out,Integer a,ulen k) const
 {
  if( print_lo_short(out,a.getBody(),k) ) return;

  if( !a )
    {
     print_lo(out,k);
    }
  else if( k>0 )
    {
     auto divmod=a.divmod(pow10[k]);

     print_lo(out,divmod.div,k-1);

     print_lo(out,divmod.mod,k-1);
    }
 }

template <class Integer>
void PrintInteger<Integer>::print(PrinterType &out,ulen width,Integer a,ulen k) const
 {
  if( print_short(out,width,a.getBody()) ) return;

  if( k>0 )
    {
     if( a<pow10[k] )
       {
        print(out,width,a,k-1);
       }
     else
       {
        auto divmod=a.divmod(pow10[k]);

        if( k<Meta::UIntBits<ulen> && (width>>k) )
          width-=(ulen(1)<<k);
        else
          width=0;

        print(out,width,divmod.div,k-1);

        print_lo(out,divmod.mod,k-1);
       }
    }
 }

template <class Integer>
PrintInteger<Integer>::PrintInteger(ulen max_body_len)
 {
  pow10[0]=10;

  ulen k=0;

  for(;;)
    {
     Integer p2=pow10[k].sq();

     if( p2.getBody().len>max_body_len ) break; // 10^(2^(k+1)) > 2^(max_body_len*UnitBits-1)

     pow10[++k]=p2;
    }

  K=k;
 }

template <class Integer>
void PrintInteger<Integer>::operator () (PrinterType &out,IntegerPrintOpt opt,Integer a) const
 {
  switch( a.sign() )
    {
     case CmpLess :
      {
       out.put('-');

       print(out,PosSub(opt.width,1u),-a,K);
      }
     break;

     case CmpEqual :
      {
       if( opt.show_sign==IntShowPlus )
         {
          out.put('+');

          opt.width=PosSub(opt.width,1u);
         }

       if( opt.width )
         out.put('0',opt.width);
       else
         out.put('0');
      }
     break;

     default: // case CmpGreater :
      {
       if( opt.show_sign==IntShowPlus )
         {
          out.put('+');

          opt.width=PosSub(opt.width,1u);
         }

       print(out,opt.width,a,K);
      }
    }
 }

} // namespace Math
} // namespace CCore

#endif

