/* MessageFrame.h */
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
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_MessageFrame_h
#define CCore_inc_video_MessageFrame_h

#include <CCore/inc/video/WindowLib.h>
#include <CCore/inc/video/ButtonId.h>

#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Array.h>

namespace CCore {
namespace Video {

/* classes */

class MessageWindow;

class MessageFrame;

/* class MessageWindow */

class MessageWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<InfoWindow::ConfigType> info_cfg;
     CtorRefVal<KnobWindow::ConfigType> knob_cfg;
     CtorRefVal<ButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<XDoubleLineWindow::ConfigType> dline_cfg;

     RefVal<Coord> knob_dxy  = 50 ;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);

       back.bind(bag.back);

       info_cfg.bind(proxy);
       knob_cfg.bind(proxy);
       btn_cfg.bind(proxy);
       dline_cfg.bind(proxy);

       knob_dxy.bind(bag.message_knob_dxy);
      }
    };

   using ConfigType = Config ;

   struct AlertConfigType : Config
    {
     AlertConfigType() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       Config::bind(bag,proxy);

       back.bind(bag.alert);
      }
    };

  private:

   class Btn : public ButtonWindow
    {
      int btn_id;

      MessageWindow *owner;

     private:

      void assertOwner();

      SignalConnector<Btn> connector_pressed;

     public:

      Btn(SubWindowHost &host,const ButtonWindow::ConfigType &cfg,const DefString &name,int btn_id,MessageWindow *owner);

      virtual ~Btn();
    };

  private:

   const Config &cfg;
   const ButtonWindow::ConfigType &btn_cfg;

   InfoWindow info;

   XDoubleLineWindow dline;

   KnobWindow knob;

   DynArray<OwnPtr<Btn> > btn_list;

  private:

   struct BtnRange;

   void knob_pressed();

   SignalConnector<MessageWindow> connector_knob_pressed;

  public:

   MessageWindow(SubWindowHost &host,const Config &cfg);

   virtual ~MessageWindow();

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   void erase(); // for dead windows!

   MessageWindow & setInfo(const Info &info);

   MessageWindow & setInfo(const DefString &str) { return setInfo(InfoFromString(str)); }

   MessageWindow & add(const DefString &name,int btn_id);

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // base

   virtual void open();

   // signals

   Signal<int> pressed; // btn_id
 };

/* class MessageFrame */

class MessageFrame : public FixedFrame
 {
  public:

   struct Config
    {
     RefVal<Ratio> pos_ry = Div(5,12) ;

     CtorRefVal<FixedFrame::ConfigType> frame_cfg;
     CtorRefVal<MessageWindow::ConfigType> msg_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       pos_ry.bind(bag.frame_pos_ry);

       frame_cfg.bind(proxy);
       msg_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

   struct AlertConfigType : Config
    {
     AlertConfigType() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       pos_ry.bind(bag.frame_pos_ry);

       frame_cfg.bind(proxy);
       msg_cfg.bind((const MessageWindow::AlertConfigType &)proxy);
      }
    };

  private:

   const Config &cfg;

   MessageWindow client;

   int btn_id = Button_Cancel ;

  private:

   void pressed(int btn_id);

   SignalConnector<MessageFrame,int> connector_pressed;

  public:

   MessageFrame(Desktop *desktop,const Config &cfg);

   MessageFrame(Desktop *desktop,const Config &cfg,Signal<> &update);

   virtual ~MessageFrame();

   // methods

   void erase(); // for dead windows!

   MessageFrame & setInfo(const Info &info) { client.setInfo(info); return *this; }

   MessageFrame & setInfo(const DefString &str) { return setInfo(InfoFromString(str)); }

   MessageFrame & add(const DefString &name,int btn_id) { client.add(name,btn_id); return *this; }

   int getButtonId() const { return btn_id; } // available after the signal "destroyed"

   // base

   virtual void alive();

   // create

   Pane getPane(bool is_main,StrLen title) const;

   void createMain(const DefString &title)
    {
     FixedFrame::createMain(getPane(true,title.str()),title);
    }

   void create(const DefString &title)
    {
     FixedFrame::create(getPane(false,title.str()),title);
    }

   void create(FrameWindow *parent,const DefString &title)
    {
     FixedFrame::create(parent,getPane(false,title.str()),title);
    }
 };

} // namespace Video
} // namespace CCore

#endif


