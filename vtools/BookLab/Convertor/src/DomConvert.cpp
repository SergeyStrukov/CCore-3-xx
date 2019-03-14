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
#include <CCore/inc/scanf/ScanTools.h>

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

     case Error_NoTop : return "Not a top-level element"_c;

     case Error_TagMismatch : return "Open/close element tags mismatch"_c;

     case Error_NoText : return "Text is not allowed in this element"_c;

     case Error_NoFormat : return "Format tags are not allowed in this element"_c;

     case Error_CannotAdd : return "Cannot add this element into those parent element"_c;

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
     if( fmt_b )
       {
        if( fmt_i )
          {
           if( fmt_u )
             fmt="biu"_c;
           else
             fmt="bi"_c;
          }
        else
          {
           if( fmt_u )
             fmt="bu"_c;
           else
             fmt="b"_c;
          }
       }
     else
       {
        if( fmt_i )
          {
           if( fmt_u )
             fmt="iu"_c;
           else
             fmt="i"_c;
          }
        else
          {
           if( fmt_u )
             fmt="u"_c;
           else
             fmt=""_c;
          }
       }
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

/* struct Span */

void AddSpan(List<Span> &spans,Builder &builder,const Format &format,StrLen str)
 {
  StrLen fmt=format.getFmt();

  if( format.hasLink() )
    {
     spans.add(builder,Span{str,fmt,format.getLink(),true});
    }
  else
    {
     spans.add(builder,Span{str,fmt});
    }
 }

/* class Text */

void Text::addSpan(Builder &builder,StrLen str)
 {
  AddSpan(spans,builder,format,str);
 }

DomErrorId Text::frame(Builder &builder,StrLen str)
 {
  for(;;)
    {
     SkipSpace(str);

     if( !str ) return {};

     StrLen next=str;

     SkipNonSpace(next);

     addSpan(builder,str.prefix(next));

     str=next;
    }
 }

DomErrorId Text::complete()
 {
  return format.noFormat();
 }

/* class Fixed */

void Fixed::provideLine(Builder &builder)
 {
  if( !cur )
    {
     cur=builder.create<Line>();

     lines.add(builder,cur);
    }
 }

void Fixed::breakLine(Builder &builder)
 {
  provideLine(builder);

  cur=0;

  provideLine(builder);
 }

void Fixed::extLine(Builder &builder,StrLen str)
 {
  provideLine(builder);

  AddSpan(cur->spans,builder,format,str);
 }

DomErrorId Fixed::frame(Builder &builder,StrLen str)
 {
  while( +str )
    {
     SplitLine split(str);

     extLine(builder,split.line);

     if( split.eol )
       {
        breakLine(builder);
        str=split.rest;
       }
     else
       {
        break;
       }
    }

  return {};
 }

DomErrorId Fixed::complete()
 {
  return format.noFormat();
 }

/* struct TListBase */

DomErrorId TListBase::add(Builder &builder,ElemLI *elem)
 {
  list.add(builder,elem);

  return {};
 }

/* struct ElemLI */

DomErrorId ElemLI::add(Builder &builder,ElemOL *elem)
 {
  Used(builder);
  Used(elem);

  return {};
 }

DomErrorId ElemLI::add(Builder &builder,ElemUL *elem)
 {
  Used(builder);
  Used(elem);

  return {};
 }

DomErrorId ElemLI::complete()
 {
  return text.complete();
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
void DomConvert::setId(Elem *)
 {
  if( Change(has_id,false) )
    {
     id=Empty;
    }
 }

template <Dom::Has_id Elem>
void DomConvert::setId(Elem *elem)
 {
  if( Change(has_id,false) )
    {
     elem->id=builder.dup(id);

     id=Empty;
    }
 }

template <class Elem,class Func>
auto DomConvert::openElem(Func func) -> EId
 {
  auto *elem=builder.create<Elem>();

  setId(elem);

  func(elem);

  stack.push(elem);

  return {};
 }

template <class Base,class Elem>
auto DomConvert::addElem(Base *,Elem *) -> EId
 {
  return Dom::Error_CannotAdd;
 }

template <class Base,Dom::CanAdd<Base> Elem>
auto DomConvert::addElem(Base *base,Elem *elem) -> EId
 {
  return base->add(builder,elem);
 }

template <class Elem>
auto DomConvert::closeElem() -> EId
 {
  if( stack.isEmpty() ) return Dom::Error_NoElem;

  auto *elem=stack.pop().castPtr<Elem>();

  if( !elem ) return Dom::Error_TagMismatch;

  if( stack.isEmpty() )
    {
     Dom::TopPtr ptr;

     if( TrySetAnyPtr(ptr,elem) )
       {
        EId ret=elem->complete();

        builder.add(ptr);

        return ret;
       }
     else
       {
        return Dom::Error_NoTop;
       }
    }
  else
    {
     EId ret;

     stack.top().apply( [&] (auto *base) { ret=addElem(base,elem); } );

     return ret;
    }
 }

template <class Elem,class Func>
auto DomConvert::SetFormat(Elem *,Func) -> EId
 {
  return Dom::Error_NoFormat;
 }

template <Dom::Has_refFormat Elem,class Func>
auto DomConvert::SetFormat(Elem *elem,Func func) -> EId
 {
  return func(elem->refFormat());
 }

template <class Func>
auto DomConvert::setFormat(Func func) ->EId
 {
  if( stack.isEmpty() ) return Dom::Error_NoElem;

  EId ret;

  stack.top().apply( [&] (auto *elem) { ret=SetFormat(elem,func); } );

  return ret;
 }

template <class Elem>
auto DomConvert::frame(Elem *,StrLen str) -> EId
 {
  if( TestSpace(str) ) return {};

  return Dom::Error_NoText;
 }

template <Dom::Has_frame Elem>
auto DomConvert::frame(Elem *elem,StrLen str) -> EId
 {
  return elem->frame(builder,str);
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

  stack.top().apply( [&] (auto *elem) { ret=frame(elem,str); } );

  return ret;
 }

 // text

auto DomConvert::tagH1() -> EId
 {
  return openElem<Dom::ElemH1>();
 }

auto DomConvert::tagH1end() -> EId
 {
  return closeElem<Dom::ElemH1>();
 }

auto DomConvert::tagH2() -> EId
 {
  return openElem<Dom::ElemH2>();
 }

auto DomConvert::tagH2end() -> EId
 {
  return closeElem<Dom::ElemH2>();
 }

auto DomConvert::tagH3() -> EId
 {
  return openElem<Dom::ElemH3>();
 }

auto DomConvert::tagH3end() -> EId
 {
  return closeElem<Dom::ElemH3>();
 }

auto DomConvert::tagH4() -> EId
 {
  return openElem<Dom::ElemH4>();
 }

auto DomConvert::tagH4end() -> EId
 {
  return closeElem<Dom::ElemH4>();
 }

auto DomConvert::tagH5() -> EId
 {
  return openElem<Dom::ElemH5>();
 }

auto DomConvert::tagH5end() -> EId
 {
  return closeElem<Dom::ElemH5>();
 }

auto DomConvert::tagP() -> EId
 {
  return openElem<Dom::ElemP>();
 }

auto DomConvert::tagP(String elem_class) -> EId
 {
  auto str=builder.dup(elem_class);

  return openElem<Dom::ElemP>( [=] (Dom::ElemP *elem) { elem->elem_class=str; } );
 }

auto DomConvert::tagPend() -> EId
 {
  return closeElem<Dom::ElemP>();
 }

auto DomConvert::tagPRE() -> EId
 {
  return openElem<Dom::ElemPRE>();
 }

auto DomConvert::tagPREend() -> EId
 {
  return closeElem<Dom::ElemPRE>();
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
  return setFormat( [&] (Dom::Format &format) { return format.setA(builder,url); } );
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
  return openElem<Dom::ElemOL>();
 }

auto DomConvert::tagOLend() -> EId
 {
  return closeElem<Dom::ElemOL>();
 }

auto DomConvert::tagUL() -> EId
 {
  return openElem<Dom::ElemUL>();
 }

auto DomConvert::tagULend() -> EId
 {
  return closeElem<Dom::ElemUL>();
 }

auto DomConvert::tagLI() -> EId
 {
  return openElem<Dom::ElemLI>();
 }

auto DomConvert::tagLIend() -> EId
 {
  return closeElem<Dom::ElemLI>();
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



