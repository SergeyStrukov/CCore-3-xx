/* test7007.CommonArt.cpp */
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

#include <CCore/inc/RangeDel.h>
#include <CCore/inc/Print.h>

namespace App {

namespace Private_7007 {

/* functions */

template <class A>
void Remove(A &obj,ulen ind)
 {
  if( RangeCopyDel(Range(obj),ind) ) obj.shrink_one();
 }

template <class A,class T>
void Insert(A &obj,ulen ind,T item)
 {
  if( ind<obj.getLen() )
    {
     obj.append_default();

     auto r=RangeReverse(Range(obj).part(ind+1));

     for(; r.len>1 ;++r) r[0]=r[1];

     r[0]=item;
    }
  else
    {
     obj.append_copy(item);
    }
 }

/* class ClientWindow */

class ClientWindow : public SubWindow
 {
  public:

   struct ConfigType
    {
     RefVal<Coord> knob_len =  3 ;

     RefVal<VColor> back  = Silver ;
     RefVal<VColor> field =  White ;
     RefVal<VColor> grid  =  Black ;
     RefVal<VColor> knob  =  Black ;
     RefVal<VColor> cross =  Green ;
     RefVal<VColor> path  =    Red ;
     RefVal<VColor> solid =   Blue ;

     ConfigType() {}
    };

  private:

   const ConfigType &cfg;

   DynArray<Point> dots;
   Pane field;

   enum DrawType
    {
     DrawPath,
     DrawLoop,
     DrawCurvePath,
     DrawCurveLoop,
     DrawPathSmooth,
     DrawLoopSmooth,
     DrawCurvePathSmooth,
     DrawCurveLoopSmooth,

     DrawSolid,
     DrawCurveSolid
    };

   DrawType draw_type = DrawCurveSolid ;

   SolidFlag solid_flag = SolidAll ;

   ulen selected = 0 ;
   Coord magnify_factor = 32 ;

   bool magnify = false ;
   Point focus;

   mutable PrintFile out;

  private:

   void cross(CommonDrawArt &art,Point p,DesktopColor color) const
    {
     Point size=getSize();

     art.path(color,Point(p.x,0),Point(p.x,size.y-1));
     art.path(color,Point(0,p.y),Point(size.x-1,p.y));
    }

   void select(Point point)
    {
     if( selected<dots.getLen() )
       {
        dots[selected]=point;

        redraw();
       }
    }

   static const char * GetTextDesc(DrawType draw_type)
    {
     switch( draw_type )
       {
        case DrawPath            : return "Path";
        case DrawLoop            : return "Loop";
        case DrawCurvePath       : return "CurvePath";
        case DrawCurveLoop       : return "CurveLoop";
        case DrawPathSmooth      : return "PathSmooth";
        case DrawLoopSmooth      : return "LoopSmooth";
        case DrawCurvePathSmooth : return "CurvePathSmooth";
        case DrawCurveLoopSmooth : return "CurveLoopSmooth";

        case DrawSolid           : return "Solid";
        case DrawCurveSolid      : return "CurveSolid";

        default: return "???";
       }
    }

  public:

   ClientWindow(SubWindowHost &host,const ConfigType &cfg_)
    : SubWindow(host),
      cfg(cfg_),
      out("time.txt")
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

        art.grid(magnify_factor,+cfg.back,+cfg.grid);

        switch( draw_type )
          {
           case DrawCurvePath       : art.curvePath_micro(Range_const(dots),+cfg.path,focus,magnify_factor); break;

           case DrawPathSmooth      : art.path_smooth_micro(Range_const(dots),+cfg.path,focus,magnify_factor); break;

           case DrawCurvePathSmooth : art.curvePath_smooth_micro(Range_const(dots),+cfg.path,focus,magnify_factor); break;
          }
       }
     else
       {
        CommonDrawArt art(buf);

        art.erase(+cfg.back);

        art.block(field,+cfg.field);

        if( draw_type<DrawSolid )
          {
           for(auto p : dots ) art.knob(p,+cfg.knob_len,+cfg.knob);

           if( selected<dots.getLen() ) cross(art,dots[selected],+cfg.cross);
          }

        CommonDrawArt field_art(buf.cut(field));

        ClockTimer timer;

        switch( draw_type )
          {
           case DrawPath            : field_art.path(Range_const(dots),+cfg.path); break;
           case DrawLoop            : field_art.loop(Range_const(dots),+cfg.path); break;
           case DrawCurvePath       : field_art.curvePath(Range_const(dots),+cfg.path); break;
           case DrawCurveLoop       : field_art.curveLoop(Range_const(dots),+cfg.path); break;
           case DrawPathSmooth      : field_art.path_smooth(Range_const(dots),+cfg.path); break;
           case DrawLoopSmooth      : field_art.loop_smooth(Range_const(dots),+cfg.path); break;
           case DrawCurvePathSmooth : field_art.curvePath_smooth(Range_const(dots),+cfg.path); break;
           case DrawCurveLoopSmooth : field_art.curveLoop_smooth(Range_const(dots),+cfg.path); break;

           case DrawSolid           : field_art.solid(Range_const(dots),solid_flag,+cfg.solid); break;
           case DrawCurveSolid      : field_art.curveSolid(Range_const(dots),solid_flag,+cfg.solid); break;
          }

        auto time=timer.get();

        Printf(out,"#;[#;] #;\n",GetTextDesc(draw_type),dots.getLen(),time);

        if( draw_type>=DrawSolid )
          {
           if( selected<dots.getLen() ) cross(art,dots[selected],+cfg.cross);
          }
       }
    }

   // user input

   virtual void react(UserAction action)
    {
     action.dispatch(*this);
    }

   void react_Key(VKey vkey,KeyMod kmod)
    {
     switch( vkey )
       {
        case VKey_F2 :
         {
          draw_type=DrawPath;

          redraw();
         }
        break;

        case VKey_F3 :
         {
          draw_type=DrawLoop;

          redraw();
         }
        break;

        case VKey_F4 :
         {
          draw_type=DrawCurvePath;

          redraw();
         }
        break;

        case VKey_F5 :
         {
          draw_type=DrawCurveLoop;

          redraw();
         }
        break;

        case VKey_F6 :
         {
          draw_type=DrawPathSmooth;

          redraw();
         }
        break;

        case VKey_F7 :
         {
          draw_type=DrawLoopSmooth;

          redraw();
         }
        break;

        case VKey_F8 :
         {
          draw_type=DrawCurvePathSmooth;

          redraw();
         }
        break;

        case VKey_F9 :
         {
          draw_type=DrawCurveLoopSmooth;

          redraw();
         }
        break;

        case VKey_F10 :
         {
          draw_type=DrawSolid;

          redraw();
         }
        break;

        case VKey_F11 :
         {
          draw_type=DrawCurveSolid;

          redraw();
         }
        break;

        case VKey_F12 :
         {
          solid_flag=(solid_flag?SolidOdd:SolidAll);

          redraw();
         }
        break;

        case VKey_Tab :
         {
          if( ulen len=dots.getLen() )
            {
             if( kmod&KeyMod_Shift )
               {
                if( selected ) selected--; else selected=len-1;
               }
             else
               {
                if( ++selected >= len ) selected=0;
               }

             redraw();
            }
         }
        break;

        case VKey_Home :
         {
          if( dots.getLen() )
            {
             selected=0;

             redraw();
            }
         }
        break;

        case VKey_End :
         {
          if( ulen len=dots.getLen() )
            {
             selected=len-1;

             redraw();
            }
         }
        break;

        case VKey_Delete :
         {
          ulen ind=selected;
          ulen len=dots.getLen();

          if( ind<len )
            {
             Remove(dots,ind);

             if( ind==len-1 && ind>0 ) selected=ind-1;

             redraw();
            }
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey mkey)
    {
     if( mkey&MouseKey_Shift )
       {
        Insert(dots,selected,point);

        if( dots.getLen()>1 ) selected++;

        redraw();
       }
     else
       {
        select(point);
       }
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
     else
       {
        if( mkey&MouseKey_Left )
          {
           if( getFrameHost()->getToken() ) return;

           select(point);
          }
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
    }
 };

} // namespace Private_7007

using namespace Private_7007;

/* TestMain() */

template <>
int TestMain<7007>(CmdDisplay cmd_display)
 {
  return ClientApplication<ClientWindow>::Main(cmd_display,"Test7007"_def);
 }

} // namespace App4





