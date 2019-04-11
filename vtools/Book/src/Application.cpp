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

"type Coord = sint32 ;\r\n"
"\r\n"
"struct Pane\r\n"
" {\r\n"
"  Coord x;\r\n"
"  Coord y;\r\n"
"  Coord dx;\r\n"
"  Coord dy;\r\n"
" };\r\n"
"\r\n"
"struct AppState\r\n"
" {\r\n"
"  Pane place;\r\n"
" };"_c;
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

     auto p=data.place;

     place=Pane(p.x,p.y,p.dx,p.dy);

     return true;
    }

  return false;
 }

void AppState::save(StrLen file_name) const
 {
  PrintFile out(file_name);

  Printf(out,"//include <AppState.ddl>\n\n");

  Printf(out,"AppState Data=\n {\n\n");

  Printf(out,"  { #; , #; , #; , #; }\n\n",place.x,place.y,place.dx,place.dy);

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

 // methods

void ClientWindow::prepare(const AppState &app_state)
 {
  Used(app_state);
 }

 // AliveControl

void ClientWindow::dying()
 {
  AppState app_state;

  app_state.place=getFrameHost()->getPlace();

  app_state.save();
 }

} // namespace App


