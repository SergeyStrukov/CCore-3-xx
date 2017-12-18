/* Window.SimpleTextList.h */
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

#ifndef CCore_inc_video_lib_Window_SimpleTextList_h
#define CCore_inc_video_lib_Window_SimpleTextList_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.SimpleTextList.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class SimpleTextListWindowOf;

/* class SimpleTextListWindowOf<Shape> */

template <class Shape>
class SimpleTextListWindowOf : public SubWindow
 {
   Shape shape;

  private:

   void setXOff(Coord xoff)
    {
     if( Change(shape.xoff,Cap<Coord>(0,xoff,shape.xoffMax)) ) redraw();
    }

   void addXOff(Coordinate count)
    {
     Coordinate xoff=shape.xoff+count*shape.dxoff;

     setXOff(+xoff);
    }

   void setYOff(ulen yoff)
    {
     if( Change(shape.yoff,Min(yoff,shape.yoffMax)) ) redraw();
    }

   void addYOff(ulen delta)
    {
     setYOff(AddToCap(shape.yoff,delta,shape.yoffMax));
    }

   void subYOff(ulen delta)
    {
     setYOff(PosSub(shape.yoff,delta));
    }

   void setSelect2(ulen index,ulen count)
    {
     if( !count ) return;

     Replace_min(index,count-1);

     if( Change(shape.select,index) )
       {
        shape.showSelect();

        redraw();

        selected.assert(shape.select);
       }
    }

   void setSelect(ulen index)
    {
     setSelect2(index,shape.info->getLineCount());
    }

   void selectFirst()
    {
     setSelect(0);
    }

   void selectLast()
    {
     if( ulen count=shape.info->getLineCount() )
       {
        setSelect2(count-1,count);
       }
    }

   void addSelect(ulen delta)
    {
     if( ulen count=shape.info->getLineCount() )
       {
        setSelect2(AddToCap(shape.select,delta,count-1),count);
       }
    }

   void subSelect(ulen delta)
    {
     setSelect(PosSub(shape.select,delta));
    }

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   SimpleTextListWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~SimpleTextListWindowOf()
    {
    }

   // methods

   auto getMinSize(unsigned flags,Point cap=Point::Max()) const { return shape.getMinSize(flags&LayoutUpdate,cap); }

   bool isEnabled() const { return shape.enable; }

   void enable(bool enable=true)
    {
     if( Change(shape.enable,enable) ) redraw();
    }

   void disable() { enable(false); }

   void setInfo(const Info &info)
    {
     shape.info=info;
     shape.yoff=0;
     shape.xoff=0;

     shape.initSelect();

     shape.setMax(LayoutUpdate);

     redraw();
    }

   const Info & getInfo() const { return shape.info; }

   ulen getSelect() const { return shape.select; } // valid OR MaxULen, if there is no positions

   bool select(ulen index)
    {
     ulen count=shape.info->getLineCount();

     if( !count )
       {
        shape.select=MaxULen;

        return false;
       }

     Replace_min(index,count-1);

     if( Change(shape.select,index) )
       {
        shape.showSelect();

        redraw();
       }

     return true;
    }

   bool reselect()
    {
     return select(shape.select);
    }

   void ping()
    {
     ulen count=shape.info->getLineCount();

     if( shape.select<count )
       {
        selected.assert(shape.select);
       }
    }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout(unsigned flags)
    {
     shape.pane=Pane(Null,getSize());

     shape.setMax(flags&LayoutUpdate);
    }

   virtual void draw(DrawBuf buf,bool) const
    {
     shape.draw(buf);
    }

   // base

   virtual void open()
    {
     shape.focus=false;
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

   virtual void looseCapture()
    {
     // do nothing
    }

   virtual MouseShape getMouseShape(Point,KeyMod) const
    {
     return Mouse_Arrow;
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     if( vkey==VKey_Tab )
       {
        tabbed.assert(kmod&KeyMod_Shift);

        return;
       }

     if( !shape.enable ) return;

     switch( vkey )
       {
        case VKey_Left :
         {
          addXOff(-CountToCoordinate(repeat));
         }
        break;

        case VKey_Right :
         {
          addXOff(CountToCoordinate(repeat));
         }
        break;

        case VKey_Up :
         {
          if( kmod&KeyMod_Shift )
            {
             subYOff(repeat);
            }
          else
            {
             subSelect(repeat);
            }
         }
        break;

        case VKey_Down :
         {
          if( kmod&KeyMod_Shift )
            {
             addYOff(repeat);
            }
          else
            {
             addSelect(repeat);
            }
         }
        break;

        case VKey_PageUp :
         {
          ulen delta=shape.page*repeat;

          subYOff(delta);
          subSelect(delta);
         }
        break;

        case VKey_PageDown :
         {
          ulen delta=shape.page*repeat;

          addYOff(delta);
          addSelect(delta);
         }
        break;

        case VKey_Home :
         {
          selectFirst();
         }
        break;

        case VKey_End :
         {
          selectLast();
         }
        break;

        case VKey_Enter :
         {
          entered.assert();
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     if( !shape.enable ) return;

     setSelect(shape.getPosition(point));
    }

   void react_LeftDClick(Point,MouseKey)
    {
     if( !shape.enable ) return;

     dclicked.assert();
    }

   void react_Wheel(Point,MouseKey mkey,Coord delta_)
    {
     if( !shape.enable ) return;

     ulen delta=IntAbs(delta_);

     if( delta_<0 )
       {
        if( mkey&MouseKey_Shift )
          {
           addYOff(delta);
          }
        else
          {
           addSelect(delta);
          }
       }
     else
       {
        if( mkey&MouseKey_Shift )
          {
           subYOff(delta);
          }
        else
          {
           subSelect(delta);
          }
       }
    }

   // signals

   Signal<> entered;
   Signal<> dclicked;
   Signal<ulen> selected; // select, always valid
   Signal<bool> tabbed; // shift
 };

/* type SimpleTextListWindow */

using SimpleTextListWindow = SimpleTextListWindowOf<SimpleTextListShape> ;

} // namespace Video
} // namespace CCore

#endif

