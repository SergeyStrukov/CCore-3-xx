/* IntervalTree.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.60
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_IntervalTree_h
#define CCore_inc_IntervalTree_h

#include <CCore/inc/ForLoop.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>

namespace CCore {

/* classes */

template <class T> class IntervalTree;

/* class IntervalTree<T> */

template <class T>
class IntervalTree
 {
   struct Rec
    {
     T point;
     ulen index;

     bool operator < (const Rec &obj) const { return point<obj.point; }
    };

   struct Trio
    {
     T a;
     T b;
     ulen index;

     bool operator < (const Trio &obj) const { return a<obj.a; }
    };

   struct Node
    {
     T split;

     Node *lo;
     Node *hi;

     PtrLen<Rec> mid_lo;
     PtrLen<Rec> mid_hi;

     template <class A>
     Node(T split_,Node *lo_,Node *hi_,PtrLen<Trio> mid,A &buf)
      : split(split_),
        lo(lo_),
        hi(hi_),
        mid_lo( buf.extend_raw(mid.len) ),
        mid_hi( buf.extend_raw(mid.len) )
      {
       CopyA(mid,mid_lo.ptr);
       CopyB(mid,mid_hi.ptr);

       Sort(mid_hi);
      }
    };

   DynArray<Node,ArrayAlgo_mini<Node> > buf;
   DynArray<Rec,ArrayAlgo_mini<Rec> > rec_buf;

   NullMovePtr<Node> root;

  private:

   // build

   static void CopyA(PtrLen<Trio> mid,Rec *out)
    {
     for(const Trio &obj : mid ) *(out++)={obj.a,obj.index};
    }

   static void CopyB(PtrLen<Trio> mid,Rec *out)
    {
     for(const Trio &obj : mid ) *(out++)={obj.b,obj.index};
    }

   static ulen Cut(PtrLen<Trio> list,T split)
    {
     return Algon::BinarySearch_if(list, [split] (const Trio &obj) { return obj.a>split; } ).len;
    }

   static ulen Partition(PtrLen<Trio> list,T split,Trio *temp) // obj.b <= split
    {
     ulen k=0;

     for(ulen i=0; i<list.len ;i++)
       {
        auto &obj=list[i];

        if( obj.b>split )
          {
           temp[k++]=obj;

           for(ulen j=i++; i<list.len ;i++)
             {
              auto &obj=list[i];

              if( obj.b>split )
                {
                 temp[k++]=obj;
                }
              else
                {
                 list[j++]=obj;
                }
             }

           break;
          }
       }

     ulen len=list.len-k;

     Range(temp,k).copyTo(list.ptr+len);

     return len;
    }

   Node * buildNode(PtrLen<Trio> list,Trio *temp)
    {
     if( !list ) return 0;

     ulen i=list.len/2; // i<list.len

     T split=list[i].a;

     ulen hiLen=Cut(list.part(i+1),split)+i+1;

     ulen loLen=Partition(list.prefix(i),split,temp);

     Node *lo=buildNode(list.prefix(loLen),temp);
     Node *hi=buildNode(list.part(hiLen),temp);

     return buf.append_fill(split,lo,hi,list.part(loLen,hiLen-loLen),rec_buf);
    }

   void build(PtrLen<Trio> list)
    {
     Sort(list);

     DynArray<Trio> temp(list.len);

     buf.reserve(list.len);
     rec_buf.reserve(LenOf(list.len,2));

     root=NullMovePtr( buildNode(list,temp.getPtr()) );

     buf.shrink_extra();
    }

   // find

   template <class Func>
   static void Feed(Func func,PtrLen<const Rec> list)
    {
     for(auto &rec : list ) func(rec.index);
    }

   template <class Func>
   static void FindLo(T point,Func func,PtrLen<const Rec> list) // obj.point <= point
    {
     auto res=Algon::BinarySearch_if(list, [point] (const Rec &obj) { return obj.point>point; } );

     Feed(func,res);
    }

   template <class Func>
   static void FindHi(T point,Func func,PtrLen<const Rec> list) // obj.point > point
    {
     Algon::BinarySearch_if(list, [point] (const Rec &obj) { return obj.point>point; } );

     Feed(func,list);
    }

   template <class Func>
   static void Find(T point,Func func,const Node *node)
    {
     if( !node ) return;

     if( point<node->split )
       {
        Find(point,func,node->lo);

        FindLo(point,func,node->mid_lo);
       }
     else if( point>node->split )
       {
        FindHi(point,func,node->mid_hi);

        Find(point,func,node->hi);
       }
     else
       {
        Feed(func,node->mid_lo);
       }
    }

   // find while

   template <class Func>
   static bool FeedWhile(Func func,PtrLen<const Rec> list)
    {
     for(auto &rec : list ) if( !func(rec.index) ) return false;

     return true;
    }

   template <class Func>
   static bool FindLoWhile(T point,Func func,PtrLen<const Rec> list) // obj.point <= point
    {
     auto res=Algon::BinarySearch_if(list, [point] (const Rec &obj) { return obj.point>point; } );

     return FeedWhile(func,res);
    }

   template <class Func>
   static bool FindHiWhile(T point,Func func,PtrLen<const Rec> list) // obj.point > point
    {
     Algon::BinarySearch_if(list, [point] (const Rec &obj) { return obj.point>point; } );

     return FeedWhile(func,list);
    }

   template <class Func>
   static bool FindWhile(T point,Func func,const Node *node)
    {
     if( !node ) return true;

     if( point<node->split )
       {
        return FindWhile(point,func,node->lo) && FindLoWhile(point,func,node->mid_lo) ;
       }
     else if( point>node->split )
       {
        return FindHiWhile(point,func,node->mid_hi) && FindWhile(point,func,node->hi) ;
       }
     else
       {
        return FeedWhile(func,node->mid_lo);
       }
    }

  public:

   IntervalTree() {}

   template <class R,class Func>
   IntervalTree(R range,Func func) // func(range[index]) -> {T a,T b} , [a,b)
    {
     DynArray<Trio> list(DoReserve,range.len);

     for(ulen i : IndLim(range.len) )
       {
        auto interval=func(range[i]);

        if( interval.a<interval.b ) list.append_copy({interval.a,interval.b,i});
       }

     list.shrink_extra();

     build(Range(list));
    }

   void find(T point,FuncArgType<ulen> func) const // func(index)
    {
     Find(point,func,root.getPtr());
    }

   bool find(T point,FuncType<bool,ulen> func) const // func(index), return false to break
    {
     return FindWhile(point,func,root.getPtr());
    }
 };

} // namespace CCore

#endif

