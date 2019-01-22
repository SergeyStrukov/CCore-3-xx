/* PastData.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/PastData.h>

#include <CCore/inc/CharProp.h>

namespace App {

/* class PastData */

bool PastData::ParseChar(StrLen &text,char ch)
 {
  if( !text || *text!=ch ) return false;

  ++text;

  return true;
 }

bool PastData::ParseString(StrLen &text,String &ret)
 {
  PrintString out;

  if( !ParseChar(text,'"') ) return false;

  while( +text )
    {
     char ch=*text;

     ++text;

     if( ch=='\\' )
       {
        if( !text ) return false;

        ch=*text;

        ++text;

        out.put(ch);
       }
     else if( ch=='"' )
       {
        ret=out.close();

        return true;
       }
     else
       {
        out.put(ch);
       }
    }

  return false;
 }

bool PastData::ParseSpan(StrLen &text,Span &ret)
 {
  if( !ParseChar(text,'{') ) return false;

  if( !ParseString(text,ret.body) ) return false;

  if( !ParseChar(text,',') ) return false;

  if( !ParseString(text,ret.format) ) return false;

  if( !ParseChar(text,',') ) return false;

  if( !ParseString(text,ret.ref) ) return false;

  if( !ParseChar(text,'}') ) return false;

  return true;
 }

bool PastData::ParseSpan(StrLen &text,Collector<Span> &buf)
 {
  Span obj;

  if( !ParseSpan(text,obj) ) return false;

  buf.append_fill(std::move(obj));

  return true;
 }

bool PastData::ParseLine(StrLen &text,Line &ret)
 {
  if( !ParseChar(text,'{') ) return false;

  if( !text ) return false;

  if( *text=='}' )
    {
     ++text;

     return true;
    }

  Collector<Span> buf;

  if( !ParseSpan(text,buf) ) return false;

  while( +text )
    {
     char ch=*text;

     if( ch=='}' )
       {
        ++text;

        buf.extractTo(ret.list);

        return true;
       }
     else if( ch==',' )
       {
        ++text;

        if( !ParseSpan(text,buf) ) return false;
       }
     else
       {
        return false;
       }
    }

  return false;
 }

bool PastData::ParseLine(StrLen &text,Collector<Line> &buf)
 {
  Line obj;

  if( !ParseLine(text,obj) ) return false;

  buf.append_fill(std::move(obj));

  return true;
 }

bool PastData::ParseCombo(StrLen text,Collector<Line> &buf)
 {
  if( !ParseLine(text,buf) ) return false;

  while( +text )
    {
     char ch=*text;

     if( ch==',' )
       {
        ++text;

        if( !ParseLine(text,buf) ) return false;
       }
     else
       {
        return false;
       }
    }

  return true;
 }

bool PastData::parseCombo(StrLen text)
 {
  if( !text ) return true;

  Collector<Line> buf;

  if( !ParseCombo(text,buf) ) return false;

  buf.extractTo(list);

  return true;
 }

void PastData::ParseSimpleLine(StrLen text,Collector<Span> &buf)
 {
  for(;;)
    {
     SkipSpace(text);

     if( !text ) break;

     StrLen span=text;

     SkipNonSpace(text);

     Span obj;

     obj.body=StrLen(span.prefix(text));

     buf.append_fill(std::move(obj));
    }
 }

void PastData::ParseSimpleLine(StrLen text,Line &ret)
 {
  Collector<Span> buf;

  ParseSimpleLine(text,buf);

  buf.extractTo(ret.list);
 }

void PastData::ParseSimple(StrLen text,Collector<Line> &buf)
 {
  while( +text )
    {
     StrLen line=CutLine(text);

     Line obj;

     ParseSimpleLine(line,obj);

     buf.append_fill(std::move(obj));
    }
 }

void PastData::parseSimple(StrLen text)
 {
  Collector<Line> buf;

  ParseSimple(text,buf);

  buf.extractTo(list);
 }

void PastData::load(StrLen text)
 {
  if( !parseCombo(text) ) parseSimple(text);
 }

} // namespace App

