/* DomConvert.h */
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

#ifndef App_DomConvert_h
#define App_DomConvert_h

#include <inc/ErrorId.h>

#include <CCore/inc/String.h>
#include <CCore/inc/AnyPtr.h>
#include <CCore/inc/List.h>
#include <CCore/inc/ElementPool.h>

namespace App {

/* namespace Dom */

namespace Dom {

/* classes */

template <class T> class List;

class Text;

class Fixed;

class TList;

struct ElemH1;

struct ElemH2;

struct ElemH3;

struct ElemH4;

struct ElemH5;

struct ElemP;

struct ElemPRE;

struct ElemOL;

struct ElemUL;

struct ElemLI;

struct ElemImg;

class Builder;

/* class List<T> */

template <class T>
class List : NoCopy
 {
   struct Node : NoCopy
    {
     SLink<Node> link;

     T obj;

     explicit Node(const T &obj_) : obj(obj_) {}
    };

   using Algo = typename SLink<Node>::template LinearAlgo<&Node::link> ;

   typename Algo::FirstLast list;

  public:

   List() {}

   void add(ElementPool &pool,const T &obj)
    {
     Node *node=pool.create<Node>(obj);

     list.ins_last(node);
    }
 };

/* class Text */

class Text : NoCopy // TODO
 {
 };

/* class Fixed */

class Fixed : NoCopy // TODO
 {
 };

/* class TList */

class TList : NoCopy // TODO
 {
 };

/* struct ElemH1 */

struct ElemH1 : NoCopy
 {
  StrLen id;
  Text text;
 };

/* struct ElemH2 */

struct ElemH2 : NoCopy
 {
  StrLen id;
  Text text;
 };

/* struct ElemH3 */

struct ElemH3 : NoCopy
 {
  StrLen id;
  Text text;
 };

/* struct ElemH4 */

struct ElemH4 : NoCopy
 {
  StrLen id;
  Text text;
 };

/* struct ElemH5 */

struct ElemH5 : NoCopy
 {
  StrLen id;
  Text text;
 };

/* struct ElemP */

struct ElemP : NoCopy
 {
  StrLen id;
  StrLen elem_class;
  Text text;
 };

/* struct ElemPRE */

struct ElemPRE : NoCopy
 {
  StrLen id;
  Text text;
 };

/* struct ElemOL */

struct ElemOL : NoCopy
 {
  StrLen id;
  TList list;
 };

/* struct ElemUL */

struct ElemUL : NoCopy
 {
  StrLen id;
  TList list;
 };

/* struct ElemLI */

struct ElemLI : NoCopy // TODO
 {
 };

/* struct ElemImg */

struct ElemImg : NoCopy
 {
  StrLen id;
  StrLen file_name;
 };

/* class Builder */

using BlockPtr = AnyPtr<ElemH1,ElemH2,ElemH3,ElemH4,ElemH5,ElemP,ElemPRE,ElemOL,ElemUL,ElemImg> ;

class Builder : NoCopy
 {
   ElementPool pool;

   List<BlockPtr> blocks;

  public:

   Builder() {}

   ~Builder() {}

   // common

   template <class T>
   T * create() { return pool.create<T>(); }

   StrLen dup(StrLen str) { return pool.dup(str); }

   StrLen dup(const String &str) { return pool.dup(Range(str)); }

   // add

   void add(BlockPtr ptr) { blocks.add(pool,ptr); }
 };

} // namespace Dom

/* classes */

class DomConvert;

/* class DomConvert */

class DomConvert : NoCopy
 {
   Dom::Builder builder;

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

   bool fmt_a = false ;

  private:

   bool inList() const { return block>=Block_OL ; }

   bool notOpened() const { return !block || ( inList() && !item ) ; }

   TagErrorId noFormat() const;

   TagErrorId open(BlockType bt);

   TagErrorId close(BlockType bt);

   TagErrorId setFmt(bool &flag);

   TagErrorId clearFmt(bool &flag);

   static bool TestSpace(StrLen str);

  public:

   DomConvert();

   ~DomConvert();

   // title

   void setTitle(String title);

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



