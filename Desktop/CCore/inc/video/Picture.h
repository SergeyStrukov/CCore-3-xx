/* Picture.h */
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

#ifndef CCore_inc_video_Picture_h
#define CCore_inc_video_Picture_h

#include <CCore/inc/video/DrawBuf.h>

#include <CCore/inc/RefObjectBase.h>

namespace CCore {
namespace Video {

/* classes */

struct AbstractPicture;

class Picture;

class DefaultAppIcon;

/* struct AbstractPicture */

struct AbstractPicture
 {
  // abstract

  virtual ulen getCount() const =0;

  virtual Point getSize() const =0;

  virtual VColor defaultGround() const =0;

  virtual void draw(ulen index,DrawBuf buf,Coord dx,Coord dy) const =0;

  // helpers

  void draw(ulen index,const DrawBuf &buf,Pane place) const
   {
    draw(index,buf.cutRebase(place),place.dx,place.dy);
   }

  void draw(const DrawBuf &buf,Coord dx,Coord dy) const
   {
    draw(0,buf,dx,dy);
   }

  void draw(const DrawBuf &buf,Pane place) const
   {
    draw(0,buf.cutRebase(place),place.dx,place.dy);
   }

  Point sizeX(Coord dx) const
   {
    return {dx,YdivX(getSize())*dx};
   }

  Point sizeY(Coord dy) const
   {
    return {XdivY(getSize())*dy,dy};
   }
 };

/* type PictureBase */

using PictureBase = RefObjectBase<AbstractPicture> ;

/* class Picture */

class Picture
 {
   RefPtr<PictureBase> ptr;

  protected:

   explicit Picture(PictureBase *pict) : ptr(pict) {}

   template <class T>
   T * castPtr() const { return dynamic_cast<T *>(ptr.getPtr()); }

  public:

   Picture() noexcept; // empty picture

   ~Picture() {}

   const AbstractPicture * getPtr() const { return ptr.getPtr(); }

   const AbstractPicture * operator -> () const { return ptr.getPtr(); }
 };

/* class DefaultAppIcon */

class DefaultAppIcon : public Picture
 {
   class Base;

  public:

   DefaultAppIcon();
 };

/* SetAppIcon() */

void SetAppIcon(Picture pict); // implemented by the target

} // namespace Video
} // namespace CCore

#endif

