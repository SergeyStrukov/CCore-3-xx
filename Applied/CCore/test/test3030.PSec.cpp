/* test3030.PSec.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>
#include <CCore/test/testNet.h>

#include <CCore/inc/net/SingleBridge.h>
#include <CCore/inc/net/SingleEchoDevice.h>
#include <CCore/inc/net/PSec.h>
#include <CCore/inc/net/PSecKey.h>

namespace App {

namespace Private_3030 {

/* class Engine */

class Engine : NoCopy
 {
   Net::SingleBridge bridge;
   Net::PSec::EndpointDevice server_psec;
   Net::PSec::EndpointDevice client_psec;

   ObjMaster server_psec_master;
   ObjMaster client_psec_master;

   Net::SingleEchoDevice echo;

   PacketSource src;
   PacketTask client;

  public:

   Engine(PacketFormat format,const Net::PSec::MasterKey &master_key)
    : bridge(format,format),
      server_psec(Net::SingleBridge::ServerName(),master_key,10_sec),
      client_psec(Net::SingleBridge::ClientName(),master_key,10_sec),
      server_psec_master(server_psec,"server_psec"),
      client_psec_master(client_psec,"client_psec"),
      echo("server_psec",200),
      src(100,1200),
      client(src,"client_psec")
    {
    }

   ~Engine()
    {
    }

   void close() { client_psec.close(); }

   void showStat()
    {
     ShowStat(src,"Src");
     ShowStat(echo,"Echo");
     ShowStat(client,"Client");
     ShowStat(server_psec,"Server PSec");
     ShowStat(client_psec,"Client PSec");
    }

   class StartStop : NoCopy
    {
      Net::SingleBridge::StartStop bridge;

      RunTask run_task;

     public:

      explicit StartStop(Engine &engine)
       : bridge(engine.bridge),
         run_task(engine.src.function_stop())
       {
        run_task(engine.client.function_run());
       }

      ~StartStop() {}
    };
 };

} // namespace Private_3030

using namespace Private_3030;

/* Testit<3030> */

template<>
const char *const Testit<3030>::Name="Test3030 PSec";

template<>
bool Testit<3030>::Main()
 {
  PacketFormat format;

  format.prefix=0;
  format.suffix=0;
  format.max_data=1472;

  Net::PSec::CryptAlgoSelect algo_select(Net::PSec::CryptID_AES128,Net::PSec::HashID_SHA224,Net::PSec::DHGroupID_I);

  Net::PSec::SessionKeyParam param(20,10,100000);

  Net::PSec::SessionKey master_key(algo_select,param);

  {
   Random random;

   random.fill(master_key.takeKeyBuf());
  }

  Engine engine(format,master_key);
  TaskEventRecorder recorder(100_MByte);

  {
   TickTask tick_task;
   TaskEventHostType::StartStop event_start_stop(TaskEventHost,&recorder);
   Engine::StartStop start_stop(engine);

   Task::Sleep(100_sec);

   engine.close();

   Task::Sleep(10_sec);
  }

  engine.showStat();

  BinaryFile dev("test3030.bin");

  dev(recorder);

  return true;
 }

} // namespace App

