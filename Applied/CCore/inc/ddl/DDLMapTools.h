/* DDLMapTools.h */
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

#ifndef CCore_inc_ddl_DDLMapTools_h
#define CCore_inc_ddl_DDLMapTools_h

#include <CCore/inc/ddl/DDLEval.h>

namespace CCore {
namespace DDL {

/* functions */

void GuardMapTooDeep();

void GuardMapNameDuplication();

void GuardMapLenOverflow();

inline ulen MapAddLen(ulen a,ulen b)
 {
  ulen ret=a+b;

  if( ret<a ) GuardMapLenOverflow();

  return ret;
 }

inline ulen MapMulLen(ulen a,ulen b)
 {
  if( a && b>MaxULen/a ) GuardMapLenOverflow();

  return a*b;
 }

/* classes */

class TypeComparer;

class NameKey;

/* class TypeComparer */

class TypeComparer
 {
   EvalResult *eval;
   unsigned level;

   struct CmpRet;
   struct CmpFunc;

  public:

   TypeComparer(EvalResult *eval_,unsigned level_) : eval(eval_),level(level_) {}

   CmpResult operator () (TypeNode *a,TypeNode *b) const;

   CmpResult operator () (LenNode &a,LenNode &b) const { return Cmp(eval->getLen(a),eval->getLen(b)); }

   ulen typeIndex(TypeNode *type,TypeList *type_list) const;
 };

/* class NameKey */

class NameKey : CmpComparable<NameKey>
 {
   StrLen name;
   ScopeNode *parent;
   uint32 hash;

  private:

   struct Cur;

   Cur getCur() const;

   void setHash();

  public:

   // constructors

   NameKey() : parent(0),hash(0) {}

   template <class T>
   explicit NameKey(T *node) : name(node->name.getStr()),parent(node->parent) { setHash(); }

   explicit NameKey(const StrLen &name_) : name(name_),parent(0) { setHash(); }

   // cmp objects

   CmpResult objCmp(const NameKey &obj) const;
 };

} // namespace DDL
} // namespace CCore

#endif


