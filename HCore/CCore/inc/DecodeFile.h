/* DecodeFile.h */
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

#ifndef CCore_inc_DecodeFile_h
#define CCore_inc_DecodeFile_h

#include <CCore/inc/scan/ScanFile.h>

#include <CCore/inc/SaveLoad.h>

namespace CCore {

/* classes */

class DecodeFile;

/* class DecodeFile */

class DecodeFile : public NoCopyBase< GetDevBase<DecodeFile> >
 {
   static constexpr ulen BufLen = 64_KByte ;

   RawFileToScan file;
   SafeBuf buf;

   PtrLen<const uint8> cur;

  private:

   void reset() { cur=Null; }

   void underflow();

   bool underflow_eof();

  public:

   // constructors

   DecodeFile() noexcept;

   explicit DecodeFile(StrLen file_name);

   ~DecodeFile();

   // methods

   bool isOpened() const { return file.isOpened(); }

   void open(StrLen file_name);

   void soft_close(FileMultiError &errout);

   void close();

   // pump raw data

   bool more() { return +cur || underflow_eof() ; }

   PtrLen<const uint8> pump() { return Replace_null(cur); }

   // get

   uint8 do_get()
    {
     if( !cur ) underflow();

     uint8 ret=*cur;

     ++cur;

     return ret;
    }

   void do_get(uint8 *ptr,ulen len);
 };

} // namespace CCore

#endif

