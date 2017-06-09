/* ScanProxy.h */
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

#ifndef CCore_inc_ScanProxy_h
#define CCore_inc_ScanProxy_h

#include <CCore/inc/scanf/IntScan.h>
#include <CCore/inc/scanf/StringScan.h>

namespace CCore {

/* classes */

template <UIntType UInt> struct UIntScanProxy;

template <SIntType SInt> struct SIntScanProxy;

template <class T> struct ScanProxy_other;

template <class T> struct ScanProxy_noclass;

template <class T> struct ScanProxy_class_noproxy;

template <class T> struct ScanProxy_class;

template <class T> struct ScanProxy;

/* struct UIntScanProxy<UInt> */

template <UIntType UInt>
struct UIntScanProxy
 {
  using OptType = IntScanOpt ;

  using ProxyType = UIntScan<UInt> ;
 };

/* struct SIntScanProxy<SInt> */

template <SIntType SInt>
struct SIntScanProxy
 {
  using OptType = IntScanOpt ;

  using ProxyType = SIntScan<SInt> ;
 };

/* struct ScanProxy_other<T> */

template <class T>
struct ScanProxy_other
 {
 };

/* struct ScanProxy_noclass<T> */

template <class T>
struct ScanProxy_noclass : ScanProxy_other<T> {};

template <UIntType T>
struct ScanProxy_noclass<T> : UIntScanProxy<T> {};

template <SIntType T>
struct ScanProxy_noclass<T> : SIntScanProxy<T> {};

/* concept Has_ScanOptType<T> */

template <class T>
concept bool Has_ScanOptType = requires()
 {
  typename T::ScanOptType;
 } ;

/* concept No_ScanOptType<T> */

template <class T>
concept bool No_ScanOptType = !Has_ScanOptType<T> ;

/* concept Has_ScanProxyType<T> */

template <class T>
concept bool Has_ScanProxyType = requires()
 {
  typename T::ScanProxyType;
 } ;

/* concept No_ScanProxyType<T> */

template <class T>
concept bool No_ScanProxyType = !Has_ScanProxyType<T> ;

/* struct ScanProxy_class_noproxy<T> */

template <Has_ScanOptType T>
struct ScanProxy_class_noproxy<T>
 {
  using OptType = typename T::ScanOptType ;

  using ProxyType = T & ;
 };

template <No_ScanOptType T>
struct ScanProxy_class_noproxy<T>
 {
  using ProxyType = T & ;
 };

/* struct ScanProxy_class<T> */

template <Has_ScanProxyType T>
struct ScanProxy_class<T> : ScanProxy<typename T::ScanProxyType> {};

template <No_ScanProxyType T>
struct ScanProxy_class<T> : ScanProxy_class_noproxy<T> {};

/* struct ScanProxy<T> */

template <class T>
struct ScanProxy : ScanProxy_noclass<T> {};

template <ClassType T>
struct ScanProxy<T> : ScanProxy_class<T> {};

template <>
struct ScanProxy<String>
 {
  using OptType = StringScanOpt ;

  using ProxyType = StringScan ;
 };

} // namespace CCore

#endif


