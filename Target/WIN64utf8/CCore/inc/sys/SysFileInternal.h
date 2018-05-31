/* SysFileInternal.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/GenFile.h>
#include <CCore/inc/MakeString.h>
#include <CCore/inc/MemBase.h>

#include <CCore/inc/sys/SysUtf8.h>

//#include <CCore/inc/Print.h>

#include <CCore/inc/win64/Win64.h>

namespace CCore {
namespace Sys {

/* functions */

inline FileError MakeError(FileError fe,Win64::error_t error)
 {
  switch( error )
    {
     case Win64::ErrorFileNotFound     : return FileError_NoFile;
     case Win64::ErrorPathNotFound     : return FileError_NoPath;
     case Win64::ErrorTooManyOpenFiles : return FileError_SysOverload;
     case Win64::ErrorAccessDenied     : return FileError_NoAccess;
     case Win64::ErrorNotEnoughMemory  : return FileError_SysOverload;
     case Win64::ErrorOutOfMemory      : return FileError_SysOverload;
     case Win64::ErrorInvalidDrive     : return FileError_NoDevice;
     case Win64::ErrorWriteProtect     : return FileError_WriteProtect;
     case Win64::ErrorSeek             : return FileError_PosFault;
     case Win64::ErrorWriteFault       : return FileError_WriteFault;
     case Win64::ErrorReadFault        : return FileError_ReadFault;
     case Win64::ErrorHandleEOF        : return FileError_BadPosition;
     case Win64::ErrorFileExists       : return FileError_FileExist;
     case Win64::ErrorDiskFull         : return FileError_DiskFull;
     case Win64::ErrorInvalidHandle    : return FileError_BadId;
     case Win64::ErrorInvalidName      : return FileError_BadName;
     case Win64::ErrorAlreadyExists    : return FileError_FileExist;
     case Win64::ErrorDirNotEmpty      : return FileError_DirIsNotEmpty;

     default:
      {
       //Printf(Con,"error = #;\n",error);

       return fe;
      }
    }
 }

inline FileError MakeError(FileError fe)
 {
  return MakeError(fe,Win64::GetLastError());
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

inline CmpFileTimeType ToCmpFileTime(Win64::FileTime ft)
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

   explicit TempBuf(ulen len) noexcept { ptr=static_cast<T *>( TryMemAlloc(LenOf(len,sizeof (T))) ); }

   ~TempBuf() { MemFree(ptr); }

   T * operator + () const { return ptr; }

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

