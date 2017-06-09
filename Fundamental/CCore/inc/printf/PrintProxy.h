/* PrintProxy.h */
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

#ifndef CCore_inc_printf_PrintProxy_h
#define CCore_inc_printf_PrintProxy_h

#include <CCore/inc/printf/StrPrint.h>
#include <CCore/inc/printf/IntPrint.h>

namespace CCore {

/* classes */

struct StrPrintProxy;

template <UIntType UInt> struct UIntPrintProxy;

template <SIntType SInt> struct SIntPrintProxy;

template <class T> struct PrintProxy_other;

template <class T> struct PrintProxy_noclass;

template <class T> struct PrintProxy_class_noproxy;

template <class T> struct PrintProxy_class;

template <class T> struct PrintProxy;

/* struct StrPrintProxy */

struct StrPrintProxy
 {
  using OptType = StrPrintOpt ;
  using ProxyType = StrPrint ;
 };

/* struct UIntPrintProxy<UInt> */

template <UIntType UInt>
struct UIntPrintProxy
 {
  using OptType = IntPrintOpt ;
  using ProxyType = UIntPrint<UInt> ;
 };

/* struct SIntPrintProxy<SInt> */

template <SIntType SInt>
struct SIntPrintProxy
 {
  using OptType = IntPrintOpt ;
  using ProxyType = SIntPrint<SInt> ;
 };

/* struct PrintProxy_other<T> */

template <class T>
struct PrintProxy_other
 {
 };

/* struct PrintProxy_noclass<T> */

template <class T>
struct PrintProxy_noclass : PrintProxy_other<T> {};

template <UIntType T>
struct PrintProxy_noclass<T> : UIntPrintProxy<T> {};

template <SIntType T>
struct PrintProxy_noclass<T> : SIntPrintProxy<T> {};

/* concept Has_PrintOptType<T> */

template <class T>
concept bool Has_PrintOptType = requires()
 {
  typename T::PrintOptType;
 } ;

/* concept No_PrintOptType<T> */

template <class T>
concept bool No_PrintOptType = !Has_PrintOptType<T> ;

/* concept Has_PrintProxyType<T> */

template <class T>
concept bool Has_PrintProxyType = requires()
 {
  typename T::PrintProxyType;
 } ;

/* concept No_PrintProxyType<T> */

template <class T>
concept bool No_PrintProxyType = !Has_PrintProxyType<T> ;

/* struct PrintProxy_class_noproxy<T> */

template <Has_PrintOptType T>
struct PrintProxy_class_noproxy<T>
 {
  using OptType = typename T::PrintOptType ;

  using ProxyType = const T & ;
 };

template <No_PrintOptType T>
struct PrintProxy_class_noproxy<T>
 {
  using ProxyType = const T & ;
 };

/* struct PrintProxy_class<T> */

template <Has_PrintProxyType T>
struct PrintProxy_class<T> : PrintProxy<typename T::PrintProxyType> {};

template <No_PrintProxyType T>
struct PrintProxy_class<T> : PrintProxy_class_noproxy<T> {};

/* struct PrintProxy<T> */

template <class T>
struct PrintProxy : PrintProxy_noclass<T> {};

template <ClassType T>
struct PrintProxy<T> : PrintProxy_class<T> {};

template <>
struct PrintProxy<char *> : StrPrintProxy {};

template <>
struct PrintProxy<const char *> : StrPrintProxy {};

template <ulen N>
struct PrintProxy<char [N]> : StrPrintProxy {};

template <ulen N>
struct PrintProxy<const char [N]> : StrPrintProxy {};

template <>
struct PrintProxy<StrLen> : StrPrintProxy {};

} // namespace CCore

#endif


