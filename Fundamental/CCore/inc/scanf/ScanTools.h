/* ScanTools.h */
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

#ifndef CCore_inc_scanf_ScanTools_h
#define CCore_inc_scanf_ScanTools_h

#include <CCore/inc/TextTools.h>

namespace CCore {

/* concept CharStreamType<S> */

template <class S> // ref extended
concept bool CharStreamType = requires(S &obj,Meta::ToConst<S> &cobj)
 {
  { +cobj } -> bool ;

  { !cobj } -> bool ;

  { *cobj } -> char ;

  ++obj;
 } ;

/* concept CharFailStreamType<S> */

template <class S> // ref extended
concept bool CharFailStreamType = CharStreamType<S> && requires(S &obj)
 {
  obj.fail();
 } ;

/* CharBaseValue() */

inline int CharBaseValue(char ch,unsigned base)
 {
  int dig=CharHexValue(ch);

  if( (unsigned)dig>=base ) return -1;

  return dig;
 }

/* SkipSpace() */

void SkipSpace(CharStreamType &inp)
 {
  for(; +inp && CharIsSpace(*inp) ;++inp);
 }

/* SkipNonSpace() */

void SkipNonSpace(CharStreamType &inp)
 {
  for(; +inp && !CharIsSpace(*inp) ;++inp);
 }

/* ProbeChar() */

bool ProbeChar(CharStreamType &inp,char ch)
 {
  if( +inp )
    {
     if( *inp==ch )
       {
        ++inp;

        return true;
       }
    }

  return false;
 }

/* PassChars() */

template <class S>
void PassChars(S &)
 {
  // do nothing
 }

template <CharFailStreamType S,class C,class ... CC>
void PassChars(S &inp,C ch,CC ... cc)
 {
  if( +inp && (*inp)==char(ch) )
    {
     ++inp;

     PassChars(inp,cc...);
    }
  else
    {
     inp.fail();
    }
 }

/* PassOneOfChar() */

void PassOneOfChar(CharFailStreamType &inp,FuncType<bool,char> func)
 {
  if( +inp && func(*inp) )
    {
     ++inp;
    }
  else
    {
     inp.fail();
    }
 }

/* SkipAllOfChar() */

void SkipAllOfChar(CharStreamType &inp,FuncType<bool,char> func)
 {
  for(; +inp && func(*inp) ;++inp);
 }

} // namespace CCore

#endif


