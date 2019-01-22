/* PastData.h */
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

#ifndef PastData_h
#define PastData_h

#include <inc/BookLab.h>

namespace App {

/* classes */

class PastData;

/* class PastData */

class PastData : public Funchor
 {
  public:

   struct Span
    {
     String body;
     String format;
     String ref;

     BookLab::Span build() const
      {
       BookLab::Span ret;

       ret.body=body;
       ret.format.name=format;
       ret.ref.name=ref;

       return ret;
      }
    };

   struct Line
    {
     DynArray<Span> list;

     BookLab::TextLine build() const
      {
       BookLab::TextLine ret;

       extend(ret);

       return ret;
      }

     void extend(BookLab::TextLine &line) const
      {
       ulen len=list.getLen();

       auto r=line.list.extend_default(len);

       for(ulen i : IndLim(len) ) r[i]=list[i].build();
      }
    };

   DynArray<Line> list;

   PastData() {}

   ~PastData() {}

   bool operator ! () const { return !list.getLen(); }

   bool isSimple() const { return list.getLen()==1 && list[0].list.getLen()==1 ; }

   StrLen getSimple() const { return Range(list[0].list[0].body); }

   Function<void (StrLen)> function_load() { return FunctionOf(this,&PastData::load); }

  private:

   static bool ParseChar(StrLen &text,char ch);

   static bool ParseString(StrLen &text,String &ret);

   static bool ParseSpan(StrLen &text,Span &ret);

   static bool ParseSpan(StrLen &text,Collector<Span> &buf);

   static bool ParseLine(StrLen &text,Line &ret);

   static bool ParseLine(StrLen &text,Collector<Line> &buf);

   static bool ParseCombo(StrLen text,Collector<Line> &buf);

   bool parseCombo(StrLen text);

   static void ParseSimpleLine(StrLen text,Collector<Span> &buf);

   static void ParseSimpleLine(StrLen text,Line &ret);

   static void ParseSimple(StrLen text,Collector<Line> &buf);

   void parseSimple(StrLen text);

   void load(StrLen text);
 };

} // namespace App

#endif
