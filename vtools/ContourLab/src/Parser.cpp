/* Parser.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Parser.h>

namespace App {

/* class CharProp */

CharProp::CharProp()
 {
  setSet(GetDigitChars(),Char_Digit);
  setSet(GetCLetterChars(),Char_Letter);
  setSet(GetSpaceChars(),Char_Space);

  setSet(".",Char_Dot);

  setSet("()+-*/=,",Char_Punct);
 }

const CharProp CharProp::Object;

/* struct Token */

PtrLen<const Char> Token::getNumber() const
 {
  Char ch=str.back(1);

  if( ch=='p' || ch=='g' ) return str.inner(0,1);

  return str;
 }

/* class Tokenizer */

ulen Tokenizer::ScanLetterDigit(PtrLen<const Char> text)
 {
  ulen len=text.len;

  for(++text; +text && CharIsLetterDigit(*text) ;++text);

  return len-text.len;
 }

ulen Tokenizer::ScanLetterDigitDot(PtrLen<const Char> text)
 {
  ulen len=text.len;

  for(++text; +text && CharIsLetterDigitDot(*text) ;++text);

  return len-text.len;
 }

ulen Tokenizer::ScanSpace(PtrLen<const Char> text)
 {
  ulen len=text.len;

  for(++text; +text && SymCharIsSpace(*text) ;++text);

  return len-text.len;
 }

TokenClass Tokenizer::IsNumber(PtrLen<const Char> text)
 {
  TokenClass ret;

  switch( text.back(1) )
    {
     case 'p' : ret=Token_Length; text.len--; break;

     case 'g' : ret=Token_Angle; text.len--; break;

     default: ret=Token_Number;
    }

  bool has_dot=false;
  bool has_digit=false;

  for(; +text ;++text)
    switch( GetCharClass(*text) )
      {
       case Char_Dot : if( has_dot ) return Token_Other; has_dot=true; break;

       case Char_Digit : has_digit=true; break;

       default: return Token_Other;
      }

  return has_digit?ret:Token_Other;
 }

Token Tokenizer::cut(TokenClass tc,ulen len)
 {
  Token ret(tc,pos,text+=len);

  pos+=len;

  return ret;
 }

Token Tokenizer::next_number()
 {
  ulen len=ScanLetterDigitDot(text);

  return cut(IsNumber(text.prefix(len)),len);
 }

Token Tokenizer::next_word()
 {
  return cut(Token_Word,ScanLetterDigit(text));
 }

Token Tokenizer::next_punct()
 {
  return cut(Token_Punct,1);
 }

Token Tokenizer::next_space()
 {
  return cut(Token_Space,ScanSpace(text));
 }

Token Tokenizer::next_other()
 {
  return cut(Token_Other,1);
 }

Token Tokenizer::next()
 {
  switch( GetCharClass(*text) )
    {
     case Char_Dot :
     case Char_Digit  : return next_number();

     case Char_Letter : return next_word();

     case Char_Punct  : return next_punct();

     case Char_Space  : return next_space();

     case Char_Other  : return next_other();
    }

  return Token();
 }

/* class ParserBase */

CharAccent ParserBase::Map(TokenClass tc)
 {
  switch( tc )
    {
     case Token_Number : return CharNumber;

     case Token_Length : return CharLength;

     case Token_Angle : return CharAngle;

     case Token_Word : return CharName;

     case Token_Punct : return CharPunct;

     case Token_Space : return CharNormal;

     default: return CharError;
    }
 }

void ParserBase::paint(Token token,CharAccent acc)
 {
  if( accent ) Range(accent+token.pos,token.str.len).set(acc);
 }

void ParserBase::paint(Token token)
 {
  paint(token,Map(token.tc));
 }

void ParserBase::next(Token token)
 {
  paint(token);
 }

void ParserBase::stop()
 {
 }

void ParserBase::run()
 {
  while( +tok ) next(tok.next());

  stop();
 }

/* class PadTextParser */

void PadTextParser::next(Token token)
 {
  paint(token);

  if( state==-1 ) return;

  if( token.is(Token_Space) ) return;

  if( token.is(Token_Other) )
    {
     state=-1;

     return;
    }

  switch( state )
    {
     case 0 :
      {
       if( token.is("angle"_c) ) { state=13; break; }

       if( token.is("len"_c) ) { state=14; break; }

       if( token.is("point"_c) ) { state=12; break; }

       if( token.is("ratio"_c) ) { state=15; break; }

       if( token.is(Token_Word) ) { name=token; state=1; break; }

       paintError(token);
      }
     break;

     case 1 :
      {
       if( token.is('(') ) { state=20; break; }

       if( token.is('=') ) { state=9; break; }

       paintError(token);
      }
     break;

     case 2 :
      {
       if( token.is(')') ) { state=22; break; }

       paintError(token);
      }
     break;

     case 3 :
      {
       if( token.is(')') ) { state=23; break; }

       paintError(token);
      }
     break;

     case 4 :
      {
       if( token.is(',') ) { state=17; break; }

       paintError(token);
      }
     break;

     case 5 :
      {
       if( token.is(',') ) { state=18; break; }

       paintError(token);
      }
     break;

     case 6 :
      {
       if( token.is('=') ) { state=10; break; }

       paintError(token);
      }
     break;

     case 7 :
      {
       if( token.is('=') ) { state=11; break; }

       paintError(token);
      }
     break;

     case 8 :
      {
       if( token.is('=') ) { state=21; break; }

       paintError(token);
      }
     break;

     case 9 :
      {
       if( token.is(Token_Angle) ) { value=token; state=29; break; }

       if( token.is(Token_Length) ) { value=token; state=26; break; }

       if( token.is(Token_Number) ) { value=token; state=31; break; }

       paintError(token);
      }
     break;

     case 10 :
      {
       if( token.is(Token_Angle) ) { value=token; state=28; break; }

       if( token.is(Token_Number) ) { value=token; state=27; break; }

       paintError(token);
      }
     break;

     case 11 :
      {
       if( token.is(Token_Length) ) { value=token; state=25; break; }

       if( token.is(Token_Number) ) { value=token; state=24; break; }

       paintError(token);
      }
     break;

     case 12 :
      {
       if( token.isName() ) { name=token; state=16; break; }

       paintError(token);
      }
     break;

     case 13 :
      {
       if( token.isName() ) { name=token; state=6; break; }

       paintError(token);
      }
     break;

     case 14 :
      {
       if( token.isName() ) { name=token; state=7; break; }

       paintError(token);
      }
     break;

     case 15 :
      {
       if( token.isName() ) { name=token; state=8; break; }

       paintError(token);
      }
     break;

     case 16 :
      {
       if( token.is('(') ) { state=19; break; }

       paintError(token);
      }
     break;

     case 17 :
      {
       if( token.is(Token_Number) ) { value2=token; state=2; break; }

       paintError(token);
      }
     break;

     case 18 :
      {
       if( token.is(Token_Number) ) { value2=token; state=3; break; }

       paintError(token);
      }
     break;

     case 19 :
      {
       if( token.is(Token_Number) ) { value=token; state=4; break; }

       paintError(token);
      }
     break;

     case 20 :
      {
       if( token.is(Token_Number) ) { value=token; state=5; break; }

       paintError(token);
      }
     break;

     case 21 :
      {
       if( token.is(Token_Number) ) { value=token; state=30; break; }

       paintError(token);
      }
     break;

     default:
      {
       paintError(token);
      }
    }
 }

void PadTextParser::stop()
 {
  if( state==-1 ) return;

  switch( state )
    {
     case 22 :
     case 23 :

      if( !point(name.str,value.getNumber(),value2.getNumber()) ) paintError(name);

     break;

     case 24 :
     case 25 :
     case 26 :

      if( !length(name.str,value.getNumber()) ) paintError(name);

     break;

     case 27 :
     case 28 :
     case 29 :

      if( !angle(name.str,value.getNumber()) ) paintError(name);

     break;

     case 30 :
     case 31 :

      if( !ratio(name.str,value.getNumber()) ) paintError(name);

     break;

     default: state=-1;
    }
 }

bool PadTextParser::point(PtrLen<const Char>,PtrLen<const Char>,PtrLen<const Char>) { return true; }

bool PadTextParser::length(PtrLen<const Char>,PtrLen<const Char>) { return true; }

bool PadTextParser::angle(PtrLen<const Char>,PtrLen<const Char>) { return true; }

bool PadTextParser::ratio(PtrLen<const Char>,PtrLen<const Char>) { return true; }

/* class Atom */

Atom::Atom(const Token &token)
 : Token(token),
   ac(AtomNull)
 {
  switch( tc )
    {
     case Token_Number : ac=Atom_Number; break;

     case Token_Length : ac=Atom_Length; break;

     case Token_Angle : ac=Atom_Angle; break;

     case Token_Word : ac=Atom_Name; break;

     case Token_Punct :
      {
       switch( str[0] )
         {
          case '(' : ac=Atom_obr; break;

          case ')' : ac=Atom_cbr; break;

          case '+' : ac=Atom_plus; break;

          case '-' : ac=Atom_minus; break;

          case '*' : ac=Atom_asterisk; break;

          case '/' : ac=Atom_div; break;

          case ',' : ac=Atom_comma; break;

          case '=' : ac=Atom_assign; break;
         }
      }
     break;
    }
 }

/* class FormulaTextParser<Context> */

#if 0

struct Context
 {
  using ExprType = int ;

  bool set(PtrLen<const Char> name,ExprType value);

  bool add(ExprType &ret,ExprType a,ExprType b);

  bool sub(ExprType &ret,ExprType a,ExprType b);

  bool mul(ExprType &ret,ExprType a,ExprType b);

  bool div(ExprType &ret,ExprType a,ExprType b);

  bool neg(ExprType &ret,ExprType a);

  bool func(ExprType &ret,PtrLen<const Char> name,PtrLen<const ExprType> list);

  bool arg(ExprType &ret,PtrLen<const Char> name);

  bool number(ExprType &ret,PtrLen<const Char> number);

  bool angle(ExprType &ret,PtrLen<const Char> number);

  bool length(ExprType &ret,PtrLen<const Char> number);

  bool point(ExprType &ret,PtrLen<const Char> number_x,PtrLen<const Char> number_y);
 };

bool inner_test()
 {
  Context ctx;

  FormulaTextParser<Context> parser(ctx,{});

  parser.run();

  return parser;
 }

#endif

} // namespace App

