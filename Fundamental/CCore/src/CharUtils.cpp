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

#ifdef CCORE_UTF8

/* struct FillCharBuf */

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

/* class PrintCharBuf */

void PrintCharBuf::shift()
 {
  if( off==0 ) return;

  for(unsigned i=0; i<len ;i++) buf[i]=buf[i+off];

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

  StrLen text=Range(buf+off,len);

  while( +text )
    {
     char ch=*text;

     unsigned delta=Utf8Len(ch);

     if( delta==0 ) GuardUtf8Broken(name);

     if( delta>text.len ) break;

     for(unsigned i=1; i<delta ;i++) if( !Utf8Ext(text[i]) ) GuardUtf8Broken(name);

     switch( delta )
       {
        case 1 : push(Utf8Code::ToUnicode(ch)); break;

        case 2 : push(Utf8Code::ToUnicode(ch,text[1])); break;

        case 3 : push(Utf8Code::ToUnicode(ch,text[1],text[2])); break;

        case 4 : push(Utf8Code::ToUnicode(ch,text[1],text[2],text[3])); break;
       }

     text+=delta;
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
     Printf(Exception,"");
    }

  return start.prefix(out);
 }

#endif

} // namespace CCore

