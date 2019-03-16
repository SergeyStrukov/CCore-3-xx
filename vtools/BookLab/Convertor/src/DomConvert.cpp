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

#include <CCore/inc/scanf/ScanTools.h>
#include <CCore/inc/Path.h>

#include <CCore/inc/Exception.h>

namespace App {

/* namespace Dom */

namespace Dom {

/* IsSpace() */

bool IsSpace(StrLen str)
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

template <class Func>
void Format::setLink(Builder &builder,StrLen str,Func func)
 {
  if( !str ) return;

  SkipPrefix(str,"html/"_c);

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

        if( SkipSuffix(page,".html"_c) )
          {
           ++name;

           link=builder.cat("..#"_c,page,"#link_"_c,name);

           has_link=true;
          }
       }
     else
       {
        StrLen page=str;

        if( SkipSuffix(page,".html"_c) )
          {
           func(page);

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

template <class Func>
DomErrorId Format::setA(Builder &builder,const String &str,Func func)
 {
  setLink(builder,Range(str),func);

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
  str=builder.dup(str);

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

template <class Kind>
void PrintSpanList(PrintBase &out,Kind kind,const List<Span> &spans)
 {
  Printf(out,"{\n");

  spans.apply( [&] (ulen ind,const Span &span)
                   {
                    out.put(' ');

                    if( ind ) out.put(','); else out.put(' ');

                    span.printKind(out,kind);

                    out.put('\n');

                   } );

  Printf(out,"}");
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

template <class Kind>
void Text::printKind(PrintBase &out,Kind kind) const
 {
  PrintSpanList(out,kind,spans);
 }

/* struct Line */

template <class Kind>
void Line::printKind(PrintBase &out,Kind kind) const
 {
  PrintSpanList(out,kind,spans);
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

template <class Kind>
void Fixed::printKind(PrintBase &out,Kind kind) const
 {
  Printf(out,"{\n");

  lines.apply( [&] (ulen ind,Line *line)
                   {
                    if( ind )
                      {
                       out.put(',');
                       out.put('\n');
                      }

                    line->printKind(out,kind);

                    out.put('\n');

                   } );

  Printf(out,"}");
 }

/* struct TextBase */

template <class Kind>
void TextBase::printKind(PrintBase &out,Kind kind) const
 {
  Putobj(out,"{ "_c);

  text.printKind(out,kind);

  Printf(out," , & fmt_#; , & align_#; }",kind,kind);
 }

/* struct ElemPRE */

template <class Kind>
void ElemPRE::printKind(PrintBase &out,Kind kind) const
 {
  Putobj(out,"{ "_c);

  text.printKind(out,kind);

  Printf(out," , & fmt_#; }",kind);
 }

/* struct ElemOL */

template <class Kind>
void ElemOL::PrintItem(PrintBook &book,Text *text,Kind kind,ulen &)
 {
  auto name=book.addExt(text,kind);

  book.printf("{ '' , { { & #; , null , ItemInner , ItemOuter } } }",name);
 }

template <class Kind>
void ElemOL::PrintItem(PrintBook &book,ElemLI *elem,Kind kind,ulen &bullet)
 {
  book.printf("{ '#;.' , ",bullet++);

  elem->printKind(book,kind);

  book.putobj(" }"_c);
 }

template <class Kind>
void ElemOL::printKind(PrintBook &book,Kind kind) const
 {
  book.putobj("{ {\n"_c);

  ulen bullet=1;

  apply( [&] (ulen ind,auto aptr)
             {
              book.put(' ');

              if( ind ) book.put(','); else book.put(' ');

              aptr.apply( [&] (auto *ptr) { PrintItem(book,ptr,kind,bullet); } );

              book.put('\n');

             } );

  book.putobj("} }"_c);
 }

/* struct ElemUL */

template <class Kind>
void ElemUL::PrintItem(PrintBook &book,Text *text,Kind kind)
 {
  auto name=book.addExt(text,kind);

  book.printf("{ '' , { { & #; , null , ItemInner , ItemOuter } } }",name);
 }

template <class Kind>
void ElemUL::PrintItem(PrintBook &book,ElemLI *elem,Kind kind)
 {
  book.putobj("{ '•' , "_c);

  elem->printKind(book,kind);

  book.putobj(" }"_c);
 }

template <class Kind>
void ElemUL::printKind(PrintBook &book,Kind kind) const
 {
  book.putobj("{ {\n"_c);

  apply( [&] (ulen ind,auto aptr)
             {
              book.put(' ');

              if( ind ) book.put(','); else book.put(' ');

              aptr.apply( [&] (auto *ptr) { PrintItem(book,ptr,kind); } );

              book.put('\n');

             } );

  book.putobj("} }"_c);
 }

/* struct ElemLI */

template <class Kind>
void ElemLI::PrintItem(PrintBook &book,Text *text,Kind kind)
 {
  auto name=book.addExt(text,kind);

  book.printf("{ & #; , null , ItemInner , ItemOuter }",name);
 }

template <class Elem,class Kind>
void ElemLI::PrintItem(PrintBook &book,Elem *elem,Kind)
 {
  auto name=book.addExt(elem,elem->getKind());

  book.printf("{ & #; , null , ItemInner , ItemOuter }",name);
 }

template <class Kind>
void ElemLI::printKind(PrintBook &book,Kind kind) const
 {
  book.putobj("{\n"_c);

  apply( [&] (ulen ind,auto aptr)
             {
              book.put(' ');

              if( ind ) book.put(','); else book.put(' ');

              aptr.apply( [&] (auto *ptr) { PrintItem(book,ptr,kind); } );

              book.put('\n');

             } );

  book.putobj("}"_c);
 }

/* struct ElemImg */

void ElemImg::print(PrintBase &out) const
 {
  SplitFullExt split(file_name);

  Printf(out,"{ \"#;.zipmap\" }",PrintText(split.name));
 }

/* class PrintBook */

template <class Elem>
void PrintBook::print(ulen ind,Elem *elem)
 {
  StrLen type=elem->getType();
  StrLen id=elem->id;

  Printf(out,"#; b#; = #; ;\n\n",type,ind,*elem);

  if( +id )
    Printf(out,"Link link_#; = { & page , { #; } } ;\n\n",id,ind);
 }

template <ExtPrint Elem>
void PrintBook::print(ulen ind,Elem *elem)
 {
  StrLen type=elem->getType();
  StrLen id=elem->id;

  Printf(out,"#; b#; = ",type,ind);

  elem->print(*this);

  Putobj(out," ;\n\n"_c);

  if( +id )
    Printf(out,"Link link_#; = { & page , { #; } } ;\n\n",id,ind);
 }

template <class Elem,class Kind>
void PrintBook::addRec(ExtName name,Elem *elem,Kind kind)
 {
  defer_list.insLast( OwnPtr<RecBase>(new Rec<Elem,Kind>(name,elem,kind)) );
 }

void PrintBook::process(RecBase *rec)
 {
  rec->print(*this);
 }

template <class Kind>
void PrintBook::print(ExtName name,Text *text,Kind kind)
 {
  Printf(out,"Text #; = ",name);

  Putobj(out,"{ "_c);

  text->printKind(out,kind);

  Printf(out," , & fmt_#; , & align_#; }",kind,kind);

  Putobj(out," ;\n\n"_c);
 }

template <class Elem,class Kind>
void PrintBook::print(ExtName name,Elem *elem,Kind kind)
 {
  StrLen type=elem->getType();

  Printf(out,"#; #; = ",type,name);

  elem->printKind(out,kind);

  Putobj(out," ;\n\n"_c);
 }

template <ExtPrint Elem,class Kind>
void PrintBook::print(ExtName name,Elem *elem,Kind kind)
 {
  StrLen type=elem->getType();

  Printf(out,"#; #; = ",type,name);

  elem->printKind(*this,kind);

  Putobj(out," ;\n\n"_c);
 }

template <class Elem,class Kind>
ExtName PrintBook::addExt(Elem *elem,Kind kind)
 {
  ExtName name=getExtName();

  addRec(name,elem,kind);

  return name;
 }

void PrintBook::pump()
 {
  for(; +defer_list ;defer_list.delFirst())
    {
     process(defer_list.getFirst()->getPtr());
    }
 }

void PrintBook::print(ulen ind,TopPtr aptr)
 {
  aptr.apply( [&] (auto *elem) { print(ind,elem); } );

  pump();
 }

/* class Builder */

void Builder::print(PrintBase &out,PageParam param) const
 {
  Printf(out,"scope #; {\n\n",param.name);

  PrintBook book(out);

  elems.apply( [&] (ulen ind,TopPtr aptr) { book.print(ind,aptr); } );

  Printf(out,"Page page = { \"#;\" ,\n{\n",PrintText(title));

  elems.apply( [&] (ulen ind,TopPtr aptr)
                   {
                    out.put(' ');

                    if( ind ) out.put(','); else out.put(' ');

                    aptr.apply( [&] (auto *ptr)
                                    {
                                     auto kind=ptr->getKind();

                                     Printf(out,"{ & b#; , null , inner_#; , outer_#; , back_#; }\n",ind,kind,kind,kind);

                                    } );

                   } );

  Printf(out,"} , NoColor , NoColor , #; , #; , #; };\n\n",PrintPtr(param.up),PrintPtr(param.prev),PrintPtr(param.next));

  Putobj(out,"Link link = { &page } ;\n\n"_c);

  Putobj(out,"}\n\n"_c);
 }

} // namespace Dom

/* guard functions */

void GuardStackEmpty()
 {
  Printf(Exception,"App::Stack<...>::top() : stack is empty");
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
auto DomConvert::setFormat(Elem *,Func) -> EId
 {
  return Dom::Error_NoFormat;
 }

template <Dom::Has_refFormat Elem,class Func>
auto DomConvert::setFormat(Elem *elem,Func func) -> EId
 {
  return func(elem->refFormat(builder));
 }

template <class Func>
auto DomConvert::setFormat(Func func) ->EId
 {
  if( stack.isEmpty() ) return Dom::Error_NoElem;

  EId ret;

  stack.top().apply( [&] (auto *elem) { ret=setFormat(elem,func); } );

  return ret;
 }

template <class Elem>
auto DomConvert::frame(Elem *,StrLen str) -> EId
 {
  if( Dom::IsSpace(str) ) return {};

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
     if( Dom::IsSpace(str) ) return {};

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

  return openElem<Dom::ElemP>( [=] (Dom::ElemP *elem) { elem->kind.set(str); } );
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
  return setFormat( [&] (Dom::Format &format)
                        {
                         return format.setA(builder,url, [&] (StrLen page) { page_list.append_fill(page); } );

                        } );
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



