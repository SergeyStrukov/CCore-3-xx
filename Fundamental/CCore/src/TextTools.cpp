/* TextTools.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/TextTools.h>

namespace CCore {

/* struct TextPos */

void TextPos::update(StrLen text)
 {
  StrLen line=text;

  while( +text )
    {
     char ch=*text;

     if( ch=='\r' || ch=='\n' )
       {
        ++text;

        if( ch=='\r' && +text && *text=='\n' ) ++text;

        line=text;

        nextLine();
       }
     else
       {
        ++text;
       }
    }

  update(SymLen(line));
 }

/* class TextPosCounter */

void TextPosCounter::put(char ch)
 {
  if( ch=='\r' )
    {
     if( flag )
       {
        pos.nextLine();
       }
     else
       {
        flag=true;
       }
    }
  else if( ch=='\n' )
    {
     pos.nextLine();
     det.reset();

     flag=false;
    }
  else
    {
     if( flag )
       {
        pos.nextLine();
        det.reset();

        flag=false;
       }

     if( det.put(ch) ) pos.nextPos();
    }
 }

} // namespace CCore


