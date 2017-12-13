/* Window.DragFrame.h */
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

#ifndef CCore_inc_video_lib_Window_DragFrame_h
#define CCore_inc_video_lib_Window_DragFrame_h

#include <CCore/inc/video/SubWindow.h>

#include <CCore/inc/video/lib/Shape.DragFrame.h>
#include <CCore/inc/video/lib/Shape.FixedFrame.h>

namespace CCore {
namespace Video {

/* classes */

template <class Shape> class DragFrameOf;

/* class DragWindowOf<Shape> */

template <class Shape>
class DragFrameOf : public FrameWindow , public SubWindowHost
 {
   Shape shape;

   SubWindow *client = 0 ;
   SubWindow *alert_client = 0 ;

   AliveControl *client_ac = &AliveControl::Default ;
   AliveControl *alert_client_ac = &AliveControl::Default ;

   Point size;

   Point drag_base;

   bool client_enter = false ;
   bool client_capture = false ;
   bool delay_draw = false ;
   bool enable_react = true ;

   RedrawSet redraw_set;

   Hint cur_hint;

  private:

   void guardClient()
    {
     if( !client ) GuardNoClient();
    }

   void guardDead()
    {
     if( isAlive() ) GuardNotDead();
    }

   void reset()
    {
     size=Null;
     client_enter=false;
     client_capture=false;
     delay_draw=false;
     enable_react=true;

     redraw_set.pop();
     cur_hint=Nothing;
    }

   void assert_moved(Point from,Point to)
    {
     if( from!=to ) moved.assert(to-from);
    }

   void setMaxButton() requires ( Shape::EnableMaximize )
    {
     if( Change(shape.max_button,true) ) redrawFrame(DragType_Max);
    }

   void setMaxButton() requires ( !Shape::EnableMaximize )
    {
    }

   void replace(Pane place,Point delta,DragType drag_type)
    {
     Point base=place.getBase();

     DragPane(place,delta,drag_type);

     Point new_size=place.getSize();

     if( new_size>=shape.getMinSize() && new_size<=host->getMaxSize() )
       {
        Pane screen=Pane(Null,desktop->getScreenSize());

        if( +Inf(place,screen) )
          {
           setMaxButton();

           host->setPlace(place);

           host->invalidate(1);

           assert_moved(base,place.getBase());
          }
       }
    }

   void replace(Point delta,DragType drag_type)
    {
     Pane place=host->getPlace();

     replace(place,delta,drag_type);
    }

   void startDrag(Point point,DragType drag_type)
    {
     shape.drag_type=drag_type;

     if( !client_capture ) host->captureMouse();

     Pane place=host->getPlace();

     drag_base=point+place.getBase();

     redrawAll();
    }

   void dragTo(Point point)
    {
     Pane place=host->getPlace();

     Point delta=Diff(drag_base,point+place.getBase());

     replace(place,delta,shape.drag_type);
    }

   void endDrag()
    {
     shape.drag_type=DragType_None;

     redrawAll();
    }

   void endDrag(Point point)
    {
     dragTo(point);

     shape.drag_type=DragType_None;

     if( !client_capture ) host->releaseMouse();

     redrawAll();
    }

   void btnDown(DragType drag_type)
    {
     shape.btn_type=drag_type;

     redrawFrame(drag_type);
    }

   void btnUp(Point point)
    {
     DragType type=Replace(shape.btn_type,DragType_None);

     redrawFrame(type);

     if( shape.dragTest(point)==type )
       {
        switch( type )
          {
           case DragType_Alert : switchClients(); break;

           case DragType_Help  : help(); break;

           case DragType_Min   : try_minimize(); break;

           case DragType_Max   : try_maximize(); break;

           case DragType_Close : askClose(); break;
          }
       }
    }

   void moveBtn(Point point)
    {
     if( shape.dragTest(point)!=shape.btn_type ) endBtn();
    }

   void endBtn()
    {
     redrawFrame(Replace(shape.btn_type,DragType_None));
    }

   void hilightFrame(Point point)
    {
     DragType drag_type=shape.hilightTest(point);

     if( drag_type!=shape.hilight )
       {
        DragType type=Replace(shape.hilight,drag_type);

        redrawFrame(type);
        redrawFrame(drag_type);
       }
    }

   void endHilightFrame()
    {
     if( shape.hilight )
       {
        redrawFrame(Replace(shape.hilight,DragType_None));
       }
    }

   void try_minimize() requires ( !Shape::EnableMinimize )
    {
    }

   void try_maximize() requires ( !Shape::EnableMaximize )
    {
    }

   void try_minimize() requires ( Shape::EnableMinimize )
    {
     minimize();
    }

   void try_maximize() requires ( Shape::EnableMaximize )
    {
     maximize();
    }

   bool forwardKey(VKey vkey,KeyMod kmod,unsigned repeat=1)
    {
     if( kmod&KeyMod_Alt )
       {
        switch( Shape::Filter(vkey,kmod) )
          {
           case VKey_Left  : replace(Point(-(Coord)repeat,0),(kmod&KeyMod_Shift)?DragType_Right:DragType_Bar); return true;

           case VKey_Right : replace(Point((Coord)repeat,0),(kmod&KeyMod_Shift)?DragType_Right:DragType_Bar); return true;

           case VKey_Up    : replace(Point(0,-(Coord)repeat),(kmod&KeyMod_Shift)?DragType_Bottom:DragType_Bar); return true;

           case VKey_Down  : replace(Point(0,(Coord)repeat),(kmod&KeyMod_Shift)?DragType_Bottom:DragType_Bar); return true;

           case VKey_F2    : try_minimize(); return true;

           case VKey_F3    : try_maximize(); return true;

           case VKey_F4    : askClose(); return true;

           case VKey_F12   : switchClients(); return true;

           default: return false;
          }
       }
     else
       {
        switch( Shape::Filter(vkey,kmod) )
          {
           case VKey_F1    : help(true); return true;

           default: return false;
          }
       }
    }

   bool forwardKeyUp(VKey vkey,KeyMod kmod,unsigned =1)
    {
     if( kmod&KeyMod_Alt )
       {
        switch( Shape::Filter(vkey,kmod) )
          {
           case VKey_Left  :
           case VKey_Right :
           case VKey_Up    :
           case VKey_Down  :
           case VKey_F2    :
           case VKey_F3    :
           case VKey_F4    :
           case VKey_F12   : return true;

           default: return false;
          }
       }
     else
       {
        switch( Shape::Filter(vkey,kmod) )
          {
           case VKey_F1    : help(false); return true;

           default: return false;
          }
       }
    }

   SubWindow & getClient()
    {
     if( alert_client && shape.alert_type==AlertType_Opened ) return *alert_client;

     guardClient();

     return *client;
    }

   void shade(FrameBuf<DesktopColor> &buf)
    {
     if( !enable_react ) shape.shade(buf);
    }

   void shade(FrameBuf<DesktopColor> &buf,Pane pane)
    {
     if( !enable_react ) shape.shade(buf,pane);
    }

   void shadeOuter(FrameBuf<DesktopColor> &buf,Pane client)
    {
     if( !enable_react )
       {
        PaneSub sub(buf.getPane(),client);

        shape.shade(buf,sub.top);
        shape.shade(buf,sub.bottom);
        shape.shade(buf,sub.left);
        shape.shade(buf,sub.right);
       }
    }

   void shadeOuter(FrameBuf<DesktopColor> &buf,Pane client,Pane pane)
    {
     if( !enable_react )
       {
        PaneSub sub(buf.getPane(),client);

        shape.shade(buf,Inf(sub.top,pane));
        shape.shade(buf,Inf(sub.bottom,pane));
        shape.shade(buf,Inf(sub.left,pane));
        shape.shade(buf,Inf(sub.right,pane));
       }
    }

   void redrawBuf(FuncArgType<FrameBuf<DesktopColor> &> func)
    {
     if( host->isDead() ) return;

     if( host->getToken() )
       {
        delay_draw=true;

        return;
       }

     FrameBuf<DesktopColor> buf(host->getDrawPlane());

     if( size<=buf.getSize() )
       {
        func(buf);

        if( shape.help )
          {
           shape.drawHint(buf,cur_hint);

           host->invalidate(1);
          }
       }
     else
       {
        buf.erase(Black);

        host->invalidate(1);
       }
    }

   void redrawFrame()
    {
     redrawBuf( [this] (FrameBuf<DesktopColor> &buf)
                       {
                        try { shape.draw(buf); } catch(...) {}

                        Pane client=shape.getClient();

                        shadeOuter(buf,client);

                        host->invalidate(1);

                       } );
    }

   void redrawFrame(DragType drag_type)
    {
     Pane pane=shape.getPane(drag_type);

     if( !pane ) return;

     redrawBuf( [this,drag_type,pane] (FrameBuf<DesktopColor> &buf)
                                      {
                                       try { shape.draw(buf,drag_type); } catch(...) {}

                                       Pane client=shape.getClient();

                                       shadeOuter(buf,client,pane);

                                       host->invalidate(pane,1);

                                      } );
    }

   void redrawAll(unsigned flags=NoLayout)
    {
     if( flags )
       {
        shape.layout(size);

        Pane place=shape.getClient();

        if( client ) client->setPlace(place,flags);

        if( alert_client ) alert_client->setPlace(place,flags);
       }

     auto &client=getClient();

     shape.has_good_size=client.hasGoodSize();

     redraw_set.pop();

     redrawBuf( [this,&client] (FrameBuf<DesktopColor> &buf)
                               {
                                try { shape.draw(buf); } catch(...) {}

                                client.forward_draw(buf,shape.drag_type);

                                shade(buf);

                                host->invalidate(1);

                               } );
    }

   void redrawSet()
    {
     auto &client=getClient();

     if( Change(shape.has_good_size,client.hasGoodSize()) ) redrawFrame();

     auto r=redraw_set.pop();

     if( !r ) return;

     redrawBuf( [this,r,&client] (FrameBuf<DesktopColor> &buf_)
                                 {
                                  DrawBuf buf(buf_);

                                  for(Pane pane : r )
                                    {
                                     client.forward_draw(buf.cut(pane),pane,shape.drag_type);

                                     shade(buf_,pane);

                                     host->invalidate(pane,1);
                                    }

                                 } );
    }

   void pushAlertBlink()
    {
     if( shape.resetTime() ) defer_tick.start();
    }

   void tick()
    {
     if( shape.checkTime() )
       {
        if( shape.tick() )
          {
           shape.alert_blink=!shape.alert_blink;

           redrawFrame(DragType_Alert);
          }
       }
     else
       {
        defer_tick.stop();

        shape.alert_blink=false;

        redrawFrame(DragType_Alert);
       }
    }

   void switchClients()
    {
     if( shape.alert_type && alert_client )
       {
        getClient().close();

        shape.alert_type=(shape.alert_type==AlertType_Closed)?AlertType_Opened:AlertType_Closed;

        getClient().open();

        redrawAll();
       }
    }

   void help()
    {
     help(!shape.help);
    }

   void help(bool on)
    {
     if( Change(shape.help,on) )
       {
        if( on )
          {
           Point point=host->getMousePos();

           cur_hint=getClient().getHint(point);
          }

        redrawAll();
       }
    }

   void hint(Point point)
    {
     Hint hint=shape.getHint(point);

     if( +hint )
       setHint(hint);
     else
       setHint(getClient().getHint(point));
    }

   void setHint(Hint hint)
    {
     if( cur_hint.pane!=hint.pane )
       {
        cur_hint=hint;

        redrawAll();
       }
    }

   void endHint()
    {
     setHint(Nothing);
    }

  public:

   using ShapeType = Shape ;

   using ConfigType = typename Shape::Config ;

   DragFrameOf(Desktop *desktop,const ConfigType &cfg)
    : FrameWindow(desktop),
      shape(cfg),
      input(this),
      connector_update(this,&DragFrameOf<Shape>::update),
      connector_alert(this,&DragFrameOf<Shape>::alert)
    {
     defer_tick=input.create(&DragFrameOf<Shape>::tick);
    }

   DragFrameOf(Desktop *desktop,const ConfigType &cfg,Signal<> &update)
    : DragFrameOf(desktop,cfg)
    {
     connector_update.connect(update);
    }

   virtual ~DragFrameOf()
    {
    }

   // methods

   Point getDeltaSize() const { return shape.getDeltaSize(); }

   Point getMinSize(bool is_main,StrLen title,Point size) const { return shape.getMinSize(is_main,title,size); }

   void bindClient(SubWindow &client_)
    {
     guardDead();

     client=&client_;
     client_ac=client_.getAliveControl();
    }

   void bindAlertClient(SubWindow &alert_client_) requires ( Shape::EnableAlert )
    {
     guardDead();

     alert_client=&alert_client_;
     alert_client_ac=alert_client_.getAliveControl();
    }

   void connectUpdate(Signal<> &update)
    {
     connector_update.connect(update);
    }

   void connectAlert(Signal<> &update) requires ( Shape::EnableAlert )
    {
     connector_alert.connect(update);
    }

   void createMain(CmdDisplay cmd_display,Point max_size,const DefString &title) requires ( !Shape::EnableFixed )
    {
     guardClient();
     guardDead();

     shape.reset(title,true, cmd_display!=CmdDisplay_Maximized );

     host->createMain(max_size);
     host->setTitle(title.str());
     host->display(cmd_display);
    }

   void createMain(CmdDisplay cmd_display,Pane pane,Point max_size,const DefString &title) requires ( !Shape::EnableFixed )
    {
     guardClient();
     guardDead();

     shape.reset(title,true, cmd_display!=CmdDisplay_Maximized );

     host->createMain(pane,max_size);
     host->setTitle(title.str());
     host->display(cmd_display);
    }

   void createMain(CmdDisplay cmd_display,const DefString &title) requires ( !Shape::EnableFixed )
    {
     Point max_size=getScreenSize();

     createMain(cmd_display,max_size,title);
    }

   void createMain(CmdDisplay cmd_display,Pane pane,const DefString &title) requires ( !Shape::EnableFixed )
    {
     Point max_size=getScreenSize();

     createMain(cmd_display,pane,max_size,title);
    }

   void create(Pane pane,Point max_size,const DefString &title) requires ( !Shape::EnableFixed )
    {
     guardClient();
     guardDead();

     shape.reset(title,false,true);

     host->create(pane,max_size);
     host->show();
    }

   void create(FrameWindow *parent,Pane pane,Point max_size,const DefString &title) requires ( !Shape::EnableFixed )
    {
     guardClient();
     guardDead();

     shape.reset(title,false,true);

     host->create(parent->getHost(),pane,max_size);
     host->show();
    }

   void create(Pane pane,const DefString &title) requires ( !Shape::EnableFixed )
    {
     Point max_size=getScreenSize();

     create(pane,max_size,title);
    }

   void create(FrameWindow *parent,Pane pane,const DefString &title) requires ( !Shape::EnableFixed )
    {
     Point max_size=getScreenSize();

     create(parent,pane,max_size,title);
    }

   void createMain(Pane pane,const DefString &title) requires ( Shape::EnableFixed )
    {
     guardClient();
     guardDead();

     shape.reset(title,true);

     host->createMain(pane,pane.getSize());
     host->setTitle(title.str());
     host->display(CmdDisplay_Normal);
    }

   void create(Pane pane,const DefString &title) requires ( Shape::EnableFixed )
    {
     guardClient();
     guardDead();

     shape.reset(title,false);

     host->create(pane,pane.getSize());
     host->show();
    }

   void create(FrameWindow *parent,Pane pane,const DefString &title) requires ( Shape::EnableFixed )
    {
     guardClient();
     guardDead();

     shape.reset(title,false);

     host->create(parent->getHost(),pane,pane.getSize());
     host->show();
    }

   void minimize() requires ( Shape::EnableMinimize )
    {
     if( shape.is_main ) host->display(CmdDisplay_Minimized);
    }

   void maximize() requires ( Shape::EnableMaximize )
    {
     if( shape.max_button )
       {
        shape.max_button=false;

        redrawFrame(DragType_Max);

        host->display(CmdDisplay_Maximized);
       }
     else
       {
        shape.max_button=true;

        redrawFrame(DragType_Max);

        host->display(CmdDisplay_Restore);
       }
    }

   void setTitle(const DefString &title)
    {
     shape.title=title;

     host->setTitle(title.str());

     redrawFrame();
    }

   // SubWindowHost

   virtual FrameWindow * getFrame() noexcept
    {
     return this;
    }

   virtual Point getScreenOrigin() noexcept
    {
     try { return host->getPlace().getBase(); } catch(...) { return Null; }
    }

   virtual void redraw(Pane pane)  noexcept
    {
     try { if( redraw_set.add(pane) ) input.redrawSet(); } catch(...) {}
    }

   virtual void setFocus(SubWindow *) noexcept
    {
     if( shape.has_focus )
       {
        try { getClient().gainFocus(); } catch(...) {}
       }
    }

   virtual void captureMouse(SubWindow *) noexcept
    {
     if( !client_capture )
       {
        client_capture=true;

        if( !shape.drag_type ) try { host->captureMouse(); } catch(...) {}
       }
    }

   virtual void releaseMouse(SubWindow *) noexcept
    {
     if( client_capture )
       {
        client_capture=false;

        if( !shape.drag_type ) try { host->releaseMouse(); } catch(...) {}
       }
    }

   // base

   virtual void alive()
    {
     reset();

     host->trackMouseHover();
     host->trackMouseLeave();

     client_ac->alive();
     alert_client_ac->alive();

     getClient().open();
    }

   virtual void dying()
    {
     client_ac->dying();
     alert_client_ac->dying();
    }

   virtual void dead()
    {
     defer_tick.stop();

     getClient().close();

     client_ac->dead();
     alert_client_ac->dead();
    }

   virtual void askClose()
    {
     if( client_ac->askDestroy() ) destroy();
    }

   virtual void setSize(Point size_,bool buf_dirty)
    {
     if( ( size_!=Null && size!=size_ ) || buf_dirty )
       {
        size=size_;

        redrawAll(LayoutResize);
       }
    }

   virtual void paintDone(unsigned)
    {
     if( delay_draw )
       {
        delay_draw=false;

        redrawAll();
       }
    }

   // keyboard

   virtual void gainFocus()
    {
     if( Change(shape.has_focus,true) )
       {
        redrawFrame();

        getClient().gainFocus();
       }
    }

   virtual void looseFocus()
    {
     if( Change(shape.has_focus,false) )
       {
        redrawFrame();

        getClient().looseFocus();
       }
    }

   // mouse

   virtual void looseCapture()
    {
     if( shape.drag_type ) endDrag();

     if( client_capture )
       {
        client_capture=false;

        getClient().looseCapture();
       }
    }

   virtual void setMouseShape(Point point,KeyMod kmod)
    {
     switch( DragType drag_type=shape.dragTest(point) )
       {
        case DragType_Top         : host->setMouseShape(Mouse_SizeUpDown); break;

        case DragType_TopLeft     : host->setMouseShape(Mouse_SizeUpLeft); break;

        case DragType_Left        : host->setMouseShape(Mouse_SizeLeftRight); break;

        case DragType_BottomLeft  : host->setMouseShape(Mouse_SizeUpRight); break;

        case DragType_Bottom      : host->setMouseShape(Mouse_SizeUpDown); break;

        case DragType_BottomRight : host->setMouseShape(Mouse_SizeUpLeft); break;

        case DragType_Right       : host->setMouseShape(Mouse_SizeLeftRight); break;

        case DragType_TopRight    : host->setMouseShape(Mouse_SizeUpRight); break;

        case DragType_Bar         : host->setMouseShape(Mouse_SizeAll); break;

        case DragType_Close       : host->setMouseShape(Mouse_Stop); break;

        default:
         {
          if( IsButton(drag_type) )
            {
             host->setMouseShape(Mouse_Hand);
            }
          else
            {
             host->setMouseShape(getClient().forward_getMouseShape(point,kmod));
            }
         }
       }
    }

   // user input

   virtual void disableReact()
    {
     if( Change(enable_react,false) ) redrawAll();
    }

   virtual void enableReact()
    {
     if( Change(enable_react,true) ) redrawAll();
    }

   virtual void react(UserAction action)
    {
     if( enable_react ) action.dispatch(*this);
    }

   void react_other(UserAction action)
    {
     if( action.fromKeyboard() )
       {
        getClient().react(action);
       }
     else
       {
        if( shape.drag_type || shape.btn_type ) return;

        Point point=action.getPoint();

        if( client_capture || shape.getClient().contains(point) )
          {
           getClient().forward_react(action);
          }
       }
    }

   void react_Key(VKey vkey,KeyMod kmod)
    {
     if( !forwardKey(vkey,kmod) ) getClient().put_Key(vkey,kmod);
    }

   void react_Key(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     if( !forwardKey(vkey,kmod,repeat) ) getClient().put_Key(vkey,kmod,repeat);
    }

   void react_KeyUp(VKey vkey,KeyMod kmod)
    {
     if( !forwardKeyUp(vkey,kmod) ) getClient().put_KeyUp(vkey,kmod);
    }

   void react_KeyUp(VKey vkey,KeyMod kmod,unsigned repeat)
    {
     if( !forwardKeyUp(vkey,kmod,repeat) ) getClient().put_KeyUp(vkey,kmod,repeat);
    }

   void react_LeftClick(Point point,MouseKey mkey)
    {
     if( DragType drag_type=shape.dragTest(point) )
       {
        if( IsButton(drag_type) )
          {
           if( !shape.drag_type && !shape.btn_type ) btnDown(drag_type);
          }
        else
          {
           if( !shape.drag_type && !shape.btn_type ) startDrag(point,drag_type);
          }
       }
     else
       {
        if( client_capture || shape.getClient().contains(point) )
          {
           getClient().forward().put_LeftClick(point,mkey);
          }
       }
    }

   void react_LeftUp(Point point,MouseKey mkey)
    {
     hilightFrame(point);

     if( shape.drag_type )
       {
        endDrag(point);
       }
     else if( shape.btn_type )
       {
        btnUp(point);
       }
     else if( client_capture || shape.getClient().contains(point) )
       {
        getClient().forward().put_LeftUp(point,mkey);
       }
    }

   void react_Move(Point point,MouseKey mkey)
    {
     if( shape.drag_type )
       {
        if( mkey&MouseKey_Left )
          dragTo(point);
        else
          endDrag(point);
       }
     else if( shape.btn_type )
       {
        if( mkey&MouseKey_Left )
          moveBtn(point);
        else
          endBtn();
       }
     else
       {
        hilightFrame(point);

        if( shape.getClient().contains(point) )
          {
           client_enter=true;

           getClient().forward().put_Move(point,mkey);
          }
        else
          {
           if( client_capture ) getClient().forward().put_Move(point,mkey);

           if( client_enter )
             {
              client_enter=false;

              getClient().put_Leave();
             }
          }

        if( shape.help ) hint(point);
       }
    }

   void react_Leave()
    {
     if( shape.btn_type )
       {
        endBtn();
       }
     else if( !shape.drag_type )
       {
        endHilightFrame();
       }

     if( client_enter )
       {
        client_enter=false;

        getClient().put_Leave();
       }

     endHint();
    }

   // DeferInput

   class Input : DeferInput<DragFrameOf<Shape> >
    {
      friend class DragFrameOf<Shape>;

      explicit Input(DragFrameOf<Shape> *window) : DeferInput<DragFrameOf<Shape> >(window) {}

      ~Input() {}

      using DeferInput<DragFrameOf<Shape> >::try_post;

     public:

      void redrawAll(unsigned flags=NoLayout) { try_post(&DragFrameOf<Shape>::redrawAll,flags); }

      void redrawSet() { try_post(&DragFrameOf<Shape>::redrawSet); }
    };

   Input input;

  private:

   DeferTick defer_tick;

   void update()
    {
     input.redrawAll(LayoutUpdate);
    }

   void alert()
    {
     switch( shape.alert_type )
       {
        case AlertType_No :
         {
          shape.alert_type=AlertType_Closed;

          redrawFrame(DragType_Alert);

          pushAlertBlink();
         }
        break;

        case AlertType_Closed :
         {
          pushAlertBlink();
         }
        break;
       }
    }

   SignalConnector<DragFrameOf<Shape> > connector_update;
   SignalConnector<DragFrameOf<Shape> > connector_alert;
 };

/* type DragFrame */

using DragFrame = DragFrameOf<DragFrameShape> ;

/* type FixedFrame */

using FixedFrame = DragFrameOf<FixedFrameShape> ;

} // namespace Video
} // namespace CCore

#endif

