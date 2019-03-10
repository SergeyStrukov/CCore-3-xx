/* TagTest.cpp */
//----------------------------------------------------------------------------------------
//
//  Project: Book Convertor 1.00
//
//  License: Boost Software License - Version 1.0 - August 17th, 2003
//
//            see http://www.boost.org/LICENSE_1_0.txt or the local copy
//
//  Copyright (c) 2018 Sergey Strukov. All rights reserved.
//
//----------------------------------------------------------------------------------------

#include <inc/TagTest.h>

#include <CCore/inc/CharProp.h>

namespace App {

/* class TagTest */

StrLen TagTest::ToString(int code)
 {
  switch( code )
    {
     case Error_NoBlock : return "No text block"_c;

     case Error_BlockMismatch : return "Text block mismatch"_c;

     case Error_InBlock : return "Text block is opened"_c;

     default: return "???"_c;
    }
 }

auto TagTest::open(BlockType bt) -> TagErrorId
 {
  if( block==NoBlock )
    {
     block=bt;

     return {};
    }

  return Error_InBlock;
 }

auto TagTest::close(BlockType bt) -> TagErrorId
 {
  if( block==bt )
    {
     block=NoBlock;

     return {};
    }

  return block?Error_BlockMismatch:Error_NoBlock;
 }

bool TagTest::TestSpace(StrLen str)
 {
  for(char ch : str ) if( !CharIsSpace(ch) ) return false;

  return true;
 }

 // frame

auto TagTest::frame(String str) -> TagErrorId
 {
  if( !block && !TestSpace(Range(str)) ) return Error_NoBlock;

  return {};
 }

 // text

auto TagTest::tagH1() -> TagErrorId
 {
  return open(Block_H1);
 }

auto TagTest::tagH1end() -> TagErrorId
 {
  return close(Block_H1);
 }

auto TagTest::tagH2() -> TagErrorId
 {
  return open(Block_H2);
 }

auto TagTest::tagH2end() -> TagErrorId
 {
  return close(Block_H2);
 }

auto TagTest::tagH3() -> TagErrorId
 {
  return open(Block_H3);
 }

auto TagTest::tagH3end() -> TagErrorId
 {
  return close(Block_H3);
 }

auto TagTest::tagH4() -> TagErrorId
 {
  return open(Block_H4);
 }

auto TagTest::tagH4end() -> TagErrorId
 {
  return close(Block_H4);
 }

auto TagTest::tagH5() -> TagErrorId
 {
  return open(Block_H5);
 }

auto TagTest::tagH5end() -> TagErrorId
 {
  return close(Block_H5);
 }

auto TagTest::tagP() -> TagErrorId
 {
  return open(Block_P);
 }

auto TagTest::tagPend() -> TagErrorId
 {
  return close(Block_P);
 }

auto TagTest::tagP(String) -> TagErrorId
 {
  return open(Block_P);
 }

auto TagTest::tagPRE() -> TagErrorId
 {
  return open(Block_PRE);
 }

auto TagTest::tagPREend() -> TagErrorId
 {
  return close(Block_PRE);
 }

 // format

auto TagTest::tagBR() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagB() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagBend() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagI() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagIend() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagU() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagUend() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagSUB() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagSUBend() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagSUP() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagSUPend() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagSPAN(String) -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagSPANend() -> TagErrorId // TODO
 {
  return {};
 }

 // hyperlink

auto TagTest::tagA(String) -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagA(String,String) -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagAname(String) -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagAend() -> TagErrorId // TODO
 {
  return {};
 }

 // list

auto TagTest::tagOL() -> TagErrorId
 {
  return open(Block_OL);
 }

auto TagTest::tagOLend() -> TagErrorId
 {
  return close(Block_OL);
 }

auto TagTest::tagUL() -> TagErrorId
 {
  return open(Block_UL);
 }

auto TagTest::tagULend() -> TagErrorId
 {
  return close(Block_UL);
 }

auto TagTest::tagLI() -> TagErrorId // TODO
 {
  return {};
 }

auto TagTest::tagLIend() -> TagErrorId // TODO
 {
  return {};
 }

 // image

auto TagTest::tagImg(String) -> TagErrorId
 {
  if( block ) return Error_InBlock;

  return {};
 }

 // complete

auto TagTest::complete() -> TagErrorId
 {
  if( block ) return Error_InBlock;

  return {};
 }

} // namespace App

