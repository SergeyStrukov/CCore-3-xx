/* PKE.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_net_PKE_h
#define CCore_inc_net_PKE_h

#include <CCore/inc/net/PSecKey.h>
#include <CCore/inc/net/PacketEndpointDevice.h>

#include <CCore/inc/PacketSet.h>

#include <CCore/inc/Scanf.h>
#include <CCore/inc/TreeMap.h>
#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/ObjHost.h>
#include <CCore/inc/PlatformRandom.h>

namespace CCore {
namespace Net {
namespace PSec {

/* consts */

inline constexpr ulen MaxClientIDLen = 255 ;

inline constexpr ulen NonceLen = 128 ;

inline constexpr unsigned StartTickCount = InboundTicksPerSec*1 ; // 1 sec

inline constexpr unsigned MaxRetry = 100 ;

inline constexpr ulen MaxAlgos = 16 ;

inline constexpr ulen MaxPKETransLen = 1100 ;

/* enum PKEType */

enum PKEType : uint16
 {
  PKE_None      = 0,

  PKE_ServerAck = 1,
  PKE_ClientAck,
  PKE_ServerParam,
  PKE_ClientParam,
  PKE_FirstServerSKey,
  PKE_ClientSKey,
  PKE_ServerSKey,
  PKE_Done,

  PKE_ServerError = 100,
  PKE_ClientError = 101
 };

/* classes */

//enum PKError;

struct AbstractClientID;

class ClientID;

struct ClientDatabase;

class AlgoSet;

struct NegotiantData;

class ClientNegotiant;

class ServerNegotiant;

/* enum PKError */

enum PKError : uint32
 {
  PKENoError = 0 ,
  PKError_NoClientID,
  PKError_Exhausted,
  PKError_NoAlgo,
  PKError_NoAccess,
  PKError_NoLimit
 };

const char * GetTextDesc(PKError error);

/* struct AbstractClientID */

struct AbstractClientID : MemBase_nocopy
 {
  virtual ~AbstractClientID() {}

  virtual uint8 getLen() const =0;

  virtual void getID(uint8 buf[ /* Len */ ]) const =0;
 };

/* type ClientIDPtr */

using ClientIDPtr = OwnPtr<AbstractClientID> ;

/* class ClientID */

class ClientID : public AbstractClientID
 {
   uint8 name[MaxClientIDLen];
   uint8 len;

  private:

   template <class T>
   void init(PtrLen<T> name);

  public:

   explicit ClientID(StrLen name);

   explicit ClientID(PtrLen<const uint8> name);

   virtual ~ClientID();

   // AbstractClientID

   virtual uint8 getLen() const;

   virtual void getID(uint8 buf[ /* Len */ ]) const;
 };

/* type PrimeKeyPtr */

using PrimeKeyPtr = OwnPtr<AbstractHashFunc> ;

/* struct ClientDatabase */

struct ClientDatabase
 {
  static const Unid TypeUnid;

  enum FindErrorCode : uint32
   {
    Find_Ok = 0,

    FindError_NoMemory,
    FindError_NoClientID
   };

  virtual FindErrorCode findClient(PtrLen<const uint8> client_id,PrimeKeyPtr &client_key,ClientProfilePtr &client_profile) const =0;
 };

/* class AlgoSet */

class AlgoSet : NoCopy
 {
   DynArray<CryptAlgoSelect> algo_list;
   DynArray<AlgoLen> algo_lens;

  public:

   AlgoSet();

   enum DefaultType { DefaultSet };

   explicit AlgoSet(DefaultType) { addDefault(); }

   ~AlgoSet();

   void add(CryptID crypt_id,HashID hash_id,DHGroupID dhg_id);

   void addDefault();

   PtrLen<const CryptAlgoSelect> getAlgoList() const { return Range(algo_list); }

   PtrLen<const AlgoLen> getAlgoLens() const { return Range(algo_lens); }
 };

/* struct NegotiantData */

struct NegotiantData : NoCopy
 {
  // machines

  PlatformRandom random;

  OwnPtr<AbstractCryptFunc> encrypt;
  OwnPtr<AbstractCryptFunc> decrypt;
  OwnPtr<AbstractHashFunc> hash;
  OwnPtr<AbstractDHGroup> dhg;

  DirectConvolution direct_conv;
  InverseConvolution inverse_conv;

  // id part

  uint8 client_id[MaxClientIDLen];
  uint8 client_id_len;

  AbstractHashFunc *client_key;
  AbstractHashFunc *server_key;

  // key part

  XPoint point;
  CryptAlgoSelect algo;
  uint8 server_nonce[NonceLen];
  uint8 client_nonce[NonceLen];

  ulen blen;
  ulen hlen;
  ulen glen;

  uint8 x[MaxGLen];
  uint8 gx[MaxGLen];
  uint8 gy[MaxGLen];
  uint8 gxy[MaxGLen];

  NegotiantData();

  ~NegotiantData();

  PtrLen<const uint8> getClientID() const { return Range(client_id,client_id_len); }

  void prepare(const AbstractClientID &client_id,AbstractHashFunc *client_key,AbstractHashFunc *server_key);

  void prepare(AbstractHashFunc *client_key,AbstractHashFunc *server_key);

  bool create();

  void keyGen();

  void clientKeyGen();

  void serverKeyGen();

  void clientGen();

  void serverGen();

  // encrypt/decrypt packets

  BufPutDev start(uint8 *buf,uint16 type);

  ulen finish(uint8 *buf,BufPutDev dev);

  PKEType process(PtrLen<const uint8> &data);

  // skey part

  XPoint psec_port;
  SessionKeyParam param;
  MasterKeyPtr skey;
  PtrLen<uint8> key_buf;

  uint32 rep_count;
  uint32 max_count;
  uint32 cur_count;

  bool createSKey();

  void setCounts();

  bool testCounts();

  void keyBufGen();

  void clientKeyBufGen();

  void serverKeyBufGen();
 };

/* class ClientNegotiant */

class ClientNegotiant : NoCopy
 {
  public:

   enum State
    {
     State_Null,
     State_Ready,
     State_Started,
     State_Done,
     State_ClientError,
     State_ServerError,
     State_Timeout
    };

   friend const char * GetTextDesc(State state);

  private:

   class Proc : NoCopy
    {
      State state = State_Null ;
      PKError error = PKENoError ;

      PrimeKeyPtr client_key;
      PrimeKeyPtr server_key;

      CryptAlgoSelect algo_list[MaxAlgos];
      ulen algo_count = 0 ;

      uint8 send_buf[MaxPKETransLen];
      ulen send_len = 0 ;

      using InboundFunc = bool (Proc::*)(PtrLen<const uint8> data) ;

      InboundFunc inbound_func;

      NegotiantData neg_data;

     private:

      void build1();

      bool test_algo() const;

      bool process2(PtrLen<const uint8> data);

      void build3();

      bool process4(PtrLen<const uint8> data);

      void build5();

      bool process6(PtrLen<const uint8> data);

      void build7();

      bool process8(PtrLen<const uint8> data);

      void build9();

      bool process10(PtrLen<const uint8> data);

      bool process11(PtrLen<const uint8> data);

      void build_error();

      void build_encrypted_error();

      bool process_error(PtrLen<const uint8> data);

     public:

      Proc();

      ~Proc();

      State getState() const { return state; }

      PKError getError() const { return error; }

      void prepare(XPoint psec_port,const AbstractClientID &client_id,PrimeKeyPtr &&client_key,PrimeKeyPtr &&server_key,SessionKeyParam param);

      void start(PtrLen<const CryptAlgoSelect> algo_list);

      void stop() { state=State_Timeout; }

      bool inbound(PtrLen<const uint8> data);

      PtrLen<const uint8> getSendData() const { return Range(send_buf,send_len); }

      void getSessionKey(MasterKeyPtr &ret) { ret=std::move(neg_data.skey); }
    };

   class Engine : public NoCopyBase<PacketEndpointDevice::InboundProc>
    {
      PacketEndpointDevice *dev;

      PacketFormat outbound_format;

      Function<void (void)> done_func;

      PacketSet<uint8> pset;

      mutable Mutex mutex;

      Proc proc;

      unsigned tick_count = 0 ;
      unsigned retry_count = 0 ;

     private:

      Packet<uint8> prepare_send();

      // InboundProc

      virtual void inbound(Packet<uint8> packet,PtrLen<const uint8> data);

      virtual void tick();

     public:

      Engine(PacketEndpointDevice *dev,Function<void (void)> done_func);

      ~Engine();

      State getState() const;

      PKError getError() const;

      void prepare(XPoint psec_port,const AbstractClientID &client_id,PrimeKeyPtr &&client_key,PrimeKeyPtr &&server_key,SessionKeyParam param);

      void start(PtrLen<const CryptAlgoSelect> algo_list);

      void getSessionKey(MasterKeyPtr &skey);
    };

  private:

   ObjHook hook;

   Engine engine;

  public:

   ClientNegotiant(StrLen ep_dev_name,Function<void (void)> done_func);

   ~ClientNegotiant();

   State getState() const { return engine.getState(); }

   PKError getError() const { return engine.getError(); }

   void prepare(XPoint psec_port,const AbstractClientID &client_id,PrimeKeyPtr &&client_key,PrimeKeyPtr &&server_key,SessionKeyParam param={})
    {
     engine.prepare(psec_port,client_id,std::move(client_key),std::move(server_key),param);
    }

   void start(PtrLen<const CryptAlgoSelect> algo_list) { engine.start(algo_list); }

   void start(const AlgoSet &algo_set) { start(algo_set.getAlgoList()); }

   void getSessionKey(MasterKeyPtr &ret) { return engine.getSessionKey(ret); }
 };

/* class ServerNegotiant */

class ServerNegotiant : NoCopy
 {
   class Engine;

   class Proc : NoCopy
    {
      Engine *engine;

      uint8 send_buf[MaxPKETransLen];
      ulen send_len = 0 ;

      uint8 final_send_buf[MaxPKETransLen];
      ulen final_send_len = 0 ;

      unsigned tick_count = 0 ;
      unsigned retry_count = 0 ;

      enum InboundResult
       {
        InboundDrop,
        InboundOk,
        InboundLast,
        InboundFinal,
        InboundServerError,
        InboundClientError
       };

      using InboundFunc = InboundResult (Proc::*)(PtrLen<const uint8> data);

      InboundFunc inbound_func;

      PrimeKeyPtr client_key;
      ClientProfilePtr client_profile;

      NegotiantData neg_data;

     private:

      InboundResult process1(XPoint point,PtrLen<const uint8> data);

      void build2();

      InboundResult process3(PtrLen<const uint8> data);

      void build4();

      InboundResult process5(PtrLen<const uint8> data);

      void build6();

      InboundResult process7(PtrLen<const uint8> data);

      void build8();

      InboundResult process9(PtrLen<const uint8> data);

      void build10();

      void build11();

      InboundResult process_final(PtrLen<const uint8> data);

      void build_error(PKError error);

      void build_encrypted_error(PKError error);

      InboundResult process_error(PtrLen<const uint8> data);

     public:

      explicit Proc(Engine *engine);

      ~Proc();

      bool inbound_first(XPoint point,PtrLen<const uint8> data,PacketList &list); // true to del

      bool inbound(PtrLen<const uint8> data,PacketList &list); // true to del

      bool tick(PacketList &list); // true to del
    };

   class Engine : public NoCopyBase<PacketMultipointDevice::InboundProc>
    {
      PacketMultipointDevice *dev;
      PortManager *port_manager;

      PacketFormat outbound_format;

      const ClientDatabase &client_db;
      PrimeKeyPtr server_key;
      EndpointManager &epman;
      ulen max_clients;
      unsigned final_tick_count;

      SessionKeyParam param;

      PacketSet<uint8> pset;

      Mutex mutex;

      bool enable = false ;

      DynArray<CryptAlgoSelect> algo_list;

      RadixTreeMap<XPoint,Proc> map;

      friend class Proc;

     private:

      bool filter(const CryptAlgoSelect &algo) const;

      void prepare_send(XPoint point,PtrLen<const uint8> send_data,PacketList &list);

      void send(PacketList &list);

      void prepare_error(XPoint point,PKError error,PacketList &list);

      // InboundProc

      virtual void inbound(XPoint point,Packet<uint8> packet,PtrLen<const uint8> data);

      virtual void tick();

     public:

      Engine(PacketMultipointDevice *dev,PortManager *port_manager,const ClientDatabase &client_db,EndpointManager &epman,ulen max_clients,MSec final_timeout);

      ~Engine();

      void prepare(PrimeKeyPtr &&server_key,SessionKeyParam param);

      void start(PtrLen<const CryptAlgoSelect> algo_list);
    };

  private:

   ObjHook hook;

   Engine engine;

  public:

   static constexpr ulen DefaultMaxClients = 10'000 ;

   ServerNegotiant(StrLen mp_dev_name,const ClientDatabase &client_db,EndpointManager &epman,ulen max_clients=DefaultMaxClients,MSec final_timeout=5_sec);

    // client_db and epman methods are called under the mutex protection

   ~ServerNegotiant();

   void prepare(PrimeKeyPtr &&server_key,SessionKeyParam param={}) { engine.prepare(std::move(server_key),param); }

   void start(PtrLen<const CryptAlgoSelect> algo_list) { engine.start(algo_list); }

   void start(const AlgoSet &algo_set) { start(algo_set.getAlgoList()); }
 };

} // namespace PSec
} // namespace Net
} // namespace CCore

#endif


