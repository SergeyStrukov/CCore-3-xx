/* test3005.LogMem.cpp */
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
#include <CCore/inc/Random.h>
#include <CCore/inc/OwnPtr.h>
#include <CCore/inc/Counters.h>

namespace App {

namespace Private_3005 {

/* enum Event */

enum Event
 {
  EventNoMem,
  EventAlloc,
  EventFree,
  EventDel,
  EventClear,

  EventLim
 };

const char * GetTextDesc(Event ev)
 {
  static const char *const Table[]=
   {
    "NoMem",
    "Alloc",
    "Free",
    "Del",
    "Clear"
   };

  return Table[ev];
 }

/* class Engine */

class Engine : NoCopy
 {
   LogMem logmem;
   Random random;
   Counters<Event,EventLim> stat;

   struct Head
    {
     SLink<Head> link;

     ulen len;
     byte fill;

     byte * mem() { return PlaceAt(this)+sizeof (Head); }

     PtrLen<byte> range() { return Range(mem(),len); }

     void init(ulen len_,byte fill_)
      {
       len=len_;
       fill=fill_;

       fill_ext();
      }

     void fill_ext()
      {
       range().set(fill);
      }

     void check_ext()
      {
       for(byte b : range() ) if( b!=fill ) Printf(Exception,"fail");
      }
    };

   SLink<Head>::LinearAlgo<&Head::link>::FirstLast list;

  private:

   void alloc()
    {
     ulen len=random.select(0,1_KByte);

     void *mem=logmem.alloc(len+sizeof (Head));

     if( !mem )
       {
        stat.count(EventNoMem);

        return;
       }

     if( random.select(10) )
       {
        Head *head=new(PlaceAt(mem)) Head;

        head->init(len,random.next_uint<byte>());

        list.ins_last(head);

        stat.count(EventAlloc);
       }
     else
       {
        logmem.free(mem);

        stat.count(EventFree);
       }
    }

   void del()
    {
     if( Head *head=list.del_first() )
       {
        head->check_ext();

        if( +list )
          {
           logmem.del(list.first);

           stat.count(EventDel);
          }
        else
          {
           logmem.clear();

           stat.count(EventClear);
          }
       }
    }

  public:

   Engine()
    : logmem(10_KByte)
    {
    }

   void run(ulen count)
    {
     for(; count ;count--)
       {
        switch( random.select(2) )
          {
           case 0 :
            {
             alloc();
            }
           break;

           case 1 :
            {
             del();
            }
           break;
          }
       }

     Printf(Con,"#10l;\n",stat);
    }
 };

} // namespace Private_3005

using namespace Private_3005;

/* Testit<3005> */

template<>
const char *const Testit<3005>::Name="Test3005 LogMem";

template<>
bool Testit<3005>::Main()
 {
  OwnPtr<Engine> engine(new Engine);

  engine->run(10'000'000);

  return true;
 }

} // namespace App

