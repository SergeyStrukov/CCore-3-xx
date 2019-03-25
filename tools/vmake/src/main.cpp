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

/* class Main */

class Main : NoCopy
 {
   unsigned pcap = 0 ;
   StrLen file_name = "default.vm.ddl"_c ;
   StrLen target = "main"_c ;

   bool ok = false ;

   VMake::FileProc file_proc;

  private:

   static int Usage()
    {
     Putobj(Con,"Usage: vmake [-pNNN]\n");
     Putobj(Con,"OR     vmake [-pNNN] <target>\n");
     Putobj(Con,"OR     vmake [-pNNN] <target> <vmake-file>\n\n");

     return 1;
    }

   static bool IsOpt(const char *str) { return *str=='-' ; }

   bool getP(StrLen arg)
    {
     ScanString inp(arg);

     Scanf(inp,"-p#;#;",pcap,EndOfScan);

     return inp.isOk();
    }

  public:

   Main(int argc,const char **argv)
    {
     if( argc<1 ) return;

     auto list=Range(argv+1,argc-1);

     if( +list && IsOpt(*list) )
       {
        if( !getP(*list) ) return;

        ++list;
       }

     if( +list )
       {
        target=*list;

        ++list;
       }

     if( +list )
       {
        file_name=*list;

        ++list;
       }

     if( +list ) return;

     if( !file_proc.checkExist(""_c,file_name) )
       {
        Printf(Con,"#.q; does not exist\n\n",file_name);

        return;
       }

     ok=true;
    }

   int run()
    {
     if( !ok ) return Usage();

     if( pcap )
       Printf(Con,"#; @ #; -p #;\n\n",file_name,target,pcap);
     else
       Printf(Con,"#; @ #;\n\n",file_name,target);

     file_proc.prepare(pcap);

     VMake::DataProc proc(file_proc,file_name,target);

     return proc.make();
    }
 };

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char **argv)
 {
  try
    {
     ReportException report;

     Putobj(Con,"--- vmake 1.00 ---\n--- Copyright (c) 2019 Sergey Strukov. All rights reserved. ---\n\n"_c);

     Main obj(argc,argv);

     int ret=obj.run();

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

