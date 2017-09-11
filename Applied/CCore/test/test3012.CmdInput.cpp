/* test3012.CmdInput.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/CmdInput.h>
#include <CCore/inc/ReadCon.h>

namespace App {

namespace Private_3012 {

/* class Target */

class Target : public NoCopyBase<CmdInput::Target>
 {
   bool run_flag;

  private:

   void empty(StrLen) {}

   void help(StrLen arg) { Printf(Con,"help #.q;\n",arg); }

   void stop(StrLen arg) { Printf(Con,"stop #.q;\n",arg); }

   void stat(StrLen arg) { Printf(Con,"stat #.q;\n",arg); }

   void stat_ip(StrLen arg) { Printf(Con,"stat_ip #.q;\n",arg); }

   void exit(StrLen arg) { Printf(Con,"exit #.q;\n",arg); run_flag=false; }

   void exec(StrLen arg) { Printf(Con,"exec #.q;\n",arg); }

   virtual void buildCmdList(CmdInput &input)
    {
     addCommand(input,"",&Target::empty);
     addCommand(input,"help",&Target::help);
#ifdef CCORE_UTF8
     addCommand(input,"стоп",&Target::stop);
#else
     addCommand(input,"stop",&Target::stop);
#endif
     addCommand(input,"stat",&Target::stat);
     addCommand(input,"stat_ip",&Target::stat_ip);
     addCommand(input,"exit",&Target::exit);
     addCommand(input,"exec",&Target::exec);
    }

  public:

   Target() : run_flag(true) {}

   ~Target() {}

   bool operator + () const { return run_flag; }

   bool operator ! () const { return !run_flag; }
 };

/* class Test */

class Test : NoCopy
 {
   Target target;

   CmdInputCon<ReadCon> input;

  public:

   Test()
    : input(target,"test> ")
    {
    }

   ~Test()
    {
    }

   void run()
    {
     while( +target )
       {
        input.command();
       }
    }
 };

} // namespace Private_3012

using namespace Private_3012;

/* Testit<3012> */

template<>
const char *const Testit<3012>::Name="Test3012 CmdInput";

template<>
bool Testit<3012>::Main()
 {
  Test test;

  test.run();

  return true;
 }

} // namespace App
