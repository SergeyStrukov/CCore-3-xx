/* testArray.h */
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

#ifndef CCore_test_testArray_h
#define CCore_test_testArray_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>
#include <CCore/inc/PrintSet.h>

namespace App {

/* using */

using namespace CCore;

namespace Private_testArray {

/* struct X */

struct X : SetNoThrowFlags<X,false,true>
 {
  int val;

  X()
   : val(NextVal++)
   {
    Printf(Con,"X::X(#;)\n",val);

    if( val>10 ) Printf(Exception,"XTrap");
   }

  ~X()
   {
    Printf(Con,"X::~X(#;)\n",val);
   }

  using PrintProxyType = int ;

  operator int() const { return val; }

  static int NextVal;
 };

/* functions */

template <class T>
void Show(const T &a)
 {
  Printf(Con,"#; maxlen = #;\n",PrintSet(Range(a)),a.getMaxLen());
 }

template <class T>
void ShowReverse(const T &a)
 {
  Printf(Con,"#; maxlen = #;\n",PrintSet(RangeReverse(a)),a.getMaxLen());
 }

} // namespace Private_testArray

using namespace Private_testArray;

} // namespace App

#endif


