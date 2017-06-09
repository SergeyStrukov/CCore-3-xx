/* FileToMem.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/inc/FileToMem.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class RawFileToRead */

RawFileToRead::RawFileToRead(StrLen file_name,FileOpenFlags oflags)
 {
  if( FileError fe=file.open(file_name,oflags) )
    {
     Printf(Exception,"CCore::RawFileToRead::RawFileToRead(#.q;,#;) : #;",file_name,oflags,fe);
    }
 }

RawFileToRead::~RawFileToRead()
 {
  FileMultiError errout;

  file.close(errout);

  if( +errout )
    {
     Printf(NoException,"CCore::RawFileToRead::~RawFileToRead() : #;",errout);
    }
 }

FilePosType RawFileToRead::getLen()
 {
  auto result=file.getLen();

  if( result.error )
    {
     Printf(Exception,"CCore::RawFileToRead::getLen() : #;",result.error);
    }

  return result.pos;
 }

ulen RawFileToRead::read(uint8 *buf,ulen len)
 {
  auto result=file.read(buf,len);

  if( result.error )
    {
     Printf(Exception,"CCore::RawFileToRead::read(...) : #;",result.error);
    }

  return result.len;
 }

void RawFileToRead::read_all(uint8 *buf,ulen len)
 {
  auto result=file.read(buf,len);

  if( result.error )
    {
     Printf(Exception,"CCore::RawFileToRead::read_all(...) : #;",result.error);
    }

  if( result.len!=len )
    {
     Printf(Exception,"CCore::RawFileToRead::read_all(...,#;) : return #;",len,result.len);
    }
 }

/* class FileToMem */

FileToMem::FileToMem(StrLen file_name,ulen max_len)
 {
  RawFileToRead file(file_name,Open_Read|Open_Pos);

  auto file_len=file.getLen();

  if( file_len>max_len )
    {
     Printf(Exception,"CCore::FileToMem::FileToMem(#.q;,max_len=#;) : file is too long #;",file_name,max_len,file_len);
    }

  ulen len=(ulen)file_len;

  file.read_all(alloc(len),len);
 }

FileToMem::~FileToMem()
 {
 }

/* class PartFileToMem */

PartFileToMem::PartFileToMem(StrLen file_name,ulen buf_len)
 : file(file_name,Open_Read|Open_Pos),
   buf(buf_len),
   off(0)
 {
  file_len=file.getLen();
 }

PartFileToMem::~PartFileToMem()
 {
 }

PtrLen<const uint8> PartFileToMem::read()
 {
  uint8 *ptr=buf.getPtr();
  ulen len=buf.getLen();

  FilePosType delta=file_len-off;

  if( !delta ) return Empty;

  if( delta<len ) len=(ulen)delta;

  file.read_all(ptr,len);

  off+=len;

  return Range(ptr,len);
 }

} // namespace CCore



