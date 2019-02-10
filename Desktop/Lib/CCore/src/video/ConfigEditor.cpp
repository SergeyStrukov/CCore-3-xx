/* ConfigEditor.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/video/ConfigEditor.h>

#include <CCore/inc/video/Layout.h>

namespace CCore {
namespace Video {

/* class ConfigEditorWindow::PrefInfo::Base */

class ConfigEditorWindow::PrefInfo::Base : public ComboInfoBase
 {
   enum VarType
    {
     Var_Title,
     Var_Separator,

     Var_Coord,
     Var_MCoord,
     Var_VColor,
     Var_Clr,
     Var_unsigned,
     Var_String,
     Var_Point,
     Var_Font,
     Var_bool,
     Var_Ratio,

     VarLim
    };

   struct Rec
    {
     String name;
     VarType type;

     union Ref
      {
       Coord      *of_Coord;
       Fraction   *of_MCoord;
       VColor     *of_VColor;
       Clr        *of_Clr;
       unsigned   *of_unsigned;
       String  *of_String;
       Point      *of_Point;
       FontCouple *of_Font;
       bool       *of_bool;
       Ratio      *of_Ratio;

       Ref() {}

       Ref(Coord &var) : of_Coord{&var} {}

       Ref(Fraction &var) : of_MCoord{&var} {}

       Ref(VColor &var) : of_VColor{&var} {}

       Ref(unsigned &var) : of_unsigned{&var} {}

       Ref(Clr &var) : of_Clr{&var} {}

       Ref(String &var) : of_String{&var} {}

       Ref(Point &var) : of_Point{&var} {}

       Ref(FontCouple &var) : of_Font{&var} {}

       Ref(bool &var) : of_bool{&var} {}

       Ref(Ratio &var) : of_Ratio{&var} {}
      };

     Ref ref;

     Rec() noexcept : type(Var_Separator) {}

     Rec(String name_) : name(name_),type(Var_Title) {}

     Rec(String name_,Coord &var)
      : name(name_),
        type(Var_Coord),
        ref(var)
      {
      }

     Rec(String name_,Fraction &var)
      : name(name_),
        type(Var_MCoord),
        ref(var)
      {
      }

     Rec(String name_,VColor &var)
      : name(name_),
        type(Var_VColor),
        ref(var)
      {
      }

     Rec(String name_,Clr &var)
      : name(name_),
        type(Var_Clr),
        ref(var)
      {
      }

     Rec(String name_,unsigned &var)
      : name(name_),
        type(Var_unsigned),
        ref(var)
      {
      }

     Rec(String name_,String &var)
      : name(name_),
        type(Var_String),
        ref(var)
      {
      }

     Rec(String name_,Point &var)
      : name(name_),
        type(Var_Point),
        ref(var)
      {
      }

     Rec(String name_,FontCouple &var)
      : name(name_),
        type(Var_Font),
        ref(var)
      {
      }

     Rec(String name_,bool &var)
      : name(name_),
        type(Var_bool),
        ref(var)
      {
      }

     Rec(String name_,Ratio &var)
      : name(name_),
        type(Var_Ratio),
        ref(var)
      {
      }

     template <class Func>
     void operator () (Func func)
      {
       switch( type )
         {
          case Var_Coord : func(*ref.of_Coord); break;

          case Var_MCoord : func(*ref.of_MCoord); break;

          case Var_VColor : func(*ref.of_VColor); break;

          case Var_Clr : func(*ref.of_Clr); break;

          case Var_unsigned : func(*ref.of_unsigned); break;

          case Var_String : func(*ref.of_String); break;

          case Var_Point : func(*ref.of_Point); break;

          case Var_Font : func(*ref.of_Font); break;

          case Var_bool : func(*ref.of_bool); break;

          case Var_Ratio : func(*ref.of_Ratio); break;
         }
      }
    };

   DynArray<Rec> list;

   bool en_all = true ;

   bool en[VarLim] = {} ;

   DynArray<Rec> sublist;

  private:

   void buildSubList()
    {
     sublist.erase();

     DynArray<Rec> temp;

     {
      bool item=false;

      for(const Rec &rec : list )
        switch( rec.type )
          {
           case Var_Title :
            {
             temp.append_copy(rec);

             item=false;
            }
           break;

           case Var_Separator :
            {
             if( item )
               {
                temp.append_copy(rec);

                item=false;
               }
            }
           break;

           default:
            {
             if( en[rec.type] )
               {
                temp.append_copy(rec);

                item=true;
               }
            }
          }
     }

     ulen len=temp.getLen();

     DynArray<bool> flag(len);

     {
      bool item=false;

      for(ulen i=len; i-- ;)
        switch( temp[i].type )
          {
           case Var_Title :
            {
             if( item )
               {
                flag[i]=true;

                item=false;
               }
            }
           break;

           case Var_Separator :
            {
             if( item )
               {
                flag[i]=true;

                item=false;
               }
            }
           break;

           default:
            {
             flag[i]=true;

             item=true;
            }
          }
     }

     {
      for(ulen i=0; i<len ;i++) if( flag[i] ) sublist.append_copy(temp[i]);
     }
    }

   template <class Func>
   static void Select(DynArray<Rec> &list,ulen index,Func func)
    {
     if( index<list.getLen() )
       {
        list[index](func);
       }
     else
       {
        func();
       }
    }

   static ComboInfoItem ToItem(const Rec &rec)
    {
     switch( rec.type )
       {
        case Var_Title : return {ComboInfoTitle,Range(rec.name)};

        case Var_Separator : return {ComboInfoSeparator,Empty};

        default: return {ComboInfoText,Range(rec.name)};
       }
    }

  public:

   Base() noexcept {}

   ~Base() {}

   // select

   template <class Func>
   void select(ulen index,Func func)
    {
     if( en_all )
       {
        Select(list,index,func);
       }
     else
       {
        Select(sublist,index,func);
       }
    }

   // add...()

   void addTitle(String name) { list.append_fill(name); }

   void addSeparator() { list.append_fill(); }

   void add(String name,Coord &var) { list.append_fill(name,var); }

   void add(String name,Fraction &var) { list.append_fill(name,var); }

   void add(String name,VColor &var) { list.append_fill(name,var); }

   void add(String name,Clr &var) { list.append_fill(name,var); }

   void add(String name,unsigned &var) { list.append_fill(name,var); }

   void add(String name,String &var) { list.append_fill(name,var); }

   void add(String name,Point &var) { list.append_fill(name,var); }

   void add(String name,FontCouple &var) { list.append_fill(name,var); }

   void add(String name,bool &var) { list.append_fill(name,var); }

   void add(String name,Ratio &var) { list.append_fill(name,var); }

   // enable...()

   bool enable_all(bool on)
    {
     if( Change(en_all,on) )
       {
        if( !on ) buildSubList();

        return true;
       }
     else
       {
        return false;
       }
    }

   bool enable(VarType type,bool on)
    {
     if( Change(en[type],on) )
       {
        if( en_all ) return false;

        buildSubList();

        return true;
       }
     else
       {
        return false;
       }
    }

   bool enable_Coord(bool on) { return enable(Var_Coord,on); }

   bool enable_MCoord(bool on) { return enable(Var_MCoord,on); }

   bool enable_VColor(bool on) { return enable(Var_VColor,on); }

   bool enable_Clr(bool on) { return enable(Var_Clr,on); }

   bool enable_unsigned(bool on) { return enable(Var_unsigned,on); }

   bool enable_String(bool on) { return enable(Var_String,on); }

   bool enable_Point(bool on) { return enable(Var_Point,on); }

   bool enable_Font(bool on) { return enable(Var_Font,on); }

   bool enable_bool(bool on) { return enable(Var_bool,on); }

   bool enable_Ratio(bool on) { return enable(Var_Ratio,on); }

   // AbstractComboInfo

   virtual ulen getLineCount() const
    {
     if( en_all )
       {
        return list.getLen();
       }
     else
       {
        return sublist.getLen();
       }
    }

   virtual ComboInfoItem getLine(ulen index) const
    {
     if( en_all )
       {
        return ToItem(list.at(index));
       }
     else
       {
        return ToItem(sublist.at(index));
       }
    }
 };

/* class ConfigEditorWindow::PrefInfo::Binder */

class ConfigEditorWindow::PrefInfo::Binder : public ConfigItemBind
 {
   Base *base;

  public:

   Binder(Base *base_) : base(base_) {}

   // ConfigItemBind

   virtual void group(String name) { base->addTitle(name); }

   virtual void space() { base->addSeparator(); }

   virtual void item(String name,Coord &var) { base->add(name,var); }

   virtual void item(String name,Fraction &var) { base->add(name,var); }

   virtual void item(String name,VColor &var) { base->add(name,var); }

   virtual void item(String name,Clr &var) { base->add(name,var); }

   virtual void item(String name,unsigned &var) { base->add(name,var); }

   virtual void item(String name,String &var) { base->add(name,var); }

   virtual void item(String name,Point &var) { base->add(name,var); }

   virtual void item(String name,FontCouple &var) { base->add(name,var); }

   virtual void item(String name,bool &var) { base->add(name,var); }

   virtual void item(String name,Ratio &var) { base->add(name,var); }
 };

/* class ConfigEditorWindow::PrefInfo */

auto ConfigEditorWindow::PrefInfo::getBase() -> Base *
 {
  return castPtr<Base>();
 }

ConfigEditorWindow::PrefInfo::PrefInfo()
 : ComboInfo(new Base)
 {
 }

ConfigEditorWindow::PrefInfo::~PrefInfo()
 {
 }

auto ConfigEditorWindow::PrefInfo::getBinder() -> Binder
 {
  return getBase();
 }

bool ConfigEditorWindow::PrefInfo::enable_all(bool on)
 {
  return getBase()->enable_all(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_Coord(bool on)
 {
  return getBase()->enable_Coord(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_MCoord(bool on)
 {
  return getBase()->enable_MCoord(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_VColor(bool on)
 {
  return getBase()->enable_VColor(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_Clr(bool on)
 {
  return getBase()->enable_Clr(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_unsigned(bool on)
 {
  return getBase()->enable_unsigned(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_String(bool on)
 {
  return getBase()->enable_String(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_Point(bool on)
 {
  return getBase()->enable_Point(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_Font(bool on)
 {
  return getBase()->enable_Font(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_bool(bool on)
 {
  return getBase()->enable_bool(on);
 }

bool ConfigEditorWindow::PrefInfo::enable_Ratio(bool on)
 {
  return getBase()->enable_Ratio(on);
 }

template <class Func>
void ConfigEditorWindow::PrefInfo::select(ulen index,Func func)
 {
  getBase()->select(index,func);
 }

/* class ConfigEditorWindow */

void ConfigEditorWindow::switchTo(SubWindow *editor,BackSet *backset)
 {
  active_backset=backset;

  if( active_editor!=editor )
    {
     if( active_editor ) wlist.del(active_editor);

     SubWindow *focus=wlist.getFocus();

     active_editor=editor;

     if( editor ) wlist.insBottom(editor);

     if( !focus ) focus=editor;

     if( focus ) focus->setFocus();

     redraw();
    }
 }

void ConfigEditorWindow::newList()
 {
  item_list.setInfo(info);

  selectVar(item_list.getSelect());

  layout();

  redraw();
 }

 // dragged

void ConfigEditorWindow::split_dragged(Point delta)
 {
  if( min_list_dx<=max_list_dx )
    {
     list_split_dx=Cap<Coord>(min_list_dx,list_split_dx+delta.x,max_list_dx);

     split_on=true;

     layout();

     redraw();
    }
 }

 // enable

void ConfigEditorWindow::enable_all(bool on)
 {
  if( info.enable_all(on) ) newList();
 }

void ConfigEditorWindow::enable_Coord(bool on)
 {
  if( info.enable_Coord(on) ) newList();
 }

void ConfigEditorWindow::enable_MCoord(bool on)
 {
  if( info.enable_MCoord(on) ) newList();
 }

void ConfigEditorWindow::enable_VColor(bool on)
 {
  if( info.enable_VColor(on) ) newList();
 }

void ConfigEditorWindow::enable_Clr(bool on)
 {
  if( info.enable_Clr(on) ) newList();
 }

void ConfigEditorWindow::enable_unsigned(bool on)
 {
  if( info.enable_unsigned(on) ) newList();
 }

void ConfigEditorWindow::enable_String(bool on)
 {
  if( info.enable_String(on) ) newList();
 }

void ConfigEditorWindow::enable_Point(bool on)
 {
  if( info.enable_Point(on) ) newList();
 }

void ConfigEditorWindow::enable_Font(bool on)
 {
  if( info.enable_Font(on) ) newList();
 }

void ConfigEditorWindow::enable_bool(bool on)
 {
  if( info.enable_bool(on) ) newList();
 }

void ConfigEditorWindow::enable_Ratio(bool on)
 {
  if( info.enable_Ratio(on) ) newList();
 }

 // buttons

void ConfigEditorWindow::setPref()
 {
  if( active_backset ) active_backset->set();

  btn_Set.disable();
  btn_Back.disable();
 }

void ConfigEditorWindow::backPref()
 {
  if( active_backset )
    {
     if( active_backset->back() )
       {
        btn_Save.enable();

        updated.assert();
       }
    }

  btn_Set.disable();
  btn_Back.disable();
 }

void ConfigEditorWindow::savePref()
 {
  setPref();

  btn_Save.disable();

  doSave.assert();
 }

void ConfigEditorWindow::selfPref()
 {
  setPref();

  doSelf.assert();
 }

 // select

void ConfigEditorWindow::select(Coord &var)
 {
  coord_pad.bind(var);

  switchTo(coord_edit,coord_pad);
 }

void ConfigEditorWindow::select(Fraction &var)
 {
  mcoord_pad.bind(var.value);

  switchTo(mcoord_edit,mcoord_pad);
 }

void ConfigEditorWindow::select(VColor &var)
 {
  color_pad.bind(var);

  switchTo(color_edit,color_pad);
 }

void ConfigEditorWindow::select(Clr &var)
 {
  clr_pad.bind(var);

  switchTo(clr_edit,clr_pad);
 }

void ConfigEditorWindow::select(unsigned &var)
 {
  unsigned_pad.bind(var);

  switchTo(unsigned_edit,unsigned_pad);
 }

void ConfigEditorWindow::select(String &var)
 {
  string_pad.bind(var);

  switchTo(string_edit,string_pad);
 }

void ConfigEditorWindow::select(Point &var)
 {
  point_pad.bind(var);

  switchTo(point_edit,point_pad);
 }

void ConfigEditorWindow::select(FontCouple &var)
 {
  font_pad.bind(var);

  switchTo(font_edit,font_pad);
 }

void ConfigEditorWindow::select(bool &var)
 {
  bool_pad.bind(var);

  switchTo(bool_edit,bool_pad);
 }

void ConfigEditorWindow::select(Ratio &var)
 {
  ratio_pad.bind(var);

  switchTo(ratio_edit,ratio_pad);
 }

void ConfigEditorWindow::select()
 {
  switchTo(0);
 }

struct ConfigEditorWindow::FuncSelect
 {
  ConfigEditorWindow *obj;

  template <class ... TT>
  void operator () (TT & ... var) { obj->select(var...); }
 };

void ConfigEditorWindow::selectVar(ulen index)
 {
  backPref();

  info.select(index,FuncSelect{this});
 }

 // changed

void ConfigEditorWindow::changed()
 {
  btn_Set.enable();
  btn_Back.enable();
  btn_Save.enable();

  updated.assert();
 }

void ConfigEditorWindow::string_edit_changed()
 {
  if( string_pad.update(string_edit.getString()) ) changed();
 }

void ConfigEditorWindow::coord_edit_changed(Coord value)
 {
  if( coord_pad.update(value) ) changed();
 }

void ConfigEditorWindow::mcoord_edit_changed(MCoord value)
 {
  if( mcoord_pad.update(value) ) changed();
 }

void ConfigEditorWindow::font_edit_changed()
 {
  if( font_pad.update(font_edit.getCouple()) ) changed();
 }

void ConfigEditorWindow::unsigned_edit_changed(int value)
 {
  if( unsigned_pad.update((unsigned)value) ) changed();
 }

void ConfigEditorWindow::clr_edit_changed(int value)
 {
  if( clr_pad.update((Clr)value) ) changed();
 }

void ConfigEditorWindow::point_edit_changed(Point value)
 {
  if( point_pad.update(value) ) changed();
 }

void ConfigEditorWindow::color_edit_changed(VColor value)
 {
  if( color_pad.update(value) ) changed();
 }

void ConfigEditorWindow::bool_edit_changed(bool value)
 {
  if( bool_pad.update(value) ) changed();
 }

void ConfigEditorWindow::ratio_edit_changed(Ratio value)
 {
  if( ratio_pad.update(value) ) changed();
 }

 // constructors

ConfigEditorWindow::ConfigEditorWindow(SubWindowHost &host,const Config &cfg_,bool use_self_)
 : ComboWindow(host),
   cfg(cfg_),
   use_self(use_self_),

   item_list(wlist,cfg.list_cfg),

   check_all(wlist,cfg.check_cfg,true),
   check_Coord(wlist,cfg.check_cfg),
   check_MCoord(wlist,cfg.check_cfg),
   check_VColor(wlist,cfg.check_cfg),
   check_Clr(wlist,cfg.check_cfg),
   check_unsigned(wlist,cfg.check_cfg),
   check_String(wlist,cfg.check_cfg),
   check_Point(wlist,cfg.check_cfg),
   check_Font(wlist,cfg.check_cfg),
   check_bool(wlist,cfg.check_cfg),
   check_Ratio(wlist,cfg.check_cfg),

   label_all(wlist,cfg.label_cfg,cfg.text_all,AlignX_Left),
   label_Coord(wlist,cfg.label_cfg,cfg.text_Coord,AlignX_Left),
   label_MCoord(wlist,cfg.label_cfg,cfg.text_MCoord,AlignX_Left),
   label_VColor(wlist,cfg.label_cfg,cfg.text_VColor,AlignX_Left),
   label_Clr(wlist,cfg.label_cfg,cfg.text_Clr,AlignX_Left),
   label_unsigned(wlist,cfg.label_cfg,cfg.text_unsigned,AlignX_Left),
   label_String(wlist,cfg.label_cfg,cfg.text_String,AlignX_Left),
   label_Point(wlist,cfg.label_cfg,cfg.text_Point,AlignX_Left),
   label_Font(wlist,cfg.label_cfg,cfg.text_Font,AlignX_Left),
   label_bool(wlist,cfg.label_cfg,cfg.text_bool,AlignX_Left),
   label_Ratio(wlist,cfg.label_cfg,cfg.text_Ratio,AlignX_Left),

   btn_Set(wlist,cfg.btn_cfg,cfg.text_Set),
   btn_Back(wlist,cfg.btn_cfg,cfg.text_Back),
   btn_Save(wlist,cfg.btn_cfg,cfg.text_Save),
   btn_Self(wlist,cfg.btn_cfg,cfg.text_Self),

   split(wlist,cfg.split_cfg),

   string_edit(wlist,cfg.edit_cfg),
   string_pad(string_edit),

   coord_edit(wlist,cfg.coord_cfg),
   coord_pad(coord_edit),

   mcoord_edit(wlist,cfg.mcoord_cfg),
   mcoord_pad(mcoord_edit),

   font_edit(wlist,cfg.font_cfg),
   font_pad(font_edit),

   unsigned_edit(wlist,cfg.spinor_cfg),
   unsigned_pad(unsigned_edit),

   clr_edit(wlist,cfg.spinor_cfg),
   clr_pad(clr_edit),

   point_edit(wlist,cfg.point_cfg),
   point_pad(point_edit),

   color_edit(wlist,cfg.color_cfg),
   color_pad(color_edit),

   bool_edit(wlist,cfg.check_cfg),
   bool_pad(bool_edit),

   ratio_edit(wlist,cfg.ratio_cfg),
   ratio_pad(ratio_edit),

   connector_split_dragged(this,&ConfigEditorWindow::split_dragged,split.dragged),

   connector_check_all_changed(this,&ConfigEditorWindow::enable_all,check_all.changed),
   connector_check_Coord_changed(this,&ConfigEditorWindow::enable_Coord,check_Coord.changed),
   connector_check_MCoord_changed(this,&ConfigEditorWindow::enable_MCoord,check_MCoord.changed),
   connector_check_VColor_changed(this,&ConfigEditorWindow::enable_VColor,check_VColor.changed),
   connector_check_Clr_changed(this,&ConfigEditorWindow::enable_Clr,check_Clr.changed),
   connector_check_unsigned_changed(this,&ConfigEditorWindow::enable_unsigned,check_unsigned.changed),
   connector_check_String_changed(this,&ConfigEditorWindow::enable_String,check_String.changed),
   connector_check_Point_changed(this,&ConfigEditorWindow::enable_Point,check_Point.changed),
   connector_check_Font_changed(this,&ConfigEditorWindow::enable_Font,check_Font.changed),
   connector_check_bool_changed(this,&ConfigEditorWindow::enable_bool,check_bool.changed),
   connector_check_Ratio_changed(this,&ConfigEditorWindow::enable_Ratio,check_Ratio.changed),

   connector_btnSet_pressed(this,&ConfigEditorWindow::setPref,btn_Set.pressed),
   connector_btnBack_pressed(this,&ConfigEditorWindow::backPref,btn_Back.pressed),
   connector_btnSave_pressed(this,&ConfigEditorWindow::savePref,btn_Save.pressed),
   connector_btnSelf_pressed(this,&ConfigEditorWindow::selfPref,btn_Self.pressed),

   connector_item_list_selected(this,&ConfigEditorWindow::selectVar,item_list.selected),

   connector_string_edit_changed(this,&ConfigEditorWindow::string_edit_changed,string_edit.changed),
   connector_coord_edit_changed(this,&ConfigEditorWindow::coord_edit_changed,coord_edit.changed),
   connector_mcoord_edit_changed(this,&ConfigEditorWindow::mcoord_edit_changed,mcoord_edit.changed),
   connector_font_edit_changed(this,&ConfigEditorWindow::font_edit_changed,font_edit.changed),
   connector_unsigned_edit_changed(this,&ConfigEditorWindow::unsigned_edit_changed,unsigned_edit.changed),
   connector_clr_edit_changed(this,&ConfigEditorWindow::clr_edit_changed,clr_edit.changed),
   connector_point_edit_changed(this,&ConfigEditorWindow::point_edit_changed,point_edit.changed),
   connector_color_edit_changed(this,&ConfigEditorWindow::color_edit_changed,color_edit.changed),
   connector_bool_edit_changed(this,&ConfigEditorWindow::bool_edit_changed,bool_edit.changed),
   connector_ratio_edit_changed(this,&ConfigEditorWindow::ratio_edit_changed,ratio_edit.changed)
 {
  wlist.insTop(item_list,check_all,check_Coord,check_MCoord,check_VColor,check_Clr,
                         check_unsigned,check_String,check_Point,check_Font,check_bool,check_Ratio,
                         label_all,label_Coord,label_MCoord,label_VColor,label_Clr,
                         label_unsigned,label_String,label_Point,label_Font,label_bool,label_Ratio,
                         btn_Set,btn_Back,btn_Save,split);

  if( use_self ) wlist.insBottom(btn_Self);

  btn_Set.disable();
  btn_Back.disable();
  btn_Save.disable();

  unsigned_edit.setRange(0,10'000);
  clr_edit.setRange(0,MaxClr);

  // bind hints

  item_list.bindHint(cfg.hint_list);

  btn_Set.bindHint(cfg.hint_Set);
  btn_Back.bindHint(cfg.hint_Back);
  btn_Save.bindHint(cfg.hint_Save);
  btn_Self.bindHint(cfg.hint_Self);
 }

ConfigEditorWindow::~ConfigEditorWindow()
 {
 }

 // methods

Point ConfigEditorWindow::getMinSize(Point cap) const
 {
  Coord space=+cfg.space_dxy;

  Point m;

  {
   Coord check_dxy=check_all.getMinSize().dxy;

   Coord ex=BoxExt(check_dxy);

   Point s1=SupMinSize(label_all,label_Coord,label_MCoord,label_VColor,label_Clr,
                       label_unsigned,label_String,label_Point,label_Font,label_bool,label_Ratio);

   Point s2=SupMinSize(btn_Save,btn_Self,btn_Set,btn_Back);

   Coord dx=Sup(ex+s1.x,s2.x);
   Coord dy=14*space+4*s2.y+11*Sup(check_dxy,s1.y);

   m=Point(dx,dy);
  }

  Point t=SupMinSize(color_edit,string_edit,coord_edit,
                     mcoord_edit,unsigned_edit,clr_edit,point_edit,
                     bool_edit,ratio_edit);

  t=Sup(t,font_edit.getMinSize(Point(MaxCoord,cap.y-2*space)));

  Coord ex=split.getMinSize().dx;

  Point delta(3*space+m.x+t.x+ex,2*space);

  Point s=item_list.getMinSize(cap-delta);

  return delta+Point( s.x , Sup(s.y,m.y,t.y) );
 }

void ConfigEditorWindow::bindConfig(ConfigItemHost &host)
 {
  auto binder=info.getBinder();

  host.bind(binder);

  newList();
 }

 // drawing

void ConfigEditorWindow::layout()
 {
  Coord space=+cfg.space_dxy;
  PaneCut pane(getSize(),space);

  pane.shrink();

  // item_list

  {
   auto item__list=CutPoint(item_list);

   Coord len=item__list.getMinSize().x;

   min_list_dx=len/2;
   max_list_dx=pane.getSize().x/2;

   if( split_on )
     {
      pane.place_cutLeft(item__list,list_split_dx);
     }
   else
     {
      list_split_dx=len;

      pane.place_cutLeft(item__list);
     }
  }

  // checks labels buttons

  {
   Coord check_dxy=check_all.getMinSize().dxy;

   auto label__all=CutPoint(label_all);
   auto label__Coord=CutPoint(label_Coord);
   auto label__MCoord=CutPoint(label_MCoord);
   auto label__VColor=CutPoint(label_VColor);
   auto label__Clr=CutPoint(label_Clr);
   auto label__unsigned=CutPoint(label_unsigned);
   auto label__String=CutPoint(label_String);
   auto label__Point=CutPoint(label_Point);
   auto label__Font=CutPoint(label_Font);
   auto label__bool=CutPoint(label_bool);
   auto label__Ratio=CutPoint(label_Ratio);

   Point label_size=SupMinSize(label__all,label__Coord,label__MCoord,label__VColor,label__Clr,
                               label__unsigned,label__String,label__Point,label__Font,label__bool,label__Ratio);

   auto btn__Set=CutPoint(btn_Set);
   auto btn__Back=CutPoint(btn_Back);
   auto btn__Save=CutPoint(btn_Save);
   auto btn__Self=CutPoint(btn_Self);

   Coord dx=Max(IntAdd(BoxExt(check_dxy),label_size.x),SupDX(btn__Save,btn__Self,btn__Set,btn__Back));

   PaneCut p=pane.cutLeft(dx);

   Coord dy=Max(check_dxy,label_size.y);

   p.cutTop(dy).place_cutLeft(check_all).place_cutLeft(label__all);
   p.cutTop(dy).place_cutLeft(check_Coord).place_cutLeft(label__Coord);
   p.cutTop(dy).place_cutLeft(check_MCoord).place_cutLeft(label__MCoord);
   p.cutTop(dy).place_cutLeft(check_VColor).place_cutLeft(label__VColor);
   p.cutTop(dy).place_cutLeft(check_Clr).place_cutLeft(label__Clr);
   p.cutTop(dy).place_cutLeft(check_unsigned).place_cutLeft(label__unsigned);
   p.cutTop(dy).place_cutLeft(check_String).place_cutLeft(label__String);
   p.cutTop(dy).place_cutLeft(check_Point).place_cutLeft(label__Point);
   p.cutTop(dy).place_cutLeft(check_Font).place_cutLeft(label__Font);
   p.cutTop(dy).place_cutLeft(check_bool).place_cutLeft(label__bool);
   p.cutTop(dy).place_cutLeft(check_Ratio).place_cutLeft(label__Ratio);

   Point btn_size=SupMinSize(btn__Set,btn__Back,btn__Save);

   p.place_cutTopLeft(btn__Set,btn_size);
   p.place_cutTopLeft(btn__Back,btn_size);
   p.place_cutTopLeft(btn__Save,btn_size);

   if( use_self ) p.place_cutBottomLeft(btn__Self);
  }

  // split

  pane.place_cutLeft(split);

  // font_edit

  pane.place(font_edit);

  // color_edit

  pane.place(color_edit);

  // point_edit

  pane.place(point_edit);

  // string_edit

  pane.dup().place_cutTop(string_edit);

  // bool_edit

  pane.placeMin(bool_edit);

  // unsigned_edit

  pane.placeMin(unsigned_edit);

  // clr_edit

  pane.placeMin(clr_edit);

  // coord_edit

  pane.placeMin(coord_edit);

  // mcoord_edit

  pane.placeMin(mcoord_edit);

  // ratio_edit

  pane.placeMin(ratio_edit);
 }

void ConfigEditorWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

/* class ConfigEditorFrame */

ConfigEditorFrame::ConfigEditorFrame(Desktop *desktop,const Config &cfg_,bool use_self)
 : DragFrame(desktop,cfg_.frame_cfg),
   cfg(cfg_),

   client(*this,cfg_.editor_cfg,use_self),

   updated(client.updated),
   doSave(client.doSave),
   doSelf(client.doSelf)
 {
  bindClient(client);
 }

ConfigEditorFrame::~ConfigEditorFrame()
 {
 }

 // create

Pane ConfigEditorFrame::getPane(StrLen title,Point base) const
 {
  Point screen_size=getScreenSize();

  Point cap=Div(9,10)*screen_size-getDeltaSize();

  Point size=getMinSize(false,title,client.getMinSize(cap));

  return FitToScreen(base,size,screen_size);
 }

Pane ConfigEditorFrame::getPane(bool is_main,StrLen title) const
 {
  Point screen_size=getScreenSize();

  Point cap=Div(9,10)*screen_size-getDeltaSize();

  Point size=getMinSize(is_main,title,client.getMinSize(cap));

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

} // namespace Video
} // namespace CCore

