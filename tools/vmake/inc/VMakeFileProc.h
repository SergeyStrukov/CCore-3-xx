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

#include <CCore/inc/OptMember.h>
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

/* SpawnCommand() */

void SpawnCommand(StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,SpawnSlot &slot);

/* SpawnExecute() */

void SpawnExecute(StrLen exe_file,StrLen wdir,PtrLen<DDL::MapText> args,PtrLen<TypeDef::Env> env,SpawnSlot &slot);

/* classes */

struct ExeRule;

class ExeList;

class PExeProc;

class FileProc;

/* struct ExeRule */

struct ExeRule : NoCopy
 {
  ulen ind = 0 ;

  TypeDef::Rule *rule = 0 ;

  int status = 0 ;
  PtrLen<DDL::MapPolyPtr<TypeDef::Exe,TypeDef::Cmd,TypeDef::VMake> > list;

  void set(TypeDef::Rule *rule_)
   {
    rule=rule_;

    status=0;
    list=rule->cmd.getRange();
   }

  template <class Func>
  bool start(Func func);

  TypeDef::VMake * getVMake();
 };

/* class ExeList */

class ExeList : NoCopy
 {
   ExeRule **buf;
   ulen running;
   ulen ready;
   ulen count;
   CompleteFunction complete;

  private:

   void swap(ulen a,ulen b);

   void moveOut(ulen ind);

   void moveToRunning(ulen ind);

   void moveToVMake(ulen ind);

   void moveToReady(ulen ind);

   template <class Func>
   void step(ulen ind,ExeRule *exeobj,OneOfTypes<TypeDef::Exe,TypeDef::Cmd> *cmd,Func func);

   template <class Func>
   void step(ulen ind,ExeRule *exeobj,TypeDef::VMake *cmd,Func func);

   template <class Func>
   void step(ulen ind,Func func); // ind in [running,ready)

  public:

   ExeList(PtrLen<ExeRule> list,ExeRule * buf[],CompleteFunction complete);

   ulen notEmpty() const { return count; }

   ulen hasReady() const { return ready; }

   ulen hasRunning() const { return running; }

   template <class Func>
   void loop(Func func); // func(ExeRule *,{TypeDef::Exe,TypeDef::Cmd} *)

   template <class Func>
   void vmake(Func func); // func(TypeDef::VMake *)

   void completeObj(ExeRule *exeobj,int status);
 };

/* class PExeProc */

class PExeProc : NoCopy
 {
  public:

   using CompleteArg = ExeRule * ;

   using CompleteCtx = ExeList * ;

   struct CompleteExe
    {
     CompleteArg arg;
     CompleteCtx ctx;

     CompleteExe(CompleteArg arg_,CompleteCtx ctx_) : arg(arg_),ctx(ctx_) {}

     void operator () (int status) { ctx->completeObj(arg,status); }
    };

  private:

   struct Slot : SpawnSlot
    {
     CompleteArg arg = {} ;

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

   void setRunning(Slot *slot,CompleteExe complete);

  public:

   explicit PExeProc(ulen pcap);

   ~PExeProc();

   void waitFree(CompleteCtx ctx);

   void waitOne(CompleteCtx ctx);

   void waitAll(CompleteCtx ctx);

   void waitAll() noexcept;

   void command(StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,CompleteExe complete);

   void execute(StrLen exe_file,StrLen wdir,PtrLen<DDL::MapText> args,PtrLen<TypeDef::Env> env,CompleteExe complete);
 };

/* class FileProc */

class FileProc : NoCopy
 {
   FileSystem fs;

   unsigned level = 100 ;

   OptMember<PExeProc> pexe;

  private:

   static int Command(StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env);

   static int Execute(StrLen exe_file,StrLen wdir,PtrLen<DDL::MapText> args,PtrLen<TypeDef::Env> env);

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

   void exeRuleList(StrLen wdir,PtrLen<ExeRule> list,ExeRule * buf[],CompleteFunction complete);
 };

} // namespace VMake
} // namespace App

#endif

