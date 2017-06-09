/* Window.Radio.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_lib_Window_Radio_h
#define CCore_inc_video_lib_Window_Radio_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.Radio.h>

namespace CCore {
namespace Video {

/* classes */

class RadioItem;

class RadioGroup;

template <class Shape> class RadioWindowOf;

/* class RadioItem */

class RadioItem : NoCopy
 {
   int radio_id;

   DLink<RadioItem> link;
   RadioGroup *group = 0 ;

  protected:

   void setCheck(bool signal);

   virtual void check(bool check)=0;

   virtual void uncheck()=0;

   friend class RadioGroup;

  public:

   explicit RadioItem(int radio_id);

   ~RadioItem();
 };

/* class RadioGroup */

class RadioGroup : NoCopy
 {
   using Algo = DLink<RadioItem>::LinearAlgo<&RadioItem::link> ;

   Algo::FirstLast list;
   RadioItem *cur = 0 ;

   friend class RadioItem;

  public:

   RadioGroup();

   ~RadioGroup();

   void add(RadioItem *item);

   void del(RadioItem *item);

   void add(RadioItem &item) { add(&item); }

   template <class ... TT>
   void add(RadioItem *item,TT * ... tt)
    {
     add(item);

     add(tt...);
    }

   template <class ... TT>
   void add(RadioItem &item,TT && ... tt)
    {
     add(item);

     add(tt...);
    }

   // signals

   Signal<int,int> changed; // new_id , prev_id
 };

/* class RadioWindowOf<Shape> */

template <class Shape>
class RadioWindowOf : public SubWindow , public RadioItem
 {
   Shape shape;

  private:

   void inside()
    {
     if( Change(shape.mover,true) ) redraw();
    }

   void outside()
    {
     if( Change(shape.mover,false) ) redraw();
    }

   void select(bool signal=true)
    {
     if( Change(shape.check,true) )
       {
        setCheck(signal);

        redraw();
       }
    }

   // RadioItem

   virtual void check(bool check)
    {
     shape.check=check;
    }

   virtual void uncheck()
    {
     shape.check=false;

     redraw();
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   RadioWindowOf(SubWindowHost &host,int radio_id,TT && ... tt)
    : SubWindow(host),
      RadioItem(radio_id),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~RadioWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   bool isChecked() const { return shape.check; }

   void check() { select(false); }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout()
    {
     shape.pane=Pane(Null,getSize());
    }

   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }

   // base

   virtual void open()
    {
     shape.focus=false;
     shape.mover=false;
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return shape.enable?FocusOk:NoFocus;
    }

   virtual void gainFocus()
    {
     if( Change(shape.focus,true) ) redraw();
    }

   virtual void looseFocus()
    {
     if( Change(shape.focus,false) ) redraw();
    }

   // mouse

   virtual MouseShape getMouseShape(Point,KeyMod) const
    {
     return shape.enable?Mouse_Hand:Mouse_Arrow;
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_Enter :
        case VKey_Space :
         {
          if( shape.enable ) select();
         }
        break;

        case VKey_Tab :
         {
          tabbed.assert(kmod&KeyMod_Shift);
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     if( shape.enable && shape.pane.contains(point) ) select();
    }

   void react_Move(Point point,MouseKey)
    {
     if( shape.pane.contains(point) )
       {
        inside();
       }
     else
       {
        outside();
       }
    }

   void react_Leave()
    {
     outside();
    }

   // signals

   Signal<bool> tabbed; // shift
 };

/* type RadioWindow */

using RadioWindow = RadioWindowOf<RadioShape> ;

} // namespace Video
} // namespace CCore

#endif

