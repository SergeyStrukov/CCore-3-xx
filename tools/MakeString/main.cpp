/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: MakeString 1.00
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

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/CharProp.h>

namespace App {

/* using */

using namespace CCore;

/* functions */

inline bool IsEOL(char ch)
 {
  return ch=='\n' || ch=='\r' ;
 }

/* class Strip */

class Strip : NoCopy
 {
   StrLen input;

   char ch = 0 ;
   bool ok = true ;

  private:

   static StrLen SkipShortComment(StrLen input)
    {
     input+=2;

     for(; +input && !IsEOL(*input) ;++input);

     return input;
    }

   static StrLen SkipLongComment(StrLen input)
    {
     input+=2;

     for(; input.len>=2 ;++input)
       {
        if( input[0]=='*' && input[1]=='/' )
          {
           input+=2;

           return input;
          }
       }

     return Null;
    }

   void next()
    {
     if( !input )
       {
        ok=false;
       }
     else
       {
        if( input.len>=2 && input[0]=='/' )
          {
           switch( input[1] )
             {
              case '/' :
               {
                ch=' ';

                input=SkipShortComment(input);
               }
              return;

              case '*' :
               {
                ch=' ';

                input=SkipLongComment(input);
               }
              return;
             }
          }

        ch=*input;

        ++input;
       }
    }

  public:

   explicit Strip(StrLen input_) : input(input_) { next(); }

   bool operator + () const { return ok; }

   bool operator ! () const { return !ok; }

   char operator * () const { return ch; }

   void operator ++ () { next(); }
 };

/* class Line */

class Line : NoCopy
 {
   Strip input;

   char ch = 0 ;
   bool ok = true ;
   bool need_eol = false ;

  private:

   template <class T>
   static void SkipEOL(char ch,T &cur)
    {
     ++cur;

     if( ch=='\r' && (*cur)=='\n' ) ++cur;
    }

   void next()
    {
     if( !input )
       {
        if( need_eol )
          {
           this->ch='\n';

           need_eol=false;
          }
        else
          {
           ok=false;
          }
       }
     else
       {
        char ch=*input;

        if( IsEOL(ch) )
          {
           this->ch='\n';

           SkipEOL(ch,input);

           need_eol=false;
          }
        else
          {
           this->ch=ch;

           ++input;

           need_eol=true;
          }
       }
    }

  public:

   explicit Line(StrLen input_) : input(input_) { next(); }

   bool operator + () const { return ok; }

   bool operator ! () const { return !ok; }

   char operator * () const { return ch; }

   void operator ++ () { next(); }
 };

/* PrintChar() */

void PrintChar(PrinterType &out,char ch)
 {
  if( CharIsPrintable(ch) )
    {
     switch( ch )
       {
        case '"' :
        case '\\' :
         {
          out.put('\\');
          out.put(ch);
         }
        break;

        default:
         {
          out.put(ch);
         }
       }
    }
  else
    {
     out.put(' ');
    }
 }

/* ProcStrip() */

void ProcStrip(StrLen input_file_name,StrLen output_file_name)
 {
  Printf(Con,"#.q; -> #.q; strip comments\n\n",input_file_name,output_file_name);

  FileToMem input_file(input_file_name);
  StrLen input=Mutate<const char>(Range(input_file));
  PrintFile out(output_file_name,Open_ToWrite|Open_AutoDelete);

  Line line(input);

  for(; +line ;++line)
    {
     Putch(out,'"');

     for(char ch; (ch=*line)!='\n' ;++line) PrintChar(out,ch);

     Putobj(out,"\\n\"\n"_c);
    }

  out.preserveFile();
 }

/* Proc() */

void Proc(StrLen input_file_name,StrLen output_file_name)
 {
  Printf(Con,"#.q; -> #.q;\n\n",input_file_name,output_file_name);

  FileToMem input_file(input_file_name);
  StrLen input=Mutate<const char>(Range(input_file));
  PrintFile out(output_file_name,Open_ToWrite|Open_AutoDelete);

  while( +input )
    {
     StrLen line=CutLine(input);

     Putch(out,'"');

     for(char ch : line ) PrintChar(out,ch);

     Putobj(out,"\\n\"\n"_c);
    }

  out.preserveFile();
 }

/* Main() */

int Main(int argc,const char *argv[])
 {
  switch( argc )
    {
     case 1 :
      {
       Putobj(Con,"Usage: CCore-MakeString <input-file> <output-file>\n");
       Putobj(Con,"OR     CCore-MakeString -s <input-file> <output-file>\n\n");
      }
     return 1;

     case 3 :
      {
       Proc(argv[1],argv[2]);
      }
     break;

     case 4 :
      {
       StrLen opt(argv[1]);

       if( opt.equal("-s"_c) )
         {
          ProcStrip(argv[2],argv[3]);
         }
       else
         {
          Printf(Exception,"App::Main(...) : bad option");
         }
      }
     break;

     default:
      {
       Printf(Exception,"App::Main(...) : bad arguments number");
      }
    }

  return 0;
 }

} // namespace App

/* main() */

using namespace App;

int main(int argc,const char *argv[])
 {
  try
    {
     ReportException report;
     int ret;

     {
      Putobj(Con,"--- MakeString 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

      ret=Main(argc,argv);
     }

     report.guard();

     return ret;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

