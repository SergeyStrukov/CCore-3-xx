/* test4032.DelDirRecursive.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/FileSystem.h>

namespace App {

namespace Private_4032 {


} // namespace Private_4032

using namespace Private_4032;

/* Testit<4032> */

template<>
const char *const Testit<4032>::Name="Test4032 DelDirRecursive";

template<>
bool Testit<4032>::Main()
 {
  FileSystem fs;

  fs.createDir("dir1");

  fs.createFile("dir1/file1");
  fs.createFile("dir1/file2");
  fs.createFile("dir1/file3");

  fs.createDir("dir1/dir2");

  fs.createFile("dir1/dir2/file1");
  fs.createFile("dir1/dir2/file2");
  fs.createFile("dir1/dir2/file3");

  fs.createDir("dir1/dir3");

  fs.createFile("dir1/dir3/file1");
  fs.createFile("dir1/dir3/file2");
  fs.createFile("dir1/dir3/file3");

  fs.createDir("dir1/dir2/dir4");

  fs.createFile("dir1/dir2/dir4/file1");
  fs.createFile("dir1/dir2/dir4/file2");
  fs.createFile("dir1/dir2/dir4/file3");

  fs.deleteDir("dir1",true);

  return true;
 }

} // namespace App

