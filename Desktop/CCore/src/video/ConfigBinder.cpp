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

#include <CCore/inc/MakeString.h>
#include <CCore/inc/FileSystem.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* struct HomeSyncBase */

void HomeSyncBase::syncHome(StrLen home_dir,StrLen cfg_file) noexcept
 {
  try
    {
     HomeDir home;

     MakeString<MaxPathLen> buf;

     buf.add(home.get(),home_dir);

     StrLen dir=buf.get();

     buf.add(cfg_file);

     if( !buf )
       {
        Printf(Exception,"CCore::Video::HomeSyncBase::syncHome(...) : too long file name");
       }

     StrLen file_name=buf.get();

     ConfigMap map;

     map.loadDDL_safe(file_name);

     syncMap(map);

     if( map.isModified() )
       {
        FileSystem fs;

        if( fs.getFileType(dir)==FileType_none ) fs.createDir(dir);

        map.saveDDL(file_name);
       }
    }
  catch(...)
    {
    }
 }

void HomeSyncBase::updateHome(StrLen home_dir,StrLen cfg_file) noexcept
 {
  try
    {
     HomeDir home;

     MakeString<MaxPathLen> buf;

     buf.add(home.get(),home_dir);

     StrLen dir=buf.get();

     buf.add(cfg_file);

     if( !buf )
       {
        Printf(Exception,"CCore::Video::HomeSyncBase::updateHome(...) : too long file name");
       }

     StrLen file_name=buf.get();

     ConfigMap map;

     map.loadDDL_safe(file_name);

     updateMap(map);

     FileSystem fs;

     if( fs.getFileType(dir)==FileType_none ) fs.createDir(dir);

     map.saveDDL(file_name);
    }
  catch(...)
    {
    }
 }

} // namespace Video
} // namespace CCore

