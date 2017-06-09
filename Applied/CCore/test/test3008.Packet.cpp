/* test3008.Packet.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/PacketPool.h>

namespace App {

namespace Private_3008 {

/* struct Ext1 */

struct Ext1
 {
  int a;

  explicit Ext1(int a_) : a(a_) {}

  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;)",a);
   }
 };

/* struct Ext2 */

struct Ext2
 {
  int a;
  int b;

  Ext2(int a_,int b_) : a(a_),b(b_) {}

  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;,#;)",a,b);
   }
 };

/* struct Ext3 */

struct Ext3
 {
  int a;
  int b;
  int c;

  Ext3(int a_,int b_,int c_) : a(a_),b(b_),c(c_) {}

  template <class P>
  void print(P &out) const
   {
    Printf(out,"(#;,#;,#;)",a,b,c);
   }
 };

} // namespace Private_3008

using namespace Private_3008;

/* Testit<3008> */

template<>
const char *const Testit<3008>::Name="Test3008 Packet";

template<>
bool Testit<3008>::Main()
 {
  Packet<uint8> p1=AllocPacket<uint8>();
  Packet<uint8,Ext1> p2=p1.pushExt<Ext1>(1);
  Packet<uint8,Ext1,Ext2> p3=p2.pushExt<Ext2>(2,3);
  Packet<uint8,Ext1,Ext2,Ext3> p4=p3.pushExt<Ext3>(4,5,6);

  Printf(Con,"#;\n",*p4.getExt());
  Printf(Con,"#;\n",*p4.getDeepExt<1>());
  Printf(Con,"#;\n",*p4.getDeepExt<2>());
  Printf(Con,"#;\n",*p4.getDeepExt<3>());

  auto p5=p4.popExt();

  Printf(Con,"#;\n",*p5.getExt());

  auto p6=p5.popExt();

  Printf(Con,"#;\n",*p6.getExt());

  auto p7=p6.popExt();

  p7.complete();

  return true;
 }

} // namespace App

