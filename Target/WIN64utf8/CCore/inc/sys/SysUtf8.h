/* SysUtf8.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysUtf8_h
#define CCore_inc_sys_SysUtf8_h

#include <CCore/inc/Utf8.h>

#include <CCore/inc/sys/SysError.h>

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

const WChar * ZScan(const WChar *ztext) noexcept;

ulen ZLen(const WChar *ztext) noexcept;

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

ulen Truncate(PtrLen<const WChar> text,PtrLen<char> out) noexcept;

ulen Full(PtrLen<const WChar> text,PtrLen<char> out) noexcept; // MaxULen on overflow

ulen Full(const WChar *ztext,PtrLen<char> out) noexcept; // MaxULen on overflow

/* classes */

struct SurrogateCouple;

struct CopySym;

struct StartTransform;

struct TransformCountLen;

class WCharToUtf8Full;

template <ulen Len> struct WCharToUtf8;

struct ToWChar;

template <ulen MaxLen=TextBufLen> class WCharString;

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

/* struct StartTransform */

struct StartTransform
 {
  ulen len;
  Unicode next_sym = 0 ;
  PtrLen<const WChar> rest;
  bool ok;

  StartTransform(PtrLen<const WChar> text,PtrLen<char> out) noexcept;
 };

/* struct TransformCountLen */

struct TransformCountLen
 {
  ulen len;
  bool ok;

  TransformCountLen(ulen slen,Unicode sym,PtrLen<const WChar> text) noexcept;
 };

/* FinishTransform() */

ulen FinishTransform(PtrLen<char> out,PtrLen<const char> str,Unicode sym,PtrLen<const WChar> text) noexcept;

/* class WCharToUtf8Full */

class WCharToUtf8Full : NoCopy
 {
   char small[TextBufLen];

   char *ptr;
   ulen len;

  private:

   bool countLen(ulen slen,Unicode sym,PtrLen<const WChar> text);

   void longText(ulen slen,Unicode sym,PtrLen<const WChar> text);

  public:

   explicit WCharToUtf8Full(PtrLen<const WChar> text) noexcept;

   explicit WCharToUtf8Full(const WChar *ztext) : WCharToUtf8Full(Range(ztext,ZLen(ztext))) {}

   ~WCharToUtf8Full();

   bool operator ! () const { return !ptr; }

   ulen getLen() const { return len; }

   StrLen get() const { return StrLen(ptr,len); }
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

/* struct ToWChar */

struct ToWChar
 {
  ulen len;
  bool overflow = false ;
  bool broken = false ;

  ToWChar(PtrLen<WChar> out,StrLen text) noexcept;
 };

/* class WCharString<MaxLen> */

template <ulen MaxLen>
class WCharString : NoCopy
 {
   WChar buf[MaxLen+1];
   ErrorType error;

  public:

   explicit WCharString(StrLen text)
    {
     ToWChar to(Range(buf,MaxLen),text);

     buf[to.len]=0;

     if( to.overflow )
       error=Error_TooLong;
     else if( to.broken )
       error=Error_BrokenUtf8;
     else
       error=NoError;
    }

   ErrorType getError() const { return error; }

   operator const WChar * () const { return buf; }
 };

} // namespace Sys
} // namespace CCore

#endif

