/* PSecKey.cpp */
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

#include <CCore/inc/net/PSecKey.h>

#include <CCore/inc/TypeSwitch.h>

#include <CCore/inc/PlatformRandom.h>
#include <CCore/inc/crypton/PlatformSHA.h>
#include <CCore/inc/crypton/PlatformAES.h>
#include <CCore/inc/crypton/DHExp.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Net {
namespace PSec {

/* enum CryptID */

const char * GetTextDesc(CryptID crypt_id)
 {
  switch( crypt_id )
    {
     case CryptID_AES128 : return "AES128";
     case CryptID_AES192 : return "AES192";
     case CryptID_AES256 : return "AES256";

     default: return "???";
    }
 }

ProxySet_CryptID::ProxySet_CryptID()
 : StringSetScan{"AES128","AES192","AES256"}
 {
 }

void ProxySet_CryptID::map(CryptID &ret) const
 {
  switch( *this )
    {
     case 1 : ret=CryptID_AES128; break;
     case 2 : ret=CryptID_AES192; break;
     case 3 : ret=CryptID_AES256; break;
    }
 }

/* enum HashID */

const char * GetTextDesc(HashID hash_id)
 {
  switch( hash_id )
    {
     case HashID_SHA1   : return "SHA1";
     case HashID_SHA224 : return "SHA224";
     case HashID_SHA256 : return "SHA256";
     case HashID_SHA384 : return "SHA384";
     case HashID_SHA512 : return "SHA512";

     default: return "???";
    }
 }

ProxySet_HashID::ProxySet_HashID()
 : StringSetScan{"SHA1","SHA224","SHA256","SHA384","SHA512"}
 {
 }

void ProxySet_HashID::map(HashID &ret) const
 {
  switch( *this )
    {
     case 1 : ret=HashID_SHA1;   break;
     case 2 : ret=HashID_SHA224; break;
     case 3 : ret=HashID_SHA256; break;
     case 4 : ret=HashID_SHA384; break;
     case 5 : ret=HashID_SHA512; break;
    }
 }

/* enum DHGroupID */

const char * GetTextDesc(DHGroupID dhg_id)
 {
  switch( dhg_id )
    {
     case DHGroupID_I  : return "DHG_I";
     case DHGroupID_II : return "DHG_II";

     default: return "???";
    }
 }

ProxySet_DHGroupID::ProxySet_DHGroupID()
 : StringSetScan{"DHG_I","DHG_II"}
 {
 }

void ProxySet_DHGroupID::map(DHGroupID &ret) const
 {
  switch( *this )
    {
     case 1 : ret=DHGroupID_I;  break;
     case 2 : ret=DHGroupID_II; break;
    }
 }

/* case lists */

using EncryptCaseList = Meta::CaseList<Meta::Case<uint8,CryptID_AES128,Crypton::PlatformAES128>,
                                       Meta::Case<uint8,CryptID_AES192,Crypton::PlatformAES192>,
                                       Meta::Case<uint8,CryptID_AES256,Crypton::PlatformAES256> > ;

using DecryptCaseList = Meta::CaseList<Meta::Case<uint8,CryptID_AES128,Crypton::PlatformAESInverse128>,
                                       Meta::Case<uint8,CryptID_AES192,Crypton::PlatformAESInverse192>,
                                       Meta::Case<uint8,CryptID_AES256,Crypton::PlatformAESInverse256> > ;

using HashCaseList = Meta::CaseList<Meta::Case<uint8,HashID_SHA1  ,Crypton::PlatformSHA1  >,
                                    Meta::Case<uint8,HashID_SHA224,Crypton::PlatformSHA224>,
                                    Meta::Case<uint8,HashID_SHA256,Crypton::PlatformSHA256>,
                                    Meta::Case<uint8,HashID_SHA384,Crypton::PlatformSHA384>,
                                    Meta::Case<uint8,HashID_SHA512,Crypton::PlatformSHA512> > ;

using KeyedHashCaseList = Meta::CaseList<Meta::Case<uint8,HashID_SHA1  ,Crypton::PlatformKeyedSHA1  >,
                                         Meta::Case<uint8,HashID_SHA224,Crypton::PlatformKeyedSHA224>,
                                         Meta::Case<uint8,HashID_SHA256,Crypton::PlatformKeyedSHA256>,
                                         Meta::Case<uint8,HashID_SHA384,Crypton::PlatformKeyedSHA384>,
                                         Meta::Case<uint8,HashID_SHA512,Crypton::PlatformKeyedSHA512> > ;

using DHGCaseList = Meta::CaseList<Meta::Case<uint8,DHGroupID_I ,Crypton::DHExp<Crypton::DHModI > >,
                                   Meta::Case<uint8,DHGroupID_II,Crypton::DHExp<Crypton::DHModII> > > ;

/* functions */

namespace Private_PSecKey {

struct IsValidCtx
 {
  using RetType = bool ;

  template <class T>
  static RetType call() { return true; }

  template <class T>
  static RetType defcall(T) { return false; }
 };

struct CreateCryptCtx
 {
  using RetType = AbstractCryptFunc * ;

  template <class T>
  static RetType call() { return new CryptFunc<T>(); }

  static RetType defcall(uint8 crypt_id)
   {
    Printf(Exception,"CCore::Net::PSec::Create(En/De)crypt(#;) : unknown crypt_id",crypt_id);

    return 0;
   }
 };

struct CreateHashCtx
 {
  using RetType = AbstractHashFunc * ;

  template <class T>
  static RetType call() { return new HashFunc<T>(); }

  static RetType defcall(uint8 hash_id)
   {
    Printf(Exception,"CCore::Net::PSec::CreateHash(#;) : unknown hash_id",hash_id);

    return 0;
   }
 };

struct CreateKeyedHashCtx
 {
  using RetType = AbstractHashFunc * ;

  PtrLen<const uint8> key;

  explicit CreateKeyedHashCtx(PtrLen<const uint8> key_) : key(key_) {}

  template <class T>
  RetType call() { return new HashFunc<T>(key); }

  static RetType defcall(uint8 hash_id)
   {
    Printf(Exception,"CCore::Net::PSec::CreateKeyedHash(#;) : unknown hash_id",hash_id);

    return 0;
   }
 };

struct CreateDHGroupCtx
 {
  using RetType = AbstractDHGroup * ;

  template <class T>
  static RetType call() { return new DHGroup<T>(); }

  static RetType defcall(uint8 dhg_id)
   {
    Printf(Exception,"CCore::Net::PSec::CreateDHGroup(#;) : unknown dhg_id",dhg_id);

    return 0;
   }
 };

struct GetBLenCtx
 {
  using RetType = ulen ;

  template <class T>
  static RetType call()
   {
    return T::BlockLen;
   }

  static RetType defcall(uint8 crypt_id)
   {
    Printf(Exception,"CCore::Net::PSec::GetBLen(#;) : unknown crypt_id",crypt_id);

    return 0;
   }
 };

struct GetKLenCtx
 {
  using RetType = ulen ;

  template <class T>
  static RetType call()
   {
    return T::KeyLen;
   }

  static RetType defcall(uint8 crypt_id)
   {
    Printf(Exception,"CCore::Net::PSec::GetKLen(#;) : unknown crypt_id",crypt_id);

    return 0;
   }
 };

struct GetHLenCtx
 {
  using RetType = ulen ;

  template <class T>
  static RetType call()
   {
    return T::DigestLen;
   }

  static RetType defcall(uint8 hash_id)
   {
    Printf(Exception,"CCore::Net::PSec::GetHLen(#;) : unknown hash_id",hash_id);

    return 0;
   }
 };

struct GetGLenCtx
 {
  using RetType = ulen ;

  template <class T>
  static RetType call()
   {
    return T::GLen;
   }

  static RetType defcall(uint8 dhg_id)
   {
    Printf(Exception,"CCore::Net::PSec::GetGLen(#;) : unknown dhg_id",dhg_id);

    return 0;
   }
 };

} // namespace Private_PSecKey

using namespace Private_PSecKey;

bool IsValid(CryptID crypt_id)
 {
  return Meta::TypeSwitch<EncryptCaseList>::Switch(crypt_id,IsValidCtx());
 }

bool IsValid(HashID hash_id)
 {
  return Meta::TypeSwitch<HashCaseList>::Switch(hash_id,IsValidCtx());
 }

bool IsValid(DHGroupID dhg_id)
 {
  return Meta::TypeSwitch<DHGCaseList>::Switch(dhg_id,IsValidCtx());
 }

AbstractCryptFunc * CreateEncrypt(CryptID crypt_id)
 {
  return Meta::TypeSwitch<EncryptCaseList>::Switch(crypt_id,CreateCryptCtx());
 }

AbstractCryptFunc * CreateDecrypt(CryptID crypt_id)
 {
  return Meta::TypeSwitch<DecryptCaseList>::Switch(crypt_id,CreateCryptCtx());
 }

AbstractHashFunc * CreateHash(HashID hash_id)
 {
  return Meta::TypeSwitch<HashCaseList>::Switch(hash_id,CreateHashCtx());
 }

AbstractHashFunc * CreateKeyedHash(HashID hash_id,PtrLen<const uint8> key)
 {
  return Meta::TypeSwitch<KeyedHashCaseList>::Switch(hash_id,CreateKeyedHashCtx(key));
 }

AbstractDHGroup * CreateDHGroup(DHGroupID dhg_id)
 {
  return Meta::TypeSwitch<DHGCaseList>::Switch(dhg_id,CreateDHGroupCtx());
 }

ulen GetBLen(CryptID crypt_id)
 {
  return Meta::TypeSwitch<EncryptCaseList>::Switch(crypt_id,GetBLenCtx());
 }

ulen GetKLen(CryptID crypt_id)
 {
  return Meta::TypeSwitch<EncryptCaseList>::Switch(crypt_id,GetKLenCtx());
 }

ulen GetHLen(HashID hash_id)
 {
  return Meta::TypeSwitch<HashCaseList>::Switch(hash_id,GetHLenCtx());
 }

ulen GetGLen(DHGroupID dhg_id)
 {
  return Meta::TypeSwitch<DHGCaseList>::Switch(dhg_id,GetGLenCtx());
 }

/* class SessionKey */

struct SessionKey::GetSecretLenCtx
 {
  using RetType = ulen ;

  ulen klen;
  ulen hlen;

  GetSecretLenCtx(ulen klen_,ulen hlen_) : klen(klen_),hlen(hlen_) {}

  template <class T>
  RetType call()
   {
    return KeyGen<T>::GetSecretLen(klen,hlen);
   }

  static RetType defcall(uint8 dhg_id)
   {
    Printf(Exception,"CCore::Net::PSec::SessionKey::GetSecretLen() : unknown dhg_id #;",dhg_id);

    return 0;
   }
 };

struct SessionKey::CreateKeyGenCtx
 {
  using RetType = AbstractKeyGen * ;

  const SessionKey *obj;
  OwnPtr<AbstractHashFunc> &&hash;

  CreateKeyGenCtx(const SessionKey *obj_,OwnPtr<AbstractHashFunc> &&hash_) : obj(obj_),hash(std::move(hash_)) {}

  template <class T>
  RetType call() { return obj->createKeyGen<T>(std::move(hash)); }

  static RetType defcall(uint8 dhg_id)
   {
    Printf(Exception,"CCore::Net::PSec::SessionKey::createKeyGen() : unknown dhg_id #;",dhg_id);

    return 0;
   }
 };

ulen SessionKey::GetSecretLen(CryptAlgoSelect algo_select,ulen klen)
 {
  ulen hlen=algo_select.getHLen();

  return Meta::TypeSwitch<DHGCaseList>::Switch(algo_select.dhg_id,GetSecretLenCtx(klen,hlen));
 }

SessionKey::SessionKey(CryptAlgoSelect algo_select_,SessionKeyParam param_)
 : algo_select(algo_select_),
   param(param_),
   klen(algo_select_.getKLen()),
   ktotal(LenOf(ulen(1)+param_.keyset_len,klen)),
   secret_len(GetSecretLen(algo_select_,klen)),
   key_buf(LenAdd(ktotal,secret_len,RandomWarpLen))
 {
  if( !Fit(MinKeySetLen,param.keyset_len,MaxKeySetLen) )
    {
     Printf(Exception,"CCore::Net::PSec::SessionKey::SessionKey(...,{keyset_len=#;}) : bad keyset length",param.keyset_len);
    }
 }

SessionKey::~SessionKey()
 {
  Crypton::Forget(algo_select);
  Crypton::Forget(param);

  Crypton::ForgetRange(Range(key_buf));
 }

AbstractCryptFunc * SessionKey::createEncrypt() const
 {
  return algo_select.createEncrypt();
 }

AbstractCryptFunc * SessionKey::createDecrypt() const
 {
  return algo_select.createDecrypt();
 }

AbstractHashFunc * SessionKey::createHash() const
 {
  return algo_select.createHash();
 }

AbstractKeyGen * SessionKey::createKeyGen() const
 {
  OwnPtr<AbstractHashFunc> hash(createHash());

  return Meta::TypeSwitch<DHGCaseList>::Switch(algo_select.dhg_id,CreateKeyGenCtx(this,std::move(hash)));
 }

AbstractRandomGen * SessionKey::createRandom() const
 {
  return new RandomGen<PlatformRandom>(Range(key_buf.getPtr()+ktotal+secret_len,RandomWarpLen));
 }

ulen SessionKey::getKLen() const
 {
  return klen;
 }

LifeLim SessionKey::getLifeLim() const
 {
  return LifeLim(param.ttl,param.utl);
 }

void SessionKey::getKey0(uint8 key[]) const
 {
  Range(key_buf.getPtr(),klen).copyTo(key);
 }

ulen SessionKey::getKeySetLen() const
 {
  return param.keyset_len;
 }

void SessionKey::getKey(ulen index,uint8 key[]) const
 {
  Range(key_buf.getPtr()+klen*(index+1),klen).copyTo(key);
 }

} // namespace PSec
} // namespace Net
} // namespace CCore

