/* ErrorIds.h */
//----------------------------------------------------------------------------------------
//
//  Project: PTPServerProc 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef PTPServer_ErrorIds_h
#define PTPServer_ErrorIds_h

#include <CCore/inc/net/PTPExtra.h>
#include <CCore/inc/net/HFSBase.h>

#include <CCore/inc/GenFile.h>

namespace PTPServerProc {

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

inline constexpr ErrorIdType Error_ConNotOpened      = 1'000 ;
inline constexpr ErrorIdType Error_BadConId          = 1'001 ;
inline constexpr ErrorIdType Error_CannotOpenMoreCon = 1'002 ;
inline constexpr ErrorIdType Error_ReadStarted       = 1'003 ;
inline constexpr ErrorIdType Error_WriteFault        = 1'004 ;

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

} // namespace PTPServerProc

#endif


