/* ServerProc.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: PTPSecureServerProc 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "ServerProc.h"

#include <CCore/inc/Exception.h>

namespace PTPSecureServerProc {

/* class ServerProc */

void ServerProc::session(XPoint point)
 {
  support_proc.session(point);
  hfs_proc.session(point);
 }

bool ServerProc::exist(ServiceIdType service_id,FunctionIdType function_id)
 {
  switch( service_id )
    {
     case Net::PTPSupport::ServiceId : return support_proc.exist(function_id);

     case Net::HFS::ServiceId :        return hfs_proc.exist(function_id);

     default: return false;
    }
 }

void ServerProc::inbound(XPoint point,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info)
 {
  SilentReportException report;

  Inbound inbound(point,idx,packet,client_info);

  if( !inbound ) return inbound.send_cancel(ptp);

  switch( inbound.serv_func.service_id )
    {
     case Net::PTPSupport::ServiceId : support_proc.inbound(inbound); break;

     case Net::HFS::ServiceId :        hfs_proc.inbound(inbound); break;

     default:
      {
       inbound.error_id=Error_NoFunction;

       inbound.send_error(ptp);
      }
    }
 }

void ServerProc::tick()
 {
  SilentReportException report;

  support_proc.tick();
  hfs_proc.tick();

  log.flush();
 }

ServerProc::ServerProc(StrLen ptp_server_name,StrLen root,Net::PSec::EndpointManager &epman)
 : ServerProcBase(ptp_server_name),
   support_proc(this),
   hfs_proc(this,root,epman)
 {
  ptp->attach(this);
 }

ServerProc::~ServerProc()
 {
  ptp->detach();
 }

Symbol ServerProc::get()
 {
  for(;;)
    {
     Symbol ch;

     if( con.get(100_msec,ch) ) return ch;
    }
 }

} // namespace PTPSecureServerProc


