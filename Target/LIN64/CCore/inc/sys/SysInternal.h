/* SysInternal.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/LIN64
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysInternal_h
#define CCore_inc_sys_SysInternal_h

#include <CCore/inc/sys/SysAbort.h>

#include <CCore/inc/GenFile.h>
#include <CCore/inc/MakeString.h>

#include <time.h>
#include <errno.h>

namespace CCore {
namespace Sys {

/* functions */

inline FileError MakeError(FileError fe,int error)
 {
  switch( error )
    {
     case ENOENT       : return FileError_NoFile;
     case EMFILE       : return FileError_SysOverload;
     case ENFILE       : return FileError_SysOverload;
     case EACCES       : return FileError_NoAccess;
     case ENOMEM       : return FileError_SysOverload;
     case ENODEV       : return FileError_NoDevice;
     case ENOSPC       : return FileError_DiskFull;
     case EBADF        : return FileError_BadId;
     case EEXIST       : return FileError_FileExist;
     case ENOTEMPTY    : return FileError_DirIsNotEmpty;
     case EFBIG        : return FileError_SysOverload;
     case ENAMETOOLONG : return FileError_TooLongPath;

     default:
      {
       return fe;
      }
    }
 }

inline FileError MakeError(FileError fe)
 {
  return MakeError(fe,errno);
 }

/* classes */

struct FileName;

struct TimeSpec;

struct TimeVal;

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

/* struct TimeSpec */

struct TimeSpec : timespec
 {
  static unsigned GetSec(MSec time) { return +time/1000u; }

  static unsigned GetNanoSec(MSec time) { return (+time%1000u)*1000'000u; }

  TimeSpec() {}

  explicit TimeSpec(const timespec &ts) : timespec(ts) {}

  explicit TimeSpec(MSec time)
   {
    tv_sec=GetSec(time);
    tv_nsec=GetNanoSec(time);
   }

  explicit TimeSpec(clockid_t clock_id)
   {
    AbortIf( clock_gettime(clock_id,this)!=0 ,"CCore::Sys::TimeSpec::TimeSpec");
   }

  TimeSpec(clockid_t clock_id,MSec time)
   {
    AbortIf( clock_gettime(clock_id,this)!=0 ,"CCore::Sys::TimeSpec::TimeSpec");

    unsigned delta_sec=GetSec(time);
    unsigned delta_nsec=GetNanoSec(time);

    if( (tv_nsec+=delta_nsec)>=1'000'000'000u )
      {
       tv_nsec-=1'000'000'000u;
       delta_sec++;
      }

    tv_sec+=delta_sec;
   }

  unsigned long long getMSec() const { return tv_nsec/1'000'000u+tv_sec*1000ull; }

  unsigned long long getSec() const { return tv_sec; }

  unsigned long long getNanoSec() const { return tv_nsec+tv_sec*1'000'000'000ull; }
 };

/* struct TimeVal */

struct TimeVal : timeval
 {
  static unsigned GetSec(MSec time) { return +time/1000u; }

  static unsigned GetMicroSec(MSec time) { return (+time%1000u)*1000u; }

  TimeVal() {}

  explicit TimeVal(MSec time)
   {
    tv_sec=GetSec(time);
    tv_usec=GetMicroSec(time);
   }
 };

} // namespace Sys
} // namespace CCore

#endif


