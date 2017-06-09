/* NodeAllocator.h */
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

#ifndef CCore_inc_NodeAllocator_h
#define CCore_inc_NodeAllocator_h

#include <CCore/inc/MemBase.h>
#include <CCore/inc/Move.h>

#include <CCore/inc/algon/GCDConst.h>

namespace CCore {

/* functions */

void NodePoolAbort();

/* classes */

template <class Node> class NodeAllocator;

class MemBlockPool;

template <NothrowDtorType Node> class NodePoolAllocator;

/* class NodeAllocator<Node> */

template <class Node>
class NodeAllocator : NoCopy
 {
   ulen count;

  public:

   // constructors

   NodeAllocator() noexcept : count(0) {}

   // std move

   NodeAllocator(NodeAllocator<Node> &&obj) noexcept : count(Replace_null(obj.count)) {}

   NodeAllocator<Node> & operator = (NodeAllocator<Node> &&obj) noexcept
    {
     if( this!=&obj )
       {
        count=Replace_null(obj.count);
       }

     return *this;
    }

   // props

   ulen operator + () const { return count; }

   bool operator ! () const { return !count; }

   ulen getCount() const { return count; }

   // methods

   template <class ... SS>
   Node * alloc(SS && ... ss) requires ( ConstructibleType<Node,SS...> )
    {
     Node *ret=new Node( std::forward<SS>(ss)... );

     count++;

     return ret;
    }

   void free_nonnull(Node *node)
    {
     count--;

     delete node;
    }

   bool free(Node *node)
    {
     if( node )
       {
        free_nonnull(node);

        return true;
       }

     return false;
    }

   // swap/move objects

   void objSwap(NodeAllocator<Node> &obj)
    {
     Swap(count,obj.count);
    }

   explicit NodeAllocator(ToMoveCtor<NodeAllocator<Node> > obj)
    : count(Replace_null(obj->count))
    {
    }
 };

/* class MemBlockPool */

class MemBlockPool : NoCopy
 {
   struct FreeNode
    {
     FreeNode *next;

     explicit FreeNode(FreeNode *next_) : next(next_) {}
    };

   static constexpr ulen Delta = Align(sizeof (FreeNode)) ;

  private:

   ulen len;
   ulen alloc_count;
   ulen alloc_len;

   FreeNode *free_list;
   FreeNode *mem_list;

   Place<void> cur;
   ulen count;

  private:

   void * alloc_new();

   static void Destroy(FreeNode *mem_list);

  public:

   // constructors

   static constexpr ulen DefaultCount = 100 ;

   template <ulen Len,ulen AlignOf>
   struct LenCheckCtor
    {
     static constexpr ulen A = Algon::LCMConst<ulen,AlignOf,alignof (FreeNode)> ;

     static constexpr ulen Lim = A*((MaxULen-Delta)/A) ;

     enum RetType { Ret = ( Len <= Lim && sizeof (FreeNode) <= Lim ) };
    };

   MemBlockPool(ulen len,ulen align_of,ulen alloc_count=DefaultCount);

   ~MemBlockPool() { Destroy(mem_list); }

   // std move

   MemBlockPool(MemBlockPool &&obj) noexcept
     : len(obj.len),
       alloc_count(obj.alloc_count),
       alloc_len(obj.alloc_len),

       free_list(Replace_null(obj.free_list)),
       mem_list(Replace_null(obj.mem_list)),

       cur(Replace(obj.cur,Place<void>(0))),
       count(Replace_null(obj.count))
    {
    }

   MemBlockPool & operator = (MemBlockPool &&obj) noexcept
    {
     if( this!=&obj)
       {
        len=obj.len;
        alloc_count=obj.alloc_count;
        alloc_len=obj.alloc_len;

        free_list=Replace_null(obj.free_list);
        Destroy(Replace(mem_list,Replace_null(obj.mem_list)));

        cur=Replace(obj.cur,Place<void>(0));
        count=Replace_null(obj.count);
       }

     return *this;
    }

   // methods

   void * alloc()
    {
     if( FreeNode *node=free_list )
       {
        free_list=node->next;

        return node;
       }

     return alloc_new();
    }

   void free(void *mem)
    {
     free_list=new(PlaceAt(mem)) FreeNode(free_list);
    }

   // AllocGuard

   class AllocGuard : NoCopy
    {
      MemBlockPool &pool;
      void *mem;

     public:

      explicit AllocGuard(MemBlockPool &pool_)
       : pool(pool_)
       {
        mem=pool.alloc();
       }

      ~AllocGuard()
       {
        if( mem ) pool.free(mem);
       }

      operator void * () const { return mem; }

      void * disarm() { return Replace_null(mem); }
    };

   // swap/move objects

   void objSwap(MemBlockPool &obj)
    {
     Swap(len,obj.len);
     Swap(alloc_count,obj.alloc_count);
     Swap(alloc_len,obj.alloc_len);

     Swap(free_list,obj.free_list);
     Swap(mem_list,obj.mem_list);

     Swap(cur,obj.cur);
     Swap(count,obj.count);
    }

   explicit MemBlockPool(ToMoveCtor<MemBlockPool> obj)
    : len(obj->len),
      alloc_count(obj->alloc_count),
      alloc_len(obj->alloc_len),

      free_list(obj->free_list),
      mem_list(Replace_null(obj->mem_list)),

      cur(obj->cur),
      count(obj->count)
    {
    }
 };

/* concept MemBlockPool_LenCheck<ulen Len,ulen AlignOf> */

template <ulen Len,ulen AlignOf>
concept bool MemBlockPool_LenCheck = (bool)MemBlockPool::LenCheckCtor<Len,AlignOf>::Ret ;

/* class NodePoolAllocator<Node> */

template <NothrowDtorType Node>
class NodePoolAllocator : NoCopy
 {
   MemBlockPool pool;

   ulen count;

  public:

   // constructors

   explicit NodePoolAllocator(ulen pool_count=MemBlockPool::DefaultCount) noexcept requires ( MemBlockPool_LenCheck<sizeof (Node),alignof (Node)> )
    : pool(sizeof (Node),alignof (Node),pool_count),
      count(0)
    {
    }

   ~NodePoolAllocator() { if( count ) NodePoolAbort(); }

   // std move

   NodePoolAllocator(NodePoolAllocator<Node> &&obj) noexcept : pool(std::move(obj.pool)),count(Replace_null(obj.count)) {}

   NodePoolAllocator<Node> & operator = (NodePoolAllocator<Node> &&obj) noexcept
    {
     if( this!=&obj )
       {
        if( count ) NodePoolAbort();

        pool=std::move(obj.pool);
        count=Replace_null(obj.count);
       }

     return *this;
    }

   // props

   ulen operator + () const { return count; }

   bool operator ! () const { return !count; }

   ulen getCount() const { return count; }

   // methods

   template <class ... SS>
   Node * alloc(SS && ... ss) requires ( ConstructibleType<Node,SS...> )
    {
     MemBlockPool::AllocGuard guard(pool);

     Node *ret=new(PlaceAt(guard)) Node( std::forward<SS>(ss)... );

     guard.disarm();

     count++;

     return ret;
    }

   void free_nonnull(Node *node)
    {
     count--;

     node->~Node();

     pool.free(node);
    }

   bool free(Node *node)
    {
     if( node )
       {
        free_nonnull(node);

        return true;
       }

     return false;
    }

   // swap/move objects

   void objSwap(NodePoolAllocator<Node> &obj)
    {
     Swap(pool,obj.pool);
     Swap(count,obj.count);
    }

   explicit NodePoolAllocator(ToMoveCtor<NodePoolAllocator<Node> > obj)
    : pool(ToMoveCtor(obj->pool)),
      count(Replace_null(obj->count))
    {
    }
 };

} // namespace CCore

#endif



