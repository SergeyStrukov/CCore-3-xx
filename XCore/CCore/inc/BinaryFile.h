/* BinaryFile.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: XCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_BinaryFile_h
#define CCore_inc_BinaryFile_h

#include <CCore/inc/AsyncBinaryFile.h>

namespace CCore {

/* classes */

class BinaryFile;

/* class BinaryFile */

class BinaryFile : public AsyncBinaryFile
 {
  public:

   // constructors

   BinaryFile() noexcept;

   explicit BinaryFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);

   ~BinaryFile();

   // methods

   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
 };

} // namespace CCore

#endif

