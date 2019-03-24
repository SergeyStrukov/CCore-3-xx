/* VMakeCommand.cpp */
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

#include <CCore/inc/Path.h>
#include <CCore/inc/SpawnProcess.h>

namespace App {

namespace VMake {

/* class FileProc */

int FileProc::command(StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env)
 {
  try
    {
     StrLen exe_name=Sys::GetShell();

     SpawnProcess spawn(wdir,exe_name);

     SplitPath split1(exe_name);
     SplitName split2(split1.path);

     spawn.addArg(split2.name);
     spawn.addArg("-c"_c);
     spawn.addArg(cmdline);

     for(TypeDef::Env obj : env ) spawn.addEnv(obj.name,obj.value);

     spawn.spawn();

     return spawn.wait();
    }
  catch(CatchType)
    {
     return 1000;
    }
 }

} // namespace VMake

} // namespace App

