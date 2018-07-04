/* main.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Labs/IntervalTree
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/inc/Print.h>
#include <CCore/inc/Exception.h>

#include <CCore/inc/ForLoop.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/CompactList.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>

namespace App {

/* using */

using namespace CCore;

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

     Node *lo = 0 ;
     Node *hi = 0 ;

     DynArray<Rec> mid_lo;
     DynArray<Rec> mid_hi;

     Node(T split_,Node *lo_,Node *hi_,PtrLen<Trio> mid)
      : split(split_),
        lo(lo_),
        hi(hi_),
        mid_lo(mid.len),
        mid_hi(mid.len)
      {
       CopyA(mid,mid_lo.getPtr());
       CopyB(mid,mid_hi.getPtr());

       Sort(Range(mid_hi));
      }
    };

   CompactList<Node> buf;

   Node *root = 0 ;

  private:

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

     return buf.ins(split,lo,hi,list.part(loLen,hiLen-loLen));
    }

   void build(PtrLen<Trio> list)
    {
     Sort(list);

     DynArray<Trio> temp(list.len);

     root=buildNode(list,temp.getPtr());
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

   template <class Func>
   void find(T point,Func func) // func(index)
    {
    }
 };

/* Main() */

void Main()
 {
 }

} // namespace App

/* main() */

using namespace App;

int main()
 {
  try
    {
     ReportException report;

     Main();

     report.guard();

     return 0;
    }
  catch(CatchType)
    {
     return 1;
    }
 }

