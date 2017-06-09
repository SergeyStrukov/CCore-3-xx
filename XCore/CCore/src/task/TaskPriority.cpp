/* TaskPriority.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/task/TaskPriority.h>

namespace CCore {

/* struct PrintTaskPriority */

PrintTaskPriority::PrintOptType::PrintOptType(const char *ptr,const char *lim)
 {
  StrParse dev(ptr,lim);

  ParseUInt_empty(dev,width,0u);

  Parse_empty(dev,align);

  if( !dev.finish() ) setDefault();
 }

} // namespace CCore


