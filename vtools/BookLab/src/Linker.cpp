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
#include <CCore/inc/algon/BinarySearch.h>

namespace App {
namespace BookLab {

/* class NameCursor */

void NameCursor::set(StrLen text)
 {
  if( +text )
    {
     for(auto fin=text.getFinal(); fin.len<text.len ;)
       {
        --fin;

        if( (*fin)=='#' )
          {
           path=text.prefix(fin);

           ++fin;

           name=fin;

           ok=true;

           return;
          }
       }

     path=Null;
     name=text;
     ok=true;
    }
  else
    {
     ok=false;
    }
 }

/* class Linker */

void Linker::fillPath(Base *obj,IntAnyObjPtr<Scope,Doc> scope)
 {
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

void Linker::fill(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name)
 {
  obj->name=StrKey(name);

  fillPath(obj,scope);
 }

void Linker::append(Base *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name)
 {
  fill(obj,scope,name);

  collector.append_copy(obj);
 }

PtrLen<StrKey> Linker::makeExt(NameCursor cur,ulen count)
 {
  if( !count ) return Empty;

  PtrLen<StrKey> ret=pool.createArray<StrKey>(count);

  for(StrKey &key : RangeReverse(ret) )
    {
     key=StrKey(*cur);

     ++cur;
    }

  return ret;
 }

void Linker::fillPtrRel(PtrBase *obj,IntAnyObjPtr<Scope,Doc> scope,NameCursor cur,ulen count)
 {
  fillPath(obj,scope);

  obj->ext=makeExt(cur,count);
 }

void Linker::fillPtrAbs(PtrBase *obj,NameCursor cur,ulen count)
 {
  obj->abs=true;

  obj->path=makeExt(cur,count);
 }

bool Linker::fillPtr(PtrBase *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name)
 {
  NameCursor cur(name);

  if( !cur || !(*cur) )
    {
     Printf(eout,"Bad name #.q;\n",name);

     return false;
    }

  obj->name=StrKey(*cur);

  ++cur;

  ulen count=0;

  for(StrLen sname : ForLoop(cur) )
    {
     if( !sname )
       {
        Printf(eout,"Bad name #.q;\n",name);

        return false;
       }

     count++;
    }

  if( *name=='#' )
    fillPtrAbs(obj,cur,count);
  else
    fillPtrRel(obj,scope,cur,count);

  return true;
 }

void Linker::appendPtr(PtrBase *obj,IntAnyObjPtr<Scope,Doc> scope,StrLen name)
 {
  if( fillPtr(obj,scope,name) ) collector.append_copy(obj);
 }

bool Linker::link(PtrLen<Base *> list)
 {
  bool ret=true;

  Algon::IncrSortThenApplyUniqueRangeBy(list, [] (Base *obj) { return obj->name; } ,
                                              [&] (PtrLen<Base *> list) { if( !linkName(list) ) ret=false; } );

  return ret;
 }

struct Linker::PrintPath
 {
  PtrLen<StrKey> path;

  void print(PrinterType &out) const
   {
    out.put('"');

    if( +path )
      {
       for(const StrKey &key : path )
         {
          out.put('#');

          Putobj(out,key.str);
         }
      }
    else
      {
       out.put('#');
      }

    out.put('"');
   }
 };

struct Linker::NeqPath
 {
  PtrLen<StrKey> path;

  bool operator != (const NeqPath &obj) const { return RangeCmp(path,obj.path)!=0; }
 };

bool Linker::LessPrefix(Base *a,Base *b)
 {
  if( auto ret=RangeCmp(a->path,b->path) ) return ret<0;

  return a->def < b->def ;
 }

bool Linker::linkNameAbs(PtrLen<Base *> def)
 {
  PtrLen<Base *> req=Algon::BinarySearch_if(def, [] (Base *base) { return base->def; } );

  if( def.len>1 )
    {
     Printf(eout,"Name duplication #.q;\n",(*def)->name.str);
     Printf(eout," in scope #;\n",PrintPath{(*def)->path});

     return false;
    }

  bool ret=true;

  for(Base *base : req )
    {
     PtrBase *base1=static_cast<PtrBase *>(base);

     if( base1->abs )
       {
        if( !def )
          {
           Printf(eout,"Undefined name #.q;\n",base->name.str);
           Printf(eout," in scope #;\n",PrintPath{base->path});

           ret=false;
          }
        else
          {
           if( !assign(base1,*def) ) ret=false;
          }
       }
    }

  return ret;
 }

bool Linker::linkName(PtrLen<Base *> list) // TODO
 {
  IncrSort(list,LessPrefix);

  bool ret=true;

  Algon::ApplyUniqueRangeBy(list, [] (Base *base) -> NeqPath { return {base->path}; } ,

                                  [&] (PtrLen<Base *> list) { if( !linkNameAbs(list) ) ret=false; } );

  // TODO

  ret=false;

  return ret;
 }

bool Linker::assign(PtrBase *req,Base *def)
 {
  if( req->assign(req,static_cast<NameBase *>(def)) ) return true;

  Printf(eout,"Incompatible type #;\n",def->name.str);
  Printf(eout," in scope #;\n",PrintPath{def->path});

  return false;
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
