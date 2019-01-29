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

/* namespace CppText */

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
  set("{}[]#()<>%:;.?*+-/^&|~!=,\\\"’",CharPunct);
  set("0123456789abcdefABCDEF",CharHex);
  set(" \n\b\t\v\f",CharSpace);
 }

CharFlags FlagTable::operator [] (unsigned char ch) const
 {
  if( ch>=128 ) return CharNull;

  return table[ch];
 }

/* class Tokenizer */

StrLen Tokenizer::ScanId(StrLen text)
 {
  ++text;

  while( +text && (FlagChar(*text)&(CharLetter|CharDigit)) ) ++text;

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

StrLen Tokenizer::cut(StrLen suffix)
 {
  StrLen str=text.prefix(suffix);

  text=suffix;

  return str;
 }

Token Tokenizer::nextId()
 {
  StrLen str=cut(ScanId(text));

  return {str,TestKeyword(str)?TokenKeyword:TokenId};
 }

Token Tokenizer::next()
 {
  if( !text ) return {};

  FlagChar fc(*text);

  if( fc.flags&CharLetter )
    {
     return nextId();
    }
  else if( fc.flags&CharDigit )
    {
    }
  else if( fc.flags&CharPunct )
    {
    }
  else if( fc.flags&CharSpace )
    {
    }
  else
    {
    }
 }

} // namespace CppText

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

void PastData::loadCPP(StrLen text) // TODO
 {
  Used(text);
 }

} // namespace App

