/* ConfigBinder.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
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

#ifndef CCore_inc_video_ConfigBinder_h
#define CCore_inc_video_ConfigBinder_h

#include <CCore/inc/video/ConfigStore.h>

namespace CCore {
namespace Video {

/* classes */

struct ConfigItemBind;

struct ConfigItemHost;

struct HomeSyncBase;

template <class Bag,class ... TT> class ConfigBinder;

/* struct ConfigItemBind */

struct ConfigItemBind
 {
  virtual void group(DefString name)=0;

  virtual void space()=0;

  virtual void item(DefString name,unsigned &var)=0;

  virtual void item(DefString name,Coord &var)=0;

  virtual void item(DefString name,MCoord &var)=0;

  virtual void item(DefString name,VColor &var)=0;

  virtual void item(DefString name,Clr &var)=0;

  virtual void item(DefString name,Point &var)=0;

  virtual void item(DefString name,DefString &var)=0;

  virtual void item(DefString name,FontCouple &var)=0;

  virtual void item(DefString name,bool &var)=0;

  virtual void item(DefString name,Ratio &var)=0;
 };

/* struct ConfigItemHost */

struct ConfigItemHost
 {
  virtual void bind(ConfigItemBind &binder)=0;
 };

/* struct HomeSyncBase */

struct HomeSyncBase
 {
  virtual void syncMap(ConfigMap &map)=0;

  virtual void updateMap(ConfigMap &map) const = 0;

  bool syncHome(StrLen home_dir,StrLen cfg_file) noexcept; // "/dir" "/file"

  void updateHome(StrLen home_dir,StrLen cfg_file) noexcept; // "/dir" "/file"
 };

/* class ConfigBinder<Bag,TT> */

template <class Bag,class ... TT>
class ConfigBinder : NoCopyBase<Bag> , public HomeSyncBase
 {
   template <class T>
   struct Item
    {
     T obj;
    };

   struct Pack : Item<TT>...
    {
    };

   Pack pack;

  private:

   template <class T>
   void bind()
    {
     BindBagProxy( static_cast<Item<T> &>(pack).obj ,get(),getSmartConfig());
    }

  public:

   // constructors

   ConfigBinder() noexcept
    {
     ( bind<TT>() , ... );
    }

   ~ConfigBinder() {}

   // methods

   const Bag & get() const { return *this; }

   Bag & ref() { return *this; }

   template <OneOfTypes<TT...> T>
   const T & getConfig() const
    {
     return static_cast<const Item<T> &>(pack).obj;
    }

   virtual void syncMap(ConfigMap &map)
    {
     Bag::Members(this, [&map] (StrLen name,AnyType &obj) { map.sync(name,obj); } );

     Bag::createFonts();
    }

   virtual void updateMap(ConfigMap &map) const
    {
     Bag::Members(this, [&map] (StrLen name,AnyType &obj) { map.update(name,obj); } );
    }

   // getSmartConfig()

   class Proxy
    {
      const ConfigBinder *obj;

     public:

      Proxy(const ConfigBinder *obj_) : obj(obj_) {}

      template <OneOfTypes<TT...> T>
      operator const T & () const { return obj->template getConfig<T>(); }
    };

   Proxy getSmartConfig() const { return this; }
 };

} // namespace Video
} // namespace CCore

#endif

