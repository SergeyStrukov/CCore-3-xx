/* test2010.MersenneTwister.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 1.02
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

#include <CCore/test/test.h>

#include <CCore/inc/MersenneTwister.h>

namespace App {

namespace Private_2010 {

/* class Gen */

using MT19937_UnitType = uint32 ;

#include <CCore/test/mt19937.data>

class Gen : MersenneTwister::Gen<MersenneTwister::MT19937>
 {
  public:

   Gen()
    {
     getState().copy(State);

     pure_init();
    }

   UnitType next() { return pure_next(); }
 };

} // namespace Private_2010

using namespace Private_2010;

/* Testit<2010> */

template<>
const char *const Testit<2010>::Name="Test2010 Mersenne Twister";

template<>
bool Testit<2010>::Main()
 {
  Gen gen;

  for(ulen i=0; i<DimOf(Output) ;i++)
    {
     auto r=Range(Output[i]);

     for(; +r ;++r)
       if( *r!=gen.next() )
         {
          return false;
         }
    }

  return true;
 }

} // namespace App

