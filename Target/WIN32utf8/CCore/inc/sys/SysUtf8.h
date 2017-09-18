/* SysUtf8.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN323utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysUtf8_h
#define CCore_inc_sys_SysUtf8_h

#include <CCore/inc/Utf8.h>

namespace CCore {
namespace Sys {

/* type WChar */

using WChar = uint16 ;

/* functions */

inline bool IsHiSurrogate(WChar wch) { return (wch&0xFC00u)==0xD800u; }

inline bool IsLoSurrogate(WChar wch) { return (wch&0xFC00u)==0xDC00u; }

inline Unicode Surrogate(WChar hi,WChar lo) { return ((uint32(hi&0x3FFu)<<10)|(lo&0x3FFu))+0x10000u ; }

inline bool IsSurrogate(Unicode sym) { return sym>=0x10000u; }

/* functions */

const WChar * ZScan(const WChar *ztext);

ulen ZLen(const WChar *ztext);

/* functions */

inline Unicode CutUnicode(PtrLen<const WChar> &text) // +text
 {
  Unicode sym;

  WChar hi=*text;

  if( IsHiSurrogate(hi) )
    {
     if( text.len<2 )
       { // single Hi
        sym=hi;

        ++text;
       }
     else
       {
        WChar lo=text[1];

        if( IsLoSurrogate(lo) )
          {
           sym=Surrogate(hi,lo);

           text+=2;
          }
        else
          { // single Hi
           sym=hi;

           ++text;
          }
       }
    }
  else
    { // may be single Lo
     sym=hi;

     ++text;
    }

  return sym;
 }

bool FeedUnicode(PtrLen<const WChar> text,FuncType<bool,Unicode> func)
 {
  while( +text )
    {
     Unicode sym=CutUnicode(text);

     if( !func(sym) ) return false;
    }

  return true;
 }

void FeedUnicode(PtrLen<const WChar> text,FuncArgType<Unicode> func)
 {
  while( +text )
    {
     Unicode sym=CutUnicode(text);

     func(sym);
    }
 }

ulen Truncate(PtrLen<const WChar> text,PtrLen<char> out);

ulen Full(PtrLen<const WChar> text,PtrLen<char> out); // MaxULen on overflow

ulen Full(const WChar *ztext,PtrLen<char> out); // MaxULen on overflow

/* classes */

struct CopySym;

struct SurrogateCouple;

template <ulen Len> struct WCharToUtf8;

/* struct CopySym */

struct CopySym
 {
  PtrLen<char> &out;

  explicit CopySym(PtrLen<char> &out_) : out(out_) {}

  bool operator () (Unicode sym)
   {
    Utf8Code code=ToUtf8(sym);

    if( code.getLen()>out.len ) return false;

    code.getRange().copyTo(out.ptr);

    out+=code.getLen();

    return true;
   }
 };

/* struct SurrogateCouple */

struct SurrogateCouple
 {
  WChar hi;
  WChar lo;

  explicit SurrogateCouple(Unicode sym)
   {
    sym-=0x10000u;

    hi=WChar( 0xD800u|((sym>>10)&0x3FFu) );
    lo=WChar( 0xDC00u|(sym&0x3FFu) );
   }
 };

/* struct WCharToUtf8<ulen Len> */

template <ulen Len_>
struct WCharToUtf8 : NoCopy
 {
  static constexpr ulen Len = Len_ ;

  WChar buf[Len];
  ulen len;

  ulen truncate(PtrLen<char> out) const { return Truncate(Range(buf,len),out); }

  ulen full(PtrLen<char> out) const { return Full(Range(buf,len),out); } // MaxULen on overflow
 };

} // namespace Sys
} // namespace CCore

#endif

