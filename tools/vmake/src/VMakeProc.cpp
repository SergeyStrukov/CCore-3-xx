/* VMakeProc.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: vmake 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2019 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/VMakeProc.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

namespace App {

namespace VMake {

/* guard functions */

void GuardStackEmpty()
 {
  Printf(Exception,"vmake internal : stack is empty");
 }

/* class DataProc */

auto DataProc::getRec(TypeDef::Target *obj) -> TRec *
 {
  if( ulen ext=obj->ext ) return trecs[ext-1];

  TRec *ret=pool.create<TRec>();

  trecs.append_copy(ret);

  obj->ext=trecs.getLen();

  return ret;
 }

void DataProc::add(TypeDef::Target *dst,TypeDef::Rule *rule)
 {
  TRec *rec=getRec(dst);

  if( rec->rule )
    {
     Printf(Exception,"vmake file #.q; : multiple rules for a target",file_name);
    }

  rec->rule=rule;
 }

void DataProc::add(TypeDef::Target *dst,TypeDef::Dep *dep)
 {
  TRec *rec=getRec(dst);

  rec->deps.add(pool,dep);
 }

void DataProc::prepare(OneOfTypes<TypeDef::Rule,TypeDef::Dep> *obj)
 {
  for(TypeDef::Target *ptr : obj->dst.getRange() ) if( ptr ) add(ptr,obj);
 }

void DataProc::prepare()
 {
  trecs.reserve(1000);

  for(auto ptr : data.getRules() ) prepare(ptr);

  for(auto ptr : data.getDeps() ) prepare(ptr);

  trecs.shrink_extra();

  pool.shrink_extra();
 }

TypeDef::Rule * DataProc::getRule(TypeDef::Target *obj)
 {
  return getRec(obj)->rule;
 }

template <class Func>
void DataProc::applyToDeps(TypeDef::Target *obj,Func func)
 {
  getRec(obj)->deps.apply(func);
 }

template <class Func>
void DataProc::ApplyToSrc(OneOfTypes<TypeDef::Rule,TypeDef::Dep> *obj,Func func)
 {
  for(TypeDef::Target *ptr : obj->src.getRange() ) if( ptr ) func(ptr);
 }

template <class Func>
void DataProc::applyToSrc(TypeDef::Target *obj,Func func)
 {
  TRec *rec=getRec(obj);

  if( rec->rule ) ApplyToSrc(rec->rule,func);

  rec->deps.apply( [&] (TypeDef::Dep *obj) { ApplyToSrc(obj,func); } );
 }

bool DataProc::checkNotExist(StrLen dst)
 {
  return file_proc.checkNotExist(Range(wdir),dst);
 }

bool DataProc::checkOlder(StrLen dst,StrLen src)
 {
  return file_proc.checkOlder(Range(wdir),dst,src);
 }

bool DataProc::checkOlder(TypeDef::Target *dst,TypeDef::Target *src)
 {
  StrLen dst_file=dst->file;
  StrLen src_file=src->file;

  if( !dst_file )
    {
     return true;
    }
  else
    {
     if( !src_file )
       {
        return true;
       }
     else
       {
        return checkOlder(dst_file,src_file);
       }
    }
 }

bool DataProc::checkSelf(TypeDef::Target *dst)
 {
  StrLen dst_file=dst->file;

  if( !dst_file )
    {
     return true;
    }
  else
    {
     return checkNotExist(dst_file);
    }
 }

void DataProc::finish(TypeDef::Target *obj)
 {
  bool rebuild=checkSelf(obj);

  applyToSrc(obj, [&] (TypeDef::Target *src)
                      {
                       switch( getRec(src)->state )
                         {
                          case StateOk :
                           {
                            if( !rebuild ) rebuild=checkOlder(obj,src);
                           }
                          break;

                          case StateRebuild :
                           {
                            rebuild=true;
                           }
                          break;

                          default:
                           {
                            Printf(Exception,"vmake internal : unexpected src state");
                           }

                         }

                      } );

  if( rebuild )
    {
     getRec(obj)->state=StateRebuild;

     addWork(obj);
    }
  else
    {
     getRec(obj)->state=StateOk;
    }
 }

void DataProc::buildWorkTree()
 {
  Stack<TypeDef::Target *> stack;

  stack.push(data.getTarget());

  while( stack.notEmpty() )
    {
     TypeDef::Target *obj=stack.top();
     TRec *rec=getRec(obj);

     switch( rec->state )
       {
        case StateInitial :
         {
          rec->state=StateLocked;

          applyToSrc(obj, [&] (TypeDef::Target *src)
                              {
                               switch( getRec(src)->state )
                                 {
                                  case StateInitial :
                                   {
                                    stack.push(src);
                                   }
                                  break;

                                  case StateLocked :
                                   {
                                    Printf(Exception,"vmake file #.q; : dependency loop detected",file_name);
                                   }
                                  break;
                                 }

                              } );
         }
        break;

        case StateLocked :
         {
          finish(obj);

          stack.pop();
         }
        break;

        case StateOk :
         {
          stack.pop();
         }
        break;

        case StateRebuild :
         {
          stack.pop();
         }
        break;

        default:
         {
          Printf(Exception,"vmake internal : broken state");
         }
       }
    }
 }

void DataProc::addWork(TypeDef::Target *obj) // TODO
 {
  Used(obj);

  StrLen file=obj->file;

  Printf(Con,"rebuild #;\n",file);
 }

DataProc::DataProc(FileProc &file_proc,StrLen file_name,StrLen target)
 : DataProc(file_proc,file_name,target,PrefixPath(file_name))
 {
 }

DataProc::DataProc(FileProc &file_proc_,StrLen file_name_,StrLen target,StrLen wdir_)
 : file_proc(file_proc_),
   data(file_name_,target)
 {
  file_name=pool.dup(file_name_);
  wdir=pool.dup(wdir_);

  prepare();
 }

DataProc::~DataProc()
 {
 }

int DataProc::make() // TODO
 {
  buildWorkTree();

  return 1;
 }

} // namespace VMake

} // namespace App

