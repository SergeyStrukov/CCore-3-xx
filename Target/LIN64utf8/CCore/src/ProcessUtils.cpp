/* ProcessUtils.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/LIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ProcessUtils.h>

#include <CCore/inc/Exception.h>

#include <stdlib.h>

namespace CCore {

/* class UnixHomeDir */

void UnixHomeDir::make()
 {
  if( const char *s=getenv("HOME") )
    {
     StrLen text(s);

     if( text.len>MaxPathLen )
       {
        Printf(Exception,"CCore::UnixHomeDir::make() : too long path");
       }

     text.copyTo(buf);

     str=Range(buf,text.len);
    }
  else
    {
     Printf(Exception,"CCore::UnixHomeDir::make() : no variable HOME");
    }
 }

} // namespace CCore

