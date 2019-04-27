/* Application.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Application.h>

#include <CCore/inc/video/HomeFile.h>
#include <CCore/inc/video/PrintDDL.h>

#include <CCore/inc/Print.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/Exception.h>

namespace App {

/* struct AppState */

StrLen AppState::File() { return "/BookState.ddl"_c; }

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

     place.set(data.place);

     fav_place.set(data.fav_place);

     return true;
    }

  return false;
 }

void AppState::save(StrLen file_name) const
 {
  PrintFile out(file_name);

  Printf(out,"//include <AppState.ddl>\n\n");

  Printf(out,"AppState Data=\n {\n\n");

  Printf(out,"  #;,\n\n",place);

  Printf(out,"  #;\n\n",fav_place);

  Printf(out," };\n\n");
 }

bool AppState::load() noexcept
 {
  try
    {
     HomeFile home_file(AppProp::Key(),File());

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
     HomeFile home_file(AppProp::Key(),File());

     home_file.createDir();

     save(home_file.get());
    }
  catch(...)
    {
    }
 }

/* class ClientWindow */

ClientWindow::ClientWindow(SubWindowHost &host,const Config &cfg,OptFileName opt,Signal<> &update)
 : Book::ClientWindow(host,cfg,opt,update)
 {
 }

ClientWindow::~ClientWindow()
 {
 }

 // AliveControl

void ClientWindow::dying()
 {
  AppState app_state;

  app_state.place.set(getFrameHost()->getPlace());

  save(app_state);

  app_state.save();
 }

} // namespace App


