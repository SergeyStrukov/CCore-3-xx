/* SysUtf8.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysUtf8.h>

#include <CCore/inc/MemBase.h>

#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

static_assert( Meta::IsSame<WChar,Win32::wchar> ,"CCore::Sys : bad WChar");

/* functions */

const WChar * ZScan(const WChar *ztext)
 {
  for(; *ztext ;ztext++);

  return ztext;
 }

ulen ZLen(const WChar *ztext)
 {
  return Dist(ztext,ZScan(ztext));
 }

/* functions */

ulen Truncate(PtrLen<const WChar> text,PtrLen<char> out)
 {
  ulen start=out.len;

  FeedUnicode(text,CopySym(out));

  return start-out.len;
 }

ulen Full(PtrLen<const WChar> text,PtrLen<char> out)
 {
  ulen start=out.len;

  bool ok=FeedUnicode(text,CopySym(out));

  if( ok ) return start-out.len;

  return MaxULen;
 }

ulen Full(const WChar *ztext,PtrLen<char> out)
 {
  return Full(Range(ztext,ZLen(ztext)),out);
 }

/* class WCharToUtf8Full */

bool WCharToUtf8Full::countLen(ulen slen,Unicode sym,PtrLen<const WChar> text)
 {
  struct CountLen
   {
    ULenSat result;

    bool operator () (Unicode sym)
     {
      Utf8Code code=ToUtf8(sym);

      result+=code.getLen();

      return result.overflow;
     }
   };

  CountLen count{slen};

  count(sym); // cannot overflow here

  while( +text )
    if( count(CutUnicode(text)) )
      {
       len=MaxULen;
       ptr=0;

       return false;
      }

  len=count.result.value;

  return true;
 }

void WCharToUtf8Full::longText(ulen slen,Unicode sym,PtrLen<const WChar> text)
 {
  // count len

  if( !countLen(slen,sym,text) ) return;

  // build

  ptr=static_cast<char *>(TryMemAlloc(len));

  if( !ptr ) return;

  Range(small,slen).copyTo(ptr);

  auto out=Range(ptr+slen,len-slen);

  CopySym copy(out);

  copy(sym);

  while( +text ) copy(CutUnicode(text));

  len-=out.len;
 }

WCharToUtf8Full::WCharToUtf8Full(PtrLen<const WChar> text)
 {
  auto out=Range(small);

  CopySym copy(out);

  while( +text )
    {
     Unicode sym=CutUnicode(text);

     if( !copy(sym) )
       {
        longText(DimOf(small)-out.len,sym,text);

        return;
       }
    }

  ptr=small;
  len=DimOf(small)-out.len;
 }

WCharToUtf8Full::~WCharToUtf8Full()
 {
  if( ptr && ptr!=small ) MemFree(ptr);
 }

} // namespace Sys
} // namespace CCore

