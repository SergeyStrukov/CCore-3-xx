/* PSecKey.h */
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

#ifndef CCore_inc_net_PSecKey_h
#define CCore_inc_net_PSecKey_h

#include <CCore/inc/net/PSecCore.h>

#include <CCore/inc/Scanf.h>
#include <CCore/inc/SaveLoad.h>

namespace CCore {
namespace Net {
namespace PSec {

/* consts */

inline constexpr uint16 MinKeySetLen     = 5 ;
inline constexpr uint16 DefaultKeySetLen = 10 ;
inline constexpr uint16 MaxKeySetLen     = 100 ;

inline constexpr uint32 MinTTL     = 360 ;   // 6 min
inline constexpr uint32 DefaultTTL = 3600 ;  // 1 hour
inline constexpr uint32 MaxTTL     = 36000 ; // 10 hour

inline constexpr uint32 MinUTL     = 1'000'000 ;
inline constexpr uint32 DefaultUTL = 100'000'000 ;
inline constexpr uint32 MaxUTL     = 1'000'000'000 ;

/* enum CryptID */

enum CryptID : uint8
 {
  CryptID_AES128,
  CryptID_AES192,
  CryptID_AES256

  // may be continued
 };

const char * GetTextDesc(CryptID crypt_id);

class ProxySet_CryptID : public StringSetScan
 {
  public:

   ProxySet_CryptID();

   void map(CryptID &ret) const;
 };

/* enum HashID */

enum HashID : uint8
 {
  HashID_SHA1,
  HashID_SHA224,
  HashID_SHA256,
  HashID_SHA384,
  HashID_SHA512

  // may be continued
 };

const char * GetTextDesc(HashID hash_id);

class ProxySet_HashID : public StringSetScan
 {
  public:

   ProxySet_HashID();

   void map(HashID &ret) const;
 };

/* enum DHGroupID */

enum DHGroupID : uint8
 {
  DHGroupID_I,
  DHGroupID_II

  // may be continued
 };

const char * GetTextDesc(DHGroupID dhg_id);

class ProxySet_DHGroupID : public StringSetScan
 {
  public:

   ProxySet_DHGroupID();

   void map(DHGroupID &ret) const;
 };

} // namespace PSec
} // namespace Net

/* enum CryptID */

template <>
struct ScanProxy<Net::PSec::CryptID> : ScanProxySet<Net::PSec::CryptID,Net::PSec::ProxySet_CryptID> {};

/* enum HashID */

template <>
struct ScanProxy<Net::PSec::HashID> : ScanProxySet<Net::PSec::HashID,Net::PSec::ProxySet_HashID> {};

/* enum DHGroupID */

template <>
struct ScanProxy<Net::PSec::DHGroupID> : ScanProxySet<Net::PSec::DHGroupID,Net::PSec::ProxySet_DHGroupID> {};

namespace Net {
namespace PSec {

/* functions */

bool IsValid(CryptID crypt_id);

bool IsValid(HashID hash_id);

bool IsValid(DHGroupID dhg_id);

AbstractCryptFunc * CreateEncrypt(CryptID crypt_id);

AbstractCryptFunc * CreateDecrypt(CryptID crypt_id);

AbstractHashFunc * CreateHash(HashID hash_id);

AbstractHashFunc * CreateKeyedHash(HashID hash_id,PtrLen<const uint8> key);

AbstractDHGroup * CreateDHGroup(DHGroupID dhg_id);

ulen GetBLen(CryptID crypt_id);

ulen GetKLen(CryptID crypt_id);

ulen GetHLen(HashID hash_id);

ulen GetGLen(DHGroupID dhg_id);

/* classes */

struct CryptAlgoSelect;

struct SessionKeyParam;

class SessionKey;

/* struct CryptAlgoSelect */

struct CryptAlgoSelect
 {
  uint8 crypt_id = CryptID_AES256 ;
  uint8 hash_id = HashID_SHA256 ;
  uint8 dhg_id = DHGroupID_II ;

  // constructors

  CryptAlgoSelect() noexcept {}

  CryptAlgoSelect(CryptID crypt_id_,HashID hash_id_,DHGroupID dhg_id_) : crypt_id(crypt_id_),hash_id(hash_id_),dhg_id(dhg_id_) {}

  // methods

  bool operator == (const CryptAlgoSelect &obj) const
   {
    return crypt_id==obj.crypt_id && hash_id==obj.hash_id && dhg_id==obj.dhg_id ;
   }

  bool operator != (const CryptAlgoSelect &obj) const
   {
    return !(*this==obj);
   }

  // methods

  bool isValid() const { return IsValid(CryptID(crypt_id)) && IsValid(HashID(hash_id)) && IsValid(DHGroupID(dhg_id)) ; }

  AbstractCryptFunc * createEncrypt() const { return CreateEncrypt(CryptID(crypt_id)); }

  AbstractCryptFunc * createDecrypt() const { return CreateDecrypt(CryptID(crypt_id)); }

  AbstractHashFunc * createHash() const { return CreateHash(HashID(hash_id)); }

  AbstractDHGroup * createDHGroup() const { return CreateDHGroup(DHGroupID(dhg_id)); }

  ulen getKLen() const { return GetKLen(CryptID(crypt_id)); }

  ulen getHLen() const { return GetHLen(HashID(hash_id)); }

  ulen getGLen() const { return GetGLen(DHGroupID(dhg_id)); }

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint8,uint8,uint8>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(crypt_id,hash_id,dhg_id);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(crypt_id,hash_id,dhg_id);
   }
 };

/* struct SessionKeyParam */

struct SessionKeyParam
 {
  uint16 keyset_len = DefaultKeySetLen ;
  uint32 ttl = DefaultTTL ;
  uint32 utl = DefaultUTL ;

  // constructors

  SessionKeyParam() noexcept {}

  SessionKeyParam(uint16 keyset_len_,uint32 ttl_,uint32 utl_) : keyset_len(keyset_len_),ttl(ttl_),utl(utl_) {}

  // methods

  bool fit() const
   {
    return Fit(MinKeySetLen,keyset_len,MaxKeySetLen) && Fit(MinTTL,ttl,MaxTTL) && Fit(MinUTL,utl,MaxUTL) ;
   }

  void cap()
   {
    keyset_len=Cap(MinKeySetLen,keyset_len,MaxKeySetLen);
    ttl=Cap(MinTTL,ttl,MaxTTL);
    utl=Cap(MinUTL,utl,MaxUTL);
   }

  void select(const SessionKeyParam &obj)
   {
    Replace_min(keyset_len,obj.keyset_len);
    Replace_min(ttl,obj.ttl);
    Replace_min(utl,obj.utl);

    cap();
   }

  // save/load object

  enum { SaveLoadLen = SaveLenCounter<uint16,uint32,uint32>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(keyset_len,ttl,utl);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(keyset_len,ttl,utl);
   }
 };

/* class SessionKey */

class SessionKey : public MasterKey
 {
   static constexpr ulen RandomWarpLen = 128 ;

   CryptAlgoSelect algo_select;
   SessionKeyParam param;

   ulen klen;
   ulen ktotal;
   ulen secret_len;

   SimpleArray<uint8> key_buf;

  private:

   struct GetSecretLenCtx;
   struct CreateKeyGenCtx;

   static ulen GetSecretLen(CryptAlgoSelect algo_select,ulen klen);

   template <class T>
   AbstractKeyGen * createKeyGen(OwnPtr<AbstractHashFunc> &&hash) const
    {
     auto *ret=new KeyGen<T>(std::move(hash),klen);

     ret->takeSecret().copy(key_buf.getPtr()+ktotal);

     return ret;
    }

  public:

   SessionKey(CryptAlgoSelect algo_select,SessionKeyParam param);

   virtual ~SessionKey();

   PtrLen<uint8> takeKeyBuf() { return Range(key_buf); }

   // MasterKey

   // factory

   virtual AbstractCryptFunc * createEncrypt() const;

   virtual AbstractCryptFunc * createDecrypt() const;

   virtual AbstractHashFunc * createHash() const;

   virtual AbstractKeyGen * createKeyGen() const;

   virtual AbstractRandomGen * createRandom() const;

   // keys

   virtual ulen getKLen() const;

   virtual LifeLim getLifeLim() const;

   virtual void getKey0(uint8 key[ /* KLen */ ]) const;

   virtual ulen getKeySetLen() const;

   virtual void getKey(ulen index,uint8 key[ /* KLen */ ]) const;
 };

} // namespace PSec
} // namespace Net
} // namespace CCore

#endif

