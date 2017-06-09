/* ReadCon.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ReadCon.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintError.h>

namespace CCore {

/* class ReadCon */

ReadCon::ReadCon()
 : cur(buf),
   lim(buf)
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

char ReadCon::get()
 {
  if( cur>=lim )
    {
     auto result=con.read(buf,Len);

     if( result.error )
       {
        Printf(Exception,"CCore::ReadCon::get() : #;",PrintError(result.error));
       }

     if( result.len==0 )
       {
        Printf(Exception,"CCore::ReadCon::get() : null read");
       }

     cur=buf;
     lim=buf+result.len;
    }

  return *(cur++);
 }

bool ReadCon::get(MSec timeout,char &ret)
 {
  if( cur>=lim )
    {
     auto result=con.read(buf,Len,timeout);

     if( result.error )
       {
        Printf(Exception,"CCore::ReadCon::get(...) : #;",PrintError(result.error));
       }

     if( result.len==0 ) return false;

     cur=buf;
     lim=buf+result.len;
    }

  ret=*(cur++);

  return true;
 }

bool ReadCon::get(TimeScope time_scope,char &ret)
 {
  if( cur>=lim )
    {
     auto result=con.read(buf,Len,time_scope);

     if( result.error )
       {
        Printf(Exception,"CCore::ReadCon::get(...) : #;",PrintError(result.error));
       }

     if( result.len==0 ) return false;

     cur=buf;
     lim=buf+result.len;
    }

  ret=*(cur++);

  return true;
 }

} // namespace CCore


