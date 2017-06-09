/* CompactList.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Fundamental Mini
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_CompactList_h
#define CCore_inc_CompactList_h

#include <CCore/inc/CompactNodeAllocator.h>
#include <CCore/inc/List.h>
#include <CCore/inc/ListCursor.h>
#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* classes */

template <NothrowDtorType T> class CompactList;

template <NothrowDtorType T> class CompactList2;

template <NothrowDtorType T> class CompactCircularList;

/* class CompactList<T> */

template <NothrowDtorType T>
class CompactList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename DLink<Node>::template LinearAlgo<&Node::link> ;

   CompactNodeAllocator<Node> allocator;

   typename Algo::Top list;

  private:

   void delNode(Node *node);

   void delNode(Node *node,typename Algo::Cur &cur);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

  public:

   // constructors

   template <class ... SS>
   explicit CompactList(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~CompactList() { erase(); }

   // std move

   CompactList(CompactList &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      list(Replace_null(obj.list))
    {
    }

   CompactList & operator = (CompactList &&obj) noexcept
    {
     if( this!=&obj )
       {
        erase();

        allocator=std::move(obj.allocator);
        list=Replace_null(obj.list);
       }

     return *this;
    }

   // props

   ulen operator + () const { return +allocator; }

   bool operator ! () const { return !allocator; }

   ulen getCount() const { return allocator.getCount(); }

   // content

   T * getTop() { return GetObject(list.top); }

   const T * getTop() const { return GetObject(list.top); }

   const T * getTop_const() const { return GetObject(list.top); }

   template <class S>
   using Cur = ListCursor<typename Algo::Cur,S> ;

   Cur<T> getStart() { return list.start(); }

   Cur<const T> getStart() const { return list.start(); }

   Cur<const T> getStart_const() const { return list.start(); }

   template <class S>
   using CountCur = ListCountCursor<typename Algo::Cur,S> ;

   CountCur<T> begin() { return CountCur<T>(list.start(),getCount()); }

   ulen end() { return 0; }

   CountCur<const T> begin() const { return CountCur<const T>(list.start(),getCount()); }

   ulen end() const { return 0; }

   // ins/del

   template <class ... SS>
   T * ins(SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   template <class S,class ... SS>
   T * insBefore(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   template <class S,class ... SS>
   T * insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   bool del();

   template <class S>
   void delAndMove(Cur<S> &pos); // +pos

   ulen erase();

   // apply

   auto apply(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   // swap/move objects

   void objSwap(CompactList<T> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }

   explicit CompactList(ToMoveCtor<CompactList<T> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      list(obj->list)
    {
    }
 };

template <NothrowDtorType T>
void CompactList<T>::delNode(Node *node)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     list.replace(todel,node);

     Swap(node->obj,todel->obj);
    }

  allocator.del();
 }

template <NothrowDtorType T>
void CompactList<T>::delNode(Node *node,typename Algo::Cur &cur)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     list.replace(todel,node);

     if( cur.ptr==todel ) cur.ptr=node;

     Swap(node->obj,todel->obj);
    }

  allocator.del();
 }

template <NothrowDtorType T>
template <class ... SS>
T * CompactList<T>::ins(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins(node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactList<T>::insBefore(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactList<T>::insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
bool CompactList<T>::del()
 {
  if( Node *node=list.del() )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType T>
template <class S>
void CompactList<T>::delAndMove(Cur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);

  delNode(node,pos.cur);
 }

template <NothrowDtorType T>
ulen CompactList<T>::erase()
 {
  list.init();

  return allocator.erase();
 }

/* class CompactList2<T> */

template <NothrowDtorType T>
class CompactList2 : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename DLink<Node>::template LinearAlgo<&Node::link> ;

   CompactNodeAllocator<Node> allocator;

   typename Algo::FirstLast list;

  private:

   void delNode(Node *node);

   void delNode(Node *node,typename Algo::Cur &cur);

   void delNode(Node *node,typename Algo::RevCur &cur);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

  public:

   // constructors

   template <class ... SS>
   explicit CompactList2(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~CompactList2() { erase(); }

   // std move

   CompactList2(CompactList2 &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      list(Replace_null(obj.list))
    {
    }

   CompactList2 & operator = (CompactList2 &&obj) noexcept
    {
     if( this!=&obj )
       {
        erase();

        allocator=std::move(obj.allocator);
        list=Replace_null(obj.list);
       }

     return *this;
    }

   // props

   ulen operator + () const { return +allocator; }

   bool operator ! () const { return !allocator; }

   ulen getCount() const { return allocator.getCount(); }

   // content

   T * getFirst() { return GetObject(list.first); }

   const T * getFirst() const { return GetObject(list.first); }

   const T * getFirst_const() const { return GetObject(list.first); }

   T * getLast() { return GetObject(list.last); }

   const T * getLast() const { return GetObject(list.last); }

   const T * getLast_const() const { return GetObject(list.last); }

   template <class S>
   using Cur = ListCursor<typename Algo::Cur,S> ;

   Cur<T> getStart() { return list.start(); }

   Cur<const T> getStart() const { return list.start(); }

   Cur<const T> getStart_const() const { return list.start(); }

   template <class S>
   using RevCur = ListCursor<typename Algo::RevCur,S> ;

   RevCur<T> getStartReverse() { return list.start_rev(); }

   RevCur<const T> getStartReverse() const { return list.start_rev(); }

   RevCur<const T> getStartReverse_const() const { return list.start_rev(); }

   template <class S>
   using CountCur = ListCountCursor<typename Algo::Cur,S> ;

   CountCur<T> begin() { return CountCur<T>(list.start(),getCount()); }

   ulen end() { return 0; }

   CountCur<const T> begin() const { return CountCur<const T>(list.start(),getCount()); }

   ulen end() const { return 0; }

   template <class S>
   using RevCountCur = ListCountCursor<typename Algo::RevCur,S> ;

   RevCountCur<T> rbegin() { return RevCountCur<T>(list.start_rev(),getCount()); }

   ulen rend() { return 0; }

   RevCountCur<const T> rbegin() const { return RevCountCur<const T>(list.start_rev(),getCount()); }

   ulen rend() const { return 0; }

   template <class S>
   struct ReverseAdapter
    {
     RevCountCur<S> cur;

     ReverseAdapter(const RevCountCur<S> &cur_) : cur(cur_) {}

     RevCountCur<S> begin() const { return cur; }

     ulen end() const { return 0; }
    };

   ReverseAdapter<T> reverse() { return rbegin(); }

   ReverseAdapter<const T> reverse() const { return rbegin(); }

   ReverseAdapter<const T> reverse_const() const { return rbegin(); }

   // ins/del

   template <class ... SS>
   T * insFirst(SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   template <class ... SS>
   T * insLast(SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   template <class S,class ... SS>
   T * insBefore(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   template <class S,class ... SS>
   T * insBefore(RevCur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   template <class S,class ... SS>
   T * insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   template <class S,class ... SS>
   T * insAfter(RevCur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   bool delFirst();

   bool delLast();

   template <class S>
   void delAndMove(Cur<S> &pos); // +pos

   template <class S>
   void delAndMove(RevCur<S> &pos); // +pos

   ulen erase();

   // apply

   auto apply(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   auto applyReverse(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(getStartReverse(),func_init); }

   auto applyReverse(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStartReverse(),func_init); }

   auto applyReverse_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStartReverse(),func_init); }

   // swap/move objects

   void objSwap(CompactList2<T> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }

   explicit CompactList2(ToMoveCtor<CompactList2<T> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      list(obj->list)
    {
    }
 };

template <NothrowDtorType T>
void CompactList2<T>::delNode(Node *node)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     list.replace(todel,node);

     Swap(node->obj,todel->obj);
    }

  allocator.del();
 }

template <NothrowDtorType T>
void CompactList2<T>::delNode(Node *node,typename Algo::Cur &cur)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     list.replace(todel,node);

     if( cur.ptr==todel ) cur.ptr=node;

     Swap(node->obj,todel->obj);
    }

  allocator.del();
 }

template <NothrowDtorType T>
void CompactList2<T>::delNode(Node *node,typename Algo::RevCur &cur)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     list.replace(todel,node);

     if( cur.ptr==todel ) cur.ptr=node;

     Swap(node->obj,todel->obj);
    }

  allocator.del();
 }

template <NothrowDtorType T>
template <class ... SS>
T * CompactList2<T>::insFirst(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_first(node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class ... SS>
T * CompactList2<T>::insLast(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_last(node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactList2<T>::insBefore(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactList2<T>::insBefore(RevCur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactList2<T>::insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactList2<T>::insAfter(RevCur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
bool CompactList2<T>::delFirst()
 {
  if( Node *node=list.del_first() )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType T>
bool CompactList2<T>::delLast()
 {
  if( Node *node=list.del_last() )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType T>
template <class S>
void CompactList2<T>::delAndMove(Cur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);

  delNode(node,pos.cur);
 }

template <NothrowDtorType T>
template <class S>
void CompactList2<T>::delAndMove(RevCur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);

  delNode(node,pos.cur);
 }

template <NothrowDtorType T>
ulen CompactList2<T>::erase()
 {
  list.init();

  return allocator.erase();
 }

/* class CompactCircularList<T> */

template <NothrowDtorType T>
class CompactCircularList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename DLink<Node>::template CircularAlgo<&Node::link> ;

   CompactNodeAllocator<Node> allocator;

   typename Algo::Top list;

  private:

   void delNode(Node *node);

   void delNode(Node *node,typename Algo::Cur &cur);

   void delNode(Node *node,typename Algo::RevCur &cur);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

  public:

   // constructors

   template <class ... SS>
   explicit CompactCircularList(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~CompactCircularList() { erase(); }

   // std move

   CompactCircularList(CompactCircularList &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      list(Replace_null(obj.list))
    {
    }

   CompactCircularList & operator = (CompactCircularList &&obj) noexcept
    {
     if( this!=&obj )
       {
        erase();

        allocator=std::move(obj.allocator);
        list=Replace_null(obj.list);
       }

     return *this;
    }

   // props

   ulen operator + () const { return +allocator; }

   bool operator ! () const { return !allocator; }

   ulen getCount() const { return allocator.getCount(); }

   // content

   T * getTop() { return GetObject(list.top); }

   const T * getTop() const { return GetObject(list.top); }

   const T * getTop_const() const { return GetObject(list.top); }

   template <class S>
   using Cur = ListCursor<typename Algo::Cur,S> ;

   Cur<T> getStart() { return list.start(); }

   Cur<const T> getStart() const { return list.start(); }

   Cur<const T> getStart_const() const { return list.start(); }

   template <class S>
   using RevCur = ListCursor<typename Algo::RevCur,S> ;

   RevCur<T> getStartReverse() { return list.start_rev(); }

   RevCur<const T> getStartReverse() const { return list.start_rev(); }

   RevCur<const T> getStartReverse_const() const { return list.start_rev(); }

   struct FreeCur
    {
     Node *node;

     FreeCur() : node(0) {}

     FreeCur(Node *node_) : node(node_) {}

     Node * operator -> () const { return node; }

     void operator ++ () { node=Algo::Link(node).next; }
    };

   template <class S>
   using CountCur = ListCountCursor<FreeCur,S> ;

   CountCur<T> begin() { return CountCur<T>(list.top,getCount()); }

   ulen end() { return 0; }

   CountCur<const T> begin() const { return CountCur<const T>(list.top,getCount()); }

   ulen end() const { return 0; }

   struct RevFreeCur
    {
     Node *node;

     RevFreeCur() : node(0) {}

     RevFreeCur(Node *top)
      {
       if( top )
         node=Algo::Link(top).prev;
       else
         node=0;
      }

     Node * operator -> () const { return node; }

     void operator ++ () { node=Algo::Link(node).prev; }
    };

   template <class S>
   using RevCountCur = ListCountCursor<RevFreeCur,S> ;

   RevCountCur<T> rbegin() { return RevCountCur<T>(list.top,getCount()); }

   ulen rend() { return 0; }

   RevCountCur<const T> rbegin() const { return RevCountCur<const T>(list.top,getCount()); }

   ulen rend() const { return 0; }

   template <class S>
   struct ReverseAdapter
    {
     RevCountCur<S> cur;

     ReverseAdapter(RevCountCur<S> cur_) : cur(cur_) {}

     RevCountCur<S> begin() const { return cur; }

     ulen end() const { return 0; }
    };

   ReverseAdapter<T> reverse() { return rbegin(); }

   ReverseAdapter<const T> reverse() const { return rbegin(); }

   ReverseAdapter<const T> reverse_const() const { return rbegin(); }

   // ins/del

   template <class ... SS>
   T * insFirst(SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   template <class ... SS>
   T * insLast(SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   template <class S,class ... SS>
   T * insBefore(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   template <class S,class ... SS>
   T * insBefore(RevCur<S> &pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   template <class S,class ... SS>
   T * insAfter(Cur<S> &pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   template <class S,class ... SS>
   T * insAfter(RevCur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   bool delFirst();

   bool delLast();

   template <class S>
   void delAndMove(Cur<S> &pos); // +pos

   template <class S>
   void delAndMove(RevCur<S> &pos); // +pos

   ulen erase();

   T * rotateForward() { return GetObject(list.rotate_forward()); } // return top element moved to bottom

   T * rotateBackward() { return GetObject(list.rotate_backward()); } // return bottom element moved to top

   // apply

   auto apply(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   auto applyReverse(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(getStartReverse(),func_init); }

   auto applyReverse(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStartReverse(),func_init); }

   auto applyReverse_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStartReverse(),func_init); }

   // swap/move objects

   void objSwap(CompactCircularList<T> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }

   explicit CompactCircularList(ToMoveCtor<CompactCircularList<T> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
 };

template <NothrowDtorType T>
void CompactCircularList<T>::delNode(Node *node)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     list.replace(todel,node);

     Swap(node->obj,todel->obj);
    }

  allocator.del();
 }

template <NothrowDtorType T>
void CompactCircularList<T>::delNode(Node *node,typename Algo::Cur &cur)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     list.replace(todel,node);

     if( cur.ptr==todel ) cur.ptr=node;
     if( cur.last==todel ) cur.last=node;

     Swap(node->obj,todel->obj);
    }

  allocator.del();
 }

template <NothrowDtorType T>
void CompactCircularList<T>::delNode(Node *node,typename Algo::RevCur &cur)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     list.replace(todel,node);

     if( cur.ptr==todel ) cur.ptr=node;
     if( cur.first==todel ) cur.first=node;

     Swap(node->obj,todel->obj);
    }

  allocator.del();
 }

template <NothrowDtorType T>
template <class ... SS>
T * CompactCircularList<T>::insFirst(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_first(node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class ... SS>
T * CompactCircularList<T>::insLast(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_last(node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactCircularList<T>::insBefore(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactCircularList<T>::insBefore(RevCur<S> &pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactCircularList<T>::insAfter(Cur<S> &pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
template <class S,class ... SS>
T * CompactCircularList<T>::insAfter(RevCur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T>
bool CompactCircularList<T>::delFirst()
 {
  if( Node *node=list.del_first() )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType T>
bool CompactCircularList<T>::delLast()
 {
  if( Node *node=list.del_last() )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType T>
template <class S>
void CompactCircularList<T>::delAndMove(Cur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);

  delNode(node,pos.cur);
 }

template <NothrowDtorType T>
template <class S>
void CompactCircularList<T>::delAndMove(RevCur<S> &pos)
 {
  Node *node=list.del_and_move(pos.cur);

  delNode(node,pos.cur);
 }

template <NothrowDtorType T>
ulen CompactCircularList<T>::erase()
 {
  list.init();

  return allocator.erase();
 }

} // namespace CCore

#endif


