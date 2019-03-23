/* SpawnProcess.h */
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

#ifndef App_SpawnProcess_h
#define App_SpawnProcess_h

#include <CCore/inc/String.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>

#include <CCore/inc/FileSystem.h>

namespace App {

/* using */

using namespace CCore;

namespace VMake {

/* classes */

class CmdLineParser;

class SpawnProcess;

/* class CmdLineParser */

class CmdLineParser
 {
   StrLen text;

  public:

   explicit CmdLineParser(StrLen text_) : text(text_) {}

   StrLen next();
 };

/* class SpawnProcess */

class SpawnProcess : NoCopy
 {
   String exe_name;

   DynArray<String> args;

   struct EnvRec
    {
     String str;
     StrLen name;
     ulen ind;

     EnvRec(String &&str_,ulen name_len,ulen ind_)
      : str(std::move(str_)),
        name(Range(str).prefix(name_len)),
        ind(ind_)
      {
      }

     bool operator < (const EnvRec &obj) const
      {
       if( CmpResult cmp=StrCmp(name,obj.name) ) return cmp<0;

       return ind<obj.ind;
      }

     bool operator != (const EnvRec &obj) const { return StrCmp(name,obj.name)!=0; }
    };

   DynArray<EnvRec> envs;

   int pid;

  public:

   SpawnProcess(FileSystem &fs,StrLen wdir,StrLen exe_name);

   ~SpawnProcess();

   void addArg(StrLen str);

   void addCmdline(StrLen cmdline);

   void addEnv(StrLen name,StrLen value);

   void addEnv(StrLen str);

   void spawn();

   int wait();
 };

} // namespace VMake

} // namespace App

#endif
