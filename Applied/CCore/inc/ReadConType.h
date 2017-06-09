/* ReadConType.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ReadConType_h
#define CCore_inc_ReadConType_h

#include <CCore/inc/TimeScope.h>

namespace CCore {

/* concept ReadConType<ReadCon> */

template <class ReadCon>
concept bool ReadConType = requires(ReadCon &con,MSec timeout,TimeScope time_scope,char &ret,char ch,const char *ptr,ulen len,StrLen str)
 {
  { con.get() } -> char ;

  { con.get(timeout,ret) } -> bool ;

  { con.get(time_scope,ret) } -> bool ;

  con.put(ch);

  con.put(ptr,len);

  con.put(str);
 } ;

} // namespace CCore

#endif

