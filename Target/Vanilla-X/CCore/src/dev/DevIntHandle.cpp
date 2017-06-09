/* DevIntHandle.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/dev/DevIntHandle.h>

#include <CCore/inc/dev/DevInt.h>

#include <CCore/inc/task/TaskMonitor.h>
#include <CCore/inc/task/TaskEvent.h>

#include <__std_init.h>

namespace CCore {
namespace Dev {

/* GetPlanInitNode_...() */

namespace Private_DevIntHandle {

class IntTable : NoCopy
 {
   Function<void (void)> table[Int_TableLen];

  public:

   IntTable()
    {
    }

   ~IntTable()
    {
    }

   void set(uint32 int_source,Function<void (void)> handle_int)
    {
     // TODO

     table[int_source]=handle_int;
    }

   void clear(uint32 int_source)
    {
     table[int_source]=Nothing;
    }

   void enable(uint32 int_source)
    {
     Used(int_source);

     // TODO
    }

   void disable(uint32 int_source)
    {
     Used(int_source);

     // TODO
    }

   void dispatch(uint32 int_source)
    {
     table[int_source]();
    }
 };

class IntEngine : public IntTable
 {
  public:

   IntEngine();

   ~IntEngine();

   static const char * GetTag() { return "DevIntHandle"; }
 };

PlanInitObject<IntEngine> Object CCORE_INITPRI_1 ;

extern "C" {

void IRQ_main()
 {
  TaskEventHost.add<TaskSwitchEvent>(TaskNumber::EnterInt);

  TaskMonitor::Internal::BeginInt();

  // TODO

  uint32 int_source=0;

  Object->dispatch(int_source);

  TaskMonitor::Internal::EndInt();

  TaskEventHost.add<TaskSwitchEvent>(TaskNumber::LeaveInt);
 }

} // extern "C"

IntEngine::IntEngine()
 {
  // TODO

  __std_intsetup(IRQ_main);
 }

IntEngine::~IntEngine()
 {
  // TODO

  __std_intcleanup();
 }

} // namespace Private_DevIntHandle

using namespace Private_DevIntHandle;

PlanInitNode * GetPlanInitNode_DevIntHandle() { return &Object; }

/* functions */

void SetupIntHandler(IntSource int_source,Function<void (void)> handle_int)
 {
  IntLock lock;

  Object->set(int_source,handle_int);

  Object->enable(int_source);
 }

void CleanupIntHandler(IntSource int_source)
 {
  IntLock lock;

  Object->disable(int_source);

  Object->clear(int_source);
 }

void EnableInt(IntSource int_source)
 {
  IntLock lock;

  Object->enable(int_source);
 }

void DisableInt(IntSource int_source)
 {
  IntLock lock;

  Object->disable(int_source);
 }

} // namespace Dev
} // namespace CCore
