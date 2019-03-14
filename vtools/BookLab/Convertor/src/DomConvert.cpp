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

#include <CCore/inc/Exception.h>

namespace App {

/* namespace Dom */

namespace Dom {

/* TestSpace() */

bool TestSpace(StrLen str)
 {
  for(char ch : str ) if( !CharIsSpace(ch) ) return false;

  return true;
 }

/* enum ErrorCode */

StrLen ToString(int code)
 {
  switch( code )
    {
     case Error_NoElem : return "Element is not opened"_c;

     case Error_Top : return "Must be a top-level element"_c;

     case Error_NoTop : return "Not a top-level element"_c;

     case Error_TagMismatch : return "Open/close element tags mismatch"_c;

     case Error_NoText : return "Text is not allowed in this element"_c;

     //case  : return ""_c;

     default: return "???"_c;
    }
 }

} // namespace Dom

/* guard functions */

void GuardStackEmpty()
 {
  Printf(Exception,"App::Stack<...>::top() : stack is empty");
 }

/* class DomConvert */

template <class Elem,class Func>
auto DomConvert::openBlock(Func func) -> EId
 {
  auto *elem=builder.create<Elem>();

  if( Change(has_id,false) )
    {
     elem->id=builder.dup(id);

     id=Empty;
    }

  func(elem);

  stack.push(elem);

  return {};
 }

template <class Elem>
auto DomConvert::closeBlock() -> EId
 {
  if( stack.isEmpty() ) return Dom::Error_NoElem;

  auto ptr=stack.pop();

  if( stack.isEmpty() )
    {
     auto *elem=ptr.castPtr<Elem>();

     if( !elem ) return Dom::Error_TagMismatch;

     Dom::BlockPtr bptr;

     if( TrySetAnyPtr(bptr,elem) )
       {
        EId ret=elem->complete();

        builder.add(bptr);

        return ret;
       }
     else
       {
        return Dom::Error_NoTop;
       }
    }
  else
    {
     return Dom::Error_Top;
    }
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
  builder.setTitle(builder.dup(title));
 }

 // id

void DomConvert::setId(String id_)
 {
  id=id_;
  has_id=true;
 }

 // frame

auto DomConvert::frame(String str_) -> EId
 {
  StrLen str=Range(str_);

  if( stack.isEmpty() )
    {
     if( Dom::TestSpace(str) ) return {};

     return Dom::Error_NoElem;
    }

  EId ret;

  stack.top().apply( [&] (auto *elem) { ret=elem->frame(builder,str); } );

  return ret;
 }

 // text

auto DomConvert::tagH1() -> EId
 {
  return openBlock<Dom::ElemH1>();
 }

auto DomConvert::tagH1end() -> EId
 {
  return closeBlock<Dom::ElemH1>();
 }

auto DomConvert::tagH2() -> EId
 {
  return openBlock<Dom::ElemH2>();
 }

auto DomConvert::tagH2end() -> EId
 {
  return closeBlock<Dom::ElemH2>();
 }

auto DomConvert::tagH3() -> EId
 {
  return openBlock<Dom::ElemH3>();
 }

auto DomConvert::tagH3end() -> EId
 {
  return closeBlock<Dom::ElemH3>();
 }

auto DomConvert::tagH4() -> EId
 {
  return openBlock<Dom::ElemH4>();
 }

auto DomConvert::tagH4end() -> EId
 {
  return closeBlock<Dom::ElemH4>();
 }

auto DomConvert::tagH5() -> EId
 {
  return openBlock<Dom::ElemH5>();
 }

auto DomConvert::tagH5end() -> EId
 {
  return closeBlock<Dom::ElemH5>();
 }

auto DomConvert::tagP() -> EId
 {
  return openBlock<Dom::ElemP>();
 }

auto DomConvert::tagP(String elem_class) -> EId
 {
  auto str=builder.dup(elem_class);

  return openBlock<Dom::ElemP>( [=] (Dom::ElemP *elem) { elem->elem_class=str; } );
 }

auto DomConvert::tagPend() -> EId
 {
  return closeBlock<Dom::ElemP>();
 }

auto DomConvert::tagPRE() -> EId
 {
  return openBlock<Dom::ElemPRE>();
 }

auto DomConvert::tagPREend() -> EId
 {
  return closeBlock<Dom::ElemPRE>();
 }

 // format

auto DomConvert::tagB() -> EId
 {
  return setFmt(fmt_b);
 }

auto DomConvert::tagBend() -> EId
 {
  return clearFmt(fmt_b);
 }

auto DomConvert::tagI() -> EId
 {
  return setFmt(fmt_i);
 }

auto DomConvert::tagIend() -> EId
 {
  return clearFmt(fmt_i);
 }

auto DomConvert::tagU() -> EId
 {
  return setFmt(fmt_u);
 }

auto DomConvert::tagUend() -> EId
 {
  return clearFmt(fmt_u);
 }

auto DomConvert::tagSUB() -> EId
 {
  return setFmt(fmt_sub);
 }

auto DomConvert::tagSUBend() -> EId
 {
  return clearFmt(fmt_sub);
 }

auto DomConvert::tagSUP() -> EId
 {
  return setFmt(fmt_sup);
 }

auto DomConvert::tagSUPend() -> EId
 {
  return clearFmt(fmt_sup);
 }

auto DomConvert::tagSPAN(String tclass) -> EId
 {
  return setFmt(fmt_span);
 }

auto DomConvert::tagSPANend() -> EId
 {
  return clearFmt(fmt_span);
 }

 // hyperlink

auto DomConvert::tagA(String url) -> EId
 {
  return setFmt(fmt_a);
 }

auto DomConvert::tagA(String type,String url) -> EId
 {
  return setFmt(fmt_a);
 }

auto DomConvert::tagAend() -> EId
 {
  return clearFmt(fmt_a);
 }

 // list

auto DomConvert::tagOL() -> EId
 {
  return open(Block_OL);
 }

auto DomConvert::tagOLend() -> EId
 {
  if( item ) return Error_ItemNotClosed;

  return close(Block_OL);
 }

auto DomConvert::tagUL() -> EId
 {
  return open(Block_UL);
 }

auto DomConvert::tagULend() -> EId
 {
  if( item ) return Error_ItemNotClosed;

  return close(Block_UL);
 }

auto DomConvert::tagLI() -> EId
 {
  if( inList() && !item )
    {
     item=true;

     return {};
    }

  return Error_NotList;
 }

auto DomConvert::tagLIend() -> EId
 {
  if( inList() && item )
    {
     item=false;

     return noFormat();
    }

  return Error_NotItem;
 }

 // image

auto DomConvert::tagImg(String file_name) -> EId
 {
  if( block ) return Error_InBlock;

  return {};
 }

 // complete

auto DomConvert::complete() -> EId
 {
  if( block ) return Error_InBlock;

  return {};
 }

} // namespace App



