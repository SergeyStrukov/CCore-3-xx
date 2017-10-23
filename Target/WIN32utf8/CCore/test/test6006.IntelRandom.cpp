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

  Printf(Con,"TIMESTAMP = #;\n",(bool)cpuid.capableTIMESTAMP());
  Printf(Con,"MMX = #;\n",(bool)cpuid.capableMMX());
  Printf(Con,"SSE = #;\n",(bool)cpuid.capableSSE());
  Printf(Con,"SSE2 = #;\n",(bool)cpuid.capableSSE2());
  Printf(Con,"SSE3 = #;\n",(bool)cpuid.capableSSE3());
  Printf(Con,"PCLMULQDQ = #;\n",(bool)cpuid.capablePCLMULQDQ());
  Printf(Con,"SSSE3 = #;\n",(bool)cpuid.capableSSSE3());
  Printf(Con,"SSE4_1 = #;\n",(bool)cpuid.capableSSE4_1());
  Printf(Con,"SSE4_2 = #;\n",(bool)cpuid.capableSSE4_2());
  Printf(Con,"AVX = #;\n",(bool)cpuid.capableAVX());

  Crypton::IntelRandom random;

  for(unsigned cnt=10; cnt ;cnt--) Printf(Con,"#.h;\n",random.next());

  return true;
 }

} // namespace App

