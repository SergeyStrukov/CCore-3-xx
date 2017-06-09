/* AsyncFileToMem.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_AsyncFileToMem_h
#define CCore_inc_AsyncFileToMem_h

#include <CCore/inc/AsyncFile.h>
#include <CCore/inc/ToMemBase.h>
#include <CCore/inc/FunctorType.h>

namespace CCore {

/* classes */

class AsyncFileToMem;

class AsyncFileListToMem;

class PartAsyncFileToMem;

/* class AsyncFileToMem */

class AsyncFileToMem : public ToMemBase
 {
  public:

   AsyncFileToMem() noexcept {}

   explicit AsyncFileToMem(StrLen file_name,ulen max_len=MaxULen,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);

   AsyncFileToMem(StrLen dev_name,StrLen dev_file_name,ulen max_len=MaxULen,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);

   ~AsyncFileToMem();

   // std move

   AsyncFileToMem(AsyncFileToMem &&obj) noexcept = default ;

   AsyncFileToMem & operator = (AsyncFileToMem &&obj) noexcept = default ;

   // swap/move objects

   void objSwap(AsyncFileToMem &obj)
    {
     Swap<ToMemBase>(*this,obj);
    }

   explicit AsyncFileToMem(ToMoveCtor<AsyncFileToMem> obj) : ToMemBase(obj.cast<ToMemBase>()) {}
 };

/* class AsyncFileListToMem */

class AsyncFileListToMem : public ToMemBase
 {
   PtrLen<const uint8> data;

   PtrLen<const uint8> file_name;

   FileType file_type;

  private:

   void build(AsyncFileSystem &fs,StrLen dev_path,ulen max_len,MSec timeout,ulen max_packets);

  public:

   explicit AsyncFileListToMem(StrLen path,ulen max_len=MaxULen,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);

   AsyncFileListToMem(AsyncFileSystem &fs,StrLen dev_path,ulen max_len=MaxULen,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);

   ~AsyncFileListToMem();

   bool next();

   StrLen getFileName() const { return Mutate<const char>(file_name); }

   FileType getFileType() const { return file_type; }

   template <FuncInitArgType<StrLen,FileType> FuncInit>
   auto apply(FuncInit func_init)
    {
     FunctorTypeOf<FuncInit> func(func_init);

     while( next() ) func(getFileName(),getFileType());

     return Algon::GetResult(func);
    }
 };

/* class PartAsyncFileToMem */

class PartAsyncFileToMem : NoCopy
 {
   AsyncFile file;
   SimpleArray<uint8> buf;
   FilePosType off;
   FilePosType file_len;

  public:

   static constexpr ulen DefaultBufLen = 64_KByte ;

   explicit PartAsyncFileToMem(StrLen file_name,ulen buf_len=DefaultBufLen,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);

   PartAsyncFileToMem(StrLen dev_name,StrLen dev_file_name,ulen buf_len=DefaultBufLen,MSec timeout=DefaultTimeout,ulen max_packets=DefaultMaxPackets);

   ~PartAsyncFileToMem();

   FilePosType getFileLen() const { return file_len; }

   FilePosType getCurPos() const { return off; }

   FilePosType getRestLen() const { return file_len-off; }

   bool more() const { return off<file_len; }

   PtrLen<const uint8> read();
 };

} // namespace CCore

#endif


