/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: PTPSecureClient 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/net/AsyncUDPDevice.h>
#include <CCore/inc/net/PKE.h>
#include <CCore/inc/net/PSec.h>
#include <CCore/inc/net/PTPClientDevice.h>
#include <CCore/inc/net/HFSClientDevice.h>
#include <CCore/inc/net/HFSFileSystemDevice.h>

#include <CCore/inc/AsyncFile.h>
#include <CCore/inc/AsyncBinaryFile.h>
#include <CCore/inc/AsyncFileToMem.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Cmp.h>
#include <CCore/inc/CmdInput.h>
#include <CCore/inc/Scanf.h>

#include <CCore/inc/ReadCon.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/BinaryFile.h>

#include "Config.h"

namespace App {

/* using */

using namespace CCore;

/* CreateKey() */

Net::PSec::AbstractHashFunc * CreateKey(const TypeDef::Key &key)
 {
  return Net::PSec::CreateKeyedHash(Net::PSec::HashID(key.hash_id),key.key.getRange());
 }

/* TakeString() */

StrLen TakeString(StrLen &text)
 {
  StrLen cur=text;

  for(; +cur && !CharIsSpace(*cur) ;++cur);

  StrLen ret=text.prefix(cur);

  text=cur;

  return ret;
 }

/* classes */

class CurPath;

class FileList;

class ClientID;

class ConnectEngine;

class Executor;

class CommandTarget;

class CommandEngine;

class DataEngine;

/* class CurPath */

class CurPath : public NoCopyBase<PathBase>
 {
   char buf[MaxPathLen];
   ulen len;

  private:

   void startRoot();

   void startHome();

   void addName(StrLen name);

   void back();

   void nextName(StrLen name);

   void lastName(StrLen name,bool file_flag);

   void nextPath(StrLen path,bool file_flag);

  public:

   CurPath();

   CurPath(const CurPath &cur,StrLen path,bool file_flag);

   operator StrLen() const { return StrLen(buf,len); }

   void copy(const CurPath &obj);
 };

void CurPath::startRoot()
 {
  buf[0]='/';
  len=1;
 }

void CurPath::startHome()
 {
  buf[0]='~';
  len=1;
 }

void CurPath::addName(StrLen name)
 {
  if( buf[len-1]=='/' )
    {
     if( name.len>MaxPathLen-len )
       {
        Printf(Exception,"Too long path");
       }
    }
  else
    {
     if( len>=MaxPathLen || name.len>(MaxPathLen-1)-len )
       {
        Printf(Exception,"Too long path");
       }

     buf[len++]='/';
    }

  name.copyTo(buf+len);

  len+=name.len;
 }

void CurPath::back()
 {
  if( len==1 )
    {
     Printf(Exception,"No back path");
    }

  for(ulen i=len; i-- ;)
    {
     if( buf[i]=='/' )
       {
        if( i )
          len=i;
        else
          startRoot();

        return;
       }
    }

  Printf(Exception,"No back path");
 }

void CurPath::nextName(StrLen name)
 {
  if( IsDot(name) )
    {
     // do nothing
    }
  else if( IsDotDot(name) )
    {
     back();
    }
  else
    {
     addName(name);
    }
 }

void CurPath::lastName(StrLen name,bool file_flag)
 {
  if( IsDot(name) )
    {
     if( file_flag )
       {
        Printf(Exception,"Bad file path");
       }

     // do nothing
    }
  else if( IsDotDot(name) )
    {
     if( file_flag )
       {
        Printf(Exception,"Bad file path");
       }

     back();
    }
  else
    {
     addName(name);
    }
 }

void CurPath::nextPath(StrLen path,bool file_flag)
 {
  while( +path )
    {
     SplitDirName split(path);

     if( !split )
       {
        lastName(path,file_flag);

        return;
       }
     else
       {
        nextName(split.dir_name);

        path=split.path;
       }
    }

  Printf(Exception,"Empty name");
 }

CurPath::CurPath()
 {
  startRoot();
 }

CurPath::CurPath(const CurPath &cur,StrLen path,bool file_flag)
 {
  if( !path )
    {
     Printf(Exception,"Empty path");
    }

  char ch=*path;

  if( IsSlash(ch) )
    {
     startRoot();

     ++path;

     if( !path ) return;
    }
  else if( IsTilde(ch) )
    {
     startHome();

     ++path;

     if( !path ) return;

     if( IsSlash(*path) )
       {
        ++path;

        if( !path )
          {
           Printf(Exception,"Bad path");
          }
       }
     else
       {
        Printf(Exception,"Bad path");
       }
    }
  else
    {
     copy(cur);
    }

  nextPath(path,file_flag);
 }

void CurPath::copy(const CurPath &obj)
 {
  StrLen str(obj);

  str.copyTo(buf);

  len=str.len;
 }

/* class FileList */

class FileList : NoCopy
 {
   ElementPool pool;

   Collector<StrLen> dirs;
   Collector<StrLen> files;

   PtrLen<StrLen> dir_list;
   PtrLen<StrLen> file_list;

  public:

   FileList();

   ~FileList();

   void add(StrLen file_name,FileType file_type);

   void complete();

   PtrLen<const StrLen> getDirs() const { return dir_list; }

   PtrLen<const StrLen> getFiles() const { return file_list; }
 };

FileList::FileList()
 : pool(4_KByte)
 {
 }

FileList::~FileList()
 {
 }

void FileList::add(StrLen file_name,FileType file_type)
 {
  switch( file_type )
    {
     case FileType_dir : dirs.append_copy(pool.dup(file_name)); break;

     case FileType_file : files.append_copy(pool.dup(file_name)); break;
    }
 }

void FileList::complete()
 {
  dir_list=dirs.flat();
  file_list=files.flat();

  auto less = [] (StrLen a,StrLen b) { return StrLess(a,b); } ;

  IncrSort(dir_list,less);
  IncrSort(file_list,less);
 }

/* class ClientID */

class ClientID : public Net::PSec::AbstractClientID
 {
   StrLen name;

  public:

   explicit ClientID(StrLen name);

   ~ClientID();

   // Net::PSec::AbstractClientID

   virtual uint8 getLen() const;

   virtual void getID(uint8 buf[ /* Len */ ]) const;
 };

ClientID::ClientID(StrLen name_)
 : name(name_)
 {
  ulen len=name.len;

  if( len>MaxUInt<uint8> )
    {
     Printf(Exception,"App: too long client name");
    }
 }

ClientID::~ClientID()
 {
 }

 // Net::PSec::AbstractClientID

uint8 ClientID::getLen() const
 {
  return (uint8)name.len;
 }

void ClientID::getID(uint8 buf[ /* Len */ ]) const
 {
  name.copyTo(buf);
 }

/* class ConnectEngine */

class ConnectEngine : public Funchor_nocopy
 {
   Net::AsyncUDPEndpointDevice udp;

   ObjMaster udp_master;

   Net::PSec::ClientNegotiant neg;

   Sem sem;

  private:

   void done();

   Function<void (void)> function_done() { return FunctionOf(this,&ConnectEngine::done); }

  public:

   explicit ConnectEngine(const TypeDef::PTPSecureConfig *cfg);

   ~ConnectEngine();

   void connect(Net::PSec::MasterKeyPtr &ret,MSec timeout=DefaultTimeout);
 };

void ConnectEngine::done()
 {
  sem.give();
 }

ConnectEngine::ConnectEngine(const TypeDef::PTPSecureConfig *cfg)
 : udp(cfg->pke_port,Net::UDPoint(Net::IPAddress(cfg->server_ip),cfg->server_pke_port)),
   udp_master(udp,"udp"),
   neg("udp",function_done())
 {
  ClientID client_id(cfg->name);
  Net::PSec::PrimeKeyPtr client_key(CreateKey(cfg->key));
  Net::PSec::PrimeKeyPtr server_key(CreateKey(cfg->server_key));

  neg.prepare(cfg->psec_port,client_id,std::move(client_key),std::move(server_key));
 }

ConnectEngine::~ConnectEngine()
 {
 }

void ConnectEngine::connect(Net::PSec::MasterKeyPtr &ret,MSec timeout)
 {
  Net::AsyncUDPEndpointDevice::StartStop start_stop(udp);

  Net::PSec::AlgoSet algo_set(Net::PSec::AlgoSet::DefaultSet);

  neg.start(algo_set);

  if( sem.take(timeout) )
    {
     if( neg.getState()==Net::PSec::ClientNegotiant::State_Done )
       {
        neg.getSessionKey(ret);

        return;
       }

     Printf(Exception,"App: cannot connect #; #;",neg.getState(),neg.getError());
    }

  Printf(Exception,"App: cannot connect #; timeout",neg.getState());
 }

/* class Executor */

class Executor : NoCopy
 {
   CurPath cur;
   AsyncFileSystem fs;

  private:

   void do_dir(StrLen dir);

  public:

   Executor();

   ~Executor();

   StrLen getCurPath() const { return cur; }

   void cmd_dir();
   void cmd_dir(StrLen arg);
   void cmd_cd(StrLen arg);

   void cmd_mkdir(StrLen arg);
   void cmd_rmdir(StrLen arg,bool recursive);

   void cmd_mkfile(StrLen arg);
   void cmd_del(StrLen arg);

   void cmd_type(StrLen arg);
   void cmd_add(StrLen arg,StrLen line);

   void cmd_put(StrLen file_name,StrLen arg);
   void cmd_get(StrLen file_name,StrLen arg);

   void cmd_fileinfo(StrLen arg);
 };

void Executor::do_dir(StrLen dir)
 {
  AsyncFileListToMem list(fs,dir);

  FileList file_list;

  list.apply( [&file_list] (StrLen file_name,FileType file_type) { file_list.add(file_name,file_type); } );

  file_list.complete();

  Printf(Con,"-----\n");

  for(auto name : file_list.getDirs() ) Printf(Con,"#;\n",name);

  Printf(Con,"-----\n");

  for(auto name : file_list.getFiles() ) Printf(Con,"#;\n",name);
 }

Executor::Executor()
 : fs("host")
 {
 }

Executor::~Executor()
 {
 }

void Executor::cmd_dir()
 {
  do_dir(cur);
 }

void Executor::cmd_dir(StrLen arg)
 {
  CurPath path(cur,arg,false);

  do_dir(path);
 }

void Executor::cmd_cd(StrLen arg)
 {
  CurPath path(cur,arg,false);

  if( fs.getFileType(path)!=FileType_dir )
    {
     Printf(Exception,"cd: no such directory");
    }

  cur.copy(path);
 }

void Executor::cmd_mkdir(StrLen arg)
 {
  CurPath path(cur,arg,false);

  fs.createDir(path);
 }

void Executor::cmd_rmdir(StrLen arg,bool recursive)
 {
  CurPath path(cur,arg,false);

  fs.deleteDir(path,recursive);
 }

void Executor::cmd_mkfile(StrLen arg)
 {
  CurPath path(cur,arg,true);

  fs.createFile(path);
 }

void Executor::cmd_del(StrLen arg)
 {
  CurPath path(cur,arg,true);

  fs.deleteFile(path);
 }

void Executor::cmd_type(StrLen arg)
 {
  CurPath path(cur,arg,true);

  PartAsyncFileToMem file("host",path);

  while( file.more() )
    {
     Putobj(Con,StrLen(Mutate<const char>(file.read())));
    }
 }

void Executor::cmd_add(StrLen arg,StrLen line)
 {
  CurPath path(cur,arg,true);

  PrintAsyncFile out("host",path,Open_ToAppend);

  Putobj(out,line);
  Putch(out,'\n');
 }

void Executor::cmd_put(StrLen file_name,StrLen arg)
 {
  CurPath path(cur,arg,true);

  PartFileToMem file(file_name);
  AsyncBinaryFile out("host",path);

  while( file.more() ) out.put(file.read());
 }

void Executor::cmd_get(StrLen file_name,StrLen arg)
 {
  CurPath path(cur,arg,true);

  PartAsyncFileToMem file("host",path);
  BinaryFile out(file_name);

  while( file.more() ) out.put(file.read());
 }

void Executor::cmd_fileinfo(StrLen arg) // TODO
 {
  CurPath path(cur,arg,true);

  auto file_type=fs.getFileType(path);
  auto file_time=fs.getFileUpdateTime(path);

  Printf(Con,"#; #;\n",file_type,file_time);
 }

/* class CommandTarget */

class CommandTarget : public CmdInput::Target
 {
   Executor exec;

   bool run_flag = true ;

  private:

   void cmd_nothing(StrLen arg);
   void cmd_exit(StrLen arg);
   void cmd_help(StrLen arg);

   void cmd_pwd(StrLen arg);
   void cmd_dir(StrLen arg);
   void cmd_cd(StrLen arg);
   void cmd_mkdir(StrLen arg);
   void cmd_rmdir(StrLen arg);
   void cmd_mkfile(StrLen arg);
   void cmd_del(StrLen arg);
   void cmd_type(StrLen arg);
   void cmd_add(StrLen arg);
   void cmd_put(StrLen arg);
   void cmd_get(StrLen arg);

   void cmd_fileinfo(StrLen arg);

   virtual void buildCmdList(CmdInput &input);

  public:

   CommandTarget();

   ~CommandTarget();

   operator bool() const { return run_flag; }

   StrLen getCurPath() const { return exec.getCurPath(); }
 };

void CommandTarget::cmd_nothing(StrLen)
 {
  // do nothing
 }

void CommandTarget::cmd_exit(StrLen)
 {
  run_flag=false;
 }

void CommandTarget::cmd_help(StrLen)
 {
  Printf(Con,"commands: help exit pwd dir cd mkdir rmdir mkfile del type add put get fileinfo\n");
 }

void CommandTarget::cmd_pwd(StrLen arg)
 {
  if( +arg )
    {
     Printf(Exception,"pwd: no argument is required");
    }
  else
    {
     Printf(Con,"#;\n",getCurPath());
    }
 }

void CommandTarget::cmd_dir(StrLen arg)
 {
  if( +arg )
    {
     exec.cmd_dir(arg);
    }
  else
    {
     exec.cmd_dir();
    }
 }

void CommandTarget::cmd_cd(StrLen arg)
 {
  if( +arg )
    {
     exec.cmd_cd(arg);
    }
  else
    {
     Printf(Exception,"cd: path is not given");
    }
 }

void CommandTarget::cmd_mkdir(StrLen arg)
 {
  if( +arg )
    {
     exec.cmd_mkdir(arg);
    }
  else
    {
     Printf(Exception,"mkdir: path is not given");
    }
 }

void CommandTarget::cmd_rmdir(StrLen arg)
 {
  if( +arg )
    {
     if( ProbeChar(arg,'-') )
       {
        if( ProbeChar(arg,'r') )
          {
           SkipSpace(arg);

           exec.cmd_rmdir(arg,true);
          }
        else
          {
           Printf(Exception,"rmdir: bad option");
          }
       }
     else
       {
        exec.cmd_rmdir(arg,false);
       }
    }
  else
    {
     Printf(Exception,"rmdir: path is not given");
    }
 }

void CommandTarget::cmd_mkfile(StrLen arg)
 {
  if( +arg )
    {
     exec.cmd_mkfile(arg);
    }
  else
    {
     Printf(Exception,"mkfile: path is not given");
    }
 }

void CommandTarget::cmd_del(StrLen arg)
 {
  if( +arg )
    {
     exec.cmd_del(arg);
    }
  else
    {
     Printf(Exception,"del: path is not given");
    }
 }

void CommandTarget::cmd_type(StrLen arg)
 {
  if( +arg )
    {
     exec.cmd_type(arg);
    }
  else
    {
     Printf(Exception,"type: path is not given");
    }
 }

void CommandTarget::cmd_add(StrLen arg)
 {
  if( +arg )
    {
     StrLen file=TakeString(arg);

     SkipSpace(arg);

     exec.cmd_add(file,arg);
    }
  else
    {
     Printf(Exception,"add: path is not given");
    }
 }

void CommandTarget::cmd_put(StrLen arg)
 {
  if( +arg )
    {
     StrLen file_name=TakeString(arg);

     SkipSpace(arg);

     exec.cmd_put(file_name,arg);
    }
  else
    {
     Printf(Exception,"put: path is not given");
    }
 }

void CommandTarget::cmd_get(StrLen arg)
 {
  if( +arg )
    {
     StrLen file_name=TakeString(arg);

     SkipSpace(arg);

     exec.cmd_get(file_name,arg);
    }
  else
    {
     Printf(Exception,"get: path is not given");
    }
 }

void CommandTarget::cmd_fileinfo(StrLen arg)
 {
  if( +arg )
    {
     exec.cmd_fileinfo(arg);
    }
  else
    {
     Printf(Exception,"fileinfo: path is not given");
    }
 }

void CommandTarget::buildCmdList(CmdInput &input)
 {
  addCommand(input,"",&CommandTarget::cmd_nothing);
  addCommand(input,"exit",&CommandTarget::cmd_exit);
  addCommand(input,"help",&CommandTarget::cmd_help);

  addCommand(input,"pwd",&CommandTarget::cmd_pwd);
  addCommand(input,"dir",&CommandTarget::cmd_dir);
  addCommand(input,"cd",&CommandTarget::cmd_cd);
  addCommand(input,"mkdir",&CommandTarget::cmd_mkdir);
  addCommand(input,"rmdir",&CommandTarget::cmd_rmdir);
  addCommand(input,"mkfile",&CommandTarget::cmd_mkfile);
  addCommand(input,"del",&CommandTarget::cmd_del);
  addCommand(input,"type",&CommandTarget::cmd_type);
  addCommand(input,"add",&CommandTarget::cmd_add);
  addCommand(input,"put",&CommandTarget::cmd_put);
  addCommand(input,"get",&CommandTarget::cmd_get);

  addCommand(input,"fileinfo",&CommandTarget::cmd_fileinfo);
 }

CommandTarget::CommandTarget()
 {
 }

CommandTarget::~CommandTarget()
 {
 }

/* class CommandEngine */

class CommandEngine : NoCopy
 {
   ReadCon con;
   CommandTarget target;
   CmdInput input;
   ReportException report;

   static const ulen MaxArgLen = 80 ;

   static const char BadChar = '?' ;

   char arg[MaxArgLen];
   ulen arg_len;

  private:

   bool inputArg();

   void command();

  public:

   CommandEngine();

   ~CommandEngine();

   void run();
 };

bool CommandEngine::inputArg()
 {
  arg_len=0;

  for(;;)
    {
     switch( char ch=con.get() )
       {
        case '\b' :
         {
          if( arg_len>0 )
            {
             arg_len--;

             con.put("\b \b",3);
            }
          else
            {
             con.put('\b');

             return false;
            }
         }
        break;

        case '\n' : case '\r' :
         {
          con.put("\r\n",2);

          return true;
         }
        break;

        default:
         {
          if( CharIsPrintable(ch) && arg_len<MaxArgLen )
            {
             arg[arg_len++]=ch;

             con.put(ch);
            }
         }
       }
    }
 }

void CommandEngine::command()
 {
  con.put(target.getCurPath());
  con.put("> ");

  input.start();

  for(;;)
    {
     switch( char ch=con.get() )
       {
        case ' ' :
         {
          auto result=input.finish();

          if( +result )
            {
             con.put(' ');

             if( inputArg() )
               {
                result(StrLen(arg,arg_len),report);

                return;
               }
             else
               {
                // do nothing
               }
            }
          else
            {
             // do nothing
            }
         }
        break;

        case '\r' : case '\n' :
         {
          auto result=input.finish();

          if( +result )
            {
             con.put("\r\n",2);

             result(StrLen(),report);

             return;
            }
          else
            {
             // do nothing
            }
         }
        break;

        case '\t' :
         {
          auto result=input.complete();

          if( result.count==1 )
            {
             con.put(result.str);
             input.put(result.str);
            }
         }
        break;

        case '\b' :
         {
          if( input.back() )
            {
             con.put("\b \b",3);
            }
         }
        break;

        default:
         {
          if( input.put(ch) )
            con.put(ch);
          else
            con.put(BadChar);
         }
       }
    }
 }

CommandEngine::CommandEngine()
 : input(target)
 {
 }

CommandEngine::~CommandEngine()
 {
 }

void CommandEngine::run()
 {
  while( target ) command();
 }

/* class DataEngine */

class DataEngine : NoCopy
 {
   Net::AsyncUDPEndpointDevice udp;

   ObjMaster udp_master;

   Net::PSec::EndpointDevice psec;

   ObjMaster psec_master;

   Net::PTP::ClientDevice ptp;

   ObjMaster ptp_master;

   Net::HFS::ClientDevice hfs;

   ObjMaster hfs_master;

   Net::HFS::FileSystemDevice fs;

   ObjMaster fs_master;

  public:

   DataEngine(const TypeDef::PTPSecureConfig *cfg,const Net::PSec::MasterKey &skey);

   ~DataEngine();

   void run();
 };

DataEngine::DataEngine(const TypeDef::PTPSecureConfig *cfg,const Net::PSec::MasterKey &skey)
 : udp(cfg->psec_port,Net::UDPoint(Net::IPAddress(cfg->server_ip),cfg->server_psec_port)),
   udp_master(udp,"udp"),
   psec("udp",skey,1_min),
   psec_master(psec,"psec"),
   ptp("psec"),
   ptp_master(ptp,"ptp"),
   hfs("ptp"),
   hfs_master(hfs,"hfs"),
   fs("hfs"),
   fs_master(fs,"host")
 {
 }

DataEngine::~DataEngine()
 {
 }

void DataEngine::run()
 {
  Net::AsyncUDPEndpointDevice::StartStop start_stop(udp);

  ptp.support_guarded();

  CommandEngine engine;

  engine.run();
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     {
      Putobj(Con,"--- PTPSecureClient 1.00 ---\n--- Copyright (c) 2015 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc!=2 )
        {
         Putobj(Con,"Usage: CCore-PTPSecureClient <config.ddl>\n");

         return 2;
        }

      Config cfg(argv[1]);

      cfg.show();

      Net::PSec::MasterKeyPtr skey;

      {
       ConnectEngine engine(cfg);

       engine.connect(skey);
      }

      {
       DataEngine engine(cfg,*skey);

       engine.run();
      }
     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }




