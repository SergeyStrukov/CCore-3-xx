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

#include <CCore/inc/algon/BinarySearch.h>

#include <CCore/inc/Exception.h>

#include <CCore/inc/FileToMem.h>
#include <CCore/inc/BinaryFile.h>

namespace App {

namespace Private_3037 {

using namespace Deflate;

/* Mismatch() */

template <class Ptr>
Ptr Mismatch(Ptr a,Ptr lim,Ptr b)
 {
  for(; a<lim ;++a,++b) if( *a!=*b ) return a;

  return lim;
 }

/* class Deflator */

class Deflator : NoCopy
 {
   SymWriter sym;

   // params

   Log2WindowLen log2_window_len;

   unsigned DSIZE, DMASK, HSIZE, HMASK, GOOD_MATCH, MAX_CHAIN_LENGTH;

   unsigned max_lazy_len;

   // data

   SimpleArray<uint8> buf;

   struct Frame
    {
     unsigned pos;
     unsigned len;

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

   SimpleArray<uint16> m_head, m_prev;

  private:

   static constexpr unsigned MinMatch =   3 ;
   static constexpr unsigned MaxMatch = 258 ;

   void setLevel(Level level);

   void init(Param param);

   void reset();

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

void Deflator::setLevel(Level level)
 {
  if( !( level>=MinLevel && level<=MaxLevel ) )
    {
     Printf(Exception,"Deflator: #; is an invalid deflate level",level);
    }

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
    /* 9 */ {32, 258, 258, 4096}  // maximum compression
   };

  GOOD_MATCH = configurationTable[level][0] ;
  max_lazy_len = configurationTable[level][1] ;
  MAX_CHAIN_LENGTH = configurationTable[level][3] ;
 }

void Deflator::init(Param param)
 {
  if( !( MinLog2WindowLen<=param.log2_window_len && param.log2_window_len<=MaxLog2WindowLen ) )
    {
     Printf(Exception,"Deflator: #; is an invalid window size",param.log2_window_len);
    }

  log2_window_len = param.log2_window_len ;

  DSIZE = 1 << log2_window_len ;
  DMASK = DSIZE - 1 ;
  HSIZE = 1 << log2_window_len ;
  HMASK = HSIZE - 1 ;

  buf=SimpleArray<uint8>(2*DSIZE);

  m_head=SimpleArray<uint16>(HSIZE);
  m_prev=SimpleArray<uint16>(DSIZE);

  setLevel(param.level);

  sym.init(param.level,param.detect_uncompressible,DSIZE/2);

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

  // m_prev will be initialized automatically in InsertString

  Range(m_head).set_null();
 }


unsigned Deflator::fillWindow(PtrLen<const uint8> data)
 {
  unsigned maxBlockSize=Min<unsigned>(2*DSIZE,0xFFFFu);

  uint8 *base=buf.getPtr();

  if( string.pos>=maxBlockSize-MaxMatch )
    {
     if( block.pos<DSIZE ) endBlock(false);

     Range(base,DSIZE).copy(base+DSIZE);

     string.pos-=DSIZE;
     match.pos-=DSIZE;
     block.pos-=DSIZE;

     hashed_len=PosSub(hashed_len,DSIZE);

     for(unsigned i=0; i<HSIZE ;i++) m_head[i]=PosSub(m_head[i],DSIZE);

     for(unsigned i=0; i<DSIZE ;i++) m_prev[i]=PosSub(m_prev[i],DSIZE);
    }

  unsigned off=string.pos+string.len;

  unsigned delta = (unsigned)Min<ulen>(maxBlockSize-off,data.len) ;

  Range(base+off,delta).copy(data.ptr);

  string.len+=delta;

  return delta;
 }


unsigned Deflator::computeHash(const uint8 *str) const
 {
  unsigned s0=str[0];
  unsigned s1=str[1];
  unsigned s2=str[2];

  return ((s0<<10)^(s1<<5)^s2)&HMASK;
 }

void Deflator::insertHash(unsigned start)
 {
  unsigned hash=computeHash(buf.getPtr()+start);

  m_prev[start&DMASK]=m_head[hash];
  m_head[hash]=uint16(start);
 }

auto Deflator::bestMatch(unsigned prev_len) const -> Frame
 {
  unsigned bestMatch=0;
  unsigned bestLength=Max<unsigned>(prev_len,MinMatch-1);

  if( string.len<=bestLength ) return {0,0};

  const uint8 *scan=buf.getPtr()+string.pos;
  const uint8 *scanEnd=scan+Min<unsigned>(MaxMatch,string.len);

  unsigned limit=PosSub(string.pos,DSIZE-MaxMatch);

  unsigned current=m_head[computeHash(scan)];

  unsigned chainLength=MAX_CHAIN_LENGTH;

  if( prev_len>=GOOD_MATCH ) chainLength>>=2;

  while( current>limit && --chainLength>0 )
    {
     const uint8 *match=buf.getPtr()+current;

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

  return {bestMatch,(bestMatch>0)? bestLength : 0 };
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
     while( hashed_len<string.pos && hashed_len+3<=string.pos+string.len ) insertHash(hashed_len++);

     if( has_match )
       {
        Frame next;

        bool push_current;

        if( match.len>=max_lazy_len )
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

