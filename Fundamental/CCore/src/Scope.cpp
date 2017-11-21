/* Scope.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Scope.h>

#include <CCore/inc/TlsSlot.h>

namespace CCore {

/* GetPlanInitNode_...() */

namespace Private_Scope {

struct Slot : TlsSlot
 {
  Slot() : TlsSlot("Scope") {}
 };

Slot Object CCORE_INITPRI_1 ;

} // namespace Private_Scope

using namespace Private_Scope;

PlanInitNode * GetPlanInitNode_Scope() { return &Object; }

/* class Scope */

Scope * Scope::Top()
 {
  return static_cast<Scope *>(Object.get());
 }

void Scope::SetTop(Scope *top)
 {
  Object.set(top);
 }

Scope::Scope(StrLen name_)
 : name(name_)
 {
  SetTop( Algo::InsTop(Top(),this) );
 }

Scope::~Scope()
 {
  SetTop( Algo::DelTop(Top(),this) );
 }

} // namespace CCore

