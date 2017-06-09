/* SHA.h */
//----------------------------------------------------------------------------------------
//
//  Project: CCore 3.00
//
//  Tag: Applied
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2015 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#ifndef CCore_inc_crypton_SHA_h
#define CCore_inc_crypton_SHA_h

#include <CCore/inc/crypton/HashFunction.h>
#include <CCore/inc/crypton/Rot.h>

namespace CCore {
namespace Crypton {

/* classes */

struct SHA32Word;
struct SHA64Word;

struct SHA1Param;
struct SHA256Param;
struct SHA224Param;
struct SHA512Param;
struct SHA384Param;

template <class Param> struct SHABlock;

template <class Param> struct SHA;

/* struct SHA32Word */

struct SHA32Word
 {
  static constexpr ulen BlockLen  = 64 ;
  static constexpr ulen TailLen   =  8 ;
  static constexpr ulen WLoadLen  = 16 ;

  using Word = uint32 ;

  using TotalType = uint64 ;

  static void Load(Word &x,const uint8 data[4]);

  static void Save(Word x,uint8 data[4]);

  static void Load(Word W[WLoadLen],const uint8 block[BlockLen]);

  static void Load(Word W[WLoadLen],const uint8 block[BlockLen-TailLen],TotalType total);
 };

/* struct SHA64Word */

struct SHA64Word
 {
  static constexpr ulen BlockLen  = 128 ;
  static constexpr ulen TailLen   =  16 ;
  static constexpr ulen WLoadLen  =  16 ;

  using Word = uint64 ;

  struct TotalType
   {
    Word hi = 0 ;
    Word lo = 0 ;

    TotalType() noexcept {}

    void operator = (Word lo_)
     {
      hi=0;
      lo=lo_;
     }

    void operator += (Word delta)
     {
      if( (lo+=delta)<delta ) hi++;
     }
   };

  static void Load(Word &x,const uint8 data[8]);

  static void Save(Word x,uint8 data[8]);

  static void Load(Word W[WLoadLen],const uint8 block[BlockLen]);

  static void Load(Word W[WLoadLen],const uint8 block[BlockLen-TailLen],TotalType total);
 };

/* struct SHA1Param */

struct SHA1Param : SHA32Word
 {
  static constexpr ulen DigestLen = 20 ;
  static constexpr ulen WLen      = 80 ;

  static const char *const Name;

  struct State
   {
    // data

    Word a = 0 ;
    Word b = 0 ;
    Word c = 0 ;
    Word d = 0 ;
    Word e = 0 ;

    // private

    static void Extend(Word W[WLen]);

    static Word Func1(Word b,Word c,Word d) { return Word( ((b&c)^(~b&d))+0x5A827999u ); }

    static Word Func2(Word b,Word c,Word d) { return Word( (b^c^d)+0x6ED9EBA1u ); }

    static Word Func3(Word b,Word c,Word d) { return Word( ((b&c)^(b&d)^(c&d))+0x8F1BBCDCu ); }

    static Word Func4(Word b,Word c,Word d) { return Word( (b^c^d)+0xCA62C1D6u ); }

    static constexpr ulen RunLen = 20 ;

    template <Word Func(Word,Word,Word)>
    static void Run(Word &a,Word &b,Word &c,Word &d,Word &e,Word w)
     {
      e+=Word( Rol32(a,5)+Func(b,c,d)+w );
      b=Ror32(b,2);
     }

    template <Word Func(Word,Word,Word)>
    void run5(const Word W[5])
     {
      Run<Func>(a,b,c,d,e,W[0]);
      Run<Func>(e,a,b,c,d,W[1]);
      Run<Func>(d,e,a,b,c,W[2]);
      Run<Func>(c,d,e,a,b,W[3]);
      Run<Func>(b,c,d,e,a,W[4]);
     }

    template <Word Func(Word,Word,Word)>
    void run(const Word W[RunLen])
     {
#if 0

      for(ulen i=0; i<RunLen ;i++)
        {
         Word temp=Word( Rol32(a,5)+Func(b,c,d)+e+W[i] );

         e=d;
         d=c;
         c=Ror32(b,2);
         b=a;
         a=temp;
        }

#else

      run5<Func>(W);
      run5<Func>(W+5);
      run5<Func>(W+10);
      run5<Func>(W+15);

#endif
     }

    void add(Word W[WLen]);

    // public

    State() noexcept {}

    void reset()
     {
      a=0x67452301;
      b=0xEFCDAB89;
      c=0x98BADCFE;
      d=0x10325476;
      e=0xC3D2E1F0;
     }

    void forget()
     {
      Forget(*this);
     }

    void add(const uint8 block[BlockLen]);

    void add(const uint8 block[BlockLen-TailLen],TotalType total);

    void finish(uint8 digest[DigestLen]);
   };
 };

/* struct SHA256Param */

struct SHA256Param : SHA32Word
 {
  static constexpr ulen DigestLen = 32 ;
  static constexpr ulen WLen      = 64 ;

  static const char *const Name;

  struct State
   {
    // data

    Word a = 0 ;
    Word b = 0 ;
    Word c = 0 ;
    Word d = 0 ;
    Word e = 0 ;
    Word f = 0 ;
    Word g = 0 ;
    Word h = 0 ;

    // private

    static const Word K[WLen];

    static Word Sigma0(Word w) { return Word( Ror32(w,7)^Ror32(w,18)^(w>>3) ); }

    static Word Sigma1(Word w) { return Word( Ror32(w,17)^Ror32(w,19)^(w>>10) ); }

    static Word USigma0(Word w) { return Word( Ror32(w,2)^Ror32(w,13)^Ror32(w,22) ); }

    static Word USigma1(Word w) { return Word( Ror32(w,6)^Ror32(w,11)^Ror32(w,25) ); }

    static void Extend(Word W[WLen]);

    static void Run(Word &a,Word &b,Word &c,Word &d,Word &e,Word &f,Word &g,Word &h,Word w);

    void run8(const Word W[8],const Word K[8]);

    void run(const Word W[WLen]);

    void add(Word W[WLen]);

    // public

    State() noexcept {}

    void reset()
     {
      a=0x6A09E667;
      b=0xBB67AE85;
      c=0x3C6EF372;
      d=0xA54FF53A;
      e=0x510E527F;
      f=0x9B05688C;
      g=0x1F83D9AB;
      h=0x5BE0CD19;
     }

    void forget()
     {
      Forget(*this);
     }

    void add(const uint8 block[BlockLen]);

    void add(const uint8 block[BlockLen-TailLen],TotalType total);

    void finish(uint8 digest[DigestLen]);
   };
 };

/* struct SHA224Param */

struct SHA224Param : SHA32Word
 {
  static constexpr ulen DigestLen = 28 ;
  static constexpr ulen WLen      = 64 ;

  static const char *const Name;

  struct State : SHA256Param::State
   {
    void reset()
     {
      a=0xC1059ED8;
      b=0x367CD507;
      c=0x3070DD17;
      d=0xF70E5939;
      e=0xFFC00B31;
      f=0x68581511;
      g=0x64F98FA7;
      h=0xBEFA4FA4;
     }

    void finish(uint8 digest[DigestLen]);
   };
 };

/* struct SHA512Param */

struct SHA512Param : SHA64Word
 {
  static constexpr ulen DigestLen = 64 ;
  static constexpr ulen WLen      = 80 ;

  static const char *const Name;

  struct State
   {
    // data

    Word a = 0 ;
    Word b = 0 ;
    Word c = 0 ;
    Word d = 0 ;
    Word e = 0 ;
    Word f = 0 ;
    Word g = 0 ;
    Word h = 0 ;

    // private

    static const Word K[WLen];

    static Word Sigma0(Word w) { return Word( Ror64(w,1)^Ror64(w,8)^(w>>7) ); }

    static Word Sigma1(Word w) { return Word( Ror64(w,19)^Ror64(w,61)^(w>>6) ); }

    static Word USigma0(Word w) { return Word( Ror64(w,28)^Ror64(w,34)^Ror64(w,39) ); }

    static Word USigma1(Word w) { return Word( Ror64(w,14)^Ror64(w,18)^Ror64(w,41) ); }

    static void Extend(Word W[WLen]);

    static void Run(Word &a,Word &b,Word &c,Word &d,Word &e,Word &f,Word &g,Word &h,Word w);

    void run8(const Word W[8],const Word K[8]);

    void run(const Word W[WLen]);

    void add(Word W[WLen]);

    // public

    State() noexcept {}

    void reset()
     {
      a=0x6A09E667F3BCC908ull;
      b=0xBB67AE8584CAA73Bull;
      c=0x3C6EF372FE94F82Bull;
      d=0xA54FF53A5F1D36F1ull;
      e=0x510E527FADE682D1ull;
      f=0x9B05688C2B3E6C1Full;
      g=0x1F83D9ABFB41BD6Bull;
      h=0x5BE0CD19137E2179ull;
     }

    void forget()
     {
      Forget(*this);
     }

    void add(const uint8 block[BlockLen]);

    void add(const uint8 block[BlockLen-TailLen],TotalType total);

    void finish(uint8 digest[DigestLen]);
   };
 };

/* struct SHA384Param */

struct SHA384Param : SHA64Word
 {
  static constexpr ulen DigestLen = 48 ;
  static constexpr ulen WLen      = 80 ;

  static const char *const Name;

  struct State : SHA512Param::State
   {
    void reset()
     {
      a=0xCBBB9D5DC1059ED8ull;
      b=0x629A292A367CD507ull;
      c=0x9159015A3070DD17ull;
      d=0x152FECD8F70E5939ull;
      e=0x67332667FFC00B31ull;
      f=0x8EB44A8768581511ull;
      g=0xDB0C2E0D64F98FA7ull;
      h=0x47B5481DBEFA4FA4ull;
     }

    void finish(uint8 digest[DigestLen]);
   };
 };

/* struct SHABlock<Param> */

template <class Param>
struct SHABlock
 {
  // consts

  static constexpr ulen Len     = Param::BlockLen ;
  static constexpr ulen TailLen =  Param::TailLen ;
  static constexpr ulen LastLen =   Len - TailLen ;

  // data

  uint8 block[Len];
  ulen len;
  typename Param::TotalType total;

  // methods

  void reset()
   {
    Range(block).set_null();

    len=0;
    total=0;
   }

  void forget()
   {
    Forget(block);
    Forget(len);
    Forget(total);
   }

  ulen feed(const uint8 *data,ulen data_len)
   {
    ulen delta=Min<ulen>(Len-len,data_len);

    Range(data,delta).copyTo(block+len);

    len+=delta;

    count(delta);

    return delta;
   }

  void feed_short(const uint8 *data,ulen data_len)
   {
    Range(data,data_len).copyTo(block);

    len=data_len;

    count(data_len);
   }

  bool operator ! () const { return len<Len; }

  const uint8 * take()
   {
    len=0;

    return block;
   }

  void count(ulen delta=Len)
   {
    total+=delta*8;
   }

  bool pad()
   {
    block[len]=0x80;

    if( len<LastLen )
      {
       Range(block+len+1,LastLen-len-1).set_null();

       return true;
      }
    else
      {
       Range(block+len+1,Len-len-1).set_null();

       return false;
      }
   }

  void pad2()
   {
    Range(block,LastLen).set_null();
   }
 };

/* struct SHA<Param> */

template <class Param>
struct SHA
 {
  // consts

  static constexpr ulen DigestLen = Param::DigestLen ;

  static constexpr ulen BlockLen  = Param::BlockLen ;

  static const char * GetName() { return Param::Name; }

  // data

  SHABlock<Param> block;
  typename Param::State state;

  // methods

  void reset() noexcept
   {
    block.reset();
    state.reset();
   }

  void forget() noexcept
   {
    block.forget();
    state.forget();
   }

  void add(const uint8 *data,ulen len)
   {
    // 1
    {
     ulen delta=block.feed(data,len);

     if( !block ) return;

     data+=delta;
     len-=delta;

     state.add(block.take());
    }

    // 2
    while( len>=Param::BlockLen )
      {
       block.count();

       state.add(data);

       data+=Param::BlockLen;
       len-=Param::BlockLen;
      }

    // 3
    {
     block.feed_short(data,len);
    }
   }

  void finish(uint8 digest[DigestLen])
   {
    if( !block.pad() )
      {
       state.add(block.block);

       block.pad2();
      }

    state.add(block.block,block.total);
    state.finish(digest);
   }
 };

/* types */

using SHA1   = HashFunction<SHA<SHA1Param> > ;
using SHA224 = HashFunction<SHA<SHA224Param> > ;
using SHA256 = HashFunction<SHA<SHA256Param> > ;
using SHA384 = HashFunction<SHA<SHA384Param> > ;
using SHA512 = HashFunction<SHA<SHA512Param> > ;

using KeyedSHA1   = KeyedHashFunction<SHA<SHA1Param> > ;
using KeyedSHA224 = KeyedHashFunction<SHA<SHA224Param> > ;
using KeyedSHA256 = KeyedHashFunction<SHA<SHA256Param> > ;
using KeyedSHA384 = KeyedHashFunction<SHA<SHA384Param> > ;
using KeyedSHA512 = KeyedHashFunction<SHA<SHA512Param> > ;

} // namespace Crypton
} // namespace CCore

#endif


