/* RawFileToRead.h */
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

#ifndef CCore_inc_RawFileToRead_h
#define CCore_inc_RawFileToRead_h

#include <CCore/inc/AsyncFile.h>

namespace CCore {

/* classes */

class RawFileToRead;

/* class RawFileToRead */

class RawFileToRead : NoCopy
 {
   AsyncFile file;
   FileOpenFlags oflags;

   FilePosType file_len;
   FilePosType pos;

  private:

   FilePosType getRest() const { return file_len-pos; }

  public:

   explicit RawFileToRead(StrLen file_name,FileOpenFlags oflags=Open_Read);

   ~RawFileToRead();

   FilePosType getLen();

   ulen read(uint8 *buf,ulen len);

   void read_all(uint8 *buf,ulen len);
 };

} // namespace CCore

#endif

