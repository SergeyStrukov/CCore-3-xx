/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/Console/test2
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/Task.h>

namespace App {

/* using */

using namespace CCore;

/* Main() */

void Main(const char *name)
 {
  Task::Sleep(3_sec);

  Printf(Con,"#;> stop\n\n",name);
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char * argv[])
 {
  try
    {
     ReportException report;

     Main( (argc>1)? argv[1] : "???" );

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

