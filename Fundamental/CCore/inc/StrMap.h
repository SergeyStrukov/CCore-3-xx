/* StrMap.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_StrMap_h
#define CCore_inc_StrMap_h

#include <CCore/inc/Array.h>
#include <CCore/inc/Cmp.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>

namespace CCore {

/* functions */

template <Algon::RangeType R,class Func>
R StrNextFrame(R r,ulen ind,char ch,Func by)
 {
  using T = Meta::PtrObjType<R> ;

  Algon::BinarySearch_if(r, [=] (const T &obj) { StrLen str=by(obj); return str.len>ind && str[ind]>=ch ; } );

  return Algon::BinarySearch_if(r, [=] (const T &obj) { StrLen str=by(obj); return str[ind]>ch ; } );
 }

template <Algon::RangeType R,class Func>
R StrLastFrame(R r,ulen len,Func by)
 {
  using T = Meta::PtrObjType<R> ;

  return Algon::BinarySearch_if(r, [=] (const T &obj) { StrLen str=by(obj); return str.len>len; } );
 }

/* classes */

template <class T> class StrMap;

/* class StrMap<T> */

template <class T>
class StrMap : NoCopy
 {
   struct Rec : CmpComparable<Rec>
    {
     StrLen key;
     T obj;

     Rec() noexcept( Meta::HasNothrowDefaultCtor<T> ) : obj() {}

     template <class ... SS>
     Rec(StrLen key_,SS && ... ss) : key(key_),obj( std::forward<SS>(ss)... ) {}

     // cmp objects

     CmpResult objCmp(const Rec &obj) const { return StrCmp(key,obj.key); }

     // swap objects

     void objSwap(Rec &rec)
      {
       Swap(key,rec.key);
       Swap(obj,rec.obj);
      }
    };

   DynArray<Rec> map;

  private:

   template <class R>
   static R Search(R r,ulen i,char ch)
    {
     return StrNextFrame(r,i,ch, [] (const Rec &rec) { return rec.key; } );
    }

   template <class R>
   static R Search(R r,ulen len)
    {
     return StrLastFrame(r,len, [] (const Rec &rec) { return rec.key; } );
    }

   static T * PickNone(PtrLen<Rec>)
    {
     return 0;
    }

   static const T * PickNone(PtrLen<const Rec>)
    {
     return 0;
    }

   template <class R>
   static auto Pick(R r)
    {
     if( +r ) return &r->obj;

     return PickNone(r);
    }

   template <class R>
   static auto Search(R r,StrLen key)
    {
     for(ulen i=0; i<key.len ;i++)
       {
        r=Search(r,i,key[i]);

        if( r.len==0 ) return PickNone(r);

        if( r.len==1 )
          {
           ulen off=i+1;

           if( r->key.part(off).equal(key.part(off)) ) return Pick(r);

           return PickNone(r);
          }
       }

     r=Search(r,key.len);

     return Pick(r);
    }

  protected:

   StrMap() {}

   template <class ... SS>
   void add(StrLen key,SS && ... ss) // key is persistent
    {
     map.append_fill(key, std::forward<SS>(ss)... );
    }

   void complete()
    {
     Sort(Range(map));
    }

  public:

   ~StrMap() {}

   T * operator [] (StrLen key)
    {
     return Search(Range(map),key);
    }

   const T * operator [] (StrLen key) const
    {
     return Search(Range(map),key);
    }
 };

} // namespace CCore

#endif

