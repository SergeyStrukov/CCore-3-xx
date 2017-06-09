/* ContainerList.h */
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

#ifndef CCore_inc_ContainerList_h
#define CCore_inc_ContainerList_h

#include <CCore/inc/NodeAllocator.h>
#include <CCore/inc/List.h>
#include <CCore/inc/ListCursor.h>
#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* classes */

template <NothrowDtorType T,template <class Node> class Allocator=NodeAllocator> class LinearSList;

template <NothrowDtorType T,template <class Node> class Allocator=NodeAllocator> class LinearSList2;

template <NothrowDtorType T,template <class Node> class Allocator=NodeAllocator> class CircularSList;

template <NothrowDtorType T,template <class Node> class Allocator=NodeAllocator> class LinearDList;

template <NothrowDtorType T,template <class Node> class Allocator=NodeAllocator> class LinearDList2;

template <NothrowDtorType T,template <class Node> class Allocator=NodeAllocator> class CircularDList;

/* class LinearSList<T,Allocator> */

template <NothrowDtorType T,template <class Node> class Allocator>
class LinearSList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     SLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename SLink<Node>::template LinearAlgo<&Node::link> ;

   Allocator<Node> allocator;

   typename Algo::Top list;

  private:

   void destroy(Node *node);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

  public:

   // constructors

   template <class ... SS>
   explicit LinearSList(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~LinearSList() { erase(); }

   // std move

   LinearSList(LinearSList &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      list(Replace_null(obj.list))
    {
    }

   LinearSList & operator = (LinearSList &&obj) noexcept
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
   T * insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   bool del();

   ulen erase();

   // apply

   auto apply(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   // swap/move objects

   void objSwap(LinearSList<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }

   explicit LinearSList(ToMoveCtor<LinearSList<T,Allocator> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
 };

template <NothrowDtorType T,template <class Node> class Allocator>
void LinearSList<T,Allocator>::destroy(Node *node)
 {
  while( node )
    {
     Node *next=Algo::Link(node).next;

     allocator.free_nonnull(node);

     node=next;
    }
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
T * LinearSList<T,Allocator>::ins(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins(node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * LinearSList<T,Allocator>::insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
bool LinearSList<T,Allocator>::del()
 {
  return allocator.free(list.del());
 }

template <NothrowDtorType T,template <class Node> class Allocator>
ulen LinearSList<T,Allocator>::erase()
 {
  Node *node=list.top;

  list.init();

  ulen ret=getCount();

  destroy(node);

  return ret;
 }

/* class LinearSList2<T,Allocator> */

template <NothrowDtorType T,template <class Node> class Allocator>
class LinearSList2 : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     SLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename SLink<Node>::template LinearAlgo<&Node::link> ;

   Allocator<Node> allocator;

   typename Algo::FirstLast list;

  private:

   void destroy(Node *node);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

  public:

   // constructors

   template <class ... SS>
   explicit LinearSList2(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~LinearSList2() { erase(); }

   // std move

   LinearSList2(LinearSList2 &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      list(Replace_null(obj.list))
    {
    }

   LinearSList2 & operator = (LinearSList2 &&obj) noexcept
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
   using CountCur = ListCountCursor<typename Algo::Cur,S> ;

   CountCur<T> begin() { return CountCur<T>(list.start(),getCount()); }

   ulen end() { return 0; }

   CountCur<const T> begin() const { return CountCur<const T>(list.start(),getCount()); }

   ulen end() const { return 0; }

   // ins/del

   template <class ... SS>
   T * insFirst(SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   template <class ... SS>
   T * insLast(SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   template <class S,class ... SS>
   T * insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   bool delFirst();

   ulen erase();

   // apply

   auto apply(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   // swap/move objects

   void objSwap(LinearSList2<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }

   explicit LinearSList2(ToMoveCtor<LinearSList2<T,Allocator> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
 };

template <NothrowDtorType T,template <class Node> class Allocator>
void LinearSList2<T,Allocator>::destroy(Node *node)
 {
  while( node )
    {
     Node *next=Algo::Link(node).next;

     allocator.free_nonnull(node);

     node=next;
    }
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
T * LinearSList2<T,Allocator>::insFirst(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_first(node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
T * LinearSList2<T,Allocator>::insLast(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_last(node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * LinearSList2<T,Allocator>::insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
bool LinearSList2<T,Allocator>::delFirst()
 {
  return allocator.free(list.del_first());
 }

template <NothrowDtorType T,template <class Node> class Allocator>
ulen LinearSList2<T,Allocator>::erase()
 {
  Node *node=list.first;

  list.init();

  ulen ret=getCount();

  destroy(node);

  return ret;
 }

/* class CircularSList<T,Allocator> */

template <NothrowDtorType T,template <class Node> class Allocator>
class CircularSList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     SLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename SLink<Node>::template CircularAlgo<&Node::link> ;

   Allocator<Node> allocator;

   typename Algo::Top list;

  private:

   void destroy(Node *node);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

  public:

   // constructors

   template <class ... SS>
   explicit CircularSList(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~CircularSList() { erase(); }

   // std move

   CircularSList(CircularSList &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      list(Replace_null(obj.list))
    {
    }

   CircularSList & operator = (CircularSList &&obj) noexcept
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

   T * getBottom() { return GetObject(list.bottom); }

   const T * getBottom() const { return GetObject(list.bottom); }

   const T * getBottom_const() const { return GetObject(list.bottom); }

   template <class S>
   using Cur = ListCursor<typename Algo::Cur,S> ;

   Cur<T> getStart() { return list.start(); }

   Cur<const T> getStart() const { return list.start(); }

   Cur<const T> getStart_const() const { return list.start(); }

   struct FreeCur
    {
     Node *node;

     FreeCur() : node(0) {}

     FreeCur(Node *bottom)
      {
       if( bottom )
         node=Algo::Link(bottom).next;
       else
         node=0;
      }

     Node * operator -> () const { return node; }

     void operator ++ () { node=Algo::Link(node).next; }
    };

   template <class S>
   using CountCur = ListCountCursor<FreeCur,S> ;

   CountCur<T> begin() { return CountCur<T>(list.bottom,getCount()); }

   ulen end() { return 0; }

   CountCur<const T> begin() const { return CountCur<const T>(list.bottom,getCount()); }

   ulen end() const { return 0; }

   // ins/del

   template <class ... SS>
   T * ins(SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   template <class S,class ... SS>
   T * insAfter(Cur<S> &pos,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ; // +pos

   bool del();

   ulen erase();

   T * rotate() { return GetObject(list.rotate()); } // return top element moved to bottom

   // apply

   auto apply(FuncInitArgType<T &> func_init) { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   auto apply_const(FuncInitArgType<const T &> func_init) const { return Algon::ApplyToRange(getStart(),func_init); }

   // swap/move objects

   void objSwap(CircularSList<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }

   explicit CircularSList(ToMoveCtor<CircularSList<T,Allocator> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
 };

template <NothrowDtorType T,template <class Node> class Allocator>
void CircularSList<T,Allocator>::destroy(Node *node)
 {
  if( !node ) return;

  node=Replace_null(Algo::Link(node).next);

  while( node )
    {
     Node *next=Algo::Link(node).next;

     allocator.free_nonnull(node);

     node=next;
    }
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
T * CircularSList<T,Allocator>::ins(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins(node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * CircularSList<T,Allocator>::insAfter(Cur<S> &pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
bool CircularSList<T,Allocator>::del()
 {
  return allocator.free(list.del());
 }

template <NothrowDtorType T,template <class Node> class Allocator>
ulen CircularSList<T,Allocator>::erase()
 {
  Node *node=list.bottom;

  list.init();

  ulen ret=getCount();

  destroy(node);

  return ret;
 }

/* class LinearDList<T,Allocator> */

template <NothrowDtorType T,template <class Node> class Allocator>
class LinearDList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename DLink<Node>::template LinearAlgo<&Node::link> ;

   Allocator<Node> allocator;

   typename Algo::Top list;

  private:

   void destroy(Node *node);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

  public:

   // constructors

   template <class ... SS>
   explicit LinearDList(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~LinearDList() { erase(); }

   // std move

   LinearDList(LinearDList &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      list(Replace_null(obj.list))
    {
    }

   LinearDList & operator = (LinearDList &&obj) noexcept
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

   void objSwap(LinearDList<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }

   explicit LinearDList(ToMoveCtor<LinearDList<T,Allocator> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
 };

template <NothrowDtorType T,template <class Node> class Allocator>
void LinearDList<T,Allocator>::destroy(Node *node)
 {
  while( node )
    {
     Node *next=Algo::Link(node).next;

     allocator.free_nonnull(node);

     node=next;
    }
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
T * LinearDList<T,Allocator>::ins(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins(node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * LinearDList<T,Allocator>::insBefore(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * LinearDList<T,Allocator>::insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
bool LinearDList<T,Allocator>::del()
 {
  return allocator.free(list.del());
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S>
void LinearDList<T,Allocator>::delAndMove(Cur<S> &pos)
 {
  allocator.free_nonnull(list.del_and_move(pos.cur));
 }

template <NothrowDtorType T,template <class Node> class Allocator>
ulen LinearDList<T,Allocator>::erase()
 {
  Node *node=list.top;

  list.init();

  ulen ret=getCount();

  destroy(node);

  return ret;
 }

/* class LinearDList2<T,Allocator> */

template <NothrowDtorType T,template <class Node> class Allocator>
class LinearDList2 : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename DLink<Node>::template LinearAlgo<&Node::link> ;

   Allocator<Node> allocator;

   typename Algo::FirstLast list;

  private:

   void destroy(Node *node);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

  public:

   // constructors

   template <class ... SS>
   explicit LinearDList2(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~LinearDList2() { erase(); }

   // std move

   LinearDList2(LinearDList2 &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      list(Replace_null(obj.list))
    {
    }

   LinearDList2 & operator = (LinearDList2 &&obj) noexcept
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

   void objSwap(LinearDList2<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }

   explicit LinearDList2(ToMoveCtor<LinearDList2<T,Allocator> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
 };

template <NothrowDtorType T,template <class Node> class Allocator>
void LinearDList2<T,Allocator>::destroy(Node *node)
 {
  while( node )
    {
     Node *next=Algo::Link(node).next;

     allocator.free_nonnull(node);

     node=next;
    }
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
T * LinearDList2<T,Allocator>::insFirst(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_first(node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
T * LinearDList2<T,Allocator>::insLast(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_last(node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * LinearDList2<T,Allocator>::insBefore(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * LinearDList2<T,Allocator>::insBefore(RevCur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * LinearDList2<T,Allocator>::insAfter(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * LinearDList2<T,Allocator>::insAfter(RevCur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
bool LinearDList2<T,Allocator>::delFirst()
 {
  return allocator.free(list.del_first());
 }

template <NothrowDtorType T,template <class Node> class Allocator>
bool LinearDList2<T,Allocator>::delLast()
 {
  return allocator.free(list.del_last());
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S>
void LinearDList2<T,Allocator>::delAndMove(Cur<S> &pos)
 {
  allocator.free_nonnull(list.del_and_move(pos.cur));
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S>
void LinearDList2<T,Allocator>::delAndMove(RevCur<S> &pos)
 {
  allocator.free_nonnull(list.del_and_move(pos.cur));
 }

template <NothrowDtorType T,template <class Node> class Allocator>
ulen LinearDList2<T,Allocator>::erase()
 {
  Node *node=list.first;

  list.init();

  ulen ret=getCount();

  destroy(node);

  return ret;
 }

/* class CircularDList<T,Allocator> */

template <NothrowDtorType T,template <class Node> class Allocator>
class CircularDList : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     DLink<Node> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename DLink<Node>::template CircularAlgo<&Node::link> ;

   Allocator<Node> allocator;

   typename Algo::Top list;

  private:

   void destroy(Node *node);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

  public:

   // constructors

   template <class ... SS>
   explicit CircularDList(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~CircularDList() { erase(); }

   // std move

   CircularDList(CircularDList &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      list(Replace_null(obj.list))
    {
    }

   CircularDList & operator = (CircularDList &&obj) noexcept
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

   void objSwap(CircularDList<T,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(list,obj.list);
    }

   explicit CircularDList(ToMoveCtor<CircularDList<T,Allocator> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      list(Replace_null(obj->list))
    {
    }
 };

template <NothrowDtorType T,template <class Node> class Allocator>
void CircularDList<T,Allocator>::destroy(Node *node)
 {
  if( !node ) return;

  node=Replace_null(Algo::Link(node).next);

  while( node )
    {
     Node *next=Algo::Link(node).next;

     allocator.free_nonnull(node);

     node=next;
    }
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
T * CircularDList<T,Allocator>::insFirst(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_first(node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
T * CircularDList<T,Allocator>::insLast(SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_last(node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * CircularDList<T,Allocator>::insBefore(Cur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * CircularDList<T,Allocator>::insBefore(RevCur<S> &pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_before(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * CircularDList<T,Allocator>::insAfter(Cur<S> &pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S,class ... SS>
T * CircularDList<T,Allocator>::insAfter(RevCur<S> pos,SS && ... ss) requires ( ConstructibleType<T,SS...> )
 {
  Node *node=allocator.alloc( std::forward<SS>(ss) ... );

  list.ins_after(pos.cur,node);

  return &node->obj;
 }

template <NothrowDtorType T,template <class Node> class Allocator>
bool CircularDList<T,Allocator>::delFirst()
 {
  return allocator.free(list.del_first());
 }

template <NothrowDtorType T,template <class Node> class Allocator>
bool CircularDList<T,Allocator>::delLast()
 {
  return allocator.free(list.del_last());
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S>
void CircularDList<T,Allocator>::delAndMove(Cur<S> &pos)
 {
  allocator.free_nonnull(list.del_and_move(pos.cur));
 }

template <NothrowDtorType T,template <class Node> class Allocator>
template <class S>
void CircularDList<T,Allocator>::delAndMove(RevCur<S> &pos)
 {
  allocator.free_nonnull(list.del_and_move(pos.cur));
 }

template <NothrowDtorType T,template <class Node> class Allocator>
ulen CircularDList<T,Allocator>::erase()
 {
  Node *node=list.top;

  list.init();

  ulen ret=getCount();

  destroy(node);

  return ret;
 }

} // namespace CCore

#endif



