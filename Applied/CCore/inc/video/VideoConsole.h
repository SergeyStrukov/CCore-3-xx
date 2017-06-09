/* VideoConsole.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_VideoConsole_h
#define CCore_inc_video_VideoConsole_h

#include <CCore/inc/ObjHost.h>
#include <CCore/inc/SingleHost.h>
#include <CCore/inc/Task.h>

#include <CCore/inc/video/SimpleConsole.h>
#include <CCore/inc/video/VideoDevice.h>

namespace CCore {
namespace Video {

/* classes */

class VideoConsole;

/* class VideoConsole */

class VideoConsole : NoCopyBase<VideoDevice::Control>
 {
   ObjHook hook;

   VideoDevice *dev;

   bool first = true ;

   Mutex mutex;

   MultiMode<SimpleConsole> con;

   Sem sem;

  private:

   struct InitFunc;

   struct PrintFunc;

   struct ToggleMarkerFunc;

   ColorMode setDevice();

   bool open();

   void close();

   void do_print(StrLen str);

   void do_tick();

  private:

   // VideoDevice::Control

   virtual void change(bool plug,bool power);

   virtual void tick();

  public:

   explicit VideoConsole(StrLen video_dev_name);

   ~VideoConsole();

   bool waitOpen(MSec timeout=DefaultTimeout);

   void print(StrLen str);
 };

} // namespace Video
} // namespace CCore

#endif


