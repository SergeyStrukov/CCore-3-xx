/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Zipmap 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {

/* using */

using namespace CCore;


} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     {
      Putobj(Con,"--- Zipmap 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

