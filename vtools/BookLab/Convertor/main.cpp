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
           "p","/p",
           "b","/b",
           "i","/i",
           "a","/a",
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
           case 11 :
            {
             Scanf(inp," href = #.q; >",param);
            }
           break;

           case 13 :
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

           case 5 : return step( proc.tagP() );
           case 6 : return step( proc.tagPend() );

           case 7 : return step( proc.tagB() );
           case 8 : return step( proc.tagBend() );

           case 9 : return step( proc.tagI() );
           case 10 : return step( proc.tagIend() );

           case 11 : return step( proc.tagA(param) );
           case 12 : return step( proc.tagAend() );

           case 13 : return step( proc.tagImg(param) );

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

/* class TestProc */

class TestProc
 {
  public:

   bool word(String word) { Printf(Con,"  #;\n",word); return true; }

   bool tagH1() { Printf(Con,"H1\n"); return true; }
   bool tagH1end() { Printf(Con,"/H1\n"); return true; }

   bool tagH2() { Printf(Con,"H2\n"); return true; }
   bool tagH2end() { Printf(Con,"/H2\n"); return true; }

   bool tagP() { Printf(Con,"P\n"); return true; }
   bool tagPend() { Printf(Con,"/P\n"); return true; }

   bool tagB() { Printf(Con,"B\n"); return true; }
   bool tagBend() { Printf(Con,"/B\n"); return true; }

   bool tagI() { Printf(Con,"I\n"); return true; }
   bool tagIend() { Printf(Con,"/I\n"); return true; }

   bool tagA(String url) { Printf(Con,"A #.q;\n",url); return true; }
   bool tagAend() { Printf(Con,"/A\n"); return true; }

   bool tagImg(String file_name) { Printf(Con,"Img #.q;\n",file_name); return true; }

   bool complete() { return true; }
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
     TagP,

     TagB,
     TagI,
     TagA
    };

   State state = Start ;

   ulen ind = 1 ;
   bool first = true ;

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

        case TagP : wordP(word); return true;

        case TagB : wordB(word); return true;

        case TagI : wordI(word); return true;

        case TagA : wordA(word); return true;
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
     if( state==TagP )
       {
        startA(url);

        state=TagA;

        return true;
       }

     return false;
    }

   bool tagAend()
    {
     if( state==TagA )
       {
        endA();

        state=TagP;

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

#if 1

  Convert convert(output_file_name);

  src.run(convert);

#else

  TestProc test;

  src.run(test);

#endif
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

