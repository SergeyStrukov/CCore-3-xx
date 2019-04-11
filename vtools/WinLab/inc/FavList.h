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

struct FavRec;

class FavList;

/* struct FavRec */

struct FavRec
 {
  String title;
  String path;
  bool section = false ;
  bool open = true ;
 };

/* class FavList */

class FavList : NoCopy
 {
   DynArray<FavRec> list;

   ulen off = 0 ;
   ulen cur = 0 ;

  private:

   static StrLen Pretext();

  public:

   FavList();

   ~FavList();

   // methods

   void erase();

   PtrLen<const FavRec> getRange(ulen len) const { return Range(list).safe_part(off,len); }

   // load/save

   bool load(StrLen file_name);

   void save(StrLen file_name) const;

   bool load(StrLen key,StrLen file) noexcept;

   void save(StrLen key,StrLen file) const noexcept;
 };

} // namespace Video
} // namespace CCore

#endif


