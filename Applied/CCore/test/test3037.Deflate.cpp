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

/* Mismatch() */

template <class Ptr>
Ptr Mismatch(Ptr a,Ptr lim,Ptr b)
 {
  for(; a<lim ;++a,++b) if( *a!=*b ) return a;

  return lim;
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

  public:

   explicit LowFirstBitWriter(Function<void (const uint8 *,ulen)> out);

   void StartCounting();

   ulen FinishCounting();

   void PutBits(Code code);

   void Put16(uint16 value)
    {
     uint8 buf[2]={ uint8(value) , uint8(value>>8) };

     Put(buf,2);
    }

   void Put(const uint8 *bytes,ulen len)
    {
     out(bytes,len);
    }

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
           Put(m_outputBuffer,m_bytesBuffered);
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
        Put(m_outputBuffer,m_bytesBuffered);

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

     // maxbitlen>0 && counts.len>0 && counts.len <= 2^maxbitlen

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

  if( initial.len==1 )
    {
     Range(bitlens,counts.len).set_null();

     bitlens[initial->sym]=1;

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

/* class Deflator */

class Deflator : public LowFirstBitWriter
 {
  public:

   enum
    {
     MIN_DEFLATE_LEVEL     = 0,
     DEFAULT_DEFLATE_LEVEL = 6,
     MAX_DEFLATE_LEVEL     = 9
    };

   enum
    {
     MIN_LOG2_WINDOW_SIZE     = 9,
     DEFAULT_LOG2_WINDOW_SIZE = 15,
     MAX_LOG2_WINDOW_SIZE     = 15
    };

   Deflator(Function<void (const uint8 *,ulen)> out,
            int deflateLevel=DEFAULT_DEFLATE_LEVEL,
            int log2WindowSize=DEFAULT_LOG2_WINDOW_SIZE,
            bool detectUncompressible=true);

   ~Deflator();

   void SetDeflateLevel(int deflateLevel);

   int GetDeflateLevel() const { return m_deflateLevel; }

   int GetLog2WindowSize() const { return m_log2WindowSize; }

   ulen Put2(const uint8 *str,ulen len,int messageEnd,bool blocking);

   bool IsolatedFlush(bool hardFlush,bool blocking);

  protected:

   virtual void WritePrestreamHeader();

   virtual void ProcessUncompressedData(const uint8 *str,ulen len);

   virtual void WritePoststreamTail();

   enum { STORED = 0, STATIC = 1, DYNAMIC = 2 };

   enum { MIN_MATCH = 3, MAX_MATCH = 258 };

   void InitializeStaticEncoders();

   void Init(int deflateLevel,int log2WindowSize,bool detectUncompressible);

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

   struct EncodedMatch
    {
     unsigned literalCode : 9 ;
     unsigned literalExtra : 5 ;
     unsigned distanceCode : 5 ;
     unsigned distanceExtra : 13 ;
    };

   int m_deflateLevel, m_log2WindowSize, m_compressibleDeflateLevel;

   unsigned m_detectSkip, m_detectCount;

   unsigned DSIZE, DMASK, HSIZE, HMASK, GOOD_MATCH, MAX_LAZYLENGTH, MAX_CHAIN_LENGTH;

   bool m_headerWritten, m_matchAvailable;

   unsigned m_dictionaryEnd, m_stringStart, m_lookahead, m_minLookahead, m_previousMatch, m_previousLength;

   HuffmanEncoder m_staticLiteralEncoder, m_staticDistanceEncoder, m_dynamicLiteralEncoder, m_dynamicDistanceEncoder;

   SimpleArray<uint8> m_byteBuffer;
   SimpleArray<uint16> m_head, m_prev;

   unsigned m_literalCounts[286];
   unsigned m_distanceCounts[30];

   SimpleArray<EncodedMatch> m_matchBuffer;

   unsigned m_matchBufferEnd, m_blockStart, m_blockLength;
 };

void Deflator::WritePrestreamHeader()
 {
 }

void Deflator::ProcessUncompressedData(const uint8 *,ulen)
 {
 }

void Deflator::WritePoststreamTail()
 {
 }

Deflator::Deflator(Function<void (const uint8 *,ulen)> out,int deflateLevel,int log2WindowSize,bool detectUncompressible)
 : LowFirstBitWriter(out),
   m_deflateLevel(-1)
 {
  InitializeStaticEncoders();

  Init(deflateLevel,log2WindowSize,detectUncompressible);
 }

Deflator::~Deflator()
 {
 }

void Deflator::InitializeStaticEncoders()
 {
  BitLen codeLengths[288];

  // lit

  Range(codeLengths+0,codeLengths+144).set(8);
  Range(codeLengths+144,codeLengths+256).set(9);
  Range(codeLengths+256,codeLengths+280).set(7);
  Range(codeLengths+280,codeLengths+288).set(8);

  m_staticLiteralEncoder.Initialize({codeLengths,288});

  // dist

  Range(codeLengths+0,codeLengths+32).set(5);

  m_staticDistanceEncoder.Initialize({codeLengths,32});
 }

void Deflator::Init(int deflateLevel,int log2WindowSize,bool detectUncompressible)
 {
  if( !( MIN_LOG2_WINDOW_SIZE<=log2WindowSize && log2WindowSize<=MAX_LOG2_WINDOW_SIZE) )
    {
     Printf(Exception,"Deflator: #; is an invalid window size",log2WindowSize);
    }

  m_log2WindowSize = log2WindowSize ;
  DSIZE = 1 << m_log2WindowSize ;
  DMASK = DSIZE - 1 ;
  HSIZE = 1 << m_log2WindowSize ;
  HMASK = HSIZE - 1 ;

  m_byteBuffer=SimpleArray<uint8>(2*DSIZE);

  m_head=SimpleArray<uint16>(HSIZE);
  m_prev=SimpleArray<uint16>(DSIZE);

  m_matchBuffer=SimpleArray<EncodedMatch>(DSIZE/2);

  Reset(true);

  SetDeflateLevel(deflateLevel);

  m_compressibleDeflateLevel = detectUncompressible ? m_deflateLevel : 0 ;
 }

void Deflator::Reset(bool forceReset)
 {
  if( forceReset ) ClearBitBuffer();

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

void Deflator::SetDeflateLevel(int deflateLevel)
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
     WritePrestreamHeader();

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

ulen Deflator::Put2(const uint8 *str,ulen len,int messageEnd,bool blocking)
 {
  if( !blocking )
    {
     Printf(Exception,"Deflator : blocking input only");
    }

  ulen accepted=0;

  while( accepted<len )
    {
     unsigned newAccepted=FillWindow(str+accepted,len-accepted);

     ProcessBuffer();

     ProcessUncompressedData(str+accepted,newAccepted);

     accepted+=newAccepted;
    }

  if( messageEnd )
    {
     m_minLookahead=0;

     ProcessBuffer();

     EndBlock(true);

     FlushBitBuffer();

     WritePoststreamTail();

     Reset();
    }

  return 0;
 }

bool Deflator::IsolatedFlush(bool hardFlush,bool blocking)
 {
  if( !blocking )
    {
     Printf(Exception,"Deflator : blocking input only");
    }

  m_minLookahead=0;

  ProcessBuffer();

  m_minLookahead=MAX_MATCH;

  EndBlock(false);

  if( hardFlush ) EncodeBlock(false,STORED);

  return false;
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
 }

void Deflator::EncodeBlock(bool eof,unsigned blockType)
 {
  PutBits({eof,1});
  PutBits({blockType,2});

  if( blockType==STORED )
    {
     FlushBitBuffer();

     Put16(uint16(m_blockLength));
     Put16(~uint16(m_blockLength));
     Put(m_byteBuffer.getPtr()+m_blockStart,m_blockLength);
    }
  else
    {
     if( blockType==DYNAMIC )
       {
        BitLen literalCodeLengths[286];
        BitLen distanceCodeLengths[30];

        m_literalCounts[256]=1;

        HuffmanEncoder::Tree(literalCodeLengths,15,Range(m_literalCounts));

        m_dynamicLiteralEncoder.Initialize(Range(literalCodeLengths));

          unsigned hlit = (unsigned)(FindIfNot(RevIt(literalCodeLengths.end()), RevIt(literalCodeLengths.begin()+257), 0).base() - (literalCodeLengths.begin()+257));

        HuffmanEncoder::Tree(distanceCodeLengths,15,Range(m_distanceCounts));

        m_dynamicDistanceEncoder.Initialize(Range(distanceCodeLengths));

          unsigned int hdist = (unsigned int)(FindIfNot(RevIt(distanceCodeLengths.end()), RevIt(distanceCodeLengths.begin()+1), 0).base() - (distanceCodeLengths.begin()+1));

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

        PutBits({hlit,5});
        PutBits({hdist,5});
        PutBits({hclen,4});

        for(unsigned i=0; i<hclen+4 ;i++) PutBits({codeLengthCodeLengths[border[i]],3});

        for(const unsigned *p=beg; p<lim ;)
          {
           unsigned code=0, extraBits=0, extraBitsLength=0;

           code=CodeLengthEncode(beg,lim,p,extraBits,extraBitsLength);

           codeLengthEncoder.Encode(*this,code);

           PutBits({extraBits,extraBitsLength});
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

        literalEncoder.Encode(*this,literalCode);

        if( literalCode>=257 )
          {
           PutBits({m_matchBuffer[i].literalExtra,lengthExtraBits[literalCode-257]});

           unsigned distanceCode=m_matchBuffer[i].distanceCode;

           distanceEncoder.Encode(*this,distanceCode);

           PutBits({m_matchBuffer[i].distanceExtra,distanceExtraBits[distanceCode]});
          }
       }

     literalEncoder.Encode(*this,256); // end of block
    }
 }

void Deflator::EndBlock(bool eof)
 {
    if (m_blockLength == 0 && !eof)
        return;

    if (m_deflateLevel == 0)
    {
        EncodeBlock(eof, STORED);

        if (m_compressibleDeflateLevel > 0 && ++m_detectCount == m_detectSkip)
        {
            m_deflateLevel = m_compressibleDeflateLevel;
            m_detectCount = 1;
        }
    }
    else
    {
        unsigned long storedLen = 8*((unsigned long)m_blockLength+4) + RoundUpToMultipleOf(m_bitsBuffered+3, 8U)-m_bitsBuffered;

        StartCounting();
        EncodeBlock(eof, STATIC);
        unsigned long staticLen = FinishCounting();

        unsigned long dynamicLen;
        if (m_blockLength < 128 && m_deflateLevel < 8)
            dynamicLen = ULONG_MAX;
        else
        {
            StartCounting();
            EncodeBlock(eof, DYNAMIC);
            dynamicLen = FinishCounting();
        }

        if (storedLen <= staticLen && storedLen <= dynamicLen)
        {
            EncodeBlock(eof, STORED);

            if (m_compressibleDeflateLevel > 0)
            {
                if (m_detectSkip)
                    m_deflateLevel = 0;
                m_detectSkip = m_detectSkip ? STDMIN(2*m_detectSkip, 128U) : 1;
            }
        }
        else
        {
            if (staticLen <= dynamicLen)
                EncodeBlock(eof, STATIC);
            else
                EncodeBlock(eof, DYNAMIC);

            if (m_compressibleDeflateLevel > 0)
                m_detectSkip = 0;
        }
    }

    m_matchBufferEnd = 0;
    m_blockStart += m_blockLength;
    m_blockLength = 0;
    std::fill(m_literalCounts.begin(), m_literalCounts.end(), 0);
    std::fill(m_distanceCounts.begin(), m_distanceCounts.end(), 0);
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

