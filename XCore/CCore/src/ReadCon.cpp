/* ReadCon.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ReadCon.h>

#include <CCore/inc/Abort.h>

namespace CCore {

/* class ReadCon */

Sys::ConInputResult ReadCon::input_any(ReadConCode ch)
 {
  bool ok;

  {
   Lock lock(*this);

   if( ToChar(ch)==3 ) // ^C
     {
      Abort("--- ^C abort ---");
     }

   ok=fifo.put(ch);
  }

  if( ok )
    {
     sem.give_any();

     return Sys::Con_NoEcho;
    }

  return Sys::Con_Drop;
 }

bool ReadCon::do_get(ReadConCode &ret)
 {
  Lock lock(*this);

  return fifo.get(ret);
 }

ReadCon::ReadCon(MSec timeout_)
 : timeout(timeout_),
   sem("ReadCon"),
   own("ReadCon",function_input())
 {
 }

ReadCon::~ReadCon()
 {
 }

ReadConCode ReadCon::get()
 {
  sem.take();

  ReadConCode ch;

  do_get(ch);

  return ch;
 }

bool ReadCon::get(MSec timeout,ReadConCode &ret)
 {
  if( sem.take(timeout) ) return do_get(ret);

  return false;
 }

bool ReadCon::get(TimeScope time_scope,ReadConCode &ret)
 {
  if( sem.take(time_scope) ) return do_get(ret);

  return false;
 }

void ReadCon::put(StrLen str)
 {
  while( +str )
    {
     NanoPacket<char> packet=Sys::AllocConPacket(timeout);

     if( !packet ) return;

     auto frame=str.takeup(packet.getMaxDataLen());

     packet.setDataLen(frame.len).copy(frame.ptr);

     Sys::ConWrite(packet);
    }
 }

} // namespace CCore


