/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/WIN32
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#ifndef CCORE_MINI

#include <CCore/inc/PacketPool.h>

#endif

#include <CCore/inc/MemBase.h>

namespace App {

/* Testit<0> */

template<>
const char *const Testit<0>::Name="Test0 empty";

template<>
bool Testit<0>::Main() { return false; }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  MemScope mem_scope;

  //Testit<2999>().run();
  Testit<4035>().run();

  Printf(Con,"\nPeak memory usage #;\n\n",MemPeak());

#ifndef CCORE_MINI

  DetachPacketBufs();

#endif

  return 0;
 }


