/* SysEnv.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysEnv_h
#define CCore_inc_sys_SysEnv_h

#include <CCore/inc/sys/SysError.h>
#include <CCore/inc/sys/SysUtf8.h>

namespace CCore {
namespace Sys {

/* classes */

struct NormalGetEnv;

struct BackupGetEnv;

template <ulen NameLen,ulen ValueLen> class GetEnv;

template <ulen NameLen,ulen ValueLen> struct TryGetEnv;

/* struct NormalGetEnv */

struct NormalGetEnv
 {
  ulen len;
  ErrorType error;

  NormalGetEnv(const WChar *name,WChar *buf,ulen buf_len);
 };

/* struct BackupGetEnv */

struct BackupGetEnv
 {
  ulen len;
  ErrorType error;

  BackupGetEnv(const char *name,WChar *buf,ulen buf_len);
 };

/* class GetEnv<ulen NameLen,ulen ValueLen> */

template <ulen NameLen,ulen ValueLen>
class GetEnv : NoCopy
 {
   WCharString<NameLen> name;

   WCharToUtf8<ValueLen+1> value;
   ErrorType error;

  public:

   explicit GetEnv(const char *name_)
    : name(name_)
    {
     if( auto e=name.getError() )
       {
        value.len=0;
        error=e;

        return;
       }

     NormalGetEnv result(name,value.buf,value.Len);

     value.len=result.len;
     error=result.error;

     if( result.error && ( result.error!=Error_TooLong ) )
       {
        BackupGetEnv result(name_,value.buf,value.Len);

        value.len=result.len;
        error=result.error;
       }
    }

   ErrorType getError() const { return error; }

   ulen full(PtrLen<char> out) const { return value.full(out); }
 };

/* struct TryGetEnv<ulen NameLen,ulen ValueLen> */

template <ulen NameLen,ulen ValueLen>
struct TryGetEnv
 {
  StrLen str;
  bool ok;

  TryGetEnv(PtrLen<char> buf,const char *name)
   {
    ok=false;

    GetEnv<NameLen,ValueLen> data(name);

    if( !data.getError() )
      {
       ulen len=data.full(buf);

       if( len!=MaxULen )
         {
          str=buf.prefix(len);
          ok=true;
         }
      }
   }
 };

} // namespace Sys
} // namespace CCore

#endif

