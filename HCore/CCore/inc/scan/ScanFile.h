/* ScanFile.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#ifndef CCore_inc_scan_ScanFile_h
#define CCore_inc_scan_ScanFile_h

#include <CCore/inc/Scanf.h>
#include <CCore/inc/SafeBuf.h>

#include <CCore/inc/sys/SysFile.h>

namespace CCore {

/* classes */

class RawFileToScan;

class ScanFile;

/* class RawFileToScan */

class RawFileToScan : NoCopy
 {
   Sys::File file;
   bool opened = false ;

  public:

   // constructors

   RawFileToScan() {}

   // No destructor !

  // methods

  bool isOpened() const { return opened; }

  FileError open(StrLen file_name);

  void close(FileMultiError &errout);

  Sys::File::IOResult read(uint8 *buf,ulen len);
 };

/* class ScanFile */

class ScanFile : public ScanBase
 {
   static constexpr ulen BufLen = 64_KByte ;

   RawFileToScan file;
   SafeBuf buf;
   bool no_underflow_exception = false ;
   FileError underflow_error;

  private:

   virtual PtrLen<const char> underflow();

  public:

   // constructors

   ScanFile() noexcept;

   explicit ScanFile(StrLen file_name,bool disable_exceptions=false);

   ~ScanFile();

   // methods

   bool isOpened() const { return file.isOpened(); }

   void open(StrLen file_name,bool disable_exceptions=false);

   void disableExceptions();

   void soft_close(FileMultiError &errout);

   void close();
 };

} // namespace CCore

#endif


