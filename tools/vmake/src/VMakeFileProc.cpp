/* VMakeFileProc.cpp */
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

#include <inc/VMakeFileProc.h>

#include <CCore/inc/ForLoop.h>
#include <CCore/inc/MakeFileName.h>
#include <CCore/inc/Path.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {
namespace VMake {

/* class CmdLineParser */

StrLen CmdLineParser::next()
 {
  for(; +text && CharIsSpace(*text) ;++text);

  if( !text ) return Empty;

  switch( char ch=*text )
    {
     case '"' :
     case '\'' :
      {
       ++text;

       StrLen line=text;

       for(; +text && *text!=ch ;++text);

       StrLen ret=line.prefix(text);

       if( +text ) ++text;

       return ret;
      }
     break;

     default:
      {
       StrLen line=text;

       for(; +text && !CharIsSpace(*text) ;++text);

       return line.prefix(text);
      }
    }
 }

void AddCmdLine(SpawnProcess &obj,StrLen cmdline)
 {
  CmdLineParser parser(cmdline);

  for(;;)
    {
     StrLen str=parser.next();

     if( !str ) break;

     obj.addArg(str);
    }
 }

/* struct ExeRule */

template <class Func>
bool ExeRule::start(Func func)
 {
  if( status ) return false;

  while( +list )
    {
     auto aptr=list->getPtr();

     ++list;

     bool ret=false;

     aptr.apply( [&] (auto *cmd) { if( cmd ) { func(cmd); ret=true; } } );

     if( ret ) return ret;
    }

  return false;
 }

TypeDef::VMake * ExeRule::getVMake()
 {
  if( status || !list ) return 0;

  auto aptr=list->getPtr();

  if( TypeDef::VMake *ret=aptr.castPtr<TypeDef::VMake>() )
    {
     ++list;

     return ret;
    }

  return 0;
 }

/* class ExeList */

void ExeList::swap(ulen a,ulen b)
 {
  if( a!=b )
    {
     Swap(buf[a],buf[b]);

     buf[a]->ind=a;
     buf[b]->ind=b;
    }
 }

void ExeList::moveOut(ulen ind)
 {
  swap(ind,--ready);

  swap(ready,--count);
 }

void ExeList::moveToRunning(ulen ind)
 {
  swap(running++,ind);
 }

void ExeList::moveToVMake(ulen ind)
 {
  swap(ind,--ready);
 }

void ExeList::moveToReady(ulen ind)
 {
  swap(ind,--running);
 }

template <class Func>
void ExeList::step(ulen ind,ExeRule *exeobj,OneOfTypes<TypeDef::Exe,TypeDef::Cmd> *cmd,Func func)
 {
  moveToRunning(ind);

  func(exeobj,cmd);
 }

template <class Func>
void ExeList::step(ulen ind,ExeRule *exeobj,TypeDef::VMake *,Func)
 {
  --(exeobj->list);

  moveToVMake(ind);
 }

template <class Func>
void ExeList::step(ulen ind,Func func)
 {
  ExeRule *exeobj=buf[ind];

  if( !exeobj->start( [&] (auto *cmd) { step(ind,exeobj,cmd,func); } ) )
    {
     TypeDef::Rule *rule=exeobj->rule;

     moveOut(ind);

     complete(rule,exeobj->status);
    }
 }

ExeList::ExeList(PtrLen<ExeRule> list,ExeRule * buf_[],CompleteFunction complete_)
 : buf(buf_),
   running(0),
   ready(list.len),
   count(list.len),
   complete(complete_)
 {
  for(ulen ind : IndLim(count) )
    {
     ExeRule &obj=list[ind];

     buf[ind]=&obj;

     obj.ind=ind;
    }
 }

template <class Func>
void ExeList::loop(Func func)
 {
  while( running<ready ) step(running,func);
 }

template <class Func>
void ExeList::vmake(Func func)
 {
  if( ready<count )
    {
     TypeDef::VMake *cmd=buf[ready]->getVMake();

     func(cmd);
    }
 }

void ExeList::completeObj(ExeRule *exeobj,int status)
 {
  ulen ind=exeobj->ind;

  exeobj->status=status;

  moveToReady(ind);
 }

/* class PExeProc */

void PExeProc::movetoFree(ulen ind)
 {
  if( free<ind )
    {
     Swap(slots[free],slots[ind]);

     slots[free]->ind=free;
     slots[ind]->ind=ind;
    }

  free++;
 }

auto PExeProc::waitOneFinish(Slot *slot,int status) -> WaitOneResult
 {
  ulen ind=slot->ind;

  movetoFree(ind);

  return {slot,status};
 }

auto PExeProc::waitOne() -> WaitOneResult
 {
  for(;;)
    {
     auto result=waitset.wait();

     if( result.slot ) return waitOneFinish(static_cast<Slot *>(result.slot),result.status);
    }
 }

void PExeProc::waitFree(CompleteCtx ctx)
 {
  if( !free ) waitOne(ctx);
 }

void PExeProc::waitOne(CompleteCtx ctx)
 {
  auto result=waitOne();

  CompleteExe temp(Replace_null(result.slot->arg),ctx);

  temp(result.status);
 }

void PExeProc::waitAll(CompleteCtx ctx)
 {
  while( free<slots.getLen() ) waitOne(ctx);
 }

void PExeProc::waitAll() noexcept
 {
  while( free<slots.getLen() )
    {
     waitOne().slot->arg={};
    }
 }

void PExeProc::setRunning(Slot *slot,CompleteExe complete)
 {
  slot->arg=complete.arg;

  waitset.add(slot);

  free--;
 }

void PExeProc::command(StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,CompleteExe complete)
 {
  if( !free )
    {
     Printf(Exception,"vmake internal : no free slot");
    }

  Slot *slot=slots[free-1];

  slot->clean();

  try
    {
     ShellPath shell;

     SpawnProcess spawn(wdir,shell.get());

     SplitPath split1(shell.get());
     SplitName split2(split1.path);

     spawn.addArg(split2.name);
     spawn.addArg("-c"_c);
     spawn.addArg(cmdline);

     for(TypeDef::Env obj : env ) spawn.addEnv(obj.name,obj.value);

     spawn.spawn(*slot);

     setRunning(slot,complete);
    }
  catch(CatchType)
    {
     complete(1000);
    }
 }

void PExeProc::execute(StrLen exe_file,StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env,CompleteExe complete)
 {
  if( !free )
    {
     Printf(Exception,"vmake internal : no free slot");
    }

  Slot *slot=slots[free-1];

  slot->clean();

  try
    {
     SpawnProcess spawn(wdir,exe_file);

     spawn.addArg(exe_file);

     AddCmdLine(spawn,cmdline);

     for(TypeDef::Env obj : env ) spawn.addEnv(obj.name,obj.value);

     spawn.spawn(*slot);

     setRunning(slot,complete);
    }
  catch(CatchType)
    {
     return complete(1000);
    }
 }

PExeProc::PExeProc(ulen pcap)
 : slotbuf(pcap),
   slots(pcap),
   free(pcap),
   waitset(pcap)
 {
  for(ulen ind : IndLim(pcap) )
    {
     Slot &slot=slotbuf[ind];

     slot.ind=ind;

     slots[ind]=&slot;
    }
 }

PExeProc::~PExeProc()
 {
 }

/* class FileProc::BuildFileName */

class FileProc::BuildFileName : NoCopy
 {
   MakeFileName buf;

   StrLen result;

  private:

   static bool IsRooted(StrLen name)
    {
     return name.len && PathBase::IsSlash(name[0]) ;
    }

   static bool IsRel(StrLen file)
    {
     SplitDev split_dev(file);

     return !split_dev && !IsRooted(file) ;
    }

  public:

   BuildFileName(StrLen wdir,StrLen file)
    {
     if( !wdir )
       {
        result=file;
       }
     else
       {
        if( IsRel(file) )
          {
           result=buf(wdir,file);
          }
        else
          {
           result=file;
          }
       }
    }

   StrLen get() const { return result; }
 };

/* class FileProc */

int FileProc::Command(StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env)
 {
  try
    {
     ShellPath shell;

     SpawnProcess spawn(wdir,shell.get());

     SplitPath split1(shell.get());
     SplitName split2(split1.path);

     spawn.addArg(split2.name);
     spawn.addArg("-c"_c);
     spawn.addArg(cmdline);

     for(TypeDef::Env obj : env ) spawn.addEnv(obj.name,obj.value);

     SpawnSlot slot;

     spawn.spawn(slot);

     return slot.wait();
    }
  catch(CatchType)
    {
     return 1000;
    }
 }

int FileProc::Execute(StrLen exe_file,StrLen wdir,StrLen cmdline,PtrLen<TypeDef::Env> env)
 {
  try
    {
     SpawnProcess spawn(wdir,exe_file);

     spawn.addArg(exe_file);

     AddCmdLine(spawn,cmdline);

     for(TypeDef::Env obj : env ) spawn.addEnv(obj.name,obj.value);

     SpawnSlot slot;

     spawn.spawn(slot);

     return slot.wait();
    }
  catch(CatchType)
    {
     return 1000;
    }
 }

FileProc::FileProc()
 {
 }

FileProc::~FileProc()
 {
 }

void FileProc::prepare(unsigned pcap)
 {
  if( pcap>1 ) pexe.create( Cap<unsigned>(0,pcap,100) );
 }

 // check

bool FileProc::checkExist(StrLen wdir,StrLen dst)
 {
  BuildFileName dst1(wdir,dst);

  return fs.getFileType(dst1.get())==FileType_file;
 }

bool FileProc::checkOlder(StrLen wdir,StrLen dst,StrLen src)
 {
  BuildFileName dst1(wdir,dst);
  BuildFileName src1(wdir,src);

  auto dst_time=fs.getFileUpdateTime(dst1.get());
  auto src_time=fs.getFileUpdateTime(src1.get());

  return dst_time<src_time;
 }

 // exe

int FileProc::exeCmd(StrLen wdir,TypeDef::Exe *cmd)
 {
  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen exe_file=cmd->exe;
  StrLen cmdline=cmd->cmdline;
  StrLen new_wdir=cmd->wdir;
  PtrLen<TypeDef::Env> env=cmd->env;

  if( +new_wdir )
    {
     try
       {
        BuildFileName wdir1(wdir,new_wdir);

        return Execute(exe_file,wdir1.get(),cmdline,env);
       }
     catch(CatchType)
       {
        return 1000;
       }
    }
  else
    {
     return Execute(exe_file,wdir,cmdline,env);
    }
 }

int FileProc::exeCmd(StrLen wdir,TypeDef::Cmd *cmd)
 {
  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen cmdline=cmd->cmdline;
  StrLen new_wdir=cmd->wdir;
  PtrLen<TypeDef::Env> env=cmd->env;

  if( +new_wdir )
    {
     try
       {
        BuildFileName wdir1(wdir,new_wdir);

        return Command(wdir1.get(),cmdline,env);
       }
     catch(CatchType)
       {
        return 1000;
       }
    }
  else
    {
     return Command(wdir,cmdline,env);
    }
 }

int FileProc::exeCmd(StrLen wdir,TypeDef::VMake *cmd)
 {
  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen file_name=cmd->file;
  StrLen target=cmd->target;
  StrLen new_wdir=cmd->wdir;

  if( +new_wdir )
    {
     try
       {
        LockUse lock(level);

        BuildFileName wdir1(wdir,new_wdir);

        return VMake(*this,file_name,target,wdir1.get());
       }
     catch(CatchType)
       {
        return 1000;
       }
    }
  else
    {
     try
       {
        LockUse lock(level);

        return VMake(*this,file_name,target,wdir);
       }
     catch(CatchType)
       {
        return 1000;
       }
    }
 }

int FileProc::exeRule(StrLen wdir,TypeDef::Rule *rule)
 {
  for(auto cmd : rule->cmd.getRange() )
    {
     int ret=0;

     cmd.getPtr().apply( [&] (auto *cmd) { if( cmd ) ret=exeCmd(wdir,cmd); } );

     if( ret ) return ret;
    }

  return 0;
 }

 // pexe

void FileProc::startCmd(StrLen wdir,TypeDef::Exe *cmd,PExeProc::CompleteExe complete)
 {
  pexe->waitFree(complete.ctx);

  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen exe_file=cmd->exe;
  StrLen cmdline=cmd->cmdline;
  StrLen new_wdir=cmd->wdir;
  PtrLen<TypeDef::Env> env=cmd->env;

  if( +new_wdir )
    {
     try
       {
        BuildFileName wdir1(wdir,new_wdir);

        pexe->execute(exe_file,wdir1.get(),cmdline,env,complete);
       }
     catch(CatchType)
       {
        complete(1000);
       }
    }
  else
    {
     pexe->execute(exe_file,wdir,cmdline,env,complete);
    }
 }

void FileProc::startCmd(StrLen wdir,TypeDef::Cmd *cmd,PExeProc::CompleteExe complete)
 {
  pexe->waitFree(complete.ctx);

  StrLen echo=cmd->echo;

  Printf(Con,"#;\n",echo);

  StrLen cmdline=cmd->cmdline;
  StrLen new_wdir=cmd->wdir;
  PtrLen<TypeDef::Env> env=cmd->env;

  if( +new_wdir )
    {
     try
       {
        BuildFileName wdir1(wdir,new_wdir);

        return pexe->command(wdir1.get(),cmdline,env,complete);
       }
     catch(CatchType)
       {
        complete(1000);
       }
    }
  else
    {
     pexe->command(wdir,cmdline,env,complete);
    }
 }

void FileProc::exeRuleList(StrLen wdir,PtrLen<ExeRule> list,ExeRule * buf[],CompleteFunction complete)
 {
  if( !list ) return;

  Printf(Con,"vmake : start #; rules\n",list.len);

  try
    {
     ExeList exelist(list,buf,complete);

     while( exelist.notEmpty() )
       {
        while( exelist.hasReady() )
          {
           exelist.loop( [&] (ExeRule *obj,auto *cmd) { startCmd(wdir,cmd,{obj,&exelist}); } );

           if( exelist.hasRunning() ) pexe->waitOne(&exelist);
          }

        exelist.vmake( [&] (TypeDef::VMake *cmd) { exeCmd(wdir,cmd); } );
       }
    }
  catch(...)
    {
     pexe->waitAll();

     throw;
    }

#if 0

  for(auto &obj : list )
    {
     int status=exeRule(wdir,obj.rule);

     complete(obj.rule,status);
    }

#endif
 }

} // namespace VMake
} // namespace App

