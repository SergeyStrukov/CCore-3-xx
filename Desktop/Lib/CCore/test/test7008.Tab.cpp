/* test7008.Tab.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/test/wintest.h>

#include <CCore/inc/video/WindowLib.h>
#include <CCore/inc/video/Layout.h>

namespace App {

namespace Private_7008 {

/* class Sub2 */

class Sub2 : public ComboWindow
 {
   ContourWindow::ConfigType contour_cfg;

   ContourWindow contour;

   KnobWindow::ConfigType knob_cfg;

   KnobWindow win1;
   KnobWindow win2;
   KnobWindow win3;

  public:

   explicit Sub2(SubWindowHost &host)
    : ComboWindow(host),

      contour(wlist,contour_cfg),
      win1(wlist,knob_cfg,KnobShape::FaceOk),
      win2(wlist,knob_cfg,KnobShape::FacePlus),
      win3(wlist,knob_cfg,KnobShape::FaceMinus)
    {
     wlist.insTop(win1,win2,win3,contour);
    }

   virtual ~Sub2()
    {
    }

   // drawing

   virtual void layout()
    {
     contour.setPlace({Null,getSize()});

     Pane pane=contour.getInner();
     Coord space=10;

     Point s(25,25);

     PlaceRow row(pane,s,space,3);

     win1.setPlace(*row);

     ++row;

     win2.setPlace(*row);

     ++row;

     win3.setPlace(*row);
    }
 };

/* class Sub1 */

class Sub1 : public ComboWindow
 {
   ContourWindow::ConfigType contour_cfg;

   ContourWindow contour;

   Sub2 win1;
   Sub2 win2;
   Sub2 win3;

  public:

   explicit Sub1(SubWindowHost &host)
    : ComboWindow(host),

      contour(wlist,contour_cfg),
      win1(wlist),
      win2(wlist),
      win3(wlist)
    {
     wlist.insTop(win1,win2,win3,contour);
    }

   virtual ~Sub1()
    {
    }

   // drawing

   virtual void layout()
    {
     contour.setPlace({Null,getSize()});

     Pane pane=contour.getInner();
     Coord space=10;

     Point s(pane.dx-2*space,(pane.dy-4*space)/3);

     PlaceColumn col(pane,s,space,3);

     win1.setPlace(*col);

     ++col;

     win2.setPlace(*col);

     ++col;

     win3.setPlace(*col);
    }
 };

/* class ClientWindow */

class ClientWindow : public ComboWindow
 {
  public:

   struct ConfigType
    {
     RefVal<VColor> back = Silver ;

     ConfigType() {}
    };

  private:

   const ConfigType &cfg;

   Sub1 win1;
   Sub1 win2;

  public:

   ClientWindow(SubWindowHost &host,const ConfigType &cfg_)
    : ComboWindow(host),
      cfg(cfg_),

      win1(wlist),
      win2(wlist)
    {
     wlist.insTop(win1,win2);
    }

   virtual ~ClientWindow()
    {
    }

   // drawing

   virtual void layout()
    {
     Point size=getSize();
     Coord space=10;

     Point s((size.x-3*space)/2,size.y-2*space);

     PlaceRow row({Null,size},s,space,2);

     win1.setPlace(*row);

     ++row;

     win2.setPlace(*row);
    }

   virtual void drawBack(DrawBuf buf,bool) const
    {
     buf.erase(+cfg.back);
    }
 };

} // namespace Private_7008

using namespace Private_7008;

/* TestMain() */

template <>
int TestMain<7008>(CmdDisplay cmd_display)
 {
  return ClientApplication<ClientWindow>::Main(cmd_display,"Test7008"_def);
 }

} // namespace App

