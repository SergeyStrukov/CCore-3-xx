/* DDLMapTools.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/inc/ddl/DDLMapTools.h>

#include <CCore/inc/Exception.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/Crc.h>

namespace CCore {
namespace DDL {

/* functions */

void GuardMapTooDeep()
 {
  Printf(Exception,"CCore::DDL::(Typed)Map : too deep");
 }

void GuardMapNameDuplication()
 {
  Printf(Exception,"CCore::DDL::(Typed)Map : const name duplication");
 }

void GuardMapLenOverflow()
 {
  Printf(Exception,"CCore::DDL::(Typed)Map : len overflow");
 }

/* class TypeComparer */

struct TypeComparer::CmpRet
 {
  CmpResult result;

  CmpRet() : result(CmpEqual) {}

  CmpRet(unsigned a,unsigned b) : result(Cmp(a,b)) {}

  CmpRet(CmpResult result_) : result(result_) {}
 };

struct TypeComparer::CmpFunc
 {
  TypeComparer cmp;

  CmpFunc(EvalResult *eval,unsigned level) : cmp(eval,level) {}

  CmpRet operator () (TypeNode::Base *a,TypeNode::Base *b)
   {
    return Cmp(a->type,b->type);
   }

  CmpRet operator () (TypeNode::Ptr *a,TypeNode::Ptr *b)
   {
    return cmp(a->type_node,b->type_node);
   }

  struct Rec
   {
    TypeNode *type;
    unsigned flag;

    void set(TypeNode *type_,unsigned flag_)
     {
      type=type_;
      flag=flag_;
     }
   };

  static Rec * Fill(Rec *out,TypeList *type_list,unsigned flag)
   {
    for(TypeListNode &node : *type_list )
      {
       out->set(node.type_node,flag);

       ++out;
      }

    return out;
   }

  CmpResult finish(PtrLen<Rec> range)
   {
    while( +range )
      {
       TypeNode *type=range->type;
       unsigned flags=range->flag;

       ++range;

       for(; +range && !cmp(type,range->type) ;++range) flags|=range->flag;

       switch( flags )
         {
          case 1 : return CmpGreater;
          case 2 : return CmpLess;
         }
      }

    return CmpEqual;
   }

  CmpRet operator () (TypeNode::PolyPtr *a,TypeNode::PolyPtr *b)
   {
    ulen count=LenAdd(a->type_list->count,b->type_list->count);

    TempArray<Rec,100> buf(count);

    auto range=Range(buf.getPtr(),count);

    Fill(Fill(range.ptr,a->type_list,1),b->type_list,2);

    IncrSort(range, [=] (const Rec &a,const Rec &b) { return cmp(a.type,b.type)<0; } );

    return finish(range);
   }

  CmpRet operator () (TypeNode::Array *a,TypeNode::Array *b)
   {
    return cmp(a->type_node,b->type_node);
   }

  CmpRet operator () (TypeNode::ArrayLen *a,TypeNode::ArrayLen *b)
   {
    if( CmpResult ret=cmp(a->type_node,b->type_node) ) return ret;

    return cmp(a->len_node,b->len_node);
   }

  CmpRet operator () (StructNode *a,StructNode *b)
   {
    return Cmp(a->index,b->index);
   }
 };

CmpResult TypeComparer::operator () (TypeNode *a,TypeNode *b) const
 {
  if( !level ) GuardMapTooDeep();

  return TypeAdapter::Binary<CmpRet>(a,b,CmpFunc(eval,level-1)).result;
 }

ulen TypeComparer::typeIndex(TypeNode *type,TypeList *type_list) const
 {
  ulen ret=0;

  for(TypeListNode &node : *type_list )
    {
     if( !(*this)(type,node.type_node) ) return type_list->count-ret;

     ret++;
    }

  return 0;
 }

/* class NameKey */

struct NameKey::Cur
 {
  PtrLenReverse<const char> name;
  ScopeNode *parent;
  char ch;

  Cur(PtrLenReverse<const char> name_,ScopeNode *parent_) : name(name_),parent(parent_),ch(0) {}

  bool next()
   {
    if( +name )
      {
       ch=*name;

       ++name;

       return true;
      }
    else
      {
       if( parent )
         {
          ch='#';

          name=RangeReverse(parent->name.getStr());
          parent=parent->parent;

          return true;
         }
       else
         {
          return false;
         }
      }
   }

  char operator * () const { return ch; }
 };

auto NameKey::getCur() const -> Cur { return Cur(RangeReverse(name),parent); }

void NameKey::setHash()
 {
  Crc32 crc;

  for(auto cur=getCur(); cur.next() ;) crc.add(*cur);

  hash=crc;
 }

CmpResult NameKey::objCmp(const NameKey &obj) const
 {
  if( CmpResult ret=Cmp(hash,obj.hash) ) return ret;

  Cur a=getCur();
  Cur b=obj.getCur();

  while( a.next() )
    {
     if( b.next() )
       {
        if( CmpResult ret=Cmp(*a,*b) ) return ret;
       }
     else
       {
        return CmpGreater;
       }
    }

  if( b.next() )
    {
     return CmpLess;
    }
  else
    {
     return CmpEqual;
    }
 }

} // namespace DDL
} // namespace CCore


