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

#ifdef CCORE_UTF8

void ReadCon::shift()
 {
  if( !off ) return;

  for(ulen i=0; i<len ;i++) buf[i]=buf[i+off];

  off=0;
 }

Utf8Code ReadCon::GetCode(char ch,const char *ptr,unsigned len)
 {
  switch( len )
    {
     default: [[fallthrough]];
     case 1 : return Utf8Code(ch);
     case 2 : return Utf8Code(ch,ptr[1]);
     case 3 : return Utf8Code(ch,ptr[1],ptr[2]);
     case 4 : return Utf8Code(ch,ptr[1],ptr[2],ptr[3]);
    }
 }

ReadCon::ReadCon()
 : off(0),
   len(0)
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

bool ReadCon::try_get(Utf8Code &ret)
 {
  if( !len ) return false;

  char ch=buf[off];

  unsigned symlen=Utf8Len(ch);

  if( symlen==0 ) symlen=1;

  if( symlen>len ) return false;

  ret=GetCode(ch,buf+off,symlen);

  off+=symlen;
  len-=symlen;

  return true;
 }

Utf8Code ReadCon::get()
 {
  Utf8Code ret;

  while( !get(DefaultTimeout,ret) );

  return ret;
 }

bool ReadCon::get(MSec timeout,Utf8Code &ret)
 {
  return get(TimeScope(timeout),ret);
 }

bool ReadCon::get(TimeScope time_scope,Utf8Code &ret)
 {
  if( try_get(ret) ) return true;

  shift();

  while( +time_scope.get() )
    {
     auto result=con.read(buf+len,Len-len,time_scope);

     if( result.error )
       {
        Printf(Exception,"CCore::ReadCon::get(...) : #;",PrintError(result.error));
       }

     if( result.len==0 ) continue;

     len+=result.len;

     if( try_get(ret) ) return true;
    }

  return false;
 }

#else

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

#endif

} // namespace CCore


