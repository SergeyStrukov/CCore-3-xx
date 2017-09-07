/* SymCount.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_SymCount_h
#define CCore_inc_SymCount_h

#include <CCore/inc/Gadget.h>

#ifdef CCORE_UTF8
# include <CCore/inc/Utf8.h>
#endif

namespace CCore {

/* SymLen() */

#ifdef CCORE_UTF8

inline ulen SymLen(StrLen text) { return Utf8Len(text); }

#else

inline ulen SymLen(StrLen text) { return text.len; }

#endif

/* class SymCounter */

class SymDetector;

class SymCounter;

/* class SymDetector */

#ifdef CCORE_UTF8

class SymDetector : NoCopy
 {
   unsigned len;

  public:

   SymDetector() { reset(); }

   void reset() { len=0; }

   bool put(char ch)
    {
     if( len )
       {
        len--;

        return !len;
       }
     else
       {
        if( unsigned l=Utf8Len(ch) )
          {
           if( l==1 )
             {
              return true;
             }
           else
             {
              len=l-1;

              return false;
             }
          }
        else
          {
           return true;
          }
       }
    }
 };

#else

class SymDetector : NoCopy
 {
  public:

   SymDetector() { reset(); }

   void reset() {}

   bool put(char) { return true; }
 };

#endif

/* class SymCounter */

#ifdef CCORE_UTF8

class SymCounter : NoCopy
 {
   ulen count;
   SymDetector det;

  public:

   SymCounter() : count(0) {}

   operator ulen() const { return count; }

   void put(char ch)
    {
     if( det.put(ch) ) count++;
    }

   void put(char ch,ulen len)
    {
     for(; len ;len--) put(ch);
    }

   void put(const char *str,ulen len)
    {
     for(; len ;len--,str++) put(*str);
    }
 };

#else

class SymCounter : NoCopy
 {
   ulen count;

  public:

   SymCounter() : count(0) {}

   operator ulen() const { return count; }

   void put(char)
    {
     count++;
    }

   void put(char,ulen len)
    {
     count+=len;
    }

   void put(const char *,ulen len)
    {
     count+=len;
    }
 };

#endif

} // namespace CCore

#endif

