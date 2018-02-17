/* AppOpt.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_AppOpt_h
#define CCore_inc_video_AppOpt_h

#include <CCore/inc/video/Point.h>

namespace CCore {
namespace Video {

/* classes */

struct OptNone;

struct OptFileName;

struct PersistNone;

/* struct OptNone */

struct OptNone
 {
  OptNone(int argc,const char *argv[])
   {
    Used(argc);
    Used(argv);
   }
 };

/* struct OptFileName */

struct OptFileName
 {
  StrLen file_name;
  bool ok;

  OptFileName(int argc,const char *argv[])
   {
    if( argc==2 )
      {
       file_name=argv[1];
       ok=true;
      }
    else
      {
       ok=false;
      }
   }
 };

/* struct PersistNone */

struct PersistNone
 {
  Pane place;

  bool load() { return false; }
 };

} // namespace Video
} // namespace CCore

#endif

