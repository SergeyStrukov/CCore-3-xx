/* SysSpawnInternal.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_sys_SysSpawnInternal_h
#define CCore_inc_sys_SysSpawnInternal_h

#include <CCore/inc/sys/SysUtf8.h>
#include <CCore/inc/sys/SysError.h>

#include <CCore/inc/Array.h>

namespace CCore {
namespace Sys {

/* classes */

class EnvironHook;

class ProcessSetup;

/* class EnvironHook */

class EnvironHook : NoCopy
 {
   WChar *envblock;

  public:

   EnvironHook();

   ~EnvironHook();

   template <class Func>
   void operator () (Func func)
    {
     const WChar *ptr=envblock;

     if( !ptr ) return;

     while( *ptr )
       {
        const WChar *str=ptr;
        const WChar *lim=ZScan(str);

        ptr=lim+1;

        func(Range(str,lim));
       }
    }
 };

/* class ProcessSetup */

class ProcessSetup : NoCopy
 {
   DynArray<WChar> dir;
   DynArray<WChar> cmdline;
   DynArray<WChar> envblock;

   bool has_dir;
   ErrorType error;

   class BuildStr;

  private:

   void makeDir(char *wdir);

   void makeCmdline(char *path,char **argv);

   void makeEnvblock(char **envp);

  public:

   ProcessSetup(char *wdir,char *path,char **argv,char **envp); // path!=0 , argv!=0 , envp!=0

   ~ProcessSetup();

   ErrorType create(int &handle);
 };

} // namespace Sys
} // namespace CCore

#endif

