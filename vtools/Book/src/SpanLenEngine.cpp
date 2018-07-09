/* SpanLenEngine.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/SpanLenEngine.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>

namespace App {

/* class SpanLenEngine */

SpanLenEngine::SpanLenEngine(ulen len_)
 : list(DoReserve,len_+100),len(len_)
 {
  for(ulen i=0,lim=len; i<lim ;i++) add(i,1,0);
 }

SpanLenEngine::~SpanLenEngine()
 {
 }

void SpanLenEngine::add(ulen i,ulen span,Coord ext)
 {
  list.append_copy({i-1,i+span-1,ext});
 }

DynArray<Coord> SpanLenEngine::complete()
 {
  ulen n=len;

  DynArray<Coord> y(n);

  // 1

  PtrLen<Cond> list=Range(this->list);

  IncrSort(list, [] (const Cond &a,const Cond &b) { return a.l<b.l; } );

  // 2

  for(ulen k=0; k<n ;k++)
    {
     Coord Y=0;

     // for(Cond cond : list ) cond.l >=k ;

     auto pref=Algon::BinarySearch_if(list, [k] (const Cond &obj) { return obj.l>k; } );

     for(Cond cond : pref ) // cond.l == k
       {
        if( cond.k!=ulen(-1) )
          Replace_max(Y,cond.a+y[cond.k]);
        else
          Replace_max(Y,cond.a);
       }

     y[k]=Y;
    }

  // 3

  DynArray<Coord> x(n);

  Coord s=0;

  for(ulen i=0; i<n ;i++) x[i]=Diff(s,y[i]);

  return x;
 }

} // namespace App


