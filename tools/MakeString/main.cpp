/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: MakeString 1.00
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

#include <CCore/inc/FileToMem.h>

namespace App {

/* using */

using namespace CCore;

/* Proc() */

void ProcStrip(StrLen input_file_name,StrLen output_file_name)
 {
  Printf(Con,"#.q; -> #.q; strip comments\n\n",input_file_name,output_file_name);
 }

void Proc(StrLen input_file_name,StrLen output_file_name)
 {
  Printf(Con,"#.q; -> #.q;\n\n",input_file_name,output_file_name);
 }

/* Main() */

void Main(int argc,const char *argv[])
 {
  switch( argc )
    {
     case 3 :
      {
       Proc(argv[1],argv[2]);
      }
     break;

     case 4 :
      {
       StrLen opt(argv[1]);

       if( opt.equal("-s"_c) )
         {
          ProcStrip(argv[2],argv[3]);
         }
       else
         {
          Printf(Exception,"App::Main(...) : bad option");
         }
      }
     break;

     default:
      {
       Printf(Exception,"App::Main(...) : bad arguments number");
      }
    }
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     {
      Putobj(Con,"--- MakeString 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

      Main(argc,argv);
     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

