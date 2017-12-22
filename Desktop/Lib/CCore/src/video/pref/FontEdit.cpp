/* FontEdit.cpp */
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

#include <CCore/inc/video/pref/FontEdit.h>

#include <CCore/inc/video/LayoutCombo.h>
#include <CCore/inc/video/SmoothDrawArt.h>

#include <CCore/inc/Sort.h>

namespace CCore {
namespace Video {

#define DISABLE_NONSCALABLE

/* class CharTableWindow */

void CharTableWindow::startDrag(Point point)
 {
  drag=true;
  drag_base=point;

  captureMouse();
 }

void CharTableWindow::dragTo(Point point)
 {
  Point delta=Diff(drag_base,point);

  off-=delta;

  off.x=Cap<Coord>(0,off.x,max_off.x);
  off.y=Cap<Coord>(0,off.y,max_off.y);

  redraw();
 }

void CharTableWindow::endDrag(Point point)
 {
  dragTo(point);
  endDrag();
 }

void CharTableWindow::endDrag()
 {
  drag=false;
  releaseMouse();
 }

CharTableWindow::CharTableWindow(SubWindowHost &host,const Config &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
 }

CharTableWindow::~CharTableWindow()
 {
 }

 // methods

Point CharTableWindow::getMinSize(unsigned) const
 {
  const Font &font=cfg.font.get();

  FontSize fs=font->getSize();

  Coordinate cell_dxy=Cell(fs.dy);

  Coordinate len=16*cell_dxy;

  return Point(len,len);
 }

 // drawing

bool CharTableWindow::isGoodSize(Point size) const
 {
  return size>=getMinSize(0);
 }

void CharTableWindow::layout(unsigned)
 {
  const Font &font=cfg.font.get();

  FontSize fs=font->getSize();

  Coord cell_dxy=Cell(fs.dy);

  Coord len=16*cell_dxy+RoundUpLen(+cfg.width);

  Point size=getSize();

  max_off.x=PlusSub(len,size.x);
  max_off.y=PlusSub(len,size.y);

  Replace_min(off.x,max_off.x);
  Replace_min(off.y,max_off.y);
 }

void CharTableWindow::draw(DrawBuf buf,bool) const
 {
  MCoord width=+cfg.width;
  VColor text=+cfg.text;
  const Font &font=cfg.font.get();

  FontSize fs=font->getSize();

  Coord cell_dxy=Cell(fs.dy);

  buf.shift(-off);

  SmoothDrawArt art(buf);

  Coord len=16*cell_dxy;

  {
   Coord y=0;

   for(unsigned count=17; count ;count--,y+=cell_dxy)
     {
      Point a(0,y);
      Point b(len,y);

      Point c(y,0);
      Point d(y,len);

      art.path(width,text,a,b);
      art.path(width,text,c,d);
     }
  }

  {
   char ch=0;
   Coord y=0;

   for(unsigned cnt_y=16; cnt_y ;cnt_y--,y+=cell_dxy)
     {
      Coord x=0;

      for(unsigned cnt_x=16; cnt_x ;cnt_x--,x+=cell_dxy,ch++)
        {
#ifdef CCORE_UTF8

         Unicode uch=map.toUnicode(ch);

         font->text(buf,Pane(x,y,cell_dxy,cell_dxy),TextPlace(AlignX_Center,AlignY_Center),Single(uch),text);

#else

         font->text(buf,Pane(x,y,cell_dxy,cell_dxy),TextPlace(AlignX_Center,AlignY_Center),Single(ch),text);

#endif
        }
     }
  }
 }

 // base

void CharTableWindow::open()
 {
  off=Null;
  drag=false;
 }

 // keyboard

FocusType CharTableWindow::askFocus() const
 {
  return NoFocus;
 }

 // mouse

void CharTableWindow::looseCapture()
 {
  drag=false;
 }

MouseShape CharTableWindow::getMouseShape(Point,KeyMod) const
 {
  return ( max_off.x>0 || max_off.y>0 )?Mouse_SizeAll:Mouse_Arrow;
 }

 // user input

void CharTableWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void CharTableWindow::react_LeftClick(Point point,MouseKey)
 {
  if( !drag ) startDrag(point);
 }

void CharTableWindow::react_LeftUp(Point point,MouseKey)
 {
  if( drag ) endDrag(point);
 }

void CharTableWindow::react_Move(Point point,MouseKey mkey)
 {
  if( drag )
    {
     if( mkey&MouseKey_Left )
       dragTo(point);
     else
       endDrag(point);
    }
 }

/* class FontEditWindow */

FontEditWindow::ProgressControl::ProgressControl(WindowList &wlist_,ProgressWindow &window_)
 : wlist(wlist_),
   window(window_)
 {
 }

FontEditWindow::ProgressControl::~ProgressControl()
 {
 }

 // IncrementalProgress

void FontEditWindow::ProgressControl::start()
 {
  wlist.insTop(window);
 }

void FontEditWindow::ProgressControl::setTotal(unsigned total)
 {
  window.setTotal(total);
 }

bool FontEditWindow::ProgressControl::setPos(unsigned pos)
 {
  window.setPosPing(pos);

  return true;
 }

void FontEditWindow::ProgressControl::stop() noexcept
 {
  wlist.del(window);
 }

/* class FontEditWindow::FDBInfo::Base */

class FontEditWindow::FDBInfo::Base : public ComboInfoBase
 {
   struct Rec
    {
     DefString name;
     const FontInfo *info;

     Rec() noexcept : name("-- Default --"_def),info(0) {}

     explicit Rec(const FontInfo &obj)
      {
       name=StringCat(obj.family," ",obj.style);

       info=&obj;
      }

     bool testFileName(StrLen file_name) const
      {
       return file_name.equal(Range(info->file_name));
      }

     bool operator < (const Rec &obj) const { return StrLess(name.str(),obj.name.str()); }
    };

   DynArray<Rec> list;

  public:

   Base() {}

   virtual ~Base() {}

   // methods

   void build(FontDatabase &fdb)
    {
     auto range=fdb.getList();

     list.erase();
     list.reserve(range.len+1);

     list.append_fill();

     for(const FontInfo &obj : range )
#ifdef DISABLE_NONSCALABLE
       if( obj.scalable )
#endif
         list.append_fill(obj);

     Sort(Range(list).part(1));
    }

   const FontInfo * get(ulen index) const
    {
     if( index<list.getLen() ) return list[index].info;

     return 0;
    }

   DefString getFamily(ulen index) const
    {
     if( index<list.getLen() ) return list[index].name;

     return Empty;
    }

   ulen getIndex(StrLen file_name) const
    {
     for(ulen index=1,count=list.getLen(); index<count ;index++)
       if( list[index].testFileName(file_name) )
         return index;

     return 0;
    }

   // AbstractComboInfo

   virtual ulen getLineCount() const
    {
     return list.getLen();
    }

   virtual ComboInfoItem getLine(ulen index) const
    {
     return {ComboInfoText,list.at(index).name.str()};
    }
 };

/* class FontEditWindow::FDBInfo */

auto FontEditWindow::FDBInfo::getBase() const -> Base *
 {
  return castPtr<Base>();
 }

FontEditWindow::FDBInfo::FDBInfo()
 : ComboInfo(new Base())
 {
 }

FontEditWindow::FDBInfo::~FDBInfo()
 {
 }

void FontEditWindow::FDBInfo::build(FontDatabase &fdb)
 {
  getBase()->build(fdb);
 }

const FontInfo * FontEditWindow::FDBInfo::get(ulen index) const
 {
  return getBase()->get(index);
 }

DefString FontEditWindow::FDBInfo::getFamily(ulen index) const
 {
  return getBase()->getFamily(index);
 }

ulen FontEditWindow::FDBInfo::getIndex(StrLen file_name) const
 {
  return getBase()->getIndex(file_name);
 }

/* class FontEditWindow */

DefString FontEditWindow::TestText()
 {
  return
   "Far over the misty mountains cold\n"
   "To dungeons deep and caverns old\n"
   "We must away ere break of day,\n"
   "To find our long-forgotten gold.\n"_def;
 }

int FontEditWindow::GetMaxIndex(Font font_)
 {
  try
    {
     FreeTypeFont font;

     (Font &)font=font_;

     int count = 0 ;

     auto temp=ToFunction<void (Coord dx,Coord dy)>( [&count] (Coord,Coord) { count++; } );

     font.getSizeList(temp.function());

     return (count>0)?count-1:0;
    }
  catch(...)
    {
     return 0;
    }
 };

void FontEditWindow::updateSample()
 {
  info_test.layout(LayoutUpdate);
  info_test.redraw();

  table.layout(LayoutUpdate);
  table.redraw();
 }

void FontEditWindow::updateFont()
 {
  font.create();

  changed.assert();

  updateSample();
 }

void FontEditWindow::showFont(ulen select)
 {
  if( const FontInfo *font_info=info.get(select) )
    {
     text_file_name.setText(font_info->file_name);
     text_family.setText(info.getFamily(select));

     light_scalable.turn(font_info->scalable);
     light_monospace.turn(font_info->monospace);
     light_bold.turn(font_info->bold);
     light_italic.turn(font_info->italic);
    }
  else
    {
     text_file_name.setText(+cfg.text_none);
     text_family.setText(info.getFamily(select));

     light_scalable.turn(false);
     light_monospace.turn(true);
     light_bold.turn(false);
     light_italic.turn(false);
    }
 }

void FontEditWindow::showFont()
 {
  text_file_name.setText(font.param.file_name);
  text_family.setText(+cfg.text_none);

  light_scalable.turn(false);
  light_monospace.turn(false);
  light_bold.turn(false);
  light_italic.turn(false);
 }

void FontEditWindow::noSize()
 {
  spin_fdy.disable();
  check_fdx.check(false);
  check_fdx.disable();
  spin_fdx.disable();
 }

void FontEditWindow::setSize()
 {
  switch( font.param.size_type )
    {
     case FontParam::SizeXY :
      {
       spin_fdy.enable();
       check_fdx.enable();
       spin_fdx.disable();

       spin_fdy.setRange(1,1000);
       spin_fdy.setValue(font.param.set_size.size_xy);

       check_fdx.check(false);
      }
     break;

     case FontParam::SizePoint :
      {
       spin_fdy.enable();
       check_fdx.enable();
       spin_fdx.enable();

       spin_fdy.setRange(1,1000);
       spin_fdy.setValue(font.param.set_size.size.y);

       check_fdx.check(true);

       spin_fdx.setValue(font.param.set_size.size.x);
      }
     break;

     case FontParam::SizeIndex :
      {
       spin_fdy.enable();
       check_fdx.check(false);
       check_fdx.disable();
       spin_fdx.disable();

       spin_fdy.setRange(0,GetMaxIndex(font.font));
       spin_fdy.setValue(font.param.set_size.index);
      }
     break;
    }
 }

void FontEditWindow::setConfig()
 {
  switch( font.param.cfg.fht )
    {
     default:
     case FontHintNone : radio_no_hint.check(); break;

     case FontHintNative : radio_native_hint.check(); break;

     case FontHintAuto : radio_auto_hint.check(); break;
    }

  switch( font.param.cfg.fsm )
    {
     default:
     case FontSmoothNone : radio_no_smooth.check(); break;

     case FontSmooth : radio_smooth.check(); break;

     case FontSmoothLCD_RGB : radio_RGB.check(); break;

     case FontSmoothLCD_BGR : radio_BGR.check(); break;
    }

  check_kerning.check(font.param.cfg.use_kerning);

  spin_strength.setValue(font.param.cfg.strength);
 }

void FontEditWindow::setCouple()
 {
  if( fdb_flag ) return;

  if( font.param.engine_type==FontParam::EngineDefault )
    {
     list.select(0);

     noSize();

     showFont(0);
    }
  else
    {
     if( ulen index=info.getIndex(Range(font.param.file_name)) )
       {
        list.select(index);

        setSize();

        showFont(index);
       }
     else
       {
        list.select(0);

        setSize();

        showFont();
       }
    }

  setConfig();

  updateSample();
 }

void FontEditWindow::split_dragged(Point delta)
 {
  if( min_list_dx<=max_list_dx )
    {
     list_split_dx=Cap<Coord>(min_list_dx,list_split_dx+delta.x,max_list_dx);

     split_on=true;

     layout(LayoutResize);

     redraw();
    }
 }

void FontEditWindow::fdb_completed(bool ok)
 {
  fdb_flag=false;

  if( ok )
    {
     info.build(fdb);

     list.setInfo(info);

     wlist.insTop(list,split,text_file_name,text_family,
                  light_scalable,light_monospace,light_bold,light_italic,
                  label_scalable,label_monospace,label_bold,label_italic,
                  line1,spin_fdy,check_fdx,spin_fdx,line2,
                  radio_no_hint,radio_native_hint,radio_auto_hint,
                  label_no_hint,label_native_hint,label_auto_hint,
                  contour_hint,
                  radio_no_smooth,radio_smooth,radio_RGB,radio_BGR,
                  label_no_smooth,label_smooth,label_RGB,label_BGR,
                  contour_smooth,
                  check_kerning,label_kerning,spin_strength,label_strength,line3,
                  radio_sample,label_sample,radio_table,label_table,
                  info_test,contour_test);

     setCouple();
    }
 }

void FontEditWindow::list_selected(ulen select)
 {
  bool def_size=true;

  if( font.param.engine_type==FontParam::EngineFreeType )
    {
     if( font.param.size_type!=FontParam::SizeIndex )
       {
        def_dy=Coord(spin_fdy.getValue());

        def_size=false;
       }
    }

  if( const FontInfo *font_info=info.get(select) )
    {
     font.param.engine_type=FontParam::EngineFreeType;

     font.param.file_name=font_info->file_name;

     if( font_info->scalable )
       {
        if( font.param.size_type==FontParam::SizeIndex || def_size )
          {
           font.param.size_type=FontParam::SizeXY;
           font.param.set_size.size_xy=def_dy;
          }
       }
     else
       {
        font.param.size_type=FontParam::SizeIndex;
        font.param.set_size.index=0;
       }

     setSize();
    }
  else
    {
     font.param.engine_type=FontParam::EngineDefault;

     noSize();
    }

  showFont(select);

  updateFont();
 }

void FontEditWindow::check_fdx_changed(bool enable)
 {
  switch( font.param.size_type )
    {
     case FontParam::SizeXY :
      {
       if( enable )
         {
          spin_fdx.enable();
          spin_fdx.setValue(spin_fdy.getValue());

          font.param.size_type=FontParam::SizePoint;
          font.param.set_size.size=Point(Coord(spin_fdx.getValue()),Coord(spin_fdy.getValue()));

          updateFont();
         }
      }
     break;

     case FontParam::SizePoint :
      {
       if( !enable )
         {
          spin_fdx.disable();

          font.param.size_type=FontParam::SizeXY;
          font.param.set_size.size_xy=Coord(spin_fdy.getValue());

          updateFont();
         }
      }
     break;
    }
 }

void FontEditWindow::spin_fdxy_changed(int)
 {
  switch( font.param.size_type )
    {
     case FontParam::SizeXY :
      {
       font.param.set_size.size_xy=Coord(spin_fdy.getValue());

       updateFont();
      }
     break;

     case FontParam::SizePoint :
      {
       font.param.set_size.size=Point(Coord(spin_fdx.getValue()),Coord(spin_fdy.getValue()));

       updateFont();
      }
     break;

     case FontParam::SizeIndex :
      {
       font.param.set_size.index=ulen(spin_fdy.getValue());

       updateFont();
      }
     break;
    }
 }

void FontEditWindow::group_hint_changed(int new_id,int)
 {
  font.param.cfg.fht=FontHintType(new_id);

  updateFont();
 }

void FontEditWindow::group_smooth_changed(int new_id,int)
 {
  font.param.cfg.fsm=FontSmoothType(new_id);

  updateFont();
 }

void FontEditWindow::check_kerning_changed(bool check)
 {
  font.param.cfg.use_kerning=check;

  updateFont();
 }

void FontEditWindow::spin_strength_changed(int strength)
 {
  font.param.cfg.strength=strength;

  updateFont();
 }

void FontEditWindow::group_sample_changed(int new_id,int)
 {
  switch( new_id )
    {
     case 0 :
      {
       wlist.del(table);

       wlist.insBefore(contour_test,info_test);

       layout(LayoutResize);
       redraw();
      }
     break;

     case 1 :
      {
       wlist.del(info_test);

       wlist.insBefore(contour_test,table);

       layout(LayoutResize);
       redraw();
      }
     break;
    }
 }

FontEditWindow::FontEditWindow(SubWindowHost &host,const ConfigType &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   progress(wlist,cfg.progress_cfg),
   progress_control(wlist,progress),

   fdb_inc(progress_control),

   list(wlist,cfg.list_cfg),
   split(wlist,cfg.split_cfg),

   text_file_name(wlist,cfg.text_cfg,AlignX_Left),
   text_family(wlist,cfg.text_cfg,AlignX_Left),

   light_scalable(wlist,cfg.light_cfg,Green),
   light_monospace(wlist,cfg.light_cfg,Green),
   light_bold(wlist,cfg.light_cfg,Green),
   light_italic(wlist,cfg.light_cfg,Green),

   label_scalable(wlist,cfg.label_cfg,cfg.text_scalable,AlignX_Left),
   label_monospace(wlist,cfg.label_cfg,cfg.text_monospace,AlignX_Left),
   label_bold(wlist,cfg.label_cfg,cfg.text_bold,AlignX_Left),
   label_italic(wlist,cfg.label_cfg,cfg.text_italic,AlignX_Left),

   line1(wlist,cfg.dline_cfg),

   spin_fdy(wlist,cfg.spin_cfg),
   check_fdx(wlist,cfg.check_cfg,false),
   spin_fdx(wlist,cfg.spin_cfg),

   line2(wlist,cfg.dline_cfg),

   radio_no_hint(wlist,FontHintNone,cfg.radio_cfg),
   radio_native_hint(wlist,FontHintNative,cfg.radio_cfg),
   radio_auto_hint(wlist,FontHintAuto,cfg.radio_cfg),

   label_no_hint(wlist,cfg.label_cfg,cfg.text_no_hint,AlignX_Left),
   label_native_hint(wlist,cfg.label_cfg,cfg.text_native_hint,AlignX_Left),
   label_auto_hint(wlist,cfg.label_cfg,cfg.text_auto_hint,AlignX_Left),

   contour_hint(wlist,cfg.text_contour_cfg,cfg.text_Hint),

   radio_no_smooth(wlist,FontSmoothNone,cfg.radio_cfg),
   radio_smooth(wlist,FontSmooth,cfg.radio_cfg),
   radio_RGB(wlist,FontSmoothLCD_RGB,cfg.radio_cfg),
   radio_BGR(wlist,FontSmoothLCD_BGR,cfg.radio_cfg),

   label_no_smooth(wlist,cfg.label_cfg,cfg.text_no_smooth,AlignX_Left),
   label_smooth(wlist,cfg.label_cfg,cfg.text_smooth,AlignX_Left),
   label_RGB(wlist,cfg.label_cfg,cfg.text_RGB,AlignX_Left),
   label_BGR(wlist,cfg.label_cfg,cfg.text_BGR,AlignX_Left),

   contour_smooth(wlist,cfg.text_contour_cfg,cfg.text_Smooth),

   check_kerning(wlist,cfg.check_cfg),

   label_kerning(wlist,cfg.label_cfg,cfg.text_kerning,AlignX_Left),

   spin_strength(wlist,cfg.spin_cfg),

   label_strength(wlist,cfg.label_cfg,cfg.text_strength,AlignX_Left),

   line3(wlist,cfg.dline_cfg),

   radio_sample(wlist,0,cfg.radio_cfg),
   radio_table(wlist,1,cfg.radio_cfg),

   label_sample(wlist,cfg.label_cfg,cfg.text_sample,AlignX_Left),
   label_table(wlist,cfg.label_cfg,cfg.text_table,AlignX_Left),

   info_cfg(cfg.info_cfg),

   info_test(wlist,info_cfg,InfoFromString(TestText())),

   table_cfg(cfg.table_cfg),

   table(wlist,table_cfg),

   contour_test(wlist,cfg.contour_cfg),

   connector_split_dragged(this,&FontEditWindow::split_dragged,split.dragged),
   connector_fdb_completed(this,&FontEditWindow::fdb_completed,fdb_inc.completed),
   connector_list_selected(this,&FontEditWindow::list_selected,list.selected),
   connector_check_fdx_changed(this,&FontEditWindow::check_fdx_changed,check_fdx.changed),
   connector_spin_fdy_changed(this,&FontEditWindow::spin_fdxy_changed,spin_fdy.changed),
   connector_spin_fdx_changed(this,&FontEditWindow::spin_fdxy_changed,spin_fdx.changed),
   connector_group_hint_changed(this,&FontEditWindow::group_hint_changed,group_hint.changed),
   connector_group_smooth_changed(this,&FontEditWindow::group_smooth_changed,group_smooth.changed),
   connector_check_kerning_changed(this,&FontEditWindow::check_kerning_changed,check_kerning.changed),
   connector_spin_strength_changed(this,&FontEditWindow::spin_strength_changed,spin_strength.changed),
   connector_group_sample_changed(this,&FontEditWindow::group_sample_changed,group_sample.changed)
 {
  spin_fdy.setRange(1,1000);
  spin_fdx.setRange(1,1000);

  spin_fdy.setValue(def_dy);
  spin_fdx.setValue(def_dy);

  spin_fdy.disable();
  check_fdx.disable();
  spin_fdx.disable();

  group_hint.add(radio_no_hint,radio_native_hint,radio_auto_hint);

  group_smooth.add(radio_no_smooth,radio_smooth,radio_RGB,radio_BGR);

  spin_strength.setRange(-1000,1000);

  group_sample.add(radio_sample,radio_table);

  info_cfg.font.bind(font.font);
  table_cfg.font.bind(font.font);

  // bind hints

  list.bindHint(cfg.hint_list);
  spin_fdy.bindHint(cfg.hint_height);
  check_fdx.bindHint(cfg.hint_length_enable);
  spin_fdx.bindHint(cfg.hint_length);
 }

FontEditWindow::~FontEditWindow()
 {
 }

 // methods

Point FontEditWindow::getMinSize(unsigned flags,Point cap) const
 {
  Coordinate space=+cfg.space_dxy;

  Point delta;

  {
   Coordinate dx;
   Coordinate dy;

   dy+=text_file_name.getMinSize(flags).y+space;
   dy+=text_family.getMinSize(flags).y+space;

   {
    Coord dxy=light_scalable.getMinSize(flags).dxy;

    Point s1=label_scalable.getMinSize(flags);
    Point s2=label_monospace.getMinSize(flags);
    Point s3=label_bold.getMinSize(flags);
    Point s4=label_italic.getMinSize(flags);

    dy+=Sup(s1.y,dxy)+2*space;

    Coordinate ex=BoxExt(dxy);

    dx=Sup(dx, 3*space+4*ex+s1.x+s2.x+s3.x+s4.x );
   }

   {
    Coord dxy=check_fdx.getMinSize(flags).dxy;

    Point s1=spin_fdy.getMinSize(flags);
    Point s2=spin_fdx.getMinSize(flags);

    dy+=Sup(s1.y,dxy)+2*space;

    Coordinate ex=BoxExt(dxy);

    dx=Sup(dx, space+ex+s1.x+s2.x );
   }

   Point delta1;

   {
    Coord dxy=radio_no_hint.getMinSize(flags).dxy;

    Point s1=label_no_hint.getMinSize(flags);
    Point s2=label_native_hint.getMinSize(flags);
    Point s3=label_auto_hint.getMinSize(flags);

    Coordinate line_dy=Sup(dxy,s1.y);

    Coordinate hint_dx=Sup(s1.x,s2.x,s3.x);

    Point size( BoxExt(dxy)+hint_dx+2*space , 3*line_dy+4*space );

    delta1=contour_hint.getMinSize(flags,size);
   }

   Point delta2;

   {
    Coord dxy=radio_no_smooth.getMinSize(flags).dxy;

    Point s1=label_no_smooth.getMinSize(flags);
    Point s2=label_smooth.getMinSize(flags);
    Point s3=label_RGB.getMinSize(flags);
    Point s4=label_BGR.getMinSize(flags);

    Coordinate line_dy=Sup(dxy,s1.y);

    Coordinate smooth_dx=Sup(s1.x,s2.x,s3.x,s4.x);

    Point size( BoxExt(dxy)+smooth_dx+2*space , 4*line_dy+5*space );

    delta2=contour_smooth.getMinSize(flags,size);
   }

   dy+=Sup(delta1.y,delta2.y)+space;

   dx=Sup(dx, space+delta1.x+delta2.x );

   {
    Coord dxy=check_kerning.getMinSize(flags).dxy;

    Point s=label_kerning.getMinSize(flags);

    dy+=Sup(s.y,dxy)+space;

    Coordinate ex=BoxExt(dxy);

    dx=Sup(dx, ex+s.x );
   }

   {
    Point s1=spin_strength.getMinSize(flags);
    Point s2=label_strength.getMinSize(flags);

    dy+=Sup(s1.y,s2.y)+space;

    dx=Sup(dx, s1.x+space+s2.x );
   }

   {
    Coord dxy=radio_sample.getMinSize(flags).dxy;

    Point s1=label_sample.getMinSize(flags);
    Point s2=label_table.getMinSize(flags);

    dy+=Sup(dxy,s1.y,s2.y)+2*space;

    Coordinate ex=BoxExt(dxy);

    dx=Sup(dx, s1.x+space+s2.x+2*ex );
   }

   dx+=2*space;
   dy+=space;

   delta=Point(dx,dy);
  }

  Point s=list.getMinSize(flags, Point(cap.x/3,cap.y) );

  return Point( 3*Sup( s.x , delta.x/2 ) , Sup(s.y,delta.y) );
 }

void FontEditWindow::setCouple(const FontCouple &font_)
 {
  font=font_;

  setCouple();
 }

 // drawing

void FontEditWindow::layout(unsigned flags)
 {
  Coord space=+cfg.space_dxy;

  PaneCut pane(getSize(),space,flags);

  // progress

  pane.dup().place_cutTop(progress,+cfg.progress_dy);

  // list , split

  {
   auto list__=CutPoint(list);

   Coord len=list__.getMinSize(flags).x;

   min_list_dx=len/4;
   max_list_dx=pane.getSize().x/2;

   if( split_on )
     {
      pane.place_cutLeft(list__,list_split_dx,0).place_cutLeft(split);
     }
   else
     {
      pane.place_cutLeft(list__,Div(1,3),0).place_cutLeft(split);

      list_split_dx=list.getSize().x;
     }
  }

  // lights

  LayToRight lay_lights(LayBox(light_scalable,label_scalable),
                        LayBox(light_monospace,label_monospace),
                        LayBox(light_bold,label_bold),
                        LayBox(light_italic,label_italic));

  // size spins

  LayAll lay1(spin_fdy);

  LayToRightCenter lay_spins(lay1,
                             LayBox(check_fdx,spin_fdx),
                             LayNull());

  // hint and smooth

  LayToBottomLeft lay_hint(LayBox(radio_no_hint,label_no_hint),
                           LayBox(radio_native_hint,label_native_hint),
                           LayBox(radio_auto_hint,label_auto_hint));

  LayToBottomLeft lay_smooth(LayBox(radio_no_smooth,label_no_smooth),
                             LayBox(radio_smooth,label_smooth),
                             LayBox(radio_RGB,label_RGB),
                             LayBox(radio_BGR,label_BGR));

  LayToRightTop lay_hint_smooth(LayInner(contour_hint,lay_hint),
                                LayInner(contour_smooth,lay_smooth),
                                LayNull());

  // text_file_name , text_family

  LayAll lay2(text_file_name);

  LayToBottom lay(lay2,
                  LayAll(text_family),
                  lay_lights,
                  LayAll(line1),
                  lay_spins,
                  LayAll(line2),
                  lay_hint_smooth,
                  LayBox(check_kerning,label_kerning),
                  LayToRightCenter(LayAll(spin_strength),LayAll(label_strength)),
                  LayAll(line3),
                  LayToRight(LayBox(radio_sample,label_sample),LayBox(radio_table,label_table)),
                  LayInner(contour_test,LaySame(LayAll(info_test),LayAll(table))));

  lay.setPlace(pane,flags,space);
 }

 // base

void FontEditWindow::open()
 {
  wlist.open();

  wlist.focusTop();

  if( fdb_flag )
    {
     fdb.cache(fdb_inc);
    }
 }

} // namespace Video
} // namespace CCore


