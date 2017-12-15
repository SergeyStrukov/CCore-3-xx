/* Layout.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
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

#ifndef CCore_inc_video_Layout_h
#define CCore_inc_video_Layout_h

#include <CCore/inc/video/Desktop.h>

#include <CCore/inc/video/MinSizeType.h>

#include <CCore/inc/algon/ApplyToList.h>

namespace CCore {
namespace Video {

/* FitToScreen() */

Pane FitToScreen(Point base,Point size,Point screen_size);

/* GetWindowPlace() */

Pane GetWindowPlace(Pane outer,Ratio ry,Point size);

Pane GetWindowPlace(Desktop *desktop,Ratio ry,Point size);

/* FreeCenter...() */

Pane FreeCenter(Pane outer,Point size);

inline Pane FreeCenter(Pane outer,Coordinate dxy) { return FreeCenter(outer,{dxy,dxy}); }

inline Pane FreeCenter(Point outer,Point size) { return FreeCenter(Pane(Null,outer),size); }

Pane FreeCenterX(Pane outer,Coordinate dx);

Pane FreeCenterY(Pane outer,Coordinate dy);

//----------------------------------------------------------------------------------------

/* concept PlaceType<W> */

template <class W> // ref extended
concept bool PlaceType = requires(W &obj,Meta::ToConst<W> &cobj,Pane pane,unsigned flags)
 {
  cobj.getMinSize();

  obj.setPlace(pane,flags);
 } ;

/* concept PlaceOfType<W,T> */

template <class W,class T> // W ref extended
concept bool PlaceOfType = PlaceType<W> && requires(Meta::ToConst<W> &cobj)
 {
  { cobj.getMinSize() } -> T ;
 } ;

/* PosSubMul() */

Coord PosSubMul(Coord a,ulen count,Coord b);

/* Align...() */

Pane AlignLeft(Pane pane,Coord dx);

Pane AlignCenterX(Pane pane,Coord dx);

Pane AlignRight(Pane pane,Coord dx);

Pane AlignTop(Pane pane,Coord dy);

Pane AlignCenterY(Pane pane,Coord dy);

Pane AlignBottom(Pane pane,Coord dy);

Pane AlignCenter(Pane pane,Coord dx,Coord dy);

inline Pane AlignCenter(Pane pane,Point size) { return AlignCenter(pane,size.x,size.y); }

/* Box...() */

inline Coordinate BoxSpace(Coordinate dxy) { return dxy/5; }

inline Coord BoxSpace(Coord dxy) { return dxy/5; }

inline Coordinate BoxExt(Coordinate dxy) { return dxy+BoxSpace(dxy); }

inline Coord BoxExt(Coord dxy) { return +BoxExt(Coordinate(dxy)); }

/* GetMinSize() */

Point GetMinSize(const PlaceType &window) { return ToSizePoint(window.getMinSize()); }

/* SupMinSize() */

template <class ... WW>
Point SupMinSize(const WW & ... ww) requires ( ... && PlaceType<WW> )
 {
  return Sup( GetMinSize(ww)... );
 }

/* SupDX() */

Coord SupDX(const PlaceType &window) { return GetMinSize(window).x; }

template <class ... WW>
Coord SupDX(const WW & ... ww) requires ( ... && PlaceType<WW> )
 {
  return Sup( SupDX(ww)... );
 }

/* SupDY() */

Coord SupDY(const PlaceType &window) { return GetMinSize(window).y; }

template <class ... WW>
Coord SupDY(const WW & ... ww) requires ( ... && PlaceType<WW> )
 {
  return Sup( SupDY(ww)... );
 }

/* ReplaceToSup() */

template <class ... TT>
void ReplaceToSup(TT & ... tt)
 {
  auto sup=Sup(tt...);

  Algon::ApplyToList( [sup] (auto &obj) { obj=sup; } , tt...  );
 }

/* classes */

template <PlaceType W,Pane Func(Pane pane,Coord dx)> struct AlignXProxy;

template <PlaceType W,Pane Func(Pane pane,Coord dy)> struct AlignYProxy;

template <PlaceOfType<SizeBox> W> struct CutBox;

template <PlaceType W> struct CutPoint;

class PlaceRow;

class PlaceColumn;

class PaneCut;

/* struct AlignXProxy<W,Pane Func(Pane pane,Coord dx)> */

template <PlaceType W,Pane Func(Pane pane,Coord dx)>
struct AlignXProxy
 {
  W &window;
  Point size;

  explicit AlignXProxy(W &window_) : window(window_),size(GetMinSize(window_)) {}

  SizeY getMinSize() const { return size.y; }

  void setPlace(Pane pane,unsigned flags) { window.setPlace(Func(pane,size.x),flags); }
 };

/* AlignX() */

template <PlaceType W>
auto AlignLeft(W &window) { return AlignXProxy<W,AlignLeft>(window); }

template <PlaceType W>
auto AlignCenterX(W &window) { return AlignXProxy<W,AlignCenterX>(window); }

template <PlaceType W>
auto AlignRight(W &window) { return AlignXProxy<W,AlignRight>(window); }

/* struct AlignYProxy<W,Pane Func(Pane pane,Coord dy)> */

template <PlaceType W,Pane Func(Pane pane,Coord dy)>
struct AlignYProxy
 {
  W &window;
  Point size;

  explicit AlignYProxy(W &window_) : window(window_),size(GetMinSize(window_)) {}

  SizeX getMinSize() const { return size.x; }

  void setPlace(Pane pane,unsigned flags) { window.setPlace(Func(pane,size.y),flags); }
 };

/* AlignY() */

template <PlaceType W>
auto AlignTop(W &window) { return AlignYProxy<W,AlignTop>(window); }

template <PlaceType W>
auto AlignCenterY(W &window) { return AlignYProxy<W,AlignCenterY>(window); }

template <PlaceType W>
auto AlignBottom(W &window) { return AlignYProxy<W,AlignBottom>(window); }

/* struct CutBox<W> */

template <PlaceOfType<SizeBox> W>
struct CutBox
 {
  W &window;
  Coord dxy;

  explicit CutBox(W &window_) : window(window_),dxy(window_.getMinSize().dxy) {}

  CutBox(W &window_,Ratio scale) : window(window_),dxy(scale*window_.getMinSize().dxy) {}

  SizeXSpace getMinSize() const { return SizeXSpace(dxy,BoxSpace(dxy)); }

  void setPlace(Pane pane,unsigned flags) { window.setPlace(AlignCenterY(pane,dxy),flags); }

  Coord getExt() const { return BoxExt(dxy); }
 };

Coord SupDY(const CutBox<AnyType> &window) { return window.dxy; }

/* struct CutPoint<W> */

template <PlaceType W>
struct CutPoint
 {
  W &window;
  Point size;

  explicit CutPoint(W &window_) : window(window_),size(GetMinSize(window_)) {}

  CutPoint(W &window_,Ratio scale) : window(window_),size(scale*GetMinSize(window_)) {}

  Point getMinSize() const { return size; }

  void setPlace(Pane pane,unsigned flags) { window.setPlace(pane,flags); }
 };

/* class PlaceRow */

class PlaceRow
 {
   Point base;
   Point size;

   Coord delta;
   Coord cap;

  public:

   PlaceRow(Pane outer,Point size,Coord space,ulen count);

   Pane operator * () const { return Pane(base,size); }

   void operator ++ ()
    {
     if( size.x>0 )
       {
        if( cap>delta )
          {
           cap-=delta;

           Replace_min(size.x,cap);

           base.x+=delta;
          }
        else
          {
           cap=0;
           size.x=0;
          }
       }
    }

   template <class ... WW>
   void place(unsigned flags,WW && ... ww) requires ( ... && PlaceType<WW> )
    {
     Algon::ApplyToList( [this,flags] (AnyType &&window) { window.setPlace(*(*this),flags); ++(*this); } , std::forward<WW>(ww)... );
    }
 };

/* class PlaceColumn */

class PlaceColumn
 {
   Point base;
   Point size;

   Coord delta;
   Coord cap;

  public:

   PlaceColumn(Pane outer,Point size,Coord space,ulen count);

   Pane operator * () const { return Pane(base,size); }

   void operator ++ ()
    {
     if( size.y>0 )
       {
        if( cap>delta )
          {
           cap-=delta;

           Replace_min(size.y,cap);

           base.y+=delta;
          }
        else
          {
           cap=0;
           size.y=0;
          }
       }
    }

   template <class ... WW>
   void place(unsigned flags,WW && ... ww) requires ( ... && PlaceType<WW> )
    {
     Algon::ApplyToList( [this,flags] (AnyType &&window) { window.setPlace(*(*this),flags); ++(*this); } , std::forward<WW>(ww)... );
    }
 };

/* class PaneCut */

class PaneCut
 {
   Pane pane;
   Coord space; // >= 0
   unsigned flags;

  public:

   explicit PaneCut(Coord space_,unsigned flags_) : space(space_),flags(flags_) {}

   PaneCut(Pane pane_,Coord space_,unsigned flags_) : pane(pane_),space(space_),flags(flags_) {}

   PaneCut(Point size,Coord space_,unsigned flags_) : pane(Null,size),space(space_),flags(flags_) {}

   // methods

   Point getMinSize() const { return 3*Point::Diag(space); }

   operator Pane() const { return pane; }

   Point getSize() const { return pane.getSize(); }

   void setPlace(Pane pane_,unsigned flags_) { pane=pane_; flags=flags_; }

   void shrink();

   // cut

   PaneCut cutLeft(Coord dx,Coord space);

   PaneCut cutRight(Coord dx,Coord space);

   PaneCut cutTop(Coord dy,Coord space);

   PaneCut cutBottom(Coord dy,Coord space);


   PaneCut cutLeft(Coord dx) { return cutLeft(dx,space); }

   PaneCut cutRight(Coord dx) { return cutRight(dx,space); }

   PaneCut cutTop(Coord dy) { return cutTop(dy,space); }

   PaneCut cutBottom(Coord dy) { return cutBottom(dy,space); }


   PaneCut cutLeft(SizeXSpace size) { return cutLeft(size.dx,size.space); }

   PaneCut cutRight(SizeXSpace size) { return cutRight(size.dx,size.space); }

   PaneCut cutTop(SizeYSpace size) { return cutTop(size.dy,size.space); }

   PaneCut cutBottom(SizeYSpace size) { return cutBottom(size.dy,size.space); }


   PaneCut cutLeft(Ratio rx) { return cutLeft(rx*pane.dx); }

   PaneCut cutRight(Ratio rx) { return cutRight(rx*pane.dx); }

   PaneCut cutTop(Ratio ry) { return cutTop(ry*pane.dy); }

   PaneCut cutBottom(Ratio ry) { return cutBottom(ry*pane.dy); }


   PaneCut cutLeft(Ratio rx,Coord space) { return cutLeft(rx*pane.dx,space); }

   PaneCut cutRight(Ratio rx,Coord space) { return cutRight(rx*pane.dx,space); }

   PaneCut cutTop(Ratio ry,Coord space) { return cutTop(ry*pane.dy,space); }

   PaneCut cutBottom(Ratio ry,Coord space) { return cutBottom(ry*pane.dy,space); }

   // cut + align

   Pane cutLeftTop(Coord dx,Coord dy) { return AlignTop(cutLeft(dx),dy); }

   Pane cutLeftCenter(Coord dx,Coord dy) { return AlignCenterY(cutLeft(dx),dy); }

   Pane cutLeftBottom(Coord dx,Coord dy) { return AlignBottom(cutLeft(dx),dy); }

   Pane cutRightTop(Coord dx,Coord dy) { return AlignTop(cutRight(dx),dy); }

   Pane cutRightCenter(Coord dx,Coord dy) { return AlignCenterY(cutRight(dx),dy); }

   Pane cutRightBottom(Coord dx,Coord dy) { return AlignBottom(cutRight(dx),dy); }

   Pane cutTopLeft(Coord dx,Coord dy) { return AlignLeft(cutTop(dy),dx); }

   Pane cutTopCenter(Coord dx,Coord dy) { return AlignCenterX(cutTop(dy),dx); }

   Pane cutTopRight(Coord dx,Coord dy) { return AlignRight(cutTop(dy),dx); }

   Pane cutBottomLeft(Coord dx,Coord dy) { return AlignLeft(cutBottom(dy),dx); }

   Pane cutBottomCenter(Coord dx,Coord dy) { return AlignCenterX(cutBottom(dy),dx); }

   Pane cutBottomRight(Coord dx,Coord dy) { return AlignRight(cutBottom(dy),dx); }


   Pane cutLeftTop(Point size) { return cutLeftTop(size.x,size.y); }

   Pane cutLeftCenter(Point size) { return cutLeftCenter(size.x,size.y); }

   Pane cutLeftBottom(Point size) { return cutLeftBottom(size.x,size.y); }

   Pane cutRightTop(Point size) { return cutRightTop(size.x,size.y); }

   Pane cutRightCenter(Point size) { return cutRightCenter(size.x,size.y); }

   Pane cutRightBottom(Point size) { return cutRightBottom(size.x,size.y); }

   Pane cutTopLeft(Point size) { return cutTopLeft(size.x,size.y); }

   Pane cutTopCenter(Point size) { return cutTopCenter(size.x,size.y); }

   Pane cutTopRight(Point size) { return cutTopRight(size.x,size.y); }

   Pane cutBottomLeft(Point size) { return cutBottomLeft(size.x,size.y); }

   Pane cutBottomCenter(Point size) { return cutBottomCenter(size.x,size.y); }

   Pane cutBottomRight(Point size) { return cutBottomRight(size.x,size.y); }

   // place

   void place(PlaceType &&window) const { window.setPlace(pane,flags); }

   void placeMin(PlaceType &&window) const { window.setPlace(Pane(pane.getBase(),GetMinSize(window)),flags); }

   void placeSmart(PlaceOfType<Point> &&window) const { window.setPlace(pane,flags); }

   void placeSmart(PlaceOfType<SizeBox> &&window) const { window.setPlace(Square(pane),flags); }


   PaneCut & place_cutLeft(PlaceType &&window,OneOfTypes<Coord,Ratio> dx) { window.setPlace(cutLeft(dx),flags); return *this; }

   PaneCut & place_cutRight(PlaceType &&window,OneOfTypes<Coord,Ratio> dx) { window.setPlace(cutRight(dx),flags); return *this; }

   PaneCut & place_cutTop(PlaceType &&window,OneOfTypes<Coord,Ratio> dy) { window.setPlace(cutTop(dy),flags); return *this; }

   PaneCut & place_cutBottom(PlaceType &&window,OneOfTypes<Coord,Ratio> dy) { window.setPlace(cutBottom(dy),flags); return *this; }


   PaneCut & place_cutLeft(PlaceType &&window,OneOfTypes<Coord,Ratio> dx,Coord space) { window.setPlace(cutLeft(dx,space),flags); return *this; }

   PaneCut & place_cutRight(PlaceType &&window,OneOfTypes<Coord,Ratio> dx,Coord space) { window.setPlace(cutRight(dx,space),flags); return *this; }

   PaneCut & place_cutTop(PlaceType &&window,OneOfTypes<Coord,Ratio> dy,Coord space) { window.setPlace(cutTop(dy,space),flags); return *this; }

   PaneCut & place_cutBottom(PlaceType &&window,OneOfTypes<Coord,Ratio> dy,Coord space) { window.setPlace(cutBottom(dy,space),flags); return *this; }


   PaneCut & place_cutLeft(PlaceType &&window,SizeXSpace size) { window.setPlace(cutLeft(size),flags); return *this; }

   PaneCut & place_cutRight(PlaceType &&window,SizeXSpace size) { window.setPlace(cutRight(size),flags); return *this; }

   PaneCut & place_cutTop(PlaceType &&window,SizeYSpace size) { window.setPlace(cutTop(size),flags); return *this; }

   PaneCut & place_cutBottom(PlaceType &&window,SizeYSpace size) { window.setPlace(cutBottom(size),flags); return *this; }


   PaneCut & place_cutLeftTop(PlaceType &&window,Point size) { window.setPlace(cutLeftTop(size),flags); return *this; }

   PaneCut & place_cutLeftCenter(PlaceType &&window,Point size) { window.setPlace(cutLeftCenter(size),flags); return *this; }

   PaneCut & place_cutLeftBottom(PlaceType &&window,Point size) { window.setPlace(cutLeftBottom(size),flags); return *this; }

   PaneCut & place_cutRightTop(PlaceType &&window,Point size) { window.setPlace(cutRightTop(size),flags); return *this; }

   PaneCut & place_cutRightCenter(PlaceType &&window,Point size) { window.setPlace(cutRightCenter(size),flags); return *this; }

   PaneCut & place_cutRightBottom(PlaceType &&window,Point size) { window.setPlace(cutRightBottom(size),flags); return *this; }

   PaneCut & place_cutTopLeft(PlaceType &&window,Point size) { window.setPlace(cutTopLeft(size),flags); return *this; }

   PaneCut & place_cutTopCenter(PlaceType &&window,Point size) { window.setPlace(cutTopCenter(size),flags); return *this; }

   PaneCut & place_cutTopRight(PlaceType &&window,Point size) { window.setPlace(cutTopRight(size),flags); return *this; }

   PaneCut & place_cutBottomLeft(PlaceType &&window,Point size) { window.setPlace(cutBottomLeft(size),flags); return *this; }

   PaneCut & place_cutBottomCenter(PlaceType &&window,Point size) { window.setPlace(cutBottomCenter(size),flags); return *this; }

   PaneCut & place_cutBottomRight(PlaceType &&window,Point size) { window.setPlace(cutBottomRight(size),flags); return *this; }


   PaneCut & place_cutLeftTop(PlaceType &&window) { window.setPlace(cutLeftTop(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutLeftCenter(PlaceType &&window) { window.setPlace(cutLeftCenter(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutLeftBottom(PlaceType &&window) { window.setPlace(cutLeftBottom(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutRightTop(PlaceType &&window) { window.setPlace(cutRightTop(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutRightCenter(PlaceType &&window) { window.setPlace(cutRightCenter(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutRightBottom(PlaceType &&window) { window.setPlace(cutRightBottom(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutTopLeft(PlaceType &&window) { window.setPlace(cutTopLeft(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutTopCenter(PlaceType &&window) { window.setPlace(cutTopCenter(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutTopRight(PlaceType &&window) { window.setPlace(cutTopRight(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutBottomLeft(PlaceType &&window) { window.setPlace(cutBottomLeft(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutBottomCenter(PlaceType &&window) { window.setPlace(cutBottomCenter(GetMinSize(window)),flags); return *this; }

   PaneCut & place_cutBottomRight(PlaceType &&window) { window.setPlace(cutBottomRight(GetMinSize(window)),flags); return *this; }

   // place Point

   PaneCut & place_cutLeft(PlaceOfType<Point> &&window) { place_cutLeft(window,window.getMinSize().x); return *this; }

   PaneCut & place_cutRight(PlaceOfType<Point> &&window) { place_cutRight(window,window.getMinSize().x); return *this; }

   PaneCut & place_cutTop(PlaceOfType<Point> &&window) { place_cutTop(window,window.getMinSize().y); return *this; }

   PaneCut & place_cutBottom(PlaceOfType<Point> &&window) { place_cutBottom(window,window.getMinSize().y); return *this; }

   // place X

   PaneCut & place_cutLeft(PlaceOfType<SizeX> &&window) { place_cutLeft(window,window.getMinSize().dx); return *this; }

   PaneCut & place_cutRight(PlaceOfType<SizeX> &&window) { place_cutRight(window,window.getMinSize().dx); return *this; }

   // place XSpace

   PaneCut & place_cutLeft(PlaceOfType<SizeXSpace> &&window) { place_cutLeft(window,window.getMinSize()); return *this; }

   PaneCut & place_cutRight(PlaceOfType<SizeXSpace> &&window) { place_cutRight(window,window.getMinSize()); return *this; }

   // place Y

   PaneCut & place_cutTop(PlaceOfType<SizeY> &&window) { place_cutTop(window,window.getMinSize().dy); return *this; }

   PaneCut & place_cutBottom(PlaceOfType<SizeY> &&window) { place_cutBottom(window,window.getMinSize().dy); return *this; }

   // place YSpace

   PaneCut & place_cutTop(PlaceOfType<SizeYSpace> &&window) { place_cutTop(window,window.getMinSize()); return *this; }

   PaneCut & place_cutBottom(PlaceOfType<SizeYSpace> &&window) { place_cutBottom(window,window.getMinSize()); return *this; }

   // place Box

   PaneCut & place_cutLeft(PlaceOfType<SizeBox> &&window) { place_cutLeft(CutBox(window)); return *this; }

   PaneCut & place_cutRight(PlaceOfType<SizeBox> &&window) { place_cutRight(CutBox(window)); return *this; }

   // placeRow

   template <class ... WW>
   PaneCut & placeRow_cutTop(WW && ... ww) requires ( ... && PlaceOfType<WW,Point> )
    {
     Point size=SupMinSize(ww...);

     PlaceRow row(cutTop(size.y),size,space,sizeof ... (WW));

     row.place(flags,ww...);

     return *this;
    }

   template <class ... WW>
   PaneCut & placeRow_cutBottom(WW && ... ww) requires ( ... && PlaceOfType<WW,Point> )
    {
     Point size=SupMinSize(ww...);

     PlaceRow row(cutBottom(size.y),size,space,sizeof ... (WW));

     row.place(flags,ww...);

     return *this;
    }

   // placeColumn

   template <class ... WW>
   PaneCut & placeColumn_cutLeft(WW && ... ww) requires ( ... && PlaceOfType<WW,Point> )
    {
     Point size=SupMinSize(ww...);

     PlaceColumn col(cutLeft(size.x),size,space,sizeof ... (WW));

     col.place(flags,ww...);

     return *this;
    }

   template <class ... WW>
   PaneCut & placeColumn_cutRight(WW && ... ww) requires ( ... && PlaceOfType<WW,Point> )
    {
     Point size=SupMinSize(ww...);

     PlaceColumn col(cutRight(size.x),size,space,sizeof ... (WW));

     col.place(flags,ww...);

     return *this;
    }
 };

} // namespace Video
} // namespace CCore

#endif

