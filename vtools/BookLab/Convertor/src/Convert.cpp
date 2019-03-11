/* Convert.cpp */
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

#include <inc/Convert.h>

namespace App {

/* class Book */

Book::Book(PrintBase &out_)
 : out(out_)
 {
 }

Book::~Book()
 {
 }

/* class Convert */

StrLen Convert::ToString(int code)
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

     default: return "???"_c;
    }
 }

auto Convert::noFormat() const -> TagErrorId
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

auto Convert::open(BlockType bt) -> TagErrorId
 {
  if( block==NoBlock )
    {
     block=bt;

     return {};
    }

  return Error_InBlock;
 }

auto Convert::close(BlockType bt) -> TagErrorId
 {
  if( block==bt )
    {
     block=NoBlock;

     return noFormat();
    }

  return block?Error_BlockMismatch:Error_NoBlock;
 }

auto Convert::setFmt(bool &flag) -> TagErrorId
 {
  if( notOpened() ) return Error_NoBlock;

  if( flag ) return Error_HasFmt;

  flag=true;

  return {};
 }

auto Convert::clearFmt(bool &flag) -> TagErrorId
 {
  if( !flag ) return Error_NoFmt;

  flag=false;

  return {};
 }

bool Convert::TestSpace(StrLen str)
 {
  for(char ch : str ) if( !CharIsSpace(ch) ) return false;

  return true;
 }

Convert::Convert(PrintBase &out)
 : book(out)
 {
 }

Convert::~Convert()
 {
 }

void Convert::setId(String)
 {
 }

 // frame

auto Convert::frame(String str) -> TagErrorId
 {
  if( notOpened() && !TestSpace(Range(str)) ) return Error_NoBlock;

  return {};
 }

 // text

auto Convert::tagH1() -> TagErrorId
 {
  return open(Block_H1);
 }

auto Convert::tagH1end() -> TagErrorId
 {
  return close(Block_H1);
 }

auto Convert::tagH2() -> TagErrorId
 {
  return open(Block_H2);
 }

auto Convert::tagH2end() -> TagErrorId
 {
  return close(Block_H2);
 }

auto Convert::tagH3() -> TagErrorId
 {
  return open(Block_H3);
 }

auto Convert::tagH3end() -> TagErrorId
 {
  return close(Block_H3);
 }

auto Convert::tagH4() -> TagErrorId
 {
  return open(Block_H4);
 }

auto Convert::tagH4end() -> TagErrorId
 {
  return close(Block_H4);
 }

auto Convert::tagH5() -> TagErrorId
 {
  return open(Block_H5);
 }

auto Convert::tagH5end() -> TagErrorId
 {
  return close(Block_H5);
 }

auto Convert::tagP() -> TagErrorId
 {
  return open(Block_P);
 }

auto Convert::tagP(String) -> TagErrorId
 {
  return open(Block_P);
 }

auto Convert::tagPend() -> TagErrorId
 {
  return close(Block_P);
 }

auto Convert::tagPRE() -> TagErrorId
 {
  return open(Block_PRE);
 }

auto Convert::tagPREend() -> TagErrorId
 {
  return close(Block_PRE);
 }

 // format

auto Convert::tagB() -> TagErrorId
 {
  return setFmt(fmt_b);
 }

auto Convert::tagBend() -> TagErrorId
 {
  return clearFmt(fmt_b);
 }

auto Convert::tagI() -> TagErrorId
 {
  return setFmt(fmt_i);
 }

auto Convert::tagIend() -> TagErrorId
 {
  return clearFmt(fmt_i);
 }

auto Convert::tagU() -> TagErrorId
 {
  return setFmt(fmt_u);
 }

auto Convert::tagUend() -> TagErrorId
 {
  return clearFmt(fmt_u);
 }

auto Convert::tagSUB() -> TagErrorId
 {
  return setFmt(fmt_sub);
 }

auto Convert::tagSUBend() -> TagErrorId
 {
  return clearFmt(fmt_sub);
 }

auto Convert::tagSUP() -> TagErrorId
 {
  return setFmt(fmt_sup);
 }

auto Convert::tagSUPend() -> TagErrorId
 {
  return clearFmt(fmt_sup);
 }

auto Convert::tagSPAN(String) -> TagErrorId
 {
  return setFmt(fmt_span);
 }

auto Convert::tagSPANend() -> TagErrorId
 {
  return clearFmt(fmt_span);
 }

 // hyperlink

auto Convert::tagA(String) -> TagErrorId
 {
  return setFmt(fmt_a);
 }

auto Convert::tagA(String,String) -> TagErrorId
 {
  return setFmt(fmt_a);
 }

auto Convert::tagAend() -> TagErrorId
 {
  return clearFmt(fmt_a);
 }

 // list

auto Convert::tagOL() -> TagErrorId
 {
  return open(Block_OL);
 }

auto Convert::tagOLend() -> TagErrorId
 {
  if( item ) return Error_ItemNotClosed;

  return close(Block_OL);
 }

auto Convert::tagUL() -> TagErrorId
 {
  return open(Block_UL);
 }

auto Convert::tagULend() -> TagErrorId
 {
  if( item ) return Error_ItemNotClosed;

  return close(Block_UL);
 }

auto Convert::tagLI() -> TagErrorId
 {
  if( inList() && !item )
    {
     item=true;

     return {};
    }

  return Error_NotList;
 }

auto Convert::tagLIend() -> TagErrorId
 {
  if( inList() && item )
    {
     item=false;

     return noFormat();
    }

  return Error_NotItem;
 }

 // image

auto Convert::tagImg(String) -> TagErrorId
 {
  if( block ) return Error_InBlock;

  return {};
 }

 // complete

auto Convert::complete() -> TagErrorId
 {
  if( block ) return Error_InBlock;

  return {};
 }

} // namespace App

