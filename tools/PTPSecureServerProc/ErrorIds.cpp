/* ErrorIds.cpp */
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

#include "ErrorIds.h"

namespace PTPSecureServerProc {

/* functions */

StrLen GetErrorDesc(ErrorIdType error_id)
 {
  if( error_id>=ErrorBase && error_id<=ErrorBase+FileError_Some )
    {
     FileError fe=FileError(error_id-ErrorBase);

     return GetTextDesc(fe);
    }

  switch( error_id )
    {
     case NoError :                 return "Ok";

     case Error_NoFunction :        return "No such service/function";

     case Error_BadInput :          return "Bad input data format";

     case Error_Exhausted :         return "Not enough resources";

     case Error_Unknown :           return "Unknown error";

     case Error_AccessDenied :      return "Access denied";

     case Error_NoProfile :         return "No profile";

     default: return "Unknown error code";
    }
 }

} // namespace PTPSecureServerProc



