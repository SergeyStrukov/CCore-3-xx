/* PrintFile.h */
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

#ifndef CCore_inc_print_PrintFile_h
#define CCore_inc_print_PrintFile_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/SafeBuf.h>

#include <CCore/inc/sys/SysFile.h>

namespace CCore {

/* classes */

class RawFileToPrint;

class PrintFile;

/* class RawFileToPrint */

class RawFileToPrint : NoCopy
 {
   Sys::File file;
   bool opened;
   bool preserve_file;

  public:

   // constructors

   RawFileToPrint() : opened(false) {}

    // No destructor !

   // methods

   bool isOpened() const { return opened; }

   FileError open(StrLen file_name,FileOpenFlags oflags);

   void close(FileMultiError &errout);

   void preserveFile() { preserve_file=true; }

   FileError write(const uint8 *buf,ulen len);
 };

/* class PrintFile */

class PrintFile : public PrintBase
 {
   static constexpr ulen BufLen = 64_KByte ;

   RawFileToPrint file;
   SafeBuf buf;
   bool no_flush_exception = false ;
   FileError flush_error;

  private:

   virtual PtrLen<char> do_provide(ulen hint_len);

   virtual void do_flush(char *ptr,ulen len);

  public:

   // constructors

   PrintFile() noexcept;

   explicit PrintFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);

   ~PrintFile();

   // methods

   bool isOpened() const { return file.isOpened(); }

   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);

   void disableExceptions();

   void soft_close(FileMultiError &errout);

   void close();

   void preserveFile() { file.preserveFile(); }
 };

} // namespace CCore

#endif


