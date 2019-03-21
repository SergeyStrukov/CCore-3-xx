/* Activator.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_Activator_h
#define CCore_inc_video_Activator_h

#include <CCore/inc/Task.h>

namespace CCore {
namespace Video {

/* classes */

class StopFlag;

class Activator;

/* class StopFlag */

class StopFlag : NoCopy
 {
   Atomic flag;

   friend class Activator;

  private:

   void set() { flag=true; }

   void clear() { flag=false; }

  public:

   StopFlag() {}

   operator bool() const { return flag; }
 };

/* class Activator */

class Activator : NoCopy
 {
   bool running = false ;

   StopFlag stop_flag;

   Atomic stopping;

   Sem stop_sem;

  private:

   void exit();

   template <class Work>
   class WorkTask : public Task
    {
      Activator *obj;
      Work work;

     private:

      virtual void entry()
       {
        work();
       }

      virtual void exit()
       {
        Activator *temp=obj;

        delete this;

        temp->exit();
       }

     public:

      template <class ... SS>
      explicit WorkTask(Activator *obj_,SS && ... ss) : obj(obj_),work(obj_->stop_flag, std::forward<SS>(ss)... ) {}

      virtual ~WorkTask() {}
    };

  public:

   Activator();

   ~Activator();

   // status

   bool isRunning() const { return running; }

   // start

   template <class Work,class ... SS>
   bool start(SS && ... ss)
    {
     if( running ) return false;

     auto *ptr=new WorkTask<Work>(this, std::forward<SS>(ss)... );

     stop_flag.clear();
     stopping=false;
     running=true;

     return ptr->run_or_exit();
    }

   // stop_flag

   void setStop() { stop_flag.set(); }

   // stop

   void stop(); // blocking, call in a destructor!

   bool waitStop(MSec timeout);
 };

} // namespace Video
} // namespace CCore

#endif

