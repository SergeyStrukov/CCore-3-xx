/* test4013.DirTreeRun.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/DirTreeRun.h>
#include <CCore/inc/ElementPool.h>

namespace App {

namespace Private_4013 {

/* class Proc */

class Proc : NoCopy
 {
   PrintFile out;
   ulen off;

   ElementPool pool;
   int next;

  private:

   int getNext() { return next++; }

  public:

   Proc() : out("test4013.txt"),off(0),next(0) {}

   ~Proc() {}

   using DataType = int ;

   DataType * dir(StrLen root)
    {
     Printf(out,"path = #;\ndir = .\n",root);

     off=3;

     return pool.create<int>(getNext());
    }

   DataType * dir(StrLen path,StrLen name,DataType *parent)
    {
     RepeatChar rep(off,' ');

     Printf(out,"#;path = #;\n#;number = #;\n#;dir = #;\n",rep,path,rep,*parent,rep,name);

     off+=3;

     return pool.create<int>(getNext());
    }

   void file(StrLen path,StrLen name,DataType *parent)
    {
     RepeatChar rep(off,' ');

     Printf(out,"#;path = #;\n#;number = #;\n#;file = #;\n#;-----\n",rep,path,rep,*parent,rep,name,rep);
    }

   void enddir(StrLen path,StrLen name,DataType *parent)
    {
     off-=3;

     RepeatChar rep(off,' ');

     Printf(out,"#;path = #;\n#;enddir = #;\n#;number = #;\n#;=====\n",rep,path,rep,name,rep,*parent,rep);
    }
 };

} // namespace Private_4013

using namespace Private_4013;

/* Testit<4013> */

template<>
const char *const Testit<4013>::Name="Test4013 DirTreeRun";

template<>
bool Testit<4013>::Main()
 {
  Proc proc;
  DirTreeRun run("../CCore"_c);

  run.apply(proc);

  return true;
 }

} // namespace App

