/* ScanFile.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
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

#include <CCore/inc/scan/ScanFile.h>
#include <CCore/inc/DefaultFileDevice.h>

namespace CCore {

/* class ScanFile */

ScanFile::ScanFile()
 {
 }

ScanFile::ScanFile(StrLen file_name)
 : ScanAsyncFile(GetDefaultFileDevice(),file_name)
 {
 }

ScanFile::~ScanFile()
 {
 }

 // methods

void ScanFile::open(StrLen file_name)
 {
  ScanAsyncFile::open(GetDefaultFileDevice(),file_name);
 }

} // namespace CCore

