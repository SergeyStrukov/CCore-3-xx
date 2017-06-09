/* PerTask.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/PerTask.h>

#include <CCore/inc/sys/SysTlsSlot.h>
#include <CCore/inc/sys/SysPlanInit.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

namespace CCore {

/* functions */

void GuardTaskObjectNoBuilder()
 {
  Printf(Exception,"CCore::GetTaskObject<...>() : no object builder");
 }

/* class PerTask::List */

class PerTask::List : NoCopy
 {
   Mutex mutex;

   DynArray<BuilderSlot> bslots;

  private:

   BuilderSlot & take(ulen slot_id)
    {
     ulen len=bslots.getLen();

     if( slot_id>=len )
       {
        bslots.extend_default(LenAdd(slot_id-len,1));
       }

     return bslots[slot_id];
    }

  public:

   List() : mutex("!PerTask"),bslots(100) {}

   ~List() {}

   void setBuilder(ulen slot_id,const BuilderSlot &bslot)
    {
     Mutex::Lock lock(mutex);

     BuilderSlot &slot=take(slot_id);

     if( slot.isTaken() )
       {
        Printf(Exception,"CCore::TaskObjectBuild<...>::TaskObjectBuild(...) : object builder is already assigned");
       }

     slot=bslot;
    }

   void clearBuilder(ulen slot_id)
    {
     Mutex::Lock lock(mutex);

     take(slot_id).clear();
    }

   void * create(ulen slot_id)
    {
     Mutex::Lock lock(mutex);

     return take(slot_id).create();
    }

   void * try_create(ulen slot_id) noexcept
    {
     Mutex::Lock lock(mutex);

     return take(slot_id).try_create();
    }

   void destroy(ulen slot_id,void *obj) noexcept
    {
     Mutex::Lock lock(mutex);

     take(slot_id).destroy(obj);
    }
 };

/* GetPlanInitNode_...() */

namespace Private_PerTask {

class PerTaskHost : public PerTask::List , public UnidRegister
 {
   Sys::TlsSlot slot;

  public:

   PerTaskHost()
    {
     if( slot.init() ) Abort("Fatal error : TLS is full");
    }

   ~PerTaskHost()
    {
     slot.exit();
    }

   void set(PerTask *obj) { slot.set(obj); }

   PerTask * get() { return static_cast<PerTask *>(slot.get()); }

   static const char * GetTag() { return "PerTask"; }
 };

PlanInitObject<PerTaskHost,PlanInitReq<Sys::GetPlanInitNode_Sys>
                          ,PlanInitReq<GetPlanInitNode_MemBase>
                          > Object CCORE_INITPRI_1 ;

} // namespace Private_PerTask

using namespace Private_PerTask;

PlanInitNode * GetPlanInitNode_PerTask() { return &Object; }

/* class PerTask */

UnidRegister & PerTask::GetRegister()
 {
  return *Object;
 }

PerTask::PerTask()
 : slots(100)
 {
 }

PerTask::~PerTask()
 {
  for(ulen slot_id=0,len=slots.getLen(); slot_id<len ;slot_id++)
    {
     if( void *obj=slots[slot_id].obj ) Destroy(slot_id,obj);
    }
 }

auto PerTask::take(ulen slot_id) -> Slot &
 {
  ulen len=slots.getLen();

  if( slot_id>=len )
    {
     slots.extend_default(LenAdd(slot_id-len,1));
    }

  return slots[slot_id];
 }

void PerTask::SetBuilder(ulen slot_id,const BuilderSlot &bslot)
 {
  Object->setBuilder(slot_id,bslot);
 }

void PerTask::ClearBuilder(ulen slot_id)
 {
  Object->clearBuilder(slot_id);
 }

void * PerTask::Create(ulen slot_id)
 {
  return Object->create(slot_id);
 }

void * PerTask::TryCreate(ulen slot_id) noexcept
 {
  return Object->try_create(slot_id);
 }

void PerTask::Destroy(ulen slot_id,void *obj) noexcept
 {
  Object->destroy(slot_id,obj);
 }

PerTask * PerTask::Get()
 {
  if( PerTask *obj=Object->get() ) return obj;

  PerTask *ret=new PerTask();

  Object->set(ret);

  return ret;
 }

PerTask * PerTask::TryGet() noexcept
 {
  try
    {
     return Get();
    }
  catch(...)
    {
     return 0;
    }
 }

PerTask * PerTask::Peak() noexcept
 {
  return Object->get();
 }

/* class DestroyPerTask */

static DestroyPerTask ForMainTask CCORE_INITPRI_3 ;

DestroyPerTask::~DestroyPerTask()
 {
  if( PerTask *obj=Object->get() )
    {
     delete obj;

     Object->set(0);
    }
 }

} // namespace CCore


