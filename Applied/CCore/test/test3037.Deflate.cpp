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

   Log2WindowLen m_log2WindowSize;

   unsigned DSIZE, DMASK, HSIZE, HMASK, GOOD_MATCH, MAX_LAZYLENGTH, MAX_CHAIN_LENGTH;

   // octets

   SimpleArray<uint8> m_byteBuffer;
   SimpleArray<uint16> m_head, m_prev;

   bool m_matchAvailable;

   unsigned m_dictionaryEnd, m_stringStart, m_lookahead, m_minLookahead, m_previousMatch, m_previousLength;
   unsigned m_blockStart, m_blockLength;

  private:

   enum { MIN_MATCH = 3, MAX_MATCH = 258 };


   void setLevel(Level level);

   void init(Param param);

   void reset();


   unsigned fillWindow(const uint8 *str,ulen len);


   unsigned computeHash(const uint8 *str) const;

   unsigned longestMatch(unsigned &bestMatch) const;

   void insertString(unsigned start);

   void processBuffer();


   PtrLen<const uint8> getBlock() const { return Range(m_byteBuffer.getPtr()+m_blockStart,m_blockLength); }

   void literalByte(uint8 octet);

   void matchFound(unsigned distance,unsigned length);

   void endBlock(bool eof);

  public:

   explicit Deflator(OutFunc out,Param param={});

   ~Deflator();

   Level getLevel() const { return sym.getLevel(); }

   Log2WindowLen getLog2WindowSize() const { return m_log2WindowSize; }

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

  m_log2WindowSize = param.log2_window_len ;

  DSIZE = 1 << m_log2WindowSize ;
  DMASK = DSIZE - 1 ;
  HSIZE = 1 << m_log2WindowSize ;
  HMASK = HSIZE - 1 ;

  m_byteBuffer=SimpleArray<uint8>(2*DSIZE);

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

  m_dictionaryEnd = 0 ;
  m_stringStart = 0 ;
  m_lookahead = 0 ;
  m_minLookahead = MAX_MATCH ;

  m_blockStart = 0 ;
  m_blockLength = 0 ;

  // m_prev will be initialized automatically in InsertString

  Range(m_head).set_null();
 }


unsigned Deflator::fillWindow(const uint8 *str,ulen len)
 {
  unsigned maxBlockSize=Min<unsigned>(2*DSIZE,0xFFFFu);

  uint8 *base=m_byteBuffer.getPtr();

  if( m_stringStart>=maxBlockSize-MAX_MATCH )
    {
     if( m_blockStart<DSIZE ) endBlock(false);

     Range(base,DSIZE).copy(base+DSIZE);

     m_stringStart-=DSIZE;
     m_previousMatch-=DSIZE;
     m_blockStart-=DSIZE;

     m_dictionaryEnd=PosSub(m_dictionaryEnd,DSIZE);

     for(unsigned i=0; i<HSIZE ;i++) m_head[i]=PosSub(m_head[i],DSIZE);

     for(unsigned i=0; i<DSIZE ;i++) m_prev[i]=PosSub(m_prev[i],DSIZE);
    }

  unsigned off=m_stringStart+m_lookahead;

  unsigned accepted = (unsigned)Min<ulen>(maxBlockSize-off,len) ;

  Range(base+off,accepted).copy(str);

  m_lookahead+=accepted;

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

  if( m_lookahead<=bestLength ) return 0;

  const uint8 *scan=m_byteBuffer.getPtr()+m_stringStart;
  const uint8 *scanEnd=scan+Min<unsigned>(MAX_MATCH,m_lookahead);

  unsigned limit=PosSub(m_stringStart,DSIZE-MAX_MATCH);

  unsigned current=m_head[computeHash(scan)];

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

void Deflator::insertString(unsigned start)
 {
  unsigned hash=computeHash(m_byteBuffer.getPtr()+start);

  m_prev[start&DMASK]=m_head[hash];
  m_head[hash]=uint16(start);
 }

void Deflator::processBuffer()
 {
  if( getLevel()==MinLevel )
    {
     m_stringStart+=m_lookahead;
     m_lookahead=0;
     m_blockLength=m_stringStart-m_blockStart;

     m_matchAvailable=false;

     return;
    }

  while( m_lookahead>m_minLookahead )
    {
     while( m_dictionaryEnd<m_stringStart && m_dictionaryEnd+3<=m_stringStart+m_lookahead ) insertString(m_dictionaryEnd++);

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
           matchFound(m_stringStart-1-m_previousMatch,m_previousLength);

           m_stringStart += m_previousLength-1 ;
           m_lookahead -= m_previousLength-1 ;

           m_matchAvailable=false;
          }
        else
          {
           m_previousLength=matchLength;
           m_previousMatch=matchPosition;

           literalByte(m_byteBuffer[m_stringStart-1]);

           m_stringStart++;
           m_lookahead--;
          }
       }
     else
       {
        m_previousLength=0;
        m_previousLength=longestMatch(m_previousMatch);

        if( m_previousLength )
          m_matchAvailable=true;
        else
          literalByte(m_byteBuffer[m_stringStart]);

        m_stringStart++;
        m_lookahead--;
       }
    }

  if( m_minLookahead==0 && m_matchAvailable )
    {
     literalByte(m_byteBuffer[m_stringStart-1]);

     m_matchAvailable = false;
    }
 }


void Deflator::literalByte(uint8 octet)
 {
  if( sym.testFull(getBlock()) )
    {
     m_blockStart+=m_blockLength;
     m_blockLength=0;
    }

  sym.put(octet);

  m_blockLength++;
 }

void Deflator::matchFound(unsigned distance,unsigned length)
 {
  if( sym.testFull(getBlock()) )
    {
     m_blockStart+=m_blockLength;
     m_blockLength=0;
    }

  sym.put(distance,length);

  m_blockLength+=length;
 }

void Deflator::endBlock(bool eof)
 {
  sym.endBlock(eof,getBlock());

  m_blockStart+=m_blockLength;
  m_blockLength=0;
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
  m_minLookahead=0;

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

