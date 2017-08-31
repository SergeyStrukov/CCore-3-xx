/* SysLaunchPath.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysLaunchPath.h>
#include <CCore/inc/sys/SysUtf8.h>

#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* struct LaunchPath */

LaunchPath::LaunchPath(char buf[MaxPathLen+1])
 {
  WCharToUtf8<MaxPathLen+1> temp;

  temp.len=Win32::GetModuleFileNameW(0,temp.buf,temp.Len);

  if( !temp.len )
    {
     path=Null;
     error=NonNullError();
    }
  else if( temp.len>MaxPathLen )
    {
     path=Null;
     error=(ErrorType)Win32::ErrorSmallBuffer;
    }
  else
    {
     ulen len=temp.full(Range(buf,MaxPathLen));

     if( len==MaxULen )
       {
        path=Null;
        error=(ErrorType)Win32::ErrorSmallBuffer;
       }
     else
       {
        buf[len]=0;
        path=StrLen(buf,len);
        error=NoError;
       }
    }
 }

} // namespace Sys
} // namespace CCore

