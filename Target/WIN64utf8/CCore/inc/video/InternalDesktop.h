/* InternalDesktop.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_InternalDesktop_h
#define CCore_inc_video_InternalDesktop_h

#include <CCore/inc/video/InternalHost.h>

namespace CCore {
namespace Video {
namespace Internal {

/* classes */

class WindowsDesktop;

/* class WindowsDesktop */

class WindowsDesktop : public Desktop
 {
   Win64::handle_t h_event;

  private:

   static bool TestMsg();

  public:

   WindowsDesktop();

   ~WindowsDesktop();

   // Desktop

   virtual WindowHost * createHost();

   virtual Point getScreenSize();

   virtual Pane getMaxPane();

   virtual bool pump(unsigned lim);

   virtual void wait(TimeScope time_scope);

   virtual void interrupt();
 };

} // namespace Internal
} // namespace Video
} // namespace CCore

#endif

