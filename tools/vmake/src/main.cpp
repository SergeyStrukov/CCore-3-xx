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

#include <CCore/inc/Scanf.h>

#include <CCore/inc/FileSystem.h>

namespace App {

/* struct OptP */

struct OptP
 {
  unsigned cap = 0 ;

  explicit OptP(StrLen arg)
   {
    ScanString inp(arg);

    Scanf(inp,"-p#;#;",cap,EndOfScan);

    if( inp.isFailed() ) cap=0;
   }
 };

/* Main() */

int Main(unsigned pcap,StrLen file_name,StrLen target)
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

bool IsOpt(const char *str) { return *str=='-' ; }

int usage()
 {
  Putobj(Con,"Usage: vmake [-pNNN]\n");
  Putobj(Con,"OR     vmake [-pNNN] <target>\n");
  Putobj(Con,"OR     vmake [-pNNN] <target> <vmake-file>\n");

  return 1;
 }

int inner_main(int argc,const char **argv)
 {
  Putobj(Con,"--- vmake 1.00 ---\n--- Copyright (c) 2019 Sergey Strukov. All rights reserved. ---\n\n"_c);

  unsigned pcap=0;

  if( argc>1 && IsOpt(argv[1]) )
    {
     OptP opt(argv[1]);

     if( opt.cap==0 ) return usage();

     pcap=opt.cap;

     argc--;
     argv++;
    }

  switch( argc )
    {
     case 1 :
      {
       if( NoDefFile() )
         return usage();
       else
         return Main(pcap,DefFile,DefTarget);
      }
     break;

     case 2 :
      {
       if( NoDefFile() )
         return usage();
       else
         return Main(pcap,DefFile,argv[1]);
      }
     break;

     case 3 :
      {
       return Main(pcap,argv[2],argv[1]);
      }
     break;

     default:
      {
       return usage();
      }
    }
 }

int main(int argc,const char **argv)
 {
  try
    {
     ReportException report;

     int ret=inner_main(argc,argv);

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

