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
#include <CCore/inc/Path.h>

#include <CCore/inc/video/PrintDDL.h>

namespace App {

/* using */

using namespace CCore;

using Video::DDLString;
using Video::DDLPrintableString;

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

/* class Convert */

class Convert : NoCopy
 {
   String name;

   PrintFile out;

   enum State
    {
     Start = 0,

     TagH1,
     TagH2,
     TagH3,
     TagH4,
     TagH5,
     TagP,

     TagB,
     TagI,
     TagA,

     TagOL,
     TagLI
    };

   State state = Start ;
   unsigned level = 0 ;

   ulen ind = 1 ;
   bool first = true ;

   State parent = Start ;

   unsigned number[10];

  private:

   void start()
    {
     Printf(out,"/* #;.book.ddl */\n\n",name);

     Printf(out,"include <#;.style.ddl>\n\n",name);

     Putobj(out,"scope Pages {\n\n");
    }

   // H1

   void startH1()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH1(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH1()
    {
     Putobj(out,"} , &fmt_h1 , &align_h1 } ;\n\n");
    }

   // H2

   void startH2()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH2(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH2()
    {
     Putobj(out,"} , &fmt_h2 , &align_h2 } ;\n\n");
    }

   // H3

   void startH3()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH3(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH3()
    {
     Putobj(out,"} , &fmt_h3 , &align_h3 } ;\n\n");
    }

   // H4

   void startH4()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH4(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH4()
    {
     Putobj(out,"} , &fmt_h4 , &align_h4 } ;\n\n");
    }

   // H5

   void startH5()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordH5(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endH5()
    {
     Putobj(out,"} , &fmt_h5 , &align_h5 } ;\n\n");
    }

   // P

   void startP()
    {
     Printf(out,"Text text#; = { {\n",ind++);

     first=true;
    }

   void wordP(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;}\n",DDLString(word));
       }
    }

   void endP()
    {
     Putobj(out,"} } ;\n\n");
    }

   // B

   void startB() {}

   void wordB(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;,&fmt_b}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;,&fmt_b}\n",DDLString(word));
       }
    }

   void endB() {}

   // I

   void startI() {}

   void wordI(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;,&fmt_i}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;,&fmt_i}\n",DDLString(word));
       }
    }

   void endI() {}

   // A

   void startA(String url) { Used(url); }

   void wordA(String word)
    {
     if( Change(first,false) )
       {
        Printf(out,"{#;,&fmt_u}\n",DDLString(word));
       }
     else
       {
        Printf(out,",{#;,&fmt_u}\n",DDLString(word));
       }
    }

   void endA() {}

   // OL

   void startOL()
    {
     Printf(out,"TextList text#; = { {\n",ind++);

     number[level]=1;
    }

   void endOL()
    {
     Putobj(out,"} } ;\n\n");
    }

   // LI

   void startLI()
    {
     unsigned num=number[level]++;

     if( num==1 )
       {
        Printf(out,"{'#;.',{",num);
       }
     else
       {
        Printf(out,",{'#;.',{",num);
       }
    }

   void wordLI(String word)
    {
    }

   void endLI()
    {
     Putobj(out,"}}\n");
    }

   // Img

   void makeImg(String file_name) { makeImg(Range(file_name)); }

   void makeImg(StrLen file_name)
    {
     SplitPath split1(file_name);
     SplitName split2(split1.path);
     SplitExt split3(split2.name);

     file_name.len-=split3.ext.len;

     Printf(out,"Bitmap text#; = { ",ind++);

     Printf(out,"#; + '.bitmap' ",DDLPrintableString(file_name));

     Putobj(out," };\n\n");
    }

  public:

   explicit Convert(StrLen output_file_name)
    : out(output_file_name)
    {
     SplitPath split1(output_file_name);
     SplitName split2(split1.path);
     SplitFullExt split3(split2.name);

     name=String(split3.name);

     start();
    }

   ~Convert() {}

   bool word(String word)
    {
     switch( state )
       {
        case TagH1 : wordH1(word); return true;

        case TagH2 : wordH2(word); return true;

        case TagH3 : wordH3(word); return true;

        case TagH4 : wordH4(word); return true;

        case TagH5 : wordH5(word); return true;

        case TagP : wordP(word); return true;

        case TagB : wordB(word); return true;

        case TagI : wordI(word); return true;

        case TagA : wordA(word); return true;

        case TagLI : wordLI(word); return true;
       }

     return false;
    }

   bool tagH1()
    {
     if( state==Start )
       {
        startH1();

        state=TagH1;

        return true;
       }

     return false;
    }

   bool tagH1end()
    {
     if( state==TagH1 )
       {
        endH1();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagH2()
    {
     if( state==Start )
       {
        startH2();

        state=TagH2;

        return true;
       }

     return false;
    }

   bool tagH2end()
    {
     if( state==TagH2 )
       {
        endH2();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagH3()
    {
     if( state==Start )
       {
        startH3();

        state=TagH3;

        return true;
       }

     return false;
    }

   bool tagH3end()
    {
     if( state==TagH3 )
       {
        endH3();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagH4()
    {
     if( state==Start )
       {
        startH4();

        state=TagH4;

        return true;
       }

     return false;
    }

   bool tagH4end()
    {
     if( state==TagH4 )
       {
        endH4();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagH5()
    {
     if( state==Start )
       {
        startH5();

        state=TagH5;

        return true;
       }

     return false;
    }

   bool tagH5end()
    {
     if( state==TagH5 )
       {
        endH5();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagP()
    {
     if( state==Start )
       {
        startP();

        state=TagP;

        return true;
       }

     return false;
    }

   bool tagPend()
    {
     if( state==TagP )
       {
        endP();

        state=Start;

        return true;
       }

     return false;
    }

   bool tagB()
    {
     if( state==TagP )
       {
        startB();

        state=TagB;

        return true;
       }

     return false;
    }

   bool tagBend()
    {
     if( state==TagB )
       {
        endB();

        state=TagP;

        return true;
       }

     return false;
    }

   bool tagI()
    {
     if( state==TagP )
       {
        startI();

        state=TagI;

        return true;
       }

     return false;
    }

   bool tagIend()
    {
     if( state==TagI )
       {
        endI();

        state=TagP;

        return true;
       }

     return false;
    }

   bool tagA(String url)
    {
     if( state==TagP || state==TagLI )
       {
        startA(url);

        parent=Replace(state,TagA);

        return true;
       }

     return false;
    }

   bool tagAend()
    {
     if( state==TagA )
       {
        endA();

        state=parent;

        return true;
       }

     return false;
    }

   bool tagOL()
    {
     if( state==Start || state==TagLI )
       {
        level++;

        if( level>=DimOf(number) )
          {
           return false;
          }

        startOL();

        state=TagOL;

        return true;
       }

     return false;
    }

   bool tagOLend()
    {
     if( state==TagOL && level )
       {
        endOL();

        level--;

        state=level?TagLI:Start;

        return true;
       }

     return false;
    }

   bool tagLI()
    {
     if( state==TagOL )
       {
        startLI();

        state=TagLI;

        return true;
       }

     return false;
    }

   bool tagLIend()
    {
     if( state==TagLI )
       {
        endLI();

        state=TagOL;

        return true;
       }

     return false;
    }

   bool tagImg(String file_name)
    {
     if( state==Start )
       {
        makeImg(file_name);

        return true;
       }

     return false;
    }

   bool complete()
    {
     Putobj(out,"Page page1 = { Pages#PageName , {\n");

     for(ulen i=1; i<ind ;i++)
       {
        if( i==1 )
          Printf(out,"{ &text#; }\n",i);
        else
          Printf(out,",{ &text#; }\n",i);
       }

     Putobj(out,"} };\n\n");

     Putobj(out,"} // scope Pages\n\n");

     Putobj(out,"Book Data = { Pages#BookName , {&Pages#page1} , Pages#Back , Pages#Fore } ;");

     return true;
    }
 };

/* Main() */

void Main(StrLen input_file_name,StrLen output_file_name)
 {
  Source src(input_file_name);

  Convert convert(output_file_name);

  src.run(convert);
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

