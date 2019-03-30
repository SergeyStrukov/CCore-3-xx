/* test4035.SysSpawn.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/PrintError.h>

#include <CCore/inc/SpawnProcess.h>

namespace App {

namespace Private_4035 {

/* test1() */

bool test1()
 {
  ShellPath shell;

  StrLen exe_name=shell.get();

  Printf(Con,"shell = #.q;\n",exe_name);

  SplitPath split1(exe_name);
  SplitName split2(split1.path);

  SpawnProcess spawn(".."_c,exe_name);

  spawn.addArg(split2.name);

  spawn.addEnv("ABRA"_c,"CODABRA"_c);

  SpawnSlot slot;

  spawn.spawn(slot);

  int status=slot.wait();

  Printf(Con,"\nstatus = #;\n",status);

  return true;
 }

/* test2() */

bool test2()
 {
  const ulen Count = 10 ;

  SpawnSlot slots[Count];

  SpawnSet set(Count);

  for(SpawnSlot &slot : slots )
    {
     StrLen exe_name="./test.exe"_c;
     StrLen arg="3"_c;

     SpawnProcess spawn(""_c,exe_name);

     spawn.addArg(exe_name.len, [=] (char *buf) { exe_name.copyTo(buf); } );

     spawn.addArg(arg);

     spawn.addEnv("ABRA"_c,"CODABRA"_c);

     spawn.spawn(slot);

     set.add(&slot);
    }

  for(ulen count=Count; count ;)
    {
     auto result=set.wait();

     if( result.slot )
       {
        count--;

        Printf(Con,"status = #;\n",result.status);
       }
    }

  return true;
 }

/* test3() */

bool test3()
 {
  SpawnProcess spawn(".."_c,"../test.exe"_c);

  spawn.addArg("./test.exe"_c);
  spawn.addArg("10"_c);

  spawn.addArg(30, [] (char *buf) { StrLen str="some-word"_c; str.copyTo(buf); buf[str.len]=0; } );

  spawn.addEnv("ABRA"_c,"CODABRA"_c);

  SpawnSlot slot;

  spawn.spawn(slot);

  int status=slot.wait();

  Printf(Con,"\nstatus = #;\n",status);

  return true;
 }

} // namespace Private_4035

using namespace Private_4035;

/* Testit<4035> */

template<>
const char *const Testit<4035>::Name="Test4035 SysSpawn";

template<>
bool Testit<4035>::Main()
 {
  //return test1();

  //return test2();

  return test3();
 }

} // namespace App

