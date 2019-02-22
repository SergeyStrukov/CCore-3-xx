/* Display.h */
//----------------------------------------------------------------------------------------
//
//  Project: DDLDisplay 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Display_h
#define Display_h

#include <inc/App.h>

#include <CCore/inc/video/lib/Window.ScrollList.h>

#include <CCore/inc/video/MessageFrame.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/String.h>
#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Array.h>

#include <CCore/inc/ddl/DDLEngine.h>

namespace App {

/* SetSize() */

inline void SetSize(Pane &pane,Point size)
 {
  pane.dx=size.x;
  pane.dy=size.y;
 }

/* classes */

class DDLFile;

struct Extension;

struct StrSize;

struct FieldDesc;

struct StructDesc;

struct ValueTarget;

struct PtrDesc;

struct ValueDesc;

struct ConstDesc;

class DDLView;

class DDLInnerWindow;

class DDLWindow;

class DisplayWindow;

/* class DDLFile */

class DDLFile : NoCopy
 {
   PrintString eout;

   FileToMem pretext;

   DDL::FileEngine<FileName,FileToMem> engine;

   DDL::EngineResult result;

  private:

   void erase();

  public:

   DDLFile() noexcept;

   ~DDLFile();

   // methods

   auto getResult() const { return result; }

   struct OpenResult
    {
     String etext;
     bool ok;
    };

   OpenResult open(StrLen file_name);

   OpenResult openPretext(StrLen file_name);

   void noPretext();

   // signals

   Signal<> updated;
 };

/* struct Extension */

struct Extension
 {
  Coord pos;
  Coord len;

  bool operator >= (Extension ext) const { return pos+len > ext.pos ; }

  bool operator <= (Extension ext) const { return pos < ext.pos+ext.len ; }

  bool operator >= (Coord pos_) const { return pos+len > pos_ ; }

  bool operator <= (Coord pos_) const { return pos <= pos_ ; }

  Extension expand(Coord dpos,Coord dlen) const { return {pos-dpos,len+dlen}; }
 };

inline Extension GetExtX(Pane pane) { return {pane.x,pane.dx}; }

inline Extension GetExtY(Pane pane) { return {pane.y,pane.dy}; }

inline void SetExtX(Pane &pane,Extension ext) { pane.x=ext.pos; pane.dx=ext.len; }

inline void SetExtY(Pane &pane,Extension ext) { pane.y=ext.pos; pane.dy=ext.len; }

/* struct StrSize */

struct StrSize
 {
  StrLen str;
  Point size;

  void operator = (StrLen str_) { str=str_; }
 };

/* struct FieldDesc */

struct FieldDesc
 {
  StrSize name;
  Pane place;

  void setSize(Point size) { SetSize(place,size); }

  Extension getExtX() const { return GetExtX(place); }
 };

/* struct StructDesc */

struct StructDesc
 {
  PtrLen<FieldDesc> fields;

  struct Row
   {
    Extension exty = {0,0} ;
    PtrLen<ValueDesc> row;
   };

  PtrLen<Row> table;
 };

/* struct ValueTarget */

struct ValueTarget
 {
  PtrLen<ValueDesc> target;
  bool single = true ;

  ValueDesc *parent = 0 ;
  StructDesc::Row *row = 0 ;

  bool operator + () const { return +target; }

  bool operator ! () const { return !target; }

  Pane frame() const;
 };

/* struct PtrDesc */

struct PtrDesc
 {
  StrSize name;

  struct Index
   {
    ulen index = 0 ;
    StrLen field;

    void set(ulen index_)
     {
      index=index_;
      field=Null;
     }
   };

  PtrLen<Index> index;

  ValueTarget target;
 };

/* struct ValueDesc */

struct ValueDesc
 {
  Pane place;

  AnyPtr<StrSize,PtrLen<ValueDesc>,StructDesc,PtrDesc> ptr;

  ValueDesc() noexcept {}

  ValueDesc(AnyType *ptr_) : ptr(ptr_) {}

  void setSize(Point size) { SetSize(place,size); }

  Extension getExtY() const { return GetExtY(place); }

  class IsScalar;

  bool isScalar() const;
 };

/* struct ConstDesc */

struct ConstDesc
 {
  StrSize name;
  Pane place;

  ValueDesc value;

  void setTitleSize(Point size) { SetSize(place,size); }

  Extension getExtY() const { return {place.y,Max(place.dy,value.place.dy)}; }
 };

/* class DDLView */

class DDLView : NoCopy
 {
   static constexpr ulen TextBufLen = 1_KByte ;

   static constexpr ulen MaxNameLen = 8_KByte ;

   ElementPool pool;

   PtrLen<ConstDesc> consts;

   DynArray<StrLen> field_name;

   DynArray<PtrDesc::Index> index_buf;

   DynArray<PtrDesc *> ptr_buf;

  private:

   void erase();

   // utils

   static void SetTail(PtrLen<char> &ret,char ch);

   static void SetTail(PtrLen<char> &ret,StrLen str);

   static void ProvideIndex(AnyType &obj,ulen index,ulen min_len);

   static void ProvideIndex(AnyType &obj,ulen index) { ProvideIndex(obj,index,100); }

   class GetStructNode;

   // string

   StrLen fieldName(ulen index,StrLen name);

   StrLen fieldName(DDL::FieldNode &field) { return fieldName(field.index,field.name.name.str); }

   StrLen fieldName(DDL::StructNode *struct_node,ulen index);

   StrLen buildName(DDL::ConstNode *node);

   StrLen toString(StrLen value) { return pool.dup(value); }

   StrLen toString(AnyType value);

   struct PrintText;

   StrLen toString(DDL::Text value);

   StrLen toString(DDL::TypeNode::Base *type,DDL::Value value);

   // setPtr

   void setPtr(PtrDesc *desc,DDL::Value value);

   // build

   ValueDesc build(DDL::TypeNode::Base *type,DDL::Value value);

   PtrLen<FieldDesc> buildFields(DDL::StructNode *struct_node);

   ValueDesc build(DDL::StructNode *struct_node,PtrLen<DDL::Value> value);

   ValueDesc build(DDL::TypeNode *type,PtrLen<DDL::Value> value);

   ValueDesc build(DDL::StructNode *struct_node,DDL::Value value);

   ValueDesc build(DDL::AliasNode *alias_node,DDL::Value value);

   ValueDesc build(DDL::TypeNode::Ref *type,DDL::Value value);

   ValueDesc buildPtr(DDL::Value value);

   ValueDesc build(DDL::TypeNode::Ptr *type,DDL::Value value);

   ValueDesc build(DDL::TypeNode::PolyPtr *type,DDL::Value value);

   ValueDesc build(DDL::TypeNode::Array *type,DDL::Value value);

   ValueDesc build(DDL::TypeNode::ArrayLen *type,DDL::Value value);

   ValueDesc build(DDL::TypeNode::Struct *type,DDL::Value value);

   ValueDesc build(DDL::TypeNode *type,DDL::Value value);

   class PtrTarget;

   void setPtrTarget(PtrDesc *desc);

   void setPtrTargets();

   void build(const DDL::EvalResult &result);

  public:

   DDLView();

   ~DDLView();

   PtrLen<ConstDesc> getConstList() const { return consts; }

   void update(DDL::EngineResult result);
 };

/* class DDLInnerWindow */

class DDLInnerWindow : public SubWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Fraction> width = Fraction(6,2) ;

     RefVal<VColor> back   =    Silver ;
     RefVal<VColor> gray   =      Gray ;
     RefVal<VColor> snow   =      Snow ;
     RefVal<VColor> focus  = OrangeRed ;

     // app

     RefVal<Coord> space_dxy = 3 ;

     RefVal<Point> space = Point(6,4) ;

     RefVal<VColor> text   =     Black ;
     RefVal<VColor> ptr    =      Blue ;
     RefVal<VColor> select = OrangeRed ;

     RefVal<Font> title_font;
     RefVal<Font> font;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref)
      {
       bind(pref.get(),pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy)
      {
       width.bind(bag.width);

       back.bind(bag.back);
       gray.bind(bag.gray);
       snow.bind(bag.snow);
       focus.bind(bag.focus);
      }

     template <class Bag>
     void bindApp(const Bag &bag)
      {
       space_dxy.bind(bag.space_dxy);
       space.bind(bag.space);
       text.bind(bag.text);
       ptr.bind(bag.ptr);
       select.bind(bag.select);
       title_font.bind(bag.title_font.font);
       font.bind(bag.font.font);
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   DDLView view;

   bool focus = false ;

   Pane selection;

   // scroll

   ulen wheel_mul = 0 ;

   struct Slide : ScrollPos
    {
     void setPage(ulen page_)
      {
       page=page_;

       adjustPos();
      }

     bool move(Coord delta,ulen mul)
      {
       if( page<total )
         {
          if( delta<0 )
            {
             ulen d=IntAbs(delta);

             d*=mul;

             Replace_min(d,total-page-pos);

             if( d )
               {
                pos+=d;

                return true;
               }
            }
          else
            {
             ulen d=IntAbs(delta);

             d*=mul;

             Replace_min(d,pos);

             if( d )
               {
                pos-=d;

                return true;
               }
            }
         }

       return false;
      }

     bool move(Coord delta,ulen mul,Signal<ulen> &sig)
      {
       if( move(delta,mul) )
         {
          sig.assert(pos);

          return true;
         }

       return false;
      }

     bool set(ulen pos_)
      {
       if( page>=total ) return false;

       Replace_min(pos_,total-page);

       return Change(pos,pos_);
      }

     bool set(ulen pos_,Signal<ulen> &sig)
      {
       if( set(pos_) )
         {
          sig.assert(pos);

          return true;
         }

       return false;
      }
    };

   Slide slide_x;
   Slide slide_y;

  private:

   Point getOff() const { return {Coord(slide_x.pos),Coord(slide_y.pos)}; }

   Point getFull() const { return {Coord(slide_x.total),Coord(slide_y.total)}; }

   class SizeProc;

   void sizeView();

   class PlaceProc;

   void placeView();

   void layoutView();

   void update()
    {
     layoutView();

     selection=Null;
    }

   struct ClipProc;

   class DrawProc;

   class FindProc;

   ValueDesc * find(Point pos) const;

   void moveTo(ValueTarget target,Point point);

   void moveTo(Point target,Point point);

   void moveTo(Point pos);

   void select(Pane pane);

  private:

   void posX(ulen pos);

   void posY(ulen pos);

   SignalConnector<DDLInnerWindow,ulen> connector_posX;
   SignalConnector<DDLInnerWindow,ulen> connector_posY;

   void updated(unsigned flags);

   SignalConnector<DDLInnerWindow,unsigned> connector_updated;

  public:

   DDLInnerWindow(SubWindowHost &host,const Config &cfg);

   virtual ~DDLInnerWindow();

   // special methods

   bool shortDX() const { return slide_x.tooShort(); }

   bool shortDY() const { return slide_y.tooShort(); }

   ScrollPos getScrollXRange() const { return slide_x; }

   ScrollPos getScrollYRange() const { return slide_y; }

   void connect(Signal<ulen> &scroll_x,Signal<ulen> &scroll_y)
    {
     connector_posX.connect(scroll_x);
     connector_posY.connect(scroll_y);
    }

   // methods

   Point getMinSize(Point cap=Point::Max()) const { Used(cap); return Point(100,100); }

   void update(DDL::EngineResult result);

   // drawing

   virtual bool isGoodSize(Point size) const
    {
     return size>=getMinSize();
    }

   virtual void layout();

   virtual void draw(DrawBuf buf,DrawParam draw_param) const;

   // base

   virtual void open();

   // keyboard

   virtual void gainFocus();

   virtual void looseFocus();

   // user input

   virtual void react(UserAction action);

   void react_LeftClick(Point point,MouseKey mkey);

   void react_Wheel(Point,MouseKey mkey,Coord delta);

   // signals

   Signal<ulen> scroll_x;
   Signal<ulen> scroll_y;
 };

/* class DDLWindow */

class DDLWindow : public ScrollableWindow<DDLInnerWindow>
 {
   const DDLFile &file;

  private:

   void file_updated();

   SignalConnector<DDLWindow> connector_file_updated;

  public:

   DDLWindow(SubWindowHost &host,const Config &cfg,DDLFile &file);

   virtual ~DDLWindow();
 };

/* class DisplayWindow */

class DisplayWindow : public ComboWindow
 {
  public:

   struct Config
    {
     // user

     RefVal<Coord> space_dxy = 10 ;

     RefVal<VColor> back = Silver ;

     CtorRefVal<MessageFrame::AlertConfigType> msg_cfg;
     CtorRefVal<LabelWindow::ConfigType> label_cfg;
     CtorRefVal<TextLineWindow::ConfigType> textline_cfg;
     CtorRefVal<XDoubleLineWindow::ConfigType> dline_cfg;

     // app

     DDLWindow::Config ddl_cfg;

     Config() noexcept {}

     template <class AppPref>
     Config(const UserPreference &pref,const AppPref &app_pref)
      : ddl_cfg(pref,app_pref)
      {
       bind(pref.get(),pref.getSmartConfig());
       bindApp(app_pref.get());
      }

     template <class Bag,class Proxy>
     void bind(const Bag &bag,Proxy proxy)
      {
       space_dxy.bind(bag.space_dxy);
       back.bind(bag.back);

       msg_cfg.bind(proxy);
       label_cfg.bind(proxy);
       textline_cfg.bind(proxy);
       dline_cfg.bind(proxy);
      }

     template <class Bag>
     void bindApp(const Bag &)
      {
      }
    };

   using ConfigType = Config ;

  private:

   const Config &cfg;

   DDLFile file;

   // subwins

   LabelWindow label_pretext;
   LabelWindow label_file;

   TextLineWindow text_pretext;
   TextLineWindow text_file;

   XDoubleLineWindow dline;

   DDLWindow ddl;

   // msg

   MessageFrame msg_frame;

  private:

   void error(StrLen str);

   void setPretextFileName(StrLen file_name);

   void setFileName(StrLen file_name);

  public:

   DisplayWindow(SubWindowHost &host,const Config &cfg);

   virtual ~DisplayWindow();

   // methods

   Point getMinSize() const;

   void open(StrLen file_name);

   void openPretext(StrLen file_name);

   void noPretext();

   // drawing

   virtual void layout();

   virtual void drawBack(DrawBuf buf,DrawParam &draw_param) const;

   // signals

   Signal<StrLen,bool> opened; // file_name ,  ok
 };

} // namespace App

#endif
