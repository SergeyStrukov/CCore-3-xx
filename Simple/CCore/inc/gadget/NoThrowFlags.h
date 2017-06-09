/* NoThrowFlags.h */
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

#ifndef CCore_inc_gadget_NoThrowFlags_h
#define CCore_inc_gadget_NoThrowFlags_h

#include <CCore/inc/gadget/Meta.h>

namespace CCore {

/* classes */

template <class T,bool default_no_throw> struct SetDefaultNoThrowFlag;

template <class T,bool copy_no_throw> struct SetCopyNoThrowFlag;

template <class T,bool default_no_throw,bool copy_no_throw> struct SetNoThrowFlags;

struct GetNoThrowFlagsBase;

template <class T> struct GetNoThrowFlags;

/* struct SetDefaultNoThrowFlag<T,bool default_no_throw> */

template <class T,bool default_no_throw> struct SetDefaultNoThrowFlag {};

/* struct SetCopyNoThrowFlag<T,bool copy_no_throw> */

template <class T,bool copy_no_throw> struct SetCopyNoThrowFlag {};

/* struct SetNoThrowFlags<T,bool default_no_throw,bool copy_no_throw> */

template <class T,bool default_no_throw,bool copy_no_throw> struct SetNoThrowFlags
 : SetDefaultNoThrowFlag<T,default_no_throw> , SetCopyNoThrowFlag<T,copy_no_throw> {};

/* struct GetNoThrowFlagsBase */

template <class T>
concept bool TrueDefaultNoThrowType = Meta::IsBaseOf<SetDefaultNoThrowFlag<T,true>,T> ;

template <class T>
concept bool FalseDefaultNoThrowType = Meta::IsBaseOf<SetDefaultNoThrowFlag<T,false>,T> ;

template <class T>
concept bool NoDefaultNoThrowType = !( TrueDefaultNoThrowType<T> || FalseDefaultNoThrowType<T> ) ;


template <class T>
concept bool TrueCopyNoThrowType = Meta::IsBaseOf<SetCopyNoThrowFlag<T,true>,T> ;

template <class T>
concept bool FalseCopyNoThrowType = Meta::IsBaseOf<SetCopyNoThrowFlag<T,false>,T> ;

template <class T>
concept bool NoCopyNoThrowType = !( TrueCopyNoThrowType<T> || FalseCopyNoThrowType<T> ) ;


struct GetNoThrowFlagsBase
 {
  // default

  template <NoDefaultNoThrowType T>
  static constexpr bool GetDefault()
   {
    return Meta::PoorFlag<T, !Meta::HasDefaultCtor<T> || Meta::HasNothrowDefaultCtor<T> >;
   }

  template <TrueDefaultNoThrowType T>
  static constexpr bool GetDefault() { return true; }

  template <FalseDefaultNoThrowType T>
  static constexpr bool GetDefault() { return false; }

  // copy

  template <NoCopyNoThrowType T>
  static constexpr bool GetCopy()
   {
    return Meta::PoorFlag<T, !Meta::HasCopyCtor<T> || Meta::HasNothrowCopyCtor<T> >;
   }

  template <TrueCopyNoThrowType T>
  static constexpr bool GetCopy() { return true; }

  template <FalseCopyNoThrowType T>
  static constexpr bool GetCopy() { return false; }
 };

/* struct GetNoThrowFlags<T> */

template <class T>
struct GetNoThrowFlags : GetNoThrowFlagsBase
 {
  enum NoThrowFlagType
   {
    Default_no_throw = GetDefault<T>(),
    Copy_no_throw = GetCopy<T>()
   };
 };

} // namespace CCore

#endif


