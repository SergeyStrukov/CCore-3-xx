/* TypeNumber.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/inc/TypeNumber.h>

#include <CCore/inc/MemBase.h>

namespace CCore {

/* GetPlanInitNode_...() */

namespace Private_TypeNumber {

class RegType : public UnidRegister
 {
  public:

   RegType() {}

   ~RegType() {}

   static const char * GetTag() { return "TypeNumber"; }
 };

PlanInitObject<RegType,PlanInitReq<GetPlanInitNode_MemBase> > Object CCORE_INITPRI_1 ;

} // namespace Private_TypeNumber

using namespace Private_TypeNumber;

PlanInitNode * GetPlanInitNode_TypeNumber()
 {
  return &Object;
 }

/* class TypeNumber */

UnidRegister & TypeNumber::GetRegister()
 {
  return *Object;
 }

} // namespace CCore


