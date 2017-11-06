/* Incremental.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_video_Incremental_h
#define CCore_inc_video_Incremental_h

#include <CCore/inc/TimeScope.h>
#include <CCore/inc/List.h>
#include <CCore/inc/Signal.h>

namespace CCore {
namespace Video {

/* enum StepResult */

enum StepResult
 {
  StepContinue = 0,
  StepFinalOk,
  StepFinalError
 };

/* functions */

void GuardIncrementalInProgress();

/* classes */

struct IncrementalProgress;

/* struct IncrementalProgress */

struct IncrementalProgress
 {
  virtual void start()=0;

  virtual void setTotal(unsigned total)=0;

  virtual bool setPos(unsigned pos)=0; // false to cancel

  virtual void stop() noexcept =0;
 };

/* concept StepBuilderType<Step,T> */

template <class Step,class T>
concept bool StepBuilderType = requires(Step &obj,T &t,IncrementalProgress &progress)
 {
  Step();

  { obj.start(t) } -> StepResult ;

  { obj(progress,t) } -> StepResult ;

  { obj.erase() } noexcept;
 } ;

//----------------------------------------------------------------------------------------

/* classes */

class IncrementalNode;

class IncrementalDriver;

template <class T,StepBuilderType<T> Step> class IncrementalBuilder;

/* class IncrementalNode */

class IncrementalNode : NoCopy
 {
   DLink<IncrementalNode> link;
   bool active = false ;

   friend class IncrementalDriver;

  public:

   IncrementalNode();

   ~IncrementalNode();

   void activate();

   void deactivate() noexcept ; // must be called in a destructor of a derived class

   virtual void step(TimeScope time_scope)=0;

   virtual void cancel() noexcept =0;
 };

/* class IncrementalDriver */

class IncrementalDriver : NoCopy
 {
   using Algo = DLink<IncrementalNode>::CircularAlgo<&IncrementalNode::link> ;

   Algo::Top list;

  private:

   void ins(IncrementalNode *node);

   void del(IncrementalNode *node);

   friend class IncrementalNode;

   // per-thread driver

   static IncrementalDriver * Get();

  public:

   IncrementalDriver();

   ~IncrementalDriver();

   void step(TimeScope time_scope);
 };

/* class IncrementalBuilder<T> */

#if 0

class Step
 {
  public:

   Step();

   ~Step();

   StepResult start(T &obj);

   StepResult operator () (IncrementalProgress &progress,T &obj);

   void erase() noexcept;
 };

#endif

template <class T,StepBuilderType<T> Step>
class IncrementalBuilder : IncrementalNode
 {
   IncrementalProgress &progress;

   T *obj = 0 ;

   Step builder;

  public:

   explicit IncrementalBuilder(IncrementalProgress &progress);

   ~IncrementalBuilder();

   template <class ... SS>
   void start(T &obj,SS && ... ss);

   virtual void step(TimeScope time_scope);

   virtual void cancel() noexcept;

   // signals

   Signal<bool> completed; // ok
 };

template <class T,StepBuilderType<T> Step>
IncrementalBuilder<T,Step>::IncrementalBuilder(IncrementalProgress &progress_)
 : progress(progress_)
 {
 }

template <class T,StepBuilderType<T> Step>
IncrementalBuilder<T,Step>::~IncrementalBuilder()
 {
  cancel();
 }

template <class T,StepBuilderType<T> Step>
template <class ... SS>
void IncrementalBuilder<T,Step>::start(T &obj_,SS && ... ss)
 {
  if( obj )
    {
     completed.assert(false);

     GuardIncrementalInProgress();
    }

  StepResult result;

  try
    {
     result=builder.start(obj_, std::forward<SS>(ss)... );
    }
  catch(...)
    {
     builder.erase();

     completed.assert(false);

     throw;
    }

  if( result )
    {
     builder.erase();

     completed.assert(result==StepFinalOk);

     return;
    }

  try
    {
     activate();

     progress.start();
    }
  catch(...)
    {
     builder.erase();

     completed.assert(false);

     throw;
    }

  obj=&obj_;
 }

template <class T,StepBuilderType<T> Step>
void IncrementalBuilder<T,Step>::step(TimeScope time_scope)
 {
  if( !obj ) return;

  StepResult result;

  try
    {
     do
       {
        result=builder(progress,*obj);

        if( result ) break;
       }
     while( +time_scope.get() );
    }
  catch(...)
    {
     obj=0;

     builder.erase();

     progress.stop();

     deactivate();

     completed.assert(false);

     throw;
    }

  if( result )
    {
     obj=0;

     builder.erase();

     progress.stop();

     deactivate();

     completed.assert(result==StepFinalOk);
    }
 }

template <class T,StepBuilderType<T> Step>
void IncrementalBuilder<T,Step>::cancel() noexcept
 {
  if( !obj )
    {
     deactivate();

     return;
    }

  obj=0;

  builder.erase();

  progress.stop();

  deactivate();

  completed.assert(false);
 }

} // namespace Video
} // namespace CCore

#endif

