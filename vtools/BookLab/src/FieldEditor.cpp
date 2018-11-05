/* FieldEditor.cpp */
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

#include <inc/FieldEditor.h>

#include <CCore/inc/video/LayoutCombo.h>

namespace App {

/* class FieldBool */

FieldBool::FieldBool(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   check_true(wlist,cfg.check_cfg),
   lab_true(wlist,cfg.lab_cfg,"True"_def)
 {
  wlist.insTop(check_true,lab_true);
 }

FieldBool::~FieldBool()
 {
 }

 // methods

Point FieldBool::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay{Lay(check_true),LayLeft(lab_true)};

  return lay.getMinSize(space);
 }

void FieldBool::setField(bool *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

void FieldBool::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldBool::noField()
 {
  pad=0;
 }

 // drawing

void FieldBool::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay{Lay(check_true),LayLeft(lab_true)};

  lay.setPlace(getPane(),space);
 }

/* class CoordWindow */

bool CoordWindow::CheckText(PtrLen<const Char> text)
 {
  for(; +text && SymCharIsSpace(*text) ;++text);

  if( !text ) return false;

  if(Char ch=*text; ch=='+' || ch=='-' )
    {
     ++text;

     if( !text ) return false;
    }

  for(; +text && SymCharDecValue(*text)>=0 ;++text);

  return !text;
 }

Coord CoordWindow::TextToValue(PtrLen<const Char> text)
 {
  for(; +text && SymCharIsSpace(*text) ;++text);

  if( !text ) return 0;

  bool neg=false;

  if(Char ch=*text; ch=='+' || ch=='-' )
    {
     if( ch=='-' ) neg=true;

     ++text;

     if( !text ) return 0;
    }

  Coord val=0;

  for(int dig; +text && (dig=SymCharDecValue(*text))>=0 ;++text)
    {
     val=10*val+dig;
    }

  if( neg ) val=-val;

  return val;
 }

void CoordWindow::edit_changed()
 {
  alert(!CheckText(getText()));
 }

CoordWindow::CoordWindow(SubWindowHost &host,const ConfigType &cfg)
 : LineEditWindow(host,cfg),

   connector_edit_changed(this,&CoordWindow::edit_changed,changed)
 {
 }

CoordWindow::~CoordWindow()
 {
 }

 // methods

Coord CoordWindow::getValue() const
 {
  return TextToValue(getText());
 }

void CoordWindow::setValue(Coord val)
 {
  printf("#;",val);

  alert(false);
 }

/* class ULenWindow */

bool ULenWindow::CheckText(PtrLen<const Char> text)
 {
  for(; +text && SymCharIsSpace(*text) ;++text);

  if( !text ) return false;

  for(; +text && SymCharDecValue(*text)>=0 ;++text);

  return !text;
 }

ulen ULenWindow::TextToValue(PtrLen<const Char> text)
 {
  for(; +text && SymCharIsSpace(*text) ;++text);

  if( !text ) return 0;

  ulen val=0;

  for(int dig; +text && (dig=SymCharDecValue(*text))>=0 ;++text)
    {
     val=10*val+dig;
    }

  return val;
 }

void ULenWindow::edit_changed()
 {
  alert(!CheckText(getText()));
 }

ULenWindow::ULenWindow(SubWindowHost &host,const ConfigType &cfg)
 : LineEditWindow(host,cfg),

   connector_edit_changed(this,&ULenWindow::edit_changed,changed)
 {
 }

ULenWindow::~ULenWindow()
 {
 }

 // methods

ulen ULenWindow::getValue() const
 {
  return TextToValue(getText());
 }

void ULenWindow::setValue(ulen val)
 {
  printf("#;",val);

  alert(false);
 }

/* class FieldCoord */

FieldCoord::FieldCoord(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   edit(wlist,cfg.edit_cfg)
 {
  wlist.insTop(edit);
 }

FieldCoord::~FieldCoord()
 {
 }

 // methods

Point FieldCoord::getMinSize() const
 {
  return edit.getMinSize();
 }

void FieldCoord::setField(Coord *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

void FieldCoord::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldCoord::noField()
 {
  pad=0;
 }

 // drawing

void FieldCoord::layout()
 {
  LayTop(edit).setPlace(getPane(),0);
 }

/* class FieldString */

FieldString::FieldString(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   edit(wlist,cfg.edit_cfg)
 {
  wlist.insTop(edit);
 }

FieldString::~FieldString()
 {
 }

 // methods

Point FieldString::getMinSize() const
 {
  return edit.getMinSize();
 }

void FieldString::setField(String *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

void FieldString::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldString::noField()
 {
  pad=0;
 }

 // drawing

void FieldString::layout()
 {
  LayTop(edit).setPlace(getPane(),0);
 }

/* class FieldULen */

FieldULen::FieldULen(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   edit(wlist,cfg.edit_cfg)
 {
  wlist.insTop(edit);
 }

FieldULen::~FieldULen()
 {
 }

 // methods

Point FieldULen::getMinSize() const
 {
  return edit.getMinSize();
 }

void FieldULen::setField(ulen *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

void FieldULen::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldULen::noField()
 {
  pad=0;
 }

 // drawing

void FieldULen::layout()
 {
  LayTop(edit).setPlace(getPane(),0);
 }

/* class FieldColor */

FieldColor::FieldColor(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   edit(wlist,cfg.edit_cfg)
 {
  wlist.insTop(edit);
 }

FieldColor::~FieldColor()
 {
 }

 // methods

Point FieldColor::getMinSize() const
 {
  return edit.getMinSize();
 }

void FieldColor::setField(VColor *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

void FieldColor::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldColor::noField()
 {
  pad=0;
 }

 // drawing

void FieldColor::layout()
 {
  LayTop(edit).setPlace(getPane(),0);
 }

/* class FieldStrength */

FieldStrength::FieldStrength(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   edit(wlist,cfg.edit_cfg)
 {
  wlist.insTop(edit);
 }

FieldStrength::~FieldStrength()
 {
 }

 // methods

Point FieldStrength::getMinSize() const
 {
  return edit.getMinSize();
 }

void FieldStrength::setField(BookLab::Strength *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

void FieldStrength::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldStrength::noField()
 {
  pad=0;
 }

 // drawing

void FieldStrength::layout()
 {
  LayTop(edit).setPlace(getPane(),0);
 }

/* class FieldAlign */

FieldAlign::FieldAlign(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   lab_left(wlist,cfg.lab_cfg,"Left"_def),
   lab_right(wlist,cfg.lab_cfg,"Right"_def),
   lab_center(wlist,cfg.lab_cfg,"Center"_def),

   rad_left(wlist,BookLab::Left,cfg.rad_cfg),
   rad_right(wlist,BookLab::Right,cfg.rad_cfg),
   rad_center(wlist,BookLab::Center,cfg.rad_cfg)
 {
  wlist.insTop(lab_left,lab_right,lab_center,rad_left,rad_right,rad_center);

  group.add(rad_left,rad_right,rad_center);
 }

FieldAlign::~FieldAlign()
 {
 }

 // methods

Point FieldAlign::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{LayBox(rad_left),LayLeft(lab_left)};
  LayToRightCenter lay2{LayBox(rad_right),LayLeft(lab_right)};
  LayToRightCenter lay3{LayBox(rad_center),LayLeft(lab_center)};

  LayToBottom lay{lay1,lay2,LayAlignTop(lay3)};

  return lay.getMinSize(space);
 }

void FieldAlign::setField(BookLab::Align *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

BookLab::Align FieldAlign::getValue() const
 {
  return BookLab::Align(group.getRadioId());
 }

void FieldAlign::setValue(BookLab::Align val)
 {
  switch( val )
    {
     case BookLab::Left : rad_left.check(); break;

     case BookLab::Right : rad_right.check(); break;

     case BookLab::Center : rad_center.check(); break;
    }
 }

void FieldAlign::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldAlign::noField()
 {
  pad=0;
 }

 // drawing

void FieldAlign::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{LayBox(rad_left),LayLeft(lab_left)};
  LayToRightCenter lay2{LayBox(rad_right),LayLeft(lab_right)};
  LayToRightCenter lay3{LayBox(rad_center),LayLeft(lab_center)};

  LayToBottom lay{lay1,lay2,LayAlignTop(lay3)};

  lay.setPlace(getPane(),space);
 }

/* class FieldEffect */

FieldEffect::FieldEffect(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   lab_none(wlist,cfg.lab_cfg,"None"_def),
   lab_under(wlist,cfg.lab_cfg,"Underline"_def),
   lab_strike(wlist,cfg.lab_cfg,"Strikeout"_def),

   rad_none(wlist,BookLab::NoEffect,cfg.rad_cfg),
   rad_under(wlist,BookLab::Underline,cfg.rad_cfg),
   rad_strike(wlist,BookLab::Strikeout,cfg.rad_cfg)
 {
  wlist.insTop(lab_none,lab_under,lab_strike,rad_none,rad_under,rad_strike);

  group.add(rad_none,rad_under,rad_strike);
 }

FieldEffect::~FieldEffect()
 {
 }

 // methods

Point FieldEffect::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{LayBox(rad_none),LayLeft(lab_none)};
  LayToRightCenter lay2{LayBox(rad_under),LayLeft(lab_under)};
  LayToRightCenter lay3{LayBox(rad_strike),LayLeft(lab_strike)};

  LayToBottom lay{lay1,lay2,LayAlignTop(lay3)};

  return lay.getMinSize(space);
 }

void FieldEffect::setField(BookLab::Effect *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

BookLab::Effect FieldEffect::getValue() const
 {
  return BookLab::Effect(group.getRadioId());
 }

void FieldEffect::setValue(BookLab::Effect val)
 {
  switch( val )
    {
     case BookLab::NoEffect : rad_none.check(); break;

     case BookLab::Underline : rad_under.check(); break;

     case BookLab::Strikeout : rad_strike.check(); break;
    }
 }

void FieldEffect::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldEffect::noField()
 {
  pad=0;
 }

 // drawing

void FieldEffect::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{LayBox(rad_none),LayLeft(lab_none)};
  LayToRightCenter lay2{LayBox(rad_under),LayLeft(lab_under)};
  LayToRightCenter lay3{LayBox(rad_strike),LayLeft(lab_strike)};

  LayToBottom lay{lay1,lay2,LayAlignTop(lay3)};

  lay.setPlace(getPane(),space);
 }

/* class LayEqualX<L1,L2> */

template <class L1,class L2>
class LayEqualX
 {
   L1 lay1;
   L2 lay2;

  private:

   static Point Equalize(Point a,Point b) { return {Sup(a.x,b.x),a.y}; }

  public:

   LayEqualX(const L1 &lay1_,const L2 &lay2_) : lay1(lay1_),lay2(lay2_) {}

   Point getMinSize1(Coord space) const { return Equalize(lay1.getMinSize(space),lay2.getMinSize(space)); }

   Point getMinSize2(Coord space) const { return Equalize(lay2.getMinSize(space),lay1.getMinSize(space)); }

   void setPlace1(Pane pane,Coord space) const { lay1.setPlace(pane,space); }

   void setPlace2(Pane pane,Coord space) const { lay2.setPlace(pane,space); }

   class Item1
    {
      const LayEqualX &lay;

     public:

      Item1(const LayEqualX &lay_) : lay(lay_) {}

      Point getMinSize(Coord space) const { return lay.getMinSize1(space); }

      void setPlace(Pane pane,Coord space) const { lay.setPlace1(pane,space); }
    };

   class Item2
    {
      const LayEqualX &lay;

     public:

      Item2(const LayEqualX &lay_) : lay(lay_) {}

      Point getMinSize(Coord space) const { return lay.getMinSize2(space); }

      void setPlace(Pane pane,Coord space) const { lay.setPlace2(pane,space); }
    };

   Item1 get1() { return *this; }

   Item2 get2() { return *this; }
 };

/* class FieldPoint */

FieldPoint::FieldPoint(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   lab_point(wlist,cfg.lab_cfg,"Point (x,y)"_def),
   lab_x(wlist,cfg.lab_cfg,"x"_def),
   lab_y(wlist,cfg.lab_cfg,"y"_def),
   edit_x(wlist,cfg.edit_cfg),
   edit_y(wlist,cfg.edit_cfg)
 {
  wlist.insTop(lab_point,lab_x,lab_y,edit_x,edit_y);

  edit_x.hideInactiveCursor();
  edit_y.hideInactiveCursor();
 }

FieldPoint::~FieldPoint()
 {
 }

 // methods

Point FieldPoint::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayEqualX layeq{LayLeft(lab_x),LayLeft(lab_y)};

  LayToRight lay1{layeq.get1(),Lay(edit_x)};
  LayToRight lay2{layeq.get2(),Lay(edit_y)};

  LayToBottom lay{Lay(lab_point),lay1,LayAlignTop(lay2)};

  return lay.getMinSize(space);
 }

void FieldPoint::setField(Point *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

void FieldPoint::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldPoint::noField()
 {
  pad=0;
 }

 // drawing

void FieldPoint::layout()
 {
  Coord space=+cfg.space_dxy;

  LayEqualX layeq{LayLeft(lab_x),LayLeft(lab_y)};

  LayToRight lay1{layeq.get1(),Lay(edit_x)};
  LayToRight lay2{layeq.get2(),Lay(edit_y)};

  LayToBottom lay{Lay(lab_point),lay1,LayAlignTop(lay2)};

  lay.setPlace(getPane(),space);
 }

/* class FieldRatio */

BookLab::Ratio FieldRatio::Correct(Coord a,Coord b)
 {
  if( !b ) return {1,1};

  return {a,b};
 }

FieldRatio::FieldRatio(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   lab_ratio(wlist,cfg.lab_cfg,"Ratio a/b"_def),
   lab_a(wlist,cfg.lab_cfg,"a"_def),
   lab_b(wlist,cfg.lab_cfg,"/b"_def),
   edit_a(wlist,cfg.edit_cfg),
   edit_b(wlist,cfg.edit_cfg)
 {
  wlist.insTop(lab_ratio,lab_a,lab_b,edit_a,edit_b);

  edit_a.hideInactiveCursor();
  edit_b.hideInactiveCursor();
 }

FieldRatio::~FieldRatio()
 {
 }

 // methods

Point FieldRatio::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayEqualX layeq{LayLeft(lab_a),LayLeft(lab_b)};

  LayToRight lay1{layeq.get1(),Lay(edit_a)};
  LayToRight lay2{layeq.get2(),Lay(edit_b)};

  LayToBottom lay{Lay(lab_ratio),lay1,LayAlignTop(lay2)};

  return lay.getMinSize(space);
 }

void FieldRatio::setField(BookLab::Ratio *pad_)
 {
  pad=pad_;

  if( pad ) setValue(*pad);
 }

void FieldRatio::set(bool *def_pad,bool def)
 {
  if( def_pad )
    {
     *def_pad=def;

     if( !def && pad ) *pad=getValue();
    }
  else
    {
     if( pad ) *pad=getValue();
    }
 }

void FieldRatio::noField()
 {
  pad=0;
 }

 // drawing

void FieldRatio::layout()
 {
  Coord space=+cfg.space_dxy;

  LayEqualX layeq{LayLeft(lab_a),LayLeft(lab_b)};

  LayToRight lay1{layeq.get1(),Lay(edit_a)};
  LayToRight lay2{layeq.get2(),Lay(edit_b)};

  LayToBottom lay{Lay(lab_ratio),lay1,LayAlignTop(lay2)};

  lay.setPlace(getPane(),space);
 }

/* class FieldWindow */

void FieldWindow::noField()
 {
  if( field_ctrl )
    {
     def_pad=0;

     field_ctrl->noField();

     field_ctrl=0;

     wlist.del(field);

     field=0;

     btn_set.disable();
     check_def.disable();
     lab_def.disable();

     redraw();
    }
 }

void FieldWindow::setFieldCtrl(FieldControl *field_ctrl_,SubWindow *field_,bool withdef)
 {
  if( field_ctrl==field_ctrl_ )
    {
     btn_set.enable();

     check_def.enable(withdef);
     lab_def.enable(withdef);
    }
  else
    {
     if( field_ctrl )
       {
        field_ctrl->noField();

        wlist.del(field);
       }

     field_ctrl=field_ctrl_;
     field=field_;

     wlist.insBottom(field);

     btn_set.enable();

     check_def.enable(withdef);
     lab_def.enable(withdef);

     redraw();
    }
 }

template <class W,class T>
void FieldWindow::setFieldCtrl(W &sub,T *pad)
 {
  def_pad=0;

  sub.setField(pad);

  setFieldCtrl(&sub,&sub,false);
 }

template <class W,class T>
void FieldWindow::setFieldCtrl(W &sub,BookLab::OptDataBase<T> *pad)
 {
  def_pad=&pad->def;

  sub.setField(&pad->data);

  setFieldCtrl(&sub,&sub,true);

  check_def.check(*def_pad);
 }

void FieldWindow::setField(bool *pad)
 {
  setFieldCtrl(field_bool,pad);
 }

void FieldWindow::setField(BookLab::OptDataBase<bool> *pad)
 {
  setFieldCtrl(field_bool,pad);
 }

void FieldWindow::setField(Coord *pad)
 {
  setFieldCtrl(field_Coord,pad);
 }

void FieldWindow::setField(BookLab::OptDataBase<Coord> *pad)
 {
  setFieldCtrl(field_Coord,pad);
 }

void FieldWindow::setField(String *pad)
 {
  setFieldCtrl(field_String,pad);
 }

void FieldWindow::setField(BookLab::OptDataBase<ulen> *pad)
 {
  setFieldCtrl(field_ulen,pad);
 }

void FieldWindow::setField(BookLab::OptDataBase<VColor> *pad)
 {
  setFieldCtrl(field_Color,pad);
 }

void FieldWindow::setField(BookLab::OptDataBase<BookLab::Strength> *pad)
 {
  setFieldCtrl(field_Strength,pad);
 }

void FieldWindow::setField(BookLab::OptDataBase<BookLab::Align> *pad)
 {
  setFieldCtrl(field_Align,pad);
 }

void FieldWindow::setField(BookLab::OptDataBase<BookLab::Effect> *pad)
 {
  setFieldCtrl(field_Effect,pad);
 }

void FieldWindow::setField(BookLab::OptDataBase<Point> *pad)
 {
  setFieldCtrl(field_Point,pad);
 }

void FieldWindow::setField(BookLab::OptDataBase<BookLab::Ratio> *pad)
 {
  setFieldCtrl(field_Ratio,pad);
 }

void FieldWindow::set_pressed()
 {
  if( field_ctrl )
    {
     field_ctrl->set(def_pad,check_def.isChecked());

     modified.assert();
    }
 }

FieldWindow::FieldWindow(SubWindowHost &host,const Config &cfg_,BookLab::Book &book_)
 : ComboWindow(host),
   cfg(cfg_),

   book(book_),

   btn_set(wlist,cfg.btn_cfg,"Set"_def),
   check_def(wlist,cfg.check_cfg),
   lab_def(wlist,cfg.lab_cfg,"default"_def),

   field_bool(wlist,cfg.field_bool_cfg),
   field_Coord(wlist,cfg.field_Coord_cfg),
   field_String(wlist,cfg.field_String_cfg),
   field_ulen(wlist,cfg.field_ulen_cfg),
   field_Color(wlist,cfg.field_Color_cfg),
   field_Strength(wlist,cfg.field_Strength_cfg),
   field_Align(wlist,cfg.field_Align_cfg),
   field_Effect(wlist,cfg.field_Effect_cfg),
   field_Point(wlist,cfg.field_Point_cfg),
   field_Ratio(wlist,cfg.field_Ratio_cfg),

   connector_set_pressed(this,&FieldWindow::set_pressed,btn_set.pressed)
 {
  wlist.insTop(btn_set,check_def,lab_def);

  btn_set.disable();
  check_def.disable();
  lab_def.disable();
 }

FieldWindow::~FieldWindow()
 {
 }

 // methods

Point FieldWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(check_def),LayLeft(lab_def)};

  LaySame lay2{Lay(field_bool),Lay(field_Coord),Lay(field_String),Lay(field_ulen),Lay(field_Color),
               Lay(field_Strength),Lay(field_Align),Lay(field_Effect),Lay(field_Point),Lay(field_Ratio)};

  LayToBottom lay{LayLeft(btn_set),lay1,lay2};

  return ExtLay(lay).getMinSize(space);
 }

void FieldWindow::setField(BookLab::PadType pad)
 {
  if( +pad )
    pad.apply( [&] (auto *pad) { setField(pad); } );
  else
    noField();
 }

 // drawing

void FieldWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(check_def),LayLeft(lab_def)};

  LaySame lay2{Lay(field_bool),Lay(field_Coord),Lay(field_String),Lay(field_ulen),Lay(field_Color),
               Lay(field_Strength),Lay(field_Align),Lay(field_Effect),Lay(field_Point),Lay(field_Ratio)};

  LayToBottom lay{LayLeft(btn_set),lay1,lay2};

  ExtLay(lay).setPlace(getPane(),space);
 }

void FieldWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

/* class FieldFrame */

FieldFrame::FieldFrame(Desktop *desktop,const Config &cfg_,BookLab::Book &book,Signal<> &update)
 : DragFrame(desktop,cfg_.frame_cfg,update),
   cfg(cfg_),

   client(*this,cfg.client_cfg,book),

   modified(client.modified)
 {
  bindClient(client);
 }

FieldFrame::~FieldFrame()
 {
 }

 // base

void FieldFrame::dying()
 {
  DragFrame::dying();

  place=host->getPlace();
  has_place=true;
 }

 // create

Pane FieldFrame::getPane(StrLen title) const
 {
  Point size=getMinSize(false,title,client.getMinSize());

  if( has_place ) return Pane(place.getBase(),Sup(place.getSize(),size));

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

} // namespace App

