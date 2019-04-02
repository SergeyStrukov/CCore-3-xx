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

#include <inc/Engine.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {

/* Main() */

int Main(StrLen src_file_name,StrLen proj_file_name,StrLen prep_file_name)
 {
  DataFile data(src_file_name);

  Engine engine(data.getParam(),src_file_name,proj_file_name,prep_file_name);

  return engine.run();
 }

} // namespace App

/* main() */

using namespace App;

int usage()
 {
  Putobj(Con,"Usage: CCore-VMakeList <src-file-name> <proj-file-name> <prep-file-name>\n");

  return 1;
 }

int main(int argc,const char * argv[])
 {
  try
    {
     ReportException report;

     int ret=0;

     {
      Putobj(Con,"--- VMakeList 1.00 ---\n--- Copyright (c) 2019 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc!=4 ) return usage();

      ret=Main(argv[1],argv[2],argv[3]);
     }

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

