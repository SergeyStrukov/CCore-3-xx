/* test2016.SaveLoad.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundmental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/SaveLoad.h>
#include <CCore/inc/PrintSet.h>

#include <typeinfo>

namespace App {

namespace Private_2016 {

/* struct Fixed */

struct Fixed
 {
  uint8  a;
  uint16 b;
  uint32 c;
  uint64 d;

  enum { SaveLoadLen = SaveLenCounter<uint8,uint16,uint32,uint64>::SaveLoadLen };

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(a,b,c,d);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(a,b,c,d);
   }

  void print(PrinterType &out) const
   {
    Printf(out,"{a=#;,b=#;,c=#;,d=#;}",a,b,c,d);
   }
 };

/* test1() */

void test1()
 {
  Fixed f{1,2,3,4};

  Printf(Con,"len = #;\n",SaveLen(f).value);

  uint8 buf[100];

  BufPutDev putdev(buf);

  putdev(f,f,f);

  Fixed f1;

  BufGetDev getdev(buf);

  getdev(f1);

  Printf(Con,"#;\n",f1);

  getdev(f1);

  Printf(Con,"#;\n",f1);

  getdev(f1);

  Printf(Con,"#;\n",f1);

  RangeGetDev rget(Range_const(buf));

  Fixed f2[3];

  rget(f2[0],f2[1],f2[2]);

  Printf(Con,"#; #; #;\n",f2[0],f2[1],f2[2]);
 }

/* struct Variable */

struct Variable
 {
  uint16 len;
  uint8 buf[10];

  Variable()
   {
    len=0;
   }

  Variable(std::initializer_list<int> il)
   {
    len=il.size();

    for(ulen i=0; i<len ;i++) buf[i]=il.begin()[i];
   }

  void save(SaveDevType &dev) const
   {
    dev.template use<BeOrder>(len);

    dev.put(buf,len);
   }

  void load(LoadDevType &dev)
   {
    dev.template use<BeOrder>(len);

    dev.get(buf,len);
   }

  void print(PrinterType &out) const
   {
    Printf(out,"#;",PrintSet(Range(buf,len)));
   }
 };

/* test2() */

void test2()
 {
  Variable v{1,2,3};

  Printf(Con,"len = #;\n",SaveLen(v).value);

  uint8 buf[100];

  BufPutDev putdev(buf);

  putdev(v,v,v);

  Variable v1;

  BufGetDev getdev(buf);

  getdev(v1);

  Printf(Con,"#;\n",v1);

  getdev(v1);

  Printf(Con,"#;\n",v1);

  getdev(v1);

  Printf(Con,"#;\n",v1);

  RangeGetDev rget(Range_const(buf));

  Variable v2[3];

  LoadRange(v2,3,rget);

  Printf(Con,"#; #; #;\n",v2[0],v2[1],v2[2]);
 }

/* class TestGetDev */

class TestGetDev
 {
   RangeGetDev dev;

  public:

   explicit TestGetDev(PtrLen<const uint8> range) : dev(range) {}

   // get

   uint8 get() { return dev.get(); }

   void get(uint8 *ptr,ulen len) { dev.get(ptr,len); }

   void get(PtrLen<uint8> buf) { dev.get(buf); }

   PtrLen<const uint8> getRange(ulen len) { return dev.getRange(len); }

   // extra

   PtrLen<const uint8> getFinalRange() { return dev.getFinalRange(); }

   PtrLen<const uint8> getFinalRange(ulen len) { return dev.getFinalRange(len); }

   void fail() { dev.fail(); }

   // split load

   template <class Custom>
   void use_buf() {}

   template <class Custom,class T,class ... TT>
   void use_buf(T &t,TT & ... tt)
    {
     Printf(Con,"use_buf() #; #;\n",typeid(T).name(),1+sizeof ... (TT));

     const uint8 *buf=getRange(SaveLenCounter<T,TT...>::SaveLoadLen).ptr;

     if( !dev ) return;

     BufGetDev dev(buf);

     dev.use<Custom>(t,tt...);
    }

   template <class Custom>
   void use_rest() {}

   template <class Custom,class T,class ... TT>
   void use_rest(T &t,TT & ... tt)
    {
     Printf(Con,"use_rest() #; #;\n",typeid(T).name(),1+sizeof ... (TT));

     LoadAdapter<T,Custom>::Load(t,*this);

     use<Custom>(tt...);
    }

   template <class Custom>
   void use() {}

   template <class Custom,class T,class ... TT>
   void use(T &t,TT & ... tt)
    {
     SplitLoad<T,TT...> split(t,tt...);

     split.template use<Custom>(*this);
    }

   template <class ... TT>
   void operator () (TT & ... tt)
    {
     use<NeOrder>(tt...);
    }
 };

/* test3() */

void test3()
 {
  Fixed f{1,2,3,4};
  Variable v{1,2,3};

  uint8 buf[100];

  BufPutDev putdev(buf);

  putdev(f,f,v,f,v);

  TestGetDev getdev(Range_const(buf));

  Fixed f1,f2,f3;
  Variable v1,v2;

  getdev(f1,f2,v1,f3,v2);

  Printf(Con,"#; #; #; #; #;\n",f1,f2,f3,v1,v2);
 }

} // namespace Private_2016

using namespace Private_2016;

/* Testit<2016> */

template<>
const char *const Testit<2016>::Name="Test2016 SaveLoad";

template<>
bool Testit<2016>::Main()
 {
  test1();
  test2();
  test3();

  return true;
 }

} // namespace App

