/* DomConvert.cpp */
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

#include <inc/DomConvert.h>

#include <CCore/inc/CharProp.h>

namespace App {

/* class DomConvert */

StrLen DomConvert::ToString(int code)
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

auto DomConvert::noFormat() const -> TagErrorId
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

auto DomConvert::open(BlockType bt) -> TagErrorId
 {
  if( block==NoBlock )
    {
     block=bt;

     return {};
    }

  return Error_InBlock;
 }

auto DomConvert::close(BlockType bt) -> TagErrorId
 {
  if( block==bt )
    {
     block=NoBlock;

     return noFormat();
    }

  return block?Error_BlockMismatch:Error_NoBlock;
 }

auto DomConvert::setFmt(bool &flag) -> TagErrorId
 {
  if( notOpened() ) return Error_NoBlock;

  if( flag ) return Error_HasFmt;

  flag=true;

  return {};
 }

auto DomConvert::clearFmt(bool &flag) -> TagErrorId
 {
  if( !flag ) return Error_NoFmt;

  flag=false;

  return {};
 }

bool DomConvert::TestSpace(StrLen str)
 {
  for(char ch : str ) if( !CharIsSpace(ch) ) return false;

  return true;
 }

DomConvert::DomConvert()
 {
 }

DomConvert::~DomConvert()
 {
 }

 // title

void DomConvert::setTitle(String title)
 {
 }

 // id

void DomConvert::setId(String id)
 {
 }

 // frame

auto DomConvert::frame(String str) -> TagErrorId
 {
  if( notOpened() && !TestSpace(Range(str)) ) return Error_NoBlock;

  return {};
 }

 // text

auto DomConvert::tagH1() -> TagErrorId
 {
  return open(Block_H1);
 }

auto DomConvert::tagH1end() -> TagErrorId
 {
  return close(Block_H1);
 }

auto DomConvert::tagH2() -> TagErrorId
 {
  return open(Block_H2);
 }

auto DomConvert::tagH2end() -> TagErrorId
 {
  return close(Block_H2);
 }

auto DomConvert::tagH3() -> TagErrorId
 {
  return open(Block_H3);
 }

auto DomConvert::tagH3end() -> TagErrorId
 {
  return close(Block_H3);
 }

auto DomConvert::tagH4() -> TagErrorId
 {
  return open(Block_H4);
 }

auto DomConvert::tagH4end() -> TagErrorId
 {
  return close(Block_H4);
 }

auto DomConvert::tagH5() -> TagErrorId
 {
  return open(Block_H5);
 }

auto DomConvert::tagH5end() -> TagErrorId
 {
  return close(Block_H5);
 }

auto DomConvert::tagP() -> TagErrorId
 {
  return open(Block_P);
 }

auto DomConvert::tagP(String) -> TagErrorId
 {
  return open(Block_P);
 }

auto DomConvert::tagPend() -> TagErrorId
 {
  return close(Block_P);
 }

auto DomConvert::tagPRE() -> TagErrorId
 {
  return open(Block_PRE);
 }

auto DomConvert::tagPREend() -> TagErrorId
 {
  return close(Block_PRE);
 }

 // format

auto DomConvert::tagB() -> TagErrorId
 {
  return setFmt(fmt_b);
 }

auto DomConvert::tagBend() -> TagErrorId
 {
  return clearFmt(fmt_b);
 }

auto DomConvert::tagI() -> TagErrorId
 {
  return setFmt(fmt_i);
 }

auto DomConvert::tagIend() -> TagErrorId
 {
  return clearFmt(fmt_i);
 }

auto DomConvert::tagU() -> TagErrorId
 {
  return setFmt(fmt_u);
 }

auto DomConvert::tagUend() -> TagErrorId
 {
  return clearFmt(fmt_u);
 }

auto DomConvert::tagSUB() -> TagErrorId
 {
  return setFmt(fmt_sub);
 }

auto DomConvert::tagSUBend() -> TagErrorId
 {
  return clearFmt(fmt_sub);
 }

auto DomConvert::tagSUP() -> TagErrorId
 {
  return setFmt(fmt_sup);
 }

auto DomConvert::tagSUPend() -> TagErrorId
 {
  return clearFmt(fmt_sup);
 }

auto DomConvert::tagSPAN(String tclass) -> TagErrorId
 {
  return setFmt(fmt_span);
 }

auto DomConvert::tagSPANend() -> TagErrorId
 {
  return clearFmt(fmt_span);
 }

 // hyperlink

auto DomConvert::tagA(String url) -> TagErrorId
 {
  return setFmt(fmt_a);
 }

auto DomConvert::tagA(String type,String url) -> TagErrorId
 {
  return setFmt(fmt_a);
 }

auto DomConvert::tagAend() -> TagErrorId
 {
  return clearFmt(fmt_a);
 }

 // list

auto DomConvert::tagOL() -> TagErrorId
 {
  return open(Block_OL);
 }

auto DomConvert::tagOLend() -> TagErrorId
 {
  if( item ) return Error_ItemNotClosed;

  return close(Block_OL);
 }

auto DomConvert::tagUL() -> TagErrorId
 {
  return open(Block_UL);
 }

auto DomConvert::tagULend() -> TagErrorId
 {
  if( item ) return Error_ItemNotClosed;

  return close(Block_UL);
 }

auto DomConvert::tagLI() -> TagErrorId
 {
  if( inList() && !item )
    {
     item=true;

     return {};
    }

  return Error_NotList;
 }

auto DomConvert::tagLIend() -> TagErrorId
 {
  if( inList() && item )
    {
     item=false;

     return noFormat();
    }

  return Error_NotItem;
 }

 // image

auto DomConvert::tagImg(String file_name) -> TagErrorId
 {
  if( block ) return Error_InBlock;

  return {};
 }

 // complete

auto DomConvert::complete() -> TagErrorId
 {
  if( block ) return Error_InBlock;

  return {};
 }

} // namespace App



