/* SysFileInternal.h */
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

#include <CCore/inc/GenFile.h>
#include <CCore/inc/MakeString.h>
#include <CCore/inc/MemBase.h>

#include <CCore/inc/sys/SysUtf8.h>

//#include <CCore/inc/Print.h>

#include <CCore/inc/win32/Win32.h>

namespace CCore {
namespace Sys {

/* functions */

inline FileError MakeError(FileError fe,Win32::error_t error)
 {
  switch( error )
    {
     case Win32::ErrorFileNotFound     : return FileError_NoFile;
     case Win32::ErrorPathNotFound     : return FileError_NoPath;
     case Win32::ErrorTooManyOpenFiles : return FileError_SysOverload;
     case Win32::ErrorAccessDenied     : return FileError_NoAccess;
     case Win32::ErrorNotEnoughMemory  : return FileError_SysOverload;
     case Win32::ErrorOutOfMemory      : return FileError_SysOverload;
     case Win32::ErrorInvalidDrive     : return FileError_NoDevice;
     case Win32::ErrorWriteProtect     : return FileError_WriteProtect;
     case Win32::ErrorSeek             : return FileError_PosFault;
     case Win32::ErrorWriteFault       : return FileError_WriteFault;
     case Win32::ErrorReadFault        : return FileError_ReadFault;
     case Win32::ErrorHandleEOF        : return FileError_BadPosition;
     case Win32::ErrorFileExists       : return FileError_FileExist;
     case Win32::ErrorDiskFull         : return FileError_DiskFull;
     case Win32::ErrorInvalidHandle    : return FileError_BadId;
     case Win32::ErrorInvalidName      : return FileError_BadName;
     case Win32::ErrorAlreadyExists    : return FileError_FileExist;
     case Win32::ErrorDirNotEmpty      : return FileError_DirIsNotEmpty;

     default:
      {
       //Printf(Con,"error = #;\n",error);

       return fe;
      }
    }
 }

inline FileError MakeError(FileError fe)
 {
  return MakeError(fe,Win32::GetLastError());
 }

inline FileError MakeErrorIf(FileError fe,bool nok)
 {
  if( nok ) return MakeError(fe);

  return FileError_Ok;
 }

inline void AddErrorIf(FileMultiError &errout,FileError fe,bool nok)
 {
  if( nok ) errout.add(MakeError(fe));
 }

inline CmpFileTimeType ToCmpFileTime(Win32::FileTime ft)
 {
  CmpFileTimeType ret=ft.lo|(CmpFileTimeType(ft.hi)<<32);

  if( !ret ) ret=1;

  return ret;
 }

/* classes */

template <PODType T> class TempBuf;

struct MakeZStr;

struct FileName;

/* class TempBuf<T> */

template <PODType T>
class TempBuf : NoCopy
 {
   T *ptr;

  public:

   explicit TempBuf(ulen len) { ptr=static_cast<T *>( MemAlloc(LenOf(len,sizeof (T))) ); }

   ~TempBuf() { MemFree(ptr); }

   operator T * () const { return ptr; }
 };

/* struct MakeZStr */

struct MakeZStr
 {
  FileError error;
  ulen len;

  void setError(FileError error_) { error=error_; len=0; }

  MakeZStr(StrLen str,PtrLen<WChar> out);
 };

/* struct FileName */

struct FileName : NoCopy
 {
  WChar wbuf[MaxPathLen+1];
  ulen len;

  operator const WChar * () const { return wbuf; }

  FileError prepare(StrLen str)
   {
    MakeZStr result(str,Range(wbuf));

    len=result.len;

    return result.error;
   }

  FileError prepare(StrLen str1,StrLen str2)
   {
    MakeString<MaxPathLen> buf;

    if( !buf.add(str1,str2) )
      {
       len=0;

       return FileError_TooLongPath;
      }

    return prepare(buf.get());
   }
 };

} // namespace Sys
} // namespace CCore

