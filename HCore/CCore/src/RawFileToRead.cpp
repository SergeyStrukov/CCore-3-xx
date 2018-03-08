/* RawFileToRead.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/RawFileToRead.h>

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

/* class AltFileToRead */

AltFileToRead::AltFileToRead(StrLen file_name,FileOpenFlags oflags)
 {
  auto result=file.open(file_name,oflags);

  if( result.error )
    {
     Printf(Exception,"CCore::AltFileToRead::AltFileToRead(#.q;,#;) : #;",file_name,oflags,result.error);
    }

  file_len=result.file_len;
 }

AltFileToRead::~AltFileToRead()
 {
  FileMultiError errout;

  file.close(errout);

  if( +errout )
    {
     Printf(NoException,"CCore::AltFileToRead::~AltFileToRead() : #;",errout);
    }
 }

ulen AltFileToRead::read(FilePosType off,uint8 *buf,ulen len)
 {
  CapDown(len,getCap(off));

  if( !len ) return 0;

  if( FileError fe=file.read(off,buf,len) )
    {
     Printf(Exception,"CCore::AltFileToRead::read(...) : #;",fe);
    }

  return len;
 }

void AltFileToRead::read_all(FilePosType off,uint8 *buf,ulen len)
 {
  if( len>getCap(off) )
    {
     Printf(Exception,"CCore::AltFileToRead::read_all(...) : out of bound");
    }

  if( !len ) return;

  if( FileError fe=file.read(off,buf,len) )
    {
     Printf(Exception,"CCore::AltFileToRead::read_all(...) : #;",fe);
    }
 }

} // namespace CCore

