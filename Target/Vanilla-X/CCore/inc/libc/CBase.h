/* CBase.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_libc_CBase_h
#define CCore_inc_libc_CBase_h

namespace LibC_Internal {

/* types */

using PtrValue = unsigned ;

      // to represent void *


using Size = unsigned ;

      // size_t : unsigned , unsigned long


using Format_sj_t =          long long ;
using Format_uj_t = unsigned long long ;

      // intmax_t


using Format_sz_t =      int ;
using Format_uz_t = unsigned ;

      // size_t


using Format_st_t =      int ;
using Format_ut_t = unsigned ;

      // ptrdiff_t


/* consts */

inline constexpr Size NumberBufSize = 64 ;

      // sufficient to hold the octal representation of any unsigned long long


inline constexpr Size PtrValueHexSize = 8 ;

      // number of hex digit to represent PtrValue


/* types */

using FilePos = unsigned long long ;

/* consts */

inline constexpr Size FileBufSize = 4*(1<<10) ;

/* functions */

void Abort(const char *zstr);

/* char prop functions */

inline bool IsSpace(char ch) // 0 is not a space
 {
  return ch==' ' || ch=='\n' || ch=='\r' || ch=='\t' || ch=='\v' || ch=='\f' ;
 }

/* signed int functions */

template <class SInt,class UInt>
void SetPosInt(SInt *out,UInt value) { *out=(SInt)value; }

template <class SInt,class UInt>
void SetNegInt(SInt *out,UInt value) { *out=(SInt)(UInt)-value; }

} // namespace LibC_Internal

#endif


