/* DrawBuf.h */
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

#ifndef CCore_inc_video_DrawBuf_h
#define CCore_inc_video_DrawBuf_h

#include <CCore/inc/video/FrameBuf.h>
#include <CCore/inc/video/Desktop.h>

namespace CCore {
namespace Video {

/* classes */

class DrawBuf;

/* class DrawBuf */

class DrawBuf
 {
  protected:

   FrameBuf<DesktopColor> buf;
   Point origin; // in buf coord

  public:

   DrawBuf() {}

   DrawBuf(const FrameBuf<DesktopColor> &buf_) : buf(buf_) {}

   DrawBuf(const FrameBuf<DesktopColor> &buf_,Point origin_) : buf(buf_),origin(origin_) {}

   // methods

   bool operator + () const { return +buf; }

   bool operator ! () const { return !buf; }

   const FrameBuf<DesktopColor> & getFrameBuf() const { return buf; }

   FrameBuf<DesktopColor> & getFrameBuf() { return buf; }

   void shift(Point delta) { origin+=delta; }

   // cut

   DrawBuf cut(Pane pane) const;

   DrawBuf cutRebase(Pane pane) const;

   // basic draw

   void pixel(Point p,DesktopColor color) { buf.pixel_safe(map(p),color); }

   void erase(DesktopColor color) { buf.erase(color); }

   void erase(Pane pane,DesktopColor color) { buf.block_safe(map(pane),color); }

   void erase(VColor vc,Clr alpha) { buf.erase(vc,alpha); }

   void erase(Pane pane,VColor vc,Clr alpha) { buf.block_safe(map(pane),vc,alpha); }

   void erase(Pane pane,BlenderType blender) { buf.block_safe(map(pane),blender); }

   // map

   template <class T>
   T map(T obj) const { return obj+origin; }

   PointMap getMapper() const { return PointMap(origin); }
 };

} // namespace Video
} // namespace CCore

#endif


