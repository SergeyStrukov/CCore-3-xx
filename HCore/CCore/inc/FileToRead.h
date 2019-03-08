/* FileToRead.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_FileToRead_h
#define CCore_inc_FileToRead_h

#include <CCore/inc/BinFileToRead.h>
#include <CCore/inc/Volume.h>

namespace CCore {

/* classes */

class DefBinFileToRead;

class VolumeBinFileToRead;

/* class DefBinFileToRead */

class DefBinFileToRead : public BinFileToRead
 {
   class Base;

  public:

   DefBinFileToRead();

   ~DefBinFileToRead();
 };

/* class VolumeBinFileToRead */

class VolumeBinFileToRead : public BinFileToRead
 {
   class Base;

  public:

   explicit VolumeBinFileToRead(StrLen file_name,FileOpenFlags oflags=Open_Read);

   ~VolumeBinFileToRead();
 };

} // namespace CCore

#endif

