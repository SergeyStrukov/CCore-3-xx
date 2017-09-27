/* TextTools.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_TextTools_h
#define CCore_inc_TextTools_h

#include <CCore/inc/CharProp.h>
#include <CCore/inc/SymCount.h>
#include <CCore/inc/Symbol.h>

namespace CCore {

/* functions */

bool CharIsEOL(OneOfTypes<char,Char> ch) { return ch=='\r' || ch=='\n' ; }

bool CharIsBin(OneOfTypes<char,Char> ch) { return ch=='0' || ch=='1' ; }

bool CharIsDec(OneOfTypes<char,Char> ch) { return ch>='0' && ch<='9' ; }

bool CharIsHex(OneOfTypes<char,Char> ch) { return CharHexValue(ch)>=0; }

int CharBinValue(OneOfTypes<char,Char> ch) { if( ch>='0' && ch<='1' ) return ch-'0'; return -1; }

/* AllChars() */

void AllChars(FuncArgType<char> func)
 {
  for(int i=-128; i<128 ;i++)
    {
     char ch=char(i);

     func(ch);
    }
 }

/* classes */

struct TextPos;

class TextPosCounter;

template <class CharClass,CharClass DefaultClass> class CharPropTable;

/* struct TextPos */

struct TextPos
 {
  ulen line;
  ulen col;

  TextPos() : line(1),col(1) {}

  void nextPos() { col++; }

  void nextLine() { col=1; line++; }

  void update(ulen len) { col+=len; }

  void update(StrLen text); // must not break "\r\n"

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"(line=#;,col=#;)",line,col);
   }
 };

/* class TextPosCounter */

class TextPosCounter : NoCopy
 {
   TextPos pos;
   SymDetector det;
   bool flag = false ;

  public:

   TextPosCounter() {}

   operator TextPos() const { return pos; }

   void reset() { pos={}; det.reset(); flag=false; }

   void put(char ch);

   void put(char ch,ulen len)
    {
     for(; len ;len--) put(ch);
    }

   void put(const char *str,ulen len)
    {
     for(; len ;len--,str++) put(*str);
    }
 };

/* class CharPropTable<CharClass,CharClass DefaultClass> */

template <class CharClass,CharClass DefaultClass>
class CharPropTable : NoCopy
 {
   CharClass table[256];

  private:

   static uint8 Index(char ch) { return uint8(ch); }

  protected:

   void set(char ch,CharClass cc)
    {
     table[Index(ch)]=cc;
    }

   void setSet(const char *zstr,CharClass cc)
    {
     for(; char ch=*zstr ;zstr++) set(ch,cc);
    }

   void setIf(FuncType<bool,char> cond,CharClass cc)
    {
     AllChars( [this,cond,cc] (char ch) { if( cond(ch) ) set(ch,cc); } );
    }

  public:

   CharPropTable() { Range(table).set(DefaultClass); }

   CharClass operator [] (char ch) const { return table[Index(ch)]; }
 };

} // namespace CCore

#endif


