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

template <class T,class R>
R * DataProc::getRec(T *obj,DynArray<R *> &list)
 {
  if( ulen ext=obj->ext ) return list[ext-1];

  R *ret=pool.create<R>();

  list.append_copy(ret);

  obj->ext=list.getLen();

  return ret;
 }

auto DataProc::getRec(TypeDef::Target *obj) -> TRec *
 {
  return getRec(obj,trecs);
 }

void DataProc::add(TypeDef::Target *dst,TypeDef::Rule *rule)
 {
  TRec *rec=getRec(dst);

  if( rec->rule )
    {
     Printf(Exception,"vmake file #.q; : multiple rules for a target #.q;",file_name,GetDesc(dst));
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

  works.reserve(trecs.getLen());
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
bool DataProc::ApplyToSrc(OneOfTypes<TypeDef::Rule,TypeDef::Dep> *obj,Func func)
 {
  for(TypeDef::Target *ptr : obj->src.getRange() ) if( ptr ) if( !func(ptr) ) return false;

  return true;
 }

template <class Func>
bool DataProc::applyToSrc(TypeDef::Target *obj,Func func)
 {
  TRec *rec=getRec(obj);

  if( rec->rule )
    {
     if( !ApplyToSrc(rec->rule,func) ) return false;
    }

  return rec->deps.applyWhile( [&] (TypeDef::Dep *obj) { return ApplyToSrc(obj,func); } );
 }

bool DataProc::checkExist(StrLen dst)
 {
  return file_proc.checkExist(Range(wdir),dst);
 }

bool DataProc::checkOlder(StrLen dst,StrLen src)
 {
  return file_proc.checkOlder(Range(wdir),dst,src);
 }

bool DataProc::checkOlder(TypeDef::Target *dst,TypeDef::Target *src,bool nofile)
 {
  StrLen dst_file=dst->file;
  StrLen src_file=src->file;

  if( !dst_file )
    {
     return false;
    }
  else
    {
     if( !src_file )
       {
        return nofile;
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
     return getRec(dst)->rule==0;
    }
  else
    {
     return checkExist(dst_file);
    }
 }

bool DataProc::checkOlderSrc(TypeDef::Target *dst,bool nofile)
 {
  return

  applyToSrc(dst, [&] (TypeDef::Target *src)
                      {
                       switch( getRec(src)->state )
                         {
                          case StateOk : return !checkOlder(dst,src,nofile);

                          case StateRebuild : return false;

                          default:
                           {
                            Printf(Exception,"vmake internal : unexpected src state");

                            return false;
                           }
                         }

                      } ) ;
 }

void DataProc::finish(TypeDef::Target *obj)
 {
  if( checkSelf(obj) && checkOlderSrc(obj,true) )
    {
     getRec(obj)->state=StateOk;
    }
  else
    {
     getRec(obj)->state=StateRebuild;

     addWork(obj);
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
                                    Printf(Exception,"vmake file #.q; : dependency loop detected #.q; #.q;",file_name,GetDesc(obj),GetDesc(src));
                                   }
                                  break;
                                 }

                               return true;

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

auto DataProc::getRec(TypeDef::Rule *obj) -> RRec *
 {
  return getRec(obj,rrecs);
 }

void DataProc::addWork(TypeDef::Target *obj) // Printf(Con
 {
  Printf(Con,"rebuild #.q;\n",GetDesc(obj));

  works.append_copy(obj);
 }

bool DataProc::dstReady(TypeDef::Target *obj)
 {
  return applyToSrc(obj, [&] (TypeDef::Target *src) { return getRec(src)->state==StateOk; } );
 }

bool DataProc::canRun(TypeDef::Rule *obj)
 {
  for(TypeDef::Target *ptr : obj->dst.getRange() ) if( ptr && !dstReady(ptr) ) return false;

  return true;
 }

bool DataProc::checkRebuild(TypeDef::Target *obj)
 {
  StrLen dst_file=obj->file;

  if( !dst_file ) return dstReady(obj);

  return checkExist(dst_file) && checkOlderSrc(obj,false) ;
 }

bool DataProc::checkRebuild(TypeDef::Target *obj,TRec *rec)
 {
  if( checkRebuild(obj) )
    {
     rec->state=StateOk;

     return true;
    }

  return false;
 }

int DataProc::exeRule(TypeDef::Rule *rule)
 {
  return file_proc.exeRule(Range(wdir),rule);
 }

void DataProc::completeRule(TypeDef::Target *obj)
 {
  StrLen dst_file=obj->file;

  if( !dst_file || ( checkExist(dst_file) && checkOlderSrc(obj,false) ) )
    {
     getRec(obj)->state=StateOk;
    }
 }

void DataProc::completeRule(TypeDef::Rule *rule)
 {
  for(TypeDef::Target *ptr : rule->dst.getRange() ) if( ptr ) completeRule(ptr);
 }

bool DataProc::commit(TypeDef::Target *obj)
 {
  TRec *rec=getRec(obj);

  if( rec->state==StateRebuild )
    {
     if( TypeDef::Rule *rule=rec->rule )
       {
        RRec *rule_rec=getRec(rule);

        if( rule_rec->done )
          {
           return false;
          }
        else
          {
           if( canRun(rule) )
             {
              int result=exeRule(rule);

              rule_rec->done=true;

              if( result==0 )
                {
                 completeRule(rule);

                 return rec->state==StateOk;
                }
             }

           return false;
          }
       }
     else
       {
        return checkRebuild(obj,rec);
       }
    }

  return true;
 }

int DataProc::commit() // Printf(Con
 {
  Printf(Con,"\ncommit\n\n");

  rrecs.reserve(1000);

  auto list=Range(works);

  while( +list )
    {
     auto save=list.ptr;

     for(TypeDef::Target *obj : list )
       if( !commit(obj) )
         {
          *(save++)=obj;
         }

     if( !Change(list.len,Dist(list.ptr,save)) )
       {
        Printf(NoException,"vmake : rebuild failed");

        return 1;
       }
    }

  return 0;
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

int DataProc::make()
 {
  buildWorkTree();

  return commit();
 }

} // namespace VMake

} // namespace App

