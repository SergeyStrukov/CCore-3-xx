/* Subs.h */
//----------------------------------------------------------------------------------------
//
//  Project: SubLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Subs_h
#define Subs_h

#include <inc/Application.h>

#include <CCore/inc/video/WindowLib.h>
#include <CCore/inc/video/Layout.h>

namespace App {
namespace Subs {

/* Create() */

template <class W>
static SubWindow * Create(SubWindowHost &host,const UserPreference &pref)
 {
  return new W(host,pref.getSmartConfig());
 }

template <class W>
static SubWindow * Create_def(SubWindowHost &host,const UserPreference &)
 {
  static typename W::ConfigType cfg;

  return new W(host,cfg);
 }

template <class W>
static SubWindow * Create_def_disable(SubWindowHost &host,const UserPreference &)
 {
  static typename W::ConfigType cfg;

  W *ret=new W(host,cfg);

  ret->disable();

  return ret;
 }

/* class DrawShape */

class DrawShape
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(10) ;

     RefVal<VColor> border = Black ;
     RefVal<VColor> body   =  Blue ;

     Config() noexcept {}
    };

   const Config &cfg;
   Pane pane;

   // methods

   explicit DrawShape(const Config &cfg_) : cfg(cfg_) {}

   Point getMinSize() const { return Point::Diag(10); }

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* type DrawWindow */

using DrawWindow = DecorWindowOf<DrawShape> ;

/* class TextContourWindow_Left */

class TextContourWindow_Left : public TextContourWindow
 {
  public:

   TextContourWindow_Left(SubWindowHost &host,const ConfigType &cfg);
 };

/* class TextContourWindow_Right */

class TextContourWindow_Right : public TextContourWindow
 {
  public:

   TextContourWindow_Right(SubWindowHost &host,const ConfigType &cfg);
 };

/* class TextContourWindow_Center */

class TextContourWindow_Center : public TextContourWindow
 {
  public:

   TextContourWindow_Center(SubWindowHost &host,const ConfigType &cfg);
 };

/* class ButtonWindow_Button */

class ButtonWindow_Button : public ButtonWindow
 {
   ExceptionBuf exbuf;

  private:

   void testException();

   SignalConnector<ButtonWindow_Button> connector_pressed;

  public:

   ButtonWindow_Button(SubWindowHost &host,const UserPreference &pref);
 };

/* class KnobWindow_Asterisk */

class KnobWindow_Asterisk : public KnobWindow
 {
   unsigned count = 0 ;

   unsigned tick_count = 0 ;

   DeferInput<KnobWindow_Asterisk> input;

   DeferTick defer_tick;

  private:

   void tick();

   void testException();

   SignalConnector<KnobWindow_Asterisk> connector_pressed;

  public:

   KnobWindow_Asterisk(SubWindowHost &host,const ConfigType &cfg);
 };

/* class KnobWindow_auto */

class KnobWindow_auto : public KnobWindow
 {
   static KnobShape::FaceType NextFace(KnobShape::FaceType face);

   void nextFace();

   SignalConnector<KnobWindow_auto> connector_pressed;

  public:

   KnobWindow_auto(SubWindowHost &host,const ConfigType &cfg);
 };

/* class LabelWindow_Label */

class LabelWindow_Label : public LabelWindow
 {
  public:

   LabelWindow_Label(SubWindowHost &host,const ConfigType &cfg);
 };

/* class TextWindow_SampleText */

class TextWindow_SampleText : public TextWindow
 {
  public:

   TextWindow_SampleText(SubWindowHost &host,const ConfigType &cfg);
 };

/* class TextLineWindow_SampleText */

class TextLineWindow_SampleText : public TextLineWindow
 {
  public:

   TextLineWindow_SampleText(SubWindowHost &host,const ConfigType &cfg);
 };

/* class ProgressWindow_Sample */

class ProgressWindow_Sample : public ProgressWindow
 {
   DeferInput<ProgressWindow_Sample> input;

   DeferTick defer_tick;

   unsigned pos = 0 ;
   unsigned count = 0 ;

  private:

   void tick();

  public:

   ProgressWindow_Sample(SubWindowHost &host,const ConfigType &cfg);

   // base

   virtual void open();

   virtual void close();
 };

/* class ArrowProgressWindow_Sample */

class ArrowProgressWindow_Sample : public ArrowProgressWindow
 {
   DeferInput<ArrowProgressWindow_Sample> input;

   DeferTick defer_tick;

   unsigned pos = 0 ;
   unsigned count = 0 ;

  private:

   void tick();

  public:

   ArrowProgressWindow_Sample(SubWindowHost &host,const ConfigType &cfg);

   // base

   virtual void open();

   virtual void close();
 };

/* class InfoWindow_SampleInfo */

class InfoWindow_SampleInfo : public InfoWindow
 {
   static String Sample();

  public:

   InfoWindow_SampleInfo(SubWindowHost &host,const ConfigType &cfg);
 };

/* class MessageWindow_knob */

class MessageWindow_knob : public MessageWindow
 {
  public:

   MessageWindow_knob(SubWindowHost &host,const ConfigType &cfg);
 };

/* class MessageWindow_ok */

class MessageWindow_ok : public MessageWindow
 {
  public:

   MessageWindow_ok(SubWindowHost &host,const ConfigType &cfg);
 };

/* class MessageWindow_yes_no */

class MessageWindow_yes_no : public MessageWindow
 {
  public:

   MessageWindow_yes_no(SubWindowHost &host,const ConfigType &cfg);
 };

/* class SimpleTextListWindow_SampleList */

class SimpleTextListWindow_SampleList : public SimpleTextListWindow
 {
   static String List();

  public:

   SimpleTextListWindow_SampleList(SubWindowHost &host,const ConfigType &cfg);
 };

/* class XScrollWindow_Sample */

class XScrollWindow_Sample : public XScrollWindow
 {
  public:

   XScrollWindow_Sample(SubWindowHost &host,const ConfigType &cfg);
 };

/* class YScrollWindow_Sample */

class YScrollWindow_Sample : public YScrollWindow
 {
  public:

   YScrollWindow_Sample(SubWindowHost &host,const ConfigType &cfg);
 };

/* class SpinorWindow_Sample */

class SpinorWindow_Sample : public SpinorWindow
 {
  public:

   SpinorWindow_Sample(SubWindowHost &host,const ConfigType &cfg);
 };

//----------------------------------------------------------------------------------------

/* CreateCombo() */

template <class W>
static SubWindow * CreateCombo(SubWindowHost &host,const UserPreference &pref)
 {
  return new W(host,pref);
 }

/* class RadioLightWindow */

class RadioLightWindow : public ComboWindow
 {
   RadioGroup group;

   RadioWindow radio_Off;
   RadioWindow radio_Red;
   RadioWindow radio_Green;
   RadioWindow radio_Blue;

   LightWindow light;

  private:

   void group_changed(int new_id,int);

   SignalConnector<RadioLightWindow,int,int> connector_group_changed;

  public:

   RadioLightWindow(SubWindowHost &host,const UserPreference &pref);

   // drawing

   virtual void layout();
 };

/* class AlignWindow<W> */

template <class W>
class AlignWindow : public ComboWindow
 {
   RadioGroup group;

   RadioWindow radio_TopLeft;
   RadioWindow radio_TopCenter;
   RadioWindow radio_TopRight;

   RadioWindow radio_BottomLeft;
   RadioWindow radio_BottomCenter;
   RadioWindow radio_BottomRight;

   RadioWindow radio_LeftCenter;
   RadioWindow radio_RightCenter;

   W window;

   RefVal<Coord> radio_dxy;
   RefVal<Coord> space_dxy;

  private:

   void group_changed(int new_id,int)
    {
     switch( new_id )
       {
        case 0 :
         {
          window.setAlign(AlignX_Left,AlignY_Top);
         }
        break;

        case 1 :
         {
          window.setAlign(AlignX_Center,AlignY_Top);
         }
        break;

        case 2 :
         {
          window.setAlign(AlignX_Right,AlignY_Top);
         }
        break;

        case 3 :
         {
          window.setAlign(AlignX_Left,AlignY_Bottom);
         }
        break;

        case 4 :
         {
          window.setAlign(AlignX_Center,AlignY_Bottom);
         }
        break;

        case 5 :
         {
          window.setAlign(AlignX_Right,AlignY_Bottom);
         }
        break;

        case 6 :
         {
          window.setAlign(AlignX_Left,AlignY_Center);
         }
        break;

        case 7 :
         {
          window.setAlign(AlignX_Right,AlignY_Center);
         }
        break;
       }
    }

   SignalConnector<AlignWindow,int,int> connector_group_changed;

  public:

   AlignWindow(SubWindowHost &host,const UserPreference &pref)
    : ComboWindow(host),

      radio_TopLeft(wlist,0,pref.getSmartConfig()),
      radio_TopCenter(wlist,1,pref.getSmartConfig()),
      radio_TopRight(wlist,2,pref.getSmartConfig()),
      radio_BottomLeft(wlist,3,pref.getSmartConfig()),
      radio_BottomCenter(wlist,4,pref.getSmartConfig()),
      radio_BottomRight(wlist,5,pref.getSmartConfig()),
      radio_LeftCenter(wlist,6,pref.getSmartConfig()),
      radio_RightCenter(wlist,7,pref.getSmartConfig()),

      window(wlist,pref.getSmartConfig()),

      connector_group_changed(this,&AlignWindow::group_changed,group.changed)
    {
     wlist.insTop(radio_TopLeft,radio_TopCenter,radio_TopRight,
                  radio_BottomLeft,radio_BottomCenter,radio_BottomRight,
                  radio_LeftCenter,radio_RightCenter,window);

     group.add(radio_TopLeft,radio_TopCenter,radio_TopRight,
               radio_BottomLeft,radio_BottomCenter,radio_BottomRight,
               radio_LeftCenter,radio_RightCenter);

     radio_dxy.bind(pref.get().radio_dxy);
     space_dxy.bind(pref.get().space_dxy);

     window.setAlign(AlignX_Left,AlignY_Top);
    }

   // drawing

   virtual void layout()
    {
     PaneCut pane(getSize(),+space_dxy);

     Coord dxy=+radio_dxy;

     pane.cutTop(dxy).place_cutLeft(radio_TopLeft)
                     .place_cutRight(radio_TopRight)
                     .place(AlignCenterX(radio_TopCenter));

     pane.cutBottom(dxy).place_cutLeft(radio_BottomLeft)
                        .place_cutRight(radio_BottomRight)
                        .place(AlignCenterX(radio_BottomCenter));

     pane.cutLeft(dxy).place(AlignCenterY(radio_LeftCenter));

     pane.cutRight(dxy).place(AlignCenterY(radio_RightCenter));

     pane.place(window);
    }
 };

/* class AltShape */

class AltShape
 {
  public:

   struct Config
    {
     RefVal<VColor> border =      Blue ;
     RefVal<VColor> focus  = OrangeRed ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> snowUp = PaleGreen ;

     // app

     RefVal<Coord> dy = 32 ;

     RefVal<VColor> mark_false    = RGBColor(64,0,0) ;
     RefVal<VColor> mark_true     = RGBColor(0,64,0) ;
     RefVal<VColor> mark_false_on = RGBColor(255,100,100) ;
     RefVal<VColor> mark_true_on  = RGBColor(100,255,100) ;

     Config() noexcept {}

     explicit Config(const UserPreference &pref) noexcept
      {
       bind(pref.get());
      }

     template <class Bag>
     void bind(const Bag &bag)
      {
       border.bind(bag.border);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       snowUp.bind(bag.snowUp);
      }
    };

   const Config &cfg;
   Pane pane;

   // state

   using CheckType = bool ;

   static CheckType Next(CheckType check) { return !check; }

   bool enable     =  true ;
   bool focus      = false ;
   bool mover      = false ;
   CheckType zone  = false ;
   CheckType check = false ;

   // methods

   explicit AltShape(const Config &cfg_,CheckType check_=false) : cfg(cfg_),check(check_) {}

   Point getMinSize() const;

   bool isGoodSize(Point size) const { return size>=getMinSize(); }

   CheckType getZone(Point point) const;

   void draw(const DrawBuf &buf,DrawParam draw_param) const;
 };

/* class AltWindow_Sample */

using AltWindow = AltWindowOf<AltShape> ;

using AltConfig = AltWindow::ConfigType ;

class AltWindow_Sample : AltConfig , public AltWindow
 {
  public:

   AltWindow_Sample(SubWindowHost &host,const UserPreference &pref);
 };

/* class FireButtonWindow_Sample */

class FireButtonWindow_Sample : public ComboWindow
 {
   LightWindow light;

   RefVal<String> name = "Fire"_str ;

   RefFireButtonWindow btn;

  private:

   void fire(bool on);

   SignalConnector<FireButtonWindow_Sample,bool> connector_fire;

  public:

   FireButtonWindow_Sample(SubWindowHost &host,const UserPreference &pref);

   // drawing

   virtual void layout();
 };

/* class XSliderWindow_Sample */

class XSliderWindow_Sample : public ComboWindow
 {
   TextWindow text;
   XSliderWindow slider;

  private:

   void changed(unsigned pos);

   SignalConnector<XSliderWindow_Sample,unsigned> connector_changed;

  public:

   XSliderWindow_Sample(SubWindowHost &host,const UserPreference &pref);

   // drawing

   virtual void layout();
 };

/* class YSliderWindow_Sample */

class YSliderWindow_Sample : public ComboWindow
 {
   TextWindow text;
   YSliderWindow slider;

  private:

   void changed(unsigned pos);

   SignalConnector<YSliderWindow_Sample,unsigned> connector_changed;

  public:

   YSliderWindow_Sample(SubWindowHost &host,const UserPreference &pref);

   // drawing

   virtual void layout();
 };

/* class RunButtonWindow_Sample */

class RunButtonWindow_Sample : public ComboWindow
 {
   LightWindow light;

   RefVal<String> name_off =  "Run"_str ;
   RefVal<String> name_on  = "Stop"_str ;

   RefRunButtonWindow btn;

  private:

   void changed(bool on);

   SignalConnector<RunButtonWindow_Sample,bool> connector_changed;

  public:

   RunButtonWindow_Sample(SubWindowHost &host,const UserPreference &pref);

   // drawing

   virtual void layout();
 };

/* class LayoutWindow */

class LayoutWindow : public SubWindow
 {
   Pane outer;

   Pane red;
   Pane green;
   Pane blue;

  public:

   LayoutWindow(SubWindowHost &host,const UserPreference &);

   // drawing

   virtual void layout();

   virtual void draw(DrawBuf buf,DrawParam draw_param) const;
 };

} // namespace Subs
} // namespace App

#endif

