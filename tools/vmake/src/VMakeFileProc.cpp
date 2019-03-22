/* VMakeFileProc.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: vmake 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/VMakeProc.h>

#include <CCore/inc/MakeFileName.h>

namespace App {

namespace VMake {

/* class FileProc */

FileProc::FileProc()
 {
 }

FileProc::~FileProc()
 {
 }

bool FileProc::checkNotExist(StrLen wdir,StrLen dst)
 {
  MakeFileName dst1(wdir,dst);

  return fs.getFileType(dst1.get())!=FileType_file;
 }

bool FileProc::checkOlder(StrLen wdir,StrLen dst,StrLen src)
 {
  MakeFileName dst1(wdir,dst);
  MakeFileName src1(wdir,src);

  auto dst_time=fs.getFileUpdateTime(dst1.get());
  auto src_time=fs.getFileUpdateTime(src1.get());

  return dst_time<src_time;
 }

} // namespace VMake

} // namespace App

