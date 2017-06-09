/* TypeNumber.h */
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

#ifndef CCore_inc_TypeNumber_h
#define CCore_inc_TypeNumber_h

#include <CCore/inc/PlanInit.h>
#include <CCore/inc/Unid.h>

namespace CCore {

/* GetPlanInitNode_...() */

PlanInitNode * GetPlanInitNode_TypeNumber();

/* classes */

class TypeNumber;

template <UnidType T> class TypeNumberOf;

/* class TypeNumber */

class TypeNumber
 {
   ulen number;

  protected:

   static UnidRegister & GetRegister();

   explicit TypeNumber(ulen number_) : number(number_) {}

  public:

   ulen get() const { return number; }

   bool operator == (TypeNumber obj) const { return number==obj.number; }

   bool operator != (TypeNumber obj) const { return number!=obj.number; }

   template <class ... TT>
   bool oneOf() const { return ( ... || ( (*this) == TypeNumberOf<TT>() ) ); }
 };

/* class TypeNumberOf<T> */

template <UnidType T>
class TypeNumberOf : public TypeNumber
 {
   class Init
    {
      ulen number;

     public:

      Init() : number(GetRegister().template getTypeId<T>()) {}

      operator ulen() const { return number; }
    };

   static Init Number;

  public:

   TypeNumberOf() : TypeNumber(Number) {}
 };

template <UnidType T>
typename TypeNumberOf<T>::Init TypeNumberOf<T>::Number CCORE_INITPRI_3 ;

} // namespace CCore

#endif


