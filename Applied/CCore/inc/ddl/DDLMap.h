/* DDLMap.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_ddl_DDLMap_h
#define CCore_inc_ddl_DDLMap_h

#include <CCore/inc/ddl/DDLEngine.h>
#include <CCore/inc/ddl/DDLTypeDesc.h>
#include <CCore/inc/ddl/DDLMapTools.h>

namespace CCore {
namespace DDL {

/* functions */

void GuardMapStructNameDuplication();

/* classes */

class Map;

/* class Map */

class Map : NoCopy
 {
   static constexpr unsigned MaxLevel = 100 ;

   struct RecValue
    {
     ulen off;

     PtrLen<RecValue> elems;

     RecValue() noexcept : off(0) {}
    };

   struct RecConst : RecValue
    {
     TypeNode *type;
     ulen size_of;

     RBTreeLink<RecConst,NameKey> link;

     RecConst() noexcept : type(0),size_of(0) {}

     void set(TypeNode *type_,ulen size_of_)
      {
       type=type_;
       size_of=size_of_;
      }
    };

   struct SizeInfo
    {
     ulen size_of;
     unsigned flags;

     SizeInfo() : size_of(0),flags(0) {}

     SizeInfo(ulen size_of_,unsigned flags_) : size_of(size_of_),flags(flags_) {}

     void set(ulen size_of_,TypeTag tag)
      {
       size_of=size_of_;
       flags=1u<<tag;
      }

     void mul(ulen count) { size_of=MapMulLen(size_of,count); }

     void setInfo(const SizeInfo &obj) { *this=obj; }
    };

   struct RecStruct : SizeInfo
    {
     StructNode *struct_node;

     RBTreeLink<RecStruct,NameKey> link;

     RecStruct() noexcept : struct_node(0) {}

     bool operator ! () const { return !struct_node; }

     void set(const SizeInfo &obj,StructNode *struct_node_)
      {
       setInfo(obj);

       struct_node=struct_node_;
      }
    };

  private:

   template <ulen N> class AlignMulTable;

   template <class T>
   static ulen AlignAdd(ulen a);

   static ulen AlignOf(unsigned flags);

   static ulen AlignFor(ulen off,unsigned flags);

  private:

   EvalResult *eval;
   BodyNode *body;

   DynArray<RecConst> const_buf;
   Collector<RecValue> rec_buf;
   DynArray<RecStruct> struct_buf;

   using ConstAlgo = RBTreeLink<RecConst,NameKey>::Algo<&RecConst::link> ;
   using StructAlgo = RBTreeLink<RecStruct,NameKey>::Algo<&RecStruct::link> ;

   ConstAlgo::Root const_map;
   StructAlgo::Root struct_map;

   ulen total;
   Place<void> base;
   unsigned level;

  private:

   void resetLevel() { level=0; }

   void incLevel() { if( level>=MaxLevel ) GuardMapTooDeep(); level++; }

   void decLevel() { level--; }

  private:

   struct PrepareFunc;

   void prepare(TypeNode *type,const Value &value,RecValue &rec);

   void prepare();

  private:

   SizeInfo layout(StructNode *struct_node);

   struct SizeOfFunc;

   SizeInfo sizeOf(TypeNode *type);

   void sizeOf();

  private:

   ulen reserve(ulen len);

   ulen reserve(ulen len,ulen count);

   void reserve(RecConst &rec) { rec.off=reserve(rec.size_of); }

   struct PlaceFunc;

   void place(TypeNode *type,const Value &value,const RecValue &rec);

   void place();

  private:

   const RecValue & getRec(PtrNode *node);

   DataPtr mapPtr(Ptr ptr);

   TypedDataPtr mapTypedPtr(Ptr ptr,TypeList *type_list);

   struct MapFunc;

   void map(TypeNode *type,const Value &value,const RecValue &rec);

  private:

   static void SetDesc(const TypeDesc_struct_base &desc,RecStruct *rec);

   struct MatchFunc;

   bool match(TypeNode *type,const TypeDesc &desc);

   bool match(StructNode *struct_node,const TypeDesc &desc);

  public:

   explicit Map(EngineResult result);

   ~Map();

   ulen getLen() const { return total; }

   void operator () (void *mem);

   bool findStruct(StrLen name,const TypeDesc &desc);

   void * findConst(StrLen name,const TypeDesc &desc);
 };

} // namespace DDL
} // namespace CCore

#endif


