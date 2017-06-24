/* HomeFile.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_HomeFile_h
#define CCore_inc_video_HomeFile_h

#include <CCore/inc/MakeString.h>
#include <CCore/inc/GenFile.h>

namespace CCore {
namespace Video {

/* classes */

class HomeFile;

/* class HomeFile */

class HomeFile
 {
   MakeString<MaxPathLen> buf;
   StrLen dir;
   StrLen file;

  public:

   HomeFile(StrLen home_dir,StrLen cfg_file); // "/dir" "/file"

   StrLen get() const { return file; }

   void createDir();
 };

} // namespace Video
} // namespace CCore

#endif

