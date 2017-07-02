/* Pow.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
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

#ifndef CCore_inc_Pow_h
#define CCore_inc_Pow_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* Pow_pos() */

template <UIntType UInt,class T>
T Pow_pos(T a,UInt deg) // deg>0
 {
  BitScanner<UInt> scanner(deg);

  T ret(a);

  for(++scanner; +scanner ;++scanner)
    if( *scanner )
      {
       ret=Sq(ret)*a;
      }
    else
      {
       ret=Sq(ret);
      }

  return ret;
 }

/* Pow() */

template <UIntType UInt,class T>
T Pow(T a,UInt deg)
 {
  if( deg>0 ) return Pow_pos(a,deg);

  return T(1);
 }

} // namespace CCore

#endif

