/* VideConsole.cpp */
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

#include <CCore/inc/video/VideoConsole.h>

namespace CCore {
namespace Video {

/* class VideoConsole */

struct VideoConsole::InitFunc
 {
  ColorPlane plane;

  explicit InitFunc(const ColorPlane &plane_) : plane(plane_) {}

  void operator () (AnyType &con) { con.init(plane); }
 };

struct VideoConsole::PrintFunc
 {
  StrLen str;

  explicit PrintFunc(StrLen str_) : str(str_) {}

  void operator () (AnyType &con) { con.print(str); }
 };

struct VideoConsole::ToggleMarkerFunc
 {
  void operator () (AnyType &con) { con.toggleMarker(); }
 };

ColorMode VideoConsole::setDevice()
 {
  if( dev->updateVideoModeList(DefaultTimeout) && dev->setVideoMode(0) ) return dev->getColorMode();

  return ColorMode_none;
 }

bool VideoConsole::open()
 {
  if( ColorMode mode=setDevice() )
    {
     {
      Mutex::Lock lock(mutex);

      con.init(mode,InitFunc(dev->getPlane()));
     }

     dev->setTick(500_msec);

     sem.give();

     return true;
    }
  else
    {
     Mutex::Lock lock(mutex);

     con.clear();

     return false;
    }
 }

void VideoConsole::close()
 {
  Mutex::Lock lock(mutex);

  con.clear();
 }

void VideoConsole::do_print(StrLen str)
 {
  con.apply(PrintFunc(str));
 }

void VideoConsole::do_tick()
 {
  con.apply(ToggleMarkerFunc());
 }

void VideoConsole::change(bool plug,bool power)
 {
  if( plug )
    {
     if( power )
       {
        if( first )
          {
           if( open() ) first=false;
          }
       }
    }
  else
    {
     first=true;

     close();
    }
 }

void VideoConsole::tick()
 {
  Mutex::Lock lock(mutex);

  do_tick();
 }

VideoConsole::VideoConsole(StrLen video_dev_name)
 : hook(video_dev_name),
   dev(hook),
   mutex("!VideoConsole.mutex"),
   sem("!VideoConsole.sem")
 {
  dev->attach(this);
 }

VideoConsole::~VideoConsole()
 {
  dev->detach();
 }

bool VideoConsole::waitOpen(MSec timeout)
 {
  return sem.take(timeout);
 }

void VideoConsole::print(StrLen str)
 {
  Mutex::Lock lock(mutex);

  do_print(str);
 }

} // namespace Video
} // namespace CCore


