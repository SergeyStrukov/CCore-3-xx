/* test6009.KeySym.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Target/LIN64utf8
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2016 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Scan.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/CharProp.h>

namespace App {

namespace Private_6009 {

class Line : NoCopy
 {
   PrintFile out;

   static const char *Pattern;

   const char *pat = Pattern ;
   bool ok = true ;

   PrintString name;
   PrintString value;
   PrintString comment;

   bool flag = false ;

   ulen line = 1 ;

   ulen legacy = 0 ;
   ulen standard = 0 ;

  private:

   void process(String name,uint32 val,uint32 unicode)
    {
     Used(name);

     if( val == unicode + 0x100'0000 || ( unicode<0x100 && val==unicode ) )
       {
        standard++;
       }
     else
       {
        legacy++;

        Printf(out,"     case #6.xi; : return #6.xi;;\n",val,unicode);
       }
    }

   void process(String name,String value,String comment)
    {
     uint32 val;

     {
      ScanString inp(Range(value));

      Scanf(inp,"#;",val);

      if( inp.isFailed() )
        {
         //Printf(Con,"#.q;\n",value);

         return;
        }
     }

     uint32 unicode;

     {
      ScanString inp(Range(comment));

      Scanf(inp," U+#.16;",unicode);

      if( inp.isFailed() )
        {
         //Printf(Con,"#.q;\n",comment);

         return;
        }
     }

     process(name,val,unicode);
    }

  public:

   Line()
    : out("keysym.txt")
    {
    }

   ~Line()
    {
    }

   void begin()
    {
     Printf(out,"uint32 X11KeyMap::MapToUnicode(KeySym ksym)\n");
     Printf(out," {\n");
     Printf(out,"  switch( ksym )\n");
     Printf(out,"    {\n");
    }

   void start()
    {
     pat=Pattern;
     ok=true;

     name.cleanup();
     value.cleanup();
     comment.cleanup();

     Putobj(name,"XK_");

     flag=false;
    }

   void next(char ch)
    {
     if( !ok ) return;

     switch( char pch=*pat )
       {
        case 0 :
         {
          ok=false;
         }
        break;

        case '@' :
         {
          if( CharIsSpace(ch) )
            {
             pat++;
            }
          else
            {
             name.put(ch);
            }
         }
        break;

        case '$' :
         {
          if( CharIsSpace(ch) )
            {
             pat++;
            }
          else if( ch=='/' )
            {
             pat++;

             next(ch);
            }
          else
            {
             value.put(ch);
            }
         }
        break;

        case '%' :
         {
          if( flag )
            {
             if( ch=='/' )
               {
                pat++;

                break;
               }
             else
               {
                comment.put('*');
               }
            }

          if( ch=='*' )
            {
             flag=true;
            }
          else
            {
             flag=false;

             comment.put(ch);
            }
         }
        break;

        case '?' :
         {
          if( !CharIsSpace(ch) )
            {
             pat++;

             next(ch);
            }
         }
        break;

        default:
         {
          if( ch==pch )
            {
             pat++;
            }
          else
            {
             ok=false;
            }
         }
       }
    }

   void stop()
    {
     if( pat[0] && pat[1] ) ok=false;

     if( ok )
       {
        process(name.close(),value.close(),comment.close());
       }

     line++;
    }

   void end()
    {
     Printf(out,"    }\n\n");

     Printf(out,"  if( ksym<0x100 ) return ksym;\n\n");

     Printf(out,"  if( ksym>=0x1000000 && ksym<0x1010000 ) return ksym-0x1000000;\n\n");

     Printf(out,"  return 0;\n");
     Printf(out," }\n\n");

     Printf(Con,"legacy = #; standard = #;\n",legacy,standard);
    }
 };

const char *Line::Pattern="?#?define ?XK_@?$?/*%?";

} // namespace Private_6009

using namespace Private_6009;

/* Testit<6009> */

template<>
const char *const Testit<6009>::Name="Test6009 KeySym";

template<>
bool Testit<6009>::Main()
 {
  ScanFile inp("/usr/include/X11/keysymdef.h");
  Line line;

  line.begin();

  line.start();

  for(; +inp ;++inp)
    {
     char ch=*inp;

     if( ch=='\n' )
       {
        line.stop();
        line.start();
       }
     else
       {
        line.next(ch);
       }
    }

  line.stop();

  line.end();

  return true;
 }

} // namespace App

