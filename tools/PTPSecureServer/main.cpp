/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: PTPSecureServer 1.00
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

#include <CCore/inc/CmdInput.h>

#include <CCore/inc/StrKey.h>
#include <CCore/inc/CompactMap.h>

#include <CCore/inc/net/AsyncUDPDevice.h>
#include <CCore/inc/net/PKE.h>
#include <CCore/inc/net/PSec.h>
#include <CCore/inc/Scanf.h>
#include <CCore/inc/FileSystem.h>

#include <ServerProc.h>

#include "Config.h"

namespace App {

/* using */

using namespace CCore;

/* CreateKey() */

Net::PSec::AbstractHashFunc * CreateKey(const TypeDef::Key &key)
 {
  return Net::PSec::CreateKeyedHash(Net::PSec::HashID(key.hash_id),key.key.getRange());
 }

/* classes */

class ClientSet;

class Engine;

/* class ClientSet */

class ClientSet : NoCopy , public Net::PSec::ClientDatabase
 {
   struct Client
    {
     StrLen name;
     TypeDef::Key key;

     bool access_read;
     bool access_write;
     bool has_home;

     Client(StrLen name_,const TypeDef::Key &key_)
      : name(name_),key(key_)
      {
       access_read=true;
       access_write=true;
       has_home=true;
      }

     Client(StrLen name_,const TypeDef::Client &client)
      : name(name_),key(client.key)
      {
       access_read=client.access_read;
       access_write=client.access_write;
       has_home=client.has_home;
      }
    };

   CompactRBTreeMap<StrKey,Client> map;

   StrLen root;

  private:

   void add(StrLen name,const TypeDef::Key &key);

   void add(StrLen name,const TypeDef::Client &client);

   static PTPSecureServerProc::ClientProfile * CreateProfile(const Client &client)
    {
     PTPSecureServerProc::ClientProfile *ret=new PTPSecureServerProc::ClientProfile();

     ret->name=client.name;
     ret->access_read=client.access_read;
     ret->access_write=client.access_write;
     ret->has_home=client.has_home;

     return ret;
    }

   static void MakeDirectory(StrLen dir);

   static void MakeHome(StrLen root,const Client *client);

  public:

   explicit ClientSet(const TypeDef::PTPSecureConfig *cfg);

   ~ClientSet();

   // Net::PSec::ClientDatabase

   virtual FindErrorCode findClient(PtrLen<const uint8> client_id,Net::PSec::PrimeKeyPtr &client_key,Net::PSec::ClientProfilePtr &client_profile) const;
 };

void ClientSet::add(StrLen name,const TypeDef::Key &key)
 {
  map.find_or_add(StrKey(name),name,key);
 }

void ClientSet::add(StrLen name,const TypeDef::Client &client)
 {
  auto result=map.find_or_add(StrKey(name),name,client);

  if( !result.new_flag )
    {
     Printf(Exception,"App::ClientSet::add(#;,...) : client name duplication",name);
    }
 }

void ClientSet::MakeDirectory(StrLen dir)
 {
  try
    {
     FileSystem fs;

     if( fs.getFileType(dir)==FileType_dir ) return;

     fs.createDir(dir);
    }
  catch(...)
    {
    }
 }

void ClientSet::MakeHome(StrLen root,const Client *client)
 {
  if( !client->has_home ) return;

  PTPSecureServerProc::Home home(client->name);

  PTPSecureServerProc::BuildClientPath path1(root,"home",home);

  if( !path1 ) return;

  PTPSecureServerProc::BuildClientPath path2(root,"~",home);

  if( !path2 ) return;

  MakeDirectory(path1.getStr());
  MakeDirectory(path2.getStr());
 }

ClientSet::ClientSet(const TypeDef::PTPSecureConfig *cfg)
 : root(cfg->root)
 {
  add(cfg->admin_name,cfg->admin_key);

  for(const TypeDef::Client &client : cfg->clients.getRange() ) add(client.name,client);
 }

ClientSet::~ClientSet()
 {
 }

auto ClientSet::findClient(PtrLen<const uint8> client_id,Net::PSec::PrimeKeyPtr &client_key,Net::PSec::ClientProfilePtr &client_profile) const -> FindErrorCode
 {
  StrLen name=Mutate<const char>(client_id);

  if( const Client *client=map.find(StrKey(name)) )
    {
     try
       {
        client_key=std::move(Net::PSec::PrimeKeyPtr(CreateKey(client->key)));
        client_profile=std::move(Net::PSec::ClientProfilePtr(CreateProfile(*client)));

        MakeHome(root,client);

        return Find_Ok;
       }
     catch(...)
       {
        return FindError_NoMemory;
       }
    }
  else
    {
     return FindError_NoClientID;
    }
 }

/* class Engine */

class Engine : public NoCopyBase<CmdInput::Target>
 {
   Net::PSec::AlgoSet algo_set;

   // data path

   Net::AsyncUDPMultipointDevice udp_psec;

   ObjMaster udp_psec_master;

   Net::PSec::MultipointDevice psec;

   ObjMaster psec_master;

   Net::PTP::ServerDevice ptp;

   ObjMaster ptp_master;

   // entry path

   Net::AsyncUDPMultipointDevice udp_pke;

   ObjMaster udp_pke_master;

   ClientSet client_set;

   Net::PSec::ServerNegotiant pke;

   // work

   Net::AsyncUDPMultipointDevice::StatInfo base_udp_info;

   Net::PSec::MultipointDevice::StatInfo base_psec_info;

   Net::PTP::ServerDevice::StatInfo base_ptp_info;

   CmdInputCon<PTPSecureServerProc::ServerProc> cmd_input;
   bool run_flag;

  private:

   void clearStat();

   void printStat();

   void cmd_nothing(StrLen arg);
   void cmd_exit(StrLen arg);
   void cmd_stat(StrLen arg);
   void cmd_clientstat(StrLen arg);
   void cmd_clear(StrLen arg);
   void cmd_kick(StrLen arg);
   void cmd_help(StrLen arg);

   virtual void buildCmdList(CmdInput &input);

  public:

   explicit Engine(const TypeDef::PTPSecureConfig *cfg);

   ~Engine();

   int run();
 };

void Engine::clearStat()
 {
  udp_psec.getStat(base_udp_info);

  psec.getStat(base_psec_info);

  ptp.getStat(base_ptp_info);
 }

void Engine::printStat()
 {
  // udp

  Net::AsyncUDPMultipointDevice::StatInfo udp_info;

  udp_psec.getStat(udp_info);

  udp_info-=base_udp_info;

  // psec

  Net::PSec::MultipointDevice::StatInfo psec_info;

  psec.getStat(psec_info);

  psec_info-=base_psec_info;

  // ptp

  Net::PTP::ServerDevice::StatInfo ptp_info;

  ptp.getStat(ptp_info);

  ptp_info-=base_ptp_info;

  // show

  Printf(Con,"\n#20;\n#20;\n#20;\n",udp_info,psec_info,ptp_info);
 }

void Engine::cmd_nothing(StrLen)
 {
 }

void Engine::cmd_exit(StrLen)
 {
  printStat();

  run_flag=false;
 }

void Engine::cmd_stat(StrLen)
 {
  printStat();
 }

void Engine::cmd_clientstat(StrLen)
 {
  psec.processStat( [this] (Net::XPoint point,Net::PSec::MultipointDevice::StatInfo &stat)
                           {
                            Net::PointDesc desc(&psec,point);
                            PTPSecureServerProc::ClientProfile *profile=dynamic_cast<PTPSecureServerProc::ClientProfile *>(psec.getClientProfile(point));

                            if( profile )
                              {
                               Printf(Con,"#; on #;\n#;\n",profile->name,desc,stat);
                              }

                           } );
 }

void Engine::cmd_clear(StrLen)
 {
  clearStat();
 }

void Engine::cmd_kick(StrLen arg)
 {
  ScanString inp(arg);

  Net::UDPoint point;

  Scanf(inp," #; ",point);

  if( !psec.close(point.get()) )
    {
     Printf(Exception,"No such connection");
    }
 }

void Engine::cmd_help(StrLen)
 {
  Printf(Con,"commands: clientstat stat clear kick help exit\n");
 }

void Engine::buildCmdList(CmdInput &input)
 {
  addCommand(input,"",&Engine::cmd_nothing);
  addCommand(input,"exit",&Engine::cmd_exit);
  addCommand(input,"stat",&Engine::cmd_stat);
  addCommand(input,"clientstat",&Engine::cmd_clientstat);
  addCommand(input,"clear",&Engine::cmd_clear);
  addCommand(input,"kick",&Engine::cmd_kick);
  addCommand(input,"help",&Engine::cmd_help);
 }

Engine::Engine(const TypeDef::PTPSecureConfig *cfg)
 : algo_set(Net::PSec::AlgoSet::DefaultSet),
   udp_psec(cfg->psec_port),
   udp_psec_master(udp_psec,"udp_psec"),
   psec("udp_psec",algo_set.getAlgoLens(),cfg->max_clients,1_min),
   psec_master(psec,"psec"),
   ptp("psec"),
   ptp_master(ptp,"ptp"),

   udp_pke(cfg->pke_port),
   udp_pke_master(udp_pke,"udp_pke"),
   client_set(cfg),
   pke("udp_pke",client_set,psec),

   cmd_input(*this,"PTPS> ","ptp",cfg->root,psec)
 {
  Net::PSec::PrimeKeyPtr server_key(CreateKey(cfg->server_key));

  Net::PSec::SessionKeyParam param(cfg->keyset_len,cfg->ttl,cfg->utl);

  pke.prepare(std::move(server_key),param);
 }

Engine::~Engine()
 {
 }

int Engine::run()
 {
  ReportException report;

  Net::AsyncUDPMultipointDevice::StartStop start_stop_psec(udp_psec);
  Net::AsyncUDPMultipointDevice::StartStop start_stop_pke(udp_pke);

  pke.start(algo_set.getAlgoList());

  for(run_flag=true; run_flag ;) cmd_input.command(report);

  return 0;
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     int ret;

     {
      Putobj(Con,"--- PTPSecureServer 1.00 ---\n--- Copyright (c) 2015 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc!=2 )
        {
         Putobj(Con,"Usage: CCore-PTPSecureServer <config.ddl>\n");

         return 2;
        }

      Config config(argv[1]);

      config.show();

      Engine engine(config);

      ret=engine.run();
     }

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

