/* Editor.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: ContourLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Editor.h>

#include <CCore/inc/video/Layout.h>

#include <CCore/inc/video/FigureLib.h>

namespace App {

/* class EditorWindow */

void EditorWindow::deactivate()
 {
  wlist.del(edit_angle,edit_length,edit_ratio);
 }

void EditorWindow::activate(SubWindow &editor)
 {
  deactivate();

  wlist.insBottom(editor);

  geom.unselect();

  redraw();
 }

void EditorWindow::select(const Contour::Object &obj,Geometry::Angle &angle)
 {
  angle_pad.select(obj,angle);

  edit_angle.setValue(angle);

  activate(edit_angle);
 }

void EditorWindow::select(const Contour::Object &obj,Geometry::Length &length)
 {
  length_pad.select(obj,length);

  edit_length.setValue(length);

  activate(edit_length);
 }

void EditorWindow::select(const Contour::Object &obj,Geometry::Ratio &ratio)
 {
  ratio_pad.select(obj,ratio);

  edit_ratio.setValue(ratio);

  activate(edit_ratio);
 }

void EditorWindow::select(const Contour::Object &obj,Geometry::Point &point)
 {
  deactivate();

  geom.selectPoint(obj,point);

  redraw();
 }

struct EditorWindow::SelectPad
 {
  EditorWindow *ptr;

  void operator () (const Label &,const Contour::Object &,auto &)
   {
   }

  void operator () (const Label &,const Contour::Object &obj,OneOfTypes<Geometry::Angle,Geometry::Length,Geometry::Ratio,Geometry::Point> &s)
   {
    ptr->select(obj,s);
   }
 };

void EditorWindow::selectPad(ulen index)
 {
  list_pad.setCheck( geom.contour.refPadLabel(index) );

  geom.contour.pad(index,SelectPad{this});

  geom.setPadIndex(index);
 }

void EditorWindow::unselectPad()
 {
  list_pad.noItem();

  deactivate();

  geom.unselect();

  geom.setPadIndex(MaxULen);

  redraw();
 }

void EditorWindow::selectFormula(ulen index)
 {
  list_formula.setCheck( geom.contour.refFormulaLabel(index) );

  geom.setFormulaIndex(index);
 }

void EditorWindow::unselectFormula()
 {
  list_formula.noItem();

  geom.setFormulaIndex(MaxULen);
 }

 // edit changed

void EditorWindow::angle_changed(Geometry::Angle angle)
 {
  if( angle_pad.set(angle) )
    {
     geom.redraw();

     setModified();
    }
 }

void EditorWindow::length_changed(Geometry::Length length)
 {
  if( length_pad.set(length) )
    {
     geom.redraw();

     setModified();
    }
 }

void EditorWindow::ratio_changed(Geometry::Ratio ratio)
 {
  if( ratio_pad.set(ratio) )
    {
     geom.redraw();

     setModified();
    }
 }

void EditorWindow::geom_changed()
 {
  setModified();
 }

 // layout

Coord EditorWindow::getMinDXY() const
 {
  return 2*(+cfg.space_dxy);
 }

Coord EditorWindow::getMaxLeftDX() const
 {
  Coord space=+cfg.space_dxy;
  Coord min_dx=2*space;

  Coord total_dx=getSize().x;
  Coord sx=split1.getMinSize().dx;

  return Max_cast(min_dx,total_dx-2*space-min_dx-sx);
 }

Coord EditorWindow::getMaxTopDY() const
 {
  Coord space=+cfg.space_dxy;
  Coord min_dy=2*space;

  Coord total_dy=getSize().y;
  Coord sy=split2.getMinSize().dy;

  return Max_cast(min_dy,total_dy-2*space-min_dy-sy);
 }

bool EditorWindow::adjustSplitX(Coord dx)
 {
  Coord min_dx=getMinDXY();
  Coord max_dx=getMaxLeftDX();

  return Change(left_dx, Cap<Coord>(min_dx,left_dx+dx,max_dx) );
 }

bool EditorWindow::adjustSplitY(Coord dy)
 {
  Coord min_dy=getMinDXY();
  Coord max_dy=getMaxTopDY();

  return Change(top_dy, Cap<Coord>(min_dy,top_dy+dy,max_dy) );
 }

void EditorWindow::adjustSplit(Point point)
 {
  if( adjustSplitX(point.x) | adjustSplitY(point.y) )
    {
     layout();

     redraw();
    }
 }

 // split

void EditorWindow::split1_dragged(Point point)
 {
  adjustSplit(point);
 }

void EditorWindow::split2_dragged(Point point)
 {
  adjustSplit(point);
 }

 // pad

void EditorWindow::pad_up(ulen ind)
 {
  if( geom.contour.padUp(ind) )
    {
     list_pad.updateList();

     list_pad.select(ind-1);

     list_pad.ping();

     setModified();
    }
 }

void EditorWindow::pad_down(ulen ind)
 {
  if( geom.contour.padDown(ind) )
    {
     list_pad.updateList();

     list_pad.select(ind+1);

     list_pad.ping();

     setModified();
    }
 }

void EditorWindow::pad_del(ulen ind)
 {
  if( geom.contour.padDel(ind) )
    {
     list_pad.updateList();

     if( list_pad.select(ind) )
       {
        list_pad.ping();
       }
     else
       {
        unselectPad();
       }

     setModified();
    }
 }

void EditorWindow::pad_add(ulen ind)
 {
  if( !pad_test() ) return;

  ind++;

  if( geom.contour.padAdd(ind,list_pad.getText()) )
    {
     list_pad.updateList();

     list_pad.select(ind);

     list_pad.ping();

     geom.redraw();

     setModified();
    }
 }

void EditorWindow::pad_selected(ulen ind)
 {
  selectPad(ind);
 }

void EditorWindow::pad_show_changed(ulen ind,bool check)
 {
  geom.contour.refPadLabel(ind).show=check;

  geom.redraw();

  setModified();
 }

void EditorWindow::pad_gray_changed(ulen ind,bool check)
 {
  geom.contour.refPadLabel(ind).gray=check;

  geom.redraw();

  setModified();
 }

void EditorWindow::pad_name_changed(ulen ind,bool check)
 {
  geom.contour.refPadLabel(ind).show_name=check;

  geom.redraw();

  setModified();
 }

void EditorWindow::pad_text_changed()
 {
  list_pad.normalAccent();

  list_pad.enableAdd(true);
 }

bool EditorWindow::pad_test()
 {
  bool ok=geom.contour.padAddTest(list_pad.getText(),list_pad.getAccentBuf());

  list_pad.clearAccentFlag();

  list_pad.enableAdd(ok);

  return ok;
 }

void EditorWindow::pad_text_paused()
 {
  pad_test();
 }

 // formula

void EditorWindow::formula_up(ulen ind)
 {
  if( geom.contour.formulaUp(ind) )
    {
     list_formula.updateList();

     list_formula.select(ind-1);

     list_formula.ping();

     setModified();
    }
 }

void EditorWindow::formula_down(ulen ind)
 {
  if( geom.contour.formulaDown(ind) )
    {
     list_formula.updateList();

     list_formula.select(ind+1);

     list_formula.ping();

     setModified();
    }
 }

void EditorWindow::formula_del(ulen ind)
 {
  if( geom.contour.formulaDel(ind) )
    {
     list_formula.updateList();

     if( list_formula.select(ind) )
       {
        list_formula.ping();
       }
     else
       {
        unselectFormula();
       }

     setModified();
    }
 }

void EditorWindow::formula_add(ulen ind)
 {
  if( !formula_test() ) return;

  ind++;

  if( geom.contour.formulaAdd(ind,list_formula.getText()) )
    {
     list_formula.updateList();

     list_formula.select(ind);

     list_formula.ping();

     geom.redraw();

     setModified();
    }
 }

void EditorWindow::formula_selected(ulen ind)
 {
  selectFormula(ind);
 }

void EditorWindow::formula_show_changed(ulen ind,bool check)
 {
  geom.contour.refFormulaLabel(ind).show=check;

  geom.redraw();

  setModified();
 }

void EditorWindow::formula_gray_changed(ulen ind,bool check)
 {
  geom.contour.refFormulaLabel(ind).gray=check;

  geom.redraw();

  setModified();
 }

void EditorWindow::formula_name_changed(ulen ind,bool check)
 {
  geom.contour.refFormulaLabel(ind).show_name=check;

  geom.redraw();

  setModified();
 }

void EditorWindow::formula_text_changed()
 {
  list_formula.normalAccent();

  list_formula.enableAdd(true);
 }

bool EditorWindow::formula_test()
 {
  bool ok=geom.contour.formulaAddTest(list_formula.getText(),list_formula.getAccentBuf());

  list_formula.clearAccentFlag();

  list_formula.enableAdd(ok);

  return ok;
 }

void EditorWindow::formula_text_paused()
 {
  formula_test();
 }

 // msg

void EditorWindow::errorMsg(StrLen text)
 {
  msg_frame.setInfo(String(text));

  msg_frame.create(getFrame(),+cfg.text_Error);

  disableFrameReact();
 }

void EditorWindow::msg_destroyed()
 {
  enableFrameReact();
 }

EditorWindow::EditorWindow(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   text_file(wlist,cfg.text_cfg),
   split1(wlist,cfg.split_cfg),
   split2(wlist,cfg.split_cfg),
   edit_angle(wlist,cfg.edit_angle_cfg),
   edit_length(wlist,cfg.edit_length_cfg),
   edit_ratio(wlist,cfg.edit_ratio_cfg),
   geom(wlist,cfg.geom_cfg),
   list_pad(wlist,cfg.ilist_cfg),
   list_formula(wlist,cfg.ilist_cfg),
   msg_frame(host.getFrameDesktop(),cfg.msg_cfg),

   connector_angle_changed(this,&EditorWindow::angle_changed,edit_angle.changed),
   connector_length_changed(this,&EditorWindow::length_changed,edit_length.changed),
   connector_ratio_changed(this,&EditorWindow::ratio_changed,edit_ratio.changed),
   connector_geom_changed(this,&EditorWindow::geom_changed,geom.changed),

   connector_split1_dragged(this,&EditorWindow::split1_dragged,split1.dragged),
   connector_split2_dragged(this,&EditorWindow::split2_dragged,split2.dragged),

   connector_list_pad_command_up(this,&EditorWindow::pad_up,list_pad.command_up),
   connector_list_pad_command_down(this,&EditorWindow::pad_down,list_pad.command_down),
   connector_list_pad_command_del(this,&EditorWindow::pad_del,list_pad.command_del),
   connector_list_pad_command_add(this,&EditorWindow::pad_add,list_pad.command_add),
   connector_list_pad_command_selected(this,&EditorWindow::pad_selected,list_pad.selected),

   connector_list_pad_show_changed(this,&EditorWindow::pad_show_changed,list_pad.show_changed),
   connector_list_pad_gray_changed(this,&EditorWindow::pad_gray_changed,list_pad.gray_changed),
   connector_list_pad_name_changed(this,&EditorWindow::pad_name_changed,list_pad.name_changed),

   connector_list_pad_text_changed(this,&EditorWindow::pad_text_changed,list_pad.text_changed),
   connector_list_pad_text_paused(this,&EditorWindow::pad_text_paused,list_pad.text_paused),

   connector_list_formula_command_up(this,&EditorWindow::formula_up,list_formula.command_up),
   connector_list_formula_command_down(this,&EditorWindow::formula_down,list_formula.command_down),
   connector_list_formula_command_del(this,&EditorWindow::formula_del,list_formula.command_del),
   connector_list_formula_command_add(this,&EditorWindow::formula_add,list_formula.command_add),
   connector_list_formula_command_selected(this,&EditorWindow::formula_selected,list_formula.selected),

   connector_list_formula_show_changed(this,&EditorWindow::formula_show_changed,list_formula.show_changed),
   connector_list_formula_gray_changed(this,&EditorWindow::formula_gray_changed,list_formula.gray_changed),
   connector_list_formula_name_changed(this,&EditorWindow::formula_name_changed,list_formula.name_changed),

   connector_list_formula_text_changed(this,&EditorWindow::formula_text_changed,list_formula.text_changed),
   connector_list_formula_text_paused(this,&EditorWindow::formula_text_paused,list_formula.text_paused),

   connector_msg_destroyed(this,&EditorWindow::msg_destroyed,msg_frame.destroyed)
 {
  wlist.insTop(split1,split2,text_file,list_pad,list_formula,geom);

  list_pad.setInfo(geom.contour.getPadInfo());

  list_formula.setInfo(geom.contour.getFormulaInfo());

  // function list

  InsWindow::Builder builder;

  builder.add("Length(Point A,Point B)"_c,"Len(?,?)"_c);
  builder.add("Angle(Point A,Point O,Point B)"_c,"Angle(?,?,?)"_c);
  builder.add("Line(Point A,Point B)"_c,"Line(?,?)"_c);
  builder.add("Circle(Point O,Length radius)"_c,"Cir(?,?)"_c);
  builder.add("Circle(Point A,Point B,Point C)"_c,"OCir(?,?,?)"_c);
  builder.add("Point Middle(Point A,Point B)"_c,"Mid(?,?)"_c);
  builder.add("Point Part(Point A,Point B,Ratio rat)"_c,"Part(?,?,?)"_c);
  builder.add("Line MiddleOrthogonal(Point A,Point B)"_c,"MidOrt(?,?)"_c);
  builder.add("Point Projection(Line m,Point A)"_c,"Proj(?,?)"_c);
  builder.add("AngleC(Length a,Length b,Length c)"_c,"AngleC(?,?,?)"_c);
  builder.add("Point Meet(Line m,Line n)"_c,"Meet(?,?)"_c);
  builder.add("Couple Meet(Line m,Circle cir)"_c,"MeetCircle(?,?)"_c);
  builder.add("Couple Meet(Circle cir1,Circle cir2)"_c,"MeetCircles(?,?)"_c);
  builder.add("Point Rotate(Point O,Angle alpha,Point P)"_c,"Rot(?,?,?)"_c);
  builder.add("Point RotateOrt(Point O,Point P)"_c,"RotOrt(?,?)"_c);
  builder.add("Point Move(Point A,Point B,Point P)"_c,"Move(?,?,?)"_c);
  builder.add("Point MoveLen(Line m,Length len,Point A)"_c,"MoveLen(?,?,?)"_c);
  builder.add("Point Mirror(Line m,Point A)"_c,"Mirror(?,?)"_c);
  builder.add("Point First(Couple AB)"_c,"First(?)"_c);
  builder.add("Point Second(Couple AB)"_c,"Second(?)"_c);
  builder.add("Point Up(Length len,Point A)"_c,"Up(?,?)"_c);
  builder.add("Point Down(Length len,Point A)"_c,"Down(?,?)"_c);
  builder.add("Point Left(Length len,Point A)"_c,"Left(?,?)"_c);
  builder.add("Point Right(Length len,Point A)"_c,"Right(?,?)"_c);
  builder.add("Step(Point A1,Point A2,...)"_c,"Step(?..)"_c);
  builder.add("Path(Point A1,Point A2,...)"_c,"Path(?..)"_c);
  builder.add("Loop(Point A1,Point A2,...)"_c,"Loop(?..)"_c);
  builder.add("Path(Step s1,Step s2,...)"_c,"BPath(?..)"_c);
  builder.add("Loop(Step s1,Step s2,...)"_c,"BLoop(?..)"_c);
  builder.add("Solid(Loop loop)"_c,"Solid(?)"_c);

  list_formula.set(builder.complete());

  // bind hints

  text_file.bindHint(cfg.hint_File);
  edit_angle.bindHint(cfg.hint_Angle);
  edit_length.bindHint(cfg.hint_Length);
  edit_ratio.bindHint(cfg.hint_Ratio);
  geom.bindHint(cfg.hint_Geom);
 }

EditorWindow::~EditorWindow()
 {
 }

 // methods

Point EditorWindow::getMinSize() const
 {
  return Point(100,100);
 }

void EditorWindow::blank()
 {
  text_file.setText(""_str);
  setModified();
  has_file=false;

  geom.contour.erase();

  list_pad.reselect();

  list_pad.updateList();

  unselectPad();

  list_formula.reselect();

  list_formula.updateList();

  unselectFormula();

  redraw();
 }

void EditorWindow::load(StrLen file_name_)
 {
  String file_name(file_name_);

  text_file.setText(file_name);
  clearModified();
  has_file=true;

  ErrorText etext;

  geom.contour.load(Range(text_file.getText()),etext);

  if( !etext )
    {
     errorMsg(etext.getText());
    }

  if( list_pad.select(0) ) list_pad.ping(); else unselectPad();

  list_pad.updateList();

  if( list_formula.select(0) ) list_formula.ping(); else unselectFormula();

  list_formula.updateList();

  redraw();
 }

bool EditorWindow::save()
 {
  if( !has_file ) return false;

  ErrorText etext;

  geom.contour.save(Range(text_file.getText()),etext);

  if( !etext )
    {
     errorMsg(etext.getText());
    }
  else
    {
     clearModified();
    }

  return true;
 }

void EditorWindow::save(StrLen file_name_)
 {
  String file_name(file_name_);

  text_file.setText(file_name);
  setModified();
  has_file=true;

  save();
 }

 // drawing

void EditorWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  PaneCut right(space);
  PaneCut top(space);
  PaneCut bottom(space);

  // first split

  {
   PaneCut pane(getSize(),space);

   pane.shrink();

   pane.place_cutTop(text_file);

   if( Change(layout_first,false) )
     {
      PaneCut p=pane.cutLeft(Div(1,3),0);

      left_dx=p.getSize().x;

      pane.place_cutLeft(split1);

      right=pane;

      p.place_cutTop(top,Div(1,2),0).place_cutTop(split2).place(bottom);

      top_dy=top.getSize().y;
     }
   else
     {
      Coord min_dxy=getMinDXY();

      left_dx=Cap(min_dxy,left_dx,getMaxLeftDX());

      top_dy=Cap(min_dxy,top_dy,getMaxTopDY());

      PaneCut p=pane.cutLeft(left_dx,0);

      pane.place_cutLeft(split1);

      right=pane;

      p.place_cutTop(top,top_dy,0).place_cutTop(split2).place(bottom);
     }
  }

  // right

  {
   PaneCut pane(space);

   right.place_cutBottom(pane,Div(20,100)).place(geom);

   pane.placeSmart(edit_angle);
   pane.placeSmart(edit_length);
   pane.placeSmart(edit_ratio);
  }

  // top

  {
   top.place(list_pad);
  }

  // bottom

  {
   bottom.place(list_formula);
  }
 }

void EditorWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
 }

} // namespace App


