/* test3037.Deflate.cpp */
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
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <CCore/test/test.h>

#include <CCore/inc/Array.h>
#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BestSearch.h>
#include <CCore/inc/algon/BinarySearch.h>

namespace App {

namespace Private_3037 {

/* struct Code */

using UCode = uint32 ; // max 16 bits

using USym  = uint32 ; // max 16 bits

using BitLen = unsigned ; // <= 16

struct Code
 {
  UCode code;
  BitLen bitlen;
 };

/* BitReverse() */

uint32 BitSwap(uint32 value,uint32 hi,uint32 lo,unsigned shift)
 {
  return uint32( (value&hi)>>shift )|uint32( (value&lo)<<shift );
 }

uint32 BitReverse(uint32 value)
 {
  value=BitSwap(value,0xAAAAAAAAu,0x55555555u,1);
  value=BitSwap(value,0xCCCCCCCCu,0x33333333u,2);
  value=BitSwap(value,0xF0F0F0F0u,0x0F0F0F0Fu,4);

  return Quick::ByteSwap32(value);
 }

/* class LowFirstBitWriter */

class LowFirstBitWriter : NoCopy
 {
   static constexpr unsigned BufLen = 256 ;

   bool m_counting;
   ulen m_bitCount;

   uint8 m_outputBuffer[BufLen];
   unsigned m_bytesBuffered;

   uint32 m_buffer;
   unsigned m_bitsBuffered;

   Function<void (const uint8 *,ulen)> out;

  private:

   void put(uint8 byte)
    {
     out(&byte,1);
    }

   void put(const uint8 *bytes,ulen len)
    {
     out(bytes,len);
    }

  public:

   explicit LowFirstBitWriter(Function<void (const uint8 *,ulen)> out);

   void StartCounting();

   ulen FinishCounting();

   void PutBits(Code code);

   void FlushBitBuffer();

   void ClearBitBuffer();
 };

LowFirstBitWriter::LowFirstBitWriter(Function<void (const uint8 *,ulen)> out_)
 : m_counting(false),
   m_bitCount(0),
   m_bytesBuffered(0),
   m_buffer(0),
   m_bitsBuffered(0),
   out(out_)
 {
 }

void LowFirstBitWriter::StartCounting()
 {
  m_counting=true;
  m_bitCount=0;
 }

ulen LowFirstBitWriter::FinishCounting()
 {
  m_counting=false;

  return m_bitCount;
 }

void LowFirstBitWriter::PutBits(Code code)
 {
  if( m_counting )
    {
     m_bitCount+=code.bitlen;
    }
  else
    {
     m_buffer |= (code.code<<m_bitsBuffered) ;
     m_bitsBuffered+=code.bitlen;

     while( m_bitsBuffered>=8 )
       {
        m_outputBuffer[m_bytesBuffered++]=(uint8)m_buffer;

        if( m_bytesBuffered==BufLen )
          {
           put(m_outputBuffer,m_bytesBuffered);
           m_bytesBuffered=0;
          }

        m_buffer>>=8;
        m_bitsBuffered-=8;
       }
    }
 }

void LowFirstBitWriter::FlushBitBuffer() // TODO
 {
  if( m_counting )
    {
     m_bitCount += 8*(m_bitsBuffered>0) ; // ?
    }
  else
    {
     if( m_bytesBuffered>0 )
       {
        put(m_outputBuffer,m_bytesBuffered);

        m_bytesBuffered=0;
       }

     if( m_bitsBuffered>0 )
       {
        put((uint8)m_buffer);

        m_buffer=0;
        m_bitsBuffered=0;
       }
    }
 }

void LowFirstBitWriter::ClearBitBuffer()
 {
  m_buffer=0;
  m_bytesBuffered=0;
  m_bitsBuffered=0;
 }

/* class HuffmanEncoder */

class HuffmanEncoder : NoCopy
 {
   DynArray<Code> m_valueToCode;

  private:

   static BitLen MaxValue(PtrLen<const BitLen> bitlens);

  public:

   static constexpr ulen MaxBitLens = 15 ;
   static constexpr ulen MaxSyms = 286 ;

   HuffmanEncoder() {}

   HuffmanEncoder(PtrLen<const BitLen> bitlens) { Initialize(bitlens); }

   void Initialize(PtrLen<const BitLen> bitlens);

   static void Tree(BitLen bitlens[ /* counts.len */ ],BitLen maxbitlen,PtrLen<const ulen> counts);

     // counts.len > 0 && counts.len <= 2^maxbitlen

   void Encode(LowFirstBitWriter &writer,USym sym) const
    {
     writer.PutBits(m_valueToCode[sym]);
    }
 };

BitLen HuffmanEncoder::MaxValue(PtrLen<const BitLen> bitlens)
 {
  auto r=Algon::BestSearch(bitlens, [] (BitLen a,BitLen b) { return a>b; } );

  if( !r ) return 0;

  return *r;
 }

void HuffmanEncoder::Initialize(PtrLen<const BitLen> bitlens)
 {
  // count table

  ulen len=(ulen)MaxValue(bitlens)+1;

  TempArray<ulen,MaxBitLens+1> counts(len);

  Range(counts).set_null();

  for(BitLen bitlen : bitlens ) counts[bitlen]++;

  // base codes

  TempArray<UCode,MaxBitLens+1> code(len);

  {
   UCode next=0;

   code[1]=next;

   for(ulen i=2; i<len ;i++)
     {
      next = (next+counts[i-1]) << 1 ;

      code[i]=next;
     }
  }

  // set codes

  m_valueToCode.erase();
  m_valueToCode.extend_raw(bitlens.len);

  for(ulen i=0; i<bitlens.len ;i++)
    {
     BitLen bitlen=bitlens[i];

     m_valueToCode[i].bitlen=bitlen;

     if( bitlen!=0 )
       m_valueToCode[i].code = BitReverse(code[bitlen]++) >> (32u-bitlen) ;
     else
       m_valueToCode[i].code = 0 ;
    }
 }

void HuffmanEncoder::Tree(BitLen bitlens[ /* counts.len */ ],BitLen maxbitlen,PtrLen<const ulen> counts)
 {
  struct Node
   {
    ulen sym;

    union
     {
      ulen count;
      ulen parent;
      ulen depth;
     };
   };

  // Huffman tree

  TempArray<Node,2*MaxSyms> tree(2*counts.len);

  for(ulen i=0; i<counts.len ;i++)
    {
     tree[i].sym=i;
     tree[i].count=counts[i];
    }

  auto initial=Range(tree.getPtr(),counts.len);

  IncrSort(initial, [] (const Node &a,const Node &b) { return a.count<b.count; } );

  Algon::BinarySearch_if(initial, [] (const Node &a) { return a.count>0; } );

  if( !initial )
    {
     Range(bitlens,counts.len).set_null();

     return;
    }

  // build

  ulen beg=counts.len-initial.len;
  ulen lim=counts.len+initial.len-1;

  for(ulen next=counts.len,leaf=beg,comb=counts.len; next<lim ;next++)
    {
     ulen least =

      ( leaf==counts.len || ( comb<next && tree[comb].count<tree[leaf].count ) ) ? comb++ : leaf++ ;

     tree[next].count=tree[least].count;
     tree[least].parent=next;

     least = ( leaf==counts.len || ( comb<next && tree[comb].count<tree[leaf].count ) ) ? comb++ : leaf++ ;

     tree[next].count+=tree[least].count;
     tree[least].parent=next;
    }

  // combo depth

  if( lim>=2 )
    {
     tree[lim-1].depth=0;

     for(ulen i=lim-2; i>=counts.len ;i--)
       tree[i].depth=tree[tree[i].parent].depth+1;
    }

  // bitlen counts

  TempArray<BitLen,MaxBitLens+1> blcounts(maxbitlen+1);

  Range(blcounts).set_null();

  ulen sum=0;

  for(ulen i=beg; i<counts.len ;i++)
    {
     ulen comb=tree[i].parent;
     ulen depth=Min<ulen>(maxbitlen,tree[comb].depth+1);

     blcounts[depth]++;

     sum += ulen(1)<<(maxbitlen-depth) ;
    }

  // bitlens

  ulen cap=ulen(1)<<maxbitlen;

  ulen overflow = ( sum>cap )? sum-cap : 0 ;

  while( overflow-- )
    {
     BitLen bits=maxbitlen-1;

     while( blcounts[bits]==0 ) bits--;

     blcounts[bits]--;
     blcounts[bits+1]+=2;

     blcounts[maxbitlen]--;
    }

  for(ulen i=0; i<beg ;i++) bitlens[tree[i].sym]=0;

  BitLen bits=maxbitlen;

  for(ulen i=beg; i<counts.len ;i++)
    {
     while( blcounts[bits]==0 ) bits--;

     bitlens[tree[i].sym]=bits;

     blcounts[bits]--;
    }
 }

//----------------------------------------------------------------------------------------


} // namespace Private_3037

using namespace Private_3037;

/* Testit<3037> */

template<>
const char *const Testit<3037>::Name="Test3037 Deflate";

template<>
bool Testit<3037>::Main()
 {
  return true;
 }

} // namespace App

