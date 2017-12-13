/* RatioEdit.h */
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

#ifndef CCore_inc_video_pref_RatioEdit_h
#define CCore_inc_video_pref_RatioEdit_h

#include <CCore/inc/video/WindowLib.h>

namespace CCore {
namespace Video {

/* classes */

class RatioEditWindow;

/* class RatioEditWindow */

class RatioEditWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<MCoord> width = Fraction(1) ;

     RefVal<Coord> mark_dy = 3 ;

     RefVal<VColor> line = Black ;

     RefVal<Coord> space_dxy = 10 ;

     RefVal<DefString> hint_a = "Select divisible"_def ;
     RefVal<DefString> hint_b = "Select divider"_def ;

     CtorRefVal<SpinorWindow::ConfigType> spin_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       width.bind(bag.cfg_edit_width);
       mark_dy.bind(bag.cfg_edit_mark_dy);
       line.bind(bag.cfg_edit_line);
       space_dxy.bind(bag.space_dxy);
       hint_a.bind(bag.hint_cfg_a);
       hint_b.bind(bag.hint_cfg_b);

       spin_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   SpinorWindow spin_a;
   SpinorWindow spin_b;

   Point pos;

  private:

   static MCoord Den(MCoord a,MCoord b,MCoord cap);

  private:

   void spin_changed(int);

   SignalConnector<RatioEditWindow,int> connector_spin_a_changed;
   SignalConnector<RatioEditWindow,int> connector_spin_b_changed;

  public:

   RatioEditWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~RatioEditWindow();

   // methods

   Point getMinSize() const;

   Ratio getRatio() const;

   void setRatio(Ratio value);

   // drawing

   virtual void layout(unsigned flags);

   virtual void drawBack(DrawBuf buf,bool drag_active) const;

   // signals

   Signal<Ratio> changed; // value
 };

} // namespace Video
} // namespace CCore

#endif

