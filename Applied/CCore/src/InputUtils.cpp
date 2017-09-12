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
  char ch;
  unsigned symlen;

  start:

  for(;;)
    {
     if( !len ) return false;

     ch=buf[off];
     symlen=Utf8Len(ch);

     if( symlen!=0 ) break;

     off++;
     len--;
    }

  if( symlen>len ) return false;

  for(unsigned i=1; i<symlen ;i++)
    if( !Utf8Ext(buf[off+i]) )
      {
       off+=i;
       len-=i;

       goto start;
      }

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

/* class SymbolParser */

#ifdef CCORE_UTF8

bool SymbolParser::feed(StrLen &text)
 {
  if( len==0 )
    {
     start:

     char ch;

     do
       {
        if( !text ) return false;

        ch=*text;

        ++text;

        symlen=Utf8Len(ch);
       }
     while( symlen==0 );

     buf[len++]=ch;
    }

  while( len<symlen )
    {
     if( !text ) return false;

     char ch=*text;

     if( Utf8Ext(ch) )
       {
        buf[len++]=ch;

        ++text;
       }
     else
       {
        len=0;

        goto start;
       }
    }

  return true;
 }

#else

bool SymbolParser::feed(StrLen &text)
 {
  if( len==0 )
    {
     if( !text ) return false;

     buf=*text;

     len++;

     ++text;
    }

  return true;
 }

#endif

} // namespace CCore

