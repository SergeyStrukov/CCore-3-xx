/* Aspect.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Aspect 1.01
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/Aspect.h>

#include <CCore/inc/video/LayoutCombo.h>
#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/FileSystem.h>

#include <CCore/inc/Exception.h>

namespace App {

/* functions */

MPoint MCenter(Pane pane)
 {
  MPane p(pane);

  return p.getCenter();
 }

/* class HideControl */

void HideControl::check_changed(bool)
 {
  changed.assert(getFilter());
 }

void HideControl::btn_pressed()
 {
  check_New.check(false);
  check_Ignore.check(false);
  check_Red.check(false);
  check_Yellow.check(false);
  check_Green.check(false);

  changed.assert(getFilter());
 }

Pane HideControl::Inner(Pane pane,Coord dxy)
 {
  Point size=Point::Diag(dxy);
  Point base=pane.getBase()+(pane.getSize()-size)/2;

  return Pane(base,size);
 }

HideControl::HideControl(SubWindowHost &host,const Config &cfg_)
 : ComboWindow(host),
   cfg(cfg_),

   label_Hide(wlist,cfg.label_cfg,cfg.text_Hide),

   check_New(wlist,cfg.check_cfg),
   check_Ignore(wlist,cfg.check_cfg),
   check_Red(wlist,cfg.check_cfg),
   check_Yellow(wlist,cfg.check_cfg),
   check_Green(wlist,cfg.check_cfg),

   btn_ShowAll(wlist,cfg.btn_cfg,cfg.text_ShowAll),

   connector_check_New_changed(this,&HideControl::check_changed,check_New.changed),
   connector_check_Ignore_changed(this,&HideControl::check_changed,check_Ignore.changed),
   connector_check_Red_changed(this,&HideControl::check_changed,check_Red.changed),
   connector_check_Yellow_changed(this,&HideControl::check_changed,check_Yellow.changed),
   connector_check_Green_changed(this,&HideControl::check_changed,check_Green.changed),

   connector_btn_pressed(this,&HideControl::btn_pressed,btn_ShowAll.pressed)
 {
  wlist.insTop(label_Hide,check_New,check_Ignore,check_Red,check_Yellow,check_Green,btn_ShowAll);
 }

HideControl::~HideControl()
 {
 }

 // methods

Point HideControl::getMinSize() const
 {
  Coord space_dxy=+cfg.space_dxy;
  Coord status_dxy=+cfg.status_dxy;

  Point s1=label_Hide.getMinSize();
  Point s2=btn_ShowAll.getMinSize();

  return Point( 6*space_dxy+5*status_dxy+s1.x+s2.x , Sup(s1.y,s2.y,status_dxy) );
 }

bool HideControl::operator [] (ItemStatus status) const
 {
  switch( status )
    {
     case Item_New    : return check_New.isChecked();
     case Item_Ignore : return check_Ignore.isChecked();
     case Item_Red    : return check_Red.isChecked();
     case Item_Yellow : return check_Yellow.isChecked();
     case Item_Green  : return check_Green.isChecked();

     default: return false;
    }
 }

Filter HideControl::getFilter() const
 {
  Filter ret;

  ret.filter[Item_New   ]=check_New.isChecked();
  ret.filter[Item_Ignore]=check_Ignore.isChecked();
  ret.filter[Item_Red   ]=check_Red.isChecked();
  ret.filter[Item_Yellow]=check_Yellow.isChecked();
  ret.filter[Item_Green ]=check_Green.isChecked();

  return ret;
 }

void HideControl::reset()
 {
  check_New.check(false);
  check_Ignore.check(true);
  check_Red.check(false);
  check_Yellow.check(false);
  check_Green.check(true);
 }

 // drawing

void HideControl::layout()
 {
  Coord status_dxy=+cfg.status_dxy;
  Point s=Point::Diag(status_dxy);

  PaneCut pane(getSize(),+cfg.space_dxy);

  pane.place_cutLeft(label_Hide);

  place_New=pane.cutLeftCenter(s);
  place_Ignore=pane.cutLeftCenter(s);
  place_Red=pane.cutLeftCenter(s);
  place_Yellow=pane.cutLeftCenter(s);
  place_Green=pane.cutLeftCenter(s);

  pane.place_cutLeftCenter(btn_ShowAll);

  Coord dxy=check_New.getMinSize().dxy;

  check_New.setPlace(Inner(place_New,dxy));
  check_Ignore.setPlace(Inner(place_Ignore,dxy));
  check_Red.setPlace(Inner(place_Red,dxy));
  check_Yellow.setPlace(Inner(place_Yellow,dxy));
  check_Green.setPlace(Inner(place_Green,dxy));
 }

void HideControl::drawBack(DrawBuf buf,bool) const
 {
  SmoothDrawArt art(buf);

  MCoord radius=Fraction(place_New.dx,1);

  art.ball(MCenter(place_New),radius,+cfg.status_New);
  art.ball(MCenter(place_Ignore),radius,+cfg.status_Ignore);
  art.ball(MCenter(place_Red),radius,+cfg.status_Red);
  art.ball(MCenter(place_Yellow),radius,+cfg.status_Yellow);
  art.ball(MCenter(place_Green),radius,+cfg.status_Green);
 }

/* class CountControl */

CountControl::CountControl(SubWindowHost &host,const Config &cfg_,VColor color_)
 : ComboWindow(host),
   cfg(cfg_),

   text(wlist,cfg.text_cfg),

   color(color_)
 {
  wlist.insTop(text);

  setCount(0);
 }

CountControl::~CountControl()
 {
 }

 // methods

Point CountControl::getMinSize() const
 {
  Coord dxy=+cfg.status_dxy;

  Point s=text.getMinSize("10000000000"_c);

  return Point( 2*dxy+s.x , Sup(2*dxy,s.y) );
 }

void CountControl::setCount(ulen count_)
 {
  count=count_;

  text.printf("#;",count_);
 }

 // drawing

void CountControl::layout()
 {
  Coord dxy=+cfg.status_dxy;

  PaneCut pane(getSize(),0);

  Pane left=pane.cutLeftCenter(2*dxy,2*dxy);
  Point s=left.getSize();

  place_status=Pane(left.getBase()+s/4,s/2);

  pane.place(AlignCenterY(text));
 }

void CountControl::drawBack(DrawBuf buf,bool) const
 {
  SmoothDrawArt art(buf);

  MCoord radius=Fraction(place_status.dx,1);

  art.ball(MCenter(place_status),radius,color);
 }

/* class InnerDataWindow */

void InnerDataWindow::hilightOff()
 {
  if( Change(hilight_type,PressNone) ) redraw();
 }

void InnerDataWindow::updateList()
 {
  ulen count=0;

  auto items=data.getItems();
  auto vis=data.getVisible();

  for(ulen i=0; i<items.len ;)
    {
     const ItemData &item=items[i];

     if( data_filter(item.ptr->status) )
       {
        if( item.is_dir )
          i=item.next_index;
        else
          i++;
       }
     else
       {
        vis[count++]=i;

        if( item.is_dir && !item.is_open )
          i=item.next_index;
        else
          i++;
       }
    }

  sy.total=count;

  hilight_type=PressNone;

  update();

  update_scroll.assert();
 }

void InnerDataWindow::setMax()
 {
  Point s=getSize();

  Coord dxy=+cfg.dxy;

  sx.page=s.x/dxy;

  sy.page=s.y/dxy;

  sx.adjustPos();

  sy.adjustPos();
 }

class InnerDataWindow::DrawItem : NoCopy
 {
   MCoord width;
   Coord dxy;
   Coord rxy;
   Coord rin;
   Coord kxy;
   VColor text;
   VColor status_color[ItemStatusLim];
   Font font;

   const RadioShape::Config &radio_cfg;
   const KnobShape::Config &knob_cfg;

   VColor face1;
   VColor face2;
   VColor line;
   VColor focus;

   Point size;
   Coord file_dx;
   Coord btn_dx;
   Coord dir_dx;

  private:

   void drawRadio(const DrawBuf &buf,Pane pane,ItemStatus status,ItemStatus item_status,bool mover) const
    {
     VColor vc=status_color[status];

     SmoothDrawArt art(buf);

     art.block(pane,vc);

     RadioShape shape(radio_cfg, status==item_status );

     shape.pane=pane.shrink(rin);
     shape.mover=mover;

     shape.draw(buf);
    }

   void drawFile(const DrawBuf &buf,Pane pane,const ItemData &item,PressType hilight) const
    {
     Coord delta=(dxy-rxy)/2;
     Pane btn(pane.getBase().addXY(delta),rxy);
     ItemStatus status=item.ptr->status;
     Coord shift=rxy+delta;

     drawRadio(buf,btn,Item_New,   status,hilight==PressNew);    btn+=Point(shift,0);
     drawRadio(buf,btn,Item_Ignore,status,hilight==PressIgnore); btn+=Point(shift,0);
     drawRadio(buf,btn,Item_Red,   status,hilight==PressRed);    btn+=Point(shift,0);
     drawRadio(buf,btn,Item_Yellow,status,hilight==PressYellow); btn+=Point(shift,0);
     drawRadio(buf,btn,Item_Green, status,hilight==PressGreen);
    }

   void drawKnob(const DrawBuf &buf,Pane pane,KnobType type,bool mover) const
    {
     MPane p(pane);

     if( !p ) return;

     SmoothDrawArt art(buf);

     // center and radius

     MCoord len=p.dx;
     MCoord radius=len/2;

     MPoint center=p.getCenter();

     VColor gray=+knob_cfg.gray;

     // body

     {
      VColor top = mover? +knob_cfg.snowUp : +knob_cfg.snow ;

      art.ball(center,radius,TwoField(p.getTopLeft(),top,p.getBottomLeft(),gray));
     }

     // face

     VColor fc = +knob_cfg.face ;

     switch( type )
       {
        case KnobPlus :
         {
          MCoord a=radius/2;
          MCoord w=radius/3;

          art.path(w,fc,center.subX(a),center.addX(a));
          art.path(w,fc,center.subY(a),center.addY(a));
         }
        break;

        case KnobMinus :
         {
          MCoord a=radius/2;
          MCoord w=radius/3;

          art.path(w,fc,center.subX(a),center.addX(a));
         }
        break;

        case KnobPlusPlus :
         {
          MCoord a=radius/2;
          MCoord w=radius/3;

          art.path(2*w,face2,center.subX(a),center.addX(a));
          art.path(2*w,face2,center.subY(a),center.addY(a));

          art.path(w,face1,center.subX(a),center.addX(a));
          art.path(w,face1,center.subY(a),center.addY(a));
         }
        break;

        case KnobMinusMinus :
         {
          MCoord a=radius/2;
          MCoord w=radius/3;

          art.path(2*w,face2,center.subX(a),center.addX(a));

          art.path(w,face1,center.subX(a),center.addX(a));
         }
        break;
       }

     // border

     {
      MCoord width=+knob_cfg.width;

      VColor border = +knob_cfg.border ;

      art.circle(center,radius-width/2,width,border);
     }
    }

   void drawKnobs(const DrawBuf &buf,Pane pane,const ItemData &item,PressType hilight) const
    {
     Coord delta=(dxy-kxy)/2;
     Pane btn(pane.getBase().addXY(delta),kxy);
     Coord shift=kxy+delta;

     drawKnob(buf,btn,item.is_open?KnobMinus:KnobPlus,hilight==PressPlus); btn+=Point(shift,0);
     drawKnob(buf,btn,KnobPlusPlus,hilight==PressPlusPlus);                btn+=Point(shift,0);
     drawKnob(buf,btn,KnobMinusMinus,hilight==PressMinusMinus);
    }

   void drawDir(const DrawBuf &buf,Pane pane,const ItemData &item,PressType hilight) const
    {
     Point base=pane.addDY();

     drawKnobs(buf,SplitX(btn_dx,pane),item,hilight);
     drawFile(buf,pane,item,hilight);

     TextSize ts=font->text(Range(item.ptr->name));

     Coord len=dir_dx+ts.full_dx;

     SmoothDrawArt art(buf);

     art.path(HalfPos,width,line,base,base.addX(len));
    }

   PressType testRadio(Point point) const
    {
     Coord delta=(dxy-rxy)/2;
     Pane btn(delta,delta,rxy,rxy);
     Coord shift=rxy+delta;

     if( btn.contains(point) ) return PressNew;    btn+=Point(shift,0);
     if( btn.contains(point) ) return PressIgnore; btn+=Point(shift,0);
     if( btn.contains(point) ) return PressRed;    btn+=Point(shift,0);
     if( btn.contains(point) ) return PressYellow; btn+=Point(shift,0);
     if( btn.contains(point) ) return PressGreen;

     return PressNone;
    }

   PressType testKnob(Point point) const
    {
     Coord delta=(dxy-kxy)/2;
     Pane btn(delta,delta,kxy,kxy);
     Coord shift=kxy+delta;

     if( btn.contains(point) ) return PressPlus;       btn+=Point(shift,0);
     if( btn.contains(point) ) return PressPlusPlus;   btn+=Point(shift,0);
     if( btn.contains(point) ) return PressMinusMinus;

     return PressNone;
    }

  public:

   DrawItem(const Config &cfg,Point size_)
    : width(+cfg.width),
      dxy(+cfg.dxy),
      rxy(+cfg.rxy),
      rin(+cfg.rin),
      kxy(+cfg.kxy),
      text(+cfg.text),
      font(+cfg.font),

      radio_cfg(cfg.radio_cfg),
      knob_cfg(cfg.knob_cfg),

      face1(+cfg.face1),
      face2(+cfg.face2),
      line(+cfg.line),
      focus(+cfg.focus),

      size(size_)
    {
     file_dx=dxy+4*(rxy+(dxy-rxy)/2);
     btn_dx=dxy+2*(kxy+(dxy-kxy)/2);
     dir_dx=btn_dx+file_dx;

     status_color[Item_New]=+cfg.status_New;
     status_color[Item_Ignore]=+cfg.status_Ignore;
     status_color[Item_Red]=+cfg.status_Red;
     status_color[Item_Yellow]=+cfg.status_Yellow;
     status_color[Item_Green]=+cfg.status_Green;
    }

   void operator () (const DrawBuf &buf,Point point,const ItemData &item,PressType hilight) const
    {
     Pane pane(point,size.x-point.x,dxy);

     if( item.is_dir )
       {
        drawDir(buf,SplitX(dir_dx,pane),item,hilight);
       }
     else
       {
        drawFile(buf,SplitX(file_dx,pane),item,hilight);
       }

     font->text(buf,pane,TextPlace(AlignX_Left,AlignY_Center),Range(item.ptr->name),text);
    }

   ulen operator () (const ItemData &item) const
    {
     Coord ex = item.is_dir? dir_dx : file_dx ;

     TextSize ts=font->text(Range(item.ptr->name));

     ulen len=(ts.full_dx+ex)/dxy+1;

     return item.depth+len;
    }

   PressType operator () (const ItemData &item,Point point) const
    {
     if( item.is_dir )
       {
        if( point.x<btn_dx )
          {
           return testKnob(point);
          }
        else
          {
           point.x-=btn_dx;

           return testRadio(point);
          }
       }
     else
       {
        return testRadio(point);
       }
    }

   bool operator () (Point point,Point test_point) const
    {
     Pane pane(point,size.x-point.x,dxy);

     return pane.contains(test_point);
    }

   void frame(const DrawBuf &buf,Pane pane) const
    {
     MPane p(pane);

     if( !p ) return;

     SmoothDrawArt art(buf);

     FigureBox fig(p);

     fig.loop(art,HalfPos,width,focus);
    }
 };

void InnerDataWindow::posX(ulen pos)
 {
  sx.setPos(pos);

  hilight_type=PressNone;

  redraw();
 }

void InnerDataWindow::posY(ulen pos)
 {
  sy.setPos(pos);

  hilight_type=PressNone;

  redraw();
 }

void InnerDataWindow::updated(unsigned flags)
 {
  if( flags&LayoutUpdate ) update();
 }

Point InnerDataWindow::BaseX(Point point,ulen off,ulen depth,Coord dxy)
 {
  return ( off<=depth )? point.addX((depth-off)*dxy) : point.subX((off-depth)*dxy) ;
 }

Point InnerDataWindow::Base(ulen off,ulen depth,ulen line,Coord dxy)
 {
  return BaseX(Point(0,CountToCoord(line)*dxy),off,depth,dxy);
 }

void InnerDataWindow::setPosX(ulen pos)
 {
  if( Change(sx.pos,pos) )
    {
     hilight_type=PressNone;

     redraw();

     scroll_x.assert(sx.pos);
    }
 }

void InnerDataWindow::addPosX(ulen delta)
 {
  if( sx.tooShort() ) setPosX(sx.getAdd(delta));
 }

void InnerDataWindow::subPosX(ulen delta)
 {
  if( sx.tooShort() ) setPosX(sx.getSub(delta));
 }

void InnerDataWindow::setPosY(ulen pos)
 {
  if( Change(sy.pos,pos) )
    {
     hilight_type=PressNone;

     redraw();

     scroll_y.assert(sy.pos);
    }
 }

void InnerDataWindow::addPosY(ulen delta)
 {
  if( sy.tooShort() ) setPosY(sy.getAdd(delta));
 }

void InnerDataWindow::subPosY(ulen delta)
 {
  if( sy.tooShort() ) setPosY(sy.getSub(delta));
 }

auto InnerDataWindow::test(const DrawItem &draw,Point test_point) const -> TestResult
 {
  if( test_point.y<0 ) return {MaxULen};

  auto items=data.getItems();
  auto vis=data.getVisible();

  Coord dxy=+cfg.dxy;
  ulen off=sx.pos;

  ulen line=test_point.y/dxy;
  ulen lim=Min(sy.total,vis.len);

  if( line<sy.page && sy.pos<lim && line<lim-sy.pos )
    {
     ulen i=sy.pos+line;
     ulen ind=vis[i];

     if( ind<items.len )
       {
        const ItemData &item=items[ind];

        Point p=Base(off,item.depth,line,dxy);

        if( draw(p,test_point) ) return {ind,p};
       }
    }

  return {MaxULen};
 }

void InnerDataWindow::change(ulen index,const ItemData &item,ItemStatus status,bool recursive)
 {
  if( item.is_dir && recursive )
    {
     auto items=data.getItems();

     for(ulen lim=item.next_index; index<lim ;index++) items[index].ptr->status=status;

     updateList();

     manychanged.assert();
    }
  else
    {
     ItemStatus prev=item.ptr->status;

     if( Change(item.ptr->status,status) )
       {
        updateList();

        changed.assert(prev,status);
       }
    }
 }

void InnerDataWindow::press(const DrawItem &draw,ulen index,Point point,bool recursive)
 {
  auto items=data.getItems();

  const ItemData &item=items[index];

  switch( draw(item,point) )
    {
     case PressPlus :
      {
       item.is_open=!item.is_open;

       updateList();
      }
     break;

     case PressPlusPlus :
      {
       for(ulen i=index,lim=item.next_index; i<lim ;i++) items[i].open();

       updateList();
      }
     break;

     case PressMinusMinus :
      {
       for(ulen i=index,lim=item.next_index; i<lim ;i++) items[i].close();

       updateList();
      }
     break;

     case PressNew :
      {
       change(index,item,Item_New,recursive);
      }
     break;

     case PressIgnore :
      {
       change(index,item,Item_Ignore,recursive);
      }
     break;

     case PressRed :
      {
       change(index,item,Item_Red,recursive);
      }
     break;

     case PressYellow :
      {
       change(index,item,Item_Yellow,recursive);
      }
     break;

     case PressGreen :
      {
       change(index,item,Item_Green,recursive);
      }
     break;
    }
 }

void InnerDataWindow::hilight(const DrawItem &draw,ulen index,Point point)
 {
  auto items=data.getItems();

  const ItemData &item=items[index];

  if( PressType type=draw(item,point) )
    {
     if( Change(hilight_type,type) | Change(hilight_index,index) ) redraw();
    }
  else
    {
     hilightOff();
    }
 }

InnerDataWindow::InnerDataWindow(SubWindowHost &host,const Config &cfg_,AspectData &data_)
 : SubWindow(host),
   cfg(cfg_),
   data(data_),

   connector_posX(this,&InnerDataWindow::posX),
   connector_posY(this,&InnerDataWindow::posY),
   connector_updated(this,&InnerDataWindow::updated,host.getFrame()->updated)
 {
 }

InnerDataWindow::~InnerDataWindow()
 {
 }

 // methods

Point InnerDataWindow::getMinSize(Point cap) const
 {
  Used(cap);

  Coord dxy=+cfg.dxy;

  return Point(40*dxy,20*dxy);
 }

void InnerDataWindow::update()
 {
  auto items=data.getItems();

  DrawItem draw(cfg,getSize());

  sx.total=0;

  for(const ItemData &item : items )
    {
     Replace_max(sx.total,draw(item));
    }
 }

void InnerDataWindow::update(Filter filter)
 {
  update();

  data_filter=filter;

  updateList();

  sx.beg();
  sy.beg();
 }

void InnerDataWindow::filter(Filter filter)
 {
  data_filter=filter;

  updateList();
 }

void InnerDataWindow::collect()
 {
  data.collect();

  updateList();

  manychanged.assert();
 }

 // drawing

bool InnerDataWindow::isGoodSize(Point size) const
 {
  return size>=getMinSize();
 }

void InnerDataWindow::layout()
 {
  setMax();
 }

void InnerDataWindow::draw(DrawBuf buf,bool) const
 {
  DrawItem draw(cfg,getSize());

  auto items=data.getItems();
  auto vis=data.getVisible();

  Point point=Null;
  Coord dxy=+cfg.dxy;
  ulen off=sx.pos;

  for(ulen i=sy.pos,lim=Min(sy.total,vis.len),line=0; i<lim && line<sy.page ;i++,line++,point=point.addY(dxy))
    {
     ulen ind=vis[i];

     if( ind<items.len )
       {
        const ItemData &item=items[ind];

        draw(buf,BaseX(point,off,item.depth,dxy),item, (ind==hilight_index)?hilight_type:PressNone );
       }
    }

  if( focus )
    {
     draw.frame(buf,getPane());
    }
 }

 // base

void InnerDataWindow::open()
 {
  focus=false;
 }

 // keyboard

FocusType InnerDataWindow::askFocus() const
 {
  return FocusOk;
 }

void InnerDataWindow::gainFocus()
 {
  if( Change(focus,true) ) redraw();
 }

void InnerDataWindow::looseFocus()
 {
  if( Change(focus,false) ) redraw();
 }

 // mouse

void InnerDataWindow::looseCapture()
 {
  // do nothing
 }

MouseShape InnerDataWindow::getMouseShape(Point,KeyMod) const
 {
  return Mouse_Arrow;
 }

 // user input

void InnerDataWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void InnerDataWindow::react_LeftClick(Point point,MouseKey mkey)
 {
  DrawItem draw(cfg,getSize());

  auto res=test(draw,point);

  if( res.index!=MaxULen )
    {
     press(draw,res.index,point-res.base,mkey&MouseKey_Shift);
    }
 }

void InnerDataWindow::react_Move(Point point,MouseKey)
 {
  DrawItem draw(cfg,getSize());

  auto res=test(draw,point);

  if( res.index!=MaxULen )
    {
     hilight(draw,res.index,point-res.base);
    }
 }

void InnerDataWindow::react_Leave()
 {
  hilightOff();
 }

void InnerDataWindow::react_Wheel(Point,MouseKey mkey,Coord delta)
 {
  if( mkey&MouseKey_Shift )
    {
     if( delta>0 )
       subPosX(delta);
     else
       addPosX(-delta);
    }
  else
    {
     if( delta>0 )
       subPosY(delta);
     else
       addPosY(-delta);
    }
 }

/* class DataWindow */

void DataWindow::update_scroll()
 {
  layout();

  redraw();
 }

DataWindow::DataWindow(SubWindowHost &host,const ConfigType &cfg,AspectData &data)
 : ScrollableWindow<InnerDataWindow>(host,cfg,data),

   connector_update_scroll(this,&DataWindow::update_scroll,window.update_scroll),

   changed(window.changed),
   manychanged(window.manychanged)
 {
 }

DataWindow::~DataWindow()
 {
 }

 // methods

void DataWindow::update()
 {
  window.update();
 }

void DataWindow::update(Filter filter)
 {
  window.update(filter);
 }

void DataWindow::filter(Filter filter)
 {
  window.filter(filter);
 }

void DataWindow::collect()
 {
  window.collect();
 }

/* class AspectWindow */

void AspectWindow::setAspect(StrLen file_name)
 {
  StrLen path=Range(data.getPath());

  aspect_file_name=String(file_name);

  RelPath rel(path,file_name);

  if( +rel )
    text_aspect.setText(String(rel.get()));
  else
    text_aspect.setText(aspect_file_name);

  has_file=true;

  btn_save.enable();
 }

void AspectWindow::clearAspect()
 {
  aspect_file_name=Null;

  text_aspect.setText(""_str);

  has_file=false;

  btn_save.disable();
 }

void AspectWindow::errorMsg(StrLen text)
 {
  msg_frame.setInfo(String(text));

  msg_frame.create(getFrame(),+cfg.text_Error);

  disableFrameReact();
 }

void AspectWindow::msg_destroyed()
 {
  enableFrameReact();
 }

void AspectWindow::hide_changed(Filter filter)
 {
  data_window.filter(filter);
 }

void AspectWindow::data_changed(ItemStatus prev,ItemStatus status)
 {
  switch( prev )
    {
     case Item_Red    : count_red.decCount(); break;
     case Item_Yellow : count_yellow.decCount(); break;
     case Item_Green  : count_green.decCount(); break;
    }

  switch( status )
    {
     case Item_Red    : count_red.incCount(); break;
     case Item_Yellow : count_yellow.incCount(); break;
     case Item_Green  : count_green.incCount(); break;
    }

  setModified();
 }

void AspectWindow::data_manychanged()
 {
  updateCount();

  setModified();
 }

void AspectWindow::btn_save_pressed()
 {
  save();
 }

AspectWindow::AspectWindow(SubWindowHost &host,const Config &cfg_,const OptFileName &opt_)
 : ComboWindow(host),
   cfg(cfg_),
   opt(opt_),

   label_path(wlist,cfg.label_cfg,cfg.text_Path),
   label_aspect(wlist,cfg.label_cfg,cfg.text_Aspect),

   text_path(wlist,cfg.text_cfg),
   text_aspect(wlist,cfg.text_cfg),

   line1(wlist,cfg.line_cfg),

   hide(wlist,cfg.hide_cfg),

   count_red(wlist,cfg.count_cfg,+cfg.hide_cfg.status_Red),
   count_yellow(wlist,cfg.count_cfg,+cfg.hide_cfg.status_Yellow),
   count_green(wlist,cfg.count_cfg,+cfg.hide_cfg.status_Green),

   btn_save(wlist,cfg.btn_cfg,cfg.text_Save),

   line2(wlist,cfg.line_cfg),

   data_window(wlist,cfg.data_cfg,data),

   msg_frame(host.getFrameDesktop(),cfg.msg_cfg),

   connector_msg_destroyed(this,&AspectWindow::msg_destroyed,msg_frame.destroyed),
   connector_hide_changed(this,&AspectWindow::hide_changed,hide.changed),
   connector_data_changed(this,&AspectWindow::data_changed,data_window.changed),
   connector_data_manychanged(this,&AspectWindow::data_manychanged,data_window.manychanged),
   connector_btn_save_pressed(this,&AspectWindow::btn_save_pressed,btn_save.pressed)
 {
  wlist.insTop(label_path,label_aspect,text_path,text_aspect,line1,hide,count_red,count_yellow,count_green,btn_save,line2,data_window);

  btn_save.disable();
 }

AspectWindow::~AspectWindow()
 {
 }

 // methods

Point AspectWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  // label_path , label_aspect , text_path , text_aspect

  LayToRightCenter lay1{Lay(label_path),Lay(text_path)};
  LayToRightCenter lay2{Lay(label_aspect),Lay(text_aspect)};

  // count_red , count_yellow , count_green , btn_save

  LayToRightCenter lay3{Lay(count_red),Lay(count_yellow),Lay(count_green),LayLeft(btn_save)};

  // lay

  LayToBottom lay(lay1,lay2,Lay(line1),Lay(hide),lay3,Lay(line2),Lay(data_window));

  return ExtLay(lay).getMinSize(space);
 }

void AspectWindow::blank(StrLen path)
 {
  hide.reset();

  data.blank(path);

  text_path.setText(data.getPath());

  clearAspect();

  setModified();

  update();
 }

void AspectWindow::load(StrLen file_name)
 {
  hide.reset();

  SimpleArray<char> ebuf(64_KByte);

  auto result=data.load(file_name,Range(ebuf));

  if( result.ok )
    {
     text_path.setText(data.getPath());

     setAspect(file_name);
    }
  else
    {
     text_path.setText(""_str);

     clearAspect();

     errorMsg(result.etext);
    }

  if( result.obj )
    setModified();
  else
    clearModified();

  update();
 }

bool AspectWindow::save()
 {
  if( !has_file ) return false;

  SimpleArray<char> ebuf(64_KByte);

  auto result=data.save(Range(aspect_file_name),Range(ebuf));

  if( result.ok )
    {
     clearModified();
    }
  else
    {
     errorMsg(result.etext);
    }

  return true;
 }

void AspectWindow::save(StrLen file_name)
 {
  if( !data )
    {
     errorMsg(+cfg.text_Nothing);

     return;
    }

  setAspect(file_name);

  setModified();

  save();
 }

void AspectWindow::updateCount()
 {
  Counts counts=data.getCounts();

  count_red.setCount(counts.count[Item_Red]);
  count_yellow.setCount(counts.count[Item_Yellow]);
  count_green.setCount(counts.count[Item_Green]);
 }

void AspectWindow::update()
 {
  updateCount();

  data_window.update(hide.getFilter());

  layout();

  redraw();
 }

void AspectWindow::collect()
 {
  data_window.collect();
 }

 // base

void AspectWindow::open()
 {
  ComboWindow::open();

  if( Change(opt.ok,false) )
    {
     NormalPath temp(opt.file_name);

     load(temp.get());
    }
 }

 // drawing

void AspectWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  // label_path , label_aspect , text_path , text_aspect

  LayToRightCenter lay1{Lay(label_path),Lay(text_path)};
  LayToRightCenter lay2{Lay(label_aspect),Lay(text_aspect)};

  // count_red , count_yellow , count_green , btn_save

  LayToRightCenter lay3{Lay(count_red),Lay(count_yellow),Lay(count_green),LayLeft(btn_save)};

  // lay

  LayToBottom lay(lay1,lay2,Lay(line1),Lay(hide),lay3,Lay(line2),Lay(data_window));

  ExtLay(lay).setPlace(getPane(),space);
 }

void AspectWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

} // namespace App

