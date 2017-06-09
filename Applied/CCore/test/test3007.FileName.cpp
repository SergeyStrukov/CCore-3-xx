/* test3007.FileName.cpp */
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

#include <CCore/inc/FileName.h>

namespace App {

namespace Private_3007 {

void test(StrLen file_name)
 {
  FileName fn(file_name);

  if( !fn )
    {
     Printf(Con,"fail\n");
    }
  else
    {
     Printf(Con,"#; @ #;\n",fn.getPath(),fn.getFile());
    }
 }

void test(StrLen path,StrLen file_name)
 {
  FileName fn(path,file_name);

  if( !fn )
    {
     Printf(Con,"fail\n");
    }
  else
    {
     Printf(Con,"#; @ #;\n",fn.getPath(),fn.getFile());
    }
 }

} // namespace Private_3007

using namespace Private_3007;

/* Testit<3007> */

template<>
const char *const Testit<3007>::Name="Test3007 FileName";

template<>
bool Testit<3007>::Main()
 {
  test("D:/d1/d2/d3/./../.././f");

  test("D:/home/","../d1/d2/d3/./../.././f");

  test("D:/home/","../../d1/d2/d3/./../.././f");

  test("D:../home/","../d1/d2/d3/./../.././f");

  test("D:../home/","../../d1/d2/d3/./../.././f");

  return true;
 }

} // namespace App

