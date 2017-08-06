/* IntegerFromString.h */
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

#ifndef CCore_inc_math_IntegerFromString_h
#define CCore_inc_math_IntegerFromString_h

#include <CCore/inc/StrParse.h>

namespace CCore {
namespace Math {

/* guards */

void GuardIntegerBadString();

/* classes */

template <class Integer> class IntegerFromString;

/* class IntegerFromString<Integer> */

template <class Integer>
class IntegerFromString
 {
   static constexpr ulen LoLen = (3*Meta::UIntBits<unsigned>)/10 ; // 10^LoLen-1 <= unsigned::MaxVal
                                                                   // 0.3 < log10(2)

   static_assert( LoLen>=2 ,"CCore::Math::IntegerFromString<Integer> : bad LoLen");

  private:

   Integer pow10[Meta::UIntBits<ulen>]; // 10^(2^index) , [K+1]
   ulen K;

  private:

   //
   // str.len <= 2^(k+1) , k<=K
   //

   Integer convert(StrLen str,ulen k) const;

  public:

   explicit IntegerFromString(ulen max_len);

   ~IntegerFromString() {}

   Integer operator () (StrLen str) const;
 };

template <class Integer>
Integer IntegerFromString<Integer>::convert(StrLen str,ulen k) const
 {
  ulen n=str.len;

  if( n<=LoLen || k==0 )
    {
     if( !n ) GuardIntegerBadString();

     unsigned ret=0;

     for(; +str ;++str)
       {
        DecValue dig(*str);

        if( !dig ) GuardIntegerBadString();

        ret=10*ret+(*dig);
       }

     return ret;
    }

  ulen m=ulen(1)<<k;

  if( m<n )
    {
     StrLen str_hi=(str+=(n-m));

     Integer lo=convert(str,k-1);
     Integer hi=convert(str_hi,k-1);

     return lo+hi*pow10[k];
    }
  else
    {
     return convert(str,k-1);
    }
 }

template <class Integer>
IntegerFromString<Integer>::IntegerFromString(ulen max_len)
 {
  if( !max_len ) GuardIntegerBadString();

  ulen k=0;

  pow10[0]=10;

  for(ulen m=1; m<max_len-m ;m<<=1,k++) pow10[k+1]=pow10[k].sq();

  K=k;
 }

template <class Integer>
Integer IntegerFromString<Integer>::operator () (StrLen str) const
 {
  if( !str ) GuardIntegerBadString();

  switch( *str )
    {
     case '-' : ++str; return -convert(str,K);

     case '+' : ++str; [[fallthrough]];

     default: return convert(str,K);
    }
 }

} // namespace Math
} // namespace CCore

#endif

