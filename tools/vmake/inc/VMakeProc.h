/* VMakeProc.h */
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

#ifndef App_VMakeProc_h
#define App_VMakeProc_h

#include <inc/VMakeData.h>
#include <inc/VMakeFileProc.h>

#include <CCore/inc/Path.h>
#include <CCore/inc/String.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/List.h>
#include <CCore/inc/StrKey.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/ElementPool.h>

#include <CCore/inc/ddl/DDLMapTypes.h>

#include <CCore/inc/FileSystem.h>

namespace App {
namespace VMake {

/* guard functions */

void GuardStackEmpty();

/* functions */

inline StrLen GetDesc(TypeDef::Target *ptr)
 {
  StrLen ret=ptr->desc;

  if( !ret ) return "???"_c;

  return ret;
 }

/* classes */

template <class T> class List;

template <class T> class Stack;

class FileProc;

class DataProc;

/* class List<T> */

template <class T>
class List : NoCopy
 {
   struct Node : NoCopy
    {
     SLink<Node> link;

     T obj;

     explicit Node(const T &obj_) : obj(obj_) {}
    };

   using Algo = typename SLink<Node>::template LinearAlgo<&Node::link> ;

   typename Algo::Top list;

  public:

   List() {}

   template <class Pool>
   void add(Pool &pool,const T &obj)
    {
     Node *node=pool.template create<Node>(obj);

     list.ins(node);
    }

   template <class Func>
   void apply(Func func) const
    {
     for(auto cur=list.start(); +cur ;++cur)
       {
        func(cur->obj);
       }
    }

   template <class Func>
   bool applyWhile(Func func) const
    {
     for(auto cur=list.start(); +cur ;++cur)
       {
        if( !func(cur->obj) ) return false;
       }

     return true;
    }
 };

/* class Stack<T> */

template <class T>
class Stack : NoCopy
 {
   DynArray<T> buf;

  private:

   void guardEmpty()
    {
     if( isEmpty() ) GuardStackEmpty();
    }

  public:

   Stack() : buf(DoReserve,1000) {}

   ~Stack() {}

   bool isEmpty() const { return buf.isEmpty(); }

   bool notEmpty() const { return buf.notEmpty(); }

   void push(const T &obj) { buf.append_copy(obj); }

   T top()
    {
     guardEmpty();

     ulen len=buf.getLen();

     return buf[len-1];
    }

   void pop() { buf.shrink_one(); }
 };

/* class DataProc */

class DataProc : public Funchor_nocopy
 {
   FileProc &file_proc;

   DataFile data;

   ElementPool pool;
   StrLen file_name;
   StrLen wdir;

   struct TimeNode : NoCopy
    {
     RBTreeLink<TimeNode,StrKey> link;

     CmpFileTimeType time;
    };

   using TreeAlgo = RBTreeLink<TimeNode,StrKey>::Algo<&TimeNode::link,const StrKey &> ;

   enum State
    {
     StateInitial,
     StateLocked,
     StateOk,
     StateRebuild
    };

   struct TRec : NoCopy
    {
     TypeDef::Rule *rule = 0 ;

     List<TypeDef::Dep *> deps;

     State state = StateInitial ;

     TimeNode *time_node = 0 ;
    };

   DynArray<TRec *> trecs;

   TreeAlgo::Root root;

  private:

   TRec * getRec(TypeDef::Target *obj);

   void add(TypeDef::Target *dst,TypeDef::Rule *rule);

   void add(TypeDef::Target *dst,TypeDef::Dep *dep);

   void prepare(OneOfTypes<TypeDef::Rule,TypeDef::Dep> *obj);

   void prepare();

  private:

   TypeDef::Rule * getRule(TypeDef::Target *obj);

   template <class Func>
   void applyToDeps(TypeDef::Target *obj,Func func);

   template <class Func>
   static bool ApplyToSrc(OneOfTypes<TypeDef::Rule,TypeDef::Dep> *obj,Func func);

   template <class Func>
   bool applyToSrc(TypeDef::Target *obj,Func func);

  private:

   bool checkExist(StrLen dst);

   bool checkOlder(StrLen dst,StrLen src);

   TimeNode * findNode(StrLen file);

   CmpFileTimeType getFileTime(TypeDef::Target *obj);

   bool checkOlderCache(TypeDef::Target *dst,TypeDef::Target *src);

   bool checkOlder(TypeDef::Target *dst,TypeDef::Target *src,bool nofile);

   bool checkSelf(TypeDef::Target *dst);

   bool checkOlderSrc(TypeDef::Target *dst,bool nofile);

   void finish(TypeDef::Target *obj);

   void buildWorkTree();

  private:

   struct RRec : NoCopy
    {
     bool done = false ;
    };

   DynArray<RRec *> rrecs;

   DynArray<TypeDef::Target *> works;

   bool exe_ok = true ;

  private:

   template <class T,class R>
   R * getRec(T *obj,DynArray<R *> &list);

   RRec * getRec(TypeDef::Rule *obj);

   void addWork(TypeDef::Target *obj);

   bool dstReady(TypeDef::Target *obj);

   bool canRun(TypeDef::Rule *obj);

   bool checkSelf(StrLen file);

   bool checkRebuild(TypeDef::Target *obj);

   bool checkRebuild(TypeDef::Target *obj,TRec *rec);

   int exeRule(TypeDef::Rule *rule);

   void completeRule(TypeDef::Target *obj);

   void completeRule(TypeDef::Rule *rule);

   struct GetRuleResult
    {
     bool commit;
     TypeDef::Rule *rule;
    };

   GetRuleResult tryCommit(TypeDef::Target *obj);

   bool commit(TypeDef::Target *obj);

   int commit();

   void finishRule(TypeDef::Rule *rule,int status);

   CompleteFunction function_finishRule() { return FunctionOf(this,&DataProc::finishRule); }

   void exeRuleList(PtrLen<ExeRule> rules,ExeRule * buf[]);

   int commitPExe();

  public:

   DataProc(FileProc &file_proc,StrLen file_name,StrLen target);

   DataProc(FileProc &file_proc,StrLen file_name,StrLen target,StrLen wdir);

   ~DataProc();

   int make(); // one-time call
 };

} // namespace VMake
} // namespace App

#endif

