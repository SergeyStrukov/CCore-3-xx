/* CppText.cpp */
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

#include <inc/CppText.h>

namespace App {
namespace CppText {

/* class FlagTable */

FlagTable FlagTable::Object;

void FlagTable::set(const char *zstr,CharFlags flags)
 {
  for(; char ch=*zstr ;++zstr) set(ch,flags);
 }

FlagTable::FlagTable()
 {
  Range(table).set(CharNull);

  set("abcdefghijklmnopqrstuvwxyz",CharLetter);
  set("ABCDEFGHIJKLMNOPQRSTUVWXYZ_",CharLetter);
  set("0123456789",CharDigit);
  set("{}[]()#;:?.,+-*/%^&|~!=<>",CharPunct);
  set("\"'",CharQuote);
  set(" \t\v\f",CharSpace);
  set("\r\n",CharEOL);

  set("0123456789abcdefABCDEF",CharHex);
  set("01234567",CharOct);

  set("+-*/%^&|<>=!",CharPunct2);
  set("&|<>+-:#",CharPunct3);
 }

CharFlags FlagTable::operator [] (unsigned char ch) const
 {
  if( ch>=DimOf(table) ) return CharNull;

  return table[ch];
 }

/* class Tokenizer */

StrLen Tokenizer::ScanId(StrLen text)
 {
  ++text;

  while( +text && FlagChar(*text).test(CharLetter|CharDigit) ) ++text;

  return text;
 }

StrLen Tokenizer::ScanNumber(StrLen text)
 {
  if( *text=='.' )
    text+=2;
  else
    ++text;

  while( +text )
    {
     switch( char ch=*text )
       {
        case '.' : ++text; break;

        case 'e' : case 'E' : case 'p' : case 'P' :
         {
          if( text.len>=2 && IsSign(text[1]) )
            text+=2;
          else
            ++text;
         }
        break;

        case '\'' :
         {
          if( text.len>=2 && FlagChar(text[1]).test(CharLetter|CharDigit) )
            text+=2;
          else
            return text;
         }
        break;

        default:
         {
          if( FlagChar(ch).test(CharLetter|CharDigit) )
            {
             ++text;
            }
          else
            {
             return text;
            }
         }
       }
    }

  return text;
 }

StrLen Tokenizer::ScanOp(StrLen text)
 {
  //
  // { } [ ] ( ) #
  // ; : ? . , + - * / % ^ & | ~ ! = < >
  //

  if( text.len==1 ) return text.part(1);

  char ch=text[0];

  //
  // += -= *= /= %= ^= &= |= <= >= == !=
  //

  if( text[1]=='=' )
    {
     if( FlagChar(ch).test(CharPunct2) )
       return text.part(2);
     else
       return text.part(1);
    }

  //
  // .* ->
  //
  // ... ->*
  //

  switch( ch )
    {
     case '.' :
      {
       switch( text[1] )
         {
          case '*' :
           {
            return text.part(2);
           }
          break;

          case '.' :
           {
            if( text.len>=3 && text[2]=='.' ) return text.part(3);
           }
          break;
         }

       return text.part(1);
      }
     break;

     case '-' :
      {
       if( text[1]=='>' )
         {
          if( text.len>=3 && text[2]=='*' )
            return text.part(3);
          else
            return text.part(2);
         }

       return text.part(1);
      }
     break;
    }

  //
  // && || << >> ++ -- :: ##
  //
  // <<= >>=
  //

  if( text[1]==ch )
    {
     if( FlagChar(ch).test(CharPunct3) )
       {
        if( text.len>=3 && text[2]=='=' && ( ch=='<' || ch=='>' ) )
          return text.part(3);
        else
          return text.part(2);
       }
    }

  return text.part(1);
 }

StrLen Tokenizer::ScanEscape(StrLen text)
 {
  if( !text ) return text;

  char ch=*text;

  ++text;

  if( ch=='x' )
    {
     while( +text && FlagChar(*text).test(CharHex) ) ++text;
    }
  else if( FlagChar(ch).test(CharOct) )
    {
     unsigned count=2;

     while( count && +text && FlagChar(*text).test(CharOct) ) ++text,count--;
    }

  return text;
 }

StrLen Tokenizer::ScanChar(StrLen text)
 {
  ++text;

  while( +text )
    {
     switch( *text )
       {
        case '\'' :
         {
          ++text;

          return text;
         }
        break;

        case '\\' :
         {
          ++text;

          text=ScanEscape(text);
         }
        break;

        case '\r' : case '\n' :
         {
          return text;
         }
        break;

        default:
         {
          ++text;
         }
       }
    }

  return text;
 }

StrLen Tokenizer::ScanString(StrLen text)
 {
  ++text;

  while( +text )
    {
     switch( *text )
       {
        case '"' :
         {
          ++text;

          return text;
         }
        break;

        case '\\' :
         {
          ++text;

          text=ScanEscape(text);
         }
        break;

        case '\r' : case '\n' :
         {
          return text;
         }
        break;

        default:
         {
          ++text;
         }
       }
    }

  return text;
 }

StrLen Tokenizer::ScanSpace(StrLen text)
 {
  ++text;

  while( +text && FlagChar(*text).test(CharSpace) ) ++text;

  return text;
 }

StrLen Tokenizer::ScanOther(StrLen text)
 {
  ++text;

  const CharFlags flags=CharLetter|CharDigit|CharPunct|CharQuote|CharSpace|CharEOL;

  while( +text && !FlagChar(*text).test(flags) ) ++text;

  return text;
 }

bool Tokenizer::TestKeyword(StrLen str)
 {
  if( !str ) return false;

  switch( str[0] )
    {
     case 'a' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'l' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'i' :
                {
                 ++str;

                 if( !str ) return false;

                 switch( str[0] )
                   {
                    case 'g' :
                     {
                      ++str;

                      if( !str ) return false;

                      switch( str[0] )
                        {
                         case 'n' :
                          {
                           ++str;

                           if( !str ) return false;

                           switch( str[0] )
                             {
                              case 'a' :
                               {
                                ++str;

                                if( str.len==1 && str[0]=='s' ) return true; else return false;
                               }

                              case 'o' :
                               {
                                ++str;

                                if( str.len==1 && str[0]=='f' ) return true; else return false;
                               }

                              default: return false;
                             }
                          }

                         default: return false;
                        }
                     }

                    default: return false;
                   }
                }

               default: return false;
              }
           }

          case 's' :
           {
            ++str;

            if( str.len==1 && str[0]=='m' ) return true; else return false;
           }

          case 'u' :
           {
            ++str;

            if( str.len==2 && str[0]=='t' && str[1]=='o' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'b' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'o' :
           {
            ++str;

            if( str.len==2 && str[0]=='o' && str[1]=='l' ) return true; else return false;
           }

          case 'r' :
           {
            ++str;

            if( str.len==3 && str[0]=='e' && str[1]=='a' && str[2]=='k' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'c' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'a' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 's' :
                {
                 ++str;

                 if( str.len==1 && str[0]=='e' ) return true; else return false;
                }

               case 't' :
                {
                 ++str;

                 if( str.len==2 && str[0]=='c' && str[1]=='h' ) return true; else return false;
                }

               default: return false;
              }
           }

          case 'h' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'a' :
                {
                 ++str;

                 if( !str ) return false;

                 switch( str[0] )
                   {
                    case 'r' :
                     {
                      ++str;

                      if( !str ) return true;

                      switch( str[0] )
                        {
                         case '1' :
                          {
                           ++str;

                           if( str.len==3 && str[0]=='6' && str[1]=='_' && str[2]=='t' ) return true; else return false;
                          }

                         case '3' :
                          {
                           ++str;

                           if( str.len==3 && str[0]=='2' && str[1]=='_' && str[2]=='t' ) return true; else return false;
                          }

                         default: return false;
                        }
                     }

                    default: return false;
                   }
                }

               default: return false;
              }
           }

          case 'l' :
           {
            ++str;

            if( str.len==3 && str[0]=='a' && str[1]=='s' && str[2]=='s' ) return true; else return false;
           }

          case 'o' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'n' :
                {
                 ++str;

                 if( !str ) return false;

                 switch( str[0] )
                   {
                    case 's' :
                     {
                      ++str;

                      if( !str ) return false;

                      switch( str[0] )
                        {
                         case 't' :
                          {
                           ++str;

                           if( !str ) return true;

                           switch( str[0] )
                             {
                              case '_' :
                               {
                                ++str;

                                if( str.len==4 && str[0]=='c' && str[1]=='a' && str[2]=='s' && str[3]=='t' ) return true; else return false;
                               }

                              case 'e' :
                               {
                                ++str;

                                if( str.len==3 && str[0]=='x' && str[1]=='p' && str[2]=='r' ) return true; else return false;
                               }

                              default: return false;
                             }
                          }

                         default: return false;
                        }
                     }

                    case 't' :
                     {
                      ++str;

                      if( str.len==4 && str[0]=='i' && str[1]=='n' && str[2]=='u' && str[3]=='e' ) return true; else return false;
                     }

                    default: return false;
                   }
                }

               default: return false;
              }
           }

          default: return false;
         }
      }

     case 'd' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'e' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'c' :
                {
                 ++str;

                 if( str.len==5 && str[0]=='l' && str[1]=='t' && str[2]=='y' && str[3]=='p' && str[4]=='e' ) return true; else return false;
                }

               case 'f' :
                {
                 ++str;

                 if( str.len==4 && str[0]=='a' && str[1]=='u' && str[2]=='l' && str[3]=='t' ) return true; else return false;
                }

               case 'l' :
                {
                 ++str;

                 if( str.len==3 && str[0]=='e' && str[1]=='t' && str[2]=='e' ) return true; else return false;
                }

               default: return false;
              }
           }

          case 'o' :
           {
            ++str;

            if( !str ) return true;

            switch( str[0] )
              {
               case 'u' :
                {
                 ++str;

                 if( str.len==3 && str[0]=='b' && str[1]=='l' && str[2]=='e' ) return true; else return false;
                }

               default: return false;
              }
           }

          case 'y' :
           {
            ++str;

            if( str.len==10 && str[0]=='n' && str[1]=='a' && str[2]=='m' && str[3]=='i' && str[4]=='c' && str[5]=='_' && str[6]=='c' && str[7]=='a' && str[8]=='s' && str[9]=='t' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'e' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'l' :
           {
            ++str;

            if( str.len==2 && str[0]=='s' && str[1]=='e' ) return true; else return false;
           }

          case 'n' :
           {
            ++str;

            if( str.len==2 && str[0]=='u' && str[1]=='m' ) return true; else return false;
           }

          case 'x' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'p' :
                {
                 ++str;

                 if( !str ) return false;

                 switch( str[0] )
                   {
                    case 'l' :
                     {
                      ++str;

                      if( str.len==4 && str[0]=='i' && str[1]=='c' && str[2]=='i' && str[3]=='t' ) return true; else return false;
                     }

                    case 'o' :
                     {
                      ++str;

                      if( str.len==2 && str[0]=='r' && str[1]=='t' ) return true; else return false;
                     }

                    default: return false;
                   }
                }

               case 't' :
                {
                 ++str;

                 if( str.len==3 && str[0]=='e' && str[1]=='r' && str[2]=='n' ) return true; else return false;
                }

               default: return false;
              }
           }

          default: return false;
         }
      }

     case 'f' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'a' :
           {
            ++str;

            if( str.len==3 && str[0]=='l' && str[1]=='s' && str[2]=='e' ) return true; else return false;
           }

          case 'i' :
           {
            ++str;

            if( str.len==3 && str[0]=='n' && str[1]=='a' && str[2]=='l' ) return true; else return false;
           }

          case 'l' :
           {
            ++str;

            if( str.len==3 && str[0]=='o' && str[1]=='a' && str[2]=='t' ) return true; else return false;
           }

          case 'o' :
           {
            ++str;

            if( str.len==1 && str[0]=='r' ) return true; else return false;
           }

          case 'r' :
           {
            ++str;

            if( str.len==4 && str[0]=='i' && str[1]=='e' && str[2]=='n' && str[3]=='d' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'g' :
      {
       ++str;

       if( str.len==3 && str[0]=='o' && str[1]=='t' && str[2]=='o' ) return true; else return false;
      }

     case 'i' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'f' :
           {
            ++str;

            if( str.len==0 ) return true; else return false;
           }

          case 'n' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'l' :
                {
                 ++str;

                 if( str.len==3 && str[0]=='i' && str[1]=='n' && str[2]=='e' ) return true; else return false;
                }

               case 't' :
                {
                 ++str;

                 if( str.len==0 ) return true; else return false;
                }

               default: return false;
              }
           }

          default: return false;
         }
      }

     case 'l' :
      {
       ++str;

       if( str.len==3 && str[0]=='o' && str[1]=='n' && str[2]=='g' ) return true; else return false;
      }

     case 'm' :
      {
       ++str;

       if( str.len==6 && str[0]=='u' && str[1]=='t' && str[2]=='a' && str[3]=='b' && str[4]=='l' && str[5]=='e' ) return true; else return false;
      }

     case 'n' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'a' :
           {
            ++str;

            if( str.len==7 && str[0]=='m' && str[1]=='e' && str[2]=='s' && str[3]=='p' && str[4]=='a' && str[5]=='c' && str[6]=='e' ) return true; else return false;
           }

          case 'e' :
           {
            ++str;

            if( str.len==1 && str[0]=='w' ) return true; else return false;
           }

          case 'o' :
           {
            ++str;

            if( str.len==6 && str[0]=='e' && str[1]=='x' && str[2]=='c' && str[3]=='e' && str[4]=='p' && str[5]=='t' ) return true; else return false;
           }

          case 'u' :
           {
            ++str;

            if( str.len==5 && str[0]=='l' && str[1]=='l' && str[2]=='p' && str[3]=='t' && str[4]=='r' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'o' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'p' :
           {
            ++str;

            if( str.len==6 && str[0]=='e' && str[1]=='r' && str[2]=='a' && str[3]=='t' && str[4]=='o' && str[5]=='r' ) return true; else return false;
           }

          case 'v' :
           {
            ++str;

            if( str.len==6 && str[0]=='e' && str[1]=='r' && str[2]=='r' && str[3]=='i' && str[4]=='d' && str[5]=='e' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'p' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'r' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'i' :
                {
                 ++str;

                 if( str.len==4 && str[0]=='v' && str[1]=='a' && str[2]=='t' && str[3]=='e' ) return true; else return false;
                }

               case 'o' :
                {
                 ++str;

                 if( str.len==6 && str[0]=='t' && str[1]=='e' && str[2]=='c' && str[3]=='t' && str[4]=='e' && str[5]=='d' ) return true; else return false;
                }

               default: return false;
              }
           }

          case 'u' :
           {
            ++str;

            if( str.len==4 && str[0]=='b' && str[1]=='l' && str[2]=='i' && str[3]=='c' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'r' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'e' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'g' :
                {
                 ++str;

                 if( str.len==5 && str[0]=='i' && str[1]=='s' && str[2]=='t' && str[3]=='e' && str[4]=='r' ) return true; else return false;
                }

               case 'i' :
                {
                 ++str;

                 if( str.len==13 && str[0]=='n' && str[1]=='t' && str[2]=='e' && str[3]=='r' && str[4]=='p' && str[5]=='r' && str[6]=='e' && str[7]=='t' && str[8]=='_' && str[9]=='c' && str[10]=='a' && str[11]=='s' && str[12]=='t' ) return true; else return false;
                }

               case 't' :
                {
                 ++str;

                 if( str.len==3 && str[0]=='u' && str[1]=='r' && str[2]=='n' ) return true; else return false;
                }

               default: return false;
              }
           }

          default: return false;
         }
      }

     case 's' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'h' :
           {
            ++str;

            if( str.len==3 && str[0]=='o' && str[1]=='r' && str[2]=='t' ) return true; else return false;
           }

          case 'i' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'g' :
                {
                 ++str;

                 if( str.len==3 && str[0]=='n' && str[1]=='e' && str[2]=='d' ) return true; else return false;
                }

               case 'z' :
                {
                 ++str;

                 if( str.len==3 && str[0]=='e' && str[1]=='o' && str[2]=='f' ) return true; else return false;
                }

               default: return false;
              }
           }

          case 't' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'a' :
                {
                 ++str;

                 if( !str ) return false;

                 switch( str[0] )
                   {
                    case 't' :
                     {
                      ++str;

                      if( !str ) return false;

                      switch( str[0] )
                        {
                         case 'i' :
                          {
                           ++str;

                           if( !str ) return false;

                           switch( str[0] )
                             {
                              case 'c' :
                               {
                                ++str;

                                if( !str ) return true;

                                switch( str[0] )
                                  {
                                   case '_' :
                                    {
                                     ++str;

                                     if( !str ) return false;

                                     switch( str[0] )
                                       {
                                        case 'a' :
                                         {
                                          ++str;

                                          if( str.len==5 && str[0]=='s' && str[1]=='s' && str[2]=='e' && str[3]=='r' && str[4]=='t' ) return true; else return false;
                                         }

                                        case 'c' :
                                         {
                                          ++str;

                                          if( str.len==3 && str[0]=='a' && str[1]=='s' && str[2]=='t' ) return true; else return false;
                                         }

                                        default: return false;
                                       }
                                    }

                                   default: return false;
                                  }
                               }

                              default: return false;
                             }
                          }

                         default: return false;
                        }
                     }

                    default: return false;
                   }
                }

               case 'r' :
                {
                 ++str;

                 if( str.len==3 && str[0]=='u' && str[1]=='c' && str[2]=='t' ) return true; else return false;
                }

               default: return false;
              }
           }

          case 'w' :
           {
            ++str;

            if( str.len==4 && str[0]=='i' && str[1]=='t' && str[2]=='c' && str[3]=='h' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 't' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'e' :
           {
            ++str;

            if( str.len==6 && str[0]=='m' && str[1]=='p' && str[2]=='l' && str[3]=='a' && str[4]=='t' && str[5]=='e' ) return true; else return false;
           }

          case 'h' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'i' :
                {
                 ++str;

                 if( str.len==1 && str[0]=='s' ) return true; else return false;
                }

               case 'r' :
                {
                 ++str;

                 if( !str ) return false;

                 switch( str[0] )
                   {
                    case 'e' :
                     {
                      ++str;

                      if( str.len==8 && str[0]=='a' && str[1]=='d' && str[2]=='_' && str[3]=='l' && str[4]=='o' && str[5]=='c' && str[6]=='a' && str[7]=='l' ) return true; else return false;
                     }

                    case 'o' :
                     {
                      ++str;

                      if( str.len==1 && str[0]=='w' ) return true; else return false;
                     }

                    default: return false;
                   }
                }

               default: return false;
              }
           }

          case 'r' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'u' :
                {
                 ++str;

                 if( str.len==1 && str[0]=='e' ) return true; else return false;
                }

               case 'y' :
                {
                 ++str;

                 if( str.len==0 ) return true; else return false;
                }

               default: return false;
              }
           }

          case 'y' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'p' :
                {
                 ++str;

                 if( !str ) return false;

                 switch( str[0] )
                   {
                    case 'e' :
                     {
                      ++str;

                      if( !str ) return false;

                      switch( str[0] )
                        {
                         case 'd' :
                          {
                           ++str;

                           if( str.len==2 && str[0]=='e' && str[1]=='f' ) return true; else return false;
                          }

                         case 'i' :
                          {
                           ++str;

                           if( str.len==1 && str[0]=='d' ) return true; else return false;
                          }

                         case 'n' :
                          {
                           ++str;

                           if( str.len==3 && str[0]=='a' && str[1]=='m' && str[2]=='e' ) return true; else return false;
                          }

                         default: return false;
                        }
                     }

                    default: return false;
                   }
                }

               default: return false;
              }
           }

          default: return false;
         }
      }

     case 'u' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'n' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'i' :
                {
                 ++str;

                 if( str.len==2 && str[0]=='o' && str[1]=='n' ) return true; else return false;
                }

               case 's' :
                {
                 ++str;

                 if( str.len==5 && str[0]=='i' && str[1]=='g' && str[2]=='n' && str[3]=='e' && str[4]=='d' ) return true; else return false;
                }

               default: return false;
              }
           }

          case 's' :
           {
            ++str;

            if( str.len==3 && str[0]=='i' && str[1]=='n' && str[2]=='g' ) return true; else return false;
           }

          default: return false;
         }
      }

     case 'v' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'i' :
           {
            ++str;

            if( str.len==5 && str[0]=='r' && str[1]=='t' && str[2]=='u' && str[3]=='a' && str[4]=='l' ) return true; else return false;
           }

          case 'o' :
           {
            ++str;

            if( !str ) return false;

            switch( str[0] )
              {
               case 'i' :
                {
                 ++str;

                 if( str.len==1 && str[0]=='d' ) return true; else return false;
                }

               case 'l' :
                {
                 ++str;

                 if( str.len==5 && str[0]=='a' && str[1]=='t' && str[2]=='i' && str[3]=='l' && str[4]=='e' ) return true; else return false;
                }

               default: return false;
              }
           }

          default: return false;
         }
      }

     case 'w' :
      {
       ++str;

       if( !str ) return false;

       switch( str[0] )
         {
          case 'c' :
           {
            ++str;

            if( str.len==5 && str[0]=='h' && str[1]=='a' && str[2]=='r' && str[3]=='_' && str[4]=='t' ) return true; else return false;
           }

          case 'h' :
           {
            ++str;

            if( str.len==3 && str[0]=='i' && str[1]=='l' && str[2]=='e' ) return true; else return false;
           }

          default: return false;
         }
      }

     default: return false;
    }
 }

 // ---

StrLen Tokenizer::ScanShortComment(StrLen text)
 {
  text+=2;

  while( +text && !FlagChar(*text).test(CharEOL) ) ++text;

  return text;
 }

StrLen Tokenizer::ScanLongComment(StrLen text)
 {
  text+=2;

  while( text.len>=2 )
    if( text[0]=='*' && text[1]=='/' )
      {
       text+=2;

       return text;
      }
    else
      {
       ++text;
      }

  return text;
 }

StrLen Tokenizer::ScanEOL(StrLen text)
 {
  if( *text=='\r' )
    {
     ++text;

     if( +text && *text=='\n' ) ++text;
    }
  else
    {
     ++text;
    }

  return text;
 }

 // ---

StrLen Tokenizer::cut(StrLen suffix)
 {
  StrLen str=text.prefix(suffix);

  text=suffix;

  return str;
 }

Token Tokenizer::nextId() // L...
 {
  StrLen str=cut(ScanId(text));

  return {str,TestKeyword(str)?TokenKeyword:TokenId};
 }

Token Tokenizer::nextNumber() // D...  .D...
 {
  StrLen str=cut(ScanNumber(text));

  return {str,TokenNumber};
 }

Token Tokenizer::nextOp() // P...
 {
  StrLen str=cut(ScanOp(text));

  return {str,TokenOp};
 }

Token Tokenizer::nextChar() // '...
 {
  StrLen str=cut(ScanChar(text));

  return {str,TokenChar};
 }

Token Tokenizer::nextString() // "...
 {
  StrLen str=cut(ScanString(text));

  return {str,TokenString};
 }

Token Tokenizer::nextSpace() // S...
 {
  StrLen str=cut(ScanSpace(text));

  return {str,TokenSpace};
 }

Token Tokenizer::nextOther()
 {
  StrLen str=cut(ScanOther(text));

  return {str,TokenOther};
 }

 // ---

Token Tokenizer::nextShortComment() // //...
 {
  StrLen str=cut(ScanShortComment(text));

  return {str,TokenShortComment};
 }

Token Tokenizer::nextLongComment() // /*...
 {
  StrLen str=cut(ScanLongComment(text));

  return {str,TokenLongComment};
 }

Token Tokenizer::nextEOL() // N...
 {
  StrLen str=cut(ScanEOL(text));

  return {str,TokenEOL};
 }

 // ---

Token Tokenizer::next()
 {
  if( !text ) return {};

  FlagChar fc(*text);

  if( fc.test(CharLetter) )
    {
     return nextId();
    }
  else if( fc.test(CharDigit) )
    {
     return nextNumber();
    }
  else if( fc.test(CharPunct) )
    {
     if( fc.ch=='/' )
       {
        if( text.len>1 )
          {
           switch( text[1] )
             {
              case '/' : return nextShortComment();
              case '*' : return nextLongComment();
             }
          }
       }
     else if( fc.ch=='.' )
       {
        if( text.len>1 )
          {
           if( FlagChar(text[1]).test(CharDigit) ) return nextNumber();
          }
       }

     return nextOp();
    }
  else if( fc.test(CharQuote) )
    {
     if( fc.ch=='"' )
       {
        return nextString();
       }
     else
       {
        return nextChar();
       }
    }
  else if( fc.test(CharSpace) )
    {
     return nextSpace();
    }
  else if( fc.test(CharEOL) )
    {
     return nextEOL();
    }
  else
    {
     return nextOther();
    }
 }

} // namespace CppText
} // namespace App

