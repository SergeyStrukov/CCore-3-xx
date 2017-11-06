/* ConfigBinder.cpp */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/ConfigBinder.h>

#include <CCore/inc/video/HomeFile.h>

namespace CCore {
namespace Video {

/* struct HomeSyncBase */

bool HomeSyncBase::syncHome(StrLen home_dir,StrLen cfg_file) noexcept
 {
  bool ret=false;

  try
    {
     HomeFile home_file(home_dir,cfg_file);

     ConfigMap map;

     ret=map.loadDDL_safe(home_file.get());

     syncMap(map);

     if( map.isModified() )
       {
        home_file.createDir();

        map.saveDDL(home_file.get());
       }
    }
  catch(...)
    {
    }

  return ret;
 }

void HomeSyncBase::updateHome(StrLen home_dir,StrLen cfg_file) noexcept
 {
  try
    {
     HomeFile home_file(home_dir,cfg_file);

     ConfigMap map;

     map.loadDDL_safe(home_file.get());

     updateMap(map);

     home_file.createDir();

     map.saveDDL(home_file.get());
    }
  catch(...)
    {
    }
 }

} // namespace Video
} // namespace CCore

