/* CharUtils.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/CharUtils.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* struct FillCharBuf */

#ifdef CCORE_UTF8

FillCharBuf::FillCharBuf(PtrLen<Char> out,StrLen text)
 {
  ulen start=out.len;

  while( +text )
    {
     Unicode ch=CutUtf8_unicode(text);

     if( ch==Unicode(-1) ) GuardUtf8Broken("CCore::FillCharBuf::FillCharBuf(...)");

     if( !out )
       {
        overflow=true;
        len=start;

        return;
       }

     *out=ch;

     ++out;
    }

  overflow=false;
  len=start-out.len;
 }

#else

FillCharBuf::FillCharBuf(PtrLen<Char> out,StrLen text)
 {
  if( text.len>out.len )
    {
     out.copy(text.ptr);

     overflow=true;
     len=out.len;
    }
  else
    {
     text.copyTo(out.ptr);

     overflow=false;
     len=text.len;
    }
 }

#endif

/* class PrintCharBuf */

#ifdef CCORE_UTF8

void PrintCharBuf::shift()
 {
  if( off==0 ) return;

  for(ulen i=0; i<len ;i++) buf[i]=buf[i+off];

  off=0;
 }

void PrintCharBuf::push(Char ch)
 {
  if( !out )
    {
     overflow=true;
    }
  else
    {
     *out=ch;

     ++out;
    }
 }

void PrintCharBuf::push()
 {
  const char *name="CCore::PrintCharBuf::push()";

  while( len )
    {
     char ch=buf[off];

     unsigned delta=Utf8Len(ch);

     if( delta==0 ) GuardUtf8Broken(name);

     if( delta>len ) break;

     switch( delta )
       {
        case 1 : push(Utf8Code::ToUnicode(ch)); break;

        case 2 :
         {
          char b2=buf[off+1];

          if( !Utf8Ext(b2) ) GuardUtf8Broken(name);

          push(Utf8Code::ToUnicode(ch,b2));
         }
        break;

        case 3 :
         {
          char b2=buf[off+1];
          char b3=buf[off+2];

          if( !Utf8Ext(b2) || !Utf8Ext(b3) ) GuardUtf8Broken(name);

          push(Utf8Code::ToUnicode(ch,b2,b3));
         }
        break;

        case 4 :
         {
          char b2=buf[off+1];
          char b3=buf[off+2];
          char b4=buf[off+3];

          if( !Utf8Ext(b2) || !Utf8Ext(b3) || !Utf8Ext(b4) ) GuardUtf8Broken(name);

          push(Utf8Code::ToUnicode(ch,b2,b3,b4));
         }
        break;
       }

     off+=delta;
     len-=delta;
    }

  shift();
 }

PtrLen<char> PrintCharBuf::do_provide(ulen)
 {
  return Range(buf).part(off+len);
 }

void PrintCharBuf::do_flush(char *,ulen len_)
 {
  len+=len_;

  push();
 }

PrintCharBuf::PrintCharBuf(PtrLen<Char> out_)
 : start(out_),out(out_)
 {
 }

PrintCharBuf::~PrintCharBuf()
 {
 }

PtrLen<const Char> PrintCharBuf::close(bool guard_overflow)
 {
  flush();

  if( guard_overflow && overflow )
    {
     Printf(Exception,"CCore::PrintCharBuf::close(true) : overflow");
    }

  return start.prefix(out);
 }

#else

PtrLen<char> PrintCharBuf::do_provide(ulen)
 {
  return out;
 }

void PrintCharBuf::do_flush(char *,ulen len)
 {
  out+=len;
 }

PrintCharBuf::PrintCharBuf(PtrLen<Char> out_)
 : start(out_),out(out_)
 {
 }

PrintCharBuf::~PrintCharBuf()
 {
 }

PtrLen<const Char> PrintCharBuf::close(bool guard_overflow)
 {
  flush();

  if( guard_overflow && getOverflowFlag() )
    {
     Printf(Exception,"CCore::PrintCharBuf::close(true) : overflow");
    }

  return start.prefix(out);
 }

#endif

/* class ScanCharString */

#ifdef CCORE_UTF8

ulen ScanCharString::Put(PtrLen<char> out,PtrLen<const Char> &str)
 {
  ulen start=out.len;

  while( +str && out.len>=4 )
    {
     Utf8Code code=ToUtf8(*str);

     code.getRange().copyTo(out.ptr);

     out+=code.getLen();

     ++str;
    }

  return start-out.len;
 }

PtrLen<const char> ScanCharString::underflow()
 {
  ulen len=Put(Range(buf),str);

  return Range(buf,len);
 }

ScanCharString::ScanCharString(PtrLen<const Char> str_)
 : str(str_)
 {
  pump();
 }

ScanCharString::~ScanCharString()
 {
 }

#endif

} // namespace CCore

