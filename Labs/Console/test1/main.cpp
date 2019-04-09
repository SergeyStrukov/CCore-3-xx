/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/Console/test1
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

#include <CCore/inc/ReadCon.h>
#include <CCore/inc/CharProp.h>

namespace App {

/* using */

using namespace CCore;

/* Main() */

void Main(const char *name)
 {
  ReadCon con;

  con.put("Type 'x' to stop\n\n");

  for(Symbol ch; ToChar(ch=con.get())!='x' ;)
    {
     Printf(Con,"#;> #;\n",name,ExtCharCode(ch));
    }

  Printf(Con,"#;> stop\n\n",name);
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char * argv[])
 {
  try
    {
     ReportException report;

     Main( (argc>1)? argv[1] : "???" );

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

