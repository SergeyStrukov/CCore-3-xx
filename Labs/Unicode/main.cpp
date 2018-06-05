/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/Unicode
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

#include <CCore/inc/video/Desktop.h>

namespace App {

/* using */

using namespace CCore;

/* Main() */

void Main()
 {
  const ulen Len = 0x11'0000 ;

  // table

  PrintFile out("table.txt");

  SimpleArray<Char> table(Len);

  ulen count=0;
  bool skip = false ;

  for(ulen i=0; i<Len ;i++)
    {
     Char ch(i);
     Char lch=Video::ToLowerCase(ch);

     table[i]=lch;

     if( ch!=lch ) count++;

     if( ch!=lch )
       {
        Printf(out,"#; -> #; : #;\n",ch,lch,(int)lch-(int)ch);

        skip=false;
       }
     else
       {
        if( Change(skip,true) ) Printf(out,"#;\n",ch);
       }
    }

  Printf(Con,"count = #;\n",count);
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  try
    {
     ReportException report;

     Main();

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

