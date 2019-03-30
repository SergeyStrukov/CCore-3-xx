/* VMakeList.h */
//----------------------------------------------------------------------------------------
//
//  Project: VMakeList 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef App_VMakeList_h
#define App_VMakeList_h

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

#include "VMakeList.TypeDef.gen.h"

/* classes */

class DataFile;

/* class DataFile */

class DataFile : NoCopy
 {
   void *mem = 0 ;

   TypeDef::Param * param = 0 ;

  private:

   static StrLen Pretext();

  public:

   explicit DataFile(StrLen file_name);

   ~DataFile();

   TypeDef::Param * getParam() const { return param; }
 };

} // namespace App

#endif


