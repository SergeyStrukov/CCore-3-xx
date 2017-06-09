/* PrintFile.h */
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

#ifndef CCore_inc_print_PrintFile_h
#define CCore_inc_print_PrintFile_h

#include <CCore/inc/print/PrintAsyncFile.h>

namespace CCore {

/* classes */

class PrintFile;

/* class PrintFile */

class PrintFile : public PrintAsyncFile
 {
  public:

   PrintFile() noexcept;

   explicit PrintFile(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);

   ~PrintFile();

   void open(StrLen file_name,FileOpenFlags oflags=Open_ToWrite);
 };

} // namespace CCore

#endif

