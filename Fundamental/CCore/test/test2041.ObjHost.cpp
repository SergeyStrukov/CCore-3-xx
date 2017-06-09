/* test2041.ObjHost.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
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

#include <CCore/inc/ObjHost.h>

namespace App {

namespace Private_2041 {

/* class Memo1 */

class Memo1 : public ObjBase
 {
   int num;

   static int Next;

  public:

   static const Unid TypeUnid;

   Memo1()
    {
     num=Next++;

     Printf(Con,"Memo1(#;)\n",num);
    }

   ~Memo1()
    {
     Printf(Con,"~Memo1(#;)\n",num);
    }

   static void Show(Memo1 *ptr)
    {
     if( !ptr )
       Printf(Con,"Not a Memo1\n");
     else
       Printf(Con,"-> Memo1(#;)\n",ptr->num);
    }
 };

const Unid Memo1::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,10001}};

int Memo1::Next=1;

/* class Memo2 */

class Memo2 : public ObjBase
 {
   int num;

   static int Next;

  public:

   static const Unid TypeUnid;

   Memo2()
    {
     num=Next++;

     Printf(Con,"Memo2(#;)\n",num);
    }

   ~Memo2()
    {
     Printf(Con,"~Memo2(#;)\n",num);
    }

   static void Show(Memo2 *ptr)
    {
     if( !ptr )
       Printf(Con,"Not a Memo2\n");
     else
       Printf(Con,"-> Memo2(#;)\n",ptr->num);
    }
 };

const Unid Memo2::TypeUnid={{0xB4C7'DD04,0x714F'53C4,0x5E5F'E9E8,0x2844'19F0,0xCEDD'8488,0xD820'86EB,0x16EC'2386,10002}};

int Memo2::Next=1;

/* functions */

template <class R>
void Show(const char *title,R r)
 {
  Printf(Con,"#;\n\n",Title(title));

  for(; +r ;++r) Printf(Con,"#;\n",*r);

  Printf(Con,"\n");
 }

void test1()
 {
  Memo1 obj1;
  Memo1 obj2;
  Memo1 obj3;

  ObjMaster master1(obj1,"obj1");
  ObjMaster master2(obj2,"obj2");
  ObjMaster master3(obj3,"obj3");

  ObjMaster_delete master4(new Memo2(),"obj4");
  ObjMaster_delete master5(new Memo2(),"obj5");

  ObjHook hook1("obj1");
  ObjHook hook2("obj2");
  ObjHook hook3("obj3");
  ObjHook hook4("obj4");
  ObjHook hook5("obj5");

  Putch(Con,'\n');

  Memo1::Show(hook1.cast<Memo1>());
  Memo1::Show(hook2.cast<Memo1>());
  Memo1::Show(hook3.cast<Memo1>());
  Memo1::Show(hook4.cast<Memo1>());
  Memo1::Show(hook5.cast<Memo1>());

  Putch(Con,'\n');

  {
   ObjHost::List<ObjInfo> list;

   list.build();

   Show("ObjInfo",Range(list));
  }

  {
   ObjHost::List<ObjInfo_obj> list;

   list.build();

   Show("ObjInfo_obj",Range(list));
  }

  {
   ObjHost::List<ObjInfo_if<Memo1> > list;

   list.build();

   Show("ObjInfo_if",Range(list));
  }

  {
   ObjHost::List<ObjInfo_obj_if<Memo2> > list;

   list.build();

   Show("ObjInfo_obj_if",Range(list));
  }
 }

} // namespace Private_2041

using namespace Private_2041;

/* Testit<2041> */

template<>
const char *const Testit<2041>::Name="Test2041 ObjHost";

template<>
bool Testit<2041>::Main()
 {
  test1();

  return true;
 }

} // namespace App

