/* Scope.h */
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

#ifndef CCore_inc_Scope_h
#define CCore_inc_Scope_h

#include <CCore/inc/Printf.h>
#include <CCore/inc/PlanInit.h>

namespace CCore {

/* GetPlanInitNode_...() */

PlanInitNode * GetPlanInitNode_Scope();

/* classes */

class Scope;

/* class Scope */

class Scope : NoCopy
 {
   DLink<Scope> link;

   StrLen name;

   using Algo = DLink<Scope>::LinearAlgo<&Scope::link> ;

  private:

   static Scope * Top();

   static void SetTop(Scope *top);

  public:

   explicit Scope(StrLen name); // persistent

   ~Scope();

   template <class P>
   static bool Print(P &&out)
    {
     Algo::Cur cur(Top());

     if( !cur ) return false;

     Putobj(std::forward<P>(out),cur->name);

     for(++cur; +cur ;++cur) Putobj(std::forward<P>(out)," "_c,cur->name);

     return true;
    }
 };

} // namespace CCore

#endif

