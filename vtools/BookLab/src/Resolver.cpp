/* Resolver.cpp */
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

#include <inc/Resolver.h>

#include <inc/BookLab.h>

namespace App {
namespace BookLab {

/* class Resolver */

struct Resolver::Loop
 {
  PtrLen<APtr> rec_list;
  APtr ptr;

  template <class Ctx,class T>
  bool step(Ctx &ctx,T *obj)
   {
    ctx(obj);

    ptr=rec_list[obj->frame];

    return true;
   }

  template <class Ctx>
  bool step(Ctx &ctx,PageRec *obj)
   {
    ctx(obj);

    return false;
   }

  template <class Ctx>
  bool step(Ctx &ctx)
   {
    bool ret=false;

    ptr.apply( [&] (auto *ptr) { ret=step(ctx,ptr); } );

    return ret;
   }

  template <class Ctx>
  void feed(Ctx &ctx)
   {
    while( step(ctx) );
   }
 };

struct Resolver::LenCtx
 {
  Link *link;
  ulen len=0;

  void operator () (PageRec *ptr)
   {
    link->page=ptr->page;

    len+=1;
   }

  void operator () (CollapseRec *)
   {
    len+=1;
   }

  void operator () (TextListRec *)
   {
    len+=2;
   }

  void operator () (TableRec *)
   {
    len+=3;
   }
 };

struct Resolver::SetCtx
 {
  ulen *out;

  void put(ulen index) { *(--out)=index; }

  void operator () (PageRec *ptr)
   {
    put(ptr->index);
   }

  void operator () (CollapseRec *ptr)
   {
    put(ptr->index);
   }

  void operator () (TextListRec *ptr)
   {
    put(ptr->index2);
    put(ptr->index1);
   }

  void operator () (TableRec *ptr)
   {
    put(ptr->index3);
    put(ptr->index2);
    put(ptr->index1);
   }
 };

void Resolver::gen(IntObjPtr<Page> page)
 {
  ulen index=0;

  for(Frame &frame : ForIntList(page->list) )
    {
     frame.index=addRec(PageRec{page,index});

     index++;

     gen(frame);
    }
 }

void Resolver::gen(Frame &frame)
 {
  auto ptr=frame.body.ptr;

  if( +ptr ) ptr.getPtr().apply( [&] (auto *obj) { gen(frame.index,obj); } );
 }

void Resolver::gen(ulen parent,Collapse *obj)
 {
  ulen index=0;

  for(Frame &frame : ForIntList(obj->list) )
    {
     frame.index=addRec(CollapseRec{parent,index});

     index++;

     gen(frame);
    }
 }

void Resolver::gen(ulen parent,TextList *obj)
 {
  ulen index1=0;

  for(Item &item : ForIntList(obj->list) )
    {
     ulen index2=0;

     for(Frame &frame : ForIntList(item.list) )
       {
        frame.index=addRec(TextListRec{parent,index1,index2});

        index2++;

        gen(frame);
       }

     index1++;
    }
 }

void Resolver::gen(ulen parent,Table *obj)
 {
  ulen nx=obj->table.width.getLen();

  if( !nx ) return;

  auto cells=Range(obj->table.cells);

  for(ulen i=0; i<cells.len ;i++)
    {
     auto ptr=cells[i].ptr;

     if( +ptr )
       {
        ulen col=i%nx;
        ulen row=i/nx;

        ulen index=0;

        for(Frame &frame : ForIntList(ptr->list) )
          {
           frame.index=addRec(TableRec{parent,col,row,index});

           index++;

           gen(frame);
          }
       }
    }
 }

ulen * Resolver::Prepare(RefArray<ulen> &obj,ulen len)
 {
  obj.erase();

  PtrLen<ulen> r=obj.extend_raw(len);

  return r.ptr+r.len;
 }

void Resolver::resolve(Link *link,PtrLen<APtr> rec_list,APtr ptr)
 {
  LenCtx len_ctx{link};

  Loop{rec_list,ptr}.feed(len_ctx);

  SetCtx set_ctx{Prepare(link->index_list,len_ctx.len)};

  Loop{rec_list,ptr}.feed(set_ctx);
 }

bool Resolver::resolve(Link *link,PtrLen<APtr> rec_list)
 {
  ulen f=link->frame->index;

  if( f>=rec_list.len )
   {
    Printf(eout,"Unresolved link\n");

    return false;
   }

  resolve(link,rec_list,rec_list[f]);

  return true;
 }

Resolver::Resolver(PrintBase &eout_)
 : eout(eout_)
 {
 }

Resolver::~Resolver()
 {
 }

void Resolver::add(IntObjPtr<Link> link)
 {
  if( +link->frame )
    links.append_copy(link.getPtr());
 }

bool Resolver::resolve()
 {
  auto links_list=links.flat();

  for(Link *link : links_list ) link->frame->index=MaxULen;

  for(IntObjPtr<Page> page : pages.flat() ) gen(page);

  auto rec_list=recs.flat();

  bool ret=true;

  for(Link *link : links_list ) if( !resolve(link,rec_list) ) ret=false;

  return ret;
 }

} // namespace BookLab
} // namespace App

