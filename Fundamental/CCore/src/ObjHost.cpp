/* ObjHost.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/inc/ObjHost.h>

#include <CCore/inc/TypeNumber.h>

#include <CCore/inc/Abort.h>
#include <CCore/inc/Exception.h>

namespace CCore {

/* GetPlanInitNode_...() */

namespace Private_ObjHost {

struct DefaultHost : ObjHost
 {
  DefaultHost() : ObjHost("!DefaultObjHost") {}

  static const char * GetTag() { return "ObjHost"; }
 };

PlanInitObject<DefaultHost,PlanInitReq<GetPlanInitNode_TypeNumber> > Object CCORE_INITPRI_1 ;

} // namespace Private_ObjHost

using namespace Private_ObjHost;

PlanInitNode * GetPlanInitNode_ObjHost() { return &Object; }

/* class ObjHost */

ObjBase * ObjHost::lock(StrLen name,bool do_throw)
 {
  StrKey key(name);
  ObjBase *ret;

  {
   Mutex::Lock lock(mutex);

   ret=root.find(key);

   if( ret ) ret->asem.inc();
  }

  if( !ret && do_throw )
    {
     Printf(Exception,"CCore::ObjHost::lock(#.q;) : object is not found",name);
    }

  return ret;
 }

StrLen ObjHost::Dup(StrLen name)
 {
  char *str=static_cast<char *>(MemAlloc(name.len));

  name.copyTo(str);

  return StrLen(str,name.len);
 }

void ObjHost::Free(StrLen name)
 {
  MemFree(const_cast<char *>(name.ptr));
 }

class ObjHost::SetHosted : NoCopy
 {
   ObjBase *obj;
   StrLen name;

  private:

   void release()
    {
     obj->hosted--;

     Free(name);
    }

  public:

   SetHosted(ObjBase &obj_,StrLen name_)
    : obj(&obj_)
    {
     name=Dup(name_);

     if( obj->hosted++ )
       {
        release();

        Printf(Exception,"CCore::ObjHost::add(...) : object is already hosted");
       }
    }

   StrLen getName() const { return name; }

   ~SetHosted()
    {
     if( obj ) release();
    }

   void disarm() { obj=0; }
 };

ObjHost::ObjHost(TextLabel name)
 : mutex(name)
 {
 }

ObjHost::~ObjHost()
 {
  Mutex::Lock lock(mutex);

  if( +root ) Abort("Fatal error : CCore::ObjHost is used on exit");
 }

void ObjHost::add(ObjBase &obj,StrLen name)
 {
  SetHosted setter(obj,name);
  StrKey key(setter.getName());

  {
   Mutex::Lock lock(mutex);

   Algo::PrepareIns prepare(root,key);

   if( prepare.found )
     {
      Printf(Exception,"CCore::ObjHost::add(...,#.q;) : name is used",name);
     }

   prepare.complete(&obj);

   obj.asem.inc();
  }

  setter.disarm();
 }

void ObjHost::del(ObjBase &obj)
 {
  {
   Mutex::Lock lock(mutex);

   root.del(&obj);
  }

  Free(Replace_null(Algo::Link(&obj).key.str));

  obj.hosted--;
  obj.asem.dec();
 }

ObjHost & ObjHost::Default() { return *Object; }

/* class ObjHook */

void ObjHook::GuardObjCastFailed()
 {
  Printf(Exception,"CCore::ObjHook::cast_guarded() : object has not an expected type");
 }

} // namespace CCore


