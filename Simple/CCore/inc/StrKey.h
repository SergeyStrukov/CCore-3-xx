/* StrKey.h */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_StrKey_h
#define CCore_inc_StrKey_h

#include <CCore/inc/Cmp.h>

namespace CCore {

/* classes */

struct StrKey;

/* struct StrKey */

struct StrKey : CmpComparable<StrKey>
 {
  using HashType = uint32 ;

  static HashType Hash(StrLen str);

  // data

  HashType hash;
  StrLen str;

  // constructors

  StrKey() noexcept : hash(0) {}

  explicit StrKey(StrLen str_) : hash(Hash(str_)),str(str_) {}

  // cmp objects

  CmpResult objCmp(const StrKey &obj) const
   {
    if( CmpResult result=LessCmp(hash,obj.hash) ) return result;

    return StrCmp(str,obj.str);
   }
 };

} // namespace CCore

#endif


