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

} // namespace App

