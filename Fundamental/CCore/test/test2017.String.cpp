/* test2017.String.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
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

#include <CCore/inc/String.h>

namespace App {

/* Testit<2017> */

template<>
const char *const Testit<2017>::Name="Test2017 String";

template<>
bool Testit<2017>::Main()
 {
  ReportException report;

  Printf(Con,"#.q;\n","This is a static string."_str);

  String a("string_a");
  String b("string_b");
  String c("string_c");

  Printf(Con,"a = #;\n",a);
  Printf(Con,"b = #;\n",b);
  Printf(Con,"c = #;\n\n",c);

  a=b;
  b=c;

  Printf(Con,"a = #20l;\n",a);
  Printf(Con,"b = #20r;\n",b);
  Printf(Con,"c = #20c;\n\n",c);

  Printf(Con,"a+b = #;\n",a+b);
  Printf(Con,"a+\" XXX\" = #;\n",a+" XXX");

  Printf(Con,"#;\n",StringCat(c," cat ",1000));

  Printf(Con,"#;\n",Stringf("a = #; b = #;",100,200));

  PrintString out(50000);

  for(ulen i=0; i<1000 ;i++) Printf(out,"------------------ #; ----------------------\n",i);

  Putobj(Con,out.close());

  for(ulen i=5000; i<6000 ;i++) Printf(out,"------------------ #; ----------------------\n",i);

  try { Putobj(Con,out.close()); } catch(CatchType) {}

  Putobj(Con,StringSum("abc","123","def"));

  return true;
 }

} // namespace App

