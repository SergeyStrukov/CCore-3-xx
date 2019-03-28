/* SysEnv.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysEnv.h>

#include <CCore/inc/win32/Win32gui.h>

#include <cstdlib>

namespace CCore {
namespace Sys {

/* struct NormalGetEnv */

NormalGetEnv::NormalGetEnv(const WChar *name,WChar *buf,ulen buf_len)
 {
  len=Win32::GetEnvironmentVariableW(name,buf,buf_len);

  if( len==0 )
    {
     error=NonNullError();

     if( error==Win32::ErrorEnvNotFound ) error=Error_NoVariable;
    }
  else if( len>=buf_len )
    {
     error=Error_TooLong;
    }
 }

/* struct BackupGetEnv */

BackupGetEnv::BackupGetEnv(const char *name,WChar *buf,ulen buf_len)
 {
  len=0;

  if( const char *str=std::getenv(name) )
    {
     ToWChar to(Range(buf,buf_len),str);

     if( to.broken )
       {
        error=Error_BrokenUtf8;
       }
     else if( to.overflow )
       {
        error=Error_TooLong;
       }
     else
       {
        len=to.len;
        error=NoError;
       }
    }
  else
    {
     error=Error_NoVariable;
    }
 }

} // namespace Sys
} // namespace CCore

