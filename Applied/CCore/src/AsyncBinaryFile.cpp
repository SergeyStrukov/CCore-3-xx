/* AsyncBinaryFile.cpp */
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

#include <CCore/inc/AsyncBinaryFile.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class AsyncBinaryFile */

void AsyncBinaryFile::provide()
 {
  flush();

  auto result=file.getWritePacket();

  packet=result.packet;

  out=result.buf;
  buf_len=out.len;
 }

AsyncBinaryFile::AsyncBinaryFile(MSec timeout,ulen max_packets)
 : file(timeout,max_packets)
 {
 }

AsyncBinaryFile::AsyncBinaryFile(StrLen file_name,FileOpenFlags oflags,MSec timeout,ulen max_packets)
 : file(timeout,max_packets)
 {
  open(file_name,oflags);
 }

AsyncBinaryFile::AsyncBinaryFile(StrLen dev_name,StrLen dev_file_name,FileOpenFlags oflags,MSec timeout,ulen max_packets)
 : file(timeout,max_packets)
 {
  open(dev_name,dev_file_name,oflags);
 }

AsyncBinaryFile::~AsyncBinaryFile()
 {
  flush();
 }

void AsyncBinaryFile::open(StrLen file_name,FileOpenFlags oflags)
 {
  FilePosType file_len=file.open(file_name,oflags);

  file_pos=(oflags&Open_PosEnd)?file_len:0;
 }

void AsyncBinaryFile::open(StrLen dev_name,StrLen dev_file_name,FileOpenFlags oflags)
 {
  FilePosType file_len=file.open(dev_name,dev_file_name,oflags);

  file_pos=(oflags&Open_PosEnd)?file_len:0;
 }

void AsyncBinaryFile::soft_close(FileMultiError &errout)
 {
  flush();

  file.soft_close(errout);
 }

void AsyncBinaryFile::close()
 {
  flush();

  file.close();
 }

void AsyncBinaryFile::do_put(const uint8 *ptr,ulen len)
 {
  auto src=Range(ptr,len);

  while( +src )
    {
     if( !out ) provide();

     ulen delta=Min(src.len,out.len);

     (out+=delta).copy( (src+=delta).ptr );
    }
 }

void AsyncBinaryFile::flush()
 {
  if( +packet )
    {
     ulen len=buf_len-out.len;

     out=Nothing;

     file.write(file_pos,len,Replace_null(packet));

     file_pos+=len;
    }
 }

} // namespace CCore


