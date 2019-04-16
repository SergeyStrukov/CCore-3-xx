/* FavFrame.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_FavFrame_h
#define CCore_inc_video_FavFrame_h

#include <CCore/inc/video/FavList.h>
#include <CCore/inc/video/WindowLib.h>
#include <CCore/inc/video/FrameOf.h>

namespace CCore {
namespace Video {

/* classes */

class FavListShape;

template <class Shape> class FavListWindowOf;

class FavWindow;

class FavFrame;

/* class FavListShape */

class FavListShape
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;

     RefVal<VColor> text        =  Black ;
     RefVal<VColor> text_select = Yellow ;

     RefVal<VColor> section_text = White ;
     RefVal<VColor> section_back = Black ;

     RefVal<Point> space = Point(8,8) ;

     RefVal<Font> font;

     CtorRefVal<KnobWindow::ConfigType> knob_cfg;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       width.bind(bag.width);
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);

       text.bind(bag.fav_text);
       text_select.bind(bag.fav_text_select);
       section_text.bind(bag.fav_section_text);
       section_back.bind(bag.fav_section_back);
       space.bind(bag.fav_space);
       font.bind(bag.fav_font.font);

       knob_cfg.bind(proxy);
      }
    };

   // parameters

   const Config &cfg;
   FavList fav_list;
   Pane pane;

   // state

   bool focus = false ;

   // methods

   explicit FavListShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;

   ulen getPageLen() const;

   bool curPageUp()
    {
     return fav_list.curUp(getPageLen());
    }

   bool curPageDown()
    {
     return fav_list.curDown(getPageLen());
    }

   void makeVisible()
    {
     fav_list.makeVisible(getPageLen());
    }

   struct TestResult
    {
     ulen ind;
     bool btn;
     bool ok;
    };

   TestResult test(Point point) const;

   ScrollPos getScrollPos() const;
 };

/* class FavListWindowOf<Shape> */

template <class Shape>
class FavListWindowOf : public SubWindow
 {
   Shape shape;

  public:

   using ShapeType = Shape ;
   using ConfigType = typename Shape::Config ;

   template <class ... TT>
   FavListWindowOf(SubWindowHost &host,TT && ... tt)
    : SubWindow(host),
      shape( std::forward<TT>(tt)... )
    {
    }

   virtual ~FavListWindowOf() {}

   // methods

   auto getMinSize() const { return shape.getMinSize(); }

   bool load(StrLen file_name)
    {
     bool ret;

     try
       {
        ret=shape.fav_list.load(file_name);
       }
     catch(...)
       {
        ret=false;
       }

     redraw();

     changed.assert();

     return ret;
    }

   void save(StrLen file_name) const
    {
     shape.fav_list.save(file_name);
    }

   bool load(StrLen key,StrLen file) noexcept
    {
     bool ret=shape.fav_list.load(key,file);

     redraw();

     changed.assert();

     return ret;
    }

   void save(StrLen key,StrLen file) const noexcept
    {
     shape.fav_list.save(key,file);
    }

   const FavRec * getCur() const { return shape.fav_list.getCur(); }

   ScrollPos getScrollPos() const
    {
     return shape.getScrollPos();
    }

   void setOff(ulen pos)
    {
     if( shape.fav_list.setOff(pos) )
       {
        redraw();
       }
    }

   void openAll()
    {
     shape.fav_list.openAll();

     shape.makeVisible();

     redraw();

     changed.assert();
    }

   void closeAll()
    {
     shape.fav_list.closeAll();

     shape.makeVisible();

     redraw();

     changed.assert();
    }

   bool canMoveUp() const { return shape.fav_list.canMoveUp(); }

   bool canMoveDown() const { return shape.fav_list.canMoveDown(); }

   void moveUp()
    {
     if( shape.fav_list.moveUp() )
       {
        shape.makeVisible();

        redraw();

        changed.assert();
       }
    }

   void moveDown()
    {
     if( shape.fav_list.moveDown() )
       {
        shape.makeVisible();

        redraw();

        changed.assert();
       }
    }

   void moveUp(ulen count)
    {
     if( shape.fav_list.moveUp(count) )
       {
        shape.makeVisible();

        redraw();

        changed.assert();
       }
    }

   void moveDown(ulen count)
    {
     if( shape.fav_list.moveDown(count) )
       {
        shape.makeVisible();

        redraw();

        changed.assert();
       }
    }

   void del()
    {
     if( shape.fav_list.del() )
       {
        shape.makeVisible();

        redraw();

        changed.assert();
       }
    }

   void insItem(const String &title,const String &path)
    {
     shape.fav_list.insItem(title,path);

     shape.makeVisible();

     redraw();

     changed.assert();
    }

   void insSection(const String &title)
    {
     shape.fav_list.insSection(title);

     shape.makeVisible();

     redraw();

     changed.assert();
    }

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return shape.isGoodSize(size);
    }

   virtual void layout()
    {
     shape.pane=getPane();
    }

   virtual void draw(DrawBuf buf,DrawParam draw_param) const
    {
     shape.draw(buf,draw_param);
    }

   // keyboard

   virtual FocusType askFocus() const
    {
     return FocusOk;
    }

   virtual void gainFocus()
    {
     if( Change(shape.focus,true) ) redraw();
    }

   virtual void looseFocus()
    {
     if( Change(shape.focus,false) ) redraw();
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
        case VKey_Up :
         {
          if( kmod&KeyMod_Ctrl )
            {
             moveUp();
            }
          else if( kmod&KeyMod_Shift )
            {
             if( shape.fav_list.offUp() )
               {
                redraw();

                off_changed.assert(shape.fav_list.getOff());
               }
            }
          else
            {
             if( shape.fav_list.curUp() )
               {
                shape.makeVisible();

                redraw();

                changed.assert();
               }
            }
         }
        break;

        case VKey_Down :
         {
          if( kmod&KeyMod_Ctrl )
            {
             moveDown();
            }
          else if( kmod&KeyMod_Shift )
            {
             if( shape.fav_list.offDown() )
               {
                redraw();

                off_changed.assert(shape.fav_list.getOff());
               }
            }
          else
            {
             if( shape.fav_list.curDown() )
               {
                shape.makeVisible();

                redraw();

                changed.assert();
               }
            }
         }
        break;

        case VKey_PageUp :
         {
          if( shape.curPageUp() )
            {
             shape.makeVisible();

             redraw();

             changed.assert();
            }
         }
        break;

        case VKey_PageDown :
         {
          if( shape.curPageDown() )
            {
             shape.makeVisible();

             redraw();

             changed.assert();
            }
         }
        break;

        case VKey_Home :
         {
          if( shape.fav_list.curBeg() )
            {
             shape.makeVisible();

             redraw();

             changed.assert();
            }
         }
        break;

        case VKey_End :
         {
          if( shape.fav_list.curEnd() )
            {
             shape.makeVisible();

             redraw();

             changed.assert();
            }
         }
        break;

        case VKey_NumPlus :
         {
          if( shape.fav_list.curOpen() )
            {
             redraw();

             changed.assert();
            }
         }
        break;

        case VKey_NumMinus :
         {
          if( shape.fav_list.curClose() )
            {
             redraw();

             changed.assert();
            }
         }
        break;

        case VKey_NumAsterisk :
         {
          openAll();
         }
        break;

        case VKey_NumSlash :
         {
          closeAll();
         }
        break;

        case VKey_Delete :
         {
          del();
         }
        break;

        case VKey_Space :
        case VKey_Enter :
         {
          auto result=shape.fav_list.curAct();

          if( result.ok )
            {
             if( result.section )
               {
                redraw();

                changed.assert();
               }
             else
               {
                selected.assert();
               }
            }
         }
        break;
       }
    }

   void react_LeftClick(Point point,MouseKey)
    {
     auto result=shape.test(point);

     if( result.ok )
       {
        if( result.btn )
          {
           shape.fav_list.changeOpen(result.ind);

           redraw();

           changed.assert();
          }
        else
          {
           if( shape.fav_list.changeCur(result.ind) )
             {
              redraw();

              changed.assert();
             }
          }
       }
    }

   void react_LeftDClick(Point point,MouseKey)
    {
     auto result=shape.test(point);

     if( result.ok )
       {
        if( !result.btn )
          {
           if( shape.fav_list.changeCur(result.ind) )
             {
              redraw();

              changed.assert();
             }

           selected.assert();
          }
       }
    }

   void react_Wheel(Point,MouseKey mkey,Coord delta_)
    {
     ulen delta=IntAbs(delta_);

     if( delta_<0 )
       {
        if( mkey&KeyMod_Ctrl )
          {
           moveDown(delta);
          }
        else if( mkey&MouseKey_Shift )
          {
           if( shape.fav_list.offDown(delta) )
             {
              redraw();

              off_changed.assert(shape.fav_list.getOff());
             }
          }
        else
          {
           if( shape.fav_list.curDown(delta) )
             {
              shape.makeVisible();

              redraw();

              changed.assert();
             }
          }
       }
     else
       {
        if( mkey&KeyMod_Ctrl )
          {
           moveUp(delta);
          }
        else if( mkey&MouseKey_Shift )
          {
           if( shape.fav_list.offUp(delta) )
             {
              redraw();

              off_changed.assert(shape.fav_list.getOff());
             }
          }
        else
          {
           if( shape.fav_list.curUp(delta) )
             {
              shape.makeVisible();

              redraw();

              changed.assert();
             }
          }
       }
    }

   // signals

   Signal<> selected;
   Signal<> changed;
   Signal<ulen> off_changed;
 };

/* type FavListWindow */

using FavListWindow = FavListWindowOf<FavListShape> ;

/* class FavWindow */

class FavWindow : public ComboWindow
 {
  public:

   struct Config
    {
     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<KnobWindow::ConfigType> knob_cfg;
     CtorRefVal<AllButtonWindow::ConfigType> allbtn_cfg;
     CtorRefVal<RefButtonWindow::ConfigType> btn_cfg;
     CtorRefVal<TextLineWindow::ConfigType> text_cfg;
     CtorRefVal<LineEditWindow::ConfigType> edit_cfg;
     CtorRefVal<FavListWindow::ConfigType> fav_cfg;
     CtorRefVal<XDoubleLineWindow::ConfigType> dline_cfg;
     CtorRefVal<YScrollWindow::ConfigType> scroll_cfg;

     RefVal<String> text_Section = "Section"_str ;
     RefVal<String> text_Select  = "Select"_str ;
     RefVal<String> text_Close   = "Close"_str ;

     RefVal<String> hint_Ins         = "Insert current book"_str ;
     RefVal<String> hint_MoveUp      = "Move selected item up"_str ;
     RefVal<String> hint_MoveDown    = "Move selected item down"_str ;
     RefVal<String> hint_OpenAll     = "Open all sections"_str ;
     RefVal<String> hint_CloseAll    = "Close all sections"_str ;
     RefVal<String> hint_Del         = "Delete selected item"_str ;
     RefVal<String> hint_SectionName = "Enter a section name here"_str ;
     RefVal<String> hint_Path        = "Path of the selected book"_str ;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);
       back.bind(bag.back);

       knob_cfg.bind(proxy);
       allbtn_cfg.bind(proxy);
       btn_cfg.bind(proxy);
       text_cfg.bind(proxy);
       edit_cfg.bind(proxy);
       fav_cfg.bind(proxy);
       dline_cfg.bind(proxy);
       scroll_cfg.bind(proxy);

       text_Section.bind(bag.text_Section);
       text_Select.bind(bag.text_Select);
       text_Close.bind(bag.text_Close);

       hint_Ins.bind(bag.hint_Ins);
       hint_MoveUp.bind(bag.hint_MoveUp);
       hint_MoveDown.bind(bag.hint_MoveDown);
       hint_OpenAll.bind(bag.hint_OpenAll);
       hint_CloseAll.bind(bag.hint_CloseAll);
       hint_Del.bind(bag.hint_Del);
       hint_SectionName.bind(bag.hint_SectionName);
       hint_Path.bind(bag.hint_Path);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   StrLen key;
   StrLen file;

   // subs

   KnobWindow knob_ins;
   KnobWindow knob_up;
   KnobWindow knob_down;

   AllButtonWindow btn_openall;
   AllButtonWindow btn_closeall;

   KnobWindow knob_del;

   RefButtonWindow btn_section;
   LineEditWindow edit;

   XDoubleLineWindow dline1;

   FavListWindow fav;
   YScrollWindow scroll;
   TextLineWindow text;

   XDoubleLineWindow dline2;

   RefButtonWindow btn_select;
   RefButtonWindow btn_close;

   // ins

   String ins_title;
   String ins_path;

   // selected path

   String selected_path;

  private:

   void fav_changed();

   SignalConnector<FavWindow> connector_fav_changed;

   SignalConnector<FavWindow> connector_fav_selected;

   void ins_pressed();

   SignalConnector<FavWindow> connector_ins_pressed;

   void up_pressed();

   SignalConnector<FavWindow> connector_up_pressed;

   void down_pressed();

   SignalConnector<FavWindow> connector_down_pressed;

   void openall_pressed();

   SignalConnector<FavWindow> connector_openall_pressed;

   void closeall_pressed();

   SignalConnector<FavWindow> connector_closeall_pressed;

   void del_pressed();

   SignalConnector<FavWindow> connector_del_pressed;

   void section_pressed();

   SignalConnector<FavWindow> connector_section_pressed;

   void select_pressed();

   SignalConnector<FavWindow> connector_select_pressed;

   void close_pressed();

   SignalConnector<FavWindow> connector_close_pressed;

   void scroll_changed(ulen pos);

   SignalConnector<FavWindow,ulen> connector_scroll_changed;

   void off_changed(ulen pos);

   SignalConnector<FavWindow,ulen> connector_off_changed;

  public:

   FavWindow(SubWindowHost &host,const Config &cfg,StrLen key,StrLen file); // persistent

   virtual ~FavWindow();

   // methods

   Point getMinSize() const;

   void setInsData(const String &title,const String &path);

   const String & getSelectedPath() const { return selected_path; }

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,DrawParam &draw_param) const;

   // base

   virtual void open();

   virtual void close();
 };

/* class FavFrame */

class FavFrame : public DragFrame
 {
  public:

   struct Config
    {
     CtorRefVal<DragFrame::ConfigType> frame_cfg;
     CtorRefVal<FavWindow::ConfigType> fav_cfg;

     RefVal<Ratio> pos_ry = Div(5,12) ;

     Config() noexcept {}

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       frame_cfg.bind(proxy);
       fav_cfg.bind(proxy);

       pos_ry.bind(bag.frame_pos_ry);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   FavWindow sub_win;

   FramePlace place;

  private:

   void setPlace();

  public:

   FavFrame(Desktop *desktop,const Config &cfg,StrLen key,StrLen file); // persistent

   FavFrame(Desktop *desktop,const Config &cfg,StrLen key,StrLen file,Signal<> &update); // persistent

   virtual ~FavFrame();

   // methods

   template <class AppState>
   void prepare(const AppState &app_state) { place=app_state.fav_place; }

   template <class AppState>
   void save(AppState &app_state) { if( isAlive() ) setPlace(); app_state.fav_place=place; }

   void setInsData(const String &title,const String &path)
    {
     sub_win.setInsData(title,path);
    }

   const String & getSelectedPath() const
    {
     return sub_win.getSelectedPath();
    }

   // base

   virtual void dying();

   // create

   Pane getPane(StrLen title,Point base) const;

   Pane getPane(StrLen title) const;

   void create(Point base,const String &title)
    {
     DragFrame::create(getPane(Range(title),base),title);
    }

   void create(FrameWindow *parent,Point base,const String &title)
    {
     DragFrame::create(parent,getPane(Range(title),base),title);
    }

   void create(const String &title)
    {
     DragFrame::create(getPane(Range(title)),title);
    }

   void create(FrameWindow *parent,const String &title)
    {
     DragFrame::create(parent,getPane(Range(title)),title);
    }
 };

} // namespace Video
} // namespace CCore

#endif

