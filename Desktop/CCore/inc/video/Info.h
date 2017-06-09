/* Info.h */
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

#ifndef CCore_inc_video_Info_h
#define CCore_inc_video_Info_h

#include <CCore/inc/RefObjectBase.h>

#include <CCore/inc/String.h>
#include <CCore/inc/ElementPool.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>

#include <CCore/inc/video/RefVal.h>

namespace CCore {
namespace Video {

/* consts */

enum ComboInfoType
 {
  ComboInfoText,
  ComboInfoSeparator,
  ComboInfoTitle
 };

/* classes */

struct AbstractInfo;

class Info;

class InfoFromString;

class InfoBuilder;

struct ComboInfoItem;

struct AbstractComboInfo;

class ComboInfo;

class ComboInfoBuilder;

/* struct AbstractInfo */

struct AbstractInfo
 {
  virtual ulen getLineCount() const =0;

  virtual StrLen getLine(ulen index) const =0;
 };

/* type InfoBase */

using InfoBase = RefObjectBase<AbstractInfo> ;

/* class Info */

class Info
 {
   RefPtr<InfoBase> ptr;

  protected:

   explicit Info(InfoBase *info) : ptr(info) {}

   template <class T>
   T * castPtr() const { return dynamic_cast<T *>(ptr.getPtr()); }

  public:

   Info() noexcept;

   ~Info() {}

   const AbstractInfo * getPtr() const { return ptr.getPtr(); }

   const AbstractInfo * operator -> () const { return ptr.getPtr(); }
 };

/* class InfoFromString */

class InfoFromString : public Info
 {
   class StringSet : public InfoBase
    {
      DefString str;
      DynArray<StrLen> list;

     public:

      explicit StringSet(DefString str);

      virtual ~StringSet();

      // AbstractInfo

      virtual ulen getLineCount() const;

      virtual StrLen getLine(ulen index) const;
    };

  public:

   explicit InfoFromString(DefString str);

   ~InfoFromString();
 };

/* class InfoBuilder */

class InfoBuilder : NoCopy
 {
   ElementPool pool;
   DynArray<StrLen> list;

   class PoolInfo;

  public:

   InfoBuilder();

   ~InfoBuilder();

   void add(StrLen line);

   void sort(ObjLessFuncType<StrLen> less) { IncrSort(Range(list),less); }

   Info complete();
 };

/* struct ComboInfoItem */

struct ComboInfoItem
 {
  ComboInfoType type;
  StrLen text;

  ComboInfoItem() noexcept : type(ComboInfoText) {}

  ComboInfoItem(NothingType) : ComboInfoItem() {}

  ComboInfoItem(ComboInfoType type_,StrLen text_) : type(type_),text(text_) {}
 };

/* struct AbstractComboInfo */

struct AbstractComboInfo
 {
  virtual ulen getLineCount() const =0;

  virtual ComboInfoItem getLine(ulen index) const =0;
 };

/* type ComboInfoBase */

using ComboInfoBase = RefObjectBase<AbstractComboInfo> ;

/* class ComboInfo */

class ComboInfo
 {
   RefPtr<ComboInfoBase> ptr;

  protected:

   explicit ComboInfo(ComboInfoBase *info) : ptr(info) {}

   template <class T>
   T * castPtr() const { return dynamic_cast<T *>(ptr.getPtr()); }

  public:

   ComboInfo() noexcept;

   ~ComboInfo() {}

   const AbstractComboInfo * getPtr() const { return ptr.getPtr(); }

   const AbstractComboInfo * operator -> () const { return ptr.getPtr(); }
 };

/* class ComboInfoBuilder */

class ComboInfoBuilder : NoCopy
 {
   ElementPool pool;
   DynArray<ComboInfoItem> list;

   class PoolInfo;

  private:

   static void SortGroups(PtrLen<ComboInfoItem> r,ObjLessFuncType<StrLen> less)
    {
     while( +r )
       {
        for(; +r && r->type!=ComboInfoText ;++r);

        if( !r ) break;

        auto temp=r;

        for(; +r && r->type==ComboInfoText ;++r);

        IncrSort(temp.prefix(r), [less] (ComboInfoItem a,ComboInfoItem b) { return less(a.text,b.text); } );
       }
    }

  public:

   ComboInfoBuilder();

   ~ComboInfoBuilder();

   // add...()

   void add(ComboInfoType type,StrLen line);

   void add(StrLen line) { add(ComboInfoText,line); }

   void addTitle(StrLen line) { add(ComboInfoTitle,line); }

   void addSeparator() { add(ComboInfoSeparator,Empty); }

   // sort...()

   void sortGroups(ObjLessFuncType<StrLen> less)
    {
     SortGroups(Range(list),less);
    }

   // complete()

   ComboInfo complete();
 };

} // namespace Video
} // namespace CCore

#endif


