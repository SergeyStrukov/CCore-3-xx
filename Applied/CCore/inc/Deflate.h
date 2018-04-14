/* Deflate.h */
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

#ifndef CCore_inc_Deflate_h
#define CCore_inc_Deflate_h

#include <CCore/inc/Array.h>

namespace CCore {
namespace Deflate {

/* enum Level */

enum Level
 {
  MinLevel         = 0, // store only

  DefaultLevel     = 6,
  EverdynamicLevel = 8,

  MaxLevel         = 9  // maximum compression
 };

/* enum Log2WindowLen */

enum Log2WindowLen
 {
  MinLog2WindowLen     = 9,

  DefaultLog2WindowLen = 15,

  MaxLog2WindowLen     = 15
 };

/* type OutFunc */

using OutFunc = Function<void (PtrLen<const uint8>)> ;

/* struct Param */

struct Param
 {
  Level level = DefaultLevel ;
  Log2WindowLen log2_window_len = DefaultLog2WindowLen ;
  bool detect_uncompressible = true ;

  Param() {}
 };

//----------------------------------------------------------------------------------------

/* consts */

inline constexpr ulen MaxBitLens = 15 ;

inline constexpr ulen MaxSyms = 286 ;

/* types */

using UCode = uint32 ;

using USym  = uint32 ;

using BitLen = unsigned ;

/* consts */

inline constexpr BitLen MaxCodeBits = Meta::UIntBits<UCode> ;

enum BlockType : UCode
 {
  Stored  = 0,
  Static  = 1,
  Dynamic = 2
 };

/* tables */

extern const USym LengthCodes[256];

extern const unsigned LengthBases[29];

extern const unsigned DistanceBases[30];

extern const unsigned Order[19];

extern const unsigned LengthExtraBits[29];

extern const unsigned DistanceExtraBits[30];

/* functions */

BitLen MaxValue(PtrLen<const BitLen> bitlens);

/* classes */

struct Code;

class BitWriter;

class HuffmanEncoder;

struct StaticLiteralBitlens;

struct StaticDistanceBitlens;

template <class Coder,class Bitlens> class StaticCoder;

class SymWriter;

class Deflator;

/* struct Code */

struct Code
 {
  UCode code;
  BitLen bitlen;
 };

/* class BitWriter */

class BitWriter : NoCopy
 {
   static constexpr unsigned BufLen = 256 ;

   OutFunc out;

   bool count_mode = false ;
   unsigned bit_count = 0 ;

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

   unsigned finishCounting();

   unsigned extBits() const { return RoundUp<unsigned>(bits+3,8)-bits; }
 };

/* class HuffmanEncoder */

class HuffmanEncoder : NoCopy
 {
   SimpleArray<Code> table;

  public:

   HuffmanEncoder() noexcept {}

   explicit HuffmanEncoder(PtrLen<const BitLen> bitlens) { init(bitlens); }

   ~HuffmanEncoder() {}

   void init(PtrLen<const BitLen> bitlens);

   static void Tree(BitLen bitlens[ /* counts.len */ ],BitLen maxbitlen,PtrLen<const ulen> counts);

     // maxbitlen > 0 && counts.len > 0 && counts.len <= 2^maxbitlen && maxbitlen < Meta::UIntBits<unsigned> - 1

   void encode(BitWriter &writer,USym sym) const { writer.putBits(table[sym]); }
 };

/* struct StaticLiteralBitlens */

struct StaticLiteralBitlens
 {
  BitLen bitlens[288];

  StaticLiteralBitlens();
 };

/* struct StaticDistanceBitlens */

struct StaticDistanceBitlens
 {
  BitLen bitlens[32];

  StaticDistanceBitlens();
 };

/* class StaticCoder<Coder,Bitlens> */

template <class Coder,class Bitlens>
class StaticCoder
 {
   static Coder Object;
   static bool Init;

  public:

   static const Coder & Get()
    {
     if( Init )
       {
        Bitlens temp;

        Object.init(Range(temp.bitlens));

        Init=false;
       }

     return Object;
    }
 };

template <class Coder,class Bitlens>
Coder StaticCoder<Coder,Bitlens>::Object;

template <class Coder,class Bitlens>
bool StaticCoder<Coder,Bitlens>::Init=true;

/* class SymWriter */

class SymWriter : NoCopy
 {
   Level level;
   Level compressible_level;

   BitWriter writer;

   struct EncodedMatch
    {
     USym literal_code : 9 ;
     UCode literal_extra : 5 ;

     USym distance_code : 5 ;
     UCode distance_extra : 13 ;
    };

   SimpleArray<EncodedMatch> buf;
   unsigned pos;

   unsigned detect_skip;
   unsigned detect_count;

   // huffman

   ulen literal_counts[286];
   ulen distance_counts[30];

   HuffmanEncoder dynamic_literal_encoder;
   HuffmanEncoder dynamic_distance_encoder;

  private:

   struct CodeLenEncoder;

   void encodeCode(PtrLen<const BitLen> combined,unsigned hlit,unsigned hdist);

   void encodeBlock(bool eof,BlockType block_type,PtrLen<const uint8> block);

  public:

   explicit SymWriter(OutFunc out);

   ~SymWriter();

   void init(Level level,bool detect_uncompressible,unsigned buflen);

   void reset();

   Level getLevel() const { return level; }

   bool testFull(PtrLen<const uint8> block);

   void put(uint8 octet);

   void put(unsigned distance,unsigned length); // distance in [1,2^15] , length in [3,258]

   void endBlock(bool eof,PtrLen<const uint8> block);
 };

/* class Deflator */

class Deflator : NoCopy
 {
   SymWriter sym;

   // params

   Log2WindowLen log2_window_len;

   unsigned wind_len, wind_mask, hash_len, hash_mask;
   unsigned cap_data_len;
   unsigned min_lazy_len;
   unsigned good_match, max_chain_len;

   // data

   SimpleArray<uint8> buf;

   struct Frame
    {
     unsigned pos;
     unsigned len;

     unsigned getLim() const { return pos+len; }

     void null()
      {
       pos=0;
       len=0;
      }

     void finish()
      {
       pos+=len;
       len=0;
      }

     void operator ++ ()
      {
       pos++;
       len--;
      }

     void operator += (unsigned delta)
      {
       pos+=delta;
       len-=delta;
      }
    };

   Frame block;
   Frame string;

   unsigned hashed_len;
   unsigned min_testlen;

   bool has_match;
   Frame match;

   // hash

   SimpleArray<uint16> hashed_head;
   SimpleArray<uint16> prevpos;

  private:

   static constexpr unsigned MinMatch =   3 ;
   static constexpr unsigned MaxMatch = 258 ;

   void setLevel(Level level);

   void init(Param param);

   void reset();

   void downWindow();

   unsigned fillWindow(PtrLen<const uint8> data);

   unsigned computeHash(const uint8 *str) const;

   void insertHash(unsigned start);

   Frame bestMatch(unsigned prev_len) const;

   void processBuffer();

   PtrLen<const uint8> getBlock() const { return Range(buf.getPtr()+block.pos,block.len); }

   void literalByte(uint8 octet);

   void matchFound(unsigned distance,unsigned length);

   void endBlock(bool eof);

  public:

   explicit Deflator(OutFunc out,Param param={});

   ~Deflator();

   Level getLevel() const { return sym.getLevel(); }

   Log2WindowLen getLog2WindowLen() const { return log2_window_len; }

   void put(const uint8 *ptr,ulen len) { put({ptr,len}); }

   void put(PtrLen<const uint8> data);

   void complete();
 };

//----------------------------------------------------------------------------------------

/* consts */

inline constexpr unsigned MaxHeaderBitlen = 3+(5+5+4)+19*3+(286+30)*(7+7) ;

/* classes */

class WindowOut;

class BitReader;

class HuffmanDecoder;

class Inflator;

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

   PtrLen<const uint8> output() const;

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

   void put(const uint8 *ptr,ulen len) { put({ptr,len}); }

   void put(PtrLen<const uint8> data);

   void put(unsigned distance,unsigned length);
 };

/* class BitReader */

class BitReader : NoCopy
 {
   static constexpr unsigned BufLen = RoundUpCount(MaxHeaderBitlen,8u) ;

   PtrLen<const uint8> inp;

   uint8 inpbuf[BufLen];
   unsigned getpos = 0 ;
   unsigned addpos = 0 ;

   uint32 buffer = 0 ;
   unsigned bits = 0 ;

  private:

   bool next(uint8 &octet);

   UCode peekBits(unsigned bitlen) const
    {
     return buffer&((UCode(1)<<bitlen)-1);
    }

   void copyDown();

  public:

   BitReader() {}

   bool isEmpty() const { return bits==0 && getpos==addpos && !inp ; }

   bool canRead(unsigned bitlen) const;

   void align8() { skipBits(bits%8); }

   void extend(PtrLen<const uint8> data);

   void bufferize(ExceptionType ex);

   void pumpTo(WindowOut &out);

   void pumpTo(WindowOut &out,ulen &cap);

   // bit buffer

   UCode peekBuffer() const { return buffer; }

   unsigned bitsBuffered() const { return bits; }

   bool fillBuffer(unsigned bitlen);

   void reqBuffer(unsigned bitlen);

   void skipBits(unsigned bitlen) // bitlen <= bitsBuffered()
    {
     buffer>>=bitlen;
     bits-=bitlen;
    }

   UCode getBits(unsigned bitlen) // bitlen <= bitsBuffered()
    {
     UCode ret=peekBits(bitlen);

     skipBits(bitlen);

     return ret;
    }
 };

/* class HuffmanDecoder */

class HuffmanDecoder : NoCopy
 {
   BitLen max_code_bits;

   // code

   struct CodeInfo
    {
     UCode ncode = 0 ;
     BitLen bitlen = 0 ;
     USym sym = 0 ;

     CodeInfo() noexcept {}

     void set(UCode code,BitLen bitlen_,USym sym_)
      {
       ncode=NormalizeCode(code,bitlen_);
       bitlen=bitlen_;
       sym=sym_;
      }

     bool operator < (const CodeInfo &obj) const { return ncode<obj.ncode; }
    };

   SimpleArray<CodeInfo> table;

   // cache

   struct CacheEntry
    {
     unsigned type;

     union
      {
       USym sym;            // 1
       const CodeInfo *beg; // 2,3
      };

     union
      {
       BitLen bitlen;       // 1,2
       const CodeInfo *lim; // 3
      };

     const CodeInfo & index(UCode ncode,BitLen cache_bits) const
      {
       return beg[ (ncode<<cache_bits)>>(MaxCodeBits-(bitlen-cache_bits)) ];
      }

     const CodeInfo & find(UCode ncode) const
      {
       return Find(beg,lim,ncode);
      }
    };

   mutable SimpleArray<CacheEntry> cache;

   BitLen cache_bits;
   UCode cache_mask;
   UCode norm_cache_mask;

  private:

   static const CodeInfo & Find(PtrLen<const CodeInfo> r,UCode ncode);

   static const CodeInfo & Find(const CodeInfo *beg,const CodeInfo *lim,UCode ncode)
    {
     return Find(Range(beg,lim),ncode);
    }

   static UCode NormalizeCode(UCode code,BitLen bitlen);

   void FillCacheEntry(CacheEntry &entry,UCode ncode) const;

  public:

   HuffmanDecoder() noexcept {}

   explicit HuffmanDecoder(PtrLen<BitLen> bitlens) { init(bitlens); }

   ~HuffmanDecoder() {}

   void init(PtrLen<BitLen> bitlens);

   BitLen decode(UCode code,USym &sym) const;

   bool decode(BitReader &reader,USym &sym) const;

   void reqDecode(BitReader &reader,USym &sym) const;
 };

/* class Inflator */

class Inflator : NoCopy
 {
   WindowOut out;

   BitReader reader;

   // params

   bool repeat;
   Function<void (void)> trigger;

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

   USym literal;
   USym distance;

   HuffmanDecoder dynamic_literal_decoder;
   HuffmanDecoder dynamic_distance_decoder;

  private:

   void decodeCode();

   void decodeHeader();

   bool decodeBody();

   void processInput(bool eof);

  public:

   explicit Inflator(OutFunc out,bool repeat=false);

   ~Inflator();

   void setTrigger(Function<void (void)> trigger_) { trigger=trigger_; }

   void put(const uint8 *ptr,ulen len) { put({ptr,len}); }

   void put(PtrLen<const uint8> data);

   void complete();
 };

} // namespace Deflate
} // namespace CCore

#endif

