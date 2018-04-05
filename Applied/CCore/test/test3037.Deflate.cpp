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

#include <CCore/inc/Exception.h>

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/BinaryFile.h>

namespace App {

namespace Private_3037 {

/* consts */

inline constexpr ulen MaxBitLens = 15 ;

inline constexpr ulen MaxSyms = 286 ;

/* struct Code */

using UCode = uint32 ;

using USym  = uint32 ;

using BitLen = unsigned ;

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

/* Mismatch() */

template <class Ptr>
Ptr Mismatch(Ptr a,Ptr lim,Ptr b)
 {
  for(; a<lim ;++a,++b) if( *a!=*b ) return a;

  return lim;
 }

/* TrimNull() */

template <class Ptr>
ulen TrimNull(Ptr beg,Ptr lim)
 {
  while( beg<lim && lim[-1]==0 ) --lim;

  return Dist(beg,lim);
 }

/* class BitWriter */

using OutFunc = Function<void (PtrLen<const uint8>)> ;

class BitWriter : NoCopy
 {
   static constexpr unsigned BufLen = 256 ;

   OutFunc out;

   bool count_mode = false ;
   ulen bit_count = 0 ;

   uint8 outbuf[BufLen];
   unsigned outlen = 0 ;

   uint32 buffer = 0 ;
   unsigned bits = 0 ;

  private:

   void put(uint8 octet) { out(Single(octet)); }

  public:

   explicit BitWriter(OutFunc out);

   // direct

   void put16(uint16 value)
    {
     uint8 buf[2]={ uint8(value) , uint8(value>>8) };

     out(Range(buf));
    }

   void put(PtrLen<const uint8> data) { out(data); }

   void put(const uint8 *ptr,ulen len) { out(Range(ptr,len)); }

   // bitbuf

   void putBits(Code code);

   void flushBitBuffer();

   void clearBitBuffer();

   // bit counting

   void startCounting();

   ulen finishCounting();

   unsigned extBits() const { return RoundUp<unsigned>(bits+3,8)-bits; } // TODO ?
 };

BitWriter::BitWriter(OutFunc out_)
 : out(out_)
 {
 }

void BitWriter::putBits(Code code)
 {
  if( count_mode )
    {
     bit_count+=code.bitlen;
    }
  else
    {
     buffer|=(code.code<<bits) ;
     bits+=code.bitlen;

     while( bits>=8 )
       {
        outbuf[outlen++]=(uint8)buffer;

        if( outlen==BufLen )
          {
           put(outbuf,outlen);
           outlen=0;
          }

        buffer>>=8;
        bits-=8;
       }
    }
 }

void BitWriter::flushBitBuffer() // TODO
 {
  if( count_mode )
    {
     bit_count += 8*(bits>0) ; // ?
    }
  else
    {
     if( outlen>0 )
       {
        put(outbuf,outlen);

        outlen=0;
       }

     if( bits>0 )
       {
        put((uint8)buffer);

        buffer=0;
        bits=0;
       }
    }
 }

void BitWriter::clearBitBuffer()
 {
  buffer=0;
  bits=0;

  outlen=0;
 }

void BitWriter::startCounting()
 {
  count_mode=true;
  bit_count=0;
 }

ulen BitWriter::finishCounting()
 {
  count_mode=false;

  return bit_count;
 }

/* class HuffmanEncoder */

class HuffmanEncoder : NoCopy
 {
   DynArray<Code> table;

  private:

   static BitLen MaxValue(PtrLen<const BitLen> bitlens);

  public:

   HuffmanEncoder() {}

   HuffmanEncoder(PtrLen<const BitLen> bitlens) { init(bitlens); }

   void init(PtrLen<const BitLen> bitlens);

   static void Tree(BitLen bitlens[ /* counts.len */ ],BitLen maxbitlen,PtrLen<const ulen> counts);

     // maxbitlen>0 && counts.len>0 && counts.len <= 2^maxbitlen

   void encode(BitWriter &writer,USym sym) const { writer.putBits(table[sym]); }
 };

BitLen HuffmanEncoder::MaxValue(PtrLen<const BitLen> bitlens)
 {
  auto r=Algon::BestSearch(bitlens, [] (BitLen a,BitLen b) { return a>b; } );

  if( !r ) return 0;

  return *r;
 }

void HuffmanEncoder::init(PtrLen<const BitLen> bitlens)
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

  table.erase();
  table.extend_raw(bitlens.len);

  for(ulen i=0; i<bitlens.len ;i++)
    {
     BitLen bitlen=bitlens[i];

     table[i].bitlen=bitlen;

     if( bitlen!=0 )
       table[i].code = BitReverse(code[bitlen]++) >> (32u-bitlen) ;
     else
       table[i].code = 0 ;
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

  if( initial.len==1 )
    {
     Range(bitlens,counts.len).set_null();

     bitlens[initial->sym]=1;

     return;
    }

  // build

  ulen beg=counts.len-initial.len;
  ulen lim=counts.len+initial.len-1;

  struct Builder
   {
    Node *tree;
    ulen leaf;
    ulen comb;

    ulen getLeast(ulen leaf_lim,ulen comb_lim)
     {
      return ( leaf>=leaf_lim || ( comb<comb_lim && tree[comb].count<tree[leaf].count ) ) ? comb++ : leaf++ ;
     }

    void setComb(ulen ind,ulen elem)
     {
      tree[ind].count=tree[elem].count;
      tree[elem].parent=ind;
     }

    void addComb(ulen ind,ulen elem)
     {
      tree[ind].count+=tree[elem].count;
      tree[elem].parent=ind;
     }
   };

  Builder builder{tree.getPtr(),beg,counts.len};

  for(ulen next=counts.len; next<lim ;next++)
    {
     builder.setComb(next, builder.getLeast(counts.len,next) );

     builder.addComb(next, builder.getLeast(counts.len,next) );
    }

  // combo depth

  tree[lim-1].depth=0;

  for(ulen i=lim-2; i>=counts.len ;i--)
    tree[i].depth=tree[tree[i].parent].depth+1;

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

/* enum DeflateLevel */

enum DeflateLevel
 {
  NO_DEFLATE_LEVEL = -1,

  MIN_DEFLATE_LEVEL     = 0,
  DEFAULT_DEFLATE_LEVEL = 6,
  MAX_DEFLATE_LEVEL     = 9
 };

/* enum DeflateLog2WindowSize */

enum DeflateLog2WindowSize
 {
  MIN_LOG2_WINDOW_SIZE     =  9,
  DEFAULT_LOG2_WINDOW_SIZE = 15,
  MAX_LOG2_WINDOW_SIZE     = 15
 };

/* struct DeflateParam */

struct DeflateParam
 {
  DeflateLevel level = DEFAULT_DEFLATE_LEVEL ;
  DeflateLog2WindowSize log2_window_size = DEFAULT_LOG2_WINDOW_SIZE ;
  bool detect_uncompressible = true ;

  DeflateParam() {}
 };

/* class Deflator */

class Deflator : NoCopy
 {
   BitWriter writer;

   DeflateLevel m_deflateLevel = NO_DEFLATE_LEVEL ;
   DeflateLog2WindowSize m_log2WindowSize;
   DeflateLevel m_compressibleDeflateLevel;

   unsigned DSIZE, DMASK, HSIZE, HMASK, GOOD_MATCH, MAX_LAZYLENGTH, MAX_CHAIN_LENGTH;

   unsigned m_detectSkip, m_detectCount;

   bool m_headerWritten, m_matchAvailable;

   unsigned m_dictionaryEnd, m_stringStart, m_lookahead, m_minLookahead, m_previousMatch, m_previousLength;

   HuffmanEncoder m_staticLiteralEncoder, m_staticDistanceEncoder, m_dynamicLiteralEncoder, m_dynamicDistanceEncoder;

   SimpleArray<uint8> m_byteBuffer;
   SimpleArray<uint16> m_head, m_prev;

   unsigned m_literalCounts[286];
   unsigned m_distanceCounts[30];

   struct EncodedMatch
    {
     unsigned literalCode : 9 ;
     unsigned literalExtra : 5 ;
     unsigned distanceCode : 5 ;
     unsigned distanceExtra : 13 ;
    };

   SimpleArray<EncodedMatch> m_matchBuffer;

   unsigned m_matchBufferEnd, m_blockStart, m_blockLength;

  private:

   enum { STORED = 0, STATIC = 1, DYNAMIC = 2 };

   enum { MIN_MATCH = 3, MAX_MATCH = 258 };

   void initializeStaticEncoders();

   void init(DeflateParam param);

   void Reset(bool forceReset=false);

   unsigned FillWindow(const uint8 *str,ulen len);

   unsigned ComputeHash(const uint8 *str) const;

   unsigned LongestMatch(unsigned &bestMatch) const;

   void InsertString(unsigned start);

   void ProcessBuffer();

   void LiteralByte(uint8 b);

   void MatchFound(unsigned distance,unsigned length);

   static unsigned CodeLengthEncode(const unsigned *beg,const unsigned *lim,const unsigned * &p,unsigned &extraBits,unsigned &extraBitsLength);

   void EncodeBlock(bool eof,unsigned blockType);

   void EndBlock(bool eof);

  public:

   explicit Deflator(OutFunc out,DeflateParam param={});

   ~Deflator();

   void setDeflateLevel(DeflateLevel deflateLevel);

   DeflateLevel getDeflateLevel() const { return m_deflateLevel; }

   DeflateLog2WindowSize getLog2WindowSize() const { return m_log2WindowSize; }

   void put(const uint8 *ptr,ulen len);

   void put(PtrLen<const uint8> data) { put(data.ptr,data.len); }

   void complete();

   void isolatedFlush(bool hardFlush);
 };

void Deflator::initializeStaticEncoders()
 {
  // literal

  {
   BitLen bitlens[288];

   Range(bitlens+0,bitlens+144).set(8);
   Range(bitlens+144,bitlens+256).set(9);
   Range(bitlens+256,bitlens+280).set(7);
   Range(bitlens+280,bitlens+288).set(8);

   m_staticLiteralEncoder.init(Range(bitlens));
  }

  // distance

  {
   BitLen bitlens[32];

   Range(bitlens).set(5);

   m_staticDistanceEncoder.init(Range(bitlens));
  }
 }

void Deflator::init(DeflateParam param)
 {
  if( !( MIN_LOG2_WINDOW_SIZE<=param.log2_window_size && param.log2_window_size<=MAX_LOG2_WINDOW_SIZE) )
    {
     Printf(Exception,"Deflator: #; is an invalid window size",param.log2_window_size);
    }

  m_log2WindowSize = param.log2_window_size ;

  DSIZE = 1 << m_log2WindowSize ;
  DMASK = DSIZE - 1 ;
  HSIZE = 1 << m_log2WindowSize ;
  HMASK = HSIZE - 1 ;

  m_byteBuffer=SimpleArray<uint8>(2*DSIZE);

  m_head=SimpleArray<uint16>(HSIZE);
  m_prev=SimpleArray<uint16>(DSIZE);

  m_matchBuffer=SimpleArray<EncodedMatch>(DSIZE/2);

  Reset(true);

  setDeflateLevel(param.level);

  m_compressibleDeflateLevel = param.detect_uncompressible ? m_deflateLevel : MIN_DEFLATE_LEVEL ;
 }


Deflator::Deflator(OutFunc out,DeflateParam param)
 : writer(out)
 {
  initializeStaticEncoders();

  init(param);
 }

Deflator::~Deflator()
 {
 }

void Deflator::setDeflateLevel(DeflateLevel deflateLevel)
 {
  if( !( deflateLevel>=MIN_DEFLATE_LEVEL && deflateLevel<=MAX_DEFLATE_LEVEL ) )
    {
     Printf(Exception,"Deflator: #; is an invalid deflate level",deflateLevel);
    }

  if( deflateLevel==m_deflateLevel ) return;

  EndBlock(false);

  static const unsigned configurationTable[10][4]=
   {
    /* 0 */ {0,    0,  0,    0},  // store only
    /* 1 */ {4,    3,  8,    4},  // maximum speed, no lazy matches
    /* 2 */ {4,    3, 16,    8},
    /* 3 */ {4,    3, 32,   32},
    /* 4 */ {4,    4, 16,   16},  // lazy matches
    /* 5 */ {8,   16, 32,   32},
    /* 6 */ {8,   16, 128, 128},
    /* 7 */ {8,   32, 128, 256},
    /* 8 */ {32, 128, 258, 1024},
    /* 9 */ {32, 258, 258, 4096} // maximum compression
   };

  GOOD_MATCH = configurationTable[deflateLevel][0] ;
  MAX_LAZYLENGTH = configurationTable[deflateLevel][1] ;
  MAX_CHAIN_LENGTH = configurationTable[deflateLevel][3] ;

  m_deflateLevel = deflateLevel ;
 }

void Deflator::Reset(bool forceReset)
 {
  if( forceReset ) writer.clearBitBuffer();

  m_headerWritten = false ;
  m_matchAvailable = false ;
  m_dictionaryEnd = 0 ;
  m_stringStart = 0 ;
  m_lookahead = 0 ;
  m_minLookahead = MAX_MATCH ;
  m_matchBufferEnd = 0 ;
  m_blockStart = 0 ;
  m_blockLength = 0 ;

  m_detectCount = 1 ;
  m_detectSkip = 0 ;

  // m_prev will be initialized automatically in InsertString

  Range(m_head).set_null();
  Range(m_literalCounts).set_null();
  Range(m_distanceCounts).set_null();
 }


unsigned Deflator::FillWindow(const uint8 *str,ulen len)
 {
  unsigned maxBlockSize = (unsigned)Min(2UL*DSIZE,0xffffUL) ;

  uint8 *base=m_byteBuffer.getPtr();

  if( m_stringStart>=maxBlockSize-MAX_MATCH )
    {
     if( m_blockStart<DSIZE ) EndBlock(false);

     Range(base,DSIZE).copy(base+DSIZE);

     m_dictionaryEnd = ( m_dictionaryEnd<DSIZE )? 0 : (m_dictionaryEnd-DSIZE) ;

     m_stringStart-=DSIZE;
     m_previousMatch-=DSIZE;
     m_blockStart-=DSIZE;

     for(unsigned i=0; i<HSIZE ;i++) m_head[i]=PosSub(m_head[i],HSIZE); // was DSIZE???

     for(unsigned i=0; i<DSIZE ;i++) m_prev[i]=PosSub(m_prev[i],DSIZE);
    }

  unsigned off=m_stringStart+m_lookahead;

  unsigned accepted = (unsigned)Min<ulen>(maxBlockSize-off,len) ;

  Range(base+off,accepted).copy(str);

  m_lookahead+=accepted;

  return accepted;
 }

unsigned Deflator::ComputeHash(const uint8 *str) const
 {
  unsigned s0=str[0];
  unsigned s1=str[1];
  unsigned s2=str[2];

  return ((s0<<10)^(s1<<5)^s2)&HMASK;
 }

unsigned Deflator::LongestMatch(unsigned &bestMatch) const
 {
  bestMatch=0;

  unsigned bestLength = Max<unsigned>(m_previousLength,MIN_MATCH-1) ;

  if( m_lookahead<=bestLength ) return 0;

  const uint8 *scan=m_byteBuffer.getPtr()+m_stringStart;
  const uint8 *scanEnd=scan+Min<unsigned>(MAX_MATCH,m_lookahead);

  unsigned limit=PosSub(m_stringStart,DSIZE-MAX_MATCH);

  unsigned current=m_head[ComputeHash(scan)];

  unsigned chainLength=MAX_CHAIN_LENGTH;

  if( m_previousLength>=GOOD_MATCH ) chainLength>>=2;

  while( current>limit && --chainLength>0 )
    {
     const uint8 *match=m_byteBuffer.getPtr()+current;

     if( scan[bestLength-1]==match[bestLength-1] && scan[bestLength]==match[bestLength] && scan[0]==match[0] && scan[1]==match[1] )
       {
        unsigned len=(unsigned)Dist(scan,Mismatch(scan+3,scanEnd,match+3));

        if( len>bestLength )
          {
           bestLength=len;
           bestMatch=current;

           if( len==Dist(scan,scanEnd) ) break;
          }
       }

     current=m_prev[current&DMASK];
    }

  return (bestMatch>0)? bestLength : 0 ;
 }

void Deflator::InsertString(unsigned start)
 {
  unsigned hash = ComputeHash(m_byteBuffer.getPtr()+start) ;

  m_prev[start&DMASK]=m_head[hash];
  m_head[hash]=uint16(start);
 }

void Deflator::ProcessBuffer()
 {
  if( !m_headerWritten )
    {
     m_headerWritten=true;
    }

  if( m_deflateLevel==0 )
    {
     m_stringStart+=m_lookahead;
     m_lookahead=0;
     m_blockLength=m_stringStart-m_blockStart;

     m_matchAvailable=false;

     return;
    }

  while( m_lookahead>m_minLookahead )
    {
     while( m_dictionaryEnd<m_stringStart && m_dictionaryEnd+3<=m_stringStart+m_lookahead ) InsertString(m_dictionaryEnd++);

     if( m_matchAvailable )
       {
        unsigned matchPosition=0,matchLength=0;

        bool usePreviousMatch;

        if( m_previousLength>=MAX_LAZYLENGTH )
          {
           usePreviousMatch = true;
          }
        else
          {
           matchLength=LongestMatch(matchPosition);

           usePreviousMatch=(matchLength==0);
          }

        if( usePreviousMatch )
          {
           MatchFound(m_stringStart-1-m_previousMatch,m_previousLength);

           m_stringStart += m_previousLength-1 ;
           m_lookahead -= m_previousLength-1 ;

           m_matchAvailable=false;
          }
        else
          {
           m_previousLength=matchLength;
           m_previousMatch=matchPosition;

           LiteralByte(m_byteBuffer[m_stringStart-1]);

           m_stringStart++;
           m_lookahead--;
          }
       }
     else
       {
        m_previousLength=0;
        m_previousLength=LongestMatch(m_previousMatch);

        if( m_previousLength )
          m_matchAvailable=true;
        else
          LiteralByte(m_byteBuffer[m_stringStart]);

        m_stringStart++;
        m_lookahead--;
       }
    }

  if( m_minLookahead==0 && m_matchAvailable )
    {
     LiteralByte(m_byteBuffer[m_stringStart-1]);

     m_matchAvailable = false;
    }
 }

void Deflator::put(const uint8 *ptr,ulen len)
 {
  ulen accepted=0;

  while( accepted<len )
    {
     unsigned newAccepted=FillWindow(ptr+accepted,len-accepted);

     ProcessBuffer();

     accepted+=newAccepted;
    }
 }

void Deflator::complete()
 {
  m_minLookahead=0;

  ProcessBuffer();

  EndBlock(true);

  writer.flushBitBuffer();

  Reset();
 }

void Deflator::isolatedFlush(bool hardFlush)
 {
  m_minLookahead=0;

  ProcessBuffer();

  m_minLookahead=MAX_MATCH;

  EndBlock(false);

  if( hardFlush ) EncodeBlock(false,STORED);
 }

void Deflator::LiteralByte(uint8 b)
 {
  if( m_matchBufferEnd==m_matchBuffer.getLen() ) EndBlock(false);

  m_matchBuffer[m_matchBufferEnd++].literalCode=b;

  m_literalCounts[b]++;

  m_blockLength++;
 }

void Deflator::MatchFound(unsigned distance,unsigned length)
 {
  if( m_matchBufferEnd==m_matchBuffer.getLen() ) EndBlock(false);

  static const unsigned lengthCodes[]=
   {
    257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268,
    269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272,
    273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274,
    275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276,
    277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277,
    278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278,
    279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279,
    280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280,
    281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281,
    282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282,
    283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283,
    284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284,
    284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285
   };

  static const unsigned lengthBases[]=
   {
    3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258
   };

  static const unsigned distanceBases[30]=
   {
    1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577
   };

  EncodedMatch &m=m_matchBuffer[m_matchBufferEnd++];

  unsigned lengthCode=lengthCodes[length-3];

  m.literalCode=lengthCode;
  m.literalExtra=length-lengthBases[lengthCode-257];

  auto r=Range(distanceBases);

  unsigned distanceCode=(unsigned)Algon::BinarySearch_greater(r,distance).len-1;

  m.distanceCode=distanceCode;
  m.distanceExtra=distance-distanceBases[distanceCode];

  m_literalCounts[lengthCode]++;
  m_distanceCounts[distanceCode]++;
  m_blockLength+=length;
 }

unsigned Deflator::CodeLengthEncode(const unsigned *beg,const unsigned *lim,const unsigned * &p,unsigned &extraBits,unsigned &extraBitsLength)
 {
  unsigned v=*p;

  if( (lim-p)>=3 )
    {
     const unsigned *oldp = p;

     if( v==0 && p[1]==0 && p[2]==0 )
       {
        for(p+=3; p<lim && *p==0 && p!=oldp+138 ;p++);

        unsigned repeat=(unsigned)(p-oldp);

        if( repeat<=10 )
          {
           extraBits=repeat-3;
           extraBitsLength=3;

           return 17;
          }
        else
          {
           extraBits=repeat-11;
           extraBitsLength=7;

           return 18;
          }
       }
     else if( p!=beg && v==p[-1] && v==p[1] && v==p[2] )
       {
        for(p+=3; p<lim && *p==v && p!=oldp+6 ;p++);

        unsigned repeat=(unsigned)(p-oldp);

        extraBits=repeat-3;
        extraBitsLength=2;

        return 16;
       }
    }

  p++;
  extraBits=0;
  extraBitsLength=0;

  return v;
 }

void Deflator::EncodeBlock(bool eof,unsigned blockType)
 {
  writer.putBits({eof,1});
  writer.putBits({blockType,2});

  if( blockType==STORED )
    {
     writer.flushBitBuffer();

     writer.put16(uint16(m_blockLength));
     writer.put16(~uint16(m_blockLength));
     writer.put(m_byteBuffer.getPtr()+m_blockStart,m_blockLength);
    }
  else
    {
     if( blockType==DYNAMIC )
       {
        BitLen literalCodeLengths[286];
        BitLen distanceCodeLengths[30];

        m_literalCounts[256]=1;

        HuffmanEncoder::Tree(literalCodeLengths,15,Range(m_literalCounts));

        m_dynamicLiteralEncoder.init(Range(literalCodeLengths));

        unsigned hlit=(unsigned)TrimNull(literalCodeLengths+257,literalCodeLengths+286);

        HuffmanEncoder::Tree(distanceCodeLengths,15,Range(m_distanceCounts));

        m_dynamicDistanceEncoder.init(Range(distanceCodeLengths));

        unsigned hdist=(unsigned)TrimNull(distanceCodeLengths+1,distanceCodeLengths+30);

        TempArray<BitLen,286+30> combinedLengths(hlit+257+hdist+1);

        Range(combinedLengths.getPtr(),hlit+257).copy(literalCodeLengths);

        Range(combinedLengths.getPtr()+hlit+257,hdist+1).copy(distanceCodeLengths);

        ulen codeLengthCodeCounts[19]={};
        BitLen codeLengthCodeLengths[19];

        const unsigned *beg=combinedLengths.getPtr();
        const unsigned *lim=beg+combinedLengths.getLen();

        for(const unsigned *p=beg; p<lim ;)
          {
           unsigned code=0, extraBits=0, extraBitsLength=0;

           code=CodeLengthEncode(beg,lim,p,extraBits,extraBitsLength);

           codeLengthCodeCounts[code]++;
          }

        HuffmanEncoder::Tree(codeLengthCodeLengths,7,Range(codeLengthCodeCounts));

        HuffmanEncoder codeLengthEncoder(Range(codeLengthCodeLengths));

        static const unsigned border[]= // Order of the bit length code lengths
         {
          16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
         };

        unsigned hclen=19;

        while( hclen>4 && codeLengthCodeLengths[border[hclen-1]]==0 ) hclen--;

        hclen-=4;

        writer.putBits({hlit,5});
        writer.putBits({hdist,5});
        writer.putBits({hclen,4});

        for(unsigned i=0; i<hclen+4 ;i++) writer.putBits({codeLengthCodeLengths[border[i]],3});

        for(const unsigned *p=beg; p<lim ;)
          {
           unsigned code=0, extraBits=0, extraBitsLength=0;

           code=CodeLengthEncode(beg,lim,p,extraBits,extraBitsLength);

           codeLengthEncoder.encode(writer,code);

           writer.putBits({extraBits,extraBitsLength});
          }
       }

     static const unsigned lengthExtraBits[]=
      {
       0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0
      };

     static const unsigned distanceExtraBits[]=
      {
       0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13
      };

     const HuffmanEncoder &literalEncoder = (blockType==STATIC)? m_staticLiteralEncoder : m_dynamicLiteralEncoder ;

     const HuffmanEncoder &distanceEncoder = (blockType==STATIC)? m_staticDistanceEncoder : m_dynamicDistanceEncoder ;

     for(unsigned i=0; i<m_matchBufferEnd ;i++)
       {
        unsigned literalCode=m_matchBuffer[i].literalCode;

        literalEncoder.encode(writer,literalCode);

        if( literalCode>=257 )
          {
           writer.putBits({m_matchBuffer[i].literalExtra,lengthExtraBits[literalCode-257]});

           unsigned distanceCode=m_matchBuffer[i].distanceCode;

           distanceEncoder.encode(writer,distanceCode);

           writer.putBits({m_matchBuffer[i].distanceExtra,distanceExtraBits[distanceCode]});
          }
       }

     literalEncoder.encode(writer,256); // end of block
    }
 }

void Deflator::EndBlock(bool eof)
 {
  if( m_blockLength==0 && !eof ) return;

  if( m_deflateLevel==0 )
    {
     EncodeBlock(eof,STORED);

     if( m_compressibleDeflateLevel>0 && ++m_detectCount==m_detectSkip )
       {
        m_deflateLevel=m_compressibleDeflateLevel;
        m_detectCount=1;
       }
    }
  else
    {
     ulen storedLen=8*((ulen)m_blockLength+4)+writer.extBits();

     writer.startCounting();

     EncodeBlock(eof,STATIC);

     ulen staticLen=writer.finishCounting();

     ulen dynamicLen;

     if( m_blockLength<128 && m_deflateLevel<8 )
       {
        dynamicLen=MaxULen;
       }
     else
       {
        writer.startCounting();

        EncodeBlock(eof,DYNAMIC);

        dynamicLen=writer.finishCounting();
       }

     if( storedLen<=staticLen && storedLen<=dynamicLen )
       {
        EncodeBlock(eof,STORED);

        if( m_compressibleDeflateLevel>0 )
          {
           if( m_detectSkip ) m_deflateLevel=MIN_DEFLATE_LEVEL;

           m_detectSkip = m_detectSkip? Min<unsigned>(2*m_detectSkip,128) : 1 ;
          }
       }
     else
       {
        if( staticLen<=dynamicLen )
          EncodeBlock(eof,STATIC);
        else
          EncodeBlock(eof,DYNAMIC);

        if( m_compressibleDeflateLevel>0 ) m_detectSkip=0;
       }
    }

  m_matchBufferEnd=0;
  m_blockStart+=m_blockLength;
  m_blockLength=0;

  Range(m_literalCounts).set_null();
  Range(m_distanceCounts).set_null();
 }

//----------------------------------------------------------------------------------------

/* class OutFile */

class OutFile : public Funchor_nocopy
 {
   BinaryFile outfile;

  public:

   explicit OutFile(StrLen file_name) : outfile(file_name) {}

   ~OutFile() {}

   void out(PtrLen<const uint8> data) { outfile.put(data); }

   OutFunc function_out() { return FunctionOf(this,&OutFile::out); }
 };

} // namespace Private_3037

using namespace Private_3037;

/* Testit<3037> */

template<>
const char *const Testit<3037>::Name="Test3037 Deflate";

template<>
bool Testit<3037>::Main()
 {
  FileToMem file("../../../HCore/files/test.txt");
  OutFile outfile("test3037.bin");

  Deflator deflate(outfile.function_out());

  deflate.put(Range(file));

  deflate.complete();

  return true;
 }

} // namespace App

