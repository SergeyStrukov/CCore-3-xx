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

class LowFirstBitReader : NoCopy
 {
   PtrLen<const uint8> inp;

   uint32 buffer = 0 ;
   unsigned bits = 0 ;

  private:

   bool next(uint8 &octet)
    {
     if( !inp ) return false;

     octet=*inp;

     ++inp;

     return true;
    }

  public:

   LowFirstBitReader() {}

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

   // byte queue

   void LazyPut(const uint8 *str,ulen len);

   void FinLazyPut();

   bool IsEmpty() const;

   ulen CurrentSize() const;

   void TransferTo(OutFunc out);

   const uint8 * Spy(ulen &len);

   void Skip(ulen len);

   void Unget(const uint8 *ptr,ulen len);
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

   HuffmanDecoder(PtrLen<BitLen> bitlens) { init(bitlens); }

   void init(PtrLen<BitLen> bitlens);

   unsigned Decode(UCode code,USym &value) const;

   bool Decode(LowFirstBitReader &reader,USym &value) const;
 };

UCode HuffmanDecoder::NormalizeCode(UCode code,unsigned codeBits)
 {
  return code<<(MaxCodeBits-codeBits);
 }

void HuffmanDecoder::init(PtrLen<BitLen> bitlens)
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

  if( bitlens.len==0 )
    {
     Printf(Exception,"HuffmanDecoder: null code");
    }

  m_maxCodeBits=MaxValue(bitlens);

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

  for(unsigned i=0; i<bitlens.len ;i++) blCount[bitlens.ptr[i]]++;

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
  m_codeToValue.extend_default(bitlens.len-blCount[0]);

  unsigned j=0;

  for(unsigned i=0; i<bitlens.len ;i++)
    {
     unsigned len=bitlens.ptr[i];

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

/* class WindowOut */

class WindowOut : NoCopy
 {
   static constexpr unsigned WindowLen = 1u<<15 ;

   OutFunc out;

   SimpleArray<uint8> buf;

   unsigned outpos = 0 ;
   unsigned addpos = 0 ;
   bool wrapped = false ;

  private:

   void output();

   void commit();

  public:

   explicit WindowOut(OutFunc out);

   ~WindowOut();

   void reset()
    {
     outpos=0;
     addpos=0;
     wrapped=false;
    }

   void flush();

   void put(uint8 octet);

   void put(const uint8 *ptr,ulen len);

   void put(unsigned length,unsigned distance);
 };

void WindowOut::output()
 {
  out(Range(buf.getPtr()+outpos,addpos-outpos));
 }

void WindowOut::commit()
 {
  if( addpos==WindowLen )
    {
     output();

     outpos=0;
     addpos=0;
     wrapped=true;
    }
 }

WindowOut::WindowOut(OutFunc out_)
 : out(out_),
   buf(WindowLen)
 {
 }

WindowOut::~WindowOut()
 {
 }

void WindowOut::flush()
 {
  output();

  outpos=addpos;
 }

void WindowOut::put(uint8 octet)
 {
  buf[addpos++]=octet;

  commit();
 }

void WindowOut::put(const uint8 *ptr,ulen len)
 {
  while( len )
    {
     ulen delta=Min<ulen>(len,WindowLen-addpos);

     Range(buf.getPtr()+addpos,delta).copy(ptr);

     addpos+=delta;
     ptr+=delta;
     len-=delta;

     commit();
    }
 }

void WindowOut::put(unsigned length,unsigned distance)
 {
  unsigned start;

  if( distance<=addpos )
    {
     start=addpos-distance;
    }
  else if( wrapped && distance<=WindowLen )
    {
     start=addpos+WindowLen-distance;
    }
  else
    {
     Printf(Exception,"");

     start=0;
    }

  if( start+length>WindowLen )
    {
     for(; start<WindowLen ;start++,length--) put(buf[start]);

     start=0;
    }

  if( start+length>addpos || addpos+length>=WindowLen )
    {
     while( length-- ) put(buf[start++]);
    }
  else
    {
     Range(buf.getPtr()+addpos,length).copy(buf.getPtr()+start);

     addpos+=length;
    }
 }

/* class Inflator */

class Inflator : NoCopy
 {
   WindowOut out;

   LowFirstBitReader m_reader;

   enum State
    {
     PRE_STREAM,
     WAIT_HEADER,
     DECODING_BODY,
     POST_STREAM,
     AFTER_END
    };

   State m_state;
   bool m_repeat, m_eof;
   uint8 m_blockType;
   uint16 m_storedLen;

   enum NextDecode
    {
     LITERAL,
     LENGTH_BITS,
     DISTANCE,
     DISTANCE_BITS
    };

   NextDecode m_nextDecode;

   unsigned m_literal, m_distance; // for LENGTH_BITS or DISTANCE_BITS

   HuffmanDecoder m_dynamicLiteralDecoder, m_dynamicDistanceDecoder;

  private:

   void ProcessInput(bool flush);

   void DecodeHeader();

   bool DecodeBody();

  public:

   Inflator(OutFunc out,bool repeat=false);

   ulen Put2(const uint8 *inString,ulen length,bool eof);
 };

void Inflator::ProcessInput(bool flush)
{
    while (true)
    {
        switch (m_state)
        {
        case PRE_STREAM:
            m_state = WAIT_HEADER;
            out.reset();

            break;
        case WAIT_HEADER:
            {
            // maximum number of bytes before actual compressed data starts

            const ulen MAX_HEADER_SIZE = RoundUpCount(3+5+5+4+19*7+286*15+19*15,8) ;

            if (m_reader.CurrentSize() < (flush ? 1u : MAX_HEADER_SIZE))
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
            if (m_reader.IsEmpty())
                return;
            break;
        case AFTER_END:

            //m_inQueue.TransferTo(out); TODO

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

            HuffmanDecoder codeLengthDecoder({codeLengths, 19});

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

            m_dynamicLiteralDecoder.init({codeLengths, hlit+257});

            if (hdist == 0 && codeLengths[hlit+257] == 0)
            {
                if (hlit != 0)  // a single zero distance code length means all literals
                 {
                  Printf(Exception,"");
                 }
            }
            else
             {
                m_dynamicDistanceDecoder.init({codeLengths+hlit+257, hdist+1});
             }
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
        while (!m_reader.IsEmpty() && !blockEnd)
        {
            ulen size;
            const uint8 *block = m_reader.Spy(size);
            size = Min<ulen>(m_storedLen, size);

            out.put(block, size);
            m_reader.Skip(size);
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

        const HuffmanDecoder& literalDecoder = (m_blockType==Static)? StaticCoder<HuffmanDecoder,StaticLiteralBitlens>::Get()
                                                                    : m_dynamicLiteralDecoder ;

        const HuffmanDecoder& distanceDecoder = (m_blockType==Static)? StaticCoder<HuffmanDecoder,StaticDistanceBitlens>::Get()
                                                                     : m_dynamicDistanceDecoder ;

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
                    out.put((uint8)m_literal);
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
                    out.put(m_literal, m_distance);
                }
            }
            break;
        }
    }
    if (blockEnd)
    {
        if (m_eof)
        {
           if( m_state!=PRE_STREAM ) out.flush();

            m_reader.SkipBits(m_reader.BitsBuffered()%8);
            if (m_reader.BitsBuffered())
            {
                // undo too much lookahead

                TempArray<uint8, 4> buffer(m_reader.BitsBuffered() / 8);

                for (unsigned int i=0; i<buffer.getLen(); i++)
                    buffer[i] = (uint8)m_reader.GetBits(8);

                m_reader.Unget(buffer.getPtr(), buffer.getLen());
            }
            m_state = POST_STREAM;
        }
        else
            m_state = WAIT_HEADER;
    }
    return blockEnd;
}

Inflator::Inflator(OutFunc out_,bool repeat)
 : out(out_),
   m_state(PRE_STREAM),
   m_repeat(repeat),
   m_eof(0),
   m_blockType(0xff),
   m_storedLen(0xffff),
   m_nextDecode(),
   m_literal(0),
   m_distance(0)
 {
 }

ulen Inflator::Put2(const uint8 *inString,ulen length,bool eof)
 {
  struct Putter
   {
     LowFirstBitReader &obj;

     Putter(LowFirstBitReader &obj_,const uint8 *inString,ulen length)
      : obj(obj_)
      {
       obj.LazyPut(inString,length);
      }

     ~Putter()
      {
       obj.FinLazyPut();
      }
   };

  Putter putter(m_reader, inString, length);

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

