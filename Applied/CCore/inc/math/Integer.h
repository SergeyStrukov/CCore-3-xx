/* Integer.h */
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

#ifndef CCore_inc_math_Integer_h
#define CCore_inc_math_Integer_h

#include <CCore/inc/math/IntegerDivider.h>
#include <CCore/inc/math/PrintInteger.h>
#include <CCore/inc/math/IntegerFromString.h>
#include <CCore/inc/math/IntegerGCD.h>

#include <CCore/inc/Random.h>

namespace CCore {
namespace Math {

/* guards */

void GuardBitsOfOverflow();

/* classes */

template <unsigned UnitBits> struct IntegerBitsOf;

template <IntAlgo Algo, template <class T,class A> class ArrayType = RefArray ,
                        template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType = ArrayAlgo > class Integer;

template <class Integer> class RandomInteger;

/* struct IntegerBitsOf<unsigned UnitBits> */

template <unsigned UnitBits>
struct IntegerBitsOf
 {
  ulen units;
  unsigned msbits;

  IntegerBitsOf(ulen units_,unsigned msbits_) : units(units_),msbits(msbits_) {}

  template <UIntType UInt>
  void total(UInt &ret) const
   {
    static_assert( UnitBits<=MaxUInt<UInt> ,"CCore::Math::IntegerBitsOf<...>::total<UInt>() : too short UInt");

    if( units>(MaxUInt<UInt>-msbits)/UnitBits ) GuardBitsOfOverflow();

    ret=UInt( units*UInt(UnitBits)+msbits );
   }

  unsigned total() const
   {
    unsigned ret;

    total(ret);

    return ret;
   }
 };

/* class Integer<Algo,ArrayType,ArrayAlgoType> */

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
class Integer
 {
  public:

   using AlgoType = Algo ;

   using Unit = typename Algo::Unit ;

   static constexpr unsigned UnitBits = Algo::UnitBits ;

   using TempArrayType = DynArray<Unit,ArrayAlgoType<Unit> > ;

  private:

   ArrayType<Unit,ArrayAlgoType<Unit> > body;

  private:

   // builders

   using NegBuilder = IntegerNegBuilder<Algo> ;
   using AddBuilder = IntegerAddBuilder<Algo> ;
   using SubBuilder = IntegerSubBuilder<Algo> ;
   using MulBuilder = IntegerMulBuilder<Algo> ;
   using SqBuilder = IntegerSqBuilder<Algo> ;
   using LShiftBuilder = IntegerLShiftBuilder<Algo> ;
   using RShiftBuilder = IntegerRShiftBuilder<Algo> ;

   // normalization

   void normalize();

   // operators

   Integer & add(const Unit *b,ulen nb); // not overlapped

   Integer & sub(const Unit *b,ulen nb); // not overlapped

   Integer & revsub(const Unit *b,ulen nb); // not overlapped

   Integer & mul(const Unit *b,ulen nb);

   Integer & div(const Unit *b,ulen nb);

   Integer & mod(const Unit *b,ulen nb);

  private:

   enum CopyFromType { CopyFrom };

   explicit Integer(CopyFromType,PtrLen<const Unit> data) : body(DoCopy(data.len),data.ptr) {}

  public:

   // generic constructor

   Integer(DoBuildType,BuilderType<Unit> builder) : body(DoBuild,builder) { normalize(); }

   // constructors

   Integer() noexcept {}

   Integer(NothingType) noexcept {}

   Integer(StrLen str)
    {
     IntegerFromString<Integer> conv(str.len);

     *this=conv(str);
    }

   template <UIntType UInt>
   Integer(UInt val) : Integer(DoBuild,IntegerUIntBuilder<Algo,UInt>(val)) {}

   template <SIntType SInt>
   Integer(SInt val) : Integer(DoBuild,IntegerSIntBuilder<Algo,SInt>(val)) {}

   ~Integer() {}

   // std copy

   Integer(const Integer &) = default ;

   Integer & operator = (const Integer &) = default ;

   // std move

   Integer(Integer &&) = default ;

   Integer & operator = (Integer &&) = default ;

   // methods

   CmpResult sign() const { return Algo::Sign(body.getPtr(),body.getLen()); }

   bool operator ! () const { return !sign(); }

   using BitsOf = IntegerBitsOf<UnitBits> ;

   BitsOf bitsOf() const;

   Integer sq() const { return Sq(getBody()); }

   Integer pow(unsigned deg) const;

   void modify() { body.modify(); }

   void cloneTo(Integer &ret) const { body.cloneTo(ret.body); }

   Integer & set_null() { body.erase(); return *this; }

   PtrLen<const Unit> getBody() const { return Range_const(body); }

   PtrLenReverse<const Unit> getBodyReverse() const { return RangeReverse_const(body); }

   bool isOdd() const { return body.getLen() && (body[0]&Unit(1)) ; }

   bool isEven() const { return !isOdd(); }

   // cast

   template <UIntType UInt>
   UInt cast() const
    {
     UInt ret=0;
     unsigned shift=0;

     for(Unit a : body )
       {
        if( shift>=Meta::UIntBits<UInt> ) break;

        ret|=(UInt(a)<<shift);

        shift+=UnitBits;
       }

     return ret;
    }

   // cmp objects

   CmpResult objCmp(const Integer &b) const
    {
     return Algo::Cmp(body.getPtr(),body.getLen(),b.body.getPtr(),b.body.getLen());
    }

   // operators

   static Integer Neg(PtrLen<const Unit> a)
    {
     return Integer(DoBuild,NegBuilder(a));
    }

   static Integer Add(PtrLen<const Unit> a,PtrLen<const Unit> b)
    {
     return Integer(DoBuild,AddBuilder(a,b));
    }

   static Integer Sub(PtrLen<const Unit> a,PtrLen<const Unit> b)
    {
     return Integer(DoBuild,SubBuilder(a,b));
    }

   static Integer Mul(PtrLen<const Unit> a,PtrLen<const Unit> b)
    {
     return Integer(DoBuild,MulBuilder(a,b));
    }

   static Integer Sq(PtrLen<const Unit> a)
    {
     return Integer(DoBuild,SqBuilder(a));
    }

   static Integer Div(PtrLen<const Unit> a,PtrLen<const Unit> b)
    {
     IntegerDivider<Algo,TempArrayType> divider(a,b);

     return Integer(CopyFrom,divider.getResult());
    }

   static Integer Mod(PtrLen<const Unit> a,PtrLen<const Unit> b)
    {
     IntegerDivider<Algo,TempArrayType> divider(a,b,true);

     return Integer(CopyFrom,divider.getMod());
    }

   static Integer LShift(PtrLen<const Unit> a,unsigned shift)
    {
     return Integer(DoBuild,LShiftBuilder(a,shift));
    }

   static Integer RShift(PtrLen<const Unit> a,unsigned shift)
    {
     return Integer(DoBuild,RShiftBuilder(a,shift));
    }

   struct DivMod
    {
     Integer div;
     Integer mod;

     DivMod(PtrLen<const Unit> a,PtrLen<const Unit> b)
      {
       IntegerDivider<Algo,TempArrayType> divider(a,b,true);

       Integer div_(CopyFrom,divider.getResult());
       Integer mod_(CopyFrom,divider.getMod());

       div=std::move(div_);
       mod=std::move(mod_);
      }
    };

   // operators

   Integer & neg();

   Integer & revsub(const Integer &b);

   Integer & operator += (const Integer &b);

   Integer & operator -= (const Integer &b);

   Integer & operator *= (const Integer &b);

   Integer & operator /= (const Integer &b);

   Integer & operator %= (const Integer &b);

   Integer & operator <<= (unsigned shift);

   Integer & operator >>= (unsigned shift);

   // operators

   Integer operator - () const
    {
     return Neg(getBody());
    }

   friend Integer operator + (const Integer &a,const Integer &b)
    {
     return Add(a.getBody(),b.getBody());
    }

   friend Integer operator - (const Integer &a,const Integer &b)
    {
     return Sub(a.getBody(),b.getBody());
    }

   friend Integer operator * (const Integer &a,const Integer &b)
    {
     return Mul(a.getBody(),b.getBody());
    }

   friend Integer operator / (const Integer &a,const Integer &b)
    {
     return Div(a.getBody(),b.getBody());
    }

   friend Integer operator % (const Integer &a,const Integer &b)
    {
     return Mod(a.getBody(),b.getBody());
    }

   Integer operator << (unsigned shift) const
    {
     if( shift )
       return LShift(getBody(),shift);
     else
       return (*this);
    }

   Integer operator >> (unsigned shift) const
    {
     if( shift )
       return RShift(getBody(),shift);
     else
       return (*this);
    }

   DivMod divmod(const Integer &b) const { return DivMod(getBody(),b.getBody()); }

   friend bool operator == (const Integer &a,const Integer &b) { return a.objCmp(b)==0; }

   friend bool operator != (const Integer &a,const Integer &b) { return a.objCmp(b)!=0; }

   friend bool operator < (const Integer &a,const Integer &b) { return a.objCmp(b)<0; }

   friend bool operator > (const Integer &a,const Integer &b) { return a.objCmp(b)>0; }

   friend bool operator <= (const Integer &a,const Integer &b) { return a.objCmp(b)<=0; }

   friend bool operator >= (const Integer &a,const Integer &b) { return a.objCmp(b)>=0; }

   // operators

   template <SUIntType SUInt>
   Integer & revsub(SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);

     return revsub(cast.getPtr(),cast.getLen());
    }

   template <SUIntType SUInt>
   Integer & operator += (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);

     return add(cast.getPtr(),cast.getLen());
    }

   template <SUIntType SUInt>
   Integer & operator -= (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);

     return sub(cast.getPtr(),cast.getLen());
    }

   template <SUIntType SUInt>
   Integer & operator *= (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);

     return mul(cast.getPtr(),cast.getLen());
    }

   template <SUIntType SUInt>
   Integer & operator /= (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);

     return div(cast.getPtr(),cast.getLen());
    }

   template <SUIntType SUInt>
   Integer & operator %= (SUInt val)
    {
     CastInteger<Algo,SUInt> cast(val);

     return mod(cast.getPtr(),cast.getLen());
    }

   template <SUIntType SUInt>
   DivMod divmod(SUInt b) const
    {
     CastInteger<Algo,SUInt> cast(b);

     return DivMod(getBody(),Range(cast));
    }

   template <SUIntType SUInt>
   CmpResult cmp(SUInt b) const
    {
     CastInteger<Algo,SUInt> cast(b);

     return Algo::Cmp(body.getPtr(),body.getLen(),cast.getPtr(),cast.getLen());
    }

   // print object

   using PrintOptType = IntegerPrintOpt ;

   void print(PrinterType &out,PrintOptType opt) const
    {
     PrintInteger<Integer> print(body.getLen());

     print(out,opt,*this);
    }

   // swap/move objects

   void objSwap(Integer &obj)
    {
     Swap(body,obj.body);
    }

   explicit Integer(ToMoveCtor<Integer> obj) : body(ToMoveCtor(obj->body)) {}
 };

 // normalization

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
void Integer<Algo,ArrayType,ArrayAlgoType>::normalize()
 {
  ulen len=body.getLen();
  ulen new_len=Algo::Normalize(body.getPtr(),len);

  if( len!=new_len ) body.shrink(len-new_len);

  body.shrink_extra();
 }

 // operators

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::add(const Unit *b,ulen nb)
 {
  ulen na=body.getLen();

  if( na>=nb )
    {
     Unit *a=body.append_raw();

     (*a)=Algo::Add(a-na,na,b,nb);
    }
  else
    {
     ArrayType<Unit,ArrayAlgoType<Unit> > result(DoBuild,AddBuilder(getBody(),Range(b,nb)));

     Swap(body,result);
    }

  normalize();

  return *this;
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::sub(const Unit *b,ulen nb)
 {
  ulen na=body.getLen();

  if( na>=nb )
    {
     Unit *a=body.append_raw();

     (*a)=Algo::Sub(a-na,na,b,nb);
    }
  else
    {
     ArrayType<Unit,ArrayAlgoType<Unit> > result(DoBuild,SubBuilder(getBody(),Range(b,nb)));

     Swap(body,result);
    }

  normalize();

  return *this;
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::revsub(const Unit *b,ulen nb)
 {
  ulen na=body.getLen();

  if( na>=nb )
    {
     Unit *a=body.append_raw();

     (*a)=Algo::RevSub(a-na,na,b,nb);
    }
  else
    {
     ArrayType<Unit,ArrayAlgoType<Unit> > result(DoBuild,SubBuilder(Range(b,nb),getBody()));

     Swap(body,result);
    }

  normalize();

  return *this;
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::mul(const Unit *b,ulen nb)
 {
  ArrayType<Unit,ArrayAlgoType<Unit> > result(DoBuild,MulBuilder(getBody(),Range(b,nb)));

  Swap(body,result);

  normalize();

  return *this;
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::div(const Unit *b,ulen nb)
 {
  IntegerDivider<Algo,TempArrayType> divider(getBody(),Range(b,nb));

  ArrayType<Unit,ArrayAlgoType<Unit> > result(DoCopy(divider.getResult().len),divider.getResult().ptr);

  body=std::move(result);

  return *this;
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::mod(const Unit *b,ulen nb)
 {
  IntegerDivider<Algo,TempArrayType> divider(getBody(),Range(b,nb),true);

  ArrayType<Unit,ArrayAlgoType<Unit> > result(DoCopy(divider.getMod().len),divider.getMod().ptr);

  body=std::move(result);

  return *this;
 }

 // methods

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
auto Integer<Algo,ArrayType,ArrayAlgoType>::bitsOf() const -> BitsOf
 {
  ulen len=body.getLen();

  if( len )
    {
     Unit msu=body[len-1];

     unsigned n;

     if( msu&Algo::MSBit )
       {
        n=Algo::CountZeroMSB(~msu);
       }
     else
       {
        n=Algo::CountZeroMSB(msu);
       }

     return BitsOf(len-1,UnitBits-n);
    }
  else
    {
     return BitsOf(0,0);
    }
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> Integer<Algo,ArrayType,ArrayAlgoType>::pow(unsigned deg) const
 {
  if( deg==0 ) return 1;

  if( deg==1 ) return *this;

  BitScanner<unsigned> scanner(deg);

  Integer ret(*this);

  for(++scanner; +scanner ;++scanner)
    if( *scanner )
      {
       ret=ret.sq()*(*this);
      }
    else
      {
       ret=ret.sq();
      }

  return ret;
 }

 // operators

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::neg()
 {
  ulen na=body.getLen();

  Unit *a=body.append_raw();

  *a=Algo::Neg(a-na,na);

  normalize();

  return *this;
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::revsub(const Integer<Algo,ArrayType,ArrayAlgoType> &b_)
 {
  const Unit *b=b_.body.getPtr();

  if( body.getPtr()==b ) return set_null();

  ulen nb=b_.body.getLen();

  return revsub(b,nb);
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator += (const Integer<Algo,ArrayType,ArrayAlgoType> &b_)
 {
  const Unit *b=b_.body.getPtr();

  if( body.getPtr()==b ) return (*this)<<=1;

  ulen nb=b_.body.getLen();

  return add(b,nb);
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator -= (const Integer<Algo,ArrayType,ArrayAlgoType> &b_)
 {
  const Unit *b=b_.body.getPtr();

  if( body.getPtr()==b ) return set_null();

  ulen nb=b_.body.getLen();

  return sub(b,nb);
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator *= (const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  return mul(b.body.getPtr(),b.body.getLen());
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator /= (const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  return div(b.body.getPtr(),b.body.getLen());
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator %= (const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  return mod(b.body.getPtr(),b.body.getLen());
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator <<= (unsigned shift_)
 {
  if( !shift_ ) return *this;

  unsigned full=unsigned(shift_/Algo::UnitBits);
  unsigned shift=unsigned(shift_%Algo::UnitBits);

  if( shift )
    {
     ulen n=body.getLen();

     AddLen(full,n,1);

     Unit *a=body.extend_raw(full+1).ptr-n;

     a[n+full]=Algo::ShiftUp(a,n,full,shift);

     Algo::Null(a,full);
    }
  else
    {
     ulen n=body.getLen();

     AddLen(full,n);

     Unit *a=body.extend_raw(full).ptr-n;

     Algo::MoveUp(a,n,full);

     Algo::Null(a,full);
    }

  return *this;
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType>
Integer<Algo,ArrayType,ArrayAlgoType> & Integer<Algo,ArrayType,ArrayAlgoType>::operator >>= (unsigned shift_)
 {
  if( !shift_ || body.getLen()==0 ) return *this;

  unsigned full=unsigned(shift_/Algo::UnitBits);
  unsigned shift=unsigned(shift_%Algo::UnitBits);

  PtrLen<Unit> data=body.modify();

  if( data.len<=full )
    {
     Unit a=Algo::SignExt(data.ptr,data.len);

     if( a==0 )
       {
        body.erase();
       }
     else
       {
        data[0]=a;

        body.shrink(data.len-1);
       }
    }
  else
    {
     ulen na=data.len-full;

     if( shift )
       {
        Algo::ShiftDown(data.ptr,na,full,shift);
       }
     else
       {
        Algo::MoveDown(data.ptr,na,full);
       }

     body.shrink(full);
    }

  return *this;
 }

 // operators

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator + (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b)
 {
  CastInteger<Algo,SUInt> cast(b);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Add(a.getBody(),Range(cast));
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator + (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  CastInteger<Algo,SUInt> cast(a);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Add(Range(cast),b.getBody());
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator - (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b)
 {
  CastInteger<Algo,SUInt> cast(b);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Sub(a.getBody(),Range(cast));
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator - (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  CastInteger<Algo,SUInt> cast(a);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Sub(Range(cast),b.getBody());
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator * (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b)
 {
  CastInteger<Algo,SUInt> cast(b);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Mul(a.getBody(),Range(cast));
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator * (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  CastInteger<Algo,SUInt> cast(a);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Mul(Range(cast),b.getBody());
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator / (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b)
 {
  CastInteger<Algo,SUInt> cast(b);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Div(a.getBody(),Range(cast));
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator / (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  CastInteger<Algo,SUInt> cast(a);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Div(Range(cast),b.getBody());
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator % (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b)
 {
  CastInteger<Algo,SUInt> cast(b);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Mod(a.getBody(),Range(cast));
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
Integer<Algo,ArrayType,ArrayAlgoType> operator % (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b)
 {
  CastInteger<Algo,SUInt> cast(a);

  return Integer<Algo,ArrayType,ArrayAlgoType>::Mod(Range(cast),b.getBody());
 }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator == (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b) { return a.cmp(b)==0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator == (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b) { return b.cmp(a)==0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator != (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b) { return a.cmp(b)!=0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator != (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b) { return b.cmp(a)!=0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator < (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b) { return a.cmp(b)<0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator < (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b) { return b.cmp(a)>0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator > (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b) { return a.cmp(b)>0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator > (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b) { return b.cmp(a)<0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator <= (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b) { return a.cmp(b)<=0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator <= (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b) { return b.cmp(a)>=0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator >= (const Integer<Algo,ArrayType,ArrayAlgoType> &a,SUInt b) { return a.cmp(b)>=0; }

template <IntAlgo Algo,template <class T,class A> class ArrayType,template <class T,class F=GetNoThrowFlags<T> > class ArrayAlgoType,SUIntType SUInt>
bool operator >= (SUInt a,const Integer<Algo,ArrayType,ArrayAlgoType> &b) { return b.cmp(a)<=0; }

/* class RandomInteger<Integer> */

template <class Integer>
class RandomInteger : public Integer
 {
   using Unit = typename Integer::Unit ;

   template <class Random>
   class Builder
    {
      ulen n;
      Random &random;

     public:

      Builder(ulen n_,Random &random_) : n(n_),random(random_) {}

      ulen getLen() const { return n; }

      PtrLen<Unit> operator () (Place<void> place) const
       {
        PtrLen<Unit> ret(place,n);

        random.fill(ret);

        return ret;
       }
    };

  public:

   template <RandomType Random>
   RandomInteger(ulen n,Random &random) : Integer(DoBuild,Builder<Random>(n,random)) {}

   ~RandomInteger() {}
 };

} // namespace Math
} // namespace CCore

#endif


