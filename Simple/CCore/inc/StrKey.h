/* StrKey.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
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
#include <CCore/inc/String.h>

namespace CCore {

/* classes */

struct StrKey;

struct StringKey;

/* struct StrKey */

struct StrKey : CmpComparable<StrKey>
 {
  using HashType = uint32 ;

  static HashType Hash(StrLen str);

  // data

  HashType hash;
  StrLen str;

  // constructors

  StrKey() noexcept { hash=Hash(Empty); }

  explicit StrKey(StrLen str_) : hash(Hash(str_)),str(str_) {}

  // cmp objects

  CmpResult objCmp(const StrKey &obj) const
   {
    if( CmpResult ret=LessCmp(hash,obj.hash) ) return ret;

    return StrCmp(str,obj.str);
   }
 };

/* struct StringKey */

struct StringKey : CmpComparable<StringKey>
 {
  StrKey::HashType hash;
  String str;

  StringKey() noexcept { hash=StrKey::Hash(Empty); }

  explicit StringKey(StrKey obj) : hash(obj.hash),str(obj.str) {}

  // cmp objects

  CmpResult objCmp(const StringKey &obj) const
   {
    if( CmpResult ret=LessCmp(hash,obj.hash) ) return ret;

    return StrCmpOf(str,obj.str);
   }
 };

inline CmpResult Cmp(StrKey key,const StringKey &obj)
 {
  if( CmpResult ret=LessCmp(key.hash,obj.hash) ) return ret;

  return StrCmp(key.str,Range(obj.str));
 }

} // namespace CCore

#endif


