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

   unsigned decode(UCode code,USym &value) const;

   bool decode(BitReader &reader,USym &value) const;
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

unsigned HuffmanDecoder::decode(UCode code,USym &value) const
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

bool HuffmanDecoder::decode(BitReader &reader,USym &value) const
 {
  reader.fillBuffer(m_maxCodeBits);

  unsigned codeBits=decode(reader.peekBuffer(),value);

  if( codeBits>reader.bitsBuffered() ) return false;

  reader.skipBits(codeBits);

  return true;
 }

/* class Inflator */

class Inflator : NoCopy
 {
   WindowOut out;

   BitReader reader;

   // params

   bool repeat;

   // data

   enum State
    {
     PreStream,
     WaitHeader,
     DecodingBody,
     PostStream,
     AfterEnd
    };

   State state;

   bool last_block;
   UCode block_type;

   ulen stored_len;

   enum DecodeState
    {
     Literal,
     LengthBits,
     Distance,
     DistanceBits
    };

   DecodeState decode_state;

   unsigned m_literal, m_distance;

   HuffmanDecoder m_dynamicLiteralDecoder, m_dynamicDistanceDecoder;

  private:

   void decodeCode();

   void decodeHeader();

   bool decodeBody();

   void processInput(bool eof);

  public:

   Inflator(OutFunc out,bool repeat=false);

   void put(const uint8 *ptr,ulen len) { put({ptr,len}); }

   void put(PtrLen<const uint8> data);

   void complete();
 };

void Inflator::decodeCode()
 {
  if( !reader.fillBuffer(5+5+4) )
    {
     Printf(Exception,"");
    }

  unsigned hlit=reader.getBits(5);
  unsigned hdist=reader.getBits(5);
  unsigned hclen=reader.getBits(4);

  BitLen codeLengths[286+32];

  Range(codeLengths,19).set_null();

  for(unsigned i=0; i<hclen+4 ;i++)
    {
     codeLengths[Order[i]]=reader.getBits(3);
    }

  bool result = false;
  unsigned k=0, count=0, repeater=0;

  HuffmanDecoder codeLengthDecoder({codeLengths,19});

  for(unsigned i=0; i<hlit+257+hdist+1 ;)
    {
     k = 0, count = 0, repeater = 0;

     result=codeLengthDecoder.decode(reader,k);

     if( !result )
       {
        Printf(Exception,"");
       }

     if( k<=15 )
       {
        count = 1;
        repeater = k;
       }
     else
       {
        switch (k)
          {
           case 16:
            {
             if( !reader.fillBuffer(2) )
               {
                Printf(Exception,"");
               }

             count=3+reader.getBits(2);

             if( i==0 )
               {
                Printf(Exception,"");
               }

             repeater=codeLengths[i-1];
            }
           break;

           case 17:
            {
             if( !reader.fillBuffer(3) )
               {
                Printf(Exception,"");
               }

             count=3+reader.getBits(3);
             repeater=0;
            }
           break;

           case 18:
            {
             if( !reader.fillBuffer(7) )
               {
                Printf(Exception,"");
               }

             count=11+reader.getBits(7);
             repeater=0;
            }
           break;
          }
       }

     if( i+count>hlit+257+hdist+1 )
       {
        Printf(Exception,"");
       }

     Range(codeLengths+i,count).set(repeater);

     i+=count;
    }

  m_dynamicLiteralDecoder.init({codeLengths,hlit+257});

  if( hdist==0 && codeLengths[hlit+257]==0 )
    {
     if( hlit!=0 )
       {
        Printf(Exception,"");
       }
    }
  else
    {
     m_dynamicDistanceDecoder.init({codeLengths+hlit+257,hdist+1});
    }
 }

void Inflator::decodeHeader()
 {
  reader.reqBuffer(3);

  last_block=( reader.getBits(1)!=0 );

  block_type=reader.getBits(2);

  switch( block_type )
    {
     case Stored :
      {
       reader.align8();

       reader.reqBuffer(32);

       uint16 len=(uint16)reader.getBits(16);
       uint16 nlen=(uint16)reader.getBits(16);

       stored_len=len;

       if( nlen!=(uint16)~len )
         {
          Printf(Exception,"CCore::Deflate::Inflator::decodeHeader() : incorrect stored length");
         }
      }
     break;

     case Static :
      {
       decode_state=Literal;
      }
     break;

     case Dynamic :
      {
       decodeCode();

       decode_state=Literal;
      }
     break;

     default:
      {
       Printf(Exception,"CCore::Deflate::Inflator::decodeHeader() : incorrect block type");
      }
    }
 }

bool Inflator::decodeBody()
 {
  bool blockEnd=false;

  if( block_type==Stored )
    {
     while( !reader.isEmpty() && !blockEnd )
       {
        reader.pumpTo(out,stored_len);

        if( stored_len==0 ) blockEnd=true;
       }
    }
  else
    {
     const HuffmanDecoder &literalDecoder = (block_type==Static)? StaticCoder<HuffmanDecoder,StaticLiteralBitlens>::Get()
                                                                 : m_dynamicLiteralDecoder ;

     const HuffmanDecoder &distanceDecoder = (block_type==Static)? StaticCoder<HuffmanDecoder,StaticDistanceBitlens>::Get()
                                                                  : m_dynamicDistanceDecoder ;

     switch( decode_state )
       {
        case Literal:

          for(;;)
            {
             if( !literalDecoder.decode(reader,m_literal) )
               {
                decode_state=Literal;

                break;
               }

             if( m_literal<256 )
               {
                out.put((uint8)m_literal);
               }
             else if( m_literal==256 )
               {
                blockEnd=true;

                break;
               }
             else
               {
                if( m_literal>285 )
                  {
                   Printf(Exception,"");
                  }

                unsigned int bits;

                case LengthBits :

                bits=LengthExtraBits[m_literal-257];

                if( !reader.fillBuffer(bits) )
                  {
                   decode_state=LengthBits;

                   break;
                  }

                m_literal=reader.getBits(bits)+LengthBases[m_literal-257];

                case Distance :

                if( !distanceDecoder.decode(reader,m_distance) )
                  {
                   decode_state=Distance;

                   break;
                  }

                case DistanceBits :

                if( m_distance>=DimOf(DistanceExtraBits) )
                  {
                   Printf(Exception,"");
                  }

                bits=DistanceExtraBits[m_distance];

                if( !reader.fillBuffer(bits) )
                  {
                   decode_state=DistanceBits;

                   break;
                  }

                if( m_distance>=DimOf(DistanceBases) )
                  {
                   Printf(Exception,"");
                  }

                m_distance=reader.getBits(bits)+DistanceBases[m_distance];

                out.put(m_distance,m_literal);
               }
            }
       }
    }

  return blockEnd;
 }

void Inflator::processInput(bool eof)
 {
  for(;;)
    {
     switch( state )
       {
        case PreStream :
         {
          out.reset();

          state=WaitHeader;
         }
        break;

        case WaitHeader :
         {
          if( !eof && !reader.canRead(MaxHeaderBitlen) ) return;

          decodeHeader();

          state=DecodingBody;
         }
        break;

        case DecodingBody :
         {
          if( !decodeBody() ) return;

          if( last_block )
            {
             out.flush();

             reader.align8();

             state=PostStream;
            }
          else
            {
             state=WaitHeader;
            }
         }
        break;

        case PostStream :
         {
          state = repeat? PreStream : AfterEnd ;
         }
        break;

        case AfterEnd :
         {
          reader.pumpTo(out);

          return;
         }
       }
    }
 }

Inflator::Inflator(OutFunc out_,bool repeat_)
 : out(out_),
   repeat(repeat_),
   state(PreStream)
 {
 }

void Inflator::put(PtrLen<const uint8> data)
 {
  reader.extend(data);

  ScopeGuard guard( [this] () { reader.bufferize(NoException); } );

  processInput(false);

  reader.bufferize(Exception);
 }

void Inflator::complete()
 {
  processInput(true);

  if( !( state==PreStream || state==AfterEnd ) )
    {
     Printf(Exception,"CCore::Deflate::Inflator::complete() : unexpected EOF");
    }
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
  // 1

  {
   FileToMem file("../../../HCore/files/test.txt");
   OutFile outfile("test3037.bin");

   Deflate::Param param;

   param.level=Deflate::MaxLevel;

   Deflator deflate(outfile.function_out(),param);

   deflate.put(Range(file));

   deflate.complete();
  }

  // 2

  {
   FileToMem file("test3037.bin");
   OutFile outfile("test3037.txt");

   Inflator inflate(outfile.function_out());

   inflate.put(Range(file));

   inflate.complete();
  }

  return true;
 }

} // namespace App

