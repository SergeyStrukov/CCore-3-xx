/* test1015.OwnPtr.cpp */
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

#include <CCore/inc/MemBase.h>
#include <CCore/inc/OwnPtr.h>

namespace App {

namespace Private_1015 {

/* class Test */

class Test : public MemBase_nocopy
 {
   int value;

  public:

   explicit Test(int value_) : value(value_) { Printf(Con,"Test(#;)\n",value); }

   ~Test() { Printf(Con,"~Test(#;)\n",value); }

   void show() { Printf(Con,"Test(#;).show()\n",value); }
 };

} // namespace Private_1015

using namespace Private_1015;

/* Testit<1015> */

template<>
const char *const Testit<1015>::Name="Test1015 OwnPtr";

template<>
bool Testit<1015>::Main()
 {
  OwnPtr<Test> obj1(new Test(1));
  OwnPtr<Test> obj2(new Test(2));

  Swap(obj1,obj2);

  obj1->show();
  obj2->show();

  InitExitObject<OwnPtr<Test> > init_obj;
  InitStorage<sizeof (OwnPtr<Test>)> mem1;
  InitStorage<sizeof (OwnPtr<Test>)> mem2;

  init_obj.clean();
  init_obj.init();

  OwnPtr<Test> *obj=init_obj.getPtr();

  Swap(obj1,*obj);

  (*obj)->show();

  obj=Move(obj,mem1.getPlace());

  (*obj)->show();

  obj=CtorMove(obj,mem2.getPlace());

  (*obj)->show();

  obj->~OwnPtr();

  return true;
 }

} // namespace App

