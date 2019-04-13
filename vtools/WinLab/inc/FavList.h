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
#include <CCore/inc/ForLoop.h>

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

  bool isVisible() const { return section || open ; }
 };

/* class FavList */

class FavList : NoCopy
 {
   DynArray<FavRec> list;

   ulen off = 0 ;
   ulen cur = 0 ;

  private:

   static StrLen Pretext();

   static void SetOpenFlags(PtrLen<FavRec> list);

   static void SetOpen(PtrLen<FavRec> list,bool flag);

   PtrLen<const FavRec> getRange() const { return Range(list).safe_part(off); }

   struct PosResult
    {
     ulen pos;
     bool ok;

     bool get(ulen &var)
      {
       if( ok )
         {
          var=pos;

          return true;
         }

       return false;
      }
    };

   PosResult posUp(ulen pos) const;

   PosResult posDown(ulen pos) const;

   PosResult posUp(ulen pos,ulen count) const;

   PosResult posDown(ulen pos,ulen count) const;

  public:

   FavList();

   ~FavList();

   // methods

   const FavRec * getCur() const
    {
     if( cur<list.getLen() ) return &list[cur];

     return 0;
    }

   void erase();

   bool curUp();

   bool curDown();

   bool curBeg();

   bool curEnd();

   bool curUp(ulen count);

   bool curDown(ulen count);

   bool offUp();

   bool offDown();

   bool offUp(ulen count);

   bool offDown(ulen count);

   void makeVisible(ulen count);

   bool curOpen();

   bool curClose();

   struct ActResult
    {
     bool section;
     bool ok;
    };

   ActResult curAct();

   bool changeCur(ulen ind);

   bool changeOpen(ulen ind);

   void apply(ulen count,FuncArgType<ulen,StrLen,StrLen,bool,bool,bool> func) const // ind title path section open cur
    {
     if( !count ) return;

     auto r=getRange();

     for(ulen ind : IndLim(r.len) )
       {
        auto &obj=r[ind];

        if( obj.isVisible() )
          {
           func(off+ind,Range(obj.title),Range(obj.path),obj.section,obj.open, off+ind==cur );

           if( !--count ) return;
          }
       }
    }

   void apply(ulen count,FuncType<bool,ulen,StrLen,StrLen,bool,bool,bool> func) const // ind title path section open cur
    {
     if( !count ) return;

     auto r=getRange();

     for(ulen ind : IndLim(r.len) )
       {
        auto &obj=r[ind];

        if( obj.isVisible() )
          {
           if( !func(off+ind,Range(obj.title),Range(obj.path),obj.section,obj.open, off+ind==cur ) ) return;

           if( !--count ) return;
          }
       }
    }

   void openAll();

   void closeAll();

   bool canMoveUp() const;

   bool canMoveDown() const;

   bool moveUp();

   bool moveDown();

   bool moveUp(ulen count);

   bool moveDown(ulen count);

   bool del();

   void insItem(const String &title,const String &path);

   void insSection(const String &title);

   // load/save

   bool load(StrLen file_name);

   void save(StrLen file_name) const;

   bool load(StrLen key,StrLen file) noexcept;

   void save(StrLen key,StrLen file) const noexcept;
 };

} // namespace Video
} // namespace CCore

#endif


