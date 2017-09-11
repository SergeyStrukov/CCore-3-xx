/* InputUtils.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/InputUtils.h>

namespace CCore {

/* class ReadConBase */

#ifdef CCORE_UTF8

void ReadConBase::shift()
 {
  if( !off ) return;

  for(ulen i=0; i<len ;i++) buf[i]=buf[i+off];

  off=0;
 }

Utf8Code ReadConBase::GetCode(char ch,const char *ptr,unsigned len)
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

ReadConBase::ReadConBase()
 : off(0),
   len(0)
 {
 }

ReadConBase::~ReadConBase()
 {
 }

 // get

bool ReadConBase::try_get(Utf8Code &ret)
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

Utf8Code ReadConBase::get()
 {
  Utf8Code ret;

  while( !get(DefaultTimeout,ret) );

  return ret;
 }

bool ReadConBase::get(MSec timeout,Utf8Code &ret)
 {
  return get(TimeScope(timeout),ret);
 }

bool ReadConBase::get(TimeScope time_scope,Utf8Code &ret)
 {
  if( try_get(ret) ) return true;

  shift();

  while( +time_scope.get() )
    {
     ulen delta=read(buf+len,Len-len,time_scope);

     if( delta==0 ) continue;

     len+=delta;

     if( try_get(ret) ) return true;
    }

  return false;
 }

#else

void ReadConBase::shift()
 {
  off=0;
 }

ReadConBase::ReadConBase()
 : off(0),
   len(0)
 {
 }

ReadConBase::~ReadConBase()
 {
 }

 // get

bool ReadConBase::try_get(char &ret)
 {
  if( !len ) return false;

  ret=buf[off];

  off++;
  len--;

  return true;
 }

char ReadConBase::get()
 {
  char ret;

  if( try_get(ret) ) return ret;

  shift();

  ulen delta=read(buf,Len);

  if( delta==0 ) return 0;

  len=delta;

  try_get(ret);

  return ret;
 }

bool ReadConBase::get(MSec timeout,char &ret)
 {
  if( try_get(ret) ) return true;

  shift();

  ulen delta=read(buf,Len,timeout);

  if( delta==0 ) return false;

  len=delta;

  return try_get(ret);
 }

bool ReadConBase::get(TimeScope time_scope,char &ret)
 {
  if( try_get(ret) ) return true;

  shift();

  ulen delta=read(buf,Len,time_scope);

  if( delta==0 ) return false;

  len=delta;

  return try_get(ret);
 }

#endif

} // namespace CCore

