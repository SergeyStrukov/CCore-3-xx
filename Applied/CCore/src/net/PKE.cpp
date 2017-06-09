/* PKE.cpp */
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

#include <CCore/inc/net/PKE.h>

#include <CCore/inc/PlatformRandom.h>
#include <CCore/inc/crypton/PlatformSHA.h>
#include <CCore/inc/crypton/PlatformAES.h>
#include <CCore/inc/crypton/DHExp.h>

#include <CCore/inc/TypeSwitch.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {
namespace PSec {

/* enum PKError */

const char * GetTextDesc(PKError error)
 {
  switch( error )
    {
     case PKENoError         : return "Ok";

     case PKError_NoClientID : return "No Client ID";
     case PKError_Exhausted  : return "Exhausted";
     case PKError_NoAlgo     : return "No algo";
     case PKError_NoAccess   : return "Access denied";
     case PKError_NoLimit    : return "Too many clients";

     default: return "???";
    }
 }

/* class ClientID */

template <class T>
void ClientID::init(PtrLen<T> name_)
 {
  if( name_.len>MaxClientIDLen )
    {
     Printf(Exception,"CCore::Net::PSec::ClientID::ClientID({len=#;}) : name is too long",name_.len);
    }

  len=(uint8)name_.len;

  name_.copyTo(name);
 }

ClientID::ClientID(StrLen name)
 {
  init(name);
 }

ClientID::ClientID(PtrLen<const uint8> name)
 {
  init(name);
 }

ClientID::~ClientID()
 {
 }

uint8 ClientID::getLen() const
 {
  return len;
 }

void ClientID::getID(uint8 buf[ /* Len */ ]) const
 {
  Range(name,len).copyTo(buf);
 }

/* struct ClientDatabase */

const Unid ClientDatabase::TypeUnid={{0x08AF'A672,0xE802'1B45,0xEF11'F1F1,0xDA1C'41DC,0x9786'21B8,0xB695'069E,0x670A'25F0,0x06EC'7D39}};

/* class AlgoSet */

AlgoSet::AlgoSet()
 {
 }

AlgoSet::~AlgoSet()
 {
 }

void AlgoSet::add(CryptID crypt_id,HashID hash_id,DHGroupID dhg_id)
 {
  algo_list.reserve(1);
  algo_lens.reserve(1);

  algo_list.append_fill(crypt_id,hash_id,dhg_id);
  algo_lens.append_fill(GetBLen(crypt_id),GetHLen(hash_id));
 }

void AlgoSet::addDefault()
 {
  add(CryptID_AES256,HashID_SHA256,DHGroupID_II);
  add(CryptID_AES256,HashID_SHA224,DHGroupID_II);
  add(CryptID_AES192,HashID_SHA256,DHGroupID_II);
  add(CryptID_AES192,HashID_SHA224,DHGroupID_II);

  add(CryptID_AES256,HashID_SHA256,DHGroupID_I);
  add(CryptID_AES256,HashID_SHA224,DHGroupID_I);
  add(CryptID_AES192,HashID_SHA256,DHGroupID_I);
  add(CryptID_AES192,HashID_SHA224,DHGroupID_I);
 }

/* struct NegotiantData */

NegotiantData::NegotiantData()
 {
 }

NegotiantData::~NegotiantData()
 {
  Crypton::ForgetRange(Range(x));
  Crypton::ForgetRange(Range(gx));
  Crypton::ForgetRange(Range(gy));
  Crypton::ForgetRange(Range(gxy));
 }

void NegotiantData::prepare(const AbstractClientID &client_id_,AbstractHashFunc *client_key_,AbstractHashFunc *server_key_)
 {
  client_id_len=client_id_.getLen();

  client_id_.getID(client_id);

  client_key=client_key_;
  server_key=server_key_;
 }

void NegotiantData::prepare(AbstractHashFunc *client_key_,AbstractHashFunc *server_key_)
 {
  client_key=client_key_;
  server_key=server_key_;
 }

bool NegotiantData::create()
 {
  SilentReportException report;

  try
    {
     encrypt.set(algo.createEncrypt());
     decrypt.set(algo.createDecrypt());
     hash.set(algo.createHash());
     dhg.set(algo.createDHGroup());

     blen=encrypt->getBLen();
     hlen=hash->getHLen();
     glen=dhg->getGLen();

     return true;
    }
  catch(...)
    {
     return false;
    }
 }

void NegotiantData::keyGen()
 {
  uint8 temp[SaveLenCounter<XPoint>::SaveLoadLen];

  {
   BufPutDev dev(temp);

   dev.use<BeOrder>(point);
  }

  ulen client_hlen=client_key->getHLen();
  ulen server_hlen=server_key->getHLen();

  uint8 key[MaxKLen];

  PtrLen<uint8> dst(key,encrypt->getKLen());

  for(;;)
    {
     client_key->add(Range_const(temp));
     client_key->add(getClientID());
     client_key->add(Range_const(client_nonce));
     client_key->add(Range_const(server_nonce));
     client_key->add(Range_const(gxy,glen));

     const uint8 *client_digest=client_key->finish();

     server_key->add(Range_const(client_digest,client_hlen));
     server_key->add(Range_const(temp));
     server_key->add(getClientID());
     server_key->add(Range_const(client_nonce));
     server_key->add(Range_const(server_nonce));
     server_key->add(Range_const(gxy,glen));

     const uint8 *server_digest=server_key->finish();

     if( server_hlen<dst.len )
       {
        (dst+=server_hlen).copy(server_digest);

        client_key->add(Range_const(server_digest,server_hlen));
       }
     else
       {
        dst.copy(server_digest);

        encrypt->key(key);
        decrypt->key(key);

        Crypton::ForgetRange(Range(key));

        return;
       }
    }
 }

void NegotiantData::clientKeyGen()
 {
  keyGen();
 }

void NegotiantData::serverKeyGen()
 {
  dhg->pow(gy,x,gxy);

  keyGen();
 }

void NegotiantData::clientGen()
 {
  random.fill(Range(client_nonce));

  random.fill(Range(x,glen));

  dhg->pow(x,gx);

  dhg->pow(gy,x,gxy);
 }

void NegotiantData::serverGen()
 {
  random.fill(Range(server_nonce));

  random.fill(Range(x,glen));

  dhg->pow(x,gx);
 }

BufPutDev NegotiantData::start(uint8 *buf,uint16 type)
 {
  BufPutDev dev(buf);

  uint8 len=random.next8();

  dev(len);

  random.fill(dev.putRange(len));

  dev.putRange(2u);

  dev.use<BeOrder>(type);

  return dev;
 }

ulen NegotiantData::finish(uint8 *buf,BufPutDev dev)
 {
  ulen len=Dist(buf,dev.getRest());

  ulen rlen=buf[0];
  uint16 plen=uint16( len-(rlen+5) );

  {
   BufPutDev temp(buf+(rlen+1));

   temp.use<BeOrder>(plen);
  }

  hash->add(Range_const(buf,len));

  dev.put(Range(hash->finish(),hlen));

  len+=hlen;

  ulen count=(len+blen-1)/blen;
  ulen total=count*blen;

  random.fill(dev.putRange(total-len));

  direct_conv.start();

  direct_conv.apply(Range(buf,total));

  for(; count ;count--,buf+=blen) encrypt->apply(buf);

  return total;
 }

PKEType NegotiantData::process(PtrLen<const uint8> &data)
 {
  uint8 *buf=const_cast<uint8 *>(data.ptr);
  ulen len=data.len;

  if( !len || len%blen ) return PKE_None;

  ulen count=len/blen;

  for(uint8 *ptr=buf; count ;count--,ptr+=blen) decrypt->apply(ptr);

  inverse_conv.start();

  inverse_conv.apply(Range(buf,len));

  ulen rlen=buf[0];

  if( len<rlen+5 ) return PKE_None;

  BufGetDev dev(buf+(rlen+1));

  uint16 plen;
  uint16 type;

  dev.use<BeOrder>(plen,type);

  ulen dlen=rlen+5+plen;

  if( len<dlen+hlen ) return PKE_None;

  hash->add(Range_const(buf,dlen));

  if( !Range(hash->finish(),hlen).equal(buf+dlen) ) return PKE_None;

  data.ptr=buf+(rlen+5);
  data.len=plen;

  return PKEType(type);
 }

bool NegotiantData::createSKey()
 {
  SilentReportException report;

  try
    {
     SessionKey *session_key=new SessionKey(algo,param);

     skey.set(session_key);

     key_buf=session_key->takeKeyBuf();

     return true;
    }
  catch(...)
    {
     return false;
    }
 }

void NegotiantData::setCounts()
 {
  ulen len=key_buf.len;
  ulen server_hlen=server_key->getHLen();

  ulen count=(len+server_hlen-1)/server_hlen;

  if( count<=10 )
    {
     rep_count=1;
     max_count=count;
    }
  else
    {
     if( count<=20 )
       rep_count=2;
     else if( count<=30 )
       rep_count=3;
     else if( count<=40 )
       rep_count=4;
     else if( count<=50 )
       rep_count=5;
     else if( count<=60 )
       rep_count=6;
     else if( count<=70 )
       rep_count=7;
     else if( count<=80 )
       rep_count=8;
     else if( count<=90 )
       rep_count=9;
     else
       rep_count=10;

     max_count=(count+rep_count-1)/rep_count;
    }

  cur_count=max_count;
 }

bool NegotiantData::testCounts()
 {
  ulen len=key_buf.len;
  ulen server_hlen=server_key->getHLen();

  return len<=server_hlen*rep_count*max_count;
 }

void NegotiantData::keyBufGen()
 {
  ulen client_hlen=client_key->getHLen();
  ulen server_hlen=server_key->getHLen();

  for(ulen cnt=rep_count; cnt ;cnt--)
    {
     client_key->add(Range_const(client_nonce));
     client_key->add(Range_const(server_nonce));
     client_key->add(Range_const(gxy,glen));

     const uint8 *client_digest=client_key->finish();

     server_key->add(Range_const(client_digest,client_hlen));
     server_key->add(Range_const(client_nonce));
     server_key->add(Range_const(server_nonce));
     server_key->add(Range_const(gxy,glen));

     const uint8 *server_digest=server_key->finish();

     if( server_hlen<key_buf.len )
       {
        (key_buf+=server_hlen).copy(server_digest);

        client_key->add(Range_const(server_digest,server_hlen));
       }
     else
       {
        key_buf.copy(server_digest);

        key_buf=Empty;

        return;
       }
    }
 }

void NegotiantData::clientKeyBufGen()
 {
  keyBufGen();
 }

void NegotiantData::serverKeyBufGen()
 {
  dhg->pow(gy,x,gxy);

  keyBufGen();
 }

/* class ClientNegotiant::Proc */

void ClientNegotiant::Proc::build1()
 {
  BufPutDev dev(send_buf);

  dev.put(neg_data.client_id_len);

  dev.put(neg_data.getClientID());

  SaveRange(algo_list,algo_count,dev);

  send_len=Dist(send_buf,dev.getRest());
 }

bool ClientNegotiant::Proc::test_algo() const
 {
  for(const CryptAlgoSelect &algo : Range(algo_list,algo_count) ) if( algo==neg_data.algo ) return true;

  return false;
 }

bool ClientNegotiant::Proc::process2(PtrLen<const uint8> data)
 {
  if( data.len==SaveLenCounter<uint32>::SaveLoadLen ) return process_error(data);

  RangeGetDev dev(data);

  dev.use<BeOrder>(neg_data.point);

  LoadRange(Range(neg_data.server_nonce),dev);

  dev(neg_data.algo);

  if( !dev || !test_algo() ) return false;

  if( !neg_data.create() )
    {
     state=State_ClientError;
     error=PKError_Exhausted;

     build_error();

     return true;
    }

  dev.get(neg_data.gy,neg_data.glen);

  if( !dev.finish() ) return false;

  neg_data.clientGen();

  neg_data.clientKeyGen();

  build3();

  inbound_func=&Proc::process4;

  return true;
 }

void ClientNegotiant::Proc::build3()
 {
  BufPutDev dev(send_buf);

  dev.use<BeOrder>(neg_data.point);

  dev.put(Range_const(neg_data.client_nonce));

  dev.put(Range_const(neg_data.gx,neg_data.glen));

  send_len=Dist(send_buf,dev.getRest());
 }

bool ClientNegotiant::Proc::process4(PtrLen<const uint8> data)
 {
  if( neg_data.process(data)!=PKE_ServerAck ) return false;

  RangeGetDev dev(data);

  CryptAlgoSelect algo;
  XPoint point=0;
  uint8 len=0;

  dev.use<BeOrder>(algo,point,len);

  PtrLen<const uint8> id=dev.getRange(len);

  if( !dev.finish() ) return false;

  if( algo!=neg_data.algo || point!=neg_data.point || !id.equal(neg_data.getClientID()) ) return false;

  build5();

  inbound_func=&Proc::process6;

  return true;
 }

void ClientNegotiant::Proc::build5()
 {
  BufPutDev dev=neg_data.start(send_buf,PKE_ClientAck);

  dev.use<BeOrder>(neg_data.algo,neg_data.point,neg_data.client_id_len);

  dev.put(neg_data.getClientID());

  send_len=neg_data.finish(send_buf,dev);
 }

bool ClientNegotiant::Proc::process6(PtrLen<const uint8> data)
 {
  if( neg_data.process(data)!=PKE_ServerParam ) return false;

  RangeGetDev dev(data);

  SessionKeyParam temp;

  dev(temp);

  if( !dev.finish() ) return false;

  neg_data.param.select(temp);

  build7();

  inbound_func=&Proc::process8;

  return true;
 }

void ClientNegotiant::Proc::build7()
 {
  BufPutDev dev=neg_data.start(send_buf,PKE_ClientParam);

  dev.use<BeOrder>(neg_data.psec_port,neg_data.param);

  send_len=neg_data.finish(send_buf,dev);
 }

bool ClientNegotiant::Proc::process8(PtrLen<const uint8> data)
 {
  switch( neg_data.process(data) )
    {
     default: return false;

     case PKE_ServerError : return process_error(data);

     case PKE_FirstServerSKey : break;
    }

  RangeGetDev dev(data);

  dev.use<BeOrder>(neg_data.rep_count,neg_data.max_count);

  neg_data.cur_count=neg_data.max_count;

  dev.get(Range(neg_data.server_nonce));

  dev.get(Range(neg_data.gy,neg_data.glen));

  if( !dev.finish() ) return false;

  if( !neg_data.createSKey() )
    {
     state=State_ClientError;
     error=PKError_Exhausted;

     build_encrypted_error();

     return true;
    }

  if( !neg_data.testCounts() ) return false;

  neg_data.clientGen();

  neg_data.clientKeyBufGen();

  build9();

  if( !--neg_data.cur_count )
    {
     inbound_func=&Proc::process11;
    }
  else
    {
     inbound_func=&Proc::process10;
    }

  return true;
 }

void ClientNegotiant::Proc::build9()
 {
  BufPutDev dev=neg_data.start(send_buf,PKE_ClientSKey);

  dev.use<BeOrder>(neg_data.cur_count);

  dev.put(Range_const(neg_data.client_nonce));

  dev.put(Range_const(neg_data.gx,neg_data.glen));

  send_len=neg_data.finish(send_buf,dev);
 }

bool ClientNegotiant::Proc::process10(PtrLen<const uint8> data)
 {
  if( neg_data.process(data)!=PKE_ServerSKey ) return false;

  RangeGetDev dev(data);

  uint32 count=0;

  dev.use<BeOrder>(count);

  dev.get(Range(neg_data.server_nonce));

  dev.get(Range(neg_data.gy,neg_data.glen));

  if( !dev.finish() ) return false;

  if( count!=neg_data.cur_count ) return false;

  neg_data.clientGen();

  neg_data.clientKeyBufGen();

  build9();

  if( !--neg_data.cur_count )
    {
     inbound_func=&Proc::process11;
    }

  return true;
 }

bool ClientNegotiant::Proc::process11(PtrLen<const uint8> data)
 {
  switch( neg_data.process(data) )
    {
     default: return false;

     case PKE_ServerError : return process_error(data);

     case PKE_Done : break;
    }

  if( +data ) return false;

  state=State_Done;

  return true;
 }

void ClientNegotiant::Proc::build_error()
 {
  uint32 code=error;

  BufPutDev dev(send_buf);

  dev.use<BeOrder>(code);

  send_len=Dist(send_buf,dev.getRest());
 }

void ClientNegotiant::Proc::build_encrypted_error()
 {
  uint32 code=error;

  BufPutDev dev=neg_data.start(send_buf,PKE_ClientError);

  dev.use<BeOrder>(code);

  send_len=neg_data.finish(send_buf,dev);
 }

bool ClientNegotiant::Proc::process_error(PtrLen<const uint8> data)
 {
  RangeGetDev dev(data);

  uint32 code=0;

  dev.use<BeOrder>(code);

  if( !dev.finish() ) return false;

  state=State_ServerError;
  error=PKError(code);

  return true;
 }

ClientNegotiant::Proc::Proc()
 {
 }

ClientNegotiant::Proc::~Proc()
 {
 }

void ClientNegotiant::Proc::prepare(XPoint psec_port,const AbstractClientID &client_id,PrimeKeyPtr &&client_key_,PrimeKeyPtr &&server_key_,SessionKeyParam param)
 {
  if( state!=State_Null )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : not null");
    }

  client_key=std::move(client_key_);
  server_key=std::move(server_key_);

  if( !client_key )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : no client key");
    }

  if( !server_key )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::prepare(...) : no server key");
    }

  neg_data.prepare(client_id,client_key.getPtr(),server_key.getPtr());

  neg_data.psec_port=psec_port;
  neg_data.param=param;

  state=State_Ready;
 }

void ClientNegotiant::Proc::start(PtrLen<const CryptAlgoSelect> algo_list_)
 {
  if( state!=State_Ready )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::start(...) : not prepared");
    }

  if( algo_list_.len>MaxAlgos )
    {
     Printf(Exception,"CCore::Net::PSec::ClientNegotiant::start(...) : too many algos");
    }

  algo_list_.copyTo(algo_list);

  algo_count=algo_list_.len;

  state=State_Started;

  build1();

  inbound_func=&Proc::process2;
 }

bool ClientNegotiant::Proc::inbound(PtrLen<const uint8> data)
 {
  if( state==State_Started ) return (this->*inbound_func)(data);

  return false;
 }

/* class ClientNegotiant::Engine */

Packet<uint8> ClientNegotiant::Engine::prepare_send()
 {
  Packet<uint8> ret=pset.try_get();

  if( !ret ) return Nothing;

  PtrLen<const uint8> data=proc.getSendData();

  if( ret.checkDataLen(outbound_format,data.len) )
    {
     ret.setDataLen(outbound_format,data.len).copy(data.ptr);

     return ret;
    }
  else
    {
     ret.complete();

     return Nothing;
    }
 }

void ClientNegotiant::Engine::inbound(Packet<uint8> packet,PtrLen<const uint8> data)
 {
  Packet<uint8> send;
  bool done=false;

  {
   Mutex::Lock lock(mutex);

   if( proc.inbound(data) )
     {
      switch( proc.getState() )
        {
         case State_Started :
          {
           tick_count=StartTickCount;
           retry_count=MaxRetry;

           send=prepare_send();
          }
         break;

         case State_ClientError :
          {
           send=prepare_send();
          }
         [[fallthrough]];

         case State_ServerError :
         case State_Done :
          {
           tick_count=0;
           retry_count=0;
           done=true;
          }
         break;
        }
     }
  }

  packet.complete();

  if( +send ) dev->outbound(send);

  if( done ) done_func();
 }

void ClientNegotiant::Engine::tick()
 {
  Packet<uint8> send;
  bool done=false;

  {
   Mutex::Lock lock(mutex);

   if( retry_count )
     {
      if( tick_count )
        {
         tick_count--;
        }
      else
        {
         retry_count--;
         tick_count=StartTickCount;

         send=prepare_send();
        }
     }
   else
     {
      if( proc.getState()==State_Started )
        {
         proc.stop();

         done=true;
        }
     }
  }

  if( +send ) dev->outbound(send);

  if( done ) done_func();
 }

ClientNegotiant::Engine::Engine(PacketEndpointDevice *dev_,Function<void (void)> done_func_)
 : dev(dev_),
   done_func(done_func_),
   pset("PSec::ClientNegotiant.pset"),
   mutex("PSec::ClientNegotiant.mutex")
 {
  outbound_format=dev->getOutboundFormat();

  dev->attach(this);
 }

ClientNegotiant::Engine::~Engine()
 {
  dev->detach();
 }

auto ClientNegotiant::Engine::getState() const -> State
 {
  Mutex::Lock lock(mutex);

  return proc.getState();
 }

auto ClientNegotiant::Engine::getError() const -> PKError
 {
  Mutex::Lock lock(mutex);

  return proc.getError();
 }

void ClientNegotiant::Engine::prepare(XPoint psec_port,const AbstractClientID &client_id,PrimeKeyPtr &&client_key,PrimeKeyPtr &&server_key,SessionKeyParam param)
 {
  Mutex::Lock lock(mutex);

  proc.prepare(psec_port,client_id,std::move(client_key),std::move(server_key),param);
 }

void ClientNegotiant::Engine::start(PtrLen<const CryptAlgoSelect> algo_list)
 {
  Packet<uint8> send;

  {
   Mutex::Lock lock(mutex);

   proc.start(algo_list);

   tick_count=StartTickCount;
   retry_count=MaxRetry;

   send=prepare_send();
  }

  if( +send ) dev->outbound(send);
 }

void ClientNegotiant::Engine::getSessionKey(MasterKeyPtr &skey)
 {
  Mutex::Lock lock(mutex);

  proc.getSessionKey(skey);
 }

/* class ClientNegotiant */

const char * GetTextDesc(ClientNegotiant::State state)
 {
  switch( state )
    {
     case ClientNegotiant::State_Null        : return "Null";
     case ClientNegotiant::State_Ready       : return "Ready";
     case ClientNegotiant::State_Started     : return "Started";
     case ClientNegotiant::State_Done        : return "Done";
     case ClientNegotiant::State_ClientError : return "ClientError";
     case ClientNegotiant::State_ServerError : return "ServerError";
     case ClientNegotiant::State_Timeout     : return "Timeout";

     default: return "???";
    }
 }

ClientNegotiant::ClientNegotiant(StrLen ep_dev_name,Function<void (void)> done_func)
 : hook(ep_dev_name),
   engine(hook,done_func)
 {
 }

ClientNegotiant::~ClientNegotiant()
 {
 }

/* class ServerNegotiant::Proc */

auto ServerNegotiant::Proc::process1(XPoint point,PtrLen<const uint8> data) -> InboundResult
 {
  RangeGetDev dev(data);

  dev(neg_data.client_id_len);

  dev.get(neg_data.client_id,neg_data.client_id_len);

  if( !dev ) return InboundDrop;

  CryptAlgoSelect selected_algo;
  bool flag=false;

  while( dev.getRest().len )
    {
     CryptAlgoSelect algo;

     dev(algo);

     if( !dev ) return InboundDrop;

     if( !flag && engine->filter(algo) )
       {
        selected_algo=algo;
        flag=true;
       }
    }

  if( !flag )
    {
     build_error(PKError_NoAlgo);

     return InboundServerError;
    }

  switch( engine->client_db.findClient(neg_data.getClientID(),client_key,client_profile) )
    {
     default:
     case ClientDatabase::FindError_NoMemory :
      {
       build_error(PKError_Exhausted);
      }
     return InboundServerError;

     case ClientDatabase::FindError_NoClientID :
      {
       build_error(PKError_NoClientID);
      }
     return InboundServerError;

     case ClientDatabase::Find_Ok : break;
    }

  neg_data.point=point;
  neg_data.algo=selected_algo;

  if( !neg_data.create() )
    {
     build_error(PKError_Exhausted);

     return InboundServerError;
    }

  neg_data.prepare(client_key.getPtr(),engine->server_key.getPtr());

  neg_data.serverGen();

  build2();

  inbound_func=&Proc::process3;

  return InboundOk;
 }

void ServerNegotiant::Proc::build2()
 {
  BufPutDev dev(send_buf);

  dev.use<BeOrder>(neg_data.point);

  dev.put(Range_const(neg_data.server_nonce));

  dev(neg_data.algo);

  dev.put(Range_const(neg_data.gx,neg_data.glen));

  send_len=Dist(send_buf,dev.getRest());
 }

auto ServerNegotiant::Proc::process3(PtrLen<const uint8> data) -> InboundResult
 {
  if( data.len==SaveLenCounter<uint32>::SaveLoadLen ) return process_error(data);

  RangeGetDev dev(data);

  XPoint point=0;

  dev.use<BeOrder>(point);

  dev.get(Range(neg_data.client_nonce));

  dev.get(Range(neg_data.gy,neg_data.glen));

  if( !dev.finish() || point!=neg_data.point ) return InboundDrop;

  neg_data.serverKeyGen();

  build4();

  inbound_func=&Proc::process5;

  return InboundOk;
 }

void ServerNegotiant::Proc::build4()
 {
  BufPutDev dev=neg_data.start(send_buf,PKE_ServerAck);

  dev.use<BeOrder>(neg_data.algo,neg_data.point,neg_data.client_id_len);

  dev.put(neg_data.getClientID());

  send_len=neg_data.finish(send_buf,dev);
 }

auto ServerNegotiant::Proc::process5(PtrLen<const uint8> data) -> InboundResult
 {
  if( neg_data.process(data)!=PKE_ClientAck ) return InboundDrop;

  RangeGetDev dev(data);

  CryptAlgoSelect algo;
  XPoint point=0;
  uint8 len=0;

  dev.use<BeOrder>(algo,point,len);

  PtrLen<const uint8> id=dev.getRange(len);

  if( !dev.finish() ) return InboundDrop;

  if( algo!=neg_data.algo || point!=neg_data.point || !id.equal(neg_data.getClientID()) ) return InboundDrop;

  build6();

  inbound_func=&Proc::process7;

  final_send_len=0;

  return InboundOk;
 }

void ServerNegotiant::Proc::build6()
 {
  BufPutDev dev=neg_data.start(send_buf,PKE_ServerParam);

  dev(engine->param);

  send_len=neg_data.finish(send_buf,dev);
 }

auto ServerNegotiant::Proc::process7(PtrLen<const uint8> data) -> InboundResult
 {
  if( neg_data.process(data)!=PKE_ClientParam ) return InboundDrop;

  RangeGetDev dev(data);

  dev.use<BeOrder>(neg_data.psec_port,neg_data.param);

  if( !dev.finish() ) return InboundDrop;

  if( !neg_data.param.fit() ) return InboundDrop;

  if( !neg_data.createSKey() )
    {
     build_encrypted_error(PKError_Exhausted);

     return InboundServerError;
    }

  build8();

  inbound_func=&Proc::process9;

  return InboundOk;
 }

void ServerNegotiant::Proc::build8()
 {
  neg_data.setCounts();

  neg_data.serverGen();

  BufPutDev dev=neg_data.start(send_buf,PKE_FirstServerSKey);

  dev.use<BeOrder>(neg_data.rep_count,neg_data.max_count);

  dev.put(Range_const(neg_data.server_nonce));

  dev.put(Range_const(neg_data.gx,neg_data.glen));

  send_len=neg_data.finish(send_buf,dev);
 }

auto ServerNegotiant::Proc::process9(PtrLen<const uint8> data) -> InboundResult
 {
  switch( neg_data.process(data) )
    {
     default: return InboundDrop;

     case PKE_ClientError : return process_error(data);

     case PKE_ClientSKey : break;
    }

  RangeGetDev dev(data);

  uint32 count=0;

  dev.use<BeOrder>(count);

  dev.get(Range(neg_data.client_nonce));

  dev.get(Range(neg_data.gy,neg_data.glen));

  if( !dev.finish() ) return InboundDrop;

  if( count!=neg_data.cur_count ) return InboundDrop;

  neg_data.serverKeyBufGen();

  if( !--neg_data.cur_count )
    {
     XPoint psec_point=engine->port_manager->changePort(neg_data.point,neg_data.psec_port);

     switch( engine->epman.open(psec_point,*neg_data.skey,std::move(client_profile)) )
       {
        default:
        case EndpointManager::OpenError_NoMemory :
         {
          build_encrypted_error(PKError_Exhausted);
         }
        return InboundServerError;

        case EndpointManager::OpenError_OpenLimit :
         {
          build_encrypted_error(PKError_NoLimit);
         }
        return InboundServerError;

        case EndpointManager::OpenError_NoAccess :
         {
          build_encrypted_error(PKError_NoAccess);
         }
        return InboundServerError;

        case EndpointManager::Open_Ok : break;
       }

     build11();

     inbound_func=&Proc::process_final;

     return InboundLast;
    }
  else
    {
     build10();

     return InboundOk;
    }
 }

void ServerNegotiant::Proc::build10()
 {
  neg_data.serverGen();

  BufPutDev dev=neg_data.start(send_buf,PKE_ServerSKey);

  dev.use<BeOrder>(neg_data.cur_count);

  dev.put(Range_const(neg_data.server_nonce));

  dev.put(Range_const(neg_data.gx,neg_data.glen));

  send_len=neg_data.finish(send_buf,dev);
 }

void ServerNegotiant::Proc::build11()
 {
  BufPutDev dev=neg_data.start(final_send_buf,PKE_Done);

  final_send_len=neg_data.finish(final_send_buf,dev);
 }

auto ServerNegotiant::Proc::process_final(PtrLen<const uint8> data) -> InboundResult
 {
  switch( process1(neg_data.point,data) )
    {
     case InboundOk : return InboundOk;

     case InboundServerError : return InboundServerError;

     default: return InboundFinal;
    }
 }

void ServerNegotiant::Proc::build_error(PKError error)
 {
  uint32 code=error;

  BufPutDev dev(send_buf);

  dev.use<BeOrder>(code);

  send_len=Dist(send_buf,dev.getRest());
 }

void ServerNegotiant::Proc::build_encrypted_error(PKError error)
 {
  uint32 code=error;

  BufPutDev dev=neg_data.start(send_buf,PKE_ServerError);

  dev.use<BeOrder>(code);

  send_len=neg_data.finish(send_buf,dev);
 }

auto ServerNegotiant::Proc::process_error(PtrLen<const uint8> data) -> InboundResult
 {
  RangeGetDev dev(data);

  uint32 code=0;

  dev.use<BeOrder>(code);

  if( !dev.finish() ) return InboundDrop;

  // code

  return InboundClientError;
 }

ServerNegotiant::Proc::Proc(Engine *engine_)
 : engine(engine_)
 {
 }

ServerNegotiant::Proc::~Proc()
 {
 }

bool ServerNegotiant::Proc::inbound_first(XPoint point,PtrLen<const uint8> data,PacketList &list)
 {
  switch( process1(point,data) )
    {
     case InboundOk :
      {
       tick_count=StartTickCount;
       retry_count=MaxRetry;

       engine->prepare_send(point,Range_const(send_buf,send_len),list);
      }
     return false;

     case InboundServerError :
      {
       engine->prepare_send(point,Range_const(send_buf,send_len),list);
      }
     return true;

     default: return true;
    }
 }

bool ServerNegotiant::Proc::inbound(PtrLen<const uint8> data,PacketList &list)
 {
  switch( (this->*inbound_func)(data) )
    {
     case InboundOk :
      {
       tick_count=StartTickCount;
       retry_count=MaxRetry;

       engine->prepare_send(neg_data.point,Range_const(send_buf,send_len),list);
      }
     break;

     case InboundLast :
      {
       tick_count=engine->final_tick_count;
       retry_count=1;

       engine->prepare_send(neg_data.point,Range_const(final_send_buf,final_send_len),list);
      }
     break;

     case InboundFinal :
      {
       engine->prepare_send(neg_data.point,Range_const(final_send_buf,final_send_len),list);
      }
     break;

     case InboundDrop :
      {
       if( final_send_len )
         {
          engine->prepare_send(neg_data.point,Range_const(final_send_buf,final_send_len),list);
         }
      }
     break;

     case InboundServerError :
      {
       engine->prepare_send(neg_data.point,Range_const(send_buf,send_len),list);
      }
     return true;

     case InboundClientError : return true;
    }

  return false;
 }

bool ServerNegotiant::Proc::tick(PacketList &list)
 {
  if( retry_count )
    {
     if( tick_count )
       {
        tick_count--;
       }
     else
       {
        if( --retry_count )
          {
           tick_count=StartTickCount;

           engine->prepare_send(neg_data.point,Range_const(send_buf,send_len),list);
          }
        else
          {
           retry_count=1;

           return true;
          }
       }
    }

  return false;
 }

/* class ServerNegotiant::Engine */

bool ServerNegotiant::Engine::filter(const CryptAlgoSelect &algo) const
 {
  for(const CryptAlgoSelect &obj : algo_list ) if( algo==obj ) return true;

  return false;
 }

void ServerNegotiant::Engine::prepare_send(XPoint point,PtrLen<const uint8> send_data,PacketList &list)
 {
  Packet<uint8> packet=pset.try_get();

  if( !packet ) return;

  if( packet.checkDataLen(outbound_format,send_data.len) )
    {
     packet.setDataLen(outbound_format,send_data.len).copy(send_data.ptr);

     list.put(packet.pushExt<XPoint>(point));
    }
  else
    {
     packet.complete();
    }
 }

void ServerNegotiant::Engine::send(PacketList &list)
 {
  while( PacketHeader *packet_=list.get() )
    {
     Packet<uint8,XPoint> packet=packet_;
     XPoint point=*packet.getExt();

     dev->outbound(point,packet.popExt());
    }
 }

void ServerNegotiant::Engine::prepare_error(XPoint point,PKError error,PacketList &list)
 {
  uint32 code=error;

  uint8 temp[SaveLenCounter<uint32>::SaveLoadLen];

  BufPutDev dev(temp);

  dev.use<BeOrder>(code);

  prepare_send(point,Range_const(temp),list);
 }

void ServerNegotiant::Engine::inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data)
 {
  PacketList list;

  {
   Mutex::Lock lock(mutex);

   if( enable )
     {
      if( map.getCount()<max_clients )
        {
         SilentReportException report;

         try
           {
            auto result=map.find_or_add(point,this);

            if( result.new_flag )
              {
               if( result.obj->inbound_first(point,data,list) )
                 {
                  map.del(point);
                 }
              }
            else
              {
               if( result.obj->inbound(data,list) )
                 {
                  map.del(point);
                 }
              }
           }
         catch(...)
           {
            prepare_error(point,PKError_Exhausted,list);
           }
        }
      else
        {
         if( auto *obj=map.find(point) )
           {
            if( obj->inbound(data,list) )
              {
               map.del(point);
              }
           }
         else
           {
            prepare_error(point,PKError_Exhausted,list);
           }
        }
     }
  }

  packet.complete();

  send(list);
 }

void ServerNegotiant::Engine::tick()
 {
  PacketList list;

  {
   Mutex::Lock lock(mutex);

   if( enable )
     {
      map.delIf( [&] (XPoint,Proc &proc) { return proc.tick(list); } );
     }
  }

  send(list);
 }

ServerNegotiant::Engine::Engine(PacketMultipointDevice *dev_,PortManager *port_manager_,const ClientDatabase &client_db_,EndpointManager &epman_,ulen max_clients_,MSec final_timeout)
 : dev(dev_),
   port_manager(port_manager_),
   client_db(client_db_),
   epman(epman_),
   max_clients(max_clients_),
   pset("PSec::ServerNegotiant.pset"),
   mutex("PSec::ServerNegotiant.mutex")
 {
  outbound_format=dev->getOutboundFormat();

  final_tick_count=ToTickCount(final_timeout);

  dev->attach(this);
 }

ServerNegotiant::Engine::~Engine()
 {
  dev->detach();
 }

void ServerNegotiant::Engine::prepare(PrimeKeyPtr &&server_key_,SessionKeyParam param_)
 {
  Mutex::Lock lock(mutex);

  if( enable )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::prepare(...) : already started");
    }

  server_key=std::move(server_key_);

  param=param_;

  if( !server_key )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::prepare(...) : no server key");
    }
 }

void ServerNegotiant::Engine::start(PtrLen<const CryptAlgoSelect> algo_list_)
 {
  Mutex::Lock lock(mutex);

  if( enable )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::start(...) : already started");
    }

  if( !server_key )
    {
     Printf(Exception,"CCore::Net::PSec::ServerNegotiant::start(...) : not prepared");
    }

  algo_list.erase();

  algo_list.extend_copy(algo_list_);

  enable=true;
 }

/* class ServerNegotiant */

ServerNegotiant::ServerNegotiant(StrLen mp_dev_name,const ClientDatabase &client_db,EndpointManager &epman,ulen max_clients,MSec final_timeout)
 : hook(mp_dev_name),
   engine(hook,hook,client_db,epman,max_clients,final_timeout)
 {
 }

ServerNegotiant::~ServerNegotiant()
 {
 }

} // namespace PSec
} // namespace Net
} // namespace CCore


