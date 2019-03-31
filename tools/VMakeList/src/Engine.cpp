/* Engine.cpp */
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

#include <inc/Engine.h>

namespace App {

/* class Engine */

Engine::Engine(TypeDef::Param *param,StrLen root,StrLen target,TypeDef::Tools *tools,StrLen dst_file_name)
 {
  Used(param);
  Used(root);
  Used(target);
  Used(tools);
  Used(dst_file_name);
 }

Engine::~Engine()
 {
 }

int Engine::run()
 {
  return 1;
 }

} // namespace App

