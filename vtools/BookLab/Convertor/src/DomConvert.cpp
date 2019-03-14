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

/* enum ErrorCode */

StrLen ToString(int code)
 {
  switch( code )
    {
     case Error_NoElem : return "Element is not opened"_c;

     case Error_NotClosed : return "Element is not closed"_c;

     case Error_Top : return "Must be a top-level element"_c;

     case Error_NoTop : return "Not a top-level element"_c;

     case Error_TagMismatch : return "Open/close element tags mismatch"_c;

     case Error_NoText : return "Text is not allowed in this element"_c;

     case Error_NoFormat : return "Format tags are not allowed in this element"_c;

     case Error_HasFmt : return "Format flag is active"_c;

     case Error_NoFmt : return "Format flag is not active"_c;

     //case  : return ""_c;

     default: return "???"_c;
    }
 }

/* class Format */

void Format::prepareFmt()
 {
  if( fmt_a )
    {
     fmt="a"_c;
    }
  else if( fmt_span )
    {
     fmt=spanclass;
    }
  else
    {
     unsigned len=0;

     if( fmt_b ) temp[len++]='b';

     if( fmt_i ) temp[len++]='i';

     if( fmt_u ) temp[len++]='u';

     if( len )
       fmt=StrLen(temp,len);
     else
       fmt=Empty;
    }
 }

DomErrorId Format::setFmt(bool &flag)
 {
  if( flag ) return Error_HasFmt;

  flag=true;

  prepareFmt();

  return {};
 }

DomErrorId Format::clearFmt(bool &flag)
 {
  if( !flag ) return Error_NoFmt;

  flag=false;

  prepareFmt();

  return {};
 }

void Format::setLink(Builder &builder,StrLen str)
 {
  if( !str ) return;

  if( *str=='#' )
    {
     ++str;

     link=builder.cat("link_"_c,str);

     has_link=true;
    }
  else if( str.hasPrefix("page_"_c) )
    {
     StrLen name=str;

     for(; +name && *name!='#' ;++name);

     if( +name )
       {
        StrLen page=str.prefix(name);

        if( page.hasSuffix(".html"_c) )
          {
           page.len-=5;

           ++name;

           link=builder.cat("..#"_c,page,"#link_"_c,name);

           has_link=true;
          }
       }
     else
       {
        StrLen page=str;

        if( page.hasSuffix(".html"_c) )
          {
           page.len-=5;

           link=builder.cat("..#"_c,page,"#link"_c);

           has_link=true;
          }
       }
    }
 }

DomErrorId Format::setSPAN(Builder &builder,const String &str)
 {
  spanclass=builder.dup(str);

  return setFmt(fmt_span);
 }

DomErrorId Format::setA()
 {
  return setFmt(fmt_a);
 }

DomErrorId Format::setA(Builder &builder,const String &str)
 {
  setLink(builder,Range(str));

  return setFmt(fmt_a);
 }

DomErrorId Format::endA()
 {
  has_link=false;

  return clearFmt(fmt_a);
 }

DomErrorId Format::noFormat() const
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

} // namespace Dom

/* guard functions */

void GuardStackEmpty()
 {
  Printf(Exception,"App::Stack<...>::top() : stack is empty");
 }

/* TestSpace() */

bool TestSpace(StrLen str)
 {
  for(char ch : str ) if( !CharIsSpace(ch) ) return false;

  return true;
 }

/* class DomConvert */

template <class Elem>
void DomConvert::setId(Elem *elem)
 {
  if( Change(has_id,false) )
    {
     elem->id=builder.dup(id);

     id=Empty;
    }
 }

template <class Elem,class Func>
auto DomConvert::openBlock(Func func) -> EId
 {
  auto *elem=builder.create<Elem>();

  setId(elem);

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

template <class Func>
auto DomConvert::SetFormat(Dom::Format &format,Func func) -> EId
 {
  return func(format);
 }

template <class Func>
auto DomConvert::SetFormat(NothingType,Func) -> EId
 {
  return Dom::Error_NoFormat;
 }

template <class Func>
auto DomConvert::setFormat(Func func) ->EId
 {
  if( stack.isEmpty() ) return Dom::Error_NoElem;

  EId ret;

  stack.pop().apply( [&] (auto *elem) { ret=SetFormat(elem->refFormat(),func); } );

  return ret;
 }

template <class T>
auto DomConvert::frame(T &text,StrLen str) -> EId
 {
  return text.frame(builder,str);
 }

auto DomConvert::frame(NothingType,StrLen str) -> EId
 {
  if( TestSpace(str) ) return {};

  return Dom::Error_NoText;
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
     if( TestSpace(str) ) return {};

     return Dom::Error_NoElem;
    }

  EId ret;

  stack.top().apply( [&] (auto *elem) { ret=frame(elem->refText(),str); } );

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
  return setFormat( [] (Dom::Format &format) { return format.setB(); } );
 }

auto DomConvert::tagBend() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.endB(); } );
 }

auto DomConvert::tagI() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.setI(); } );
 }

auto DomConvert::tagIend() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.endI(); } );
 }

auto DomConvert::tagU() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.setU(); } );
 }

auto DomConvert::tagUend() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.endU(); } );
 }

auto DomConvert::tagSUB() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.setSUB(); } );
 }

auto DomConvert::tagSUBend() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.endSUB(); } );
 }

auto DomConvert::tagSUP() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.setSUP(); } );
 }

auto DomConvert::tagSUPend() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.endSUP(); } );
 }

auto DomConvert::tagSPAN(String tclass) -> EId
 {
  return setFormat( [&] (Dom::Format &format) { return format.setSPAN(builder,tclass); } );
 }

auto DomConvert::tagSPANend() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.endSPAN(); } );
 }

 // hyperlink

auto DomConvert::tagA(String url) -> EId
 {
  return setFormat( [&] (Dom::Format &format) { return format.setSPAN(builder,url); } );
 }

auto DomConvert::tagA(String,String) -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.setA(); } );
 }

auto DomConvert::tagAend() -> EId
 {
  return setFormat( [] (Dom::Format &format) { return format.endA(); } );
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
  if( stack.isEmpty() )
    {
     auto *elem=builder.create<Dom::ElemImg>();

     setId(elem);

     elem->file_name=builder.dup(file_name);

     builder.add(elem);

     return {};
    }

  return Dom::Error_NotClosed;
 }

 // complete

auto DomConvert::complete() -> EId
 {
  if( stack.isEmpty() ) return {};

  return Dom::Error_NotClosed;
 }

} // namespace App



