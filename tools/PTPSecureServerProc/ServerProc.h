/* ServerProc.h */
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

#ifndef PTPServer_ServerProc_h
#define PTPServer_ServerProc_h

#include <CCore/inc/ReadCon.h>

#include "SupportProc.h"
#include "HFSProc.h"

namespace PTPSecureServerProc {

//
//   Net::PTP::ServerProc is called in the single task context
//
//   PacketMultipointDevice::InboundProc is called in the single task context
//
//   UDPMultipointDevice task
//
//   get, put is called in the main task context
//

/* classes */

class ServerProc;

/* class ServerProc */

class ServerProc : public Net::PTP::ServerProc , ServerProcBase
 {
   // UDPMultipointDevice task

   SupportProc support_proc;

   HFSProc hfs_proc;

   // main task

   ReadCon con;

  private:

   // ServerProcBase

   virtual void session(XPoint point);

   virtual bool exist(ServiceIdType service_id,FunctionIdType function_id);

   // Net::PTP::ServerProc

   virtual void inbound(XPoint point,TransIndex idx,Packet<uint8> packet,PtrLen<const uint8> client_info);

   virtual void tick();

  public:

   explicit ServerProc(StrLen ptp_server_name,StrLen root,Net::PSec::EndpointManager &epman);

   ~ServerProc();

   // main task

   Symbol get();

   bool get(MSec timeout,Symbol &ret) { return con.get(timeout,ret); }

   bool get(TimeScope time_scope,Symbol &ret) { return con.get(time_scope,ret); }

   void put(OneOfTypes<char,Symbol> ch) { con.put(ch); }

   void put(const char *str,ulen len) { con.put(str,len); }

   void put(StrLen str) { con.put(str); }
 };

} // namespace PTPSecureServerProc

#endif


