/* test4031.PTPSec.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/net/AsyncUDPDevice.h>
#include <CCore/inc/net/PKE.h>
#include <CCore/inc/net/PSec.h>
#include <CCore/inc/net/PTPClientDevice.h>
#include <CCore/inc/net/HFSClientDevice.h>
#include <CCore/inc/net/HFSFileSystemDevice.h>

#include <CCore/inc/CmdInput.h>
#include <CCore/inc/ReadCon.h>
#include <CCore/inc/Scanf.h>
#include <CCore/inc/Path.h>
#include <CCore/inc/AsyncFile.h>
#include <CCore/inc/AsyncFileToMem.h>
#include <CCore/inc/String.h>
#include <CCore/inc/ElementPool.h>
#include <CCore/inc/CompactList.h>

namespace App {

namespace Private_4031 {

/* TakeString() */

StrLen TakeString(StrLen &text)
 {
  StrLen cur=text;

  for(; +cur && !CharIsSpace(*cur) ;++cur);

  StrLen ret=text.prefix(cur);

  text=cur;

  return ret;
 }

/* struct Key */

struct Key
 {
  Net::PSec::HashID hash_id = Net::PSec::HashID_SHA1 ;
  PtrLen<const uint8> key;

  Key() {}

  Key(Net::PSec::HashID hash_id_,PtrLen<const uint8> key_) : hash_id(hash_id_),key(key_) {}
 };

/* struct Config */

struct Config
 {
  Net::UDPort pke_port = Net::PKEClientUDPort ;
  Net::UDPort psec_port = Net::PSecClientUDPort ;

  StrLen name;

  Key client_key;
  Key server_key;

  Config()
   {
    // server

    static const uint8 ServerKey[]=
     {
      0x00, 0x19, 0x9B, 0xFA,  0x13, 0x64, 0xD0, 0xF4,  0x61, 0x1E, 0x55, 0x50,  0x57, 0x52, 0xFB, 0x0C,
      0x4A, 0xA0, 0x4A, 0xF2,  0x83, 0x37, 0x6E, 0x01,  0x50, 0x13, 0x6D, 0xB1,  0x04, 0xA7, 0x82, 0x10
     };

    server_key=Key(Net::PSec::HashID_SHA512,Range(ServerKey));

    // client

    name="admin";

    static const uint8 ClientKey[]=
     {
      0x9E, 0x3F, 0x83, 0x9B,  0xE3, 0xEA, 0x4A, 0xD9,  0xEE, 0xA1, 0x49, 0x05,  0x46, 0xE6, 0xC8, 0x7C,
      0xA7, 0x0D, 0xF2, 0x1C,  0x30, 0xF5, 0x91, 0x8B,  0x3D, 0xCF, 0x90, 0x0A,  0xEA, 0xB4, 0xA8, 0x25
     };

    client_key=Key(Net::PSec::HashID_SHA512,Range(ClientKey));
   }
 };

/* CreateKey() */

Net::PSec::AbstractHashFunc * CreateKey(Key key)
 {
  return Net::PSec::CreateKeyedHash(key.hash_id,key.key);
 }

/* class ClientID */

class ClientID : public Net::PSec::AbstractClientID
 {
   StrLen name;

  public:

   explicit ClientID(StrLen name_)
    : name(name_)
    {
     ulen len=name.len;

     if( len>MaxUInt<uint8> )
       {
        Printf(Exception,"too long client name");
       }
    }

   ~ClientID()
    {
    }

   // Net::PSec::AbstractClientID

   virtual uint8 getLen() const
    {
     return (uint8)name.len;
    }

   virtual void getID(uint8 buf[ /* Len */ ]) const
    {
     name.copyTo(buf);
    }
 };

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

   explicit ConnectEngine(const Config &cfg);

   ~ConnectEngine();

   void connect(Net::PSec::MasterKeyPtr &ret);
 };

void ConnectEngine::done()
 {
  sem.give();
 }

ConnectEngine::ConnectEngine(const Config &cfg)
 : udp(cfg.pke_port,Net::UDPoint(127,0,0,1,Net::PKEServerUDPort)),
   udp_master(udp,"udp"),
   neg("udp",function_done())
 {
  ClientID client_id(cfg.name);
  Net::PSec::PrimeKeyPtr client_key(CreateKey(cfg.client_key));
  Net::PSec::PrimeKeyPtr server_key(CreateKey(cfg.server_key));

  neg.prepare(cfg.psec_port,client_id,std::move(client_key),std::move(server_key));
 }

ConnectEngine::~ConnectEngine()
 {
 }

void ConnectEngine::connect(Net::PSec::MasterKeyPtr &ret)
 {
  Net::AsyncUDPEndpointDevice::StartStop start_stop(udp);

  Net::PSec::AlgoSet algo_set(Net::PSec::AlgoSet::DefaultSet);

  neg.start(algo_set);

  if( sem.take(10_sec) )
    {
     if( neg.getState()==Net::PSec::ClientNegotiant::State_Done )
       {
        neg.getSessionKey(ret);

        return;
       }

     Printf(Exception,"Cannot connect #; #;",neg.getState(),neg.getError());
    }

  Printf(Exception,"Cannot connect #; timeout",neg.getState());
 }

/* class CommandEngine */

class CommandEngine : public NoCopyBase<CmdInput::Target>
 {
   CmdInputCon<ReadCon> cmd_input;
   bool run_flag;

  private:

   Path cur;

   AsyncFileSystem fs;

  private:

   class BuildPath : public Path
    {
      enum Type
       {
        FromRoot,
        FromHome,
        Relative
       };

      static Type PathType(StrLen path)
       {
        if( +path )
          {
           char ch=*path;

           if( IsSlash(ch) )
             {
              return FromRoot;
             }
           else if( IsTilde(ch) )
             {
              return FromHome;
             }
           else
             {
              return Relative;
             }
          }
        else
          {
           return Relative;
          }
       }

     public:

      BuildPath(const Path &cur,StrLen path)
       : Path(BeginEmpty)
       {
        switch( PathType(path) )
          {
           case FromRoot :
           case FromHome :
            {
             addPath(path);
            }
           break;

           case Relative :
            {
             copyPath(cur);

             addPath(path);
            }
           break;
          }
       }

      ~BuildPath()
       {
       }
    };

   void do_dir(StrLen dir);
   void do_cd(const Path &dir);
   void do_mkdir(StrLen dir);
   void do_rmdir(StrLen dir,bool recursive);
   void do_mkfile(StrLen file);
   void do_del(StrLen file);
   void do_type(StrLen file);
   void do_add(StrLen file,StrLen line);

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

   virtual void buildCmdList(CmdInput &input);

  public:

   CommandEngine();

   ~CommandEngine();

   void run();
 };

void CommandEngine::do_dir(StrLen dir)
 {
  AsyncFileListToMem list(fs,dir);

  ElementPool pool(4_KByte);
  CompactList<StrLen> dir_list;
  CompactList<StrLen> file_list;

  list.apply( [&] (StrLen file_name,FileType file_type)
                  {
                   switch( file_type )
                     {
                      case FileType_dir : dir_list.ins(pool.dup(file_name));  break;

                      case FileType_file : file_list.ins(pool.dup(file_name)); break;
                     }

                  } );

  Printf(Con,"-----\n");

  for(auto name : dir_list ) Printf(Con,"#;\n",name);

  Printf(Con,"-----\n");

  for(auto name : file_list ) Printf(Con,"#;\n",name);
 }

void CommandEngine::do_cd(const Path &dir)
 {
  if( fs.getFileType(dir)!=FileType_dir )
    {
     Printf(Exception,"cd: no such directory");
    }

  cur.copyPath(dir);
 }

void CommandEngine::do_mkdir(StrLen dir)
 {
  fs.createDir(dir);
 }

void CommandEngine::do_rmdir(StrLen dir,bool recursive)
 {
  fs.deleteDir(dir,recursive);
 }

void CommandEngine::do_mkfile(StrLen file)
 {
  fs.createFile(file);
 }

void CommandEngine::do_del(StrLen file)
 {
  fs.deleteFile(file);
 }

void CommandEngine::do_type(StrLen file)
 {
  Path path("host");

  path.addPath(file);

  AsyncFileToMem map(path,4_KByte);

  Putobj(Con,StrLen(Mutate<const char>(Range(map))));
 }

void CommandEngine::do_add(StrLen file,StrLen line)
 {
  Path path("host");

  path.addPath(file);

  PrintAsyncFile out(path,Open_ToAppend);

  Putobj(out,line);
  Putch(out,'\n');
 }

void CommandEngine::cmd_nothing(StrLen)
 {
 }

void CommandEngine::cmd_exit(StrLen)
 {
  run_flag=false;
 }

void CommandEngine::cmd_help(StrLen)
 {
  Printf(Con,"commands: help exit pwd dir cd mkdir rmdir mkfile del type add\n");
 }

void CommandEngine::cmd_pwd(StrLen arg)
 {
  if( +arg )
    {
     Printf(Exception,"pwd: no argument is required");
    }
  else
    {
     Printf(Con,"#;\n",cur);
    }
 }

void CommandEngine::cmd_dir(StrLen arg)
 {
  if( +arg )
    {
     BuildPath path(cur,arg);

     do_dir(path);
    }
  else
    {
     do_dir(cur);
    }
 }

void CommandEngine::cmd_cd(StrLen arg)
 {
  if( +arg )
    {
     BuildPath path(cur,arg);

     do_cd(path);
    }
  else
    {
     Printf(Exception,"cd: path is not given");
    }
 }

void CommandEngine::cmd_mkdir(StrLen arg)
 {
  if( +arg )
    {
     BuildPath path(cur,arg);

     do_mkdir(path);
    }
  else
    {
     Printf(Exception,"mkdir: path is not given");
    }
 }

void CommandEngine::cmd_rmdir(StrLen arg)
 {
  if( +arg )
    {
     if( ProbeChar(arg,'-') )
       {
        if( ProbeChar(arg,'r') )
          {
           SkipSpace(arg);

           BuildPath path(cur,arg);

           do_rmdir(path,true);
          }
        else
          {
           Printf(Exception,"rmdir: bad option");
          }
       }
     else
       {
        BuildPath path(cur,arg);

        do_rmdir(path,false);
       }
    }
  else
    {
     Printf(Exception,"rmdir: path is not given");
    }
 }

void CommandEngine::cmd_mkfile(StrLen arg)
 {
  if( +arg )
    {
     BuildPath path(cur,arg);

     do_mkfile(path);
    }
  else
    {
     Printf(Exception,"mkfile: path is not given");
    }
 }

void CommandEngine::cmd_del(StrLen arg)
 {
  if( +arg )
    {
     BuildPath path(cur,arg);

     do_del(path);
    }
  else
    {
     Printf(Exception,"del: path is not given");
    }
 }

void CommandEngine::cmd_type(StrLen arg)
 {
  if( +arg )
    {
     BuildPath path(cur,arg);

     do_type(path);
    }
  else
    {
     Printf(Exception,"type: path is not given");
    }
 }

void CommandEngine::cmd_add(StrLen arg)
 {
  if( +arg )
    {
     StrLen file=TakeString(arg);

     SkipSpace(arg);

     BuildPath path(cur,file);

     do_add(path,arg);
    }
  else
    {
     Printf(Exception,"add: path is not given");
    }
 }

void CommandEngine::buildCmdList(CmdInput &input)
 {
  addCommand(input,"",&CommandEngine::cmd_nothing);
  addCommand(input,"exit",&CommandEngine::cmd_exit);
  addCommand(input,"help",&CommandEngine::cmd_help);

  addCommand(input,"pwd",&CommandEngine::cmd_pwd);
  addCommand(input,"dir",&CommandEngine::cmd_dir);
  addCommand(input,"cd",&CommandEngine::cmd_cd);
  addCommand(input,"mkdir",&CommandEngine::cmd_mkdir);
  addCommand(input,"rmdir",&CommandEngine::cmd_rmdir);
  addCommand(input,"mkfile",&CommandEngine::cmd_mkfile);
  addCommand(input,"del",&CommandEngine::cmd_del);
  addCommand(input,"type",&CommandEngine::cmd_type);
  addCommand(input,"add",&CommandEngine::cmd_add);
 }

CommandEngine::CommandEngine()
 : cmd_input(*this,"test> "),
   fs("host")
 {
 }

CommandEngine::~CommandEngine()
 {
 }

void CommandEngine::run()
 {
  ReportException report;

  for(run_flag=true; run_flag ;) cmd_input.command(report);
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

   DataEngine(Net::UDPort psec_port,const Net::PSec::MasterKey &skey);

   ~DataEngine();

   void run();
 };

DataEngine::DataEngine(Net::UDPort psec_port,const Net::PSec::MasterKey &skey)
 : udp(psec_port,Net::UDPoint(127,0,0,1,Net::PSecServerUDPort)),
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

} // namespace Private_4031

using namespace Private_4031;

/* Testit<4031> */

template<>
const char *const Testit<4031>::Name="Test4031 PTPSec";

template<>
bool Testit<4031>::Main()
 {
  Config cfg;
  Net::PSec::MasterKeyPtr skey;

  {
   ConnectEngine engine(cfg);

   engine.connect(skey);
  }

  {
   DataEngine engine(cfg.psec_port,*skey);

   engine.run();
  }

  return true;
 }

} // namespace App

