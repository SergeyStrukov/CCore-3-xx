/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: vmake 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/VMakeProc.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/FileSystem.h>

namespace App {

/* Main() */

int Main(StrLen file_name,StrLen target)
 {
  Printf(Con,"#; @ #;\n\n",file_name,target);

  VMake::FileProc file_proc;

  VMake::DataProc proc(file_proc,file_name,target);

  return proc.make();
 }

} // namespace App

/* main() */

using namespace App;

const StrLen DefTarget = "main"_c ;

const StrLen DefFile = "default.vm.ddl"_c ;

bool NoDefFile()
 {
  FileSystem fs;

  return fs.getFileType(DefFile)!=FileType_file;
 }

int usage()
 {
  Putobj(Con,"Usage: vmake\n");
  Putobj(Con,"OR     vmake <target>\n");
  Putobj(Con,"OR     vmake <target> <vmake-file>\n");

  return 1;
 }

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;

     int ret;

     {
      Putobj(Con,"--- vmake 1.00 ---\n--- Copyright (c) 2019 Sergey Strukov. All rights reserved. ---\n\n"_c);

      switch( argc )
        {
         case 1 :
          {
           if( NoDefFile() )
             ret=usage();
           else
             ret=Main(DefTarget,DefFile);
          }
         break;

         case 2 :
          {
           if( NoDefFile() )
             ret=usage();
           else
             ret=Main(argv[1],DefFile);
          }
         break;

         case 3 :
          {
           ret=Main(argv[2],argv[1]);
          }
         break;

         default:
          {
           ret=usage();
          }
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

