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



