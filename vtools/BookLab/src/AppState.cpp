/* AppState.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/AppState.h>

#include <CCore/inc/video/HomeFile.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/PrintStem.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/Exception.h>

namespace App {

/* struct AppState */

StrLen AppState::File() { return "/AppState.ddl"_c; }

StrLen AppState::Pretext()
 {
  return

#include "AppState.Pretext.gen.h"

  ""_c;
 }

AppState::AppState()
 {
 }

AppState::~AppState()
 {
 }

namespace AppStateTypes {

#include "AppState.TypeDef.gen.h"
#include "AppState.TypeSet.gen.h"

} // namespace AppStateTypes

using namespace AppStateTypes;

bool AppState::load(StrLen file_name)
 {
  char buf[TextBufLen];
  PrintBuf eout(Range(buf));

  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(file_name,Pretext());

  if( !result )
    {
     return false;
    }
  else
    {
     DDL::TypedMap<TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     // populate

     TypeDef::AppState data=map.takeConst<TypeDef::AppState>("Data"_c);

     place.x=data.place.x;
     place.y=data.place.y;
     place.dx=data.place.dx;
     place.dy=data.place.dy;

     temp_place.set(data.temp_place);
     edit_place.set(data.edit_place);

     return true;
    }

  return false;
 }

void AppState::save(StrLen file_name) const
 {
  PrintFile out(file_name);

  Printf(out,"//include <AppState.ddl>\n\n");

  Printf(out,"AppState Data=\n {\n");

  Printf(out,"  .place = #;",DDLPane(place));

  if( temp_place.ok ) Printf(out,",\n  .temp_place = #;",temp_place);

  if( edit_place.ok ) Printf(out,",\n  .edit_place = #;",edit_place);

  Printf(out,"\n };\n\n");
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

void AppState::save() const noexcept
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

