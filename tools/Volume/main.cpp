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

#include <CCore/inc/RawFileToRead.h>
#include <CCore/inc/Volume.h>

#include <CCore/inc/DirTreeRun.h>
#include <CCore/inc/ElementPool.h>

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

void List(StrLen file_name)
 {
  Printf(Con,"list #.q;\n\n",file_name);

  Volume<AltFileToRead> vol(file_name);

  for(ulen i=0,count=vol.getCount(); i<count ;i++)
    {
     Printf(Con,"#;\n",vol.getName(i));
    }
 }

/* Pack() */

class Proc : NoCopy
 {
   struct Rec
    {
     StrLen file_path;
     StrLen file_name;
    };

  private:

   ulen off = 0 ;

   ElementPool pool;

   DynArray<Rec> files;

  public:

   Proc() {}

   ~Proc() {}

   PtrLen<const Rec> getList() const { return Range(files); }

   // proc interface

   using DataType = void ;

   DataType * dir(StrLen root)
    {
     off=root.len+2;

     return 0;
    }

   DataType * dir(StrLen,StrLen,DataType *) { return 0; }

   void file(StrLen path,StrLen name,DataType *)
    {
     StrLen file_path=pool.cat(path,"/"_c,name);
     StrLen file_name=pool.cat(path.part(off),"/"_c,name);

     files.append_copy({file_path,file_name});
    }

   void enddir(StrLen,StrLen,DataType *) {}
 };

void Pack(StrLen dir_name,StrLen file_name)
 {
  Printf(Con,"pack #.q; -> #.q;\n\n",dir_name,file_name);

  Proc proc;
  DirTreeRun run(dir_name);

  run.apply(proc);

  for(auto r : proc.getList() )
    {
     Printf(Con,"#; : #;\n",r.file_path,r.file_name);
    }
 }

/* Unpack() */

void Unpack(StrLen file_name,StrLen dir_name) // TODO
 {
  Printf(Con,"unpack #.q; -> #.q;\n\n",file_name,dir_name);

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

