/* Unid.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_Unid_h
#define CCore_inc_Unid_h

#include <CCore/inc/Cmp.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/CompactMap.h>

namespace CCore {

/* classes */

struct Unid;

/* struct Unid */

struct Unid
 {
  uint32 id[8];

  friend bool operator < (const Unid &a,const Unid &b) { return a.objCmp(b)<0; }

  friend bool operator > (const Unid &a,const Unid &b) { return a.objCmp(b)>0; }

  friend bool operator <= (const Unid &a,const Unid &b) { return a.objCmp(b)<=0; }

  friend bool operator >= (const Unid &a,const Unid &b) { return a.objCmp(b)>=0; }

  friend bool operator == (const Unid &a,const Unid &b) { return a.objCmp(b)==0; }

  friend bool operator != (const Unid &a,const Unid &b) { return a.objCmp(b)!=0; }

  CmpResult objCmp(const Unid &obj) const
   {
    return AlphaCmp(id[0],obj.id[0],id[1],obj.id[1],id[2],obj.id[2],id[3],obj.id[3],
                    id[4],obj.id[4],id[5],obj.id[5],id[6],obj.id[6],id[7],obj.id[7]);
   }
 };

/* concept UnidType<T> */

template <class T>
concept bool UnidType = requires()
 {
  { T::TypeUnid } -> const Unid & ;
 } ;

/* classes */

template <UnidType T> struct UnidOf;

class UnidRegister;

/* struct UnidOf<T> */

template <UnidType T>
struct UnidOf
 {
  static const Unid & Get() { return T::TypeUnid; }
 };

/* class UnidRegister */

class UnidRegister : NoCopy
 {
   Mutex mutex;

   CompactRBTreeMap<Unid,ulen,const Unid &> map;

   ulen next = 0 ;

  private:

   ulen find_or_add(const Unid &unid) noexcept;

  public:

   UnidRegister();

   ~UnidRegister();

   template <UnidType T>
   ulen getTypeId() { return find_or_add(UnidOf<T>::Get()); }
 };

} // namespace CCore

#endif


