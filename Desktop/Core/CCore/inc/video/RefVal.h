/* RefVal.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Desktop
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_video_RefVal_h
#define CCore_inc_video_RefVal_h

#include <CCore/inc/video/Point.h>

#include <CCore/inc/String.h>

namespace CCore {
namespace Video {

/* word SmartBind */

enum SmartBindType { SmartBind };

/* GuardCtorRefValLock() */

void GuardCtorRefValLock();

/* classes */

template <class T> class RefVal;

template <class T> class CtorRefVal;

/* DefString */

using DefString = String ;

template <IsType<char> T,T ... CC>
const DefString & operator "" _def ()
 {
  return String::StaticObject<CC...>::Object;
 }

/* SafeString() */

DefString SafeString(StrLen str,DefString out_of_memory);

DefString SafeString(StrLen str);

/* class RefVal<T> */

template <class T>
class RefVal
 {
   const T *ptr;
   T val;

  public:

   // constructors

   RefVal() : ptr(0),val() {}

   RefVal(const T &val_) : ptr(0),val(val_) {}

   // methods

   T operator + () const { return ptr?(*ptr):val; }

   const T & get() const { if( ptr ) return *ptr; return val; }

   auto operator -> () const { return get().operator -> (); }

   // set

   T & refVal() { return val; }

   void bind(const T &obj) { ptr=&obj; }
 };

/* concept SmartConfigType<Pref> */

template <class Pref> // ref extended
concept bool SmartConfigType = requires(Meta::ToConst<Pref> &pref)
 {
  pref.getSmartConfig();
 } ;

/* class CtorRefVal<T> */

template <class T>
class CtorRefVal
 {
   const T *ptr;
   T val;
   mutable bool lock = false ;

  public:

   // constructors

   template <class ... SS>
   explicit CtorRefVal(SS && ... ss) : ptr(0),val( std::forward<SS>(ss)... ) {}

   template <SmartConfigType Pref>
   explicit CtorRefVal(SmartBindType,const Pref &pref) { bind(pref.getSmartConfig()); }

   // methods

   const T & get() const { lock=true; if( ptr ) return *ptr; return val; }

   operator const T & () const { return get(); }

   // set

   T & refVal() { return val; }

   void bind(const T &obj) { if( lock ) GuardCtorRefValLock(); ptr=&obj; }
 };

} // namespace Video
} // namespace CCore

#endif


