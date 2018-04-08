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

   unsigned DSIZE, DMASK, HSIZE, HMASK, GOOD_MATCH, MAX_LAZYLENGTH, MAX_CHAIN_LENGTH;

   // octets

   SimpleArray<uint8> buf;
   SimpleArray<uint16> m_head, m_prev;

   bool m_matchAvailable;

   unsigned hashed_len, string_start, string_len, min_testlen, m_previousMatch, m_previousLength;
   unsigned block_start, block_len;

  private:

   enum { MIN_MATCH = 3, MAX_MATCH = 258 };


   void setLevel(Level level);

   void init(Param param);

   void reset();


   unsigned fillWindow(const uint8 *str,ulen len);


   unsigned computeHash(const uint8 *str) const;

   unsigned longestMatch(unsigned &bestMatch) const;

   void insertHash(unsigned start);

   void processBuffer();


   PtrLen<const uint8> getBlock() const { return Range(buf.getPtr()+block_start,block_len); }

   void literalByte(uint8 octet);

   void matchFound(unsigned distance,unsigned length);

   void endBlock(bool eof);

  public:

   explicit Deflator(OutFunc out,Param param={});

   ~Deflator();

   Level getLevel() const { return sym.getLevel(); }

   Log2WindowLen getLog2WindowLen() const { return log2_window_len; }

   void put(const uint8 *ptr,ulen len);

   void put(PtrLen<const uint8> data) { put(data.ptr,data.len); }

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
  MAX_LAZYLENGTH = configurationTable[level][1] ;
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

  m_matchAvailable = false ;

  hashed_len = 0 ;
  string_start = 0 ;
  string_len = 0 ;
  min_testlen = MAX_MATCH ;

  block_start = 0 ;
  block_len = 0 ;

  // m_prev will be initialized automatically in InsertString

  Range(m_head).set_null();
 }


unsigned Deflator::fillWindow(const uint8 *str,ulen len)
 {
  unsigned maxBlockSize=Min<unsigned>(2*DSIZE,0xFFFFu);

  uint8 *base=buf.getPtr();

  if( string_start>=maxBlockSize-MAX_MATCH )
    {
     if( block_start<DSIZE ) endBlock(false);

     Range(base,DSIZE).copy(base+DSIZE);

     string_start-=DSIZE;
     m_previousMatch-=DSIZE;
     block_start-=DSIZE;

     hashed_len=PosSub(hashed_len,DSIZE);

     for(unsigned i=0; i<HSIZE ;i++) m_head[i]=PosSub(m_head[i],DSIZE);

     for(unsigned i=0; i<DSIZE ;i++) m_prev[i]=PosSub(m_prev[i],DSIZE);
    }

  unsigned off=string_start+string_len;

  unsigned accepted = (unsigned)Min<ulen>(maxBlockSize-off,len) ;

  Range(base+off,accepted).copy(str);

  string_len+=accepted;

  return accepted;
 }


unsigned Deflator::computeHash(const uint8 *str) const
 {
  unsigned s0=str[0];
  unsigned s1=str[1];
  unsigned s2=str[2];

  return ((s0<<10)^(s1<<5)^s2)&HMASK;
 }

unsigned Deflator::longestMatch(unsigned &bestMatch) const
 {
  bestMatch=0;

  unsigned bestLength=Max<unsigned>(m_previousLength,MIN_MATCH-1);

  if( string_len<=bestLength ) return 0;

  const uint8 *scan=buf.getPtr()+string_start;
  const uint8 *scanEnd=scan+Min<unsigned>(MAX_MATCH,string_len);

  unsigned limit=PosSub(string_start,DSIZE-MAX_MATCH);

  unsigned current=m_head[computeHash(scan)];

  unsigned chainLength=MAX_CHAIN_LENGTH;

  if( m_previousLength>=GOOD_MATCH ) chainLength>>=2;

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

  return (bestMatch>0)? bestLength : 0 ;
 }

void Deflator::insertHash(unsigned start)
 {
  unsigned hash=computeHash(buf.getPtr()+start);

  m_prev[start&DMASK]=m_head[hash];
  m_head[hash]=uint16(start);
 }

void Deflator::processBuffer()
 {
  if( getLevel()==MinLevel )
    {
     string_start+=string_len;
     string_len=0;
     block_len=string_start-block_start;

     m_matchAvailable=false;

     return;
    }

  while( string_len>min_testlen )
    {
     while( hashed_len<string_start && hashed_len+3<=string_start+string_len ) insertHash(hashed_len++);

     if( m_matchAvailable )
       {
        unsigned matchPosition=0,matchLength=0;

        bool usePreviousMatch;

        if( m_previousLength>=MAX_LAZYLENGTH )
          {
           usePreviousMatch=true;
          }
        else
          {
           matchLength=longestMatch(matchPosition);

           usePreviousMatch=(matchLength==0);
          }

        if( usePreviousMatch )
          {
           matchFound(string_start-1-m_previousMatch,m_previousLength);

           string_start += m_previousLength-1 ;
           string_len -= m_previousLength-1 ;

           m_matchAvailable=false;
          }
        else
          {
           m_previousLength=matchLength;
           m_previousMatch=matchPosition;

           literalByte(buf[string_start-1]);

           string_start++;
           string_len--;
          }
       }
     else
       {
        m_previousLength=0;
        m_previousLength=longestMatch(m_previousMatch);

        if( m_previousLength )
          m_matchAvailable=true;
        else
          literalByte(buf[string_start]);

        string_start++;
        string_len--;
       }
    }

  if( min_testlen==0 && m_matchAvailable )
    {
     literalByte(buf[string_start-1]);

     m_matchAvailable = false;
    }
 }


void Deflator::literalByte(uint8 octet)
 {
  if( sym.testFull(getBlock()) )
    {
     block_start+=block_len;
     block_len=0;
    }

  sym.put(octet);

  block_len++;
 }

void Deflator::matchFound(unsigned distance,unsigned length)
 {
  if( sym.testFull(getBlock()) )
    {
     block_start+=block_len;
     block_len=0;
    }

  sym.put(distance,length);

  block_len+=length;
 }

void Deflator::endBlock(bool eof)
 {
  sym.endBlock(eof,getBlock());

  block_start+=block_len;
  block_len=0;
 }


Deflator::Deflator(OutFunc out,Param param)
 : sym(out)
 {
  init(param);
 }

Deflator::~Deflator()
 {
 }

void Deflator::put(const uint8 *ptr,ulen len)
 {
  ulen accepted=0;

  while( accepted<len )
    {
     unsigned newAccepted=fillWindow(ptr+accepted,len-accepted);

     processBuffer();

     accepted+=newAccepted;
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

