/* ReadCon.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ReadCon.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintError.h>

namespace CCore {

/* class ReadCon */

ulen ReadCon::read(char *ptr,ulen len)
 {
  auto result=con.read(ptr,len);

  if( result.error )
    {
     Printf(Exception,"CCore::ReadCon::read(...) : #;",PrintError(result.error));
    }

  if( result.len==0 )
    {
     Printf(Exception,"CCore::ReadCon::read(...) : null read");
    }

  return result.len;
 }

ulen ReadCon::read(char *ptr,ulen len,MSec timeout)
 {
  auto result=con.read(ptr,len,timeout);

  if( result.error )
    {
     Printf(Exception,"CCore::ReadCon::read(...) : #;",PrintError(result.error));
    }

  return result.len;
 }

ulen ReadCon::read(char *ptr,ulen len,TimeScope time_scope)
 {
  auto result=con.read(ptr,len,time_scope);

  if( result.error )
    {
     Printf(Exception,"CCore::ReadCon::read(...) : #;",PrintError(result.error));
    }

  return result.len;
 }

ReadCon::ReadCon()
 {
  if( auto error=con.init() )
    {
     Printf(Exception,"CCore::ReadCon::ReadCon() : #;",PrintError(error));
    }
 }

ReadCon::~ReadCon()
 {
  if( auto error=con.exit() )
    {
     Printf(NoException,"CCore::ReadCon::~ReadCon() : #;",PrintError(error));
    }
 }

} // namespace CCore


