/* ProcBase.cpp */
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

#include "ProcBase.h"

#include <CCore/inc/Abort.h>

namespace PTPSecureServerProc {

/* class Log */

Log::Log()
 : out("PTPSecureServerLog.txt",Open_ToAppend)
 {
  out.disableExceptions();

  Printf(out,"#;\n",Title("PTP Secure Server log"));
 }

Log::~Log()
 {
  Printf(out,"\n#;\n\nRun time = #;\n\n#;\n\n\n",TextDivider(),PrintTime(timer.get()),TextDivider());
 }

/* struct Inbound */

Inbound::Inbound(XPoint point_,TransIndex idx_,Packet<uint8> packet_,PtrLen<const uint8> client_info)
 : point(point_),
   idx(idx_),
   dev(client_info),
   packet(packet_)
 {
  dev(serv_func);

  if( !dev )
    error_id=Error_BadInput;
  else
    error_id=NoError;
 }

void Inbound::send_cancel(Net::PTP::ServerDevice *ptp)
 {
  packet.complete();

  ptp->send_cancel(idx);
 }

void Inbound::send_error(Net::PTP::ServerDevice *ptp)
 {
  Net::PTP::Result result(serv_func,error_id);

  auto len=SaveLen(result);

  if( packet.checkDataLen(len) )
    {
     PtrLen<uint8> info=packet.setDataLen(len);

     BufPutDev dev(info.ptr);

     dev(result);

     ptp->send_info(idx,Replace_null(packet),info);
    }
  else
    {
     send_cancel(ptp);
    }
 }

/* class ServerProcBase */

ServerProcBase::ServerProcBase(StrLen ptp_server_name)
 : hook(ptp_server_name),
   ptp(hook)
 {
 }

ServerProcBase::~ServerProcBase()
 {
 }

} // namespace PTPSecureServerProc


