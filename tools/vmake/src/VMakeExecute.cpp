/* VMakeExecute.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: vmake 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/VMakeProc.h>
#include <inc/SpawnProcess.h>

namespace App {

namespace VMake {

/* class FileProc */

int FileProc::execute(StrLen exe_file,StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env) // TODO
 {
  Used(exe_file);
  Used(wdir);
  Used(cmdline);
  Used(env);

  return 1;
 }

} // namespace VMake

} // namespace App

