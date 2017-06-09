/* PTPConProc.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: PTPServerProc 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include "PTPConProc.h"

namespace PTPServerProc {

/* class PTPConWrite::Frame */

bool PTPConWrite::Frame::set(StrLen text_,uint32 write_ticks_)
 {
  if( ok ) return false;

  write_ticks=write_ticks_;

  ok=true;

  try
    {
     text.extend_copy(text_);

     return true;
    }
  catch(CatchType)
    {
     return false;
    }
 }

bool PTPConWrite::Frame::tick()
 {
  if( !ok ) return false;

  if( write_ticks )
    {
     write_ticks--;

     return false;
    }

  return true;
 }

bool PTPConWrite::Frame::print()
 {
  if( !ok ) return false;

  Print(Range_const(text));

  text.erase();

  ok=false;

  return true;
 }

/* class PTPConWrite */

void PTPConWrite::Print(StrLen text)
 {
  PrintCon::Print(text);
 }

bool PTPConWrite::shift()
 {
  bool ret=buf[ind].print();

  next_number++;

  ind=Next(ind);

  return ret;
 }

void PTPConWrite::set(uint32 n,StrLen text)
 {
  ulen i=(ind+n-1)%BufLen;

  if( !buf[i].set(text,write_ticks) ) ok=false;
 }

void PTPConWrite::write(uint32 n,StrLen text)
 {
  if( n )
    {
     set(n,text);
    }
  else
    {
     Print(text);

     while( shift() );
    }
 }

ulen PTPConWrite::skip()
 {
  ulen ret=1;

  while( shift() ) ret++;

  return ret;
 }

PTPConWrite::PTPConWrite()
 : ind(0),
   ok(false)
 {
 }

PTPConWrite::~PTPConWrite()
 {
 }

void PTPConWrite::open(uint32 write_timeout_msec)
 {
  ind=0;
  ok=true;
  next_number=0;
  write_ticks=ToTicks(write_timeout_msec);
 }

bool PTPConWrite::operator () (uint32 number,StrLen text)
 {
  uint32 n=number-next_number;

  if( UIntFunc<uint32>::IsNegative(n) ) return ok=false;

  if( n>=2*BufLen )
    {
     close();

     next_number=number-BufLen;

     ind=0;

     set(BufLen,text);

     return ok=false;
    }
  else if( n>BufLen )
    {
     do
       {
        ulen delta=skip();

        if( n>=delta )
          {
           n-=delta;
          }
        else
          {
           // never happens

           return ok=false;
          }
       }
     while( n>BufLen );

     write(n,text);

     return ok=false;
    }
  else
    {
     write(n,text);

     return ok;
    }
 }

void PTPConWrite::tick()
 {
  ulen i=ind;
  ulen delta=0;

  for(ulen n=1; n<=BufLen ;n++,i=Next(i))
    {
     if( buf[i].tick() )
       {
        ok=false;

        while( delta<n ) delta+=skip();
       }
    }
 }

void PTPConWrite::close()
 {
  for(ulen cnt=BufLen; cnt ;cnt--,ind=Next(ind)) buf[ind].print();
 }

/* class PTPConRead::Buf */

void PTPConRead::Buf::fill(PtrLen<uint8> data)
 {
  avail-=data.len;

  for(; +data ;++data)
    {
     char ch=0;

     fifo.get(ch);

     *data=uint8(ch);
    }
 }

PTPConRead::Buf::Buf()
 : is_opened(false)
 {
 }

PTPConRead::Buf::~Buf()
 {
 }

void PTPConRead::Buf::open(const TriggerMask &trigger_mask_)
 {
  fifo.reset();
  avail=0;
  trigger_mask=trigger_mask_;

  is_opened=true;
 }

void PTPConRead::Buf::close()
 {
  is_opened=false;
 }

bool PTPConRead::Buf::put(char ch)
 {
  if( !is_opened ) return false;

  if( fifo.put(ch) )
    {
     if( trigger_mask.test(ch) )
       {
        avail=fifo.getCount();
       }
     else
       {
        if( CharIsPrintable(ch) ) Putch(Con,ch);
       }
    }

  return true;
 }

struct PTPConRead::Buf::Output
 {
  Net::PTPCon::ReadOutput prefix;
  mutable PtrLen<uint8> data;

  Output(uint32 number,ulen len)
   : prefix(number,len)
   {
   }

  // save object

  template <class Dev>
  void save(Dev &dev) const
   {
    dev.template use<BeOrder>(prefix);

    data=dev.putRange(prefix.len);
   }
 };

bool PTPConRead::Buf::pump(PacketList &complete_list,
                           Outbound &outbound,
                           Net::PTP::ServerDevice *ptp,
                           uint32 number,
                           LenType len,
                           bool allow_empty)
 {
  if( !is_opened || ( !avail && !allow_empty ) ) return false;

  if( outbound.packet.clearCancelFunction()!=Packet_Cancelled )
    {
     Replace_min<LenType>(len,avail);

     Output output(number,len);

     outbound.send_info(complete_list,output,ptp);

     fill(output.data);
    }
  else
    {
     *outbound.packet.getExt()=false;

     outbound.packet=Nothing;
    }

  return true;
 }

/* class PTPConRead */

void PTPConRead::pump(PacketList &complete_list,bool allow_empty)
 {
  if( buf.pump(complete_list,outbound,ptp,number,len,allow_empty) )
    {
     is_started=false;
    }
 }

void PTPConRead::stop(PacketList &complete_list)
 {
  if( outbound.packet.clearCancelFunction()!=Packet_Cancelled )
    {
     outbound.send_error(complete_list,ptp,Error_ReadStarted);
    }
  else
    {
     *outbound.packet.getExt()=false;

     outbound.packet=Nothing;
    }

  is_started=false;
 }

void PTPConRead::cancel(PacketHeader *packet_)
 {
  Packet<uint8,bool> packet=packet_;

  {
   Mutex::Lock lock(mutex);

   if( *packet.getExt() )
     {
      outbound.packet=Nothing;

      is_started=false;
     }
  }

  packet.popExt().complete();
 }

PTPConRead::PTPConRead(Net::PTP::ServerDevice *ptp_)
 : ptp(ptp_),
   mutex("PTPConRead"),
   is_started(false)
 {
 }

PTPConRead::~PTPConRead()
 {
 }

void PTPConRead::open(uint32 read_timeout_msec,const TriggerMask &trigger_mask)
 {
  read_ticks=ToTicks(read_timeout_msec);

  {
   Mutex::Lock lock(mutex);

   is_started=false;

   buf.open(trigger_mask);
  }
 }

ErrorIdType PTPConRead::start(Inbound &inbound,uint32 number_,LenType len_)
 {
  PacketList complete_list;

  {
   Mutex::Lock lock(mutex);

   if( is_started ) stop(complete_list);

   if( outbound.init(inbound,function_cancel()) )
     {
      number=number_;
      len=Min<LenType>(Net::PTPCon::MaxReadDataLen,len_);
      ticks=read_ticks;

      is_started=true;

      pump(complete_list,false);
     }
  }

  complete_list.complete();

  return NoError;
 }

void PTPConRead::tick()
 {
  PacketList complete_list;

  {
   Mutex::Lock lock(mutex);

   if( !is_started ) return;

   if( ticks )
     {
      ticks--;

      pump(complete_list,false);
     }
   else
     {
      pump(complete_list,true);
     }
  }

  complete_list.complete();
 }

void PTPConRead::close()
 {
  PacketList complete_list;

  {
   Mutex::Lock lock(mutex);

   if( is_started ) stop(complete_list);

   buf.close();
  }

  complete_list.complete();
 }

bool PTPConRead::put(char ch)
 {
  PacketList complete_list;

  {
   Mutex::Lock lock(mutex);

   if( !buf.put(ch) ) return false;

   if( is_started ) pump(complete_list,false);
  }

  complete_list.complete();

  return true;
 }

/* class PTPConProc */

void PTPConProc::setInsText(const char *text)
 {
  Mutex::Lock lock(mutex);

  ins_text=text;
 }

void PTPConProc::do_close()
 {
  is_opened=false;

  writer.close();
  reader.close();

  Printf(Con,"\n\n--- Close console #; ---\n\n",getName());

  if( exit_on_close )
    setInsText("\nexit\n");
  else
    setInsText("\n");
 }

ErrorIdType PTPConProc::open(XPoint client_,
                             uint32 write_timeout_msec,
                             uint32 read_timeout_msec,
                             const TriggerMask &trigger_mask,
                             StrLen name_)
 {
  if( is_opened ) return Error_CannotOpenMoreCon;

  client=client_;

  writer.open(write_timeout_msec);
  reader.open(read_timeout_msec,trigger_mask);

  Replace_min(name_.len,Net::PTPCon::MaxNameLen);

  name_.copyTo(name);

  name_len=name_.len;

  con_id.number++;
  con_id.clock=ClockTimer::Get();

  is_opened=true;
  write_ok=true;

  Printf(Con,"\n\n--- Open console #; ---\n\n",getName());

  return NoError;
 }

ErrorIdType PTPConProc::read(Inbound &inbound,const Net::PTPCon::ConId &con_id_,uint32 number,LenType len)
 {
  if( !is_opened ) return Error_ConNotOpened;

  if( con_id!=con_id_ ) return Error_BadConId;

  return reader.start(inbound,number,len);
 }

ErrorIdType PTPConProc::write(const Net::PTPCon::ConId &con_id_,uint32 number,StrLen text)
 {
  if( !is_opened ) return Error_ConNotOpened;

  if( con_id!=con_id_ ) return Error_BadConId;

  if( !writer(number,text) ) return Error_WriteFault;

  return NoError;
 }

ErrorIdType PTPConProc::close(const Net::PTPCon::ConId &con_id_)
 {
  if( !is_opened ) return Error_ConNotOpened;

  if( con_id!=con_id_ ) return Error_BadConId;

  do_close();

  return NoError;
 }

void PTPConProc::function_Open(Inbound &inbound)
 {
  Tailed<Net::PTPCon::OpenInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  if( ErrorIdType error_id=open(inbound.point,
                                input.base.write_timeout_msec,
                                input.base.read_timeout_msec,
                                input.base.trigger_mask,
                                Mutate<const char>(input.tail))
    )
    {
     log("PTPConOpen(...) : #;",GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::PTPCon::OpenOutput output(con_id);

  log("PTPConOpen(#;)",getName());

  inbound.send_info(output,ptp);
 }

void PTPConProc::function_Read(Inbound &inbound)
 {
  Net::PTPCon::ReadInput input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  if( ErrorIdType error_id=read(inbound,input.con_id,input.number,input.len) )
    {
     log("PTPConRead(...) : #;",GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  inbound.complete();

  //log("PTPConRead(...)");
 }

void PTPConProc::function_Write(Inbound &inbound)
 {
  Tailed<Net::PTPCon::WriteInput> input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  StrLen text(Mutate<const char>(input.tail));

  if( ErrorIdType error_id=write(input.base.con_id,input.base.number,text) )
    {
     if( error_id==Error_WriteFault )
       {
        if( write_ok )
          {
           log("PTPConWrite(...) : #;",GetErrorDesc(error_id));

           write_ok=false;
          }
       }
     else
       {
        log("PTPConWrite(...) : #;",GetErrorDesc(error_id));
       }

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::PTPCon::WriteOutput output;

  //log("PTPConWrite(#;)\n#;\n",input.base.number,text);

  inbound.send_info(output,ptp);
 }

void PTPConProc::function_Close(Inbound &inbound)
 {
  Net::PTPCon::CloseInput input;

  if( !inbound.getInput(input) ) return inbound.send_error(ptp);

  if( ErrorIdType error_id=close(input.con_id) )
    {
     log("PTPConClose(...) : #;",GetErrorDesc(error_id));

     inbound.error_id=error_id;

     return inbound.send_error(ptp);
    }

  Net::PTPCon::CloseOutput output;

  log("PTPConClose(#;)",getName());

  inbound.send_info(output,ptp);
 }

PTPConProc::PTPConProc(ServerProcBase *base,bool exit_on_close_)
 : ProcBase(base),
   is_opened(false),
   write_ok(false),
   exit_on_close(exit_on_close_),
   reader(ptp),
   mutex("PTPConProc"),
   ins_text(0)
 {
 }

PTPConProc::~PTPConProc()
 {
  if( is_opened ) do_close();
 }

void PTPConProc::inbound(Inbound &inbound)
 {
  switch( inbound.serv_func.function_id )
    {
     case Net::PTPCon::FunctionId_Open :  function_Open(inbound); break;

     case Net::PTPCon::FunctionId_Read :  function_Read(inbound); break;

     case Net::PTPCon::FunctionId_Write : function_Write(inbound); break;

     case Net::PTPCon::FunctionId_Close : function_Close(inbound); break;

     default:
      {
       inbound.error_id=Error_NoFunction;

       inbound.send_error(ptp);
      }
    }
 }

void PTPConProc::tick()
 {
  if( is_opened )
    {
     writer.tick();
     reader.tick();
    }
 }

void PTPConProc::session(XPoint point)
 {
  if( is_opened && point==client )
    {
     do_close();

     log("New session PTPConClose(#;)",getName());
    }
 }

bool PTPConProc::exist(FunctionIdType function_id)
 {
  return function_id>=Net::PTPCon::FunctionId_Open && function_id<=Net::PTPCon::FunctionId_Close ;
 }

const char * PTPConProc::ins()
 {
  Mutex::Lock lock(mutex);

  return Replace_null(ins_text);
 }

} // namespace PTPServerProc


