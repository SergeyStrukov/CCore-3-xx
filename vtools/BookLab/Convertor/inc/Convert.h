/* Convert.h */
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

#ifndef App_Convert_h
#define App_Convert_h

#include <inc/ErrorId.h>

#include <CCore/inc/String.h>
#include <CCore/inc/CompactList.h>

namespace App {

/* classes */

struct PageParam;

class Book;

class Convert;

class IndexConvert;

/* struct PageParam */

struct PageParam
 {
  String name;
  String up;
  String prev;
  String next;
 };

/* class Book */

class Book : NoCopy
 {
   PrintBase &out;
   PageParam param;
   String title;

   struct Frame
    {
     String kind;

     explicit Frame(const String &kind_) : kind(kind_) {}
    };

   CompactList2<Frame> frames;

   String kind;
   ulen spanind = 0 ;
   ulen lineind = 0 ;

   ulen listind = 0 ;
   ulen itemind = 0 ;

   String id;
   bool has_id = false ;

   String link;
   bool has_link = false ;

  private:

   void addSpan(StrLen str,StrLen fmt);

   ulen insFrame(const String &kind);

  private:

   void openLine();

   void extLine(StrLen line,StrLen fmt);

   void breakLine();

   void closeLine();

  public:

   Book(PrintBase &out,const PageParam &param);

   ~Book();

   // title

   void setTitle(const String &str);

   // text

   void openText(const String &kind);

   void addText(StrLen frame,StrLen fmt);

   void closeText();

   // fixed

   void openFixed(const String &kind);

   void addFixed(StrLen frame,StrLen fmt);

   void closeFixed();

   // list

   void openUList(const String &kind);

   void closeUList();

   void openOList(const String &kind);

   void closeOList();

   void openItem();

   void closeItem();

   // image

   void insImage(const String &kind,StrLen file_name);

   // links

   void setId(const String &id);

   void setLink(const String &url);

   void clearLink();
 };

/* class Convert */

class Convert : NoCopy
 {
   Book book;

  public:

   enum ErrorCode
    {
     Error_NoBlock = 1,
     Error_BlockMismatch,
     Error_InBlock,
     Error_NotList,
     Error_NotItem,
     Error_ItemNotClosed,

     Error_HasFmt,
     Error_NoFmt
    };

   static StrLen ToString(int code);

   class TagErrorId : public ErrorId
    {
     public:

      TagErrorId() {}

      TagErrorId(ErrorCode code) : ErrorId(code,ToString) {}
    };

  private:

   String title;

   enum BlockType
    {
     NoBlock = 0,

     Block_H1,
     Block_H2,
     Block_H3,
     Block_H4,
     Block_H5,
     Block_P,

     Block_PRE,

     Block_OL,
     Block_UL
    };

   BlockType block = NoBlock ;
   bool item = false ;

   bool fmt_b = false ;
   bool fmt_i = false ;
   bool fmt_u = false ;
   bool fmt_sub = false ;
   bool fmt_sup = false ;

   bool fmt_span = false ;
   String spanclass;

   bool fmt_a = false ;

   String fmt;

  private:

   bool inList() const { return block>=Block_OL ; }

   bool notOpened() const { return !block || ( inList() && !item ) ; }

   bool inText() const { return ( block>=Block_H1 && block<=Block_P ) || item ; }

   bool inFixed() const { return block==Block_PRE; }

   TagErrorId noFormat() const;

   TagErrorId setFmt(bool &flag);

   TagErrorId clearFmt(bool &flag);

   static bool TestSpace(StrLen str);

  private:

   void prepareFmt();

   StrLen getFmt() const;

   TagErrorId openText(BlockType bt,const String &kind);

   TagErrorId closeText(BlockType bt);

  public:

   Convert(PrintBase &out,const PageParam &param);

   ~Convert();

   // title

   const String & getTitle() const { return title; }

   void setTitle(String str);

   // id

   void setId(String id);

   // frame

   TagErrorId frame(String str);

   // text

   TagErrorId tagH1();

   TagErrorId tagH1end();

   TagErrorId tagH2();

   TagErrorId tagH2end();

   TagErrorId tagH3();

   TagErrorId tagH3end();

   TagErrorId tagH4();

   TagErrorId tagH4end();

   TagErrorId tagH5();

   TagErrorId tagH5end();

   TagErrorId tagP();

   TagErrorId tagP(String tclass);

   TagErrorId tagPend();

   TagErrorId tagPRE();

   TagErrorId tagPREend();

   // format

   TagErrorId tagB();

   TagErrorId tagBend();

   TagErrorId tagI();

   TagErrorId tagIend();

   TagErrorId tagU();

   TagErrorId tagUend();

   TagErrorId tagSUB();

   TagErrorId tagSUBend();

   TagErrorId tagSUP();

   TagErrorId tagSUPend();

   TagErrorId tagSPAN(String tclass);

   TagErrorId tagSPANend();

   // hyperlink

   TagErrorId tagA(String url);

   TagErrorId tagA(String type,String url);

   TagErrorId tagAend();

   // list

   TagErrorId tagOL();

   TagErrorId tagOLend();

   TagErrorId tagUL();

   TagErrorId tagULend();

   TagErrorId tagLI();

   TagErrorId tagLIend();

   // image

   TagErrorId tagImg(String file_name);

   // complete

   TagErrorId complete();
 };

/* class IndexConvert */

class IndexConvert : NoCopy
 {
   Book book;

  public:

   enum ErrorCode
    {
     Error_NoBlock = 1,
     Error_BlockMismatch,
     Error_InBlock,
     Error_NotList,
     Error_NotItem,
     Error_ItemNotClosed,

     Error_HasFmt,
     Error_NoFmt
    };

   static StrLen ToString(int code);

   class TagErrorId : public ErrorId
    {
     public:

      TagErrorId() {}

      TagErrorId(ErrorCode code) : ErrorId(code,ToString) {}
    };

  private:

   enum BlockType
    {
     NoBlock = 0,

     Block_H1,
     Block_H2,
     Block_H3,
     Block_H4,
     Block_H5,
     Block_P,

     Block_PRE,

     Block_OL,
     Block_UL
    };

   BlockType block = NoBlock ;
   bool item = false ;

   bool fmt_b = false ;
   bool fmt_i = false ;
   bool fmt_u = false ;
   bool fmt_sub = false ;
   bool fmt_sup = false ;

   bool fmt_span = false ;
   String spanclass;

   bool fmt_a = false ;

   String fmt;

  private:

   bool inList() const { return block>=Block_OL ; }

   bool notOpened() const { return !block || ( inList() && !item ) ; }

   bool inText() const { return ( block>=Block_H1 && block<=Block_P ) || item ; }

   bool inFixed() const { return block==Block_PRE; }

   TagErrorId noFormat() const;

   TagErrorId setFmt(bool &flag);

   TagErrorId clearFmt(bool &flag);

   static bool TestSpace(StrLen str);

  private:

   void prepareFmt();

   StrLen getFmt() const;

   TagErrorId openText(BlockType bt,const String &kind);

   TagErrorId closeText(BlockType bt);

  public:

   IndexConvert(PrintBase &out,const PageParam &param);

   ~IndexConvert();

   // title

   void setTitle(String str);

   // id

   void setId(String id);

   // frame

   TagErrorId frame(String str);

   // text

   TagErrorId tagH1();

   TagErrorId tagH1end();

   TagErrorId tagH2();

   TagErrorId tagH2end();

   TagErrorId tagH3();

   TagErrorId tagH3end();

   TagErrorId tagH4();

   TagErrorId tagH4end();

   TagErrorId tagH5();

   TagErrorId tagH5end();

   TagErrorId tagP();

   TagErrorId tagP(String tclass);

   TagErrorId tagPend();

   TagErrorId tagPRE();

   TagErrorId tagPREend();

   // format

   TagErrorId tagB();

   TagErrorId tagBend();

   TagErrorId tagI();

   TagErrorId tagIend();

   TagErrorId tagU();

   TagErrorId tagUend();

   TagErrorId tagSUB();

   TagErrorId tagSUBend();

   TagErrorId tagSUP();

   TagErrorId tagSUPend();

   TagErrorId tagSPAN(String tclass);

   TagErrorId tagSPANend();

   // hyperlink

   TagErrorId tagA(String url);

   TagErrorId tagA(String type,String url);

   TagErrorId tagAend();

   // list

   TagErrorId tagOL();

   TagErrorId tagOLend();

   TagErrorId tagUL();

   TagErrorId tagULend();

   TagErrorId tagLI();

   TagErrorId tagLIend();

   // image

   TagErrorId tagImg(String file_name);

   // complete

   TagErrorId complete();
 };

} // namespace App

#endif

