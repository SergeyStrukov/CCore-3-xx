/* DefaultFileDevice.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/DefaultFileDevice.h>

#include <CCore/inc/Task.h>
#include <CCore/inc/Exception.h>

namespace CCore {

namespace Private_DefaultFileDevice {

class DefaultFileDevice : NoCopy
 {
   Mutex mutex;

   char buf[MaxPathLen];
   ulen len = 0 ;

  private:

   void set_(StrLen dev)
    {
     if( dev.len>MaxPathLen )
       {
        Printf(Exception,"CCore::SetDefaultFileDevice(...) : too long");
       }

     dev.copyTo(buf);

     len=dev.len;
    }

  public:

   DefaultFileDevice()
    : mutex("!DefaultFileDevice")
    {
     set_("host"_c);
    }

   ~DefaultFileDevice()
    {
    }

   void set(StrLen dev)
    {
     Mutex::Lock lock(mutex);

     set_(dev);
    }

   ulen copy(char ret[MaxPathLen])
    {
     Mutex::Lock lock(mutex);

     Range(buf,len).copyTo(ret);

     return len;
    }
 };

DefaultFileDevice Object CCORE_INITPRI_3;

} // namespace Private_DefaultFileDevice

using namespace Private_DefaultFileDevice;

/* functions */

void SetDefaultFileDevice(StrLen dev)
 {
  Object.set(dev);
 }

ulen CopyDefaultFileDevice(char buf[MaxPathLen])
 {
  return Object.copy(buf);
 }

} // namespace CCore

