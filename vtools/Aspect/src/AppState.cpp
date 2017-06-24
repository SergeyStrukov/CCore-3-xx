/* AppState.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.01
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/AppState.h>

#include <CCore/inc/video/HomeFile.h>

#include <CCore/inc/Print.h>

#include <CCore/inc/Exception.h>

namespace App {

/* struct AppState */

StrLen AppState::File() { return "/AppState.ddl"_c; }

AppState::AppState()
 {
 }

AppState::~AppState()
 {
 }

bool AppState::load(StrLen file_name)
 {
  // TODO

  return false;
 }

void AppState::save(StrLen file_name)
 {
  // TODO
 }

bool AppState::load() noexcept
 {
  try
    {
     HomeFile home_file(AppKey(),File());

     return load(home_file.get());
    }
  catch(...)
    {
     return false;
    }
 }

void AppState::save() noexcept
 {
  try
    {
     HomeFile home_file(AppKey(),File());

     home_file.createDir();

     save(home_file.get());
    }
  catch(...)
    {
    }
 }

} // namespace App

