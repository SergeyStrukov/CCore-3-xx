/* BinaryFile.cpp */
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

#include <CCore/inc/BinaryFile.h>

#include <CCore/inc/DefaultFileDevice.h>

namespace CCore {

/* class BinaryFile */

BinaryFile::BinaryFile() noexcept
 {
 }

BinaryFile::BinaryFile(StrLen file_name,FileOpenFlags oflags)
 : AsyncBinaryFile(GetDefaultFileDevice(),file_name,oflags)
 {
 }

BinaryFile::~BinaryFile()
 {
 }

 // methods

void BinaryFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  AsyncBinaryFile::open(GetDefaultFileDevice(),file_name,oflags);
 }

} // namespace CCore

