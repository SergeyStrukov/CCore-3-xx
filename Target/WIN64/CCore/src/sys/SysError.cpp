/* SysError.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Target/WIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/sys/SysError.h>

#include <CCore/inc/win64/Win64.h>

namespace CCore {
namespace Sys {

/* private functions */

ErrorType NonNullError() noexcept
 {
  if( auto ret=Win64::GetLastError() ) return ErrorType(ret);

  return Error_SysErrorFault;
 }

/* struct ErrorDesc */

bool ErrorDesc::set(StrLen msg)
 {
  str=msg.ptr;
  len=msg.len;

  return true;
 }

bool ErrorDesc::init(ErrorType error,PtrLen<char> buf) noexcept
 {
  switch( error )
    {
     case Error_SysErrorFault : return set("System failed to report error"_c);

     case Error_Task          : return set("System cannot create task"_c);

     case Error_Socket        : return set("System socket failure"_c);

     case Error_Spawn         : return set("Child process spawn/wait failed"_c);

     case Error_Running       : return set("Child process still running"_c);

     case Error_TooLong       : return set("Too long string"_c);

     case Error_NoVariable    : return set("No such variable"_c);
    }

  Win64::flags_t flags=Win64::FormatMessageFromSystem
                      |Win64::FormatMessageIgnoreInserts
                      |Win64::FormatMessageMaxWidthMask;

  len=Win64::FormatMessageA(flags,0,error,0,buf.ptr,(Win64::ushortlen_t)Min<ulen>(buf.len,4_KByte),0);

  if( len )
    {
     str=buf.ptr;

     return true;
    }
  else
    {
     str=0;

     return false;
    }
 }

} // namespace Sys
} // namespace CCore


