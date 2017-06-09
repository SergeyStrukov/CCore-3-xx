/* IntPrint.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/printf/IntPrint.h>

namespace CCore {

/* struct IntPrintOpt */

IntPrintOpt::IntPrintOpt(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  Parse_empty(dev,show_sign);

  ParseUInt_empty(dev,width,0u);

  Parse_IntBase(dev,base,fract,show_base);

  Parse_empty(dev,align);

  if( !dev.finish() ) setDefault();
 }

/* struct PrintDumpOptType */

PrintDumpOptType::PrintDumpOptType(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  ParseUInt_empty(dev,width,0u);

  if( ParseChar_try(dev,'.') )
    {
     ParseUInt(dev,line_len);
    }
  else
    {
     line_len=Default_line_len;
    }

  if( !dev.finish() ) setDefault();
 }

} // namespace CCore


