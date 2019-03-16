/* PrintPage.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/PrintPage.h>

namespace App {

/* class TransformInput */

PrintFile TransformInput::Log("amplog.txt");

void TransformInput::finish()
 {
  if( len )
    {
     out.put(buf,len);

     Log.put(buf,len);

     Putobj(Log,"`\n"_c);

     len=0;
    }
 }

void TransformInput::amp()
 {
  StrLen text(buf+1,len-1);

  len=0;

  if( text.equal("lt"_c) )
    {
     out.put('<');

     return;
    }

  if( text.equal("gt"_c) )
    {
     out.put('>');

     return;
    }

  if( text.equal("amp"_c) )
    {
     out.put('&');

     return;
    }

  if( text.equal("mdash"_c) )
    {
     Putobj(out,"—"_c);

     return;
    }

  if( text.equal("minus"_c) )
    {
     Putobj(out,"−"_c);

     return;
    }

  if( text.equal("pi"_c) )
    {
     Putobj(out,"π"_c);

     return;
    }

  out.put('&');

  Putobj(out,text);

  out.put(';');

  Printf(Log,"&#;;\n",text);
 }

void TransformInput::put(char ch)
 {
  if( len )
    {
     if( CharIsSpecial(ch) )
       {
        finish();

        out.put(ch);
       }
     else if( ch=='&' )
       {
        finish();

        buf[len++]=ch;
       }
     else if( ch==';' )
       {
        amp();
       }
     else if( len>=Len )
       {
        finish();

        out.put(ch);
       }
     else
       {
        buf[len++]=ch;
       }
    }
  else
    {
     if( ch=='&' )
       {
        buf[len++]=ch;
       }
     else
       {
        out.put(ch);
       }
    }
 }

String TransformInput::close()
 {
  finish();

  return out.close();
 }

} // namespace App




