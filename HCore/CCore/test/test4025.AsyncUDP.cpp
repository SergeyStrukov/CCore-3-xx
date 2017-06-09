/* test4025.AsyncUDP.cpp */
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
#include <CCore/test/testNet.h>

#include <CCore/inc/net/AsyncUDPDevice.h>
#include <CCore/inc/net/EchoDevice.h>

namespace App {

namespace Private_4025 {

/* class Engine */

class Engine : NoCopy
 {
   Net::AsyncUDPMultipointDevice server;
   Net::AsyncUDPEndpointDevice client;

   ObjMaster server_master;
   ObjMaster client_master;

   Net::EchoDevice echo;
   PacketEchoTest test;

  public:

   Engine()
    : server(55'000),
      client(55'001,Net::UDPoint(127,0,0,1,55'000)),

      server_master(server,"server"),
      client_master(client,"client"),

      echo("server"),
      test("client")
    {
    }

   ~Engine()
    {
    }

   void send(ulen forward,ulen cnt) { test.run(forward,cnt); }

   void showStat()
    {
     ShowStat(echo,"Echo");

     Printf(Con,"traffic = #;\n\n",echo.getTraffic());

     ShowStat(server,"UDP server");
     ShowStat(client,"UDP client");
    }

   class StartStop : NoCopy
    {
      Net::AsyncUDPMultipointDevice::StartStop server;
      Net::AsyncUDPEndpointDevice::StartStop client;

     public:

      explicit StartStop(Engine &engine)
       : server(engine.server),
         client(engine.client)
       {
        Task::Sleep(1_sec);
       }

      ~StartStop()
       {
        Task::Sleep(1_sec);
       }
    };
 };

} // namespace Private_4025

using namespace Private_4025;

/* Testit<4025> */

template<>
const char *const Testit<4025>::Name="Test4025 AsyncUDP";

template<>
bool Testit<4025>::Main()
 {
  Engine engine;

  {
   Engine::StartStop start_stop(engine);

   engine.send(5,100'000);
  }

  engine.showStat();

  return true;
 }

} // namespace App

