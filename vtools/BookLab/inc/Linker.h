/* Linker.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef Linker_h
#define Linker_h

#include <inc/BookElements.h>

namespace App {
namespace BookLab {

/* classes */

class Linker;

/* class Linker */

class Linker : NoCopy
 {
  public:

   Linker() {}

   ~Linker() {}

   template <class T>
   void addName(IntAnyObjPtr<Scope,Doc> scope,String name,IntObjPtr<T> ptr) // TODO
    {
     Used(scope);
     Used(name);
     Used(ptr);
    }

   template <class T>
   void addPtr(IntAnyObjPtr<Scope,Doc> scope,String name,IntObjPtr<T> &ptr) // TODO
    {
     Used(scope);
     Used(name);
     Used(ptr);
    }

   template <class ... TT>
   void addPtr(IntAnyObjPtr<Scope,Doc> scope,String name,IntAnyObjPtr<TT...> &ptr) // TODO
    {
     Used(scope);
     Used(name);
     Used(ptr);
    }

   bool link(PrintBase &eout)
    {
     Printf(eout,"not implemented");

     return false;
    }
 };

} // namespace BookLab
} // namespace App

#endif
