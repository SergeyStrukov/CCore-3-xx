/* Engine.h */
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

#ifndef App_Engine_h
#define App_Engine_h

#include <CCore/inc/ddl/DDLMapTypes.h>

namespace App {

/* using */

using namespace CCore;

#ifndef VMakeList_TypeDef_h
#define VMakeList_TypeDef_h
#include "VMakeList.TypeDef.gen.h"
#endif

/* classes */

class Engine;

/* class Engine */

class Engine : NoCopy
 {
  public:

   Engine(TypeDef::Param *param,StrLen root,StrLen target,TypeDef::Tools *tools,StrLen dst_file_name);

   ~Engine();

   int run();
 };

} // namespace App

#endif

