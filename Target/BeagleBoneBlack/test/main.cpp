/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/BeagleBoneBlack
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/MemBase.h>
#include <CCore/inc/PacketPool.h>

namespace App {

/* Testit<0> */

template<>
const char *const Testit<0>::Name="Test0 empty";

template<>
bool Testit<0>::Main() { return false; }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  Used(argc);
  Used(argv);

  Testit<2999>().run();

  Printf(Con,"\nPeak memory usage #;\n\n",MemPeak());

  return 0;
 }

/* before_main() */

#include <CCore/inc/I2CDevice.h>
#include <CCore/inc/video/VideoControl.h>
#include <CCore/inc/sys/SysConHost.h>

#include <CCore/inc/dev/DevEth.h>
#include <CCore/inc/net/NanoIPDevice.h>
#include <CCore/inc/net/PTPClientDevice.h>
#include <CCore/inc/net/HFSClientDevice.h>
#include <CCore/inc/net/HFSFileSystemDevice.h>
#include <CCore/inc/net/PTPConDevice.h>
#include <CCore/inc/RedirectPTPCon.h>

#include <stdio.h>

void before_main()
 {
  using namespace CCore;

  MemScope mem_scope;

#if 1

  I2CDevice i2c(Dev::I2C_0);

  ObjMaster i2c_master(i2c,"i2c[0]");

  Video::VideoControl vctrl("i2c[0]");

  ObjMaster vctrl_master(vctrl,"video");

#endif

#if 1

  Video::VideoConsole vcon("video");

  vcon.waitOpen();

  SingleMaster<Video::VideoConsole> vcon_master(Sys::GetConHost(),"!VideoConsoleMaster",vcon);

#endif

#if 1

  Dev::EthDevice eth;

  ObjMaster eth_master(eth,"eth");

  Net::NanoIPDevice ip("eth",Net::IPAddress(192,168,99,10),Net::IPAddress(255,255,255,0));

  Dev::EthDevice::StartStop start_stop(eth,TaskPriority(5000));

  ObjMaster ip_master(ip,"ip");

  Net::NanoUDPEndpointDevice udp_ptp("ip",Net::PTPClientUDPort,true,Net::UDPoint(192,168,99,1,Net::PTPServerUDPort));

  ObjMaster udp_ptp_master(udp_ptp,"udp_ptp");

  Net::PTP::ClientDevice ptp("udp_ptp");

  ptp.support_guarded(10_sec);

  ObjMaster ptp_master(ptp,"ptp");

  Net::HFS::ClientDevice hfs("ptp");

  ObjMaster hfs_master(hfs,"hfs");

  Net::HFS::FileSystemDevice host("hfs");

  ObjMaster host_master(host,"host");

  Net::PTPCon::ClientDevice ptpcon("ptp");

  ObjMaster ptpcon_master(ptpcon,"ptpcon");

  Net::PTPCon::Cfg cfg(Net::PTPCon::TriggerAll);

  RedirectPTPCon redirect("ptpcon","Beagle",cfg);

#endif

  const char *argv[]={"main",0};

  int ret=main(1,argv);

  fflush(stdout);

  Printf(Con,"main() return #;\n",ret);

  DetachPacketBufs();
 }





