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

#include <CCore/inc/Exception.h>

namespace App {

/* class Engine */

bool Engine::prepareRoot()
 {
  if( !root )
    {
     // TODO

     return false;
    }

  return true;
 }

bool Engine::prepareTarget()
 {
  if( !target )
    {
     // TODO

     return false;
    }

  return true;
 }

bool Engine::prepareTools()
 {
  if( !tools )
    {
     // TODO

     return false;
    }

  return true;
 }

Engine::Engine(TypeDef::Param *param_,StrLen src_file_name_,StrLen dst_file_name_)
 : param(param_),
   src_file_name(src_file_name_),
   dst_file_name(dst_file_name_)
 {
  root=param->CCORE_ROOT;
  target=param->CCORE_TARGET;
  tools=param->tools;
 }

Engine::~Engine()
 {
 }

int Engine::run()
 {
  if( prepareRoot() && prepareTarget() && prepareTools() )
    {
     Printf(Con,"run()\n");

     // TODO

     return 1;
    }

  return 1;
 }

} // namespace App

