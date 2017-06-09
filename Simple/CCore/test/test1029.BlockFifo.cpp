/* test1029.BlockFifo.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 2.00
//
//  Tag: Simple
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/BlockFifo.h>
#include <CCore/inc/Random.h>

namespace App {

namespace Private_1029 {

/* class Engine */

class Engine : NoCopy
 {
   static const ulen MaxLen = 2048 ;
   static const ulen Len = 1024 ;

   Random random;

   BlockFifoBuf<unsigned,Len> fifo;

   unsigned next_put = 0 ;
   unsigned next_get = 0 ;

  private:

   void put(ulen len)
    {
     unsigned temp[MaxLen];

     for(unsigned i=0; i<len ;i++) temp[i]=next_put+i;

     next_put+=(unsigned)fifo.put(Range_const(temp,len));
    }

   void put_func(ulen len)
    {
     fifo.put(len, [this] (unsigned *ptr,ulen len) { for(unsigned &x : Range(ptr,len) ) x=next_put++; } );
    }

   void get(ulen len)
    {
     unsigned temp[MaxLen];

     len=fifo.get(Range(temp,len));

     for(unsigned i=0; i<len ;i++)
       if( temp[i]!=next_get+i )
         {
          Printf(Exception,"Error !");
         }

     next_get+=(unsigned)len;
    }

   void get_func(ulen len)
    {
     fifo.get(len, [this] (const unsigned *ptr,ulen len) { for(unsigned x : Range(ptr,len) ) if( x!=next_get++ ) Printf(Exception,"Error !"); } );
    }

  public:

   Engine() {}

   ~Engine() {}

   void run(unsigned count)
    {
     next_put=0;
     next_get=0;

     fifo.reset();

     while( next_get<count )
       {
        switch( random.select(2) )
          {
           case 0 :
            {
             switch( random.select(2) )
               {
                case 0 : put(random.select(MaxLen)); break;

                case 1 : put_func(random.select(MaxLen)); break;
               }
            }
           break;

           case 1 :
            {
             switch( random.select(2) )
               {
                case 0 : get(random.select(MaxLen)); break;

                case 1 : get_func(random.select(MaxLen)); break;
               }
            }
           break;
          }
       }
    }
 };

} // namespace Private_1029

using namespace Private_1029;

/* Testit<1029> */

template<>
const char *const Testit<1029>::Name="Test1029 BlockFifo";

template<>
bool Testit<1029>::Main()
 {
  Engine engine;

  for(ulen count=100; count ;count--) engine.run(100'000'000);

  return true;
 }

} // namespace App

