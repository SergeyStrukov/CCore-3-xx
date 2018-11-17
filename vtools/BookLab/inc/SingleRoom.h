/* SingleRoom.h */
//----------------------------------------------------------------------------------------
//
//  Project: BookLab 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef SingleRoom_h
#define SingleRoom_h

#include <CCore/inc/AnyPtr.h>

namespace App {

/* using */

using namespace CCore;

/* classes */

template <class ... TT> class SingleRoom;

/* class SingleRoom<TT...> */

template <class ... TT>
class SingleRoom : NoCopy
 {
   static constexpr ulen Len = Max_cast( sizeof (TT) ... ) ;

   InitStorage<Len> mem;

   AnyPtr<TT...> ptr;

  private:

   template <NothrowDtorType T>
   static void Destroy(T *ptr) { ptr->~T(); }

  public:

   SingleRoom() {}

   ~SingleRoom() { destroy(); }

   bool operator + () const { return +ptr; }

   bool operator ! () const { return !ptr; }

   AnyPtr<TT...> getPtr() const { return ptr; }

   bool destroy()
    {
     if( +ptr )
       {
        Replace_null(ptr).apply( [] (auto *ptr) { Destroy(ptr); } );

        return true;
       }

     return false;
    }

   template <class T,class ... SS>
   T * create(SS && ... ss) requires ( ConstructibleType<T,SS...> )
    {
     destroy();

     T *ret=new(mem.getPlace()) T( std::forward<SS>(ss)... );

     ptr=ret;

     return ret;
    }
 };

} // namespace App

#endif


