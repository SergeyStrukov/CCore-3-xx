/* test2051.DeferCall.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/DeferCall.h>
#include <CCore/inc/Log.h>
#include <CCore/inc/ReadCon.h>
#include <CCore/inc/CharProp.h>

namespace App {

namespace Private_2051 {

/* class Log */

enum LogSource
 {
  LogWork
 };

const char * GetTextDesc(LogSource) { return "Work"; }

enum LogType
 {
  LogEntry
 };

const char * GetTextDesc(LogType) { return "Entry"; }

using LogCat = LogCategory_enum<LogSource,LogType> ;

using LogFilter = LogFilter_enum<LogSource,LogType> ;

inline LogCat operator | (LogSource src,LogType type) { return LogCat(src,type); }

using Log = UserLog<LogCat,LogStamp,LogFilter> ;

/* class Window */

#if 0

class Window : NoCopy
 {
   class Work : NoCopy
    {
      Log log;
      DeferTick &defer_tick;

     public:

      explicit Work(DeferTick &defer_tick_) : log("Work log",64_KByte),defer_tick(defer_tick_) {}

      ~Work()
       {
        PrintFile out("test2051.txt");

        Putobj(out,PrintLog(log,1000000));
       }

      void put(ReadConCode ch)
       {
        log(LogWork|LogEntry,"put('#;')",ExtCharCode(ch));

        switch( ToChar(ch) )
          {
           case 'x' : case 'X' : DeferCallQueue::Stop(); break;

           case 't' : case 'T' : defer_tick.start(); break;

           case 's' : case 'S' : defer_tick.stop(); break;
          }
       }

      void tick()
       {
        log(LogWork|LogEntry,"tick()");
       }
    };

   Work work;

  public:

   Window()
    : work(tick),
      input(work),
      tick(input.create(&Work::tick))
    {
    }

   ~Window()
    {
    }

   class Input : DeferInput<Work>
    {
      friend class Window;

      explicit Input(Work &work) : DeferInput<Work>(&work) {}

      ~Input() {}

     public:

      void put(ReadConCode ch) { try_post(&Work::put,ch); }
    };

   Input input;

  private:

   DeferTick tick;
 };

#else

class Window : NoCopy
 {
   Log log;
   DeferTick defer_tick;

  private:

   void put(ReadConCode ch)
    {
     log(LogWork|LogEntry,"put('#;')",ExtCharCode(ch));

     switch( ToChar(ch) )
       {
        case 'x' : case 'X' : DeferCallQueue::Stop(); break;

        case 't' : case 'T' : defer_tick.start(); break;

        case 's' : case 'S' : defer_tick.stop(); break;
       }
    }

   void tick()
    {
     log(LogWork|LogEntry,"tick()");
    }

  public:

   Window()
    : log("Work log",64_KByte),
      input(this)
    {
     //defer_tick=input.create(&Window::tick);

     defer_tick=input.create( [] (Window &window) { window.tick(); } );
    }

   ~Window()
    {
     PrintFile out("test2051.txt");

     Putobj(out,PrintLog(log,1000000));
    }

   class Input : DeferInput<Window>
    {
      friend class Window;

      explicit Input(Window *window) : DeferInput<Window>(window) {}

      ~Input() {}

     public:

      void put(ReadConCode ch) { try_post(&Window::put,ch); }
    };

   Input input;
 };

#endif

/* class Queue */

class Queue : public DeferCallQueue
 {
   ReadCon read_con;
   Window *window;

  public:

   Queue()
    {
     activate();
    }

   ~Queue()
    {
     deactivate();
    }

   void set(Window &window_) { window=&window_; }

   void forward(TimeScope time_scope) override
    {
     ReadConCode ch;

     if( read_con.get(time_scope,ch) )
       {
        window->input.put(ch);
       }
    }
 };

} // namespace Private_2051

using namespace Private_2051;

/* Testit<2051> */

template<>
const char *const Testit<2051>::Name="Test2051 DeferCall";

template<>
bool Testit<2051>::Main()
 {
  Queue queue;

  Printf(Con,"#;\n",sizeof (Queue));

  Window window;

  queue.set(window);

  Queue::Loop();

  return true;
 }

} // namespace App

