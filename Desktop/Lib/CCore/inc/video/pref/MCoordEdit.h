/* MCoordEdit.h */
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

#ifndef CCore_inc_video_pref_MCoordEdit_h
#define CCore_inc_video_pref_MCoordEdit_h

#include <CCore/inc/video/WindowLib.h>

namespace CCore {
namespace Video {

/* classes */

class MCoordEditWindow;

/* class MCoordEditWindow */

class MCoordEditWindow : public ComboWindow
 {
  public:

   struct Config
    {
     CtorRefVal<SpinorWindow::ConfigType> spinor_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &,Proxy proxy)
      {
       spinor_cfg.bind(proxy);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   SpinorWindow spinor;

  private:

   void spinor_changed(int);

   SignalConnector<MCoordEditWindow,int> connector_spinor_changed;

  public:

   MCoordEditWindow(SubWindowHost &host,const ConfigType &cfg);

   virtual ~MCoordEditWindow();

   // methods

   Point getMinSize() const;

   MCoord getMCoord() const { return (spinor.getValue()*1024)/100; }

   void setMCoord(MCoord value) { spinor.setValue( (value*100)/1024 ); }

   // drawing

   virtual void layout();

   // signals

   Signal<MCoord> changed; // value
 };

} // namespace Video
} // namespace CCore

#endif

