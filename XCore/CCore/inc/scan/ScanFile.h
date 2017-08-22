/* ScanFile.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
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

#ifndef CCore_inc_scan_ScanFile_h
#define CCore_inc_scan_ScanFile_h

#include <CCore/inc/scan/ScanAsyncFile.h>

namespace CCore {

/* classes */

class ScanFile;

/* class ScanFile */

class ScanFile : public ScanAsyncFile
 {
  public:

   ScanFile();

   explicit ScanFile(StrLen file_name);

   ~ScanFile();

   // methods

   void open(StrLen file_name);
 };

} // namespace CCore

#endif

