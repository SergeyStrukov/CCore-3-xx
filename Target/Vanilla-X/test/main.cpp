/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/Vanilla-X
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/MemBase.h>
#include <CCore/inc/PacketPool.h>

namespace App {

/* Testit<0> */

template<>
const char *const Testit<0>::Name="Test0 empty";

template<>
bool Testit<0>::Main() { return false; }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  Used(argc);
  Used(argv);

  Testit<2999>().run();

  Printf(Con,"\nPeak memory usage #;\n\n",MemPeak());

  return 0;
 }

/* before_main() */

#include <stdio.h>

void before_main()
 {
  using namespace CCore;

  MemScope mem_scope;

  // TODO

  const char *argv[]={"main",0};

  int ret=main(1,argv);

  fflush(stdout);

  Printf(Con,"main() return #;\n",ret);

  DetachPacketBufs();
 }





