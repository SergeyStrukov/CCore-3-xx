/* test3004.Log.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Log.h>

namespace App {

namespace Private_3004 {

/* enum LogSource */

enum LogSource
 {
  LogSourceCRT,

  LogSourceTask,
  LogSourceSem,
  LogSourceMutex,
  LogSourceEvent,
  LogSourceMultiSem,

  LogSourceUserMin = 10,
  LogSourceUserMax = 31
 };

const char * GetTextDesc(LogSource src)
 {
  static const char *const Table[]=
   {
    "CRT",
    "Task",
    "Sem",
    "Mutex",
    "Event",
    "MultiSem",

    "Sys6",
    "Sys7",
    "Sys8",
    "Sys9",

    "User10",
    "User11",
    "User12",
    "User13",
    "User14",
    "User15",
    "User16",
    "User17",
    "User18",
    "User19",
    "User20",
    "User21",
    "User22",
    "User23",
    "User24",
    "User25",
    "User26",
    "User27",
    "User28",
    "User29",
    "User30",
    "User31"
   };

  return Table[src];
 }

/* enum LogType */

enum LogType
 {
  LogDebug,
  LogEvent,
  LogError,
  LogAlert,

  LogTypeUserMin = 10,
  LogTypeUserMax = 31
 };

const char * GetTextDesc(LogType type)
 {
  static const char *const Table[]=
   {
    "Debug",
    "Event",
    "Error",
    "Alert",

    "Sys4",
    "Sys5",
    "Sys6",
    "Sys7",
    "Sys8",
    "Sys9",

    "User10",
    "User11",
    "User12",
    "User13",
    "User14",
    "User15",
    "User16",
    "User17",
    "User18",
    "User19",
    "User20",
    "User21",
    "User22",
    "User23",
    "User24",
    "User25",
    "User26",
    "User27",
    "User28",
    "User29",
    "User30",
    "User31"
   };

  return Table[type];
 }

/* Log */

using Cat = LogCategory_enum<LogSource,LogType> ;

using Filter = LogFilter_enum<LogSource,LogType> ;

inline Cat operator | (LogSource src,LogType type) { return Cat(src,type); }

UserLog<Cat,LogStamp,Filter> Log("TestLog",10_KByte);

} // namespace Private_3004

using namespace Private_3004;

/* Testit<3004> */

template<>
const char *const Testit<3004>::Name="Test3004 Log";

template<>
bool Testit<3004>::Main()
 {
  //Log.setFilter(Filter(LogSourceTask|LogEvent));

  Log(LogSourceTask|LogEvent,"start");

  Log(LogSourceTask|LogDebug,"point #;",1);
  Log(LogSourceTask|LogDebug,"point #;",2);
  Log(LogSourceTask|LogDebug,"point #; #;",1,2);
  Log(LogSourceTask|LogDebug,"point #; #; #;",1,2,3);
  Log(LogSourceTask|LogEvent,"point #;",10);
  Log(LogSourceTask|LogEvent,"point #;",20);

  Log(LogSourceTask|LogEvent,"finish");

  Printf(Con,"no filter\n\n#;",PrintLog(Log,100));
  Printf(Con,"\nfiltered\n\n#;",PrintLog(Log,100,Filter(LogSourceTask|LogDebug)));

  for(ulen count=10'000; count ;count--)
    {
     Log(LogSourceTask|LogEvent,"count = #;",count);
    }

  PrintFile out("testLog.txt");

  Putobj(out,PrintLog(Log,250));

  return true;
 }

} // namespace App

