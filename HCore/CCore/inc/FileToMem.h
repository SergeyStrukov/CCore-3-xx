/* FileToMem.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_FileToMem_h
#define CCore_inc_FileToMem_h

#include <CCore/inc/ToMemBase.h>
#include <CCore/inc/Array.h>

#include <CCore/inc/sys/SysFile.h>

namespace CCore {

/* classes */

class RawFileToRead;

class FileToMem;

class PartFileToMem;

/* class RawFileToRead */

class RawFileToRead : NoCopy
 {
   Sys::File file;

  public:

   explicit RawFileToRead(StrLen file_name,FileOpenFlags oflags=Open_Read);

   ~RawFileToRead();

   FilePosType getLen();

   ulen read(uint8 *buf,ulen len);

   void read_all(uint8 *buf,ulen len);
 };

/* class FileToMem */

class FileToMem : public ToMemBase
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
     Swap<ToMemBase>(*this,obj);
    }

   explicit FileToMem(ToMoveCtor<FileToMem> obj) : ToMemBase(obj.cast<ToMemBase>()) {}
 };

/* class PartFileToMem */

class PartFileToMem : NoCopy
 {
   RawFileToRead file;
   SimpleArray<uint8> buf;
   FilePosType off;
   FilePosType file_len;

  public:

   static constexpr ulen DefaultBufLen = 64_KByte ;

   explicit PartFileToMem(StrLen file_name,ulen buf_len=DefaultBufLen);

   ~PartFileToMem();

   FilePosType getFileLen() const { return file_len; }

   FilePosType getCurPos() const { return off; }

   FilePosType getRestLen() const { return file_len-off; }

   bool more() const { return off<file_len; }

   PtrLen<const uint8> read();
 };

} // namespace CCore

#endif



