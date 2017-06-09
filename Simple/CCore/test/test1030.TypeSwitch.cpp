/* test1030.TypeSwitch.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/TypeSwitch.h>

namespace App {

namespace Private_1030 {

/* struct Node<unsigned Ind> */

template <unsigned Ind>
struct Node
 {
  template <class P>
  static void Print(P &out)
   {
    Printf(out,"Node<#;>\n",Ind);
   }
 };

/* struct PrintList<CC> */

template <class ... CC> struct PrintList;

template <class C,class ... CC>
struct PrintList<C,CC...>
 {
  template <class P>
  static void Print(P &out)
   {
    C::Type::Print(out);

    PrintList<CC...>::Print(out);
   }
 };

template <>
struct PrintList<>
 {
  template <class P>
  static void Print(P &)
   {
   }
 };

/* PrintCaseList<CaseList> */

template <class CaseList> struct PrintCaseList;

template <class ... CC>
struct PrintCaseList<Meta::CaseList<CC...> >
 {
  template <class P>
  static void Print(P &out)
   {
    PrintList<CC...>::Print(out);

    Putch(out,'\n');
   }
 };

/* struct MakeCaseList<unsigned Len> */

template <unsigned Len>
struct MakeCaseList
 {
  using Box = typename MakeCaseList<Len-1>::Box::template Extend< Meta::Case<unsigned,Len,Node<Len> > > ;

  using Ret = Meta::CaseListBox<Box> ;

  static void test1()
   {
    PrintCon out;

    PrintCaseList<Ret>::Print(out);
   }

  struct Ctx
   {
    using RetType = void ;

    template <class T>
    static void call()
     {
      PrintCon out;

      T::Print(out);
     }

    static void defcall(unsigned sw)
     {
      Printf(Con,"default #;\n",sw);
     }
   };

  static void test2()
   {
    for(unsigned sw=0; sw<=Len ;sw++)
      Meta::TypeSwitch<Ret>::Switch(sw,Ctx());
   }
 };

template <>
struct MakeCaseList<0>
 {
  using Box = Meta::TypeListBox<> ;

  using Ret = Meta::CaseList<> ;
 };

void test1()
 {
  MakeCaseList<100>::test1();
 }

void test2()
 {
  MakeCaseList<100>::test2();
 }

} // namespace Private_1030

using namespace Private_1030;

/* Testit<1030> */

template<>
const char *const Testit<1030>::Name="Test1030 TypeSwitch";

template<>
bool Testit<1030>::Main()
 {
  test1();
  test2();

  return true;
 }

} // namespace App

