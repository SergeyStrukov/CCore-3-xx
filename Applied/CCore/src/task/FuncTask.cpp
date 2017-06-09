/* FuncTask.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/task/FuncTask.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* functions */

void GuardRunFuncTaskFailed()
 {
  Printf(Exception,"CCore::RunFuncTask<FuncInit>(...) : failed");
 }

} // namespace CCore


