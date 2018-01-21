/* RawFileToRead.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/RawFileToRead.h>

#include <CCore/inc/DefaultFileDevice.h>

#include <CCore/inc/Exception.h>

namespace CCore {

/* class RawFileToRead */

RawFileToRead::RawFileToRead(StrLen file_name,FileOpenFlags oflags_)
 : oflags(oflags_)
 {
  file_len=file.open(GetDefaultFileDevice(),file_name,oflags_);

  if( oflags_&Open_PosEnd )
    pos=file_len;
  else
    pos=0;
 }

RawFileToRead::~RawFileToRead()
 {
 }

FilePosType RawFileToRead::getLen()
 {
  if( !(oflags&Open_Pos) )
    {
     Printf(Exception,"CCore::RawFileToRead::getLen() : #;",FileError_NoMethod);
    }

  return file_len;
 }

ulen RawFileToRead::read(uint8 *buf,ulen len)
 {
  CapDown(len,getRest());

  file.read_all(pos,buf,len);

  pos+=len;

  return len;
 }

void RawFileToRead::read_all(uint8 *buf,ulen len)
 {
  if( len>getRest() )
    {
     Printf(Exception,"CCore::RawFileToRead::read_all(...) : #;",FileError_ReadLenMismatch);
    }

  file.read_all(pos,buf,len);

  pos+=len;
 }

} // namespace CCore

