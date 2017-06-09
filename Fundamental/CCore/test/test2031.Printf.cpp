/* test2031.Printf.cpp */
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

#include <CCore/inc/PrintTitle.h>

namespace App {

namespace Private_2031 {

/* class Test */

class Test : NoCopy
 {
   int val;

  public:

   Test() : val(54321) {}

   void print(PrinterType &out) const
    {
     Printf(out,"#.h;",val);
    }
 };

} // namespace Private_2031

using namespace Private_2031;

/* Testit<2031> */

template<>
const char *const Testit<2031>::Name="Test2031 Printf";

template<>
bool Testit<2031>::Main()
 {
  Printf(Con,"#;\n",PrintTitle(12345));

  Printf(Con,"#; #; #;\n",Tuple(1,2,3));

  Test test;

  Printf(Con,"#;\n",PrintTitle(test));

  Printf(Con,"\n#;\n\n",TextDivider());

  Printf(Con,"#;\n",100_msec);
  Printf(Con,"#;\n",2345_msec);
  Printf(Con,"#;\n",100_msec+100_sec);
  Printf(Con,"#;\n",100_msec+5_sec+10_min);

  Printf(Con,"\n#;\n\n",TextDivider());

  Printf(Con,"--- #10l; ---\n",12345);
  Printf(Con,"--- #10i; ---\n",12345);
  Printf(Con,"--- #10r; ---\n",12345);
  Printf(Con,"--- #+10.5l; ---\n",12345);
  Printf(Con,"--- #+10.hi; ---\n",12345);
  Printf(Con,"--- #10.hi; ---\n",-12345);

  Printf(Con,"--- #10.f2l; ---\n",12345);
  Printf(Con,"--- #10.f2i; ---\n",12345);
  Printf(Con,"--- #10.f2r; ---\n",12345);

  Printf(Con,"--- #10.f2l; ---\n",-12345);
  Printf(Con,"--- #10.f2i; ---\n",-12345);
  Printf(Con,"--- #10.f2r; ---\n",-12345);

  Printf(Con,"--- #10.f2l; ---\n",-12);
  Printf(Con,"--- #10.f2i; ---\n",-12);
  Printf(Con,"--- #10.f2r; ---\n",-12);

  Printf(Con,"--- #10.f4l; ---\n",12);
  Printf(Con,"--- #10.f4i; ---\n",12);
  Printf(Con,"--- #10.f4r; ---\n",12);

  Printf(Con,"--- #10.f2l; ---\n",0);
  Printf(Con,"--- #10.f2i; ---\n",0);
  Printf(Con,"--- #10.f2r; ---\n",0);

  Printf(Con,"\n#;\n\n",TextDivider());

  uint8 buf[50];

  for(ulen i=0; i<DimOf(buf) ;i++) buf[i]=uint8(i);

  Printf(Con,"#4.8;\n",PrintDump(Range(buf)));

  return true;
 }

} // namespace App

