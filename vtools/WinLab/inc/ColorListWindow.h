/* ColorListWindow.h */
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

#ifndef CCore_inc_video_pref_ColorListWindow_h
#define CCore_inc_video_pref_ColorListWindow_h

#include <CCore/inc/video/WindowLib.h>

namespace CCore {
namespace Video {

/* classes */

struct NamedColor;

struct AbstractColorInfo;

class ColorListShape;

/* struct NamedColor */

struct NamedColor
 {
  String name;
  VColor vc = Black ;
 };

/* struct AbstractColorInfo */

struct AbstractColorInfo
 {
  virtual ulen getLineCount() const =0;

  virtual NamedColor getLine(ulen index) const =0;
 };

/* type ColorInfoBase */

using ColorInfoBase = RefObjectBase<AbstractColorInfo> ;

/* GetNullColorInfoPtr() */

ColorInfoBase * GetNullColorInfoPtr();

/* type ColorInfo */

using ColorInfo = RefObjectHook<ColorInfoBase,AbstractColorInfo,GetNullColorInfoPtr> ;

/* class ColorListShape */

class ColorListShape : public ScrollListState
 {
  public:

   struct Config
    {
     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> back         =    Silver ;
     RefVal<VColor> focus        = OrangeRed ;
     RefVal<VColor> gray         =      Gray ;
     RefVal<VColor> snow         =      Snow ;
     RefVal<VColor> inactive     =      Gray ;
     RefVal<VColor> select       =    Yellow ;
     RefVal<VColor> text         =     Black ;
     RefVal<VColor> net          =     Black ;

     RefVal<Point> space = Point(8,8) ;

     RefVal<Font> font;

     Config() noexcept {}

     template <class Bag>
     void bind(const Bag &bag)
      {
       width.bind(bag.width);
       back.bind(bag.back);
       focus.bind(bag.focus);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       inactive.bind(bag.inactive);

       select.bind(bag.text_select);

       text.bind(bag.list_text);
       net.bind(bag.list_net);
       space.bind(bag.list_space);
       font.bind(bag.list_font.font);
      }
    };

   using InfoType = ColorInfo ;

   // parameters

   const Config &cfg;
   ColorInfo info;
   Pane pane;
   unsigned update_mask = LayoutUpdate ;

   // methods

   explicit ColorListShape(const Config &cfg_) : cfg(cfg_) {}

   ColorListShape(const Config &cfg_,const ColorInfo &info_) : cfg(cfg_),info(info_) { setSelectDown(0); }

   void update(unsigned flags) { if( flags&update_mask ) cache.ok=false; }

   Point getMinSize(Point cap=Point::Max()) const;

   Point getMinSize(unsigned lines) const;

   bool isGoodSize(Point size,Point cap=Point::Max()) const { return size>=getMinSize(cap); }

   void layout();

   void initSelect();

   ulen getLineCount() const { return info->getLineCount(); }

   bool isSelectable(ulen) const { return true; }

   bool setSelectDown(ulen pos);

   bool setSelectUp(ulen pos);

   bool showSelect();

   ulen getPosition(Point point) const;

   void draw(const DrawBuf &buf) const;

  private:

   static StrLen SampleLine();

   static Point LineSize(Font font,Point space,const ColorInfo &info);

   static Point ExtSpace(const Config &cfg);

   struct Cache
    {
     Point line;

     Coord med_dx = 0 ;
     bool ok = false ;

     void operator () (const Config &cfg,const ColorInfo &info);
    };

   mutable Cache cache;
 };

/* type ColorListWindow */

using ColorListWindow = ScrollListWindowOf<ColorListShape,XScrollShape,YScrollShape> ;

} // namespace Video
} // namespace CCore

#endif
