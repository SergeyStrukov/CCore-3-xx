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
     case Error_NoBlock : return "No opened text block"_c;

     case Error_BlockMismatch : return "Text block mismatch"_c;

     case Error_InBlock : return "Text block is opened"_c;

     case Error_NotList : return "Not a list"_c;

     case Error_NotItem : return "Not a list item"_c;

     case Error_ItemNotClosed : return "List item is not closed"_c;

     case Error_HasFmt : return "Format flag is active"_c;

     case Error_NoFmt : return "Format flag is not active"_c;

     case Error_BR : return "BR tag"_c;

     default: return "???"_c;
    }
 }

auto TagTest::noFormat() const -> TagErrorId
 {
  if( fmt_b ) return Error_HasFmt;
  if( fmt_i ) return Error_HasFmt;
  if( fmt_u ) return Error_HasFmt;
  if( fmt_sub ) return Error_HasFmt;
  if( fmt_sup ) return Error_HasFmt;
  if( fmt_span ) return Error_HasFmt;
  if( fmt_a ) return Error_HasFmt;

  return {};
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

     return noFormat();
    }

  return block?Error_BlockMismatch:Error_NoBlock;
 }

auto TagTest::setFmt(bool &flag) -> TagErrorId
 {
  if( notOpened() ) return Error_NoBlock;

  if( flag ) return Error_HasFmt;

  flag=true;

  return {};
 }

auto TagTest::clearFmt(bool &flag) -> TagErrorId
 {
  if( !flag ) return Error_NoFmt;

  flag=false;

  return {};
 }

bool TagTest::TestSpace(StrLen str)
 {
  for(char ch : str ) if( !CharIsSpace(ch) ) return false;

  return true;
 }

 // frame

auto TagTest::frame(String str) -> TagErrorId
 {
  if( notOpened() && !TestSpace(Range(str)) ) return Error_NoBlock;

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

auto TagTest::tagBR() -> TagErrorId
 {
  return Error_BR;
 }

auto TagTest::tagB() -> TagErrorId
 {
  return setFmt(fmt_b);
 }

auto TagTest::tagBend() -> TagErrorId
 {
  return clearFmt(fmt_b);
 }

auto TagTest::tagI() -> TagErrorId
 {
  return setFmt(fmt_i);
 }

auto TagTest::tagIend() -> TagErrorId
 {
  return clearFmt(fmt_i);
 }

auto TagTest::tagU() -> TagErrorId
 {
  return setFmt(fmt_u);
 }

auto TagTest::tagUend() -> TagErrorId
 {
  return clearFmt(fmt_u);
 }

auto TagTest::tagSUB() -> TagErrorId
 {
  return setFmt(fmt_sub);
 }

auto TagTest::tagSUBend() -> TagErrorId
 {
  return clearFmt(fmt_sub);
 }

auto TagTest::tagSUP() -> TagErrorId
 {
  return setFmt(fmt_sup);
 }

auto TagTest::tagSUPend() -> TagErrorId
 {
  return clearFmt(fmt_sup);
 }

auto TagTest::tagSPAN(String) -> TagErrorId
 {
  return setFmt(fmt_span);
 }

auto TagTest::tagSPANend() -> TagErrorId
 {
  return clearFmt(fmt_span);
 }

 // hyperlink

auto TagTest::tagA(String) -> TagErrorId
 {
  return setFmt(fmt_a);
 }

auto TagTest::tagA(String,String) -> TagErrorId
 {
  return setFmt(fmt_a);
 }

auto TagTest::tagAname(String) -> TagErrorId
 {
  if( block ) return Error_InBlock;

  if( fmt_aname ) return Error_HasFmt;

  fmt_aname=true;

  return {};
 }

auto TagTest::tagAend() -> TagErrorId
 {
  if( block )
    {
     return clearFmt(fmt_a);
    }
  else
    {
     return clearFmt(fmt_aname);
    }
 }

 // list

auto TagTest::tagOL() -> TagErrorId
 {
  return open(Block_OL);
 }

auto TagTest::tagOLend() -> TagErrorId
 {
  if( item ) return Error_ItemNotClosed;

  return close(Block_OL);
 }

auto TagTest::tagUL() -> TagErrorId
 {
  return open(Block_UL);
 }

auto TagTest::tagULend() -> TagErrorId
 {
  if( item ) return Error_ItemNotClosed;

  return close(Block_UL);
 }

auto TagTest::tagLI() -> TagErrorId
 {
  if( inList() && !item )
    {
     item=true;

     return {};
    }

  return Error_NotList;
 }

auto TagTest::tagLIend() -> TagErrorId
 {
  if( inList() && item )
    {
     item=false;

     return noFormat();
    }

  return Error_NotItem;
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

