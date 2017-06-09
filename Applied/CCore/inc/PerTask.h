/* PerTask.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_PerTask_h
#define CCore_inc_PerTask_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/Task.h>
#include <CCore/inc/MemBase.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Unid.h>

namespace CCore {

/* concept TOCType<TOC> */

template <class ObjectType,class BuilderType>
concept bool TOCType2 = requires(ObjectType &obj,BuilderType &builder)
 {
  { builder.create() } -> ObjectType * ;
 } ;

template <class TOC>
concept bool TOCType = UnidType<TOC> && requires()
 {
  typename TOC::ObjectType;
  typename TOC::BuilderType;

  requires ( TOCType2<typename TOC::ObjectType,typename TOC::BuilderType> );
 } ;

/* concept FullTOCType<TOC> */

template <class ObjectType>
concept bool FullTOCType2 = requires(ObjectType &obj)
 {
  obj.destroy();
 } ;

template <class TOC>
concept bool FullTOCType = TOCType<TOC> && requires()
 {
  requires ( FullTOCType2<typename TOC::ObjectType> );
 } ;

/* GetPlanInitNode_...() */

PlanInitNode * GetPlanInitNode_PerTask();

/* functions */

void GuardTaskObjectNoBuilder();

/* classes */

class PerTask;

class DestroyPerTask;

template <TOCType TOC> class PerTaskObjectScope;

template <TOCType TOC> class TaskObjectBuild;

/* class PerTask */

 //
 // struct TaskObjectControl
 //  {
 //   static const Unid TypeUnid;
 //
 //   class ObjectType
 //    {
 //     public:
 //
 //      void destroy();
 //    };
 //
 //   class BuilderType
 //    {
 //     public:
 //
 //      ObjectType * create();
 //    };
 //  };
 //

class PerTask : public MemBase_nocopy
 {
   struct Slot
    {
     void *obj = 0 ;

     Slot() noexcept {}

     void * getObj(ulen slot_id)
      {
       if( obj ) return obj;

       return obj=Create(slot_id);
      }

     void * tryGetObj(ulen slot_id) noexcept
      {
       if( obj ) return obj;

       return obj=TryCreate(slot_id);
      }

     void destroy(ulen slot_id)
      {
       if( obj ) Destroy(slot_id,Replace_null(obj));
      }
    };

   DynArray<Slot> slots;

  private:

   static UnidRegister & GetRegister();

   template <TOCType TOC>
   struct TaskObjectSlotId
    {
     class SlotId : NoCopy
      {
        ulen id;

       public:

        SlotId() : id(GetRegister().template getTypeId<TOC>()) {}

        operator ulen() const { return id; }
      };

     static SlotId Id;
    };

  private:

   PerTask();

   ~PerTask();

   Slot & take(ulen slot_id);

   friend class DestroyPerTask;

   class BuilderSlot
    {
      void *builder;
      void * (*create_func)(void *builder);
      void (*destroy_func)(void *obj);

     private:

      template <TOCType TOC>
      static void * CreateFunc(void *builder_)
       {
        typename TOC::BuilderType *builder=static_cast<typename TOC::BuilderType *>(builder_);

        typename TOC::ObjectType *obj=builder->create();

        return obj;
       }

      template <FullTOCType TOC>
      static void DestroyFunc(void *obj)
       {
        static_cast<typename TOC::ObjectType *>(obj)->destroy();
       }

     public:

      BuilderSlot() noexcept : builder(0),create_func(0),destroy_func(0) {}

      bool isTaken() const { return builder!=0; }

      template <FullTOCType TOC>
      void init(typename TOC::BuilderType *builder_)
       {
        builder=builder_;
        create_func=CreateFunc<TOC>;
        destroy_func=DestroyFunc<TOC>;
       }

      void clear() { builder=0; }

      void * create() const
       {
        if( !builder ) GuardTaskObjectNoBuilder();

        return create_func(builder);
       }

      void * try_create() const noexcept
       {
        if( !builder ) return 0;

        try
          {
           return create_func(builder);
          }
        catch(...)
          {
           return 0;
          }
       }

      void destroy(void *obj) const noexcept
       {
        destroy_func(obj);
       }
    };

   static void SetBuilder(ulen slot_id,const BuilderSlot &bslot);

   static void ClearBuilder(ulen slot_id);

   static void * Create(ulen slot_id);

   static void * TryCreate(ulen slot_id) noexcept;

   static void Destroy(ulen slot_id,void *obj) noexcept;

  public:

   class List;

   static PerTask * Get();

   static PerTask * TryGet() noexcept;

   static PerTask * Peak() noexcept;

   template <TOCType TOC>
   typename TOC::ObjectType * getTaskObject()
    {
     ulen slot_id=TaskObjectSlotId<TOC>::Id;

     return static_cast<typename TOC::ObjectType *>(take(slot_id).getObj(slot_id));
    }

   template <TOCType TOC>
   typename TOC::ObjectType * tryGetTaskObject() noexcept
    {
     ulen slot_id=TaskObjectSlotId<TOC>::Id;

     return static_cast<typename TOC::ObjectType *>(take(slot_id).tryGetObj(slot_id));
    }

   template <TOCType TOC>
   void destroyTaskObject()
    {
     ulen slot_id=TaskObjectSlotId<TOC>::Id;

     take(slot_id).destroy(slot_id);
    }

   template <FullTOCType TOC>
   static void SetBuilder(typename TOC::BuilderType *builder)
    {
     BuilderSlot bslot;

     bslot.init<TOC>(builder);

     SetBuilder(TaskObjectSlotId<TOC>::Id,bslot);
    }

   template <TOCType TOC>
   static void ClearBuilder()
    {
     ClearBuilder(TaskObjectSlotId<TOC>::Id);
    }
 };

template <TOCType TOC>
typename PerTask::TaskObjectSlotId<TOC>::SlotId PerTask::TaskObjectSlotId<TOC>::Id CCORE_INITPRI_3 ;

/* class DestroyPerTask */

class DestroyPerTask : NoCopy
 {
  public:

   ~DestroyPerTask();
 };

/* GetTaskObject<TOC>() */

template <TOCType TOC>
typename TOC::ObjectType * GetTaskObject()
 {
  return PerTask::Get()->getTaskObject<TOC>();
 }

template <TOCType TOC>
typename TOC::ObjectType * TryGetTaskObject() noexcept
 {
  if( PerTask *obj=PerTask::TryGet() ) return obj->tryGetTaskObject<TOC>();

  return 0;
 }

/* class PerTaskObjectScope<TOC> */

template <TOCType TOC>
class PerTaskObjectScope : NoCopy
 {
   void destroy()
    {
     if( PerTask *obj=PerTask::Peak() ) obj->destroyTaskObject<TOC>();
    }

  public:

   explicit PerTaskObjectScope(bool clean=true)
    {
     if( clean ) destroy();
    }

   ~PerTaskObjectScope()
    {
     destroy();
    }
 };

/* class TaskObjectBuild<TOC> */

template <TOCType TOC>
class TaskObjectBuild : NoCopy
 {
   using BuilderType = typename TOC::BuilderType ;

   BuilderType builder;

  public:

   template <class ... SS>
   explicit TaskObjectBuild(SS && ... ss)
    : builder( std::forward<SS>(ss)... )
    {
     PerTask::SetBuilder<TOC>(&builder);
    }

   ~TaskObjectBuild()
    {
     PerTask::ClearBuilder<TOC>();
    }
 };

} // namespace CCore

#endif


