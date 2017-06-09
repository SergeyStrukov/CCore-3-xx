/* test2022.EuclidRotate.cpp */
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

#include <CCore/inc/algon/EuclidRotate.h>
#include <CCore/inc/PrintSet.h>

namespace App {

/* Testit<2022> */

template<>
const char *const Testit<2022>::Name="Test2022 EuclidRotate";

template<>
bool Testit<2022>::Main()
 {
  const int Len = 10 ;

  int buf[Len];

  for(int i=0; i<Len ;i++) buf[i]=i;

  for(ulen len=0; len<=(ulen)Len ;len++)
    {
     PtrLen<int> r=Range(buf);

     Algon::EuclidRotate_prefix(r,len);

     Printf(Con,"#;\n",PrintSet(r));

     Algon::EuclidRotate_suffix(r,len);

     Printf(Con,"#;\n\n",PrintSet(r));
    }

  return true;
 }

} // namespace App

