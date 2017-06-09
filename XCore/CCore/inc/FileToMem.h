/* FileToMem.h */
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

#ifndef CCore_inc_FileToMem_h
#define CCore_inc_FileToMem_h

#include <CCore/inc/AsyncFileToMem.h>

namespace CCore {

/* classes */

class FileToMem;

class PartFileToMem;

/* class FileToMem */

class FileToMem : public AsyncFileToMem
 {
  public:

   FileToMem() noexcept {}

   explicit FileToMem(StrLen file_name,ulen max_len=MaxULen);

   ~FileToMem();

   // std move

   FileToMem(FileToMem &&obj) noexcept = default ;

   FileToMem & operator = (FileToMem &&obj) noexcept = default ;

   // swap/move objects

   void objSwap(FileToMem &obj)
    {
     Swap<AsyncFileToMem>(*this,obj);
    }

   explicit FileToMem(ToMoveCtor<FileToMem> obj) : AsyncFileToMem(obj.cast<AsyncFileToMem>()) {}
 };

/* class PartFileToMem */

class PartFileToMem : public PartAsyncFileToMem
 {
  public:

   explicit PartFileToMem(StrLen file_name,ulen buf_len=DefaultBufLen);

   ~PartFileToMem();
 };

} // namespace CCore

#endif



