/* test2054.ApplyToRange.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/algon/ApplyToRange.h>

namespace App {

namespace Private_2054 {

struct AccFunc
 {
  int result = 0 ;

  void operator () (int x) { result+=x; }

  int getResult() { return result; }
 };

struct CapAccFunc
 {
  int cap;
  int result = 0 ;

  explicit CapAccFunc(int cap_) : cap(cap_) {}

  bool operator () (int x) { if( x>cap ) return false; result+=x; return true; }

  int getResult() { return result; }
 };

} // namespace Private_2054

using namespace Private_2054;

/* Testit<2054> */

template<>
const char *const Testit<2054>::Name="Test2054 ApplyToRange";

template<>
bool Testit<2054>::Main()
 {
  int buf[]={1,2,3,4,5};

  Algon::ApplyToRange(Range(buf), [] (int x) { Printf(Con,"#; ",x); } );

  Printf(Con,"\n");

  Algon::ApplyToRange(Range(buf), [] (int x) { Printf(Con,"#; ",x); return x<3; } );

  Printf(Con,"\n");

  Printf(Con,"#;\n",Algon::ApplyToRange(Range(buf),AccFunc()));

  Printf(Con,"#;\n",Algon::ApplyToRange(Range(buf),CapAccFunc(3)));

  return true;
 }

} // namespace App

