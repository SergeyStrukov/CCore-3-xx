/* Activator.cpp */
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

#include <CCore/inc/video/Activator.h>

namespace CCore {
namespace Video {

/* class Activator */

void Activator::exit()
 {
  stopping=true;

  stop_sem.give();
 }

Activator::Activator()
 {
 }

Activator::~Activator()
 {
 }

void Activator::stop()
 {
  if( running )
    {
     setStop();

     stop_sem.take();

     running=false;
    }
 }

bool Activator::waitStop(MSec timeout)
 {
  if( running && stopping )
    {
     if( stop_sem.take(timeout) )
       {
        running=false;

        return true;
       }
    }

  return false;
 }

} // namespace Video
} // namespace CCore

