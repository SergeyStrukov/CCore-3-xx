/* ObjHost.h */
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

#ifndef CCore_inc_ObjHost_h
#define CCore_inc_ObjHost_h

#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/StrKey.h>
#include <CCore/inc/PlanInit.h>
#include <CCore/inc/Printf.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/InterfaceHost.h>

namespace CCore {

/* GetPlanInitNode_...() */

PlanInitNode * GetPlanInitNode_ObjHost();

/* classes */

class ObjBase;

class ObjHost;

struct ObjInfo;

template <UnidType T> struct ObjInfo_if;

struct ObjInfo_obj;

template <UnidType T> struct ObjInfo_obj_if;

class ObjHook;

class ObjMaster;

class ObjMaster_delete;

/* concept ObjInfoType<Info> */

template <class Info,bool Lock>
concept bool ObjInfoType3 = !Lock || requires(Info info)
 {
  { info.getObj() } -> ObjBase * ;
 } ;

template <class Info,class Extra>
concept bool ObjInfoType2 = requires(ObjBase *obj,StrLen name,Extra ext)
 {
  Extra(obj);

  { !ext } -> bool ;

  Info(obj,name,ext);
 } ;

template <class Info>
concept bool ObjInfoType = requires()
 {
  typename Info::Extra;

  { Info::Lock } -> bool ;

  requires ( ObjInfoType2<Info,typename Info::Extra> );

  requires ( ObjInfoType3<Info,Info::Lock> );
 } ;

/* class ObjBase */

class ObjBase : public NoCopyBase<MemBase,InterfaceHost>
 {
   AntiSem asem;
   RBTreeUpLink<ObjBase,StrKey> link;
   Atomic hosted;

  private:

   friend class ObjHost;
   friend class ObjHook;

  public:

   ObjBase() : ObjBase("ObjBase") {}

   explicit ObjBase(TextLabel name) : asem(name) {}

   virtual ~ObjBase() {}

   void wait_released() { asem.wait(); }

   bool wait_released(MSec timeout) { return asem.wait(timeout); }

   bool wait_released(TimeScope time_scope) { return asem.wait(time_scope); }
 };

/* class ObjHost */

class ObjHost : NoCopy
 {
   Mutex mutex;

   using Algo = RBTreeUpLink<ObjBase,StrKey>::Algo<&ObjBase::link> ;

   Algo::Root root;

  private:

   ObjBase * lock(StrLen name,bool do_throw=true);

   ObjBase * try_lock(StrLen name) { return lock(name,false); }

   friend class ObjHook;

   auto apply(FuncInitArgType<ObjBase &> func_init) // locked operation
    {
     Mutex::Lock lock(mutex);

     return Algon::ApplyToRange(root.start(),func_init);
    }

   template <bool Lock> struct ListLock;

   static StrLen Dup(StrLen name);

   static void Free(StrLen name);

   class SetHosted;

  public:

   explicit ObjHost(TextLabel name);

   ~ObjHost();

   void add(ObjBase &obj,StrLen name);

   void del(ObjBase &obj);

   static ObjHost & Default();

   template <ObjInfoType Info> class List;
 };

template <>
struct ObjHost::ListLock<true>
 {
  static void Lock(ObjBase *obj) { obj->asem.inc(); }

  template <ObjInfoType Info>
  static void Unlock(PtrLen<Info> r)
   {
    for(Info &obj : r ) obj.getObj()->asem.dec();
   }
 };

template <>
struct ObjHost::ListLock<false>
 {
  static void Lock(ObjBase *) {}

  template <ObjInfoType Info>
  static void Unlock(PtrLen<Info>) {}
 };

/* class ObjHost::List<Info> */

template <ObjInfoType Info>
class ObjHost::List : NoCopy
 {
   ElementPool pool;
   DynArray<Info> infos;

  private:

   void add(ObjBase *obj)
    {
     typename Info::Extra extra(obj);

     if( !extra ) return;

     StrLen name=Algo::Link(obj).key.str;

     infos.append_fill(obj,pool.dup(name),extra);

     ListLock<Info::Lock>::Lock(obj);
    }

  public:

   List() : pool(4_KByte) {}

   ~List()
    {
     ListLock<Info::Lock>::Unlock(Range(infos));
    }

   void build(ObjHost &host=Default())
    {
     host.apply( [this] (ObjBase &obj) { add(&obj); } );
    }

   const Info * getPtr() const { return infos.getPtr(); }

   const Info * getPtr_const() const { return infos.getPtr_const(); }

   ulen getLen() const { return infos.getLen(); }
 };

/* struct ObjInfo */

struct ObjInfo
 {
  enum LockFlagType { Lock = false };

  using Extra = ObjBase * ;

  // data

  StrLen name;

  // constructors

  ObjInfo(ObjBase *,StrLen name_,Extra) : name(name_) {}

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"#;",name);
   }
 };

/* struct ObjInfo_if<T> */

template <UnidType T>
struct ObjInfo_if
 {
  enum LockFlagType { Lock = false };

  struct Extra
   {
    T *ptr;

    explicit Extra(ObjBase *obj) : ptr(obj->pickInterface<T>()) {}

    bool operator ! () const { return !ptr; }
   };

  // data

  StrLen name;

  // constructors

  ObjInfo_if(ObjBase *,StrLen name_,Extra) : name(name_) {}

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"#;",name);
   }
 };

/* struct ObjInfo_obj */

struct ObjInfo_obj
 {
  enum LockFlagType { Lock = true };

  using Extra = ObjBase * ;

  // data

  StrLen name;
  ObjBase *obj;

  // constructors

  ObjInfo_obj(ObjBase *obj_,StrLen name_,Extra) : name(name_),obj(obj_) {}

  // methods

  ObjBase * getObj() const { return obj; }

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"#;",name);
   }
 };

/* struct ObjInfo_obj_if<T> */

template <UnidType T>
struct ObjInfo_obj_if
 {
  enum LockFlagType { Lock = true };

  struct Extra
   {
    ObjBase *obj;
    T *ptr;

    explicit Extra(ObjBase *obj_) : obj(obj_),ptr(obj_->pickInterface<T>()) {}

    bool operator ! () const { return !ptr; }
   };

  // data

  StrLen name;
  Extra extra;

  // constructors

  ObjInfo_obj_if(ObjBase *,StrLen name_,Extra extra_) : name(name_),extra(extra_) {}

  // methods

  ObjBase * getObj() const { return extra.obj; }

  T * getPtr() const { return extra.ptr; }

  // print object

  void print(PrinterType &out) const
   {
    Printf(out,"#;",name);
   }
 };

/* class ObjHook */

class ObjHook : NoCopy
 {
   ObjBase *obj;

  private:

   void lock(StrLen name,ObjHost &host=ObjHost::Default()) { obj=host.lock(name); }

   void try_lock(StrLen name,ObjHost &host=ObjHost::Default()) { obj=host.try_lock(name); }

   static void GuardObjCastFailed();

  public:

   //
   // assign/move/swap are not provided to prevent cyclic dependencies
   //

   // constructors

   ObjHook(ObjHost &host,StrLen name) { lock(name,host); }

   explicit ObjHook(StrLen name) { lock(name); }

   ObjHook(JustTryType,ObjHost &host,StrLen name) { try_lock(name,host); }

   ObjHook(JustTryType,StrLen name) { try_lock(name); }

   ~ObjHook() { if( obj ) obj->asem.dec(); }

   // cast

   bool operator + () const { return obj; }

   bool operator ! () const { return !obj; }

   void requestInterface(InterfaceCaster &caster) { if( obj ) obj->requestInterface(caster); }

   template <UnidType T>
   T * cast() const { return obj?obj->pickInterface<T>():0; }

   template <UnidType T>
   T * cast_guarded() const
    {
     T *ret=cast<T>();

     if( !ret ) GuardObjCastFailed();

     return ret;
    }

   template <UnidType T>
   operator T * () const { return cast_guarded<T>(); }

   // copy objects

   ObjHook(const ObjHook &hook)
    : NoCopy() // warning supression
    {
     obj=hook.obj;

     if( obj ) obj->asem.inc();
    }
 };

/* class ObjMaster */

class ObjMaster : NoCopy
 {
   ObjHost &host;
   ObjBase &obj;

  public:

   ObjMaster(ObjHost &host_,ObjBase &obj_,StrLen name)
    : host(host_),
      obj(obj_)
    {
     host.add(obj,name);
    }

   ObjMaster(ObjBase &obj_,StrLen name) : ObjMaster(ObjHost::Default(),obj_,name) {}

   ~ObjMaster()
    {
     host.del(obj);

     obj.wait_released();
    }
 };

/* class ObjMaster_delete */

class ObjMaster_delete : NoCopy
 {
   ObjHost &host;
   OwnPtr<ObjBase> obj;

  public:

   ObjMaster_delete(ObjHost &host_,ObjBase *obj_,StrLen name)
    : host(host_),
      obj(obj_)
    {
     host.add(*obj_,name);
    }

   ObjMaster_delete(ObjBase *obj_,StrLen name) : ObjMaster_delete(ObjHost::Default(),obj_,name) {}

   ~ObjMaster_delete()
    {
     host.del(*obj);

     obj->wait_released();
    }
 };

} // namespace CCore

#endif


