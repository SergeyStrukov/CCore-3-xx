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

class DefString;

template <class T> class RefVal;

template <class T> class CtorRefVal;

/* class DefString */

class DefString
 {
   StrLen def_const;
   String dynamic_str;

  public:

   // constructors

   DefString() noexcept {}

   DefString(NothingType) noexcept {}

   DefString(const char *persistent_str,ulen str_len) noexcept : def_const(persistent_str,str_len) {}

   DefString(const String &obj) noexcept : dynamic_str(obj) {}

   ~DefString() {}

   // methods

   const String & getDynamic() const noexcept { return dynamic_str; }

   StrLen str() const noexcept
    {
     if( +def_const ) return def_const;

     return Range(dynamic_str);
    }

   // print object

   using PrintOptType = StrPrintOpt ;

   void print(PrinterType &out,const PrintOptType &opt) const
    {
     Putobj(out,BindOpt(opt,str()));
    }
 };

/* DefString literal */

inline DefString operator "" _def (const char *str,ulen len) { return DefString(str,len); }

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


