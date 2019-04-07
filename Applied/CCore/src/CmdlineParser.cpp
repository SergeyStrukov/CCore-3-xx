/* CmdlineParser.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/CmdlineParser.h>

#include <CCore/inc/Scanf.h>
#include <CCore/inc/ScanRange.h>

namespace CCore {

/* class CmdlineParser */

struct CmdlineParser::ScanSpace : ScanStr
 {
  explicit ScanSpace(StrLen text) : ScanStr(text, [] (char ch) { return CharIsSpace(ch); } ) {}
 };

struct CmdlineParser::ScanFrame
 {
  StrLen before;
  StrLen next;

  explicit ScanFrame(StrLen text)
   {
    StrLen start=text;

    for(; +text ;++text)
      {
       switch( *text )
         {
          case '\\' :
           {
            if( text.len>=2 ) ++text;
           }
          break;

          case '"' :
           {
            before=start.prefix(next);
            next=text;

            return;
           }
          break;
         }
      }

    before=start;
    next=Empty;
   }
 };

PtrLen<char> CmdlineParser::ArgBuilder::operator () (char *buf) const
 {
  if( bsproc )
    {
     char *start=buf;

     for(StrLen t=text; +t ;++t)
       {
        switch( char ch=*t )
          {
           case '\\' :
            {
             if( t.len>=2 )
               {
                ++t;

                switch( char ch=*t )
                  {
                   case '\\' :
                   case '"' :
                    {
                     *(buf++)=ch;
                    }
                   break;

                   default:
                    {
                     *(buf++)='\\';
                     *(buf++)=ch;
                    }
                  }
               }
            }
           break;

           default:
            {
             *(buf++)=ch;
            }
          }
       }

     return Range(start,buf);
    }
  else
    {
     text.copyTo(buf);

     return Range(buf,text.len);
    }
 }

auto CmdlineParser::next() -> ArgBuilder
 {
  SkipSpace(text);

  if( !text ) return {};

  switch( *text )
    {
     case '"' :
      {
       ++text;

       ScanFrame scan(text);

       text=scan.next;

       if( +text ) ++text;

       return {scan.before,true};
      }
     break;

     case '\'' :
      {
       ++text;

       ScanStr scan(text,'\'');

       text=scan.next;

       if( +text ) ++text;

       return scan.before;
      }
     break;

     default:
      {
       ScanSpace scan(text);

       text=scan.next;

       return scan.before;
      }
    }
 }

} // namespace CCore

