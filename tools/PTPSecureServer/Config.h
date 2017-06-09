/* Config.h */
//----------------------------------------------------------------------------------------
//
//  Project: PTPSecureServer 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

/* TypeDef */

#include "Config.type.h"

/* classes */

class Config;

/* class Config */

class Config : NoCopy
 {
   void *mem;

   TypeDef::PTPSecureConfig *config;

  public:

   explicit Config(StrLen file_name);

   ~Config();

   operator TypeDef::PTPSecureConfig * () const { return config; }

   void show();
 };

} // namespace App

