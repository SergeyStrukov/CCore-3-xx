/* PrintPTPCon.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/print/PrintPTPCon.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class PTPConOpenClose */

PTPConOpenClose::PTPConOpenClose(StrLen con_dev_name,StrLen name,const Net::PTPCon::Cfg &cfg)
 : hook(con_dev_name),
   con(hook),
   open_close(*con,name,cfg)
 {
  format=con->getWriteFormat();
 }

PTPConOpenClose::~PTPConOpenClose()
 {
 }

/* class ReadPTPCon */

void ReadPTPCon::input(PacketBuf &,PtrLen<const uint8> str)
 {
  if( !str ) return;

  {
   Mutex::Lock lock(mutex);

   fifo.put(Mutate<const char>(str));
  }

  event.trigger();
 }

void ReadPTPCon::stop()
 {
  {
   Mutex::Lock lock(mutex);

   stop_flag=true;
  }

  event.trigger();
 }

ulen ReadPTPCon::do_read(char *ptr,ulen len)
 {
  ulen ret;
  bool flag;

  {
   Mutex::Lock lock(mutex);

   if( stop_flag )
     {
      ret=MaxULen;
      flag=false;
     }
   else
     {
      ret=fifo.get(Range(ptr,len));
      flag=!fifo.isEmpty();
     }
  }

  if( ret==MaxULen )
    {
     Printf(Exception,"CCore::ReadPTPCon::read(...) : console read is stopped");
    }

  if( flag ) event.trigger();

  return ret;
 }

ulen ReadPTPCon::read(char *ptr,ulen len)
 {
  event.wait();

  return do_read(ptr,len);
 }

ulen ReadPTPCon::read(char *ptr,ulen len,MSec timeout)
 {
  if( event.wait(timeout) ) return do_read(ptr,len);

  return 0;
 }

ulen ReadPTPCon::read(char *ptr,ulen len,TimeScope time_scope)
 {
  if( event.wait(time_scope) ) return do_read(ptr,len);

  return 0;
 }

ReadPTPCon::ReadPTPCon(PTPConOpenClose &con_openclose_,MSec timeout_,ulen max_packets)
 : con_openclose(con_openclose_),
   mutex("ReadPTPCon.mutex"),
   event("ReadPTPCon.event"),
   pset("ReadPTPCon.pset",max_packets),
   timeout(timeout_)
 {
  con_openclose_.start_read(this);
 }

ReadPTPCon::~ReadPTPCon()
 {
  pset.wait(timeout);

  con_openclose.stop_read();
 }

void ReadPTPCon::put(const char *str,ulen len)
 {
  PacketFormat format=con_openclose.getWriteFormat();

  for(auto range=Range(str,len); +range ;)
    {
     Packet<uint8> packet=pset.get(timeout);

     if( !packet ) return;

     ulen len=packet.getMaxDataLen(format).len;

     if( !len )
       {
        packet.complete();

        return;
       }

     auto frame=range.takeup(len);

     packet.setDataLen(format,frame.len).copyFrom(frame.ptr);

     con_openclose.write(packet);
    }
 }

/* class PrintPTPCon */

PtrLen<char> PrintPTPCon::do_provide(ulen)
 {
  if( enable_exceptions && con->getWriteErrorFlag() )
    {
     Printf(Exception,"CCore::PrintPTPCon::do_provide(...) : PTP Console failure");
    }

  packet=pset.get(timeout);

  if( !packet )
    {
     if( enable_exceptions )
       {
        Printf(Exception,"CCore::PrintPTPCon::do_provide(...) : no packet");
       }

     return Nothing;
    }

  PtrLen<uint8> buf=packet.getMaxRange(format).range;

  if( !buf )
    {
     packet.complete();

     if( enable_exceptions )
       {
        Printf(Exception,"CCore::PrintPTPCon::do_provide(...) : no room");
       }

     return Nothing;
    }

  return Mutate<char>(buf);
 }

void PrintPTPCon::do_flush(char *,ulen len)
 {
  packet.setDataLen(format,len);

  con->write(Replace_null(packet));
 }

PrintPTPCon::PrintPTPCon(StrLen con_dev_name,MSec timeout_,ulen max_packets)
 : hook(con_dev_name),
   con(hook),
   timeout(timeout_),
   enable_exceptions(false),
   pset(max_packets)
 {
  format=con->getWriteFormat();
 }

PrintPTPCon::~PrintPTPCon()
 {
  flush();
 }

void PrintPTPCon::flush_and_wait()
 {
  flush();

  pset.wait(timeout);

  if( enable_exceptions && con->getWriteErrorFlag() )
    {
     Printf(Exception,"CCore::PrintPTPCon::flush_and_wait() : PTP Console failure");
    }
 }

} // namespace CCore


