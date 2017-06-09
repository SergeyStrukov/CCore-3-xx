/* PrintFile.cpp */
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

#include <CCore/inc/print/PrintFile.h>

#include <CCore/inc/DefaultFileDevice.h>

namespace CCore {

/* class PrintFile */

PrintFile::PrintFile() noexcept
 {
 }

PrintFile::PrintFile(StrLen file_name,FileOpenFlags oflags)
 : PrintAsyncFile(GetDefaultFileDevice(),file_name,oflags)
 {
 }

PrintFile::~PrintFile()
 {
 }

void PrintFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  PrintAsyncFile::open(GetDefaultFileDevice(),file_name,oflags);
 }

} // namespace CCore

