/* PlanInit.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_PlanInit_h
#define CCore_inc_PlanInit_h

#include <CCore/inc/List.h>

namespace CCore {

/* concept PlanInitObjectType<T> */

template <NothrowDtorType T>
concept bool PlanInitObjectType = requires()
 {
  { T::GetTag() } -> const char * ;
 } ;

/* classes */

class PlanInitNode;

template <PlanInitNode * GetPtr()> struct PlanInitReq;

/* concept PlanInitReqType<R> */

template <class R>
concept bool PlanInitReqType = requires()
 {
  { R::GetPtr() } -> PlanInitNode * ;
 } ;

/* classes */

template <PlanInitReqType ... RR> class PlanInitReqList;

template <PlanInitObjectType T,PlanInitReqType ... RR> class PlanInitObject;

/* class PlanInitNode */

class PlanInitNode : NoCopy
 {
   const char *tag;
   PtrLen<PlanInitNode *> req_list;

   SLink<PlanInitNode> link;

   DLink<PlanInitNode> init_link;

   int flag;
   PlanInitNode *back;
   PtrLen<PlanInitNode *> cur;

  private:

   bool prepare(PlanInitNode *back=0);

   PlanInitNode * next();

   PlanInitNode * complete();

   class Engine;

  private:

   virtual void init() {}

   virtual void exit() {}

  public:

   explicit PlanInitNode(const char *tag,PtrLen<PlanInitNode *> req_list=Empty);

   const char * getTag() const { return tag; }
 };

/* struct PlanInitReq<PlanInitNode * GetPtr()> */

template <PlanInitNode * GetPtr_()>
struct PlanInitReq
 {
  static PlanInitNode * GetPtr() { return GetPtr_(); }
 };

/* class PlanInitReqList<RR> */

template <PlanInitReqType ... RR>
class PlanInitReqList : NoCopy
 {
   PlanInitNode * req_list[sizeof ... (RR)];

  public:

   PlanInitReqList() : req_list{ RR::GetPtr() ... } {}

   PtrLen<PlanInitNode *> getReqList() { return Range(req_list); }
 };

template <>
class PlanInitReqList<> : NoCopy
 {
  public:

   PlanInitReqList() {}

   PtrLen<PlanInitNode *> getReqList() { return Empty; }
 };

/* class PlanInitObject<T,RR> */

template <PlanInitObjectType T,PlanInitReqType ... RR>
class PlanInitObject : PlanInitReqList<RR...> , public PlanInitNode
 {
   InitExitObject<T> obj;

  private:

   virtual void init() { obj.init(); }

   virtual void exit() { obj.exit(); }

  public:

   explicit PlanInitObject() : PlanInitNode(T::GetTag(),this->getReqList()),obj() {}

   T * operator + () const { return +obj; }

   bool operator ! () const { return !obj; }

   T * getPtr() const { return obj.getPtr(); }

   T & operator * () const { return *getPtr(); }

   T * operator -> () const { return getPtr(); }
 };

/* GetPlanInitNode_...() */

PlanInitNode * GetPlanInitNode_CCore();

} // namespace CCore

#endif


