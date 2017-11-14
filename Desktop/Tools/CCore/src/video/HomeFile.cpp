/* HomeFile.cpp */
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

#include <CCore/inc/video/HomeFile.h>

#include <CCore/inc/FileSystem.h>

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* class HomeFile */

HomeFile::HomeFile(StrLen home_dir,StrLen cfg_file)
 {
  HomeDir home;

  buf.add(home.get(),home_dir);

  dir=buf.get();

  buf.add(cfg_file);

  if( !buf )
    {
     Printf(Exception,"CCore::Video::HomeFile::HomeFile(#.q;,#.q;) : too long file name",home_dir,cfg_file);
    }

  file=buf.get();
 }

bool HomeFile::exist() const
 {
  FileSystem fs;

  return fs.getFileType(file)==FileType_file ;
 }

void HomeFile::createDir() const
 {
  FileSystem fs;

  if( fs.getFileType(dir)==FileType_none ) fs.createDir(dir);
 }

} // namespace Video
} // namespace CCore

