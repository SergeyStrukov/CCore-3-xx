/* Client.cpp */
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

#include <inc/Client.h>

#include <CCore/inc/video/ExceptionFrame.h>
#include <CCore/inc/video/MessageFrame.h>

#include <CCore/inc/video/Layout.h>
#include <CCore/inc/video/FigureLib.h>

#include <CCore/inc/Array.h>

#include <CCore/inc/Exception.h>

namespace App {

/* class DrawShape */

void DrawShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  SmoothDrawArt art(buf.cut(pane));

  FigureDownArrow fig1(p);

  fig1.curveSolid(art,+cfg.body);

  auto fig2=fig1.border(+cfg.width);

  fig2.curveSolid(art,+cfg.border);
 }

/* class AltShape */

Point AltShape::getMinSize() const
 {
  Coordinate dy=+cfg.dy;

  return Point(2*dy,dy);
 }

auto AltShape::getZone(Point point) const -> CheckType
 {
  return point.x-pane.x > pane.dx/2 ;
 }

void AltShape::draw(const DrawBuf &buf) const
 {
  MPane p(pane);

  if( !p ) return;

  MCoord t=p.x+p.dx/2;
  MCoord space=p.dy/5;

  MPane a=p.cutLeft(t);
  MPane b=p.cutRight(t);

  SmoothDrawArt art(buf.cut(pane));

  VColor snow=+cfg.snow;
  VColor gray=+cfg.gray;
  VColor snowUp=+cfg.snowUp;

  // body

  {
   FigureBox fig(a);

   if( enable && check )
     {
      VColor top_ = ( mover && !zone )? snowUp : snow ;

      fig.solid(art,TwoField(a.getTopLeft(),top_,a.getBottomLeft(),gray));
     }
   else
     {
      fig.solid(art,gray);
     }
  }
  {
   FigureBox fig(b);

   if( enable && !check )
     {
      VColor top_ = ( mover && zone )? snowUp : snow ;

      fig.solid(art,TwoField(b.getTopLeft(),top_,b.getTopRight(),gray));
     }
   else
     {
      fig.solid(art,gray);
     }
  }

  // mark

  {
   FigureDownArrow fig(a.shrink(space));

   VColor mark = ( enable && !check )? +cfg.mark_false_on : +cfg.mark_false ;

   fig.curveSolid(art,mark);
  }
  {
   FigureRightArrow fig(b.shrink(space));

   VColor mark = ( enable && check )? +cfg.mark_true_on : +cfg.mark_true ;

   fig.curveSolid(art,mark);
  }

  // border

  {
   FigureBox fig(p);

   MCoord width=space/2;

   VColor border = enable? +cfg.border : snow ;

   fig.loop(art,HalfPos,width,border);

   art.path(width,border,p.getTopMid(),p.getBottomMid());

   if( focus )
     fig.loop(art,HalfPos,width/2,+cfg.focus);
  }
 }

/* class SpaceWindow */

void SpaceWindow::startDrag(Point point)
 {
  if( Change(drag,true) )
    {
     drag_base=point;
     space_base=space;

     captureMouse();

     redraw();
    }
 }

void SpaceWindow::dragTo(Point point)
 {
  Point delta=point-drag_base;

  space=space_base+delta;

  redraw();

  changed.assert();
 }

void SpaceWindow::endDrag()
 {
  drag=false;

  releaseMouse();
 }

void SpaceWindow::endDrag(Point point)
 {
  endDrag();

  dragTo(point);
 }

SpaceWindow::SpaceWindow(SubWindowHost &host,const ConfigType &cfg_)
 : SubWindow(host),
   cfg(cfg_)
 {
  space=Point::Diag(+cfg.space_dxy);
 }

SpaceWindow::~SpaceWindow()
 {
 }

 // drawing

bool SpaceWindow::isGoodSize(Point size) const
 {
  return size/2 >= space ;
 }

void SpaceWindow::layout(unsigned)
 {
  // do nothing
 }

void SpaceWindow::draw(DrawBuf buf,bool) const
 {
  Pane pane(Null,getSize());

  Pane inner=pane.shrink(space);

  if( +inner )
    {
     if( drag )
       {
        MPane p(inner);

        SmoothDrawArt art(buf.cut(pane));

        FigureBox fig(p);

        fig.loop(art,HalfNeg,Fraction(+cfg.border_dxy),+cfg.border);
       }
    }
  else
    {
     SmoothDrawArt art(buf.cut(pane));

     art.erase(+cfg.border);
    }
 }

 // base

void SpaceWindow::open()
 {
  drag=false;
 }

 // keyboard

FocusType SpaceWindow::askFocus() const
 {
  return NoFocus;
 }

 // mouse

void SpaceWindow::looseCapture()
 {
  drag=false;
 }

MouseShape SpaceWindow::getMouseShape(Point,KeyMod) const
 {
  return drag?Mouse_SizeAll:Mouse_Arrow;
 }

 // user input

void SpaceWindow::react(UserAction action)
 {
  action.dispatch(*this);
 }

void SpaceWindow::react_LeftClick(Point point,MouseKey mkey)
 {
  if( mkey&MouseKey_Shift )
    {
     space=point;

     redraw();

     changed.assert();
    }
  else
    {
     startDrag(point);
    }
 }

void SpaceWindow::react_LeftUp(Point point,MouseKey)
 {
  if( drag ) endDrag(point);
 }

void SpaceWindow::react_Move(Point point,MouseKey mkey)
 {
  if( drag )
    {
     if( mkey&MouseKey_Left )
       {
        dragTo(point);
       }
     else
       {
        endDrag();
       }
    }
 }

/* class ClientWindow::TypeInfo::Base */

class ClientWindow::TypeInfo::Base : public ComboInfoBase
 {
   struct Item
    {
     ComboInfoType type;
     DefString name;
     SubFactory factory;

     explicit Item(const DefString &title)
      : type(ComboInfoTitle),
        name(title),
        factory(0)
      {
      }

     Item(const DefString &name_,SubFactory factory_)
      : type(ComboInfoText),
        name(name_),
        factory(factory_)
      {
      }

     operator ComboInfoItem() const
      {
       return ComboInfoItem(type,name.str());
      }
    };

   DynArray<Item> list;

  private:

   void add(const DefString &title)
    {
     list.append_fill(title);
    }

   void add(const DefString &name,SubFactory factory)
    {
     list.append_fill(name,factory);
    }

   // Create()

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

   class TextContourWindow_Left : public TextContourWindow
    {
     public:

      TextContourWindow_Left(SubWindowHost &host,const ConfigType &cfg)
       : TextContourWindow(host,cfg,"Title left"_def,AlignX_Left)
       {
       }
    };

   class TextContourWindow_Right : public TextContourWindow
    {
     public:

      TextContourWindow_Right(SubWindowHost &host,const ConfigType &cfg)
       : TextContourWindow(host,cfg,"Title right"_def,AlignX_Right)
       {
       }
    };

   class TextContourWindow_Center : public TextContourWindow
    {
     public:

      TextContourWindow_Center(SubWindowHost &host,const ConfigType &cfg)
       : TextContourWindow(host,cfg,"Title center"_def,AlignX_Center)
       {
       }
    };

   class ButtonWindow_Button : public ButtonWindow
    {
      ExceptionBuf exbuf;

     private:

      void testException()
       {
        ExceptionFrame frame(exbuf);

        Printf(Exception,"Button pressed");
       }

      SignalConnector<ButtonWindow_Button> connector_pressed;

     public:

      ButtonWindow_Button(SubWindowHost &host,const UserPreference &pref)
       : ButtonWindow(host,pref.getSmartConfig(),"Button"_def),
         exbuf(getFrame(),pref.getSmartConfig()),

         connector_pressed(this,&ButtonWindow_Button::testException,pressed)
       {
       }
    };

   class KnobWindow_Asterisk : public KnobWindow
    {
      unsigned count = 0 ;

      unsigned tick_count = 0 ;

      DeferInput<KnobWindow_Asterisk> input;

      DeferTick defer_tick;

     private:

      void tick()
       {
        if( tick_count )
          {
           tick_count--;

           unsigned period=5_sectick;

           if( (tick_count%period)==0 )
             {
              Printf(NoException,"Tick");
              Printf(Exception,"Tick exception\n>>>>>>>>>>>>>>> #; >>>>>>>>>>>>>>>>>>>>>>>>>>",count++);
             }
          }
        else
          {
           defer_tick.stop();
          }
       }

      void testException()
       {
        if( tick_count==0 )
          {
           tick_count=60_sectick;

           defer_tick.start();
          }

        Printf(Exception,"Test exception #;",count++);
       }

      SignalConnector<KnobWindow_Asterisk> connector_pressed;

     public:

      KnobWindow_Asterisk(SubWindowHost &host,const ConfigType &cfg)
       : KnobWindow(host,cfg,KnobShape::FaceAsterisk),
         input(this),

         connector_pressed(this,&KnobWindow_Asterisk::testException,pressed)
       {
        defer_tick=input.create(&KnobWindow_Asterisk::tick);
       }
    };

   class KnobWindow_auto : public KnobWindow
    {
      static KnobShape::FaceType NextFace(KnobShape::FaceType face)
       {
        auto ret=KnobShape::FaceType(face+1);

        if( ret==KnobShape::FaceLim ) return KnobShape::FaceOk;

        return ret;
       }

      void nextFace()
       {
        setFace(NextFace(getFace()));
       }

      SignalConnector<KnobWindow_auto> connector_pressed;

     public:

      KnobWindow_auto(SubWindowHost &host,const ConfigType &cfg)
       : KnobWindow(host,cfg,KnobShape::FaceOk),

         connector_pressed(this,&KnobWindow_auto::nextFace,pressed)
       {
       }
    };

   class LabelWindow_Label : public LabelWindow
    {
     public:

      LabelWindow_Label(SubWindowHost &host,const ConfigType &cfg)
       : LabelWindow(host,cfg,"Label"_def,AlignX_Center,AlignY_Center)
       {
       }
    };

   class TextWindow_SampleText : public TextWindow
    {
     public:

      TextWindow_SampleText(SubWindowHost &host,const ConfigType &cfg)
       : TextWindow(host,cfg,"Sample text line"_def,AlignX_Center,AlignY_Center)
       {
       }
    };

   class TextLineWindow_SampleText : public TextLineWindow
    {
     public:

      TextLineWindow_SampleText(SubWindowHost &host,const ConfigType &cfg)
       : TextLineWindow(host,cfg,"Sample text long line 1234567890"_def)
       {
       }
    };

   class ProgressWindow_Sample : public ProgressWindow
    {
      DeferInput<ProgressWindow_Sample> input;

      DeferTick defer_tick;

      unsigned pos = 0 ;
      unsigned count = 0 ;

     private:

      void tick()
       {
        if( !count )
          {
           count=2_sectick;

           if( pos<=getTotal() )
             setPosPing(pos++);
           else
             defer_tick.stop();
          }

        count--;
       }

     public:

      ProgressWindow_Sample(SubWindowHost &host,const ConfigType &cfg)
       : ProgressWindow(host,cfg),
         input(this)
       {
        defer_tick=input.create(&ProgressWindow_Sample::tick);

        setTotal(100);
       }

      // base

      virtual void open()
       {
        defer_tick.start();
       }

      virtual void close()
       {
        defer_tick.stop();
       }
    };

   class ArrowProgressWindow_Sample : public ArrowProgressWindow
    {
      DeferInput<ArrowProgressWindow_Sample> input;

      DeferTick defer_tick;

      unsigned pos = 0 ;
      unsigned count = 0 ;

     private:

      void tick()
       {
        if( !count )
          {
           count=2_sectick;

           if( pos<=getTotal() )
             setPosPing(pos++);
           else
             defer_tick.stop();
          }

        count--;
       }

     public:

      ArrowProgressWindow_Sample(SubWindowHost &host,const ConfigType &cfg)
       : ArrowProgressWindow(host,cfg),
         input(this)
       {
        defer_tick=input.create(&ArrowProgressWindow_Sample::tick);

        setTotal(100);
       }

      // base

      virtual void open()
       {
        defer_tick.start();
       }

      virtual void close()
       {
        defer_tick.stop();
       }
    };

   class InfoWindow_SampleInfo : public InfoWindow
    {
      static DefString Sample()
       {
        return
        "type AtomIndex = uint32 ;\r\n"
        "type SyntIndex = uint32 ;\r\n"
        "type KindIndex = uint32 ;\r\n"
        "type ElementIndex = uint32 ;\r\n"
        "type RuleIndex = uint32 ;\r\n"
        "type StateIndex = uint32 ;\r\n"
        "type FinalIndex = uint32 ;\r\n"
        "\r\n"
        "struct Lang\r\n"
        " {\r\n"
        "  Atom[] atoms;\r\n"
        "  Synt[] synts;\r\n"
        "  Synt * [] lang;\r\n"
        "  Element[] elements;\r\n"
        "  Rule[] rules;\r\n"
        "  TopRule[] top_rules;\r\n"
        "  State[] states;\r\n"
        "  Final[] finals;\r\n"
        " };\r\n"
        "\r\n"
        "struct Atom\r\n"
        " {\r\n"
        "  AtomIndex index;\r\n"
        "  text name;\r\n"
        "  \r\n"
        "  Element *element;\r\n"
        " };\r\n"
        "\r\n"
        "struct Synt\r\n"
        " {\r\n"
        "  SyntIndex index;\r\n"
        "  text name;\r\n"
        "  \r\n"
        "  Kind[] kinds;\r\n"
        "  Rule * [] rules;\r\n"
        " };\r\n"
        "\r\n"
        "struct Kind\r\n"
        " {\r\n"
        "  KindIndex kindex; // index among all kinds\r\n"
        "  KindIndex index; // index in synt array\r\n"
        "  text name;\r\n"
        "\r\n"
        "  Synt *synt;\r\n"
        "  \r\n"
        "  Element *element;\r\n"
        "  \r\n"
        "  TopRule * [] rules;\r\n"
        " };\r\n"
        "\r\n"
        "struct Element\r\n"
        " {\r\n"
        "  ElementIndex index;\r\n"
        "  \r\n"
        "  {Atom,Kind} * elem;\r\n"
        " };\r\n"
        "\r\n"
        "struct Rule\r\n"
        " {\r\n"
        "  RuleIndex index;\r\n"
        "  text name;\r\n"
        "\r\n"
        "  Kind *result;\r\n"
        "\r\n"
        "  type Arg = {Atom,Synt} * ;\r\n"
        "\r\n"
        "  Arg[] args;\r\n"
        " };\r\n"
        "\r\n"_def;
       }

     public:

      InfoWindow_SampleInfo(SubWindowHost &host,const ConfigType &cfg)
       : InfoWindow(host,cfg,InfoFromString(Sample()))
       {
       }
    };

   class MessageWindow_knob : public MessageWindow
    {
     public:

      MessageWindow_knob(SubWindowHost &host,const ConfigType &cfg)
       : MessageWindow(host,cfg)
       {
        setInfo("Knob message window"_def);
       }
    };

   class MessageWindow_ok : public MessageWindow
    {
     public:

      MessageWindow_ok(SubWindowHost &host,const ConfigType &cfg)
       : MessageWindow(host,cfg)
       {
        add("Ok"_def,Button_Ok).setInfo("Ok message window"_def);
       }
    };

   class MessageWindow_yes_no : public MessageWindow
    {
     public:

      MessageWindow_yes_no(SubWindowHost &host,const ConfigType &cfg)
       : MessageWindow(host,cfg)
       {
        add("Yes"_def,Button_Yes).add("No"_def,Button_No).setInfo("Yes/No message window"_def);
       }
    };

   class SimpleTextListWindow_SampleList : public SimpleTextListWindow
    {
      static DefString List()
       {
        return
        "XSingleLine\r\n"
        "YSingleLine\r\n"
        "XDoubleLine\r\n"
        "YDoubleLine\r\n"
        "Contour\r\n"
        "TextContour left\r\n"
        "TextContour right\r\n"
        "TextContour center\r\n"_def;
       }

     public:

      SimpleTextListWindow_SampleList(SubWindowHost &host,const ConfigType &cfg)
       : SimpleTextListWindow(host,cfg,InfoFromString(List()))
       {
       }
    };

   class XScrollWindow_Sample : public XScrollWindow
    {
     public:

      XScrollWindow_Sample(SubWindowHost &host,const ConfigType &cfg)
       : XScrollWindow(host,cfg)
       {
        setRange(1000,10);
       }
    };

   class YScrollWindow_Sample : public YScrollWindow
    {
     public:

      YScrollWindow_Sample(SubWindowHost &host,const ConfigType &cfg)
       : YScrollWindow(host,cfg)
       {
        setRange(1000,10);
       }
    };

   class SpinorWindow_Sample : public SpinorWindow
    {
     public:

      SpinorWindow_Sample(SubWindowHost &host,const ConfigType &cfg)
       : SpinorWindow(host,cfg)
       {
        setRange(-100,100);

        setOptions("+4i");
       }
    };

   // CreateCombo()

   template <class W>
   static SubWindow * CreateCombo(SubWindowHost &host,const UserPreference &pref)
    {
     return new W(host,pref);
    }

   class RadioLightWindow : public ComboWindow
    {
      RadioGroup group;

      RadioWindow radio_Off;
      RadioWindow radio_Red;
      RadioWindow radio_Green;
      RadioWindow radio_Blue;

      LightWindow light;

     private:

      void group_changed(int new_id,int)
       {
        switch( new_id )
          {
           case 0 :
            {
             light.turnOff();
            }
           break;

           case 1 :
            {
             light.setFace(Red);

             light.turnOn();
            }
           break;

           case 2 :
            {
             light.setFace(Green);

             light.turnOn();
            }
           break;

           case 3 :
            {
             light.setFace(Blue);

             light.turnOn();
            }
           break;
          }
       }

      SignalConnector<RadioLightWindow,int,int> connector_group_changed;

     public:

      RadioLightWindow(SubWindowHost &host,const UserPreference &pref)
       : ComboWindow(host),

         radio_Off(wlist,0,pref.getSmartConfig()),
         radio_Red(wlist,1,pref.getSmartConfig()),
         radio_Green(wlist,2,pref.getSmartConfig()),
         radio_Blue(wlist,3,pref.getSmartConfig()),

         light(wlist,pref.getSmartConfig(),Red,false),

         connector_group_changed(this,&RadioLightWindow::group_changed,group.changed)
       {
        wlist.insTop(radio_Off,radio_Red,radio_Green,radio_Blue,light);

        group.add(radio_Off,radio_Red,radio_Green,radio_Blue);
       }

      // drawing

      virtual void layout(unsigned flags)
       {
        Point size=getSize();

        {
         Pane pane(Null,size.x/2,size.y/7);

         Coord delta=2*pane.dy;

         radio_Off.setPlace(pane,flags); pane.y+=delta;
         radio_Red.setPlace(pane,flags); pane.y+=delta;
         radio_Green.setPlace(pane,flags); pane.y+=delta;
         radio_Blue.setPlace(pane,flags); pane.y+=delta;
        }

        {
         Coord dx=size.x/3;

         light.setPlace(Pane(2*dx,(size.y-dx)/2,dx,dx),flags);
        }
       }
    };

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

      virtual void layout(unsigned flags)
       {
        PaneCut pane(getSize(),+space_dxy,flags);

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

   using AltWindow = AltWindowOf<AltShape> ;

   using AltConfig = AltWindow::ConfigType ;

   class AltWindow_Sample : AltConfig , public AltWindow
    {
     public:

      AltWindow_Sample(SubWindowHost &host,const UserPreference &pref)
       : AltConfig(pref),
         AltWindow(host,(AltConfig &)*this)
       {
       }
    };

   class FireButtonWindow_Sample : public ComboWindow
    {
      LightWindow light;

      RefVal<DefString> name = "Fire"_def ;

      RefFireButtonWindow btn;

     private:

      void fire(bool on)
       {
        light.turn(on);
       }

      SignalConnector<FireButtonWindow_Sample,bool> connector_fire;

     public:

      FireButtonWindow_Sample(SubWindowHost &host,const UserPreference &pref)
       : ComboWindow(host),

         light(wlist,pref.getSmartConfig(),Red,false),
         btn(wlist,pref.getSmartConfig(),name),

         connector_fire(this,&FireButtonWindow_Sample::fire,btn.fire)
       {
        wlist.insTop(light,btn);
       }

      // drawing

      virtual void layout(unsigned flags)
       {
        Pane pane(Null,getSize());

        Coord dy=light.getMinSize(flags).dxy;

        light.setPlace( TrySplitY(dy,pane) ,ClearUpdate(flags));

        TrySplitY(dy,pane);

        btn.setPlace(pane,flags);
       }
    };

   class XSliderWindow_Sample : public ComboWindow
    {
      TextWindow text;
      XSliderWindow slider;

     private:

      void changed(unsigned pos)
       {
        text.printf("#;",pos);
       }

      SignalConnector<XSliderWindow_Sample,unsigned> connector_changed;

     public:

      XSliderWindow_Sample(SubWindowHost &host,const UserPreference &pref)
       : ComboWindow(host),

         text(wlist,pref.getSmartConfig()),
         slider(wlist,pref.getSmartConfig()),

         connector_changed(this,&XSliderWindow_Sample::changed,slider.changed)
       {
        wlist.insTop(text,slider);

        slider.setCap(1000);
       }

      // drawing

      virtual void layout(unsigned flags)
       {
        Pane pane(Null,getSize());

        Coord dy=text.getMinSize(flags).y;

        text.setPlace( TrySplitY(dy,pane) ,ClearUpdate(flags));

        TrySplitY(dy,pane);

        slider.setPlace(pane,flags);
       }
    };

   class YSliderWindow_Sample : public ComboWindow
    {
      TextWindow text;
      YSliderWindow slider;

     private:

      void changed(unsigned pos)
       {
        text.printf("#;",pos);
       }

      SignalConnector<YSliderWindow_Sample,unsigned> connector_changed;

     public:

      YSliderWindow_Sample(SubWindowHost &host,const UserPreference &pref)
       : ComboWindow(host),

         text(wlist,pref.getSmartConfig()),
         slider(wlist,pref.getSmartConfig()),

         connector_changed(this,&YSliderWindow_Sample::changed,slider.changed)
       {
        wlist.insTop(text,slider);

        slider.setCap(1000);
       }

      // drawing

      virtual void layout(unsigned flags)
       {
        Pane pane(Null,getSize());

        Point s=text.getMinSize("12345"_c);

        Pane left=TrySplitX(s.x,pane);

        text.setPlace( TrySplitY(s.y,left) ,flags);

        TrySplitX(s.y,pane);

        slider.setPlace(pane,flags);
       }
    };

   class RunButtonWindow_Sample : public ComboWindow
    {
      LightWindow light;

      RefVal<DefString> name_off =  "Run"_def ;
      RefVal<DefString> name_on  = "Stop"_def ;

      RefRunButtonWindow btn;

     private:

      void changed(bool on)
       {
        light.turn(on);
       }

      SignalConnector<RunButtonWindow_Sample,bool> connector_changed;

     public:

      RunButtonWindow_Sample(SubWindowHost &host,const UserPreference &pref)
       : ComboWindow(host),

         light(wlist,pref.getSmartConfig(),Red,false),
         btn(wlist,pref.getSmartConfig(),name_off,name_on),

         connector_changed(this,&RunButtonWindow_Sample::changed,btn.changed)
       {
        wlist.insTop(light,btn);
       }

      // drawing

      virtual void layout(unsigned flags)
       {
        Pane pane(Null,getSize());

        Coord dy=light.getMinSize(flags).dxy;

        light.setPlace( TrySplitY(dy,pane) ,ClearUpdate(flags));

        TrySplitY(dy,pane);

        btn.setPlace(pane,flags);
       }
    };

   class LayoutWindow : public SubWindow
    {
      Pane outer;

      Pane red;
      Pane green;
      Pane blue;

     public:

      LayoutWindow(SubWindowHost &host,const UserPreference &)
       : SubWindow(host)
       {
       }

      // drawing

      virtual void layout(unsigned)
       {
        outer=getPane().shrink(10);

        PlaceColumn place(outer,{30,20},10,3);

        red=*place; ++place;
        green=*place; ++place;
        blue=*place;
       }

      virtual void draw(DrawBuf buf,bool) const
       {
        Coord width=Fraction(6,4);

        SmoothDrawArt art(buf);

        FigureBox fig(outer);

        fig.loop(art,HalfPos,width,Black);

        art.block(red,Red);
        art.block(green,Green);
        art.block(blue,Blue);
       }
    };

  public:

   Base() // Update here
    {
     add("Decorative"_def);

       add("XSingleLine"_def,Create<XSingleLineWindow>);
       add("YSingleLine"_def,Create<YSingleLineWindow>);
       add("XDoubleLine"_def,Create<XDoubleLineWindow>);
       add("YDoubleLine"_def,Create<YDoubleLineWindow>);
       add("Contour"_def,Create<ContourWindow>);
       add("TextContour left"_def,Create<TextContourWindow_Left>);
       add("TextContour right"_def,Create<TextContourWindow_Right>);
       add("TextContour center"_def,Create<TextContourWindow_Center>);
       add("Draw"_def,Create_def<DrawWindow>);
       add("Layout"_def,CreateCombo<LayoutWindow>);

     add("Button"_def);

       add("Button"_def,CreateCombo<ButtonWindow_Button>);
       add("Knob"_def,Create<KnobWindow_Asterisk>);
       add("Knob auto"_def,Create<KnobWindow_auto>);
       add("FireButton"_def,CreateCombo<FireButtonWindow_Sample>);
       add("RunButton"_def,CreateCombo<RunButtonWindow_Sample>);

     add("Box"_def);

       add("Check"_def,Create<CheckWindow>);
       add("Switch"_def,Create<SwitchWindow>);
       add("RadioLight"_def,CreateCombo<RadioLightWindow>);
       add("Alt"_def,CreateCombo<AltWindow_Sample>);

     add("Line"_def);

       add("Label"_def,Create<LabelWindow_Label>);
       add("Text"_def,Create<TextWindow_SampleText>);
       add("Label align"_def,CreateCombo<AlignWindow<LabelWindow_Label> >);
       add("Text align"_def,CreateCombo<AlignWindow<TextWindow_SampleText> >);
       add("TextLine"_def,Create<TextLineWindow_SampleText>);
       add("Progress"_def,Create<ProgressWindow_Sample>);
       add("ArrowProgress"_def,Create<ArrowProgressWindow_Sample>);
       add("LineEdit"_def,Create<LineEditWindow>);
       add("XScroll"_def,Create<XScrollWindow_Sample>);
       add("YScroll"_def,Create<YScrollWindow_Sample>);
       add("Spinor"_def,Create<SpinorWindow_Sample>);
       add("XSlider"_def,CreateCombo<XSliderWindow_Sample>);
       add("YSlider"_def,CreateCombo<YSliderWindow_Sample>);

     add("Pane"_def);

       add("Info"_def,Create<InfoWindow_SampleInfo>);
       add("Message knob"_def,Create<MessageWindow_knob>);
       add("Message ok"_def,Create<MessageWindow_ok>);
       add("Message yes/no"_def,Create<MessageWindow_yes_no>);
       add("SimpleTextList"_def,Create<SimpleTextListWindow_SampleList>);

       //add(""_def,Create<>);
    }

   virtual ~Base()
    {
    }

   // methods

   SubFactory getFactory(ulen index) const
    {
     SubFactory ret=list.at(index).factory;

     if( !ret )
       {
        Printf(Exception,"App::ClientWindow::TypeInfo::Base::getFactory(#;) : title index",index);
       }

     return ret;
    }

   // AbstractComboInfo

   virtual ulen getLineCount() const
    {
     return list.getLen();
    }

   virtual ComboInfoItem getLine(ulen index) const
    {
     return list.at(index);
    }
 };

/* class ClientWindow::TypeInfo */

ClientWindow::TypeInfo::TypeInfo()
 : ComboInfo(new Base)
 {
 }

ClientWindow::TypeInfo::~TypeInfo()
 {
 }

auto ClientWindow::TypeInfo::getFactory(ulen index) const -> SubFactory
 {
  return castPtr<Base>()->getFactory(index);
 }

/* class ClientWindow */

void ClientWindow::wheat_changed(bool)
 {
  redraw();
 }

void ClientWindow::type_selected(ulen index)
 {
  if( Change(cur_index,index) )
    {
     // delete old

     cur.set(0);

     // create new

     cur.set( info.getFactory(index)(wlist,pref) );

     wlist.insTop(*cur);

     // update

     list_type.setFocus();

     layout(LayoutResize);
     redraw();
    }
 }

void ClientWindow::space_changed()
 {
  if( +cur )
    {
     cur->setPlace(space.getInner(),LayoutUpdate);

     space.redraw();
    }
 }

ClientWindow::ClientWindow(SubWindowHost &host,const Config &cfg_,const UserPreference &pref_)
 : ComboWindow(host),
   cfg(cfg_),
   pref(pref_),

   check_wheat(wlist,cfg.check_cfg,false),
   label_wheat(wlist,cfg.label_cfg,"Wheat"_def),
   list_type(wlist,cfg.list_cfg,info),
   space(wlist,cfg.space_cfg),

   connector_wheat_changed(this,&ClientWindow::wheat_changed,check_wheat.changed),
   connector_type_selected(this,&ClientWindow::type_selected,list_type.selected),
   connector_space_changed(this,&ClientWindow::space_changed,space.changed)
 {
  wlist.insTop(check_wheat,label_wheat,list_type,space);

  ulen index=list_type.getSelect();

  if( Change(cur_index,index) )
    {
     // create new

     cur.set( info.getFactory(index)(wlist,pref) );

     wlist.insTop(*cur);
    }

  // bind hints

  bindHint(cfg.hint_Text);

  check_wheat.bindHint(cfg.hint_Wheat);

  list_type.bindHint(cfg.hint_List);

  space.bindHint(cfg.hint_Space);
 }

ClientWindow::~ClientWindow()
 {
 }

 // drawing

void ClientWindow::layout(unsigned flags)
 {
  PaneCut pane(getSize(),+cfg.space_dxy,flags);

  pane.shrink();

  // check_wheat , label_wheat , list_type

  {
   auto check__wheat=CutBox(check_wheat);
   auto label__wheat=CutPoint(label_wheat);
   auto list__type=CutPoint(list_type);

   Coordinate len=Coordinate(check__wheat.getExt(flags))+label__wheat.getMinSize(flags).x;

   Coord dx=Sup(list__type.getMinSize(flags).x,+len);

   PaneCut p=pane.cutLeft(dx);

   Coord dy=SupDY(flags,check__wheat,label__wheat);

   PaneCut q=p.cutTop(dy);

   q.place_cutLeft(check__wheat).placeMin(label__wheat);

   p.place(list__type);
  }

  // space

  pane.place(space);

  // cur

  if( +cur )
    {
     cur->setPlace(space.getInner(),flags);
    }
 }

void ClientWindow::drawBack(DrawBuf buf,bool) const
 {
  buf.erase(getBack());
 }

 // base

void ClientWindow::open()
 {
  wlist.open();
 }

} // namespace App

