/* MakeString.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_MakeString_h
#define CCore_inc_MakeString_h

#include <CCore/inc/Gadget.h>

namespace CCore {

/* classes */

template <ulen Len> class MakeString;

/* class MakeString<ulen Len> */

template <ulen Len>
class MakeString : NoCopy
 {
   char buf[Len];
   ulen len = 0 ;
   bool overflow = false ;

  public:

   MakeString() {}

   bool operator + () const { return !overflow; }

   bool operator ! () const { return overflow; }

   void reset()
    {
     len=0;
     overflow=false;
    }

   // add()

   MakeString & add(StrLen str)
    {
     if( str.len <= Len-len )
       {
        str.copyTo(buf+len);

        len+=str.len;
       }
     else
       {
        overflow=true;
       }

     return *this;
    }

   MakeString & add(const char *zstr)
    {
     for(; char ch=*zstr ;zstr++)
       {
        if( len<Len )
          {
           buf[len++]=ch;
          }
        else
          {
           overflow=true;

           break;
          }
       }

     return *this;
    }

   MakeString & add(char ch)
    {
     if( len<Len )
       {
        buf[len++]=ch;
       }
     else
       {
        overflow=true;
       }

     return *this;
    }

   MakeString & zero()
    {
     if( len<Len )
       {
        buf[len]=0;
       }
     else
       {
        overflow=true;
       }

     return *this;
    }

   // multiadd

   MakeString & add(NothingType) { return zero(); }

   template <class T>
   MakeString & operator += (T t) { return add(t); }

   template <class ... TT>
   MakeString & add(TT ... tt)
    {
     return ( (*this) += ... += tt );
    }

   // get result

   StrLen get() const { return StrLen(buf,len); }

   const char * getZStr() const { return buf; }
 };

} // namespace CCore

#endif

