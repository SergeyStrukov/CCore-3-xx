/* test2024.SortUnique.cpp */
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

#include <CCore/inc/PrintSet.h>
#include <CCore/inc/algon/SortUnique.h>

namespace App {

namespace Private_2024 {

/* struct PrintSeq */

struct PrintSeq
 {
  class FunctorType : NoCopy
   {
     bool first;

    public:

     explicit FunctorType(const PrintSeq &)
      : first(true)
      {
       Putobj(Con,"{ ");
      }

     ~FunctorType()
      {
       Putobj(Con," }\n");
      }

     void operator () (int a)
      {
       if( first )
         {
          Printf(Con,"#;",a);

          first=false;
         }
       else
         {
          Printf(Con," , #;",a);
         }
      }

     void operator () (PtrLen<int> a)
      {
       if( first )
         {
          Printf(Con,"#;",PrintSet(a));

          first=false;
         }
       else
         {
          Printf(Con," , #;",PrintSet(a));
         }
      }

     void operator () (PtrLenReverse<int> a)
      {
       if( first )
         {
          Printf(Con,"#;",PrintSet(a));

          first=false;
         }
       else
         {
          Printf(Con," , #;",PrintSet(a));
         }
      }
   };
 };

} // namespace Private_2024

using namespace Private_2024;

/* Testit<2024> */

template<>
const char *const Testit<2024>::Name="Test2024 SortUnique";

template<>
bool Testit<2024>::Main()
 {
  int buf[]={1,2,2,3,3,3,4,4,4,4,5,5,5,5,5};

  Algon::SortThenApplyUnique(Range(buf),PrintSeq());
  Algon::SortThenApplyUnique(RangeReverse(buf),PrintSeq());
  Algon::ApplyUnique(Range(buf),PrintSeq());

  Putch(Con,'\n');

  Algon::ApplyUniqueBy(Range(buf), [] (int a) { return a; } ,PrintSeq());
  Algon::IncrSortThenApplyUniqueBy(Range(buf), [] (int a) { return a; } ,PrintSeq());
  Algon::DecrSortThenApplyUniqueBy(Range(buf), [] (int a) { return a; } ,PrintSeq());

  Putch(Con,'\n');

  Algon::ApplyUniqueRange(RangeReverse(buf),PrintSeq());
  Algon::SortThenApplyUniqueRange(Range(buf),PrintSeq());

  Putch(Con,'\n');

  Algon::IncrSortThenApplyUniqueRangeBy(Range(buf), [] (int a) { return -a; } ,PrintSeq());
  Algon::DecrSortThenApplyUniqueRangeBy(Range(buf), [] (int a) { return -a; } ,PrintSeq());

  return true;
 }

} // namespace App

