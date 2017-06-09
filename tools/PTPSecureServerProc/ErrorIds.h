/* ErrorIds.h */
//----------------------------------------------------------------------------------------
//
//  Project: PTPSecureServerProc 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef PTPServer_ErrorIds_h
#define PTPServer_ErrorIds_h

#include <CCore/inc/net/PTPExtra.h>
#include <CCore/inc/net/HFSBase.h>

#include <CCore/inc/GenFile.h>

namespace PTPSecureServerProc {

/* using */

using namespace CCore;

using Net::PTP::ErrorIdType;

using Net::PTP::NoError;
using Net::PTP::Error_NoFunction;
using Net::PTP::Error_BadInput;
using Net::PTP::Error_Exhausted;
using Net::PTP::Error_Unknown;

using Net::HFS::ErrorBase;

/* consts */

const ErrorIdType Error_AccessDenied = 1'000 ;
const ErrorIdType Error_NoProfile    = 1'001 ;

/* functions */

inline ErrorIdType ToErrorId(FileError fe)
 {
  return fe+ErrorBase;
 }

inline ErrorIdType ToErrorId_Ok(FileError fe)
 {
  if( !fe ) return NoError;

  return ToErrorId(fe);
 }

StrLen GetErrorDesc(ErrorIdType error_id);

} // namespace PTPSecureServerProc

#endif


