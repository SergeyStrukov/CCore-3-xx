/* Replace.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_gadget_Replace_h
#define CCore_inc_gadget_Replace_h

#include <CCore/inc/gadget/UtilFunc.h>
#include <CCore/inc/gadget/Classification.h>

namespace CCore {

/* Replace...() */

template <class T,class S>
T Replace(T &obj,S a) { T ret(obj); obj=a; return ret; }

template <class T>
T Replace_null(T &obj) { T ret(obj); obj=T(); return ret; }

template <class T,class S>
T Replace_min(T &obj,S a) { T ret(obj); obj=Min<T>(ret,a); return ret; }

template <class T,class S>
T Replace_max(T &obj,S a) { T ret(obj); obj=Max<T>(ret,a); return ret; }

template <class T,class S>
T Replace_add(T &obj,S a) { T ret(obj); obj=ret+a; return ret; }

template <class T,class S>
T Replace_sub(T &obj,S a) { T ret(obj); obj=ret-a; return ret; }

template <class Func,class T>
T Replace_gen(Func func,T &obj) requires ( FuncType<Func,T,T> ) { T ret(obj); obj=func(ret); return ret; }

} // namespace CCore

#endif


