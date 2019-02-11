/* FontReplace.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/FontReplace.h>

#include <CCore/inc/Cmp.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/ForLoop.h>
#include <CCore/inc/PrintStem.h>
#include <CCore/inc/Array.h>

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeSet.h>
#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/video/LayoutCombo.h>
#include <CCore/inc/video/DesktopKey.h>
#include <CCore/inc/video/HomeFile.h>
#include <CCore/inc/video/PrintDDL.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

namespace Private_FontReplace {

#include "FontMap.TypeDef.gen.h"
#include "FontMap.TypeSet.gen.h"

} // namespace Private_FontReplace

using namespace Private_FontReplace;

/* class FontReplaceMap */

StrLen FontReplaceMap::ReplaceFile() { return "/FontReplace.ddl"_c; }

StrLen FontReplaceMap::Pretext()
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

void FontReplaceMap::loadDDL(StrLen file_name)
 {
  map.erase();

  char temp[512];
  PrintBuf eout(Range(temp));
  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(file_name,Pretext());

  if( !result )
    {
     Printf(Exception,"App::FontReplaceMap::loadDDL(#.q;) : input file processing error\n#;",file_name,eout.close());
    }
  else
    {
     DDL::TypedMap<TypeSet> map(result);
     MemAllocGuard guard(map.getLen());

     map(guard);

     // populate

     TypeDef::Map obj=map.takeConst<TypeDef::Map>("Data");

     for(auto entry : obj.list.getRange() ) add(entry.face,entry.replace);
    }
 }

void FontReplaceMap::saveDDL(StrLen file_name) const
 {
  PrintFile out(file_name);

  Putobj(out,"Map Data={{"_c);

  PrintFirst stem(""_c,","_c);

  map.applyIncr( [&] (const StringKey &key,const Rec &val)
                     {
                      Printf(out,"#;\n{ #; , #; }",stem,DDLPrintableString(key.str),DDLPrintableString(val.str));
                     } );

  Putobj(out,"\n}};"_c);
 }

void FontReplaceMap::load(StrLen dir,StrLen file)
 {
  HomeFile home_file(dir,file);

  if( home_file.exist() ) loadDDL(home_file.get());
 }

void FontReplaceMap::save(StrLen dir,StrLen file) const
 {
  HomeFile home_file(dir,file);

  home_file.createDir();

  saveDDL(home_file.get());
 }

void FontReplaceMap::add(StrLen face,StrLen replace)
 {
  StrKey key(face);

  map.find_or_add(key,replace);
 }

FontReplaceMap::FontReplaceMap()
 {
 }

FontReplaceMap::~FontReplaceMap()
 {
 }

StrLen FontReplaceMap::operator () (StrLen face) const
 {
  StrKey key(face);

  if( const Rec *obj=map.find(key) )
    {
     if( StrLen ret=Range(obj->str) ; +ret ) return ret;
    }

  return face;
 }

void FontReplaceMap::addNotFound(StrLen face)
 {
  StrKey key(face);

  map.find_or_add(key);

  modified=true;
 }

void FontReplaceMap::load() noexcept
 {
  try { load(HomeKey(),ReplaceFile()); } catch(...) {}

  modified=true;
 }

void FontReplaceMap::save() const noexcept
 {
  try { save(HomeKey(),ReplaceFile()); } catch(...) {}
 }

auto FontReplaceMap::find(StrLen face) const -> FindResult
 {
  StrKey key(face);

  if( const Rec *obj=map.find(key) ) return {Range(obj->str),obj->index};

  return {};
 }

void FontReplaceMap::del(StrLen face)
 {
  StrKey key(face);

  map.del(key);
 }

ulen FontReplaceMap::set(StrLen face,String replace)
 {
  StrKey key(face);

  auto result=map.find_or_add(key,replace);

  if( result.new_flag )
    {
     return MaxULen;
    }
  else
    {
     result.obj->str=replace;

     return result.obj->index;
    }
 }

/* class FontMapWindow::InfoBase */

FontMapWindow::Rec::Rec(StrLen face_,StrLen replace_)
 {
  text=StringCat(face_," -> "_c,replace_);

  face=face_.len;
  replace=replace_.len;
 }

void FontMapWindow::Rec::update(StrLen replace_)
 {
  String text_=StringCat(getFace()," -> "_c,replace_);

  text=text_;

  replace=replace_.len;
 }

class FontMapWindow::InfoBase : public ComboInfoBase
 {
   DynArray<Rec> list;

  private:

   void add(StrLen face,StrLen replace);

  public:

   InfoBase() noexcept;

   explicit InfoBase(FontReplaceMap &map);

   virtual ~InfoBase();

   // AbstractComboInfo

   virtual ulen getLineCount() const;

   virtual ComboInfoItem getLine(ulen index) const;

   // methods

   Rec get(ulen index) const;

   void update(ulen index,StrLen replace);
 };

void FontMapWindow::InfoBase::add(StrLen face,StrLen replace)
 {
  list.append_fill(face,replace);
 }

FontMapWindow::InfoBase::InfoBase() noexcept
 {
 }

FontMapWindow::InfoBase::InfoBase(FontReplaceMap &map)
 {
  list.erase();

  struct Temp
   {
    StrLen face;
    StrLen replace;
    ulen *index;

    Temp(StrLen face_,StrLen replace_,ulen *index_) : face(face_),replace(replace_),index(index_) {}

    bool operator < (const Temp &obj) const { return StrLess(face,obj.face); }

    void set(ulen ind) { *index=ind; }
   };

  DynArray<Temp> temp(DoReserve,map.getCount());

  map.apply( [&] (StrLen face,StrLen replace,ulen &index) { temp.append_fill(face,replace,&index); } );

  auto r=Range(temp);

  Sort(r);

  list.reserve(r.len);

  for(ulen i : IndLim(r.len) )
    {
     auto &obj=r[i];

     obj.set(i);

     add(obj.face,obj.replace);
    }
 }

FontMapWindow::InfoBase::~InfoBase()
 {
 }

ulen FontMapWindow::InfoBase::getLineCount() const
 {
  return list.getLen();
 }

ComboInfoItem FontMapWindow::InfoBase::getLine(ulen index) const
 {
  return list.at(index).item();
 }

auto FontMapWindow::InfoBase::get(ulen index) const -> Rec
 {
  return list.at(index);
 }

void FontMapWindow::InfoBase::update(ulen index,StrLen replace)
 {
  list.at(index).update(replace);
 }

/* class FontMapWindow */

FontMapWindow::Info::Info()
 : ComboInfo(new InfoBase())
 {
 }

FontMapWindow::Info::Info(FontReplaceMap &map)
 : ComboInfo(new InfoBase(map))
 {
 }

FontMapWindow::Info::~Info()
 {
 }

auto FontMapWindow::Info::get(ulen index) const -> Rec
 {
  InfoBase *base=castPtr<InfoBase>();

  return base->get(index);
 }

void FontMapWindow::Info::update(ulen index,StrLen replace)
 {
  InfoBase *base=castPtr<InfoBase>();

  base->update(index,replace);
 }

void FontMapWindow::updatePreserve()
 {
  ulen sel=getSelect();

  info=Info(map);

  setInfo(info);

  if( sel!=MaxULen ) select(sel);

  ping();
 }

void FontMapWindow::set(ulen index)
 {
  auto rec=info.get(index);

  selected.assert(rec.getFace(),rec.getReplace());
 }

FontMapWindow::FontMapWindow(SubWindowHost &host,const Config &cfg,FontReplaceMap &map_)
 : ScrollListWindow(host,cfg),

   map(map_),

   connector_selected(this,&FontMapWindow::set,ScrollListWindow::selected)
 {
 }

FontMapWindow::~FontMapWindow()
 {
 }

 // methods

void FontMapWindow::update()
 {
  info=Info(map);

  setInfo(info);

  ping();
 }

StrLen FontMapWindow::find(StrLen face)
 {
  auto result=map.find(face);

  if( result.index!=MaxULen ) select(result.index);

  return result.str;
 }

void FontMapWindow::del(StrLen face)
 {
  map.del(face);

  updatePreserve();
 }

void FontMapWindow::set(StrLen face,String replace)
 {
  if( ulen index=map.set(face,replace) ; index==MaxULen )
    {
     updatePreserve();
    }
  else
    {
     info.update(index,Range(replace));

     ScrollListWindow::update();

     select(index);
    }
 }

/* class FontSelectWindow */

void FontSelectWindow::selectFont()
 {
  selected.assert(GetFontFamily(fontedit.getFont()));
 }

FontSelectWindow::FontSelectWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   btn_select(wlist,cfg.btn_cfg,cfg.text_Select),
   fontedit(wlist,cfg.fontedit_cfg),

   btn_pressed(this,&FontSelectWindow::selectFont,btn_select.pressed)
 {
  wlist.insTop(btn_select,fontedit);
 }

FontSelectWindow::~FontSelectWindow()
 {
 }

 // methods

Point FontSelectWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToTop lay{LayCenterX(btn_select),Lay(fontedit)};

  return lay.getMinSize(space);
 }

 // drawing

void FontSelectWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToTop lay{LayCenterX(btn_select),Lay(fontedit)};

  ExtLay(lay).setPlace(getPane(),space);
 }

void FontSelectWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

 // user input

void FontSelectWindow::react(UserAction action)
 {
  wlist.react(action);
 }

/* class FontSelectFrame */

FontSelectFrame::FontSelectFrame(Desktop *desktop,const Config &cfg,Signal<> &update)
 : FrameOf<FontSelectWindow>(desktop,cfg,update),

   selected(client.selected)
 {
 }

FontSelectFrame::~FontSelectFrame()
 {
 }

/* class FontReplaceWindow */

void FontReplaceWindow::findFace()
 {
  edit_replace.setText(map.find(cache_face.getText()));
 }

void FontReplaceWindow::delEntry()
 {
  map.del(cache_face.getText());
 }

void FontReplaceWindow::replaceFace()
 {
  map.set(cache_face.getText(),edit_replace.getString());
 }

void FontReplaceWindow::saveMap()
 {
  map.save();
 }

void FontReplaceWindow::applyMap()
 {
  apply.assert();
 }

void FontReplaceWindow::setEdit(StrLen face,StrLen replace)
 {
  edit_face.setText(face);
  edit_replace.setText(replace);
 }

void FontReplaceWindow::openFont()
 {
  if( select_frame.isDead() ) select_frame.create(getFrame());
 }

void FontReplaceWindow::fontSelected(StrLen replace)
 {
  map.set(cache_face.getText(),replace);

  edit_replace.setText(replace);
 }

FontReplaceWindow::FontReplaceWindow(SubWindowHost &host,const Config &cfg_,FontReplaceMap &map_,Signal<> &update)
 : ComboWindow(host),
   cfg(cfg_),

   btn_find(wlist,cfg.btn_cfg,cfg.text_Find),
   edit_face(wlist,cfg.edit_cfg),
   knob_del(wlist,cfg.knob_cfg,KnobShape::FaceCross),

   btn_replace(wlist,cfg.btn_cfg,cfg.text_Replace),
   edit_replace(wlist,cfg.edit_cfg),
   knob_font(wlist,cfg.knob_cfg,KnobShape::FacePlus),

   map(wlist,cfg.map_cfg,map_),

   btn_save(wlist,cfg.btn_cfg,cfg.text_Save),
   btn_apply(wlist,cfg.btn_cfg,cfg.text_Apply),

   cache_face(edit_face),

   select_frame(host.getFrameDesktop(),cfg.select_cfg,update),

   connector_find_pressed(this,&FontReplaceWindow::findFace,btn_find.pressed),
   connector_del_pressed(this,&FontReplaceWindow::delEntry,knob_del.pressed),
   connector_replace_pressed(this,&FontReplaceWindow::replaceFace,btn_replace.pressed),
   connector_save_pressed(this,&FontReplaceWindow::saveMap,btn_save.pressed),
   connector_apply_pressed(this,&FontReplaceWindow::applyMap,btn_apply.pressed),

   connector_map_selected(this,&FontReplaceWindow::setEdit,map.selected),

   connector_font_pressed(this,&FontReplaceWindow::openFont,knob_font.pressed),
   connector_font_selected(this,&FontReplaceWindow::fontSelected,select_frame.selected)
 {
  wlist.insTop(btn_find,edit_face,knob_del,btn_replace,edit_replace,knob_font,map,btn_save,btn_apply);

  edit_face.hideInactiveCursor();
  edit_replace.hideInactiveCursor();
 }

FontReplaceWindow::~FontReplaceWindow()
 {
 }

 // methods

Point FontReplaceWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToLeftCenter lay1{Lay(knob_del),LayToRightCenter(Lay(btn_find),Lay(edit_face))};

  LayToLeftCenter lay2{Lay(knob_font),LayToRightCenter(Lay(btn_replace),Lay(edit_replace))};

  LayToBottom lay3{Lay(btn_save),LayTop(btn_apply)};

  LayToLeft lay4{lay3,LaySpecial(map,10)};

  LayToBottom lay{lay1,lay2,lay4};

  return ExtLay(lay).getMinSize(space);
 }

void FontReplaceWindow::update()
 {
  if( map.testModified() )
    {
     edit_face.setTextLen(0);
     edit_replace.setTextLen(0);

     map.update();
    }
 }

 // drawing

void FontReplaceWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToLeftCenter lay1{Lay(knob_del),LayToRightCenter(Lay(btn_find),Lay(edit_face))};

  LayToLeftCenter lay2{Lay(knob_font),LayToRightCenter(Lay(btn_replace),Lay(edit_replace))};

  LayToBottom lay3{Lay(btn_save),LayTop(btn_apply)};

  LayToLeft lay4{lay3,LaySpecial(map,10)};

  LayToBottom lay{lay1,lay2,lay4};

  ExtLay(lay).setPlace(getPane(),space);
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

FontReplaceFrame::FontReplaceFrame(Desktop *desktop,const Config &cfg,FontReplaceMap &map,Signal<> &update)
 : FrameOf<FontReplaceWindow>(desktop,cfg,update,map,update),

   apply(client.apply)
 {
 }

FontReplaceFrame::~FontReplaceFrame()
 {
 }

} // namespace Video
} // namespace CCore

