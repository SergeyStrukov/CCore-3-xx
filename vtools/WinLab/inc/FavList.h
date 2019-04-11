/* FavList.h */
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

#ifndef CCore_inc_video_FavList_h
#define CCore_inc_video_FavList_h

#include <CCore/inc/Array.h>
#include <CCore/inc/String.h>

namespace CCore {
namespace Video {

/* classes */

class FavList;

/* class FavList */

class FavList : NoCopy
 {
   struct Rec
    {
     String title;
     String path;
     bool section = false ;
     bool open = true ;
    };

   DynArray<Rec> list;

   ulen off = 0 ;
   ulen cur = 0 ;

  private:

   static StrLen Pretext();

  public:

   FavList();

   ~FavList();

   // methods

   // load/save

   bool load(StrLen file_name);

   void save(StrLen file_name) const;

   bool load(StrLen key,StrLen file) noexcept;

   void save(StrLen key,StrLen file) const noexcept;
 };

} // namespace Video
} // namespace CCore

#endif


