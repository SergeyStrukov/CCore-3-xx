/* VMakeFileProc.h */
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

#ifndef App_VMakeFileProc_h
#define App_VMakeFileProc_h

#include <CCore/inc/Array.h>
#include <CCore/inc/FileSystem.h>
#include <CCore/inc/SpawnProcess.h>

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

namespace VMake {

#ifndef App_vmaketypedef_h
#define App_vmaketypedef_h

#include "vmake.TypeDef.gen.h"

#endif

/* type CompleteFunction */

using CompleteFunction = Function<void (TypeDef::Rule *rule,int status)> ;

/* classes */

template <class T> class OptMember;

class PExeProc;

class FileProc;

/* class OptMember<T> */

void GuardNoObject();

template <class T>
class OptMember : NoCopy
 {
   InitExitObject<T> obj;

  public:

   OptMember()
    : obj{}
    {
    }

   ~OptMember()
    {
     obj.exit();
    }

   // object ptr

   T * operator + () const { return +obj; }

   bool operator ! () const { return !obj; }

   T * getPtr_unsafe() const { return obj.getPtr_unsafe(); }

   T * getPtr() const
    {
     if( !obj ) GuardNoObject();

     return obj.getPtr_unsafe();
    }

   T & operator * () const { return *getPtr(); }

   T * operator -> () const { return getPtr(); }

   // create/destroy

   template <class ... SS>
   void create(SS && ... ss)
    {
     obj.init( std::forward<SS>(ss)... );
    }

   void destroy()
    {
     obj.exit();
    }
 };

/* class PExeProc */

class PExeProc : NoCopy
 {
  public:

   struct ExeRule : NoCopy
    {
     TypeDef::Rule *rule = 0 ;

     PtrLen<DDL::MapPolyPtr<TypeDef::Exe,TypeDef::Cmd,TypeDef::VMake> > list;
     bool ready = true ;

     void set(TypeDef::Rule *rule_)
      {
       rule=rule_;

       list=rule->cmd.getRange();

       ready=true;
      }
    };

   struct CompleteArg
    {
     ExeRule *obj = 0 ;
    };

   struct CompleteCtx
    {
     CompleteFunction complete;
    };

   struct CompleteExe
    {
     CompleteArg arg;
     CompleteCtx ctx;

     CompleteExe(CompleteArg arg_,CompleteCtx ctx_) : arg(arg_),ctx(ctx_) {}

     void operator () (int status);
    };

  private:

   struct Slot : SpawnSlot
    {
     CompleteArg arg;

     ulen ind = 0 ;

     Slot() noexcept {}
    };

   SimpleArray<Slot> slotbuf;
   SimpleArray<Slot *> slots;
   ulen free;

   SpawnSet waitset;

  private:

   void movetoFree(ulen ind);

   struct WaitOneResult
    {
     Slot *slot;
     int status;
    };

   WaitOneResult waitOneFinish(Slot *slot,int status);

   WaitOneResult waitOne();

   void waitOne(CompleteCtx ctx);

   void setRunning(Slot *slot,CompleteExe complete);

  public:

   explicit PExeProc(ulen pcap);

   ~PExeProc();

   void waitFree(CompleteCtx ctx);

   void waitAll(CompleteCtx ctx);

   void waitAll() noexcept;

   void command(StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,CompleteExe complete);

   void execute(StrLen exe_file,StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,CompleteExe complete);
 };

/* class FileProc */

class FileProc : NoCopy
 {
   FileSystem fs;

   unsigned level = 100 ;

   OptMember<PExeProc> pexe;

  private:

   static int Command(StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env);

   static int Execute(StrLen exe_file,StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env);

   static int VMake(FileProc &file_proc,StrLen file_name,StrLen target,StrLen wdir);

   class BuildFileName;

  public:

   FileProc();

   ~FileProc();

   void prepare(unsigned pcap);

   bool usePExe() const { return +pexe; }

   // check

   bool checkExist(StrLen wdir,StrLen dst);

   bool checkOlder(StrLen wdir,StrLen dst,StrLen src); // dst.noexist OR dst.time < src.time

   // exe

   int exeCmd(StrLen wdir,TypeDef::Exe *cmd);

   int exeCmd(StrLen wdir,TypeDef::Cmd *cmd);

   int exeCmd(StrLen wdir,TypeDef::VMake *cmd);

   int exeRule(StrLen wdir,TypeDef::Rule *rule);

   // pexe

   void startCmd(StrLen wdir,TypeDef::Exe *cmd,PExeProc::CompleteExe complete);

   void startCmd(StrLen wdir,TypeDef::Cmd *cmd,PExeProc::CompleteExe complete);

   void exeRuleList(StrLen wdir,PtrLen<PExeProc::ExeRule> list,CompleteFunction complete);
 };

} // namespace VMake
} // namespace App

#endif

