/* test7006.Ball.cpp */
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
#include <CCore/test/SpecialDrawArt.h>

#include <CCore/inc/video/CommonDrawArt.h>
#include <CCore/inc/video/DrawAlgo.h>

namespace App {

namespace Private_7006 {

/* class ClientWindow */

class ClientWindow : public SubWindow
 {
  public:

   struct ConfigType
    {
     RefVal<VColor> back   = Silver ;
     RefVal<VColor> field  =  White ;
     RefVal<VColor> grid   =  Black ;

     RefVal<VColor> ball   =   Blue ;
     RefVal<VColor> spline =    Red ;

     ConfigType() {}
    };

  private:

   const ConfigType &cfg;

   Pane field;

   Point center;
   Coord radius = 1 ;
   Coord magnify_factor = 10 ;

   bool magnify = false ;
   Point focus;

   bool ball          =  true ;
   bool circle        = false ;
   bool spline        = false ;
   bool spline_smooth = false ;

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

     if( magnify )
       {
        SpecialDrawArt art(buf,getSize());

        art.grid(magnify_factor,+cfg.field,+cfg.grid);

        art.circle_micro(center,radius,+cfg.ball,focus,magnify_factor);
       }
     else
       {
        CommonDrawArt art(buf);

        art.erase(+cfg.back);

        CommonDrawArt field_art(buf.cut(field));

        field_art.erase(+cfg.field);

        if( ball )
          {
           field_art.ball(center,radius,+cfg.ball);
          }

        if( circle )
          {
           field_art.circle(center,radius,+cfg.ball);
          }

        if( spline )
          {
           field_art.circleSpline(center,radius,+cfg.spline);
          }

        if( spline_smooth )
          {
           field_art.circleSpline_smooth(center,radius,+cfg.spline);
          }
       }
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod)
    {
     switch( vkey )
       {
        case VKey_F2 :
         {
          ball=!ball;

          redraw();
         }
        break;

        case VKey_F3 :
         {
          circle=!circle;

          redraw();
         }
        break;

        case VKey_F4 :
         {
          spline=!spline;

          redraw();
         }
        break;

        case VKey_F5 :
         {
          spline_smooth=!spline_smooth;

          redraw();
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     center=point;

     redraw();
    }

   void react_RightClick(Point point,MouseKey)
    {
     magnify=true;
     focus=point;

     redraw();
    }

   void react_RightUp(Point,MouseKey)
    {
     if( magnify )
       {
        magnify=false;

        redraw();
       }
    }

   void react_Move(Point point,MouseKey mkey)
    {
     if( magnify )
       {
        focus=point;

        redraw();
       }
     else if( mkey&MouseKey_Left )
       {
        center=point;

        redraw();
       }
    }

   void react_Leave()
    {
     if( magnify )
       {
        magnify=false;

        redraw();
       }
    }

   void react_Wheel(Point,MouseKey,Coord delta)
    {
     if( magnify )
       {
        magnify_factor=Cap<Coord>(4,magnify_factor+2*delta,100);

        redraw();
       }
     else
       {
        radius=Cap<Coord>(1,radius+delta,1000);

        redraw();
       }
    }
 };

} // namespace Private_7006

using namespace Private_7006;

/* TestMain() */

template <>
int TestMain<7006>(CmdDisplay cmd_display)
 {
  return ClientApplication<ClientWindow>::Main(cmd_display,"Test7006"_def);
 }

} // namespace App





