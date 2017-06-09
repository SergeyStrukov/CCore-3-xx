/* test4021.AsyncFile.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: HCore
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>
#include <CCore/test/testRun.h>
#include <CCore/test/testNet.h>

#include <CCore/inc/String.h>
#include <CCore/inc/Timer.h>

#include <CCore/inc/AsyncFileDevice.h>
#include <CCore/inc/FileToMem.h>
#include <CCore/inc/AsyncFileToMem.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/FileSystem.h>

namespace App {

namespace Private_4021 {

/* consts */

const unsigned LineCount = 1'000'000 ;
const unsigned FileCount = 10 ;

/* FillFile() */

template <class P>
void FillFile(P &out)
 {
  for(unsigned line=1; line<=LineCount ;line++)
    Printf(out,"--- #7; ---------------------------\n",line);
 }

/* class AsyncTask */

class AsyncTask
 {
   unsigned ind;
   MSec timeout;

  public:

   AsyncTask(unsigned ind_,MSec timeout_=DefaultTimeout) : ind(ind_),timeout(timeout_) {}

   String buildName() const { return Stringf("host:atest#;.txt",ind); }

   void operator () ()
    {
     String name=buildName();
     PrintAsyncFile out(Range(name),Open_ToWrite,timeout);

     //out.setLargeWriteLen(256*KByte);

     FillFile(out);

     Printf(Con,"#; done\n",name);
    }
 };

/* class SyncTask */

class SyncTask
 {
   unsigned ind;

  public:

   explicit SyncTask(unsigned ind_) : ind(ind_) {}

   String buildName() const { return Stringf("test#;.txt",ind); }

   void operator () ()
    {
     String name=buildName();
     PrintFile out(Range(name));

     FillFile(out);

     Printf(Con,"#; done\n",name);
    }
 };

/* class AsyncEngine */

class AsyncEngine : NoCopy
 {
   SecTimer timer;
   MSec timeout;

  public:

   explicit AsyncEngine(MSec timeout_=DefaultTimeout) : timeout(timeout_) {}

   ~AsyncEngine()
    {
     Printf(Con,"\nasync time = #; sec\n\n",timer.get());
    }

   void run()
    {
     RunTask run_task;

     for(unsigned i=1; i<=FileCount ;i++) run_task(AsyncTask(i,timeout));
    }
 };

/* class SyncEngine */

class SyncEngine : NoCopy
 {
   SecTimer timer;

  public:

   SyncEngine() {}

   ~SyncEngine()
    {
     Printf(Con,"\nsync time = #; sec\n\n",timer.get());
    }

   void run()
    {
     RunTask run_task;

     for(unsigned i=1; i<=FileCount ;i++) run_task(SyncTask(i));
    }
 };

} // namespace Private_4021

using namespace Private_4021;

/* Testit<4021> */

template<>
const char *const Testit<4021>::Name="Test4021 AsyncFile";

template<>
bool Testit<4021>::Main()
 {
  FileSystem fs;

  AsyncFileDevice host;

  ObjMaster host_master(host,"host");

#if 1

  {
   AsyncEngine engine;

   engine.run();
  }

  {
   SyncEngine engine;

   engine.run();
  }

  for(unsigned i=1; i<=FileCount ;i++)
    {
     String aname=AsyncTask(i).buildName();
     String sname=SyncTask(i).buildName();

     FileToMem sfile(Range(sname));
     AsyncFileToMem afile(Range(aname));

     FileToMem stemp(std::move(sfile));
     AsyncFileToMem atemp(std::move(afile));

     sfile=std::move(stemp);
     afile=std::move(atemp);

     if( !Range(sfile).equal(Range(afile)) )
       {
        Printf(Con,"difference #;\n",i);

        return false;
       }
    }

  Printf(Con,"match\n");

  {
   String aname=AsyncTask(1).buildName();

   PacketRead read(Range(aname));

   read.guard();

   Putobj(Con,read);
  }

  for(unsigned i=1; i<=FileCount ;i++)
    {
     String aname=AsyncTask(i).buildName();
     String sname=SyncTask(i).buildName();

     fs.deleteFile(Range(sname));

     SplitDevName split(Range(aname));

     fs.deleteFile(split.dev_path);
    }

#else

  {
   AsyncEngine engine(10_msec);

   engine.run();
  }

#endif

  return true;
 }

} // namespace App

