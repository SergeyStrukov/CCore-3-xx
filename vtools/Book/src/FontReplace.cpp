/* FontReplace.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/FontReplace.h>

#include <CCore/inc/video/DesktopKey.h>
#include <CCore/inc/video/HomeFile.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>
#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/video/PrintDDL.h>
#include <CCore/inc/PrintStem.h>

namespace App {

namespace FontMap {

#include "FontMap.TypeDef.gen.h"
#include "FontMap.TypeSet.gen.h"

} // namespace FontMap

/* class FontReplace */

StrLen FontReplace::ReplaceFile() { return "/FontReplace.ddl"_c; }

StrLen FontReplace::Pretext()
 {
  return
"struct Entry\n"
" {\n"
"  text face;\n"
"  text replace;\n"
" };\n"
"\n"
"struct Map\n"
" {\n"
"  Entry[] list;\n"
" };\n"_c;
 }

void FontReplace::loadDDL(StrLen file_name)
 {
  map.erase();

  char temp[512];
  PrintBuf eout(Range(temp));
  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(file_name,Pretext());

  if( !result )
    {
     Printf(Exception,"App::FontReplace::loadDDL(#.q;) : input file processing error\n#;",file_name,eout.close());
    }
  else
    {
     DDL::TypedMap<FontMap::TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     // populate

     FontMap::TypeDef::Map obj=map.takeConst<FontMap::TypeDef::Map>("Data");

     for(auto entry : obj.list.getRange() ) add(entry.face,entry.replace);
    }
 }

void FontReplace::saveDDL(StrLen file_name) const
 {
  PrintFile out(file_name);

  Putobj(out,"Map Data={{"_c);

  PrintFirst stem(""_c,","_c);

  map.applyIncr( [&] (const StringKey &key,const String &val)
                     {
                      Printf(out,"#;\n{ #; , #; }",stem,DDLPrintableString(key.str),DDLPrintableString(val));
                     } );

  Putobj(out,"\n}};"_c);
 }

void FontReplace::load(StrLen dir,StrLen file)
 {
  HomeFile home_file(dir,file);

  if( home_file.exist() ) loadDDL(home_file.get());
 }

void FontReplace::save(StrLen dir,StrLen file) const
 {
  HomeFile home_file(dir,file);

  home_file.createDir();

  saveDDL(home_file.get());
 }

void FontReplace::add(StrLen face,StrLen replace)
 {
  StrKey key(face);

  map.find_or_add(key,replace);
 }

FontReplace::FontReplace()
 {
 }

FontReplace::~FontReplace()
 {
 }

StrLen FontReplace::operator () (StrLen face) const
 {
  StrKey key(face);

  if( const String *obj=map.find(key) )
    {
     if( StrLen ret=Range(*obj) ; +ret ) return ret;
    }

  return face;
 }

void FontReplace::addNotFound(StrLen face)
 {
  StrKey key(face);

  map.find_or_add(key);
 }

void FontReplace::load() noexcept
 {
  try { load(HomeKey(),ReplaceFile()); } catch(...) {}
 }

void FontReplace::save() const noexcept
 {
  try { save(HomeKey(),ReplaceFile()); } catch(...) {}
 }

/* class FontMapWindow */

FontMapWindow::FontMapWindow(SubWindowHost &host,const Config &cfg_,FontReplace &replace_)
 : SubWindow(host),
   cfg(cfg_),

   replace(replace_)
 {
 }

FontMapWindow::~FontMapWindow()
 {
 }

 // methods

Point FontMapWindow::getMinSize() const
 {
  return Point(100,100);
 }

 // drawing

void FontMapWindow::layout()
 {
 }

void FontMapWindow::draw(DrawBuf buf,bool) const
 {
  Used(buf);
 }

 // keyboard

void FontMapWindow::gainFocus()
 {
 }

void FontMapWindow::looseFocus()
 {
 }

 // user input

void FontMapWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void FontMapWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  Used(vkey);
  Used(kmod);
  Used(repeat);
 }

void FontMapWindow::react_LeftClick(Point point,MouseKey mkey)
 {
  Used(point);
  Used(mkey);
 }

void FontMapWindow::react_Wheel(Point point,MouseKey mkey,Coord delta)
 {
  Used(point);
  Used(mkey);
  Used(delta);
 }

/* class FontReplaceWindow */

FontReplaceWindow::FontReplaceWindow(SubWindowHost &host,const Config &cfg_,FontReplace &replace_)
 : ComboWindow(host),
   cfg(cfg_),

   replace(replace_)
 {
 }

FontReplaceWindow::~FontReplaceWindow()
 {
 }

 // methods

Point FontReplaceWindow::getMinSize() const
 {
  return Point(100,100);
 }

void FontReplaceWindow::update()
 {
 }

 // drawing

void FontReplaceWindow::layout()
 {
 }

void FontReplaceWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

 // user input

void FontReplaceWindow::react(UserAction action)
 {
  wlist.react(action);
 }

/* class FontReplaceFrame */

FontReplaceFrame::FontReplaceFrame(Desktop *desktop,const Config &cfg_,FontReplace &replace,Signal<> &update)
 : DragFrame(desktop,cfg_.frame_cfg,update),
   cfg(cfg_),

   client(*this,cfg.client_cfg,replace),

   apply(client.apply)
 {
  bindClient(client);
 }

FontReplaceFrame::~FontReplaceFrame()
 {
 }

 // base

void FontReplaceFrame::dying()
 {
  DragFrame::dying();

  place.set(host->getPlace());
 }

 // create

Pane FontReplaceFrame::getPane(StrLen title) const
 {
  if( place.ok ) return place.place;

  Point size=getMinSize(false,title,client.getMinSize());

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

} // namespace App

