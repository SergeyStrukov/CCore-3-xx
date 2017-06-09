/* BinaryFile.h */
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

#ifndef CCore_inc_BinaryFile_h
#define CCore_inc_BinaryFile_h

#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/Array.h>

#include <CCore/inc/print/PrintFile.h>

namespace CCore {

/* classes */

class BinaryFile;

/* class BinaryFile */

class BinaryFile : public NoCopyBase< PutDevBase<BinaryFile> >
 {
   static constexpr ulen BufLen = 64_KByte ;

   RawFileToPrint file;
   DynArray<uint8> buf;
   bool no_flush_exception = false ;
   FileError flush_error;

   PtrLen<uint8> out;
   bool has_data = false ;

  private:

   void provide();

  public:

   // constructors

   BinaryFile() noexcept;

   explicit BinaryFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);

   ~BinaryFile();

   // methods

   bool isOpened() const { return file.isOpened(); }

   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);

   void disableExceptions();

   void soft_close(FileMultiError &errout);

   void close();

   void preserveFile() { file.preserveFile(); }

   // put

   void do_put(uint8 value)
    {
     if( !out ) provide();

     *out=value;

     ++out;
    }

   void do_put(const uint8 *ptr,ulen len);

   void flush();
 };

} // namespace CCore

#endif


