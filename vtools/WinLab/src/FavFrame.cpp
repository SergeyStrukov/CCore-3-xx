/* FavFrame.cpp */
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

//#include <CCore/inc/video/FavFrame.h>
#include <inc/FavFrame.h>

#include <CCore/inc/video/FigureLib.h>
#include <CCore/inc/video/LayoutCombo.h>

namespace CCore {
namespace Video {

/* class FavListShape */

Point FavListShape::getMinSize() const
 {
  Point space=+cfg.space;
  const Font &font=cfg.font.get();

  FontSize fs=font->getSize();

  Coord h=AddSize(fs.dy,space.y);

  Coord dy=MulSize(10u,h);

  return 2*space+Point(Div(2,3)*dy,dy);
 }

void FavListShape::draw(const DrawBuf &buf,DrawParam) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  MCoord width=+cfg.width;

  const Font &font=cfg.font.get();

  // lines

  {
   Point space=+cfg.space;
   Pane inner=pane.shrink(space);

   if( +inner )
     {
      VColor gray=+cfg.gray;
      VColor text=+cfg.text;
      VColor text_select=+cfg.text_select;
      VColor section_text=+cfg.section_text;
      VColor section_back=+cfg.section_back;

      FontSize fs=font->getSize();

      Coord h=fs.dy+space.y;
      MCoord H=Fraction(h);

      Coord item_offx=0;
      Coord section_offx=h;

      Pane line=inner;

      line.dy=h;

      line.shrink(space.x/2,RoundUpLen(width/2)+1);

      if( +line )
        {
         ulen count=inner.dy/h;

         MPoint A=MPointTopLeft(inner.getBase());
         MPoint B=MPointTopLeft(inner.addDX());

         art.path(width,gray,A,B);

         KnobShape shape(cfg.knob_cfg,KnobShape::FacePlus);

         auto drawItem = [&] (ulen,StrLen title,StrLen,bool section,bool open,bool cur)
                             {
                              if( section )
                                {
                                 Pane tpane=line.pushLeft(section_offx);

                                 if( cur )
                                   {
                                    art.block(tpane,text_select);

                                    font->textOn(art,tpane,TextPlace(AlignX_Left,AlignY_Center),title,text);
                                   }
                                 else
                                   {
                                    art.block(tpane,section_back);

                                    font->textOn(art,tpane,TextPlace(AlignX_Left,AlignY_Center),title,section_text);
                                   }

                                 shape.face = open? KnobShape::FaceMinus : KnobShape::FacePlus ;

                                 Pane bpane=line;

                                 bpane.dx=bpane.dy;

                                 shape.pane=bpane.shrink(h/8);

                                 shape.draw(buf,DrawParam());
                                }
                              else
                                {
                                 Pane tpane=line.pushLeft(item_offx);

                                 if( cur ) art.block(tpane,text_select);

                                 font->textOn(art,tpane,TextPlace(AlignX_Left,AlignY_Center),title,text);
                                }

                              A=A.addY(H);
                              B=B.addY(H);
                              line.y+=h;

                              art.path(width,gray,A,B);
                             } ;

         fav_list.apply(count,drawItem);
        }
     }
  }

  // border

  {
   VColor border = focus? +cfg.focus : +cfg.border ;

   FigureBox fig(p);

   fig.loop(art,HalfPos,width,border);
  }
 }

ulen FavListShape::getPageLen() const
 {
  if( !pane ) return 0;

  Point space=+cfg.space;

  Pane inner=pane.shrink(space);

  if( !inner ) return 0;

  const Font &font=cfg.font.get();

  FontSize fs=font->getSize();

  Coord h=fs.dy+space.y;

  return inner.dy/h;
 }

auto FavListShape::test(Point point) const -> TestResult
 {
  if( !pane ) return {0,false,false};

  MCoord width=+cfg.width;

  const Font &font=cfg.font.get();

  Point space=+cfg.space;

  Pane inner=pane.shrink(space);

  if( !inner ) return {0,false,false};

  FontSize fs=font->getSize();

  Coord h=fs.dy+space.y;

  Pane line=inner;

  line.dy=h;

  line.shrink(space.x/2,RoundUpLen(width/2)+1);

  if( !line ) return {0,false,false};

  ulen count=inner.dy/h;

  TestResult result={0,false,false};

  auto testItem = [&] (ulen ind,StrLen,StrLen,bool section,bool,bool)
                      {
                       if( section )
                         {
                          Pane bpane=line;

                          bpane.dx=bpane.dy;

                          if( bpane.shrink(h/8).contains(point) )
                            {
                             result={ind,true,true};

                             return false;
                            }

                          if( line.contains(point) )
                            {
                             result={ind,false,true};

                             return false;
                            }

                         }
                       else
                         {
                          if( line.contains(point) )
                            {
                             result={ind,false,true};

                             return false;
                            }
                         }

                       line.y+=h;

                       return true;

                      } ;

  fav_list.apply(count,testItem);

  return result;
 }

ScrollPos FavListShape::getScrollPos() const
 {
  ulen page=getPageLen();
  ulen total=fav_list.getTotal();
  ulen pos=fav_list.getOff();

  if( !page ) page=1;

  return {total+page-1,page,pos};
 }

/* class FavWindow */

void FavWindow::fav_changed()
 {
  knob_up.enable(fav.canMoveUp());
  knob_down.enable(fav.canMoveDown());

  if( const FavRec *obj=fav.getCur() )
    {
     knob_del.enable();
     btn_select.enable(!obj->section);

     text.setText(obj->path);
    }
  else
    {
     knob_del.disable();
     btn_select.disable();

     text.setText(Empty);
    }

  scroll.setRange(fav.getScrollPos());
 }

void FavWindow::ins_pressed()
 {
  fav.insItem(ins_title,ins_path);

  knob_ins.disable();
 }

void FavWindow::up_pressed()
 {
  fav.moveUp();
 }

void FavWindow::down_pressed()
 {
  fav.moveDown();
 }

void FavWindow::openall_pressed()
 {
  fav.openAll();
 }

void FavWindow::closeall_pressed()
 {
  fav.closeAll();
 }

void FavWindow::del_pressed()
 {
  fav.del();
 }

void FavWindow::section_pressed()
 {
  fav.insSection(edit.getString());
 }

void FavWindow::select_pressed()
 {
  if( const FavRec *obj=fav.getCur() )
    {
     if( !obj->section )
       {
        selected_path=obj->path;

        getFrame()->askClose();
       }
    }
 }

void FavWindow::close_pressed()
 {
  getFrame()->askClose();
 }

void FavWindow::scroll_changed(ulen pos)
 {
  fav.setOff(pos);
 }

void FavWindow::off_changed(ulen pos)
 {
  scroll.setPos(pos);
 }

FavWindow::FavWindow(SubWindowHost &host,const Config &cfg_,StrLen key_,StrLen file_)
 : ComboWindow(host),
   cfg(cfg_),
   key(key_),
   file(file_),

   knob_ins(wlist,cfg.knob_cfg,KnobShape::FacePlus),
   knob_up(wlist,cfg.knob_cfg,KnobShape::FaceUp),
   knob_down(wlist,cfg.knob_cfg,KnobShape::FaceDown),

   btn_openall(wlist,cfg.btn_cfg,"Open All"_str),
   btn_closeall(wlist,cfg.btn_cfg,"Close All"_str),

   knob_del(wlist,cfg.knob_cfg,KnobShape::FaceCross),

   btn_section(wlist,cfg.btn_cfg,cfg.text_Section),
   edit(wlist,cfg.edit_cfg),

   dline1(wlist,cfg.dline_cfg),

   fav(wlist,cfg.fav_cfg),
   scroll(wlist,cfg.scroll_cfg),
   text(wlist,cfg.text_cfg),

   dline2(wlist,cfg.dline_cfg),

   btn_select(wlist,cfg.btn_cfg,cfg.text_Select),
   btn_close(wlist,cfg.btn_cfg,cfg.text_Close),

   connector_fav_changed(this,&FavWindow::fav_changed,fav.changed),
   connector_fav_selected(this,&FavWindow::select_pressed,fav.selected),
   connector_ins_pressed(this,&FavWindow::ins_pressed,knob_ins.pressed),
   connector_up_pressed(this,&FavWindow::up_pressed,knob_up.pressed),
   connector_down_pressed(this,&FavWindow::down_pressed,knob_down.pressed),
   connector_openall_pressed(this,&FavWindow::openall_pressed,btn_openall.pressed),
   connector_closeall_pressed(this,&FavWindow::closeall_pressed,btn_closeall.pressed),
   connector_del_pressed(this,&FavWindow::del_pressed,knob_del.pressed),
   connector_section_pressed(this,&FavWindow::section_pressed,btn_section.pressed),
   connector_select_pressed(this,&FavWindow::select_pressed,btn_select.pressed),
   connector_close_pressed(this,&FavWindow::close_pressed,btn_close.pressed),
   connector_scroll_changed(this,&FavWindow::scroll_changed,scroll.changed),
   connector_off_changed(this,&FavWindow::off_changed,fav.off_changed)
 {
  wlist.insTop(knob_ins,knob_up,knob_down,btn_openall,btn_closeall,knob_del,
               btn_section,edit,dline1,fav,scroll,text,dline2,btn_select,btn_close);

  knob_ins.disable();
 }

FavWindow::~FavWindow()
 {
 }

 // methods

Point FavWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(knob_ins),Lay(knob_up),Lay(knob_down),Lay(btn_openall),Lay(btn_closeall),LayRight(knob_del)};

  LayToRightCenter lay2{Lay(btn_section),Lay(edit)};

  LaySupCenterXExt lay3{Lay(btn_select),Lay(btn_close)};

  LayToBottom lay{lay1,lay2,Lay(dline1),LayToTop{lay3,Lay(dline2),Lay(text),LayToLeft{Lay(scroll),Lay(fav)}}};

  return ExtLay(lay).getMinSize(space);
 }

void FavWindow::setInsData(const String &title,const String &path)
 {
  ins_title=title;
  ins_path=path;

  knob_ins.enable();
 }

 // drawing

void FavWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(knob_ins),Lay(knob_up),Lay(knob_down),Lay(btn_openall),Lay(btn_closeall),LayRight(knob_del)};

  LayToRightCenter lay2{Lay(btn_section),Lay(edit)};

  LaySupCenterXExt lay3{Lay(btn_select),Lay(btn_close)};

  LayToBottom lay{lay1,lay2,Lay(dline1),LayToTop{lay3,Lay(dline2),Lay(text),LayToLeft{Lay(scroll),Lay(fav)}}};

  ExtLay(lay).setPlace(getPane(),space);

  scroll.setRange(fav.getScrollPos());
 }

void FavWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
 }

 // base

void FavWindow::open()
 {
  ComboWindow::open();

  selected_path=Null;

  fav.load(key,file);

  fav.setFocus();
 }

void FavWindow::close()
 {
  fav.save(key,file);

  ComboWindow::close();
 }

} // namespace Video
} // namespace CCore

