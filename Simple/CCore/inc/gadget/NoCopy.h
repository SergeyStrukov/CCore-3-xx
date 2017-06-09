/* NoCopy.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#ifndef CCore_inc_gadget_NoCopy_h
#define CCore_inc_gadget_NoCopy_h

namespace CCore {

/* classes */

struct NoCopyType;

template <class ... TT> struct NoCopyBaseOf;

/* struct NoCopyType */

struct NoCopyType
 {
  NoCopyType() = default ;

  NoCopyType(const NoCopyType &) = delete ;

  void operator = (const NoCopyType &) = delete ;
 };

/* struct NoCopyBaseOf<TT> */

template <class ... TT>
struct NoCopyBaseOf : TT ...
 {
  NoCopyBaseOf() = default ;

  NoCopyBaseOf(const NoCopyBaseOf &) = delete ;

  void operator = (const NoCopyBaseOf &) = delete ;
 };

/* type NoCopyBase<TT> */

template <class ... TT>
using NoCopyBase = NoCopyBaseOf<TT...> ;

/* type NoCopy */

using NoCopy = NoCopyType ;

} // namespace CCore

#endif


