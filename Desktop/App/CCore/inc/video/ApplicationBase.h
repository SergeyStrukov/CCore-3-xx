/* ApplicationBase.h */
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

#ifndef CCore_inc_video_ApplicationBase_h
#define CCore_inc_video_ApplicationBase_h

#include <CCore/inc/video/FrameWindow.h>

#include <CCore/inc/DeferCall.h>
#include <CCore/inc/video/Incremental.h>

namespace CCore {
namespace Video {

/* classes */

class ApplicationBase;

/* class ApplicationBase */

class ApplicationBase : public DeferCallQueue
 {
   IncrementalDriver driver;

  private:

   virtual void forward(TimeScope time_scope);

  protected:

   Desktop *const desktop;

  protected:

   // exception control

   virtual void clearException() noexcept =0;

   virtual void guardException()=0;

   virtual void showException() noexcept =0;

   // start

   virtual void prepare()=0;

   virtual void beforeLoop() noexcept =0;

   // finish

   virtual void afterLoop() noexcept =0;

   virtual void final()=0;

   // extra

   virtual void idle(TimeScope time_scope);

  public:

   explicit ApplicationBase(Desktop *desktop,MSec tick_period);

   ~ApplicationBase();

   int run();
 };

} // namespace Video
} // namespace CCore

#endif


