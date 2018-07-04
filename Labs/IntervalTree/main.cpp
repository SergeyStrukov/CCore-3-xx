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
#include <CCore/inc/PlatformRandom.h>

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

        FindLo(point,func,Range(node->mid_lo));
       }
     else if( point>node->split )
       {
        FindHi(point,func,Range(node->mid_hi));

        Find(point,func,node->hi);
       }
     else
       {
        Feed(func,Range(node->mid_lo));
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

   template <class Func>
   void find(T point,Func func) const // func(index)
    {
     Find(point,func,root);
    }
 };

/* class Engine */

class Engine : NoCopy
 {
   PlatformRandom random;

   struct Int
    {
     int a;
     int b;
    };

   struct Rec
    {
     int a;
     int b;
     bool hit;

     void test(int t)
      {
       bool res = ( t>=a && t<b ) ;

       if( res!=hit )
         {
          Printf(Exception,"test failed");
         }

       //Printf(Con,"#;\n",(int)res);
      }
    };

   DynArray<Rec> list;

   IntervalTree<int> tree;

  private:

   Rec gen()
    {
     int a=random.select(1000);
     int b=a+1+random.select(1000);

     return {a,b,false};
    }

   void test()
    {
     int t=random.select(2000);

     for(Rec &rec : list ) rec.hit=false;

     tree.find(t, [&] (ulen ind) { list[ind].hit=true; } );

     for(Rec &rec : list ) rec.test(t);
    }

  public:

   Engine()
    : list(random.select(10,1000))
    {
     for(Rec &obj : list ) obj=gen();

     tree=IntervalTree<int>(Range(list), [] (Rec rec) ->Int { return {rec.a,rec.b}; } );
    }

   void run(unsigned count=1000)
    {
     for(; count ;count--) test();
    }
 };

/* Main() */

void Main()
 {
#if 0

  Engine engine;

  engine.run(1);

#else

  for(unsigned cnt=10000; cnt ;cnt--)
    {
     Engine engine;

     engine.run();
    }

#endif
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

