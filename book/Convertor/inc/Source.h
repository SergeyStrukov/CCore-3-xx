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

#include <inc/ErrorId.h>
#include <inc/PrintPage.h>

#include <CCore/inc/Print.h>
#include <CCore/inc/Scan.h>

namespace App {

/* classes */

class SourceErrorId;

class Source;

class TestConvert;

class LogConvert;

/* class SourceErrorId */

enum SourceErrorCode
 {
  UnknownTag = 1,
  BadTagText,
  BrokenTitle
 };

class SourceErrorId : public ErrorId
 {
   static StrLen Func(int code);

  public:

   SourceErrorId(SourceErrorCode code) : ErrorId(code,Func) {}
 };

/* class Source */

class Source : NoCopy
 {
   ScanFile inp;
   ErrorId err;

   StringSetScan tags;

   StringSetScan atype;
   StringSetScan ptype;

   bool probe_title = true ;
   bool body_on = false ;

  private:

   static bool CharStop(char ch) { return ch=='<' ; }

   static bool ProbeStr(CharStreamType &inp,StrLen str)
    {
     for(char ch : str )
       {
        if( !ProbeChar(inp,ch) ) return false;
       }

     return true;
    }

   static bool ProbeClose(CharStreamType &inp)
    {
     SkipSpace(inp);

     return ProbeChar(inp,'>');
    }

   bool step(ErrorId err_)
    {
     if( +err ) return false;

     if( !err_ ) return true;

     inp.fail();
     err=err_;

     return false;
    }

   bool step(SourceErrorCode code) { return step(SourceErrorId(code)); }

   bool step(bool ok)
    {
     return step(ErrorId(ok));
    }

   template <class Proc>
   bool setTitle(Proc &proc)
    {
     PrintString out;

     for(; +inp ;++inp)
       {
        char ch=*inp;

        if( ch=='<' )
          {
           if( ProbeStr(inp,"</title>"_c) )
             {
              proc.setTitle(out.close());

              return true;
             }
           else
             {
              return step(BrokenTitle);
             }
          }
        else
          {
           out.put(ch);
          }
       }

     return step(BrokenTitle);
    }

   template <class Proc>
   bool nextBody(Proc &proc)
    {
     if( ProbeChar(inp,'<') )
       {
        Scanf(inp," #;",tags);

        if( inp.isFailed() ) return step(UnknownTag);

        String type;
        String param;
        bool has_param=false;

        switch( tags )
          {
           case 1 :
           case 3 :
           case 5 :
           case 7 :
           case 9 :
           case 25 :
            {
             if( !ProbeClose(inp) )
               {
                String id;

                Scanf(inp," id = #.q; >",id);

                proc.setId(id);
               }
            }
           break;

           case 11 : // <p
            {
             if( !ProbeClose(inp) )
               {
                Scanf(inp," #; = #.q;",ptype,param);

                if( ptype==2 )
                  {
                   proc.setId(param);

                   Scanf(inp," >");
                  }
                else
                  {
                   has_param=true;

                   if( !ProbeClose(inp) )
                     {
                      String id;

                      Scanf(inp," id = #.q; >",id);

                      proc.setId(id);
                     }
                  }
               }
            }
           break;

           case 17 : // <a
            {
             Scanf(inp," #; = #.q;",atype,param);

             if( atype==2 )
               {
                type=param;

                Scanf(inp," href = #.q; >",param);
               }
             else
               {
                Scanf(inp," >");
               }
            }
           break;

           case 19 : // <ol
            {
             if( !ProbeClose(inp) )
               {
                Scanf(inp," class = #.q; >",param);

                has_param=true;
               }
            }
           break;

           case 23 : // <img
            {
             Scanf(inp," src = #.q; />",param);
            }
           break;

           case 27 : // <span
            {
             Scanf(inp," class = #.q; >",param);
            }
           break;

           default:
            {
             Scanf(inp," >");
            }
          }

        if( inp.isFailed() ) return step(BadTagText);

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

           case 11 :
            {
             if( has_param )
               {
                return step( proc.tagP(param) );
               }
             else
               {
                return step( proc.tagP() );
               }
            }
           break;

           case 12 : return step( proc.tagPend() );

           case 13 : return step( proc.tagB() );
           case 14 : return step( proc.tagBend() );

           case 15 : return step( proc.tagI() );
           case 16 : return step( proc.tagIend() );

           case 17 :
            {
             switch( atype )
              {
               case 1 : return step( proc.tagA(param) );
               case 2 : return step( proc.tagA(type,param) );
              }

             return false;
            }
           break;

           case 18 : return step( proc.tagAend() );

           case 19 : return step( proc.tagOL() );
           case 20 : return step( proc.tagOLend() );

           case 21 : return step( proc.tagLI() );
           case 22 : return step( proc.tagLIend() );

           case 23 : return step( proc.tagImg(param) );

           case 24 : body_on=false; return true;

           case 25 : return step( proc.tagPRE() );
           case 26 : return step( proc.tagPREend() );

           case 27 : return step( proc.tagSPAN(param) );
           case 28 : return step( proc.tagSPANend() );

           case 29 : return step( proc.tagSUB() );
           case 30 : return step( proc.tagSUBend() );

           case 31 : return step( proc.tagSUP() );
           case 32 : return step( proc.tagSUPend() );

           case 33 : return step( proc.tagUL() );
           case 34 : return step( proc.tagULend() );

           case 35 : return step( proc.tagU() );
           case 36 : return step( proc.tagUend() );

           default: return step(UnknownTag);
          }
       }
     else
       {
        TransformInput dev;

        for(char ch; +inp && !CharStop(ch=*inp) ;++inp) dev.put(ch);

        return step( proc.frame(dev.close()) );
       }
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
           "img","/body",
           "pre","/pre",
           "span","/span",
           "sub","/sub",
           "sup","/sup",
           "ul","/ul",
           "u","/u"},

      atype{"href","type"},

      ptype{"class","id"}
    {
    }

   ~Source() {}

   template <class Proc>
   bool next(Proc &proc)
    {
     if( !inp ) return false;

     if( body_on )
       {
        return nextBody(proc);
       }
     else
       {
        if( probe_title )
          {
           if( ProbeStr(inp,"<title>"_c) )
             {
              probe_title=false;

              return setTitle(proc);
             }
           else
             {
              ++inp;

              return true;
             }
          }
        else
          {
           if( ProbeStr(inp,"<body>"_c) )
             {
              body_on=true;

              return true;
             }
           else
             {
              ++inp;

              return true;
             }
          }
       }
    }

   template <class Proc>
   bool run(Proc &proc)
    {
     while( next(proc) );

     step( proc.complete() );

     if( inp.isFailed() )
       {
        if( +err )
          Printf(Con,"Failed at #; : #;\n",inp.getTextPos(),err);
        else
          Printf(Con,"Failed at #; : scanning failed\n",inp.getTextPos());

        return false;
       }
     else
       {
        return true;
       }
    }
 };

/* class TestConvert */

class TestConvert
 {
  public:

   TestConvert() {}

   explicit TestConvert(StrLen output_file_name) { Used(output_file_name); }

   // title

   void setTitle(String) {}

   // id

   void setId(String) {}

   // frame

   bool frame(String str);

   // text

   bool tagH1();

   bool tagH1end();

   bool tagH2();

   bool tagH2end();

   bool tagH3();

   bool tagH3end();

   bool tagH4();

   bool tagH4end();

   bool tagH5();

   bool tagH5end();

   bool tagP();

   bool tagP(String tclass);

   bool tagPend();

   bool tagPRE();

   bool tagPREend();

   // format

   bool tagB();

   bool tagBend();

   bool tagI();

   bool tagIend();

   bool tagU();

   bool tagUend();

   bool tagSUB();

   bool tagSUBend();

   bool tagSUP();

   bool tagSUPend();

   bool tagSPAN(String tclass);

   bool tagSPANend();

   // hyperlink

   bool tagA(String url);

   bool tagA(String type,String url);

   bool tagAend();

   // list

   bool tagOL();

   bool tagOLend();

   bool tagUL();

   bool tagULend();

   bool tagLI();

   bool tagLIend();

   // image

   bool tagImg(String file_name);

   // complete

   bool complete();
 };

/* class LogConvert */

class LogConvert
 {
   PrintFile out;

  public:

   explicit LogConvert(StrLen output_file_name) : out(output_file_name) {}

   // title

   void setTitle(String) {}

   // id

   void setId(String id);

   // frame

   bool frame(String str);

   // text

   bool tagH1();

   bool tagH1end();

   bool tagH2();

   bool tagH2end();

   bool tagH3();

   bool tagH3end();

   bool tagH4();

   bool tagH4end();

   bool tagH5();

   bool tagH5end();

   bool tagP();

   bool tagP(String tclass);

   bool tagPend();

   bool tagPRE();

   bool tagPREend();

   // format

   bool tagB();

   bool tagBend();

   bool tagI();

   bool tagIend();

   bool tagU();

   bool tagUend();

   bool tagSUB();

   bool tagSUBend();

   bool tagSUP();

   bool tagSUPend();

   bool tagSPAN(String tclass);

   bool tagSPANend();

   // hyperlink

   bool tagA(String url);

   bool tagA(String type,String url);

   bool tagAend();

   // list

   bool tagOL();

   bool tagOLend();

   bool tagUL();

   bool tagULend();

   bool tagLI();

   bool tagLIend();

   // image

   bool tagImg(String file_name);

   // complete

   bool complete();
 };

} // namespace App

#endif
