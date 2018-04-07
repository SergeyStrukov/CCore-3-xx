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
  MinLevel         = 0,

  DefaultLevel     = 6,
  EverdynamicLevel = 8,

  MaxLevel         = 9
 };

/* enum Log2WindowLen */

enum Log2WindowLen
 {
  MinLog2WindowLen     = 9,

  DefaultLog2WindowLen = 15,

  MaxLog2WindowLen     = 15
 };

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

/* classes */

struct Code;

class BitWriter;

class HuffmanEncoder;

class SymWriter;

/* struct Code */

struct Code
 {
  UCode code;
  BitLen bitlen;
 };

/* class BitWriter */

using OutFunc = Function<void (PtrLen<const uint8>)> ;

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
   DynArray<Code> table;

  private:

   static BitLen MaxValue(PtrLen<const BitLen> bitlens);

  public:

   HuffmanEncoder() {}

   HuffmanEncoder(PtrLen<const BitLen> bitlens) { init(bitlens); }

   void init(PtrLen<const BitLen> bitlens);

   static void Tree(BitLen bitlens[ /* counts.len */ ],BitLen maxbitlen,PtrLen<const ulen> counts);

     // maxbitlen > 0 && counts.len > 0 && counts.len <= 2^maxbitlen && maxbitlen < Meta::UIntBits<unsigned> - 1

   void encode(BitWriter &writer,USym sym) const { writer.putBits(table[sym]); }
 };

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

   HuffmanEncoder static_literal_encoder;
   HuffmanEncoder static_distance_encoder;

   HuffmanEncoder dynamic_literal_encoder;
   HuffmanEncoder dynamic_distance_encoder;

  private:

   void initStaticEncoders();

   enum BlockType : unsigned
    {
     Stored  = 0,
     Static  = 1,
     Dynamic = 2
    };

   struct CodeLenEncoder;

   void encodeTree(PtrLen<const BitLen> combined,unsigned hlit,unsigned hdist);

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

} // namespace Deflate
} // namespace CCore

#endif

