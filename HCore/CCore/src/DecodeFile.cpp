/* DecodeFile.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/DecodeFile.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class DecodeFile */

void DecodeFile::underflow()
 {
  uint8 *ptr=getBase();

  auto result=file.read(ptr,buf.getLen());

  if( result.error )
    {
     Printf(Exception,"CCore::DecodeFile::underflow() : #;",result.error);
    }
  else if( !result.len )
    {
     Printf(Exception,"CCore::DecodeFile::underflow() : EOF");
    }
  else
    {
     cur=Range_const(ptr,result.len);
    }
 }

bool DecodeFile::underflow_eof()
 {
  uint8 *ptr=getBase();

  auto result=file.read(ptr,buf.getLen());

  if( result.error )
    {
     Printf(Exception,"CCore::DecodeFile::underflow_eof() : #;",result.error);

     return false;
    }
  else if( !result.len )
    {
     return false;
    }
  else
    {
     cur=Range_const(ptr,result.len);

     return true;
    }
 }

DecodeFile::DecodeFile() noexcept
 : buf(BufLen)
 {
 }

DecodeFile::DecodeFile(StrLen file_name)
 : DecodeFile()
 {
  open(file_name);
 }

DecodeFile::~DecodeFile()
 {
  if( isOpened() )
    {
     FileMultiError errout;

     soft_close(errout);

     if( +errout )
       {
        Printf(NoException,"CCore::DecodeFile::~DecodeFile() : #;",errout);
       }
    }
 }

 // methods

void DecodeFile::open(StrLen file_name)
 {
  if( FileError error=file.open(file_name) )
    {
     Printf(Exception,"CCore::DecodeFile::open(#.q;,...) : #;",file_name,error);
    }

  reset();
 }

void DecodeFile::soft_close(FileMultiError &errout)
 {
  if( isOpened() )
    {
     file.close(errout);

     reset();
    }
  else
    {
     errout.add(FileError_NoMethod);
    }
 }

void DecodeFile::close()
 {
  FileMultiError errout;

  soft_close(errout);

  if( +errout )
    {
     Printf(Exception,"CCore::DecodeFile::close() : #;",errout);
    }
 }

 // get

void DecodeFile::do_get(uint8 *ptr,ulen len)
 {
  while( len )
    {
     if( !cur ) underflow();

     ulen delta=Min(len,cur.len);

     Range(ptr,delta).copy(cur.ptr);

     cur+=delta;
     ptr+=delta;
     len-=delta;
    }
 }

/* class DecodeBinFile */

void DecodeBinFile::underflow()
 {
  uint8 *ptr=getBase();

  ulen len=file->read(off,ptr,buf.getLen());

  if( !len )
    {
     Printf(Exception,"CCore::DecodeBinFile::underflow() : EOF");
    }
  else
    {
     cur=Range_const(ptr,len);

     off+=len;
    }
 }

bool DecodeBinFile::underflow_eof()
 {
  uint8 *ptr=getBase();

  ulen len=file->read(off,ptr,buf.getLen());

  if( !len )
    {
     return false;
    }
  else
    {
     cur=Range_const(ptr,len);

     off+=len;

     return true;
    }
 }

 // constructors

DecodeBinFile::DecodeBinFile(const BinFileToRead &file_,StrLen file_name)
 : file(file_),
   buf(BufLen)
 {
  file->open(file_name);
 }

DecodeBinFile::~DecodeBinFile()
 {
  file->close();
 }

 // get

void DecodeBinFile::do_get(uint8 *ptr,ulen len)
 {
  while( len )
    {
     if( !cur ) underflow();

     ulen delta=Min(len,cur.len);

     Range(ptr,delta).copy(cur.ptr);

     cur+=delta;
     ptr+=delta;
     len-=delta;
    }
 }

} // namespace CCore

