/* InternalDesktop.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Target/LIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_InternalDesktop_h
#define CCore_inc_video_InternalDesktop_h

#include <CCore/inc/video/InternalHost.h>

namespace CCore {
namespace Video {
namespace Internal {

/* classes */

class X11Desktop;

/* class X11Desktop */

class X11Desktop : public Desktop
 {
   Display *display = 0 ;
   int screen = 0 ;
   int fd = -1 ;
   int sem_fd = -1 ;

   X11KeyMap keymap;

  private:

   void guardDisplay(const char *format);

   static Bool MatchAll(Display *,XEvent *,XPointer);

   static int ErrorHandler(Display *display,XErrorEvent *err);

   static int IOErrorHandler(Display *);

  public:

   X11Desktop();

   ~X11Desktop();

   Display * getDisplay() const { return display; }

   int getScreen() const { return screen; }

   // key map

   void updateMap() { keymap.updateMap(display); }

   MouseKey getMKey(unsigned state) const { return keymap.getMKey(state); }

   KeyMod getKMod(unsigned state) const { return keymap.getKMod(state); }

   auto mapToVKey(unsigned state,unsigned keycode) const { return keymap.mapToVKey(state,keycode); }

   auto mapToChar(unsigned state,unsigned keycode) const { return keymap.mapToChar(state,keycode); }

   // Desktop

   virtual WindowHost * createHost();

   virtual Point getScreenSize();

   virtual Pane getMaxPane();

   virtual bool pump(unsigned lim);

   virtual void wait(TimeScope time_scope);

   virtual void interrupt(); // async
 };

/* global DesktopObject */

extern X11Desktop DesktopObject;

} // namespace Internal
} // namespace Video
} // namespace CCore

#endif

