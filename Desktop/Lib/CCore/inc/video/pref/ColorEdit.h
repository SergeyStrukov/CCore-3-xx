/* ColorEdit.h */
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

#ifndef CCore_inc_video_pref_ColorEdit_h
#define CCore_inc_video_pref_ColorEdit_h

#include <CCore/inc/video/pref/ColorListWindow.h>
#include <CCore/inc/video/pref/MixColorWindow.h>

namespace CCore {
namespace Video {

/* classes */

class ColorEditWindow;

/* class ColorEditWindow */

class ColorEditWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<Coord> space_dxy = 10 ;

     CtorRefVal<MixColorWindow::ConfigType> mix_cfg;
     CtorRefVal<ColorListWindow::ConfigType> list_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);

       mix_cfg.bind(proxy);
       list_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   MixColorWindow mix_win;
   ColorListWindow list_win;

  private:

   void list_selected(ulen index);

   SignalConnector<ColorEditWindow,ulen> connector_selected;

  public:

   ColorEditWindow(SubWindowHost &host,const Config &cfg);

   virtual ~ColorEditWindow();

   // methods

   Point getMinSize(Point cap=Point::Max()) const;

   VColor getColor() const { return mix_win.getColor(); }

   void setColor(VColor value) { mix_win.setColor(value); }

   // drawing

   virtual void layout();

   // signals

   Signal<VColor> &changed; // value
 };

} // namespace Video
} // namespace CCore

#endif


