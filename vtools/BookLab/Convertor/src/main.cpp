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

#include <inc/Source.h>
#include <inc/Convert.h>
#include <inc/TagTest.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/FileSystem.h>
#include <CCore/inc/MakeFileName.h>

namespace App {

/* Main() */

int Main(StrLen input_file_name,StrLen output_file_name)
 {
  Source src(input_file_name);

  PrintFile out(output_file_name);

  PageParam param;

  param.name="test"_c;

  Convert convert(out,param);

  return !src.run(convert);
 }

/* Test() */

bool Test(StrLen dir,StrLen file_name)
 {
  MakeFileName path(dir,file_name);

  Source src(path.get());

  TagTest convert;

  return src.run(convert);
 }

/* Main() */

int Main()
 {
  FileSystem fs;

  StrLen dir="../../../html"_c;

  FileSystem::DirCursor cur(fs,dir);

  int ret=0;

  cur.apply( [&] (StrLen file_name,FileType file_type)
                 {
                  if( file_type==FileType_file && file_name.hasSuffix(".html"_c) )
                    {
                     if( !Test(dir,file_name) )
                       {
                        Printf(Con,"@ #;\n",file_name);

                        ret=1;
                       }
                    }

                 } );

  return ret;
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     int ret;

     {
      Putobj(Con,"--- Book Convertor 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

      if( argc==1 )
        {
         ret=Main();
        }
      else if( argc==3 )
        {
         ret=Main(argv[1],argv[2]);
        }
      else
        {
         Putobj(Con,"Usage: Convertor <input-file-name> <output-file-name>\n");

         return 1;
        }
     }

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

