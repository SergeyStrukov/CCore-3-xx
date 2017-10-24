/* PrintRatio.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/PrintRatio.h>

namespace CCore {

/* struct RatioPrintOpt */

RatioPrintOpt::RatioPrintOpt(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  Parse_empty(dev,show_sign);

  ParseUInt_empty(dev,width,0u);

  if( ParseChar_try(dev,'.') )
    {
     ParseUInt(dev,fract,MinIntFract,MaxIntFract);
    }
  else
    {
     fract=DefaultRatioFract;
    }

  Parse_empty(dev,align);

  if( !dev.finish() ) setDefault();
 }

} // namespace CCore

