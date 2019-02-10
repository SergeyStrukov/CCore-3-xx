/* Info.cpp */
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

#include <CCore/inc/video/Info.h>

#include <CCore/inc/CharProp.h>

namespace CCore {
namespace Video {

namespace Private_Info {

class DefInfo : public InfoBase
 {
  public:

   DefInfo() {}

   virtual ~DefInfo() {}

   // AbstractInfo

   virtual ulen getLineCount() const { return 0; }

   virtual StrLen getLine(ulen) const { return Empty; }
 };

DefInfo Object CCORE_INITPRI_3 ;

class DefComboInfo : public ComboInfoBase
 {
  public:

   DefComboInfo() {}

   virtual ~DefComboInfo() {}

   // AbstractComboInfo

   virtual ulen getLineCount() const { return 0; }

   virtual ComboInfoItem getLine(ulen) const { return Empty; }
 };

DefComboInfo ComboObject CCORE_INITPRI_3 ;

} // namespace Private_Info

using namespace Private_Info;

/* class Info */

Info::Info() noexcept
 : ptr(&Object)
 {
  ptr->incRef();
 }

/* class InfoFromString::StringSet */

class InfoFromString::StringSet : public InfoBase
 {
   String str;
   DynArray<StrLen> list;

  public:

   explicit StringSet(const String &str_)
    : str(str_),
      list(DoReserve,100)
    {
     StrLen total=Range(str);

     while( +total )
       {
        StrLen line=CutLine(total);

        list.append_fill(line);
       }

     list.shrink_extra();
    }

   virtual ~StringSet()
    {
    }

   // AbstractInfo

   virtual ulen getLineCount() const
    {
     return list.getLen();
    }

   virtual StrLen getLine(ulen index) const
    {
     return list.at(index);
    }
 };

/* class InfoFromString */

InfoFromString::InfoFromString(const String &str)
 : Info(new StringSet(str))
 {
 }

InfoFromString::~InfoFromString()
 {
 }

/* class InfoBuilder::PoolInfo */

class InfoBuilder::PoolInfo : public Info
 {
   class Base : public InfoBase
    {
      ElementPool pool;
      DynArray<StrLen> list;

     public:

      Base(ElementPool &pool_,DynArray<StrLen> &list_)
       {
        Swap(pool,pool_);
        Swap(list,list_);

        pool.shrink_extra();
        list.shrink_extra();
       }

      virtual ~Base()
       {
       }

      // AbstractInfo

      virtual ulen getLineCount() const
       {
        return list.getLen();
       }

      virtual StrLen getLine(ulen index) const
       {
        return list.at(index);
       }
    };

  public:

   PoolInfo(ElementPool &pool,DynArray<StrLen> &list)
    : Info(new Base(pool,list))
    {
    }

   ~PoolInfo()
    {
    }
 };

/* class InfoBuilder */

InfoBuilder::InfoBuilder()
 {
 }

InfoBuilder::~InfoBuilder()
 {
 }

void InfoBuilder::add(StrLen line)
 {
  list.append_copy(pool.dup(line));
 }

Info InfoBuilder::complete()
 {
  return PoolInfo(pool,list);
 }

/* class ComboInfo */

ComboInfo::ComboInfo() noexcept
 : ptr(&ComboObject)
 {
  ptr->incRef();
 }

/* class ComboInfoBuilder::PoolInfo */

class ComboInfoBuilder::PoolInfo : public ComboInfo
 {
   class Base : public ComboInfoBase
    {
      ElementPool pool;
      DynArray<ComboInfoItem> list;

     public:

      Base(ElementPool &pool_,DynArray<ComboInfoItem> &list_)
       {
        Swap(pool,pool_);
        Swap(list,list_);

        pool.shrink_extra();
        list.shrink_extra();
       }

      virtual ~Base()
       {
       }

      // AbstractComboInfo

      virtual ulen getLineCount() const
       {
        return list.getLen();
       }

      virtual ComboInfoItem getLine(ulen index) const
       {
        return list.at(index);
       }
    };

  public:

   PoolInfo(ElementPool &pool,DynArray<ComboInfoItem> &list)
    : ComboInfo(new Base(pool,list))
    {
    }

   ~PoolInfo()
    {
    }
 };

/* class ComboInfoBuilder */

ComboInfoBuilder::ComboInfoBuilder()
 {
 }

ComboInfoBuilder::~ComboInfoBuilder()
 {
 }

void ComboInfoBuilder::add(ComboInfoType type,StrLen line)
 {
  list.append_fill(type,pool.dup(line));
 }

ComboInfo ComboInfoBuilder::complete()
 {
  return PoolInfo(pool,list);
 }

} // namespace Video
} // namespace CCore


