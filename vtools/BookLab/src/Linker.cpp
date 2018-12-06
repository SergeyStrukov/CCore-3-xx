/* Linker.cpp */
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

#include <inc/Linker.h>

#include <CCore/inc/ForLoop.h>

#include <CCore/inc/algon/SortUnique.h>

namespace App {
namespace BookLab {

/* class Linker */

void Linker::fill(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name)
 {
  obj->name=StrKey(name);

  ulen count=0;

  for(StrLen sname : ForLoop(ScopeCursor(scope)) )
    {
     Used(sname);

     count++;
    }

  if( !count ) return;

  PtrLen<StrKey> path=pool.createArray<StrKey>(count);

  obj->path=path;

  auto out=RangeReverse(path);

  for(StrLen sname : ForLoop(ScopeCursor(scope)) )
    {
     *out=StrKey(sname);

     ++out;
    }
 }

void Linker::append(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name)
 {
  fill(obj,scope,name);

  collector.append_copy(obj);
 }

bool Linker::fillPtr(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name) // TODO split name by #
 {
  obj->name=StrKey(name);

  ulen count=0;

  for(StrLen sname : ForLoop(ScopeCursor(scope)) )
    {
     Used(sname);

     count++;
    }

  if( !count ) return true;

  PtrLen<StrKey> path=pool.createArray<StrKey>(count);

  obj->path=path;

  auto out=RangeReverse(path);

  for(StrLen sname : ForLoop(ScopeCursor(scope)) )
    {
     *out=StrKey(sname);

     ++out;
    }

  return true;
 }

void Linker::appendPtr(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name)
 {
  if( fillPtr(obj,scope,name) ) collector.append_copy(obj);
 }

bool Linker::linkName(PtrLen<Base *> list) // TODO
 {
  Printf(eout,"#; not implemented\n",(*list)->name.str);

  return false;
 }

bool Linker::link(PtrLen<Base *> list)
 {
  bool ret=true;

  Algon::IncrSortThenApplyUniqueRangeBy(list, [] (Base *obj) { return obj->name; } ,
                                              [&] (PtrLen<Base *> list) { if( !linkName(list) ) ret=false; } );

  return ret;
 }

Linker::Linker(PrintBase &eout_)
 : eout(eout_)
 {
 }

Linker::~Linker()
 {
 }

bool Linker::link()
 {
  return link(collector.flat());
 }

} // namespace BookLab
} // namespace App
