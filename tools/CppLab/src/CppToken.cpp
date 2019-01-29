/* CppToken.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CppLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/CppToken.h>

#include <CCore/inc/ForLoop.h>

namespace App {

/* class SrcCursor */

void SrcCursor::nextSym()
 {
  struct Ret
   {
    Unicode code;
    unsigned len;

    Ret(char) { code=SrcChar::Broken; len=1; }

    Ret(char,Unicode ch) { code=ch; len=1; }

    Ret(char,char,Unicode ch) { code=ch; len=2; }

    Ret(char,char,char,Unicode ch) { code=ch; len=3; }

    Ret(char,char,char,char,Unicode ch) { code=ch; len=4; }
   };

  Ret ret=PeekUtf8_gen<Ret>(text);

  cur.code=ret.code;

  text+=ret.len;
 }

void SrcCursor::next()
 {
  if( +text )
    {
     bool new_line = ( cur.code == '\n' ) ;

     nextSym();

     if( cur.code=='\r' )
       {
        if( +text && *text=='\n' ) ++text;

        cur.code='\n';

        cur.pos++;
       }
     else if( cur.code=='\n' )
       {
        cur.pos++;
       }
     else
       {
        if( new_line )
          {
           cur.line++;
           cur.pos=1;
          }
        else
          {
           cur.pos++;
          }
       }
    }
  else
    {
     if( cur.pos!=0 && cur.code!='\n' )
       {
        cur.code='\n';
        cur.pos++;
       }
     else
       {
        cur.code=SrcChar::Eof;
       }
    }
 }

SrcCursor::SrcCursor(StrLen text_)
 {
  text=text_;

  cur.line=1;
  cur.pos=0;
  cur.code=0;

  next();
 }

void SrcCursor::operator ++ ()
 {
  if( +cur )
    {
     next();
    }
 }

/* struct TokChar */

TokFlags TokChar::Flags(Unicode ch) // TODO
 {
  return TokNull;
 }

/* class TokCursor */

bool TokCursor::provide()
 {
  if( off>=lim )
    {
     off=0;

     if( +src )
       {
        buf[0]=*src;

        ++src;

        lim=1;
       }
     else
       {
        lim=0;
       }
    }

  return off<lim;
 }

bool TokCursor::provide(unsigned count) // TODO
 {
  if( unsigned len=lim-off; len<count )
    {
     if( Len-off<count )
       {
        for(unsigned i : IndLim() ) buf[i]=buf[i+off];
       }


    }

  return lim-off>=count;
 }

void TokCursor::setFlags(unsigned count,TokFlags flags)
 {
  for(unsigned i : IndLim(count) ) buf[off+i].flags|=flags;
 }

bool TokCursor::testHex(unsigned base,unsigned len) const
 {
  for(unsigned i : IndLim(base,base+len) ) if( !(buf[off+i].flags&TokHex) ) return false;

  return true;
 }

void TokCursor::next()
 {
  // \EOL
  // \uHHHH
  // \UHHHHHHHH

  if( provide() )
    {
     if( buf[off].is('\\') && provide(2) )
       {
        if( buf[off+1].is('\n') )
          {
           setFlags(2,TokDel);
          }
        else if( buf[off+1].is('u') )
          {
           if( provide(6) && testHex(2,4) )
             {
              setFlags(6,TokU4);
             }
          }
        else if( buf[off+1].is('U') )
          {
           if( provide(10) && testHex(2,8) )
             {
              setFlags(10,TokU8);
             }
          }
       }
    }
 }

TokCursor::TokCursor(StrLen text)
 : src(text)
 {
  next();
 }

void TokCursor::operator ++ ()
 {
  off++;

  next();
 }

} // namespace App

