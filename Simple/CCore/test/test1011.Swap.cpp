/* test1011.Swap.cpp */
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

#include <CCore/inc/Swap.h>

namespace App {

namespace Private_1011 {

class Test1
 {
   int a;

  public:

   explicit Test1(int a_) : a(a_) {}

   template <class P>
   void print(P &out) const
    {
     Printf(out,"Test1(#;)",a);
    }
 };

class Test2 : NoCopy
 {
   int a;

  public:

   explicit Test2(int a_) : a(a_) {}

   Test2(Test2 &&obj) : a(Replace_null(obj.a)) {}

   ~Test2()
    {
     if( a ) Printf(Con,"~Test2(#;)\n",a);
    }

   Test2 & operator = (Test2 &&obj)
    {
     if( this!=&obj )
       {
        if( a ) Printf(Con,"Test2::close(#;)\n",a);

        a=Replace_null(obj.a);
       }

     return *this;
    }

   template <class P>
   void print(P &out) const
    {
     Printf(out,"Test2(#;)",a);
    }
 };

class Test3 : NoCopy
 {
   int a;

  public:

   explicit Test3(int a_) : a(a_) {}

   void objSwap(Test3 &obj)
    {
     Swap(a,obj.a);
    }

   template <class P>
   void print(P &out) const
    {
     Printf(out,"Test3(#;)",a);
    }
 };

} // namespace Private_1011

using namespace Private_1011;

/* Testit<1011> */

template<>
const char *const Testit<1011>::Name="Test1011 Swap";

template<>
bool Testit<1011>::Main()
 {
  {
   Test1 a(1),b(2);

   Printf(Con,"#; #;\n",a,b);

   Swap(a,b);

   Printf(Con,"#; #;\n\n",a,b);
  }

  {
   Test2 a(1),b(2);

   Printf(Con,"#; #;\n",a,b);

   Swap(a,b);

   Printf(Con,"#; #;\n\n",a,b);
  }

  {
   Test3 a(1),b(2);

   Printf(Con,"#; #;\n",a,b);

   Swap(a,b);

   Printf(Con,"#; #;\n\n",a,b);
  }

  return true;
 }

} // namespace App

