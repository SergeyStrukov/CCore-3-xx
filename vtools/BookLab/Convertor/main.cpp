/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Scan.h>
#include <CCore/inc/Exception.h>

namespace App {

/* using */

using namespace CCore;

/* Main() */

void Main(StrLen input_file_name,StrLen output_file_name)
 {
  ScanFile inp(input_file_name);
  PrintFile out(output_file_name);

  // 1

  Putobj(out,"include <Mandelbrot.style.ddl>\n\n");

  Putobj(out,"scope Pages {\n\n");

  Putobj(out,"Page page1 = { 'Manual' ,\n  {\n");

  Putobj(out,"  }\n");
  Putobj(out," };\n\n");

  Putobj(out,"} // scope Pages\n\n");

  Putobj(out,"Book Data = { 'Mandelbrot scope' , {&Pages#page1} , Pages#Back , Pages#Fore } ;");
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
      Putobj(Con,"--- Book Convertor 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc<3 )
        {
         Putobj(Con,"Usage: Convertor <input-file-name> <output-file-name>\n");

         return 1;
        }

      Main(argv[1],argv[2]);
     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

