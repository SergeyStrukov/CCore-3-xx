/* ConfigStore.h */
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

#ifndef CCore_inc_video_ConfigStore_h
#define CCore_inc_video_ConfigStore_h

#include <CCore/inc/video/Color.h>
#include <CCore/inc/video/MPoint.h>
#include <CCore/inc/video/FontParam.h>
#include <CCore/inc/video/RefVal.h>
#include <CCore/inc/video/PrintDDL.h>

#include <CCore/inc/TypeSwitch.h>
#include <CCore/inc/CompactMap.h>
#include <CCore/inc/StrKey.h>

namespace CCore {
namespace Video {

/* GuardItemTypeMismatch() */

void GuardItemTypeMismatch(const char *name);

/* Gamma <-> Int */

inline int GammaToInt(double g) { return int(g*1024+0.5); }

inline double IntToGamma(int g) { return g/1024.; }

/* classes */

class ConfigItem;

class ConfigMap;

/* type ConfigTypeList */

using ConfigTypeList = Meta::CaseList<
                                       Meta::Case<int,1,unsigned> ,
                                       Meta::Case<int,2,Coord> ,
                                       Meta::Case<int,3,Fraction> ,
                                       Meta::Case<int,4,VColor> ,
                                       Meta::Case<int,5,Clr> ,
                                       Meta::Case<int,6,Point> ,
                                       Meta::Case<int,7,DefString> ,
                                       Meta::Case<int,8,FontParam> ,
                                       Meta::Case<int,9,bool> ,
                                       Meta::Case<int,10,Ratio>
                                     > ;

/* concept ConfigType<T> */

template <class T>
concept bool ConfigType = OneOfTypes<T,unsigned,Coord,Fraction,VColor,Clr,Point,DefString,FontParam,bool,Ratio> ;

/* class ConfigItem */

class ConfigItem : NoCopy
 {
   static constexpr ulen Len = Meta::CaseListMaxSizeof<ConfigTypeList> ;

   InitStorage<Len> storage;
   int id = 0 ;

  private:

   struct DestroyCtx;

   static void Destroy(int id,Place<void> place);

   struct DDLTypeNameCtx;

   template <class P>
   struct PrintCtx
    {
     P &out;
     Place<const void> place;

     using RetType = void ;

     template <class T>
     void print(const T &obj)
      {
       Putobj(out,obj);
      }

     void print(VColor obj)
      {
       Printf(out,"#8.hi;",obj);
      }

     void print(Point obj)
      {
       Printf(out,"{ #; , #; }",obj.x,obj.y);
      }

     void print(const DefString &obj)
      {
       Putobj(out,DDLString(obj.str()));
      }

     void print(const FontParam &obj)
      {
       Printf(out,"{ Font###; , #; , ",obj.engine_type,DDLPrintableString(obj.file_name));

       switch( obj.size_type )
         {
          case FontParam::SizeXY    : Printf(out,"Font###; , #; , 0 , ",obj.size_type,obj.set_size.size_xy); break;
          case FontParam::SizePoint : Printf(out,"Font###; , #; , #; , ",obj.size_type,obj.set_size.size.x,obj.set_size.size.y); break;
          case FontParam::SizeIndex : Printf(out,"Font###; , #; , 0 , ",obj.size_type,obj.set_size.index); break;
         }

       Printf(out," { Font##Config###; , Font##Config###; , #; , #; , #; } }",
                      obj.cfg.fht,
                      obj.cfg.fsm,
                      DDLBool(obj.cfg.use_kerning),
                      obj.cfg.strength,
                      GammaToInt(obj.cfg.gamma_order));
      }

     void print(bool obj)
      {
       Printf(out,"#;",DDLBool(obj));
      }

     void print(Ratio obj)
      {
       Printf(out,"{ #; }",obj.value);
      }

     template <class T>
     RetType call()
      {
       print(*(const T *)place);
      }

     RetType defcall(int)
      {
       // do nothing
      }
    };

  public:

   ConfigItem() noexcept {}

   ~ConfigItem() { if( id ) Destroy(id,storage.getPlace()); }

   StrLen getDDLTypeName() const;

   template <ConfigType T>
   bool sync(T &ret)
    {
     if( !id )
       {
        new(storage.getPlace()) T((const T &)ret);

        id=Meta::CaseVal<ConfigTypeList,T>;

        return true;
       }
     else
       {
        if( id!=Meta::CaseVal<ConfigTypeList,T> ) GuardItemTypeMismatch("sync");

        ret=*(T *)storage.getPlace();

        return false;
       }
    }

   template <ConfigType T>
   void update(const T &value)
    {
     if( !id )
       {
        new(storage.getPlace()) T(value);

        id=Meta::CaseVal<ConfigTypeList,T>;
       }
     else
       {
        if( id!=Meta::CaseVal<ConfigTypeList,T> ) GuardItemTypeMismatch("update");

        *(T *)storage.getPlace()=value;
       }
    }

   // print object

   template <PrinterType P>
   void print(P &out) const // DDL print
    {
     Meta::TypeSwitch<ConfigTypeList>::Switch(id,PrintCtx<P>{out,storage.getPlace()});
    }
 };

/* class ConfigMap */

class ConfigMap : NoCopy
 {
   bool modified = false ;

   CompactRBTreeMap<StringKey,ConfigItem,StrKey> map;

  private:

   ConfigItem & find_or_add(StrLen name);

   static StrLen Pretext();

   template <class Func> struct TypeFilter;

   template <class Ptr,class Func>
   static void Filter(Ptr ptr,Func func);

   struct AddItem;

   void add(StrLen name,const ConfigType &value);

   void add_uint(StrLen name,unsigned value);

   void add_text(StrLen name,StrLen value);

   void add_Coord(StrLen name,Coord value);

   void add_MCoord(StrLen name,MCoord value);

   void add_VColor(StrLen name,uint32 value);

   void add_Clr(StrLen name,uint8 value);

   void add_Point(StrLen name,Point value);

   void add_Font(StrLen name,const FontParam &value);

   void add_Bool(StrLen name,uint8 value);

   void add_Ratio(StrLen name,Ratio value);

  public:

   // constructors

   ConfigMap() noexcept;

   ~ConfigMap();

   // methods

   bool isModified() const { return modified; }

   void sync(StrLen name,ConfigType &ret)
    {
     ConfigItem &item=find_or_add(name);

     if( item.sync(ret) ) modified=true;
    }

   void update(StrLen name,const ConfigType &value)
    {
     ConfigItem &item=find_or_add(name);

     item.update(value);

     modified=true;
    }

   void sync(StrLen name,FontCouple &ret)
    {
     sync(name,ret.param);

     ret.create();
    }

   void update(StrLen name,const FontCouple &value)
    {
     update(name,value.param);
    }

   void saveDDL(StrLen file_name) const;

   void loadDDL(StrLen file_name);

   bool loadDDL_safe(StrLen file_name) noexcept;

   // object swap

   void objSwap(ConfigMap &obj)
    {
     Swap(modified,obj.modified);
     Swap(map,obj.map);
    }
 };

} // namespace Video
} // namespace CCore

#endif

