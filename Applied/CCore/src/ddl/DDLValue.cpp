/* DDLValue.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ddl/DDLValue.h>

namespace CCore {
namespace DDL {

/* DString functions */

ulen DStringLen(StrLen str)
 {
  ulen ret=0;

  for(; +str ;++str)
    {
     char ch=*str;

     if( ch=='\\' )
       {
        ++str;

        ret++;
       }
     else
       {
        ret++;
       }
    }

  return ret;
 }

void DString(StrLen str,char *out)
 {
  for(; +str ;++str)
    {
     char ch=*str;

     if( ch=='\\' )
       {
        ++str;

        *(out++)=MapDChar(*str);
       }
     else
       {
        *(out++)=ch;
       }
    }
 }

} // namespace DDL
} // namespace CCore
