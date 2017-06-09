/* CompactMap.h */
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

#ifndef CCore_inc_CompactMap_h
#define CCore_inc_CompactMap_h

#include <CCore/inc/CompactNodeAllocator.h>
#include <CCore/inc/TreeMap.h>

namespace CCore {

/* classes */

template <NothrowDtorType K,NothrowDtorType T,class KRef=K> requires ( RBTreeMapKeyTypes<K,KRef> ) class CompactRBTreeMap;

template <UIntType K,NothrowDtorType T> class CompactRadixTreeMap;

/* class CompactRBTreeMap<K,T,KRef> */

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
class CompactRBTreeMap : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     RBTreeUpLink<Node,K> link;
     T obj;

     template <class ... SS>
     explicit Node(const KRef &key,SS && ... ss) : link(key),obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename RBTreeUpLink<Node,K>::template Algo<&Node::link,KRef,NoCopyKey> ;

   CompactNodeAllocator<Node> allocator;

   typename Algo::Root root;

  private:

   void delNode(Node *node);

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
   explicit CompactRBTreeMap(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   ~CompactRBTreeMap() { erase(); }

   // std move

   CompactRBTreeMap(CompactRBTreeMap &&obj) noexcept
    : allocator(std::move(obj.allocator)),
      root(Replace_null(obj.root))
    {
    }

   CompactRBTreeMap & operator = (CompactRBTreeMap &&obj) noexcept
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

   void objSwap(CompactRBTreeMap<K,T,KRef> &obj)
    {
     Swap(allocator,obj.allocator);
     Swap(root,obj.root);
    }

   explicit CompactRBTreeMap(ToMoveCtor<CompactRBTreeMap<K,T,KRef> > obj)
    : allocator(ToMoveCtor(obj->allocator)),
      root(obj->root)
    {
    }
 };

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
void CompactRBTreeMap<K,T,KRef>::delNode(Node *node)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     root.replace(todel,node);

     Swap(todel->obj,node->obj);
    }

  allocator.del();
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
template <class ... SS>
auto CompactRBTreeMap<K,T,KRef>::find_or_add(KRef key,SS && ... ss) -> Result requires ( ConstructibleType<T,SS...> )
 {
  typename Algo::PrepareIns prepare(root,key);

  if( Node *node=prepare.found ) return Result(&GetKey(node),&node->obj,false);

  Node *node=allocator.alloc( key , std::forward<SS>(ss)... );

  prepare.complete(node);

  return Result(&GetKey(node),&node->obj,true);
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
bool CompactRBTreeMap<K,T,KRef>::del(KRef key)
 {
  if( Node *node=root.del(key) )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
bool CompactRBTreeMap<K,T,KRef>::delMin()
 {
  if( Node *node=root.delMin() )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
bool CompactRBTreeMap<K,T,KRef>::delMax()
 {
  if( Node *node=root.delMax() )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
template <class S>
bool CompactRBTreeMap<K,T,KRef>::del(NodePtr<S> node_ptr)
 {
  if( Node *node=node_ptr.node )
    {
     root.del(node);

     delNode(node);

     return true;
    }

  return false;
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
ulen CompactRBTreeMap<K,T,KRef>::erase()
 {
  root.init();

  return allocator.erase();
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
template <FuncInitArgType<const K &,T &> FuncInit>
auto CompactRBTreeMap<K,T,KRef>::applyIncr(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start(), [&func] (Node &node) { return func(GetKey(node),node.obj); } );

  return Algon::GetResult(func);
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
template <FuncInitArgType<const K &,T &> FuncInit>
auto CompactRBTreeMap<K,T,KRef>::applyDecr(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start_rev(), [&func] (Node &node) { return func(GetKey(node),node.obj); } );

  return Algon::GetResult(func);
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
template <FuncInitArgType<const K &,const T &> FuncInit>
auto CompactRBTreeMap<K,T,KRef>::applyIncr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start(), [&func] (Node &node) { return func(GetKey(node),(const T &)node.obj); } );

  return Algon::GetResult(func);
 }

template <NothrowDtorType K,NothrowDtorType T,class KRef> requires ( RBTreeMapKeyTypes<K,KRef> )
template <FuncInitArgType<const K &,const T &> FuncInit>
auto CompactRBTreeMap<K,T,KRef>::applyDecr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start_rev(), [&func] (Node &node) { return func(GetKey(node),(const T &)node.obj); } );

  return Algon::GetResult(func);
 }

/* class CompactRadixTreeMap<K,T> */

template <UIntType K,NothrowDtorType T>
class CompactRadixTreeMap : NoCopy
 {
   struct Node : MemBase_nocopy
    {
     TreeUpLink<Node,K> link;
     T obj;

     template <class ... SS>
     explicit Node(SS && ... ss) : obj( std::forward<SS>(ss)... ) {}
    };

   using Algo = typename TreeUpLink<Node,K>::template RadixAlgo<&Node::link> ;

   KeyRange<K> key_range;

   CompactNodeAllocator<Node> allocator;

   typename Algo::Root root;

  private:

   void delNode(Node *node);

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
   explicit CompactRadixTreeMap(SS && ... ss) noexcept : allocator( std::forward<SS>(ss)... ) {}

   template <class ... SS>
   explicit CompactRadixTreeMap(KeyRange<K> key_range_,SS && ... ss) noexcept : key_range(key_range_),allocator( std::forward<SS>(ss)... ) {}

   ~CompactRadixTreeMap() { erase(); }

   // std move

   CompactRadixTreeMap(CompactRadixTreeMap &&obj) noexcept
    : key_range(obj.key_range),
      allocator(std::move(obj.allocator)),
      root(Replace_null(obj.root))
    {
    }

   CompactRadixTreeMap & operator = (CompactRadixTreeMap &&obj) noexcept
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

   // swap/move objects

   void objSwap(CompactRadixTreeMap<K,T> &obj)
    {
     Swap(key_range,obj.key_range);
     Swap(allocator,obj.allocator);
     Swap(root,obj.root);
    }

   explicit CompactRadixTreeMap(ToMoveCtor<CompactRadixTreeMap<K,T> > obj)
    : key_range(obj->key_range),
      allocator(ToMoveCtor(obj->allocator)),
      root(obj->root)
    {
    }
 };

template <UIntType K,NothrowDtorType T>
void CompactRadixTreeMap<K,T>::delNode(Node *node)
 {
  Node *todel=allocator.todel();

  if( node!=todel )
    {
     root.replace(todel,node);

     Swap(todel->obj,node->obj);
    }

  allocator.del();
 }

template <UIntType K,NothrowDtorType T>
template <class ... SS>
auto CompactRadixTreeMap<K,T>::find_or_add(K key,SS && ... ss) -> Result requires ( ConstructibleType<T,SS...> )
 {
  key_range.guard(key);

  typename Algo::PrepareIns prepare(root,key,key_range.kmin,key_range.kmax);

  if( Node *node=prepare.found ) return Result(&node->obj,false);

  Node *node=allocator.alloc( std::forward<SS>(ss)... );

  prepare.complete(node);

  return Result(&node->obj,true);
 }

template <UIntType K,NothrowDtorType T>
bool CompactRadixTreeMap<K,T>::del(K key)
 {
  if( Node *node=root.del(key) )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <UIntType K,NothrowDtorType T>
bool CompactRadixTreeMap<K,T>::delMin()
 {
  if( Node *node=root.delMin() )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <UIntType K,NothrowDtorType T>
bool CompactRadixTreeMap<K,T>::delMax()
 {
  if( Node *node=root.delMax() )
    {
     delNode(node);

     return true;
    }

  return false;
 }

template <UIntType K,NothrowDtorType T>
template <class S>
bool CompactRadixTreeMap<K,T>::del(NodePtr<S> node_ptr)
 {
  if( Node *node=node_ptr.node )
    {
     root.del(node);

     delNode(node);

     return true;
    }

  return false;
 }

template <UIntType K,NothrowDtorType T>
ulen CompactRadixTreeMap<K,T>::erase()
 {
  root.init();

  return allocator.erase();
 }

template <UIntType K,NothrowDtorType T>
template <FuncInitArgType<K,T &> FuncInit>
auto CompactRadixTreeMap<K,T>::applyIncr(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start(), [&func] (Node &node) { return func(GetKey(node),node.obj); } );

  return Algon::GetResult(func);
 }

template <UIntType K,NothrowDtorType T>
template <FuncInitArgType<K,T &> FuncInit>
auto CompactRadixTreeMap<K,T>::applyDecr(FuncInit func_init)
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start_rev(), [&func] (Node &node) { return func(GetKey(node),node.obj); } );

  return Algon::GetResult(func);
 }

template <UIntType K,NothrowDtorType T>
template <FuncInitArgType<K,const T &> FuncInit>
auto CompactRadixTreeMap<K,T>::applyIncr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start(), [&func] (Node &node) { return func(GetKey(node),(const T &)node.obj); } );

  return Algon::GetResult(func);
 }

template <UIntType K,NothrowDtorType T>
template <FuncInitArgType<K,const T &> FuncInit>
auto CompactRadixTreeMap<K,T>::applyDecr(FuncInit func_init) const
 {
  FunctorTypeOf<FuncInit> func(func_init);

  Algon::ApplyToRange(root.start_rev(), [&func] (Node &node) { return func(GetKey(node),(const T &)node.obj); } );

  return Algon::GetResult(func);
 }

} // namespace CCore

#endif


