/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: VMakeDep 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Scan.h>
#include <CCore/inc/Exception.h>

namespace App {

/* using */

using namespace CCore;

/* Main() */

int Main(StrLen src_file_name,StrLen dst_file_name,StrLen ind)
 {
  ScanFile inp(src_file_name);
  PrintFile out(dst_file_name,Open_ToWrite|Open_AutoDelete);

  String target;

  Scanf(inp,"#.s;",target);

  ulen n=1;

  for(;;)
    {
     String text;

     Scanf(inp," #.s;",text);

     if( text.isEmpty() ) break;

     StrLen t=Range(text);

     if( t.equal("\\"_c) ) continue;

     Printf(out,"Target inc#;_#; = { \"#;\" , \"#;\" } ;\n\n",ind,n++,text,text);
    }

  {
   StrLen t=Range(target);

   if( t.len<2 || t.back(1)!=':' ) return 1;

   t.len--;

   Printf(out,"Dep dep#; = { {",ind);

   for(ulen i=1; i<n ;i++)
     {
      if( i==1 ) Putobj(out,"\n "_c); else Putobj(out,"\n,"_c);

      Printf(out,"&inc#;_#;",ind,i);
     }

   Printf(out,"\n} , {&ocpp#;} } ;",ind);
  }

  out.preserveFile();

  return 0;
 }

} // namespace App

/* main() */

using namespace App;

int usage()
 {
  Putobj(Con,"Usage: CCore-VMakeDep <src-file-name> <dst-file-name> <index>\n");

  return 1;
 }

int main(int argc,const char * argv[])
 {
  try
    {
     ReportException report;

     int ret=0;

     {
      Putobj(Con,"--- VMakeDep 1.00 ---\n--- Copyright (c) 2019 Sergey Strukov. All rights reserved. ---\n\n");

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

