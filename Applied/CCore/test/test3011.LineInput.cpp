/* test3011.LineInput.cpp */
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

#include <CCore/inc/LineInput.h>
#include <CCore/inc/ReadCon.h>

namespace App {

/* Testit<3011> */

template<>
const char *const Testit<3011>::Name="Test3011 LineInput";

template<>
bool Testit<3011>::Main()
 {
  LineInput<ReadCon> line;

  Putobj(Con,"type exit to stop\n\n");

  for(;;)
    {
     Putobj(Con,"test> ");

     StrLen str=line.get();

     Printf(Con,"#.q;\n",str);

     if( str.equal(StrLen("exit")) ) break;
    }

  Putobj(Con,"\ntype exit to exit\n\n");

  Putobj(Con,"test> ");

  for(TimeScope time_scope(3_sec);;)
    {
     StrLen str;

     if( line.get(time_scope,str) )
       {
        Printf(Con,"#.q;\n",str);

        if( str.equal(StrLen("exit")) ) break;

        Putobj(Con,"test> ");
       }
     else
       {
        Putobj(Con,".....\b\b\b\b\b");

        Task::Sleep(300_msec);

        Putobj(Con,"     \b\b\b\b\b");

        time_scope.nextScope();
       }
    }

  return true;
 }

} // namespace App

