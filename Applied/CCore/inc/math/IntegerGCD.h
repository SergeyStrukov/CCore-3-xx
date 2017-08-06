/* IntegerGCD.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.01
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2017 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_math_IntegerGCD_h
#define CCore_inc_math_IntegerGCD_h

#include <CCore/inc/math/IntegerAlgo.h>

#include <CCore/inc/Array.h>

namespace CCore {
namespace Math {

/* guards */

void GuardQSymEven();

void GuardQSymNotCoprime();

/* classes */

template <IntAlgo Algo> struct GCDAlgo;

template <UIntType Unit,class TempArrayType> class TempInteger2;

template <IntAlgo Algo,class TempArrayType> class GCDivBuilder;

template <class Integer> class GCDiv;

/* struct GCDAlgo<Algo> */

template <IntAlgo Algo>
struct GCDAlgo
 {
  using Unit = typename Algo::Unit ;

  // internal

  static CmpResult Cmp(PtrLen<Unit> a,PtrLen<Unit> b)
   {
    return Algo::UCmp(a.ptr,a.len,b.ptr,b.len);
   }

  static void Sub(PtrLen<Unit> b,PtrLen<Unit> a) // b>=a
   {
    if( a.len<b.len )
      {
       Unit c=Algo::USub(b.ptr,a.ptr,a.len);

       Algo::USubUnit(b.ptr+a.len,b.len-a.len,c);
      }
    else
      {
       Algo::USub(b.ptr,a.ptr,b.len);
      }
   }

  static PtrLen<Unit> Norm(PtrLen<Unit> a)
   {
    return Range(a.ptr,Algo::UNormalize(a.ptr,a.len));
   }

  static PtrLen<Unit> NormSub(PtrLen<Unit> b,PtrLen<Unit> a)
   {
    Sub(b,a);

    return Norm(b);
   }

  static PtrLen<Unit> Div2(PtrLen<Unit> a) // a!=0
   {
    while( *a==0 ) ++a;

    if( unsigned shift=Algo::CountZeroLSB(*a) ) Algo::URShift(a.ptr,a.len,shift);

    return Norm(a);
   }

  static PtrLen<Unit> Odd(PtrLen<Unit> a,PtrLen<Unit> b) // a and b are odd , no overlapp
   {
    for(;;)
      switch( Cmp(a,b) )
        {
         case CmpLess :
          {
           b=Div2(NormSub(b,a));
          }
         break;

         case CmpGreater :
          {
           a=Div2(NormSub(a,b));
          }
         break;

         default: // case CmpEqual :
          {
           return a;
          }
        }
   }

  struct Shift
   {
    ulen full;
    unsigned shift;

    bool operator < (Shift obj) const { return full<obj.full || ( full==obj.full && shift<obj.shift ) ; }

    Shift min(Shift obj) const { return Min(*this,obj); }
   };

  struct Result
   {
    PtrLen<Unit> result;
    Unit msu;

    explicit Result(PtrLen<Unit> a)
     {
      result=a;
      msu=0;
     }

    Result(Shift s,PtrLen<Unit> a)
     {
      if( s.shift )
        {
         msu=Algo::ULShift(a.ptr,a.len,s.shift);
        }
      else
        {
         msu=0;
        }

      for(ulen cnt=s.full; cnt ;cnt--)
        {
         --a;

         *a=0;
        }

      result=a;
     }

    ulen copyTo(Unit *buf) const // [result.len+2]
     {
      result.copyTo(buf);

      buf[result.len]=msu;
      buf[result.len+1]=0;

      return Algo::Normalize(buf,result.len+2);
     }
   };

  struct ShiftVal : Shift
   {
    using Shift::full;
    using Shift::shift;

    PtrLen<Unit> odd;

    explicit ShiftVal(PtrLen<Unit> a)
     {
      ulen len=a.len;

      for(; +a ;++a)
        if( Unit u=*a )
          {
           full=len-a.len;

           shift=Algo::CountZeroLSB(u);

           odd=a;

           return;
          }

      full=len;
      shift=0;
     }

    bool operator ! () const { return !odd.len; }

    void complete()
     {
      if( shift ) Algo::URShift(odd.ptr,odd.len,shift);
     }
   };

  // GCD

  static Result UnsignedGCD(PtrLen<Unit> a,PtrLen<Unit> b) // no overlap
   {
    ShiftVal sa(a);

    if( !sa ) return Result(b);

    ShiftVal sb(b);

    if( !sb ) return Result(a);

    sa.complete();
    sb.complete();

    PtrLen<Unit> c=Odd(sa.odd,sb.odd);

    return Result(sa.min(sb),c);
   }

  static Result SignedGCD(PtrLen<Unit> a,PtrLen<Unit> b) // no overlap
   {
    if( Algo::Sign(a.ptr,a.len)<0 ) Algo::UNeg(a.ptr,a.len);
    if( Algo::Sign(b.ptr,b.len)<0 ) Algo::UNeg(b.ptr,b.len);

    return UnsignedGCD(a,b);
   }

  // QSym

  static bool QSym2(Unit b) // Unit at least 3 bit
   {
    switch( b&7u )
      {
       case 3 : case 5 : return true;

       default: return false;
      }
   }

  static unsigned QSymEps(Unit a,Unit b)
   {
    if( (a&3u)==1 || (b&3u)==1 ) return 0;

    return 1;
   }

  static int UnsignedQSym(PtrLen<Unit> a,PtrLen<Unit> b) // no overlap
   {
    if( b.len==0 || (b[0]&1u)==0 ) GuardQSymEven();

    bool qsym2=QSym2(b[0]);

    for(unsigned ret=0;;)
      {
       ShiftVal sa(a);

       if( !sa )
         {
          if( Algo::UNormalize(b.ptr,b.len)!=1 || b[0]!=1 ) GuardQSymNotCoprime();

          return (ret&1u)?-1:+1;
         }

       sa.complete();

       if( qsym2 )
         {
          if( Algo::UnitBits&1u )
            ret ^= sa.shift^unsigned(sa.full) ;
          else
            ret ^= sa.shift ;
         }

       if( Cmp(sa.odd,b)>=0 )
         {
          a=NormSub(sa.odd,b);
         }
       else
         {
          a=b;
          b=sa.odd;

          ret ^= QSymEps(a[0],b[0]) ;

          qsym2=QSym2(b[0]);

          a=NormSub(a,b);
         }
      }
   }

  static int SignedQSym(PtrLen<Unit> a,PtrLen<Unit> b) // no overlap
   {
    if( Algo::Sign(b.ptr,b.len)<0 ) Algo::UNeg(b.ptr,b.len);

    if( Algo::Sign(a.ptr,a.len)<0 )
      {
       Algo::UNeg(a.ptr,a.len);

       if( b.len>0 && (b[0]&3u)==3 )
         return -UnsignedQSym(a,b);
       else
         return UnsignedQSym(a,b);
      }
    else
      {
       return UnsignedQSym(a,b);
      }
   }
 };

/* class TempInteger2<Unit,TempArrayType> */

template <UIntType Unit,class TempArrayType>
class TempInteger2
 {
   TempArrayType buf;
   PtrLen<Unit> a;
   PtrLen<Unit> b;

  public:

   TempInteger2(PtrLen<const Unit> a_,PtrLen<const Unit> b_)
    : buf(DoRaw( AddLen(a_.len,b_.len) ))
    {
     Unit *a1=buf.getPtr();
     Unit *b1=a1+a_.len;

     a_.copyTo(a1);
     b_.copyTo(b1);

     a=Range(a1,a_.len);
     b=Range(b1,b_.len);
    }

   ~TempInteger2()
    {
    }

   PtrLen<Unit> getA() const { return a; }

   PtrLen<Unit> getB() const { return b; }
 };

/* class GCDivBuilder<Algo,TempArrayType> */

template <IntAlgo Algo,class TempArrayType>
class GCDivBuilder
 {
   using Unit = typename Algo::Unit ;

   PtrLen<const Unit> a;
   PtrLen<const Unit> b;

  public:

   GCDivBuilder(PtrLen<const Unit> a_,PtrLen<const Unit> b_) : a(a_),b(b_) {}

   ulen getLen() const { return AddLen(Max(a.len,b.len),2); }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     TempInteger2<Unit,TempArrayType> temp(a,b);

     auto result=GCDAlgo<Algo>::SignedGCD(temp.getA(),temp.getB());

     Unit *c=place;
     ulen len=result.copyTo(c);

     return Range(c,len);
    }
 };

/* class GCDiv<Integer> */

template <class Integer>
class GCDiv : public Integer
 {
  public:

   GCDiv(const Integer &a,const Integer &b)
    : Integer(DoBuild,GCDivBuilder<typename Integer::AlgoType,typename Integer::TempArrayType>(a.getBody(),b.getBody()))
    {
    }
 };

/* QSym() */

template <class Integer>
int QSym(const Integer &a,const Integer &b)
 {
  TempInteger2<typename Integer::Unit,typename Integer::TempArrayType> temp(a.getBody(),b.getBody());

  return GCDAlgo<typename Integer::AlgoType>::SignedQSym(temp.getA(),temp.getB());
 }

} // namespace Math
} // namespace CCore

#endif

