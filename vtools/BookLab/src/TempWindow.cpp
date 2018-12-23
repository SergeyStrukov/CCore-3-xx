/* TempWindow.cpp */
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

#include <inc/TempWindow.h>

#include <CCore/inc/video/LayoutCombo.h>
#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/algon/SimpleRotate.h>

#include <CCore/inc/RangeDel.h>
#include <CCore/inc/ForLoop.h>

namespace App {

/* class SlotWindow */

TempSlot * SlotWindow::ref(ulen slot)
 {
  return list.at(slot).getPtr();
 }

void SlotWindow::append()
 {
  list.append_fill(OwnPtr<TempSlot>(new TempSlot(book)));
 }

void SlotWindow::moveUp()
 {
  if( cur>0 )
    {
     cur--;

     if( cur<off ) off=cur;

     Swap(list[cur],list[cur+1]);

     slotChanged.assert();

     redraw();
    }
 }

void SlotWindow::moveDown()
 {
  ulen count=list.getLen();

  if( cur<count-1 )
    {
     cur++;

     if( off+len<=cur ) off=cur-len+1;

     Swap(list[cur],list[cur-1]);

     slotChanged.assert();

     redraw();
    }
 }

void SlotWindow::curUp()
 {
  if( cur>0 )
    {
     cur--;

     if( cur<off ) off=cur;

     slotChanged.assert();

     redraw();
    }
 }

void SlotWindow::curDown()
 {
  ulen count=list.getLen();

  if( cur<count-1 )
    {
     cur++;

     if( off+len<=cur ) off=cur-len+1;

     slotChanged.assert();

     redraw();
    }
 }

SlotWindow::SlotWindow(SubWindowHost &host,const Config &cfg_,BookLab::Book &book_)
 : SubWindow(host),
   cfg(cfg_),
   book(book_),

   list(DoReserve,100)
 {
  append();
 }

SlotWindow::~SlotWindow()
 {
 }

 // methods

Point SlotWindow::getMinSize() const
 {
  const Font &font=cfg.text_font.get();

  Coord cell_dy=font->getSize().dy;
  Coord table_dxy=+cfg.table_dxy;

  Coord dy=5*cell_dy+6*table_dxy;

  return Point(3*dy,dy);
 }

void SlotWindow::setPos(ulen pos)
 {
  if( Change(off,Min(pos,getMaxPos())) ) redraw();
 }

BookLab::TempData & SlotWindow::refSlot(ulen slot)
 {
  return ref(slot)->data;
 }

BookLab::TempData & SlotWindow::freeSlot()
 {
  if( ref(0)->notEmpty() )
    {
     append();

     Algon::RangeRotateRight(Range(list));

     off=0;
     cur=0;

     layout();

     redraw();
    }

  return refSlot(0);
 }

void SlotWindow::setCurName(String name)
 {
  ref(cur)->name=name;

  if( cur==0 )
    {
     append();

     Algon::RangeRotateRight(Range(list));

     off=0;

     layout();
    }

  redraw();
 }

void SlotWindow::delCurSlot()
 {
  ulen count=list.getLen();

  if( count==1 && cur==0 )
    {
     list[0]->erase();

     layout();

     redraw();

     return;
    }

  if( count>1 && RangeSwapDel(Range(list),cur) )
    {
     list.shrink_one();

     Replace_min(cur,count-2);

     slotChanged.assert();

     layout();

     redraw();
    }
 }

 // drawing

void SlotWindow::layout()
 {
  const Font &font=cfg.text_font.get();

  cell_dy=font->getSize().dy;
  cell_dx=cell_dy;

  for(OwnPtr<TempSlot> &ptr : list )
    {
     TextSize ts=font->text(ptr->data.getTypeName());

     Replace_max(cell_dx,ts.full_dx);
    }

  Coord table_dxy=+cfg.table_dxy;
  Coord dy=getSize().y;

  len = (ulen)Sup(0,(dy-table_dxy)/(cell_dy+table_dxy)) ;

  ulen count=list.getLen();

  Replace_min(len,count);
  Replace_min(off,count-len);

  reposed.assert({count,len,off});
 }

void SlotWindow::draw(DrawBuf buf,bool) const
 {
  Fraction line_width=+cfg.line_width;
  Coord table_dxy=+cfg.table_dxy;
  const Font &font=cfg.text_font.get();
  VColor table=+cfg.table;
  VColor text=+cfg.text;

  Coord wlen=getSize().x;

  SmoothDrawArt art(buf);

  // table
  {
   MPoint A=Point::Diag(table_dxy-1);

   A=A/2;

   MCoord tdx=Fraction(wlen-table_dxy);
   MCoord tdy=Fraction(cell_dy+table_dxy);

   {
    MPoint O=A;
    MCoord flen=tdx;
    MCoord delta=tdy;

    art.path(line_width,table,O,O.addX(flen));

    for(ulen cnt=len; cnt ;cnt--)
      {
       O=O.addY(delta);

       art.path(line_width,table,O,O.addX(flen));
      }
   }

   {
    MPoint O=A;
    MCoord flen=MCoord(len)*tdy;

    art.path(line_width,table,O,O.addY(flen));

    O=A.addX(Fraction(cell_dx+table_dxy));

    art.path(line_width,table,O,O.addY(flen));

    O=A.addX(tdx);

    art.path(line_width,table,O,O.addY(flen));
   }
  }

  // fill table
  {
   Point a=Point::Diag(table_dxy);
   Point b=a.addX(cell_dx+table_dxy);

   Coord delta=cell_dy+table_dxy;
   Coord name_dx=wlen-table_dxy-b.x;

   for(ulen i : IndLim(off,off+len) )
     {
      if( i==cur )
        {
         VColor vc = focus? +cfg.cursor : +cfg.gray_cursor ;

         art.block(Pane(a,cell_dx,cell_dy),vc);
         art.block(Pane(b,name_dx,cell_dy),vc);
        }

      TempSlot *slot=list[i].getPtr();

      font->text(buf,Pane(a,cell_dx,cell_dy),TextPlace(AlignX_Left,AlignY_Top),slot->data.getTypeName(),text);
      font->text(buf,Pane(b,name_dx,cell_dy),TextPlace(AlignX_Left,AlignY_Top),Range(slot->name),text);

      a.y+=delta;
      b.y+=delta;
     }
  }
 }

 // keyboard

void SlotWindow::gainFocus()
 {
  if( Change(focus,true) ) redraw();
 }

void SlotWindow::looseFocus()
 {
  if( Change(focus,false) ) redraw();
 }

 // user input

void SlotWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void SlotWindow::react_Key(VKey vkey,KeyMod kmod,unsigned)
 {
  switch( vkey )
    {
     case VKey_Up :
      {
       if( kmod&KeyMod_Shift )
         {
          moveUp();
         }
       else
         {
          curUp();
         }
      }
     break;

     case VKey_Down :
      {
       if( kmod&KeyMod_Shift )
         {
          moveDown();
         }
       else
         {
          curDown();
         }
      }
     break;
    }
 }

void SlotWindow::react_LeftClick(Point point,MouseKey)
 {
  Coord table_dxy=+cfg.table_dxy;
  Coord delta=cell_dy+table_dxy;

  Coord ind=point.y/delta;
  Coord y=point.y%delta;

  if( y>=table_dxy && ind>=0 )
    {
     ulen i=(ulen)ind;

     if( i<len )
       {
        i+=off;

        if( i<list.getLen() && Change(cur,i) )
          {
           slotChanged.assert();

           redraw();
          }
       }
    }
 }

void SlotWindow::react_Wheel(Point,MouseKey mkey,Coord delta)
 {
  if( mkey&MouseKey_Shift )
    {
     if( delta>0 )
       {
        moveUp();
       }
     else
       {
        moveDown();
       }
    }
  else
    {
     if( delta>0 )
       {
        curUp();
       }
     else
       {
        curDown();
       }
    }
 }

/* class TempWindow */

void TempWindow::copy_pressed()
 {
  askCopy.assert(slots.getCurSlot());
 }

void TempWindow::past_pressed()
 {
  askPast.assert(slots.getCurSlot());
 }

void TempWindow::del_pressed()
 {
  slots.delCurSlot();
 }

void TempWindow::name_pressed()
 {
  slots.setCurName(edit.getString());
 }

void TempWindow::slots_reposed(ScrollPos pos)
 {
  scroll.setRange(pos);
 }

void TempWindow::scroll_changed(ulen pos)
 {
  slots.setPos(pos);
 }

void TempWindow::slot_changed()
 {
  askProbe.assert();
 }

TempWindow::TempWindow(SubWindowHost &host,const Config &cfg_,BookLab::Book &book)
 : ComboWindow(host),
   cfg(cfg_),

   btn_copy(wlist,cfg.btn_cfg,cfg.text_Copy),
   btn_past(wlist,cfg.btn_cfg,cfg.text_Past),
   btn_del(wlist,cfg.btn_cfg,cfg.text_Del),
   btn_name(wlist,cfg.btn_cfg,cfg.text_Name),

   edit(wlist,cfg.edit_cfg),

   scroll(wlist,cfg.scroll_cfg),
   slots(wlist,cfg.slot_cfg,book),

   connector_copy_pressed(this,&TempWindow::copy_pressed,btn_copy.pressed),
   connector_past_pressed(this,&TempWindow::past_pressed,btn_past.pressed),
   connector_del_pressed(this,&TempWindow::del_pressed,btn_del.pressed),
   connector_name_pressed(this,&TempWindow::name_pressed,btn_name.pressed),
   connector_slots_reposed(this,&TempWindow::slots_reposed,slots.reposed),
   connector_scroll_changed(this,&TempWindow::scroll_changed,scroll.changed),
   connector_slot_changed(this,&TempWindow::slot_changed,slots.slotChanged)
 {
  wlist.insTop(btn_copy,btn_past,btn_del,btn_name,edit,scroll,slots);
 }

TempWindow::~TempWindow()
 {
 }

 // methods

Point TempWindow::getMinSize() const
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(btn_copy),Lay(btn_past),Lay(btn_del),Lay(btn_name),Lay(edit)};

  LayToRight lay2{Lay(scroll),Lay(slots)};

  LayToBottom lay{lay1,lay2};

  return ExtLay(lay).getMinSize(space);
 }

bool TempWindow::copy(BookLab::Ref cursor)
 {
  if( slots.freeSlot().copy(cursor) )
    {
     slots.layout();
     slots.redraw();

     return true;
    }

  return false;
 }

bool TempWindow::copy(ulen slot,BookLab::Ref cursor)
 {
  if( slots.refSlot(slot).copy(cursor) )
    {
     slots.layout();
     slots.redraw();

     return true;
    }

  return false;
 }

bool TempWindow::past(ulen slot,BookLab::Ref cursor)
 {
  return slots.refSlot(slot).past(cursor);
 }

void TempWindow::probe(BookLab::Ref cursor)
 {
  ulen slot=slots.getCurSlot();

  auto result=slots.refSlot(slot).probe(cursor);

  btn_copy.enable(result.copy);
  btn_past.enable(result.past);
 }

 // drawing

void TempWindow::layout()
 {
  Coord space=+cfg.space_dxy;

  LayToRightCenter lay1{Lay(btn_copy),Lay(btn_past),Lay(btn_del),Lay(btn_name),Lay(edit)};

  LayToRight lay2{Lay(scroll),Lay(slots)};

  LayToBottom lay{lay1,lay2};

  ExtLay(lay).setPlace(getPane(),space);
 }

void TempWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(+cfg.back);
 }

 // user input

void TempWindow::react(UserAction action)
 {
  action.dispatch(*this, [this] (UserAction action) { wlist.react(action); } );
 }

void TempWindow::react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
 {
  switch( vkey )
    {
     case VKey_Delete :
      {
       del_pressed();
      }
     return;
    }

  wlist.put_Key(vkey,kmod,repeat);
 }

/* class TempFrame */

TempFrame::TempFrame(Desktop *desktop,const Config &cfg_,BookLab::Book &book,Signal<> &update)
 : DragFrame(desktop,cfg_.frame_cfg,update),
   cfg(cfg_),

   client(*this,cfg.client_cfg,book),

   askCopy(client.askCopy),
   askPast(client.askPast),
   askProbe(client.askProbe)
 {
  bindClient(client);
 }

TempFrame::~TempFrame()
 {
 }

 // base

void TempFrame::dying()
 {
  DragFrame::dying();

  place.set(host->getPlace());
 }

 // create

Pane TempFrame::getPane(StrLen title) const
 {
  Point size=getMinSize(false,title,client.getMinSize());

  if( place.ok ) return place.get(size);

  return GetWindowPlace(desktop,+cfg.pos_ry,size);
 }

} // namespace App

