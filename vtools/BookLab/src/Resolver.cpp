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

void Resolver::gen(IntObjPtr<Page> page)
 {
  ulen index=0;

  for(Frame &frame : ForIntList(page->list) )
    {
     ulen f=addRec(PageRec{page,index});

     frame.index=f;

     index++;

     frame.body.ptr.getPtr().apply( [&] (auto *obj) { gen(f,obj); } );
    }
 }

void Resolver::gen(ulen frame,Collapse *obj)
 {
 }

void Resolver::gen(ulen frame,TextList *obj)
 {
 }

void Resolver::gen(ulen frame,Table *obj)
 {
 }

bool Resolver::resolve(Link *link,PtrLen<APtr> rec_list,APtr ptr) // TODO
 {
  return false;
 }

bool Resolver::resolve(Link *link,PtrLen<APtr> rec_list)
 {
  ulen f=link->frame->index;

  if( f>=rec_list.len || !resolve(link,rec_list,rec_list[f]) )
   {
    Printf(eout,"Unresolved link\n");

    return false;
   }

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

