/* Incremental.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/Incremental.h>

#include <CCore/inc/TlsSlot.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* functions */

void GuardIncrementalInProgress()
 {
  Printf(Exception,"CCore::Video::IncrementalBuilder<...>::start(...) : in progress");
 }

/* class IncrementalNode */

IncrementalNode::IncrementalNode()
 {
 }

IncrementalNode::~IncrementalNode()
 {
 }

void IncrementalNode::activate()
 {
  if( !active )
    {
     if( IncrementalDriver *driver=IncrementalDriver::Get() )
       {
        driver->ins(this);

        active=true;
       }
     else
       {
        Printf(Exception,"CCore::Video::IncrementalNode::activate() : no driver");
       }
    }
 }

void IncrementalNode::deactivate() noexcept
 {
  if( active )
    {
     if( IncrementalDriver *driver=IncrementalDriver::Get() ) driver->del(this);

     active=false;
    }
 }

/* per-thread IncrementalDriver */

namespace Private_Incremental {

struct Slot : TlsSlot
 {
  Slot() : TlsSlot("IncrementalDriver") {}
 };

Slot Object CCORE_INITPRI_1 ;

} // namespace Private_Incremental

using namespace Private_Incremental;

IncrementalDriver * IncrementalDriver::Get()
 {
  return static_cast<IncrementalDriver *>(Object.get());
 }

/* class IncrementalDriver */

void IncrementalDriver::ins(IncrementalNode *node)
 {
  list.ins_last(node);
 }

void IncrementalDriver::del(IncrementalNode *node)
 {
  list.del(node);
 }

IncrementalDriver::IncrementalDriver()
 {
  if( Object.get() )
    {
     Printf(Exception,"CCore::Video::IncrementalDriver::IncrementalDriver() : another driver is active");
    }

  Object.set(this);
 }

IncrementalDriver::~IncrementalDriver()
 {
  if( Object.get()==this )
    {
     Object.set(0);

     while( IncrementalNode *node=list.del_first() ) node->cancel();
    }
 }

void IncrementalDriver::step(TimeScope time_scope)
 {
  if( !list ) return;

  do
    {
     IncrementalNode *node=list.rotate_forward();

     if( !node ) return;

     node->step(time_scope);
    }
  while( +time_scope.get() );
 }

} // namespace Video
} // namespace CCore

