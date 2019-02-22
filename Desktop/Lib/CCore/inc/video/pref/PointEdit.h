/* PointEdit.h */
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

#ifndef CCore_inc_video_pref_PointEdit_h
#define CCore_inc_video_pref_PointEdit_h

#include <CCore/inc/video/WindowLib.h>

namespace CCore {
namespace Video {

/* classes */

class PointEditWindow;

/* class PointEditWindow */

class PointEditWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(1) ;

     RefVal<VColor> line = Black ;

     RefVal<Coord> space_dxy = 10 ;

     RefVal<String> hint_x = "Select x coordinate"_str ;
     RefVal<String> hint_y = "Select y coordinate"_str ;

     CtorRefVal<SpinorWindow::ConfigType> spin_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       width.bind(bag.cfg_edit_width);
       line.bind(bag.cfg_edit_line);
       space_dxy.bind(bag.space_dxy);
       hint_x.bind(bag.hint_cfg_x);
       hint_y.bind(bag.hint_cfg_y);

       spin_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   SpinorWindow spin_x;
   SpinorWindow spin_y;

   Point pos;

  private:

   void spin_changed(int);

   SignalConnector<PointEditWindow,int> connector_spin_x_changed;
   SignalConnector<PointEditWindow,int> connector_spin_y_changed;

  public:

   PointEditWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~PointEditWindow();

   // methods

   Point getMinSize() const;

   Point getPoint() const;

   void setPoint(Point value);

   // drawing

   virtual bool hasGoodSize() const;

   virtual void layout();

   virtual void drawBack(DrawBuf buf,DrawParam &draw_param) const;

   // signals

   Signal<Point> changed; // value
 };

} // namespace Video
} // namespace CCore

#endif

