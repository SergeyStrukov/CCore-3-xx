/* FileToMem.cpp */
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

#include <CCore/inc/FileToMem.h>

#include <CCore/inc/DefaultFileDevice.h>

namespace CCore {

/* class FileToMem */

FileToMem::FileToMem(StrLen file_name,ulen max_len)
 : AsyncFileToMem(GetDefaultFileDevice(),file_name,max_len)
 {
 }

FileToMem::~FileToMem()
 {
 }

/* class PartFileToMem */

PartFileToMem::PartFileToMem(StrLen file_name,ulen buf_len)
 : PartAsyncFileToMem(GetDefaultFileDevice(),file_name,buf_len)
 {
 }

PartFileToMem::~PartFileToMem()
 {
 }

} // namespace CCore



