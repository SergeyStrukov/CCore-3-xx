/* BookFrame.h */
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

#ifndef CCore_inc_video_BookFrame_h
#define CCore_inc_video_BookFrame_h

#include <CCore/inc/video/book/BookWindow.h>

namespace CCore {
namespace Video {

/* classes */

class ShowBookClient;

class BookFrame;

/* class ShowBookClient */

class ShowBookClient
 {
 };

/* class BookFrame */

class BookFrame : NoCopy
 {
   ShowBookClient client;

   DragFrame frame;

  public:

   BookFrame();

   ~BookFrame();
 };

} // namespace Video
} // namespace CCore

#endif

