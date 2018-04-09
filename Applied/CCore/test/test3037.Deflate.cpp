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

#include <CCore/inc/Deflate.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BinarySearch.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/BinaryFile.h>

namespace App {

namespace Private_3037 {

using namespace Deflate;

/* BitReverse() */

inline uint32 BitSwap(uint32 value,uint32 hi,uint32 lo,unsigned shift)
 {
  return uint32( (value&hi)>>shift )|uint32( (value&lo)<<shift );
 }

inline uint32 BitReverse(uint32 value)
 {
  value=BitSwap(value,0xAAAAAAAAu,0x55555555u,1);
  value=BitSwap(value,0xCCCCCCCCu,0x33333333u,2);
  value=BitSwap(value,0xF0F0F0F0u,0x0F0F0F0Fu,4);

  return Quick::ByteSwap32(value);
 }

/* class LowFirstBitReader */

using InpFunc = Function<ulen (PtrLen<uint8>)> ;

class LowFirstBitReader : NoCopy
 {
   static constexpr unsigned BufLen = 256 ;

   InpFunc inp;

   uint8 inpbuf[BufLen];
   unsigned pos = 0 ;
   unsigned inplen = 0 ;

   uint32 buffer = 0 ;
   unsigned bits = 0 ;

  private:

   bool fill()
    {
     inplen=(unsigned)inp(Range(inpbuf));
     pos=0;

     return inplen>0;
    }

   bool next(uint8 &octet)
    {
     if( pos>=inplen && !fill() ) return false;

     octet=inpbuf[pos++];

     return true;
    }

  public:

   explicit LowFirstBitReader(InpFunc inp_) : inp(inp_) {}

   unsigned BitsBuffered() const { return bits; }

   uint32 PeekBuffer() const { return buffer; }

   bool FillBuffer(unsigned bitlen);

   UCode PeekBits(unsigned bitlen)
    {
     FillBuffer(bitlen);

     return buffer&((uint32(1)<<bitlen)-1);
    }

   void SkipBits(unsigned bitlen)
    {
     buffer>>=bitlen;
     bits-=bitlen;
    }

   UCode GetBits(unsigned bitlen)
    {
     UCode ret=PeekBits(bitlen);

     SkipBits(bitlen);

     return ret;
    }
 };

bool LowFirstBitReader::FillBuffer(unsigned bitlen)
 {
  while( bits<bitlen )
    {
     uint8 octet;

     if( !next(octet) ) return false;

     buffer|=uint32(octet)<<bits;

     bits+=8;
    }

  return true;
 }

/* class HuffmanDecoder */

class HuffmanDecoder
 {
   static constexpr unsigned MaxCodeBits = Meta::UIntBits<UCode> ;

   struct CodeInfo
    {
     UCode code;
     unsigned len;
     USym value;

     CodeInfo(UCode code_=0,unsigned len_=0,USym value_=0) noexcept : code(code_),len(len_),value(value_) {}

     bool operator < (const CodeInfo &obj) const { return code<obj.code; }
    };

   struct CacheEntry
    {
     unsigned type;

     union
      {
       USym value;
       const CodeInfo *begin;
      };

     union
      {
       unsigned len;
       const CodeInfo *end;
      };
    };

   unsigned m_maxCodeBits = 0 , m_cacheBits = 0 , m_cacheMask = 0 , m_normalizedCacheMask = 0 ;

   DynArray<CodeInfo> m_codeToValue;

   mutable DynArray<CacheEntry> m_cache;

  private:

   static const CodeInfo & Find(const CodeInfo *beg,const CodeInfo *lim,UCode ncode)
    {
     return Find(Range(beg,lim),ncode);
    }

   static const CodeInfo & Find(PtrLen<const CodeInfo> r,UCode ncode)
    {
     auto prefix=Algon::BinarySearch_if(r, [ncode] (const CodeInfo &obj) { return obj.code>ncode; } );

     return prefix.back(1);
    }

   static UCode NormalizeCode(UCode code,unsigned codeBits);

   void FillCacheEntry(CacheEntry &entry,UCode normalizedCode) const;

  public:

   HuffmanDecoder() {}

   HuffmanDecoder(const unsigned *codeBitLengths,unsigned nCodes) { Initialize(codeBitLengths,nCodes); }

   void Initialize(const unsigned *codeBitLengths,unsigned nCodes);

   unsigned Decode(UCode code,USym &value) const;

   bool Decode(LowFirstBitReader &reader,USym &value) const;
 };

UCode HuffmanDecoder::NormalizeCode(UCode code,unsigned codeBits)
 {
  return code<<(MaxCodeBits-codeBits);
 }

void HuffmanDecoder::Initialize(const unsigned *codeBits,unsigned nCodes)
 {
  // the Huffman codes are represented in 3 ways in this code:
  //
  // 1. most significant code bit (i.e. top of code tree) in the least significant bit position
  // 2. most significant code bit (i.e. top of code tree) in the most significant bit position
  // 3. most significant code bit (i.e. top of code tree) in n-th least significant bit position,
  //    where n is the maximum code length for this code tree
  //
  // (1) is the way the codes come in from the deflate stream
  // (2) is used to sort codes so they can be binary searched
  // (3) is used in this function to compute codes from code lengths
  //
  // a code in representation (2) is called "normalized" here
  // The BitReverse() function is used to convert between (1) and (2)
  // The NormalizeCode() function is used to convert from (3) to (2)

  if( nCodes==0 )
    {
     Printf(Exception,"HuffmanDecoder: null code");
    }

  m_maxCodeBits=MaxValue(Range(codeBits,nCodes));

  if( m_maxCodeBits>MaxCodeBits || m_maxCodeBits>=Meta::UIntBits<ulen> )
    {
     Printf(Exception,"HuffmanDecoder: code length exceeds maximum");
    }

  if( m_maxCodeBits==0 )
    {
     Printf(Exception,"HuffmanDecoder: null code");
    }

  // count number of codes of each length

  TempArray<unsigned,MaxBitLens+1> blCount(m_maxCodeBits+1);

  Range(blCount).set_null();

  for(unsigned i=0; i<nCodes ;i++) blCount[codeBits[i]]++;

  // compute the starting code of each length

  UCode code=0;

  TempArray<UCode,MaxBitLens+1> nextCode(m_maxCodeBits+1);

  nextCode[1]=0;

  for(unsigned i=2; i<=m_maxCodeBits; i++)
    {
     auto t=blCount[i-1];

     if( t>MaxUInt<UCode> || UIntAdd(code,(UCode)t) || UIntAdd(code,code) )
       {
        Printf(Exception,"HuffmanDecoder: code overflow");
       }

     nextCode[i]=code;
    }

  // MaxCodeBits is 32, m_maxCodeBits may be smaller.

  const uint64 shiftedMaxCode=(uint64(1)<<m_maxCodeBits);

  if( code>shiftedMaxCode-blCount[m_maxCodeBits] )
    {
     Printf(Exception,"HuffmanDecoder: code overflow");
    }
  else if( m_maxCodeBits!=1 && code<shiftedMaxCode-blCount[m_maxCodeBits] )
    {
     Printf(Exception,"HuffmanDecoder: code incomplete");
    }

  // compute a vector of <code, length, value> triples sorted by code

  m_codeToValue.erase();
  m_codeToValue.extend_default(nCodes-blCount[0]);

  unsigned j=0;

  for(unsigned i=0; i<nCodes ;i++)
    {
     unsigned len=codeBits[i];

     if( len!=0 )
       {
        code=NormalizeCode(nextCode[len]++,len);

        m_codeToValue[j].code=code;
        m_codeToValue[j].len=len;
        m_codeToValue[j].value=i;

        j++;
       }
    }

  Sort(Range(m_codeToValue));

  // initialize the decoding cache

  m_cacheBits=Min<unsigned>(9,m_maxCodeBits);

  m_cacheMask=(1<<m_cacheBits)-1;

  m_normalizedCacheMask=NormalizeCode(m_cacheMask,m_cacheBits);

  const ulen shiftedCache=(ulen(1)<<m_cacheBits);

  if( m_cache.getLen()!=shiftedCache )
    {
     m_cache.erase();
     m_cache.extend_raw(shiftedCache);
    }

  for(auto &m : m_cache ) m.type=0;
 }

void HuffmanDecoder::FillCacheEntry(CacheEntry &entry,UCode normalizedCode) const
 {
  normalizedCode&=m_normalizedCacheMask;

  const CodeInfo &codeInfo=Find(Range(m_codeToValue),normalizedCode);

  if( codeInfo.len<=m_cacheBits )
    {
     entry.type=1;
     entry.value=codeInfo.value;
     entry.len=codeInfo.len;
    }
  else
    {
     entry.begin=&codeInfo;

     const CodeInfo *last=&Find(Range(m_codeToValue),normalizedCode + ~m_normalizedCacheMask);

     if( codeInfo.len==last->len )
       {
        entry.type=2;
        entry.len=codeInfo.len;
       }
     else
       {
        entry.type=3;
        entry.end=last+1;
       }
    }
 }

unsigned HuffmanDecoder::Decode(UCode code,USym &value) const
 {
  CacheEntry &entry=m_cache[code&m_cacheMask];

  UCode normalizedCode=0;

  if( entry.type!=1 ) normalizedCode=BitReverse(code);

  if( entry.type==0 ) FillCacheEntry(entry,normalizedCode);

  if( entry.type==1 )
    {
     value=entry.value;

     return entry.len;
    }
  else
    {
     const CodeInfo &codeInfo = (entry.type==2)
                                ? entry.begin[(normalizedCode<<m_cacheBits)>>(MaxCodeBits-(entry.len-m_cacheBits))]
                                : Find(entry.begin,entry.end,normalizedCode) ;

     value=codeInfo.value;

     return codeInfo.len;
    }
 }

bool HuffmanDecoder::Decode(LowFirstBitReader &reader,USym &value) const
 {
  reader.FillBuffer(m_maxCodeBits);

  unsigned codeBits=Decode(reader.PeekBuffer(),value);

  if( codeBits>reader.BitsBuffered() ) return false;

  reader.SkipBits(codeBits);

  return true;
 }

#if 0

/* class Inflator */

class Inflator : NoCopy
 {
   OutFunc out;

   class ByteQueue : NoCopy
    {
     public:

      ByteQueue();

      ~ByteQueue();

      void LazyPut(const uint8 *str,ulen len);

      void FinLazyPut();

      bool IsEmpty() const;

      ulen CurrentSize() const;

      void TransferTo(OutFunc out);

      const uint8 * Spy(ulen &len);

      void Skip(ulen len);

      void Unget(const uint8 *ptr,ulen len);

      InpFunc function_get();
    };

   ByteQueue m_inQueue;

   enum State {PRE_STREAM, WAIT_HEADER, DECODING_BODY, POST_STREAM, AFTER_END};

   State m_state;
   bool m_repeat, m_eof, m_wrappedAround;
   uint8 m_blockType;
   uint16 m_storedLen;

   enum NextDecode {LITERAL, LENGTH_BITS, DISTANCE, DISTANCE_BITS};

   NextDecode m_nextDecode;

   unsigned m_literal, m_distance; // for LENGTH_BITS or DISTANCE_BITS

   HuffmanDecoder m_dynamicLiteralDecoder, m_dynamicDistanceDecoder;
   LowFirstBitReader m_reader;
   SimpleArray<uint8> m_window;

   ulen m_current, m_lastFlush;

   static HuffmanDecoder FixedLiteralDecoder;
   static HuffmanDecoder FixedDistanceDecoder;

   static bool FixedLiteralDecoderInit;
   static bool FixedDistanceDecoderInit;

  private:

   static const HuffmanDecoder & GetFixedLiteralDecoder();
   static const HuffmanDecoder & GetFixedDistanceDecoder();

   void ProcessDecompressedData(const uint8 *string,ulen length) { out(Range(string,length));}


   void ProcessInput(bool flush);

   void DecodeHeader();

   bool DecodeBody();

   void FlushOutput();

   void OutputByte(uint8 b);

   void OutputString(const uint8 *string,ulen length);

   void OutputPast(unsigned length,unsigned distance);

   const HuffmanDecoder & GetLiteralDecoder() const;
   const HuffmanDecoder & GetDistanceDecoder() const;

  public:

   Inflator(OutFunc out,bool repeat=false);

   ulen Put2(const uint8 *inString,ulen length,bool eof);

   unsigned GetLog2WindowSize() const { return 15; }
 };

HuffmanDecoder Inflator::FixedLiteralDecoder;

HuffmanDecoder Inflator::FixedDistanceDecoder;

bool Inflator::FixedLiteralDecoderInit=true;

bool Inflator::FixedDistanceDecoderInit=true;

const HuffmanDecoder & Inflator::GetFixedLiteralDecoder()
 {
  if( Change(FixedLiteralDecoderInit,false) )
    {
     unsigned bitlens[288];

     Range(bitlens,bitlens+144).set(8);
     Range(bitlens+144,bitlens+256).set(9);
     Range(bitlens+256,bitlens+280).set(7);
     Range(bitlens+280,bitlens+288).set(8);

     FixedLiteralDecoder.Initialize(bitlens,288);
    }

  return FixedLiteralDecoder;
 }

const HuffmanDecoder & Inflator::GetFixedDistanceDecoder()
 {
  if( Change(FixedDistanceDecoderInit,false) )
    {
     unsigned bitlens[32];

     Range(bitlens).set(5);

     FixedDistanceDecoder.Initialize(bitlens,32);
    }

  return FixedDistanceDecoder;
 }

void Inflator::ProcessInput(bool flush)
{
    while (true)
    {
        switch (m_state)
        {
        case PRE_STREAM:
            m_state = WAIT_HEADER;
            m_wrappedAround = false;
            m_current = 0;
            m_lastFlush = 0;

            m_window=SimpleArray<uint8>( ulen(1)<<GetLog2WindowSize() );

            break;
        case WAIT_HEADER:
            {
            // maximum number of bytes before actual compressed data starts

            const ulen MAX_HEADER_SIZE = RoundUpCount(3+5+5+4+19*7+286*15+19*15,8) ;

            if (m_inQueue.CurrentSize() < (flush ? 1u : MAX_HEADER_SIZE))
                return;

            DecodeHeader();

            break;
            }
        case DECODING_BODY:
            if (!DecodeBody())
                return;
            break;
        case POST_STREAM:
            m_state = m_repeat ? PRE_STREAM : AFTER_END;
            if (m_inQueue.IsEmpty())
                return;
            break;
        case AFTER_END:

            m_inQueue.TransferTo(out);

            return;
        }
    }
}

void Inflator::DecodeHeader()
{
    if (!m_reader.FillBuffer(3))
      {
       Printf(Exception,"");
      }

    m_eof = m_reader.GetBits(1) != 0;
    m_blockType = (byte)m_reader.GetBits(2);

    switch (m_blockType)
    {
    case 0: // stored
        {
        m_reader.SkipBits(m_reader.BitsBuffered() % 8);

        if (!m_reader.FillBuffer(32))
          {
           Printf(Exception,"");
          }
        m_storedLen = (uint16)m_reader.GetBits(16);

        uint16 nlen = (uint16)m_reader.GetBits(16);

        if (nlen != (uint16)~m_storedLen)
          {
           Printf(Exception,"");
          }
        break;
        }
    case 1: // fixed codes
        m_nextDecode = LITERAL;
        break;
    case 2: // dynamic codes
        {
        if (!m_reader.FillBuffer(5+5+4))
          {
           Printf(Exception,"");
          }

        unsigned int hlit = m_reader.GetBits(5);
        unsigned int hdist = m_reader.GetBits(5);
        unsigned int hclen = m_reader.GetBits(4);

        unsigned int codeLengths[286+32];

        static const unsigned int border[19] = {    // Order of the bit length code lengths
            16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};

        Range(codeLengths,19).set_null();

        for (unsigned i=0; i<hclen+4; ++i)
        {
            codeLengths[border[i]] = m_reader.GetBits(3);
        }

        {
            bool result = false;
            unsigned int k=0, count=0, repeater=0;
            HuffmanDecoder codeLengthDecoder(codeLengths, 19);
            for (unsigned i=0; i < hlit+257+hdist+1; )
            {
                k = 0, count = 0, repeater = 0;
                result = codeLengthDecoder.Decode(m_reader, k);
                if (!result)
                 {
                  Printf(Exception,"");
                 }
                if (k <= 15)
                {
                    count = 1;
                    repeater = k;
                }
                else switch (k)
                {
                case 16:
                    if (!m_reader.FillBuffer(2))
                     {
                      Printf(Exception,"");
                     }
                    count = 3 + m_reader.GetBits(2);
                    if (i == 0)
                     {
                      Printf(Exception,"");
                     }
                    repeater = codeLengths[i-1];
                    break;
                case 17:
                    if (!m_reader.FillBuffer(3))
                     {
                      Printf(Exception,"");
                     }
                    count = 3 + m_reader.GetBits(3);
                    repeater = 0;
                    break;
                case 18:
                    if (!m_reader.FillBuffer(7))
                     {
                      Printf(Exception,"");
                     }
                    count = 11 + m_reader.GetBits(7);
                    repeater = 0;
                    break;
                }
                if (i + count > hlit+257+hdist+1)
                 {
                  Printf(Exception,"");
                 }

                Range(codeLengths + i, count).set(repeater);

                i += count;
            }
            m_dynamicLiteralDecoder.Initialize(codeLengths, hlit+257);
            if (hdist == 0 && codeLengths[hlit+257] == 0)
            {
                if (hlit != 0)  // a single zero distance code length means all literals
                 {
                  Printf(Exception,"");
                 }
            }
            else
                m_dynamicDistanceDecoder.Initialize(codeLengths+hlit+257, hdist+1);
            m_nextDecode = LITERAL;
        }
        break;
        }
    default:
     {
      Printf(Exception,"");
     }
    }
    m_state = DECODING_BODY;
}

bool Inflator::DecodeBody()
{
    bool blockEnd = false;
    switch (m_blockType)
    {
    case 0: // stored
        while (!m_inQueue.IsEmpty() && !blockEnd)
        {
            ulen size;
            const uint8 *block = m_inQueue.Spy(size);
            size = Min<ulen>(m_storedLen, size);

            OutputString(block, size);
            m_inQueue.Skip(size);
            m_storedLen = m_storedLen - (uint16)size;
            if (m_storedLen == 0)
                blockEnd = true;
        }
        break;
    case 1: // fixed codes
    case 2: // dynamic codes
        static const unsigned int lengthStarts[] = {
            3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
            35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258};
        static const unsigned int lengthExtraBits[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
            3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
        static const unsigned int distanceStarts[] = {
            1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
            257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,
            8193, 12289, 16385, 24577};
        static const unsigned int distanceExtraBits[] = {
            0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
            7, 7, 8, 8, 9, 9, 10, 10, 11, 11,
            12, 12, 13, 13};

        const HuffmanDecoder& literalDecoder = GetLiteralDecoder();
        const HuffmanDecoder& distanceDecoder = GetDistanceDecoder();

        switch (m_nextDecode)
        {
        case LITERAL:
            while (true)
            {
                if (!literalDecoder.Decode(m_reader, m_literal))
                {
                    m_nextDecode = LITERAL;
                    break;
                }
                if (m_literal < 256)
                    OutputByte((uint8)m_literal);
                else if (m_literal == 256)  // end of block
                {
                    blockEnd = true;
                    break;
                }
                else
                {
                    if (m_literal > 285)
                     {
                      Printf(Exception,"");
                     }
                    unsigned int bits;
        case LENGTH_BITS:
                    bits = lengthExtraBits[m_literal-257];
                    if (!m_reader.FillBuffer(bits))
                    {
                        m_nextDecode = LENGTH_BITS;
                        break;
                    }
                    m_literal = m_reader.GetBits(bits) + lengthStarts[m_literal-257];
        case DISTANCE:
                    if (!distanceDecoder.Decode(m_reader, m_distance))
                    {
                        m_nextDecode = DISTANCE;
                        break;
                    }
        case DISTANCE_BITS:
                    if (m_distance >= DimOf(distanceExtraBits))
                     {
                      Printf(Exception,"");
                     }
                    bits = distanceExtraBits[m_distance];
                    if (!m_reader.FillBuffer(bits))
                    {
                        m_nextDecode = DISTANCE_BITS;
                        break;
                    }
                    if (m_distance >= DimOf(distanceStarts))
                     {
                      Printf(Exception,"");
                     }
                    m_distance = m_reader.GetBits(bits) + distanceStarts[m_distance];
                    OutputPast(m_literal, m_distance);
                }
            }
            break;
        }
    }
    if (blockEnd)
    {
        if (m_eof)
        {
            FlushOutput();
            m_reader.SkipBits(m_reader.BitsBuffered()%8);
            if (m_reader.BitsBuffered())
            {
                // undo too much lookahead

                TempArray<uint8, 4> buffer(m_reader.BitsBuffered() / 8);

                for (unsigned int i=0; i<buffer.getLen(); i++)
                    buffer[i] = (uint8)m_reader.GetBits(8);

                m_inQueue.Unget(buffer.getPtr(), buffer.getLen());
            }
            m_state = POST_STREAM;
        }
        else
            m_state = WAIT_HEADER;
    }
    return blockEnd;
}

void Inflator::FlushOutput()
{
    if (m_state != PRE_STREAM)
    {
        ProcessDecompressedData(m_window.getPtr() + m_lastFlush, m_current - m_lastFlush);
        m_lastFlush = m_current;
    }
}

void Inflator::OutputByte(uint8 b)
{
    m_window[m_current++] = b;

    if (m_current == m_window.getLen())
    {
        ProcessDecompressedData(m_window.getPtr() + m_lastFlush, m_window.getLen() - m_lastFlush);

        m_lastFlush = 0;
        m_current = 0;
        m_wrappedAround = true;
    }
}

void Inflator::OutputString(const uint8 *string, ulen length)
{
    while (length)
    {
        ulen len = Min(length, m_window.getLen() - m_current);

        Range(m_window.getPtr()+m_current,len).copy(string);

        m_current += len;

        if (m_current == m_window.getLen() )
        {
            ProcessDecompressedData(m_window.getPtr() + m_lastFlush, m_window.getLen() - m_lastFlush);
            m_lastFlush = 0;
            m_current = 0;
            m_wrappedAround = true;
        }

        string += len;
        length -= len;
    }
}

void Inflator::OutputPast(unsigned length,unsigned distance)
{
    ulen start;

    if (distance <= m_current)
        start = m_current - distance;
    else if (m_wrappedAround && distance <= m_window.getLen())
        start = m_current + m_window.getLen() - distance;
    else
      {
       Printf(Exception,"");

       start=0;
      }

    if (start + length > m_window.getLen() )
    {
        for (; start < m_window.getLen(); start++, length--)
            OutputByte(m_window[start]);
        start = 0;
    }

    if (start + length > m_current || m_current + length >= m_window.getLen())
    {
        while (length--)
            OutputByte(m_window[start++]);
    }
    else
    {
      Range(m_window.getPtr() + m_current,length).copy(m_window.getPtr() + start);

        m_current += length;
    }
}

const HuffmanDecoder & Inflator::GetLiteralDecoder() const
 {
  return (m_blockType==1)? GetFixedLiteralDecoder() : m_dynamicLiteralDecoder ;
 }

const HuffmanDecoder & Inflator::GetDistanceDecoder() const
 {
  return (m_blockType==1)? GetFixedDistanceDecoder() : m_dynamicDistanceDecoder ;
 }

Inflator::Inflator(OutFunc out_,bool repeat)
 : out(out_),
   m_state(PRE_STREAM),
   m_repeat(repeat),
   m_eof(0),
   m_wrappedAround(0),
   m_blockType(0xff),
   m_storedLen(0xffff),
   m_nextDecode(),
   m_literal(0),
   m_distance(0),
   m_reader(m_inQueue.function_get()),
   m_current(0),
   m_lastFlush(0)
 {
 }

ulen Inflator::Put2(const uint8 *inString,ulen length,bool eof)
 {
  struct Putter
   {
     ByteQueue &obj;

     Putter(ByteQueue &obj_,const uint8 *inString,ulen length)
      : obj(obj_)
      {
       obj.LazyPut(inString,length);
      }

     ~Putter()
      {
       obj.FinLazyPut();
      }
   };

  Putter putter(m_inQueue, inString, length);

  ProcessInput(eof);

  if( eof )
    {
        if (!(m_state == PRE_STREAM || m_state == AFTER_END))
         {
          Printf(Exception,"");
         }
    }

  return 0;
 }

#endif

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

  Deflate::Param param;

  param.level=Deflate::MaxLevel;

  Deflator deflate(outfile.function_out(),param);

  deflate.put(Range(file));

  deflate.complete();

  return true;
 }

} // namespace App

