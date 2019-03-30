/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: VMakeList 1.00
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

namespace App {

/* using */

using namespace CCore;

/* Main() */

int Main(StrLen src_file_name,StrLen dst_file_name)
 {
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char * argv[])
 {
  try
    {
     ReportException report;

     int ret=0;

     {
      Putobj(Con,"--- VMakeList 1.00 ---\n--- Copyright (c) 2019 Sergey Strukov. All rights reserved. ---\n\n");


     }

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

