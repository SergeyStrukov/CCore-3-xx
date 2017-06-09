/* HeapSort.h */
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

#ifndef CCore_inc_sort_HeapSort_h
#define CCore_inc_sort_HeapSort_h

#include <CCore/inc/sort/ShortSort.h>

namespace CCore {

/* classes */

template <RanType Ran,SortContextType<Ran> Ctx=SortCtx<Ran> > struct HeapSort;

/* struct HeapSort<Ran,Ctx> */

template <RanType Ran,SortContextType<Ran> Ctx>
struct HeapSort
 {
  template <ULenType Len>
  static void Sort(Ran ptr,Len len,Ctx ctx);

  static void Sort(Ran ptr,ULenType len) requires ( DefaultCtorType<Ctx> ) { Sort(ptr,len,Ctx()); }
 };

template <RanType Ran,SortContextType<Ran> Ctx>
template <ULenType Len>
void HeapSort<Ran,Ctx>::Sort(Ran ptr,Len len,Ctx ctx)
 {
  Used(ctx);

  if( len<2 ) return;

  // create heap

  Len len2=len/2;
  Len len3=(len-1)/2;

  Ran end=ptr+(len-1);

  for(Len i=len2; i>0 ;)
    {
     Len j=--i;
     Ran a=ptr+j;

     for(;;)
       {
        if( j>=len3 )
          {
           if( j<len2 )
             {
              if( ctx.less(a,end) ) ctx.swap(a,end);
             }

           break;
          }

        Len k=2*j+1;
        Ran b=ptr+k;
        Ran c=b+1;

        if( ctx.less(b,c) )
          {
           b=c;
           k++;
          }

        if( ctx.less(a,b) )
          {
           ctx.swap(a,b);
           j=k;
           a=b;
          }
        else
          {
           break;
          }
       }
    }

  // consume heap

  for(Len i=len-1; i>0 ;i--)
    {
     Len i2=i/2;
     Len i3=(i-1)/2;
     Ran d=ptr+i;

     Len j=0;
     Ran a=ptr;

     for(;;)
       {
        if( j>=i3 )
          {
           if( j<i2 )
             {
              Len k=i-1;
              Ran b=ptr+k;

              ctx.swap(a,b);
              j=k;
              a=b;
             }

           ctx.swap(a,d);

           while( j>0 )
             {
              Len k=(j-1)/2;
              Ran b=ptr+k;

              if( ctx.less(b,a) )
                {
                 ctx.swap(b,a);
                 j=k;
                 a=b;
                }
              else
                {
                 break;
                }
             }

           break;
          }

        Len k=2*j+1;
        Ran b=ptr+k;
        Ran c=b+1;

        if( ctx.less(b,c) )
          {
           b=c;
           k++;
          }

        ctx.swap(a,b);
        j=k;
        a=b;
       }
    }
 }

} // namespace CCore

#endif


