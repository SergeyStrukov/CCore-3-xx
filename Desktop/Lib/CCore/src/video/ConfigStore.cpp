/* ConfigStore.cpp */
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

#include <CCore/inc/video/ConfigStore.h>

#include <CCore/inc/FileName.h>
#include <CCore/inc/FileToMem.h>

#include <CCore/inc/Print.h>

#include <CCore/inc/ddl/DDLEngine.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Video {

/* GuardItemTypeMismatch() */

void GuardItemTypeMismatch(const char *name)
 {
  Printf(Exception,"CCore::Video::ConfigItem::#;<...>() : item type mismatch",name);
 }

/* class ConfigItem */

struct ConfigItem::DestroyCtx
 {
  Place<void> place;

  using RetType = void ;

  template <class T>
  RetType call()
   {
    T *obj=place;

    obj->~T();
   }

  RetType defcall(int)
   {
    // do nothing
   }
 };

void ConfigItem::Destroy(int id,Place<void> place)
 {
  Meta::TypeSwitch<ConfigTypeList>::Switch(id,DestroyCtx{place});
 }

struct ConfigItem::DDLTypeNameCtx
 {
  using RetType = StrLen ;

  template <class T>
  RetType call();

  RetType defcall(int)
   {
    return "???";
   }
 };

template <>
auto ConfigItem::DDLTypeNameCtx::call<unsigned>() -> RetType { return "uint"; }

template <>
auto ConfigItem::DDLTypeNameCtx::call<Coord>() -> RetType { return "Coord"; }

template <>
auto ConfigItem::DDLTypeNameCtx::call<MCoord>() -> RetType { return "MCoord"; }

template <>
auto ConfigItem::DDLTypeNameCtx::call<VColor>() -> RetType { return "VColor"; }

template <>
auto ConfigItem::DDLTypeNameCtx::call<Clr>() -> RetType { return "Clr"; }

template <>
auto ConfigItem::DDLTypeNameCtx::call<Point>() -> RetType { return "Point"; }

template <>
auto ConfigItem::DDLTypeNameCtx::call<DefString>() -> RetType { return "text"; }

template <>
auto ConfigItem::DDLTypeNameCtx::call<FontParam>() -> RetType { return "Font"; }

template <>
auto ConfigItem::DDLTypeNameCtx::call<bool>() -> RetType { return "Bool"; }

template <>
auto ConfigItem::DDLTypeNameCtx::call<Ratio>() -> RetType { return "Ratio"; }

StrLen ConfigItem::getDDLTypeName() const
 {
  return Meta::TypeSwitch<ConfigTypeList>::Switch(id,DDLTypeNameCtx{});
 }

/* class ConfigMap */

ConfigItem & ConfigMap::find_or_add(StrLen name)
 {
  StrKey key(name);
  auto result=map.find_or_add(key);

  return *result.obj;
 }

StrLen ConfigMap::Pretext()
 {
  return
"type Bool = uint8 ;"

"Bool True = 1 ;"

"Bool False = 0 ;"

"type Coord = sint16 ;"

"type MCoord = sint32 ; "

"type VColor = uint32 ;"

"type Clr = uint8 ;"

"struct Point"
" {"
"  Coord x;"
"  Coord y;"
" };"

"struct Ratio"
" {"
"  sint32 ratio;"
" }; "

"struct Font"
" {"
"  type EngineType = int ;"

"  const EngineType EngineDefault  = 0 ;"
"  const EngineType EngineFreeType = 1 ;"

"  EngineType engine_type;"

"  text file_name;"

"  type SizeType = int ;"

"  const SizeType SizeXY    = 0 ;"
"  const SizeType SizePoint = 1 ;"
"  const SizeType SizeIndex = 2 ;"

"  SizeType size_type;"
"  int dx;"
"  int dy;"

"  struct Config"
"   {"
"    type FontHintType = int ;"

"    const FontHintType FontHintNone   = 0 ;"
"    const FontHintType FontHintNative = 1 ;"
"    const FontHintType FontHintAuto   = 2 ;"

"    FontHintType fht;"

"    type FontSmoothType = int ;"

"    const FontSmoothType FontSmoothNone    = 0 ;"
"    const FontSmoothType FontSmooth        = 1 ;"
"    const FontSmoothType FontSmoothLCD_RGB = 2 ;"
"    const FontSmoothType FontSmoothLCD_BGR = 3 ;"

"    FontSmoothType fsm;"

"    Bool use_kerning;"
"    int strength;"
"    int gamma_order;"
"   };"

"  Config cfg;"
" };"_c;
 }

template <class Func>
struct ConfigMap::TypeFilter
 {
  Func func;

  void operator () (DDL::TypeNode::Base *ptr)
   {
    switch( ptr->type )
      {
       case DDL::TypeNode::Base::Type_uint : func.do_uint(); break;

       case DDL::TypeNode::Base::Type_text : func.do_text(); break;
      }
   }

  void operator () (DDL::TypeNode::Ref *ptr)
   {
    struct Dispatch
     {
      Func &func;

      void operator () (DDL::AliasNode *ptr)
       {
        if( ptr->depth==0 )
          {
           StrLen name=ptr->name.getStr();

           if( name.equal("Coord"_c) )
             {
              func.do_Coord();
             }
           else if( name.equal("MCoord"_c) )
             {
              func.do_MCoord();
             }
           else if( name.equal("VColor"_c) )
             {
              func.do_VColor();
             }
           else if( name.equal("Clr"_c) )
             {
              func.do_Clr();
             }
           else if( name.equal("Bool"_c) )
             {
              func.do_Bool();
             }
          }
       }

      void operator () (DDL::StructNode *ptr)
       {
        if( ptr->depth==0 )
          {
           StrLen name=ptr->name.getStr();

           if( name.equal("Font"_c) )
             {
              func.do_Font();
             }
           else if( name.equal("Point"_c) )
             {
              func.do_Point();
             }
           else if( name.equal("Ratio"_c) )
             {
              func.do_Ratio();
             }
          }
       }
     };

    ptr->ptr.apply(Dispatch{func});
   }

  template <class T>
  void operator () (T *)
   {
    // do nothing
   }
 };

template <class Ptr,class Func>
void ConfigMap::Filter(Ptr ptr,Func func)
 {
  ptr.apply(TypeFilter<Func>{func});
 }

struct ConfigMap::AddItem
 {
  ConfigMap *obj;
  StrLen name;
  DDL::Value value;

  // Get... ()

  static int Get_int(DDL::Value value) { return value.get<DDL::imp_sint>().value; }

  static bool Get_Bool(DDL::Value value) { return value.get<DDL::imp_uint8>().value; }

  static StrLen Get_text(DDL::Value value) { return value.get<DDL::Text>().str; }

  static Coord Get_Coord(DDL::Value value) { return value.get<DDL::imp_sint16>().value; }

  // get...()

  unsigned get_uint() const { return value.get<DDL::imp_uint>().value; }

  StrLen get_text() const { return Get_text(value); }

  Coord get_Coord() const { return Get_Coord(value); }

  MCoord get_MCoord() const { return value.get<DDL::imp_sint32>().value; }

  uint32 get_VColor() const { return value.get<DDL::imp_uint32>().value; }

  uint8 get_Clr() const { return value.get<DDL::imp_uint8>().value; }

  Point get_Point() const
   {
    auto r=value.get<DDL::Block>().data;

    return Point(Get_Coord(r[0]),Get_Coord(r[1]));
   }

  FontParam get_Font() const
   {
    auto r=value.get<DDL::Block>().data;

    FontParam param;

    param.engine_type=FontParam::EngineType(Get_int(r[0]));

    param.file_name=Get_text(r[1]);

    param.size_type=FontParam::SizeType(Get_int(r[2]));

    int x=Get_int(r[3]);
    int y=Get_int(r[4]);

    switch( param.size_type )
      {
       case FontParam::SizeXY : param.set_size.size_xy=Coord(x); break;

       case FontParam::SizePoint : param.set_size.size=Point(Coord(x),Coord(y)); break;

       case FontParam::SizeIndex : param.set_size.index=ulen(x); break;
      }

    auto cfg=r[5].get<DDL::Block>().data;

    param.cfg.fht=FontHintType(Get_int(cfg[0]));
    param.cfg.fsm=FontSmoothType(Get_int(cfg[1]));
    param.cfg.use_kerning=Get_Bool(cfg[2]);
    param.cfg.strength=Get_int(cfg[3]);
    param.cfg.gamma_order=IntToGamma(Get_int(cfg[4]));

    return param;
   }

  uint8 get_Bool() const { return value.get<DDL::imp_uint8>().value; }

  Ratio get_Ratio() const
   {
    auto r=value.get<DDL::Block>().data;

    return Ratio(r[0].get<DDL::imp_sint32>().value);
   }

  // do...()

  void do_uint() { obj->add_uint(name,get_uint()); }

  void do_text() { obj->add_text(name,get_text()); }

  void do_Coord() { obj->add_Coord(name,get_Coord()); }

  void do_MCoord() { obj->add_MCoord(name,get_MCoord()); }

  void do_VColor() { obj->add_VColor(name,get_VColor()); }

  void do_Clr() { obj->add_Clr(name,get_Clr()); }

  void do_Point() { obj->add_Point(name,get_Point()); }

  void do_Font() { obj->add_Font(name,get_Font()); }

  void do_Bool() { obj->add_Bool(name,get_Bool()); }

  void do_Ratio() { obj->add_Ratio(name,get_Ratio()); }
 };

void ConfigMap::add(StrLen name,const ConfigType &value)
 {
  StrKey key(name);
  auto result=map.find_or_add(key);

  if( !result.new_flag )
    {
     Printf(Exception,"CCore::Value::ConfigMap::add(#.q;,...) : name duplication",name);
    }

  result.obj->update(value);
 }

void ConfigMap::add_uint(StrLen name,unsigned value) { add(name,value); }

void ConfigMap::add_text(StrLen name,StrLen value) { add(name,DefString(value)); }

void ConfigMap::add_Coord(StrLen name,Coord value) { add(name,value); }

void ConfigMap::add_MCoord(StrLen name,MCoord value) { add(name,value); }

void ConfigMap::add_VColor(StrLen name,uint32 value) { add(name,VColor(value)); }

void ConfigMap::add_Clr(StrLen name,uint8 value) { add(name,Clr(value)); }

void ConfigMap::add_Point(StrLen name,Point value) { add(name,value); }

void ConfigMap::add_Font(StrLen name,const FontParam &value) { add(name,value); }

void ConfigMap::add_Bool(StrLen name,uint8 value)
 {
  if( !name.equal("True"_c) && !name.equal("False"_c) ) add(name,bool(value));
 }

void ConfigMap::add_Ratio(StrLen name,Ratio value) { add(name,value); }

ConfigMap::ConfigMap() noexcept
 {
 }

ConfigMap::~ConfigMap()
 {
 }

void ConfigMap::saveDDL(StrLen file_name) const
 {
  PrintFile out(file_name);

  Printf(out,"//include <ConfigTypes.ddl>\n\n");

  map.applyIncr( [&out] (const StringKey &key,const ConfigItem &item)
                        {
                         Printf(out,"#; #; = #; ;\n",item.getDDLTypeName(),key.str,item);

                        } );
 }

void ConfigMap::loadDDL(StrLen file_name)
 {
  modified=false;
  map.erase();

  SimpleArray<char> temp(4_KByte);
  PrintBuf eout(Range(temp));
  DDL::FileEngine<FileName,FileToMem> engine(eout);

  auto result=engine.process(file_name,Pretext());

  if( !result )
    {
     Printf(Exception,"CCore::Video::ConfigMap::loadDDL(#.q;) : input file processing error\n#;",file_name,eout.close());
    }
  else
    {
     for(const auto &res : result.eval->const_table )
       {
        auto *node=res.node;

        if( node->depth ) continue;

        auto *type=res.type;

        StrLen name=node->name.getStr();

        Filter(type->ptr,AddItem{this,name,res.value});
       }
    }
 }

bool ConfigMap::loadDDL_safe(StrLen file_name) noexcept
 {
  try
    {
     ConfigMap temp;

     temp.loadDDL(file_name);

     Swap(*this,temp);

     return true;
    }
  catch(...)
    {
     return false;
    }
 }

} // namespace Video
} // namespace CCore

