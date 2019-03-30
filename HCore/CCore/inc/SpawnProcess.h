/* SpawnProcess.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_SpawnProcess_h
#define CCore_inc_SpawnProcess_h

#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Cmp.h>

#include <CCore/inc/sys/SysSpawn.h>

namespace CCore {

/* enum SpawnSlotState */

enum SpawnSlotState
 {
  SpawnSlot_Ready,
  SpawnSlot_Broken,
  SpawnSlot_Running,
  SpawnSlot_Stopped
 };

/* classes */

class ShellPath;

class SpawnSlot;

class SpawnSet;

class SpawnProcess;

/* class ShellPath */

class ShellPath : NoCopy
 {
   char buf[MaxPathLen+1];
   StrLen path;

  public:

   ShellPath() { path=Sys::GetShell(buf); }

   StrLen get() const { return path; }
 };

/* class SpawnSlot */

class SpawnSlot : NoCopy
 {
   Sys::SpawnChild sys_spawn;

   SpawnSlotState state = SpawnSlot_Ready ;

   friend class SpawnProcess;
   friend class SpawnSet;

  public:

   SpawnSlot() noexcept;

   ~SpawnSlot();

   SpawnSlotState getState() const { return state; }

   int wait();

   bool clean()
    {
     if( state==SpawnSlot_Running ) return false;

     state=SpawnSlot_Ready;

     return true;
    }
 };

/* class SpawnSet */

class SpawnSet : NoCopy
 {
   Sys::SpawnWaitList list;

  public:

   explicit SpawnSet(ulen reserve);

   ~SpawnSet();

   void add(SpawnSlot *slot);

   struct WaitResult
    {
     SpawnSlot *slot;
     int status;
    };

   WaitResult wait();
 };

/* class SpawnProcess */

class SpawnProcess : NoCopy
 {
   ElementPool pool;

   char *wdir = 0 ;
   char *exe_name = 0 ;

   DynArray<char *> args;

   struct EnvRec
    {
     char *str;
     ulen name_len;
     ulen ind;

     EnvRec(char *str_,ulen name_len_,ulen ind_) : str(str_),name_len(name_len_),ind(ind_) {}

     StrLen getName() const { return StrLen(str,name_len); }

     bool operator < (const EnvRec &obj) const
      {
       if( CmpResult cmp=StrCmp(getName(),obj.getName()) ) return cmp<0;

       return ind<obj.ind;
      }

     bool operator != (const EnvRec &obj) const { return StrCmp(getName(),obj.getName())!=0; }
    };

   DynArray<EnvRec> envs;

   bool used = false ;

  private:

   template <class ... TT>
   char * cat(TT ... tt);

   char ** alloc(ulen len);

   char * allocBuf(ulen len);

   char ** buildArgv();

   char ** buildEnvp();

  public:

   explicit SpawnProcess(StrLen exe_name) : SpawnProcess(Empty,exe_name) {}

   SpawnProcess(StrLen wdir,StrLen exe_name);

   ~SpawnProcess();

   void addArg(StrLen str);

   void addArg(ulen reserve,FuncArgType<char *> func)
    {
     char *buf=allocBuf(reserve);

     func(buf);

     buf[reserve]=0;

     args.append_copy(buf);
    }

   void addEnv(StrLen name,StrLen value);

   void addEnv(StrLen str);

   void spawn(SpawnSlot &slot);
 };

} // namespace CCore

#endif

