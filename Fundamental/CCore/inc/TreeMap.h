/* TreeMap.h */
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

#ifndef CCore_inc_TreeMap_h
#define CCore_inc_TreeMap_h

#include <CCore/inc/NodeAllocator.h>
#include <CCore/inc/Tree.h>
#include <CCore/inc/FunctorType.h>

#include <CCore/inc/algon/ApplyToRange.h>

namespace CCore {

/* function */

void GuardKeyOutOfRange();

/* concept RBTreeMapKeyTypes<K,KRef> */

template <class K,class KRef>
concept bool RBTreeMapKeyTypes = RBTreeKeyTypes<K,KRef> && requires(const KRef &ref) { K(ref); } ;

/* classes */

template <NothrowDtorType K,NothrowDtorType T,class KRef=K,template <class Node> class Allocator=NodeAllocator> requires ( RBTreeMapKeyTypes<K,KRef> ) class RBTreeMap;

template <UIntType K> struct KeyRange;

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator=NodeAllocator> class RadixTreeMap;

/* class RBTreeMap<K,T,KRef,Allocator> */

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
class RBTreeMap : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     RBTreeLink<Node,K> link;
     T obj;

     template <class ... SS>
     explicit Node(const KRef &key,SS && ... ss) : link(key),obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename RBTreeLink<Node,K>::template Algo<&Node::link,KRef,NoCopyKey> ;

   Allocator<Node> allocator;

   typename Algo::Root root;

  private:

   void destroy(Node *node);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

   static const K & GetKey(Node *node)
    {
     return Algo::Link(node).key;
    }

   static const K & GetKey(Node &node)
    {
     return Algo::Link(&node).key;
    }

  public:

   // constructors

   template <class ... SS>
   explicit RBTreeMap(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~RBTreeMap() { erase(); }

   // std move

   RBTreeMap(RBTreeMap &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      root(Replace_null(obj.root))
    {
    }

   RBTreeMap & operator = (RBTreeMap &&obj) noexcept
    {
     if( this!=&obj )
       {
        erase();

        allocator=std::move(obj.allocator);
        root=Replace_null(obj.root);
       }

     return *this;
    }

   // props

   ulen operator + () const { return +allocator; }

   bool operator ! () const { return !allocator; }

   ulen getCount() const { return allocator.getCount(); }

   // find

   T * find(KRef key) { return GetObject(root.find(key)); }

   T * findMin() { return GetObject(root.findMin()); }

   T * findMin(KRef key) { return GetObject(root.findMin(key)); }

   T * findMax() { return GetObject(root.findMax()); }

   T * findMax(KRef key) { return GetObject(root.findMax(key)); }


   const T * find(KRef key) const { return GetObject(root.find(key)); }

   const T * findMin() const { return GetObject(root.findMin()); }

   const T * findMin(KRef key) const { return GetObject(root.findMin(key)); }

   const T * findMax() const { return GetObject(root.findMax()); }

   const T * findMax(KRef key) const { return GetObject(root.findMax(key)); }


   const T * find_const(KRef key) const { return GetObject(root.find(key)); }

   const T * findMin_const() const { return GetObject(root.findMin()); }

   const T * findMin_const(KRef key) const { return GetObject(root.findMin(key)); }

   const T * findMax_const() const { return GetObject(root.findMax()); }

   const T * findMax_const(KRef key) const { return GetObject(root.findMax(key)); }


   template <class S>
   struct NodePtr
    {
     Node *node;

     NodePtr() : node(0) {}

     NodePtr(Node *node_) : node(node_) {}

     // object ptr

     Node * operator + () const { return node; }

     bool operator ! () const { return !node; }

     S * getPtr() const { return &node->obj; }

     S & operator * () const { return node->obj; }

     S * operator -> () const { return &node->obj; }

     const K & getKey() const { return GetKey(node); }
    };


   NodePtr<T> find_ptr(KRef key) { return root.find(key); }

   NodePtr<T> findMin_ptr() { return root.findMin(); }

   NodePtr<T> findMin_ptr(KRef key) { return root.findMin(key); }

   NodePtr<T> findMax_ptr() { return root.findMax(); }

   NodePtr<T> findMax_ptr(KRef key) { return root.findMax(key); }


   NodePtr<const T> find_ptr(KRef key) const { return root.find(key); }

   NodePtr<const T> findMin_ptr() const { return root.findMin(); }

   NodePtr<const T> findMin_ptr(KRef key) const { return root.findMin(key); }

   NodePtr<const T> findMax_ptr() const { return root.findMax(); }

   NodePtr<const T> findMax_ptr(KRef key) const { return root.findMax(key); }


   NodePtr<const T> find_ptr_const(KRef key) const { return root.find(key); }

   NodePtr<const T> findMin_ptr_const() const { return root.findMin(); }

   NodePtr<const T> findMin_ptr_const(KRef key) const { return root.findMin(key); }

   NodePtr<const T> findMax_ptr_const() const { return root.findMax(); }

   NodePtr<const T> findMax_ptr_const(KRef key) const { return root.findMax(key); }

   // add/del

   struct Result
    {
     const K *key;
     T *obj;
     bool new_flag;

     Result(const K *key_,T *obj_,bool new_flag_) : key(key_),obj(obj_),new_flag(new_flag_) {}

     operator T * () const { return obj; }
    };

   template <class ... SS>
   Result find_or_add(KRef key,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   bool del(KRef key);

   bool delMin();

   bool delMax();

   template <class S>
   bool del(NodePtr<S> node_ptr);

   ulen erase();

   // apply

   template <FuncInitArgType<const K &,T &> FuncInit>
   auto applyIncr(FuncInit func_init);

   template <FuncInitArgType<const K &,T &> FuncInit>
   auto applyDecr(FuncInit func_init);

   template <FuncInitArgType<const K &,const T &> FuncInit>
   auto applyIncr(FuncInit func_init) const;

   template <FuncInitArgType<const K &,const T &> FuncInit>
   auto applyDecr(FuncInit func_init) const;

   template <FuncInitArgType<const K &,const T &> FuncInit>
   auto applyIncr_const(FuncInit func_init) const { return applyIncr(func_init); }

   template <FuncInitArgType<const K &,const T &> FuncInit>
   auto applyDecr_const(FuncInit func_init) const { return applyDecr(func_init); }

   // swap/move objects

   void objSwap(RBTreeMap<K,T,KRef,Allocator> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(root,obj.root);
    }

   explicit RBTreeMap(ToMoveCtor<RBTreeMap<K,T,KRef,Allocator> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      root(Replace_null(obj->root))
    {
    }
 };

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
void RBTreeMap<K,T,KRef,Allocator>::destroy(Node *node)
 {
  if( node )
    {
     destroy(Algo::Link(node).lo);
     destroy(Algo::Link(node).hi);

     allocator.free_nonnull(node);
    }
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
template <class ... SS>
auto RBTreeMap<K,T,KRef,Allocator>::find_or_add(KRef key,SS && ... ss) -> Result requires ( ConstructibleType<T,SS...> )
 {
  typename Algo::PrepareIns prepare(root,key);

  if( Node *node=prepare.found ) return Result(&GetKey(node),&node->obj,false);

  Node *node=allocator.alloc( key , std::forward<SS>(ss)... );

  prepare.complete(node);

  return Result(&GetKey(node),&node->obj,true);
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
bool RBTreeMap<K,T,KRef,Allocator>::del(KRef key)
 {
  return allocator.free(root.del(key));
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
bool RBTreeMap<K,T,KRef,Allocator>::delMin()
 {
  return allocator.free(root.delMin());
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
bool RBTreeMap<K,T,KRef,Allocator>::delMax()
 {
  return allocator.free(root.delMax());
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
template <class S>
bool RBTreeMap<K,T,KRef,Allocator>::del(NodePtr<S> node_ptr)
 {
  if( Node *node=node_ptr.node )
    {
     root.del(node);

     allocator.free_nonnull(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
ulen RBTreeMap<K,T,KRef,Allocator>::erase()
 {
  Node *ptr=root.root;

  root.init();

  ulen ret=getCount();

  destroy(ptr);

  return ret;
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
template <FuncInitArgType<const K &,T &> FuncInit>
auto RBTreeMap<K,T,KRef,Allocator>::applyIncr(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start(), [&func] (Node &node) { return func(GetKey(node),node.obj); } );

  return Algon::GetResult(func);
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
template <FuncInitArgType<const K &,T &> FuncInit>
auto RBTreeMap<K,T,KRef,Allocator>::applyDecr(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start_rev(), [&func] (Node &node) { return func(GetKey(node),node.obj); } );

  return Algon::GetResult(func);
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
template <FuncInitArgType<const K &,const T &> FuncInit>
auto RBTreeMap<K,T,KRef,Allocator>::applyIncr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start(), [&func] (Node &node) { return func(GetKey(node),(const T &)node.obj); } );

  return Algon::GetResult(func);
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef,template <class Node> class Allocator> requires ( RBTreeMapKeyTypes<K,KRef> )
template <FuncInitArgType<const K &,const T &> FuncInit>
auto RBTreeMap<K,T,KRef,Allocator>::applyDecr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start_rev(), [&func] (Node &node) { return func(GetKey(node),(const T &)node.obj); } );

  return Algon::GetResult(func);
 }

/* struct KeyRange<K> */

template <UIntType K>
struct KeyRange
 {
  K kmin;
  K kmax;

  KeyRange() : kmin(0),kmax(MaxUInt<K>) {}

  explicit KeyRange(K kmax_) : kmin(0),kmax(kmax_) {}

  KeyRange(K kmin_,K kmax_) : kmin(kmin_),kmax(kmax_) {}

  void guard(K key) const
   {
    if( key<kmin || key>kmax ) GuardKeyOutOfRange();
   }
 };

/* class RadixTreeMap<K,T,Allocator> */

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
class RadixTreeMap : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     TreeLink<Node,K> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename TreeLink<Node,K>::template RadixAlgo<&Node::link> ;

   KeyRange<K> key_range;

   Allocator<Node> allocator;

   typename Algo::Root root;

  private:

   void destroy(Node *node);

   static T * GetObject(Node *node)
    {
     if( node ) return &node->obj;

     return 0;
    }

   static K GetKey(Node *node)
    {
     return Algo::Link(node).key;
    }

   static K GetKey(Node &node)
    {
     return Algo::Link(&node).key;
    }

  public:

   // constructors

   template <class ... SS>
   explicit RadixTreeMap(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   template <class ... SS>
   explicit RadixTreeMap(KeyRange<K> key_range_,SS && ... ss) noexcept : key_range(key_range_),allocator( std::forward<SS>(ss)... ) {}

   ~RadixTreeMap() { erase(); }

   // std move

   RadixTreeMap(RadixTreeMap &&obj) noexcept
    : key_range(obj.key_range),
      allocator(std::move(obj.allocator)),
      root(Replace_null(obj.root))
    {
    }

   RadixTreeMap & operator = (RadixTreeMap &&obj) noexcept
    {
     if( this!=&obj )
       {
        erase();

        key_range=obj.key_range;
        allocator=std::move(obj.allocator);
        root=Replace_null(obj.root);
       }

     return *this;
    }

   // props

   ulen operator + () const { return +allocator; }

   bool operator ! () const { return !allocator; }

   ulen getCount() const { return allocator.getCount(); }

   // find

   T * find(K key) { return GetObject(root.find(key)); }

   T * findMin() { return GetObject(root.findMin()); }

   T * findMin(K key) { return GetObject(root.findMin(key)); }

   T * findMax() { return GetObject(root.findMax()); }

   T * findMax(K key) { return GetObject(root.findMax(key)); }


   const T * find(K key) const { return GetObject(root.find(key)); }

   const T * findMin() const { return GetObject(root.findMin()); }

   const T * findMin(K key) const { return GetObject(root.findMin(key)); }

   const T * findMax() const { return GetObject(root.findMax()); }

   const T * findMax(K key) const { return GetObject(root.findMax(key)); }


   const T * find_const(K key) const { return GetObject(root.find(key)); }

   const T * findMin_const() const { return GetObject(root.findMin()); }

   const T * findMin_const(K key) const { return GetObject(root.findMin(key)); }

   const T * findMax_const() const { return GetObject(root.findMax()); }

   const T * findMax_const(K key) const { return GetObject(root.findMax(key)); }


   template <class S>
   struct NodePtr
    {
     Node *node;

     NodePtr() : node(0) {}

     NodePtr(Node *node_) : node(node_) {}

     // object ptr

     Node * operator + () const { return node; }

     bool operator ! () const { return !node; }

     S * getPtr() const { return &node->obj; }

     S & operator * () const { return node->obj; }

     S * operator -> () const { return &node->obj; }

     K getKey() const { return GetKey(node); }
    };


   NodePtr<T> find_ptr(K key) { return root.find(key); }

   NodePtr<T> findMin_ptr() { return root.findMin(); }

   NodePtr<T> findMin_ptr(K key) { return root.findMin(key); }

   NodePtr<T> findMax_ptr() { return root.findMax(); }

   NodePtr<T> findMax_ptr(K key) { return root.findMax(key); }


   NodePtr<const T> find_ptr(K key) const { return root.find(key); }

   NodePtr<const T> findMin_ptr() const { return root.findMin(); }

   NodePtr<const T> findMin_ptr(K key) const { return root.findMin(key); }

   NodePtr<const T> findMax_ptr() const { return root.findMax(); }

   NodePtr<const T> findMax_ptr(K key) const { return root.findMax(key); }


   NodePtr<const T> find_ptr_const(K key) const { return root.find(key); }

   NodePtr<const T> findMin_ptr_const() const { return root.findMin(); }

   NodePtr<const T> findMin_ptr_const(K key) const { return root.findMin(key); }

   NodePtr<const T> findMax_ptr_const() const { return root.findMax(); }

   NodePtr<const T> findMax_ptr_const(K key) const { return root.findMax(key); }

   // add/del

   struct Result
    {
     T *obj;
     bool new_flag;

     Result(T *obj_,bool new_flag_) : obj(obj_),new_flag(new_flag_) {}

     operator T * () const { return obj; }
    };

   template <class ... SS>
   Result find_or_add(K key,SS && ... ss) requires ( ConstructibleType<T,SS...> ) ;

   bool del(K key);

   bool delMin();

   bool delMax();

   template <class S>
   bool del(NodePtr<S> node_ptr);

   ulen erase();

   // apply

   template <FuncInitArgType<K,T &> FuncInit>
   auto applyIncr(FuncInit func_init);

   template <FuncInitArgType<K,T &> FuncInit>
   auto applyDecr(FuncInit func_init);

   template <FuncInitArgType<K,const T &> FuncInit>
   auto applyIncr(FuncInit func_init) const;

   template <FuncInitArgType<K,const T &> FuncInit>
   auto applyDecr(FuncInit func_init) const;

   template <FuncInitArgType<K,const T &> FuncInit>
   auto applyIncr_const(FuncInit func_init) const { return applyIncr(func_init); }

   template <FuncInitArgType<K,const T &> FuncInit>
   auto applyDecr_const(FuncInit func_init) const { return applyDecr(func_init); }

   // delIf

   template <FuncInitType<bool,K,T &> FuncInit>
   void delIf(FuncInit func_init);

   // swap/move objects

   void objSwap(RadixTreeMap<K,T,Allocator> &obj)
    {
     Swap(key_range,obj.key_range);
     Swap(allocator,obj.allocator);
     Swap(root,obj.root);
    }

   explicit RadixTreeMap(ToMoveCtor<RadixTreeMap<K,T,Allocator> > obj)
    : key_range(obj->key_range),
      allocator(ToMoveCtor(obj->allocator)),
      root(Replace_null(obj->root))
    {
    }
 };

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
void RadixTreeMap<K,T,Allocator>::destroy(Node *node)
 {
  if( node )
    {
     destroy(Algo::Link(node).lo);
     destroy(Algo::Link(node).hi);

     allocator.free_nonnull(node);
    }
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
template <class ... SS>
auto RadixTreeMap<K,T,Allocator>::find_or_add(K key,SS && ... ss) -> Result requires ( ConstructibleType<T,SS...> )
 {
  key_range.guard(key);

  typename Algo::PrepareIns prepare(root,key,key_range.kmin,key_range.kmax);

  if( Node *node=prepare.found ) return Result(&node->obj,false);

  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  prepare.complete(node);

  return Result(&node->obj,true);
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
bool RadixTreeMap<K,T,Allocator>::del(K key)
 {
  return allocator.free(root.del(key));
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
bool RadixTreeMap<K,T,Allocator>::delMin()
 {
  return allocator.free(root.delMin());
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
bool RadixTreeMap<K,T,Allocator>::delMax()
 {
  return allocator.free(root.delMax());
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
template <class S>
bool RadixTreeMap<K,T,Allocator>::del(NodePtr<S> node_ptr)
 {
  if( Node *node=node_ptr.node )
    {
     root.del(node);

     allocator.free_nonnull(node);

     return true;
    }

  return false;
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
ulen RadixTreeMap<K,T,Allocator>::erase()
 {
  Node *ptr=root.root;

  root.init();

  ulen ret=getCount();

  destroy(ptr);

  return ret;
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
template <FuncInitArgType<K,T &> FuncInit>
auto RadixTreeMap<K,T,Allocator>::applyIncr(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start(), [&func] (Node &node) { return func(GetKey(node),node.obj); } );

  return Algon::GetResult(func);
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
template <FuncInitArgType<K,T &> FuncInit>
auto RadixTreeMap<K,T,Allocator>::applyDecr(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start_rev(), [&func] (Node &node) { return func(GetKey(node),node.obj); } );

  return Algon::GetResult(func);
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
template <FuncInitArgType<K,const T &> FuncInit>
auto RadixTreeMap<K,T,Allocator>::applyIncr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start(), [&func] (Node &node) { return func(GetKey(node),(const T &)node.obj); } );

  return Algon::GetResult(func);
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
template <FuncInitArgType<K,const T &> FuncInit>
auto RadixTreeMap<K,T,Allocator>::applyDecr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start_rev(), [&func] (Node &node) { return func(GetKey(node),(const T &)node.obj); } );

  return Algon::GetResult(func);
 }

template <UIntType K,NothrowDtorType T,template <class Node> class Allocator>
template <FuncInitType<bool,K,T &> FuncInit>
void RadixTreeMap<K,T,Allocator>::delIf(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  root.delIf( [&] (Node *node) { return func(GetKey(node),node->obj); } , [this] (Node *node) { allocator.free_nonnull(node); } );
 }

} // namespace CCore

#endif


