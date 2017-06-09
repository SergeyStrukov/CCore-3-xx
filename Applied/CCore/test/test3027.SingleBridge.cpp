/* test3027.SingleBridge.cpp */
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

namespace App {

namespace Private_3027 {

/* class Engine */

class Engine : NoCopy
 {
   Net::SingleBridge bridge;

   Net::SingleEchoDevice echo;

   PacketSource src;
   PacketTask client;

  public:

   Engine()
    : echo(Net::SingleBridge::ServerName()),
      src(1000,1200),
      client(src,Net::SingleBridge::ClientName())
    {
    }

   ~Engine()
    {
    }

   void showStat()
    {
     ShowStat(src,"Src");
     ShowStat(echo,"Echo");
     ShowStat(client,"Client");
    }

   class StartStop : NoCopy
    {
      Net::SingleBridge::StartStop bridge;

      RunTask run;

     public:

      explicit StartStop(Engine &engine)
       : bridge(engine.bridge),
         run(engine.src.function_stop())
       {
        run(engine.client.function_run());
       }

      ~StartStop() {}
    };
 };

} // namespace Private_3027

using namespace Private_3027;

/* Testit<3027> */

template<>
const char *const Testit<3027>::Name="Test3027 SingleBridge";

template<>
bool Testit<3027>::Main()
 {
  Engine engine;

  {
   Engine::StartStop start_stop(engine);

   Task::Sleep(10_sec);
  }

  engine.showStat();

  return true;
 }

} // namespace App

