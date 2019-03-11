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

#include <CCore/inc/scanf/ScanTools.h>

namespace App {

namespace Private_Convert {

/* class PrintPtr */

class PrintPtr
 {
   StrLen str;

  public:

   explicit PrintPtr(const String &str_) : str(Range(str_)) {}

   void print(PrinterType &out) const
    {
     if( !str )
       {
        Putobj(out,"null"_c);
       }
     else
       {
        Printf(out,"& #;",str);
       }
    }
 };

/* class PrintSpan */

class PrintSpan
 {
   StrLen str;

  private:

   static void PrintAmp(PrinterType &out,StrLen text)
    {
     if( text.equal("lt"_c) )
       {
        out.put('<');

        return;
       }

     if( text.equal("gt"_c) )
       {
        out.put('>');

        return;
       }

     if( text.equal("amp"_c) )
       {
        out.put('&');

        return;
       }

     out.put('$');
    }

   static void PrintChar(PrinterType &out,StrLen &text)
    {
     char ch=*text;

     ++text;

     if( ch=='&' )
       {
        StrLen next=text;

        for(; +next && *next!=';' ;++next);

        if( !next )
          {
           out.put('$');

           text=Empty;
          }
        else
          {
           PrintAmp(out,text.prefix(next));

           ++next;

           text=next;
          }
       }
     else
       {
        if( CharIsSpecial(ch) )
          {
           out.put('$');
          }
        else
          {
           if( ch!='"' )
             {
              out.put(ch);
             }
           else
             {
              out.put('\\');
              out.put('"');
             }
          }
       }
    }

  public:

   explicit PrintSpan(StrLen str_) : str(str_) {}

   void print(PrinterType &out) const
    {
     out.put('\"');

     for(StrLen text=str; +text ;) PrintChar(out,text);

     out.put('\"');
    }
 };

} // namespace Private_Convert

using namespace Private_Convert;

/* class Book */

void Book::addSpan(StrLen str)
 {
  if( spanind ) out.put(',');

  Printf(out,"{ #; }\n",PrintSpan(str));

  spanind++;
 }

Book::Book(PrintBase &out_,const PageParam &param_)
 : out(out_),param(param_)
 {
 }

Book::~Book()
 {
  Printf(out,"Page page = { #.q; ,\n{\n",param.name);

  ulen ind = 0 ;

  frames.apply( [&] (const Frame &frame)
                    {
                     out.put(' ');

                     if( ind ) out.put(',');

                     Printf(out,"{ &b#; , null , inner_#; , outer_#; , back_#; }\n",ind,frame.kind,frame.kind,frame.kind);

                     ind++;

                    } );

  Printf(out,"} , NoColor , NoColor , #; , #; , #; };\n\n",PrintPtr(param.up),PrintPtr(param.prev),PrintPtr(param.next));
 }

 // text

void Book::openText(StrLen kind)
 {
  ulen ind=frames.getCount();

  frames.insLast(kind);

  Printf(out,"Text b#; = { {\n",ind);

  this->kind=kind;

  spanind=0;
 }

void Book::addText(StrLen frame)
 {
  for(;;)
    {
     SkipSpace(frame);

     if( !frame ) return;

     StrLen next=frame;

     SkipNonSpace(next);

     addSpan(frame.prefix(next));

     frame=next;
    }
 }

void Book::closeText()
 {
  Printf(out,"} , &fmt_#; , &align_#; } ;\n\n",kind,kind);
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

auto Convert::openText(BlockType bt,StrLen kind) -> TagErrorId
 {
  if( block==NoBlock )
    {
     block=bt;

     book.openText(kind);

     return {};
    }

  return Error_InBlock;
 }

auto Convert::closeText(BlockType bt) -> TagErrorId
 {
  if( block==bt )
    {
     block=NoBlock;

     book.closeText();

     return noFormat();
    }

  return block?Error_BlockMismatch:Error_NoBlock;
 }

Convert::Convert(PrintBase &out,const PageParam &param)
 : book(out,param)
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

  if( block==Block_P )
    {
     book.addText(Range(str));
    }

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
  return openText(Block_P,"text"_c);
 }

auto Convert::tagP(String) -> TagErrorId
 {
  return openText(Block_P,"text"_c);
 }

auto Convert::tagPend() -> TagErrorId
 {
  return closeText(Block_P);
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

