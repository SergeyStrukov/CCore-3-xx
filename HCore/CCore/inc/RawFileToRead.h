/* RawFileToRead.h */
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

#ifndef CCore_inc_RawFileToRead_h
#define CCore_inc_RawFileToRead_h

#include <CCore/inc/sys/SysFile.h>

namespace CCore {

/* classes */

class RawFileToRead;

class AltFileToRead;

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

/* class AltFileToRead */

class AltFileToRead : NoCopy
 {
   Sys::AltFile file;
   FilePosType file_len;

  private:

   FilePosType getCap(FilePosType off) const { return (off>file_len)?0:(file_len-off); }

  public:

   explicit AltFileToRead(StrLen file_name,FileOpenFlags oflags=Open_Read);

   ~AltFileToRead();

   FilePosType getLen() const { return file_len; }

   ulen read(FilePosType off,uint8 *buf,ulen len);

   void read_all(FilePosType off,uint8 *buf,ulen len);
 };

} // namespace CCore

#endif

