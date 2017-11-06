/* test7003.DragWindow.cpp */
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

#include <CCore/inc/video/CommonDrawArt.h>

namespace App {

namespace Private_7003 {

/* class ClientWindow */

class ClientWindow : public SubWindow
 {
  public:

   struct ConfigType
    {
     RefVal<VColor> back  = Silver ;
     RefVal<VColor> field =  White ;

     RefVal<VColor> begin =   Blue ;
     RefVal<VColor> end   =  Green ;

     RefVal<VColor> line  =    Red ;

     ConfigType() {}
    };

  private:

   const ConfigType &cfg;

   Point a;
   Point b;
   Pane field;

   bool select_a = true ;

  private:

   void cross(CommonDrawArt &art,Point p,VColor color) const
    {
     Point size=getSize();

     art.path(color,Point(p.x,0),Point(p.x,size.y-1));
     art.path(color,Point(0,p.y),Point(size.x-1,p.y));
    }

   void select(Point point)
    {
     if( select_a )
       a=point;
     else
       b=point;

     redraw();
    }

  public:

   ClientWindow(SubWindowHost &host,const ConfigType &cfg_)
    : SubWindow(host),
      cfg(cfg_)
    {
    }

   virtual ~ClientWindow()
    {
    }

   // drawing

   virtual void layout()
    {
     Point size=getSize();

     field=Pane(size.x/4,size.y/4,size.x/2,size.y/2);
    }

   virtual void draw(DrawBuf buf,bool drag_active) const
    {
     Used(drag_active);

     CommonDrawArt art(buf);

     art.erase(+cfg.back);

     art.block(field,+cfg.field);

     if( select_a )
       cross(art,a,+cfg.begin);
     else
       cross(art,b,+cfg.end);

     CommonDrawArt(buf.cut(field)).path(+cfg.line,a,b);
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod)
    {
     if( vkey==VKey_Tab )
       {
        select_a=!select_a;

        redraw();
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     select(point);
    }

   void react_Move(Point point,MouseKey mkey)
    {
     if( mkey&MouseKey_Left )
       {
        select(point);
       }
    }
 };

} // namespace Private_7003

using namespace Private_7003;

/* TestMain() */

template <>
int TestMain<7003>(CmdDisplay cmd_display)
 {
  return ClientApplication<ClientWindow>::Main(cmd_display,"Test7003"_def);
 }

} // namespace App





