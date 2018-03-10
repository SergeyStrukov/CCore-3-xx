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

namespace App {

/* using */

using namespace CCore;

/* struct Opt */

struct Opt
 {
  enum Command
   {
    List,
    Pack,
    Unpack
   };

  Command cmd;
  StrLen dir_name;
  StrLen file_name;

  Opt(int argc,const char *argv[]) // TODO
   {
   }
 };

/* List() */

void List(StrLen file_name) // TODO
 {
  Used(file_name);
 }

/* Pack() */

void Pack(StrLen dir_name,StrLen file_name) // TODO
 {
  Used(dir_name);
  Used(file_name);
 }

/* Unpack() */

void Unpack(StrLen file_name,StrLen dir_name) // TODO
 {
  Used(dir_name);
  Used(file_name);
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

