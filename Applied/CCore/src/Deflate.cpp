/* Deflate.cpp */
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

#include <CCore/inc/Deflate.h>

#include <CCore/inc/Sort.h>
#include <CCore/inc/algon/BestSearch.h>
#include <CCore/inc/algon/BinarySearch.h>

#include <CCore/inc/Exception.h>

namespace CCore {
namespace Deflate {

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

void BitWriter::flushBitBuffer()
 {
  if( !count_mode )
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

unsigned BitWriter::finishCounting()
 {
  count_mode=false;

  return bit_count;
 }

/* class HuffmanEncoder */

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

  for(ulen i=lim-2; i>=counts.len ;i--) tree[i].depth=tree[tree[i].parent].depth+1;

  // bitlen counts

  TempArray<BitLen,MaxBitLens+1> blcounts(maxbitlen+1);

  Range(blcounts).set_null();

  unsigned sum=0;

  for(Node &node : initial )
    {
     ulen depth=Min<ulen>(maxbitlen,tree[node.parent].depth+1);

     blcounts[depth]++;

     sum += ulen(1)<<(maxbitlen-depth) ;
    }

  // correct bitlens

  unsigned cap=ulen(1)<<maxbitlen;

  if( sum>cap )
    {
     unsigned overflow=sum-cap;

     while( overflow-- )
       {
        BitLen bits=maxbitlen-1;

        while( blcounts[bits]==0 ) bits--;

        blcounts[bits]--;
        blcounts[bits+1]+=2;

        blcounts[maxbitlen]--;
       }
    }

  // set bitlens

  for(Node &node : Range(tree.getPtr(),beg) ) bitlens[node.sym]=0;

  BitLen bits=maxbitlen;

  for(Node &node : initial )
    {
     while( blcounts[bits]==0 ) bits--;

     bitlens[node.sym]=bits;

     blcounts[bits]--;
    }
 }

/* class SymWriter */

void SymWriter::initStaticEncoders()
 {
  // literal

  {
   BitLen bitlens[288];

   Range(bitlens,bitlens+144).set(8);
   Range(bitlens+144,bitlens+256).set(9);
   Range(bitlens+256,bitlens+280).set(7);
   Range(bitlens+280,bitlens+288).set(8);

   static_literal_encoder.init(Range(bitlens));
  }

  // distance

  {
   BitLen bitlens[32];

   Range(bitlens).set(5);

   static_distance_encoder.init(Range(bitlens));
  }
 }

struct SymWriter::CodeLenEncoder
 {
  USym sym; // < 19
  Code extra;
  PtrLen<const BitLen> next;

  CodeLenEncoder(const BitLen *beg,PtrLen<const BitLen> cur)
   {
    BitLen v=*cur;

    if( cur.len>=3 )
      {
       ulen prev=cur.len;

       if( v==0 && cur[1]==0 && cur[2]==0 )
         {
          for(cur+=3; +cur && *cur==0 && prev-cur.len<138u ;++cur);

          UCode repeat=(UCode)(prev-cur.len);

          if( repeat<=10 )
            {
             sym=17;
             extra.code=repeat-3;
             extra.bitlen=3;
            }
          else
            {
             sym=18;
             extra.code=repeat-11;
             extra.bitlen=7;
            }

          next=cur;

          return;
         }

       if( cur.ptr>beg && v==cur.ptr[-1] && v==cur[1] && v==cur[2] )
         {
          for(cur+=3; +cur && *cur==v && prev-cur.len<6u ;++cur);

          UCode repeat=(UCode)(prev-cur.len);

          sym=16;
          extra.code=repeat-3;
          extra.bitlen=2;

          next=cur;

          return;
         }
      }

    sym=v;
    extra.code=0;
    extra.bitlen=0;

    ++cur;

    next=cur;
   }
 };

void SymWriter::encodeTree(PtrLen<const BitLen> combined,unsigned hlit,unsigned hdist)
 {
  // create encoder

  ulen counts[19]={};

  for(PtrLen<const BitLen> cur=combined; +cur ;)
    {
     CodeLenEncoder lencode(combined.ptr,cur);

     counts[lencode.sym]++;

     cur=lencode.next;
    }

  BitLen bitlens[19];

  HuffmanEncoder::Tree(bitlens,7,Range(counts));

  HuffmanEncoder encoder(Range(bitlens));

  // put header

  static const unsigned Order[19]= // bitlen permutation
   {
    16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
   };

  unsigned hclen=19;

  while( hclen>4 && bitlens[Order[hclen-1]]==0 ) hclen--;

  writer.putBits({hlit,5});
  writer.putBits({hdist,5});
  writer.putBits({hclen-4,4});

  for(unsigned i=0; i<hclen ;i++) writer.putBits({bitlens[Order[i]],3});

  // put combined

  for(PtrLen<const BitLen> cur=combined; +cur ;)
    {
     CodeLenEncoder lencode(combined.ptr,cur);

     encoder.encode(writer,lencode.sym);

     writer.putBits(lencode.extra);

     cur=lencode.next;
    }
 }

void SymWriter::encodeBlock(bool eof,BlockType block_type,PtrLen<const uint8> block)
 {
  writer.putBits({eof,1});
  writer.putBits({block_type,2});

  if( block_type==Stored )
    {
     writer.flushBitBuffer();

     uint16 blen=uint16(block.len);

     writer.put16(blen);
     writer.put16(~blen);
     writer.put(block);
    }
  else
    {
     if( block_type==Dynamic )
       {
        BitLen literal_bitlens[286];
        BitLen distance_bitlens[30];

        literal_counts[256]=1;

        HuffmanEncoder::Tree(literal_bitlens,15,Range(literal_counts));

        dynamic_literal_encoder.init(Range(literal_bitlens));

        unsigned hlit=(unsigned)TrimNull(literal_bitlens+257,literal_bitlens+286);

        HuffmanEncoder::Tree(distance_bitlens,15,Range(distance_counts));

        dynamic_distance_encoder.init(Range(distance_bitlens));

        unsigned hdist=(unsigned)TrimNull(distance_bitlens+1,distance_bitlens+30);

        unsigned nlit=hlit+257;
        unsigned ndist=hdist+1;

        TempArray<BitLen,286+30> combined(nlit+ndist);

        Range(combined.getPtr(),nlit).copy(literal_bitlens);

        Range(combined.getPtr()+nlit,ndist).copy(distance_bitlens);

        encodeTree(Range(combined),hlit,hdist);
       }

     static const unsigned LengthExtraBits[29]=
      {
       0, 0, 0, 0,
       0, 0, 0, 0,
       1, 1, 1, 1,
       2, 2, 2, 2,
       3, 3, 3, 3,
       4, 4, 4, 4,
       5, 5, 5, 5,
       0
      };

     static const unsigned DistanceExtraBits[30]=
      {
       0, 0,
       0, 0,
       1, 1,
       2, 2,
       3, 3,
       4, 4,
       5, 5,
       6, 6,
       7, 7,
       8, 8,
       9, 9,
       10, 10,
       11, 11,
       12, 12,
       13, 13
      };

     const HuffmanEncoder &literal_encoder = (block_type==Static)? static_literal_encoder : dynamic_literal_encoder ;

     const HuffmanEncoder &distance_encoder = (block_type==Static)? static_distance_encoder : dynamic_distance_encoder ;

     for(auto m : Range(buf.getPtr(),pos) )
       {
        USym literal_code=m.literal_code;

        literal_encoder.encode(writer,literal_code);

        if( literal_code>=257 )
          {
           writer.putBits({m.literal_extra,LengthExtraBits[literal_code-257]});

           USym distance_code=m.distance_code;

           distance_encoder.encode(writer,distance_code);

           writer.putBits({m.distance_extra,DistanceExtraBits[distance_code]});
          }
       }

     literal_encoder.encode(writer,256);
    }
 }

SymWriter::SymWriter(OutFunc out)
 : writer(out)
 {
  initStaticEncoders();
 }

SymWriter::~SymWriter()
 {
 }

void SymWriter::init(Level level_,bool detect_uncompressible,unsigned buflen)
 {
  level=level_;
  compressible_level = detect_uncompressible? level_ : MinLevel ;

  buf=SimpleArray<EncodedMatch>(buflen);
 }

void SymWriter::reset()
 {
  pos=0;

  detect_skip=0;
  detect_count=1;

  Range(literal_counts).set_null();
  Range(distance_counts).set_null();

  writer.clearBitBuffer();
 }

bool SymWriter::testFull(PtrLen<const uint8> block)
 {
  if( pos==buf.getLen() )
    {
     endBlock(false,block);

     return true;
    }

  return false;
 }

void SymWriter::put(uint8 octet)
 {
  buf[pos++].literal_code=octet;

  literal_counts[octet]++;
 }

void SymWriter::put(unsigned distance,unsigned length)
 {
  static const USym LengthCodes[256]=
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

  static const unsigned LengthBases[29]=
   {
    3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227,258
   };

  static const unsigned DistanceBases[30]=
   {
    1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577
   };

  EncodedMatch &m=buf[pos++];

  USym length_code=LengthCodes[length-3];

  m.literal_code=length_code;
  m.literal_extra=length-LengthBases[length_code-257];

  auto r=Range(DistanceBases);

  USym distance_code=(USym)Algon::BinarySearch_greater(r,distance).len-1;

  m.distance_code=distance_code;
  m.distance_extra=distance-DistanceBases[distance_code];

  literal_counts[length_code]++;
  distance_counts[distance_code]++;
 }

void SymWriter::endBlock(bool eof,PtrLen<const uint8> block)
 {
  if( block.len==0 && !eof ) return;

  if( level==MinLevel )
    {
     encodeBlock(eof,Stored,block);

     if( compressible_level>MinLevel && ++detect_count==detect_skip )
       {
        level=compressible_level;

        detect_count=1;
       }
    }
  else
    {
     unsigned stored_len=8*(block.len+4)+writer.extBits();

     writer.startCounting();

     encodeBlock(eof,Static,block);

     unsigned static_len=writer.finishCounting();

     unsigned dynamic_len;

     if( block.len<128 && level<EverdynamicLevel )
       {
        dynamic_len=MaxUInt<unsigned>;
       }
     else
       {
        writer.startCounting();

        encodeBlock(eof,Dynamic,block);

        dynamic_len=writer.finishCounting();
       }

     if( stored_len<=static_len && stored_len<=dynamic_len )
       {
        encodeBlock(eof,Stored,block);

        if( compressible_level>MinLevel )
          {
           if( detect_skip )
             {
              level=MinLevel;

              detect_skip=Min<unsigned>(2*detect_skip,128);
             }
           else
             {
              detect_skip=1;
             }
          }
       }
     else
       {
        if( static_len<=dynamic_len )
          encodeBlock(eof,Static,block);
        else
          encodeBlock(eof,Dynamic,block);

        if( compressible_level>MinLevel ) detect_skip=0;
       }
    }

  pos=0;

  Range(literal_counts).set_null();
  Range(distance_counts).set_null();

  if( eof ) writer.flushBitBuffer();
 }

/* class Deflator */

void Deflator::setLevel(Level level)
 {
  if( !( level>=MinLevel && level<=MaxLevel ) )
    {
     Printf(Exception,"Deflator: #; is an invalid deflate level",level);
    }

  struct Rec
   {
    unsigned good_match;
    unsigned min_lazy_len;
    unsigned max_chain_len;
   };

  static const Rec Table[10]=
   {
    /* 0 */ {0,    0,    0},  // store only
    /* 1 */ {4,    3,    4},  // maximum speed, no lazy matches
    /* 2 */ {4,    3,    8},
    /* 3 */ {4,    3,   32},
    /* 4 */ {4,    4,   16},  // lazy matches
    /* 5 */ {8,   16,   32},
    /* 6 */ {8,   16,  128},  // default
    /* 7 */ {8,   32,  256},
    /* 8 */ {32, 128, 1024},
    /* 9 */ {32, 258, 4096}  // maximum compression
   };

  min_lazy_len=Table[level].min_lazy_len;
  good_match=Table[level].good_match;
  max_chain_len=Table[level].max_chain_len;
 }

void Deflator::init(Param param)
 {
  if( !( MinLog2WindowLen<=param.log2_window_len && param.log2_window_len<=MaxLog2WindowLen ) )
    {
     Printf(Exception,"Deflator: #; is an invalid window size",param.log2_window_len);
    }

  log2_window_len=param.log2_window_len;

  wind_len = 1 << log2_window_len ; // > MaxMatch
  wind_mask = wind_len - 1 ;

  hash_len = 1 << log2_window_len ;
  hash_mask = hash_len - 1 ;

  cap_data_len=Min<unsigned>(2*wind_len,0xFFFFu); // >= wind_len+MaxMatch , >= 2*wind_len-1

  buf=SimpleArray<uint8>(2*wind_len);

  hashed_head=SimpleArray<uint16>(hash_len);

  prevpos=SimpleArray<uint16>(wind_len);

  setLevel(param.level);

  sym.init(param.level,param.detect_uncompressible,wind_len/2);

  reset();
 }

void Deflator::reset()
 {
  sym.reset();

  block.null();

  string.null();

  hashed_len=0;
  min_testlen=MaxMatch;

  has_match=false;

  Range(hashed_head).set_null();
 }

void Deflator::downWindow()
 {
  if( block.pos<wind_len ) endBlock(false);

  uint8 *base=buf.getPtr();

  Range(base,wind_len).copy(base+wind_len);

  block.pos-=wind_len;
  string.pos-=wind_len;

  match.pos-=wind_len;

  hashed_len=PosSub(hashed_len,wind_len);

  for(auto &start : hashed_head ) start=PosSub(start,wind_len);

  for(auto &prev : prevpos ) prev=PosSub(prev,wind_len);
 }

unsigned Deflator::fillWindow(PtrLen<const uint8> data)
 {
  if( string.pos>=cap_data_len-MaxMatch ) downWindow();

  unsigned off=string.getLim();

  unsigned delta=(unsigned)Min<ulen>(cap_data_len-off,data.len) ;

  Range(buf.getPtr()+off,delta).copy(data.ptr);

  string.len+=delta;

  return delta;
 }

unsigned Deflator::computeHash(const uint8 *str) const
 {
  unsigned s0=str[0];
  unsigned s1=str[1];
  unsigned s2=str[2];

  return ((s0<<10)^(s1<<5)^s2)&hash_mask;
 }

void Deflator::insertHash(unsigned start)
 {
  unsigned hash=computeHash(buf.getPtr()+start);

  prevpos[start&wind_mask]=hashed_head[hash];

  hashed_head[hash]=uint16(start);
 }

auto Deflator::bestMatch(unsigned prev_len) const -> Frame
 {
  unsigned best_pos=0;
  unsigned best_len=Max(prev_len,MinMatch-1);

  unsigned testlen=Min(MaxMatch,string.len);

  if( testlen<=best_len ) return {0,0};

  const uint8 *ptr=buf.getPtr()+string.pos;
  const uint8 *lim=ptr+testlen;

  unsigned pos_limit=PosSub(string.pos,wind_len-MaxMatch);

  unsigned pos=hashed_head[computeHash(ptr)];

  unsigned chain_len=max_chain_len;

  if( prev_len>=good_match ) chain_len>>=2;

  while( pos>pos_limit && --chain_len>0 )
    {
     const uint8 *match=buf.getPtr()+pos;

     if( ptr[best_len-1]==match[best_len-1] && ptr[best_len]==match[best_len] && ptr[0]==match[0] && ptr[1]==match[1] )
       {
        unsigned len=(unsigned)Dist(ptr,Mismatch(ptr+3,lim,match+3));

        if( len>best_len )
          {
           best_len=len;
           best_pos=pos;

           if( len==testlen ) break;
          }
       }

     pos=prevpos[pos&wind_mask];
    }

  if( best_pos ) return {best_pos,best_len};

  return {0,0};
 }

void Deflator::processBuffer()
 {
  if( getLevel()==MinLevel )
    {
     string.finish();

     block.len=string.pos-block.pos;

     has_match=false;

     return;
    }

  while( string.len>min_testlen )
    {
     while( hashed_len<string.pos && hashed_len+3<=string.getLim() ) insertHash(hashed_len++);

     if( has_match )
       {
        Frame next;

        bool push_current;

        if( match.len>=min_lazy_len )
          {
           push_current=true;
          }
        else
          {
           next=bestMatch(match.len);

           push_current=(next.len==0);
          }

        if( push_current )
          {
           matchFound(string.pos-1-match.pos,match.len);

           string+=match.len-1;

           has_match=false;
          }
        else
          {
           match=next;

           literalByte(buf[string.pos-1]);

           ++string;
          }
       }
     else
       {
        match=bestMatch(0);

        if( match.len )
          has_match=true;
        else
          literalByte(buf[string.pos]);

        ++string;
       }
    }

  if( min_testlen==0 && has_match )
    {
     literalByte(buf[string.pos-1]);

     has_match=false;
    }
 }

void Deflator::literalByte(uint8 octet)
 {
  if( sym.testFull(getBlock()) ) block.finish();

  sym.put(octet);

  block.len++;
 }

void Deflator::matchFound(unsigned distance,unsigned length)
 {
  if( sym.testFull(getBlock()) ) block.finish();

  sym.put(distance,length);

  block.len+=length;
 }

void Deflator::endBlock(bool eof)
 {
  sym.endBlock(eof,getBlock());

  block.finish();
 }

Deflator::Deflator(OutFunc out,Param param)
 : sym(out)
 {
  init(param);
 }

Deflator::~Deflator()
 {
 }

void Deflator::put(PtrLen<const uint8> data)
 {
  while( +data )
    {
     unsigned delta=fillWindow(data);

     data+=delta;

     processBuffer();
    }
 }

void Deflator::complete()
 {
  min_testlen=0;

  processBuffer();

  endBlock(true);

  reset();
 }

} // namespace Deflate
} // namespace CCore

