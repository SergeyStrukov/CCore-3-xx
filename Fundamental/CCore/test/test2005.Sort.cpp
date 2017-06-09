/* test2005.Sort.cpp */
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

#include <CCore/test/test.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/Random.h>
#include <CCore/inc/Array.h>
#include <CCore/inc/PrintSet.h>

namespace App {

namespace Private_2005 {

/* consts */

const ulen Count  = 1000  ;
const ulen MaxLen = 10000 ;

/* functions */

inline ulen DeltaLen(ulen len)
 {
  if( len<100 ) return 1;
  if( len<1000 ) return 10;
  if( len<10000 ) return 100;

  return 1000;
 }

/* class Engine<Algo> */

template <template <class Ran,class Ctx> class Algo>
class Engine
 {
   using Type = unsigned ;

   Random random;

  private:

   Type next() { return random.select(100,200); }

   void fill(Type *ptr,ulen len)
    {
     for(; len ;len--) *(ptr++)=next();
    }

   void sort(Type *ptr,ulen len)
    {
     Algo<Type *,SortCtx<Type *> >::Sort(ptr,len);
    }

   void test(const Type *ptr,ulen len)
    {
     for(; len>1 ;len--,ptr++)
       if( ptr[0]>ptr[1] )
         Printf(Exception,"test failed");
    }

   void show(const Type *ptr,ulen len)
    {
     Printf(Con,"#;\n",PrintSet(Range(ptr,len)));
    }

  public:

   Engine() {}

   ~Engine() {}

   bool run(ulen len)
    {
     if( len>MaxLen ) return false;

     if( len%10==0 )
       Printf(Con,"len = #;\n",len);

     SimpleArray<Type> a(len);

     Type *ptr=a.getPtr();

     for(ulen cnt=Count; cnt ;cnt--)
       {
        fill(ptr,len);

        if( cnt==Count && len==10 ) show(ptr,len);

        sort(ptr,len);

        if( cnt==Count && len==10 ) show(ptr,len);

        test(ptr,len);
       }

     return true;
    }
 };

/* class IndexEngine<Algo> */

template <template <class Ran,class Ctx> class Algo>
class IndexEngine
 {
   using Type = unsigned ;
   using IndexType = unsigned ;

   Random random;

  private:

   Type next() { return random.next_uint<unsigned>(); }

   void fill(Type *ptr,IndexType *ind,ulen len)
    {
     IndexType i=0;

     for(; len ;len--)
       {
        *(ptr++)=next();
        *(ind++)=(i++);
       }
    }

   void sort(const Type *ptr,IndexType *ind,ulen len)
    {
     Algo<IndexType *,SortIndexCtx<const Type> >::Sort(ind,len,ptr);
    }

   void test(const Type *ptr,const IndexType *ind,ulen len)
    {
     for(; len>1 ;len--,ind++)
       if( ptr[ind[0]]>ptr[ind[1]] )
         Printf(Exception,"test failed");
    }

  public:

   IndexEngine() {}

   ~IndexEngine() {}

   bool run(ulen len)
    {
     if( len>MaxLen ) return false;

     if( len%10==0 )
       Printf(Con,"len = #;\n",len);

     SimpleArray<Type> a(len);
     SimpleArray<IndexType> b(len);

     Type *ptr=a.getPtr();
     IndexType *ind=b.getPtr();

     for(ulen cnt=Count; cnt ;cnt--)
       {
        fill(ptr,ind,len);

        sort(ptr,ind,len);

        test(ptr,ind,len);
       }

     return true;
    }
 };

} // namespace Private_2005

using namespace Private_2005;

/* Testit<2005> */

template<>
const char *const Testit<2005>::Name="Test2005 Sort";

template<>
bool Testit<2005>::Main()
 {
  {
   int buf[10];

   int i=1;

   for(int &x : buf) x=i++;

   DecrSort(Range(buf), [] (int a,int b) { return a<b; } );

   Printf(Con,"#;\n",PrintSet(Range(buf)));

   IncrSort(Range(buf), [] (int a,int b) { return a<b; } );

   Printf(Con,"#;\n\n",PrintSet(Range(buf)));
  }

  Printf(Con,"#;\n\n",Title("ParaQuickSort"));

  {
   Job::Init job_init;

   Engine<ParaQuickSort> engine;

   for(ulen len=0; engine.run(len) ;len+=DeltaLen(len));
  }

  Printf(Con,"\n#;\n\n",Title("QuickSort"));

  {
   Engine<QuickSort> engine;

   for(ulen len=0; engine.run(len) ;len+=DeltaLen(len));
  }

  Printf(Con,"\n#;\n\n",Title("QuickSort index"));

  {
   IndexEngine<QuickSort> engine;

   for(ulen len=0; engine.run(len) ;len+=DeltaLen(len));
  }

  Printf(Con,"\n#;\n\n",Title("HeapSort"));

  {
   Engine<HeapSort> engine;

   for(ulen len=0; engine.run(len) ;len+=DeltaLen(len));
  }

  Printf(Con,"\n#;\n\n",Title("HeapSort index"));

  {
   IndexEngine<HeapSort> engine;

   for(ulen len=0; engine.run(len) ;len+=DeltaLen(len));
  }

  Printf(Con,"\n#;\n\n",Title("MergeSort"));

  {
   Engine<MergeSort> engine;

   for(ulen len=0; engine.run(len) ;len+=DeltaLen(len));
  }

  Printf(Con,"\n#;\n\n",Title("MergeSort index"));

  {
   IndexEngine<MergeSort> engine;

   for(ulen len=0; engine.run(len) ;len+=DeltaLen(len));
  }

  return true;
 }

} // namespace App

