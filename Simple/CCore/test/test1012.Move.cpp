/* test1012.Move.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/OwnPtr.h>

namespace App {

namespace Private_1012 {

struct Test1
 {
 };

struct Test2
 {
  explicit Test2(ToMoveCtor<Test2> obj);
 };

class Test : public MemBase_nocopy
 {
   int a;

  public:

   explicit Test(int a_) : a(a_) {}

   int get() const { return a; }

   template <class P>
   void print(P &out) const
    {
     Printf(out,"Test(#;)",a);
    }
 };

class TestPtr
 {
   OwnPtr<Test> ptr;

  public:

   explicit TestPtr(int a) : ptr(new Test(a)) {}

   template <class P>
   void print(P &out) const
    {
     Printf(out,"TestPtr(#;)",ptr->get());
    }
 };

} // namespace Private_1012

using namespace Private_1012;

/* Testit<1012> */

template<>
const char *const Testit<1012>::Name="Test1012 Move";

template<>
bool Testit<1012>::Main()
 {
  Printf(Con,"#; #;\n\n",Has_ToMoveCtor<Test1>,Has_ToMoveCtor<Test2>);

  {
   DynArray<OwnPtr<Test> > buf;

   for(int i=0; i<10 ;i++) buf.append_fill( std::move( OwnPtr<Test>(new Test(i)) ) );

   buf.apply( [] (const OwnPtr<Test> &obj) { Printf(Con,"#; ",*obj); } );

   Printf(Con,"\n\n");
  }

  {
   DynArray<TestPtr> buf;

   for(int i=0; i<10 ;i++) buf.append_fill( std::move( TestPtr(i) ) );

   buf.apply( [] (const TestPtr &obj) { Printf(Con,"#; ",obj); } );

   Printf(Con,"\n\n");
  }

  return true;
 }

} // namespace App

