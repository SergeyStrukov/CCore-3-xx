/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Volume 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/MakeString.h>
#include <CCore/inc/Path.h>

namespace App {

/* using */

using namespace CCore;

/* class Opt */

class Opt : NoCopy
 {
  public:

   enum Command
    {
     List,
     Pack,
     Unpack
    };

   Command cmd;
   StrLen dir_name;
   StrLen file_name;

   Opt(int argc,const char *argv[])
    {
     if( argc<3 )
       {
        Printf(Exception,"App::Opt::Opt(...) : bad arguments number");
       }

     cmd=GetCommand(argv[1]);

     switch( cmd )
       {
        case List :
         {
          if( argc!=3 )
            {
             Printf(Exception,"App::Opt::Opt(...) : bad arguments number");
            }

          file_name=argv[2];
         }
        break;

        case Pack :
         {
          if( argc==3 )
            {
             dir_name=argv[2];

             file_name=makeFileName(dir_name);
            }
          else if( argc==4 )
            {
             dir_name=argv[2];
             file_name=argv[3];
            }
          else
            {
             Printf(Exception,"App::Opt::Opt(...) : bad arguments number");
            }
         }
        break;

        case Unpack :
         {
          if( argc==3 )
            {
             file_name=argv[2];

             dir_name=makeDirName(file_name);
            }
          else if( argc==4 )
            {
             file_name=argv[2];
             dir_name=argv[3];
            }
          else
            {
             Printf(Exception,"App::Opt::Opt(...) : bad arguments number");
            }
         }
        break;
       }
    }

  private:

   static Command GetCommand(StrLen str)
    {
     if( str.equal("-l"_c) ) return List;

     if( str.equal("-a"_c) ) return Pack;

     if( str.equal("-x"_c) ) return Unpack;

     Printf(Exception,"App::Opt::Opt(...) : bad command");

     return List;
    }

  private:

   MakeString<MaxPathLen> temp;

   StrLen makeFileName(StrLen dir_name)
    {
     if( !temp.add(dir_name,".vol") )
       {
        Printf(Exception,"App::Opt::Opt(...) : overflow");
       }

     return temp.get();
    }

   StrLen makeDirName(StrLen file_name)
    {
     SplitPath split1(file_name);
     SplitName split2(split1.path);
     SplitExt split3(split2.name);

     if( !split3 || split3.ext.equal("."_c) )
       {
        Printf(Exception,"App::Opt::Opt(...) : no file extension");
       }

     return file_name.inner(0,split3.ext.len);
    }
 };

/* List() */

void List(StrLen file_name) // TODO
 {
  Printf(Con,"list #.q;\n",file_name);

 }

/* Pack() */

void Pack(StrLen dir_name,StrLen file_name) // TODO
 {
  Printf(Con,"pack #.q; -> #.q;\n",dir_name,file_name);

 }

/* Unpack() */

void Unpack(StrLen file_name,StrLen dir_name) // TODO
 {
  Printf(Con,"unpack #.q; -> #.q;\n",file_name,dir_name);

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
      Putobj(Con,"--- Volume 1.00 ---\n--- Copyright (c) 2018 Sergey Strukov. All rights reserved. ---\n\n");

      Opt opt(argc,argv);

      switch( opt.cmd )
        {
         case Opt::List :
          {
           List(opt.file_name);
          }
         break;

         case Opt::Pack :
          {
           Pack(opt.dir_name,opt.file_name);
          }
         break;

         case Opt::Unpack :
          {
           Unpack(opt.file_name,opt.dir_name);
          }
         break;
        }
     }

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

