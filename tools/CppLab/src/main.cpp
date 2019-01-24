/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CppLab 1.00
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

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/Print.h>

#include <inc/CppToken.h>

namespace App {

/* Process() */

void Process(StrLen text,PrintBase &out)
 {
  SrcCursor cur(text);

  for(; +cur ;++cur) Printf(out,"#;\n",*cur);
 }

void Process(StrLen src_file_name,StrLen dst_file_name)
 {
  FileToMem file(src_file_name);
  PrintFile out(dst_file_name);

  Process(Mutate<const char>(Range(file)),out);
 }

/* Main() */

void Main()
 {
  Process("src/main.cpp"_c,"test.txt"_c);
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  try
    {
     ReportException report;

     {
      Putobj(Con,"--- CppLab 1.00 ---\n--- Copyright (c) 2019 Sergey Strukov. All rights reserved. ---\n\n");

      Main();
     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }
