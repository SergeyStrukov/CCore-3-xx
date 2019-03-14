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
#include <CCore/inc/Array.h>
#include <CCore/inc/ElementPool.h>

namespace App {

/* namespace Dom */

namespace Dom {

/* TestSpace() */

bool TestSpace(StrLen str);

/* classes */

template <class T> class List;

//enum ErrorCode;

class DomErrorId;

class Text;

class Fixed;

class TList;

struct TextBase;

struct ElemH1;

struct ElemH2;

struct ElemH3;

struct ElemH4;

struct ElemH5;

struct ElemP;

struct ElemPRE;

struct TListBase;

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

/* enum ErrorCode */

enum ErrorCode
 {
  Error_NoElem = 1,

  Error_Top,
  Error_NoTop,
  Error_TagMismatch,
  Error_NoText
 };

StrLen ToString(int code);

/* class DomErrorId */

class DomErrorId : public ErrorId
 {
  public:

   DomErrorId() {}

   DomErrorId(ErrorCode code) : ErrorId(code,ToString) {}
 };

/* class Text */

class Text : NoCopy // TODO
 {
  public:

   DomErrorId frame(Builder &builder,StrLen str);

   DomErrorId complete();
 };

/* class Fixed */

class Fixed : NoCopy // TODO
 {
  public:

   DomErrorId frame(Builder &builder,StrLen str);

   DomErrorId complete();
 };

/* class TList */

class TList : NoCopy // TODO
 {
  public:

  DomErrorId frame(Builder &builder,StrLen str);

  DomErrorId complete();
 };

/* struct TextBase */

struct TextBase : NoCopy
 {
  Text text;

  DomErrorId frame(Builder &builder,StrLen str) { return text.frame(builder,str); }

  DomErrorId complete() { return text.complete(); }
 };

/* struct ElemH1 */

struct ElemH1 : TextBase
 {
  StrLen id;
 };

/* struct ElemH2 */

struct ElemH2 : TextBase
 {
  StrLen id;
 };

/* struct ElemH3 */

struct ElemH3 : TextBase
 {
  StrLen id;
 };

/* struct ElemH4 */

struct ElemH4 : TextBase
 {
  StrLen id;
 };

/* struct ElemH5 */

struct ElemH5 : TextBase
 {
  StrLen id;
 };

/* struct ElemP */

struct ElemP : TextBase
 {
  StrLen id;
  StrLen elem_class;
 };

/* struct ElemPRE */

struct ElemPRE : NoCopy
 {
  StrLen id;
  Fixed text;

  DomErrorId frame(Builder &builder,StrLen str) { return text.frame(builder,str); }

  DomErrorId complete() { return text.complete(); }
 };

/* struct TListBase */

struct TListBase
 {
  TList list;

  DomErrorId frame(Builder &,StrLen str) { if( TestSpace(str) ) return {}; return Error_NoText; }

  DomErrorId complete() { return list.complete(); }
 };

/* struct ElemOL */

struct ElemOL : TListBase
 {
  StrLen id;
 };

/* struct ElemUL */

struct ElemUL : TListBase
 {
  StrLen id;
 };

/* struct ElemLI */

struct ElemLI : NoCopy // TODO
 {
  DomErrorId frame(Builder &builder,StrLen str);
 };

/* struct ElemImg */

struct ElemImg : NoCopy
 {
  StrLen id;
  StrLen file_name;
 };

/* class Builder */

using BlockPtr = AnyPtr<ElemH1,ElemH2,ElemH3,ElemH4,ElemH5,ElemP,ElemPRE,ElemOL,ElemUL,ElemImg> ;

using ElemPtr = AnyPtr<ElemH1,ElemH2,ElemH3,ElemH4,ElemH5,ElemP,ElemPRE,ElemOL,ElemUL,ElemLI> ;

class Builder : NoCopy
 {
   ElementPool pool;

   StrLen title;

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

   void setTitle(StrLen title_) { title=title_; }

   void add(BlockPtr ptr) { blocks.add(pool,ptr); }
 };

} // namespace Dom

/* functions */

template <class T,class ... TT>
bool TrySetAnyPtr(AnyPtr<TT...> &dst,T *ptr) requires ( OneOfTypes<T,TT...> )
 {
  dst=ptr;

  return true;
 }

template <class T,class Ptr>
bool TrySetAnyPtr(T &,Ptr)
 {
  return false;
 }

template <class T,class S>
bool TryCastAnyPtr(T &dst,S src)
 {
  bool null=true;
  bool ret=false;

  src.apply( [&] (auto *ptr) { ret=TrySetAnyPtr(dst,ptr); null=false; } );

  if( null )
    {
     dst=Null;

     return true;
    }

  return ret;
 }

/* guard functions */

void GuardStackEmpty();

/* classes */

template <class T> class Stack;

class DomConvert;

/* class Stack<T> */

template <class T>
class Stack : NoCopy
 {
   DynArray<T> buf;

  public:

   Stack() : buf(DoReserve,100) {}

   ~Stack() {}

   bool isEmpty() const { return buf.isEmpty(); }

   T top() const
    {
     ulen len=buf.getLen();

     if( !len ) GuardStackEmpty();

     return buf[len-1];
    }

   void push(const T &obj)
    {
     buf.append_copy(obj);
    }

   T pop()
    {
     T ret=top();

     buf.shrink_one();

     return ret;
    }
 };

/* class DomConvert */

class DomConvert : NoCopy
 {
   Dom::Builder builder;

   Stack<Dom::ElemPtr> stack;

   String id;
   bool has_id = false ;

  public:

   using EId = Dom::DomErrorId ;

  private:

   template <class Elem,class Func>
   EId openBlock(Func func);

   template <class Elem>
   EId openBlock() { return openBlock<Elem>( [] (Elem *) {} ); }

   template <class Elem>
   EId closeBlock();

  public:

   DomConvert();

   ~DomConvert();

   // title

   void setTitle(String title);

   // id

   void setId(String id);

   // frame

   EId frame(String str);

   // text

   EId tagH1();

   EId tagH1end();

   EId tagH2();

   EId tagH2end();

   EId tagH3();

   EId tagH3end();

   EId tagH4();

   EId tagH4end();

   EId tagH5();

   EId tagH5end();

   EId tagP();

   EId tagP(String tclass);

   EId tagPend();

   EId tagPRE();

   EId tagPREend();

   // format

   EId tagB();

   EId tagBend();

   EId tagI();

   EId tagIend();

   EId tagU();

   EId tagUend();

   EId tagSUB();

   EId tagSUBend();

   EId tagSUP();

   EId tagSUPend();

   EId tagSPAN(String tclass);

   EId tagSPANend();

   // hyperlink

   EId tagA(String url);

   EId tagA(String type,String url);

   EId tagAend();

   // list

   EId tagOL();

   EId tagOLend();

   EId tagUL();

   EId tagULend();

   EId tagLI();

   EId tagLIend();

   // image

   EId tagImg(String file_name);

   // complete

   EId complete();
 };

} // namespace App

#endif



