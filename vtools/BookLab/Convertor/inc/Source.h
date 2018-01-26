/* Source.h */
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

#ifndef App_Source_h
#define App_Source_h

#include <CCore/inc/Print.h>
#include <CCore/inc/Scan.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

class Source;

/* class Source */

class Source : NoCopy
 {
   ScanFile inp;

   StringSetScan tags;

  private:

   static bool CharStop(char ch)
    {
     return CharIsSpace(ch) || ch=='<' ;
    }

   bool step(bool ok)
    {
     if( ok ) return ok;

     inp.fail();

     return false;
    }

  public:

   explicit Source(StrLen input_file_name)
    : inp(input_file_name),
      tags{"h1","/h1",
           "h2","/h2",
           "h3","/h3",
           "h4","/h4",
           "h5","/h5",
           "p","/p",
           "b","/b",
           "i","/i",
           "a","/a",
           "ol","/ol",
           "li","/li",
           "img"}
    {
    }

   ~Source() {}

   template <class Proc>
   bool next(Proc &proc)
    {
     SkipSpace(inp);

     if( !inp ) return false;

     if( ProbeChar(inp,'<') )
       {
        Scanf(inp," #;",tags);

        if( !inp ) return false;

        String param;

        switch( tags )
          {
           case 17 :
            {
             Scanf(inp," href = #.q; >",param);
            }
           break;

           case 23 :
            {
             Scanf(inp," src = #.q; >",param);
            }
           break;

           default:
            {
             Scanf(inp," >");
            }
          }

        if( !inp ) return false;

        switch( tags )
          {
           case 1 : return step( proc.tagH1() );
           case 2 : return step( proc.tagH1end() );

           case 3 : return step( proc.tagH2() );
           case 4 : return step( proc.tagH2end() );

           case 5 : return step( proc.tagH3() );
           case 6 : return step( proc.tagH3end() );

           case 7 : return step( proc.tagH4() );
           case 8 : return step( proc.tagH4end() );

           case 9  : return step( proc.tagH5() );
           case 10 : return step( proc.tagH5end() );

           case 11 : return step( proc.tagP() );
           case 12 : return step( proc.tagPend() );

           case 13 : return step( proc.tagB() );
           case 14 : return step( proc.tagBend() );

           case 15 : return step( proc.tagI() );
           case 16 : return step( proc.tagIend() );

           case 17 : return step( proc.tagA(param) );
           case 18 : return step( proc.tagAend() );

           case 19 : return step( proc.tagOL() );
           case 20 : return step( proc.tagOLend() );

           case 21 : return step( proc.tagLI() );
           case 22 : return step( proc.tagLIend() );

           case 23 : return step( proc.tagImg(param) );

           default: return step(false);
          }
       }
     else
       {
        PrintString out;

        for(char ch; +inp && !CharStop(ch=*inp) ;++inp) out.put(ch);

        String word=out.close();

        if( !inp ) return false;

        return step( proc.word(word) );
       }
    }

   template <class Proc>
   void run(Proc &proc)
    {
     while( next(proc) );

     step( proc.complete() );

     if( inp.isFailed() )
       {
        Printf(Con,"Failed at #;\n",inp.getTextPos());
       }
    }
 };

} // namespace App

#endif
