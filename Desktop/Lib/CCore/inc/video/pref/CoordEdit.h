/* CoordEdit.h */
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
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_pref_CoordEdit_h
#define CCore_inc_video_pref_CoordEdit_h

#include <CCore/inc/video/WindowLib.h>

namespace CCore {
namespace Video {

/* classes */

class CoordEditWindow;

/* class CoordEditWindow */

class CoordEditWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(1) ;

     RefVal<Coord> mark_dy = 3 ;

     RefVal<VColor> line = Black ;

     CtorRefVal<SpinorWindow::ConfigType> spin_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       width.bind(bag.cfg_edit_width);
       mark_dy.bind(bag.cfg_edit_mark_dy);
       line.bind(bag.cfg_edit_line);

       spin_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   SpinorWindow spin;

   Point pos;

  private:

   void spin_changed(int value);

   SignalConnector<CoordEditWindow,int> connector_spin_changed;

  public:

   CoordEditWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~CoordEditWindow();

   // methods

   Point getMinSize() const;

   Coord getCoord() const
    {
     return Coord(spin.getValue());
    }

   void setCoord(Coord value)
    {
     spin.setValue(value);

     redraw();
    }

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // signals

   Signal<Coord> changed; // value
 };

} // namespace Video
} // namespace CCore

#endif



