/* test6006.IntelRandom.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Target/WIN32utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/crypton/IntelCPUID.h>
#include <CCore/inc/crypton/IntelRandom.h>

namespace App {

/* Testit<6006> */

template<>
const char *const Testit<6006>::Name="Test6006 IntelRandom";

template<>
bool Testit<6006>::Main()
 {
  Crypton::IntelCPUID1 cpuid;

  Printf(Con,"EAX=#.h; EBX=#.h; ECX=#.h; EDX=#.h;\n",cpuid.EAX,cpuid.EBX,cpuid.ECX,cpuid.EDX);

  Crypton::IntelRandom random;

  for(unsigned cnt=10; cnt ;cnt--) Printf(Con,"#.h;\n",random.next());

  return true;
 }

} // namespace App

