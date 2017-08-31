/* SysFileInternal.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/GenFile.h>
#include <CCore/inc/MakeString.h>

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

struct FileName;

/* struct FileName */

struct FileName
 {
  MakeString<MaxPathLen+1> buf;

  operator const char * () const { return buf.getZStr(); }

  template <class ... TT>
  bool set(TT ... tt)
   {
    return +buf.add(tt...,Null);
   }
 };

} // namespace Sys
} // namespace CCore

