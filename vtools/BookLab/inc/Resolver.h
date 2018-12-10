/* Resolver.h */
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

#ifndef Resolver_h
#define Resolver_h

#include <inc/BookElements.h>

#include <CCore/inc/ElementPool.h>

namespace App {
namespace BookLab {

/* classes */

class Resolver;

/* class Resolver */

class Resolver : NoCopy
 {
   PrintBase &eout;

   Collector<IntObjPtr<Page> > pages;
   Collector<Link *> links;

   struct PageRec
    {
     IntObjPtr<Page> page;
     ulen index;
    };

   struct CollapseRec
    {
     ulen frame;
     ulen index;
    };

   struct TextListRec
    {
     ulen frame;
     ulen index1;
     ulen index2;
    };

   struct TableRec
    {
     ulen frame;
     ulen index1;
     ulen index2;
     ulen index3;
    };

   using APtr = AnyPtr<PageRec,CollapseRec,TextListRec,TableRec> ;

   ElementPool pool;
   Collector<APtr> recs;

  private:

   template <class T>
   ulen addRec(T obj)
    {
     ulen ret=recs.getLen();

     recs.append_fill(pool.create<T>(obj));

     return ret;
    }

   void gen(IntObjPtr<Page> page);

   template <class T>
   void gen(ulen,T *) {}

   void gen(ulen frame,Collapse *obj);

   void gen(ulen frame,TextList *obj);

   void gen(ulen frame,Table *obj);

   bool resolve(Link *link,PtrLen<APtr> rec_list,APtr ptr);

   bool resolve(Link *link,PtrLen<APtr> rec_list);

  public:

   explicit Resolver(PrintBase &eout);

   ~Resolver();

   template <class T>
   void add(IntObjPtr<T>) {}

   void add(IntObjPtr<Page> page) { pages.append_copy(page); }

   void add(IntObjPtr<Link> link);

   bool resolve();
 };

} // namespace BookLab
} // namespace App

#endif
