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

/* class FavWindow */

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
   btn_close(wlist,cfg.btn_cfg,cfg.text_Close)
 {
  wlist.insTop(knob_ins,knob_up,knob_down,btn_openall,btn_closeall,knob_del,
               btn_section,edit,dline1,fav,scroll,text,dline2,btn_select,btn_close);
 }

FavWindow::~FavWindow()
 {
 }

 // methods

Point FavWindow::getMinSize() const // TODO
 {
  return Point(100,100);
 }

 // drawing

void FavWindow::layout() // TODO
 {
 }

void FavWindow::drawBack(DrawBuf buf,DrawParam &draw_param) const
 {
  draw_param.erase(buf,+cfg.back);
 }

 // base

void FavWindow::open()
 {
  ComboWindow::open();

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

