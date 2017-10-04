/* IntegerBuilder.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.50
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

#ifndef CCore_inc_math_IntegerBuilder_h
#define CCore_inc_math_IntegerBuilder_h

#include <CCore/inc/math/IntegerAlgo.h>

namespace CCore {
namespace Math {

/* classes */

template <UIntType Unit,UIntType UInt,unsigned UnitBits=Meta::UIntBits<Unit>,unsigned UIntBits=Meta::UIntBits<UInt> > struct IntegerFillUInt;

template <IntAlgo Algo,SUIntType SUInt> class CastInteger;

template <IntAlgo Algo,SIntType SInt> class IntegerSIntBuilder;

template <IntAlgo Algo,UIntType UInt> class IntegerUIntBuilder;

template <IntAlgo Algo> class IntegerNegBuilder;

template <IntAlgo Algo> class IntegerAddBuilder;

template <IntAlgo Algo> class IntegerSubBuilder;

template <IntAlgo Algo> class IntegerMulBuilder;

template <IntAlgo Algo> class IntegerSqBuilder;

template <IntAlgo Algo> class IntegerLShiftBuilder;

template <IntAlgo Algo> class IntegerRShiftBuilder;

/* type IntegerFillUInt<Unit,UInt,unsigned UnitBits,unsigned UIntBits> */

template <UIntType Unit,UIntType UInt,unsigned UnitBits,unsigned UIntBits> requires( UIntBits>UnitBits && UIntBits%UnitBits!=0 ) // split
struct IntegerFillUInt<Unit,UInt,UnitBits,UIntBits>
 {
  static constexpr ulen Len = 1+UIntBits/UnitBits ;

  static void FillPos(Unit a[Len],UInt val)
   {
    for(ulen i=0; i<Len ;i++)
      {
       a[i]=Unit(val);

       val>>=UnitBits;
      }
   }

  static void FillNeg(Unit a[Len],UInt val)
   {
    for(ulen i=0; i<Len ;i++)
      {
       a[i]=Unit(val);

       val>>=UnitBits;
      }

    a[Len-1]|=Unit( MaxUInt<Unit> << (UIntBits%UnitBits) );
   }
 };

template <UIntType Unit,UIntType UInt,unsigned UnitBits,unsigned UIntBits> requires( UIntBits>UnitBits && UIntBits%UnitBits==0 ) // split exact
struct IntegerFillUInt<Unit,UInt,UnitBits,UIntBits>
 {
  static constexpr ulen Len = 1+UIntBits/UnitBits ;

  static void FillPos(Unit a[Len],UInt val)
   {
    for(ulen i=0; i<Len-1 ;i++)
      {
       a[i]=Unit(val);

       val>>=UnitBits;
      }

    a[Len-1]=0;
   }

  static void FillNeg(Unit a[Len],UInt val)
   {
    for(ulen i=0; i<Len-1 ;i++)
      {
       a[i]=Unit(val);

       val>>=UnitBits;
      }

    a[Len-1]=MaxUInt<Unit>;
   }
 };

template <UIntType Unit,UIntType UInt,unsigned UnitBits,unsigned UIntBits> requires( UIntBits<UnitBits ) // ext
struct IntegerFillUInt<Unit,UInt,UnitBits,UIntBits>
 {
  static constexpr ulen Len = 1 ;

  static void FillPos(Unit a[Len],UInt val)
   {
    a[0]=val;
   }

  static void FillNeg(Unit a[Len],UInt val)
   {
    a[0]=Unit( val|(MaxUInt<Unit>^MaxUInt<UInt>) );
   }
 };

template <UIntType Unit,UIntType UInt,unsigned UnitBits,unsigned UIntBits> requires( UIntBits==UnitBits ) // same
struct IntegerFillUInt<Unit,UInt,UnitBits,UIntBits>
 {
  static constexpr ulen Len = 2 ;

  static void FillPos(Unit a[Len],UInt val)
   {
    a[0]=val;
    a[1]=0;
   }

  static void FillNeg(Unit a[Len],UInt val)
   {
    a[0]=val;
    a[1]=MaxUInt<Unit>;
   }
 };

/* class CastInteger<Algo,SUInt> */

template <IntAlgo Algo,SIntType SInt>
class CastInteger<Algo,SInt>
 {
   using Unit = typename Algo::Unit ;

   using UInt = typename Meta::SIntToUInt<SInt>::UType ;

   static constexpr ulen Len = IntegerFillUInt<Unit,UInt>::Len ;

   Unit buf[Len];
   ulen len;

  public:

   explicit CastInteger(SInt val_)
    {
     UInt val=UInt(val_);

     if( val_<0 )
       IntegerFillUInt<Unit,UInt>::FillNeg(buf,val);
     else
       IntegerFillUInt<Unit,UInt>::FillPos(buf,val);

     len=Algo::Normalize(buf,Len);
    }

   // range access

   const Unit * getPtr() const { return buf; }

   const Unit * getPtr_const() const { return buf; }

   ulen getLen() const { return len; }
 };

template <IntAlgo Algo,UIntType UInt>
class CastInteger<Algo,UInt>
 {
   using Unit = typename Algo::Unit ;

   static constexpr ulen Len = IntegerFillUInt<Unit,UInt>::Len ;

   Unit buf[Len];
   ulen len;

  public:

   explicit CastInteger(UInt val)
    {
     IntegerFillUInt<Unit,UInt>::FillPos(buf,val);

     len=Algo::Normalize(buf,Len);
    }

   // range access

   const Unit * getPtr() const { return buf; }

   const Unit * getPtr_const() const { return buf; }

   ulen getLen() const { return len; }
 };

/* class IntegerSIntBuilder<Algo,SInt> */

template <IntAlgo Algo,SIntType SInt>
class IntegerSIntBuilder
 {
   using Unit = typename Algo::Unit ;

   using UInt = typename Meta::SIntToUInt<SInt>::UType ;

   //
   // SInt::MaxVal < UInt::Mod
   // SInt::MinVal >= -UInt::Mod
   //

   UInt val;
   bool neg;

  public:

   explicit IntegerSIntBuilder(SInt val_)
    {
     val=UInt(val_);
     neg=(val_<0);
    }

   ulen getLen() const
    {
     return IntegerFillUInt<Unit,UInt>::Len;
    }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *a=place;
     ulen n=getLen();

     if( neg )
       IntegerFillUInt<Unit,UInt>::FillNeg(a,val);
     else
       IntegerFillUInt<Unit,UInt>::FillPos(a,val);

     return Range(a,n);
    }
 };

/* class IntegerUIntBuilder<Algo,UInt> */

template <IntAlgo Algo,UIntType UInt>
class IntegerUIntBuilder
 {
   using Unit = typename Algo::Unit ;

   UInt val;

  public:

   explicit IntegerUIntBuilder(UInt val_) : val(val_) {}

   ulen getLen() const
    {
     return IntegerFillUInt<Unit,UInt>::Len;
    }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *a=place;
     ulen n=getLen();

     IntegerFillUInt<Unit,UInt>::FillPos(a,val);

     return Range(a,n);
    }
 };

/* class IntegerNegBuilder<Algo> */

template <IntAlgo Algo>
class IntegerNegBuilder
 {
   using Unit = typename Algo::Unit ;

   PtrLen<const Unit> a;

  public:

   explicit IntegerNegBuilder(PtrLen<const Unit> a_) : a(a_) {}

   ulen getLen() const { return AddLen(a.len,1); }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *b=place;
     ulen n=a.len;

     Algo::Copy(b,a.ptr,n);

     b[n]=Algo::Neg(b,n);

     return Range(b,n+1);
    }
 };

/* class IntegerAddBuilder<Algo> */

template <IntAlgo Algo>
class IntegerAddBuilder
 {
   using Unit = typename Algo::Unit ;

   PtrLen<const Unit> a;
   PtrLen<const Unit> b;

  public:

   IntegerAddBuilder(PtrLen<const Unit> a_,PtrLen<const Unit> b_)
    {
     if( a_.len<=b_.len )
       {
        a=a_;
        b=b_;
       }
     else
       {
        a=b_;
        b=a_;
       }

     // a.len <= b.len
    }

   ulen getLen() const { return AddLen(b.len,1); }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *c=place;
     ulen n=b.len;

     Algo::Copy(c,b.ptr,n);

     c[n]=Algo::Add(c,n,a.ptr,a.len);

     return Range(c,n+1);
    }
 };

/* IntegerSubBuilder<Algo> */

template <IntAlgo Algo>
class IntegerSubBuilder
 {
   using Unit = typename Algo::Unit ;

   PtrLen<const Unit> a;
   PtrLen<const Unit> b;
   bool rev_flag;

  public:

   IntegerSubBuilder(PtrLen<const Unit> b_,PtrLen<const Unit> a_)
    {
     if( a_.len<=b_.len )
       {
        a=a_;
        b=b_;
        rev_flag=false;
       }
     else
       {
        a=b_;
        b=a_;
        rev_flag=true;
       }

     // a.len <= b.len
    }

   ulen getLen() const { return AddLen(b.len,1); }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *c=place;
     ulen n=b.len;

     Algo::Copy(c,b.ptr,n);

     if( rev_flag )
       {
        c[n]=Algo::RevSub(c,n,a.ptr,a.len);
       }
     else
       {
        c[n]=Algo::Sub(c,n,a.ptr,a.len);
       }

     return Range(c,n+1);
    }
 };

/* class IntegerMulBuilder<Algo> */

template <IntAlgo Algo>
class IntegerMulBuilder
 {
   using Unit = typename Algo::Unit ;

   PtrLen<const Unit> a;
   PtrLen<const Unit> b;
   ulen n;

  public:

   IntegerMulBuilder(PtrLen<const Unit> a_,PtrLen<const Unit> b_)
    : a(a_),b(b_)
    {
     n=AddLen(a_.len,b_.len);
    }

   ulen getLen() const { return n; }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *c=place;

     Algo::Mul(c,a.ptr,a.len,b.ptr,b.len);

     return Range(c,n);
    }
 };

/* IntegerSqBuilder<Algo> */

template <IntAlgo Algo>
class IntegerSqBuilder
 {
   using Unit = typename Algo::Unit ;

   PtrLen<const Unit> a;
   ulen n;

  public:

   explicit IntegerSqBuilder(PtrLen<const Unit> a_)
    : a(a_)
    {
     n=AddLen(a_.len,a_.len);
    }

   ulen getLen() const { return n; }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *c=place;

     Algo::Sq(c,a.ptr,a.len);

     return Range(c,n);
    }
 };

/* class IntegerLShiftBuilder<Algo> */

template <IntAlgo Algo>
class IntegerLShiftBuilder
 {
   using Unit = typename Algo::Unit ;

   PtrLen<const Unit> a;
   unsigned shift,full;
   ulen n;

  public:

   IntegerLShiftBuilder(PtrLen<const Unit> a_,unsigned shift_)
    : a(a_)
    {
     full=unsigned(shift_/Algo::UnitBits);
     shift=unsigned(shift_%Algo::UnitBits);

     n=AddLen(full,a.len,(shift!=0));
    }

   ulen getLen() const { return n; }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *b=place;

     Algo::Null(b,full);

     if( shift )
       {
        b[full+a.len]=Algo::LShift(b+full,a.ptr,a.len,shift);
       }
     else
       {
        Algo::Copy(b+full,a.ptr,a.len);
       }

     return Range(b,n);
    }
 };

/* class IntegerRShiftBuilder<Algo> */

template <IntAlgo Algo>
class IntegerRShiftBuilder
 {
   using Unit = typename Algo::Unit ;

   PtrLen<const Unit> a;
   unsigned shift,full;
   ulen n;

  public:

   IntegerRShiftBuilder(PtrLen<const Unit> a_,unsigned shift_)
    : a(a_)
    {
     full=unsigned(shift_/Algo::UnitBits);
     shift=unsigned(shift_%Algo::UnitBits);

     if( full<a.len )
       n=a.len-full;
     else
       n=1;
    }

   ulen getLen() const { return n; }

   PtrLen<Unit> operator () (Place<void> place) const
    {
     Unit *b=place;

     if( full<a.len )
       {
        if( shift )
          Algo::RShift(b,a.ptr+full,n,shift);
        else
          Algo::Copy(b,a.ptr+full,n);
       }
     else
       {
        b[0]=Algo::SignExt(a.ptr,a.len);
       }

     return Range(b,n);
    }
 };

} // namespace Math
} // namespace CCore

#endif

