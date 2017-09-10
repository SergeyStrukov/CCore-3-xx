/* ReadConType.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ReadConType_h
#define CCore_inc_ReadConType_h

#include <CCore/inc/TimeScope.h>

#ifdef CCORE_UTF8
# include <CCore/inc/Utf8.h>
#endif

namespace CCore {

/* type ReadConCode */

#ifdef CCORE_UTF8

using ReadConCode = Utf8Code ;

#else

using ReadConCode = char ;

#endif

/* ToChar() */

#ifdef CCORE_UTF8

inline int ToChar(Utf8Code ch) { return (ch.getLen()==1)?ch[0]:(-1); }

#else

inline int ToChar(char ch) { return ch; }

#endif

/* concept ReadConType<ReadCon> */

template <class ReadCon>
concept bool ReadConType = requires(ReadCon &con,MSec timeout,TimeScope time_scope,ReadConCode &ret,char ch,const char *ptr,ulen len,StrLen str)
 {
  { con.get() } -> ReadConCode ;

  { con.get(timeout,ret) } -> bool ;

  { con.get(time_scope,ret) } -> bool ;

  con.put(ch);

  con.put(ptr,len);

  con.put(str);

  con.put(ret);
 } ;

} // namespace CCore

#endif

